<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 * Copyright (C) 2017 Jonathan Liu <net147@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iopoll.h>

#समावेश "sun4i_hdmi.h"

#घोषणा SUN4I_HDMI_DDC_INT_STATUS_ERROR_MASK ( \
	SUN4I_HDMI_DDC_INT_STATUS_ILLEGAL_FIFO_OPERATION | \
	SUN4I_HDMI_DDC_INT_STATUS_DDC_RX_FIFO_UNDERFLOW | \
	SUN4I_HDMI_DDC_INT_STATUS_DDC_TX_FIFO_OVERFLOW | \
	SUN4I_HDMI_DDC_INT_STATUS_ARBITRATION_ERROR | \
	SUN4I_HDMI_DDC_INT_STATUS_ACK_ERROR | \
	SUN4I_HDMI_DDC_INT_STATUS_BUS_ERROR \
)

/* FIFO request bit is set when FIFO level is above RX_THRESHOLD during पढ़ो */
#घोषणा RX_THRESHOLD SUN4I_HDMI_DDC_FIFO_CTRL_RX_THRES_MAX

अटल पूर्णांक fअगरo_transfer(काष्ठा sun4i_hdmi *hdmi, u8 *buf, पूर्णांक len, bool पढ़ो)
अणु
	/*
	 * 1 byte takes 9 घड़ी cycles (8 bits + 1 ACK) = 90 us क्रम 100 kHz
	 * घड़ी. As घड़ी rate is fixed, just round it up to 100 us.
	 */
	स्थिर अचिन्हित दीर्घ byte_समय_ns = 100;
	स्थिर u32 mask = SUN4I_HDMI_DDC_INT_STATUS_ERROR_MASK |
			 SUN4I_HDMI_DDC_INT_STATUS_FIFO_REQUEST |
			 SUN4I_HDMI_DDC_INT_STATUS_TRANSFER_COMPLETE;
	u32 reg;
	/*
	 * If threshold is inclusive, then the FIFO may only have
	 * RX_THRESHOLD number of bytes, instead of RX_THRESHOLD + 1.
	 */
	पूर्णांक पढ़ो_len = RX_THRESHOLD +
		(hdmi->variant->ddc_fअगरo_thres_incl ? 0 : 1);

	/*
	 * Limit transfer length by FIFO threshold or FIFO size.
	 * For TX the threshold is क्रम an empty FIFO.
	 */
	len = min_t(पूर्णांक, len, पढ़ो ? पढ़ो_len : SUN4I_HDMI_DDC_FIFO_SIZE);

	/* Wait until error, FIFO request bit set or transfer complete */
	अगर (regmap_field_पढ़ो_poll_समयout(hdmi->field_ddc_पूर्णांक_status, reg,
					   reg & mask, len * byte_समय_ns,
					   100000))
		वापस -ETIMEDOUT;

	अगर (reg & SUN4I_HDMI_DDC_INT_STATUS_ERROR_MASK)
		वापस -EIO;

	अगर (पढ़ो)
		पढ़ोsb(hdmi->base + hdmi->variant->ddc_fअगरo_reg, buf, len);
	अन्यथा
		ग_लिखोsb(hdmi->base + hdmi->variant->ddc_fअगरo_reg, buf, len);

	/* Clear FIFO request bit by क्रमcing a ग_लिखो to that bit */
	regmap_field_क्रमce_ग_लिखो(hdmi->field_ddc_पूर्णांक_status,
				 SUN4I_HDMI_DDC_INT_STATUS_FIFO_REQUEST);

	वापस len;
पूर्ण

