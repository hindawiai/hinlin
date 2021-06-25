<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/crc7.h>
#समावेश <linux/crc-itu-t.h>

#समावेश "netdev.h"
#समावेश "cfg80211.h"

अटल bool enable_crc7;	/* protect SPI commands with CRC7 */
module_param(enable_crc7, bool, 0644);
MODULE_PARM_DESC(enable_crc7,
		 "Enable CRC7 checksum to protect command transfers\n"
		 "\t\t\tagainst corruption during the SPI transfer.\n"
		 "\t\t\tCommand transfers are short and the CPU-cycle cost\n"
		 "\t\t\tof enabling this is small.");

अटल bool enable_crc16;	/* protect SPI data with CRC16 */
module_param(enable_crc16, bool, 0644);
MODULE_PARM_DESC(enable_crc16,
		 "Enable CRC16 checksum to protect data transfers\n"
		 "\t\t\tagainst corruption during the SPI transfer.\n"
		 "\t\t\tData transfers can be large and the CPU-cycle cost\n"
		 "\t\t\tof enabling this may be substantial.");

/*
 * For CMD_SINGLE_READ and CMD_INTERNAL_READ, WILC may insert one or
 * more zero bytes between the command response and the DATA Start tag
 * (0xf3).  This behavior appears to be unकरोcumented in "ATWILC1000
 * USER GUIDE" (https://tinyurl.com/4hhshdts) but we have observed 1-4
 * zero bytes when the SPI bus operates at 48MHz and none when it
 * operates at 1MHz.
 */
#घोषणा WILC_SPI_RSP_HDR_EXTRA_DATA	8

काष्ठा wilc_spi अणु
	bool probing_crc;	/* true अगर we're probing chip's CRC config */
	bool crc7_enabled;	/* true अगर crc7 is currently enabled */
	bool crc16_enabled;	/* true अगर crc16 is currently enabled */
पूर्ण;

अटल स्थिर काष्ठा wilc_hअगर_func wilc_hअगर_spi;

/********************************************
 *
 *      Spi protocol Function
 *
 ********************************************/

#घोषणा CMD_DMA_WRITE				0xc1
#घोषणा CMD_DMA_READ				0xc2
#घोषणा CMD_INTERNAL_WRITE			0xc3
#घोषणा CMD_INTERNAL_READ			0xc4
#घोषणा CMD_TERMINATE				0xc5
#घोषणा CMD_REPEAT				0xc6
#घोषणा CMD_DMA_EXT_WRITE			0xc7
#घोषणा CMD_DMA_EXT_READ			0xc8
#घोषणा CMD_SINGLE_WRITE			0xc9
#घोषणा CMD_SINGLE_READ				0xca
#घोषणा CMD_RESET				0xcf

#घोषणा SPI_ENABLE_VMM_RETRY_LIMIT		2

/* SPI response fields (section 11.1.2 in ATWILC1000 User Guide): */
#घोषणा RSP_START_FIELD				GENMASK(7, 4)
#घोषणा RSP_TYPE_FIELD				GENMASK(3, 0)

/* SPI response values क्रम the response fields: */
#घोषणा RSP_START_TAG				0xc
#घोषणा RSP_TYPE_FIRST_PACKET			0x1
#घोषणा RSP_TYPE_INNER_PACKET			0x2
#घोषणा RSP_TYPE_LAST_PACKET			0x3
#घोषणा RSP_STATE_NO_ERROR			0x00

#घोषणा PROTOCOL_REG_PKT_SZ_MASK		GENMASK(6, 4)
#घोषणा PROTOCOL_REG_CRC16_MASK			GENMASK(3, 3)
#घोषणा PROTOCOL_REG_CRC7_MASK			GENMASK(2, 2)

/*
 * The SPI data packet size may be any पूर्णांकeger घातer of two in the
 * range from 256 to 8192 bytes.
 */
#घोषणा DATA_PKT_LOG_SZ_MIN			8	/* 256 B */
#घोषणा DATA_PKT_LOG_SZ_MAX			13	/* 8 KiB */

/*
 * Select the data packet size (log2 of number of bytes): Use the
 * maximum data packet size.  We only retransmit complete packets, so
 * there is no benefit from using smaller data packets.
 */
#घोषणा DATA_PKT_LOG_SZ				DATA_PKT_LOG_SZ_MAX
#घोषणा DATA_PKT_SZ				(1 << DATA_PKT_LOG_SZ)

#घोषणा USE_SPI_DMA				0

#घोषणा WILC_SPI_COMMAND_STAT_SUCCESS		0
#घोषणा WILC_GET_RESP_HDR_START(h)		(((h) >> 4) & 0xf)

काष्ठा wilc_spi_cmd अणु
	u8 cmd_type;
	जोड़ अणु
		काष्ठा अणु
			u8 addr[3];
			u8 crc[];
		पूर्ण __packed simple_cmd;
		काष्ठा अणु
			u8 addr[3];
			u8 size[2];
			u8 crc[];
		पूर्ण __packed dma_cmd;
		काष्ठा अणु
			u8 addr[3];
			u8 size[3];
			u8 crc[];
		पूर्ण __packed dma_cmd_ext;
		काष्ठा अणु
			u8 addr[2];
			__be32 data;
			u8 crc[];
		पूर्ण __packed पूर्णांकernal_w_cmd;
		काष्ठा अणु
			u8 addr[3];
			__be32 data;
			u8 crc[];
		पूर्ण __packed w_cmd;
	पूर्ण u;
