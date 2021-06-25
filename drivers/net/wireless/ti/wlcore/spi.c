<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/swab.h>
#समावेश <linux/crc7.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/wl12xx.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "wlcore.h"
#समावेश "wl12xx_80211.h"
#समावेश "io.h"

#घोषणा WSPI_CMD_READ                 0x40000000
#घोषणा WSPI_CMD_WRITE                0x00000000
#घोषणा WSPI_CMD_FIXED                0x20000000
#घोषणा WSPI_CMD_BYTE_LENGTH          0x1FFE0000
#घोषणा WSPI_CMD_BYTE_LENGTH_OFFSET   17
#घोषणा WSPI_CMD_BYTE_ADDR            0x0001FFFF

#घोषणा WSPI_INIT_CMD_CRC_LEN       5

#घोषणा WSPI_INIT_CMD_START         0x00
#घोषणा WSPI_INIT_CMD_TX            0x40
/* the extra bypass bit is sampled by the TNET as '1' */
#घोषणा WSPI_INIT_CMD_BYPASS_BIT    0x80
#घोषणा WSPI_INIT_CMD_FIXEDBUSY_LEN 0x07
#घोषणा WSPI_INIT_CMD_EN_FIXEDBUSY  0x80
#घोषणा WSPI_INIT_CMD_DIS_FIXEDBUSY 0x00
#घोषणा WSPI_INIT_CMD_IOD           0x40
#घोषणा WSPI_INIT_CMD_IP            0x20
#घोषणा WSPI_INIT_CMD_CS            0x10
#घोषणा WSPI_INIT_CMD_WS            0x08
#घोषणा WSPI_INIT_CMD_WSPI          0x01
#घोषणा WSPI_INIT_CMD_END           0x01

#घोषणा WSPI_INIT_CMD_LEN           8

#घोषणा HW_ACCESS_WSPI_FIXED_BUSY_LEN \
		((WL1271_BUSY_WORD_LEN - 4) / माप(u32))
#घोषणा HW_ACCESS_WSPI_INIT_CMD_MASK  0

/* HW limitation: maximum possible chunk size is 4095 bytes */
#घोषणा WSPI_MAX_CHUNK_SIZE    4092

/*
 * wl18xx driver aggregation buffer size is (13 * 4K) compared to
 * (4 * 4K) क्रम wl12xx, so use the larger buffer needed क्रम wl18xx
 */
#घोषणा SPI_AGGR_BUFFER_SIZE (13 * SZ_4K)

/* Maximum number of SPI ग_लिखो chunks */
#घोषणा WSPI_MAX_NUM_OF_CHUNKS \
	((SPI_AGGR_BUFFER_SIZE / WSPI_MAX_CHUNK_SIZE) + 1)

अटल स्थिर काष्ठा wilink_family_data wl127x_data = अणु
	.name = "wl127x",
	.nvs_name = "ti-connectivity/wl127x-nvs.bin",
पूर्ण;

अटल स्थिर काष्ठा wilink_family_data wl128x_data = अणु
	.name = "wl128x",
	.nvs_name = "ti-connectivity/wl128x-nvs.bin",
पूर्ण;

अटल स्थिर काष्ठा wilink_family_data wl18xx_data = अणु
	.name = "wl18xx",
	.cfg_name = "ti-connectivity/wl18xx-conf.bin",
	.nvs_name = "ti-connectivity/wl1271-nvs.bin",
पूर्ण;

काष्ठा wl12xx_spi_glue अणु
	काष्ठा device *dev;
	काष्ठा platक्रमm_device *core;
	काष्ठा regulator *reg; /* Power regulator */
पूर्ण;

अटल व्योम wl12xx_spi_reset(काष्ठा device *child)
अणु
	काष्ठा wl12xx_spi_glue *glue = dev_get_drvdata(child->parent);
	u8 *cmd;
	काष्ठा spi_transfer t;
	काष्ठा spi_message m;

	cmd = kzalloc(WSPI_INIT_CMD_LEN, GFP_KERNEL);
	अगर (!cmd) अणु
		dev_err(child->parent,
			"could not allocate cmd for spi reset\n");
		वापस;
	पूर्ण

	स_रखो(&t, 0, माप(t));
	spi_message_init(&m);

	स_रखो(cmd, 0xff, WSPI_INIT_CMD_LEN);

	t.tx_buf = cmd;
	t.len = WSPI_INIT_CMD_LEN;
	spi_message_add_tail(&t, &m);

	spi_sync(to_spi_device(glue->dev), &m);

	kमुक्त(cmd);
