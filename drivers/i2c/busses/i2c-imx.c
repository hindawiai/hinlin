<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	Copyright (C) 2002 Motorola GSG-China
 *
 * Author:
 *	Darius Augulis, Teltonika Inc.
 *
 * Desc.:
 *	Implementation of I2C Adapter/Algorithm Driver
 *	क्रम I2C Bus पूर्णांकegrated in Freescale i.MX/MXC processors
 *
 *	Derived from Motorola GSG China I2C example driver
 *
 *	Copyright (C) 2005 Torsten Koschorrek <koschorrek at synertronixx.de
 *	Copyright (C) 2005 Matthias Blaschke <blaschke at synertronixx.de
 *	Copyright (C) 2007 RightHand Technologies, Inc.
 *	Copyright (C) 2008 Darius Augulis <darius.augulis at teltonika.lt>
 *
 *	Copyright 2013 Freescale Semiconductor, Inc.
 *	Copyright 2020 NXP
 *
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_data/i2c-imx.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

/* This will be the driver name the kernel reports */
#घोषणा DRIVER_NAME "imx-i2c"

/*
 * Enable DMA अगर transfer byte size is bigger than this threshold.
 * As the hardware request, it must bigger than 4 bytes.\
 * I have set '16' here, maybe it's not the best but I think it's
 * the appropriate.
 */
#घोषणा DMA_THRESHOLD	16
#घोषणा DMA_TIMEOUT	1000

/* IMX I2C रेजिस्टरs:
 * the I2C रेजिस्टर offset is dअगरferent between SoCs,
 * to provid support क्रम all these chips, split the
 * रेजिस्टर offset पूर्णांकo a fixed base address and a
 * variable shअगरt value, then the full रेजिस्टर offset
 * will be calculated by
 * reg_off = ( reg_base_addr << reg_shअगरt)
 */
#घोषणा IMX_I2C_IADR	0x00	/* i2c slave address */
#घोषणा IMX_I2C_IFDR	0x01	/* i2c frequency भागider */
#घोषणा IMX_I2C_I2CR	0x02	/* i2c control */
#घोषणा IMX_I2C_I2SR	0x03	/* i2c status */
#घोषणा IMX_I2C_I2DR	0x04	/* i2c transfer data */

/*
 * All of the layerscape series SoCs support IBIC रेजिस्टर.
 */
#घोषणा IMX_I2C_IBIC	0x05    /* i2c bus पूर्णांकerrupt config */

#घोषणा IMX_I2C_REGSHIFT	2
#घोषणा VF610_I2C_REGSHIFT	0

/* Bits of IMX I2C रेजिस्टरs */
#घोषणा I2SR_RXAK	0x01
#घोषणा I2SR_IIF	0x02
#घोषणा I2SR_SRW	0x04
#घोषणा I2SR_IAL	0x10
#घोषणा I2SR_IBB	0x20
#घोषणा I2SR_IAAS	0x40
#घोषणा I2SR_ICF	0x80
#घोषणा I2CR_DMAEN	0x02
#घोषणा I2CR_RSTA	0x04
#घोषणा I2CR_TXAK	0x08
#घोषणा I2CR_MTX	0x10
#घोषणा I2CR_MSTA	0x20
#घोषणा I2CR_IIEN	0x40
#घोषणा I2CR_IEN	0x80
#घोषणा IBIC_BIIE	0x80 /* Bus idle पूर्णांकerrupt enable */

/* रेजिस्टर bits dअगरferent operating codes definition:
 * 1) I2SR: Interrupt flags clear operation dअगरfer between SoCs:
 * - ग_लिखो zero to clear(w0c) INT flag on i.MX,
 * - but ग_लिखो one to clear(w1c) INT flag on Vybrid.
 * 2) I2CR: I2C module enable operation also dअगरfer between SoCs:
 * - set I2CR_IEN bit enable the module on i.MX,
 * - but clear I2CR_IEN bit enable the module on Vybrid.
 */
#घोषणा I2SR_CLR_OPCODE_W0C	0x0
#घोषणा I2SR_CLR_OPCODE_W1C	(I2SR_IAL | I2SR_IIF)
#घोषणा I2CR_IEN_OPCODE_0	0x0
#घोषणा I2CR_IEN_OPCODE_1	I2CR_IEN

#घोषणा I2C_PM_TIMEOUT		10 /* ms */

/*
 * sorted list of घड़ी भागider, रेजिस्टर value pairs
 * taken from table 26-5, p.26-9, Freescale i.MX
 * Integrated Portable System Processor Reference Manual
 * Document Number: MC9328MXLRM, Rev. 5.1, 06/2007
 *
 * Duplicated भागider values हटाओd from list
 */
काष्ठा imx_i2c_clk_pair अणु
	u16	भाग;
	u16	val;
पूर्ण;

अटल काष्ठा imx_i2c_clk_pair imx_i2c_clk_भाग[] = अणु
	अणु 22,	0x20 पूर्ण, अणु 24,	0x21 पूर्ण, अणु 26,	0x22 पूर्ण, अणु 28,	0x23 पूर्ण,
	अणु 30,	0x00 पूर्ण,	अणु 32,	0x24 पूर्ण, अणु 36,	0x25 पूर्ण, अणु 40,	0x26 पूर्ण,
	अणु 42,	0x03 पूर्ण, अणु 44,	0x27 पूर्ण,	अणु 48,	0x28 पूर्ण, अणु 52,	0x05 पूर्ण,
	अणु 56,	0x29 पूर्ण, अणु 60,	0x06 पूर्ण, अणु 64,	0x2A पूर्ण,	अणु 72,	0x2B पूर्ण,
	अणु 80,	0x2C पूर्ण, अणु 88,	0x09 पूर्ण, अणु 96,	0x2D पूर्ण, अणु 104,	0x0A पूर्ण,
	अणु 112,	0x2E पूर्ण, अणु 128,	0x2F पूर्ण, अणु 144,	0x0C पूर्ण, अणु 160,	0x30 पूर्ण,
	अणु 192,	0x31 पूर्ण,	अणु 224,	0x32 पूर्ण, अणु 240,	0x0F पूर्ण, अणु 256,	0x33 पूर्ण,
	अणु 288,	0x10 पूर्ण, अणु 320,	0x34 पूर्ण,	अणु 384,	0x35 पूर्ण, अणु 448,	0x36 पूर्ण,
	अणु 480,	0x13 पूर्ण, अणु 512,	0x37 पूर्ण, अणु 576,	0x14 पूर्ण,	अणु 640,	0x38 पूर्ण,
	अणु 768,	0x39 पूर्ण, अणु 896,	0x3A पूर्ण, अणु 960,	0x17 पूर्ण, अणु 1024,	0x3B पूर्ण,
	अणु 1152,	0x18 पूर्ण, अणु 1280,	0x3C पूर्ण, अणु 1536,	0x3D पूर्ण, अणु 1792,	0x3E पूर्ण,
	अणु 1920,	0x1B पूर्ण,	अणु 2048,	0x3F पूर्ण, अणु 2304,	0x1C पूर्ण, अणु 2560,	0x1D पूर्ण,
	अणु 3072,	0x1E पूर्ण, अणु 3840,	0x1F पूर्ण
पूर्ण;