पूर्ण __packed;

काष्ठा wilc_spi_पढ़ो_rsp_data अणु
	u8 header;
	u8 data[4];
	u8 crc[];
पूर्ण __packed;

काष्ठा wilc_spi_rsp_data अणु
	u8 rsp_cmd_type;
	u8 status;
	u8 data[];
पूर्ण __packed;

अटल पूर्णांक wilc_bus_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा wilc *wilc;
	काष्ठा wilc_spi *spi_priv;

	spi_priv = kzalloc(माप(*spi_priv), GFP_KERNEL);
	अगर (!spi_priv)
		वापस -ENOMEM;

	ret = wilc_cfg80211_init(&wilc, &spi->dev, WILC_HIF_SPI, &wilc_hअगर_spi);
	अगर (ret) अणु
		kमुक्त(spi_priv);
		वापस ret;
	पूर्ण

	spi_set_drvdata(spi, wilc);
	wilc->dev = &spi->dev;
	wilc->bus_data = spi_priv;
	wilc->dev_irq_num = spi->irq;

	wilc->rtc_clk = devm_clk_get(&spi->dev, "rtc_clk");
	अगर (PTR_ERR_OR_ZERO(wilc->rtc_clk) == -EPROBE_DEFER) अणु
		kमुक्त(spi_priv);
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अगर (!IS_ERR(wilc->rtc_clk))
		clk_prepare_enable(wilc->rtc_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_bus_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा wilc *wilc = spi_get_drvdata(spi);

	अगर (!IS_ERR(wilc->rtc_clk))
		clk_disable_unprepare(wilc->rtc_clk);

	wilc_netdev_cleanup(wilc);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id wilc_of_match[] = अणु
	अणु .compatible = "microchip,wilc1000", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wilc_of_match);

अटल काष्ठा spi_driver wilc_spi_driver = अणु
	.driver = अणु
		.name = MODALIAS,
		.of_match_table = wilc_of_match,
	पूर्ण,
	.probe =  wilc_bus_probe,
	.हटाओ = wilc_bus_हटाओ,
पूर्ण;
module_spi_driver(wilc_spi_driver);
MODULE_LICENSE("GPL");