पूर्ण

अटल व्योम wl12xx_spi_init(काष्ठा device *child)
अणु
	काष्ठा wl12xx_spi_glue *glue = dev_get_drvdata(child->parent);
	काष्ठा spi_transfer t;
	काष्ठा spi_message m;
	काष्ठा spi_device *spi = to_spi_device(glue->dev);
	u8 *cmd = kzalloc(WSPI_INIT_CMD_LEN, GFP_KERNEL);

	अगर (!cmd) अणु
		dev_err(child->parent,
			"could not allocate cmd for spi init\n");
		वापस;
	पूर्ण

	स_रखो(&t, 0, माप(t));
	spi_message_init(&m);

	/*
	 * Set WSPI_INIT_COMMAND
	 * the data is being send from the MSB to LSB
	 */
	cmd[0] = 0xff;
	cmd[1] = 0xff;
	cmd[2] = WSPI_INIT_CMD_START | WSPI_INIT_CMD_TX;
	cmd[3] = 0;
	cmd[4] = 0;
	cmd[5] = HW_ACCESS_WSPI_INIT_CMD_MASK << 3;
	cmd[5] |= HW_ACCESS_WSPI_FIXED_BUSY_LEN & WSPI_INIT_CMD_FIXEDBUSY_LEN;

	cmd[6] = WSPI_INIT_CMD_IOD | WSPI_INIT_CMD_IP | WSPI_INIT_CMD_CS
		| WSPI_INIT_CMD_WSPI | WSPI_INIT_CMD_WS;

	अगर (HW_ACCESS_WSPI_FIXED_BUSY_LEN == 0)
		cmd[6] |= WSPI_INIT_CMD_DIS_FIXEDBUSY;
	अन्यथा
		cmd[6] |= WSPI_INIT_CMD_EN_FIXEDBUSY;

	cmd[7] = crc7_be(0, cmd+2, WSPI_INIT_CMD_CRC_LEN) | WSPI_INIT_CMD_END;

	/*
	 * The above is the logical order; it must actually be stored
	 * in the buffer byte-swapped.
	 */
	__swab32s((u32 *)cmd);
	__swab32s((u32 *)cmd+1);

	t.tx_buf = cmd;
	t.len = WSPI_INIT_CMD_LEN;
	spi_message_add_tail(&t, &m);

	spi_sync(to_spi_device(glue->dev), &m);

	/* Send extra घड़ीs with inverted CS (high). this is required
	 * by the wilink family in order to successfully enter WSPI mode.
	 */
	spi->mode ^= SPI_CS_HIGH;
	स_रखो(&m, 0, माप(m));
	spi_message_init(&m);

	cmd[0] = 0xff;
	cmd[1] = 0xff;
	cmd[2] = 0xff;
	cmd[3] = 0xff;
	__swab32s((u32 *)cmd);

	t.tx_buf = cmd;
	t.len = 4;
	spi_message_add_tail(&t, &m);

	spi_sync(to_spi_device(glue->dev), &m);

	/* Restore chip select configuration to normal */
	spi->mode ^= SPI_CS_HIGH;
	kमुक्त(cmd);
पूर्ण

#घोषणा WL1271_BUSY_WORD_TIMEOUT 1000

अटल पूर्णांक wl12xx_spi_पढ़ो_busy(काष्ठा device *child)
अणु
	काष्ठा wl12xx_spi_glue *glue = dev_get_drvdata(child->parent);
	काष्ठा wl1271 *wl = dev_get_drvdata(child);
	काष्ठा spi_transfer t[1];
	काष्ठा spi_message m;
	u32 *busy_buf;
	पूर्णांक num_busy_bytes = 0;

	/*
	 * Read further busy words from SPI until a non-busy word is
	 * encountered, then पढ़ो the data itself पूर्णांकo the buffer.
	 */

	num_busy_bytes = WL1271_BUSY_WORD_TIMEOUT;
	busy_buf = wl->buffer_busyword;
	जबतक (num_busy_bytes) अणु
		num_busy_bytes--;
		spi_message_init(&m);
		स_रखो(t, 0, माप(t));
		t[0].rx_buf = busy_buf;
		t[0].len = माप(u32);
		t[0].cs_change = true;
		spi_message_add_tail(&t[0], &m);
		spi_sync(to_spi_device(glue->dev), &m);

		अगर (*busy_buf & 0x1)
			वापस 0;
	पूर्ण

	/* The SPI bus is unresponsive, the पढ़ो failed. */
	dev_err(child->parent, "SPI read busy-word timeout!\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक __must_check wl12xx_spi_raw_पढ़ो(काष्ठा device *child, पूर्णांक addr,
					    व्योम *buf, माप_प्रकार len, bool fixed)