/* Vybrid VF610 घड़ी भागider, रेजिस्टर value pairs */
अटल काष्ठा imx_i2c_clk_pair vf610_i2c_clk_भाग[] = अणु
	अणु 20,   0x00 पूर्ण, अणु 22,   0x01 पूर्ण, अणु 24,   0x02 पूर्ण, अणु 26,   0x03 पूर्ण,
	अणु 28,   0x04 पूर्ण, अणु 30,   0x05 पूर्ण, अणु 32,   0x09 पूर्ण, अणु 34,   0x06 पूर्ण,
	अणु 36,   0x0A पूर्ण, अणु 40,   0x07 पूर्ण, अणु 44,   0x0C पूर्ण, अणु 48,   0x0D पूर्ण,
	अणु 52,   0x43 पूर्ण, अणु 56,   0x0E पूर्ण, अणु 60,   0x45 पूर्ण, अणु 64,   0x12 पूर्ण,
	अणु 68,   0x0F पूर्ण, अणु 72,   0x13 पूर्ण, अणु 80,   0x14 पूर्ण, अणु 88,   0x15 पूर्ण,
	अणु 96,   0x19 पूर्ण, अणु 104,  0x16 पूर्ण, अणु 112,  0x1A पूर्ण, अणु 128,  0x17 पूर्ण,
	अणु 136,  0x4F पूर्ण, अणु 144,  0x1C पूर्ण, अणु 160,  0x1D पूर्ण, अणु 176,  0x55 पूर्ण,
	अणु 192,  0x1E पूर्ण, अणु 208,  0x56 पूर्ण, अणु 224,  0x22 पूर्ण, अणु 228,  0x24 पूर्ण,
	अणु 240,  0x1F पूर्ण, अणु 256,  0x23 पूर्ण, अणु 288,  0x5C पूर्ण, अणु 320,  0x25 पूर्ण,
	अणु 384,  0x26 पूर्ण, अणु 448,  0x2A पूर्ण, अणु 480,  0x27 पूर्ण, अणु 512,  0x2B पूर्ण,
	अणु 576,  0x2C पूर्ण, अणु 640,  0x2D पूर्ण, अणु 768,  0x31 पूर्ण, अणु 896,  0x32 पूर्ण,
	अणु 960,  0x2F पूर्ण, अणु 1024, 0x33 पूर्ण, अणु 1152, 0x34 पूर्ण, अणु 1280, 0x35 पूर्ण,
	अणु 1536, 0x36 पूर्ण, अणु 1792, 0x3A पूर्ण, अणु 1920, 0x37 पूर्ण, अणु 2048, 0x3B पूर्ण,
	अणु 2304, 0x3C पूर्ण, अणु 2560, 0x3D पूर्ण, अणु 3072, 0x3E पूर्ण, अणु 3584, 0x7A पूर्ण,
	अणु 3840, 0x3F पूर्ण, अणु 4096, 0x7B पूर्ण, अणु 5120, 0x7D पूर्ण, अणु 6144, 0x7E पूर्ण,
पूर्ण;

क्रमागत imx_i2c_type अणु
	IMX1_I2C,
	IMX21_I2C,
	VF610_I2C,
पूर्ण;

काष्ठा imx_i2c_hwdata अणु
	क्रमागत imx_i2c_type	devtype;
	अचिन्हित		regshअगरt;
	काष्ठा imx_i2c_clk_pair	*clk_भाग;
	अचिन्हित		nभागs;
	अचिन्हित		i2sr_clr_opcode;
	अचिन्हित		i2cr_ien_opcode;
पूर्ण;

काष्ठा imx_i2c_dma अणु
	काष्ठा dma_chan		*chan_tx;
	काष्ठा dma_chan		*chan_rx;
	काष्ठा dma_chan		*chan_using;
	काष्ठा completion	cmd_complete;
	dma_addr_t		dma_buf;
	अचिन्हित पूर्णांक		dma_len;
	क्रमागत dma_transfer_direction dma_transfer_dir;
	क्रमागत dma_data_direction dma_data_dir;
पूर्ण;

काष्ठा imx_i2c_काष्ठा अणु
	काष्ठा i2c_adapter	adapter;
	काष्ठा clk		*clk;
	काष्ठा notअगरier_block	clk_change_nb;
	व्योम __iomem		*base;
	रुको_queue_head_t	queue;
	अचिन्हित दीर्घ		i2csr;
	अचिन्हित पूर्णांक		disable_delay;
	पूर्णांक			stopped;
	अचिन्हित पूर्णांक		अगरdr; /* IMX_I2C_IFDR */
	अचिन्हित पूर्णांक		cur_clk;
	अचिन्हित पूर्णांक		bitrate;
	स्थिर काष्ठा imx_i2c_hwdata	*hwdata;
	काष्ठा i2c_bus_recovery_info rinfo;

	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pinctrl_pins_शेष;
	काष्ठा pinctrl_state *pinctrl_pins_gpio;

	काष्ठा imx_i2c_dma	*dma;
	काष्ठा i2c_client	*slave;
	क्रमागत i2c_slave_event last_slave_event;
पूर्ण;

अटल स्थिर काष्ठा imx_i2c_hwdata imx1_i2c_hwdata = अणु
	.devtype		= IMX1_I2C,
	.regshअगरt		= IMX_I2C_REGSHIFT,
	.clk_भाग		= imx_i2c_clk_भाग,
	.nभागs			= ARRAY_SIZE(imx_i2c_clk_भाग),
	.i2sr_clr_opcode	= I2SR_CLR_OPCODE_W0C,
	.i2cr_ien_opcode	= I2CR_IEN_OPCODE_1,

पूर्ण;

अटल स्थिर काष्ठा imx_i2c_hwdata imx21_i2c_hwdata = अणु
	.devtype		= IMX21_I2C,
	.regshअगरt		= IMX_I2C_REGSHIFT,
	.clk_भाग		= imx_i2c_clk_भाग,
	.nभागs			= ARRAY_SIZE(imx_i2c_clk_भाग),
	.i2sr_clr_opcode	= I2SR_CLR_OPCODE_W0C,
	.i2cr_ien_opcode	= I2CR_IEN_OPCODE_1,

पूर्ण;

अटल काष्ठा imx_i2c_hwdata vf610_i2c_hwdata = अणु
	.devtype		= VF610_I2C,
	.regshअगरt		= VF610_I2C_REGSHIFT,
	.clk_भाग		= vf610_i2c_clk_भाग,
	.nभागs			= ARRAY_SIZE(vf610_i2c_clk_भाग),
	.i2sr_clr_opcode	= I2SR_CLR_OPCODE_W1C,
	.i2cr_ien_opcode	= I2CR_IEN_OPCODE_0,

पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id imx_i2c_devtype[] = अणु
	अणु
		.name = "imx1-i2c",
		.driver_data = (kernel_uदीर्घ_t)&imx1_i2c_hwdata,
	पूर्ण, अणु
		.name = "imx21-i2c",
		.driver_data = (kernel_uदीर्घ_t)&imx21_i2c_hwdata,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, imx_i2c_devtype);

अटल स्थिर काष्ठा of_device_id i2c_imx_dt_ids[] = अणु
	अणु .compatible = "fsl,imx1-i2c", .data = &imx1_i2c_hwdata, पूर्ण,
	अणु .compatible = "fsl,imx21-i2c", .data = &imx21_i2c_hwdata, पूर्ण,
	अणु .compatible = "fsl,vf610-i2c", .data = &vf610_i2c_hwdata, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_imx_dt_ids);

अटल स्थिर काष्ठा acpi_device_id i2c_imx_acpi_ids[] = अणु
	अणु"NXP0001", .driver_data = (kernel_uदीर्घ_t)&vf610_i2c_hwdataपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, i2c_imx_acpi_ids);

अटल अंतरभूत पूर्णांक is_imx1_i2c(काष्ठा imx_i2c_काष्ठा *i2c_imx)
अणु
	वापस i2c_imx->hwdata->devtype == IMX1_I2C;
पूर्ण

अटल अंतरभूत पूर्णांक is_vf610_i2c(काष्ठा imx_i2c_काष्ठा *i2c_imx)
अणु
	वापस i2c_imx->hwdata->devtype == VF610_I2C;
पूर्ण

अटल अंतरभूत व्योम imx_i2c_ग_लिखो_reg(अचिन्हित पूर्णांक val,
		काष्ठा imx_i2c_काष्ठा *i2c_imx, अचिन्हित पूर्णांक reg)
