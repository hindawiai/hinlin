<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip OTP Driver
 *
 * Copyright (c) 2018 Rockchip Electronics Co. Ltd.
 * Author: Finley Xiao <finley.xiao@rock-chips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

/* OTP Register Offsets */
#घोषणा OTPC_SBPI_CTRL			0x0020
#घोषणा OTPC_SBPI_CMD_VALID_PRE		0x0024
#घोषणा OTPC_SBPI_CS_VALID_PRE		0x0028
#घोषणा OTPC_SBPI_STATUS		0x002C
#घोषणा OTPC_USER_CTRL			0x0100
#घोषणा OTPC_USER_ADDR			0x0104
#घोषणा OTPC_USER_ENABLE		0x0108
#घोषणा OTPC_USER_Q			0x0124
#घोषणा OTPC_INT_STATUS			0x0304
#घोषणा OTPC_SBPI_CMD0_OFFSET		0x1000
#घोषणा OTPC_SBPI_CMD1_OFFSET		0x1004

/* OTP Register bits and masks */
#घोषणा OTPC_USER_ADDR_MASK		GENMASK(31, 16)
#घोषणा OTPC_USE_USER			BIT(0)
#घोषणा OTPC_USE_USER_MASK		GENMASK(16, 16)
#घोषणा OTPC_USER_FSM_ENABLE		BIT(0)
#घोषणा OTPC_USER_FSM_ENABLE_MASK	GENMASK(16, 16)
#घोषणा OTPC_SBPI_DONE			BIT(1)
#घोषणा OTPC_USER_DONE			BIT(2)

#घोषणा SBPI_DAP_ADDR			0x02
#घोषणा SBPI_DAP_ADDR_SHIFT		8
#घोषणा SBPI_DAP_ADDR_MASK		GENMASK(31, 24)
#घोषणा SBPI_CMD_VALID_MASK		GENMASK(31, 16)
#घोषणा SBPI_DAP_CMD_WRF		0xC0
#घोषणा SBPI_DAP_REG_ECC		0x3A
#घोषणा SBPI_ECC_ENABLE			0x00
#घोषणा SBPI_ECC_DISABLE		0x09
#घोषणा SBPI_ENABLE			BIT(0)
#घोषणा SBPI_ENABLE_MASK		GENMASK(16, 16)

#घोषणा OTPC_TIMEOUT			10000

काष्ठा rockchip_otp अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा clk_bulk_data	*clks;
	पूर्णांक num_clks;
	काष्ठा reset_control *rst;
पूर्ण;

/* list of required घड़ीs */
अटल स्थिर अक्षर * स्थिर rockchip_otp_घड़ीs[] = अणु
	"otp", "apb_pclk", "phy",
पूर्ण;

काष्ठा rockchip_data अणु
	पूर्णांक size;
पूर्ण;