अणु
	काष्ठा wl12xx_spi_glue *glue = dev_get_drvdata(child->parent);
	काष्ठा wl1271 *wl = dev_get_drvdata(child);
	काष्ठा spi_transfer t[2];
	काष्ठा spi_message m;
	u32 *busy_buf;
	u32 *cmd;
	u32 chunk_len;

	जबतक (len > 0) अणु
		chunk_len = min_t(माप_प्रकार, WSPI_MAX_CHUNK_SIZE, len);

		cmd = &wl->buffer_cmd;
		busy_buf = wl->buffer_busyword;

		*cmd = 0;
		*cmd |= WSPI_CMD_READ;
		*cmd |= (chunk_len << WSPI_CMD_BYTE_LENGTH_OFFSET) &
			WSPI_CMD_BYTE_LENGTH;
		*cmd |= addr & WSPI_CMD_BYTE_ADDR;

		अगर (fixed)
			*cmd |= WSPI_CMD_FIXED;

		spi_message_init(&m);
		स_रखो(t, 0, माप(t));

		t[0].tx_buf = cmd;
		t[0].len = 4;
		t[0].cs_change = true;
		spi_message_add_tail(&t[0], &m);

		/* Busy and non busy words पढ़ो */
		t[1].rx_buf = busy_buf;
		t[1].len = WL1271_BUSY_WORD_LEN;
		t[1].cs_change = true;
		spi_message_add_tail(&t[1], &m);

		spi_sync(to_spi_device(glue->dev), &m);

		अगर (!(busy_buf[WL1271_BUSY_WORD_CNT - 1] & 0x1) &&
		    wl12xx_spi_पढ़ो_busy(child)) अणु
			स_रखो(buf, 0, chunk_len);
			वापस 0;
		पूर्ण

		spi_message_init(&m);
		स_रखो(t, 0, माप(t));

		t[0].rx_buf = buf;
		t[0].len = chunk_len;
		t[0].cs_change = true;
		spi_message_add_tail(&t[0], &m);

		spi_sync(to_spi_device(glue->dev), &m);

		अगर (!fixed)
			addr += chunk_len;
		buf += chunk_len;
		len -= chunk_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __wl12xx_spi_raw_ग_लिखो(काष्ठा device *child, पूर्णांक addr,
				  व्योम *buf, माप_प्रकार len, bool fixed)
अणु
	काष्ठा wl12xx_spi_glue *glue = dev_get_drvdata(child->parent);
	काष्ठा spi_transfer *t;
	काष्ठा spi_message m;
	u32 commands[WSPI_MAX_NUM_OF_CHUNKS]; /* 1 command per chunk */
	u32 *cmd;
	u32 chunk_len;
	पूर्णांक i;

	/* SPI ग_लिखो buffers - 2 क्रम each chunk */
	t = kzalloc(माप(*t) * 2 * WSPI_MAX_NUM_OF_CHUNKS, GFP_KERNEL);
	अगर (!t)
		वापस -ENOMEM;

	WARN_ON(len > SPI_AGGR_BUFFER_SIZE);

	spi_message_init(&m);

	cmd = &commands[0];
	i = 0;
	जबतक (len > 0) अणु
		chunk_len = min_t(माप_प्रकार, WSPI_MAX_CHUNK_SIZE, len);

		*cmd = 0;
		*cmd |= WSPI_CMD_WRITE;
		*cmd |= (chunk_len << WSPI_CMD_BYTE_LENGTH_OFFSET) &
			WSPI_CMD_BYTE_LENGTH;
		*cmd |= addr & WSPI_CMD_BYTE_ADDR;

		अगर (fixed)
			*cmd |= WSPI_CMD_FIXED;

		t[i].tx_buf = cmd;
		t[i].len = माप(*cmd);
		spi_message_add_tail(&t[i++], &m);

		t[i].tx_buf = buf;
		t[i].len = chunk_len;
		spi_message_add_tail(&t[i++], &m);

		अगर (!fixed)
			addr += chunk_len;
		buf += chunk_len;
		len -= chunk_len;
		cmd++;
	पूर्ण

	spi_sync(to_spi_device(glue->dev), &m);

	kमुक्त(t);
	वापस 0;
