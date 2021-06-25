<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * tcan4x5x - Texas Instruments TCAN4x5x Family CAN controller driver
 *
 * Copyright (c) 2020 Pengutronix,
 *                    Marc Kleine-Budde <kernel@pengutronix.de>
 */

#अगर_अघोषित _TCAN4X5X_H
#घोषणा _TCAN4X5X_H

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश "m_can.h"

#घोषणा TCAN4X5X_SANITIZE_SPI 1

काष्ठा __packed tcan4x5x_buf_cmd अणु
	u8 cmd;
	__be16 addr;
	u8 len;
पूर्ण;

काष्ठा tcan4x5x_map_buf अणु
	काष्ठा tcan4x5x_buf_cmd cmd;
	u8 data[256 * माप(u32)];
पूर्ण ____cacheline_aligned;

काष्ठा tcan4x5x_priv अणु
	काष्ठा m_can_classdev cdev;

	काष्ठा regmap *regmap;
	काष्ठा spi_device *spi;

	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *device_wake_gpio;
	काष्ठा gpio_desc *device_state_gpio;
	काष्ठा regulator *घातer;

	काष्ठा tcan4x5x_map_buf map_buf_rx;
	काष्ठा tcan4x5x_map_buf map_buf_tx;
पूर्ण;

अटल अंतरभूत व्योम
tcan4x5x_spi_cmd_set_len(काष्ठा tcan4x5x_buf_cmd *cmd, u8 len)
अणु
	/* number of u32 */
	cmd->len = len >> 2;
पूर्ण

पूर्णांक tcan4x5x_regmap_init(काष्ठा tcan4x5x_priv *priv);

#पूर्ण_अगर
