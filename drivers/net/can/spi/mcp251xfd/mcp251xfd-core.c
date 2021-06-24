<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mcp251xfd - Microchip MCP251xFD Family CAN controller driver
//
// Copyright (c) 2019, 2020, 2021 Pengutronix,
//               Marc Kleine-Budde <kernel@pengutronix.de>
//
// Based on:
//
// CAN bus driver क्रम Microchip 25XXFD CAN Controller with SPI Interface
//
// Copyright (c) 2019 Martin Sperl <kernel@martin.sperl.org>
//

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <यंत्र/unaligned.h>

#समावेश "mcp251xfd.h"

#घोषणा DEVICE_NAME "mcp251xfd"

अटल स्थिर काष्ठा mcp251xfd_devtype_data mcp251xfd_devtype_data_mcp2517fd = अणु
	.quirks = MCP251XFD_QUIRK_MAB_NO_WARN | MCP251XFD_QUIRK_CRC_REG |
		MCP251XFD_QUIRK_CRC_RX | MCP251XFD_QUIRK_CRC_TX |
		MCP251XFD_QUIRK_ECC,
	.model = MCP251XFD_MODEL_MCP2517FD,
पूर्ण;

अटल स्थिर काष्ठा mcp251xfd_devtype_data mcp251xfd_devtype_data_mcp2518fd = अणु
	.quirks = MCP251XFD_QUIRK_CRC_REG | MCP251XFD_QUIRK_CRC_RX |
		MCP251XFD_QUIRK_CRC_TX | MCP251XFD_QUIRK_ECC,
	.model = MCP251XFD_MODEL_MCP2518FD,
पूर्ण;

/* Autodetect model, start with CRC enabled. */
अटल स्थिर काष्ठा mcp251xfd_devtype_data mcp251xfd_devtype_data_mcp251xfd = अणु
	.quirks = MCP251XFD_QUIRK_CRC_REG | MCP251XFD_QUIRK_CRC_RX |
		MCP251XFD_QUIRK_CRC_TX | MCP251XFD_QUIRK_ECC,
	.model = MCP251XFD_MODEL_MCP251XFD,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर mcp251xfd_bittiming_स्थिर = अणु
	.name = DEVICE_NAME,
	.tseg1_min = 2,
	.tseg1_max = 256,
	.tseg2_min = 1,
	.tseg2_max = 128,
	.sjw_max = 128,
	.brp_min = 1,
	.brp_max = 256,
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर mcp251xfd_data_bittiming_स्थिर = अणु
	.name = DEVICE_NAME,
	.tseg1_min = 1,
	.tseg1_max = 32,
	.tseg2_min = 1,
	.tseg2_max = 16,
	.sjw_max = 16,
	.brp_min = 1,
	.brp_max = 256,
	.brp_inc = 1,
पूर्ण;

अटल स्थिर अक्षर *__mcp251xfd_get_model_str(क्रमागत mcp251xfd_model model)
अणु
	चयन (model) अणु
	हाल MCP251XFD_MODEL_MCP2517FD:
		वापस "MCP2517FD";
	हाल MCP251XFD_MODEL_MCP2518FD:
		वापस "MCP2518FD";
	हाल MCP251XFD_MODEL_MCP251XFD:
		वापस "MCP251xFD";
	पूर्ण

	वापस "<unknown>";
पूर्ण