अणु
	ग_लिखोb(val, i2c_imx->base + (reg << i2c_imx->hwdata->regshअगरt));
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर imx_i2c_पढ़ो_reg(काष्ठा imx_i2c_काष्ठा *i2c_imx,
		अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोb(i2c_imx->base + (reg << i2c_imx->hwdata->regshअगरt));
पूर्ण

अटल व्योम i2c_imx_clear_irq(काष्ठा imx_i2c_काष्ठा *i2c_imx, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक temp;

	/*
	 * i2sr_clr_opcode is the value to clear all पूर्णांकerrupts. Here we want to
	 * clear only <bits>, so we ग_लिखो ~i2sr_clr_opcode with just <bits>
	 * toggled. This is required because i.MX needs W0C and Vybrid uses W1C.
	 */
	temp = ~i2c_imx->hwdata->i2sr_clr_opcode ^ bits;
	imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2SR);
पूर्ण

/* Set up i2c controller रेजिस्टर and i2c status रेजिस्टर to शेष value. */
अटल व्योम i2c_imx_reset_regs(काष्ठा imx_i2c_काष्ठा *i2c_imx)
अणु
	imx_i2c_ग_लिखो_reg(i2c_imx->hwdata->i2cr_ien_opcode ^ I2CR_IEN,
			  i2c_imx, IMX_I2C_I2CR);
	i2c_imx_clear_irq(i2c_imx, I2SR_IIF | I2SR_IAL);
पूर्ण

/* Functions क्रम DMA support */
अटल व्योम i2c_imx_dma_request(काष्ठा imx_i2c_काष्ठा *i2c_imx,
						dma_addr_t phy_addr)
अणु
	काष्ठा imx_i2c_dma *dma;
	काष्ठा dma_slave_config dma_sconfig;
	काष्ठा device *dev = &i2c_imx->adapter.dev;
	पूर्णांक ret;

	dma = devm_kzalloc(dev, माप(*dma), GFP_KERNEL);
	अगर (!dma)
		वापस;

	dma->chan_tx = dma_request_chan(dev, "tx");
	अगर (IS_ERR(dma->chan_tx)) अणु
		ret = PTR_ERR(dma->chan_tx);
		अगर (ret != -ENODEV && ret != -EPROBE_DEFER)
			dev_err(dev, "can't request DMA tx channel (%d)\n", ret);
		जाओ fail_al;
	पूर्ण

	dma_sconfig.dst_addr = phy_addr +
				(IMX_I2C_I2DR << i2c_imx->hwdata->regshअगरt);
	dma_sconfig.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma_sconfig.dst_maxburst = 1;
	dma_sconfig.direction = DMA_MEM_TO_DEV;
	ret = dmaengine_slave_config(dma->chan_tx, &dma_sconfig);
	अगर (ret < 0) अणु
		dev_err(dev, "can't configure tx channel (%d)\n", ret);
		जाओ fail_tx;
	पूर्ण

	dma->chan_rx = dma_request_chan(dev, "rx");
	अगर (IS_ERR(dma->chan_rx)) अणु
		ret = PTR_ERR(dma->chan_rx);
		अगर (ret != -ENODEV && ret != -EPROBE_DEFER)
			dev_err(dev, "can't request DMA rx channel (%d)\n", ret);
		जाओ fail_tx;
	पूर्ण

	dma_sconfig.src_addr = phy_addr +
				(IMX_I2C_I2DR << i2c_imx->hwdata->regshअगरt);
	dma_sconfig.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma_sconfig.src_maxburst = 1;
	dma_sconfig.direction = DMA_DEV_TO_MEM;
	ret = dmaengine_slave_config(dma->chan_rx, &dma_sconfig);
	अगर (ret < 0) अणु
		dev_err(dev, "can't configure rx channel (%d)\n", ret);
		जाओ fail_rx;
	पूर्ण

	i2c_imx->dma = dma;
	init_completion(&dma->cmd_complete);
	dev_info(dev, "using %s (tx) and %s (rx) for DMA transfers\n",
		dma_chan_name(dma->chan_tx), dma_chan_name(dma->chan_rx));

	वापस;

fail_rx:
	dma_release_channel(dma->chan_rx);
fail_tx:
	dma_release_channel(dma->chan_tx);
fail_al:
	devm_kमुक्त(dev, dma);
पूर्ण

अटल व्योम i2c_imx_dma_callback(व्योम *arg)
अणु
	काष्ठा imx_i2c_काष्ठा *i2c_imx = (काष्ठा imx_i2c_काष्ठा *)arg;
	काष्ठा imx_i2c_dma *dma = i2c_imx->dma;

	dma_unmap_single(dma->chan_using->device->dev, dma->dma_buf,
			dma->dma_len, dma->dma_data_dir);
	complete(&dma->cmd_complete);
पूर्ण

अटल पूर्णांक i2c_imx_dma_xfer(काष्ठा imx_i2c_काष्ठा *i2c_imx,
					काष्ठा i2c_msg *msgs)
अणु
	काष्ठा imx_i2c_dma *dma = i2c_imx->dma;
	काष्ठा dma_async_tx_descriptor *txdesc;
	काष्ठा device *dev = &i2c_imx->adapter.dev;
	काष्ठा device *chan_dev = dma->chan_using->device->dev;

	dma->dma_buf = dma_map_single(chan_dev, msgs->buf,
					dma->dma_len, dma->dma_data_dir);
	अगर (dma_mapping_error(chan_dev, dma->dma_buf)) अणु
		dev_err(dev, "DMA mapping failed\n");
		जाओ err_map;
	पूर्ण

	txdesc = dmaengine_prep_slave_single(dma->chan_using, dma->dma_buf,
					dma->dma_len, dma->dma_transfer_dir,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!txdesc) अणु
		dev_err(dev, "Not able to get desc for DMA xfer\n");
		जाओ err_desc;
	पूर्ण

	reinit_completion(&dma->cmd_complete);
	txdesc->callback = i2c_imx_dma_callback;
	txdesc->callback_param = i2c_imx;
	अगर (dma_submit_error(dmaengine_submit(txdesc))) अणु
		dev_err(dev, "DMA submit failed\n");
		जाओ err_submit;
	पूर्ण

	dma_async_issue_pending(dma->chan_using);
	वापस 0;

err_submit:
	dmaengine_terminate_all(dma->chan_using);
err_desc:
	dma_unmap_single(chan_dev, dma->dma_buf,
			dma->dma_len, dma->dma_data_dir);
err_map:
	वापस -EINVAL;
पूर्ण

अटल व्योम i2c_imx_dma_मुक्त(काष्ठा imx_i2c_काष्ठा *i2c_imx)
अणु
	काष्ठा imx_i2c_dma *dma = i2c_imx->dma;

	dma->dma_buf = 0;
	dma->dma_len = 0;

	dma_release_channel(dma->chan_tx);
	dma->chan_tx = शून्य;

	dma_release_channel(dma->chan_rx);
	dma->chan_rx = शून्य;

	dma->chan_using = शून्य;
पूर्ण

अटल पूर्णांक i2c_imx_bus_busy(काष्ठा imx_i2c_काष्ठा *i2c_imx, पूर्णांक क्रम_busy, bool atomic)
अणु
	अचिन्हित दीर्घ orig_jअगरfies = jअगरfies;
	अचिन्हित पूर्णांक temp;

	dev_dbg(&i2c_imx->adapter.dev, "<%s>\n", __func__);

	जबतक (1) अणु
		temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2SR);

		/* check क्रम arbitration lost */
		अगर (temp & I2SR_IAL) अणु
			i2c_imx_clear_irq(i2c_imx, I2SR_IAL);
			वापस -EAGAIN;
		पूर्ण

		अगर (क्रम_busy && (temp & I2SR_IBB)) अणु
			i2c_imx->stopped = 0;
			अवरोध;
		पूर्ण
		अगर (!क्रम_busy && !(temp & I2SR_IBB)) अणु
			i2c_imx->stopped = 1;
			अवरोध;
		पूर्ण
		अगर (समय_after(jअगरfies, orig_jअगरfies + msecs_to_jअगरfies(500))) अणु
			dev_dbg(&i2c_imx->adapter.dev,
				"<%s> I2C bus is busy\n", __func__);
			वापस -ETIMEDOUT;
		पूर्ण
		अगर (atomic)
			udelay(100);
		अन्यथा
			schedule();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_imx_trx_complete(काष्ठा imx_i2c_काष्ठा *i2c_imx, bool atomic)
