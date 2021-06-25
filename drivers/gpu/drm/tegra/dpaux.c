<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 NVIDIA Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/workqueue.h>

#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_panel.h>

#समावेश "dp.h"
#समावेश "dpaux.h"
#समावेश "drm.h"
#समावेश "trace.h"

अटल DEFINE_MUTEX(dpaux_lock);
अटल LIST_HEAD(dpaux_list);

काष्ठा tegra_dpaux_soc अणु
	अचिन्हित पूर्णांक cmh;
	अचिन्हित पूर्णांक drvz;
	अचिन्हित पूर्णांक drvi;
पूर्ण;

काष्ठा tegra_dpaux अणु
	काष्ठा drm_dp_aux aux;
	काष्ठा device *dev;

	स्थिर काष्ठा tegra_dpaux_soc *soc;

	व्योम __iomem *regs;
	पूर्णांक irq;

	काष्ठा tegra_output *output;

	काष्ठा reset_control *rst;
	काष्ठा clk *clk_parent;
	काष्ठा clk *clk;

	काष्ठा regulator *vdd;

	काष्ठा completion complete;
	काष्ठा work_काष्ठा work;
	काष्ठा list_head list;

#अगर_घोषित CONFIG_GENERIC_PINCONF
	काष्ठा pinctrl_dev *pinctrl;
	काष्ठा pinctrl_desc desc;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा tegra_dpaux *to_dpaux(काष्ठा drm_dp_aux *aux)
अणु
	वापस container_of(aux, काष्ठा tegra_dpaux, aux);
पूर्ण

अटल अंतरभूत काष्ठा tegra_dpaux *work_to_dpaux(काष्ठा work_काष्ठा *work)
अणु
	वापस container_of(work, काष्ठा tegra_dpaux, work);
पूर्ण

अटल अंतरभूत u32 tegra_dpaux_पढ़ोl(काष्ठा tegra_dpaux *dpaux,
				    अचिन्हित पूर्णांक offset)
अणु
	u32 value = पढ़ोl(dpaux->regs + (offset << 2));

	trace_dpaux_पढ़ोl(dpaux->dev, offset, value);

	वापस value;
पूर्ण

अटल अंतरभूत व्योम tegra_dpaux_ग_लिखोl(काष्ठा tegra_dpaux *dpaux,
				      u32 value, अचिन्हित पूर्णांक offset)
अणु
	trace_dpaux_ग_लिखोl(dpaux->dev, offset, value);
	ग_लिखोl(value, dpaux->regs + (offset << 2));
पूर्ण

अटल व्योम tegra_dpaux_ग_लिखो_fअगरo(काष्ठा tegra_dpaux *dpaux, स्थिर u8 *buffer,
				   माप_प्रकार size)
अणु
	माप_प्रकार i, j;

	क्रम (i = 0; i < DIV_ROUND_UP(size, 4); i++) अणु
		माप_प्रकार num = min_t(माप_प्रकार, size - i * 4, 4);
		u32 value = 0;

		क्रम (j = 0; j < num; j++)
			value |= buffer[i * 4 + j] << (j * 8);

		tegra_dpaux_ग_लिखोl(dpaux, value, DPAUX_DP_AUXDATA_WRITE(i));
	पूर्ण
पूर्ण

अटल व्योम tegra_dpaux_पढ़ो_fअगरo(काष्ठा tegra_dpaux *dpaux, u8 *buffer,
				  माप_प्रकार size)
