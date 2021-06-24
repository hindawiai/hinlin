<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Synopsys DesignWare I2C adapter driver (master only).
 *
 * Based on the TI DAVINCI I2C adapter driver.
 *
 * Copyright (C) 2006 Texas Instruments.
 * Copyright (C) 2007 MontaVista Software Inc.
 * Copyright (C) 2009 Provigent Ltd.
 */
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश "i2c-designware-core.h"

#घोषणा AMD_TIMEOUT_MIN_US	25
#घोषणा AMD_TIMEOUT_MAX_US	250
#घोषणा AMD_MASTERCFG_MASK	GENMASK(15, 0)

अटल व्योम i2c_dw_configure_fअगरo_master(काष्ठा dw_i2c_dev *dev)
अणु
	/* Configure Tx/Rx FIFO threshold levels */
	regmap_ग_लिखो(dev->map, DW_IC_TX_TL, dev->tx_fअगरo_depth / 2);
	regmap_ग_लिखो(dev->map, DW_IC_RX_TL, 0);

	/* Configure the I2C master */
	regmap_ग_लिखो(dev->map, DW_IC_CON, dev->master_cfg);
पूर्ण

अटल पूर्णांक i2c_dw_set_timings_master(काष्ठा dw_i2c_dev *dev)
अणु
	u32 comp_param1;
	u32 sda_falling_समय, scl_falling_समय;
	काष्ठा i2c_timings *t = &dev->timings;
	स्थिर अक्षर *fp_str = "";
	u32 ic_clk;
	पूर्णांक ret;

	ret = i2c_dw_acquire_lock(dev);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(dev->map, DW_IC_COMP_PARAM_1, &comp_param1);
	i2c_dw_release_lock(dev);
	अगर (ret)
		वापस ret;

	/* Set standard and fast speed भागiders क्रम high/low periods */
	sda_falling_समय = t->sda_fall_ns ?: 300; /* ns */
	scl_falling_समय = t->scl_fall_ns ?: 300; /* ns */

	/* Calculate SCL timing parameters क्रम standard mode अगर not set */
	अगर (!dev->ss_hcnt || !dev->ss_lcnt) अणु
		ic_clk = i2c_dw_clk_rate(dev);
		dev->ss_hcnt =
			i2c_dw_scl_hcnt(ic_clk,
					4000,	/* tHD;STA = tHIGH = 4.0 us */
					sda_falling_समय,
					0,	/* 0: DW शेष, 1: Ideal */
					0);	/* No offset */
		dev->ss_lcnt =
			i2c_dw_scl_lcnt(ic_clk,
					4700,	/* tLOW = 4.7 us */
					scl_falling_समय,
					0);	/* No offset */
	पूर्ण
	dev_dbg(dev->dev, "Standard Mode HCNT:LCNT = %d:%d\n",
		dev->ss_hcnt, dev->ss_lcnt);

	/*
	 * Set SCL timing parameters क्रम fast mode or fast mode plus. Only
	 * dअगरference is the timing parameter values since the रेजिस्टरs are
	 * the same.
	 */
	अगर (t->bus_freq_hz == I2C_MAX_FAST_MODE_PLUS_FREQ) अणु
		/*
		 * Check are Fast Mode Plus parameters available. Calculate
		 * SCL timing parameters क्रम Fast Mode Plus अगर not set.
		 */
		अगर (dev->fp_hcnt && dev->fp_lcnt) अणु
			dev->fs_hcnt = dev->fp_hcnt;
			dev->fs_lcnt = dev->fp_lcnt;
		पूर्ण अन्यथा अणु
			ic_clk = i2c_dw_clk_rate(dev);
			dev->fs_hcnt =
				i2c_dw_scl_hcnt(ic_clk,
						260,	/* tHIGH = 260 ns */
						sda_falling_समय,
						0,	/* DW शेष */
						0);	/* No offset */
			dev->fs_lcnt =
				i2c_dw_scl_lcnt(ic_clk,
						500,	/* tLOW = 500 ns */
						scl_falling_समय,
						0);	/* No offset */
		पूर्ण
		fp_str = " Plus";
	पूर्ण
	/*
	 * Calculate SCL timing parameters क्रम fast mode अगर not set. They are
	 * needed also in high speed mode.
	 */
	अगर (!dev->fs_hcnt || !dev->fs_lcnt) अणु
		ic_clk = i2c_dw_clk_rate(dev);
		dev->fs_hcnt =
			i2c_dw_scl_hcnt(ic_clk,
					600,	/* tHD;STA = tHIGH = 0.6 us */
					sda_falling_समय,
					0,	/* 0: DW शेष, 1: Ideal */
					0);	/* No offset */
		dev->fs_lcnt =
			i2c_dw_scl_lcnt(ic_clk,
					1300,	/* tLOW = 1.3 us */
					scl_falling_समय,
					0);	/* No offset */
	पूर्ण
	dev_dbg(dev->dev, "Fast Mode%s HCNT:LCNT = %d:%d\n",
		fp_str, dev->fs_hcnt, dev->fs_lcnt);

	/* Check is high speed possible and fall back to fast mode अगर not */
	अगर ((dev->master_cfg & DW_IC_CON_SPEED_MASK) ==
		DW_IC_CON_SPEED_HIGH) अणु
		अगर ((comp_param1 & DW_IC_COMP_PARAM_1_SPEED_MODE_MASK)
			!= DW_IC_COMP_PARAM_1_SPEED_MODE_HIGH) अणु
			dev_err(dev->dev, "High Speed not supported!\n");
			t->bus_freq_hz = I2C_MAX_FAST_MODE_FREQ;
			dev->master_cfg &= ~DW_IC_CON_SPEED_MASK;
			dev->master_cfg |= DW_IC_CON_SPEED_FAST;
			dev->hs_hcnt = 0;
			dev->hs_lcnt = 0;
		पूर्ण अन्यथा अगर (!dev->hs_hcnt || !dev->hs_lcnt) अणु
			ic_clk = i2c_dw_clk_rate(dev);
			dev->hs_hcnt =
				i2c_dw_scl_hcnt(ic_clk,
						160,	/* tHIGH = 160 ns */
						sda_falling_समय,
						0,	/* DW शेष */
						0);	/* No offset */
			dev->hs_lcnt =
				i2c_dw_scl_lcnt(ic_clk,
						320,	/* tLOW = 320 ns */
						scl_falling_समय,
						0);	/* No offset */
		पूर्ण
		dev_dbg(dev->dev, "High Speed Mode HCNT:LCNT = %d:%d\n",
			dev->hs_hcnt, dev->hs_lcnt);
	पूर्ण

	ret = i2c_dw_set_sda_hold(dev);
	अगर (ret)
		वापस ret;

	dev_dbg(dev->dev, "Bus speed: %s\n", i2c_freq_mode_string(t->bus_freq_hz));
	वापस 0;
