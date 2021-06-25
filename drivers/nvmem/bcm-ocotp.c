<शैली गुरु>
/*
 * Copyright (C) 2016 Broadcom
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * # of tries क्रम OTP Status. The समय to execute a command varies. The slowest
 * commands are ग_लिखोs which also vary based on the # of bits turned on. Writing
 * 0xffffffff takes ~3800 us.
 */
#घोषणा OTPC_RETRIES                 5000

/* Sequence to enable OTP program */
#घोषणा OTPC_PROG_EN_SEQ             अणु 0xf, 0x4, 0x8, 0xd पूर्ण

/* OTPC Commands */
#घोषणा OTPC_CMD_READ                0x0
#घोषणा OTPC_CMD_OTP_PROG_ENABLE     0x2
#घोषणा OTPC_CMD_OTP_PROG_DISABLE    0x3
#घोषणा OTPC_CMD_PROGRAM             0x8

/* OTPC Status Bits */
#घोषणा OTPC_STAT_CMD_DONE           BIT(1)
#घोषणा OTPC_STAT_PROG_OK            BIT(2)

/* OTPC रेजिस्टर definition */
#घोषणा OTPC_MODE_REG_OFFSET         0x0
#घोषणा OTPC_MODE_REG_OTPC_MODE      0
#घोषणा OTPC_COMMAND_OFFSET          0x4
#घोषणा OTPC_COMMAND_COMMAND_WIDTH   6
#घोषणा OTPC_CMD_START_OFFSET        0x8
#घोषणा OTPC_CMD_START_START         0
#घोषणा OTPC_CPU_STATUS_OFFSET       0xc
#घोषणा OTPC_CPUADDR_REG_OFFSET      0x28
#घोषणा OTPC_CPUADDR_REG_OTPC_CPU_ADDRESS_WIDTH 16
#घोषणा OTPC_CPU_WRITE_REG_OFFSET    0x2c

#घोषणा OTPC_CMD_MASK  (BIT(OTPC_COMMAND_COMMAND_WIDTH) - 1)
#घोषणा OTPC_ADDR_MASK (BIT(OTPC_CPUADDR_REG_OTPC_CPU_ADDRESS_WIDTH) - 1)


काष्ठा otpc_map अणु
	/* in words. */
	u32 otpc_row_size;
	/* 128 bit row / 4 words support. */
	u16 data_r_offset[4];
	/* 128 bit row / 4 words support. */
	u16 data_w_offset[4];
पूर्ण;

अटल काष्ठा otpc_map otp_map = अणु
	.otpc_row_size = 1,
	.data_r_offset = अणु0x10पूर्ण,
	.data_w_offset = अणु0x2cपूर्ण,
पूर्ण;

अटल काष्ठा otpc_map otp_map_v2 = अणु
	.otpc_row_size = 2,
	.data_r_offset = अणु0x10, 0x5cपूर्ण,
	.data_w_offset = अणु0x2c, 0x64पूर्ण,
पूर्ण;

काष्ठा otpc_priv अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	स्थिर काष्ठा otpc_map *map;
	काष्ठा nvmem_config *config;
पूर्ण;

अटल अंतरभूत व्योम set_command(व्योम __iomem *base, u32 command)
अणु
	ग_लिखोl(command & OTPC_CMD_MASK, base + OTPC_COMMAND_OFFSET);
पूर्ण

अटल अंतरभूत व्योम set_cpu_address(व्योम __iomem *base, u32 addr)
अणु
	ग_लिखोl(addr & OTPC_ADDR_MASK, base + OTPC_CPUADDR_REG_OFFSET);
पूर्ण

अटल अंतरभूत व्योम set_start_bit(व्योम __iomem *base)
अणु
	ग_लिखोl(1 << OTPC_CMD_START_START, base + OTPC_CMD_START_OFFSET);
पूर्ण

अटल अंतरभूत व्योम reset_start_bit(व्योम __iomem *base)
अणु
	ग_लिखोl(0, base + OTPC_CMD_START_OFFSET);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_cpu_data(व्योम __iomem *base, u32 value)
अणु
	ग_लिखोl(value, base + OTPC_CPU_WRITE_REG_OFFSET);
पूर्ण

अटल पूर्णांक poll_cpu_status(व्योम __iomem *base, u32 value)
अणु
	u32 status;
	u32 retries;

	क्रम (retries = 0; retries < OTPC_RETRIES; retries++) अणु
		status = पढ़ोl(base + OTPC_CPU_STATUS_OFFSET);
		अगर (status & value)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (retries == OTPC_RETRIES)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक enable_ocotp_program(व्योम __iomem *base)
अणु
	अटल स्थिर u32 vals[] = OTPC_PROG_EN_SEQ;
	पूर्णांक i;
	पूर्णांक ret;

	/* Write the magic sequence to enable programming */
	set_command(base, OTPC_CMD_OTP_PROG_ENABLE);
	क्रम (i = 0; i < ARRAY_SIZE(vals); i++) अणु
		ग_लिखो_cpu_data(base, vals[i]);
		set_start_bit(base);
		ret = poll_cpu_status(base, OTPC_STAT_CMD_DONE);
		reset_start_bit(base);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस poll_cpu_status(base, OTPC_STAT_PROG_OK);
पूर्ण

अटल पूर्णांक disable_ocotp_program(व्योम __iomem *base)
अणु
	पूर्णांक ret;

	set_command(base, OTPC_CMD_OTP_PROG_DISABLE);
	set_start_bit(base);
	ret = poll_cpu_status(base, OTPC_STAT_PROG_OK);
	reset_start_bit(base);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_otpc_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset, व्योम *val,
	माप_प्रकार bytes)