अटल अंतरभूत स्थिर अक्षर *
mcp251xfd_get_model_str(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	वापस __mcp251xfd_get_model_str(priv->devtype_data.model);
पूर्ण

अटल स्थिर अक्षर *mcp251xfd_get_mode_str(स्थिर u8 mode)
अणु
	चयन (mode) अणु
	हाल MCP251XFD_REG_CON_MODE_MIXED:
		वापस "Mixed (CAN FD/CAN 2.0)";
	हाल MCP251XFD_REG_CON_MODE_SLEEP:
		वापस "Sleep";
	हाल MCP251XFD_REG_CON_MODE_INT_LOOPBACK:
		वापस "Internal Loopback";
	हाल MCP251XFD_REG_CON_MODE_LISTENONLY:
		वापस "Listen Only";
	हाल MCP251XFD_REG_CON_MODE_CONFIG:
		वापस "Configuration";
	हाल MCP251XFD_REG_CON_MODE_EXT_LOOPBACK:
		वापस "External Loopback";
	हाल MCP251XFD_REG_CON_MODE_CAN2_0:
		वापस "CAN 2.0";
	हाल MCP251XFD_REG_CON_MODE_RESTRICTED:
		वापस "Restricted Operation";
	पूर्ण

	वापस "<unknown>";
पूर्ण

अटल अंतरभूत पूर्णांक mcp251xfd_vdd_enable(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	अगर (!priv->reg_vdd)
		वापस 0;

	वापस regulator_enable(priv->reg_vdd);
पूर्ण

अटल अंतरभूत पूर्णांक mcp251xfd_vdd_disable(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	अगर (!priv->reg_vdd)
		वापस 0;

	वापस regulator_disable(priv->reg_vdd);
पूर्ण

अटल अंतरभूत पूर्णांक
mcp251xfd_transceiver_enable(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	अगर (!priv->reg_xceiver)
		वापस 0;

	वापस regulator_enable(priv->reg_xceiver);
पूर्ण

अटल अंतरभूत पूर्णांक
mcp251xfd_transceiver_disable(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	अगर (!priv->reg_xceiver)
		वापस 0;

	वापस regulator_disable(priv->reg_xceiver);
पूर्ण

अटल पूर्णांक mcp251xfd_clks_and_vdd_enable(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	पूर्णांक err;

	err = clk_prepare_enable(priv->clk);
	अगर (err)
		वापस err;

	err = mcp251xfd_vdd_enable(priv);
	अगर (err)
		clk_disable_unprepare(priv->clk);

	/* Wait क्रम oscillator stabilisation समय after घातer up */
	usleep_range(MCP251XFD_OSC_STAB_SLEEP_US,
		     2 * MCP251XFD_OSC_STAB_SLEEP_US);

	वापस err;
पूर्ण

अटल पूर्णांक mcp251xfd_clks_and_vdd_disable(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	पूर्णांक err;

	err = mcp251xfd_vdd_disable(priv);
	अगर (err)
		वापस err;

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल अंतरभूत u8
mcp251xfd_cmd_prepare_ग_लिखो_reg(स्थिर काष्ठा mcp251xfd_priv *priv,
				जोड़ mcp251xfd_ग_लिखो_reg_buf *ग_लिखो_reg_buf,
				स्थिर u16 reg, स्थिर u32 mask, स्थिर u32 val)
अणु
	u8 first_byte, last_byte, len;
	u8 *data;
	__le32 val_le32;

	first_byte = mcp251xfd_first_byte_set(mask);
	last_byte = mcp251xfd_last_byte_set(mask);
	len = last_byte - first_byte + 1;

	data = mcp251xfd_spi_cmd_ग_लिखो(priv, ग_लिखो_reg_buf, reg + first_byte);
	val_le32 = cpu_to_le32(val >> BITS_PER_BYTE * first_byte);
	स_नकल(data, &val_le32, len);

	अगर (priv->devtype_data.quirks & MCP251XFD_QUIRK_CRC_REG) अणु
		u16 crc;

		mcp251xfd_spi_cmd_crc_set_len_in_reg(&ग_लिखो_reg_buf->crc.cmd,
						     len);
		/* CRC */
		len += माप(ग_लिखो_reg_buf->crc.cmd);
		crc = mcp251xfd_crc16_compute(&ग_लिखो_reg_buf->crc, len);
		put_unaligned_be16(crc, (व्योम *)ग_लिखो_reg_buf + len);

		/* Total length */
		len += माप(ग_लिखो_reg_buf->crc.crc);
	पूर्ण अन्यथा अणु
		len += माप(ग_लिखो_reg_buf->nocrc.cmd);
	पूर्ण

	वापस len;
पूर्ण

अटल अंतरभूत पूर्णांक
mcp251xfd_tef_tail_get_from_chip(स्थिर काष्ठा mcp251xfd_priv *priv,
				 u8 *tef_tail)
अणु
	u32 tef_ua;
	पूर्णांक err;

	err = regmap_पढ़ो(priv->map_reg, MCP251XFD_REG_TEFUA, &tef_ua);
	अगर (err)
		वापस err;

	*tef_tail = tef_ua / माप(काष्ठा mcp251xfd_hw_tef_obj);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
mcp251xfd_tx_tail_get_from_chip(स्थिर काष्ठा mcp251xfd_priv *priv,
				u8 *tx_tail)
अणु
	u32 fअगरo_sta;
	पूर्णांक err;

	err = regmap_पढ़ो(priv->map_reg,
			  MCP251XFD_REG_FIFOSTA(MCP251XFD_TX_FIFO),
			  &fअगरo_sta);
	अगर (err)
		वापस err;

	*tx_tail = FIELD_GET(MCP251XFD_REG_FIFOSTA_FIFOCI_MASK, fअगरo_sta);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
mcp251xfd_rx_head_get_from_chip(स्थिर काष्ठा mcp251xfd_priv *priv,
				स्थिर काष्ठा mcp251xfd_rx_ring *ring,
				u8 *rx_head)
अणु
	u32 fअगरo_sta;
	पूर्णांक err;

	err = regmap_पढ़ो(priv->map_reg, MCP251XFD_REG_FIFOSTA(ring->fअगरo_nr),
			  &fअगरo_sta);
	अगर (err)
		वापस err;

	*rx_head = FIELD_GET(MCP251XFD_REG_FIFOSTA_FIFOCI_MASK, fअगरo_sta);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
mcp251xfd_rx_tail_get_from_chip(स्थिर काष्ठा mcp251xfd_priv *priv,
				स्थिर काष्ठा mcp251xfd_rx_ring *ring,
				u8 *rx_tail)
अणु
	u32 fअगरo_ua;
	पूर्णांक err;

	err = regmap_पढ़ो(priv->map_reg, MCP251XFD_REG_FIFOUA(ring->fअगरo_nr),
			  &fअगरo_ua);
	अगर (err)
		वापस err;

	fअगरo_ua -= ring->base - MCP251XFD_RAM_START;
	*rx_tail = fअगरo_ua / ring->obj_size;

	वापस 0;
पूर्ण

अटल व्योम
mcp251xfd_tx_ring_init_tx_obj(स्थिर काष्ठा mcp251xfd_priv *priv,
			      स्थिर काष्ठा mcp251xfd_tx_ring *ring,
			      काष्ठा mcp251xfd_tx_obj *tx_obj,
			      स्थिर u8 rts_buf_len,
			      स्थिर u8 n)
अणु
	काष्ठा spi_transfer *xfer;
	u16 addr;

	/* FIFO load */
	addr = mcp251xfd_get_tx_obj_addr(ring, n);
	अगर (priv->devtype_data.quirks & MCP251XFD_QUIRK_CRC_TX)
		mcp251xfd_spi_cmd_ग_लिखो_crc_set_addr(&tx_obj->buf.crc.cmd,
						     addr);
	अन्यथा
		mcp251xfd_spi_cmd_ग_लिखो_nocrc(&tx_obj->buf.nocrc.cmd,
					      addr);

	xfer = &tx_obj->xfer[0];
	xfer->tx_buf = &tx_obj->buf;
	xfer->len = 0;	/* actual len is asचिन्हित on the fly */
	xfer->cs_change = 1;
	xfer->cs_change_delay.value = 0;
	xfer->cs_change_delay.unit = SPI_DELAY_UNIT_NSECS;

	/* FIFO request to send */
	xfer = &tx_obj->xfer[1];
	xfer->tx_buf = &ring->rts_buf;
	xfer->len = rts_buf_len;

	/* SPI message */
	spi_message_init_with_transfers(&tx_obj->msg, tx_obj->xfer,
					ARRAY_SIZE(tx_obj->xfer));
पूर्ण

अटल व्योम mcp251xfd_ring_init(काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा mcp251xfd_tef_ring *tef_ring;
	काष्ठा mcp251xfd_tx_ring *tx_ring;
	काष्ठा mcp251xfd_rx_ring *rx_ring, *prev_rx_ring = शून्य;
	काष्ठा mcp251xfd_tx_obj *tx_obj;
	काष्ठा spi_transfer *xfer;
	u32 val;
	u16 addr;
	u8 len;
	पूर्णांक i, j;

	netdev_reset_queue(priv->ndev);

	/* TEF */
	tef_ring = priv->tef;
	tef_ring->head = 0;
	tef_ring->tail = 0;

	/* FIFO increment TEF tail poपूर्णांकer */
	addr = MCP251XFD_REG_TEFCON;
	val = MCP251XFD_REG_TEFCON_UINC;
	len = mcp251xfd_cmd_prepare_ग_लिखो_reg(priv, &tef_ring->uinc_buf,
					      addr, val, val);

	क्रम (j = 0; j < ARRAY_SIZE(tef_ring->uinc_xfer); j++) अणु
		xfer = &tef_ring->uinc_xfer[j];
		xfer->tx_buf = &tef_ring->uinc_buf;
		xfer->len = len;
		xfer->cs_change = 1;
		xfer->cs_change_delay.value = 0;
		xfer->cs_change_delay.unit = SPI_DELAY_UNIT_NSECS;
	पूर्ण

	/* "cs_change == 1" on the last transfer results in an active
	 * chip select after the complete SPI message. This causes the
	 * controller to पूर्णांकerpret the next रेजिस्टर access as
	 * data. Set "cs_change" of the last transfer to "0" to
	 * properly deactivate the chip select at the end of the
	 * message.
	 */
	xfer->cs_change = 0;

	/* TX */
	tx_ring = priv->tx;
	tx_ring->head = 0;
	tx_ring->tail = 0;
	tx_ring->base = mcp251xfd_get_tef_obj_addr(tx_ring->obj_num);

	/* FIFO request to send */
	addr = MCP251XFD_REG_FIFOCON(MCP251XFD_TX_FIFO);
	val = MCP251XFD_REG_FIFOCON_TXREQ | MCP251XFD_REG_FIFOCON_UINC;
	len = mcp251xfd_cmd_prepare_ग_लिखो_reg(priv, &tx_ring->rts_buf,
					      addr, val, val);

	mcp251xfd_क्रम_each_tx_obj(tx_ring, tx_obj, i)
		mcp251xfd_tx_ring_init_tx_obj(priv, tx_ring, tx_obj, len, i);

	/* RX */
	mcp251xfd_क्रम_each_rx_ring(priv, rx_ring, i) अणु
		rx_ring->head = 0;
		rx_ring->tail = 0;
		rx_ring->nr = i;
		rx_ring->fअगरo_nr = MCP251XFD_RX_FIFO(i);

		अगर (!prev_rx_ring)
			rx_ring->base =
				mcp251xfd_get_tx_obj_addr(tx_ring,
							  tx_ring->obj_num);
		अन्यथा
			rx_ring->base = prev_rx_ring->base +
				prev_rx_ring->obj_size *
				prev_rx_ring->obj_num;

		prev_rx_ring = rx_ring;

		/* FIFO increment RX tail poपूर्णांकer */
		addr = MCP251XFD_REG_FIFOCON(rx_ring->fअगरo_nr);
		val = MCP251XFD_REG_FIFOCON_UINC;
		len = mcp251xfd_cmd_prepare_ग_लिखो_reg(priv, &rx_ring->uinc_buf,
						      addr, val, val);

		क्रम (j = 0; j < ARRAY_SIZE(rx_ring->uinc_xfer); j++) अणु
			xfer = &rx_ring->uinc_xfer[j];
			xfer->tx_buf = &rx_ring->uinc_buf;
			xfer->len = len;
			xfer->cs_change = 1;
			xfer->cs_change_delay.value = 0;
			xfer->cs_change_delay.unit = SPI_DELAY_UNIT_NSECS;
		पूर्ण

		/* "cs_change == 1" on the last transfer results in an
		 * active chip select after the complete SPI
		 * message. This causes the controller to पूर्णांकerpret
		 * the next रेजिस्टर access as data. Set "cs_change"
		 * of the last transfer to "0" to properly deactivate
		 * the chip select at the end of the message.
		 */
		xfer->cs_change = 0;
	पूर्ण
पूर्ण

अटल व्योम mcp251xfd_ring_मुक्त(काष्ठा mcp251xfd_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(priv->rx) - 1; i >= 0; i--) अणु
		kमुक्त(priv->rx[i]);
		priv->rx[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mcp251xfd_ring_alloc(काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा mcp251xfd_tx_ring *tx_ring;
	काष्ठा mcp251xfd_rx_ring *rx_ring;
	पूर्णांक tef_obj_size, tx_obj_size, rx_obj_size;
	पूर्णांक tx_obj_num;
	पूर्णांक ram_मुक्त, i;

	tef_obj_size = माप(काष्ठा mcp251xfd_hw_tef_obj);
	/* listen-only mode works like FD mode */
	अगर (priv->can.ctrlmode & (CAN_CTRLMODE_LISTENONLY | CAN_CTRLMODE_FD)) अणु
		tx_obj_num = MCP251XFD_TX_OBJ_NUM_CANFD;
		tx_obj_size = माप(काष्ठा mcp251xfd_hw_tx_obj_canfd);
		rx_obj_size = माप(काष्ठा mcp251xfd_hw_rx_obj_canfd);
	पूर्ण अन्यथा अणु
		tx_obj_num = MCP251XFD_TX_OBJ_NUM_CAN;
		tx_obj_size = माप(काष्ठा mcp251xfd_hw_tx_obj_can);
		rx_obj_size = माप(काष्ठा mcp251xfd_hw_rx_obj_can);
	पूर्ण

	tx_ring = priv->tx;
	tx_ring->obj_num = tx_obj_num;
	tx_ring->obj_size = tx_obj_size;

	ram_मुक्त = MCP251XFD_RAM_SIZE - tx_obj_num *
		(tef_obj_size + tx_obj_size);

	क्रम (i = 0;
	     i < ARRAY_SIZE(priv->rx) && ram_मुक्त >= rx_obj_size;
	     i++) अणु
		पूर्णांक rx_obj_num;

		rx_obj_num = ram_मुक्त / rx_obj_size;
		rx_obj_num = min(1 << (fls(rx_obj_num) - 1),
				 MCP251XFD_RX_OBJ_NUM_MAX);

		rx_ring = kzalloc(माप(*rx_ring) + rx_obj_size * rx_obj_num,
				  GFP_KERNEL);
		अगर (!rx_ring) अणु
			mcp251xfd_ring_मुक्त(priv);
			वापस -ENOMEM;
		पूर्ण
		rx_ring->obj_num = rx_obj_num;
		rx_ring->obj_size = rx_obj_size;
		priv->rx[i] = rx_ring;

		ram_मुक्त -= rx_ring->obj_num * rx_ring->obj_size;
	पूर्ण
	priv->rx_ring_num = i;

	netdev_dbg(priv->ndev,
		   "FIFO setup: TEF: %d*%d bytes = %d bytes, TX: %d*%d bytes = %d bytes\n",
		   tx_obj_num, tef_obj_size, tef_obj_size * tx_obj_num,
		   tx_obj_num, tx_obj_size, tx_obj_size * tx_obj_num);

	mcp251xfd_क्रम_each_rx_ring(priv, rx_ring, i) अणु
		netdev_dbg(priv->ndev,
			   "FIFO setup: RX-%d: %d*%d bytes = %d bytes\n",
			   i, rx_ring->obj_num, rx_ring->obj_size,
			   rx_ring->obj_size * rx_ring->obj_num);
	पूर्ण

	netdev_dbg(priv->ndev,
		   "FIFO setup: free: %d bytes\n",
		   ram_मुक्त);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
mcp251xfd_chip_get_mode(स्थिर काष्ठा mcp251xfd_priv *priv, u8 *mode)
अणु
	u32 val;
	पूर्णांक err;

	err = regmap_पढ़ो(priv->map_reg, MCP251XFD_REG_CON, &val);
	अगर (err)
		वापस err;

	*mode = FIELD_GET(MCP251XFD_REG_CON_OPMOD_MASK, val);

	वापस 0;
पूर्ण

अटल पूर्णांक
__mcp251xfd_chip_set_mode(स्थिर काष्ठा mcp251xfd_priv *priv,
			  स्थिर u8 mode_req, bool noरुको)
अणु
	u32 con, con_reqop;
	पूर्णांक err;

	con_reqop = FIELD_PREP(MCP251XFD_REG_CON_REQOP_MASK, mode_req);
	err = regmap_update_bits(priv->map_reg, MCP251XFD_REG_CON,
				 MCP251XFD_REG_CON_REQOP_MASK, con_reqop);
	अगर (err)
		वापस err;

	अगर (mode_req == MCP251XFD_REG_CON_MODE_SLEEP || noरुको)
		वापस 0;

	err = regmap_पढ़ो_poll_समयout(priv->map_reg, MCP251XFD_REG_CON, con,
				       FIELD_GET(MCP251XFD_REG_CON_OPMOD_MASK,
						 con) == mode_req,
				       MCP251XFD_POLL_SLEEP_US,
				       MCP251XFD_POLL_TIMEOUT_US);
	अगर (err) अणु
		u8 mode = FIELD_GET(MCP251XFD_REG_CON_OPMOD_MASK, con);

		netdev_err(priv->ndev,
			   "Controller failed to enter mode %s Mode (%u) and stays in %s Mode (%u).\n",
			   mcp251xfd_get_mode_str(mode_req), mode_req,
			   mcp251xfd_get_mode_str(mode), mode);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
mcp251xfd_chip_set_mode(स्थिर काष्ठा mcp251xfd_priv *priv,
			स्थिर u8 mode_req)
अणु
	वापस __mcp251xfd_chip_set_mode(priv, mode_req, false);
पूर्ण

अटल अंतरभूत पूर्णांक
mcp251xfd_chip_set_mode_noरुको(स्थिर काष्ठा mcp251xfd_priv *priv,
			       स्थिर u8 mode_req)
अणु
	वापस __mcp251xfd_chip_set_mode(priv, mode_req, true);
पूर्ण

अटल अंतरभूत bool mcp251xfd_osc_invalid(u32 reg)
अणु
	वापस reg == 0x0 || reg == 0xffffffff;
पूर्ण

अटल पूर्णांक mcp251xfd_chip_घड़ी_enable(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	u32 osc, osc_reference, osc_mask;
	पूर्णांक err;

	/* Set Power On Defaults क्रम "Clock Output Divisor" and हटाओ
	 * "Oscillator Disable" bit.
	 */
	osc = FIELD_PREP(MCP251XFD_REG_OSC_CLKODIV_MASK,
			 MCP251XFD_REG_OSC_CLKODIV_10);
	osc_reference = MCP251XFD_REG_OSC_OSCRDY;
	osc_mask = MCP251XFD_REG_OSC_OSCRDY | MCP251XFD_REG_OSC_PLLRDY;

	/* Note:
	 *
	 * If the controller is in Sleep Mode the following ग_लिखो only
	 * हटाओs the "Oscillator Disable" bit and घातers it up. All
	 * other bits are unaffected.
	 */
	err = regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_OSC, osc);
	अगर (err)
		वापस err;

	/* Wait क्रम "Oscillator Ready" bit */
	err = regmap_पढ़ो_poll_समयout(priv->map_reg, MCP251XFD_REG_OSC, osc,
				       (osc & osc_mask) == osc_reference,
				       MCP251XFD_OSC_STAB_SLEEP_US,
				       MCP251XFD_OSC_STAB_TIMEOUT_US);
	अगर (mcp251xfd_osc_invalid(osc)) अणु
		netdev_err(priv->ndev,
			   "Failed to detect %s (osc=0x%08x).\n",
			   mcp251xfd_get_model_str(priv), osc);
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (err == -ETIMEDOUT) अणु
		netdev_err(priv->ndev,
			   "Timeout waiting for Oscillator Ready (osc=0x%08x, osc_reference=0x%08x)\n",
			   osc, osc_reference);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mcp251xfd_chip_softreset_करो(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	स्थिर __be16 cmd = mcp251xfd_cmd_reset();
	पूर्णांक err;

	/* The Set Mode and SPI Reset command only seems to works अगर
	 * the controller is not in Sleep Mode.
	 */
	err = mcp251xfd_chip_घड़ी_enable(priv);
	अगर (err)
		वापस err;

	err = mcp251xfd_chip_set_mode(priv, MCP251XFD_REG_CON_MODE_CONFIG);
	अगर (err)
		वापस err;

	/* spi_ग_लिखो_then_पढ़ो() works with non DMA-safe buffers */
	वापस spi_ग_लिखो_then_पढ़ो(priv->spi, &cmd, माप(cmd), शून्य, 0);
पूर्ण

अटल पूर्णांक mcp251xfd_chip_softreset_check(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	u32 osc, osc_reference;
	u8 mode;
	पूर्णांक err;

	err = mcp251xfd_chip_get_mode(priv, &mode);
	अगर (err)
		वापस err;

	अगर (mode != MCP251XFD_REG_CON_MODE_CONFIG) अणु
		netdev_info(priv->ndev,
			    "Controller not in Config Mode after reset, but in %s Mode (%u).\n",
			    mcp251xfd_get_mode_str(mode), mode);
		वापस -ETIMEDOUT;
	पूर्ण

	osc_reference = MCP251XFD_REG_OSC_OSCRDY |
		FIELD_PREP(MCP251XFD_REG_OSC_CLKODIV_MASK,
			   MCP251XFD_REG_OSC_CLKODIV_10);

	/* check reset शेषs of OSC reg */
	err = regmap_पढ़ो(priv->map_reg, MCP251XFD_REG_OSC, &osc);
	अगर (err)
		वापस err;

	अगर (osc != osc_reference) अणु
		netdev_info(priv->ndev,
			    "Controller failed to reset. osc=0x%08x, reference value=0x%08x.\n",
			    osc, osc_reference);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mcp251xfd_chip_softreset(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < MCP251XFD_SOFTRESET_RETRIES_MAX; i++) अणु
		अगर (i)
			netdev_info(priv->ndev,
				    "Retrying to reset controller.\n");

		err = mcp251xfd_chip_softreset_करो(priv);
		अगर (err == -ETIMEDOUT)
			जारी;
		अगर (err)
			वापस err;

		err = mcp251xfd_chip_softreset_check(priv);
		अगर (err == -ETIMEDOUT)
			जारी;
		अगर (err)
			वापस err;

		वापस 0;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mcp251xfd_chip_घड़ी_init(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	u32 osc;
	पूर्णांक err;

	/* Activate Low Power Mode on Oscillator Disable. This only
	 * works on the MCP2518FD. The MCP2517FD will go पूर्णांकo normal
	 * Sleep Mode instead.
	 */
	osc = MCP251XFD_REG_OSC_LPMEN |
		FIELD_PREP(MCP251XFD_REG_OSC_CLKODIV_MASK,
			   MCP251XFD_REG_OSC_CLKODIV_10);
	err = regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_OSC, osc);
	अगर (err)
		वापस err;

	/* Set Time Base Counter Prescaler to 1.
	 *
	 * This means an overflow of the 32 bit Time Base Counter
	 * रेजिस्टर at 40 MHz every 107 seconds.
	 */
	वापस regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_TSCON,
			    MCP251XFD_REG_TSCON_TBCEN);
पूर्ण

अटल पूर्णांक mcp251xfd_set_bittiming(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	स्थिर काष्ठा can_bittiming *bt = &priv->can.bittiming;
	स्थिर काष्ठा can_bittiming *dbt = &priv->can.data_bittiming;
	u32 val = 0;
	s8 tdco;
	पूर्णांक err;

	/* CAN Control Register
	 *
	 * - no transmit bandwidth sharing
	 * - config mode
	 * - disable transmit queue
	 * - store in transmit FIFO event
	 * - transition to restricted operation mode on प्रणाली error
	 * - ESI is transmitted recessive when ESI of message is high or
	 *   CAN controller error passive
	 * - restricted retransmission attempts,
	 *   use TQXCON_TXAT and FIFOCON_TXAT
	 * - wake-up filter bits T11FILTER
	 * - use CAN bus line filter क्रम wakeup
	 * - protocol exception is treated as a क्रमm error
	 * - Do not compare data bytes
	 */
	val = FIELD_PREP(MCP251XFD_REG_CON_REQOP_MASK,
			 MCP251XFD_REG_CON_MODE_CONFIG) |
		MCP251XFD_REG_CON_STEF |
		MCP251XFD_REG_CON_ESIGM |
		MCP251XFD_REG_CON_RTXAT |
		FIELD_PREP(MCP251XFD_REG_CON_WFT_MASK,
			   MCP251XFD_REG_CON_WFT_T11FILTER) |
		MCP251XFD_REG_CON_WAKFIL |
		MCP251XFD_REG_CON_PXEDIS;

	अगर (!(priv->can.ctrlmode & CAN_CTRLMODE_FD_NON_ISO))
		val |= MCP251XFD_REG_CON_ISOCRCEN;

	err = regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_CON, val);
	अगर (err)
		वापस err;

	/* Nominal Bit Time */
	val = FIELD_PREP(MCP251XFD_REG_NBTCFG_BRP_MASK, bt->brp - 1) |
		FIELD_PREP(MCP251XFD_REG_NBTCFG_TSEG1_MASK,
			   bt->prop_seg + bt->phase_seg1 - 1) |
		FIELD_PREP(MCP251XFD_REG_NBTCFG_TSEG2_MASK,
			   bt->phase_seg2 - 1) |
		FIELD_PREP(MCP251XFD_REG_NBTCFG_SJW_MASK, bt->sjw - 1);

	err = regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_NBTCFG, val);
	अगर (err)
		वापस err;

	अगर (!(priv->can.ctrlmode & CAN_CTRLMODE_FD))
		वापस 0;

	/* Data Bit Time */
	val = FIELD_PREP(MCP251XFD_REG_DBTCFG_BRP_MASK, dbt->brp - 1) |
		FIELD_PREP(MCP251XFD_REG_DBTCFG_TSEG1_MASK,
			   dbt->prop_seg + dbt->phase_seg1 - 1) |
		FIELD_PREP(MCP251XFD_REG_DBTCFG_TSEG2_MASK,
			   dbt->phase_seg2 - 1) |
		FIELD_PREP(MCP251XFD_REG_DBTCFG_SJW_MASK, dbt->sjw - 1);

	err = regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_DBTCFG, val);
	अगर (err)
		वापस err;

	/* Transmitter Delay Compensation */
	tdco = clamp_t(पूर्णांक, dbt->brp * (dbt->prop_seg + dbt->phase_seg1),
		       -64, 63);
	val = FIELD_PREP(MCP251XFD_REG_TDC_TDCMOD_MASK,
			 MCP251XFD_REG_TDC_TDCMOD_AUTO) |
		FIELD_PREP(MCP251XFD_REG_TDC_TDCO_MASK, tdco);

	वापस regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_TDC, val);
पूर्ण

अटल पूर्णांक mcp251xfd_chip_rx_पूर्णांक_enable(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	u32 val;

	अगर (!priv->rx_पूर्णांक)
		वापस 0;

	/* Configure GPIOs:
	 * - PIN0: GPIO Input
	 * - PIN1: GPIO Input/RX Interrupt
	 *
	 * PIN1 must be Input, otherwise there is a glitch on the
	 * rx-INT line. It happens between setting the PIN as output
	 * (in the first byte of the SPI transfer) and configuring the
	 * PIN as पूर्णांकerrupt (in the last byte of the SPI transfer).
	 */
	val = MCP251XFD_REG_IOCON_PM0 | MCP251XFD_REG_IOCON_TRIS1 |
		MCP251XFD_REG_IOCON_TRIS0;
	वापस regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_IOCON, val);
पूर्ण

अटल पूर्णांक mcp251xfd_chip_rx_पूर्णांक_disable(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	u32 val;

	अगर (!priv->rx_पूर्णांक)
		वापस 0;

	/* Configure GPIOs:
	 * - PIN0: GPIO Input
	 * - PIN1: GPIO Input
	 */
	val = MCP251XFD_REG_IOCON_PM1 | MCP251XFD_REG_IOCON_PM0 |
		MCP251XFD_REG_IOCON_TRIS1 | MCP251XFD_REG_IOCON_TRIS0;
	वापस regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_IOCON, val);
पूर्ण

अटल पूर्णांक
mcp251xfd_chip_rx_fअगरo_init_one(स्थिर काष्ठा mcp251xfd_priv *priv,
				स्थिर काष्ठा mcp251xfd_rx_ring *ring)
अणु
	u32 fअगरo_con;

	/* Enable RXOVIE on _all_ RX FIFOs, not just the last one.
	 *
	 * FIFOs hit by a RX MAB overflow and RXOVIE enabled will
	 * generate a RXOVIF, use this to properly detect RX MAB
	 * overflows.
	 */
	fअगरo_con = FIELD_PREP(MCP251XFD_REG_FIFOCON_FSIZE_MASK,
			      ring->obj_num - 1) |
		MCP251XFD_REG_FIFOCON_RXTSEN |
		MCP251XFD_REG_FIFOCON_RXOVIE |
		MCP251XFD_REG_FIFOCON_TFNRFNIE;

	अगर (priv->can.ctrlmode & (CAN_CTRLMODE_LISTENONLY | CAN_CTRLMODE_FD))
		fअगरo_con |= FIELD_PREP(MCP251XFD_REG_FIFOCON_PLSIZE_MASK,
				       MCP251XFD_REG_FIFOCON_PLSIZE_64);
	अन्यथा
		fअगरo_con |= FIELD_PREP(MCP251XFD_REG_FIFOCON_PLSIZE_MASK,
				       MCP251XFD_REG_FIFOCON_PLSIZE_8);

	वापस regmap_ग_लिखो(priv->map_reg,
			    MCP251XFD_REG_FIFOCON(ring->fअगरo_nr), fअगरo_con);
पूर्ण

अटल पूर्णांक
mcp251xfd_chip_rx_filter_init_one(स्थिर काष्ठा mcp251xfd_priv *priv,
				  स्थिर काष्ठा mcp251xfd_rx_ring *ring)
अणु
	u32 fltcon;

	fltcon = MCP251XFD_REG_FLTCON_FLTEN(ring->nr) |
		MCP251XFD_REG_FLTCON_FBP(ring->nr, ring->fअगरo_nr);

	वापस regmap_update_bits(priv->map_reg,
				  MCP251XFD_REG_FLTCON(ring->nr >> 2),
				  MCP251XFD_REG_FLTCON_FLT_MASK(ring->nr),
				  fltcon);
पूर्ण

अटल पूर्णांक mcp251xfd_chip_fअगरo_init(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	स्थिर काष्ठा mcp251xfd_tx_ring *tx_ring = priv->tx;
	स्थिर काष्ठा mcp251xfd_rx_ring *rx_ring;
	u32 val;
	पूर्णांक err, n;

	/* TEF */
	val = FIELD_PREP(MCP251XFD_REG_TEFCON_FSIZE_MASK,
			 tx_ring->obj_num - 1) |
		MCP251XFD_REG_TEFCON_TEFTSEN |
		MCP251XFD_REG_TEFCON_TEFOVIE |
		MCP251XFD_REG_TEFCON_TEFNEIE;

	err = regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_TEFCON, val);
	अगर (err)
		वापस err;

	/* FIFO 1 - TX */
	val = FIELD_PREP(MCP251XFD_REG_FIFOCON_FSIZE_MASK,
			 tx_ring->obj_num - 1) |
		MCP251XFD_REG_FIFOCON_TXEN |
		MCP251XFD_REG_FIFOCON_TXATIE;

	अगर (priv->can.ctrlmode & (CAN_CTRLMODE_LISTENONLY | CAN_CTRLMODE_FD))
		val |= FIELD_PREP(MCP251XFD_REG_FIFOCON_PLSIZE_MASK,
				  MCP251XFD_REG_FIFOCON_PLSIZE_64);
	अन्यथा
		val |= FIELD_PREP(MCP251XFD_REG_FIFOCON_PLSIZE_MASK,
				  MCP251XFD_REG_FIFOCON_PLSIZE_8);

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		val |= FIELD_PREP(MCP251XFD_REG_FIFOCON_TXAT_MASK,
				  MCP251XFD_REG_FIFOCON_TXAT_ONE_SHOT);
	अन्यथा
		val |= FIELD_PREP(MCP251XFD_REG_FIFOCON_TXAT_MASK,
				  MCP251XFD_REG_FIFOCON_TXAT_UNLIMITED);

	err = regmap_ग_लिखो(priv->map_reg,
			   MCP251XFD_REG_FIFOCON(MCP251XFD_TX_FIFO),
			   val);
	अगर (err)
		वापस err;

	/* RX FIFOs */
	mcp251xfd_क्रम_each_rx_ring(priv, rx_ring, n) अणु
		err = mcp251xfd_chip_rx_fअगरo_init_one(priv, rx_ring);
		अगर (err)
			वापस err;

		err = mcp251xfd_chip_rx_filter_init_one(priv, rx_ring);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mcp251xfd_chip_ecc_init(काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा mcp251xfd_ecc *ecc = &priv->ecc;
	व्योम *ram;
	u32 val = 0;
	पूर्णांक err;

	ecc->ecc_stat = 0;

	अगर (priv->devtype_data.quirks & MCP251XFD_QUIRK_ECC)
		val = MCP251XFD_REG_ECCCON_ECCEN;

	err = regmap_update_bits(priv->map_reg, MCP251XFD_REG_ECCCON,
				 MCP251XFD_REG_ECCCON_ECCEN, val);
	अगर (err)
		वापस err;

	ram = kzalloc(MCP251XFD_RAM_SIZE, GFP_KERNEL);
	अगर (!ram)
		वापस -ENOMEM;

	err = regmap_raw_ग_लिखो(priv->map_reg, MCP251XFD_RAM_START, ram,
			       MCP251XFD_RAM_SIZE);
	kमुक्त(ram);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम mcp251xfd_ecc_tefअगर_successful(काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा mcp251xfd_ecc *ecc = &priv->ecc;

	ecc->ecc_stat = 0;
पूर्ण

अटल u8 mcp251xfd_get_normal_mode(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	u8 mode;


	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		mode = MCP251XFD_REG_CON_MODE_INT_LOOPBACK;
	अन्यथा अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		mode = MCP251XFD_REG_CON_MODE_LISTENONLY;
	अन्यथा अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD)
		mode = MCP251XFD_REG_CON_MODE_MIXED;
	अन्यथा
		mode = MCP251XFD_REG_CON_MODE_CAN2_0;

	वापस mode;
पूर्ण

अटल पूर्णांक
__mcp251xfd_chip_set_normal_mode(स्थिर काष्ठा mcp251xfd_priv *priv,
				 bool noरुको)
अणु
	u8 mode;

	mode = mcp251xfd_get_normal_mode(priv);

	वापस __mcp251xfd_chip_set_mode(priv, mode, noरुको);
पूर्ण

अटल अंतरभूत पूर्णांक
mcp251xfd_chip_set_normal_mode(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	वापस __mcp251xfd_chip_set_normal_mode(priv, false);
पूर्ण

अटल अंतरभूत पूर्णांक
mcp251xfd_chip_set_normal_mode_noरुको(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	वापस __mcp251xfd_chip_set_normal_mode(priv, true);
पूर्ण

अटल पूर्णांक mcp251xfd_chip_पूर्णांकerrupts_enable(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	u32 val;
	पूर्णांक err;

	val = MCP251XFD_REG_CRC_FERRIE | MCP251XFD_REG_CRC_CRCERRIE;
	err = regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_CRC, val);
	अगर (err)
		वापस err;

	val = MCP251XFD_REG_ECCCON_DEDIE | MCP251XFD_REG_ECCCON_SECIE;
	err = regmap_update_bits(priv->map_reg, MCP251XFD_REG_ECCCON, val, val);
	अगर (err)
		वापस err;

	val = MCP251XFD_REG_INT_CERRIE |
		MCP251XFD_REG_INT_SERRIE |
		MCP251XFD_REG_INT_RXOVIE |
		MCP251XFD_REG_INT_TXATIE |
		MCP251XFD_REG_INT_SPICRCIE |
		MCP251XFD_REG_INT_ECCIE |
		MCP251XFD_REG_INT_TEFIE |
		MCP251XFD_REG_INT_MODIE |
		MCP251XFD_REG_INT_RXIE;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING)
		val |= MCP251XFD_REG_INT_IVMIE;

	वापस regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_INT, val);
पूर्ण

अटल पूर्णांक mcp251xfd_chip_पूर्णांकerrupts_disable(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	पूर्णांक err;
	u32 mask;

	err = regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_INT, 0);
	अगर (err)
		वापस err;

	mask = MCP251XFD_REG_ECCCON_DEDIE | MCP251XFD_REG_ECCCON_SECIE;
	err = regmap_update_bits(priv->map_reg, MCP251XFD_REG_ECCCON,
				 mask, 0x0);
	अगर (err)
		वापस err;

	वापस regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_CRC, 0);
पूर्ण

अटल पूर्णांक mcp251xfd_chip_stop(काष्ठा mcp251xfd_priv *priv,
			       स्थिर क्रमागत can_state state)
अणु
	priv->can.state = state;

	mcp251xfd_chip_पूर्णांकerrupts_disable(priv);
	mcp251xfd_chip_rx_पूर्णांक_disable(priv);
	वापस mcp251xfd_chip_set_mode(priv, MCP251XFD_REG_CON_MODE_SLEEP);
पूर्ण

अटल पूर्णांक mcp251xfd_chip_start(काष्ठा mcp251xfd_priv *priv)
अणु
	पूर्णांक err;

	err = mcp251xfd_chip_softreset(priv);
	अगर (err)
		जाओ out_chip_stop;

	err = mcp251xfd_chip_घड़ी_init(priv);
	अगर (err)
		जाओ out_chip_stop;

	err = mcp251xfd_set_bittiming(priv);
	अगर (err)
		जाओ out_chip_stop;

	err = mcp251xfd_chip_rx_पूर्णांक_enable(priv);
	अगर (err)
		वापस err;

	err = mcp251xfd_chip_ecc_init(priv);
	अगर (err)
		जाओ out_chip_stop;

	mcp251xfd_ring_init(priv);

	err = mcp251xfd_chip_fअगरo_init(priv);
	अगर (err)
		जाओ out_chip_stop;

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	err = mcp251xfd_chip_set_normal_mode(priv);
	अगर (err)
		जाओ out_chip_stop;

	वापस 0;

 out_chip_stop:
	mcp251xfd_dump(priv);
	mcp251xfd_chip_stop(priv, CAN_STATE_STOPPED);

	वापस err;
पूर्ण

अटल पूर्णांक mcp251xfd_set_mode(काष्ठा net_device *ndev, क्रमागत can_mode mode)
अणु
	काष्ठा mcp251xfd_priv *priv = netdev_priv(ndev);
	पूर्णांक err;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		err = mcp251xfd_chip_start(priv);
		अगर (err)
			वापस err;

		err = mcp251xfd_chip_पूर्णांकerrupts_enable(priv);
		अगर (err) अणु
			mcp251xfd_chip_stop(priv, CAN_STATE_STOPPED);
			वापस err;
		पूर्ण

		netअगर_wake_queue(ndev);
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __mcp251xfd_get_berr_counter(स्थिर काष्ठा net_device *ndev,
					काष्ठा can_berr_counter *bec)
अणु
	स्थिर काष्ठा mcp251xfd_priv *priv = netdev_priv(ndev);
	u32 trec;
	पूर्णांक err;

	err = regmap_पढ़ो(priv->map_reg, MCP251XFD_REG_TREC, &trec);
	अगर (err)
		वापस err;

	अगर (trec & MCP251XFD_REG_TREC_TXBO)
		bec->txerr = 256;
	अन्यथा
		bec->txerr = FIELD_GET(MCP251XFD_REG_TREC_TEC_MASK, trec);
	bec->rxerr = FIELD_GET(MCP251XFD_REG_TREC_REC_MASK, trec);

	वापस 0;
पूर्ण

अटल पूर्णांक mcp251xfd_get_berr_counter(स्थिर काष्ठा net_device *ndev,
				      काष्ठा can_berr_counter *bec)
अणु
	स्थिर काष्ठा mcp251xfd_priv *priv = netdev_priv(ndev);

	/* Aव्योम waking up the controller अगर the पूर्णांकerface is करोwn */
	अगर (!(ndev->flags & IFF_UP))
		वापस 0;

	/* The controller is घातered करोwn during Bus Off, use saved
	 * bec values.
	 */
	अगर (priv->can.state == CAN_STATE_BUS_OFF) अणु
		*bec = priv->bec;
		वापस 0;
	पूर्ण

	वापस __mcp251xfd_get_berr_counter(ndev, bec);
पूर्ण

अटल पूर्णांक mcp251xfd_check_tef_tail(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	u8 tef_tail_chip, tef_tail;
	पूर्णांक err;

	अगर (!IS_ENABLED(CONFIG_CAN_MCP251XFD_SANITY))
		वापस 0;

	err = mcp251xfd_tef_tail_get_from_chip(priv, &tef_tail_chip);
	अगर (err)
		वापस err;

	tef_tail = mcp251xfd_get_tef_tail(priv);
	अगर (tef_tail_chip != tef_tail) अणु
		netdev_err(priv->ndev,
			   "TEF tail of chip (0x%02x) and ours (0x%08x) inconsistent.\n",
			   tef_tail_chip, tef_tail);
		वापस -EILSEQ;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mcp251xfd_check_rx_tail(स्थिर काष्ठा mcp251xfd_priv *priv,
			स्थिर काष्ठा mcp251xfd_rx_ring *ring)
अणु
	u8 rx_tail_chip, rx_tail;
	पूर्णांक err;

	अगर (!IS_ENABLED(CONFIG_CAN_MCP251XFD_SANITY))
		वापस 0;

	err = mcp251xfd_rx_tail_get_from_chip(priv, ring, &rx_tail_chip);
	अगर (err)
		वापस err;

	rx_tail = mcp251xfd_get_rx_tail(ring);
	अगर (rx_tail_chip != rx_tail) अणु
		netdev_err(priv->ndev,
			   "RX tail of chip (%d) and ours (%d) inconsistent.\n",
			   rx_tail_chip, rx_tail);
		वापस -EILSEQ;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mcp251xfd_handle_tefअगर_recover(स्थिर काष्ठा mcp251xfd_priv *priv, स्थिर u32 seq)
अणु
	स्थिर काष्ठा mcp251xfd_tx_ring *tx_ring = priv->tx;
	u32 tef_sta;
	पूर्णांक err;

	err = regmap_पढ़ो(priv->map_reg, MCP251XFD_REG_TEFSTA, &tef_sta);
	अगर (err)
		वापस err;

	अगर (tef_sta & MCP251XFD_REG_TEFSTA_TEFOVIF) अणु
		netdev_err(priv->ndev,
			   "Transmit Event FIFO buffer overflow.\n");
		वापस -ENOBUFS;
	पूर्ण

	netdev_info(priv->ndev,
		    "Transmit Event FIFO buffer %s. (seq=0x%08x, tef_tail=0x%08x, tef_head=0x%08x, tx_head=0x%08x).\n",
		    tef_sta & MCP251XFD_REG_TEFSTA_TEFFIF ?
		    "full" : tef_sta & MCP251XFD_REG_TEFSTA_TEFNEIF ?
		    "not empty" : "empty",
		    seq, priv->tef->tail, priv->tef->head, tx_ring->head);

	/* The Sequence Number in the TEF करोesn't match our tef_tail. */
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक
mcp251xfd_handle_tefअगर_one(काष्ठा mcp251xfd_priv *priv,
			   स्थिर काष्ठा mcp251xfd_hw_tef_obj *hw_tef_obj,
			   अचिन्हित पूर्णांक *frame_len_ptr)
अणु
	काष्ठा net_device_stats *stats = &priv->ndev->stats;
	काष्ठा sk_buff *skb;
	u32 seq, seq_masked, tef_tail_masked, tef_tail;

	seq = FIELD_GET(MCP251XFD_OBJ_FLAGS_SEQ_MCP2518FD_MASK,
			hw_tef_obj->flags);

	/* Use the MCP2517FD mask on the MCP2518FD, too. We only
	 * compare 7 bits, this should be enough to detect
	 * net-yet-completed, i.e. old TEF objects.
	 */
	seq_masked = seq &
		field_mask(MCP251XFD_OBJ_FLAGS_SEQ_MCP2517FD_MASK);
	tef_tail_masked = priv->tef->tail &
		field_mask(MCP251XFD_OBJ_FLAGS_SEQ_MCP2517FD_MASK);
	अगर (seq_masked != tef_tail_masked)
		वापस mcp251xfd_handle_tefअगर_recover(priv, seq);

	tef_tail = mcp251xfd_get_tef_tail(priv);
	skb = priv->can.echo_skb[tef_tail];
	अगर (skb)
		mcp251xfd_skb_set_बारtamp(priv, skb, hw_tef_obj->ts);
	stats->tx_bytes +=
		can_rx_offload_get_echo_skb(&priv->offload,
					    tef_tail, hw_tef_obj->ts,
					    frame_len_ptr);
	stats->tx_packets++;
	priv->tef->tail++;

	वापस 0;
पूर्ण

अटल पूर्णांक mcp251xfd_tef_ring_update(काष्ठा mcp251xfd_priv *priv)
अणु
	स्थिर काष्ठा mcp251xfd_tx_ring *tx_ring = priv->tx;
	अचिन्हित पूर्णांक new_head;
	u8 chip_tx_tail;
	पूर्णांक err;

	err = mcp251xfd_tx_tail_get_from_chip(priv, &chip_tx_tail);
	अगर (err)
		वापस err;

	/* chip_tx_tail, is the next TX-Object send by the HW.
	 * The new TEF head must be >= the old head, ...
	 */
	new_head = round_करोwn(priv->tef->head, tx_ring->obj_num) + chip_tx_tail;
	अगर (new_head <= priv->tef->head)
		new_head += tx_ring->obj_num;

	/* ... but it cannot exceed the TX head. */
	priv->tef->head = min(new_head, tx_ring->head);

	वापस mcp251xfd_check_tef_tail(priv);
पूर्ण

अटल अंतरभूत पूर्णांक
mcp251xfd_tef_obj_पढ़ो(स्थिर काष्ठा mcp251xfd_priv *priv,
		       काष्ठा mcp251xfd_hw_tef_obj *hw_tef_obj,
		       स्थिर u8 offset, स्थिर u8 len)
अणु
	स्थिर काष्ठा mcp251xfd_tx_ring *tx_ring = priv->tx;
	स्थिर पूर्णांक val_bytes = regmap_get_val_bytes(priv->map_rx);

	अगर (IS_ENABLED(CONFIG_CAN_MCP251XFD_SANITY) &&
	    (offset > tx_ring->obj_num ||
	     len > tx_ring->obj_num ||
	     offset + len > tx_ring->obj_num)) अणु
		netdev_err(priv->ndev,
			   "Trying to read to many TEF objects (max=%d, offset=%d, len=%d).\n",
			   tx_ring->obj_num, offset, len);
		वापस -दुस्फल;
	पूर्ण

	वापस regmap_bulk_पढ़ो(priv->map_rx,
				mcp251xfd_get_tef_obj_addr(offset),
				hw_tef_obj,
				माप(*hw_tef_obj) / val_bytes * len);
पूर्ण

अटल पूर्णांक mcp251xfd_handle_tefअगर(काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा mcp251xfd_hw_tef_obj hw_tef_obj[MCP251XFD_TX_OBJ_NUM_MAX];
	अचिन्हित पूर्णांक total_frame_len = 0;
	u8 tef_tail, len, l;
	पूर्णांक err, i;

	err = mcp251xfd_tef_ring_update(priv);
	अगर (err)
		वापस err;

	tef_tail = mcp251xfd_get_tef_tail(priv);
	len = mcp251xfd_get_tef_len(priv);
	l = mcp251xfd_get_tef_linear_len(priv);
	err = mcp251xfd_tef_obj_पढ़ो(priv, hw_tef_obj, tef_tail, l);
	अगर (err)
		वापस err;

	अगर (l < len) अणु
		err = mcp251xfd_tef_obj_पढ़ो(priv, &hw_tef_obj[l], 0, len - l);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		अचिन्हित पूर्णांक frame_len = 0;

		err = mcp251xfd_handle_tefअगर_one(priv, &hw_tef_obj[i], &frame_len);
		/* -EAGAIN means the Sequence Number in the TEF
		 * करोesn't match our tef_tail. This can happen अगर we
		 * पढ़ो the TEF objects too early. Leave loop let the
		 * पूर्णांकerrupt handler call us again.
		 */
		अगर (err == -EAGAIN)
			जाओ out_netअगर_wake_queue;
		अगर (err)
			वापस err;

		total_frame_len += frame_len;
	पूर्ण

 out_netअगर_wake_queue:
	len = i;	/* number of handled goods TEFs */
	अगर (len) अणु
		काष्ठा mcp251xfd_tef_ring *ring = priv->tef;
		काष्ठा mcp251xfd_tx_ring *tx_ring = priv->tx;
		पूर्णांक offset;

		/* Increment the TEF FIFO tail poपूर्णांकer 'len' बार in
		 * a single SPI message.
		 *
		 * Note:
		 * Calculate offset, so that the SPI transfer ends on
		 * the last message of the uinc_xfer array, which has
		 * "cs_change == 0", to properly deactivate the chip
		 * select.
		 */
		offset = ARRAY_SIZE(ring->uinc_xfer) - len;
		err = spi_sync_transfer(priv->spi,
					ring->uinc_xfer + offset, len);
		अगर (err)
			वापस err;

		tx_ring->tail += len;
		netdev_completed_queue(priv->ndev, len, total_frame_len);

		err = mcp251xfd_check_tef_tail(priv);
		अगर (err)
			वापस err;
	पूर्ण

	mcp251xfd_ecc_tefअगर_successful(priv);

	अगर (mcp251xfd_get_tx_मुक्त(priv->tx)) अणु
		/* Make sure that anybody stopping the queue after
		 * this sees the new tx_ring->tail.
		 */
		smp_mb();
		netअगर_wake_queue(priv->ndev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mcp251xfd_rx_ring_update(स्थिर काष्ठा mcp251xfd_priv *priv,
			 काष्ठा mcp251xfd_rx_ring *ring)
अणु
	u32 new_head;
	u8 chip_rx_head;
	पूर्णांक err;

	err = mcp251xfd_rx_head_get_from_chip(priv, ring, &chip_rx_head);
	अगर (err)
		वापस err;

	/* chip_rx_head, is the next RX-Object filled by the HW.
	 * The new RX head must be >= the old head.
	 */
	new_head = round_करोwn(ring->head, ring->obj_num) + chip_rx_head;
	अगर (new_head <= ring->head)
		new_head += ring->obj_num;

	ring->head = new_head;

	वापस mcp251xfd_check_rx_tail(priv, ring);
पूर्ण

अटल व्योम
mcp251xfd_hw_rx_obj_to_skb(काष्ठा mcp251xfd_priv *priv,
			   स्थिर काष्ठा mcp251xfd_hw_rx_obj_canfd *hw_rx_obj,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा canfd_frame *cfd = (काष्ठा canfd_frame *)skb->data;
	u8 dlc;

	अगर (hw_rx_obj->flags & MCP251XFD_OBJ_FLAGS_IDE) अणु
		u32 sid, eid;

		eid = FIELD_GET(MCP251XFD_OBJ_ID_EID_MASK, hw_rx_obj->id);
		sid = FIELD_GET(MCP251XFD_OBJ_ID_SID_MASK, hw_rx_obj->id);

		cfd->can_id = CAN_EFF_FLAG |
			FIELD_PREP(MCP251XFD_REG_FRAME_EFF_EID_MASK, eid) |
			FIELD_PREP(MCP251XFD_REG_FRAME_EFF_SID_MASK, sid);
	पूर्ण अन्यथा अणु
		cfd->can_id = FIELD_GET(MCP251XFD_OBJ_ID_SID_MASK,
					hw_rx_obj->id);
	पूर्ण

	dlc = FIELD_GET(MCP251XFD_OBJ_FLAGS_DLC_MASK, hw_rx_obj->flags);

	/* CANFD */
	अगर (hw_rx_obj->flags & MCP251XFD_OBJ_FLAGS_FDF) अणु

		अगर (hw_rx_obj->flags & MCP251XFD_OBJ_FLAGS_ESI)
			cfd->flags |= CANFD_ESI;

		अगर (hw_rx_obj->flags & MCP251XFD_OBJ_FLAGS_BRS)
			cfd->flags |= CANFD_BRS;

		cfd->len = can_fd_dlc2len(dlc);
	पूर्ण अन्यथा अणु
		अगर (hw_rx_obj->flags & MCP251XFD_OBJ_FLAGS_RTR)
			cfd->can_id |= CAN_RTR_FLAG;

		can_frame_set_cc_len((काष्ठा can_frame *)cfd, dlc,
				     priv->can.ctrlmode);
	पूर्ण

	अगर (!(hw_rx_obj->flags & MCP251XFD_OBJ_FLAGS_RTR))
		स_नकल(cfd->data, hw_rx_obj->data, cfd->len);

	mcp251xfd_skb_set_बारtamp(priv, skb, hw_rx_obj->ts);
पूर्ण

अटल पूर्णांक
mcp251xfd_handle_rxअगर_one(काष्ठा mcp251xfd_priv *priv,
			  काष्ठा mcp251xfd_rx_ring *ring,
			  स्थिर काष्ठा mcp251xfd_hw_rx_obj_canfd *hw_rx_obj)
अणु
	काष्ठा net_device_stats *stats = &priv->ndev->stats;
	काष्ठा sk_buff *skb;
	काष्ठा canfd_frame *cfd;
	पूर्णांक err;

	अगर (hw_rx_obj->flags & MCP251XFD_OBJ_FLAGS_FDF)
		skb = alloc_canfd_skb(priv->ndev, &cfd);
	अन्यथा
		skb = alloc_can_skb(priv->ndev, (काष्ठा can_frame **)&cfd);

	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस 0;
	पूर्ण

	mcp251xfd_hw_rx_obj_to_skb(priv, hw_rx_obj, skb);
	err = can_rx_offload_queue_sorted(&priv->offload, skb, hw_rx_obj->ts);
	अगर (err)
		stats->rx_fअगरo_errors++;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
mcp251xfd_rx_obj_पढ़ो(स्थिर काष्ठा mcp251xfd_priv *priv,
		      स्थिर काष्ठा mcp251xfd_rx_ring *ring,
		      काष्ठा mcp251xfd_hw_rx_obj_canfd *hw_rx_obj,
		      स्थिर u8 offset, स्थिर u8 len)
अणु
	स्थिर पूर्णांक val_bytes = regmap_get_val_bytes(priv->map_rx);
	पूर्णांक err;

	err = regmap_bulk_पढ़ो(priv->map_rx,
			       mcp251xfd_get_rx_obj_addr(ring, offset),
			       hw_rx_obj,
			       len * ring->obj_size / val_bytes);

	वापस err;
पूर्ण

अटल पूर्णांक
mcp251xfd_handle_rxअगर_ring(काष्ठा mcp251xfd_priv *priv,
			   काष्ठा mcp251xfd_rx_ring *ring)
अणु
	काष्ठा mcp251xfd_hw_rx_obj_canfd *hw_rx_obj = ring->obj;
	u8 rx_tail, len;
	पूर्णांक err, i;

	err = mcp251xfd_rx_ring_update(priv, ring);
	अगर (err)
		वापस err;

	जबतक ((len = mcp251xfd_get_rx_linear_len(ring))) अणु
		पूर्णांक offset;

		rx_tail = mcp251xfd_get_rx_tail(ring);

		err = mcp251xfd_rx_obj_पढ़ो(priv, ring, hw_rx_obj,
					    rx_tail, len);
		अगर (err)
			वापस err;

		क्रम (i = 0; i < len; i++) अणु
			err = mcp251xfd_handle_rxअगर_one(priv, ring,
							(व्योम *)hw_rx_obj +
							i * ring->obj_size);
			अगर (err)
				वापस err;
		पूर्ण

		/* Increment the RX FIFO tail poपूर्णांकer 'len' बार in a
		 * single SPI message.
		 *
		 * Note:
		 * Calculate offset, so that the SPI transfer ends on
		 * the last message of the uinc_xfer array, which has
		 * "cs_change == 0", to properly deactivate the chip
		 * select.
		 */
		offset = ARRAY_SIZE(ring->uinc_xfer) - len;
		err = spi_sync_transfer(priv->spi,
					ring->uinc_xfer + offset, len);
		अगर (err)
			वापस err;

		ring->tail += len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mcp251xfd_handle_rxअगर(काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा mcp251xfd_rx_ring *ring;
	पूर्णांक err, n;

	mcp251xfd_क्रम_each_rx_ring(priv, ring, n) अणु
		err = mcp251xfd_handle_rxअगर_ring(priv, ring);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *
mcp251xfd_alloc_can_err_skb(काष्ठा mcp251xfd_priv *priv,
			    काष्ठा can_frame **cf, u32 *बारtamp)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	err = mcp251xfd_get_बारtamp(priv, बारtamp);
	अगर (err)
		वापस शून्य;

	skb = alloc_can_err_skb(priv->ndev, cf);
	अगर (skb)
		mcp251xfd_skb_set_बारtamp(priv, skb, *बारtamp);

	वापस skb;
पूर्ण

अटल पूर्णांक mcp251xfd_handle_rxovअगर(काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा net_device_stats *stats = &priv->ndev->stats;
	काष्ठा mcp251xfd_rx_ring *ring;
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf;
	u32 बारtamp, rxovअगर;
	पूर्णांक err, i;

	stats->rx_over_errors++;
	stats->rx_errors++;

	err = regmap_पढ़ो(priv->map_reg, MCP251XFD_REG_RXOVIF, &rxovअगर);
	अगर (err)
		वापस err;

	mcp251xfd_क्रम_each_rx_ring(priv, ring, i) अणु
		अगर (!(rxovअगर & BIT(ring->fअगरo_nr)))
			जारी;

		/* If SERRIF is active, there was a RX MAB overflow. */
		अगर (priv->regs_status.पूर्णांकf & MCP251XFD_REG_INT_SERRIF) अणु
			netdev_info(priv->ndev,
				    "RX-%d: MAB overflow detected.\n",
				    ring->nr);
		पूर्ण अन्यथा अणु
			netdev_info(priv->ndev,
				    "RX-%d: FIFO overflow.\n", ring->nr);
		पूर्ण

		err = regmap_update_bits(priv->map_reg,
					 MCP251XFD_REG_FIFOSTA(ring->fअगरo_nr),
					 MCP251XFD_REG_FIFOSTA_RXOVIF,
					 0x0);
		अगर (err)
			वापस err;
	पूर्ण

	skb = mcp251xfd_alloc_can_err_skb(priv, &cf, &बारtamp);
	अगर (!skb)
		वापस 0;

	cf->can_id |= CAN_ERR_CRTL;
	cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;

	err = can_rx_offload_queue_sorted(&priv->offload, skb, बारtamp);
	अगर (err)
		stats->rx_fअगरo_errors++;

	वापस 0;
पूर्ण

अटल पूर्णांक mcp251xfd_handle_txatअगर(काष्ठा mcp251xfd_priv *priv)
अणु
	netdev_info(priv->ndev, "%s\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक mcp251xfd_handle_ivmअगर(काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा net_device_stats *stats = &priv->ndev->stats;
	u32 bdiag1, बारtamp;
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf = शून्य;
	पूर्णांक err;

	err = mcp251xfd_get_बारtamp(priv, &बारtamp);
	अगर (err)
		वापस err;

	err = regmap_पढ़ो(priv->map_reg, MCP251XFD_REG_BDIAG1, &bdiag1);
	अगर (err)
		वापस err;

	/* Write 0s to clear error bits, करोn't ग_लिखो 1s to non active
	 * bits, as they will be set.
	 */
	err = regmap_ग_लिखो(priv->map_reg, MCP251XFD_REG_BDIAG1, 0x0);
	अगर (err)
		वापस err;

	priv->can.can_stats.bus_error++;

	skb = alloc_can_err_skb(priv->ndev, &cf);
	अगर (cf)
		cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

	/* Controller misconfiguration */
	अगर (WARN_ON(bdiag1 & MCP251XFD_REG_BDIAG1_DLCMM))
		netdev_err(priv->ndev,
			   "recv'd DLC is larger than PLSIZE of FIFO element.");

	/* RX errors */
	अगर (bdiag1 & (MCP251XFD_REG_BDIAG1_DCRCERR |
		      MCP251XFD_REG_BDIAG1_NCRCERR)) अणु
		netdev_dbg(priv->ndev, "CRC error\n");

		stats->rx_errors++;
		अगर (cf)
			cf->data[3] |= CAN_ERR_PROT_LOC_CRC_SEQ;
	पूर्ण
	अगर (bdiag1 & (MCP251XFD_REG_BDIAG1_DSTUFERR |
		      MCP251XFD_REG_BDIAG1_NSTUFERR)) अणु
		netdev_dbg(priv->ndev, "Stuff error\n");

		stats->rx_errors++;
		अगर (cf)
			cf->data[2] |= CAN_ERR_PROT_STUFF;
	पूर्ण
	अगर (bdiag1 & (MCP251XFD_REG_BDIAG1_DFORMERR |
		      MCP251XFD_REG_BDIAG1_NFORMERR)) अणु
		netdev_dbg(priv->ndev, "Format error\n");

		stats->rx_errors++;
		अगर (cf)
			cf->data[2] |= CAN_ERR_PROT_FORM;
	पूर्ण

	/* TX errors */
	अगर (bdiag1 & MCP251XFD_REG_BDIAG1_NACKERR) अणु
		netdev_dbg(priv->ndev, "NACK error\n");

		stats->tx_errors++;
		अगर (cf) अणु
			cf->can_id |= CAN_ERR_ACK;
			cf->data[2] |= CAN_ERR_PROT_TX;
		पूर्ण
	पूर्ण
	अगर (bdiag1 & (MCP251XFD_REG_BDIAG1_DBIT1ERR |
		      MCP251XFD_REG_BDIAG1_NBIT1ERR)) अणु
		netdev_dbg(priv->ndev, "Bit1 error\n");

		stats->tx_errors++;
		अगर (cf)
			cf->data[2] |= CAN_ERR_PROT_TX | CAN_ERR_PROT_BIT1;
	पूर्ण
	अगर (bdiag1 & (MCP251XFD_REG_BDIAG1_DBIT0ERR |
		      MCP251XFD_REG_BDIAG1_NBIT0ERR)) अणु
		netdev_dbg(priv->ndev, "Bit0 error\n");

		stats->tx_errors++;
		अगर (cf)
			cf->data[2] |= CAN_ERR_PROT_TX | CAN_ERR_PROT_BIT0;
	पूर्ण

	अगर (!cf)
		वापस 0;

	mcp251xfd_skb_set_बारtamp(priv, skb, बारtamp);
	err = can_rx_offload_queue_sorted(&priv->offload, skb, बारtamp);
	अगर (err)
		stats->rx_fअगरo_errors++;

	वापस 0;
पूर्ण

अटल पूर्णांक mcp251xfd_handle_cerrअगर(काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा net_device_stats *stats = &priv->ndev->stats;
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf = शून्य;
	क्रमागत can_state new_state, rx_state, tx_state;
	u32 trec, बारtamp;
	पूर्णांक err;

	err = regmap_पढ़ो(priv->map_reg, MCP251XFD_REG_TREC, &trec);
	अगर (err)
		वापस err;

	अगर (trec & MCP251XFD_REG_TREC_TXBO)
		tx_state = CAN_STATE_BUS_OFF;
	अन्यथा अगर (trec & MCP251XFD_REG_TREC_TXBP)
		tx_state = CAN_STATE_ERROR_PASSIVE;
	अन्यथा अगर (trec & MCP251XFD_REG_TREC_TXWARN)
		tx_state = CAN_STATE_ERROR_WARNING;
	अन्यथा
		tx_state = CAN_STATE_ERROR_ACTIVE;

	अगर (trec & MCP251XFD_REG_TREC_RXBP)
		rx_state = CAN_STATE_ERROR_PASSIVE;
	अन्यथा अगर (trec & MCP251XFD_REG_TREC_RXWARN)
		rx_state = CAN_STATE_ERROR_WARNING;
	अन्यथा
		rx_state = CAN_STATE_ERROR_ACTIVE;

	new_state = max(tx_state, rx_state);
	अगर (new_state == priv->can.state)
		वापस 0;

	/* The skb allocation might fail, but can_change_state()
	 * handles cf == शून्य.
	 */
	skb = mcp251xfd_alloc_can_err_skb(priv, &cf, &बारtamp);
	can_change_state(priv->ndev, cf, tx_state, rx_state);

	अगर (new_state == CAN_STATE_BUS_OFF) अणु
		/* As we're going to switch off the chip now, let's
		 * save the error counters and वापस them to
		 * userspace, अगर करो_get_berr_counter() is called जबतक
		 * the chip is in Bus Off.
		 */
		err = __mcp251xfd_get_berr_counter(priv->ndev, &priv->bec);
		अगर (err)
			वापस err;

		mcp251xfd_chip_stop(priv, CAN_STATE_BUS_OFF);
		can_bus_off(priv->ndev);
	पूर्ण

	अगर (!skb)
		वापस 0;

	अगर (new_state != CAN_STATE_BUS_OFF) अणु
		काष्ठा can_berr_counter bec;

		err = mcp251xfd_get_berr_counter(priv->ndev, &bec);
		अगर (err)
			वापस err;
		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;
	पूर्ण

	err = can_rx_offload_queue_sorted(&priv->offload, skb, बारtamp);
	अगर (err)
		stats->rx_fअगरo_errors++;

	वापस 0;
पूर्ण

अटल पूर्णांक
mcp251xfd_handle_modअगर(स्थिर काष्ठा mcp251xfd_priv *priv, bool *set_normal_mode)
अणु
	स्थिर u8 mode_reference = mcp251xfd_get_normal_mode(priv);
	u8 mode;
	पूर्णांक err;

	err = mcp251xfd_chip_get_mode(priv, &mode);
	अगर (err)
		वापस err;

	अगर (mode == mode_reference) अणु
		netdev_dbg(priv->ndev,
			   "Controller changed into %s Mode (%u).\n",
			   mcp251xfd_get_mode_str(mode), mode);
		वापस 0;
	पूर्ण

	/* According to MCP2517FD errata DS80000792B 1., during a TX
	 * MAB underflow, the controller will transition to Restricted
	 * Operation Mode or Listen Only Mode (depending on SERR2LOM).
	 *
	 * However this is not always the हाल. If SERR2LOM is
	 * configured क्रम Restricted Operation Mode (SERR2LOM not set)
	 * the MCP2517FD will someबार transition to Listen Only Mode
	 * first. When polling this bit we see that it will transition
	 * to Restricted Operation Mode लघुly after.
	 */
	अगर ((priv->devtype_data.quirks & MCP251XFD_QUIRK_MAB_NO_WARN) &&
	    (mode == MCP251XFD_REG_CON_MODE_RESTRICTED ||
	     mode == MCP251XFD_REG_CON_MODE_LISTENONLY))
		netdev_dbg(priv->ndev,
			   "Controller changed into %s Mode (%u).\n",
			   mcp251xfd_get_mode_str(mode), mode);
	अन्यथा
		netdev_err(priv->ndev,
			   "Controller changed into %s Mode (%u).\n",
			   mcp251xfd_get_mode_str(mode), mode);

	/* After the application requests Normal mode, the controller
	 * will स्वतःmatically attempt to retransmit the message that
	 * caused the TX MAB underflow.
	 *
	 * However, अगर there is an ECC error in the TX-RAM, we first
	 * have to reload the tx-object beक्रमe requesting Normal
	 * mode. This is करोne later in mcp251xfd_handle_eccअगर().
	 */
	अगर (priv->regs_status.पूर्णांकf & MCP251XFD_REG_INT_ECCIF) अणु
		*set_normal_mode = true;
		वापस 0;
	पूर्ण

	वापस mcp251xfd_chip_set_normal_mode_noरुको(priv);
पूर्ण

अटल पूर्णांक mcp251xfd_handle_serrअगर(काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा mcp251xfd_ecc *ecc = &priv->ecc;
	काष्ठा net_device_stats *stats = &priv->ndev->stats;
	bool handled = false;

	/* TX MAB underflow
	 *
	 * According to MCP2517FD Errata DS80000792B 1. a TX MAB
	 * underflow is indicated by SERRIF and MODIF.
	 *
	 * In addition to the effects mentioned in the Errata, there
	 * are Bus Errors due to the पातed CAN frame, so a IVMIF
	 * will be seen as well.
	 *
	 * Someबार there is an ECC error in the TX-RAM, which leads
	 * to a TX MAB underflow.
	 *
	 * However, probably due to a race condition, there is no
	 * associated MODIF pending.
	 *
	 * Further, there are situations, where the SERRIF is caused
	 * by an ECC error in the TX-RAM, but not even the ECCIF is
	 * set. This only seems to happen _after_ the first occurrence
	 * of a ECCIF (which is tracked in ecc->cnt).
	 *
	 * Treat all as a known प्रणाली errors..
	 */
	अगर ((priv->regs_status.पूर्णांकf & MCP251XFD_REG_INT_MODIF &&
	     priv->regs_status.पूर्णांकf & MCP251XFD_REG_INT_IVMIF) ||
	    priv->regs_status.पूर्णांकf & MCP251XFD_REG_INT_ECCIF ||
	    ecc->cnt) अणु
		स्थिर अक्षर *msg;

		अगर (priv->regs_status.पूर्णांकf & MCP251XFD_REG_INT_ECCIF ||
		    ecc->cnt)
			msg = "TX MAB underflow due to ECC error detected.";
		अन्यथा
			msg = "TX MAB underflow detected.";

		अगर (priv->devtype_data.quirks & MCP251XFD_QUIRK_MAB_NO_WARN)
			netdev_dbg(priv->ndev, "%s\n", msg);
		अन्यथा
			netdev_info(priv->ndev, "%s\n", msg);

		stats->tx_पातed_errors++;
		stats->tx_errors++;
		handled = true;
	पूर्ण

	/* RX MAB overflow
	 *
	 * According to MCP2517FD Errata DS80000792B 1. a RX MAB
	 * overflow is indicated by SERRIF.
	 *
	 * In addition to the effects mentioned in the Errata, (most
	 * of the बार) a RXOVIF is उठाओd, अगर the FIFO that is being
	 * received पूर्णांकo has the RXOVIE activated (and we have enabled
	 * RXOVIE on all FIFOs).
	 *
	 * Someबार there is no RXOVIF just a RXIF is pending.
	 *
	 * Treat all as a known प्रणाली errors..
	 */
	अगर (priv->regs_status.पूर्णांकf & MCP251XFD_REG_INT_RXOVIF ||
	    priv->regs_status.पूर्णांकf & MCP251XFD_REG_INT_RXIF) अणु
		stats->rx_dropped++;
		handled = true;
	पूर्ण

	अगर (!handled)
		netdev_err(priv->ndev,
			   "Unhandled System Error Interrupt (intf=0x%08x)!\n",
			   priv->regs_status.पूर्णांकf);

	वापस 0;
पूर्ण

अटल पूर्णांक
mcp251xfd_handle_eccअगर_recover(काष्ठा mcp251xfd_priv *priv, u8 nr)
अणु
	काष्ठा mcp251xfd_tx_ring *tx_ring = priv->tx;
	काष्ठा mcp251xfd_ecc *ecc = &priv->ecc;
	काष्ठा mcp251xfd_tx_obj *tx_obj;
	u8 chip_tx_tail, tx_tail, offset;
	u16 addr;
	पूर्णांक err;

	addr = FIELD_GET(MCP251XFD_REG_ECCSTAT_ERRADDR_MASK, ecc->ecc_stat);

	err = mcp251xfd_tx_tail_get_from_chip(priv, &chip_tx_tail);
	अगर (err)
		वापस err;

	tx_tail = mcp251xfd_get_tx_tail(tx_ring);
	offset = (nr - chip_tx_tail) & (tx_ring->obj_num - 1);

	/* Bail out अगर one of the following is met:
	 * - tx_tail inक्रमmation is inconsistent
	 * - क्रम mcp2517fd: offset not 0
	 * - क्रम mcp2518fd: offset not 0 or 1
	 */
	अगर (chip_tx_tail != tx_tail ||
	    !(offset == 0 || (offset == 1 && mcp251xfd_is_2518(priv)))) अणु
		netdev_err(priv->ndev,
			   "ECC Error information inconsistent (addr=0x%04x, nr=%d, tx_tail=0x%08x(%d), chip_tx_tail=%d, offset=%d).\n",
			   addr, nr, tx_ring->tail, tx_tail, chip_tx_tail,
			   offset);
		वापस -EINVAL;
	पूर्ण

	netdev_info(priv->ndev,
		    "Recovering %s ECC Error at address 0x%04x (in TX-RAM, tx_obj=%d, tx_tail=0x%08x(%d), offset=%d).\n",
		    ecc->ecc_stat & MCP251XFD_REG_ECCSTAT_SECIF ?
		    "Single" : "Double",
		    addr, nr, tx_ring->tail, tx_tail, offset);

	/* reload tx_obj पूर्णांकo controller RAM ... */
	tx_obj = &tx_ring->obj[nr];
	err = spi_sync_transfer(priv->spi, tx_obj->xfer, 1);
	अगर (err)
		वापस err;

	/* ... and trigger retransmit */
	वापस mcp251xfd_chip_set_normal_mode(priv);
पूर्ण

अटल पूर्णांक
mcp251xfd_handle_eccअगर(काष्ठा mcp251xfd_priv *priv, bool set_normal_mode)
अणु
	काष्ठा mcp251xfd_ecc *ecc = &priv->ecc;
	स्थिर अक्षर *msg;
	bool in_tx_ram;
	u32 ecc_stat;
	u16 addr;
	u8 nr;
	पूर्णांक err;

	err = regmap_पढ़ो(priv->map_reg, MCP251XFD_REG_ECCSTAT, &ecc_stat);
	अगर (err)
		वापस err;

	err = regmap_update_bits(priv->map_reg, MCP251XFD_REG_ECCSTAT,
				 MCP251XFD_REG_ECCSTAT_IF_MASK, ~ecc_stat);
	अगर (err)
		वापस err;

	/* Check अगर ECC error occurred in TX-RAM */
	addr = FIELD_GET(MCP251XFD_REG_ECCSTAT_ERRADDR_MASK, ecc_stat);
	err = mcp251xfd_get_tx_nr_by_addr(priv->tx, &nr, addr);
	अगर (!err)
		in_tx_ram = true;
	अन्यथा अगर (err == -ENOENT)
		in_tx_ram = false;
	अन्यथा
		वापस err;

	/* Errata Reference:
	 * mcp2517fd: DS80000789B, mcp2518fd: DS80000792C 2.
	 *
	 * ECC single error correction करोes not work in all हालs:
	 *
	 * Fix/Work Around:
	 * Enable single error correction and द्विगुन error detection
	 * पूर्णांकerrupts by setting SECIE and DEDIE. Handle SECIF as a
	 * detection पूर्णांकerrupt and करो not rely on the error
	 * correction. Instead, handle both पूर्णांकerrupts as a
	 * notअगरication that the RAM word at ERRADDR was corrupted.
	 */
	अगर (ecc_stat & MCP251XFD_REG_ECCSTAT_SECIF)
		msg = "Single ECC Error detected at address";
	अन्यथा अगर (ecc_stat & MCP251XFD_REG_ECCSTAT_DEDIF)
		msg = "Double ECC Error detected at address";
	अन्यथा
		वापस -EINVAL;

	अगर (!in_tx_ram) अणु
		ecc->ecc_stat = 0;

		netdev_notice(priv->ndev, "%s 0x%04x.\n", msg, addr);
	पूर्ण अन्यथा अणु
		/* Re-occurring error? */
		अगर (ecc->ecc_stat == ecc_stat) अणु
			ecc->cnt++;
		पूर्ण अन्यथा अणु
			ecc->ecc_stat = ecc_stat;
			ecc->cnt = 1;
		पूर्ण

		netdev_info(priv->ndev,
			    "%s 0x%04x (in TX-RAM, tx_obj=%d), occurred %d time%s.\n",
			    msg, addr, nr, ecc->cnt, ecc->cnt > 1 ? "s" : "");

		अगर (ecc->cnt >= MCP251XFD_ECC_CNT_MAX)
			वापस mcp251xfd_handle_eccअगर_recover(priv, nr);
	पूर्ण

	अगर (set_normal_mode)
		वापस mcp251xfd_chip_set_normal_mode_noरुको(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक mcp251xfd_handle_spicrcअगर(काष्ठा mcp251xfd_priv *priv)
अणु
	पूर्णांक err;
	u32 crc;

	err = regmap_पढ़ो(priv->map_reg, MCP251XFD_REG_CRC, &crc);
	अगर (err)
		वापस err;

	err = regmap_update_bits(priv->map_reg, MCP251XFD_REG_CRC,
				 MCP251XFD_REG_CRC_IF_MASK,
				 ~crc);
	अगर (err)
		वापस err;

	अगर (crc & MCP251XFD_REG_CRC_FERRIF)
		netdev_notice(priv->ndev, "CRC write command format error.\n");
	अन्यथा अगर (crc & MCP251XFD_REG_CRC_CRCERRIF)
		netdev_notice(priv->ndev,
			      "CRC write error detected. CRC=0x%04lx.\n",
			      FIELD_GET(MCP251XFD_REG_CRC_MASK, crc));

	वापस 0;
पूर्ण

#घोषणा mcp251xfd_handle(priv, irq, ...) \
(अणु \
	काष्ठा mcp251xfd_priv *_priv = (priv); \
	पूर्णांक err; \
\
	err = mcp251xfd_handle_##irq(_priv, ## __VA_ARGS__); \
	अगर (err) \
		netdev_err(_priv->ndev, \
			"IRQ handler mcp251xfd_handle_%s() returned %d.\n", \
			__stringअगरy(irq), err); \
	err; \
पूर्ण)

अटल irqवापस_t mcp251xfd_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mcp251xfd_priv *priv = dev_id;
	स्थिर पूर्णांक val_bytes = regmap_get_val_bytes(priv->map_reg);
	irqवापस_t handled = IRQ_NONE;
	पूर्णांक err;

	अगर (priv->rx_पूर्णांक)
		करो अणु
			पूर्णांक rx_pending;

			rx_pending = gpiod_get_value_cansleep(priv->rx_पूर्णांक);
			अगर (!rx_pending)
				अवरोध;

			err = mcp251xfd_handle(priv, rxअगर);
			अगर (err)
				जाओ out_fail;

			handled = IRQ_HANDLED;
		पूर्ण जबतक (1);

	करो अणु
		u32 पूर्णांकf_pending, पूर्णांकf_pending_clearable;
		bool set_normal_mode = false;

		err = regmap_bulk_पढ़ो(priv->map_reg, MCP251XFD_REG_INT,
				       &priv->regs_status,
				       माप(priv->regs_status) /
				       val_bytes);
		अगर (err)
			जाओ out_fail;

		पूर्णांकf_pending = FIELD_GET(MCP251XFD_REG_INT_IF_MASK,
					 priv->regs_status.पूर्णांकf) &
			FIELD_GET(MCP251XFD_REG_INT_IE_MASK,
				  priv->regs_status.पूर्णांकf);

		अगर (!(पूर्णांकf_pending))
			वापस handled;

		/* Some पूर्णांकerrupts must be ACKed in the
		 * MCP251XFD_REG_INT रेजिस्टर.
		 * - First ACK then handle, to aव्योम lost-IRQ race
		 *   condition on fast re-occurring पूर्णांकerrupts.
		 * - Write "0" to clear active IRQs, "1" to all other,
		 *   to aव्योम r/m/w race condition on the
		 *   MCP251XFD_REG_INT रेजिस्टर.
		 */
		पूर्णांकf_pending_clearable = पूर्णांकf_pending &
			MCP251XFD_REG_INT_IF_CLEARABLE_MASK;
		अगर (पूर्णांकf_pending_clearable) अणु
			err = regmap_update_bits(priv->map_reg,
						 MCP251XFD_REG_INT,
						 MCP251XFD_REG_INT_IF_MASK,
						 ~पूर्णांकf_pending_clearable);
			अगर (err)
				जाओ out_fail;
		पूर्ण

		अगर (पूर्णांकf_pending & MCP251XFD_REG_INT_MODIF) अणु
			err = mcp251xfd_handle(priv, modअगर, &set_normal_mode);
			अगर (err)
				जाओ out_fail;
		पूर्ण

		अगर (पूर्णांकf_pending & MCP251XFD_REG_INT_RXIF) अणु
			err = mcp251xfd_handle(priv, rxअगर);
			अगर (err)
				जाओ out_fail;
		पूर्ण

		अगर (पूर्णांकf_pending & MCP251XFD_REG_INT_TEFIF) अणु
			err = mcp251xfd_handle(priv, tefअगर);
			अगर (err)
				जाओ out_fail;
		पूर्ण

		अगर (पूर्णांकf_pending & MCP251XFD_REG_INT_RXOVIF) अणु
			err = mcp251xfd_handle(priv, rxovअगर);
			अगर (err)
				जाओ out_fail;
		पूर्ण

		अगर (पूर्णांकf_pending & MCP251XFD_REG_INT_TXATIF) अणु
			err = mcp251xfd_handle(priv, txatअगर);
			अगर (err)
				जाओ out_fail;
		पूर्ण

		अगर (पूर्णांकf_pending & MCP251XFD_REG_INT_IVMIF) अणु
			err = mcp251xfd_handle(priv, ivmअगर);
			अगर (err)
				जाओ out_fail;
		पूर्ण

		अगर (पूर्णांकf_pending & MCP251XFD_REG_INT_SERRIF) अणु
			err = mcp251xfd_handle(priv, serrअगर);
			अगर (err)
				जाओ out_fail;
		पूर्ण

		अगर (पूर्णांकf_pending & MCP251XFD_REG_INT_ECCIF) अणु
			err = mcp251xfd_handle(priv, eccअगर, set_normal_mode);
			अगर (err)
				जाओ out_fail;
		पूर्ण

		अगर (पूर्णांकf_pending & MCP251XFD_REG_INT_SPICRCIF) अणु
			err = mcp251xfd_handle(priv, spicrcअगर);
			अगर (err)
				जाओ out_fail;
		पूर्ण

		/* On the MCP2527FD and MCP2518FD, we करोn't get a
		 * CERRIF IRQ on the transition TX ERROR_WARNING -> TX
		 * ERROR_ACTIVE.
		 */
		अगर (पूर्णांकf_pending & MCP251XFD_REG_INT_CERRIF ||
		    priv->can.state > CAN_STATE_ERROR_ACTIVE) अणु
			err = mcp251xfd_handle(priv, cerrअगर);
			अगर (err)
				जाओ out_fail;

			/* In Bus Off we completely shut करोwn the
			 * controller. Every subsequent रेजिस्टर पढ़ो
			 * will पढ़ो bogus data, and अगर
			 * MCP251XFD_QUIRK_CRC_REG is enabled the CRC
			 * check will fail, too. So leave IRQ handler
			 * directly.
			 */
			अगर (priv->can.state == CAN_STATE_BUS_OFF)
				वापस IRQ_HANDLED;
		पूर्ण

		handled = IRQ_HANDLED;
	पूर्ण जबतक (1);

 out_fail:
	netdev_err(priv->ndev, "IRQ handler returned %d (intf=0x%08x).\n",
		   err, priv->regs_status.पूर्णांकf);
	mcp251xfd_dump(priv);
	mcp251xfd_chip_पूर्णांकerrupts_disable(priv);

	वापस handled;
पूर्ण

अटल अंतरभूत काष्ठा
mcp251xfd_tx_obj *mcp251xfd_get_tx_obj_next(काष्ठा mcp251xfd_tx_ring *tx_ring)
अणु
	u8 tx_head;

	tx_head = mcp251xfd_get_tx_head(tx_ring);

	वापस &tx_ring->obj[tx_head];
पूर्ण

अटल व्योम
mcp251xfd_tx_obj_from_skb(स्थिर काष्ठा mcp251xfd_priv *priv,
			  काष्ठा mcp251xfd_tx_obj *tx_obj,
			  स्थिर काष्ठा sk_buff *skb,
			  अचिन्हित पूर्णांक seq)
अणु
	स्थिर काष्ठा canfd_frame *cfd = (काष्ठा canfd_frame *)skb->data;
	काष्ठा mcp251xfd_hw_tx_obj_raw *hw_tx_obj;
	जोड़ mcp251xfd_tx_obj_load_buf *load_buf;
	u8 dlc;
	u32 id, flags;
	पूर्णांक len_sanitized = 0, len;

	अगर (cfd->can_id & CAN_EFF_FLAG) अणु
		u32 sid, eid;

		sid = FIELD_GET(MCP251XFD_REG_FRAME_EFF_SID_MASK, cfd->can_id);
		eid = FIELD_GET(MCP251XFD_REG_FRAME_EFF_EID_MASK, cfd->can_id);

		id = FIELD_PREP(MCP251XFD_OBJ_ID_EID_MASK, eid) |
			FIELD_PREP(MCP251XFD_OBJ_ID_SID_MASK, sid);

		flags = MCP251XFD_OBJ_FLAGS_IDE;
	पूर्ण अन्यथा अणु
		id = FIELD_PREP(MCP251XFD_OBJ_ID_SID_MASK, cfd->can_id);
		flags = 0;
	पूर्ण

	/* Use the MCP2518FD mask even on the MCP2517FD. It करोesn't
	 * harm, only the lower 7 bits will be transferred पूर्णांकo the
	 * TEF object.
	 */
	flags |= FIELD_PREP(MCP251XFD_OBJ_FLAGS_SEQ_MCP2518FD_MASK, seq);

	अगर (cfd->can_id & CAN_RTR_FLAG)
		flags |= MCP251XFD_OBJ_FLAGS_RTR;
	अन्यथा
		len_sanitized = canfd_sanitize_len(cfd->len);

	/* CANFD */
	अगर (can_is_canfd_skb(skb)) अणु
		अगर (cfd->flags & CANFD_ESI)
			flags |= MCP251XFD_OBJ_FLAGS_ESI;

		flags |= MCP251XFD_OBJ_FLAGS_FDF;

		अगर (cfd->flags & CANFD_BRS)
			flags |= MCP251XFD_OBJ_FLAGS_BRS;

		dlc = can_fd_len2dlc(cfd->len);
	पूर्ण अन्यथा अणु
		dlc = can_get_cc_dlc((काष्ठा can_frame *)cfd,
				     priv->can.ctrlmode);
	पूर्ण

	flags |= FIELD_PREP(MCP251XFD_OBJ_FLAGS_DLC_MASK, dlc);

	load_buf = &tx_obj->buf;
	अगर (priv->devtype_data.quirks & MCP251XFD_QUIRK_CRC_TX)
		hw_tx_obj = &load_buf->crc.hw_tx_obj;
	अन्यथा
		hw_tx_obj = &load_buf->nocrc.hw_tx_obj;

	put_unaligned_le32(id, &hw_tx_obj->id);
	put_unaligned_le32(flags, &hw_tx_obj->flags);

	/* Copy data */
	स_नकल(hw_tx_obj->data, cfd->data, cfd->len);

	/* Clear unused data at end of CAN frame */
	अगर (MCP251XFD_SANITIZE_CAN && len_sanitized) अणु
		पूर्णांक pad_len;

		pad_len = len_sanitized - cfd->len;
		अगर (pad_len)
			स_रखो(hw_tx_obj->data + cfd->len, 0x0, pad_len);
	पूर्ण

	/* Number of bytes to be written पूर्णांकo the RAM of the controller */
	len = माप(hw_tx_obj->id) + माप(hw_tx_obj->flags);
	अगर (MCP251XFD_SANITIZE_CAN)
		len += round_up(len_sanitized, माप(u32));
	अन्यथा
		len += round_up(cfd->len, माप(u32));

	अगर (priv->devtype_data.quirks & MCP251XFD_QUIRK_CRC_TX) अणु
		u16 crc;

		mcp251xfd_spi_cmd_crc_set_len_in_ram(&load_buf->crc.cmd,
						     len);
		/* CRC */
		len += माप(load_buf->crc.cmd);
		crc = mcp251xfd_crc16_compute(&load_buf->crc, len);
		put_unaligned_be16(crc, (व्योम *)load_buf + len);

		/* Total length */
		len += माप(load_buf->crc.crc);
	पूर्ण अन्यथा अणु
		len += माप(load_buf->nocrc.cmd);
	पूर्ण

	tx_obj->xfer[0].len = len;
पूर्ण

अटल पूर्णांक mcp251xfd_tx_obj_ग_लिखो(स्थिर काष्ठा mcp251xfd_priv *priv,
				  काष्ठा mcp251xfd_tx_obj *tx_obj)
अणु
	वापस spi_async(priv->spi, &tx_obj->msg);
पूर्ण

अटल bool mcp251xfd_tx_busy(स्थिर काष्ठा mcp251xfd_priv *priv,
			      काष्ठा mcp251xfd_tx_ring *tx_ring)
अणु
	अगर (mcp251xfd_get_tx_मुक्त(tx_ring) > 0)
		वापस false;

	netअगर_stop_queue(priv->ndev);

	/* Memory barrier beक्रमe checking tx_मुक्त (head and tail) */
	smp_mb();

	अगर (mcp251xfd_get_tx_मुक्त(tx_ring) == 0) अणु
		netdev_dbg(priv->ndev,
			   "Stopping tx-queue (tx_head=0x%08x, tx_tail=0x%08x, len=%d).\n",
			   tx_ring->head, tx_ring->tail,
			   tx_ring->head - tx_ring->tail);

		वापस true;
	पूर्ण

	netअगर_start_queue(priv->ndev);

	वापस false;
पूर्ण

अटल netdev_tx_t mcp251xfd_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *ndev)
अणु
	काष्ठा mcp251xfd_priv *priv = netdev_priv(ndev);
	काष्ठा mcp251xfd_tx_ring *tx_ring = priv->tx;
	काष्ठा mcp251xfd_tx_obj *tx_obj;
	अचिन्हित पूर्णांक frame_len;
	u8 tx_head;
	पूर्णांक err;

	अगर (can_dropped_invalid_skb(ndev, skb))
		वापस NETDEV_TX_OK;

	अगर (mcp251xfd_tx_busy(priv, tx_ring))
		वापस NETDEV_TX_BUSY;

	tx_obj = mcp251xfd_get_tx_obj_next(tx_ring);
	mcp251xfd_tx_obj_from_skb(priv, tx_obj, skb, tx_ring->head);

	/* Stop queue अगर we occupy the complete TX FIFO */
	tx_head = mcp251xfd_get_tx_head(tx_ring);
	tx_ring->head++;
	अगर (mcp251xfd_get_tx_मुक्त(tx_ring) == 0)
		netअगर_stop_queue(ndev);

	frame_len = can_skb_get_frame_len(skb);
	err = can_put_echo_skb(skb, ndev, tx_head, frame_len);
	अगर (!err)
		netdev_sent_queue(priv->ndev, frame_len);

	err = mcp251xfd_tx_obj_ग_लिखो(priv, tx_obj);
	अगर (err)
		जाओ out_err;

	वापस NETDEV_TX_OK;

 out_err:
	netdev_err(priv->ndev, "ERROR in %s: %d\n", __func__, err);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक mcp251xfd_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा mcp251xfd_priv *priv = netdev_priv(ndev);
	स्थिर काष्ठा spi_device *spi = priv->spi;
	पूर्णांक err;

	err = pm_runसमय_get_sync(ndev->dev.parent);
	अगर (err < 0) अणु
		pm_runसमय_put_noidle(ndev->dev.parent);
		वापस err;
	पूर्ण

	err = खोलो_candev(ndev);
	अगर (err)
		जाओ out_pm_runसमय_put;

	err = mcp251xfd_ring_alloc(priv);
	अगर (err)
		जाओ out_बंद_candev;

	err = mcp251xfd_transceiver_enable(priv);
	अगर (err)
		जाओ out_mcp251xfd_ring_मुक्त;

	err = mcp251xfd_chip_start(priv);
	अगर (err)
		जाओ out_transceiver_disable;

	mcp251xfd_बारtamp_init(priv);
	can_rx_offload_enable(&priv->offload);

	err = request_thपढ़ोed_irq(spi->irq, शून्य, mcp251xfd_irq,
				   IRQF_ONESHOT, dev_name(&spi->dev),
				   priv);
	अगर (err)
		जाओ out_can_rx_offload_disable;

	err = mcp251xfd_chip_पूर्णांकerrupts_enable(priv);
	अगर (err)
		जाओ out_मुक्त_irq;

	netअगर_start_queue(ndev);

	वापस 0;

 out_मुक्त_irq:
	मुक्त_irq(spi->irq, priv);
 out_can_rx_offload_disable:
	can_rx_offload_disable(&priv->offload);
	mcp251xfd_बारtamp_stop(priv);
 out_transceiver_disable:
	mcp251xfd_transceiver_disable(priv);
 out_mcp251xfd_ring_मुक्त:
	mcp251xfd_ring_मुक्त(priv);
 out_बंद_candev:
	बंद_candev(ndev);
 out_pm_runसमय_put:
	mcp251xfd_chip_stop(priv, CAN_STATE_STOPPED);
	pm_runसमय_put(ndev->dev.parent);

	वापस err;
पूर्ण

अटल पूर्णांक mcp251xfd_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा mcp251xfd_priv *priv = netdev_priv(ndev);

	netअगर_stop_queue(ndev);
	mcp251xfd_chip_पूर्णांकerrupts_disable(priv);
	मुक्त_irq(ndev->irq, priv);
	can_rx_offload_disable(&priv->offload);
	mcp251xfd_बारtamp_stop(priv);
	mcp251xfd_chip_stop(priv, CAN_STATE_STOPPED);
	mcp251xfd_transceiver_disable(priv);
	mcp251xfd_ring_मुक्त(priv);
	बंद_candev(ndev);

	pm_runसमय_put(ndev->dev.parent);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops mcp251xfd_netdev_ops = अणु
	.nकरो_खोलो = mcp251xfd_खोलो,
	.nकरो_stop = mcp251xfd_stop,
	.nकरो_start_xmit	= mcp251xfd_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल व्योम
mcp251xfd_रेजिस्टर_quirks(काष्ठा mcp251xfd_priv *priv)
अणु
	स्थिर काष्ठा spi_device *spi = priv->spi;
	स्थिर काष्ठा spi_controller *ctlr = spi->controller;

	अगर (ctlr->flags & SPI_CONTROLLER_HALF_DUPLEX)
		priv->devtype_data.quirks |= MCP251XFD_QUIRK_HALF_DUPLEX;
पूर्ण

अटल पूर्णांक mcp251xfd_रेजिस्टर_chip_detect(काष्ठा mcp251xfd_priv *priv)
अणु
	स्थिर काष्ठा net_device *ndev = priv->ndev;
	स्थिर काष्ठा mcp251xfd_devtype_data *devtype_data;
	u32 osc;
	पूर्णांक err;

	/* The OSC_LPMEN is only supported on MCP2518FD, so use it to
	 * स्वतःdetect the model.
	 */
	err = regmap_update_bits(priv->map_reg, MCP251XFD_REG_OSC,
				 MCP251XFD_REG_OSC_LPMEN,
				 MCP251XFD_REG_OSC_LPMEN);
	अगर (err)
		वापस err;

	err = regmap_पढ़ो(priv->map_reg, MCP251XFD_REG_OSC, &osc);
	अगर (err)
		वापस err;

	अगर (osc & MCP251XFD_REG_OSC_LPMEN)
		devtype_data = &mcp251xfd_devtype_data_mcp2518fd;
	अन्यथा
		devtype_data = &mcp251xfd_devtype_data_mcp2517fd;

	अगर (!mcp251xfd_is_251X(priv) &&
	    priv->devtype_data.model != devtype_data->model) अणु
		netdev_info(ndev,
			    "Detected %s, but firmware specifies a %s. Fixing up.",
			    __mcp251xfd_get_model_str(devtype_data->model),
			    mcp251xfd_get_model_str(priv));
	पूर्ण
	priv->devtype_data = *devtype_data;

	/* We need to preserve the Half Duplex Quirk. */
	mcp251xfd_रेजिस्टर_quirks(priv);

	/* Re-init regmap with quirks of detected model. */
	वापस mcp251xfd_regmap_init(priv);
पूर्ण

अटल पूर्णांक mcp251xfd_रेजिस्टर_check_rx_पूर्णांक(काष्ठा mcp251xfd_priv *priv)
अणु
	पूर्णांक err, rx_pending;

	अगर (!priv->rx_पूर्णांक)
		वापस 0;

	err = mcp251xfd_chip_rx_पूर्णांक_enable(priv);
	अगर (err)
		वापस err;

	/* Check अगर RX_INT is properly working. The RX_INT should not
	 * be active after a softreset.
	 */
	rx_pending = gpiod_get_value_cansleep(priv->rx_पूर्णांक);

	err = mcp251xfd_chip_rx_पूर्णांक_disable(priv);
	अगर (err)
		वापस err;

	अगर (!rx_pending)
		वापस 0;

	netdev_info(priv->ndev,
		    "RX_INT active after softreset, disabling RX_INT support.");
	devm_gpiod_put(&priv->spi->dev, priv->rx_पूर्णांक);
	priv->rx_पूर्णांक = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक
mcp251xfd_रेजिस्टर_get_dev_id(स्थिर काष्ठा mcp251xfd_priv *priv,
			      u32 *dev_id, u32 *effective_speed_hz)
अणु
	काष्ठा mcp251xfd_map_buf_nocrc *buf_rx;
	काष्ठा mcp251xfd_map_buf_nocrc *buf_tx;
	काष्ठा spi_transfer xfer[2] = अणु पूर्ण;
	पूर्णांक err;

	buf_rx = kzalloc(माप(*buf_rx), GFP_KERNEL);
	अगर (!buf_rx)
		वापस -ENOMEM;

	buf_tx = kzalloc(माप(*buf_tx), GFP_KERNEL);
	अगर (!buf_tx) अणु
		err = -ENOMEM;
		जाओ out_kमुक्त_buf_rx;
	पूर्ण

	xfer[0].tx_buf = buf_tx;
	xfer[0].len = माप(buf_tx->cmd);
	xfer[1].rx_buf = buf_rx->data;
	xfer[1].len = माप(dev_id);

	mcp251xfd_spi_cmd_पढ़ो_nocrc(&buf_tx->cmd, MCP251XFD_REG_DEVID);
	err = spi_sync_transfer(priv->spi, xfer, ARRAY_SIZE(xfer));
	अगर (err)
		जाओ out_kमुक्त_buf_tx;

	*dev_id = be32_to_cpup((__be32 *)buf_rx->data);
	*effective_speed_hz = xfer->effective_speed_hz;

 out_kमुक्त_buf_tx:
	kमुक्त(buf_tx);
 out_kमुक्त_buf_rx:
	kमुक्त(buf_rx);

	वापस 0;
पूर्ण

#घोषणा MCP251XFD_QUIRK_ACTIVE(quirk) \
	(priv->devtype_data.quirks & MCP251XFD_QUIRK_##quirk ? '+' : '-')

अटल पूर्णांक
mcp251xfd_रेजिस्टर_करोne(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	u32 dev_id, effective_speed_hz;
	पूर्णांक err;

	err = mcp251xfd_रेजिस्टर_get_dev_id(priv, &dev_id,
					    &effective_speed_hz);
	अगर (err)
		वापस err;

	netdev_info(priv->ndev,
		    "%s rev%lu.%lu (%cRX_INT %cMAB_NO_WARN %cCRC_REG %cCRC_RX %cCRC_TX %cECC %cHD c:%u.%02uMHz m:%u.%02uMHz r:%u.%02uMHz e:%u.%02uMHz) successfully initialized.\n",
		    mcp251xfd_get_model_str(priv),
		    FIELD_GET(MCP251XFD_REG_DEVID_ID_MASK, dev_id),
		    FIELD_GET(MCP251XFD_REG_DEVID_REV_MASK, dev_id),
		    priv->rx_पूर्णांक ? '+' : '-',
		    MCP251XFD_QUIRK_ACTIVE(MAB_NO_WARN),
		    MCP251XFD_QUIRK_ACTIVE(CRC_REG),
		    MCP251XFD_QUIRK_ACTIVE(CRC_RX),
		    MCP251XFD_QUIRK_ACTIVE(CRC_TX),
		    MCP251XFD_QUIRK_ACTIVE(ECC),
		    MCP251XFD_QUIRK_ACTIVE(HALF_DUPLEX),
		    priv->can.घड़ी.freq / 1000000,
		    priv->can.घड़ी.freq % 1000000 / 1000 / 10,
		    priv->spi_max_speed_hz_orig / 1000000,
		    priv->spi_max_speed_hz_orig % 1000000 / 1000 / 10,
		    priv->spi->max_speed_hz / 1000000,
		    priv->spi->max_speed_hz % 1000000 / 1000 / 10,
		    effective_speed_hz / 1000000,
		    effective_speed_hz % 1000000 / 1000 / 10);

	वापस 0;
पूर्ण

अटल पूर्णांक mcp251xfd_रेजिस्टर(काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	पूर्णांक err;

	err = mcp251xfd_clks_and_vdd_enable(priv);
	अगर (err)
		वापस err;

	pm_runसमय_get_noresume(ndev->dev.parent);
	err = pm_runसमय_set_active(ndev->dev.parent);
	अगर (err)
		जाओ out_runसमय_put_noidle;
	pm_runसमय_enable(ndev->dev.parent);

	mcp251xfd_रेजिस्टर_quirks(priv);

	err = mcp251xfd_chip_softreset(priv);
	अगर (err == -ENODEV)
		जाओ out_runसमय_disable;
	अगर (err)
		जाओ out_chip_set_mode_sleep;

	err = mcp251xfd_रेजिस्टर_chip_detect(priv);
	अगर (err)
		जाओ out_chip_set_mode_sleep;

	err = mcp251xfd_रेजिस्टर_check_rx_पूर्णांक(priv);
	अगर (err)
		जाओ out_chip_set_mode_sleep;

	err = रेजिस्टर_candev(ndev);
	अगर (err)
		जाओ out_chip_set_mode_sleep;

	err = mcp251xfd_रेजिस्टर_करोne(priv);
	अगर (err)
		जाओ out_unरेजिस्टर_candev;

	/* Put controller पूर्णांकo sleep mode and let pm_runसमय_put()
	 * disable the घड़ीs and vdd. If CONFIG_PM is not enabled,
	 * the घड़ीs and vdd will stay घातered.
	 */
	err = mcp251xfd_chip_set_mode(priv, MCP251XFD_REG_CON_MODE_SLEEP);
	अगर (err)
		जाओ out_unरेजिस्टर_candev;

	pm_runसमय_put(ndev->dev.parent);

	वापस 0;

 out_unरेजिस्टर_candev:
	unरेजिस्टर_candev(ndev);
 out_chip_set_mode_sleep:
	mcp251xfd_chip_set_mode(priv, MCP251XFD_REG_CON_MODE_SLEEP);
 out_runसमय_disable:
	pm_runसमय_disable(ndev->dev.parent);
 out_runसमय_put_noidle:
	pm_runसमय_put_noidle(ndev->dev.parent);
	mcp251xfd_clks_and_vdd_disable(priv);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम mcp251xfd_unरेजिस्टर(काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा net_device *ndev	= priv->ndev;

	unरेजिस्टर_candev(ndev);

	pm_runसमय_get_sync(ndev->dev.parent);
	pm_runसमय_put_noidle(ndev->dev.parent);
	mcp251xfd_clks_and_vdd_disable(priv);
	pm_runसमय_disable(ndev->dev.parent);
पूर्ण

अटल स्थिर काष्ठा of_device_id mcp251xfd_of_match[] = अणु
	अणु
		.compatible = "microchip,mcp2517fd",
		.data = &mcp251xfd_devtype_data_mcp2517fd,
	पूर्ण, अणु
		.compatible = "microchip,mcp2518fd",
		.data = &mcp251xfd_devtype_data_mcp2518fd,
	पूर्ण, अणु
		.compatible = "microchip,mcp251xfd",
		.data = &mcp251xfd_devtype_data_mcp251xfd,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp251xfd_of_match);

अटल स्थिर काष्ठा spi_device_id mcp251xfd_id_table[] = अणु
	अणु
		.name = "mcp2517fd",
		.driver_data = (kernel_uदीर्घ_t)&mcp251xfd_devtype_data_mcp2517fd,
	पूर्ण, अणु
		.name = "mcp2518fd",
		.driver_data = (kernel_uदीर्घ_t)&mcp251xfd_devtype_data_mcp2518fd,
	पूर्ण, अणु
		.name = "mcp251xfd",
		.driver_data = (kernel_uदीर्घ_t)&mcp251xfd_devtype_data_mcp251xfd,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, mcp251xfd_id_table);

अटल पूर्णांक mcp251xfd_probe(काष्ठा spi_device *spi)
अणु
	स्थिर व्योम *match;
	काष्ठा net_device *ndev;
	काष्ठा mcp251xfd_priv *priv;
	काष्ठा gpio_desc *rx_पूर्णांक;
	काष्ठा regulator *reg_vdd, *reg_xceiver;
	काष्ठा clk *clk;
	u32 freq;
	पूर्णांक err;

	अगर (!spi->irq)
		वापस dev_err_probe(&spi->dev, -ENXIO,
				     "No IRQ specified (maybe node \"interrupts-extended\" in DT missing)!\n");

	rx_पूर्णांक = devm_gpiod_get_optional(&spi->dev, "microchip,rx-int",
					 GPIOD_IN);
	अगर (IS_ERR(rx_पूर्णांक))
		वापस dev_err_probe(&spi->dev, PTR_ERR(rx_पूर्णांक),
				     "Failed to get RX-INT!\n");

	reg_vdd = devm_regulator_get_optional(&spi->dev, "vdd");
	अगर (PTR_ERR(reg_vdd) == -ENODEV)
		reg_vdd = शून्य;
	अन्यथा अगर (IS_ERR(reg_vdd))
		वापस dev_err_probe(&spi->dev, PTR_ERR(reg_vdd),
				     "Failed to get VDD regulator!\n");

	reg_xceiver = devm_regulator_get_optional(&spi->dev, "xceiver");
	अगर (PTR_ERR(reg_xceiver) == -ENODEV)
		reg_xceiver = शून्य;
	अन्यथा अगर (IS_ERR(reg_xceiver))
		वापस dev_err_probe(&spi->dev, PTR_ERR(reg_xceiver),
				     "Failed to get Transceiver regulator!\n");

	clk = devm_clk_get(&spi->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस dev_err_probe(&spi->dev, PTR_ERR(clk),
				     "Failed to get Oscillator (clock)!\n");
	freq = clk_get_rate(clk);

	/* Sanity check */
	अगर (freq < MCP251XFD_SYSCLOCK_HZ_MIN ||
	    freq > MCP251XFD_SYSCLOCK_HZ_MAX) अणु
		dev_err(&spi->dev,
			"Oscillator frequency (%u Hz) is too low or high.\n",
			freq);
		वापस -दुस्फल;
	पूर्ण

	अगर (freq <= MCP251XFD_SYSCLOCK_HZ_MAX / MCP251XFD_OSC_PLL_MULTIPLIER) अणु
		dev_err(&spi->dev,
			"Oscillator frequency (%u Hz) is too low and PLL is not supported.\n",
			freq);
		वापस -दुस्फल;
	पूर्ण

	ndev = alloc_candev(माप(काष्ठा mcp251xfd_priv),
			    MCP251XFD_TX_OBJ_NUM_MAX);
	अगर (!ndev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(ndev, &spi->dev);

	ndev->netdev_ops = &mcp251xfd_netdev_ops;
	ndev->irq = spi->irq;
	ndev->flags |= IFF_ECHO;

	priv = netdev_priv(ndev);
	spi_set_drvdata(spi, priv);
	priv->can.घड़ी.freq = freq;
	priv->can.करो_set_mode = mcp251xfd_set_mode;
	priv->can.करो_get_berr_counter = mcp251xfd_get_berr_counter;
	priv->can.bittiming_स्थिर = &mcp251xfd_bittiming_स्थिर;
	priv->can.data_bittiming_स्थिर = &mcp251xfd_data_bittiming_स्थिर;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK |
		CAN_CTRLMODE_LISTENONLY | CAN_CTRLMODE_BERR_REPORTING |
		CAN_CTRLMODE_FD | CAN_CTRLMODE_FD_NON_ISO |
		CAN_CTRLMODE_CC_LEN8_DLC;
	priv->ndev = ndev;
	priv->spi = spi;
	priv->rx_पूर्णांक = rx_पूर्णांक;
	priv->clk = clk;
	priv->reg_vdd = reg_vdd;
	priv->reg_xceiver = reg_xceiver;

	match = device_get_match_data(&spi->dev);
	अगर (match)
		priv->devtype_data = *(काष्ठा mcp251xfd_devtype_data *)match;
	अन्यथा
		priv->devtype_data = *(काष्ठा mcp251xfd_devtype_data *)
			spi_get_device_id(spi)->driver_data;

	/* Errata Reference:
	 * mcp2517fd: DS80000792C 5., mcp2518fd: DS80000789C 4.
	 *
	 * The SPI can ग_लिखो corrupted data to the RAM at fast SPI
	 * speeds:
	 *
	 * Simultaneous activity on the CAN bus जबतक writing data to
	 * RAM via the SPI पूर्णांकerface, with high SCK frequency, can
	 * lead to corrupted data being written to RAM.
	 *
	 * Fix/Work Around:
	 * Ensure that FSCK is less than or equal to 0.85 *
	 * (FSYSCLK/2).
	 *
	 * Known good combinations are:
	 *
	 * MCP	ext-clk	SoC			SPI			SPI-clk		max-clk	parent-clk	config
	 *
	 * 2518	20 MHz	allwinner,sun8i-h3	allwinner,sun8i-h3-spi	 8333333 Hz	 83.33%	600000000 Hz	asचिन्हित-घड़ीs = <&ccu CLK_SPIx>
	 * 2518	40 MHz	allwinner,sun8i-h3	allwinner,sun8i-h3-spi	16666667 Hz	 83.33%	600000000 Hz	asचिन्हित-घड़ीs = <&ccu CLK_SPIx>
	 * 2517	40 MHz	aपंचांगel,sama5d27		aपंचांगel,at91rm9200-spi	16400000 Hz	 82.00%	 82000000 Hz	शेष
	 * 2518	40 MHz	aपंचांगel,sama5d27		aपंचांगel,at91rm9200-spi	16400000 Hz	 82.00%	 82000000 Hz	शेष
	 * 2518	40 MHz	fsl,imx6dl		fsl,imx51-ecspi		15000000 Hz	 75.00%	 30000000 Hz	शेष
	 * 2517	20 MHz	fsl,imx8mm		fsl,imx51-ecspi		 8333333 Hz	 83.33%	 16666667 Hz	asचिन्हित-घड़ीs = <&clk IMX8MM_CLK_ECSPIx_ROOT>
	 *
	 */
	priv->spi_max_speed_hz_orig = spi->max_speed_hz;
	spi->max_speed_hz = min(spi->max_speed_hz, freq / 2 / 1000 * 850);
	spi->bits_per_word = 8;
	spi->rt = true;
	err = spi_setup(spi);
	अगर (err)
		जाओ out_मुक्त_candev;

	err = mcp251xfd_regmap_init(priv);
	अगर (err)
		जाओ out_मुक्त_candev;

	err = can_rx_offload_add_manual(ndev, &priv->offload,
					MCP251XFD_NAPI_WEIGHT);
	अगर (err)
		जाओ out_मुक्त_candev;

	err = mcp251xfd_रेजिस्टर(priv);
	अगर (err)
		जाओ out_can_rx_offload_del;

	वापस 0;

 out_can_rx_offload_del:
	can_rx_offload_del(&priv->offload);
 out_मुक्त_candev:
	spi->max_speed_hz = priv->spi_max_speed_hz_orig;

	मुक्त_candev(ndev);

	वापस err;
पूर्ण

अटल पूर्णांक mcp251xfd_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा mcp251xfd_priv *priv = spi_get_drvdata(spi);
	काष्ठा net_device *ndev = priv->ndev;

	can_rx_offload_del(&priv->offload);
	mcp251xfd_unरेजिस्टर(priv);
	spi->max_speed_hz = priv->spi_max_speed_hz_orig;
	मुक्त_candev(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mcp251xfd_runसमय_suspend(काष्ठा device *device)
अणु
	स्थिर काष्ठा mcp251xfd_priv *priv = dev_get_drvdata(device);

	वापस mcp251xfd_clks_and_vdd_disable(priv);
पूर्ण

अटल पूर्णांक __maybe_unused mcp251xfd_runसमय_resume(काष्ठा device *device)
अणु
	स्थिर काष्ठा mcp251xfd_priv *priv = dev_get_drvdata(device);

	वापस mcp251xfd_clks_and_vdd_enable(priv);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mcp251xfd_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mcp251xfd_runसमय_suspend,
			   mcp251xfd_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा spi_driver mcp251xfd_driver = अणु
	.driver = अणु
		.name = DEVICE_NAME,
		.pm = &mcp251xfd_pm_ops,
		.of_match_table = mcp251xfd_of_match,
	पूर्ण,
	.probe = mcp251xfd_probe,
	.हटाओ = mcp251xfd_हटाओ,
	.id_table = mcp251xfd_id_table,
पूर्ण;
module_spi_driver(mcp251xfd_driver);

MODULE_AUTHOR("Marc Kleine-Budde <mkl@pengutronix.de>");
MODULE_DESCRIPTION("Microchip MCP251xFD Family CAN controller driver");
MODULE_LICENSE("GPL v2");
