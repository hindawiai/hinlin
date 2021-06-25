<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mcp251xfd - Microchip MCP251xFD Family CAN controller driver
//
// Copyright (c) 2019, 2020 Pengutronix,
//                          Marc Kleine-Budde <kernel@pengutronix.de>
//

#समावेश "mcp251xfd.h"

#समावेश <यंत्र/unaligned.h>

अटल स्थिर काष्ठा regmap_config mcp251xfd_regmap_crc;

अटल पूर्णांक
mcp251xfd_regmap_nocrc_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा spi_device *spi = context;

	वापस spi_ग_लिखो(spi, data, count);
पूर्ण

अटल पूर्णांक
mcp251xfd_regmap_nocrc_gather_ग_लिखो(व्योम *context,
				    स्थिर व्योम *reg, माप_प्रकार reg_len,
				    स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	काष्ठा spi_device *spi = context;
	काष्ठा mcp251xfd_priv *priv = spi_get_drvdata(spi);
	काष्ठा mcp251xfd_map_buf_nocrc *buf_tx = priv->map_buf_nocrc_tx;
	काष्ठा spi_transfer xfer[] = अणु
		अणु
			.tx_buf = buf_tx,
			.len = माप(buf_tx->cmd) + val_len,
		पूर्ण,
	पूर्ण;

	BUILD_BUG_ON(माप(buf_tx->cmd) != माप(__be16));

	अगर (IS_ENABLED(CONFIG_CAN_MCP251XFD_SANITY) &&
	    reg_len != माप(buf_tx->cmd.cmd))
		वापस -EINVAL;

	स_नकल(&buf_tx->cmd, reg, माप(buf_tx->cmd));
	स_नकल(buf_tx->data, val, val_len);

	वापस spi_sync_transfer(spi, xfer, ARRAY_SIZE(xfer));
पूर्ण

अटल अंतरभूत bool mcp251xfd_update_bits_पढ़ो_reg(अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MCP251XFD_REG_INT:
	हाल MCP251XFD_REG_TEFCON:
	हाल MCP251XFD_REG_FIFOCON(MCP251XFD_RX_FIFO(0)):
	हाल MCP251XFD_REG_FLTCON(0):
	हाल MCP251XFD_REG_ECCSTAT:
	हाल MCP251XFD_REG_CRC:
		वापस false;
	हाल MCP251XFD_REG_CON:
	हाल MCP251XFD_REG_FIFOSTA(MCP251XFD_RX_FIFO(0)):
	हाल MCP251XFD_REG_OSC:
	हाल MCP251XFD_REG_ECCCON:
		वापस true;
	शेष:
		WARN(1, "Status of reg 0x%04x unknown.\n", reg);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक
mcp251xfd_regmap_nocrc_update_bits(व्योम *context, अचिन्हित पूर्णांक reg,
				   अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	काष्ठा spi_device *spi = context;
	काष्ठा mcp251xfd_priv *priv = spi_get_drvdata(spi);
	काष्ठा mcp251xfd_map_buf_nocrc *buf_rx = priv->map_buf_nocrc_rx;
	काष्ठा mcp251xfd_map_buf_nocrc *buf_tx = priv->map_buf_nocrc_tx;
	__le32 orig_le32 = 0, mask_le32, val_le32, पंचांगp_le32;
	u8 first_byte, last_byte, len;
	पूर्णांक err;

	BUILD_BUG_ON(माप(buf_rx->cmd) != माप(__be16));
	BUILD_BUG_ON(माप(buf_tx->cmd) != माप(__be16));

	अगर (IS_ENABLED(CONFIG_CAN_MCP251XFD_SANITY) &&
	    mask == 0)
		वापस -EINVAL;

	first_byte = mcp251xfd_first_byte_set(mask);
	last_byte = mcp251xfd_last_byte_set(mask);
	len = last_byte - first_byte + 1;

	अगर (mcp251xfd_update_bits_पढ़ो_reg(reg)) अणु
		काष्ठा spi_transfer xfer[2] = अणु पूर्ण;
		काष्ठा spi_message msg;

		spi_message_init(&msg);
		spi_message_add_tail(&xfer[0], &msg);

		अगर (priv->devtype_data.quirks & MCP251XFD_QUIRK_HALF_DUPLEX) अणु
			xfer[0].tx_buf = buf_tx;
			xfer[0].len = माप(buf_tx->cmd);

			xfer[1].rx_buf = buf_rx->data;
			xfer[1].len = len;
			spi_message_add_tail(&xfer[1], &msg);
		पूर्ण अन्यथा अणु
			xfer[0].tx_buf = buf_tx;
			xfer[0].rx_buf = buf_rx;
			xfer[0].len = माप(buf_tx->cmd) + len;

			अगर (MCP251XFD_SANITIZE_SPI)
				स_रखो(buf_tx->data, 0x0, len);
		पूर्ण

		mcp251xfd_spi_cmd_पढ़ो_nocrc(&buf_tx->cmd, reg + first_byte);
		err = spi_sync(spi, &msg);
		अगर (err)
			वापस err;

		स_नकल(&orig_le32, buf_rx->data, len);
	पूर्ण

	mask_le32 = cpu_to_le32(mask >> BITS_PER_BYTE * first_byte);
	val_le32 = cpu_to_le32(val >> BITS_PER_BYTE * first_byte);

	पंचांगp_le32 = orig_le32 & ~mask_le32;
	पंचांगp_le32 |= val_le32 & mask_le32;

	mcp251xfd_spi_cmd_ग_लिखो_nocrc(&buf_tx->cmd, reg + first_byte);
	स_नकल(buf_tx->data, &पंचांगp_le32, len);

	वापस spi_ग_लिखो(spi, buf_tx, माप(buf_tx->cmd) + len);
पूर्ण

अटल पूर्णांक
mcp251xfd_regmap_nocrc_पढ़ो(व्योम *context,
			    स्थिर व्योम *reg, माप_प्रकार reg_len,
			    व्योम *val_buf, माप_प्रकार val_len)
अणु
	काष्ठा spi_device *spi = context;
	काष्ठा mcp251xfd_priv *priv = spi_get_drvdata(spi);
	काष्ठा mcp251xfd_map_buf_nocrc *buf_rx = priv->map_buf_nocrc_rx;
	काष्ठा mcp251xfd_map_buf_nocrc *buf_tx = priv->map_buf_nocrc_tx;
	काष्ठा spi_transfer xfer[2] = अणु पूर्ण;
	काष्ठा spi_message msg;
	पूर्णांक err;

	BUILD_BUG_ON(माप(buf_rx->cmd) != माप(__be16));
	BUILD_BUG_ON(माप(buf_tx->cmd) != माप(__be16));

	अगर (IS_ENABLED(CONFIG_CAN_MCP251XFD_SANITY) &&
	    reg_len != माप(buf_tx->cmd.cmd))
		वापस -EINVAL;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer[0], &msg);

	अगर (priv->devtype_data.quirks & MCP251XFD_QUIRK_HALF_DUPLEX) अणु
		xfer[0].tx_buf = reg;
		xfer[0].len = माप(buf_tx->cmd);

		xfer[1].rx_buf = val_buf;
		xfer[1].len = val_len;
		spi_message_add_tail(&xfer[1], &msg);
	पूर्ण अन्यथा अणु
		xfer[0].tx_buf = buf_tx;
		xfer[0].rx_buf = buf_rx;
		xfer[0].len = माप(buf_tx->cmd) + val_len;

		स_नकल(&buf_tx->cmd, reg, माप(buf_tx->cmd));
		अगर (MCP251XFD_SANITIZE_SPI)
			स_रखो(buf_tx->data, 0x0, val_len);
	पूर्ण

	err = spi_sync(spi, &msg);
	अगर (err)
		वापस err;

	अगर (!(priv->devtype_data.quirks & MCP251XFD_QUIRK_HALF_DUPLEX))
		स_नकल(val_buf, buf_rx->data, val_len);

	वापस 0;
पूर्ण

अटल पूर्णांक
mcp251xfd_regmap_crc_gather_ग_लिखो(व्योम *context,
				  स्थिर व्योम *reg_p, माप_प्रकार reg_len,
				  स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	काष्ठा spi_device *spi = context;
	काष्ठा mcp251xfd_priv *priv = spi_get_drvdata(spi);
	काष्ठा mcp251xfd_map_buf_crc *buf_tx = priv->map_buf_crc_tx;
	काष्ठा spi_transfer xfer[] = अणु
		अणु
			.tx_buf = buf_tx,
			.len = माप(buf_tx->cmd) + val_len +
				माप(buf_tx->crc),
		पूर्ण,
	पूर्ण;
	u16 reg = *(u16 *)reg_p;
	u16 crc;

	BUILD_BUG_ON(माप(buf_tx->cmd) != माप(__be16) + माप(u8));

	अगर (IS_ENABLED(CONFIG_CAN_MCP251XFD_SANITY) &&
	    reg_len != माप(buf_tx->cmd.cmd) +
	    mcp251xfd_regmap_crc.pad_bits / BITS_PER_BYTE)
		वापस -EINVAL;

	mcp251xfd_spi_cmd_ग_लिखो_crc(&buf_tx->cmd, reg, val_len);
	स_नकल(buf_tx->data, val, val_len);

	crc = mcp251xfd_crc16_compute(buf_tx, माप(buf_tx->cmd) + val_len);
	put_unaligned_be16(crc, buf_tx->data + val_len);

	वापस spi_sync_transfer(spi, xfer, ARRAY_SIZE(xfer));
पूर्ण

अटल पूर्णांक
mcp251xfd_regmap_crc_ग_लिखो(व्योम *context,
			   स्थिर व्योम *data, माप_प्रकार count)
अणु
	स्थिर माप_प्रकार data_offset = माप(__be16) +
		mcp251xfd_regmap_crc.pad_bits / BITS_PER_BYTE;

	वापस mcp251xfd_regmap_crc_gather_ग_लिखो(context,
						 data, data_offset,
						 data + data_offset,
						 count - data_offset);
पूर्ण

अटल पूर्णांक
mcp251xfd_regmap_crc_पढ़ो_check_crc(स्थिर काष्ठा mcp251xfd_map_buf_crc * स्थिर buf_rx,
				    स्थिर काष्ठा mcp251xfd_map_buf_crc * स्थिर buf_tx,
				    अचिन्हित पूर्णांक data_len)
अणु
	u16 crc_received, crc_calculated;

	crc_received = get_unaligned_be16(buf_rx->data + data_len);
	crc_calculated = mcp251xfd_crc16_compute2(&buf_tx->cmd,
						  माप(buf_tx->cmd),
						  buf_rx->data,
						  data_len);
	अगर (crc_received != crc_calculated)
		वापस -EBADMSG;

	वापस 0;
पूर्ण


अटल पूर्णांक
mcp251xfd_regmap_crc_पढ़ो_one(काष्ठा mcp251xfd_priv *priv,
			      काष्ठा spi_message *msg, अचिन्हित पूर्णांक data_len)
अणु
	स्थिर काष्ठा mcp251xfd_map_buf_crc *buf_rx = priv->map_buf_crc_rx;
	स्थिर काष्ठा mcp251xfd_map_buf_crc *buf_tx = priv->map_buf_crc_tx;
	पूर्णांक err;

	BUILD_BUG_ON(माप(buf_rx->cmd) != माप(__be16) + माप(u8));
	BUILD_BUG_ON(माप(buf_tx->cmd) != माप(__be16) + माप(u8));

	err = spi_sync(priv->spi, msg);
	अगर (err)
		वापस err;

	वापस mcp251xfd_regmap_crc_पढ़ो_check_crc(buf_rx, buf_tx, data_len);
पूर्ण

अटल पूर्णांक
mcp251xfd_regmap_crc_पढ़ो(व्योम *context,
			  स्थिर व्योम *reg_p, माप_प्रकार reg_len,
			  व्योम *val_buf, माप_प्रकार val_len)
अणु
	काष्ठा spi_device *spi = context;
	काष्ठा mcp251xfd_priv *priv = spi_get_drvdata(spi);
	काष्ठा mcp251xfd_map_buf_crc *buf_rx = priv->map_buf_crc_rx;
	काष्ठा mcp251xfd_map_buf_crc *buf_tx = priv->map_buf_crc_tx;
	काष्ठा spi_transfer xfer[2] = अणु पूर्ण;
	काष्ठा spi_message msg;
	u16 reg = *(u16 *)reg_p;
	पूर्णांक i, err;

	BUILD_BUG_ON(माप(buf_rx->cmd) != माप(__be16) + माप(u8));
	BUILD_BUG_ON(माप(buf_tx->cmd) != माप(__be16) + माप(u8));

	अगर (IS_ENABLED(CONFIG_CAN_MCP251XFD_SANITY) &&
	    reg_len != माप(buf_tx->cmd.cmd) +
	    mcp251xfd_regmap_crc.pad_bits / BITS_PER_BYTE)
		वापस -EINVAL;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer[0], &msg);

	अगर (priv->devtype_data.quirks & MCP251XFD_QUIRK_HALF_DUPLEX) अणु
		xfer[0].tx_buf = buf_tx;
		xfer[0].len = माप(buf_tx->cmd);

		xfer[1].rx_buf = buf_rx->data;
		xfer[1].len = val_len + माप(buf_tx->crc);
		spi_message_add_tail(&xfer[1], &msg);
	पूर्ण अन्यथा अणु
		xfer[0].tx_buf = buf_tx;
		xfer[0].rx_buf = buf_rx;
		xfer[0].len = माप(buf_tx->cmd) + val_len +
			माप(buf_tx->crc);

		अगर (MCP251XFD_SANITIZE_SPI)
			स_रखो(buf_tx->data, 0x0, val_len +
			       माप(buf_tx->crc));
	पूर्ण

	mcp251xfd_spi_cmd_पढ़ो_crc(&buf_tx->cmd, reg, val_len);

	क्रम (i = 0; i < MCP251XFD_READ_CRC_RETRIES_MAX; i++) अणु
		err = mcp251xfd_regmap_crc_पढ़ो_one(priv, &msg, val_len);
		अगर (!err)
			जाओ out;
		अगर (err != -EBADMSG)
			वापस err;

		/* MCP251XFD_REG_TBC is the समय base counter
		 * रेजिस्टर. It increments once per SYS घड़ी tick,
		 * which is 20 or 40 MHz.
		 *
		 * Observation shows that अगर the lowest byte (which is
		 * transferred first on the SPI bus) of that रेजिस्टर
		 * is 0x00 or 0x80 the calculated CRC करोesn't always
		 * match the transferred one.
		 *
		 * If the highest bit in the lowest byte is flipped
		 * the transferred CRC matches the calculated one. We
		 * assume क्रम now the CRC calculation in the chip
		 * works on wrong data and the transferred data is
		 * correct.
		 */
		अगर (reg == MCP251XFD_REG_TBC &&
		    (buf_rx->data[0] == 0x0 || buf_rx->data[0] == 0x80)) अणु
			/* Flip highest bit in lowest byte of le32 */
			buf_rx->data[0] ^= 0x80;

			/* re-check CRC */
			err = mcp251xfd_regmap_crc_पढ़ो_check_crc(buf_rx,
								  buf_tx,
								  val_len);
			अगर (!err) अणु
				/* If CRC is now correct, assume
				 * transferred data was OK, flip bit
				 * back to original value.
				 */
				buf_rx->data[0] ^= 0x80;
				जाओ out;
			पूर्ण
		पूर्ण

		/* MCP251XFD_REG_OSC is the first ever reg we पढ़ो from.
		 *
		 * The chip may be in deep sleep and this SPI transfer
		 * (i.e. the निश्चितion of the CS) will wake the chip
		 * up. This takes about 3ms. The CRC of this transfer
		 * is wrong.
		 *
		 * Or there isn't a chip at all, in this हाल the CRC
		 * will be wrong, too.
		 *
		 * In both हालs ignore the CRC and copy the पढ़ो data
		 * to the caller. It will take care of both हालs.
		 *
		 */
		अगर (reg == MCP251XFD_REG_OSC) अणु
			err = 0;
			जाओ out;
		पूर्ण

		netdev_info(priv->ndev,
			    "CRC read error at address 0x%04x (length=%zd, data=%*ph, CRC=0x%04x) retrying.\n",
			    reg, val_len, (पूर्णांक)val_len, buf_rx->data,
			    get_unaligned_be16(buf_rx->data + val_len));
	पूर्ण

	अगर (err) अणु
		netdev_err(priv->ndev,
			   "CRC read error at address 0x%04x (length=%zd, data=%*ph, CRC=0x%04x).\n",
			   reg, val_len, (पूर्णांक)val_len, buf_rx->data,
			   get_unaligned_be16(buf_rx->data + val_len));

		वापस err;
	पूर्ण
 out:
	स_नकल(val_buf, buf_rx->data, val_len);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_range mcp251xfd_reg_table_yes_range[] = अणु
	regmap_reg_range(0x000, 0x2ec),	/* CAN FD Controller Module SFR */
	regmap_reg_range(0x400, 0xbfc),	/* RAM */
	regmap_reg_range(0xe00, 0xe14),	/* MCP2517/18FD SFR */
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table mcp251xfd_reg_table = अणु
	.yes_ranges = mcp251xfd_reg_table_yes_range,
	.n_yes_ranges = ARRAY_SIZE(mcp251xfd_reg_table_yes_range),
पूर्ण;

अटल स्थिर काष्ठा regmap_config mcp251xfd_regmap_nocrc = अणु
	.name = "nocrc",
	.reg_bits = 16,
	.reg_stride = 4,
	.pad_bits = 0,
	.val_bits = 32,
	.max_रेजिस्टर = 0xffc,
	.wr_table = &mcp251xfd_reg_table,
	.rd_table = &mcp251xfd_reg_table,
	.cache_type = REGCACHE_NONE,
	.पढ़ो_flag_mask = (__क्रमce अचिन्हित दीर्घ)
		cpu_to_be16(MCP251XFD_SPI_INSTRUCTION_READ),
	.ग_लिखो_flag_mask = (__क्रमce अचिन्हित दीर्घ)
		cpu_to_be16(MCP251XFD_SPI_INSTRUCTION_WRITE),
पूर्ण;

अटल स्थिर काष्ठा regmap_bus mcp251xfd_bus_nocrc = अणु
	.ग_लिखो = mcp251xfd_regmap_nocrc_ग_लिखो,
	.gather_ग_लिखो = mcp251xfd_regmap_nocrc_gather_ग_लिखो,
	.reg_update_bits = mcp251xfd_regmap_nocrc_update_bits,
	.पढ़ो = mcp251xfd_regmap_nocrc_पढ़ो,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_LITTLE,
	.max_raw_पढ़ो = माप_field(काष्ठा mcp251xfd_map_buf_nocrc, data),
	.max_raw_ग_लिखो = माप_field(काष्ठा mcp251xfd_map_buf_nocrc, data),
पूर्ण;

अटल स्थिर काष्ठा regmap_config mcp251xfd_regmap_crc = अणु
	.name = "crc",
	.reg_bits = 16,
	.reg_stride = 4,
	.pad_bits = 16,		/* keep data bits aligned */
	.val_bits = 32,
	.max_रेजिस्टर = 0xffc,
	.wr_table = &mcp251xfd_reg_table,
	.rd_table = &mcp251xfd_reg_table,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल स्थिर काष्ठा regmap_bus mcp251xfd_bus_crc = अणु
	.ग_लिखो = mcp251xfd_regmap_crc_ग_लिखो,
	.gather_ग_लिखो = mcp251xfd_regmap_crc_gather_ग_लिखो,
	.पढ़ो = mcp251xfd_regmap_crc_पढ़ो,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_NATIVE,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_LITTLE,
	.max_raw_पढ़ो = माप_field(काष्ठा mcp251xfd_map_buf_crc, data),
	.max_raw_ग_लिखो = माप_field(काष्ठा mcp251xfd_map_buf_crc, data),
पूर्ण;

अटल अंतरभूत bool
mcp251xfd_regmap_use_nocrc(काष्ठा mcp251xfd_priv *priv)
अणु
	वापस (!(priv->devtype_data.quirks & MCP251XFD_QUIRK_CRC_REG)) ||
		(!(priv->devtype_data.quirks & MCP251XFD_QUIRK_CRC_RX));
पूर्ण

अटल अंतरभूत bool
mcp251xfd_regmap_use_crc(काष्ठा mcp251xfd_priv *priv)
अणु
	वापस (priv->devtype_data.quirks & MCP251XFD_QUIRK_CRC_REG) ||
		(priv->devtype_data.quirks & MCP251XFD_QUIRK_CRC_RX);
पूर्ण

अटल पूर्णांक
mcp251xfd_regmap_init_nocrc(काष्ठा mcp251xfd_priv *priv)
अणु
	अगर (!priv->map_nocrc) अणु
		काष्ठा regmap *map;

		map = devm_regmap_init(&priv->spi->dev, &mcp251xfd_bus_nocrc,
				       priv->spi, &mcp251xfd_regmap_nocrc);
		अगर (IS_ERR(map))
			वापस PTR_ERR(map);

		priv->map_nocrc = map;
	पूर्ण

	अगर (!priv->map_buf_nocrc_rx) अणु
		priv->map_buf_nocrc_rx =
			devm_kzalloc(&priv->spi->dev,
				     माप(*priv->map_buf_nocrc_rx),
				     GFP_KERNEL);
		अगर (!priv->map_buf_nocrc_rx)
			वापस -ENOMEM;
	पूर्ण

	अगर (!priv->map_buf_nocrc_tx) अणु
		priv->map_buf_nocrc_tx =
			devm_kzalloc(&priv->spi->dev,
				     माप(*priv->map_buf_nocrc_tx),
				     GFP_KERNEL);
		अगर (!priv->map_buf_nocrc_tx)
			वापस -ENOMEM;
	पूर्ण

	अगर (!(priv->devtype_data.quirks & MCP251XFD_QUIRK_CRC_REG))
		priv->map_reg = priv->map_nocrc;

	अगर (!(priv->devtype_data.quirks & MCP251XFD_QUIRK_CRC_RX))
		priv->map_rx = priv->map_nocrc;

	वापस 0;
पूर्ण

अटल व्योम mcp251xfd_regmap_destroy_nocrc(काष्ठा mcp251xfd_priv *priv)
अणु
	अगर (priv->map_buf_nocrc_rx) अणु
		devm_kमुक्त(&priv->spi->dev, priv->map_buf_nocrc_rx);
		priv->map_buf_nocrc_rx = शून्य;
	पूर्ण
	अगर (priv->map_buf_nocrc_tx) अणु
		devm_kमुक्त(&priv->spi->dev, priv->map_buf_nocrc_tx);
		priv->map_buf_nocrc_tx = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक
mcp251xfd_regmap_init_crc(काष्ठा mcp251xfd_priv *priv)
अणु
	अगर (!priv->map_crc) अणु
		काष्ठा regmap *map;

		map = devm_regmap_init(&priv->spi->dev, &mcp251xfd_bus_crc,
				       priv->spi, &mcp251xfd_regmap_crc);
		अगर (IS_ERR(map))
			वापस PTR_ERR(map);

		priv->map_crc = map;
	पूर्ण

	अगर (!priv->map_buf_crc_rx) अणु
		priv->map_buf_crc_rx =
			devm_kzalloc(&priv->spi->dev,
				     माप(*priv->map_buf_crc_rx),
				     GFP_KERNEL);
		अगर (!priv->map_buf_crc_rx)
			वापस -ENOMEM;
	पूर्ण

	अगर (!priv->map_buf_crc_tx) अणु
		priv->map_buf_crc_tx =
			devm_kzalloc(&priv->spi->dev,
				     माप(*priv->map_buf_crc_tx),
				     GFP_KERNEL);
		अगर (!priv->map_buf_crc_tx)
			वापस -ENOMEM;
	पूर्ण

	अगर (priv->devtype_data.quirks & MCP251XFD_QUIRK_CRC_REG)
		priv->map_reg = priv->map_crc;

	अगर (priv->devtype_data.quirks & MCP251XFD_QUIRK_CRC_RX)
		priv->map_rx = priv->map_crc;

	वापस 0;
पूर्ण

अटल व्योम mcp251xfd_regmap_destroy_crc(काष्ठा mcp251xfd_priv *priv)
अणु
	अगर (priv->map_buf_crc_rx) अणु
		devm_kमुक्त(&priv->spi->dev, priv->map_buf_crc_rx);
		priv->map_buf_crc_rx = शून्य;
	पूर्ण
	अगर (priv->map_buf_crc_tx) अणु
		devm_kमुक्त(&priv->spi->dev, priv->map_buf_crc_tx);
		priv->map_buf_crc_tx = शून्य;
	पूर्ण
पूर्ण

पूर्णांक mcp251xfd_regmap_init(काष्ठा mcp251xfd_priv *priv)
अणु
	पूर्णांक err;

	अगर (mcp251xfd_regmap_use_nocrc(priv)) अणु
		err = mcp251xfd_regmap_init_nocrc(priv);

		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		mcp251xfd_regmap_destroy_nocrc(priv);
	पूर्ण

	अगर (mcp251xfd_regmap_use_crc(priv)) अणु
		err = mcp251xfd_regmap_init_crc(priv);

		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		mcp251xfd_regmap_destroy_crc(priv);
	पूर्ण

	वापस 0;
पूर्ण
