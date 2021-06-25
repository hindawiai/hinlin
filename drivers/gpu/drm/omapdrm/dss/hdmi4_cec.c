<शैली गुरु>
/*
 * HDMI CEC
 *
 * Based on the CEC code from hdmi_ti_4xxx_ip.c from Android.
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com/
 * Authors: Yong Zhi
 *	Mythri pk <mythripk@ti.com>
 *
 * Heavily modअगरied to use the linux CEC framework:
 *
 * Copyright 2016-2017 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
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
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "dss.h"
#समावेश "hdmi.h"
#समावेश "hdmi4_core.h"
#समावेश "hdmi4_cec.h"

/* HDMI CEC */
#घोषणा HDMI_CEC_DEV_ID                         0x900
#घोषणा HDMI_CEC_SPEC                           0x904

/* Not really a debug रेजिस्टर, more a low-level control रेजिस्टर */
#घोषणा HDMI_CEC_DBG_3                          0x91C
#घोषणा HDMI_CEC_TX_INIT                        0x920
#घोषणा HDMI_CEC_TX_DEST                        0x924
#घोषणा HDMI_CEC_SETUP                          0x938
#घोषणा HDMI_CEC_TX_COMMAND                     0x93C
#घोषणा HDMI_CEC_TX_OPERAND                     0x940
#घोषणा HDMI_CEC_TRANSMIT_DATA                  0x97C
#घोषणा HDMI_CEC_CA_7_0                         0x988
#घोषणा HDMI_CEC_CA_15_8                        0x98C
#घोषणा HDMI_CEC_INT_STATUS_0                   0x998
#घोषणा HDMI_CEC_INT_STATUS_1                   0x99C
#घोषणा HDMI_CEC_INT_ENABLE_0                   0x990
#घोषणा HDMI_CEC_INT_ENABLE_1                   0x994
#घोषणा HDMI_CEC_RX_CONTROL                     0x9B0
#घोषणा HDMI_CEC_RX_COUNT                       0x9B4
#घोषणा HDMI_CEC_RX_CMD_HEADER                  0x9B8
#घोषणा HDMI_CEC_RX_COMMAND                     0x9BC
#घोषणा HDMI_CEC_RX_OPERAND                     0x9C0

#घोषणा HDMI_CEC_TX_FIFO_INT_MASK		0x64
#घोषणा HDMI_CEC_RETRANSMIT_CNT_INT_MASK	0x2

#घोषणा HDMI_CORE_CEC_RETRY    200

अटल व्योम hdmi_cec_received_msg(काष्ठा hdmi_core_data *core)
अणु
	u32 cnt = hdmi_पढ़ो_reg(core->base, HDMI_CEC_RX_COUNT) & 0xff;

	/* While there are CEC frames in the FIFO */
	जबतक (cnt & 0x70) अणु
		/* and the frame करोesn't have an error */
		अगर (!(cnt & 0x80)) अणु
			काष्ठा cec_msg msg = अणुपूर्ण;
			अचिन्हित पूर्णांक i;

			/* then पढ़ो the message */
			msg.len = cnt & 0xf;
			अगर (msg.len > CEC_MAX_MSG_SIZE - 2)
				msg.len = CEC_MAX_MSG_SIZE - 2;
			msg.msg[0] = hdmi_पढ़ो_reg(core->base,
						   HDMI_CEC_RX_CMD_HEADER);
			msg.msg[1] = hdmi_पढ़ो_reg(core->base,
						   HDMI_CEC_RX_COMMAND);
			क्रम (i = 0; i < msg.len; i++) अणु
				अचिन्हित पूर्णांक reg = HDMI_CEC_RX_OPERAND + i * 4;

				msg.msg[2 + i] =
					hdmi_पढ़ो_reg(core->base, reg);
			पूर्ण
			msg.len += 2;
			cec_received_msg(core->adap, &msg);
		पूर्ण
		/* Clear the current frame from the FIFO */
		hdmi_ग_लिखो_reg(core->base, HDMI_CEC_RX_CONTROL, 1);
		/* Wait until the current frame is cleared */
		जबतक (hdmi_पढ़ो_reg(core->base, HDMI_CEC_RX_CONTROL) & 1)
			udelay(1);
		/*
		 * Re-पढ़ो the count रेजिस्टर and loop to see अगर there are
		 * more messages in the FIFO.
		 */
		cnt = hdmi_पढ़ो_reg(core->base, HDMI_CEC_RX_COUNT) & 0xff;
	पूर्ण