अणु
	अगर (atomic) अणु
		व्योम __iomem *addr = i2c_imx->base + (IMX_I2C_I2SR << i2c_imx->hwdata->regshअगरt);
		अचिन्हित पूर्णांक regval;

		/*
		 * The क्रमmula क्रम the poll समयout is करोcumented in the RM
		 * Rev.5 on page 1878:
		 *     T_min = 10/F_scl
		 * Set the value hard as it is करोne क्रम the non-atomic use-हाल.
		 * Use 10 kHz क्रम the calculation since this is the minimum
		 * allowed SMBus frequency. Also add an offset of 100us since it
		 * turned out that the I2SR_IIF bit isn't set correctly within
		 * the minimum समयout in polling mode.
		 */
		पढ़ोb_poll_समयout_atomic(addr, regval, regval & I2SR_IIF, 5, 1000 + 100);
		i2c_imx->i2csr = regval;
		i2c_imx_clear_irq(i2c_imx, I2SR_IIF | I2SR_IAL);
	पूर्ण अन्यथा अणु
		रुको_event_समयout(i2c_imx->queue, i2c_imx->i2csr & I2SR_IIF, HZ / 10);
	पूर्ण

	अगर (unlikely(!(i2c_imx->i2csr & I2SR_IIF))) अणु
		dev_dbg(&i2c_imx->adapter.dev, "<%s> Timeout\n", __func__);
		वापस -ETIMEDOUT;
	पूर्ण

	/* check क्रम arbitration lost */
	अगर (i2c_imx->i2csr & I2SR_IAL) अणु
		dev_dbg(&i2c_imx->adapter.dev, "<%s> Arbitration lost\n", __func__);
		i2c_imx_clear_irq(i2c_imx, I2SR_IAL);

		i2c_imx->i2csr = 0;
		वापस -EAGAIN;
	पूर्ण

	dev_dbg(&i2c_imx->adapter.dev, "<%s> TRX complete\n", __func__);
	i2c_imx->i2csr = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_imx_acked(काष्ठा imx_i2c_काष्ठा *i2c_imx)
अणु
	अगर (imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2SR) & I2SR_RXAK) अणु
		dev_dbg(&i2c_imx->adapter.dev, "<%s> No ACK\n", __func__);
		वापस -ENXIO;  /* No ACK */
	पूर्ण

	dev_dbg(&i2c_imx->adapter.dev, "<%s> ACK received\n", __func__);
	वापस 0;
पूर्ण

अटल व्योम i2c_imx_set_clk(काष्ठा imx_i2c_काष्ठा *i2c_imx,
			    अचिन्हित पूर्णांक i2c_clk_rate)
अणु
	काष्ठा imx_i2c_clk_pair *i2c_clk_भाग = i2c_imx->hwdata->clk_भाग;
	अचिन्हित पूर्णांक भाग;
	पूर्णांक i;

	/* Divider value calculation */
	अगर (i2c_imx->cur_clk == i2c_clk_rate)
		वापस;

	i2c_imx->cur_clk = i2c_clk_rate;

	भाग = DIV_ROUND_UP(i2c_clk_rate, i2c_imx->bitrate);
	अगर (भाग < i2c_clk_भाग[0].भाग)
		i = 0;
	अन्यथा अगर (भाग > i2c_clk_भाग[i2c_imx->hwdata->nभागs - 1].भाग)
		i = i2c_imx->hwdata->nभागs - 1;
	अन्यथा
		क्रम (i = 0; i2c_clk_भाग[i].भाग < भाग; i++)
			;

	/* Store भागider value */
	i2c_imx->अगरdr = i2c_clk_भाग[i].val;

	/*
	 * There dummy delay is calculated.
	 * It should be about one I2C घड़ी period दीर्घ.
	 * This delay is used in I2C bus disable function
	 * to fix chip hardware bug.
	 */
	i2c_imx->disable_delay = DIV_ROUND_UP(500000U * i2c_clk_भाग[i].भाग,
					      i2c_clk_rate / 2);

#अगर_घोषित CONFIG_I2C_DEBUG_BUS
	dev_dbg(&i2c_imx->adapter.dev, "I2C_CLK=%d, REQ DIV=%d\n",
		i2c_clk_rate, भाग);
	dev_dbg(&i2c_imx->adapter.dev, "IFDR[IC]=0x%x, REAL DIV=%d\n",
		i2c_clk_भाग[i].val, i2c_clk_भाग[i].भाग);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक i2c_imx_clk_notअगरier_call(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *ndata = data;
	काष्ठा imx_i2c_काष्ठा *i2c_imx = container_of(nb,
						      काष्ठा imx_i2c_काष्ठा,
						      clk_change_nb);

	अगर (action & POST_RATE_CHANGE)
		i2c_imx_set_clk(i2c_imx, ndata->new_rate);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक i2c_imx_start(काष्ठा imx_i2c_काष्ठा *i2c_imx, bool atomic)
अणु
	अचिन्हित पूर्णांक temp = 0;
	पूर्णांक result;

	dev_dbg(&i2c_imx->adapter.dev, "<%s>\n", __func__);

	imx_i2c_ग_लिखो_reg(i2c_imx->अगरdr, i2c_imx, IMX_I2C_IFDR);
	/* Enable I2C controller */
	imx_i2c_ग_लिखो_reg(i2c_imx->hwdata->i2sr_clr_opcode, i2c_imx, IMX_I2C_I2SR);
	imx_i2c_ग_लिखो_reg(i2c_imx->hwdata->i2cr_ien_opcode, i2c_imx, IMX_I2C_I2CR);

	/* Wait controller to be stable */
	अगर (atomic)
		udelay(50);
	अन्यथा
		usleep_range(50, 150);

	/* Start I2C transaction */
	temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
	temp |= I2CR_MSTA;
	imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);
	result = i2c_imx_bus_busy(i2c_imx, 1, atomic);
	अगर (result)
		वापस result;

	temp |= I2CR_IIEN | I2CR_MTX | I2CR_TXAK;
	अगर (atomic)
		temp &= ~I2CR_IIEN; /* Disable पूर्णांकerrupt */

	temp &= ~I2CR_DMAEN;
	imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);
	वापस result;
पूर्ण

अटल व्योम i2c_imx_stop(काष्ठा imx_i2c_काष्ठा *i2c_imx, bool atomic)
अणु
	अचिन्हित पूर्णांक temp = 0;

	अगर (!i2c_imx->stopped) अणु
		/* Stop I2C transaction */
		dev_dbg(&i2c_imx->adapter.dev, "<%s>\n", __func__);
		temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
		अगर (!(temp & I2CR_MSTA))
			i2c_imx->stopped = 1;
		temp &= ~(I2CR_MSTA | I2CR_MTX);
		अगर (i2c_imx->dma)
			temp &= ~I2CR_DMAEN;
		imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);
	पूर्ण
	अगर (is_imx1_i2c(i2c_imx)) अणु
		/*
		 * This delay caused by an i.MXL hardware bug.
		 * If no (or too लघु) delay, no "STOP" bit will be generated.
		 */
		udelay(i2c_imx->disable_delay);
	पूर्ण

	अगर (!i2c_imx->stopped)
		i2c_imx_bus_busy(i2c_imx, 0, atomic);

	/* Disable I2C controller */
	temp = i2c_imx->hwdata->i2cr_ien_opcode ^ I2CR_IEN,
	imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);
पूर्ण

/*
 * Enable bus idle पूर्णांकerrupts
 * Note: IBIC रेजिस्टर will be cleared after disabled i2c module.
 * All of layerscape series SoCs support IBIC रेजिस्टर.
 */
अटल व्योम i2c_imx_enable_bus_idle(काष्ठा imx_i2c_काष्ठा *i2c_imx)
अणु
	अगर (is_vf610_i2c(i2c_imx)) अणु
		अचिन्हित पूर्णांक temp;

		temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_IBIC);
		temp |= IBIC_BIIE;
		imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_IBIC);
	पूर्ण
पूर्ण

अटल व्योम i2c_imx_slave_event(काष्ठा imx_i2c_काष्ठा *i2c_imx,
				क्रमागत i2c_slave_event event, u8 *val)
अणु
	i2c_slave_event(i2c_imx->slave, event, val);
	i2c_imx->last_slave_event = event;
पूर्ण

अटल व्योम i2c_imx_slave_finish_op(काष्ठा imx_i2c_काष्ठा *i2c_imx)
अणु
	u8 val;

	जबतक (i2c_imx->last_slave_event != I2C_SLAVE_STOP) अणु
		चयन (i2c_imx->last_slave_event) अणु
		हाल I2C_SLAVE_READ_REQUESTED:
			i2c_imx_slave_event(i2c_imx, I2C_SLAVE_READ_PROCESSED,
					    &val);
			अवरोध;

		हाल I2C_SLAVE_WRITE_REQUESTED:
		हाल I2C_SLAVE_READ_PROCESSED:
		हाल I2C_SLAVE_WRITE_RECEIVED:
			i2c_imx_slave_event(i2c_imx, I2C_SLAVE_STOP, &val);
			अवरोध;

		हाल I2C_SLAVE_STOP:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t i2c_imx_slave_isr(काष्ठा imx_i2c_काष्ठा *i2c_imx,
				     अचिन्हित पूर्णांक status, अचिन्हित पूर्णांक ctl)