अटल पूर्णांक wilc_spi_tx(काष्ठा wilc *wilc, u8 *b, u32 len)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	पूर्णांक ret;
	काष्ठा spi_message msg;

	अगर (len > 0 && b) अणु
		काष्ठा spi_transfer tr = अणु
			.tx_buf = b,
			.len = len,
			.delay = अणु
				.value = 0,
				.unit = SPI_DELAY_UNIT_USECS
			पूर्ण,
		पूर्ण;
		अक्षर *r_buffer = kzalloc(len, GFP_KERNEL);

		अगर (!r_buffer)
			वापस -ENOMEM;

		tr.rx_buf = r_buffer;
		dev_dbg(&spi->dev, "Request writing %d bytes\n", len);

		स_रखो(&msg, 0, माप(msg));
		spi_message_init(&msg);
		msg.spi = spi;
		msg.is_dma_mapped = USE_SPI_DMA;
		spi_message_add_tail(&tr, &msg);

		ret = spi_sync(spi, &msg);
		अगर (ret < 0)
			dev_err(&spi->dev, "SPI transaction failed\n");

		kमुक्त(r_buffer);
	पूर्ण अन्यथा अणु
		dev_err(&spi->dev,
			"can't write data with the following length: %d\n",
			len);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wilc_spi_rx(काष्ठा wilc *wilc, u8 *rb, u32 rlen)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	पूर्णांक ret;

	अगर (rlen > 0) अणु
		काष्ठा spi_message msg;
		काष्ठा spi_transfer tr = अणु
			.rx_buf = rb,
			.len = rlen,
			.delay = अणु
				.value = 0,
				.unit = SPI_DELAY_UNIT_USECS
			पूर्ण,

		पूर्ण;
		अक्षर *t_buffer = kzalloc(rlen, GFP_KERNEL);

		अगर (!t_buffer)
			वापस -ENOMEM;

		tr.tx_buf = t_buffer;

		स_रखो(&msg, 0, माप(msg));
		spi_message_init(&msg);
		msg.spi = spi;
		msg.is_dma_mapped = USE_SPI_DMA;
		spi_message_add_tail(&tr, &msg);

		ret = spi_sync(spi, &msg);
		अगर (ret < 0)
			dev_err(&spi->dev, "SPI transaction failed\n");
		kमुक्त(t_buffer);
	पूर्ण अन्यथा अणु
		dev_err(&spi->dev,
			"can't read data with the following length: %u\n",
			rlen);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wilc_spi_tx_rx(काष्ठा wilc *wilc, u8 *wb, u8 *rb, u32 rlen)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	पूर्णांक ret;

	अगर (rlen > 0) अणु
		काष्ठा spi_message msg;
		काष्ठा spi_transfer tr = अणु
			.rx_buf = rb,
			.tx_buf = wb,
			.len = rlen,
			.bits_per_word = 8,
			.delay = अणु
				.value = 0,
				.unit = SPI_DELAY_UNIT_USECS
			पूर्ण,

		पूर्ण;

		स_रखो(&msg, 0, माप(msg));
		spi_message_init(&msg);
		msg.spi = spi;
		msg.is_dma_mapped = USE_SPI_DMA;

		spi_message_add_tail(&tr, &msg);
		ret = spi_sync(spi, &msg);
		अगर (ret < 0)
			dev_err(&spi->dev, "SPI transaction failed\n");
	पूर्ण अन्यथा अणु
		dev_err(&spi->dev,
			"can't read data with the following length: %u\n",
			rlen);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक spi_data_ग_लिखो(काष्ठा wilc *wilc, u8 *b, u32 sz)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	काष्ठा wilc_spi *spi_priv = wilc->bus_data;
	पूर्णांक ix, nbytes;
	पूर्णांक result = 0;
	u8 cmd, order, crc[2];
	u16 crc_calc;

	/*
	 * Data
	 */
	ix = 0;
	करो अणु
		अगर (sz <= DATA_PKT_SZ) अणु
			nbytes = sz;
			order = 0x3;
		पूर्ण अन्यथा अणु
			nbytes = DATA_PKT_SZ;
			अगर (ix == 0)
				order = 0x1;
			अन्यथा
				order = 0x02;
		पूर्ण

		/*
		 * Write command
		 */
		cmd = 0xf0;
		cmd |= order;

		अगर (wilc_spi_tx(wilc, &cmd, 1)) अणु
			dev_err(&spi->dev,
				"Failed data block cmd write, bus error...\n");
			result = -EINVAL;
			अवरोध;
		पूर्ण

		/*
		 * Write data
		 */
		अगर (wilc_spi_tx(wilc, &b[ix], nbytes)) अणु
			dev_err(&spi->dev,
				"Failed data block write, bus error...\n");
			result = -EINVAL;
			अवरोध;
		पूर्ण

		/*
		 * Write CRC
		 */
		अगर (spi_priv->crc16_enabled) अणु
			crc_calc = crc_itu_t(0xffff, &b[ix], nbytes);
			crc[0] = crc_calc >> 8;
			crc[1] = crc_calc;
			अगर (wilc_spi_tx(wilc, crc, 2)) अणु
				dev_err(&spi->dev, "Failed data block crc write, bus error...\n");
				result = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * No need to रुको क्रम response
		 */
		ix += nbytes;
		sz -= nbytes;
	पूर्ण जबतक (sz);

	वापस result;
पूर्ण

/********************************************
 *
 *      Spi Internal Read/Write Function
 *
 ********************************************/
अटल u8 wilc_get_crc7(u8 *buffer, u32 len)
अणु
	वापस crc7_be(0xfe, buffer, len);
पूर्ण