पूर्ण

व्योम hdmi4_cec_irq(काष्ठा hdmi_core_data *core)
अणु
	u32 stat0 = hdmi_पढ़ो_reg(core->base, HDMI_CEC_INT_STATUS_0);
	u32 stat1 = hdmi_पढ़ो_reg(core->base, HDMI_CEC_INT_STATUS_1);

	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_INT_STATUS_0, stat0);
	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_INT_STATUS_1, stat1);

	अगर (stat0 & 0x20) अणु
		cec_transmit_करोne(core->adap, CEC_TX_STATUS_OK,
				  0, 0, 0, 0);
		REG_FLD_MOD(core->base, HDMI_CEC_DBG_3, 0x1, 7, 7);
	पूर्ण अन्यथा अगर (stat1 & 0x02) अणु
		u32 dbg3 = hdmi_पढ़ो_reg(core->base, HDMI_CEC_DBG_3);

		cec_transmit_करोne(core->adap,
				  CEC_TX_STATUS_NACK |
				  CEC_TX_STATUS_MAX_RETRIES,
				  0, (dbg3 >> 4) & 7, 0, 0);
		REG_FLD_MOD(core->base, HDMI_CEC_DBG_3, 0x1, 7, 7);
	पूर्ण
	अगर (stat0 & 0x02)
		hdmi_cec_received_msg(core);
पूर्ण

अटल bool hdmi_cec_clear_tx_fअगरo(काष्ठा cec_adapter *adap)
अणु
	काष्ठा hdmi_core_data *core = cec_get_drvdata(adap);
	पूर्णांक retry = HDMI_CORE_CEC_RETRY;
	पूर्णांक temp;

	REG_FLD_MOD(core->base, HDMI_CEC_DBG_3, 0x1, 7, 7);
	जबतक (retry) अणु
		temp = hdmi_पढ़ो_reg(core->base, HDMI_CEC_DBG_3);
		अगर (FLD_GET(temp, 7, 7) == 0)
			अवरोध;
		retry--;
	पूर्ण
	वापस retry != 0;
पूर्ण

अटल bool hdmi_cec_clear_rx_fअगरo(काष्ठा cec_adapter *adap)
अणु
	काष्ठा hdmi_core_data *core = cec_get_drvdata(adap);
	पूर्णांक retry = HDMI_CORE_CEC_RETRY;
	पूर्णांक temp;

	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_RX_CONTROL, 0x3);
	retry = HDMI_CORE_CEC_RETRY;
	जबतक (retry) अणु
		temp = hdmi_पढ़ो_reg(core->base, HDMI_CEC_RX_CONTROL);
		अगर (FLD_GET(temp, 1, 0) == 0)
			अवरोध;
		retry--;
	पूर्ण
	वापस retry != 0;
पूर्ण