अणु
	काष्ठा otpc_priv *priv = context;
	u32 *buf = val;
	u32 bytes_पढ़ो;
	u32 address = offset / priv->config->word_size;
	पूर्णांक i, ret;

	क्रम (bytes_पढ़ो = 0; bytes_पढ़ो < bytes;) अणु
		set_command(priv->base, OTPC_CMD_READ);
		set_cpu_address(priv->base, address++);
		set_start_bit(priv->base);
		ret = poll_cpu_status(priv->base, OTPC_STAT_CMD_DONE);
		अगर (ret) अणु
			dev_err(priv->dev, "otp read error: 0x%x", ret);
			वापस -EIO;
		पूर्ण

		क्रम (i = 0; i < priv->map->otpc_row_size; i++) अणु
			*buf++ = पढ़ोl(priv->base +
					priv->map->data_r_offset[i]);
			bytes_पढ़ो += माप(*buf);
		पूर्ण

		reset_start_bit(priv->base);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_otpc_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक offset, व्योम *val,
	माप_प्रकार bytes)
अणु
	काष्ठा otpc_priv *priv = context;
	u32 *buf = val;
	u32 bytes_written;
	u32 address = offset / priv->config->word_size;
	पूर्णांक i, ret;

	अगर (offset % priv->config->word_size)
		वापस -EINVAL;

	ret = enable_ocotp_program(priv->base);
	अगर (ret)
		वापस -EIO;

	क्रम (bytes_written = 0; bytes_written < bytes;) अणु
		set_command(priv->base, OTPC_CMD_PROGRAM);
		set_cpu_address(priv->base, address++);
		क्रम (i = 0; i < priv->map->otpc_row_size; i++) अणु
			ग_लिखोl(*buf, priv->base + priv->map->data_w_offset[i]);
			buf++;
			bytes_written += माप(*buf);
		पूर्ण
		set_start_bit(priv->base);
		ret = poll_cpu_status(priv->base, OTPC_STAT_CMD_DONE);
		reset_start_bit(priv->base);
		अगर (ret) अणु
			dev_err(priv->dev, "otp write error: 0x%x", ret);
			वापस -EIO;
		पूर्ण
	पूर्ण

	disable_ocotp_program(priv->base);

	वापस 0;
पूर्ण

अटल काष्ठा nvmem_config bcm_otpc_nvmem_config = अणु
	.name = "bcm-ocotp",
	.पढ़ो_only = false,
	.word_size = 4,
	.stride = 4,
	.reg_पढ़ो = bcm_otpc_पढ़ो,
	.reg_ग_लिखो = bcm_otpc_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm_otpc_dt_ids[] = अणु
	अणु .compatible = "brcm,ocotp", .data = &otp_map पूर्ण,
	अणु .compatible = "brcm,ocotp-v2", .data = &otp_map_v2 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_otpc_dt_ids);

अटल स्थिर काष्ठा acpi_device_id bcm_otpc_acpi_ids[] = अणु
	अणु .id = "BRCM0700", .driver_data = (kernel_uदीर्घ_t)&otp_map पूर्ण,
	अणु .id = "BRCM0701", .driver_data = (kernel_uदीर्घ_t)&otp_map_v2 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bcm_otpc_acpi_ids);

अटल पूर्णांक bcm_otpc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा otpc_priv *priv;
	काष्ठा nvmem_device *nvmem;
	पूर्णांक err;
	u32 num_words;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->map = device_get_match_data(dev);
	अगर (!priv->map)
		वापस -ENODEV;

	/* Get OTP base address रेजिस्टर. */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->base)) अणु
		dev_err(dev, "unable to map I/O memory\n");
		वापस PTR_ERR(priv->base);
	पूर्ण

	/* Enable CPU access to OTPC. */
	ग_लिखोl(पढ़ोl(priv->base + OTPC_MODE_REG_OFFSET) |
		BIT(OTPC_MODE_REG_OTPC_MODE),
		priv->base + OTPC_MODE_REG_OFFSET);
	reset_start_bit(priv->base);

	/* Read size of memory in words. */
	err = device_property_पढ़ो_u32(dev, "brcm,ocotp-size", &num_words);
	अगर (err) अणु
		dev_err(dev, "size parameter not specified\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (num_words == 0) अणु
		dev_err(dev, "size must be > 0\n");
		वापस -EINVAL;
	पूर्ण

	bcm_otpc_nvmem_config.size = 4 * num_words;
	bcm_otpc_nvmem_config.dev = dev;
	bcm_otpc_nvmem_config.priv = priv;

	अगर (priv->map == &otp_map_v2) अणु
		bcm_otpc_nvmem_config.word_size = 8;
		bcm_otpc_nvmem_config.stride = 8;
	पूर्ण

	priv->config = &bcm_otpc_nvmem_config;

	nvmem = devm_nvmem_रेजिस्टर(dev, &bcm_otpc_nvmem_config);
	अगर (IS_ERR(nvmem)) अणु
		dev_err(dev, "error registering nvmem config\n");
		वापस PTR_ERR(nvmem);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bcm_otpc_driver = अणु
	.probe	= bcm_otpc_probe,
	.driver = अणु
		.name	= "brcm-otpc",
		.of_match_table = bcm_otpc_dt_ids,
		.acpi_match_table = ACPI_PTR(bcm_otpc_acpi_ids),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcm_otpc_driver);

MODULE_DESCRIPTION("Broadcom OTPC driver");
MODULE_LICENSE("GPL v2");