पूर्ण

/**
 * i2c_dw_init_master() - Initialize the designware I2C master hardware
 * @dev: device निजी data
 *
 * This functions configures and enables the I2C master.
 * This function is called during I2C init function, and in हाल of समयout at
 * run समय.
 */
अटल पूर्णांक i2c_dw_init_master(काष्ठा dw_i2c_dev *dev)
अणु
	पूर्णांक ret;

	ret = i2c_dw_acquire_lock(dev);
	अगर (ret)
		वापस ret;

	/* Disable the adapter */
	__i2c_dw_disable(dev);

	/* Write standard speed timing parameters */
	regmap_ग_लिखो(dev->map, DW_IC_SS_SCL_HCNT, dev->ss_hcnt);
	regmap_ग_लिखो(dev->map, DW_IC_SS_SCL_LCNT, dev->ss_lcnt);

	/* Write fast mode/fast mode plus timing parameters */
	regmap_ग_लिखो(dev->map, DW_IC_FS_SCL_HCNT, dev->fs_hcnt);
	regmap_ग_लिखो(dev->map, DW_IC_FS_SCL_LCNT, dev->fs_lcnt);

	/* Write high speed timing parameters अगर supported */
	अगर (dev->hs_hcnt && dev->hs_lcnt) अणु
		regmap_ग_लिखो(dev->map, DW_IC_HS_SCL_HCNT, dev->hs_hcnt);
		regmap_ग_लिखो(dev->map, DW_IC_HS_SCL_LCNT, dev->hs_lcnt);
	पूर्ण

	/* Write SDA hold समय अगर supported */
	अगर (dev->sda_hold_समय)
		regmap_ग_लिखो(dev->map, DW_IC_SDA_HOLD, dev->sda_hold_समय);

	i2c_dw_configure_fअगरo_master(dev);
	i2c_dw_release_lock(dev);

	वापस 0;
पूर्ण

