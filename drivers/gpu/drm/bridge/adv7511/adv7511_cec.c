<शैली गुरु>
/*
 * adv7511_cec.c - Analog Devices ADV7511/33 cec driver
 *
 * Copyright 2017 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>

#समावेश <media/cec.h>

#समावेश "adv7511.h"

#घोषणा ADV7511_INT1_CEC_MASK \
	(ADV7511_INT1_CEC_TX_READY | ADV7511_INT1_CEC_TX_ARBIT_LOST | \
	 ADV7511_INT1_CEC_TX_RETRY_TIMEOUT | ADV7511_INT1_CEC_RX_READY1)

अटल व्योम adv_cec_tx_raw_status(काष्ठा adv7511 *adv7511, u8 tx_raw_status)
अणु
	अचिन्हित पूर्णांक offset = adv7511->type == ADV7533 ?
					ADV7533_REG_CEC_OFFSET : 0;
	अचिन्हित पूर्णांक val;

	अगर (regmap_पढ़ो(adv7511->regmap_cec,
			ADV7511_REG_CEC_TX_ENABLE + offset, &val))
		वापस;

	अगर ((val & 0x01) == 0)
		वापस;

	अगर (tx_raw_status & ADV7511_INT1_CEC_TX_ARBIT_LOST) अणु
		cec_transmit_attempt_करोne(adv7511->cec_adap,
					  CEC_TX_STATUS_ARB_LOST);
		वापस;
	पूर्ण
	अगर (tx_raw_status & ADV7511_INT1_CEC_TX_RETRY_TIMEOUT) अणु
		u8 status;
		u8 err_cnt = 0;
		u8 nack_cnt = 0;
		u8 low_drive_cnt = 0;
		अचिन्हित पूर्णांक cnt;

		/*
		 * We set this status bit since this hardware perक्रमms
		 * retransmissions.
		 */
		status = CEC_TX_STATUS_MAX_RETRIES;
		अगर (regmap_पढ़ो(adv7511->regmap_cec,
			    ADV7511_REG_CEC_TX_LOW_DRV_CNT + offset, &cnt)) अणु
			err_cnt = 1;
			status |= CEC_TX_STATUS_ERROR;
		पूर्ण अन्यथा अणु
			nack_cnt = cnt & 0xf;
			अगर (nack_cnt)
				status |= CEC_TX_STATUS_NACK;
			low_drive_cnt = cnt >> 4;
			अगर (low_drive_cnt)
				status |= CEC_TX_STATUS_LOW_DRIVE;
		पूर्ण
		cec_transmit_करोne(adv7511->cec_adap, status,
				  0, nack_cnt, low_drive_cnt, err_cnt);
		वापस;
	पूर्ण
	अगर (tx_raw_status & ADV7511_INT1_CEC_TX_READY) अणु
		cec_transmit_attempt_करोne(adv7511->cec_adap, CEC_TX_STATUS_OK);
		वापस;
	पूर्ण
पूर्ण

व्योम adv7511_cec_irq_process(काष्ठा adv7511 *adv7511, अचिन्हित पूर्णांक irq1)
अणु
	अचिन्हित पूर्णांक offset = adv7511->type == ADV7533 ?
					ADV7533_REG_CEC_OFFSET : 0;
	स्थिर u32 irq_tx_mask = ADV7511_INT1_CEC_TX_READY |
				ADV7511_INT1_CEC_TX_ARBIT_LOST |
				ADV7511_INT1_CEC_TX_RETRY_TIMEOUT;
	काष्ठा cec_msg msg = अणुपूर्ण;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक val;
	u8 i;

	अगर (irq1 & irq_tx_mask)
		adv_cec_tx_raw_status(adv7511, irq1);

	अगर (!(irq1 & ADV7511_INT1_CEC_RX_READY1))
		वापस;

	अगर (regmap_पढ़ो(adv7511->regmap_cec,
			ADV7511_REG_CEC_RX_FRAME_LEN + offset, &len))
		वापस;

	msg.len = len & 0x1f;

	अगर (msg.len > 16)
		msg.len = 16;

	अगर (!msg.len)
		वापस;

	क्रम (i = 0; i < msg.len; i++) अणु
		regmap_पढ़ो(adv7511->regmap_cec,
			    i + ADV7511_REG_CEC_RX_FRAME_HDR + offset, &val);
		msg.msg[i] = val;
	पूर्ण

	/* toggle to re-enable rx 1 */
	regmap_ग_लिखो(adv7511->regmap_cec,
		     ADV7511_REG_CEC_RX_BUFFERS + offset, 1);
	regmap_ग_लिखो(adv7511->regmap_cec,
		     ADV7511_REG_CEC_RX_BUFFERS + offset, 0);
	cec_received_msg(adv7511->cec_adap, &msg);
