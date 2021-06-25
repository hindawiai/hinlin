<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Silicon Image SiI8620 HDMI/MHL bridge driver
 *
 * Copyright (C) 2015, Samsung Electronics Co., Ltd.
 * Andrzej Hajda <a.hajda@samsung.com>
 */

#समावेश <यंत्र/unaligned.h>

#समावेश <drm/bridge/mhl.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_encoder.h>

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/extcon.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <media/rc-core.h>

#समावेश "sil-sii8620.h"

#घोषणा SII8620_BURST_BUF_LEN 288
#घोषणा VAL_RX_HDMI_CTRL2_DEFVAL VAL_RX_HDMI_CTRL2_IDLE_CNT(3)

#घोषणा MHL1_MAX_PCLK 75000
#घोषणा MHL1_MAX_PCLK_PP_MODE 150000
#घोषणा MHL3_MAX_PCLK 200000
#घोषणा MHL3_MAX_PCLK_PP_MODE 300000

क्रमागत sii8620_mode अणु
	CM_DISCONNECTED,
	CM_DISCOVERY,
	CM_MHL1,
	CM_MHL3,
	CM_ECBUS_S
पूर्ण;

क्रमागत sii8620_sink_type अणु
	SINK_NONE,
	SINK_HDMI,
	SINK_DVI
पूर्ण;

क्रमागत sii8620_mt_state अणु
	MT_STATE_READY,
	MT_STATE_BUSY,
	MT_STATE_DONE
पूर्ण;

काष्ठा sii8620 अणु
	काष्ठा drm_bridge bridge;
	काष्ठा device *dev;
	काष्ठा rc_dev *rc_dev;
	काष्ठा clk *clk_xtal;
	काष्ठा gpio_desc *gpio_reset;
	काष्ठा gpio_desc *gpio_पूर्णांक;
	काष्ठा regulator_bulk_data supplies[2];
	काष्ठा mutex lock; /* context lock, protects fields below */
	पूर्णांक error;
	अचिन्हित पूर्णांक use_packed_pixel:1;
	क्रमागत sii8620_mode mode;
	क्रमागत sii8620_sink_type sink_type;
	u8 cbus_status;
	u8 stat[MHL_DST_SIZE];
	u8 xstat[MHL_XDS_SIZE];
	u8 devcap[MHL_DCAP_SIZE];
	u8 xdevcap[MHL_XDC_SIZE];
	bool feature_complete;
	bool devcap_पढ़ो;
	bool sink_detected;
	काष्ठा edid *edid;
	अचिन्हित पूर्णांक gen2_ग_लिखो_burst:1;
	क्रमागत sii8620_mt_state mt_state;
	काष्ठा extcon_dev *extcon;
	काष्ठा notअगरier_block extcon_nb;
	काष्ठा work_काष्ठा extcon_wq;
	पूर्णांक cable_state;
	काष्ठा list_head mt_queue;
	काष्ठा अणु
		पूर्णांक r_size;
		पूर्णांक r_count;
		पूर्णांक rx_ack;
		पूर्णांक rx_count;
		u8 rx_buf[32];
		पूर्णांक tx_count;
		u8 tx_buf[32];
	पूर्ण burst;
पूर्ण;

काष्ठा sii8620_mt_msg;

प्रकार व्योम (*sii8620_mt_msg_cb)(काष्ठा sii8620 *ctx,
				  काष्ठा sii8620_mt_msg *msg);

प्रकार व्योम (*sii8620_cb)(काष्ठा sii8620 *ctx, पूर्णांक ret);

काष्ठा sii8620_mt_msg अणु
	काष्ठा list_head node;
	u8 reg[4];
	u8 ret;
	sii8620_mt_msg_cb send;
	sii8620_mt_msg_cb recv;
	sii8620_cb continuation;
पूर्ण;

अटल स्थिर u8 sii8620_i2c_page[] = अणु
	0x39, /* Main System */
	0x3d, /* TDM and HSIC */
	0x49, /* TMDS Receiver, MHL EDID */
	0x4d, /* eMSC, HDCP, HSIC */
	0x5d, /* MHL Spec */
	0x64, /* MHL CBUS */
	0x59, /* Hardware TPI (Transmitter Programming Interface) */
	0x61, /* eCBUS-S, eCBUS-D */
पूर्ण;

अटल व्योम sii8620_fetch_edid(काष्ठा sii8620 *ctx);
अटल व्योम sii8620_set_upstream_edid(काष्ठा sii8620 *ctx);
अटल व्योम sii8620_enable_hpd(काष्ठा sii8620 *ctx);
अटल व्योम sii8620_mhl_disconnected(काष्ठा sii8620 *ctx);
अटल व्योम sii8620_disconnect(काष्ठा sii8620 *ctx);

अटल पूर्णांक sii8620_clear_error(काष्ठा sii8620 *ctx)
अणु
	पूर्णांक ret = ctx->error;

	ctx->error = 0;
	वापस ret;
पूर्ण

अटल व्योम sii8620_पढ़ो_buf(काष्ठा sii8620 *ctx, u16 addr, u8 *buf, पूर्णांक len)
अणु
	काष्ठा device *dev = ctx->dev;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 data = addr;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = sii8620_i2c_page[addr >> 8],
			.flags = client->flags,
			.len = 1,
			.buf = &data
		पूर्ण,
		अणु
			.addr = sii8620_i2c_page[addr >> 8],
			.flags = client->flags | I2C_M_RD,
			.len = len,
			.buf = buf
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	अगर (ctx->error)
		वापस;

	ret = i2c_transfer(client->adapter, msg, 2);
	dev_dbg(dev, "read at %04x: %*ph, %d\n", addr, len, buf, ret);

	अगर (ret != 2) अणु
		dev_err(dev, "Read at %#06x of %d bytes failed with code %d.\n",
			addr, len, ret);
		ctx->error = ret < 0 ? ret : -EIO;
	पूर्ण
पूर्ण

अटल u8 sii8620_पढ़ोb(काष्ठा sii8620 *ctx, u16 addr)
अणु
	u8 ret = 0;

	sii8620_पढ़ो_buf(ctx, addr, &ret, 1);
	वापस ret;
पूर्ण

अटल व्योम sii8620_ग_लिखो_buf(काष्ठा sii8620 *ctx, u16 addr, स्थिर u8 *buf,
			      पूर्णांक len)
अणु
	काष्ठा device *dev = ctx->dev;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 data[2];
	काष्ठा i2c_msg msg = अणु
		.addr = sii8620_i2c_page[addr >> 8],
		.flags = client->flags,
		.len = len + 1,
	पूर्ण;
	पूर्णांक ret;

	अगर (ctx->error)
		वापस;

	अगर (len > 1) अणु
		msg.buf = kदो_स्मृति(len + 1, GFP_KERNEL);
		अगर (!msg.buf) अणु
			ctx->error = -ENOMEM;
			वापस;
		पूर्ण
		स_नकल(msg.buf + 1, buf, len);
	पूर्ण अन्यथा अणु
		msg.buf = data;
		msg.buf[1] = *buf;
	पूर्ण

	msg.buf[0] = addr;

	ret = i2c_transfer(client->adapter, &msg, 1);
	dev_dbg(dev, "write at %04x: %*ph, %d\n", addr, len, buf, ret);

	अगर (ret != 1) अणु
		dev_err(dev, "Write at %#06x of %*ph failed with code %d.\n",
			addr, len, buf, ret);
		ctx->error = ret ?: -EIO;
	पूर्ण

	अगर (len > 1)
		kमुक्त(msg.buf);
पूर्ण

#घोषणा sii8620_ग_लिखो(ctx, addr, arr...) \
(अणु\
	u8 d[] = अणु arr पूर्ण; \
	sii8620_ग_लिखो_buf(ctx, addr, d, ARRAY_SIZE(d)); \
पूर्ण)

अटल व्योम __sii8620_ग_लिखो_seq(काष्ठा sii8620 *ctx, स्थिर u16 *seq, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i += 2)
		sii8620_ग_लिखो(ctx, seq[i], seq[i + 1]);
पूर्ण

#घोषणा sii8620_ग_लिखो_seq(ctx, seq...) \
(अणु\
	स्थिर u16 d[] = अणु seq पूर्ण; \
	__sii8620_ग_लिखो_seq(ctx, d, ARRAY_SIZE(d)); \
पूर्ण)

#घोषणा sii8620_ग_लिखो_seq_अटल(ctx, seq...) \
(अणु\
	अटल स्थिर u16 d[] = अणु seq पूर्ण; \
	__sii8620_ग_लिखो_seq(ctx, d, ARRAY_SIZE(d)); \
पूर्ण)

अटल व्योम sii8620_setbits(काष्ठा sii8620 *ctx, u16 addr, u8 mask, u8 val)
अणु
	val = (val & mask) | (sii8620_पढ़ोb(ctx, addr) & ~mask);
	sii8620_ग_लिखो(ctx, addr, val);
पूर्ण

अटल अंतरभूत bool sii8620_is_mhl3(काष्ठा sii8620 *ctx)
अणु
	वापस ctx->mode >= CM_MHL3;
पूर्ण

अटल व्योम sii8620_mt_cleanup(काष्ठा sii8620 *ctx)
अणु
	काष्ठा sii8620_mt_msg *msg, *n;

	list_क्रम_each_entry_safe(msg, n, &ctx->mt_queue, node) अणु
		list_del(&msg->node);
		kमुक्त(msg);
	पूर्ण
	ctx->mt_state = MT_STATE_READY;
पूर्ण

अटल व्योम sii8620_mt_work(काष्ठा sii8620 *ctx)
अणु
	काष्ठा sii8620_mt_msg *msg;

	अगर (ctx->error)
		वापस;
	अगर (ctx->mt_state == MT_STATE_BUSY || list_empty(&ctx->mt_queue))
		वापस;

	अगर (ctx->mt_state == MT_STATE_DONE) अणु
		ctx->mt_state = MT_STATE_READY;
		msg = list_first_entry(&ctx->mt_queue, काष्ठा sii8620_mt_msg,
				       node);
		list_del(&msg->node);
		अगर (msg->recv)
			msg->recv(ctx, msg);
		अगर (msg->continuation)
			msg->continuation(ctx, msg->ret);
		kमुक्त(msg);
	पूर्ण

	अगर (ctx->mt_state != MT_STATE_READY || list_empty(&ctx->mt_queue))
		वापस;

	ctx->mt_state = MT_STATE_BUSY;
	msg = list_first_entry(&ctx->mt_queue, काष्ठा sii8620_mt_msg, node);
	अगर (msg->send)
		msg->send(ctx, msg);
पूर्ण

अटल व्योम sii8620_enable_gen2_ग_लिखो_burst(काष्ठा sii8620 *ctx)
अणु
	u8 ctrl = BIT_MDT_RCV_CTRL_MDT_RCV_EN;

	अगर (ctx->gen2_ग_लिखो_burst)
		वापस;

	अगर (ctx->mode >= CM_MHL1)
		ctrl |= BIT_MDT_RCV_CTRL_MDT_DELAY_RCV_EN;

	sii8620_ग_लिखो_seq(ctx,
		REG_MDT_RCV_TIMEOUT, 100,
		REG_MDT_RCV_CTRL, ctrl
	);
	ctx->gen2_ग_लिखो_burst = 1;
पूर्ण

अटल व्योम sii8620_disable_gen2_ग_लिखो_burst(काष्ठा sii8620 *ctx)
अणु
	अगर (!ctx->gen2_ग_लिखो_burst)
		वापस;

	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_MDT_XMIT_CTRL, 0,
		REG_MDT_RCV_CTRL, 0
	);
	ctx->gen2_ग_लिखो_burst = 0;
पूर्ण

अटल व्योम sii8620_start_gen2_ग_लिखो_burst(काष्ठा sii8620 *ctx)
अणु
	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_MDT_INT_1_MASK, BIT_MDT_RCV_TIMEOUT
			| BIT_MDT_RCV_SM_ABORT_PKT_RCVD | BIT_MDT_RCV_SM_ERROR
			| BIT_MDT_XMIT_TIMEOUT | BIT_MDT_XMIT_SM_ABORT_PKT_RCVD
			| BIT_MDT_XMIT_SM_ERROR,
		REG_MDT_INT_0_MASK, BIT_MDT_XFIFO_EMPTY
			| BIT_MDT_IDLE_AFTER_HAWB_DISABLE
			| BIT_MDT_RFIFO_DATA_RDY
	);
	sii8620_enable_gen2_ग_लिखो_burst(ctx);
पूर्ण

अटल व्योम sii8620_mt_msc_cmd_send(काष्ठा sii8620 *ctx,
				    काष्ठा sii8620_mt_msg *msg)