अटल पूर्णांक wilc_spi_single_पढ़ो(काष्ठा wilc *wilc, u8 cmd, u32 adr, व्योम *b,
				u8 घड़ीless)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	काष्ठा wilc_spi *spi_priv = wilc->bus_data;
	u8 wb[32], rb[32];
	पूर्णांक cmd_len, resp_len, i;
	u16 crc_calc, crc_recv;
	काष्ठा wilc_spi_cmd *c;
	काष्ठा wilc_spi_rsp_data *r;
	काष्ठा wilc_spi_पढ़ो_rsp_data *r_data;

	स_रखो(wb, 0x0, माप(wb));
	स_रखो(rb, 0x0, माप(rb));
	c = (काष्ठा wilc_spi_cmd *)wb;
	c->cmd_type = cmd;
	अगर (cmd == CMD_SINGLE_READ) अणु
		c->u.simple_cmd.addr[0] = adr >> 16;
		c->u.simple_cmd.addr[1] = adr >> 8;
		c->u.simple_cmd.addr[2] = adr;
	पूर्ण अन्यथा अगर (cmd == CMD_INTERNAL_READ) अणु
		c->u.simple_cmd.addr[0] = adr >> 8;
		अगर (घड़ीless == 1)
			c->u.simple_cmd.addr[0] |= BIT(7);
		c->u.simple_cmd.addr[1] = adr;
		c->u.simple_cmd.addr[2] = 0x0;
	पूर्ण अन्यथा अणु
		dev_err(&spi->dev, "cmd [%x] not supported\n", cmd);
		वापस -EINVAL;
	पूर्ण

	cmd_len = दुरत्व(काष्ठा wilc_spi_cmd, u.simple_cmd.crc);
	resp_len = माप(*r) + माप(*r_data) + WILC_SPI_RSP_HDR_EXTRA_DATA;

	अगर (spi_priv->crc7_enabled) अणु
		c->u.simple_cmd.crc[0] = wilc_get_crc7(wb, cmd_len);
		cmd_len += 1;
		resp_len += 2;
	पूर्ण

	अगर (cmd_len + resp_len > ARRAY_SIZE(wb)) अणु
		dev_err(&spi->dev,
			"spi buffer size too small (%d) (%d) (%zu)\n",
			cmd_len, resp_len, ARRAY_SIZE(wb));
		वापस -EINVAL;
	पूर्ण

	अगर (wilc_spi_tx_rx(wilc, wb, rb, cmd_len + resp_len)) अणु
		dev_err(&spi->dev, "Failed cmd write, bus error...\n");
		वापस -EINVAL;
	पूर्ण

	r = (काष्ठा wilc_spi_rsp_data *)&rb[cmd_len];
	अगर (r->rsp_cmd_type != cmd) अणु
		अगर (!spi_priv->probing_crc)
			dev_err(&spi->dev,
				"Failed cmd, cmd (%02x), resp (%02x)\n",
				cmd, r->rsp_cmd_type);
		वापस -EINVAL;
	पूर्ण

	अगर (r->status != WILC_SPI_COMMAND_STAT_SUCCESS) अणु
		dev_err(&spi->dev, "Failed cmd state response state (%02x)\n",
			r->status);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < WILC_SPI_RSP_HDR_EXTRA_DATA; ++i)
		अगर (WILC_GET_RESP_HDR_START(r->data[i]) == 0xf)
			अवरोध;

	अगर (i >= WILC_SPI_RSP_HDR_EXTRA_DATA) अणु
		dev_err(&spi->dev, "Error, data start missing\n");
		वापस -EINVAL;
	पूर्ण

	r_data = (काष्ठा wilc_spi_पढ़ो_rsp_data *)&r->data[i];

	अगर (b)
		स_नकल(b, r_data->data, 4);

	अगर (!घड़ीless && spi_priv->crc16_enabled) अणु
		crc_recv = (r_data->crc[0] << 8) | r_data->crc[1];
		crc_calc = crc_itu_t(0xffff, r_data->data, 4);
		अगर (crc_recv != crc_calc) अणु
			dev_err(&spi->dev, "%s: bad CRC 0x%04x "
				"(calculated 0x%04x)\n", __func__,
				crc_recv, crc_calc);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_spi_ग_लिखो_cmd(काष्ठा wilc *wilc, u8 cmd, u32 adr, u32 data,
			      u8 घड़ीless)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	काष्ठा wilc_spi *spi_priv = wilc->bus_data;
	u8 wb[32], rb[32];
	पूर्णांक cmd_len, resp_len;
	काष्ठा wilc_spi_cmd *c;
	काष्ठा wilc_spi_rsp_data *r;

	स_रखो(wb, 0x0, माप(wb));
	स_रखो(rb, 0x0, माप(rb));
	c = (काष्ठा wilc_spi_cmd *)wb;
	c->cmd_type = cmd;
	अगर (cmd == CMD_INTERNAL_WRITE) अणु
		c->u.पूर्णांकernal_w_cmd.addr[0] = adr >> 8;
		अगर (घड़ीless == 1)
			c->u.पूर्णांकernal_w_cmd.addr[0] |= BIT(7);

		c->u.पूर्णांकernal_w_cmd.addr[1] = adr;
		c->u.पूर्णांकernal_w_cmd.data = cpu_to_be32(data);
		cmd_len = दुरत्व(काष्ठा wilc_spi_cmd, u.पूर्णांकernal_w_cmd.crc);
		अगर (spi_priv->crc7_enabled)
			c->u.पूर्णांकernal_w_cmd.crc[0] = wilc_get_crc7(wb, cmd_len);
	पूर्ण अन्यथा अगर (cmd == CMD_SINGLE_WRITE) अणु
		c->u.w_cmd.addr[0] = adr >> 16;
		c->u.w_cmd.addr[1] = adr >> 8;
		c->u.w_cmd.addr[2] = adr;
		c->u.w_cmd.data = cpu_to_be32(data);
		cmd_len = दुरत्व(काष्ठा wilc_spi_cmd, u.w_cmd.crc);
		अगर (spi_priv->crc7_enabled)
			c->u.w_cmd.crc[0] = wilc_get_crc7(wb, cmd_len);
	पूर्ण अन्यथा अणु
		dev_err(&spi->dev, "write cmd [%x] not supported\n", cmd);
		वापस -EINVAL;
	पूर्ण

	अगर (spi_priv->crc7_enabled)
		cmd_len += 1;

	resp_len = माप(*r);

	अगर (cmd_len + resp_len > ARRAY_SIZE(wb)) अणु
		dev_err(&spi->dev,
			"spi buffer size too small (%d) (%d) (%zu)\n",
			cmd_len, resp_len, ARRAY_SIZE(wb));
		वापस -EINVAL;
	पूर्ण

	अगर (wilc_spi_tx_rx(wilc, wb, rb, cmd_len + resp_len)) अणु
		dev_err(&spi->dev, "Failed cmd write, bus error...\n");
		वापस -EINVAL;
	पूर्ण

	r = (काष्ठा wilc_spi_rsp_data *)&rb[cmd_len];
	अगर (r->rsp_cmd_type != cmd) अणु
		dev_err(&spi->dev,
			"Failed cmd response, cmd (%02x), resp (%02x)\n",
			cmd, r->rsp_cmd_type);
		वापस -EINVAL;
	पूर्ण

	अगर (r->status != WILC_SPI_COMMAND_STAT_SUCCESS) अणु
		dev_err(&spi->dev, "Failed cmd state response state (%02x)\n",
			r->status);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_spi_dma_rw(काष्ठा wilc *wilc, u8 cmd, u32 adr, u8 *b, u32 sz)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	काष्ठा wilc_spi *spi_priv = wilc->bus_data;
	u16 crc_recv, crc_calc;
	u8 wb[32], rb[32];
	पूर्णांक cmd_len, resp_len;
	पूर्णांक retry, ix = 0;
	u8 crc[2];
	काष्ठा wilc_spi_cmd *c;
	काष्ठा wilc_spi_rsp_data *r;

	स_रखो(wb, 0x0, माप(wb));
	स_रखो(rb, 0x0, माप(rb));
	c = (काष्ठा wilc_spi_cmd *)wb;
	c->cmd_type = cmd;
	अगर (cmd == CMD_DMA_WRITE || cmd == CMD_DMA_READ) अणु
		c->u.dma_cmd.addr[0] = adr >> 16;
		c->u.dma_cmd.addr[1] = adr >> 8;
		c->u.dma_cmd.addr[2] = adr;
		c->u.dma_cmd.size[0] = sz >> 8;
		c->u.dma_cmd.size[1] = sz;
		cmd_len = दुरत्व(काष्ठा wilc_spi_cmd, u.dma_cmd.crc);
		अगर (spi_priv->crc7_enabled)
			c->u.dma_cmd.crc[0] = wilc_get_crc7(wb, cmd_len);
	पूर्ण अन्यथा अगर (cmd == CMD_DMA_EXT_WRITE || cmd == CMD_DMA_EXT_READ) अणु
		c->u.dma_cmd_ext.addr[0] = adr >> 16;
		c->u.dma_cmd_ext.addr[1] = adr >> 8;
		c->u.dma_cmd_ext.addr[2] = adr;
		c->u.dma_cmd_ext.size[0] = sz >> 16;
		c->u.dma_cmd_ext.size[1] = sz >> 8;
		c->u.dma_cmd_ext.size[2] = sz;
		cmd_len = दुरत्व(काष्ठा wilc_spi_cmd, u.dma_cmd_ext.crc);
		अगर (spi_priv->crc7_enabled)
			c->u.dma_cmd_ext.crc[0] = wilc_get_crc7(wb, cmd_len);
	पूर्ण अन्यथा अणु
		dev_err(&spi->dev, "dma read write cmd [%x] not supported\n",
			cmd);
		वापस -EINVAL;
	पूर्ण
	अगर (spi_priv->crc7_enabled)
		cmd_len += 1;

	resp_len = माप(*r);

	अगर (cmd_len + resp_len > ARRAY_SIZE(wb)) अणु
		dev_err(&spi->dev, "spi buffer size too small (%d)(%d) (%zu)\n",
			cmd_len, resp_len, ARRAY_SIZE(wb));
		वापस -EINVAL;
	पूर्ण

	अगर (wilc_spi_tx_rx(wilc, wb, rb, cmd_len + resp_len)) अणु
		dev_err(&spi->dev, "Failed cmd write, bus error...\n");
		वापस -EINVAL;
	पूर्ण

	r = (काष्ठा wilc_spi_rsp_data *)&rb[cmd_len];
	अगर (r->rsp_cmd_type != cmd) अणु
		dev_err(&spi->dev,
			"Failed cmd response, cmd (%02x), resp (%02x)\n",
			cmd, r->rsp_cmd_type);
		वापस -EINVAL;
	पूर्ण

	अगर (r->status != WILC_SPI_COMMAND_STAT_SUCCESS) अणु
		dev_err(&spi->dev, "Failed cmd state response state (%02x)\n",
			r->status);
		वापस -EINVAL;
	पूर्ण

	अगर (cmd == CMD_DMA_WRITE || cmd == CMD_DMA_EXT_WRITE)
		वापस 0;

	जबतक (sz > 0) अणु
		पूर्णांक nbytes;
		u8 rsp;

		अगर (sz <= DATA_PKT_SZ)
			nbytes = sz;
		अन्यथा
			nbytes = DATA_PKT_SZ;

		/*
		 * Data Response header
		 */
		retry = 100;
		करो अणु
			अगर (wilc_spi_rx(wilc, &rsp, 1)) अणु
				dev_err(&spi->dev,
					"Failed resp read, bus err\n");
				वापस -EINVAL;
			पूर्ण
			अगर (WILC_GET_RESP_HDR_START(rsp) == 0xf)
				अवरोध;
		पूर्ण जबतक (retry--);

		/*
		 * Read bytes
		 */
		अगर (wilc_spi_rx(wilc, &b[ix], nbytes)) अणु
			dev_err(&spi->dev,
				"Failed block read, bus err\n");
			वापस -EINVAL;
		पूर्ण

		/*
		 * Read CRC
		 */
		अगर (spi_priv->crc16_enabled) अणु
			अगर (wilc_spi_rx(wilc, crc, 2)) अणु
				dev_err(&spi->dev,
					"Failed block CRC read, bus err\n");
				वापस -EINVAL;
			पूर्ण
			crc_recv = (crc[0] << 8) | crc[1];
			crc_calc = crc_itu_t(0xffff, &b[ix], nbytes);
			अगर (crc_recv != crc_calc) अणु
				dev_err(&spi->dev, "%s: bad CRC 0x%04x "
					"(calculated 0x%04x)\n", __func__,
					crc_recv, crc_calc);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		ix += nbytes;
		sz -= nbytes;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wilc_spi_पढ़ो_reg(काष्ठा wilc *wilc, u32 addr, u32 *data)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	पूर्णांक result;
	u8 cmd = CMD_SINGLE_READ;
	u8 घड़ीless = 0;

	अगर (addr < WILC_SPI_CLOCKLESS_ADDR_LIMIT) अणु
		/* Clockless रेजिस्टर */
		cmd = CMD_INTERNAL_READ;
		घड़ीless = 1;
	पूर्ण

	result = wilc_spi_single_पढ़ो(wilc, cmd, addr, data, घड़ीless);
	अगर (result) अणु
		dev_err(&spi->dev, "Failed cmd, read reg (%08x)...\n", addr);
		वापस result;
	पूर्ण

	le32_to_cpus(data);

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_spi_पढ़ो(काष्ठा wilc *wilc, u32 addr, u8 *buf, u32 size)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	पूर्णांक result;

	अगर (size <= 4)
		वापस -EINVAL;

	result = wilc_spi_dma_rw(wilc, CMD_DMA_EXT_READ, addr, buf, size);
	अगर (result) अणु
		dev_err(&spi->dev, "Failed cmd, read block (%08x)...\n", addr);
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spi_पूर्णांकernal_ग_लिखो(काष्ठा wilc *wilc, u32 adr, u32 dat)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	पूर्णांक result;

	result = wilc_spi_ग_लिखो_cmd(wilc, CMD_INTERNAL_WRITE, adr, dat, 0);
	अगर (result) अणु
		dev_err(&spi->dev, "Failed internal write cmd...\n");
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spi_पूर्णांकernal_पढ़ो(काष्ठा wilc *wilc, u32 adr, u32 *data)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	काष्ठा wilc_spi *spi_priv = wilc->bus_data;
	पूर्णांक result;

	result = wilc_spi_single_पढ़ो(wilc, CMD_INTERNAL_READ, adr, data, 0);
	अगर (result) अणु
		अगर (!spi_priv->probing_crc)
			dev_err(&spi->dev, "Failed internal read cmd...\n");
		वापस result;
	पूर्ण

	le32_to_cpus(data);

	वापस 0;