अटल व्योम i2c_dw_xfer_init(काष्ठा dw_i2c_dev *dev)
अणु
	काष्ठा i2c_msg *msgs = dev->msgs;
	u32 ic_con = 0, ic_tar = 0;
	u32 dummy;

	/* Disable the adapter */
	__i2c_dw_disable(dev);

	/* If the slave address is ten bit address, enable 10BITADDR */
	अगर (msgs[dev->msg_ग_लिखो_idx].flags & I2C_M_TEN) अणु
		ic_con = DW_IC_CON_10BITADDR_MASTER;
		/*
		 * If I2C_DYNAMIC_TAR_UPDATE is set, the 10-bit addressing
		 * mode has to be enabled via bit 12 of IC_TAR रेजिस्टर.
		 * We set it always as I2C_DYNAMIC_TAR_UPDATE can't be
		 * detected from रेजिस्टरs.
		 */
		ic_tar = DW_IC_TAR_10BITADDR_MASTER;
	पूर्ण

	regmap_update_bits(dev->map, DW_IC_CON, DW_IC_CON_10BITADDR_MASTER,
			   ic_con);

	/*
	 * Set the slave (target) address and enable 10-bit addressing mode
	 * अगर applicable.
	 */
	regmap_ग_लिखो(dev->map, DW_IC_TAR,
		     msgs[dev->msg_ग_लिखो_idx].addr | ic_tar);

	/* Enक्रमce disabled पूर्णांकerrupts (due to HW issues) */
	i2c_dw_disable_पूर्णांक(dev);

	/* Enable the adapter */
	__i2c_dw_enable(dev);

	/* Dummy पढ़ो to aव्योम the रेजिस्टर getting stuck on Bay Trail */
	regmap_पढ़ो(dev->map, DW_IC_ENABLE_STATUS, &dummy);

	/* Clear and enable पूर्णांकerrupts */
	regmap_पढ़ो(dev->map, DW_IC_CLR_INTR, &dummy);
	regmap_ग_लिखो(dev->map, DW_IC_INTR_MASK, DW_IC_INTR_MASTER_MASK);
पूर्ण