अणु
	अगर (msg->reg[0] == MHL_SET_INT &&
	    msg->reg[1] == MHL_INT_REG(RCHANGE) &&
	    msg->reg[2] == MHL_INT_RC_FEAT_REQ)
		sii8620_enable_gen2_ग_लिखो_burst(ctx);
	अन्यथा
		sii8620_disable_gen2_ग_लिखो_burst(ctx);

	चयन (msg->reg[0]) अणु
	हाल MHL_WRITE_STAT:
	हाल MHL_SET_INT:
		sii8620_ग_लिखो_buf(ctx, REG_MSC_CMD_OR_OFFSET, msg->reg + 1, 2);
		sii8620_ग_लिखो(ctx, REG_MSC_COMMAND_START,
			      BIT_MSC_COMMAND_START_WRITE_STAT);
		अवरोध;
	हाल MHL_MSC_MSG:
		sii8620_ग_लिखो_buf(ctx, REG_MSC_CMD_OR_OFFSET, msg->reg, 3);
		sii8620_ग_लिखो(ctx, REG_MSC_COMMAND_START,
			      BIT_MSC_COMMAND_START_MSC_MSG);
		अवरोध;
	हाल MHL_READ_DEVCAP_REG:
	हाल MHL_READ_XDEVCAP_REG:
		sii8620_ग_लिखो(ctx, REG_MSC_CMD_OR_OFFSET, msg->reg[1]);
		sii8620_ग_लिखो(ctx, REG_MSC_COMMAND_START,
			      BIT_MSC_COMMAND_START_READ_DEVCAP);
		अवरोध;
	शेष:
		dev_err(ctx->dev, "%s: command %#x not supported\n", __func__,
			msg->reg[0]);
	पूर्ण
पूर्ण

अटल काष्ठा sii8620_mt_msg *sii8620_mt_msg_new(काष्ठा sii8620 *ctx)
अणु
	काष्ठा sii8620_mt_msg *msg = kzalloc(माप(*msg), GFP_KERNEL);

	अगर (!msg)
		ctx->error = -ENOMEM;
	अन्यथा
		list_add_tail(&msg->node, &ctx->mt_queue);

	वापस msg;
पूर्ण

अटल व्योम sii8620_mt_set_cont(काष्ठा sii8620 *ctx, sii8620_cb cont)
अणु
	काष्ठा sii8620_mt_msg *msg;

	अगर (ctx->error)
		वापस;

	अगर (list_empty(&ctx->mt_queue)) अणु
		ctx->error = -EINVAL;
		वापस;
	पूर्ण
	msg = list_last_entry(&ctx->mt_queue, काष्ठा sii8620_mt_msg, node);
	msg->continuation = cont;
पूर्ण

अटल व्योम sii8620_mt_msc_cmd(काष्ठा sii8620 *ctx, u8 cmd, u8 arg1, u8 arg2)
अणु
	काष्ठा sii8620_mt_msg *msg = sii8620_mt_msg_new(ctx);

	अगर (!msg)
		वापस;

	msg->reg[0] = cmd;
	msg->reg[1] = arg1;
	msg->reg[2] = arg2;
	msg->send = sii8620_mt_msc_cmd_send;
पूर्ण

अटल व्योम sii8620_mt_ग_लिखो_stat(काष्ठा sii8620 *ctx, u8 reg, u8 val)
अणु
	sii8620_mt_msc_cmd(ctx, MHL_WRITE_STAT, reg, val);
पूर्ण

अटल अंतरभूत व्योम sii8620_mt_set_पूर्णांक(काष्ठा sii8620 *ctx, u8 irq, u8 mask)
अणु
	sii8620_mt_msc_cmd(ctx, MHL_SET_INT, irq, mask);
पूर्ण

अटल व्योम sii8620_mt_msc_msg(काष्ठा sii8620 *ctx, u8 cmd, u8 data)
अणु
	sii8620_mt_msc_cmd(ctx, MHL_MSC_MSG, cmd, data);
पूर्ण

अटल व्योम sii8620_mt_rap(काष्ठा sii8620 *ctx, u8 code)
अणु
	sii8620_mt_msc_msg(ctx, MHL_MSC_MSG_RAP, code);
पूर्ण

अटल व्योम sii8620_mt_rcpk(काष्ठा sii8620 *ctx, u8 code)
अणु
	sii8620_mt_msc_msg(ctx, MHL_MSC_MSG_RCPK, code);
पूर्ण

अटल व्योम sii8620_mt_rcpe(काष्ठा sii8620 *ctx, u8 code)
अणु
	sii8620_mt_msc_msg(ctx, MHL_MSC_MSG_RCPE, code);
पूर्ण

अटल व्योम sii8620_mt_पढ़ो_devcap_send(काष्ठा sii8620 *ctx,
					काष्ठा sii8620_mt_msg *msg)
अणु
	u8 ctrl = BIT_EDID_CTRL_DEVCAP_SELECT_DEVCAP
			| BIT_EDID_CTRL_EDID_FIFO_ADDR_AUTO
			| BIT_EDID_CTRL_EDID_MODE_EN;

	अगर (msg->reg[0] == MHL_READ_XDEVCAP)
		ctrl |= BIT_EDID_CTRL_XDEVCAP_EN;

	sii8620_ग_लिखो_seq(ctx,
		REG_INTR9_MASK, BIT_INTR9_DEVCAP_DONE,
		REG_EDID_CTRL, ctrl,
		REG_TPI_CBUS_START, BIT_TPI_CBUS_START_GET_DEVCAP_START
	);
पूर्ण