अणु
	u8 value;

	अगर (status & I2SR_IAL) अणु /* Arbitration lost */
		i2c_imx_clear_irq(i2c_imx, I2SR_IAL);
		अगर (!(status & I2SR_IAAS))
			वापस IRQ_HANDLED;
	पूर्ण

	अगर (status & I2SR_IAAS) अणु /* Addressed as a slave */
		i2c_imx_slave_finish_op(i2c_imx);
		अगर (status & I2SR_SRW) अणु /* Master wants to पढ़ो from us*/
			dev_dbg(&i2c_imx->adapter.dev, "read requested");
			i2c_imx_slave_event(i2c_imx,
					    I2C_SLAVE_READ_REQUESTED, &value);

			/* Slave transmit */
			ctl |= I2CR_MTX;
			imx_i2c_ग_लिखो_reg(ctl, i2c_imx, IMX_I2C_I2CR);

			/* Send data */
			imx_i2c_ग_लिखो_reg(value, i2c_imx, IMX_I2C_I2DR);
		पूर्ण अन्यथा अणु /* Master wants to ग_लिखो to us */
			dev_dbg(&i2c_imx->adapter.dev, "write requested");
			i2c_imx_slave_event(i2c_imx,
					    I2C_SLAVE_WRITE_REQUESTED, &value);

			/* Slave receive */
			ctl &= ~I2CR_MTX;
			imx_i2c_ग_लिखो_reg(ctl, i2c_imx, IMX_I2C_I2CR);
			/* Dummy पढ़ो */
			imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2DR);
		पूर्ण
	पूर्ण अन्यथा अगर (!(ctl & I2CR_MTX)) अणु /* Receive mode */
		अगर (status & I2SR_IBB) अणु /* No STOP संकेत detected */
			value = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2DR);
			i2c_imx_slave_event(i2c_imx,
					    I2C_SLAVE_WRITE_RECEIVED, &value);
		पूर्ण अन्यथा अणु /* STOP संकेत is detected */
			dev_dbg(&i2c_imx->adapter.dev,
				"STOP signal detected");
			i2c_imx_slave_event(i2c_imx,
					    I2C_SLAVE_STOP, &value);
		पूर्ण
	पूर्ण अन्यथा अगर (!(status & I2SR_RXAK)) अणु /* Transmit mode received ACK */
		ctl |= I2CR_MTX;
		imx_i2c_ग_लिखो_reg(ctl, i2c_imx, IMX_I2C_I2CR);

		i2c_imx_slave_event(i2c_imx,
				    I2C_SLAVE_READ_PROCESSED, &value);

		imx_i2c_ग_लिखो_reg(value, i2c_imx, IMX_I2C_I2DR);
	पूर्ण अन्यथा अणु /* Transmit mode received NAK */
		ctl &= ~I2CR_MTX;
		imx_i2c_ग_लिखो_reg(ctl, i2c_imx, IMX_I2C_I2CR);
		imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2DR);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम i2c_imx_slave_init(काष्ठा imx_i2c_काष्ठा *i2c_imx)
अणु
	पूर्णांक temp;

	/* Set slave addr. */
	imx_i2c_ग_लिखो_reg((i2c_imx->slave->addr << 1), i2c_imx, IMX_I2C_IADR);

	i2c_imx_reset_regs(i2c_imx);

	/* Enable module */
	temp = i2c_imx->hwdata->i2cr_ien_opcode;
	imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);

	/* Enable पूर्णांकerrupt from i2c module */
	temp |= I2CR_IIEN;
	imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);

	i2c_imx_enable_bus_idle(i2c_imx);
पूर्ण

अटल पूर्णांक i2c_imx_reg_slave(काष्ठा i2c_client *client)
अणु
	काष्ठा imx_i2c_काष्ठा *i2c_imx = i2c_get_adapdata(client->adapter);
	पूर्णांक ret;

	अगर (i2c_imx->slave)
		वापस -EBUSY;

	i2c_imx->slave = client;
	i2c_imx->last_slave_event = I2C_SLAVE_STOP;

	/* Resume */
	ret = pm_runसमय_resume_and_get(i2c_imx->adapter.dev.parent);
	अगर (ret < 0) अणु
		dev_err(&i2c_imx->adapter.dev, "failed to resume i2c controller");
		वापस ret;
	पूर्ण

	i2c_imx_slave_init(i2c_imx);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_imx_unreg_slave(काष्ठा i2c_client *client)
अणु
	काष्ठा imx_i2c_काष्ठा *i2c_imx = i2c_get_adapdata(client->adapter);
	पूर्णांक ret;

	अगर (!i2c_imx->slave)
		वापस -EINVAL;

	/* Reset slave address. */
	imx_i2c_ग_लिखो_reg(0, i2c_imx, IMX_I2C_IADR);

	i2c_imx_reset_regs(i2c_imx);

	i2c_imx->slave = शून्य;

	/* Suspend */
	ret = pm_runसमय_put_sync(i2c_imx->adapter.dev.parent);
	अगर (ret < 0)
		dev_err(&i2c_imx->adapter.dev, "failed to suspend i2c controller");

	वापस ret;
पूर्ण

अटल irqवापस_t i2c_imx_master_isr(काष्ठा imx_i2c_काष्ठा *i2c_imx, अचिन्हित पूर्णांक status)
अणु
	/* save status रेजिस्टर */
	i2c_imx->i2csr = status;
	wake_up(&i2c_imx->queue);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t i2c_imx_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imx_i2c_काष्ठा *i2c_imx = dev_id;
	अचिन्हित पूर्णांक ctl, status;

	status = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2SR);
	ctl = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);

	अगर (status & I2SR_IIF) अणु
		i2c_imx_clear_irq(i2c_imx, I2SR_IIF);
		अगर (i2c_imx->slave) अणु
			अगर (!(ctl & I2CR_MSTA)) अणु
				वापस i2c_imx_slave_isr(i2c_imx, status, ctl);
			पूर्ण अन्यथा अगर (i2c_imx->last_slave_event !=
				   I2C_SLAVE_STOP) अणु
				i2c_imx_slave_finish_op(i2c_imx);
			पूर्ण
		पूर्ण
		वापस i2c_imx_master_isr(i2c_imx, status);
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक i2c_imx_dma_ग_लिखो(काष्ठा imx_i2c_काष्ठा *i2c_imx,
					काष्ठा i2c_msg *msgs)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ समय_left;
	अचिन्हित पूर्णांक temp = 0;
	अचिन्हित दीर्घ orig_jअगरfies = jअगरfies;
	काष्ठा imx_i2c_dma *dma = i2c_imx->dma;
	काष्ठा device *dev = &i2c_imx->adapter.dev;

	dma->chan_using = dma->chan_tx;
	dma->dma_transfer_dir = DMA_MEM_TO_DEV;
	dma->dma_data_dir = DMA_TO_DEVICE;
	dma->dma_len = msgs->len - 1;
	result = i2c_imx_dma_xfer(i2c_imx, msgs);
	अगर (result)
		वापस result;

	temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
	temp |= I2CR_DMAEN;
	imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);

	/*
	 * Write slave address.
	 * The first byte must be transmitted by the CPU.
	 */
	imx_i2c_ग_लिखो_reg(i2c_8bit_addr_from_msg(msgs), i2c_imx, IMX_I2C_I2DR);
	समय_left = रुको_क्रम_completion_समयout(
				&i2c_imx->dma->cmd_complete,
				msecs_to_jअगरfies(DMA_TIMEOUT));
	अगर (समय_left == 0) अणु
		dmaengine_terminate_all(dma->chan_using);
		वापस -ETIMEDOUT;
	पूर्ण

	/* Waiting क्रम transfer complete. */
	जबतक (1) अणु
		temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2SR);
		अगर (temp & I2SR_ICF)
			अवरोध;
		अगर (समय_after(jअगरfies, orig_jअगरfies +
				msecs_to_jअगरfies(DMA_TIMEOUT))) अणु
			dev_dbg(dev, "<%s> Timeout\n", __func__);
			वापस -ETIMEDOUT;
		पूर्ण
		schedule();
	पूर्ण

	temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
	temp &= ~I2CR_DMAEN;
	imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);

	/* The last data byte must be transferred by the CPU. */
	imx_i2c_ग_लिखो_reg(msgs->buf[msgs->len-1],
				i2c_imx, IMX_I2C_I2DR);
	result = i2c_imx_trx_complete(i2c_imx, false);
	अगर (result)
		वापस result;

	वापस i2c_imx_acked(i2c_imx);