पूर्ण

/********************************************
 *
 *      Spi पूर्णांकerfaces
 *
 ********************************************/

अटल पूर्णांक wilc_spi_ग_लिखो_reg(काष्ठा wilc *wilc, u32 addr, u32 data)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	पूर्णांक result;
	u8 cmd = CMD_SINGLE_WRITE;
	u8 घड़ीless = 0;

	अगर (addr < WILC_SPI_CLOCKLESS_ADDR_LIMIT) अणु
		/* Clockless रेजिस्टर */
		cmd = CMD_INTERNAL_WRITE;
		घड़ीless = 1;
	पूर्ण

	result = wilc_spi_ग_लिखो_cmd(wilc, cmd, addr, data, घड़ीless);
	अगर (result) अणु
		dev_err(&spi->dev, "Failed cmd, write reg (%08x)...\n", addr);
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spi_data_rsp(काष्ठा wilc *wilc, u8 cmd)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	पूर्णांक result, i;
	u8 rsp[4];

	/*
	 * The response to data packets is two bytes दीर्घ.  For
	 * efficiency's sake, wilc_spi_ग_लिखो() wisely ignores the
	 * responses क्रम all packets but the final one.  The करोwnside
	 * of that optimization is that when the final data packet is
	 * लघु, we may receive (part of) the response to the
	 * second-to-last packet beक्रमe the one क्रम the final packet.
	 * To handle this, we always पढ़ो 4 bytes and then search क्रम
	 * the last byte that contains the "Response Start" code (0xc
	 * in the top 4 bits).  We then know that this byte is the
	 * first response byte of the final data packet.
	 */
	result = wilc_spi_rx(wilc, rsp, माप(rsp));
	अगर (result) अणु
		dev_err(&spi->dev, "Failed bus error...\n");
		वापस result;
	पूर्ण

	क्रम (i = माप(rsp) - 2; i >= 0; --i)
		अगर (FIELD_GET(RSP_START_FIELD, rsp[i]) == RSP_START_TAG)
			अवरोध;

	अगर (i < 0) अणु
		dev_err(&spi->dev,
			"Data packet response missing (%02x %02x %02x %02x)\n",
			rsp[0], rsp[1], rsp[2], rsp[3]);
		वापस -1;
	पूर्ण

	/* rsp[i] is the last response start byte */

	अगर (FIELD_GET(RSP_TYPE_FIELD, rsp[i]) != RSP_TYPE_LAST_PACKET
	    || rsp[i + 1] != RSP_STATE_NO_ERROR) अणु
		dev_err(&spi->dev, "Data response error (%02x %02x)\n",
			rsp[i], rsp[i + 1]);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wilc_spi_ग_लिखो(काष्ठा wilc *wilc, u32 addr, u8 *buf, u32 size)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	पूर्णांक result;

	/*
	 * has to be greated than 4
	 */
	अगर (size <= 4)
		वापस -EINVAL;

	result = wilc_spi_dma_rw(wilc, CMD_DMA_EXT_WRITE, addr, शून्य, size);
	अगर (result) अणु
		dev_err(&spi->dev,
			"Failed cmd, write block (%08x)...\n", addr);
		वापस result;
	पूर्ण

	/*
	 * Data
	 */
	result = spi_data_ग_लिखो(wilc, buf, size);
	अगर (result) अणु
		dev_err(&spi->dev, "Failed block data write...\n");
		वापस result;
	पूर्ण

	/*
	 * Data response
	 */
	वापस spi_data_rsp(wilc, CMD_DMA_EXT_WRITE);