/* copy src to dst and set changed bits in src */
अटल व्योम sii8620_update_array(u8 *dst, u8 *src, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		*src ^= *dst;
		*dst++ ^= *src++;
	पूर्ण
पूर्ण

अटल व्योम sii8620_identअगरy_sink(काष्ठा sii8620 *ctx)
अणु
	अटल स्थिर अक्षर * स्थिर sink_str[] = अणु
		[SINK_NONE] = "NONE",
		[SINK_HDMI] = "HDMI",
		[SINK_DVI] = "DVI"
	पूर्ण;

	अक्षर sink_name[20];
	काष्ठा device *dev = ctx->dev;

	अगर (!ctx->sink_detected || !ctx->devcap_पढ़ो)
		वापस;

	sii8620_fetch_edid(ctx);
	अगर (!ctx->edid) अणु
		dev_err(ctx->dev, "Cannot fetch EDID\n");
		sii8620_mhl_disconnected(ctx);
		वापस;
	पूर्ण
	sii8620_set_upstream_edid(ctx);

	अगर (drm_detect_hdmi_monitor(ctx->edid))
		ctx->sink_type = SINK_HDMI;
	अन्यथा
		ctx->sink_type = SINK_DVI;

	drm_edid_get_monitor_name(ctx->edid, sink_name, ARRAY_SIZE(sink_name));

	dev_info(dev, "detected sink(type: %s): %s\n",
		 sink_str[ctx->sink_type], sink_name);
पूर्ण

अटल व्योम sii8620_mr_devcap(काष्ठा sii8620 *ctx)
अणु
	u8 dcap[MHL_DCAP_SIZE];
	काष्ठा device *dev = ctx->dev;

	sii8620_पढ़ो_buf(ctx, REG_EDID_FIFO_RD_DATA, dcap, MHL_DCAP_SIZE);
	अगर (ctx->error < 0)
		वापस;

	dev_info(dev, "detected dongle MHL %d.%d, ChipID %02x%02x:%02x%02x\n",
		 dcap[MHL_DCAP_MHL_VERSION] / 16,
		 dcap[MHL_DCAP_MHL_VERSION] % 16,
		 dcap[MHL_DCAP_ADOPTER_ID_H], dcap[MHL_DCAP_ADOPTER_ID_L],
		 dcap[MHL_DCAP_DEVICE_ID_H], dcap[MHL_DCAP_DEVICE_ID_L]);
	sii8620_update_array(ctx->devcap, dcap, MHL_DCAP_SIZE);
	ctx->devcap_पढ़ो = true;
	sii8620_identअगरy_sink(ctx);
पूर्ण

अटल व्योम sii8620_mr_xdevcap(काष्ठा sii8620 *ctx)
अणु
	sii8620_पढ़ो_buf(ctx, REG_EDID_FIFO_RD_DATA, ctx->xdevcap,
			 MHL_XDC_SIZE);
पूर्ण

अटल व्योम sii8620_mt_पढ़ो_devcap_recv(काष्ठा sii8620 *ctx,
					काष्ठा sii8620_mt_msg *msg)
अणु
	u8 ctrl = BIT_EDID_CTRL_DEVCAP_SELECT_DEVCAP
		| BIT_EDID_CTRL_EDID_FIFO_ADDR_AUTO
		| BIT_EDID_CTRL_EDID_MODE_EN;

	अगर (msg->reg[0] == MHL_READ_XDEVCAP)
		ctrl |= BIT_EDID_CTRL_XDEVCAP_EN;

	sii8620_ग_लिखो_seq(ctx,
		REG_INTR9_MASK, BIT_INTR9_DEVCAP_DONE | BIT_INTR9_EDID_DONE
			| BIT_INTR9_EDID_ERROR,
		REG_EDID_CTRL, ctrl,
		REG_EDID_FIFO_ADDR, 0
	);

	अगर (msg->reg[0] == MHL_READ_XDEVCAP)
		sii8620_mr_xdevcap(ctx);
	अन्यथा
		sii8620_mr_devcap(ctx);
पूर्ण

अटल व्योम sii8620_mt_पढ़ो_devcap(काष्ठा sii8620 *ctx, bool xdevcap)
अणु
	काष्ठा sii8620_mt_msg *msg = sii8620_mt_msg_new(ctx);

	अगर (!msg)
		वापस;

	msg->reg[0] = xdevcap ? MHL_READ_XDEVCAP : MHL_READ_DEVCAP;
	msg->send = sii8620_mt_पढ़ो_devcap_send;
	msg->recv = sii8620_mt_पढ़ो_devcap_recv;
पूर्ण

अटल व्योम sii8620_mt_पढ़ो_devcap_reg_recv(काष्ठा sii8620 *ctx,
		काष्ठा sii8620_mt_msg *msg)
अणु
	u8 reg = msg->reg[1] & 0x7f;

	अगर (msg->reg[1] & 0x80)
		ctx->xdevcap[reg] = msg->ret;
	अन्यथा
		ctx->devcap[reg] = msg->ret;
पूर्ण

अटल व्योम sii8620_mt_पढ़ो_devcap_reg(काष्ठा sii8620 *ctx, u8 reg)
अणु
	काष्ठा sii8620_mt_msg *msg = sii8620_mt_msg_new(ctx);

	अगर (!msg)
		वापस;

	msg->reg[0] = (reg & 0x80) ? MHL_READ_XDEVCAP_REG : MHL_READ_DEVCAP_REG;
	msg->reg[1] = reg;
	msg->send = sii8620_mt_msc_cmd_send;
	msg->recv = sii8620_mt_पढ़ो_devcap_reg_recv;
पूर्ण

अटल अंतरभूत व्योम sii8620_mt_पढ़ो_xdevcap_reg(काष्ठा sii8620 *ctx, u8 reg)
अणु
	sii8620_mt_पढ़ो_devcap_reg(ctx, reg | 0x80);
पूर्ण

अटल व्योम *sii8620_burst_get_tx_buf(काष्ठा sii8620 *ctx, पूर्णांक len)
अणु
	u8 *buf = &ctx->burst.tx_buf[ctx->burst.tx_count];
	पूर्णांक size = len + 2;

	अगर (ctx->burst.tx_count + size > ARRAY_SIZE(ctx->burst.tx_buf)) अणु
		dev_err(ctx->dev, "TX-BLK buffer exhausted\n");
		ctx->error = -EINVAL;
		वापस शून्य;
	पूर्ण

	ctx->burst.tx_count += size;
	buf[1] = len;

	वापस buf + 2;
पूर्ण

अटल u8 *sii8620_burst_get_rx_buf(काष्ठा sii8620 *ctx, पूर्णांक len)
अणु
	u8 *buf = &ctx->burst.rx_buf[ctx->burst.rx_count];
	पूर्णांक size = len + 1;

	अगर (ctx->burst.tx_count + size > ARRAY_SIZE(ctx->burst.tx_buf)) अणु
		dev_err(ctx->dev, "RX-BLK buffer exhausted\n");
		ctx->error = -EINVAL;
		वापस शून्य;
	पूर्ण

	ctx->burst.rx_count += size;
	buf[0] = len;

	वापस buf + 1;
पूर्ण

अटल व्योम sii8620_burst_send(काष्ठा sii8620 *ctx)
अणु
	पूर्णांक tx_left = ctx->burst.tx_count;
	u8 *d = ctx->burst.tx_buf;

	जबतक (tx_left > 0) अणु
		पूर्णांक len = d[1] + 2;

		अगर (ctx->burst.r_count + len > ctx->burst.r_size)
			अवरोध;
		d[0] = min(ctx->burst.rx_ack, 255);
		ctx->burst.rx_ack -= d[0];
		sii8620_ग_लिखो_buf(ctx, REG_EMSC_XMIT_WRITE_PORT, d, len);
		ctx->burst.r_count += len;
		tx_left -= len;
		d += len;
	पूर्ण

	ctx->burst.tx_count = tx_left;

	जबतक (ctx->burst.rx_ack > 0) अणु
		u8 b[2] = अणु min(ctx->burst.rx_ack, 255), 0 पूर्ण;

		अगर (ctx->burst.r_count + 2 > ctx->burst.r_size)
			अवरोध;
		ctx->burst.rx_ack -= b[0];
		sii8620_ग_लिखो_buf(ctx, REG_EMSC_XMIT_WRITE_PORT, b, 2);
		ctx->burst.r_count += 2;
	पूर्ण
पूर्ण

अटल व्योम sii8620_burst_receive(काष्ठा sii8620 *ctx)
अणु
	u8 buf[3], *d;
	पूर्णांक count;

	sii8620_पढ़ो_buf(ctx, REG_EMSCRFIFOBCNTL, buf, 2);
	count = get_unaligned_le16(buf);
	जबतक (count > 0) अणु
		पूर्णांक len = min(count, 3);

		sii8620_पढ़ो_buf(ctx, REG_EMSC_RCV_READ_PORT, buf, len);
		count -= len;
		ctx->burst.rx_ack += len - 1;
		ctx->burst.r_count -= buf[1];
		अगर (ctx->burst.r_count < 0)
			ctx->burst.r_count = 0;

		अगर (len < 3 || !buf[2])
			जारी;

		len = buf[2];
		d = sii8620_burst_get_rx_buf(ctx, len);
		अगर (!d)
			जारी;
		sii8620_पढ़ो_buf(ctx, REG_EMSC_RCV_READ_PORT, d, len);
		count -= len;
		ctx->burst.rx_ack += len;
	पूर्ण
पूर्ण

अटल व्योम sii8620_burst_tx_rbuf_info(काष्ठा sii8620 *ctx, पूर्णांक size)
अणु
	काष्ठा mhl_burst_blk_rcv_buffer_info *d =
		sii8620_burst_get_tx_buf(ctx, माप(*d));
	अगर (!d)
		वापस;

	d->id = cpu_to_be16(MHL_BURST_ID_BLK_RCV_BUFFER_INFO);
	d->size = cpu_to_le16(size);
पूर्ण

अटल u8 sii8620_checksum(व्योम *ptr, पूर्णांक size)
अणु
	u8 *d = ptr, sum = 0;

	जबतक (size--)
		sum += *d++;

	वापस sum;
पूर्ण

अटल व्योम sii8620_mhl_burst_hdr_set(काष्ठा mhl3_burst_header *h,
	क्रमागत mhl_burst_id id)
अणु
	h->id = cpu_to_be16(id);
	h->total_entries = 1;
	h->sequence_index = 1;
पूर्ण

अटल व्योम sii8620_burst_tx_bits_per_pixel_fmt(काष्ठा sii8620 *ctx, u8 fmt)
अणु
	काष्ठा mhl_burst_bits_per_pixel_fmt *d;
	स्थिर पूर्णांक size = माप(*d) + माप(d->desc[0]);

	d = sii8620_burst_get_tx_buf(ctx, size);
	अगर (!d)
		वापस;

	sii8620_mhl_burst_hdr_set(&d->hdr, MHL_BURST_ID_BITS_PER_PIXEL_FMT);
	d->num_entries = 1;
	d->desc[0].stream_id = 0;
	d->desc[0].pixel_क्रमmat = fmt;
	d->hdr.checksum -= sii8620_checksum(d, size);
पूर्ण

अटल व्योम sii8620_burst_rx_all(काष्ठा sii8620 *ctx)
अणु
	u8 *d = ctx->burst.rx_buf;
	पूर्णांक count = ctx->burst.rx_count;

	जबतक (count-- > 0) अणु
		पूर्णांक len = *d++;
		पूर्णांक id = get_unaligned_be16(&d[0]);

		चयन (id) अणु
		हाल MHL_BURST_ID_BLK_RCV_BUFFER_INFO:
			ctx->burst.r_size = get_unaligned_le16(&d[2]);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		count -= len;
		d += len;
	पूर्ण
	ctx->burst.rx_count = 0;
पूर्ण

अटल व्योम sii8620_fetch_edid(काष्ठा sii8620 *ctx)
अणु
	u8 lm_ddc, ddc_cmd, पूर्णांक3, cbus;
	अचिन्हित दीर्घ समयout;
	पूर्णांक fetched, i;
	पूर्णांक edid_len = EDID_LENGTH;
	u8 *edid;

	sii8620_पढ़ोb(ctx, REG_CBUS_STATUS);
	lm_ddc = sii8620_पढ़ोb(ctx, REG_LM_DDC);
	ddc_cmd = sii8620_पढ़ोb(ctx, REG_DDC_CMD);

	sii8620_ग_लिखो_seq(ctx,
		REG_INTR9_MASK, 0,
		REG_EDID_CTRL, BIT_EDID_CTRL_EDID_FIFO_ADDR_AUTO,
		REG_HDCP2X_POLL_CS, 0x71,
		REG_HDCP2X_CTRL_0, BIT_HDCP2X_CTRL_0_HDCP2X_HDCPTX,
		REG_LM_DDC, lm_ddc | BIT_LM_DDC_SW_TPI_EN_DISABLED,
	);

	क्रम (i = 0; i < 256; ++i) अणु
		u8 ddc_stat = sii8620_पढ़ोb(ctx, REG_DDC_STATUS);

		अगर (!(ddc_stat & BIT_DDC_STATUS_DDC_I2C_IN_PROG))
			अवरोध;
		sii8620_ग_लिखो(ctx, REG_DDC_STATUS,
			      BIT_DDC_STATUS_DDC_FIFO_EMPTY);
	पूर्ण

	sii8620_ग_लिखो(ctx, REG_DDC_ADDR, 0x50 << 1);

	edid = kदो_स्मृति(EDID_LENGTH, GFP_KERNEL);
	अगर (!edid) अणु
		ctx->error = -ENOMEM;
		वापस;
	पूर्ण

#घोषणा FETCH_SIZE 16
	क्रम (fetched = 0; fetched < edid_len; fetched += FETCH_SIZE) अणु
		sii8620_पढ़ोb(ctx, REG_DDC_STATUS);
		sii8620_ग_लिखो_seq(ctx,
			REG_DDC_CMD, ddc_cmd | VAL_DDC_CMD_DDC_CMD_ABORT,
			REG_DDC_CMD, ddc_cmd | VAL_DDC_CMD_DDC_CMD_CLEAR_FIFO,
			REG_DDC_STATUS, BIT_DDC_STATUS_DDC_FIFO_EMPTY
		);
		sii8620_ग_लिखो_seq(ctx,
			REG_DDC_SEGM, fetched >> 8,
			REG_DDC_OFFSET, fetched & 0xff,
			REG_DDC_DIN_CNT1, FETCH_SIZE,
			REG_DDC_DIN_CNT2, 0,
			REG_DDC_CMD, ddc_cmd | VAL_DDC_CMD_ENH_DDC_READ_NO_ACK
		);

		पूर्णांक3 = 0;
		समयout = jअगरfies + msecs_to_jअगरfies(200);
		क्रम (;;) अणु
			cbus = sii8620_पढ़ोb(ctx, REG_CBUS_STATUS);
			अगर (~cbus & BIT_CBUS_STATUS_CBUS_CONNECTED) अणु
				kमुक्त(edid);
				edid = शून्य;
				जाओ end;
			पूर्ण
			अगर (पूर्णांक3 & BIT_DDC_CMD_DONE) अणु
				अगर (sii8620_पढ़ोb(ctx, REG_DDC_DOUT_CNT)
				    >= FETCH_SIZE)
					अवरोध;
			पूर्ण अन्यथा अणु
				पूर्णांक3 = sii8620_पढ़ोb(ctx, REG_INTR3);
			पूर्ण
			अगर (समय_is_beक्रमe_jअगरfies(समयout)) अणु
				ctx->error = -ETIMEDOUT;
				dev_err(ctx->dev, "timeout during EDID read\n");
				kमुक्त(edid);
				edid = शून्य;
				जाओ end;
			पूर्ण
			usleep_range(10, 20);
		पूर्ण

		sii8620_पढ़ो_buf(ctx, REG_DDC_DATA, edid + fetched, FETCH_SIZE);
		अगर (fetched + FETCH_SIZE == EDID_LENGTH) अणु
			u8 ext = ((काष्ठा edid *)edid)->extensions;

			अगर (ext) अणु
				u8 *new_edid;

				edid_len += ext * EDID_LENGTH;
				new_edid = kपुनः_स्मृति(edid, edid_len, GFP_KERNEL);
				अगर (!new_edid) अणु
					kमुक्त(edid);
					ctx->error = -ENOMEM;
					वापस;
				पूर्ण
				edid = new_edid;
			पूर्ण
		पूर्ण
	पूर्ण

	sii8620_ग_लिखो_seq(ctx,
		REG_INTR3_MASK, BIT_DDC_CMD_DONE,
		REG_LM_DDC, lm_ddc
	);

end:
	kमुक्त(ctx->edid);
	ctx->edid = (काष्ठा edid *)edid;
पूर्ण

अटल व्योम sii8620_set_upstream_edid(काष्ठा sii8620 *ctx)
अणु
	sii8620_setbits(ctx, REG_DPD, BIT_DPD_PDNRX12 | BIT_DPD_PDIDCK_N
			| BIT_DPD_PD_MHL_CLK_N, 0xff);

	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_RX_HDMI_CTRL3, 0x00,
		REG_PKT_FILTER_0, 0xFF,
		REG_PKT_FILTER_1, 0xFF,
		REG_ALICE0_BW_I2C, 0x06
	);

	sii8620_setbits(ctx, REG_RX_HDMI_CLR_BUFFER,
			BIT_RX_HDMI_CLR_BUFFER_VSI_CLR_EN, 0xff);

	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_EDID_CTRL, BIT_EDID_CTRL_EDID_FIFO_ADDR_AUTO
			| BIT_EDID_CTRL_EDID_MODE_EN,
		REG_EDID_FIFO_ADDR, 0,
	);

	sii8620_ग_लिखो_buf(ctx, REG_EDID_FIFO_WR_DATA, (u8 *)ctx->edid,
			  (ctx->edid->extensions + 1) * EDID_LENGTH);

	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_EDID_CTRL, BIT_EDID_CTRL_EDID_PRIME_VALID
			| BIT_EDID_CTRL_EDID_FIFO_ADDR_AUTO
			| BIT_EDID_CTRL_EDID_MODE_EN,
		REG_INTR5_MASK, BIT_INTR_SCDT_CHANGE,
		REG_INTR9_MASK, 0
	);
पूर्ण

अटल व्योम sii8620_xtal_set_rate(काष्ठा sii8620 *ctx)
अणु
	अटल स्थिर काष्ठा अणु
		अचिन्हित पूर्णांक rate;
		u8 भाग;
		u8 tp1;
	पूर्ण rates[] = अणु
		अणु 19200, 0x04, 0x53 पूर्ण,
		अणु 20000, 0x04, 0x62 पूर्ण,
		अणु 24000, 0x05, 0x75 पूर्ण,
		अणु 30000, 0x06, 0x92 पूर्ण,
		अणु 38400, 0x0c, 0xbc पूर्ण,
	पूर्ण;
	अचिन्हित दीर्घ rate = clk_get_rate(ctx->clk_xtal) / 1000;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rates) - 1; ++i)
		अगर (rate <= rates[i].rate)
			अवरोध;

	अगर (rate != rates[i].rate)
		dev_err(ctx->dev, "xtal clock rate(%lukHz) not supported, setting MHL for %ukHz.\n",
			rate, rates[i].rate);

	sii8620_ग_लिखो(ctx, REG_DIV_CTL_MAIN, rates[i].भाग);
	sii8620_ग_लिखो(ctx, REG_HDCP2X_TP1, rates[i].tp1);
पूर्ण

अटल पूर्णांक sii8620_hw_on(काष्ठा sii8620 *ctx)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	अगर (ret)
		वापस ret;

	usleep_range(10000, 20000);
	ret = clk_prepare_enable(ctx->clk_xtal);
	अगर (ret)
		वापस ret;

	msleep(100);
	gpiod_set_value(ctx->gpio_reset, 0);
	msleep(100);

	वापस 0;
पूर्ण

अटल पूर्णांक sii8620_hw_off(काष्ठा sii8620 *ctx)
अणु
	clk_disable_unprepare(ctx->clk_xtal);
	gpiod_set_value(ctx->gpio_reset, 1);
	वापस regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
पूर्ण

अटल व्योम sii8620_cbus_reset(काष्ठा sii8620 *ctx)
अणु
	sii8620_ग_लिखो(ctx, REG_PWD_SRST, BIT_PWD_SRST_CBUS_RST
		      | BIT_PWD_SRST_CBUS_RST_SW_EN);
	usleep_range(10000, 20000);
	sii8620_ग_लिखो(ctx, REG_PWD_SRST, BIT_PWD_SRST_CBUS_RST_SW_EN);
पूर्ण

