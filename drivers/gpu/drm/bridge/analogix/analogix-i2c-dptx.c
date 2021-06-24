<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2016, Analogix Semiconductor.
 *
 * Based on anx7808 driver obtained from chromeos with copyright:
 * Copyright(c) 2013, Google Inc.
 */
#समावेश <linux/regmap.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "analogix-i2c-dptx.h"

#घोषणा AUX_WAIT_TIMEOUT_MS	15
#घोषणा AUX_CH_BUFFER_SIZE	16

अटल पूर्णांक anx_i2c_dp_clear_bits(काष्ठा regmap *map, u8 reg, u8 mask)
अणु
	वापस regmap_update_bits(map, reg, mask, 0);
पूर्ण

अटल bool anx_dp_aux_op_finished(काष्ठा regmap *map_dptx)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	err = regmap_पढ़ो(map_dptx, SP_DP_AUX_CH_CTRL2_REG, &value);
	अगर (err < 0)
		वापस false;

	वापस (value & SP_AUX_EN) == 0;
पूर्ण

अटल पूर्णांक anx_dp_aux_रुको(काष्ठा regmap *map_dptx)
अणु
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक status;
	पूर्णांक err;

	समयout = jअगरfies + msecs_to_jअगरfies(AUX_WAIT_TIMEOUT_MS) + 1;

	जबतक (!anx_dp_aux_op_finished(map_dptx)) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			अगर (!anx_dp_aux_op_finished(map_dptx)) अणु
				DRM_ERROR("Timed out waiting AUX to finish\n");
				वापस -ETIMEDOUT;
			पूर्ण

			अवरोध;
		पूर्ण

		usleep_range(1000, 2000);
	पूर्ण

	/* Read the AUX channel access status */
	err = regmap_पढ़ो(map_dptx, SP_AUX_CH_STATUS_REG, &status);
	अगर (err < 0) अणु
		DRM_ERROR("Failed to read from AUX channel: %d\n", err);
		वापस err;
	पूर्ण

	अगर (status & SP_AUX_STATUS) अणु
		DRM_ERROR("Failed to wait for AUX channel (status: %02x)\n",
			  status);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक anx_dp_aux_address(काष्ठा regmap *map_dptx, अचिन्हित पूर्णांक addr)
अणु
	पूर्णांक err;

	err = regmap_ग_लिखो(map_dptx, SP_AUX_ADDR_7_0_REG, addr & 0xff);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(map_dptx, SP_AUX_ADDR_15_8_REG,
			   (addr & 0xff00) >> 8);
	अगर (err)
		वापस err;

	/*
	 * DP AUX CH Address Register #2, only update bits[3:0]
	 * [7:4] RESERVED
	 * [3:0] AUX_ADDR[19:16], Register control AUX CH address.
	 */
	err = regmap_update_bits(map_dptx, SP_AUX_ADDR_19_16_REG,
				 SP_AUX_ADDR_19_16_MASK,
				 (addr & 0xf0000) >> 16);

	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

sमाप_प्रकार anx_dp_aux_transfer(काष्ठा regmap *map_dptx,
				काष्ठा drm_dp_aux_msg *msg)
अणु
	u8 ctrl1 = msg->request;
	u8 ctrl2 = SP_AUX_EN;
	u8 *buffer = msg->buffer;
	पूर्णांक err;

	/* The DP AUX transmit and receive buffer has 16 bytes. */
	अगर (WARN_ON(msg->size > AUX_CH_BUFFER_SIZE))
		वापस -E2BIG;

	/* Zero-sized messages specअगरy address-only transactions. */
	अगर (msg->size < 1)
		ctrl2 |= SP_ADDR_ONLY;
	अन्यथा	/* For non-zero-sized set the length field. */
		ctrl1 |= (msg->size - 1) << SP_AUX_LENGTH_SHIFT;

	अगर ((msg->size > 0) && ((msg->request & DP_AUX_I2C_READ) == 0)) अणु
		/* When WRITE | MOT ग_लिखो values to data buffer */
		err = regmap_bulk_ग_लिखो(map_dptx,
					SP_DP_BUF_DATA0_REG, buffer,
					msg->size);
		अगर (err)
			वापस err;
	पूर्ण

	/* Write address and request */
	err = anx_dp_aux_address(map_dptx, msg->address);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(map_dptx, SP_DP_AUX_CH_CTRL1_REG, ctrl1);
	अगर (err)
		वापस err;

	/* Start transaction */
	err = regmap_update_bits(map_dptx, SP_DP_AUX_CH_CTRL2_REG,
				 SP_ADDR_ONLY | SP_AUX_EN, ctrl2);
	अगर (err)
		वापस err;

	err = anx_dp_aux_रुको(map_dptx);
	अगर (err)
		वापस err;

	msg->reply = DP_AUX_I2C_REPLY_ACK;

	अगर ((msg->size > 0) && (msg->request & DP_AUX_I2C_READ)) अणु
		/* Read values from data buffer */
		err = regmap_bulk_पढ़ो(map_dptx,
				       SP_DP_BUF_DATA0_REG, buffer,
				       msg->size);
		अगर (err)
			वापस err;
	पूर्ण

	err = anx_i2c_dp_clear_bits(map_dptx, SP_DP_AUX_CH_CTRL2_REG,
				    SP_ADDR_ONLY);
	अगर (err)
		वापस err;

	वापस msg->size;
पूर्ण
EXPORT_SYMBOL_GPL(anx_dp_aux_transfer);