पूर्ण

अटल पूर्णांक adv7511_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा adv7511 *adv7511 = cec_get_drvdata(adap);
	अचिन्हित पूर्णांक offset = adv7511->type == ADV7533 ?
					ADV7533_REG_CEC_OFFSET : 0;

	अगर (adv7511->i2c_cec == शून्य)
		वापस -EIO;

	अगर (!adv7511->cec_enabled_adap && enable) अणु
		/* घातer up cec section */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_CLK_DIV + offset,
				   0x03, 0x01);
		/* legacy mode and clear all rx buffers */
		regmap_ग_लिखो(adv7511->regmap_cec,
			     ADV7511_REG_CEC_RX_BUFFERS + offset, 0x07);
		regmap_ग_लिखो(adv7511->regmap_cec,
			     ADV7511_REG_CEC_RX_BUFFERS + offset, 0);
		/* initially disable tx */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_TX_ENABLE + offset, 1, 0);
		/* enabled irqs: */
		/* tx: पढ़ोy */
		/* tx: arbitration lost */
		/* tx: retry समयout */
		/* rx: पढ़ोy 1 */
		regmap_update_bits(adv7511->regmap,
				   ADV7511_REG_INT_ENABLE(1), 0x3f,
				   ADV7511_INT1_CEC_MASK);
	पूर्ण अन्यथा अगर (adv7511->cec_enabled_adap && !enable) अणु
		regmap_update_bits(adv7511->regmap,
				   ADV7511_REG_INT_ENABLE(1), 0x3f, 0);
		/* disable address mask 1-3 */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_LOG_ADDR_MASK + offset,
				   0x70, 0x00);
		/* घातer करोwn cec section */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_CLK_DIV + offset,
				   0x03, 0x00);
		adv7511->cec_valid_addrs = 0;
	पूर्ण
	adv7511->cec_enabled_adap = enable;
	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 addr)
अणु
	काष्ठा adv7511 *adv7511 = cec_get_drvdata(adap);
	अचिन्हित पूर्णांक offset = adv7511->type == ADV7533 ?
					ADV7533_REG_CEC_OFFSET : 0;
	अचिन्हित पूर्णांक i, मुक्त_idx = ADV7511_MAX_ADDRS;

	अगर (!adv7511->cec_enabled_adap)
		वापस addr == CEC_LOG_ADDR_INVALID ? 0 : -EIO;

	अगर (addr == CEC_LOG_ADDR_INVALID) अणु
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_LOG_ADDR_MASK + offset,
				   0x70, 0);
		adv7511->cec_valid_addrs = 0;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ADV7511_MAX_ADDRS; i++) अणु
		bool is_valid = adv7511->cec_valid_addrs & (1 << i);

		अगर (मुक्त_idx == ADV7511_MAX_ADDRS && !is_valid)
			मुक्त_idx = i;
		अगर (is_valid && adv7511->cec_addr[i] == addr)
			वापस 0;
	पूर्ण
	अगर (i == ADV7511_MAX_ADDRS) अणु
		i = मुक्त_idx;
		अगर (i == ADV7511_MAX_ADDRS)
			वापस -ENXIO;
	पूर्ण
	adv7511->cec_addr[i] = addr;
	adv7511->cec_valid_addrs |= 1 << i;

	चयन (i) अणु
	हाल 0:
		/* enable address mask 0 */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_LOG_ADDR_MASK + offset,
				   0x10, 0x10);
		/* set address क्रम mask 0 */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_LOG_ADDR_0_1 + offset,
				   0x0f, addr);
		अवरोध;
	हाल 1:
		/* enable address mask 1 */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_LOG_ADDR_MASK + offset,
				   0x20, 0x20);
		/* set address क्रम mask 1 */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_LOG_ADDR_0_1 + offset,
				   0xf0, addr << 4);
		अवरोध;
	हाल 2:
		/* enable address mask 2 */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_LOG_ADDR_MASK + offset,
				   0x40, 0x40);
		/* set address क्रम mask 1 */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_LOG_ADDR_2 + offset,
				   0x0f, addr);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				     u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा adv7511 *adv7511 = cec_get_drvdata(adap);
	अचिन्हित पूर्णांक offset = adv7511->type == ADV7533 ?
					ADV7533_REG_CEC_OFFSET : 0;
	u8 len = msg->len;
	अचिन्हित पूर्णांक i;

	/*
	 * The number of retries is the number of attempts - 1, but retry
	 * at least once. It's not clear अगर a value of 0 is allowed, so
	 * let's करो at least one retry.
	 */
	regmap_update_bits(adv7511->regmap_cec,
			   ADV7511_REG_CEC_TX_RETRY + offset,
			   0x70, max(1, attempts - 1) << 4);

	/* blocking, clear cec tx irq status */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_INT(1), 0x38, 0x38);

	/* ग_लिखो data */
	क्रम (i = 0; i < len; i++)
		regmap_ग_लिखो(adv7511->regmap_cec,
			     i + ADV7511_REG_CEC_TX_FRAME_HDR + offset,
			     msg->msg[i]);

	/* set length (data + header) */
	regmap_ग_लिखो(adv7511->regmap_cec,
		     ADV7511_REG_CEC_TX_FRAME_LEN + offset, len);
	/* start transmit, enable tx */
	regmap_ग_लिखो(adv7511->regmap_cec,
		     ADV7511_REG_CEC_TX_ENABLE + offset, 0x01);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops adv7511_cec_adap_ops = अणु
	.adap_enable = adv7511_cec_adap_enable,
	.adap_log_addr = adv7511_cec_adap_log_addr,
	.adap_transmit = adv7511_cec_adap_transmit,