अटल व्योम sii8620_set_स्वतः_zone(काष्ठा sii8620 *ctx)
अणु
	अगर (ctx->mode != CM_MHL1) अणु
		sii8620_ग_लिखो_seq_अटल(ctx,
			REG_TX_ZONE_CTL1, 0x0,
			REG_MHL_PLL_CTL0, VAL_MHL_PLL_CTL0_HDMI_CLK_RATIO_1X
				| BIT_MHL_PLL_CTL0_CRYSTAL_CLK_SEL
				| BIT_MHL_PLL_CTL0_ZONE_MASK_OE
		);
	पूर्ण अन्यथा अणु
		sii8620_ग_लिखो_seq_अटल(ctx,
			REG_TX_ZONE_CTL1, VAL_TX_ZONE_CTL1_TX_ZONE_CTRL_MODE,
			REG_MHL_PLL_CTL0, VAL_MHL_PLL_CTL0_HDMI_CLK_RATIO_1X
				| BIT_MHL_PLL_CTL0_ZONE_MASK_OE
		);
	पूर्ण
पूर्ण

अटल व्योम sii8620_stop_video(काष्ठा sii8620 *ctx)
अणु
	u8 val;

	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_TPI_INTR_EN, 0,
		REG_HDCP2X_INTR0_MASK, 0,
		REG_TPI_COPP_DATA2, 0,
		REG_TPI_INTR_ST0, ~0,
	);

	चयन (ctx->sink_type) अणु
	हाल SINK_DVI:
		val = BIT_TPI_SC_REG_TMDS_OE_POWER_DOWN
			| BIT_TPI_SC_TPI_AV_MUTE;
		अवरोध;
	हाल SINK_HDMI:
	शेष:
		val = BIT_TPI_SC_REG_TMDS_OE_POWER_DOWN
			| BIT_TPI_SC_TPI_AV_MUTE
			| BIT_TPI_SC_TPI_OUTPUT_MODE_0_HDMI;
		अवरोध;
	पूर्ण

	sii8620_ग_लिखो(ctx, REG_TPI_SC, val);
पूर्ण

अटल व्योम sii8620_set_क्रमmat(काष्ठा sii8620 *ctx)
अणु
	u8 out_fmt;

	अगर (sii8620_is_mhl3(ctx)) अणु
		sii8620_setbits(ctx, REG_M3_P0CTRL,
				BIT_M3_P0CTRL_MHL3_P0_PIXEL_MODE_PACKED,
				ctx->use_packed_pixel ? ~0 : 0);
	पूर्ण अन्यथा अणु
		अगर (ctx->use_packed_pixel) अणु
			sii8620_ग_लिखो_seq_अटल(ctx,
				REG_VID_MODE, BIT_VID_MODE_M1080P,
				REG_MHL_TOP_CTL, BIT_MHL_TOP_CTL_MHL_PP_SEL | 1,
				REG_MHLTX_CTL6, 0x60
			);
		पूर्ण अन्यथा अणु
			sii8620_ग_लिखो_seq_अटल(ctx,
				REG_VID_MODE, 0,
				REG_MHL_TOP_CTL, 1,
				REG_MHLTX_CTL6, 0xa0
			);
		पूर्ण
	पूर्ण

	अगर (ctx->use_packed_pixel)
		out_fmt = VAL_TPI_FORMAT(YCBCR422, FULL);
	अन्यथा
		out_fmt = VAL_TPI_FORMAT(RGB, FULL);

	sii8620_ग_लिखो_seq(ctx,
		REG_TPI_INPUT, VAL_TPI_FORMAT(RGB, FULL),
		REG_TPI_OUTPUT, out_fmt,
	);
पूर्ण

अटल पूर्णांक mhl3_infoframe_init(काष्ठा mhl3_infoframe *frame)
अणु
	स_रखो(frame, 0, माप(*frame));

	frame->version = 3;
	frame->hev_क्रमmat = -1;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार mhl3_infoframe_pack(काष्ठा mhl3_infoframe *frame,
		 व्योम *buffer, माप_प्रकार size)
अणु
	स्थिर पूर्णांक frm_len = HDMI_INFOFRAME_HEADER_SIZE + MHL3_INFOFRAME_SIZE;
	u8 *ptr = buffer;

	अगर (size < frm_len)
		वापस -ENOSPC;

	स_रखो(buffer, 0, size);
	ptr[0] = HDMI_INFOFRAME_TYPE_VENDOR;
	ptr[1] = frame->version;
	ptr[2] = MHL3_INFOFRAME_SIZE;
	ptr[4] = MHL3_IEEE_OUI & 0xff;
	ptr[5] = (MHL3_IEEE_OUI >> 8) & 0xff;
	ptr[6] = (MHL3_IEEE_OUI >> 16) & 0xff;
	ptr[7] = frame->video_क्रमmat & 0x3;
	ptr[7] |= (frame->क्रमmat_type & 0x7) << 2;
	ptr[7] |= frame->sep_audio ? BIT(5) : 0;
	अगर (frame->hev_क्रमmat >= 0) अणु
		ptr[9] = 1;
		ptr[10] = (frame->hev_क्रमmat >> 8) & 0xff;
		ptr[11] = frame->hev_क्रमmat & 0xff;
	पूर्ण
	अगर (frame->av_delay) अणु
		bool sign = frame->av_delay < 0;
		पूर्णांक delay = sign ? -frame->av_delay : frame->av_delay;

		ptr[12] = (delay >> 16) & 0xf;
		अगर (sign)
			ptr[12] |= BIT(4);
		ptr[13] = (delay >> 8) & 0xff;
		ptr[14] = delay & 0xff;
	पूर्ण
	ptr[3] -= sii8620_checksum(buffer, frm_len);
	वापस frm_len;
पूर्ण

अटल व्योम sii8620_set_infoframes(काष्ठा sii8620 *ctx,
				   काष्ठा drm_display_mode *mode)
अणु
	काष्ठा mhl3_infoframe mhl_frm;
	जोड़ hdmi_infoframe frm;
	u8 buf[31];
	पूर्णांक ret;

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frm.avi,
						       शून्य, mode);
	अगर (ctx->use_packed_pixel)
		frm.avi.colorspace = HDMI_COLORSPACE_YUV422;

	अगर (!ret)
		ret = hdmi_avi_infoframe_pack(&frm.avi, buf, ARRAY_SIZE(buf));
	अगर (ret > 0)
		sii8620_ग_लिखो_buf(ctx, REG_TPI_AVI_CHSUM, buf + 3, ret - 3);

	अगर (!sii8620_is_mhl3(ctx) || !ctx->use_packed_pixel) अणु
		sii8620_ग_लिखो(ctx, REG_TPI_SC,
			BIT_TPI_SC_TPI_OUTPUT_MODE_0_HDMI);
		sii8620_ग_लिखो(ctx, REG_PKT_FILTER_0,
			BIT_PKT_FILTER_0_DROP_CEA_GAMUT_PKT |
			BIT_PKT_FILTER_0_DROP_MPEG_PKT |
			BIT_PKT_FILTER_0_DROP_GCP_PKT,
			BIT_PKT_FILTER_1_DROP_GEN_PKT);
		वापस;
	पूर्ण

	sii8620_ग_लिखो(ctx, REG_PKT_FILTER_0,
		BIT_PKT_FILTER_0_DROP_CEA_GAMUT_PKT |
		BIT_PKT_FILTER_0_DROP_MPEG_PKT |
		BIT_PKT_FILTER_0_DROP_AVI_PKT |
		BIT_PKT_FILTER_0_DROP_GCP_PKT,
		BIT_PKT_FILTER_1_VSI_OVERRIDE_DIS |
		BIT_PKT_FILTER_1_DROP_GEN_PKT |
		BIT_PKT_FILTER_1_DROP_VSIF_PKT);

	sii8620_ग_लिखो(ctx, REG_TPI_INFO_FSEL, BIT_TPI_INFO_FSEL_EN
		| BIT_TPI_INFO_FSEL_RPT | VAL_TPI_INFO_FSEL_VSI);
	ret = mhl3_infoframe_init(&mhl_frm);
	अगर (!ret)
		ret = mhl3_infoframe_pack(&mhl_frm, buf, ARRAY_SIZE(buf));
	sii8620_ग_लिखो_buf(ctx, REG_TPI_INFO_B0, buf, ret);
पूर्ण

अटल व्योम sii8620_start_video(काष्ठा sii8620 *ctx)
अणु
	काष्ठा drm_display_mode *mode =
		&ctx->bridge.encoder->crtc->state->adjusted_mode;

	अगर (!sii8620_is_mhl3(ctx))
		sii8620_stop_video(ctx);

	अगर (ctx->sink_type == SINK_DVI && !sii8620_is_mhl3(ctx)) अणु
		sii8620_ग_लिखो(ctx, REG_RX_HDMI_CTRL2,
			      VAL_RX_HDMI_CTRL2_DEFVAL);
		sii8620_ग_लिखो(ctx, REG_TPI_SC, 0);
		वापस;
	पूर्ण

	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_RX_HDMI_CTRL2, VAL_RX_HDMI_CTRL2_DEFVAL
			| BIT_RX_HDMI_CTRL2_USE_AV_MUTE,
		REG_VID_OVRRD, BIT_VID_OVRRD_PP_AUTO_DISABLE
			| BIT_VID_OVRRD_M1080P_OVRRD);
	sii8620_set_क्रमmat(ctx);

	अगर (!sii8620_is_mhl3(ctx)) अणु
		u8 link_mode = MHL_DST_LM_PATH_ENABLED;

		अगर (ctx->use_packed_pixel)
			link_mode |= MHL_DST_LM_CLK_MODE_PACKED_PIXEL;
		अन्यथा
			link_mode |= MHL_DST_LM_CLK_MODE_NORMAL;

		sii8620_mt_ग_लिखो_stat(ctx, MHL_DST_REG(LINK_MODE), link_mode);
		sii8620_set_स्वतः_zone(ctx);
	पूर्ण अन्यथा अणु
		अटल स्थिर काष्ठा अणु
			पूर्णांक max_clk;
			u8 zone;
			u8 link_rate;
			u8 rrp_decode;
		पूर्ण clk_spec[] = अणु
			अणु 150000, VAL_TX_ZONE_CTL3_TX_ZONE_1_5GBPS,
			  MHL_XDS_LINK_RATE_1_5_GBPS, 0x38 पूर्ण,
			अणु 300000, VAL_TX_ZONE_CTL3_TX_ZONE_3GBPS,
			  MHL_XDS_LINK_RATE_3_0_GBPS, 0x40 पूर्ण,
			अणु 600000, VAL_TX_ZONE_CTL3_TX_ZONE_6GBPS,
			  MHL_XDS_LINK_RATE_6_0_GBPS, 0x40 पूर्ण,
		पूर्ण;
		u8 p0_ctrl = BIT_M3_P0CTRL_MHL3_P0_PORT_EN;
		पूर्णांक clk = mode->घड़ी * (ctx->use_packed_pixel ? 2 : 3);
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(clk_spec) - 1; ++i)
			अगर (clk < clk_spec[i].max_clk)
				अवरोध;

		अगर (100 * clk >= 98 * clk_spec[i].max_clk)
			p0_ctrl |= BIT_M3_P0CTRL_MHL3_P0_UNLIMIT_EN;

		sii8620_burst_tx_bits_per_pixel_fmt(ctx, ctx->use_packed_pixel);
		sii8620_burst_send(ctx);
		sii8620_ग_लिखो_seq(ctx,
			REG_MHL_DP_CTL0, 0xf0,
			REG_MHL3_TX_ZONE_CTL, clk_spec[i].zone);
		sii8620_setbits(ctx, REG_M3_P0CTRL,
			BIT_M3_P0CTRL_MHL3_P0_PORT_EN
			| BIT_M3_P0CTRL_MHL3_P0_UNLIMIT_EN, p0_ctrl);
		sii8620_setbits(ctx, REG_M3_POSTM, MSK_M3_POSTM_RRP_DECODE,
			clk_spec[i].rrp_decode);
		sii8620_ग_लिखो_seq_अटल(ctx,
			REG_M3_CTRL, VAL_M3_CTRL_MHL3_VALUE
				| BIT_M3_CTRL_H2M_SWRST,
			REG_M3_CTRL, VAL_M3_CTRL_MHL3_VALUE
		);
		sii8620_mt_ग_लिखो_stat(ctx, MHL_XDS_REG(AVLINK_MODE_CONTROL),
			clk_spec[i].link_rate);
	पूर्ण

	sii8620_set_infoframes(ctx, mode);
पूर्ण

अटल व्योम sii8620_disable_hpd(काष्ठा sii8620 *ctx)
अणु
	sii8620_setbits(ctx, REG_EDID_CTRL, BIT_EDID_CTRL_EDID_PRIME_VALID, 0);
	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_HPD_CTRL, BIT_HPD_CTRL_HPD_OUT_OVR_EN,
		REG_INTR8_MASK, 0
	);
पूर्ण