पूर्ण

अटल पूर्णांक __must_check wl12xx_spi_raw_ग_लिखो(काष्ठा device *child, पूर्णांक addr,
					     व्योम *buf, माप_प्रकार len, bool fixed)
अणु
	/* The ELP wakeup ग_लिखो may fail the first समय due to पूर्णांकernal
	 * hardware latency. It is safer to send the wakeup command twice to
	 * aव्योम unexpected failures.
	 */
	अगर (addr == HW_ACCESS_ELP_CTRL_REG)
		__wl12xx_spi_raw_ग_लिखो(child, addr, buf, len, fixed);

	वापस __wl12xx_spi_raw_ग_लिखो(child, addr, buf, len, fixed);
पूर्ण

/**
 * wl12xx_spi_set_घातer - घातer on/off the wl12xx unit
 * @child: wl12xx device handle.
 * @enable: true/false to घातer on/off the unit.
 *
 * use the WiFi enable regulator to enable/disable the WiFi unit.
 */
अटल पूर्णांक wl12xx_spi_set_घातer(काष्ठा device *child, bool enable)
अणु
	पूर्णांक ret = 0;
	काष्ठा wl12xx_spi_glue *glue = dev_get_drvdata(child->parent);

	WARN_ON(!glue->reg);

	/* Update regulator state */
	अगर (enable) अणु
		ret = regulator_enable(glue->reg);
		अगर (ret)
			dev_err(child, "Power enable failure\n");
	पूर्ण अन्यथा अणु
		ret =  regulator_disable(glue->reg);
		अगर (ret)
			dev_err(child, "Power disable failure\n");
	पूर्ण

	वापस ret;
पूर्ण

/*
 * wl12xx_spi_set_block_size
 *
 * This function is not needed क्रम spi mode, but need to be present.
 * Without it defined the wlcore fallback to use the wrong packet
 * allignment on tx.
 */
अटल व्योम wl12xx_spi_set_block_size(काष्ठा device *child,
				      अचिन्हित पूर्णांक blksz)
अणु
पूर्ण

अटल काष्ठा wl1271_अगर_operations spi_ops = अणु
	.पढ़ो		= wl12xx_spi_raw_पढ़ो,
	.ग_लिखो		= wl12xx_spi_raw_ग_लिखो,
	.reset		= wl12xx_spi_reset,
	.init		= wl12xx_spi_init,
	.घातer		= wl12xx_spi_set_घातer,
	.set_block_size = wl12xx_spi_set_block_size,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wlcore_spi_of_match_table[] = अणु
	अणु .compatible = "ti,wl1271", .data = &wl127x_dataपूर्ण,
	अणु .compatible = "ti,wl1273", .data = &wl127x_dataपूर्ण,
	अणु .compatible = "ti,wl1281", .data = &wl128x_dataपूर्ण,
	अणु .compatible = "ti,wl1283", .data = &wl128x_dataपूर्ण,
	अणु .compatible = "ti,wl1285", .data = &wl128x_dataपूर्ण,
	अणु .compatible = "ti,wl1801", .data = &wl18xx_dataपूर्ण,
	अणु .compatible = "ti,wl1805", .data = &wl18xx_dataपूर्ण,
	अणु .compatible = "ti,wl1807", .data = &wl18xx_dataपूर्ण,
	अणु .compatible = "ti,wl1831", .data = &wl18xx_dataपूर्ण,
	अणु .compatible = "ti,wl1835", .data = &wl18xx_dataपूर्ण,
	अणु .compatible = "ti,wl1837", .data = &wl18xx_dataपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wlcore_spi_of_match_table);

/**
 * wlcore_probe_of - DT node parsing.
 * @spi: SPI slave device parameters.
 * @glue: wl12xx SPI bus to slave device glue parameters.
 * @pdev_data: wlcore device parameters
 */