अणु
	माप_प्रकार i, j;

	क्रम (i = 0; i < DIV_ROUND_UP(size, 4); i++) अणु
		माप_प्रकार num = min_t(माप_प्रकार, size - i * 4, 4);
		u32 value;

		value = tegra_dpaux_पढ़ोl(dpaux, DPAUX_DP_AUXDATA_READ(i));

		क्रम (j = 0; j < num; j++)
			buffer[i * 4 + j] = value >> (j * 8);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार tegra_dpaux_transfer(काष्ठा drm_dp_aux *aux,
				    काष्ठा drm_dp_aux_msg *msg)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(250);
	काष्ठा tegra_dpaux *dpaux = to_dpaux(aux);
	अचिन्हित दीर्घ status;
	sमाप_प्रकार ret = 0;
	u8 reply = 0;
	u32 value;

	/* Tegra has 4x4 byte DP AUX transmit and receive FIFOs. */
	अगर (msg->size > 16)
		वापस -EINVAL;

	/*
	 * Allow zero-sized messages only क्रम I2C, in which हाल they specअगरy
	 * address-only transactions.
	 */
	अगर (msg->size < 1) अणु
		चयन (msg->request & ~DP_AUX_I2C_MOT) अणु
		हाल DP_AUX_I2C_WRITE_STATUS_UPDATE:
		हाल DP_AUX_I2C_WRITE:
		हाल DP_AUX_I2C_READ:
			value = DPAUX_DP_AUXCTL_CMD_ADDRESS_ONLY;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* For non-zero-sized messages, set the CMDLEN field. */
		value = DPAUX_DP_AUXCTL_CMDLEN(msg->size - 1);
	पूर्ण

	चयन (msg->request & ~DP_AUX_I2C_MOT) अणु
	हाल DP_AUX_I2C_WRITE:
		अगर (msg->request & DP_AUX_I2C_MOT)
			value |= DPAUX_DP_AUXCTL_CMD_MOT_WR;
		अन्यथा
			value |= DPAUX_DP_AUXCTL_CMD_I2C_WR;

		अवरोध;

	हाल DP_AUX_I2C_READ:
		अगर (msg->request & DP_AUX_I2C_MOT)
			value |= DPAUX_DP_AUXCTL_CMD_MOT_RD;
		अन्यथा
			value |= DPAUX_DP_AUXCTL_CMD_I2C_RD;

		अवरोध;

	हाल DP_AUX_I2C_WRITE_STATUS_UPDATE:
		अगर (msg->request & DP_AUX_I2C_MOT)
			value |= DPAUX_DP_AUXCTL_CMD_MOT_RQ;
		अन्यथा
			value |= DPAUX_DP_AUXCTL_CMD_I2C_RQ;

		अवरोध;

	हाल DP_AUX_NATIVE_WRITE:
		value |= DPAUX_DP_AUXCTL_CMD_AUX_WR;
		अवरोध;

	हाल DP_AUX_NATIVE_READ:
		value |= DPAUX_DP_AUXCTL_CMD_AUX_RD;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	tegra_dpaux_ग_लिखोl(dpaux, msg->address, DPAUX_DP_AUXADDR);
	tegra_dpaux_ग_लिखोl(dpaux, value, DPAUX_DP_AUXCTL);

	अगर ((msg->request & DP_AUX_I2C_READ) == 0) अणु
		tegra_dpaux_ग_लिखो_fअगरo(dpaux, msg->buffer, msg->size);
		ret = msg->size;
	पूर्ण

	/* start transaction */
	value = tegra_dpaux_पढ़ोl(dpaux, DPAUX_DP_AUXCTL);
	value |= DPAUX_DP_AUXCTL_TRANSACTREQ;
	tegra_dpaux_ग_लिखोl(dpaux, value, DPAUX_DP_AUXCTL);

	status = रुको_क्रम_completion_समयout(&dpaux->complete, समयout);
	अगर (!status)
		वापस -ETIMEDOUT;

	/* पढ़ो status and clear errors */
	value = tegra_dpaux_पढ़ोl(dpaux, DPAUX_DP_AUXSTAT);
	tegra_dpaux_ग_लिखोl(dpaux, 0xf00, DPAUX_DP_AUXSTAT);

	अगर (value & DPAUX_DP_AUXSTAT_TIMEOUT_ERROR)
		वापस -ETIMEDOUT;

	अगर ((value & DPAUX_DP_AUXSTAT_RX_ERROR) ||
	    (value & DPAUX_DP_AUXSTAT_SINKSTAT_ERROR) ||
	    (value & DPAUX_DP_AUXSTAT_NO_STOP_ERROR))
		वापस -EIO;

	चयन ((value & DPAUX_DP_AUXSTAT_REPLY_TYPE_MASK) >> 16) अणु
	हाल 0x00:
		reply = DP_AUX_NATIVE_REPLY_ACK;
		अवरोध;

	हाल 0x01:
		reply = DP_AUX_NATIVE_REPLY_NACK;
		अवरोध;

	हाल 0x02:
		reply = DP_AUX_NATIVE_REPLY_DEFER;
		अवरोध;

	हाल 0x04:
		reply = DP_AUX_I2C_REPLY_NACK;
		अवरोध;

	हाल 0x08:
		reply = DP_AUX_I2C_REPLY_DEFER;
		अवरोध;
	पूर्ण

	अगर ((msg->size > 0) && (msg->reply == DP_AUX_NATIVE_REPLY_ACK)) अणु
		अगर (msg->request & DP_AUX_I2C_READ) अणु
			माप_प्रकार count = value & DPAUX_DP_AUXSTAT_REPLY_MASK;

			/*
			 * There might be a smarter way to करो this, but since
			 * the DP helpers will alपढ़ोy retry transactions क्रम
			 * an -EBUSY वापस value, simply reuse that instead.
			 */
			अगर (count != msg->size) अणु
				ret = -EBUSY;
				जाओ out;
			पूर्ण

			tegra_dpaux_पढ़ो_fअगरo(dpaux, msg->buffer, count);
			ret = count;
		पूर्ण
	पूर्ण

	msg->reply = reply;