अटल व्योम sii8620_enable_hpd(काष्ठा sii8620 *ctx)
अणु
	sii8620_setbits(ctx, REG_TMDS_CSTAT_P3,
			BIT_TMDS_CSTAT_P3_SCDT_CLR_AVI_DIS
			| BIT_TMDS_CSTAT_P3_CLR_AVI, ~0);
	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_HPD_CTRL, BIT_HPD_CTRL_HPD_OUT_OVR_EN
			| BIT_HPD_CTRL_HPD_HIGH,
	);
पूर्ण

अटल व्योम sii8620_mhl_discover(काष्ठा sii8620 *ctx)
अणु
	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_DISC_CTRL9, BIT_DISC_CTRL9_WAKE_DRVFLT
			| BIT_DISC_CTRL9_DISC_PULSE_PROCEED,
		REG_DISC_CTRL4, VAL_DISC_CTRL4(VAL_PUP_5K, VAL_PUP_20K),
		REG_CBUS_DISC_INTR0_MASK, BIT_MHL3_EST_INT
			| BIT_MHL_EST_INT
			| BIT_NOT_MHL_EST_INT
			| BIT_CBUS_MHL3_DISCON_INT
			| BIT_CBUS_MHL12_DISCON_INT
			| BIT_RGND_READY_INT,
		REG_MHL_PLL_CTL0, VAL_MHL_PLL_CTL0_HDMI_CLK_RATIO_1X
			| BIT_MHL_PLL_CTL0_CRYSTAL_CLK_SEL
			| BIT_MHL_PLL_CTL0_ZONE_MASK_OE,
		REG_MHL_DP_CTL0, BIT_MHL_DP_CTL0_DP_OE
			| BIT_MHL_DP_CTL0_TX_OE_OVR,
		REG_M3_CTRL, VAL_M3_CTRL_MHL3_VALUE,
		REG_MHL_DP_CTL1, 0xA2,
		REG_MHL_DP_CTL2, 0x03,
		REG_MHL_DP_CTL3, 0x35,
		REG_MHL_DP_CTL5, 0x02,
		REG_MHL_DP_CTL6, 0x02,
		REG_MHL_DP_CTL7, 0x03,
		REG_COC_CTLC, 0xFF,
		REG_DPD, BIT_DPD_PWRON_PLL | BIT_DPD_PDNTX12
			| BIT_DPD_OSC_EN | BIT_DPD_PWRON_HSIC,
		REG_COC_INTR_MASK, BIT_COC_PLL_LOCK_STATUS_CHANGE
			| BIT_COC_CALIBRATION_DONE,
		REG_CBUS_INT_1_MASK, BIT_CBUS_MSC_ABORT_RCVD
			| BIT_CBUS_CMD_ABORT,
		REG_CBUS_INT_0_MASK, BIT_CBUS_MSC_MT_DONE
			| BIT_CBUS_HPD_CHG
			| BIT_CBUS_MSC_MR_WRITE_STAT
			| BIT_CBUS_MSC_MR_MSC_MSG
			| BIT_CBUS_MSC_MR_WRITE_BURST
			| BIT_CBUS_MSC_MR_SET_INT
			| BIT_CBUS_MSC_MT_DONE_NACK
	);
पूर्ण

अटल व्योम sii8620_peer_specअगरic_init(काष्ठा sii8620 *ctx)
अणु
	अगर (sii8620_is_mhl3(ctx))
		sii8620_ग_लिखो_seq_अटल(ctx,
			REG_SYS_CTRL1, BIT_SYS_CTRL1_BLOCK_DDC_BY_HPD,
			REG_EMSCINTRMASK1,
				BIT_EMSCINTR1_EMSC_TRAINING_COMMA_ERR
		);
	अन्यथा
		sii8620_ग_लिखो_seq_अटल(ctx,
			REG_HDCP2X_INTR0_MASK, 0x00,
			REG_EMSCINTRMASK1, 0x00,
			REG_HDCP2X_INTR0, 0xFF,
			REG_INTR1, 0xFF,
			REG_SYS_CTRL1, BIT_SYS_CTRL1_BLOCK_DDC_BY_HPD
				| BIT_SYS_CTRL1_TX_CTRL_HDMI
		);
पूर्ण

#घोषणा SII8620_MHL_VERSION			0x32
#घोषणा SII8620_SCRATCHPAD_SIZE			16
#घोषणा SII8620_INT_STAT_SIZE			0x33

अटल व्योम sii8620_set_dev_cap(काष्ठा sii8620 *ctx)
अणु
	अटल स्थिर u8 devcap[MHL_DCAP_SIZE] = अणु
		[MHL_DCAP_MHL_VERSION] = SII8620_MHL_VERSION,
		[MHL_DCAP_CAT] = MHL_DCAP_CAT_SOURCE | MHL_DCAP_CAT_POWER,
		[MHL_DCAP_ADOPTER_ID_H] = 0x01,
		[MHL_DCAP_ADOPTER_ID_L] = 0x41,
		[MHL_DCAP_VID_LINK_MODE] = MHL_DCAP_VID_LINK_RGB444
			| MHL_DCAP_VID_LINK_PPIXEL
			| MHL_DCAP_VID_LINK_16BPP,
		[MHL_DCAP_AUD_LINK_MODE] = MHL_DCAP_AUD_LINK_2CH,
		[MHL_DCAP_VIDEO_TYPE] = MHL_DCAP_VT_GRAPHICS,
		[MHL_DCAP_LOG_DEV_MAP] = MHL_DCAP_LD_GUI,
		[MHL_DCAP_BANDWIDTH] = 0x0f,
		[MHL_DCAP_FEATURE_FLAG] = MHL_DCAP_FEATURE_RCP_SUPPORT
			| MHL_DCAP_FEATURE_RAP_SUPPORT
			| MHL_DCAP_FEATURE_SP_SUPPORT,
		[MHL_DCAP_SCRATCHPAD_SIZE] = SII8620_SCRATCHPAD_SIZE,
		[MHL_DCAP_INT_STAT_SIZE] = SII8620_INT_STAT_SIZE,
	पूर्ण;
	अटल स्थिर u8 xdcap[MHL_XDC_SIZE] = अणु
		[MHL_XDC_ECBUS_SPEEDS] = MHL_XDC_ECBUS_S_075
			| MHL_XDC_ECBUS_S_8BIT,
		[MHL_XDC_TMDS_SPEEDS] = MHL_XDC_TMDS_150
			| MHL_XDC_TMDS_300 | MHL_XDC_TMDS_600,
		[MHL_XDC_ECBUS_ROLES] = MHL_XDC_DEV_HOST,
		[MHL_XDC_LOG_DEV_MAPX] = MHL_XDC_LD_PHONE,
	पूर्ण;

	sii8620_ग_लिखो_buf(ctx, REG_MHL_DEVCAP_0, devcap, ARRAY_SIZE(devcap));
	sii8620_ग_लिखो_buf(ctx, REG_MHL_EXTDEVCAP_0, xdcap, ARRAY_SIZE(xdcap));
पूर्ण

अटल व्योम sii8620_mhl_init(काष्ठा sii8620 *ctx)
अणु
	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_DISC_CTRL4, VAL_DISC_CTRL4(VAL_PUP_OFF, VAL_PUP_20K),
		REG_CBUS_MSC_COMPAT_CTRL,
			BIT_CBUS_MSC_COMPAT_CTRL_XDEVCAP_EN,
	);

	sii8620_peer_specअगरic_init(ctx);

	sii8620_disable_hpd(ctx);

	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_EDID_CTRL, BIT_EDID_CTRL_EDID_FIFO_ADDR_AUTO,
		REG_DISC_CTRL9, BIT_DISC_CTRL9_WAKE_DRVFLT
			| BIT_DISC_CTRL9_WAKE_PULSE_BYPASS,
		REG_TMDS0_CCTRL1, 0x90,
		REG_TMDS_CLK_EN, 0x01,
		REG_TMDS_CH_EN, 0x11,
		REG_BGR_BIAS, 0x87,
		REG_ALICE0_ZONE_CTRL, 0xE8,
		REG_ALICE0_MODE_CTRL, 0x04,
	);
	sii8620_setbits(ctx, REG_LM_DDC, BIT_LM_DDC_SW_TPI_EN_DISABLED, 0);
	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_TPI_HW_OPT3, 0x76,
		REG_TMDS_CCTRL, BIT_TMDS_CCTRL_TMDS_OE,
		REG_TPI_DTD_B2, 79,
	);
	sii8620_set_dev_cap(ctx);
	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_MDT_XMIT_TIMEOUT, 100,
		REG_MDT_XMIT_CTRL, 0x03,
		REG_MDT_XFIFO_STAT, 0x00,
		REG_MDT_RCV_TIMEOUT, 100,
		REG_CBUS_LINK_CTRL_8, 0x1D,
	);

	sii8620_start_gen2_ग_लिखो_burst(ctx);
	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_BIST_CTRL, 0x00,
		REG_COC_CTL1, 0x10,
		REG_COC_CTL2, 0x18,
		REG_COC_CTLF, 0x07,
		REG_COC_CTL11, 0xF8,
		REG_COC_CTL17, 0x61,
		REG_COC_CTL18, 0x46,
		REG_COC_CTL19, 0x15,
		REG_COC_CTL1A, 0x01,
		REG_MHL_COC_CTL3, BIT_MHL_COC_CTL3_COC_AECHO_EN,
		REG_MHL_COC_CTL4, 0x2D,
		REG_MHL_COC_CTL5, 0xF9,
		REG_MSC_HEARTBEAT_CTRL, 0x27,
	);
	sii8620_disable_gen2_ग_लिखो_burst(ctx);

	sii8620_mt_ग_लिखो_stat(ctx, MHL_DST_REG(VERSION), SII8620_MHL_VERSION);
	sii8620_mt_ग_लिखो_stat(ctx, MHL_DST_REG(CONNECTED_RDY),
			      MHL_DST_CONN_DCAP_RDY | MHL_DST_CONN_XDEVCAPP_SUPP
			      | MHL_DST_CONN_POW_STAT);
	sii8620_mt_set_पूर्णांक(ctx, MHL_INT_REG(RCHANGE), MHL_INT_RC_DCAP_CHG);
पूर्ण

अटल व्योम sii8620_emsc_enable(काष्ठा sii8620 *ctx)
अणु
	u8 reg;

	sii8620_setbits(ctx, REG_GENCTL, BIT_GENCTL_EMSC_EN
					 | BIT_GENCTL_CLR_EMSC_RFIFO
					 | BIT_GENCTL_CLR_EMSC_XFIFO, ~0);
	sii8620_setbits(ctx, REG_GENCTL, BIT_GENCTL_CLR_EMSC_RFIFO
					 | BIT_GENCTL_CLR_EMSC_XFIFO, 0);
	sii8620_setbits(ctx, REG_COMMECNT, BIT_COMMECNT_I2C_TO_EMSC_EN, ~0);
	reg = sii8620_पढ़ोb(ctx, REG_EMSCINTR);
	sii8620_ग_लिखो(ctx, REG_EMSCINTR, reg);
	sii8620_ग_लिखो(ctx, REG_EMSCINTRMASK, BIT_EMSCINTR_SPI_DVLD);
पूर्ण

अटल पूर्णांक sii8620_रुको_क्रम_fsm_state(काष्ठा sii8620 *ctx, u8 state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 10; ++i) अणु
		u8 s = sii8620_पढ़ोb(ctx, REG_COC_STAT_0);

		अगर ((s & MSK_COC_STAT_0_FSM_STATE) == state)
			वापस 0;
		अगर (!(s & BIT_COC_STAT_0_PLL_LOCKED))
			वापस -EBUSY;
		usleep_range(4000, 6000);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम sii8620_set_mode(काष्ठा sii8620 *ctx, क्रमागत sii8620_mode mode)