पूर्ण

/********************************************
 *
 *      Bus पूर्णांकerfaces
 *
 ********************************************/

अटल पूर्णांक wilc_spi_deinit(काष्ठा wilc *wilc)
अणु
	/*
	 * TODO:
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक wilc_spi_init(काष्ठा wilc *wilc, bool resume)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	काष्ठा wilc_spi *spi_priv = wilc->bus_data;
	u32 reg;
	u32 chipid;
	अटल पूर्णांक isinit;
	पूर्णांक ret, i;

	अगर (isinit) अणु
		ret = wilc_spi_पढ़ो_reg(wilc, WILC_CHIPID, &chipid);
		अगर (ret)
			dev_err(&spi->dev, "Fail cmd read chip id...\n");

		वापस ret;
	पूर्ण

	/*
	 * configure protocol
	 */

	/*
	 * Infer the CRC settings that are currently in effect.  This
	 * is necessary because we can't be sure that the chip has
	 * been RESET (e.g, after module unload and reload).
	 */
	spi_priv->probing_crc = true;
	spi_priv->crc7_enabled = enable_crc7;
	spi_priv->crc16_enabled = false; /* करोn't check CRC16 during probing */
	क्रम (i = 0; i < 2; ++i) अणु
		ret = spi_पूर्णांकernal_पढ़ो(wilc, WILC_SPI_PROTOCOL_OFFSET, &reg);
		अगर (ret == 0)
			अवरोध;
		spi_priv->crc7_enabled = !enable_crc7;
	पूर्ण
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed with CRC7 on and off.\n");
		वापस ret;
	पूर्ण

	/* set up the desired CRC configuration: */
	reg &= ~(PROTOCOL_REG_CRC7_MASK | PROTOCOL_REG_CRC16_MASK);
	अगर (enable_crc7)
		reg |= PROTOCOL_REG_CRC7_MASK;
	अगर (enable_crc16)
		reg |= PROTOCOL_REG_CRC16_MASK;

	/* set up the data packet size: */
	BUILD_BUG_ON(DATA_PKT_LOG_SZ < DATA_PKT_LOG_SZ_MIN
		     || DATA_PKT_LOG_SZ > DATA_PKT_LOG_SZ_MAX);
	reg &= ~PROTOCOL_REG_PKT_SZ_MASK;
	reg |= FIELD_PREP(PROTOCOL_REG_PKT_SZ_MASK,
			  DATA_PKT_LOG_SZ - DATA_PKT_LOG_SZ_MIN);

	/* establish the new setup: */
	ret = spi_पूर्णांकernal_ग_लिखो(wilc, WILC_SPI_PROTOCOL_OFFSET, reg);
	अगर (ret) अणु
		dev_err(&spi->dev,
			"[wilc spi %d]: Failed internal write reg\n",
			__LINE__);
		वापस ret;
	पूर्ण
	/* update our state to match new protocol settings: */
	spi_priv->crc7_enabled = enable_crc7;
	spi_priv->crc16_enabled = enable_crc16;

	/* re-पढ़ो to make sure new settings are in effect: */
	spi_पूर्णांकernal_पढ़ो(wilc, WILC_SPI_PROTOCOL_OFFSET, &reg);

	spi_priv->probing_crc = false;

	/*
	 * make sure can पढ़ो back chip id correctly
	 */
	ret = wilc_spi_पढ़ो_reg(wilc, WILC_CHIPID, &chipid);
	अगर (ret) अणु
		dev_err(&spi->dev, "Fail cmd read chip id...\n");
		वापस ret;
	पूर्ण

	isinit = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_spi_पढ़ो_size(काष्ठा wilc *wilc, u32 *size)