अटल पूर्णांक wlcore_probe_of(काष्ठा spi_device *spi, काष्ठा wl12xx_spi_glue *glue,
			   काष्ठा wlcore_platdev_data *pdev_data)
अणु
	काष्ठा device_node *dt_node = spi->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id;

	of_id = of_match_node(wlcore_spi_of_match_table, dt_node);
	अगर (!of_id)
		वापस -ENODEV;

	pdev_data->family = of_id->data;
	dev_info(&spi->dev, "selected chip family is %s\n",
		 pdev_data->family->name);

	अगर (of_find_property(dt_node, "clock-xtal", शून्य))
		pdev_data->ref_घड़ी_xtal = true;

	/* optional घड़ी frequency params */
	of_property_पढ़ो_u32(dt_node, "ref-clock-frequency",
			     &pdev_data->ref_घड़ी_freq);
	of_property_पढ़ो_u32(dt_node, "tcxo-clock-frequency",
			     &pdev_data->tcxo_घड़ी_freq);

	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wl12xx_spi_glue *glue;
	काष्ठा wlcore_platdev_data *pdev_data;
	काष्ठा resource res[1];
	पूर्णांक ret;

	pdev_data = devm_kzalloc(&spi->dev, माप(*pdev_data), GFP_KERNEL);
	अगर (!pdev_data)
		वापस -ENOMEM;

	pdev_data->अगर_ops = &spi_ops;

	glue = devm_kzalloc(&spi->dev, माप(*glue), GFP_KERNEL);
	अगर (!glue) अणु
		dev_err(&spi->dev, "can't allocate glue\n");
		वापस -ENOMEM;
	पूर्ण

	glue->dev = &spi->dev;

	spi_set_drvdata(spi, glue);

	/* This is the only SPI value that we need to set here, the rest
	 * comes from the board-peripherals file */
	spi->bits_per_word = 32;

	glue->reg = devm_regulator_get(&spi->dev, "vwlan");
	अगर (PTR_ERR(glue->reg) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (IS_ERR(glue->reg)) अणु
		dev_err(glue->dev, "can't get regulator\n");
		वापस PTR_ERR(glue->reg);
	पूर्ण

	ret = wlcore_probe_of(spi, glue, pdev_data);
	अगर (ret) अणु
		dev_err(glue->dev,
			"can't get device tree parameters (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(glue->dev, "spi_setup failed\n");
		वापस ret;
	पूर्ण

	glue->core = platक्रमm_device_alloc(pdev_data->family->name,
					   PLATFORM_DEVID_AUTO);
	अगर (!glue->core) अणु
		dev_err(glue->dev, "can't allocate platform_device\n");
		वापस -ENOMEM;
	पूर्ण

	glue->core->dev.parent = &spi->dev;

	स_रखो(res, 0x00, माप(res));

	res[0].start = spi->irq;
	res[0].flags = IORESOURCE_IRQ | irq_get_trigger_type(spi->irq);
	res[0].name = "irq";

	ret = platक्रमm_device_add_resources(glue->core, res, ARRAY_SIZE(res));
	अगर (ret) अणु
		dev_err(glue->dev, "can't add resources\n");
		जाओ out_dev_put;
	पूर्ण

	ret = platक्रमm_device_add_data(glue->core, pdev_data,
				       माप(*pdev_data));
	अगर (ret) अणु
		dev_err(glue->dev, "can't add platform data\n");
		जाओ out_dev_put;
	पूर्ण

	ret = platक्रमm_device_add(glue->core);
	अगर (ret) अणु
		dev_err(glue->dev, "can't register platform device\n");
		जाओ out_dev_put;
	पूर्ण

	वापस 0;

out_dev_put:
	platक्रमm_device_put(glue->core);
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा wl12xx_spi_glue *glue = spi_get_drvdata(spi);

	platक्रमm_device_unरेजिस्टर(glue->core);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver wl1271_spi_driver = अणु
	.driver = अणु
		.name		= "wl1271_spi",
		.of_match_table = of_match_ptr(wlcore_spi_of_match_table),
	पूर्ण,

	.probe		= wl1271_probe,
	.हटाओ		= wl1271_हटाओ,
पूर्ण;

module_spi_driver(wl1271_spi_driver);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Luciano Coelho <coelho@ti.com>");
MODULE_AUTHOR("Juuso Oikarinen <juuso.oikarinen@nokia.com>");
MODULE_ALIAS("spi:wl1271");