अणु
	पूर्णांक ret;

	अगर (ctx->mode == mode)
		वापस;

	चयन (mode) अणु
	हाल CM_MHL1:
		sii8620_ग_लिखो_seq_अटल(ctx,
			REG_CBUS_MSC_COMPAT_CTRL, 0x02,
			REG_M3_CTRL, VAL_M3_CTRL_MHL1_2_VALUE,
			REG_DPD, BIT_DPD_PWRON_PLL | BIT_DPD_PDNTX12
				| BIT_DPD_OSC_EN,
			REG_COC_INTR_MASK, 0
		);
		ctx->mode = mode;
		अवरोध;
	हाल CM_MHL3:
		sii8620_ग_लिखो(ctx, REG_M3_CTRL, VAL_M3_CTRL_MHL3_VALUE);
		ctx->mode = mode;
		वापस;
	हाल CM_ECBUS_S:
		sii8620_emsc_enable(ctx);
		sii8620_ग_लिखो_seq_अटल(ctx,
			REG_TTXSPINUMS, 4,
			REG_TRXSPINUMS, 4,
			REG_TTXHSICNUMS, 0x14,
			REG_TRXHSICNUMS, 0x14,
			REG_TTXTOTNUMS, 0x18,
			REG_TRXTOTNUMS, 0x18,
			REG_PWD_SRST, BIT_PWD_SRST_COC_DOC_RST
				      | BIT_PWD_SRST_CBUS_RST_SW_EN,
			REG_MHL_COC_CTL1, 0xbd,
			REG_PWD_SRST, BIT_PWD_SRST_CBUS_RST_SW_EN,
			REG_COC_CTLB, 0x01,
			REG_COC_CTL0, 0x5c,
			REG_COC_CTL14, 0x03,
			REG_COC_CTL15, 0x80,
			REG_MHL_DP_CTL6, BIT_MHL_DP_CTL6_DP_TAP1_SGN
					 | BIT_MHL_DP_CTL6_DP_TAP1_EN
					 | BIT_MHL_DP_CTL6_DT_PREDRV_FEEDCAP_EN,
			REG_MHL_DP_CTL8, 0x03
		);
		ret = sii8620_रुको_क्रम_fsm_state(ctx, 0x03);
		sii8620_ग_लिखो_seq_अटल(ctx,
			REG_COC_CTL14, 0x00,
			REG_COC_CTL15, 0x80
		);
		अगर (!ret)
			sii8620_ग_लिखो(ctx, REG_CBUS3_CNVT, 0x85);
		अन्यथा
			sii8620_disconnect(ctx);
		वापस;
	हाल CM_DISCONNECTED:
		ctx->mode = mode;
		अवरोध;
	शेष:
		dev_err(ctx->dev, "%s mode %d not supported\n", __func__, mode);
		अवरोध;
	पूर्ण

	sii8620_set_स्वतः_zone(ctx);

	अगर (mode != CM_MHL1)
		वापस;

	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_MHL_DP_CTL0, 0xBC,
		REG_MHL_DP_CTL1, 0xBB,
		REG_MHL_DP_CTL3, 0x48,
		REG_MHL_DP_CTL5, 0x39,
		REG_MHL_DP_CTL2, 0x2A,
		REG_MHL_DP_CTL6, 0x2A,
		REG_MHL_DP_CTL7, 0x08
	);
पूर्ण

अटल व्योम sii8620_hpd_unplugged(काष्ठा sii8620 *ctx)
अणु
	sii8620_disable_hpd(ctx);
	ctx->sink_type = SINK_NONE;
	ctx->sink_detected = false;
	ctx->feature_complete = false;
	kमुक्त(ctx->edid);
	ctx->edid = शून्य;
पूर्ण

अटल व्योम sii8620_disconnect(काष्ठा sii8620 *ctx)
अणु
	sii8620_disable_gen2_ग_लिखो_burst(ctx);
	sii8620_stop_video(ctx);
	msleep(100);
	sii8620_cbus_reset(ctx);
	sii8620_set_mode(ctx, CM_DISCONNECTED);
	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_TX_ZONE_CTL1, 0,
		REG_MHL_PLL_CTL0, 0x07,
		REG_COC_CTL0, 0x40,
		REG_CBUS3_CNVT, 0x84,
		REG_COC_CTL14, 0x00,
		REG_COC_CTL0, 0x40,
		REG_HRXCTRL3, 0x07,
		REG_MHL_PLL_CTL0, VAL_MHL_PLL_CTL0_HDMI_CLK_RATIO_1X
			| BIT_MHL_PLL_CTL0_CRYSTAL_CLK_SEL
			| BIT_MHL_PLL_CTL0_ZONE_MASK_OE,
		REG_MHL_DP_CTL0, BIT_MHL_DP_CTL0_DP_OE
			| BIT_MHL_DP_CTL0_TX_OE_OVR,
		REG_MHL_DP_CTL1, 0xBB,
		REG_MHL_DP_CTL3, 0x48,
		REG_MHL_DP_CTL5, 0x3F,
		REG_MHL_DP_CTL2, 0x2F,
		REG_MHL_DP_CTL6, 0x2A,
		REG_MHL_DP_CTL7, 0x03
	);
	sii8620_hpd_unplugged(ctx);
	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_M3_CTRL, VAL_M3_CTRL_MHL3_VALUE,
		REG_MHL_COC_CTL1, 0x07,
		REG_DISC_CTRL4, VAL_DISC_CTRL4(VAL_PUP_OFF, VAL_PUP_20K),
		REG_DISC_CTRL8, 0x00,
		REG_DISC_CTRL9, BIT_DISC_CTRL9_WAKE_DRVFLT
			| BIT_DISC_CTRL9_WAKE_PULSE_BYPASS,
		REG_INT_CTRL, 0x00,
		REG_MSC_HEARTBEAT_CTRL, 0x27,
		REG_DISC_CTRL1, 0x25,
		REG_CBUS_DISC_INTR0, (u8)~BIT_RGND_READY_INT,
		REG_CBUS_DISC_INTR0_MASK, BIT_RGND_READY_INT,
		REG_MDT_INT_1, 0xff,
		REG_MDT_INT_1_MASK, 0x00,
		REG_MDT_INT_0, 0xff,
		REG_MDT_INT_0_MASK, 0x00,
		REG_COC_INTR, 0xff,
		REG_COC_INTR_MASK, 0x00,
		REG_TRXINTH, 0xff,
		REG_TRXINTMH, 0x00,
		REG_CBUS_INT_0, 0xff,
		REG_CBUS_INT_0_MASK, 0x00,
		REG_CBUS_INT_1, 0xff,
		REG_CBUS_INT_1_MASK, 0x00,
		REG_EMSCINTR, 0xff,
		REG_EMSCINTRMASK, 0x00,
		REG_EMSCINTR1, 0xff,
		REG_EMSCINTRMASK1, 0x00,
		REG_INTR8, 0xff,
		REG_INTR8_MASK, 0x00,
		REG_TPI_INTR_ST0, 0xff,
		REG_TPI_INTR_EN, 0x00,
		REG_HDCP2X_INTR0, 0xff,
		REG_HDCP2X_INTR0_MASK, 0x00,
		REG_INTR9, 0xff,
		REG_INTR9_MASK, 0x00,
		REG_INTR3, 0xff,
		REG_INTR3_MASK, 0x00,
		REG_INTR5, 0xff,
		REG_INTR5_MASK, 0x00,
		REG_INTR2, 0xff,
		REG_INTR2_MASK, 0x00,
	);
	स_रखो(ctx->stat, 0, माप(ctx->stat));
	स_रखो(ctx->xstat, 0, माप(ctx->xstat));
	स_रखो(ctx->devcap, 0, माप(ctx->devcap));
	स_रखो(ctx->xdevcap, 0, माप(ctx->xdevcap));
	ctx->devcap_पढ़ो = false;
	ctx->cbus_status = 0;
	sii8620_mt_cleanup(ctx);
पूर्ण

अटल व्योम sii8620_mhl_disconnected(काष्ठा sii8620 *ctx)
अणु
	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_DISC_CTRL4, VAL_DISC_CTRL4(VAL_PUP_OFF, VAL_PUP_20K),
		REG_CBUS_MSC_COMPAT_CTRL,
			BIT_CBUS_MSC_COMPAT_CTRL_XDEVCAP_EN
	);
	sii8620_disconnect(ctx);
पूर्ण

अटल व्योम sii8620_irq_disc(काष्ठा sii8620 *ctx)
अणु
	u8 stat = sii8620_पढ़ोb(ctx, REG_CBUS_DISC_INTR0);

	अगर (stat & VAL_CBUS_MHL_DISCON)
		sii8620_mhl_disconnected(ctx);

	अगर (stat & BIT_RGND_READY_INT) अणु
		u8 stat2 = sii8620_पढ़ोb(ctx, REG_DISC_STAT2);

		अगर ((stat2 & MSK_DISC_STAT2_RGND) == VAL_RGND_1K) अणु
			sii8620_mhl_discover(ctx);
		पूर्ण अन्यथा अणु
			sii8620_ग_लिखो_seq_अटल(ctx,
				REG_DISC_CTRL9, BIT_DISC_CTRL9_WAKE_DRVFLT
					| BIT_DISC_CTRL9_NOMHL_EST
					| BIT_DISC_CTRL9_WAKE_PULSE_BYPASS,
				REG_CBUS_DISC_INTR0_MASK, BIT_RGND_READY_INT
					| BIT_CBUS_MHL3_DISCON_INT
					| BIT_CBUS_MHL12_DISCON_INT
					| BIT_NOT_MHL_EST_INT
			);
		पूर्ण
	पूर्ण
	अगर (stat & BIT_MHL_EST_INT)
		sii8620_mhl_init(ctx);

	sii8620_ग_लिखो(ctx, REG_CBUS_DISC_INTR0, stat);
पूर्ण

अटल व्योम sii8620_पढ़ो_burst(काष्ठा sii8620 *ctx)
अणु
	u8 buf[17];

	sii8620_पढ़ो_buf(ctx, REG_MDT_RCV_READ_PORT, buf, ARRAY_SIZE(buf));
	sii8620_ग_लिखो(ctx, REG_MDT_RCV_CTRL, BIT_MDT_RCV_CTRL_MDT_RCV_EN |
		      BIT_MDT_RCV_CTRL_MDT_DELAY_RCV_EN |
		      BIT_MDT_RCV_CTRL_MDT_RFIFO_CLR_CUR);
	sii8620_पढ़ोb(ctx, REG_MDT_RFIFO_STAT);
पूर्ण

अटल व्योम sii8620_irq_g2wb(काष्ठा sii8620 *ctx)
अणु
	u8 stat = sii8620_पढ़ोb(ctx, REG_MDT_INT_0);

	अगर (stat & BIT_MDT_IDLE_AFTER_HAWB_DISABLE)
		अगर (sii8620_is_mhl3(ctx))
			sii8620_mt_set_पूर्णांक(ctx, MHL_INT_REG(RCHANGE),
				MHL_INT_RC_FEAT_COMPLETE);

	अगर (stat & BIT_MDT_RFIFO_DATA_RDY)
		sii8620_पढ़ो_burst(ctx);

	अगर (stat & BIT_MDT_XFIFO_EMPTY)
		sii8620_ग_लिखो(ctx, REG_MDT_XMIT_CTRL, 0);

	sii8620_ग_लिखो(ctx, REG_MDT_INT_0, stat);
पूर्ण

अटल व्योम sii8620_status_dcap_पढ़ोy(काष्ठा sii8620 *ctx)
अणु
	क्रमागत sii8620_mode mode;

	mode = ctx->stat[MHL_DST_VERSION] >= 0x30 ? CM_MHL3 : CM_MHL1;
	अगर (mode > ctx->mode)
		sii8620_set_mode(ctx, mode);
	sii8620_peer_specअगरic_init(ctx);
	sii8620_ग_लिखो(ctx, REG_INTR9_MASK, BIT_INTR9_DEVCAP_DONE
		      | BIT_INTR9_EDID_DONE | BIT_INTR9_EDID_ERROR);
पूर्ण

अटल व्योम sii8620_status_changed_path(काष्ठा sii8620 *ctx)
अणु
	u8 link_mode;

	अगर (ctx->use_packed_pixel)
		link_mode = MHL_DST_LM_CLK_MODE_PACKED_PIXEL;
	अन्यथा
		link_mode = MHL_DST_LM_CLK_MODE_NORMAL;

	अगर (ctx->stat[MHL_DST_LINK_MODE] & MHL_DST_LM_PATH_ENABLED)
		link_mode |= MHL_DST_LM_PATH_ENABLED;

	sii8620_mt_ग_लिखो_stat(ctx, MHL_DST_REG(LINK_MODE),
			      link_mode);
पूर्ण

अटल व्योम sii8620_msc_mr_ग_लिखो_stat(काष्ठा sii8620 *ctx)
अणु
	u8 st[MHL_DST_SIZE], xst[MHL_XDS_SIZE];

	sii8620_पढ़ो_buf(ctx, REG_MHL_STAT_0, st, MHL_DST_SIZE);
	sii8620_पढ़ो_buf(ctx, REG_MHL_EXTSTAT_0, xst, MHL_XDS_SIZE);

	sii8620_update_array(ctx->stat, st, MHL_DST_SIZE);
	sii8620_update_array(ctx->xstat, xst, MHL_XDS_SIZE);

	अगर (ctx->stat[MHL_DST_CONNECTED_RDY] & st[MHL_DST_CONNECTED_RDY] &
	    MHL_DST_CONN_DCAP_RDY) अणु
		sii8620_status_dcap_पढ़ोy(ctx);

		अगर (!sii8620_is_mhl3(ctx))
			sii8620_mt_पढ़ो_devcap(ctx, false);
	पूर्ण

	अगर (st[MHL_DST_LINK_MODE] & MHL_DST_LM_PATH_ENABLED)
		sii8620_status_changed_path(ctx);
पूर्ण

अटल व्योम sii8620_ecbus_up(काष्ठा sii8620 *ctx, पूर्णांक ret)
अणु
	अगर (ret < 0)
		वापस;

	sii8620_set_mode(ctx, CM_ECBUS_S);
पूर्ण