अटल पूर्णांक hdmi_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा hdmi_core_data *core = cec_get_drvdata(adap);
	पूर्णांक temp, err;

	अगर (!enable) अणु
		hdmi_ग_लिखो_reg(core->base, HDMI_CEC_INT_ENABLE_0, 0);
		hdmi_ग_लिखो_reg(core->base, HDMI_CEC_INT_ENABLE_1, 0);
		REG_FLD_MOD(core->base, HDMI_CORE_SYS_INTR_UNMASK4, 0, 3, 3);
		hdmi_wp_clear_irqenable(core->wp, HDMI_IRQ_CORE);
		hdmi_wp_set_irqstatus(core->wp, HDMI_IRQ_CORE);
		REG_FLD_MOD(core->wp->base, HDMI_WP_CLK, 0, 5, 0);
		hdmi4_core_disable(core);
		वापस 0;
	पूर्ण
	err = hdmi4_core_enable(core);
	अगर (err)
		वापस err;

	/*
	 * Initialize CEC घड़ी भागider: CEC needs 2MHz घड़ी hence
	 * set the भागider to 24 to get 48/24=2MHz घड़ी
	 */
	REG_FLD_MOD(core->wp->base, HDMI_WP_CLK, 0x18, 5, 0);

	/* Clear TX FIFO */
	अगर (!hdmi_cec_clear_tx_fअगरo(adap)) अणु
		pr_err("cec-%s: could not clear TX FIFO\n", adap->name);
		err = -EIO;
		जाओ err_disable_clk;
	पूर्ण

	/* Clear RX FIFO */
	अगर (!hdmi_cec_clear_rx_fअगरo(adap)) अणु
		pr_err("cec-%s: could not clear RX FIFO\n", adap->name);
		err = -EIO;
		जाओ err_disable_clk;
	पूर्ण

	/* Clear CEC पूर्णांकerrupts */
	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_INT_STATUS_1,
		hdmi_पढ़ो_reg(core->base, HDMI_CEC_INT_STATUS_1));
	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_INT_STATUS_0,
		hdmi_पढ़ो_reg(core->base, HDMI_CEC_INT_STATUS_0));

	/* Enable HDMI core पूर्णांकerrupts */
	hdmi_wp_set_irqenable(core->wp, HDMI_IRQ_CORE);
	/* Unmask CEC पूर्णांकerrupt */
	REG_FLD_MOD(core->base, HDMI_CORE_SYS_INTR_UNMASK4, 0x1, 3, 3);
	/*
	 * Enable CEC पूर्णांकerrupts:
	 * Transmit Buffer Full/Empty Change event
	 * Receiver FIFO Not Empty event
	 */
	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_INT_ENABLE_0, 0x22);
	/*
	 * Enable CEC पूर्णांकerrupts:
	 * Frame Retransmit Count Exceeded event
	 */
	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_INT_ENABLE_1, 0x02);

	/* cec calibration enable (self clearing) */
	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_SETUP, 0x03);
	msleep(20);
	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_SETUP, 0x04);

	temp = hdmi_पढ़ो_reg(core->base, HDMI_CEC_SETUP);
	अगर (FLD_GET(temp, 4, 4) != 0) अणु
		temp = FLD_MOD(temp, 0, 4, 4);
		hdmi_ग_लिखो_reg(core->base, HDMI_CEC_SETUP, temp);

		/*
		 * If we enabled CEC in middle of a CEC message on the bus,
		 * we could have start bit irregularity and/or लघु
		 * pulse event. Clear them now.
		 */
		temp = hdmi_पढ़ो_reg(core->base, HDMI_CEC_INT_STATUS_1);
		temp = FLD_MOD(0x0, 0x5, 2, 0);
		hdmi_ग_लिखो_reg(core->base, HDMI_CEC_INT_STATUS_1, temp);
	पूर्ण
	वापस 0;

err_disable_clk:
	REG_FLD_MOD(core->wp->base, HDMI_WP_CLK, 0, 5, 0);
	hdmi4_core_disable(core);

	वापस err;
पूर्ण