out:
	वापस ret;
पूर्ण

अटल व्योम tegra_dpaux_hotplug(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tegra_dpaux *dpaux = work_to_dpaux(work);

	अगर (dpaux->output)
		drm_helper_hpd_irq_event(dpaux->output->connector.dev);
पूर्ण

अटल irqवापस_t tegra_dpaux_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_dpaux *dpaux = data;
	irqवापस_t ret = IRQ_HANDLED;
	u32 value;

	/* clear पूर्णांकerrupts */
	value = tegra_dpaux_पढ़ोl(dpaux, DPAUX_INTR_AUX);
	tegra_dpaux_ग_लिखोl(dpaux, value, DPAUX_INTR_AUX);

	अगर (value & (DPAUX_INTR_PLUG_EVENT | DPAUX_INTR_UNPLUG_EVENT))
		schedule_work(&dpaux->work);

	अगर (value & DPAUX_INTR_IRQ_EVENT) अणु
		/* TODO: handle this */
	पूर्ण

	अगर (value & DPAUX_INTR_AUX_DONE)
		complete(&dpaux->complete);

	वापस ret;
पूर्ण

क्रमागत tegra_dpaux_functions अणु
	DPAUX_PADCTL_FUNC_AUX,
	DPAUX_PADCTL_FUNC_I2C,
	DPAUX_PADCTL_FUNC_OFF,
पूर्ण;

अटल व्योम tegra_dpaux_pad_घातer_करोwn(काष्ठा tegra_dpaux *dpaux)
अणु
	u32 value = tegra_dpaux_पढ़ोl(dpaux, DPAUX_HYBRID_SPARE);

	value |= DPAUX_HYBRID_SPARE_PAD_POWER_DOWN;

	tegra_dpaux_ग_लिखोl(dpaux, value, DPAUX_HYBRID_SPARE);
पूर्ण

अटल व्योम tegra_dpaux_pad_घातer_up(काष्ठा tegra_dpaux *dpaux)
अणु
	u32 value = tegra_dpaux_पढ़ोl(dpaux, DPAUX_HYBRID_SPARE);

	value &= ~DPAUX_HYBRID_SPARE_PAD_POWER_DOWN;

	tegra_dpaux_ग_लिखोl(dpaux, value, DPAUX_HYBRID_SPARE);
पूर्ण

अटल पूर्णांक tegra_dpaux_pad_config(काष्ठा tegra_dpaux *dpaux, अचिन्हित function)
अणु
	u32 value;

	चयन (function) अणु
	हाल DPAUX_PADCTL_FUNC_AUX:
		value = DPAUX_HYBRID_PADCTL_AUX_CMH(dpaux->soc->cmh) |
			DPAUX_HYBRID_PADCTL_AUX_DRVZ(dpaux->soc->drvz) |
			DPAUX_HYBRID_PADCTL_AUX_DRVI(dpaux->soc->drvi) |
			DPAUX_HYBRID_PADCTL_AUX_INPUT_RCV |
			DPAUX_HYBRID_PADCTL_MODE_AUX;
		अवरोध;

	हाल DPAUX_PADCTL_FUNC_I2C:
		value = DPAUX_HYBRID_PADCTL_I2C_SDA_INPUT_RCV |
			DPAUX_HYBRID_PADCTL_I2C_SCL_INPUT_RCV |
			DPAUX_HYBRID_PADCTL_AUX_CMH(dpaux->soc->cmh) |
			DPAUX_HYBRID_PADCTL_AUX_DRVZ(dpaux->soc->drvz) |
			DPAUX_HYBRID_PADCTL_AUX_DRVI(dpaux->soc->drvi) |
			DPAUX_HYBRID_PADCTL_MODE_I2C;
		अवरोध;

	हाल DPAUX_PADCTL_FUNC_OFF:
		tegra_dpaux_pad_घातer_करोwn(dpaux);
		वापस 0;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	tegra_dpaux_ग_लिखोl(dpaux, value, DPAUX_HYBRID_PADCTL);
	tegra_dpaux_pad_घातer_up(dpaux);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_GENERIC_PINCONF
अटल स्थिर काष्ठा pinctrl_pin_desc tegra_dpaux_pins[] = अणु
	PINCTRL_PIN(0, "DP_AUX_CHx_P"),
	PINCTRL_PIN(1, "DP_AUX_CHx_N"),
पूर्ण;

अटल स्थिर अचिन्हित tegra_dpaux_pin_numbers[] = अणु 0, 1 पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra_dpaux_groups[] = अणु
	"dpaux-io",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra_dpaux_functions[] = अणु
	"aux",
	"i2c",
	"off",
पूर्ण;

अटल पूर्णांक tegra_dpaux_get_groups_count(काष्ठा pinctrl_dev *pinctrl)
अणु
	वापस ARRAY_SIZE(tegra_dpaux_groups);
पूर्ण

अटल स्थिर अक्षर *tegra_dpaux_get_group_name(काष्ठा pinctrl_dev *pinctrl,
					      अचिन्हित पूर्णांक group)
अणु
	वापस tegra_dpaux_groups[group];
पूर्ण

अटल पूर्णांक tegra_dpaux_get_group_pins(काष्ठा pinctrl_dev *pinctrl,
				      अचिन्हित group, स्थिर अचिन्हित **pins,
				      अचिन्हित *num_pins)
अणु
	*pins = tegra_dpaux_pin_numbers;
	*num_pins = ARRAY_SIZE(tegra_dpaux_pin_numbers);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops tegra_dpaux_pinctrl_ops = अणु
	.get_groups_count = tegra_dpaux_get_groups_count,
	.get_group_name = tegra_dpaux_get_group_name,
	.get_group_pins = tegra_dpaux_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map = pinconf_generic_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक tegra_dpaux_get_functions_count(काष्ठा pinctrl_dev *pinctrl)
अणु
	वापस ARRAY_SIZE(tegra_dpaux_functions);
पूर्ण

अटल स्थिर अक्षर *tegra_dpaux_get_function_name(काष्ठा pinctrl_dev *pinctrl,
						 अचिन्हित पूर्णांक function)
अणु
	वापस tegra_dpaux_functions[function];
पूर्ण

अटल पूर्णांक tegra_dpaux_get_function_groups(काष्ठा pinctrl_dev *pinctrl,
					   अचिन्हित पूर्णांक function,
					   स्थिर अक्षर * स्थिर **groups,
					   अचिन्हित * स्थिर num_groups)
अणु
	*num_groups = ARRAY_SIZE(tegra_dpaux_groups);
	*groups = tegra_dpaux_groups;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dpaux_set_mux(काष्ठा pinctrl_dev *pinctrl,
			       अचिन्हित पूर्णांक function, अचिन्हित पूर्णांक group)
अणु
	काष्ठा tegra_dpaux *dpaux = pinctrl_dev_get_drvdata(pinctrl);

	वापस tegra_dpaux_pad_config(dpaux, function);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops tegra_dpaux_pinmux_ops = अणु
	.get_functions_count = tegra_dpaux_get_functions_count,
	.get_function_name = tegra_dpaux_get_function_name,
	.get_function_groups = tegra_dpaux_get_function_groups,
	.set_mux = tegra_dpaux_set_mux,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक tegra_dpaux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_dpaux *dpaux;
	काष्ठा resource *regs;
	u32 value;
	पूर्णांक err;

	dpaux = devm_kzalloc(&pdev->dev, माप(*dpaux), GFP_KERNEL);
	अगर (!dpaux)
		वापस -ENOMEM;

	dpaux->soc = of_device_get_match_data(&pdev->dev);
	INIT_WORK(&dpaux->work, tegra_dpaux_hotplug);
	init_completion(&dpaux->complete);
	INIT_LIST_HEAD(&dpaux->list);
	dpaux->dev = &pdev->dev;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dpaux->regs = devm_ioremap_resource(&pdev->dev, regs);
	अगर (IS_ERR(dpaux->regs))
		वापस PTR_ERR(dpaux->regs);

	dpaux->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dpaux->irq < 0) अणु
		dev_err(&pdev->dev, "failed to get IRQ\n");
		वापस -ENXIO;
	पूर्ण

	अगर (!pdev->dev.pm_करोमुख्य) अणु
		dpaux->rst = devm_reset_control_get(&pdev->dev, "dpaux");
		अगर (IS_ERR(dpaux->rst)) अणु
			dev_err(&pdev->dev,
				"failed to get reset control: %ld\n",
				PTR_ERR(dpaux->rst));
			वापस PTR_ERR(dpaux->rst);
		पूर्ण
	पूर्ण

	dpaux->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dpaux->clk)) अणु
		dev_err(&pdev->dev, "failed to get module clock: %ld\n",
			PTR_ERR(dpaux->clk));
		वापस PTR_ERR(dpaux->clk);
	पूर्ण

	dpaux->clk_parent = devm_clk_get(&pdev->dev, "parent");
	अगर (IS_ERR(dpaux->clk_parent)) अणु
		dev_err(&pdev->dev, "failed to get parent clock: %ld\n",
			PTR_ERR(dpaux->clk_parent));
		वापस PTR_ERR(dpaux->clk_parent);
	पूर्ण

	err = clk_set_rate(dpaux->clk_parent, 270000000);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to set clock to 270 MHz: %d\n",
			err);
		वापस err;
	पूर्ण

	dpaux->vdd = devm_regulator_get_optional(&pdev->dev, "vdd");
	अगर (IS_ERR(dpaux->vdd)) अणु
		अगर (PTR_ERR(dpaux->vdd) != -ENODEV) अणु
			अगर (PTR_ERR(dpaux->vdd) != -EPROBE_DEFER)
				dev_err(&pdev->dev,
					"failed to get VDD supply: %ld\n",
					PTR_ERR(dpaux->vdd));

			वापस PTR_ERR(dpaux->vdd);
		पूर्ण

		dpaux->vdd = शून्य;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dpaux);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	err = devm_request_irq(dpaux->dev, dpaux->irq, tegra_dpaux_irq, 0,
			       dev_name(dpaux->dev), dpaux);
	अगर (err < 0) अणु
		dev_err(dpaux->dev, "failed to request IRQ#%u: %d\n",
			dpaux->irq, err);
		वापस err;
	पूर्ण

	disable_irq(dpaux->irq);

	dpaux->aux.transfer = tegra_dpaux_transfer;
	dpaux->aux.dev = &pdev->dev;

	drm_dp_aux_init(&dpaux->aux);

	/*
	 * Assume that by शेष the DPAUX/I2C pads will be used क्रम HDMI,
	 * so घातer them up and configure them in I2C mode.
	 *
	 * The DPAUX code paths reconfigure the pads in AUX mode, but there
	 * is no possibility to perक्रमm the I2C mode configuration in the
	 * HDMI path.
	 */
	err = tegra_dpaux_pad_config(dpaux, DPAUX_PADCTL_FUNC_I2C);
	अगर (err < 0)
		वापस err;