अटल व्योम sii8620_got_ecbus_speed(काष्ठा sii8620 *ctx, पूर्णांक ret)
अणु
	अगर (ret < 0)
		वापस;

	sii8620_mt_ग_लिखो_stat(ctx, MHL_XDS_REG(CURR_ECBUS_MODE),
			      MHL_XDS_ECBUS_S | MHL_XDS_SLOT_MODE_8BIT);
	sii8620_mt_rap(ctx, MHL_RAP_CBUS_MODE_UP);
	sii8620_mt_set_cont(ctx, sii8620_ecbus_up);
पूर्ण

अटल व्योम sii8620_mhl_burst_emsc_support_set(काष्ठा mhl_burst_emsc_support *d,
	क्रमागत mhl_burst_id id)
अणु
	sii8620_mhl_burst_hdr_set(&d->hdr, MHL_BURST_ID_EMSC_SUPPORT);
	d->num_entries = 1;
	d->burst_id[0] = cpu_to_be16(id);
पूर्ण

अटल व्योम sii8620_send_features(काष्ठा sii8620 *ctx)
अणु
	u8 buf[16];

	sii8620_ग_लिखो(ctx, REG_MDT_XMIT_CTRL, BIT_MDT_XMIT_CTRL_EN
		| BIT_MDT_XMIT_CTRL_FIXED_BURST_LEN);
	sii8620_mhl_burst_emsc_support_set((व्योम *)buf,
		MHL_BURST_ID_HID_PAYLOAD);
	sii8620_ग_लिखो_buf(ctx, REG_MDT_XMIT_WRITE_PORT, buf, ARRAY_SIZE(buf));
पूर्ण

अटल bool sii8620_rcp_consume(काष्ठा sii8620 *ctx, u8 scancode)
अणु
	bool pressed = !(scancode & MHL_RCP_KEY_RELEASED_MASK);

	scancode &= MHL_RCP_KEY_ID_MASK;

	अगर (!IS_ENABLED(CONFIG_RC_CORE) || !ctx->rc_dev)
		वापस false;

	अगर (pressed)
		rc_keyकरोwn(ctx->rc_dev, RC_PROTO_CEC, scancode, 0);
	अन्यथा
		rc_keyup(ctx->rc_dev);

	वापस true;
पूर्ण

अटल व्योम sii8620_msc_mr_set_पूर्णांक(काष्ठा sii8620 *ctx)
अणु
	u8 पूर्णांकs[MHL_INT_SIZE];

	sii8620_पढ़ो_buf(ctx, REG_MHL_INT_0, पूर्णांकs, MHL_INT_SIZE);
	sii8620_ग_लिखो_buf(ctx, REG_MHL_INT_0, पूर्णांकs, MHL_INT_SIZE);

	अगर (पूर्णांकs[MHL_INT_RCHANGE] & MHL_INT_RC_DCAP_CHG) अणु
		चयन (ctx->mode) अणु
		हाल CM_MHL3:
			sii8620_mt_पढ़ो_xdevcap_reg(ctx, MHL_XDC_ECBUS_SPEEDS);
			sii8620_mt_set_cont(ctx, sii8620_got_ecbus_speed);
			अवरोध;
		हाल CM_ECBUS_S:
			sii8620_mt_पढ़ो_devcap(ctx, true);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (पूर्णांकs[MHL_INT_RCHANGE] & MHL_INT_RC_FEAT_REQ)
		sii8620_send_features(ctx);
	अगर (पूर्णांकs[MHL_INT_RCHANGE] & MHL_INT_RC_FEAT_COMPLETE) अणु
		ctx->feature_complete = true;
		अगर (ctx->edid)
			sii8620_enable_hpd(ctx);
	पूर्ण
पूर्ण

अटल काष्ठा sii8620_mt_msg *sii8620_msc_msg_first(काष्ठा sii8620 *ctx)
अणु
	काष्ठा device *dev = ctx->dev;

	अगर (list_empty(&ctx->mt_queue)) अणु
		dev_err(dev, "unexpected MSC MT response\n");
		वापस शून्य;
	पूर्ण

	वापस list_first_entry(&ctx->mt_queue, काष्ठा sii8620_mt_msg, node);
पूर्ण

अटल व्योम sii8620_msc_mt_करोne(काष्ठा sii8620 *ctx)
अणु
	काष्ठा sii8620_mt_msg *msg = sii8620_msc_msg_first(ctx);

	अगर (!msg)
		वापस;

	msg->ret = sii8620_पढ़ोb(ctx, REG_MSC_MT_RCVD_DATA0);
	ctx->mt_state = MT_STATE_DONE;
पूर्ण

अटल व्योम sii8620_msc_mr_msc_msg(काष्ठा sii8620 *ctx)
अणु
	काष्ठा sii8620_mt_msg *msg;
	u8 buf[2];

	sii8620_पढ़ो_buf(ctx, REG_MSC_MR_MSC_MSG_RCVD_1ST_DATA, buf, 2);

	चयन (buf[0]) अणु
	हाल MHL_MSC_MSG_RAPK:
		msg = sii8620_msc_msg_first(ctx);
		अगर (!msg)
			वापस;
		msg->ret = buf[1];
		ctx->mt_state = MT_STATE_DONE;
		अवरोध;
	हाल MHL_MSC_MSG_RCP:
		अगर (!sii8620_rcp_consume(ctx, buf[1]))
			sii8620_mt_rcpe(ctx,
					MHL_RCPE_STATUS_INEFFECTIVE_KEY_CODE);
		sii8620_mt_rcpk(ctx, buf[1]);
		अवरोध;
	शेष:
		dev_err(ctx->dev, "%s message type %d,%d not supported",
			__func__, buf[0], buf[1]);
	पूर्ण
पूर्ण

अटल व्योम sii8620_irq_msc(काष्ठा sii8620 *ctx)
अणु
	u8 stat = sii8620_पढ़ोb(ctx, REG_CBUS_INT_0);

	अगर (stat & ~BIT_CBUS_HPD_CHG)
		sii8620_ग_लिखो(ctx, REG_CBUS_INT_0, stat & ~BIT_CBUS_HPD_CHG);

	अगर (stat & BIT_CBUS_HPD_CHG) अणु
		u8 cbus_stat = sii8620_पढ़ोb(ctx, REG_CBUS_STATUS);

		अगर ((cbus_stat ^ ctx->cbus_status) & BIT_CBUS_STATUS_CBUS_HPD) अणु
			sii8620_ग_लिखो(ctx, REG_CBUS_INT_0, BIT_CBUS_HPD_CHG);
		पूर्ण अन्यथा अणु
			stat ^= BIT_CBUS_STATUS_CBUS_HPD;
			cbus_stat ^= BIT_CBUS_STATUS_CBUS_HPD;
		पूर्ण
		ctx->cbus_status = cbus_stat;
	पूर्ण

	अगर (stat & BIT_CBUS_MSC_MR_WRITE_STAT)
		sii8620_msc_mr_ग_लिखो_stat(ctx);

	अगर (stat & BIT_CBUS_HPD_CHG) अणु
		अगर (ctx->cbus_status & BIT_CBUS_STATUS_CBUS_HPD) अणु
			ctx->sink_detected = true;
			sii8620_identअगरy_sink(ctx);
		पूर्ण अन्यथा अणु
			sii8620_hpd_unplugged(ctx);
		पूर्ण
	पूर्ण

	अगर (stat & BIT_CBUS_MSC_MR_SET_INT)
		sii8620_msc_mr_set_पूर्णांक(ctx);

	अगर (stat & BIT_CBUS_MSC_MT_DONE)
		sii8620_msc_mt_करोne(ctx);

	अगर (stat & BIT_CBUS_MSC_MR_MSC_MSG)
		sii8620_msc_mr_msc_msg(ctx);
पूर्ण

अटल व्योम sii8620_irq_coc(काष्ठा sii8620 *ctx)
अणु
	u8 stat = sii8620_पढ़ोb(ctx, REG_COC_INTR);

	अगर (stat & BIT_COC_CALIBRATION_DONE) अणु
		u8 cstat = sii8620_पढ़ोb(ctx, REG_COC_STAT_0);

		cstat &= BIT_COC_STAT_0_PLL_LOCKED | MSK_COC_STAT_0_FSM_STATE;
		अगर (cstat == (BIT_COC_STAT_0_PLL_LOCKED | 0x02)) अणु
			sii8620_ग_लिखो_seq_अटल(ctx,
				REG_COC_CTLB, 0,
				REG_TRXINTMH, BIT_TDM_INTR_SYNC_DATA
					      | BIT_TDM_INTR_SYNC_WAIT
			);
		पूर्ण
	पूर्ण

	sii8620_ग_लिखो(ctx, REG_COC_INTR, stat);
पूर्ण

अटल व्योम sii8620_irq_merr(काष्ठा sii8620 *ctx)
अणु
	u8 stat = sii8620_पढ़ोb(ctx, REG_CBUS_INT_1);

	sii8620_ग_लिखो(ctx, REG_CBUS_INT_1, stat);
पूर्ण

अटल व्योम sii8620_irq_edid(काष्ठा sii8620 *ctx)
अणु
	u8 stat = sii8620_पढ़ोb(ctx, REG_INTR9);

	sii8620_ग_लिखो(ctx, REG_INTR9, stat);

	अगर (stat & BIT_INTR9_DEVCAP_DONE)
		ctx->mt_state = MT_STATE_DONE;
पूर्ण

अटल व्योम sii8620_irq_scdt(काष्ठा sii8620 *ctx)
अणु
	u8 stat = sii8620_पढ़ोb(ctx, REG_INTR5);

	अगर (stat & BIT_INTR_SCDT_CHANGE) अणु
		u8 cstat = sii8620_पढ़ोb(ctx, REG_TMDS_CSTAT_P3);

		अगर (cstat & BIT_TMDS_CSTAT_P3_SCDT)
			sii8620_start_video(ctx);
	पूर्ण

	sii8620_ग_लिखो(ctx, REG_INTR5, stat);
पूर्ण

अटल व्योम sii8620_got_xdevcap(काष्ठा sii8620 *ctx, पूर्णांक ret)
अणु
	अगर (ret < 0)
		वापस;

	sii8620_mt_पढ़ो_devcap(ctx, false);
पूर्ण

अटल व्योम sii8620_irq_tdm(काष्ठा sii8620 *ctx)
अणु
	u8 stat = sii8620_पढ़ोb(ctx, REG_TRXINTH);
	u8 tdm = sii8620_पढ़ोb(ctx, REG_TRXSTA2);

	अगर ((tdm & MSK_TDM_SYNCHRONIZED) == VAL_TDM_SYNCHRONIZED) अणु
		ctx->mode = CM_ECBUS_S;
		ctx->burst.rx_ack = 0;
		ctx->burst.r_size = SII8620_BURST_BUF_LEN;
		sii8620_burst_tx_rbuf_info(ctx, SII8620_BURST_BUF_LEN);
		sii8620_mt_पढ़ो_devcap(ctx, true);
		sii8620_mt_set_cont(ctx, sii8620_got_xdevcap);
	पूर्ण अन्यथा अणु
		sii8620_ग_लिखो_seq_अटल(ctx,
			REG_MHL_PLL_CTL2, 0,
			REG_MHL_PLL_CTL2, BIT_MHL_PLL_CTL2_CLKDETECT_EN
		);
	पूर्ण

	sii8620_ग_लिखो(ctx, REG_TRXINTH, stat);
पूर्ण

अटल व्योम sii8620_irq_block(काष्ठा sii8620 *ctx)
अणु
	u8 stat = sii8620_पढ़ोb(ctx, REG_EMSCINTR);

	अगर (stat & BIT_EMSCINTR_SPI_DVLD) अणु
		u8 bstat = sii8620_पढ़ोb(ctx, REG_SPIBURSTSTAT);

		अगर (bstat & BIT_SPIBURSTSTAT_EMSC_NORMAL_MODE)
			sii8620_burst_receive(ctx);
	पूर्ण

	sii8620_ग_लिखो(ctx, REG_EMSCINTR, stat);
पूर्ण

अटल व्योम sii8620_irq_ddc(काष्ठा sii8620 *ctx)
अणु
	u8 stat = sii8620_पढ़ोb(ctx, REG_INTR3);

	अगर (stat & BIT_DDC_CMD_DONE) अणु
		sii8620_ग_लिखो(ctx, REG_INTR3_MASK, 0);
		अगर (sii8620_is_mhl3(ctx) && !ctx->feature_complete)
			sii8620_mt_set_पूर्णांक(ctx, MHL_INT_REG(RCHANGE),
					   MHL_INT_RC_FEAT_REQ);
		अन्यथा
			sii8620_enable_hpd(ctx);
	पूर्ण
	sii8620_ग_लिखो(ctx, REG_INTR3, stat);
पूर्ण

/* endian agnostic, non-अस्थिर version of test_bit */
अटल bool sii8620_test_bit(अचिन्हित पूर्णांक nr, स्थिर u8 *addr)
अणु
	वापस 1 & (addr[nr / BITS_PER_BYTE] >> (nr % BITS_PER_BYTE));
पूर्ण