पूर्ण

अटल पूर्णांक i2c_imx_dma_पढ़ो(काष्ठा imx_i2c_काष्ठा *i2c_imx,
			काष्ठा i2c_msg *msgs, bool is_lasपंचांगsg)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ समय_left;
	अचिन्हित पूर्णांक temp;
	अचिन्हित दीर्घ orig_jअगरfies = jअगरfies;
	काष्ठा imx_i2c_dma *dma = i2c_imx->dma;
	काष्ठा device *dev = &i2c_imx->adapter.dev;


	dma->chan_using = dma->chan_rx;
	dma->dma_transfer_dir = DMA_DEV_TO_MEM;
	dma->dma_data_dir = DMA_FROM_DEVICE;
	/* The last two data bytes must be transferred by the CPU. */
	dma->dma_len = msgs->len - 2;
	result = i2c_imx_dma_xfer(i2c_imx, msgs);
	अगर (result)
		वापस result;

	समय_left = रुको_क्रम_completion_समयout(
				&i2c_imx->dma->cmd_complete,
				msecs_to_jअगरfies(DMA_TIMEOUT));
	अगर (समय_left == 0) अणु
		dmaengine_terminate_all(dma->chan_using);
		वापस -ETIMEDOUT;
	पूर्ण

	/* रुकोing क्रम transfer complete. */
	जबतक (1) अणु
		temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2SR);
		अगर (temp & I2SR_ICF)
			अवरोध;
		अगर (समय_after(jअगरfies, orig_jअगरfies +
				msecs_to_jअगरfies(DMA_TIMEOUT))) अणु
			dev_dbg(dev, "<%s> Timeout\n", __func__);
			वापस -ETIMEDOUT;
		पूर्ण
		schedule();
	पूर्ण

	temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
	temp &= ~I2CR_DMAEN;
	imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);

	/* पढ़ो n-1 byte data */
	temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
	temp |= I2CR_TXAK;
	imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);

	msgs->buf[msgs->len-2] = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2DR);
	/* पढ़ो n byte data */
	result = i2c_imx_trx_complete(i2c_imx, false);
	अगर (result)
		वापस result;

	अगर (is_lasपंचांगsg) अणु
		/*
		 * It must generate STOP beक्रमe पढ़ो I2DR to prevent
		 * controller from generating another घड़ी cycle
		 */
		dev_dbg(dev, "<%s> clear MSTA\n", __func__);
		temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
		अगर (!(temp & I2CR_MSTA))
			i2c_imx->stopped = 1;
		temp &= ~(I2CR_MSTA | I2CR_MTX);
		imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);
		अगर (!i2c_imx->stopped)
			i2c_imx_bus_busy(i2c_imx, 0, false);
	पूर्ण अन्यथा अणु
		/*
		 * For i2c master receiver repeat restart operation like:
		 * पढ़ो -> repeat MSTA -> पढ़ो/ग_लिखो
		 * The controller must set MTX beक्रमe पढ़ो the last byte in
		 * the first पढ़ो operation, otherwise the first पढ़ो cost
		 * one extra घड़ी cycle.
		 */
		temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
		temp |= I2CR_MTX;
		imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);
	पूर्ण
	msgs->buf[msgs->len-1] = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2DR);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_imx_ग_लिखो(काष्ठा imx_i2c_काष्ठा *i2c_imx, काष्ठा i2c_msg *msgs,
			 bool atomic)
अणु
	पूर्णांक i, result;

	dev_dbg(&i2c_imx->adapter.dev, "<%s> write slave address: addr=0x%x\n",
		__func__, i2c_8bit_addr_from_msg(msgs));

	/* ग_लिखो slave address */
	imx_i2c_ग_लिखो_reg(i2c_8bit_addr_from_msg(msgs), i2c_imx, IMX_I2C_I2DR);
	result = i2c_imx_trx_complete(i2c_imx, atomic);
	अगर (result)
		वापस result;
	result = i2c_imx_acked(i2c_imx);
	अगर (result)
		वापस result;
	dev_dbg(&i2c_imx->adapter.dev, "<%s> write data\n", __func__);

	/* ग_लिखो data */
	क्रम (i = 0; i < msgs->len; i++) अणु
		dev_dbg(&i2c_imx->adapter.dev,
			"<%s> write byte: B%d=0x%X\n",
			__func__, i, msgs->buf[i]);
		imx_i2c_ग_लिखो_reg(msgs->buf[i], i2c_imx, IMX_I2C_I2DR);
		result = i2c_imx_trx_complete(i2c_imx, atomic);
		अगर (result)
			वापस result;
		result = i2c_imx_acked(i2c_imx);
		अगर (result)
			वापस result;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_imx_पढ़ो(काष्ठा imx_i2c_काष्ठा *i2c_imx, काष्ठा i2c_msg *msgs,
			bool is_lasपंचांगsg, bool atomic)