अटल पूर्णांक rockchip_otp_reset(काष्ठा rockchip_otp *otp)
अणु
	पूर्णांक ret;

	ret = reset_control_निश्चित(otp->rst);
	अगर (ret) अणु
		dev_err(otp->dev, "failed to assert otp phy %d\n", ret);
		वापस ret;
	पूर्ण

	udelay(2);

	ret = reset_control_deनिश्चित(otp->rst);
	अगर (ret) अणु
		dev_err(otp->dev, "failed to deassert otp phy %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_otp_रुको_status(काष्ठा rockchip_otp *otp, u32 flag)
अणु
	u32 status = 0;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout_atomic(otp->base + OTPC_INT_STATUS, status,
					(status & flag), 1, OTPC_TIMEOUT);
	अगर (ret)
		वापस ret;

	/* clean पूर्णांक status */
	ग_लिखोl(flag, otp->base + OTPC_INT_STATUS);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_otp_ecc_enable(काष्ठा rockchip_otp *otp, bool enable)
अणु
	पूर्णांक ret = 0;

	ग_लिखोl(SBPI_DAP_ADDR_MASK | (SBPI_DAP_ADDR << SBPI_DAP_ADDR_SHIFT),
	       otp->base + OTPC_SBPI_CTRL);

	ग_लिखोl(SBPI_CMD_VALID_MASK | 0x1, otp->base + OTPC_SBPI_CMD_VALID_PRE);
	ग_लिखोl(SBPI_DAP_CMD_WRF | SBPI_DAP_REG_ECC,
	       otp->base + OTPC_SBPI_CMD0_OFFSET);
	अगर (enable)
		ग_लिखोl(SBPI_ECC_ENABLE, otp->base + OTPC_SBPI_CMD1_OFFSET);
	अन्यथा
		ग_लिखोl(SBPI_ECC_DISABLE, otp->base + OTPC_SBPI_CMD1_OFFSET);

	ग_लिखोl(SBPI_ENABLE_MASK | SBPI_ENABLE, otp->base + OTPC_SBPI_CTRL);

	ret = rockchip_otp_रुको_status(otp, OTPC_SBPI_DONE);
	अगर (ret < 0)
		dev_err(otp->dev, "timeout during ecc_enable\n");

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_otp_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			     व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा rockchip_otp *otp = context;
	u8 *buf = val;
	पूर्णांक ret = 0;

	ret = clk_bulk_prepare_enable(otp->num_clks, otp->clks);
	अगर (ret < 0) अणु
		dev_err(otp->dev, "failed to prepare/enable clks\n");
		वापस ret;
	पूर्ण

	ret = rockchip_otp_reset(otp);
	अगर (ret) अणु
		dev_err(otp->dev, "failed to reset otp phy\n");
		जाओ disable_clks;
	पूर्ण

	ret = rockchip_otp_ecc_enable(otp, false);
	अगर (ret < 0) अणु
		dev_err(otp->dev, "rockchip_otp_ecc_enable err\n");
		जाओ disable_clks;
	पूर्ण

	ग_लिखोl(OTPC_USE_USER | OTPC_USE_USER_MASK, otp->base + OTPC_USER_CTRL);
	udelay(5);
	जबतक (bytes--) अणु
		ग_लिखोl(offset++ | OTPC_USER_ADDR_MASK,
		       otp->base + OTPC_USER_ADDR);
		ग_लिखोl(OTPC_USER_FSM_ENABLE | OTPC_USER_FSM_ENABLE_MASK,
		       otp->base + OTPC_USER_ENABLE);
		ret = rockchip_otp_रुको_status(otp, OTPC_USER_DONE);
		अगर (ret < 0) अणु
			dev_err(otp->dev, "timeout during read setup\n");
			जाओ पढ़ो_end;
		पूर्ण
		*buf++ = पढ़ोb(otp->base + OTPC_USER_Q);
	पूर्ण

पढ़ो_end:
	ग_लिखोl(0x0 | OTPC_USE_USER_MASK, otp->base + OTPC_USER_CTRL);
disable_clks:
	clk_bulk_disable_unprepare(otp->num_clks, otp->clks);

	वापस ret;
पूर्ण

अटल काष्ठा nvmem_config otp_config = अणु
	.name = "rockchip-otp",
	.owner = THIS_MODULE,
	.पढ़ो_only = true,
	.stride = 1,
	.word_size = 1,
	.reg_पढ़ो = rockchip_otp_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा rockchip_data px30_data = अणु
	.size = 0x40,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_otp_match[] = अणु
	अणु
		.compatible = "rockchip,px30-otp",
		.data = (व्योम *)&px30_data,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3308-otp",
		.data = (व्योम *)&px30_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchip_otp_match);

अटल पूर्णांक rockchip_otp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rockchip_otp *otp;
	स्थिर काष्ठा rockchip_data *data;
	काष्ठा nvmem_device *nvmem;
	पूर्णांक ret, i;

	data = of_device_get_match_data(dev);
	अगर (!data) अणु
		dev_err(dev, "failed to get match data\n");
		वापस -EINVAL;
	पूर्ण

	otp = devm_kzalloc(&pdev->dev, माप(काष्ठा rockchip_otp),
			   GFP_KERNEL);
	अगर (!otp)
		वापस -ENOMEM;

	otp->dev = dev;
	otp->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(otp->base))
		वापस PTR_ERR(otp->base);

	otp->num_clks = ARRAY_SIZE(rockchip_otp_घड़ीs);
	otp->clks = devm_kसुस्मृति(dev, otp->num_clks,
				     माप(*otp->clks), GFP_KERNEL);
	अगर (!otp->clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < otp->num_clks; ++i)
		otp->clks[i].id = rockchip_otp_घड़ीs[i];

	ret = devm_clk_bulk_get(dev, otp->num_clks, otp->clks);
	अगर (ret)
		वापस ret;

	otp->rst = devm_reset_control_get(dev, "phy");
	अगर (IS_ERR(otp->rst))
		वापस PTR_ERR(otp->rst);

	otp_config.size = data->size;
	otp_config.priv = otp;
	otp_config.dev = dev;
	nvmem = devm_nvmem_रेजिस्टर(dev, &otp_config);

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल काष्ठा platक्रमm_driver rockchip_otp_driver = अणु
	.probe = rockchip_otp_probe,
	.driver = अणु
		.name = "rockchip-otp",
		.of_match_table = rockchip_otp_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rockchip_otp_driver);
MODULE_DESCRIPTION("Rockchip OTP driver");
MODULE_LICENSE("GPL v2");
