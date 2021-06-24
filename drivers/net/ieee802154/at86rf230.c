<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AT86RF230/RF231 driver
 *
 * Copyright (C) 2009-2012 Siemens AG
 *
 * Written by:
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 * Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 * Alexander Aring <aar@pengutronix.de>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/at86rf230.h>
#समावेश <linux/regmap.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/ieee802154.h>
#समावेश <linux/debugfs.h>

#समावेश <net/mac802154.h>
#समावेश <net/cfg802154.h>

#समावेश "at86rf230.h"

काष्ठा at86rf230_local;
/* at86rf2xx chip depend data.
 * All timings are in us.
 */
काष्ठा at86rf2xx_chip_data अणु
	u16 t_sleep_cycle;
	u16 t_channel_चयन;
	u16 t_reset_to_off;
	u16 t_off_to_aack;
	u16 t_off_to_tx_on;
	u16 t_off_to_sleep;
	u16 t_sleep_to_off;
	u16 t_frame;
	u16 t_p_ack;
	पूर्णांक rssi_base_val;

	पूर्णांक (*set_channel)(काष्ठा at86rf230_local *, u8, u8);
	पूर्णांक (*set_txघातer)(काष्ठा at86rf230_local *, s32);
पूर्ण;

#घोषणा AT86RF2XX_MAX_BUF		(127 + 3)
/* tx retries to access the TX_ON state
 * अगर it's above then क्रमce change will be started.
 *
 * We assume the max_frame_retries (7) value of 802.15.4 here.
 */
#घोषणा AT86RF2XX_MAX_TX_RETRIES	7
/* We use the recommended 5 minutes समयout to recalibrate */
#घोषणा AT86RF2XX_CAL_LOOP_TIMEOUT	(5 * 60 * HZ)

काष्ठा at86rf230_state_change अणु
	काष्ठा at86rf230_local *lp;
	पूर्णांक irq;

	काष्ठा hrसमयr समयr;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer trx;
	u8 buf[AT86RF2XX_MAX_BUF];

	व्योम (*complete)(व्योम *context);
	u8 from_state;
	u8 to_state;

	bool मुक्त;
पूर्ण;

काष्ठा at86rf230_trac अणु
	u64 success;
	u64 success_data_pending;
	u64 success_रुको_क्रम_ack;
	u64 channel_access_failure;
	u64 no_ack;
	u64 invalid;
पूर्ण;

काष्ठा at86rf230_local अणु
	काष्ठा spi_device *spi;

	काष्ठा ieee802154_hw *hw;
	काष्ठा at86rf2xx_chip_data *data;
	काष्ठा regmap *regmap;
	पूर्णांक slp_tr;
	bool sleep;

	काष्ठा completion state_complete;
	काष्ठा at86rf230_state_change state;

	अचिन्हित दीर्घ cal_समयout;
	bool is_tx;
	bool is_tx_from_off;
	u8 tx_retry;
	काष्ठा sk_buff *tx_skb;
	काष्ठा at86rf230_state_change tx;

	काष्ठा at86rf230_trac trac;
पूर्ण;

#घोषणा AT86RF2XX_NUMREGS 0x3F

अटल व्योम
at86rf230_async_state_change(काष्ठा at86rf230_local *lp,
			     काष्ठा at86rf230_state_change *ctx,
			     स्थिर u8 state, व्योम (*complete)(व्योम *context));

अटल अंतरभूत व्योम
at86rf230_sleep(काष्ठा at86rf230_local *lp)
अणु
	अगर (gpio_is_valid(lp->slp_tr)) अणु
		gpio_set_value(lp->slp_tr, 1);
		usleep_range(lp->data->t_off_to_sleep,
			     lp->data->t_off_to_sleep + 10);
		lp->sleep = true;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
at86rf230_awake(काष्ठा at86rf230_local *lp)
अणु
	अगर (gpio_is_valid(lp->slp_tr)) अणु
		gpio_set_value(lp->slp_tr, 0);
		usleep_range(lp->data->t_sleep_to_off,
			     lp->data->t_sleep_to_off + 100);
		lp->sleep = false;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
__at86rf230_ग_लिखो(काष्ठा at86rf230_local *lp,
		  अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data)
अणु
	bool sleep = lp->sleep;
	पूर्णांक ret;

	/* awake क्रम रेजिस्टर setting अगर sleep */
	अगर (sleep)
		at86rf230_awake(lp);

	ret = regmap_ग_लिखो(lp->regmap, addr, data);

	/* sleep again अगर was sleeping */
	अगर (sleep)
		at86rf230_sleep(lp);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
__at86rf230_पढ़ो(काष्ठा at86rf230_local *lp,
		 अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक *data)
अणु
	bool sleep = lp->sleep;
	पूर्णांक ret;

	/* awake क्रम रेजिस्टर setting अगर sleep */
	अगर (sleep)
		at86rf230_awake(lp);

	ret = regmap_पढ़ो(lp->regmap, addr, data);

	/* sleep again अगर was sleeping */
	अगर (sleep)
		at86rf230_sleep(lp);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