अणु
	पूर्णांक ret;

	ret = spi_पूर्णांकernal_पढ़ो(wilc,
				WILC_SPI_INT_STATUS - WILC_SPI_REG_BASE, size);
	*size = FIELD_GET(IRQ_DMA_WD_CNT_MASK, *size);

	वापस ret;
पूर्ण

अटल पूर्णांक wilc_spi_पढ़ो_पूर्णांक(काष्ठा wilc *wilc, u32 *पूर्णांक_status)
अणु
	वापस spi_पूर्णांकernal_पढ़ो(wilc, WILC_SPI_INT_STATUS - WILC_SPI_REG_BASE,
				 पूर्णांक_status);
पूर्ण

अटल पूर्णांक wilc_spi_clear_पूर्णांक_ext(काष्ठा wilc *wilc, u32 val)
अणु
	पूर्णांक ret;
	पूर्णांक retry = SPI_ENABLE_VMM_RETRY_LIMIT;
	u32 check;

	जबतक (retry) अणु
		ret = spi_पूर्णांकernal_ग_लिखो(wilc,
					 WILC_SPI_INT_CLEAR - WILC_SPI_REG_BASE,
					 val);
		अगर (ret)
			अवरोध;

		ret = spi_पूर्णांकernal_पढ़ो(wilc,
					WILC_SPI_INT_CLEAR - WILC_SPI_REG_BASE,
					&check);
		अगर (ret || ((check & EN_VMM) == (val & EN_VMM)))
			अवरोध;

		retry--;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक wilc_spi_sync_ext(काष्ठा wilc *wilc, पूर्णांक nपूर्णांक)