अटल irqवापस_t sii8620_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	अटल स्थिर काष्ठा अणु
		पूर्णांक bit;
		व्योम (*handler)(काष्ठा sii8620 *ctx);
	पूर्ण irq_vec[] = अणु
		अणु BIT_FAST_INTR_STAT_DISC, sii8620_irq_disc पूर्ण,
		अणु BIT_FAST_INTR_STAT_G2WB, sii8620_irq_g2wb पूर्ण,
		अणु BIT_FAST_INTR_STAT_COC, sii8620_irq_coc पूर्ण,
		अणु BIT_FAST_INTR_STAT_TDM, sii8620_irq_tdm पूर्ण,
		अणु BIT_FAST_INTR_STAT_MSC, sii8620_irq_msc पूर्ण,
		अणु BIT_FAST_INTR_STAT_MERR, sii8620_irq_merr पूर्ण,
		अणु BIT_FAST_INTR_STAT_BLOCK, sii8620_irq_block पूर्ण,
		अणु BIT_FAST_INTR_STAT_EDID, sii8620_irq_edid पूर्ण,
		अणु BIT_FAST_INTR_STAT_DDC, sii8620_irq_ddc पूर्ण,
		अणु BIT_FAST_INTR_STAT_SCDT, sii8620_irq_scdt पूर्ण,
	पूर्ण;
	काष्ठा sii8620 *ctx = data;
	u8 stats[LEN_FAST_INTR_STAT];
	पूर्णांक i, ret;

	mutex_lock(&ctx->lock);

	sii8620_पढ़ो_buf(ctx, REG_FAST_INTR_STAT, stats, ARRAY_SIZE(stats));
	क्रम (i = 0; i < ARRAY_SIZE(irq_vec); ++i)
		अगर (sii8620_test_bit(irq_vec[i].bit, stats))
			irq_vec[i].handler(ctx);

	sii8620_burst_rx_all(ctx);
	sii8620_mt_work(ctx);
	sii8620_burst_send(ctx);

	ret = sii8620_clear_error(ctx);
	अगर (ret) अणु
		dev_err(ctx->dev, "Error during IRQ handling, %d.\n", ret);
		sii8620_mhl_disconnected(ctx);
	पूर्ण
	mutex_unlock(&ctx->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sii8620_cable_in(काष्ठा sii8620 *ctx)
अणु
	काष्ठा device *dev = ctx->dev;
	u8 ver[5];
	पूर्णांक ret;

	ret = sii8620_hw_on(ctx);
	अगर (ret) अणु
		dev_err(dev, "Error powering on, %d.\n", ret);
		वापस;
	पूर्ण

	sii8620_पढ़ो_buf(ctx, REG_VND_IDL, ver, ARRAY_SIZE(ver));
	ret = sii8620_clear_error(ctx);
	अगर (ret) अणु
		dev_err(dev, "Error accessing I2C bus, %d.\n", ret);
		वापस;
	पूर्ण

	dev_info(dev, "ChipID %02x%02x:%02x%02x rev %02x.\n", ver[1], ver[0],
		 ver[3], ver[2], ver[4]);

	sii8620_ग_लिखो(ctx, REG_DPD,
		      BIT_DPD_PWRON_PLL | BIT_DPD_PDNTX12 | BIT_DPD_OSC_EN);

	sii8620_xtal_set_rate(ctx);
	sii8620_disconnect(ctx);

	sii8620_ग_लिखो_seq_अटल(ctx,
		REG_MHL_CBUS_CTL0, VAL_MHL_CBUS_CTL0_CBUS_DRV_SEL_STRONG
			| VAL_MHL_CBUS_CTL0_CBUS_RGND_VBIAS_734,
		REG_MHL_CBUS_CTL1, VAL_MHL_CBUS_CTL1_1115_OHM,
		REG_DPD, BIT_DPD_PWRON_PLL | BIT_DPD_PDNTX12 | BIT_DPD_OSC_EN,
	);

	ret = sii8620_clear_error(ctx);
	अगर (ret) अणु
		dev_err(dev, "Error accessing I2C bus, %d.\n", ret);
		वापस;
	पूर्ण

	enable_irq(to_i2c_client(ctx->dev)->irq);
पूर्ण

अटल व्योम sii8620_init_rcp_input_dev(काष्ठा sii8620 *ctx)
अणु
	काष्ठा rc_dev *rc_dev;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_RC_CORE))
		वापस;

	rc_dev = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!rc_dev) अणु
		dev_err(ctx->dev, "Failed to allocate RC device\n");
		ctx->error = -ENOMEM;
		वापस;
	पूर्ण

	rc_dev->input_phys = "sii8620/input0";
	rc_dev->input_id.bustype = BUS_VIRTUAL;
	rc_dev->map_name = RC_MAP_CEC;
	rc_dev->allowed_protocols = RC_PROTO_BIT_CEC;
	rc_dev->driver_name = "sii8620";
	rc_dev->device_name = "sii8620";

	ret = rc_रेजिस्टर_device(rc_dev);

	अगर (ret) अणु
		dev_err(ctx->dev, "Failed to register RC device\n");
		ctx->error = ret;
		rc_मुक्त_device(ctx->rc_dev);
		वापस;
	पूर्ण
	ctx->rc_dev = rc_dev;
पूर्ण

अटल व्योम sii8620_cable_out(काष्ठा sii8620 *ctx)
अणु
	disable_irq(to_i2c_client(ctx->dev)->irq);
	sii8620_hw_off(ctx);
पूर्ण

अटल व्योम sii8620_extcon_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sii8620 *ctx =
		container_of(work, काष्ठा sii8620, extcon_wq);
	पूर्णांक state = extcon_get_state(ctx->extcon, EXTCON_DISP_MHL);

	अगर (state == ctx->cable_state)
		वापस;

	ctx->cable_state = state;

	अगर (state > 0)
		sii8620_cable_in(ctx);
	अन्यथा
		sii8620_cable_out(ctx);
पूर्ण

अटल पूर्णांक sii8620_extcon_notअगरier(काष्ठा notअगरier_block *self,
			अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा sii8620 *ctx =
		container_of(self, काष्ठा sii8620, extcon_nb);

	schedule_work(&ctx->extcon_wq);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक sii8620_extcon_init(काष्ठा sii8620 *ctx)
अणु
	काष्ठा extcon_dev *edev;
	काष्ठा device_node *musb, *muic;
	पूर्णांक ret;

	/* get micro-USB connector node */
	musb = of_graph_get_remote_node(ctx->dev->of_node, 1, -1);
	/* next get micro-USB Interface Controller node */
	muic = of_get_next_parent(musb);

	अगर (!muic) अणु
		dev_info(ctx->dev, "no extcon found, switching to 'always on' mode\n");
		वापस 0;
	पूर्ण

	edev = extcon_find_edev_by_node(muic);
	of_node_put(muic);
	अगर (IS_ERR(edev)) अणु
		अगर (PTR_ERR(edev) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_err(ctx->dev, "Invalid or missing extcon\n");
		वापस PTR_ERR(edev);
	पूर्ण

	ctx->extcon = edev;
	ctx->extcon_nb.notअगरier_call = sii8620_extcon_notअगरier;
	INIT_WORK(&ctx->extcon_wq, sii8620_extcon_work);
	ret = extcon_रेजिस्टर_notअगरier(edev, EXTCON_DISP_MHL, &ctx->extcon_nb);
	अगर (ret) अणु
		dev_err(ctx->dev, "failed to register notifier for MHL\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा sii8620 *bridge_to_sii8620(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा sii8620, bridge);
पूर्ण

अटल पूर्णांक sii8620_attach(काष्ठा drm_bridge *bridge,
			  क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा sii8620 *ctx = bridge_to_sii8620(bridge);

	sii8620_init_rcp_input_dev(ctx);

	वापस sii8620_clear_error(ctx);
पूर्ण

अटल व्योम sii8620_detach(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा sii8620 *ctx = bridge_to_sii8620(bridge);

	अगर (!IS_ENABLED(CONFIG_RC_CORE))
		वापस;

	rc_unरेजिस्टर_device(ctx->rc_dev);
पूर्ण

अटल पूर्णांक sii8620_is_packing_required(काष्ठा sii8620 *ctx,
				       स्थिर काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक max_pclk, max_pclk_pp_mode;

	अगर (sii8620_is_mhl3(ctx)) अणु
		max_pclk = MHL3_MAX_PCLK;
		max_pclk_pp_mode = MHL3_MAX_PCLK_PP_MODE;
	पूर्ण अन्यथा अणु
		max_pclk = MHL1_MAX_PCLK;
		max_pclk_pp_mode = MHL1_MAX_PCLK_PP_MODE;
	पूर्ण

	अगर (mode->घड़ी < max_pclk)
		वापस 0;
	अन्यथा अगर (mode->घड़ी < max_pclk_pp_mode)
		वापस 1;
	अन्यथा
		वापस -1;
पूर्ण

अटल क्रमागत drm_mode_status sii8620_mode_valid(काष्ठा drm_bridge *bridge,
					 स्थिर काष्ठा drm_display_info *info,
					 स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा sii8620 *ctx = bridge_to_sii8620(bridge);
	पूर्णांक pack_required = sii8620_is_packing_required(ctx, mode);
	bool can_pack = ctx->devcap[MHL_DCAP_VID_LINK_MODE] &
			MHL_DCAP_VID_LINK_PPIXEL;

	चयन (pack_required) अणु
	हाल 0:
		वापस MODE_OK;
	हाल 1:
		वापस (can_pack) ? MODE_OK : MODE_CLOCK_HIGH;
	शेष:
		वापस MODE_CLOCK_HIGH;
	पूर्ण
पूर्ण

अटल bool sii8620_mode_fixup(काष्ठा drm_bridge *bridge,
			       स्थिर काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा sii8620 *ctx = bridge_to_sii8620(bridge);

	mutex_lock(&ctx->lock);

	ctx->use_packed_pixel = sii8620_is_packing_required(ctx, adjusted_mode);

	mutex_unlock(&ctx->lock);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs sii8620_bridge_funcs = अणु
	.attach = sii8620_attach,
	.detach = sii8620_detach,
	.mode_fixup = sii8620_mode_fixup,
	.mode_valid = sii8620_mode_valid,
पूर्ण;

अटल पूर्णांक sii8620_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा sii8620 *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = dev;
	mutex_init(&ctx->lock);
	INIT_LIST_HEAD(&ctx->mt_queue);

	ctx->clk_xtal = devm_clk_get(dev, "xtal");
	अगर (IS_ERR(ctx->clk_xtal))
		वापस dev_err_probe(dev, PTR_ERR(ctx->clk_xtal),
				     "failed to get xtal clock from DT\n");

	अगर (!client->irq) अणु
		dev_err(dev, "no irq provided\n");
		वापस -EINVAL;
	पूर्ण
	irq_set_status_flags(client->irq, IRQ_NOAUTOEN);
	ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
					sii8620_irq_thपढ़ो,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"sii8620", ctx);
	अगर (ret < 0)
		वापस dev_err_probe(dev, ret,
				     "failed to install IRQ handler\n");

	ctx->gpio_reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ctx->gpio_reset))
		वापस dev_err_probe(dev, PTR_ERR(ctx->gpio_reset),
				     "failed to get reset gpio from DT\n");

	ctx->supplies[0].supply = "cvcc10";
	ctx->supplies[1].supply = "iovcc18";
	ret = devm_regulator_bulk_get(dev, 2, ctx->supplies);
	अगर (ret)
		वापस ret;

	ret = sii8620_extcon_init(ctx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "failed to initialize EXTCON\n");
		वापस ret;
	पूर्ण

	i2c_set_clientdata(client, ctx);

	ctx->bridge.funcs = &sii8620_bridge_funcs;
	ctx->bridge.of_node = dev->of_node;
	drm_bridge_add(&ctx->bridge);

	अगर (!ctx->extcon)
		sii8620_cable_in(ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक sii8620_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा sii8620 *ctx = i2c_get_clientdata(client);

	अगर (ctx->extcon) अणु
		extcon_unरेजिस्टर_notअगरier(ctx->extcon, EXTCON_DISP_MHL,
					   &ctx->extcon_nb);
		flush_work(&ctx->extcon_wq);
		अगर (ctx->cable_state > 0)
			sii8620_cable_out(ctx);
	पूर्ण अन्यथा अणु
		sii8620_cable_out(ctx);
	पूर्ण
	drm_bridge_हटाओ(&ctx->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sii8620_dt_match[] = अणु
	अणु .compatible = "sil,sii8620" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sii8620_dt_match);

अटल स्थिर काष्ठा i2c_device_id sii8620_id[] = अणु
	अणु "sii8620", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, sii8620_id);
अटल काष्ठा i2c_driver sii8620_driver = अणु
	.driver = अणु
		.name	= "sii8620",
		.of_match_table = of_match_ptr(sii8620_dt_match),
	पूर्ण,
	.probe		= sii8620_probe,
	.हटाओ		= sii8620_हटाओ,
	.id_table = sii8620_id,
पूर्ण;

module_i2c_driver(sii8620_driver);
MODULE_LICENSE("GPL v2");