at86rf230_पढ़ो_subreg(काष्ठा at86rf230_local *lp,
		      अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक mask,
		      अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक rc;

	rc = __at86rf230_पढ़ो(lp, addr, data);
	अगर (!rc)
		*data = (*data & mask) >> shअगरt;

	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक
at86rf230_ग_लिखो_subreg(काष्ठा at86rf230_local *lp,
		       अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक mask,
		       अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक data)
अणु
	bool sleep = lp->sleep;
	पूर्णांक ret;

	/* awake क्रम रेजिस्टर setting अगर sleep */
	अगर (sleep)
		at86rf230_awake(lp);

	ret = regmap_update_bits(lp->regmap, addr, mask, data << shअगरt);

	/* sleep again अगर was sleeping */
	अगर (sleep)
		at86rf230_sleep(lp);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
at86rf230_slp_tr_rising_edge(काष्ठा at86rf230_local *lp)
अणु
	gpio_set_value(lp->slp_tr, 1);
	udelay(1);
	gpio_set_value(lp->slp_tr, 0);
पूर्ण

अटल bool
at86rf230_reg_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RG_TRX_STATE:
	हाल RG_TRX_CTRL_0:
	हाल RG_TRX_CTRL_1:
	हाल RG_PHY_TX_PWR:
	हाल RG_PHY_ED_LEVEL:
	हाल RG_PHY_CC_CCA:
	हाल RG_CCA_THRES:
	हाल RG_RX_CTRL:
	हाल RG_SFD_VALUE:
	हाल RG_TRX_CTRL_2:
	हाल RG_ANT_DIV:
	हाल RG_IRQ_MASK:
	हाल RG_VREG_CTRL:
	हाल RG_BATMON:
	हाल RG_XOSC_CTRL:
	हाल RG_RX_SYN:
	हाल RG_XAH_CTRL_1:
	हाल RG_FTN_CTRL:
	हाल RG_PLL_CF:
	हाल RG_PLL_DCU:
	हाल RG_SHORT_ADDR_0:
	हाल RG_SHORT_ADDR_1:
	हाल RG_PAN_ID_0:
	हाल RG_PAN_ID_1:
	हाल RG_IEEE_ADDR_0:
	हाल RG_IEEE_ADDR_1:
	हाल RG_IEEE_ADDR_2:
	हाल RG_IEEE_ADDR_3:
	हाल RG_IEEE_ADDR_4:
	हाल RG_IEEE_ADDR_5:
	हाल RG_IEEE_ADDR_6:
	हाल RG_IEEE_ADDR_7:
	हाल RG_XAH_CTRL_0:
	हाल RG_CSMA_SEED_0:
	हाल RG_CSMA_SEED_1:
	हाल RG_CSMA_BE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
at86rf230_reg_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	bool rc;

	/* all ग_लिखोable are also पढ़ोable */
	rc = at86rf230_reg_ग_लिखोable(dev, reg);
	अगर (rc)
		वापस rc;

	/* पढ़ोonly regs */
	चयन (reg) अणु
	हाल RG_TRX_STATUS:
	हाल RG_PHY_RSSI:
	हाल RG_IRQ_STATUS:
	हाल RG_PART_NUM:
	हाल RG_VERSION_NUM:
	हाल RG_MAN_ID_1:
	हाल RG_MAN_ID_0:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
at86rf230_reg_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* can be changed during runसमय */
	चयन (reg) अणु
	हाल RG_TRX_STATUS:
	हाल RG_TRX_STATE:
	हाल RG_PHY_RSSI:
	हाल RG_PHY_ED_LEVEL:
	हाल RG_IRQ_STATUS:
	हाल RG_VREG_CTRL:
	हाल RG_PLL_CF:
	हाल RG_PLL_DCU:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
at86rf230_reg_precious(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* करोn't clear irq line on पढ़ो */
	चयन (reg) अणु
	हाल RG_IRQ_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config at86rf230_regmap_spi_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ग_लिखो_flag_mask = CMD_REG | CMD_WRITE,
	.पढ़ो_flag_mask = CMD_REG,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = AT86RF2XX_NUMREGS,
	.ग_लिखोable_reg = at86rf230_reg_ग_लिखोable,
	.पढ़ोable_reg = at86rf230_reg_पढ़ोable,
	.अस्थिर_reg = at86rf230_reg_अस्थिर,
	.precious_reg = at86rf230_reg_precious,
पूर्ण;

अटल व्योम
at86rf230_async_error_recover_complete(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;

	अगर (ctx->मुक्त)
		kमुक्त(ctx);

	ieee802154_wake_queue(lp->hw);
पूर्ण

अटल व्योम
at86rf230_async_error_recover(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;

	lp->is_tx = 0;
	at86rf230_async_state_change(lp, ctx, STATE_RX_AACK_ON,
				     at86rf230_async_error_recover_complete);
पूर्ण

अटल अंतरभूत व्योम
at86rf230_async_error(काष्ठा at86rf230_local *lp,
		      काष्ठा at86rf230_state_change *ctx, पूर्णांक rc)
अणु
	dev_err(&lp->spi->dev, "spi_async error %d\n", rc);

	at86rf230_async_state_change(lp, ctx, STATE_FORCE_TRX_OFF,
				     at86rf230_async_error_recover);
पूर्ण

/* Generic function to get some रेजिस्टर value in async mode */
अटल व्योम
at86rf230_async_पढ़ो_reg(काष्ठा at86rf230_local *lp, u8 reg,
			 काष्ठा at86rf230_state_change *ctx,
			 व्योम (*complete)(व्योम *context))
अणु
	पूर्णांक rc;

	u8 *tx_buf = ctx->buf;

	tx_buf[0] = (reg & CMD_REG_MASK) | CMD_REG;
	ctx->msg.complete = complete;
	rc = spi_async(lp->spi, &ctx->msg);
	अगर (rc)
		at86rf230_async_error(lp, ctx, rc);
पूर्ण

अटल व्योम
at86rf230_async_ग_लिखो_reg(काष्ठा at86rf230_local *lp, u8 reg, u8 val,
			  काष्ठा at86rf230_state_change *ctx,
			  व्योम (*complete)(व्योम *context))
अणु
	पूर्णांक rc;

	ctx->buf[0] = (reg & CMD_REG_MASK) | CMD_REG | CMD_WRITE;
	ctx->buf[1] = val;
	ctx->msg.complete = complete;
	rc = spi_async(lp->spi, &ctx->msg);
	अगर (rc)
		at86rf230_async_error(lp, ctx, rc);
पूर्ण

अटल व्योम
at86rf230_async_state_निश्चित(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;
	स्थिर u8 *buf = ctx->buf;
	स्थिर u8 trx_state = buf[1] & TRX_STATE_MASK;

	/* Assert state change */
	अगर (trx_state != ctx->to_state) अणु
		/* Special handling अगर transceiver state is in
		 * STATE_BUSY_RX_AACK and a SHR was detected.
		 */
		अगर  (trx_state == STATE_BUSY_RX_AACK) अणु
			/* Unकरोcumented race condition. If we send a state
			 * change to STATE_RX_AACK_ON the transceiver could
			 * change his state स्वतःmatically to STATE_BUSY_RX_AACK
			 * अगर a SHR was detected. This is not an error, but we
			 * can't निश्चित this.
			 */
			अगर (ctx->to_state == STATE_RX_AACK_ON)
				जाओ करोne;

			/* If we change to STATE_TX_ON without क्रमcing and
			 * transceiver state is STATE_BUSY_RX_AACK, we रुको
			 * 'tFrame + tPAck' receiving समय. In this समय the
			 * PDU should be received. If the transceiver is still
			 * in STATE_BUSY_RX_AACK, we run a क्रमce state change
			 * to STATE_TX_ON. This is a समयout handling, अगर the
			 * transceiver stucks in STATE_BUSY_RX_AACK.
			 *
			 * Additional we करो several retries to try to get पूर्णांकo
			 * TX_ON state without क्रमcing. If the retries are
			 * higher or equal than AT86RF2XX_MAX_TX_RETRIES we
			 * will करो a क्रमce change.
			 */
			अगर (ctx->to_state == STATE_TX_ON ||
			    ctx->to_state == STATE_TRX_OFF) अणु
				u8 state = ctx->to_state;

				अगर (lp->tx_retry >= AT86RF2XX_MAX_TX_RETRIES)
					state = STATE_FORCE_TRX_OFF;
				lp->tx_retry++;

				at86rf230_async_state_change(lp, ctx, state,
							     ctx->complete);
				वापस;
			पूर्ण
		पूर्ण

		dev_warn(&lp->spi->dev, "unexcept state change from 0x%02x to 0x%02x. Actual state: 0x%02x\n",
			 ctx->from_state, ctx->to_state, trx_state);
	पूर्ण

करोne:
	अगर (ctx->complete)
		ctx->complete(context);
पूर्ण

अटल क्रमागत hrसमयr_restart at86rf230_async_state_समयr(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा at86rf230_state_change *ctx =
		container_of(समयr, काष्ठा at86rf230_state_change, समयr);
	काष्ठा at86rf230_local *lp = ctx->lp;

	at86rf230_async_पढ़ो_reg(lp, RG_TRX_STATUS, ctx,
				 at86rf230_async_state_निश्चित);

	वापस HRTIMER_NORESTART;
पूर्ण

/* Do state change timing delay. */
अटल व्योम
at86rf230_async_state_delay(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;
	काष्ठा at86rf2xx_chip_data *c = lp->data;
	bool क्रमce = false;
	kसमय_प्रकार tim;

	/* The क्रमce state changes are will show as normal states in the
	 * state status subरेजिस्टर. We change the to_state to the
	 * corresponding one and remember अगर it was a क्रमce change, this
	 * dअगरfers अगर we करो a state change from STATE_BUSY_RX_AACK.
	 */
	चयन (ctx->to_state) अणु
	हाल STATE_FORCE_TX_ON:
		ctx->to_state = STATE_TX_ON;
		क्रमce = true;
		अवरोध;
	हाल STATE_FORCE_TRX_OFF:
		ctx->to_state = STATE_TRX_OFF;
		क्रमce = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (ctx->from_state) अणु
	हाल STATE_TRX_OFF:
		चयन (ctx->to_state) अणु
		हाल STATE_RX_AACK_ON:
			tim = c->t_off_to_aack * NSEC_PER_USEC;
			/* state change from TRX_OFF to RX_AACK_ON to करो a
			 * calibration, we need to reset the समयout क्रम the
			 * next one.
			 */
			lp->cal_समयout = jअगरfies + AT86RF2XX_CAL_LOOP_TIMEOUT;
			जाओ change;
		हाल STATE_TX_ARET_ON:
		हाल STATE_TX_ON:
			tim = c->t_off_to_tx_on * NSEC_PER_USEC;
			/* state change from TRX_OFF to TX_ON or ARET_ON to करो
			 * a calibration, we need to reset the समयout क्रम the
			 * next one.
			 */
			lp->cal_समयout = jअगरfies + AT86RF2XX_CAL_LOOP_TIMEOUT;
			जाओ change;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल STATE_BUSY_RX_AACK:
		चयन (ctx->to_state) अणु
		हाल STATE_TRX_OFF:
		हाल STATE_TX_ON:
			/* Wait क्रम worst हाल receiving समय अगर we
			 * didn't make a क्रमce change from BUSY_RX_AACK
			 * to TX_ON or TRX_OFF.
			 */
			अगर (!क्रमce) अणु
				tim = (c->t_frame + c->t_p_ack) * NSEC_PER_USEC;
				जाओ change;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	/* Default value, means RESET state */
	हाल STATE_P_ON:
		चयन (ctx->to_state) अणु
		हाल STATE_TRX_OFF:
			tim = c->t_reset_to_off * NSEC_PER_USEC;
			जाओ change;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Default delay is 1us in the most हालs */
	udelay(1);
	at86rf230_async_state_समयr(&ctx->समयr);
	वापस;

change:
	hrसमयr_start(&ctx->समयr, tim, HRTIMER_MODE_REL);
पूर्ण

अटल व्योम
at86rf230_async_state_change_start(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;
	u8 *buf = ctx->buf;
	स्थिर u8 trx_state = buf[1] & TRX_STATE_MASK;

	/* Check क्रम "possible" STATE_TRANSITION_IN_PROGRESS */
	अगर (trx_state == STATE_TRANSITION_IN_PROGRESS) अणु
		udelay(1);
		at86rf230_async_पढ़ो_reg(lp, RG_TRX_STATUS, ctx,
					 at86rf230_async_state_change_start);
		वापस;
	पूर्ण

	/* Check अगर we alपढ़ोy are in the state which we change in */
	अगर (trx_state == ctx->to_state) अणु
		अगर (ctx->complete)
			ctx->complete(context);
		वापस;
	पूर्ण

	/* Set current state to the context of state change */
	ctx->from_state = trx_state;

	/* Going पूर्णांकo the next step क्रम a state change which करो a timing
	 * relevant delay.
	 */
	at86rf230_async_ग_लिखो_reg(lp, RG_TRX_STATE, ctx->to_state, ctx,
				  at86rf230_async_state_delay);
पूर्ण

अटल व्योम
at86rf230_async_state_change(काष्ठा at86rf230_local *lp,
			     काष्ठा at86rf230_state_change *ctx,
			     स्थिर u8 state, व्योम (*complete)(व्योम *context))
अणु
	/* Initialization क्रम the state change context */
	ctx->to_state = state;
	ctx->complete = complete;
	at86rf230_async_पढ़ो_reg(lp, RG_TRX_STATUS, ctx,
				 at86rf230_async_state_change_start);
पूर्ण

अटल व्योम
at86rf230_sync_state_change_complete(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;

	complete(&lp->state_complete);
पूर्ण

/* This function करो a sync framework above the async state change.
 * Some callbacks of the IEEE 802.15.4 driver पूर्णांकerface need to be
 * handled synchronously.
 */
अटल पूर्णांक
at86rf230_sync_state_change(काष्ठा at86rf230_local *lp, अचिन्हित पूर्णांक state)
अणु
	अचिन्हित दीर्घ rc;

	at86rf230_async_state_change(lp, &lp->state, state,
				     at86rf230_sync_state_change_complete);

	rc = रुको_क्रम_completion_समयout(&lp->state_complete,
					 msecs_to_jअगरfies(100));
	अगर (!rc) अणु
		at86rf230_async_error(lp, &lp->state, -ETIMEDOUT);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
at86rf230_tx_complete(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;

	ieee802154_xmit_complete(lp->hw, lp->tx_skb, false);
	kमुक्त(ctx);
पूर्ण

अटल व्योम
at86rf230_tx_on(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;

	at86rf230_async_state_change(lp, ctx, STATE_RX_AACK_ON,
				     at86rf230_tx_complete);
पूर्ण

अटल व्योम
at86rf230_tx_trac_check(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;

	अगर (IS_ENABLED(CONFIG_IEEE802154_AT86RF230_DEBUGFS)) अणु
		u8 trac = TRAC_MASK(ctx->buf[1]);

		चयन (trac) अणु
		हाल TRAC_SUCCESS:
			lp->trac.success++;
			अवरोध;
		हाल TRAC_SUCCESS_DATA_PENDING:
			lp->trac.success_data_pending++;
			अवरोध;
		हाल TRAC_CHANNEL_ACCESS_FAILURE:
			lp->trac.channel_access_failure++;
			अवरोध;
		हाल TRAC_NO_ACK:
			lp->trac.no_ack++;
			अवरोध;
		हाल TRAC_INVALID:
			lp->trac.invalid++;
			अवरोध;
		शेष:
			WARN_ONCE(1, "received tx trac status %d\n", trac);
			अवरोध;
		पूर्ण
	पूर्ण

	at86rf230_async_state_change(lp, ctx, STATE_TX_ON, at86rf230_tx_on);
पूर्ण

अटल व्योम
at86rf230_rx_पढ़ो_frame_complete(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;
	स्थिर u8 *buf = ctx->buf;
	काष्ठा sk_buff *skb;
	u8 len, lqi;

	len = buf[1];
	अगर (!ieee802154_is_valid_psdu_len(len)) अणु
		dev_vdbg(&lp->spi->dev, "corrupted frame received\n");
		len = IEEE802154_MTU;
	पूर्ण
	lqi = buf[2 + len];

	skb = dev_alloc_skb(IEEE802154_MTU);
	अगर (!skb) अणु
		dev_vdbg(&lp->spi->dev, "failed to allocate sk_buff\n");
		kमुक्त(ctx);
		वापस;
	पूर्ण

	skb_put_data(skb, buf + 2, len);
	ieee802154_rx_irqsafe(lp->hw, skb, lqi);
	kमुक्त(ctx);
पूर्ण

अटल व्योम
at86rf230_rx_trac_check(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;
	u8 *buf = ctx->buf;
	पूर्णांक rc;

	अगर (IS_ENABLED(CONFIG_IEEE802154_AT86RF230_DEBUGFS)) अणु
		u8 trac = TRAC_MASK(buf[1]);

		चयन (trac) अणु
		हाल TRAC_SUCCESS:
			lp->trac.success++;
			अवरोध;
		हाल TRAC_SUCCESS_WAIT_FOR_ACK:
			lp->trac.success_रुको_क्रम_ack++;
			अवरोध;
		हाल TRAC_INVALID:
			lp->trac.invalid++;
			अवरोध;
		शेष:
			WARN_ONCE(1, "received rx trac status %d\n", trac);
			अवरोध;
		पूर्ण
	पूर्ण

	buf[0] = CMD_FB;
	ctx->trx.len = AT86RF2XX_MAX_BUF;
	ctx->msg.complete = at86rf230_rx_पढ़ो_frame_complete;
	rc = spi_async(lp->spi, &ctx->msg);
	अगर (rc) अणु
		ctx->trx.len = 2;
		at86rf230_async_error(lp, ctx, rc);
	पूर्ण
पूर्ण

अटल व्योम
at86rf230_irq_trx_end(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;

	अगर (lp->is_tx) अणु
		lp->is_tx = 0;
		at86rf230_async_पढ़ो_reg(lp, RG_TRX_STATE, ctx,
					 at86rf230_tx_trac_check);
	पूर्ण अन्यथा अणु
		at86rf230_async_पढ़ो_reg(lp, RG_TRX_STATE, ctx,
					 at86rf230_rx_trac_check);
	पूर्ण
पूर्ण

अटल व्योम
at86rf230_irq_status(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;
	स्थिर u8 *buf = ctx->buf;
	u8 irq = buf[1];

	enable_irq(lp->spi->irq);

	अगर (irq & IRQ_TRX_END) अणु
		at86rf230_irq_trx_end(ctx);
	पूर्ण अन्यथा अणु
		dev_err(&lp->spi->dev, "not supported irq %02x received\n",
			irq);
		kमुक्त(ctx);
	पूर्ण
पूर्ण

अटल व्योम
at86rf230_setup_spi_messages(काष्ठा at86rf230_local *lp,
			     काष्ठा at86rf230_state_change *state)
अणु
	state->lp = lp;
	state->irq = lp->spi->irq;
	spi_message_init(&state->msg);
	state->msg.context = state;
	state->trx.len = 2;
	state->trx.tx_buf = state->buf;
	state->trx.rx_buf = state->buf;
	spi_message_add_tail(&state->trx, &state->msg);
	hrसमयr_init(&state->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	state->समयr.function = at86rf230_async_state_समयr;
पूर्ण

अटल irqवापस_t at86rf230_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा at86rf230_local *lp = data;
	काष्ठा at86rf230_state_change *ctx;
	पूर्णांक rc;

	disable_irq_nosync(irq);

	ctx = kzalloc(माप(*ctx), GFP_ATOMIC);
	अगर (!ctx) अणु
		enable_irq(irq);
		वापस IRQ_NONE;
	पूर्ण

	at86rf230_setup_spi_messages(lp, ctx);
	/* tell on error handling to मुक्त ctx */
	ctx->मुक्त = true;

	ctx->buf[0] = (RG_IRQ_STATUS & CMD_REG_MASK) | CMD_REG;
	ctx->msg.complete = at86rf230_irq_status;
	rc = spi_async(lp->spi, &ctx->msg);
	अगर (rc) अणु
		at86rf230_async_error(lp, ctx, rc);
		enable_irq(irq);
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
at86rf230_ग_लिखो_frame_complete(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;

	ctx->trx.len = 2;

	अगर (gpio_is_valid(lp->slp_tr))
		at86rf230_slp_tr_rising_edge(lp);
	अन्यथा
		at86rf230_async_ग_लिखो_reg(lp, RG_TRX_STATE, STATE_BUSY_TX, ctx,
					  शून्य);
पूर्ण

अटल व्योम
at86rf230_ग_लिखो_frame(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;
	काष्ठा sk_buff *skb = lp->tx_skb;
	u8 *buf = ctx->buf;
	पूर्णांक rc;

	lp->is_tx = 1;

	buf[0] = CMD_FB | CMD_WRITE;
	buf[1] = skb->len + 2;
	स_नकल(buf + 2, skb->data, skb->len);
	ctx->trx.len = skb->len + 2;
	ctx->msg.complete = at86rf230_ग_लिखो_frame_complete;
	rc = spi_async(lp->spi, &ctx->msg);
	अगर (rc) अणु
		ctx->trx.len = 2;
		at86rf230_async_error(lp, ctx, rc);
	पूर्ण
पूर्ण

अटल व्योम
at86rf230_xmit_tx_on(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;

	at86rf230_async_state_change(lp, ctx, STATE_TX_ARET_ON,
				     at86rf230_ग_लिखो_frame);
पूर्ण

अटल व्योम
at86rf230_xmit_start(व्योम *context)
अणु
	काष्ठा at86rf230_state_change *ctx = context;
	काष्ठा at86rf230_local *lp = ctx->lp;

	/* check अगर we change from off state */
	अगर (lp->is_tx_from_off)
		at86rf230_async_state_change(lp, ctx, STATE_TX_ARET_ON,
					     at86rf230_ग_लिखो_frame);
	अन्यथा
		at86rf230_async_state_change(lp, ctx, STATE_TX_ON,
					     at86rf230_xmit_tx_on);
पूर्ण

अटल पूर्णांक
at86rf230_xmit(काष्ठा ieee802154_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा at86rf230_local *lp = hw->priv;
	काष्ठा at86rf230_state_change *ctx = &lp->tx;

	lp->tx_skb = skb;
	lp->tx_retry = 0;

	/* After 5 minutes in PLL and the same frequency we run again the
	 * calibration loops which is recommended by at86rf2xx datasheets.
	 *
	 * The calibration is initiate by a state change from TRX_OFF
	 * to TX_ON, the lp->cal_समयout should be reinit by state_delay
	 * function then to start in the next 5 minutes.
	 */
	अगर (समय_is_beक्रमe_jअगरfies(lp->cal_समयout)) अणु
		lp->is_tx_from_off = true;
		at86rf230_async_state_change(lp, ctx, STATE_TRX_OFF,
					     at86rf230_xmit_start);
	पूर्ण अन्यथा अणु
		lp->is_tx_from_off = false;
		at86rf230_xmit_start(ctx);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
at86rf230_ed(काष्ठा ieee802154_hw *hw, u8 *level)
अणु
	WARN_ON(!level);
	*level = 0xbe;
	वापस 0;
पूर्ण

अटल पूर्णांक
at86rf230_start(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा at86rf230_local *lp = hw->priv;

	/* reset trac stats on start */
	अगर (IS_ENABLED(CONFIG_IEEE802154_AT86RF230_DEBUGFS))
		स_रखो(&lp->trac, 0, माप(काष्ठा at86rf230_trac));

	at86rf230_awake(lp);
	enable_irq(lp->spi->irq);

	वापस at86rf230_sync_state_change(lp, STATE_RX_AACK_ON);
पूर्ण

अटल व्योम
at86rf230_stop(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा at86rf230_local *lp = hw->priv;
	u8 csma_seed[2];

	at86rf230_sync_state_change(lp, STATE_FORCE_TRX_OFF);

	disable_irq(lp->spi->irq);

	/* It's recommended to set अक्रमom new csma_seeds beक्रमe sleep state.
	 * Makes only sense in the stop callback, not करोing this inside of
	 * at86rf230_sleep, this is also used when we करोn't transmit afterwards
	 * when calling start callback again.
	 */
	get_अक्रमom_bytes(csma_seed, ARRAY_SIZE(csma_seed));
	at86rf230_ग_लिखो_subreg(lp, SR_CSMA_SEED_0, csma_seed[0]);
	at86rf230_ग_लिखो_subreg(lp, SR_CSMA_SEED_1, csma_seed[1]);

	at86rf230_sleep(lp);
पूर्ण

अटल पूर्णांक
at86rf23x_set_channel(काष्ठा at86rf230_local *lp, u8 page, u8 channel)
अणु
	वापस at86rf230_ग_लिखो_subreg(lp, SR_CHANNEL, channel);
पूर्ण

#घोषणा AT86RF2XX_MAX_ED_LEVELS 0xF
अटल स्थिर s32 at86rf233_ed_levels[AT86RF2XX_MAX_ED_LEVELS + 1] = अणु
	-9400, -9200, -9000, -8800, -8600, -8400, -8200, -8000, -7800, -7600,
	-7400, -7200, -7000, -6800, -6600, -6400,
पूर्ण;

अटल स्थिर s32 at86rf231_ed_levels[AT86RF2XX_MAX_ED_LEVELS + 1] = अणु
	-9100, -8900, -8700, -8500, -8300, -8100, -7900, -7700, -7500, -7300,
	-7100, -6900, -6700, -6500, -6300, -6100,
पूर्ण;

अटल स्थिर s32 at86rf212_ed_levels_100[AT86RF2XX_MAX_ED_LEVELS + 1] = अणु
	-10000, -9800, -9600, -9400, -9200, -9000, -8800, -8600, -8400, -8200,
	-8000, -7800, -7600, -7400, -7200, -7000,
पूर्ण;

अटल स्थिर s32 at86rf212_ed_levels_98[AT86RF2XX_MAX_ED_LEVELS + 1] = अणु
	-9800, -9600, -9400, -9200, -9000, -8800, -8600, -8400, -8200, -8000,
	-7800, -7600, -7400, -7200, -7000, -6800,
पूर्ण;

अटल अंतरभूत पूर्णांक
at86rf212_update_cca_ed_level(काष्ठा at86rf230_local *lp, पूर्णांक rssi_base_val)
अणु
	अचिन्हित पूर्णांक cca_ed_thres;
	पूर्णांक rc;

	rc = at86rf230_पढ़ो_subreg(lp, SR_CCA_ED_THRES, &cca_ed_thres);
	अगर (rc < 0)
		वापस rc;

	चयन (rssi_base_val) अणु
	हाल -98:
		lp->hw->phy->supported.cca_ed_levels = at86rf212_ed_levels_98;
		lp->hw->phy->supported.cca_ed_levels_size = ARRAY_SIZE(at86rf212_ed_levels_98);
		lp->hw->phy->cca_ed_level = at86rf212_ed_levels_98[cca_ed_thres];
		अवरोध;
	हाल -100:
		lp->hw->phy->supported.cca_ed_levels = at86rf212_ed_levels_100;
		lp->hw->phy->supported.cca_ed_levels_size = ARRAY_SIZE(at86rf212_ed_levels_100);
		lp->hw->phy->cca_ed_level = at86rf212_ed_levels_100[cca_ed_thres];
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
at86rf212_set_channel(काष्ठा at86rf230_local *lp, u8 page, u8 channel)
अणु
	पूर्णांक rc;

	अगर (channel == 0)
		rc = at86rf230_ग_लिखो_subreg(lp, SR_SUB_MODE, 0);
	अन्यथा
		rc = at86rf230_ग_लिखो_subreg(lp, SR_SUB_MODE, 1);
	अगर (rc < 0)
		वापस rc;

	अगर (page == 0) अणु
		rc = at86rf230_ग_लिखो_subreg(lp, SR_BPSK_QPSK, 0);
		lp->data->rssi_base_val = -100;
	पूर्ण अन्यथा अणु
		rc = at86rf230_ग_लिखो_subreg(lp, SR_BPSK_QPSK, 1);
		lp->data->rssi_base_val = -98;
	पूर्ण
	अगर (rc < 0)
		वापस rc;

	rc = at86rf212_update_cca_ed_level(lp, lp->data->rssi_base_val);
	अगर (rc < 0)
		वापस rc;

	/* This sets the symbol_duration according frequency on the 212.
	 * TODO move this handling जबतक set channel and page in cfg802154.
	 * We can करो that, this timings are according 802.15.4 standard.
	 * If we करो that in cfg802154, this is a more generic calculation.
	 *
	 * This should also रक्षित from अगरs_समयr. Means cancel समयr and
	 * init with a new value. For now, this is okay.
	 */
	अगर (channel == 0) अणु
		अगर (page == 0) अणु
			/* SUB:0 and BPSK:0 -> BPSK-20 */
			lp->hw->phy->symbol_duration = 50;
		पूर्ण अन्यथा अणु
			/* SUB:1 and BPSK:0 -> BPSK-40 */
			lp->hw->phy->symbol_duration = 25;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (page == 0)
			/* SUB:0 and BPSK:1 -> OQPSK-100/200/400 */
			lp->hw->phy->symbol_duration = 40;
		अन्यथा
			/* SUB:1 and BPSK:1 -> OQPSK-250/500/1000 */
			lp->hw->phy->symbol_duration = 16;
	पूर्ण

	lp->hw->phy->lअगरs_period = IEEE802154_LIFS_PERIOD *
				   lp->hw->phy->symbol_duration;
	lp->hw->phy->sअगरs_period = IEEE802154_SIFS_PERIOD *
				   lp->hw->phy->symbol_duration;

	वापस at86rf230_ग_लिखो_subreg(lp, SR_CHANNEL, channel);
पूर्ण

अटल पूर्णांक
at86rf230_channel(काष्ठा ieee802154_hw *hw, u8 page, u8 channel)
अणु
	काष्ठा at86rf230_local *lp = hw->priv;
	पूर्णांक rc;

	rc = lp->data->set_channel(lp, page, channel);
	/* Wait क्रम PLL */
	usleep_range(lp->data->t_channel_चयन,
		     lp->data->t_channel_चयन + 10);

	lp->cal_समयout = jअगरfies + AT86RF2XX_CAL_LOOP_TIMEOUT;
	वापस rc;
पूर्ण

अटल पूर्णांक
at86rf230_set_hw_addr_filt(काष्ठा ieee802154_hw *hw,
			   काष्ठा ieee802154_hw_addr_filt *filt,
			   अचिन्हित दीर्घ changed)
अणु
	काष्ठा at86rf230_local *lp = hw->priv;

	अगर (changed & IEEE802154_AFILT_SADDR_CHANGED) अणु
		u16 addr = le16_to_cpu(filt->लघु_addr);

		dev_vdbg(&lp->spi->dev, "%s called for saddr\n", __func__);
		__at86rf230_ग_लिखो(lp, RG_SHORT_ADDR_0, addr);
		__at86rf230_ग_लिखो(lp, RG_SHORT_ADDR_1, addr >> 8);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_PANID_CHANGED) अणु
		u16 pan = le16_to_cpu(filt->pan_id);

		dev_vdbg(&lp->spi->dev, "%s called for pan id\n", __func__);
		__at86rf230_ग_लिखो(lp, RG_PAN_ID_0, pan);
		__at86rf230_ग_लिखो(lp, RG_PAN_ID_1, pan >> 8);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_IEEEADDR_CHANGED) अणु
		u8 i, addr[8];

		स_नकल(addr, &filt->ieee_addr, 8);
		dev_vdbg(&lp->spi->dev, "%s called for IEEE addr\n", __func__);
		क्रम (i = 0; i < 8; i++)
			__at86rf230_ग_लिखो(lp, RG_IEEE_ADDR_0 + i, addr[i]);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_PANC_CHANGED) अणु
		dev_vdbg(&lp->spi->dev, "%s called for panc change\n", __func__);
		अगर (filt->pan_coord)
			at86rf230_ग_लिखो_subreg(lp, SR_AACK_I_AM_COORD, 1);
		अन्यथा
			at86rf230_ग_लिखो_subreg(lp, SR_AACK_I_AM_COORD, 0);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा AT86RF23X_MAX_TX_POWERS 0xF
अटल स्थिर s32 at86rf233_घातers[AT86RF23X_MAX_TX_POWERS + 1] = अणु
	400, 370, 340, 300, 250, 200, 100, 0, -100, -200, -300, -400, -600,
	-800, -1200, -1700,
पूर्ण;

अटल स्थिर s32 at86rf231_घातers[AT86RF23X_MAX_TX_POWERS + 1] = अणु
	300, 280, 230, 180, 130, 70, 0, -100, -200, -300, -400, -500, -700,
	-900, -1200, -1700,
पूर्ण;

#घोषणा AT86RF212_MAX_TX_POWERS 0x1F
अटल स्थिर s32 at86rf212_घातers[AT86RF212_MAX_TX_POWERS + 1] = अणु
	500, 400, 300, 200, 100, 0, -100, -200, -300, -400, -500, -600, -700,
	-800, -900, -1000, -1100, -1200, -1300, -1400, -1500, -1600, -1700,
	-1800, -1900, -2000, -2100, -2200, -2300, -2400, -2500, -2600,
पूर्ण;

अटल पूर्णांक
at86rf23x_set_txघातer(काष्ठा at86rf230_local *lp, s32 mbm)
अणु
	u32 i;

	क्रम (i = 0; i < lp->hw->phy->supported.tx_घातers_size; i++) अणु
		अगर (lp->hw->phy->supported.tx_घातers[i] == mbm)
			वापस at86rf230_ग_लिखो_subreg(lp, SR_TX_PWR_23X, i);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
at86rf212_set_txघातer(काष्ठा at86rf230_local *lp, s32 mbm)
अणु
	u32 i;

	क्रम (i = 0; i < lp->hw->phy->supported.tx_घातers_size; i++) अणु
		अगर (lp->hw->phy->supported.tx_घातers[i] == mbm)
			वापस at86rf230_ग_लिखो_subreg(lp, SR_TX_PWR_212, i);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
at86rf230_set_txघातer(काष्ठा ieee802154_hw *hw, s32 mbm)
अणु
	काष्ठा at86rf230_local *lp = hw->priv;

	वापस lp->data->set_txघातer(lp, mbm);
पूर्ण

अटल पूर्णांक
at86rf230_set_lbt(काष्ठा ieee802154_hw *hw, bool on)
अणु
	काष्ठा at86rf230_local *lp = hw->priv;

	वापस at86rf230_ग_लिखो_subreg(lp, SR_CSMA_LBT_MODE, on);
पूर्ण

अटल पूर्णांक
at86rf230_set_cca_mode(काष्ठा ieee802154_hw *hw,
		       स्थिर काष्ठा wpan_phy_cca *cca)
अणु
	काष्ठा at86rf230_local *lp = hw->priv;
	u8 val;

	/* mapping 802.15.4 to driver spec */
	चयन (cca->mode) अणु
	हाल NL802154_CCA_ENERGY:
		val = 1;
		अवरोध;
	हाल NL802154_CCA_CARRIER:
		val = 2;
		अवरोध;
	हाल NL802154_CCA_ENERGY_CARRIER:
		चयन (cca->opt) अणु
		हाल NL802154_CCA_OPT_ENERGY_CARRIER_AND:
			val = 3;
			अवरोध;
		हाल NL802154_CCA_OPT_ENERGY_CARRIER_OR:
			val = 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस at86rf230_ग_लिखो_subreg(lp, SR_CCA_MODE, val);
पूर्ण

अटल पूर्णांक
at86rf230_set_cca_ed_level(काष्ठा ieee802154_hw *hw, s32 mbm)
अणु
	काष्ठा at86rf230_local *lp = hw->priv;
	u32 i;

	क्रम (i = 0; i < hw->phy->supported.cca_ed_levels_size; i++) अणु
		अगर (hw->phy->supported.cca_ed_levels[i] == mbm)
			वापस at86rf230_ग_लिखो_subreg(lp, SR_CCA_ED_THRES, i);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
at86rf230_set_csma_params(काष्ठा ieee802154_hw *hw, u8 min_be, u8 max_be,
			  u8 retries)
अणु
	काष्ठा at86rf230_local *lp = hw->priv;
	पूर्णांक rc;

	rc = at86rf230_ग_लिखो_subreg(lp, SR_MIN_BE, min_be);
	अगर (rc)
		वापस rc;

	rc = at86rf230_ग_लिखो_subreg(lp, SR_MAX_BE, max_be);
	अगर (rc)
		वापस rc;

	वापस at86rf230_ग_लिखो_subreg(lp, SR_MAX_CSMA_RETRIES, retries);
पूर्ण

अटल पूर्णांक
at86rf230_set_frame_retries(काष्ठा ieee802154_hw *hw, s8 retries)
अणु
	काष्ठा at86rf230_local *lp = hw->priv;

	वापस at86rf230_ग_लिखो_subreg(lp, SR_MAX_FRAME_RETRIES, retries);
पूर्ण

अटल पूर्णांक
at86rf230_set_promiscuous_mode(काष्ठा ieee802154_hw *hw, स्थिर bool on)
अणु
	काष्ठा at86rf230_local *lp = hw->priv;
	पूर्णांक rc;

	अगर (on) अणु
		rc = at86rf230_ग_लिखो_subreg(lp, SR_AACK_DIS_ACK, 1);
		अगर (rc < 0)
			वापस rc;

		rc = at86rf230_ग_लिखो_subreg(lp, SR_AACK_PROM_MODE, 1);
		अगर (rc < 0)
			वापस rc;
	पूर्ण अन्यथा अणु
		rc = at86rf230_ग_लिखो_subreg(lp, SR_AACK_PROM_MODE, 0);
		अगर (rc < 0)
			वापस rc;

		rc = at86rf230_ग_लिखो_subreg(lp, SR_AACK_DIS_ACK, 0);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee802154_ops at86rf230_ops = अणु
	.owner = THIS_MODULE,
	.xmit_async = at86rf230_xmit,
	.ed = at86rf230_ed,
	.set_channel = at86rf230_channel,
	.start = at86rf230_start,
	.stop = at86rf230_stop,
	.set_hw_addr_filt = at86rf230_set_hw_addr_filt,
	.set_txघातer = at86rf230_set_txघातer,
	.set_lbt = at86rf230_set_lbt,
	.set_cca_mode = at86rf230_set_cca_mode,
	.set_cca_ed_level = at86rf230_set_cca_ed_level,
	.set_csma_params = at86rf230_set_csma_params,
	.set_frame_retries = at86rf230_set_frame_retries,
	.set_promiscuous_mode = at86rf230_set_promiscuous_mode,
पूर्ण;

अटल काष्ठा at86rf2xx_chip_data at86rf233_data = अणु
	.t_sleep_cycle = 330,
	.t_channel_चयन = 11,
	.t_reset_to_off = 26,
	.t_off_to_aack = 80,
	.t_off_to_tx_on = 80,
	.t_off_to_sleep = 35,
	.t_sleep_to_off = 1000,
	.t_frame = 4096,
	.t_p_ack = 545,
	.rssi_base_val = -94,
	.set_channel = at86rf23x_set_channel,
	.set_txघातer = at86rf23x_set_txघातer,
पूर्ण;

अटल काष्ठा at86rf2xx_chip_data at86rf231_data = अणु
	.t_sleep_cycle = 330,
	.t_channel_चयन = 24,
	.t_reset_to_off = 37,
	.t_off_to_aack = 110,
	.t_off_to_tx_on = 110,
	.t_off_to_sleep = 35,
	.t_sleep_to_off = 1000,
	.t_frame = 4096,
	.t_p_ack = 545,
	.rssi_base_val = -91,
	.set_channel = at86rf23x_set_channel,
	.set_txघातer = at86rf23x_set_txघातer,
पूर्ण;

अटल काष्ठा at86rf2xx_chip_data at86rf212_data = अणु
	.t_sleep_cycle = 330,
	.t_channel_चयन = 11,
	.t_reset_to_off = 26,
	.t_off_to_aack = 200,
	.t_off_to_tx_on = 200,
	.t_off_to_sleep = 35,
	.t_sleep_to_off = 1000,
	.t_frame = 4096,
	.t_p_ack = 545,
	.rssi_base_val = -100,
	.set_channel = at86rf212_set_channel,
	.set_txघातer = at86rf212_set_txघातer,
पूर्ण;

अटल पूर्णांक at86rf230_hw_init(काष्ठा at86rf230_local *lp, u8 xtal_trim)
अणु
	पूर्णांक rc, irq_type, irq_pol = IRQ_ACTIVE_HIGH;
	अचिन्हित पूर्णांक dvdd;
	u8 csma_seed[2];

	rc = at86rf230_sync_state_change(lp, STATE_FORCE_TRX_OFF);
	अगर (rc)
		वापस rc;

	irq_type = irq_get_trigger_type(lp->spi->irq);
	अगर (irq_type == IRQ_TYPE_EDGE_FALLING ||
	    irq_type == IRQ_TYPE_LEVEL_LOW)
		irq_pol = IRQ_ACTIVE_LOW;

	rc = at86rf230_ग_लिखो_subreg(lp, SR_IRQ_POLARITY, irq_pol);
	अगर (rc)
		वापस rc;

	rc = at86rf230_ग_लिखो_subreg(lp, SR_RX_SAFE_MODE, 1);
	अगर (rc)
		वापस rc;

	rc = at86rf230_ग_लिखो_subreg(lp, SR_IRQ_MASK, IRQ_TRX_END);
	अगर (rc)
		वापस rc;

	/* reset values dअगरfers in at86rf231 and at86rf233 */
	rc = at86rf230_ग_लिखो_subreg(lp, SR_IRQ_MASK_MODE, 0);
	अगर (rc)
		वापस rc;

	get_अक्रमom_bytes(csma_seed, ARRAY_SIZE(csma_seed));
	rc = at86rf230_ग_लिखो_subreg(lp, SR_CSMA_SEED_0, csma_seed[0]);
	अगर (rc)
		वापस rc;
	rc = at86rf230_ग_लिखो_subreg(lp, SR_CSMA_SEED_1, csma_seed[1]);
	अगर (rc)
		वापस rc;

	/* CLKM changes are applied immediately */
	rc = at86rf230_ग_लिखो_subreg(lp, SR_CLKM_SHA_SEL, 0x00);
	अगर (rc)
		वापस rc;

	/* Turn CLKM Off */
	rc = at86rf230_ग_लिखो_subreg(lp, SR_CLKM_CTRL, 0x00);
	अगर (rc)
		वापस rc;
	/* Wait the next SLEEP cycle */
	usleep_range(lp->data->t_sleep_cycle,
		     lp->data->t_sleep_cycle + 100);

	/* xtal_trim value is calculated by:
	 * CL = 0.5 * (CX + CTRIM + CPAR)
	 *
	 * whereas:
	 * CL = capacitor of used crystal
	 * CX = connected capacitors at xtal pins
	 * CPAR = in all at86rf2xx datasheets this is a स्थिरant value 3 pF,
	 *	  but this is dअगरferent on each board setup. You need to fine
	 *	  tuning this value via CTRIM.
	 * CTRIM = variable capacitor setting. Resolution is 0.3 pF range is
	 *	   0 pF upto 4.5 pF.
	 *
	 * Examples:
	 * atben transceiver:
	 *
	 * CL = 8 pF
	 * CX = 12 pF
	 * CPAR = 3 pF (We assume the magic स्थिरant from datasheet)
	 * CTRIM = 0.9 pF
	 *
	 * (12+0.9+3)/2 = 7.95 which is nearly at 8 pF
	 *
	 * xtal_trim = 0x3
	 *
	 * खोलोद_असल transceiver:
	 *
	 * CL = 16 pF
	 * CX = 22 pF
	 * CPAR = 3 pF (We assume the magic स्थिरant from datasheet)
	 * CTRIM = 4.5 pF
	 *
	 * (22+4.5+3)/2 = 14.75 which is the nearest value to 16 pF
	 *
	 * xtal_trim = 0xf
	 */
	rc = at86rf230_ग_लिखो_subreg(lp, SR_XTAL_TRIM, xtal_trim);
	अगर (rc)
		वापस rc;

	rc = at86rf230_पढ़ो_subreg(lp, SR_DVDD_OK, &dvdd);
	अगर (rc)
		वापस rc;
	अगर (!dvdd) अणु
		dev_err(&lp->spi->dev, "DVDD error\n");
		वापस -EINVAL;
	पूर्ण

	/* Force setting slotted operation bit to 0. Someबार the atben
	 * sets this bit and I करोn't know why. We set this always क्रमce
	 * to zero जबतक probing.
	 */
	वापस at86rf230_ग_लिखो_subreg(lp, SR_SLOTTED_OPERATION, 0);
पूर्ण

अटल पूर्णांक
at86rf230_get_pdata(काष्ठा spi_device *spi, पूर्णांक *rstn, पूर्णांक *slp_tr,
		    u8 *xtal_trim)
अणु
	काष्ठा at86rf230_platक्रमm_data *pdata = spi->dev.platक्रमm_data;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_OF) || !spi->dev.of_node) अणु
		अगर (!pdata)
			वापस -ENOENT;

		*rstn = pdata->rstn;
		*slp_tr = pdata->slp_tr;
		*xtal_trim = pdata->xtal_trim;
		वापस 0;
	पूर्ण

	*rstn = of_get_named_gpio(spi->dev.of_node, "reset-gpio", 0);
	*slp_tr = of_get_named_gpio(spi->dev.of_node, "sleep-gpio", 0);
	ret = of_property_पढ़ो_u8(spi->dev.of_node, "xtal-trim", xtal_trim);
	अगर (ret < 0 && ret != -EINVAL)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक
at86rf230_detect_device(काष्ठा at86rf230_local *lp)
अणु
	अचिन्हित पूर्णांक part, version, val;
	u16 man_id = 0;
	स्थिर अक्षर *chip;
	पूर्णांक rc;

	rc = __at86rf230_पढ़ो(lp, RG_MAN_ID_0, &val);
	अगर (rc)
		वापस rc;
	man_id |= val;

	rc = __at86rf230_पढ़ो(lp, RG_MAN_ID_1, &val);
	अगर (rc)
		वापस rc;
	man_id |= (val << 8);

	rc = __at86rf230_पढ़ो(lp, RG_PART_NUM, &part);
	अगर (rc)
		वापस rc;

	rc = __at86rf230_पढ़ो(lp, RG_VERSION_NUM, &version);
	अगर (rc)
		वापस rc;

	अगर (man_id != 0x001f) अणु
		dev_err(&lp->spi->dev, "Non-Atmel dev found (MAN_ID %02x %02x)\n",
			man_id >> 8, man_id & 0xFF);
		वापस -EINVAL;
	पूर्ण

	lp->hw->flags = IEEE802154_HW_TX_OMIT_CKSUM |
			IEEE802154_HW_CSMA_PARAMS |
			IEEE802154_HW_FRAME_RETRIES | IEEE802154_HW_AFILT |
			IEEE802154_HW_PROMISCUOUS;

	lp->hw->phy->flags = WPAN_PHY_FLAG_TXPOWER |
			     WPAN_PHY_FLAG_CCA_ED_LEVEL |
			     WPAN_PHY_FLAG_CCA_MODE;

	lp->hw->phy->supported.cca_modes = BIT(NL802154_CCA_ENERGY) |
		BIT(NL802154_CCA_CARRIER) | BIT(NL802154_CCA_ENERGY_CARRIER);
	lp->hw->phy->supported.cca_opts = BIT(NL802154_CCA_OPT_ENERGY_CARRIER_AND) |
		BIT(NL802154_CCA_OPT_ENERGY_CARRIER_OR);

	lp->hw->phy->cca.mode = NL802154_CCA_ENERGY;

	चयन (part) अणु
	हाल 2:
		chip = "at86rf230";
		rc = -ENOTSUPP;
		जाओ not_supp;
	हाल 3:
		chip = "at86rf231";
		lp->data = &at86rf231_data;
		lp->hw->phy->supported.channels[0] = 0x7FFF800;
		lp->hw->phy->current_channel = 11;
		lp->hw->phy->symbol_duration = 16;
		lp->hw->phy->supported.tx_घातers = at86rf231_घातers;
		lp->hw->phy->supported.tx_घातers_size = ARRAY_SIZE(at86rf231_घातers);
		lp->hw->phy->supported.cca_ed_levels = at86rf231_ed_levels;
		lp->hw->phy->supported.cca_ed_levels_size = ARRAY_SIZE(at86rf231_ed_levels);
		अवरोध;
	हाल 7:
		chip = "at86rf212";
		lp->data = &at86rf212_data;
		lp->hw->flags |= IEEE802154_HW_LBT;
		lp->hw->phy->supported.channels[0] = 0x00007FF;
		lp->hw->phy->supported.channels[2] = 0x00007FF;
		lp->hw->phy->current_channel = 5;
		lp->hw->phy->symbol_duration = 25;
		lp->hw->phy->supported.lbt = NL802154_SUPPORTED_BOOL_BOTH;
		lp->hw->phy->supported.tx_घातers = at86rf212_घातers;
		lp->hw->phy->supported.tx_घातers_size = ARRAY_SIZE(at86rf212_घातers);
		lp->hw->phy->supported.cca_ed_levels = at86rf212_ed_levels_100;
		lp->hw->phy->supported.cca_ed_levels_size = ARRAY_SIZE(at86rf212_ed_levels_100);
		अवरोध;
	हाल 11:
		chip = "at86rf233";
		lp->data = &at86rf233_data;
		lp->hw->phy->supported.channels[0] = 0x7FFF800;
		lp->hw->phy->current_channel = 13;
		lp->hw->phy->symbol_duration = 16;
		lp->hw->phy->supported.tx_घातers = at86rf233_घातers;
		lp->hw->phy->supported.tx_घातers_size = ARRAY_SIZE(at86rf233_घातers);
		lp->hw->phy->supported.cca_ed_levels = at86rf233_ed_levels;
		lp->hw->phy->supported.cca_ed_levels_size = ARRAY_SIZE(at86rf233_ed_levels);
		अवरोध;
	शेष:
		chip = "unknown";
		rc = -ENOTSUPP;
		जाओ not_supp;
	पूर्ण

	lp->hw->phy->cca_ed_level = lp->hw->phy->supported.cca_ed_levels[7];
	lp->hw->phy->transmit_घातer = lp->hw->phy->supported.tx_घातers[0];

not_supp:
	dev_info(&lp->spi->dev, "Detected %s chip version %d\n", chip, version);

	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_IEEE802154_AT86RF230_DEBUGFS
अटल काष्ठा dentry *at86rf230_debugfs_root;

अटल पूर्णांक at86rf230_stats_show(काष्ठा seq_file *file, व्योम *offset)
अणु
	काष्ठा at86rf230_local *lp = file->निजी;

	seq_म_लिखो(file, "SUCCESS:\t\t%8llu\n", lp->trac.success);
	seq_म_लिखो(file, "SUCCESS_DATA_PENDING:\t%8llu\n",
		   lp->trac.success_data_pending);
	seq_म_लिखो(file, "SUCCESS_WAIT_FOR_ACK:\t%8llu\n",
		   lp->trac.success_रुको_क्रम_ack);
	seq_म_लिखो(file, "CHANNEL_ACCESS_FAILURE:\t%8llu\n",
		   lp->trac.channel_access_failure);
	seq_म_लिखो(file, "NO_ACK:\t\t\t%8llu\n", lp->trac.no_ack);
	seq_म_लिखो(file, "INVALID:\t\t%8llu\n", lp->trac.invalid);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(at86rf230_stats);

अटल व्योम at86rf230_debugfs_init(काष्ठा at86rf230_local *lp)
अणु
	अक्षर debugfs_dir_name[DNAME_INLINE_LEN + 1] = "at86rf230-";

	म_जोड़न(debugfs_dir_name, dev_name(&lp->spi->dev), DNAME_INLINE_LEN);

	at86rf230_debugfs_root = debugfs_create_dir(debugfs_dir_name, शून्य);

	debugfs_create_file("trac_stats", 0444, at86rf230_debugfs_root, lp,
			    &at86rf230_stats_fops);
पूर्ण

अटल व्योम at86rf230_debugfs_हटाओ(व्योम)
अणु
	debugfs_हटाओ_recursive(at86rf230_debugfs_root);
पूर्ण
#अन्यथा
अटल व्योम at86rf230_debugfs_init(काष्ठा at86rf230_local *lp) अणु पूर्ण
अटल व्योम at86rf230_debugfs_हटाओ(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक at86rf230_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ieee802154_hw *hw;
	काष्ठा at86rf230_local *lp;
	अचिन्हित पूर्णांक status;
	पूर्णांक rc, irq_type, rstn, slp_tr;
	u8 xtal_trim = 0;

	अगर (!spi->irq) अणु
		dev_err(&spi->dev, "no IRQ specified\n");
		वापस -EINVAL;
	पूर्ण

	rc = at86rf230_get_pdata(spi, &rstn, &slp_tr, &xtal_trim);
	अगर (rc < 0) अणु
		dev_err(&spi->dev, "failed to parse platform_data: %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (gpio_is_valid(rstn)) अणु
		rc = devm_gpio_request_one(&spi->dev, rstn,
					   GPIOF_OUT_INIT_HIGH, "rstn");
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (gpio_is_valid(slp_tr)) अणु
		rc = devm_gpio_request_one(&spi->dev, slp_tr,
					   GPIOF_OUT_INIT_LOW, "slp_tr");
		अगर (rc)
			वापस rc;
	पूर्ण

	/* Reset */
	अगर (gpio_is_valid(rstn)) अणु
		udelay(1);
		gpio_set_value_cansleep(rstn, 0);
		udelay(1);
		gpio_set_value_cansleep(rstn, 1);
		usleep_range(120, 240);
	पूर्ण

	hw = ieee802154_alloc_hw(माप(*lp), &at86rf230_ops);
	अगर (!hw)
		वापस -ENOMEM;

	lp = hw->priv;
	lp->hw = hw;
	lp->spi = spi;
	lp->slp_tr = slp_tr;
	hw->parent = &spi->dev;
	ieee802154_अक्रमom_extended_addr(&hw->phy->perm_extended_addr);

	lp->regmap = devm_regmap_init_spi(spi, &at86rf230_regmap_spi_config);
	अगर (IS_ERR(lp->regmap)) अणु
		rc = PTR_ERR(lp->regmap);
		dev_err(&spi->dev, "Failed to allocate register map: %d\n",
			rc);
		जाओ मुक्त_dev;
	पूर्ण

	at86rf230_setup_spi_messages(lp, &lp->state);
	at86rf230_setup_spi_messages(lp, &lp->tx);

	rc = at86rf230_detect_device(lp);
	अगर (rc < 0)
		जाओ मुक्त_dev;

	init_completion(&lp->state_complete);

	spi_set_drvdata(spi, lp);

	rc = at86rf230_hw_init(lp, xtal_trim);
	अगर (rc)
		जाओ मुक्त_dev;

	/* Read irq status रेजिस्टर to reset irq line */
	rc = at86rf230_पढ़ो_subreg(lp, RG_IRQ_STATUS, 0xff, 0, &status);
	अगर (rc)
		जाओ मुक्त_dev;

	irq_type = irq_get_trigger_type(spi->irq);
	अगर (!irq_type)
		irq_type = IRQF_TRIGGER_HIGH;

	rc = devm_request_irq(&spi->dev, spi->irq, at86rf230_isr,
			      IRQF_SHARED | irq_type, dev_name(&spi->dev), lp);
	अगर (rc)
		जाओ मुक्त_dev;

	/* disable_irq by शेष and रुको क्रम starting hardware */
	disable_irq(spi->irq);

	/* going पूर्णांकo sleep by शेष */
	at86rf230_sleep(lp);

	at86rf230_debugfs_init(lp);

	rc = ieee802154_रेजिस्टर_hw(lp->hw);
	अगर (rc)
		जाओ मुक्त_debugfs;

	वापस rc;

मुक्त_debugfs:
	at86rf230_debugfs_हटाओ();
मुक्त_dev:
	ieee802154_मुक्त_hw(lp->hw);

	वापस rc;
पूर्ण

अटल पूर्णांक at86rf230_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा at86rf230_local *lp = spi_get_drvdata(spi);

	/* mask all at86rf230 irq's */
	at86rf230_ग_लिखो_subreg(lp, SR_IRQ_MASK, 0);
	ieee802154_unरेजिस्टर_hw(lp->hw);
	ieee802154_मुक्त_hw(lp->hw);
	at86rf230_debugfs_हटाओ();
	dev_dbg(&spi->dev, "unregistered at86rf230\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id at86rf230_of_match[] = अणु
	अणु .compatible = "atmel,at86rf230", पूर्ण,
	अणु .compatible = "atmel,at86rf231", पूर्ण,
	अणु .compatible = "atmel,at86rf233", पूर्ण,
	अणु .compatible = "atmel,at86rf212", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, at86rf230_of_match);

अटल स्थिर काष्ठा spi_device_id at86rf230_device_id[] = अणु
	अणु .name = "at86rf230", पूर्ण,
	अणु .name = "at86rf231", पूर्ण,
	अणु .name = "at86rf233", पूर्ण,
	अणु .name = "at86rf212", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, at86rf230_device_id);

अटल काष्ठा spi_driver at86rf230_driver = अणु
	.id_table = at86rf230_device_id,
	.driver = अणु
		.of_match_table = of_match_ptr(at86rf230_of_match),
		.name	= "at86rf230",
	पूर्ण,
	.probe      = at86rf230_probe,
	.हटाओ     = at86rf230_हटाओ,
पूर्ण;

module_spi_driver(at86rf230_driver);

MODULE_DESCRIPTION("AT86RF230 Transceiver Driver");
MODULE_LICENSE("GPL v2");