अटल पूर्णांक i2c_dw_check_stopbit(काष्ठा dw_i2c_dev *dev)
अणु
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो_poll_समयout(dev->map, DW_IC_INTR_STAT, val,
				       !(val & DW_IC_INTR_STOP_DET),
					1100, 20000);
	अगर (ret)
		dev_err(dev->dev, "i2c timeout error %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_dw_status(काष्ठा dw_i2c_dev *dev)
अणु
	पूर्णांक status;

	status = i2c_dw_रुको_bus_not_busy(dev);
	अगर (status)
		वापस status;

	वापस i2c_dw_check_stopbit(dev);
पूर्ण

/*
 * Initiate and जारी master पढ़ो/ग_लिखो transaction with polling
 * based transfer routine afterward ग_लिखो messages पूर्णांकo the Tx buffer.
 */
अटल पूर्णांक amd_i2c_dw_xfer_quirk(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num_msgs)
अणु
	काष्ठा dw_i2c_dev *dev = i2c_get_adapdata(adap);
	पूर्णांक msg_wrt_idx, msg_itr_lmt, buf_len, data_idx;
	पूर्णांक cmd = 0, status;
	u8 *tx_buf;
	u32 val;

	/*
	 * In order to enable the पूर्णांकerrupt क्रम UCSI i.e. AMD NAVI GPU card,
	 * it is mandatory to set the right value in specअगरic रेजिस्टर
	 * (offset:0x474) as per the hardware IP specअगरication.
	 */
	regmap_ग_लिखो(dev->map, AMD_UCSI_INTR_REG, AMD_UCSI_INTR_EN);

	dev->msgs = msgs;
	dev->msgs_num = num_msgs;
	i2c_dw_xfer_init(dev);
	i2c_dw_disable_पूर्णांक(dev);

	/* Initiate messages पढ़ो/ग_लिखो transaction */
	क्रम (msg_wrt_idx = 0; msg_wrt_idx < num_msgs; msg_wrt_idx++) अणु
		tx_buf = msgs[msg_wrt_idx].buf;
		buf_len = msgs[msg_wrt_idx].len;

		अगर (!(msgs[msg_wrt_idx].flags & I2C_M_RD))
			regmap_ग_लिखो(dev->map, DW_IC_TX_TL, buf_len - 1);
		/*
		 * Initiate the i2c पढ़ो/ग_लिखो transaction of buffer length,
		 * and poll क्रम bus busy status. For the last message transfer,
		 * update the command with stopbit enable.
		 */
		क्रम (msg_itr_lmt = buf_len; msg_itr_lmt > 0; msg_itr_lmt--) अणु
			अगर (msg_wrt_idx == num_msgs - 1 && msg_itr_lmt == 1)
				cmd |= BIT(9);

			अगर (msgs[msg_wrt_idx].flags & I2C_M_RD) अणु
				/* Due to hardware bug, need to ग_लिखो the same command twice. */
				regmap_ग_लिखो(dev->map, DW_IC_DATA_CMD, 0x100);
				regmap_ग_लिखो(dev->map, DW_IC_DATA_CMD, 0x100 | cmd);
				अगर (cmd) अणु
					regmap_ग_लिखो(dev->map, DW_IC_TX_TL, 2 * (buf_len - 1));
					regmap_ग_लिखो(dev->map, DW_IC_RX_TL, 2 * (buf_len - 1));
					/*
					 * Need to check the stop bit. However, it cannot be
					 * detected from the रेजिस्टरs so we check it always
					 * when पढ़ो/ग_लिखो the last byte.
					 */
					status = i2c_dw_status(dev);
					अगर (status)
						वापस status;

					क्रम (data_idx = 0; data_idx < buf_len; data_idx++) अणु
						regmap_पढ़ो(dev->map, DW_IC_DATA_CMD, &val);
						tx_buf[data_idx] = val;
					पूर्ण
					status = i2c_dw_check_stopbit(dev);
					अगर (status)
						वापस status;
				पूर्ण
			पूर्ण अन्यथा अणु
				regmap_ग_लिखो(dev->map, DW_IC_DATA_CMD, *tx_buf++ | cmd);
				usleep_range(AMD_TIMEOUT_MIN_US, AMD_TIMEOUT_MAX_US);
			पूर्ण
		पूर्ण
		status = i2c_dw_check_stopbit(dev);
		अगर (status)
			वापस status;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Initiate (and जारी) low level master पढ़ो/ग_लिखो transaction.
 * This function is only called from i2c_dw_isr, and pumping i2c_msg
 * messages पूर्णांकo the tx buffer.  Even अगर the size of i2c_msg data is
 * दीर्घer than the size of the tx buffer, it handles everything.
 */
अटल व्योम
i2c_dw_xfer_msg(काष्ठा dw_i2c_dev *dev)
अणु
	काष्ठा i2c_msg *msgs = dev->msgs;
	u32 पूर्णांकr_mask;
	पूर्णांक tx_limit, rx_limit;
	u32 addr = msgs[dev->msg_ग_लिखो_idx].addr;
	u32 buf_len = dev->tx_buf_len;
	u8 *buf = dev->tx_buf;
	bool need_restart = false;
	अचिन्हित पूर्णांक flr;

	पूर्णांकr_mask = DW_IC_INTR_MASTER_MASK;

	क्रम (; dev->msg_ग_लिखो_idx < dev->msgs_num; dev->msg_ग_लिखो_idx++) अणु
		u32 flags = msgs[dev->msg_ग_लिखो_idx].flags;

		/*
		 * If target address has changed, we need to
		 * reprogram the target address in the I2C
		 * adapter when we are करोne with this transfer.
		 */
		अगर (msgs[dev->msg_ग_लिखो_idx].addr != addr) अणु
			dev_err(dev->dev,
				"%s: invalid target address\n", __func__);
			dev->msg_err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (!(dev->status & STATUS_WRITE_IN_PROGRESS)) अणु
			/* new i2c_msg */
			buf = msgs[dev->msg_ग_लिखो_idx].buf;
			buf_len = msgs[dev->msg_ग_लिखो_idx].len;

			/* If both IC_EMPTYFIFO_HOLD_MASTER_EN and
			 * IC_RESTART_EN are set, we must manually
			 * set restart bit between messages.
			 */
			अगर ((dev->master_cfg & DW_IC_CON_RESTART_EN) &&
					(dev->msg_ग_लिखो_idx > 0))
				need_restart = true;
		पूर्ण

		regmap_पढ़ो(dev->map, DW_IC_TXFLR, &flr);
		tx_limit = dev->tx_fअगरo_depth - flr;

		regmap_पढ़ो(dev->map, DW_IC_RXFLR, &flr);
		rx_limit = dev->rx_fअगरo_depth - flr;

		जबतक (buf_len > 0 && tx_limit > 0 && rx_limit > 0) अणु
			u32 cmd = 0;

			/*
			 * If IC_EMPTYFIFO_HOLD_MASTER_EN is set we must
			 * manually set the stop bit. However, it cannot be
			 * detected from the रेजिस्टरs so we set it always
			 * when writing/पढ़ोing the last byte.
			 */

			/*
			 * i2c-core always sets the buffer length of
			 * I2C_FUNC_SMBUS_BLOCK_DATA to 1. The length will
			 * be adjusted when receiving the first byte.
			 * Thus we can't stop the transaction here.
			 */
			अगर (dev->msg_ग_लिखो_idx == dev->msgs_num - 1 &&
			    buf_len == 1 && !(flags & I2C_M_RECV_LEN))
				cmd |= BIT(9);

			अगर (need_restart) अणु
				cmd |= BIT(10);
				need_restart = false;
			पूर्ण

			अगर (msgs[dev->msg_ग_लिखो_idx].flags & I2C_M_RD) अणु

				/* Aव्योम rx buffer overrun */
				अगर (dev->rx_outstanding >= dev->rx_fअगरo_depth)
					अवरोध;

				regmap_ग_लिखो(dev->map, DW_IC_DATA_CMD,
					     cmd | 0x100);
				rx_limit--;
				dev->rx_outstanding++;
			पूर्ण अन्यथा अणु
				regmap_ग_लिखो(dev->map, DW_IC_DATA_CMD,
					     cmd | *buf++);
			पूर्ण
			tx_limit--; buf_len--;
		पूर्ण

		dev->tx_buf = buf;
		dev->tx_buf_len = buf_len;

		/*
		 * Because we करोn't know the buffer length in the
		 * I2C_FUNC_SMBUS_BLOCK_DATA हाल, we can't stop
		 * the transaction here.
		 */
		अगर (buf_len > 0 || flags & I2C_M_RECV_LEN) अणु
			/* more bytes to be written */
			dev->status |= STATUS_WRITE_IN_PROGRESS;
			अवरोध;
		पूर्ण अन्यथा
			dev->status &= ~STATUS_WRITE_IN_PROGRESS;
	पूर्ण

	/*
	 * If i2c_msg index search is completed, we करोn't need TX_EMPTY
	 * पूर्णांकerrupt any more.
	 */
	अगर (dev->msg_ग_लिखो_idx == dev->msgs_num)
		पूर्णांकr_mask &= ~DW_IC_INTR_TX_EMPTY;

	अगर (dev->msg_err)
		पूर्णांकr_mask = 0;

	regmap_ग_लिखो(dev->map,  DW_IC_INTR_MASK, पूर्णांकr_mask);
पूर्ण

अटल u8
i2c_dw_recv_len(काष्ठा dw_i2c_dev *dev, u8 len)
अणु
	काष्ठा i2c_msg *msgs = dev->msgs;
	u32 flags = msgs[dev->msg_पढ़ो_idx].flags;

	/*
	 * Adjust the buffer length and mask the flag
	 * after receiving the first byte.
	 */
	len += (flags & I2C_CLIENT_PEC) ? 2 : 1;
	dev->tx_buf_len = len - min_t(u8, len, dev->rx_outstanding);
	msgs[dev->msg_पढ़ो_idx].len = len;
	msgs[dev->msg_पढ़ो_idx].flags &= ~I2C_M_RECV_LEN;

	वापस len;
पूर्ण

अटल व्योम
i2c_dw_पढ़ो(काष्ठा dw_i2c_dev *dev)
अणु
	काष्ठा i2c_msg *msgs = dev->msgs;
	अचिन्हित पूर्णांक rx_valid;

	क्रम (; dev->msg_पढ़ो_idx < dev->msgs_num; dev->msg_पढ़ो_idx++) अणु
		u32 len, पंचांगp;
		u8 *buf;

		अगर (!(msgs[dev->msg_पढ़ो_idx].flags & I2C_M_RD))
			जारी;

		अगर (!(dev->status & STATUS_READ_IN_PROGRESS)) अणु
			len = msgs[dev->msg_पढ़ो_idx].len;
			buf = msgs[dev->msg_पढ़ो_idx].buf;
		पूर्ण अन्यथा अणु
			len = dev->rx_buf_len;
			buf = dev->rx_buf;
		पूर्ण

		regmap_पढ़ो(dev->map, DW_IC_RXFLR, &rx_valid);

		क्रम (; len > 0 && rx_valid > 0; len--, rx_valid--) अणु
			u32 flags = msgs[dev->msg_पढ़ो_idx].flags;

			regmap_पढ़ो(dev->map, DW_IC_DATA_CMD, &पंचांगp);
			/* Ensure length byte is a valid value */
			अगर (flags & I2C_M_RECV_LEN &&
			    (पंचांगp & DW_IC_DATA_CMD_DAT) <= I2C_SMBUS_BLOCK_MAX && पंचांगp > 0) अणु
				len = i2c_dw_recv_len(dev, पंचांगp);
			पूर्ण
			*buf++ = पंचांगp;
			dev->rx_outstanding--;
		पूर्ण

		अगर (len > 0) अणु
			dev->status |= STATUS_READ_IN_PROGRESS;
			dev->rx_buf_len = len;
			dev->rx_buf = buf;
			वापस;
		पूर्ण अन्यथा
			dev->status &= ~STATUS_READ_IN_PROGRESS;
	पूर्ण
पूर्ण

/*
 * Prepare controller क्रम a transaction and call i2c_dw_xfer_msg.
 */
अटल पूर्णांक
i2c_dw_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा dw_i2c_dev *dev = i2c_get_adapdata(adap);
	पूर्णांक ret;

	dev_dbg(dev->dev, "%s: msgs: %d\n", __func__, num);

	pm_runसमय_get_sync(dev->dev);

	/*
	 * Initiate I2C message transfer when AMD NAVI GPU card is enabled,
	 * As it is polling based transfer mechanism, which करोes not support
	 * पूर्णांकerrupt based functionalities of existing DesignWare driver.
	 */
	अगर ((dev->flags & MODEL_MASK) == MODEL_AMD_NAVI_GPU) अणु
		ret = amd_i2c_dw_xfer_quirk(adap, msgs, num);
		जाओ करोne_nolock;
	पूर्ण

	अगर (dev_WARN_ONCE(dev->dev, dev->suspended, "Transfer while suspended\n")) अणु
		ret = -ESHUTDOWN;
		जाओ करोne_nolock;
	पूर्ण

	reinit_completion(&dev->cmd_complete);
	dev->msgs = msgs;
	dev->msgs_num = num;
	dev->cmd_err = 0;
	dev->msg_ग_लिखो_idx = 0;
	dev->msg_पढ़ो_idx = 0;
	dev->msg_err = 0;
	dev->status = STATUS_IDLE;
	dev->पात_source = 0;
	dev->rx_outstanding = 0;

	ret = i2c_dw_acquire_lock(dev);
	अगर (ret)
		जाओ करोne_nolock;

	ret = i2c_dw_रुको_bus_not_busy(dev);
	अगर (ret < 0)
		जाओ करोne;

	/* Start the transfers */
	i2c_dw_xfer_init(dev);

	/* Wait क्रम tx to complete */
	अगर (!रुको_क्रम_completion_समयout(&dev->cmd_complete, adap->समयout)) अणु
		dev_err(dev->dev, "controller timed out\n");
		/* i2c_dw_init implicitly disables the adapter */
		i2c_recover_bus(&dev->adapter);
		i2c_dw_init_master(dev);
		ret = -ETIMEDOUT;
		जाओ करोne;
	पूर्ण

	/*
	 * We must disable the adapter beक्रमe वापसing and संकेतing the end
	 * of the current transfer. Otherwise the hardware might जारी
	 * generating पूर्णांकerrupts which in turn causes a race condition with
	 * the following transfer.  Needs some more investigation अगर the
	 * additional पूर्णांकerrupts are a hardware bug or this driver करोesn't
	 * handle them correctly yet.
	 */
	__i2c_dw_disable_noरुको(dev);

	अगर (dev->msg_err) अणु
		ret = dev->msg_err;
		जाओ करोne;
	पूर्ण

	/* No error */
	अगर (likely(!dev->cmd_err && !dev->status)) अणु
		ret = num;
		जाओ करोne;
	पूर्ण

	/* We have an error */
	अगर (dev->cmd_err == DW_IC_ERR_TX_ABRT) अणु
		ret = i2c_dw_handle_tx_पात(dev);
		जाओ करोne;
	पूर्ण

	अगर (dev->status)
		dev_err(dev->dev,
			"transfer terminated early - interrupt latency too high?\n");

	ret = -EIO;

करोne:
	i2c_dw_release_lock(dev);

करोne_nolock:
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm i2c_dw_algo = अणु
	.master_xfer = i2c_dw_xfer,
	.functionality = i2c_dw_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks i2c_dw_quirks = अणु
	.flags = I2C_AQ_NO_ZERO_LEN,
पूर्ण;

अटल u32 i2c_dw_पढ़ो_clear_पूर्णांकrbits(काष्ठा dw_i2c_dev *dev)
अणु
	u32 stat, dummy;

	/*
	 * The IC_INTR_STAT रेजिस्टर just indicates "enabled" पूर्णांकerrupts.
	 * The unmasked raw version of पूर्णांकerrupt status bits is available
	 * in the IC_RAW_INTR_STAT रेजिस्टर.
	 *
	 * That is,
	 *   stat = पढ़ोl(IC_INTR_STAT);
	 * equals to,
	 *   stat = पढ़ोl(IC_RAW_INTR_STAT) & पढ़ोl(IC_INTR_MASK);
	 *
	 * The raw version might be useful क्रम debugging purposes.
	 */
	regmap_पढ़ो(dev->map, DW_IC_INTR_STAT, &stat);

	/*
	 * Do not use the IC_CLR_INTR रेजिस्टर to clear पूर्णांकerrupts, or
	 * you'll miss some पूर्णांकerrupts, triggered during the period from
	 * पढ़ोl(IC_INTR_STAT) to पढ़ोl(IC_CLR_INTR).
	 *
	 * Instead, use the separately-prepared IC_CLR_* रेजिस्टरs.
	 */
	अगर (stat & DW_IC_INTR_RX_UNDER)
		regmap_पढ़ो(dev->map, DW_IC_CLR_RX_UNDER, &dummy);
	अगर (stat & DW_IC_INTR_RX_OVER)
		regmap_पढ़ो(dev->map, DW_IC_CLR_RX_OVER, &dummy);
	अगर (stat & DW_IC_INTR_TX_OVER)
		regmap_पढ़ो(dev->map, DW_IC_CLR_TX_OVER, &dummy);
	अगर (stat & DW_IC_INTR_RD_REQ)
		regmap_पढ़ो(dev->map, DW_IC_CLR_RD_REQ, &dummy);
	अगर (stat & DW_IC_INTR_TX_ABRT) अणु
		/*
		 * The IC_TX_ABRT_SOURCE रेजिस्टर is cleared whenever
		 * the IC_CLR_TX_ABRT is पढ़ो.  Preserve it beक्रमehand.
		 */
		regmap_पढ़ो(dev->map, DW_IC_TX_ABRT_SOURCE, &dev->पात_source);
		regmap_पढ़ो(dev->map, DW_IC_CLR_TX_ABRT, &dummy);
	पूर्ण
	अगर (stat & DW_IC_INTR_RX_DONE)
		regmap_पढ़ो(dev->map, DW_IC_CLR_RX_DONE, &dummy);
	अगर (stat & DW_IC_INTR_ACTIVITY)
		regmap_पढ़ो(dev->map, DW_IC_CLR_ACTIVITY, &dummy);
	अगर (stat & DW_IC_INTR_STOP_DET)
		regmap_पढ़ो(dev->map, DW_IC_CLR_STOP_DET, &dummy);
	अगर (stat & DW_IC_INTR_START_DET)
		regmap_पढ़ो(dev->map, DW_IC_CLR_START_DET, &dummy);
	अगर (stat & DW_IC_INTR_GEN_CALL)
		regmap_पढ़ो(dev->map, DW_IC_CLR_GEN_CALL, &dummy);

	वापस stat;
पूर्ण

/*
 * Interrupt service routine. This माला_लो called whenever an I2C master पूर्णांकerrupt
 * occurs.
 */
अटल पूर्णांक i2c_dw_irq_handler_master(काष्ठा dw_i2c_dev *dev)
अणु
	u32 stat;

	stat = i2c_dw_पढ़ो_clear_पूर्णांकrbits(dev);
	अगर (stat & DW_IC_INTR_TX_ABRT) अणु
		dev->cmd_err |= DW_IC_ERR_TX_ABRT;
		dev->status = STATUS_IDLE;

		/*
		 * Anyसमय TX_ABRT is set, the contents of the tx/rx
		 * buffers are flushed. Make sure to skip them.
		 */
		regmap_ग_लिखो(dev->map, DW_IC_INTR_MASK, 0);
		जाओ tx_पातed;
	पूर्ण

	अगर (stat & DW_IC_INTR_RX_FULL)
		i2c_dw_पढ़ो(dev);

	अगर (stat & DW_IC_INTR_TX_EMPTY)
		i2c_dw_xfer_msg(dev);

	/*
	 * No need to modअगरy or disable the पूर्णांकerrupt mask here.
	 * i2c_dw_xfer_msg() will take care of it according to
	 * the current transmit status.
	 */

tx_पातed:
	अगर ((stat & (DW_IC_INTR_TX_ABRT | DW_IC_INTR_STOP_DET)) || dev->msg_err)
		complete(&dev->cmd_complete);
	अन्यथा अगर (unlikely(dev->flags & ACCESS_INTR_MASK)) अणु
		/* Workaround to trigger pending पूर्णांकerrupt */
		regmap_पढ़ो(dev->map, DW_IC_INTR_MASK, &stat);
		i2c_dw_disable_पूर्णांक(dev);
		regmap_ग_लिखो(dev->map, DW_IC_INTR_MASK, stat);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t i2c_dw_isr(पूर्णांक this_irq, व्योम *dev_id)
अणु
	काष्ठा dw_i2c_dev *dev = dev_id;
	u32 stat, enabled;

	regmap_पढ़ो(dev->map, DW_IC_ENABLE, &enabled);
	regmap_पढ़ो(dev->map, DW_IC_RAW_INTR_STAT, &stat);
	dev_dbg(dev->dev, "enabled=%#x stat=%#x\n", enabled, stat);
	अगर (!enabled || !(stat & ~DW_IC_INTR_ACTIVITY))
		वापस IRQ_NONE;

	i2c_dw_irq_handler_master(dev);

	वापस IRQ_HANDLED;
पूर्ण

व्योम i2c_dw_configure_master(काष्ठा dw_i2c_dev *dev)
अणु
	काष्ठा i2c_timings *t = &dev->timings;

	dev->functionality = I2C_FUNC_10BIT_ADDR | DW_IC_DEFAULT_FUNCTIONALITY;

	dev->master_cfg = DW_IC_CON_MASTER | DW_IC_CON_SLAVE_DISABLE |
			  DW_IC_CON_RESTART_EN;

	dev->mode = DW_IC_MASTER;

	चयन (t->bus_freq_hz) अणु
	हाल I2C_MAX_STANDARD_MODE_FREQ:
		dev->master_cfg |= DW_IC_CON_SPEED_STD;
		अवरोध;
	हाल I2C_MAX_HIGH_SPEED_MODE_FREQ:
		dev->master_cfg |= DW_IC_CON_SPEED_HIGH;
		अवरोध;
	शेष:
		dev->master_cfg |= DW_IC_CON_SPEED_FAST;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(i2c_dw_configure_master);

अटल व्योम i2c_dw_prepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा dw_i2c_dev *dev = i2c_get_adapdata(adap);

	i2c_dw_disable(dev);
	reset_control_निश्चित(dev->rst);
	i2c_dw_prepare_clk(dev, false);
पूर्ण

अटल व्योम i2c_dw_unprepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा dw_i2c_dev *dev = i2c_get_adapdata(adap);

	i2c_dw_prepare_clk(dev, true);
	reset_control_deनिश्चित(dev->rst);
	i2c_dw_init_master(dev);
पूर्ण

अटल पूर्णांक i2c_dw_init_recovery_info(काष्ठा dw_i2c_dev *dev)
अणु
	काष्ठा i2c_bus_recovery_info *rinfo = &dev->rinfo;
	काष्ठा i2c_adapter *adap = &dev->adapter;
	काष्ठा gpio_desc *gpio;

	gpio = devm_gpiod_get_optional(dev->dev, "scl", GPIOD_OUT_HIGH);
	अगर (IS_ERR_OR_शून्य(gpio))
		वापस PTR_ERR_OR_ZERO(gpio);

	rinfo->scl_gpiod = gpio;

	gpio = devm_gpiod_get_optional(dev->dev, "sda", GPIOD_IN);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);
	rinfo->sda_gpiod = gpio;

	rinfo->recover_bus = i2c_generic_scl_recovery;
	rinfo->prepare_recovery = i2c_dw_prepare_recovery;
	rinfo->unprepare_recovery = i2c_dw_unprepare_recovery;
	adap->bus_recovery_info = rinfo;

	dev_info(dev->dev, "running with gpio recovery mode! scl%s",
		 rinfo->sda_gpiod ? ",sda" : "");

	वापस 0;