अणु
	पूर्णांक i, result;
	अचिन्हित पूर्णांक temp;
	पूर्णांक block_data = msgs->flags & I2C_M_RECV_LEN;
	पूर्णांक use_dma = i2c_imx->dma && msgs->len >= DMA_THRESHOLD && !block_data;

	dev_dbg(&i2c_imx->adapter.dev,
		"<%s> write slave address: addr=0x%x\n",
		__func__, i2c_8bit_addr_from_msg(msgs));

	/* ग_लिखो slave address */
	imx_i2c_ग_लिखो_reg(i2c_8bit_addr_from_msg(msgs), i2c_imx, IMX_I2C_I2DR);
	result = i2c_imx_trx_complete(i2c_imx, atomic);
	अगर (result)
		वापस result;
	result = i2c_imx_acked(i2c_imx);
	अगर (result)
		वापस result;

	dev_dbg(&i2c_imx->adapter.dev, "<%s> setup bus\n", __func__);

	/* setup bus to पढ़ो data */
	temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
	temp &= ~I2CR_MTX;

	/*
	 * Reset the I2CR_TXAK flag initially क्रम SMBus block पढ़ो since the
	 * length is unknown
	 */
	अगर ((msgs->len - 1) || block_data)
		temp &= ~I2CR_TXAK;
	अगर (use_dma)
		temp |= I2CR_DMAEN;
	imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);
	imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2DR); /* dummy पढ़ो */

	dev_dbg(&i2c_imx->adapter.dev, "<%s> read data\n", __func__);

	अगर (use_dma)
		वापस i2c_imx_dma_पढ़ो(i2c_imx, msgs, is_lasपंचांगsg);

	/* पढ़ो data */
	क्रम (i = 0; i < msgs->len; i++) अणु
		u8 len = 0;

		result = i2c_imx_trx_complete(i2c_imx, atomic);
		अगर (result)
			वापस result;
		/*
		 * First byte is the length of reमुख्यing packet
		 * in the SMBus block data पढ़ो. Add it to
		 * msgs->len.
		 */
		अगर ((!i) && block_data) अणु
			len = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2DR);
			अगर ((len == 0) || (len > I2C_SMBUS_BLOCK_MAX))
				वापस -EPROTO;
			dev_dbg(&i2c_imx->adapter.dev,
				"<%s> read length: 0x%X\n",
				__func__, len);
			msgs->len += len;
		पूर्ण
		अगर (i == (msgs->len - 1)) अणु
			अगर (is_lasपंचांगsg) अणु
				/*
				 * It must generate STOP beक्रमe पढ़ो I2DR to prevent
				 * controller from generating another घड़ी cycle
				 */
				dev_dbg(&i2c_imx->adapter.dev,
					"<%s> clear MSTA\n", __func__);
				temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
				अगर (!(temp & I2CR_MSTA))
					i2c_imx->stopped =  1;
				temp &= ~(I2CR_MSTA | I2CR_MTX);
				imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);
				अगर (!i2c_imx->stopped)
					i2c_imx_bus_busy(i2c_imx, 0, atomic);
			पूर्ण अन्यथा अणु
				/*
				 * For i2c master receiver repeat restart operation like:
				 * पढ़ो -> repeat MSTA -> पढ़ो/ग_लिखो
				 * The controller must set MTX beक्रमe पढ़ो the last byte in
				 * the first पढ़ो operation, otherwise the first पढ़ो cost
				 * one extra घड़ी cycle.
				 */
				temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
				temp |= I2CR_MTX;
				imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);
			पूर्ण
		पूर्ण अन्यथा अगर (i == (msgs->len - 2)) अणु
			dev_dbg(&i2c_imx->adapter.dev,
				"<%s> set TXAK\n", __func__);
			temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
			temp |= I2CR_TXAK;
			imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);
		पूर्ण
		अगर ((!i) && block_data)
			msgs->buf[0] = len;
		अन्यथा
			msgs->buf[i] = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2DR);
		dev_dbg(&i2c_imx->adapter.dev,
			"<%s> read byte: B%d=0x%X\n",
			__func__, i, msgs->buf[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_imx_xfer_common(काष्ठा i2c_adapter *adapter,
			       काष्ठा i2c_msg *msgs, पूर्णांक num, bool atomic)
अणु
	अचिन्हित पूर्णांक i, temp;
	पूर्णांक result;
	bool is_lasपंचांगsg = false;
	काष्ठा imx_i2c_काष्ठा *i2c_imx = i2c_get_adapdata(adapter);

	dev_dbg(&i2c_imx->adapter.dev, "<%s>\n", __func__);

	/* Start I2C transfer */
	result = i2c_imx_start(i2c_imx, atomic);
	अगर (result) अणु
		/*
		 * Bus recovery uses gpiod_get_value_cansleep() which is not
		 * allowed within atomic context.
		 */
		अगर (!atomic && i2c_imx->adapter.bus_recovery_info) अणु
			i2c_recover_bus(&i2c_imx->adapter);
			result = i2c_imx_start(i2c_imx, atomic);
		पूर्ण
	पूर्ण

	अगर (result)
		जाओ fail0;

	/* पढ़ो/ग_लिखो data */
	क्रम (i = 0; i < num; i++) अणु
		अगर (i == num - 1)
			is_lasपंचांगsg = true;

		अगर (i) अणु
			dev_dbg(&i2c_imx->adapter.dev,
				"<%s> repeated start\n", __func__);
			temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
			temp |= I2CR_RSTA;
			imx_i2c_ग_लिखो_reg(temp, i2c_imx, IMX_I2C_I2CR);
			result = i2c_imx_bus_busy(i2c_imx, 1, atomic);
			अगर (result)
				जाओ fail0;
		पूर्ण
		dev_dbg(&i2c_imx->adapter.dev,
			"<%s> transfer message: %d\n", __func__, i);
		/* ग_लिखो/पढ़ो data */
#अगर_घोषित CONFIG_I2C_DEBUG_BUS
		temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2CR);
		dev_dbg(&i2c_imx->adapter.dev,
			"<%s> CONTROL: IEN=%d, IIEN=%d, MSTA=%d, MTX=%d, TXAK=%d, RSTA=%d\n",
			__func__,
			(temp & I2CR_IEN ? 1 : 0), (temp & I2CR_IIEN ? 1 : 0),
			(temp & I2CR_MSTA ? 1 : 0), (temp & I2CR_MTX ? 1 : 0),
			(temp & I2CR_TXAK ? 1 : 0), (temp & I2CR_RSTA ? 1 : 0));
		temp = imx_i2c_पढ़ो_reg(i2c_imx, IMX_I2C_I2SR);
		dev_dbg(&i2c_imx->adapter.dev,
			"<%s> STATUS: ICF=%d, IAAS=%d, IBB=%d, IAL=%d, SRW=%d, IIF=%d, RXAK=%d\n",
			__func__,
			(temp & I2SR_ICF ? 1 : 0), (temp & I2SR_IAAS ? 1 : 0),
			(temp & I2SR_IBB ? 1 : 0), (temp & I2SR_IAL ? 1 : 0),
			(temp & I2SR_SRW ? 1 : 0), (temp & I2SR_IIF ? 1 : 0),
			(temp & I2SR_RXAK ? 1 : 0));
#पूर्ण_अगर
		अगर (msgs[i].flags & I2C_M_RD) अणु
			result = i2c_imx_पढ़ो(i2c_imx, &msgs[i], is_lasपंचांगsg, atomic);
		पूर्ण अन्यथा अणु
			अगर (!atomic &&
			    i2c_imx->dma && msgs[i].len >= DMA_THRESHOLD)
				result = i2c_imx_dma_ग_लिखो(i2c_imx, &msgs[i]);
			अन्यथा
				result = i2c_imx_ग_लिखो(i2c_imx, &msgs[i], atomic);
		पूर्ण
		अगर (result)
			जाओ fail0;
	पूर्ण

fail0:
	/* Stop I2C transfer */
	i2c_imx_stop(i2c_imx, atomic);

	dev_dbg(&i2c_imx->adapter.dev, "<%s> exit with: %s: %d\n", __func__,
		(result < 0) ? "error" : "success msg",
			(result < 0) ? result : num);
	/* After data is transferred, चयन to slave mode(as a receiver) */
	अगर (i2c_imx->slave)
		i2c_imx_slave_init(i2c_imx);

	वापस (result < 0) ? result : num;
पूर्ण

अटल पूर्णांक i2c_imx_xfer(काष्ठा i2c_adapter *adapter,
			काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा imx_i2c_काष्ठा *i2c_imx = i2c_get_adapdata(adapter);
	पूर्णांक result;

	result = pm_runसमय_resume_and_get(i2c_imx->adapter.dev.parent);
	अगर (result < 0)
		वापस result;

	result = i2c_imx_xfer_common(adapter, msgs, num, false);

	pm_runसमय_mark_last_busy(i2c_imx->adapter.dev.parent);
	pm_runसमय_put_स्वतःsuspend(i2c_imx->adapter.dev.parent);

	वापस result;
पूर्ण

अटल पूर्णांक i2c_imx_xfer_atomic(काष्ठा i2c_adapter *adapter,
			       काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा imx_i2c_काष्ठा *i2c_imx = i2c_get_adapdata(adapter);
	पूर्णांक result;

	result = clk_enable(i2c_imx->clk);
	अगर (result)
		वापस result;

	result = i2c_imx_xfer_common(adapter, msgs, num, true);

	clk_disable(i2c_imx->clk);

	वापस result;
पूर्ण

अटल व्योम i2c_imx_prepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा imx_i2c_काष्ठा *i2c_imx;

	i2c_imx = container_of(adap, काष्ठा imx_i2c_काष्ठा, adapter);

	pinctrl_select_state(i2c_imx->pinctrl, i2c_imx->pinctrl_pins_gpio);
पूर्ण

अटल व्योम i2c_imx_unprepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा imx_i2c_काष्ठा *i2c_imx;

	i2c_imx = container_of(adap, काष्ठा imx_i2c_काष्ठा, adapter);

	pinctrl_select_state(i2c_imx->pinctrl, i2c_imx->pinctrl_pins_शेष);
पूर्ण

/*
 * We चयन SCL and SDA to their GPIO function and करो some bitbanging
 * क्रम bus recovery. These alternative pinmux settings can be
 * described in the device tree by a separate pinctrl state "gpio". If
 * this is missing this is not a big problem, the only implication is
 * that we can't करो bus recovery.
 */
अटल पूर्णांक i2c_imx_init_recovery_info(काष्ठा imx_i2c_काष्ठा *i2c_imx,
		काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_bus_recovery_info *rinfo = &i2c_imx->rinfo;

	i2c_imx->pinctrl = devm_pinctrl_get(&pdev->dev);
	अगर (!i2c_imx->pinctrl || IS_ERR(i2c_imx->pinctrl)) अणु
		dev_info(&pdev->dev, "can't get pinctrl, bus recovery not supported\n");
		वापस PTR_ERR(i2c_imx->pinctrl);
	पूर्ण

	i2c_imx->pinctrl_pins_शेष = pinctrl_lookup_state(i2c_imx->pinctrl,
			PINCTRL_STATE_DEFAULT);
	i2c_imx->pinctrl_pins_gpio = pinctrl_lookup_state(i2c_imx->pinctrl,
			"gpio");
	rinfo->sda_gpiod = devm_gpiod_get(&pdev->dev, "sda", GPIOD_IN);
	rinfo->scl_gpiod = devm_gpiod_get(&pdev->dev, "scl", GPIOD_OUT_HIGH_OPEN_DRAIN);

	अगर (PTR_ERR(rinfo->sda_gpiod) == -EPROBE_DEFER ||
	    PTR_ERR(rinfo->scl_gpiod) == -EPROBE_DEFER) अणु
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अगर (IS_ERR(rinfo->sda_gpiod) ||
		   IS_ERR(rinfo->scl_gpiod) ||
		   IS_ERR(i2c_imx->pinctrl_pins_शेष) ||
		   IS_ERR(i2c_imx->pinctrl_pins_gpio)) अणु
		dev_dbg(&pdev->dev, "recovery information incomplete\n");
		वापस 0;
	पूर्ण

	dev_dbg(&pdev->dev, "using scl%s for recovery\n",
		rinfo->sda_gpiod ? ",sda" : "");

	rinfo->prepare_recovery = i2c_imx_prepare_recovery;
	rinfo->unprepare_recovery = i2c_imx_unprepare_recovery;
	rinfo->recover_bus = i2c_generic_scl_recovery;
	i2c_imx->adapter.bus_recovery_info = rinfo;

	वापस 0;
पूर्ण

अटल u32 i2c_imx_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL
		| I2C_FUNC_SMBUS_READ_BLOCK_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm i2c_imx_algo = अणु
	.master_xfer = i2c_imx_xfer,
	.master_xfer_atomic = i2c_imx_xfer_atomic,
	.functionality = i2c_imx_func,
	.reg_slave	= i2c_imx_reg_slave,
	.unreg_slave	= i2c_imx_unreg_slave,
पूर्ण;

अटल पूर्णांक i2c_imx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_i2c_काष्ठा *i2c_imx;
	काष्ठा resource *res;
	काष्ठा imxi2c_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	व्योम __iomem *base;
	पूर्णांक irq, ret;
	dma_addr_t phy_addr;
	स्थिर काष्ठा imx_i2c_hwdata *match;

	dev_dbg(&pdev->dev, "<%s>\n", __func__);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	phy_addr = (dma_addr_t)res->start;
	i2c_imx = devm_kzalloc(&pdev->dev, माप(*i2c_imx), GFP_KERNEL);
	अगर (!i2c_imx)
		वापस -ENOMEM;

	match = device_get_match_data(&pdev->dev);
	अगर (match)
		i2c_imx->hwdata = match;
	अन्यथा
		i2c_imx->hwdata = (काष्ठा imx_i2c_hwdata *)
				platक्रमm_get_device_id(pdev)->driver_data;

	/* Setup i2c_imx driver काष्ठाure */
	strlcpy(i2c_imx->adapter.name, pdev->name, माप(i2c_imx->adapter.name));
	i2c_imx->adapter.owner		= THIS_MODULE;
	i2c_imx->adapter.algo		= &i2c_imx_algo;
	i2c_imx->adapter.dev.parent	= &pdev->dev;
	i2c_imx->adapter.nr		= pdev->id;
	i2c_imx->adapter.dev.of_node	= pdev->dev.of_node;
	i2c_imx->base			= base;
	ACPI_COMPANION_SET(&i2c_imx->adapter.dev, ACPI_COMPANION(&pdev->dev));

	/* Get I2C घड़ी */
	i2c_imx->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(i2c_imx->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(i2c_imx->clk),
				     "can't get I2C clock\n");

	ret = clk_prepare_enable(i2c_imx->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't enable I2C clock, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	/* Init queue */
	init_रुकोqueue_head(&i2c_imx->queue);

	/* Set up adapter data */
	i2c_set_adapdata(&i2c_imx->adapter, i2c_imx);

	/* Set up platक्रमm driver data */
	platक्रमm_set_drvdata(pdev, i2c_imx);

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, I2C_PM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0)
		जाओ rpm_disable;

	/* Request IRQ */
	ret = request_thपढ़ोed_irq(irq, i2c_imx_isr, शून्य, IRQF_SHARED,
				   pdev->name, i2c_imx);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't claim irq %d\n", irq);
		जाओ rpm_disable;
	पूर्ण

	/* Set up घड़ी भागider */
	i2c_imx->bitrate = I2C_MAX_STANDARD_MODE_FREQ;
	ret = of_property_पढ़ो_u32(pdev->dev.of_node,
				   "clock-frequency", &i2c_imx->bitrate);
	अगर (ret < 0 && pdata && pdata->bitrate)
		i2c_imx->bitrate = pdata->bitrate;
	i2c_imx->clk_change_nb.notअगरier_call = i2c_imx_clk_notअगरier_call;
	clk_notअगरier_रेजिस्टर(i2c_imx->clk, &i2c_imx->clk_change_nb);
	i2c_imx_set_clk(i2c_imx, clk_get_rate(i2c_imx->clk));

	i2c_imx_reset_regs(i2c_imx);

	/* Init optional bus recovery function */
	ret = i2c_imx_init_recovery_info(i2c_imx, pdev);
	/* Give it another chance अगर pinctrl used is not पढ़ोy yet */
	अगर (ret == -EPROBE_DEFER)
		जाओ clk_notअगरier_unरेजिस्टर;

	/* Add I2C adapter */
	ret = i2c_add_numbered_adapter(&i2c_imx->adapter);
	अगर (ret < 0)
		जाओ clk_notअगरier_unरेजिस्टर;

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	dev_dbg(&i2c_imx->adapter.dev, "claimed irq %d\n", irq);
	dev_dbg(&i2c_imx->adapter.dev, "device resources: %pR\n", res);
	dev_dbg(&i2c_imx->adapter.dev, "adapter name: \"%s\"\n",
		i2c_imx->adapter.name);
	dev_info(&i2c_imx->adapter.dev, "IMX I2C adapter registered\n");

	/* Init DMA config अगर supported */
	i2c_imx_dma_request(i2c_imx, phy_addr);

	वापस 0;   /* Return OK */

clk_notअगरier_unरेजिस्टर:
	clk_notअगरier_unरेजिस्टर(i2c_imx->clk, &i2c_imx->clk_change_nb);
	मुक्त_irq(irq, i2c_imx);
rpm_disable:
	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	clk_disable_unprepare(i2c_imx->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक i2c_imx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_i2c_काष्ठा *i2c_imx = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq, ret;

	ret = pm_runसमय_resume_and_get(&pdev->dev);
	अगर (ret < 0)
		वापस ret;

	/* हटाओ adapter */
	dev_dbg(&i2c_imx->adapter.dev, "adapter removed\n");
	i2c_del_adapter(&i2c_imx->adapter);

	अगर (i2c_imx->dma)
		i2c_imx_dma_मुक्त(i2c_imx);

	/* setup chip रेजिस्टरs to शेषs */
	imx_i2c_ग_लिखो_reg(0, i2c_imx, IMX_I2C_IADR);
	imx_i2c_ग_लिखो_reg(0, i2c_imx, IMX_I2C_IFDR);
	imx_i2c_ग_लिखो_reg(0, i2c_imx, IMX_I2C_I2CR);
	imx_i2c_ग_लिखो_reg(0, i2c_imx, IMX_I2C_I2SR);

	clk_notअगरier_unरेजिस्टर(i2c_imx->clk, &i2c_imx->clk_change_nb);
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq >= 0)
		मुक्त_irq(irq, i2c_imx);
	clk_disable_unprepare(i2c_imx->clk);

	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused i2c_imx_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा imx_i2c_काष्ठा *i2c_imx = dev_get_drvdata(dev);

	clk_disable(i2c_imx->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused i2c_imx_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा imx_i2c_काष्ठा *i2c_imx = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_enable(i2c_imx->clk);
	अगर (ret)
		dev_err(dev, "can't enable I2C clock, ret=%d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops i2c_imx_pm_ops = अणु
	SET_RUNTIME_PM_OPS(i2c_imx_runसमय_suspend,
			   i2c_imx_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver i2c_imx_driver = अणु
	.probe = i2c_imx_probe,
	.हटाओ = i2c_imx_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
		.pm = &i2c_imx_pm_ops,
		.of_match_table = i2c_imx_dt_ids,
		.acpi_match_table = i2c_imx_acpi_ids,
	पूर्ण,
	.id_table = imx_i2c_devtype,
पूर्ण;

अटल पूर्णांक __init i2c_adap_imx_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&i2c_imx_driver);
पूर्ण
subsys_initcall(i2c_adap_imx_init);

अटल व्योम __निकास i2c_adap_imx_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&i2c_imx_driver);
पूर्ण
module_निकास(i2c_adap_imx_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Darius Augulis");
MODULE_DESCRIPTION("I2C adapter driver for IMX I2C bus");
MODULE_ALIAS("platform:" DRIVER_NAME);