अणु
	काष्ठा spi_device *spi = to_spi_device(wilc->dev);
	u32 reg;
	पूर्णांक ret, i;

	अगर (nपूर्णांक > MAX_NUM_INT) अणु
		dev_err(&spi->dev, "Too many interrupts (%d)...\n", nपूर्णांक);
		वापस -EINVAL;
	पूर्ण

	/*
	 * पूर्णांकerrupt pin mux select
	 */
	ret = wilc_spi_पढ़ो_reg(wilc, WILC_PIN_MUX_0, &reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed read reg (%08x)...\n",
			WILC_PIN_MUX_0);
		वापस ret;
	पूर्ण
	reg |= BIT(8);
	ret = wilc_spi_ग_लिखो_reg(wilc, WILC_PIN_MUX_0, reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed write reg (%08x)...\n",
			WILC_PIN_MUX_0);
		वापस ret;
	पूर्ण

	/*
	 * पूर्णांकerrupt enable
	 */
	ret = wilc_spi_पढ़ो_reg(wilc, WILC_INTR_ENABLE, &reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed read reg (%08x)...\n",
			WILC_INTR_ENABLE);
		वापस ret;
	पूर्ण

	क्रम (i = 0; (i < 5) && (nपूर्णांक > 0); i++, nपूर्णांक--)
		reg |= (BIT((27 + i)));

	ret = wilc_spi_ग_लिखो_reg(wilc, WILC_INTR_ENABLE, reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed write reg (%08x)...\n",
			WILC_INTR_ENABLE);
		वापस ret;
	पूर्ण
	अगर (nपूर्णांक) अणु
		ret = wilc_spi_पढ़ो_reg(wilc, WILC_INTR2_ENABLE, &reg);
		अगर (ret) अणु
			dev_err(&spi->dev, "Failed read reg (%08x)...\n",
				WILC_INTR2_ENABLE);
			वापस ret;
		पूर्ण

		क्रम (i = 0; (i < 3) && (nपूर्णांक > 0); i++, nपूर्णांक--)
			reg |= BIT(i);

		ret = wilc_spi_पढ़ो_reg(wilc, WILC_INTR2_ENABLE, &reg);
		अगर (ret) अणु
			dev_err(&spi->dev, "Failed write reg (%08x)...\n",
				WILC_INTR2_ENABLE);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Global spi HIF function table */
अटल स्थिर काष्ठा wilc_hअगर_func wilc_hअगर_spi = अणु
	.hअगर_init = wilc_spi_init,
	.hअगर_deinit = wilc_spi_deinit,
	.hअगर_पढ़ो_reg = wilc_spi_पढ़ो_reg,
	.hअगर_ग_लिखो_reg = wilc_spi_ग_लिखो_reg,
	.hअगर_block_rx = wilc_spi_पढ़ो,
	.hअगर_block_tx = wilc_spi_ग_लिखो,
	.hअगर_पढ़ो_पूर्णांक = wilc_spi_पढ़ो_पूर्णांक,
	.hअगर_clear_पूर्णांक_ext = wilc_spi_clear_पूर्णांक_ext,
	.hअगर_पढ़ो_size = wilc_spi_पढ़ो_size,
	.hअगर_block_tx_ext = wilc_spi_ग_लिखो,
	.hअगर_block_rx_ext = wilc_spi_पढ़ो,
	.hअगर_sync_ext = wilc_spi_sync_ext,
पूर्ण;