पूर्ण;

अटल पूर्णांक adv7511_cec_parse_dt(काष्ठा device *dev, काष्ठा adv7511 *adv7511)
अणु
	adv7511->cec_clk = devm_clk_get(dev, "cec");
	अगर (IS_ERR(adv7511->cec_clk)) अणु
		पूर्णांक ret = PTR_ERR(adv7511->cec_clk);

		adv7511->cec_clk = शून्य;
		वापस ret;
	पूर्ण
	clk_prepare_enable(adv7511->cec_clk);
	adv7511->cec_clk_freq = clk_get_rate(adv7511->cec_clk);
	वापस 0;
पूर्ण

पूर्णांक adv7511_cec_init(काष्ठा device *dev, काष्ठा adv7511 *adv7511)
अणु
	अचिन्हित पूर्णांक offset = adv7511->type == ADV7533 ?
						ADV7533_REG_CEC_OFFSET : 0;
	पूर्णांक ret = adv7511_cec_parse_dt(dev, adv7511);

	अगर (ret)
		जाओ err_cec_parse_dt;

	adv7511->cec_adap = cec_allocate_adapter(&adv7511_cec_adap_ops,
		adv7511, dev_name(dev), CEC_CAP_DEFAULTS, ADV7511_MAX_ADDRS);
	अगर (IS_ERR(adv7511->cec_adap)) अणु
		ret = PTR_ERR(adv7511->cec_adap);
		जाओ err_cec_alloc;
	पूर्ण

	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_CEC_CTRL + offset, 0);
	/* cec soft reset */
	regmap_ग_लिखो(adv7511->regmap_cec,
		     ADV7511_REG_CEC_SOFT_RESET + offset, 0x01);
	regmap_ग_लिखो(adv7511->regmap_cec,
		     ADV7511_REG_CEC_SOFT_RESET + offset, 0x00);

	/* legacy mode */
	regmap_ग_लिखो(adv7511->regmap_cec,
		     ADV7511_REG_CEC_RX_BUFFERS + offset, 0x00);

	regmap_ग_लिखो(adv7511->regmap_cec,
		     ADV7511_REG_CEC_CLK_DIV + offset,
		     ((adv7511->cec_clk_freq / 750000) - 1) << 2);

	ret = cec_रेजिस्टर_adapter(adv7511->cec_adap, dev);
	अगर (ret)
		जाओ err_cec_रेजिस्टर;
	वापस 0;

err_cec_रेजिस्टर:
	cec_delete_adapter(adv7511->cec_adap);
	adv7511->cec_adap = शून्य;
err_cec_alloc:
	dev_info(dev, "Initializing CEC failed with error %d, disabling CEC\n",
		 ret);
err_cec_parse_dt:
	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_CEC_CTRL + offset,
		     ADV7511_CEC_CTRL_POWER_DOWN);
	वापस ret == -EPROBE_DEFER ? ret : 0;
पूर्ण