अटल पूर्णांक hdmi_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 log_addr)
अणु
	काष्ठा hdmi_core_data *core = cec_get_drvdata(adap);
	u32 v;

	अगर (log_addr == CEC_LOG_ADDR_INVALID) अणु
		hdmi_ग_लिखो_reg(core->base, HDMI_CEC_CA_7_0, 0);
		hdmi_ग_लिखो_reg(core->base, HDMI_CEC_CA_15_8, 0);
		वापस 0;
	पूर्ण
	अगर (log_addr <= 7) अणु
		v = hdmi_पढ़ो_reg(core->base, HDMI_CEC_CA_7_0);
		v |= 1 << log_addr;
		hdmi_ग_लिखो_reg(core->base, HDMI_CEC_CA_7_0, v);
	पूर्ण अन्यथा अणु
		v = hdmi_पढ़ो_reg(core->base, HDMI_CEC_CA_15_8);
		v |= 1 << (log_addr - 8);
		hdmi_ग_लिखो_reg(core->base, HDMI_CEC_CA_15_8, v);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				   u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा hdmi_core_data *core = cec_get_drvdata(adap);
	पूर्णांक temp;
	u32 i;

	/* Clear TX FIFO */
	अगर (!hdmi_cec_clear_tx_fअगरo(adap)) अणु
		pr_err("cec-%s: could not clear TX FIFO for transmit\n",
		       adap->name);
		वापस -EIO;
	पूर्ण

	/* Clear TX पूर्णांकerrupts */
	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_INT_STATUS_0,
		       HDMI_CEC_TX_FIFO_INT_MASK);

	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_INT_STATUS_1,
		       HDMI_CEC_RETRANSMIT_CNT_INT_MASK);

	/* Set the retry count */
	REG_FLD_MOD(core->base, HDMI_CEC_DBG_3, attempts - 1, 6, 4);

	/* Set the initiator addresses */
	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_TX_INIT, cec_msg_initiator(msg));

	/* Set destination id */
	temp = cec_msg_destination(msg);
	अगर (msg->len == 1)
		temp |= 0x80;
	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_TX_DEST, temp);
	अगर (msg->len == 1)
		वापस 0;

	/* Setup command and arguments क्रम the command */
	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_TX_COMMAND, msg->msg[1]);

	क्रम (i = 0; i < msg->len - 2; i++)
		hdmi_ग_लिखो_reg(core->base, HDMI_CEC_TX_OPERAND + i * 4,
			       msg->msg[2 + i]);

	/* Opeअक्रम count */
	hdmi_ग_लिखो_reg(core->base, HDMI_CEC_TRANSMIT_DATA,
		       (msg->len - 2) | 0x10);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops hdmi_cec_adap_ops = अणु
	.adap_enable = hdmi_cec_adap_enable,
	.adap_log_addr = hdmi_cec_adap_log_addr,
	.adap_transmit = hdmi_cec_adap_transmit,
पूर्ण;

व्योम hdmi4_cec_set_phys_addr(काष्ठा hdmi_core_data *core, u16 pa)
अणु
	cec_s_phys_addr(core->adap, pa, false);
पूर्ण

पूर्णांक hdmi4_cec_init(काष्ठा platक्रमm_device *pdev, काष्ठा hdmi_core_data *core,
		  काष्ठा hdmi_wp_data *wp)
अणु
	स्थिर u32 caps = CEC_CAP_TRANSMIT | CEC_CAP_LOG_ADDRS |
			 CEC_CAP_PASSTHROUGH | CEC_CAP_RC;
	पूर्णांक ret;

	core->adap = cec_allocate_adapter(&hdmi_cec_adap_ops, core,
		"omap4", caps, CEC_MAX_LOG_ADDRS);
	ret = PTR_ERR_OR_ZERO(core->adap);
	अगर (ret < 0)
		वापस ret;
	core->wp = wp;

	/* Disable घड़ी initially, hdmi_cec_adap_enable() manages it */
	REG_FLD_MOD(core->wp->base, HDMI_WP_CLK, 0, 5, 0);

	ret = cec_रेजिस्टर_adapter(core->adap, &pdev->dev);
	अगर (ret < 0) अणु
		cec_delete_adapter(core->adap);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

व्योम hdmi4_cec_uninit(काष्ठा hdmi_core_data *core)
अणु
	cec_unरेजिस्टर_adapter(core->adap);
पूर्ण