#अगर_घोषित CONFIG_GENERIC_PINCONF
	dpaux->desc.name = dev_name(&pdev->dev);
	dpaux->desc.pins = tegra_dpaux_pins;
	dpaux->desc.npins = ARRAY_SIZE(tegra_dpaux_pins);
	dpaux->desc.pctlops = &tegra_dpaux_pinctrl_ops;
	dpaux->desc.pmxops = &tegra_dpaux_pinmux_ops;
	dpaux->desc.owner = THIS_MODULE;

	dpaux->pinctrl = devm_pinctrl_रेजिस्टर(&pdev->dev, &dpaux->desc, dpaux);
	अगर (IS_ERR(dpaux->pinctrl)) अणु
		dev_err(&pdev->dev, "failed to register pincontrol\n");
		वापस PTR_ERR(dpaux->pinctrl);
	पूर्ण
#पूर्ण_अगर
	/* enable and clear all पूर्णांकerrupts */
	value = DPAUX_INTR_AUX_DONE | DPAUX_INTR_IRQ_EVENT |
		DPAUX_INTR_UNPLUG_EVENT | DPAUX_INTR_PLUG_EVENT;
	tegra_dpaux_ग_लिखोl(dpaux, value, DPAUX_INTR_EN_AUX);
	tegra_dpaux_ग_लिखोl(dpaux, value, DPAUX_INTR_AUX);

	mutex_lock(&dpaux_lock);
	list_add_tail(&dpaux->list, &dpaux_list);
	mutex_unlock(&dpaux_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dpaux_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_dpaux *dpaux = platक्रमm_get_drvdata(pdev);

	cancel_work_sync(&dpaux->work);

	/* make sure pads are घातered करोwn when not in use */
	tegra_dpaux_pad_घातer_करोwn(dpaux);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	mutex_lock(&dpaux_lock);
	list_del(&dpaux->list);
	mutex_unlock(&dpaux_lock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tegra_dpaux_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_dpaux *dpaux = dev_get_drvdata(dev);
	पूर्णांक err = 0;

	अगर (dpaux->rst) अणु
		err = reset_control_निश्चित(dpaux->rst);
		अगर (err < 0) अणु
			dev_err(dev, "failed to assert reset: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	usleep_range(1000, 2000);

	clk_disable_unprepare(dpaux->clk_parent);
	clk_disable_unprepare(dpaux->clk);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_dpaux_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_dpaux *dpaux = dev_get_drvdata(dev);
	पूर्णांक err;

	err = clk_prepare_enable(dpaux->clk);
	अगर (err < 0) अणु
		dev_err(dev, "failed to enable clock: %d\n", err);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(dpaux->clk_parent);
	अगर (err < 0) अणु
		dev_err(dev, "failed to enable parent clock: %d\n", err);
		जाओ disable_clk;
	पूर्ण

	usleep_range(1000, 2000);

	अगर (dpaux->rst) अणु
		err = reset_control_deनिश्चित(dpaux->rst);
		अगर (err < 0) अणु
			dev_err(dev, "failed to deassert reset: %d\n", err);
			जाओ disable_parent;
		पूर्ण

		usleep_range(1000, 2000);
	पूर्ण

	वापस 0;

disable_parent:
	clk_disable_unprepare(dpaux->clk_parent);
disable_clk:
	clk_disable_unprepare(dpaux->clk);
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops tegra_dpaux_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_dpaux_suspend, tegra_dpaux_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा tegra_dpaux_soc tegra124_dpaux_soc = अणु
	.cmh = 0x02,
	.drvz = 0x04,
	.drvi = 0x18,
पूर्ण;

अटल स्थिर काष्ठा tegra_dpaux_soc tegra210_dpaux_soc = अणु
	.cmh = 0x02,
	.drvz = 0x04,
	.drvi = 0x30,
पूर्ण;

अटल स्थिर काष्ठा tegra_dpaux_soc tegra194_dpaux_soc = अणु
	.cmh = 0x02,
	.drvz = 0x04,
	.drvi = 0x2c,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_dpaux_of_match[] = अणु
	अणु .compatible = "nvidia,tegra194-dpaux", .data = &tegra194_dpaux_soc पूर्ण,
	अणु .compatible = "nvidia,tegra186-dpaux", .data = &tegra210_dpaux_soc पूर्ण,
	अणु .compatible = "nvidia,tegra210-dpaux", .data = &tegra210_dpaux_soc पूर्ण,
	अणु .compatible = "nvidia,tegra124-dpaux", .data = &tegra124_dpaux_soc पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_dpaux_of_match);

काष्ठा platक्रमm_driver tegra_dpaux_driver = अणु
	.driver = अणु
		.name = "tegra-dpaux",
		.of_match_table = tegra_dpaux_of_match,
		.pm = &tegra_dpaux_pm_ops,
	पूर्ण,
	.probe = tegra_dpaux_probe,
	.हटाओ = tegra_dpaux_हटाओ,
पूर्ण;

काष्ठा drm_dp_aux *drm_dp_aux_find_by_of_node(काष्ठा device_node *np)
अणु
	काष्ठा tegra_dpaux *dpaux;

	mutex_lock(&dpaux_lock);

	list_क्रम_each_entry(dpaux, &dpaux_list, list)
		अगर (np == dpaux->dev->of_node) अणु
			mutex_unlock(&dpaux_lock);
			वापस &dpaux->aux;
		पूर्ण

	mutex_unlock(&dpaux_lock);

	वापस शून्य;
पूर्ण

पूर्णांक drm_dp_aux_attach(काष्ठा drm_dp_aux *aux, काष्ठा tegra_output *output)
अणु
	काष्ठा tegra_dpaux *dpaux = to_dpaux(aux);
	अचिन्हित दीर्घ समयout;
	पूर्णांक err;

	err = drm_dp_aux_रेजिस्टर(aux);
	अगर (err < 0)
		वापस err;

	output->connector.polled = DRM_CONNECTOR_POLL_HPD;
	dpaux->output = output;

	अगर (output->panel) अणु
		क्रमागत drm_connector_status status;

		अगर (dpaux->vdd) अणु
			err = regulator_enable(dpaux->vdd);
			अगर (err < 0)
				वापस err;
		पूर्ण

		समयout = jअगरfies + msecs_to_jअगरfies(250);

		जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
			status = drm_dp_aux_detect(aux);

			अगर (status == connector_status_connected)
				अवरोध;

			usleep_range(1000, 2000);
		पूर्ण

		अगर (status != connector_status_connected)
			वापस -ETIMEDOUT;
	पूर्ण

	enable_irq(dpaux->irq);
	वापस 0;
पूर्ण

पूर्णांक drm_dp_aux_detach(काष्ठा drm_dp_aux *aux)
अणु
	काष्ठा tegra_dpaux *dpaux = to_dpaux(aux);
	अचिन्हित दीर्घ समयout;
	पूर्णांक err;

	drm_dp_aux_unरेजिस्टर(aux);
	disable_irq(dpaux->irq);

	अगर (dpaux->output->panel) अणु
		क्रमागत drm_connector_status status;

		अगर (dpaux->vdd) अणु
			err = regulator_disable(dpaux->vdd);
			अगर (err < 0)
				वापस err;
		पूर्ण

		समयout = jअगरfies + msecs_to_jअगरfies(250);

		जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
			status = drm_dp_aux_detect(aux);

			अगर (status == connector_status_disconnected)
				अवरोध;

			usleep_range(1000, 2000);
		पूर्ण

		अगर (status != connector_status_disconnected)
			वापस -ETIMEDOUT;

		dpaux->output = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत drm_connector_status drm_dp_aux_detect(काष्ठा drm_dp_aux *aux)
अणु
	काष्ठा tegra_dpaux *dpaux = to_dpaux(aux);
	u32 value;

	value = tegra_dpaux_पढ़ोl(dpaux, DPAUX_DP_AUXSTAT);

	अगर (value & DPAUX_DP_AUXSTAT_HPD_STATUS)
		वापस connector_status_connected;

	वापस connector_status_disconnected;
पूर्ण

पूर्णांक drm_dp_aux_enable(काष्ठा drm_dp_aux *aux)
अणु
	काष्ठा tegra_dpaux *dpaux = to_dpaux(aux);

	वापस tegra_dpaux_pad_config(dpaux, DPAUX_PADCTL_FUNC_AUX);
पूर्ण

पूर्णांक drm_dp_aux_disable(काष्ठा drm_dp_aux *aux)
अणु
	काष्ठा tegra_dpaux *dpaux = to_dpaux(aux);

	tegra_dpaux_pad_घातer_करोwn(dpaux);

	वापस 0;
पूर्ण