पूर्ण

अटल पूर्णांक amd_i2c_adap_quirk(काष्ठा dw_i2c_dev *dev)
अणु
	काष्ठा i2c_adapter *adap = &dev->adapter;
	पूर्णांक ret;

	pm_runसमय_get_noresume(dev->dev);
	ret = i2c_add_numbered_adapter(adap);
	अगर (ret)
		dev_err(dev->dev, "Failed to add adapter: %d\n", ret);
	pm_runसमय_put_noidle(dev->dev);

	वापस ret;
पूर्ण

पूर्णांक i2c_dw_probe_master(काष्ठा dw_i2c_dev *dev)
अणु
	काष्ठा i2c_adapter *adap = &dev->adapter;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक ret;

	init_completion(&dev->cmd_complete);

	dev->init = i2c_dw_init_master;
	dev->disable = i2c_dw_disable;
	dev->disable_पूर्णांक = i2c_dw_disable_पूर्णांक;

	ret = i2c_dw_init_regmap(dev);
	अगर (ret)
		वापस ret;

	ret = i2c_dw_set_timings_master(dev);
	अगर (ret)
		वापस ret;

	ret = i2c_dw_set_fअगरo_size(dev);
	अगर (ret)
		वापस ret;

	ret = dev->init(dev);
	अगर (ret)
		वापस ret;

	snम_लिखो(adap->name, माप(adap->name),
		 "Synopsys DesignWare I2C adapter");
	adap->retries = 3;
	adap->algo = &i2c_dw_algo;
	adap->quirks = &i2c_dw_quirks;
	adap->dev.parent = dev->dev;
	i2c_set_adapdata(adap, dev);

	अगर ((dev->flags & MODEL_MASK) == MODEL_AMD_NAVI_GPU)
		वापस amd_i2c_adap_quirk(dev);

	अगर (dev->flags & ACCESS_NO_IRQ_SUSPEND) अणु
		irq_flags = IRQF_NO_SUSPEND;
	पूर्ण अन्यथा अणु
		irq_flags = IRQF_SHARED | IRQF_COND_SUSPEND;
	पूर्ण

	i2c_dw_disable_पूर्णांक(dev);
	ret = devm_request_irq(dev->dev, dev->irq, i2c_dw_isr, irq_flags,
			       dev_name(dev->dev), dev);
	अगर (ret) अणु
		dev_err(dev->dev, "failure requesting irq %i: %d\n",
			dev->irq, ret);
		वापस ret;
	पूर्ण

	ret = i2c_dw_init_recovery_info(dev);
	अगर (ret)
		वापस ret;

	/*
	 * Increment PM usage count during adapter registration in order to
	 * aव्योम possible spurious runसमय suspend when adapter device is
	 * रेजिस्टरed to the device core and immediate resume in हाल bus has
	 * रेजिस्टरed I2C slaves that करो I2C transfers in their probe.
	 */
	pm_runसमय_get_noresume(dev->dev);
	ret = i2c_add_numbered_adapter(adap);
	अगर (ret)
		dev_err(dev->dev, "failure adding adapter: %d\n", ret);
	pm_runसमय_put_noidle(dev->dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_dw_probe_master);

MODULE_DESCRIPTION("Synopsys DesignWare I2C bus master adapter");
MODULE_LICENSE("GPL");