अटल पूर्णांक xfer_msg(काष्ठा sun4i_hdmi *hdmi, काष्ठा i2c_msg *msg)
अणु
	पूर्णांक i, len;
	u32 reg;

	/* Set FIFO direction */
	अगर (hdmi->variant->ddc_fअगरo_has_dir) अणु
		reg = पढ़ोl(hdmi->base + SUN4I_HDMI_DDC_CTRL_REG);
		reg &= ~SUN4I_HDMI_DDC_CTRL_FIFO_सूची_MASK;
		reg |= (msg->flags & I2C_M_RD) ?
		       SUN4I_HDMI_DDC_CTRL_FIFO_सूची_READ :
		       SUN4I_HDMI_DDC_CTRL_FIFO_सूची_WRITE;
		ग_लिखोl(reg, hdmi->base + SUN4I_HDMI_DDC_CTRL_REG);
	पूर्ण

	/* Clear address रेजिस्टर (not cleared by soft reset) */
	regmap_field_ग_लिखो(hdmi->field_ddc_addr_reg, 0);

	/* Set I2C address */
	regmap_field_ग_लिखो(hdmi->field_ddc_slave_addr, msg->addr);

	/*
	 * Set FIFO RX/TX thresholds and clear FIFO
	 *
	 * If threshold is inclusive, we can set the TX threshold to
	 * 0 instead of 1.
	 */
	regmap_field_ग_लिखो(hdmi->field_ddc_fअगरo_tx_thres,
			   hdmi->variant->ddc_fअगरo_thres_incl ? 0 : 1);
	regmap_field_ग_लिखो(hdmi->field_ddc_fअगरo_rx_thres, RX_THRESHOLD);
	regmap_field_ग_लिखो(hdmi->field_ddc_fअगरo_clear, 1);
	अगर (regmap_field_पढ़ो_poll_समयout(hdmi->field_ddc_fअगरo_clear,
					   reg, !reg, 100, 2000))
		वापस -EIO;

	/* Set transfer length */
	regmap_field_ग_लिखो(hdmi->field_ddc_byte_count, msg->len);

	/* Set command */
	regmap_field_ग_लिखो(hdmi->field_ddc_cmd,
			   msg->flags & I2C_M_RD ?
			   SUN4I_HDMI_DDC_CMD_IMPLICIT_READ :
			   SUN4I_HDMI_DDC_CMD_IMPLICIT_WRITE);

	/* Clear पूर्णांकerrupt status bits by क्रमcing a ग_लिखो */
	regmap_field_क्रमce_ग_लिखो(hdmi->field_ddc_पूर्णांक_status,
				 SUN4I_HDMI_DDC_INT_STATUS_ERROR_MASK |
				 SUN4I_HDMI_DDC_INT_STATUS_FIFO_REQUEST |
				 SUN4I_HDMI_DDC_INT_STATUS_TRANSFER_COMPLETE);

	/* Start command */
	regmap_field_ग_लिखो(hdmi->field_ddc_start, 1);

	/* Transfer bytes */
	क्रम (i = 0; i < msg->len; i += len) अणु
		len = fअगरo_transfer(hdmi, msg->buf + i, msg->len - i,
				    msg->flags & I2C_M_RD);
		अगर (len <= 0)
			वापस len;
	पूर्ण

	/* Wait क्रम command to finish */
	अगर (regmap_field_पढ़ो_poll_समयout(hdmi->field_ddc_start,
					   reg, !reg, 100, 100000))
		वापस -EIO;

	/* Check क्रम errors */
	regmap_field_पढ़ो(hdmi->field_ddc_पूर्णांक_status, &reg);
	अगर ((reg & SUN4I_HDMI_DDC_INT_STATUS_ERROR_MASK) ||
	    !(reg & SUN4I_HDMI_DDC_INT_STATUS_TRANSFER_COMPLETE)) अणु
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_hdmi_i2c_xfer(काष्ठा i2c_adapter *adap,
			       काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा sun4i_hdmi *hdmi = i2c_get_adapdata(adap);
	u32 reg;
	पूर्णांक err, i, ret = num;

	क्रम (i = 0; i < num; i++) अणु
		अगर (!msgs[i].len)
			वापस -EINVAL;
		अगर (msgs[i].len > SUN4I_HDMI_DDC_BYTE_COUNT_MAX)
			वापस -EINVAL;
	पूर्ण

	/* DDC घड़ी needs to be enabled क्रम the module to work */
	clk_prepare_enable(hdmi->ddc_clk);
	clk_set_rate(hdmi->ddc_clk, 100000);

	/* Reset I2C controller */
	regmap_field_ग_लिखो(hdmi->field_ddc_en, 1);
	regmap_field_ग_लिखो(hdmi->field_ddc_reset, 1);
	अगर (regmap_field_पढ़ो_poll_समयout(hdmi->field_ddc_reset,
					   reg, !reg, 100, 2000)) अणु
		clk_disable_unprepare(hdmi->ddc_clk);
		वापस -EIO;
	पूर्ण

	regmap_field_ग_लिखो(hdmi->field_ddc_sck_en, 1);
	regmap_field_ग_लिखो(hdmi->field_ddc_sda_en, 1);

	क्रम (i = 0; i < num; i++) अणु
		err = xfer_msg(hdmi, &msgs[i]);
		अगर (err) अणु
			ret = err;
			अवरोध;
		पूर्ण
	पूर्ण

	clk_disable_unprepare(hdmi->ddc_clk);
	वापस ret;
पूर्ण

अटल u32 sun4i_hdmi_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm sun4i_hdmi_i2c_algorithm = अणु
	.master_xfer	= sun4i_hdmi_i2c_xfer,
	.functionality	= sun4i_hdmi_i2c_func,
पूर्ण;

अटल पूर्णांक sun4i_hdmi_init_regmap_fields(काष्ठा sun4i_hdmi *hdmi)
अणु
	hdmi->field_ddc_en =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_en);
	अगर (IS_ERR(hdmi->field_ddc_en))
		वापस PTR_ERR(hdmi->field_ddc_en);

	hdmi->field_ddc_start =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_start);
	अगर (IS_ERR(hdmi->field_ddc_start))
		वापस PTR_ERR(hdmi->field_ddc_start);

	hdmi->field_ddc_reset =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_reset);
	अगर (IS_ERR(hdmi->field_ddc_reset))
		वापस PTR_ERR(hdmi->field_ddc_reset);

	hdmi->field_ddc_addr_reg =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_addr_reg);
	अगर (IS_ERR(hdmi->field_ddc_addr_reg))
		वापस PTR_ERR(hdmi->field_ddc_addr_reg);

	hdmi->field_ddc_slave_addr =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_slave_addr);
	अगर (IS_ERR(hdmi->field_ddc_slave_addr))
		वापस PTR_ERR(hdmi->field_ddc_slave_addr);

	hdmi->field_ddc_पूर्णांक_mask =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_पूर्णांक_mask);
	अगर (IS_ERR(hdmi->field_ddc_पूर्णांक_mask))
		वापस PTR_ERR(hdmi->field_ddc_पूर्णांक_mask);

	hdmi->field_ddc_पूर्णांक_status =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_पूर्णांक_status);
	अगर (IS_ERR(hdmi->field_ddc_पूर्णांक_status))
		वापस PTR_ERR(hdmi->field_ddc_पूर्णांक_status);

	hdmi->field_ddc_fअगरo_clear =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_fअगरo_clear);
	अगर (IS_ERR(hdmi->field_ddc_fअगरo_clear))
		वापस PTR_ERR(hdmi->field_ddc_fअगरo_clear);

	hdmi->field_ddc_fअगरo_rx_thres =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_fअगरo_rx_thres);
	अगर (IS_ERR(hdmi->field_ddc_fअगरo_rx_thres))
		वापस PTR_ERR(hdmi->field_ddc_fअगरo_rx_thres);

	hdmi->field_ddc_fअगरo_tx_thres =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_fअगरo_tx_thres);
	अगर (IS_ERR(hdmi->field_ddc_fअगरo_tx_thres))
		वापस PTR_ERR(hdmi->field_ddc_fअगरo_tx_thres);

	hdmi->field_ddc_byte_count =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_byte_count);
	अगर (IS_ERR(hdmi->field_ddc_byte_count))
		वापस PTR_ERR(hdmi->field_ddc_byte_count);

	hdmi->field_ddc_cmd =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_cmd);
	अगर (IS_ERR(hdmi->field_ddc_cmd))
		वापस PTR_ERR(hdmi->field_ddc_cmd);

	hdmi->field_ddc_sda_en =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_sda_en);
	अगर (IS_ERR(hdmi->field_ddc_sda_en))
		वापस PTR_ERR(hdmi->field_ddc_sda_en);

	hdmi->field_ddc_sck_en =
		devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					hdmi->variant->field_ddc_sck_en);
	अगर (IS_ERR(hdmi->field_ddc_sck_en))
		वापस PTR_ERR(hdmi->field_ddc_sck_en);

	वापस 0;
पूर्ण

पूर्णांक sun4i_hdmi_i2c_create(काष्ठा device *dev, काष्ठा sun4i_hdmi *hdmi)
अणु
	काष्ठा i2c_adapter *adap;
	पूर्णांक ret = 0;

	ret = sun4i_ddc_create(hdmi, hdmi->ddc_parent_clk);
	अगर (ret)
		वापस ret;

	ret = sun4i_hdmi_init_regmap_fields(hdmi);
	अगर (ret)
		वापस ret;

	adap = devm_kzalloc(dev, माप(*adap), GFP_KERNEL);
	अगर (!adap)
		वापस -ENOMEM;

	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_DDC;
	adap->algo = &sun4i_hdmi_i2c_algorithm;
	strlcpy(adap->name, "sun4i_hdmi_i2c adapter", माप(adap->name));
	i2c_set_adapdata(adap, hdmi);

	ret = i2c_add_adapter(adap);
	अगर (ret)
		वापस ret;

	hdmi->i2c = adap;

	वापस ret;
पूर्ण
