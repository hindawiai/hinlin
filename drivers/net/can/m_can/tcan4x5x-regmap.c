<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// tcan4x5x - Texas Instruments TCAN4x5x Family CAN controller driver
//
// Copyright (c) 2020 Pengutronix,
//                    Marc Kleine-Budde <kernel@pengutronix.de>
// Copyright (c) 2018-2019 Texas Instruments Incorporated
//                    http://www.ti.com/

#समावेश "tcan4x5x.h"

#घोषणा TCAN4X5X_SPI_INSTRUCTION_WRITE (0x61 << 24)
#घोषणा TCAN4X5X_SPI_INSTRUCTION_READ (0x41 << 24)

#घोषणा TCAN4X5X_MAX_REGISTER 0x8ffc

अटल पूर्णांक tcan4x5x_regmap_gather_ग_लिखो(व्योम *context,
					स्थिर व्योम *reg, माप_प्रकार reg_len,
					स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	काष्ठा spi_device *spi = context;
	काष्ठा tcan4x5x_priv *priv = spi_get_drvdata(spi);
	काष्ठा tcan4x5x_map_buf *buf_tx = &priv->map_buf_tx;
	काष्ठा spi_transfer xfer[] = अणु
		अणु
			.tx_buf = buf_tx,
			.len = माप(buf_tx->cmd) + val_len,
		पूर्ण,
	पूर्ण;

	स_नकल(&buf_tx->cmd, reg, माप(buf_tx->cmd.cmd) +
	       माप(buf_tx->cmd.addr));
	tcan4x5x_spi_cmd_set_len(&buf_tx->cmd, val_len);
	स_नकल(buf_tx->data, val, val_len);

	वापस spi_sync_transfer(spi, xfer, ARRAY_SIZE(xfer));
पूर्ण

अटल पूर्णांक tcan4x5x_regmap_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	वापस tcan4x5x_regmap_gather_ग_लिखो(context, data, माप(__be32),
					    data + माप(__be32),
					    count - माप(__be32));
पूर्ण

अटल पूर्णांक tcan4x5x_regmap_पढ़ो(व्योम *context,
				स्थिर व्योम *reg_buf, माप_प्रकार reg_len,
				व्योम *val_buf, माप_प्रकार val_len)
अणु
	काष्ठा spi_device *spi = context;
	काष्ठा tcan4x5x_priv *priv = spi_get_drvdata(spi);
	काष्ठा tcan4x5x_map_buf *buf_rx = &priv->map_buf_rx;
	काष्ठा tcan4x5x_map_buf *buf_tx = &priv->map_buf_tx;
	काष्ठा spi_transfer xfer[2] = अणु
		अणु
			.tx_buf = buf_tx,
		पूर्ण
	पूर्ण;
	काष्ठा spi_message msg;
	पूर्णांक err;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer[0], &msg);

	स_नकल(&buf_tx->cmd, reg_buf, माप(buf_tx->cmd.cmd) +
	       माप(buf_tx->cmd.addr));
	tcan4x5x_spi_cmd_set_len(&buf_tx->cmd, val_len);

	अगर (spi->controller->flags & SPI_CONTROLLER_HALF_DUPLEX) अणु
		xfer[0].len = माप(buf_tx->cmd);

		xfer[1].rx_buf = val_buf;
		xfer[1].len = val_len;
		spi_message_add_tail(&xfer[1], &msg);
	पूर्ण अन्यथा अणु
		xfer[0].rx_buf = buf_rx;
		xfer[0].len = माप(buf_tx->cmd) + val_len;

		अगर (TCAN4X5X_SANITIZE_SPI)
			स_रखो(buf_tx->data, 0x0, val_len);
	पूर्ण

	err = spi_sync(spi, &msg);
	अगर (err)
		वापस err;

	अगर (!(spi->controller->flags & SPI_CONTROLLER_HALF_DUPLEX))
		स_नकल(val_buf, buf_rx->data, val_len);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_range tcan4x5x_reg_table_yes_range[] = अणु
	regmap_reg_range(0x0000, 0x002c),	/* Device ID and SPI Registers */
	regmap_reg_range(0x0800, 0x083c),	/* Device configuration रेजिस्टरs and Interrupt Flags*/
	regmap_reg_range(0x1000, 0x10fc),	/* M_CAN */
	regmap_reg_range(0x8000, 0x87fc),	/* MRAM */
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table tcan4x5x_reg_table = अणु
	.yes_ranges = tcan4x5x_reg_table_yes_range,
	.n_yes_ranges = ARRAY_SIZE(tcan4x5x_reg_table_yes_range),
पूर्ण;

अटल स्थिर काष्ठा regmap_config tcan4x5x_regmap = अणु
	.reg_bits = 24,
	.reg_stride = 4,
	.pad_bits = 8,
	.val_bits = 32,
	.wr_table = &tcan4x5x_reg_table,
	.rd_table = &tcan4x5x_reg_table,
	.max_रेजिस्टर = TCAN4X5X_MAX_REGISTER,
	.cache_type = REGCACHE_NONE,
	.पढ़ो_flag_mask = (__क्रमce अचिन्हित दीर्घ)
		cpu_to_be32(TCAN4X5X_SPI_INSTRUCTION_READ),
	.ग_लिखो_flag_mask = (__क्रमce अचिन्हित दीर्घ)
		cpu_to_be32(TCAN4X5X_SPI_INSTRUCTION_WRITE),
पूर्ण;

अटल स्थिर काष्ठा regmap_bus tcan4x5x_bus = अणु
	.ग_लिखो = tcan4x5x_regmap_ग_लिखो,
	.gather_ग_लिखो = tcan4x5x_regmap_gather_ग_लिखो,
	.पढ़ो = tcan4x5x_regmap_पढ़ो,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
	.max_raw_पढ़ो = 256,
	.max_raw_ग_लिखो = 256,
पूर्ण;

पूर्णांक tcan4x5x_regmap_init(काष्ठा tcan4x5x_priv *priv)
अणु
	priv->regmap = devm_regmap_init(&priv->spi->dev, &tcan4x5x_bus,
					priv->spi, &tcan4x5x_regmap);
	वापस PTR_ERR_OR_ZERO(priv->regmap);
पूर्ण
