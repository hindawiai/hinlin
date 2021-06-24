<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PTP hardware घड़ी driver क्रम the IDT ClockMatrix(TM) family of timing and
 * synchronization devices.
 *
 * Copyright (C) 2019 Integrated Device Technology, Inc., a Renesas Company.
 */
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयkeeping.h>
#समावेश <linux/माला.स>

#समावेश "ptp_private.h"
#समावेश "ptp_clockmatrix.h"

MODULE_DESCRIPTION("Driver for IDT ClockMatrix(TM) family");
MODULE_AUTHOR("Richard Cochran <richardcochran@gmail.com>");
MODULE_AUTHOR("IDT support-1588 <IDT-support-1588@lm.renesas.com>");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");

/*
 * The name of the firmware file to be loaded
 * over-rides any स्वतःmatic selection
 */
अटल अक्षर *firmware;
module_param(firmware, अक्षरp, 0);

#घोषणा SETTIME_CORRECTION (0)

अटल पूर्णांक contains_full_configuration(स्थिर काष्ठा firmware *fw)
अणु
	s32 full_count = FULL_FW_CFG_BYTES - FULL_FW_CFG_SKIPPED_BYTES;
	काष्ठा idtcm_fwrc *rec = (काष्ठा idtcm_fwrc *)fw->data;
	s32 count = 0;
	u16 regaddr;
	u8 loaddr;
	s32 len;

	/* If the firmware contains 'full configuration' SM_RESET can be used
	 * to ensure proper configuration.
	 *
	 * Full configuration is defined as the number of programmable
	 * bytes within the configuration range minus page offset addr range.
	 */
	क्रम (len = fw->size; len > 0; len -= माप(*rec)) अणु
		regaddr = rec->hiaddr << 8;
		regaddr |= rec->loaddr;

		loaddr = rec->loaddr;

		rec++;

		/* Top (status रेजिस्टरs) and bottom are पढ़ो-only */
		अगर (regaddr < GPIO_USER_CONTROL || regaddr >= SCRATCH)
			जारी;

		/* Page size 128, last 4 bytes of page skipped */
		अगर ((loaddr > 0x7b && loaddr <= 0x7f) || loaddr > 0xfb)
			जारी;

		count++;
	पूर्ण

	वापस (count >= full_count);
पूर्ण

अटल पूर्णांक अक्षर_array_to_बारpec(u8 *buf,
				  u8 count,
				  काष्ठा बारpec64 *ts)
अणु
	u8 i;
	u64 nsec;
	समय64_t sec;

	अगर (count < TOD_BYTE_COUNT)
		वापस 1;

	/* Sub-nanoseconds are in buf[0]. */
	nsec = buf[4];
	क्रम (i = 0; i < 3; i++) अणु
		nsec <<= 8;
		nsec |= buf[3 - i];
	पूर्ण

	sec = buf[10];
	क्रम (i = 0; i < 5; i++) अणु
		sec <<= 8;
		sec |= buf[9 - i];
	पूर्ण

	ts->tv_sec = sec;
	ts->tv_nsec = nsec;

	वापस 0;
पूर्ण

अटल पूर्णांक बारpec_to_अक्षर_array(काष्ठा बारpec64 स्थिर *ts,
				  u8 *buf,
				  u8 count)
अणु
	u8 i;
	s32 nsec;
	समय64_t sec;

	अगर (count < TOD_BYTE_COUNT)
		वापस 1;

	nsec = ts->tv_nsec;
	sec = ts->tv_sec;

	/* Sub-nanoseconds are in buf[0]. */
	buf[0] = 0;
	क्रम (i = 1; i < 5; i++) अणु
		buf[i] = nsec & 0xff;
		nsec >>= 8;
	पूर्ण

	क्रम (i = 5; i < TOD_BYTE_COUNT; i++) अणु

		buf[i] = sec & 0xff;
		sec >>= 8;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक idtcm_strverscmp(स्थिर अक्षर *version1, स्थिर अक्षर *version2)
अणु
	u8 ver1[3], ver2[3];
	पूर्णांक i;

	अगर (माला_पूछो(version1, "%hhu.%hhu.%hhu",
		   &ver1[0], &ver1[1], &ver1[2]) != 3)
		वापस -1;
	अगर (माला_पूछो(version2, "%hhu.%hhu.%hhu",
		   &ver2[0], &ver2[1], &ver2[2]) != 3)
		वापस -1;

	क्रम (i = 0; i < 3; i++) अणु
		अगर (ver1[i] > ver2[i])
			वापस 1;
		अगर (ver1[i] < ver2[i])
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक idtcm_xfer_पढ़ो(काष्ठा idtcm *idtcm,
			   u8 regaddr,
			   u8 *buf,
			   u16 count)
अणु
	काष्ठा i2c_client *client = idtcm->client;
	काष्ठा i2c_msg msg[2];
	पूर्णांक cnt;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf = &regaddr;

	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = count;
	msg[1].buf = buf;

	cnt = i2c_transfer(client->adapter, msg, 2);

	अगर (cnt < 0) अणु
		dev_err(&client->dev,
			"i2c_transfer failed at %d in %s, at addr: %04x!",
			__LINE__, __func__, regaddr);
		वापस cnt;
	पूर्ण अन्यथा अगर (cnt != 2) अणु
		dev_err(&client->dev,
			"i2c_transfer sent only %d of %d messages", cnt, 2);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक idtcm_xfer_ग_लिखो(काष्ठा idtcm *idtcm,
			    u8 regaddr,
			    u8 *buf,
			    u16 count)
अणु
	काष्ठा i2c_client *client = idtcm->client;
	/* we add 1 byte क्रम device रेजिस्टर */
	u8 msg[IDTCM_MAX_WRITE_COUNT + 1];
	पूर्णांक cnt;

	अगर (count > IDTCM_MAX_WRITE_COUNT)
		वापस -EINVAL;

	msg[0] = regaddr;
	स_नकल(&msg[1], buf, count);

	cnt = i2c_master_send(client, msg, count + 1);

	अगर (cnt < 0) अणु
		dev_err(&client->dev,
			"i2c_master_send failed at %d in %s, at addr: %04x!",
			__LINE__, __func__, regaddr);
		वापस cnt;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक idtcm_page_offset(काष्ठा idtcm *idtcm, u8 val)
अणु
	u8 buf[4];
	पूर्णांक err;

	अगर (idtcm->page_offset == val)
		वापस 0;

	buf[0] = 0x0;
	buf[1] = val;
	buf[2] = 0x10;
	buf[3] = 0x20;

	err = idtcm_xfer_ग_लिखो(idtcm, PAGE_ADDR, buf, माप(buf));
	अगर (err) अणु
		idtcm->page_offset = 0xff;
		dev_err(&idtcm->client->dev, "failed to set page offset");
	पूर्ण अन्यथा अणु
		idtcm->page_offset = val;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक _idtcm_rdwr(काष्ठा idtcm *idtcm,
		       u16 regaddr,
		       u8 *buf,
		       u16 count,
		       bool ग_लिखो)
अणु
	u8 hi;
	u8 lo;
	पूर्णांक err;

	hi = (regaddr >> 8) & 0xff;
	lo = regaddr & 0xff;

	err = idtcm_page_offset(idtcm, hi);
	अगर (err)
		वापस err;

	अगर (ग_लिखो)
		वापस idtcm_xfer_ग_लिखो(idtcm, lo, buf, count);

	वापस idtcm_xfer_पढ़ो(idtcm, lo, buf, count);
पूर्ण

अटल पूर्णांक idtcm_पढ़ो(काष्ठा idtcm *idtcm,
		      u16 module,
		      u16 regaddr,
		      u8 *buf,
		      u16 count)
अणु
	वापस _idtcm_rdwr(idtcm, module + regaddr, buf, count, false);
पूर्ण

अटल पूर्णांक idtcm_ग_लिखो(काष्ठा idtcm *idtcm,
		       u16 module,
		       u16 regaddr,
		       u8 *buf,
		       u16 count)
अणु
	वापस _idtcm_rdwr(idtcm, module + regaddr, buf, count, true);
पूर्ण

अटल पूर्णांक clear_boot_status(काष्ठा idtcm *idtcm)
अणु
	u8 buf[4] = अणु0पूर्ण;

	वापस idtcm_ग_लिखो(idtcm, GENERAL_STATUS, BOOT_STATUS, buf, माप(buf));
पूर्ण

अटल पूर्णांक पढ़ो_boot_status(काष्ठा idtcm *idtcm, u32 *status)
अणु
	पूर्णांक err;
	u8 buf[4] = अणु0पूर्ण;

	err = idtcm_पढ़ो(idtcm, GENERAL_STATUS, BOOT_STATUS, buf, माप(buf));

	*status = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];

	वापस err;
पूर्ण

अटल पूर्णांक रुको_क्रम_boot_status_पढ़ोy(काष्ठा idtcm *idtcm)
अणु
	u32 status = 0;
	u8 i = 30;	/* 30 * 100ms = 3s */
	पूर्णांक err;

	करो अणु
		err = पढ़ो_boot_status(idtcm, &status);
		अगर (err)
			वापस err;

		अगर (status == 0xA0)
			वापस 0;

		msleep(100);
		i--;

	पूर्ण जबतक (i);

	dev_warn(&idtcm->client->dev, "%s timed out", __func__);

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक पढ़ो_sys_apll_status(काष्ठा idtcm *idtcm, u8 *status)
अणु
	वापस idtcm_पढ़ो(idtcm, STATUS, DPLL_SYS_APLL_STATUS, status,
			  माप(u8));
पूर्ण

अटल पूर्णांक पढ़ो_sys_dpll_status(काष्ठा idtcm *idtcm, u8 *status)
अणु
	वापस idtcm_पढ़ो(idtcm, STATUS, DPLL_SYS_STATUS, status, माप(u8));
पूर्ण

अटल पूर्णांक रुको_क्रम_sys_apll_dpll_lock(काष्ठा idtcm *idtcm)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(LOCK_TIMEOUT_MS);
	u8 apll = 0;
	u8 dpll = 0;
	पूर्णांक err;

	करो अणु
		err = पढ़ो_sys_apll_status(idtcm, &apll);
		अगर (err)
			वापस err;

		err = पढ़ो_sys_dpll_status(idtcm, &dpll);
		अगर (err)
			वापस err;

		apll &= SYS_APLL_LOSS_LOCK_LIVE_MASK;
		dpll &= DPLL_SYS_STATE_MASK;

		अगर (apll == SYS_APLL_LOSS_LOCK_LIVE_LOCKED &&
		    dpll == DPLL_STATE_LOCKED) अणु
			वापस 0;
		पूर्ण अन्यथा अगर (dpll == DPLL_STATE_FREERUN ||
			   dpll == DPLL_STATE_HOLDOVER ||
			   dpll == DPLL_STATE_OPEN_LOOP) अणु
			dev_warn(&idtcm->client->dev,
				"No wait state: DPLL_SYS_STATE %d", dpll);
			वापस -EPERM;
		पूर्ण

		msleep(LOCK_POLL_INTERVAL_MS);
	पूर्ण जबतक (समय_is_after_jअगरfies(समयout));

	dev_warn(&idtcm->client->dev,
		 "%d ms lock timeout: SYS APLL Loss Lock %d  SYS DPLL state %d",
		 LOCK_TIMEOUT_MS, apll, dpll);

	वापस -ETIME;
पूर्ण

अटल व्योम रुको_क्रम_chip_पढ़ोy(काष्ठा idtcm *idtcm)
अणु
	अगर (रुको_क्रम_boot_status_पढ़ोy(idtcm))
		dev_warn(&idtcm->client->dev, "BOOT_STATUS != 0xA0");

	अगर (रुको_क्रम_sys_apll_dpll_lock(idtcm))
		dev_warn(&idtcm->client->dev,
			 "Continuing while SYS APLL/DPLL is not locked");
पूर्ण

अटल पूर्णांक _idtcm_समय_लो(काष्ठा idtcm_channel *channel,
			  काष्ठा बारpec64 *ts)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	u8 buf[TOD_BYTE_COUNT];
	u8 समयout = 10;
	u8 trigger;
	पूर्णांक err;

	err = idtcm_पढ़ो(idtcm, channel->tod_पढ़ो_primary,
			 TOD_READ_PRIMARY_CMD, &trigger, माप(trigger));
	अगर (err)
		वापस err;

	trigger &= ~(TOD_READ_TRIGGER_MASK << TOD_READ_TRIGGER_SHIFT);
	trigger |= (1 << TOD_READ_TRIGGER_SHIFT);
	trigger &= ~TOD_READ_TRIGGER_MODE; /* single shot */

	err = idtcm_ग_लिखो(idtcm, channel->tod_पढ़ो_primary,
			  TOD_READ_PRIMARY_CMD, &trigger, माप(trigger));
	अगर (err)
		वापस err;

	/* रुको trigger to be 0 */
	जबतक (trigger & TOD_READ_TRIGGER_MASK) अणु
		अगर (idtcm->calculate_overhead_flag)
			idtcm->start_समय = kसमय_get_raw();

		err = idtcm_पढ़ो(idtcm, channel->tod_पढ़ो_primary,
				 TOD_READ_PRIMARY_CMD, &trigger,
				 माप(trigger));
		अगर (err)
			वापस err;

		अगर (--समयout == 0)
			वापस -EIO;
	पूर्ण

	err = idtcm_पढ़ो(idtcm, channel->tod_पढ़ो_primary,
			 TOD_READ_PRIMARY, buf, माप(buf));
	अगर (err)
		वापस err;

	err = अक्षर_array_to_बारpec(buf, माप(buf), ts);

	वापस err;
पूर्ण

अटल पूर्णांक _sync_pll_output(काष्ठा idtcm *idtcm,
			    u8 pll,
			    u8 sync_src,
			    u8 qn,
			    u8 qn_plus_1)
अणु
	पूर्णांक err;
	u8 val;
	u16 sync_ctrl0;
	u16 sync_ctrl1;
	u8 temp;

	अगर (qn == 0 && qn_plus_1 == 0)
		वापस 0;

	चयन (pll) अणु
	हाल 0:
		sync_ctrl0 = HW_Q0_Q1_CH_SYNC_CTRL_0;
		sync_ctrl1 = HW_Q0_Q1_CH_SYNC_CTRL_1;
		अवरोध;
	हाल 1:
		sync_ctrl0 = HW_Q2_Q3_CH_SYNC_CTRL_0;
		sync_ctrl1 = HW_Q2_Q3_CH_SYNC_CTRL_1;
		अवरोध;
	हाल 2:
		sync_ctrl0 = HW_Q4_Q5_CH_SYNC_CTRL_0;
		sync_ctrl1 = HW_Q4_Q5_CH_SYNC_CTRL_1;
		अवरोध;
	हाल 3:
		sync_ctrl0 = HW_Q6_Q7_CH_SYNC_CTRL_0;
		sync_ctrl1 = HW_Q6_Q7_CH_SYNC_CTRL_1;
		अवरोध;
	हाल 4:
		sync_ctrl0 = HW_Q8_CH_SYNC_CTRL_0;
		sync_ctrl1 = HW_Q8_CH_SYNC_CTRL_1;
		अवरोध;
	हाल 5:
		sync_ctrl0 = HW_Q9_CH_SYNC_CTRL_0;
		sync_ctrl1 = HW_Q9_CH_SYNC_CTRL_1;
		अवरोध;
	हाल 6:
		sync_ctrl0 = HW_Q10_CH_SYNC_CTRL_0;
		sync_ctrl1 = HW_Q10_CH_SYNC_CTRL_1;
		अवरोध;
	हाल 7:
		sync_ctrl0 = HW_Q11_CH_SYNC_CTRL_0;
		sync_ctrl1 = HW_Q11_CH_SYNC_CTRL_1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val = SYNCTRL1_MASTER_SYNC_RST;

	/* Place master sync in reset */
	err = idtcm_ग_लिखो(idtcm, 0, sync_ctrl1, &val, माप(val));
	अगर (err)
		वापस err;

	err = idtcm_ग_लिखो(idtcm, 0, sync_ctrl0, &sync_src, माप(sync_src));
	अगर (err)
		वापस err;

	/* Set sync trigger mask */
	val |= SYNCTRL1_FBDIV_FRAME_SYNC_TRIG | SYNCTRL1_FBDIV_SYNC_TRIG;

	अगर (qn)
		val |= SYNCTRL1_Q0_DIV_SYNC_TRIG;

	अगर (qn_plus_1)
		val |= SYNCTRL1_Q1_DIV_SYNC_TRIG;

	err = idtcm_ग_लिखो(idtcm, 0, sync_ctrl1, &val, माप(val));
	अगर (err)
		वापस err;

	/* PLL5 can have OUT8 as second additional output. */
	अगर (pll == 5 && qn_plus_1 != 0) अणु
		err = idtcm_पढ़ो(idtcm, 0, HW_Q8_CTRL_SPARE,
				 &temp, माप(temp));
		अगर (err)
			वापस err;

		temp &= ~(Q9_TO_Q8_SYNC_TRIG);

		err = idtcm_ग_लिखो(idtcm, 0, HW_Q8_CTRL_SPARE,
				  &temp, माप(temp));
		अगर (err)
			वापस err;

		temp |= Q9_TO_Q8_SYNC_TRIG;

		err = idtcm_ग_लिखो(idtcm, 0, HW_Q8_CTRL_SPARE,
				  &temp, माप(temp));
		अगर (err)
			वापस err;
	पूर्ण

	/* PLL6 can have OUT11 as second additional output. */
	अगर (pll == 6 && qn_plus_1 != 0) अणु
		err = idtcm_पढ़ो(idtcm, 0, HW_Q11_CTRL_SPARE,
				 &temp, माप(temp));
		अगर (err)
			वापस err;

		temp &= ~(Q10_TO_Q11_SYNC_TRIG);

		err = idtcm_ग_लिखो(idtcm, 0, HW_Q11_CTRL_SPARE,
				  &temp, माप(temp));
		अगर (err)
			वापस err;

		temp |= Q10_TO_Q11_SYNC_TRIG;

		err = idtcm_ग_लिखो(idtcm, 0, HW_Q11_CTRL_SPARE,
				  &temp, माप(temp));
		अगर (err)
			वापस err;
	पूर्ण

	/* Place master sync out of reset */
	val &= ~(SYNCTRL1_MASTER_SYNC_RST);
	err = idtcm_ग_लिखो(idtcm, 0, sync_ctrl1, &val, माप(val));

	वापस err;
पूर्ण

अटल पूर्णांक sync_source_dpll_tod_pps(u16 tod_addr, u8 *sync_src)
अणु
	पूर्णांक err = 0;

	चयन (tod_addr) अणु
	हाल TOD_0:
		*sync_src = SYNC_SOURCE_DPLL0_TOD_PPS;
		अवरोध;
	हाल TOD_1:
		*sync_src = SYNC_SOURCE_DPLL1_TOD_PPS;
		अवरोध;
	हाल TOD_2:
		*sync_src = SYNC_SOURCE_DPLL2_TOD_PPS;
		अवरोध;
	हाल TOD_3:
		*sync_src = SYNC_SOURCE_DPLL3_TOD_PPS;
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_sync_pps_output(काष्ठा idtcm_channel *channel)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	u8 pll;
	u8 sync_src;
	u8 qn;
	u8 qn_plus_1;
	पूर्णांक err = 0;
	u8 out8_mux = 0;
	u8 out11_mux = 0;
	u8 temp;
	u16 output_mask = channel->output_mask;

	err = sync_source_dpll_tod_pps(channel->tod_n, &sync_src);
	अगर (err)
		वापस err;

	err = idtcm_पढ़ो(idtcm, 0, HW_Q8_CTRL_SPARE,
			 &temp, माप(temp));
	अगर (err)
		वापस err;

	अगर ((temp & Q9_TO_Q8_FANOUT_AND_CLOCK_SYNC_ENABLE_MASK) ==
	    Q9_TO_Q8_FANOUT_AND_CLOCK_SYNC_ENABLE_MASK)
		out8_mux = 1;

	err = idtcm_पढ़ो(idtcm, 0, HW_Q11_CTRL_SPARE,
			 &temp, माप(temp));
	अगर (err)
		वापस err;

	अगर ((temp & Q10_TO_Q11_FANOUT_AND_CLOCK_SYNC_ENABLE_MASK) ==
	    Q10_TO_Q11_FANOUT_AND_CLOCK_SYNC_ENABLE_MASK)
		out11_mux = 1;

	क्रम (pll = 0; pll < 8; pll++) अणु
		qn = 0;
		qn_plus_1 = 0;

		अगर (pll < 4) अणु
			/* First 4 pll has 2 outमाला_दो */
			qn = output_mask & 0x1;
			output_mask = output_mask >> 1;
			qn_plus_1 = output_mask & 0x1;
			output_mask = output_mask >> 1;
		पूर्ण अन्यथा अगर (pll == 4) अणु
			अगर (out8_mux == 0) अणु
				qn = output_mask & 0x1;
				output_mask = output_mask >> 1;
			पूर्ण
		पूर्ण अन्यथा अगर (pll == 5) अणु
			अगर (out8_mux) अणु
				qn_plus_1 = output_mask & 0x1;
				output_mask = output_mask >> 1;
			पूर्ण
			qn = output_mask & 0x1;
			output_mask = output_mask >> 1;
		पूर्ण अन्यथा अगर (pll == 6) अणु
			qn = output_mask & 0x1;
			output_mask = output_mask >> 1;
			अगर (out11_mux) अणु
				qn_plus_1 = output_mask & 0x1;
				output_mask = output_mask >> 1;
			पूर्ण
		पूर्ण अन्यथा अगर (pll == 7) अणु
			अगर (out11_mux == 0) अणु
				qn = output_mask & 0x1;
				output_mask = output_mask >> 1;
			पूर्ण
		पूर्ण

		अगर (qn != 0 || qn_plus_1 != 0)
			err = _sync_pll_output(idtcm, pll, sync_src, qn,
					       qn_plus_1);

		अगर (err)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक _idtcm_set_dpll_hw_tod(काष्ठा idtcm_channel *channel,
			       काष्ठा बारpec64 स्थिर *ts,
			       क्रमागत hw_tod_ग_लिखो_trig_sel wr_trig)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	u8 buf[TOD_BYTE_COUNT];
	u8 cmd;
	पूर्णांक err;
	काष्ठा बारpec64 local_ts = *ts;
	s64 total_overhead_ns;

	/* Configure HW TOD ग_लिखो trigger. */
	err = idtcm_पढ़ो(idtcm, channel->hw_dpll_n, HW_DPLL_TOD_CTRL_1,
			 &cmd, माप(cmd));
	अगर (err)
		वापस err;

	cmd &= ~(0x0f);
	cmd |= wr_trig | 0x08;

	err = idtcm_ग_लिखो(idtcm, channel->hw_dpll_n, HW_DPLL_TOD_CTRL_1,
			  &cmd, माप(cmd));
	अगर (err)
		वापस err;

	अगर (wr_trig  != HW_TOD_WR_TRIG_SEL_MSB) अणु
		err = बारpec_to_अक्षर_array(&local_ts, buf, माप(buf));
		अगर (err)
			वापस err;

		err = idtcm_ग_लिखो(idtcm, channel->hw_dpll_n,
				  HW_DPLL_TOD_OVR__0, buf, माप(buf));
		अगर (err)
			वापस err;
	पूर्ण

	/* ARM HW TOD ग_लिखो trigger. */
	cmd &= ~(0x08);

	err = idtcm_ग_लिखो(idtcm, channel->hw_dpll_n, HW_DPLL_TOD_CTRL_1,
			  &cmd, माप(cmd));

	अगर (wr_trig == HW_TOD_WR_TRIG_SEL_MSB) अणु
		अगर (idtcm->calculate_overhead_flag) अणु
			/* Assumption: I2C @ 400KHz */
			kसमय_प्रकार dअगरf = kसमय_sub(kसमय_get_raw(),
						 idtcm->start_समय);
			total_overhead_ns =  kसमय_प्रकारo_ns(dअगरf)
					     + idtcm->tod_ग_लिखो_overhead_ns
					     + SETTIME_CORRECTION;

			बारpec64_add_ns(&local_ts, total_overhead_ns);

			idtcm->calculate_overhead_flag = 0;
		पूर्ण

		err = बारpec_to_अक्षर_array(&local_ts, buf, माप(buf));
		अगर (err)
			वापस err;

		err = idtcm_ग_लिखो(idtcm, channel->hw_dpll_n,
				  HW_DPLL_TOD_OVR__0, buf, माप(buf));
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक _idtcm_set_dpll_scsr_tod(काष्ठा idtcm_channel *channel,
				    काष्ठा बारpec64 स्थिर *ts,
				    क्रमागत scsr_tod_ग_लिखो_trig_sel wr_trig,
				    क्रमागत scsr_tod_ग_लिखो_type_sel wr_type)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	अचिन्हित अक्षर buf[TOD_BYTE_COUNT], cmd;
	काष्ठा बारpec64 local_ts = *ts;
	पूर्णांक err, count = 0;

	बारpec64_add_ns(&local_ts, SETTIME_CORRECTION);

	err = बारpec_to_अक्षर_array(&local_ts, buf, माप(buf));
	अगर (err)
		वापस err;

	err = idtcm_ग_लिखो(idtcm, channel->tod_ग_लिखो, TOD_WRITE,
			  buf, माप(buf));
	अगर (err)
		वापस err;

	/* Trigger the ग_लिखो operation. */
	err = idtcm_पढ़ो(idtcm, channel->tod_ग_लिखो, TOD_WRITE_CMD,
			 &cmd, माप(cmd));
	अगर (err)
		वापस err;

	cmd &= ~(TOD_WRITE_SELECTION_MASK << TOD_WRITE_SELECTION_SHIFT);
	cmd &= ~(TOD_WRITE_TYPE_MASK << TOD_WRITE_TYPE_SHIFT);
	cmd |= (wr_trig << TOD_WRITE_SELECTION_SHIFT);
	cmd |= (wr_type << TOD_WRITE_TYPE_SHIFT);

	err = idtcm_ग_लिखो(idtcm, channel->tod_ग_लिखो, TOD_WRITE_CMD,
			   &cmd, माप(cmd));
	अगर (err)
		वापस err;

	/* Wait क्रम the operation to complete. */
	जबतक (1) अणु
		/* pps trigger takes up to 1 sec to complete */
		अगर (wr_trig == SCSR_TOD_WR_TRIG_SEL_TODPPS)
			msleep(50);

		err = idtcm_पढ़ो(idtcm, channel->tod_ग_लिखो, TOD_WRITE_CMD,
				 &cmd, माप(cmd));
		अगर (err)
			वापस err;

		अगर ((cmd & TOD_WRITE_SELECTION_MASK) == 0)
			अवरोध;

		अगर (++count > 20) अणु
			dev_err(&idtcm->client->dev,
				"Timed out waiting for the write counter");
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_output_base_addr(u8 outn)
अणु
	पूर्णांक base;

	चयन (outn) अणु
	हाल 0:
		base = OUTPUT_0;
		अवरोध;
	हाल 1:
		base = OUTPUT_1;
		अवरोध;
	हाल 2:
		base = OUTPUT_2;
		अवरोध;
	हाल 3:
		base = OUTPUT_3;
		अवरोध;
	हाल 4:
		base = OUTPUT_4;
		अवरोध;
	हाल 5:
		base = OUTPUT_5;
		अवरोध;
	हाल 6:
		base = OUTPUT_6;
		अवरोध;
	हाल 7:
		base = OUTPUT_7;
		अवरोध;
	हाल 8:
		base = OUTPUT_8;
		अवरोध;
	हाल 9:
		base = OUTPUT_9;
		अवरोध;
	हाल 10:
		base = OUTPUT_10;
		अवरोध;
	हाल 11:
		base = OUTPUT_11;
		अवरोध;
	शेष:
		base = -EINVAL;
	पूर्ण

	वापस base;
पूर्ण

अटल पूर्णांक _idtcm_समय_रखो_deprecated(काष्ठा idtcm_channel *channel,
				     काष्ठा बारpec64 स्थिर *ts)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	पूर्णांक err;

	err = _idtcm_set_dpll_hw_tod(channel, ts, HW_TOD_WR_TRIG_SEL_MSB);
	अगर (err) अणु
		dev_err(&idtcm->client->dev,
			"%s: Set HW ToD failed", __func__);
		वापस err;
	पूर्ण

	वापस idtcm_sync_pps_output(channel);
पूर्ण

अटल पूर्णांक _idtcm_समय_रखो(काष्ठा idtcm_channel *channel,
			  काष्ठा बारpec64 स्थिर *ts,
			  क्रमागत scsr_tod_ग_लिखो_type_sel wr_type)
अणु
	वापस _idtcm_set_dpll_scsr_tod(channel, ts,
					SCSR_TOD_WR_TRIG_SEL_IMMEDIATE,
					wr_type);
पूर्ण

अटल पूर्णांक idtcm_set_phase_pull_in_offset(काष्ठा idtcm_channel *channel,
					  s32 offset_ns)
अणु
	पूर्णांक err;
	पूर्णांक i;
	काष्ठा idtcm *idtcm = channel->idtcm;
	u8 buf[4];

	क्रम (i = 0; i < 4; i++) अणु
		buf[i] = 0xff & (offset_ns);
		offset_ns >>= 8;
	पूर्ण

	err = idtcm_ग_लिखो(idtcm, channel->dpll_phase_pull_in, PULL_IN_OFFSET,
			  buf, माप(buf));

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_set_phase_pull_in_slope_limit(काष्ठा idtcm_channel *channel,
					       u32 max_ffo_ppb)
अणु
	पूर्णांक err;
	u8 i;
	काष्ठा idtcm *idtcm = channel->idtcm;
	u8 buf[3];

	अगर (max_ffo_ppb & 0xff000000)
		max_ffo_ppb = 0;

	क्रम (i = 0; i < 3; i++) अणु
		buf[i] = 0xff & (max_ffo_ppb);
		max_ffo_ppb >>= 8;
	पूर्ण

	err = idtcm_ग_लिखो(idtcm, channel->dpll_phase_pull_in,
			  PULL_IN_SLOPE_LIMIT, buf, माप(buf));

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_start_phase_pull_in(काष्ठा idtcm_channel *channel)
अणु
	पूर्णांक err;
	काष्ठा idtcm *idtcm = channel->idtcm;
	u8 buf;

	err = idtcm_पढ़ो(idtcm, channel->dpll_phase_pull_in, PULL_IN_CTRL,
			 &buf, माप(buf));
	अगर (err)
		वापस err;

	अगर (buf == 0) अणु
		buf = 0x01;
		err = idtcm_ग_लिखो(idtcm, channel->dpll_phase_pull_in,
				  PULL_IN_CTRL, &buf, माप(buf));
	पूर्ण अन्यथा अणु
		err = -EBUSY;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_करो_phase_pull_in(काष्ठा idtcm_channel *channel,
				  s32 offset_ns,
				  u32 max_ffo_ppb)
अणु
	पूर्णांक err;

	err = idtcm_set_phase_pull_in_offset(channel, -offset_ns);
	अगर (err)
		वापस err;

	err = idtcm_set_phase_pull_in_slope_limit(channel, max_ffo_ppb);
	अगर (err)
		वापस err;

	err = idtcm_start_phase_pull_in(channel);

	वापस err;
पूर्ण

अटल पूर्णांक set_tod_ग_लिखो_overhead(काष्ठा idtcm_channel *channel)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	s64 current_ns = 0;
	s64 lowest_ns = 0;
	पूर्णांक err;
	u8 i;
	kसमय_प्रकार start;
	kसमय_प्रकार stop;
	kसमय_प्रकार dअगरf;

	अक्षर buf[TOD_BYTE_COUNT] = अणु0पूर्ण;

	/* Set page offset */
	idtcm_ग_लिखो(idtcm, channel->hw_dpll_n, HW_DPLL_TOD_OVR__0,
		    buf, माप(buf));

	क्रम (i = 0; i < TOD_WRITE_OVERHEAD_COUNT_MAX; i++) अणु
		start = kसमय_get_raw();

		err = idtcm_ग_लिखो(idtcm, channel->hw_dpll_n,
				  HW_DPLL_TOD_OVR__0, buf, माप(buf));
		अगर (err)
			वापस err;

		stop = kसमय_get_raw();

		dअगरf = kसमय_sub(stop, start);

		current_ns = kसमय_प्रकारo_ns(dअगरf);

		अगर (i == 0) अणु
			lowest_ns = current_ns;
		पूर्ण अन्यथा अणु
			अगर (current_ns < lowest_ns)
				lowest_ns = current_ns;
		पूर्ण
	पूर्ण

	idtcm->tod_ग_लिखो_overhead_ns = lowest_ns;

	वापस err;
पूर्ण

अटल पूर्णांक _idtcm_adjसमय_deprecated(काष्ठा idtcm_channel *channel, s64 delta)
अणु
	पूर्णांक err;
	काष्ठा idtcm *idtcm = channel->idtcm;
	काष्ठा बारpec64 ts;
	s64 now;

	अगर (असल(delta) < PHASE_PULL_IN_THRESHOLD_NS_DEPRECATED) अणु
		err = idtcm_करो_phase_pull_in(channel, delta, 0);
	पूर्ण अन्यथा अणु
		idtcm->calculate_overhead_flag = 1;

		err = set_tod_ग_लिखो_overhead(channel);
		अगर (err)
			वापस err;

		err = _idtcm_समय_लो(channel, &ts);
		अगर (err)
			वापस err;

		now = बारpec64_to_ns(&ts);
		now += delta;

		ts = ns_to_बारpec64(now);

		err = _idtcm_समय_रखो_deprecated(channel, &ts);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_state_machine_reset(काष्ठा idtcm *idtcm)
अणु
	u8 byte = SM_RESET_CMD;
	u32 status = 0;
	पूर्णांक err;
	u8 i;

	clear_boot_status(idtcm);

	err = idtcm_ग_लिखो(idtcm, RESET_CTRL, SM_RESET, &byte, माप(byte));

	अगर (!err) अणु
		क्रम (i = 0; i < 30; i++) अणु
			msleep_पूर्णांकerruptible(100);
			पढ़ो_boot_status(idtcm, &status);

			अगर (status == 0xA0) अणु
				dev_dbg(&idtcm->client->dev,
					"SM_RESET completed in %d ms", i * 100);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!status)
			dev_err(&idtcm->client->dev,
				"Timed out waiting for CM_RESET to complete");
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_पढ़ो_hw_rev_id(काष्ठा idtcm *idtcm, u8 *hw_rev_id)
अणु
	वापस idtcm_पढ़ो(idtcm, HW_REVISION, REV_ID, hw_rev_id, माप(u8));
पूर्ण

अटल पूर्णांक idtcm_पढ़ो_product_id(काष्ठा idtcm *idtcm, u16 *product_id)
अणु
	पूर्णांक err;
	u8 buf[2] = अणु0पूर्ण;

	err = idtcm_पढ़ो(idtcm, GENERAL_STATUS, PRODUCT_ID, buf, माप(buf));

	*product_id = (buf[1] << 8) | buf[0];

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_पढ़ो_major_release(काष्ठा idtcm *idtcm, u8 *major)
अणु
	पूर्णांक err;
	u8 buf = 0;

	err = idtcm_पढ़ो(idtcm, GENERAL_STATUS, MAJ_REL, &buf, माप(buf));

	*major = buf >> 1;

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_पढ़ो_minor_release(काष्ठा idtcm *idtcm, u8 *minor)
अणु
	वापस idtcm_पढ़ो(idtcm, GENERAL_STATUS, MIN_REL, minor, माप(u8));
पूर्ण

अटल पूर्णांक idtcm_पढ़ो_hotfix_release(काष्ठा idtcm *idtcm, u8 *hotfix)
अणु
	वापस idtcm_पढ़ो(idtcm,
			  GENERAL_STATUS,
			  HOTFIX_REL,
			  hotfix,
			  माप(u8));
पूर्ण

अटल पूर्णांक idtcm_पढ़ो_otp_scsr_config_select(काष्ठा idtcm *idtcm,
					     u8 *config_select)
अणु
	वापस idtcm_पढ़ो(idtcm, GENERAL_STATUS, OTP_SCSR_CONFIG_SELECT,
			  config_select, माप(u8));
पूर्ण

अटल पूर्णांक set_pll_output_mask(काष्ठा idtcm *idtcm, u16 addr, u8 val)
अणु
	पूर्णांक err = 0;

	चयन (addr) अणु
	हाल TOD0_OUT_ALIGN_MASK_ADDR:
		SET_U16_LSB(idtcm->channel[0].output_mask, val);
		अवरोध;
	हाल TOD0_OUT_ALIGN_MASK_ADDR + 1:
		SET_U16_MSB(idtcm->channel[0].output_mask, val);
		अवरोध;
	हाल TOD1_OUT_ALIGN_MASK_ADDR:
		SET_U16_LSB(idtcm->channel[1].output_mask, val);
		अवरोध;
	हाल TOD1_OUT_ALIGN_MASK_ADDR + 1:
		SET_U16_MSB(idtcm->channel[1].output_mask, val);
		अवरोध;
	हाल TOD2_OUT_ALIGN_MASK_ADDR:
		SET_U16_LSB(idtcm->channel[2].output_mask, val);
		अवरोध;
	हाल TOD2_OUT_ALIGN_MASK_ADDR + 1:
		SET_U16_MSB(idtcm->channel[2].output_mask, val);
		अवरोध;
	हाल TOD3_OUT_ALIGN_MASK_ADDR:
		SET_U16_LSB(idtcm->channel[3].output_mask, val);
		अवरोध;
	हाल TOD3_OUT_ALIGN_MASK_ADDR + 1:
		SET_U16_MSB(idtcm->channel[3].output_mask, val);
		अवरोध;
	शेष:
		err = -EFAULT; /* Bad address */;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक set_tod_ptp_pll(काष्ठा idtcm *idtcm, u8 index, u8 pll)
अणु
	अगर (index >= MAX_TOD) अणु
		dev_err(&idtcm->client->dev, "ToD%d not supported", index);
		वापस -EINVAL;
	पूर्ण

	अगर (pll >= MAX_PLL) अणु
		dev_err(&idtcm->client->dev, "Pll%d not supported", pll);
		वापस -EINVAL;
	पूर्ण

	idtcm->channel[index].pll = pll;

	वापस 0;
पूर्ण

अटल पूर्णांक check_and_set_masks(काष्ठा idtcm *idtcm,
			       u16 regaddr,
			       u8 val)
अणु
	पूर्णांक err = 0;

	चयन (regaddr) अणु
	हाल TOD_MASK_ADDR:
		अगर ((val & 0xf0) || !(val & 0x0f)) अणु
			dev_err(&idtcm->client->dev, "Invalid TOD mask 0x%02x", val);
			err = -EINVAL;
		पूर्ण अन्यथा अणु
			idtcm->tod_mask = val;
		पूर्ण
		अवरोध;
	हाल TOD0_PTP_PLL_ADDR:
		err = set_tod_ptp_pll(idtcm, 0, val);
		अवरोध;
	हाल TOD1_PTP_PLL_ADDR:
		err = set_tod_ptp_pll(idtcm, 1, val);
		अवरोध;
	हाल TOD2_PTP_PLL_ADDR:
		err = set_tod_ptp_pll(idtcm, 2, val);
		अवरोध;
	हाल TOD3_PTP_PLL_ADDR:
		err = set_tod_ptp_pll(idtcm, 3, val);
		अवरोध;
	शेष:
		err = set_pll_output_mask(idtcm, regaddr, val);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम display_pll_and_masks(काष्ठा idtcm *idtcm)
अणु
	u8 i;
	u8 mask;

	dev_dbg(&idtcm->client->dev, "tod_mask = 0x%02x", idtcm->tod_mask);

	क्रम (i = 0; i < MAX_TOD; i++) अणु
		mask = 1 << i;

		अगर (mask & idtcm->tod_mask)
			dev_dbg(&idtcm->client->dev,
				"TOD%d pll = %d    output_mask = 0x%04x",
				i, idtcm->channel[i].pll,
				idtcm->channel[i].output_mask);
	पूर्ण
पूर्ण

अटल पूर्णांक idtcm_load_firmware(काष्ठा idtcm *idtcm,
			       काष्ठा device *dev)
अणु
	अक्षर fname[128] = FW_खाताNAME;
	स्थिर काष्ठा firmware *fw;
	काष्ठा idtcm_fwrc *rec;
	u32 regaddr;
	पूर्णांक err;
	s32 len;
	u8 val;
	u8 loaddr;

	अगर (firmware) /* module parameter */
		snम_लिखो(fname, माप(fname), "%s", firmware);

	dev_dbg(&idtcm->client->dev, "requesting firmware '%s'", fname);

	err = request_firmware(&fw, fname, dev);
	अगर (err) अणु
		dev_err(&idtcm->client->dev,
			"Failed at line %d in %s!", __LINE__, __func__);
		वापस err;
	पूर्ण

	dev_dbg(&idtcm->client->dev, "firmware size %zu bytes", fw->size);

	rec = (काष्ठा idtcm_fwrc *) fw->data;

	अगर (contains_full_configuration(fw))
		idtcm_state_machine_reset(idtcm);

	क्रम (len = fw->size; len > 0; len -= माप(*rec)) अणु
		अगर (rec->reserved) अणु
			dev_err(&idtcm->client->dev,
				"bad firmware, reserved field non-zero");
			err = -EINVAL;
		पूर्ण अन्यथा अणु
			regaddr = rec->hiaddr << 8;
			regaddr |= rec->loaddr;

			val = rec->value;
			loaddr = rec->loaddr;

			rec++;

			err = check_and_set_masks(idtcm, regaddr, val);
		पूर्ण

		अगर (err != -EINVAL) अणु
			err = 0;

			/* Top (status रेजिस्टरs) and bottom are पढ़ो-only */
			अगर (regaddr < GPIO_USER_CONTROL || regaddr >= SCRATCH)
				जारी;

			/* Page size 128, last 4 bytes of page skipped */
			अगर ((loaddr > 0x7b && loaddr <= 0x7f) || loaddr > 0xfb)
				जारी;

			err = idtcm_ग_लिखो(idtcm, regaddr, 0, &val, माप(val));
		पूर्ण

		अगर (err)
			जाओ out;
	पूर्ण

	display_pll_and_masks(idtcm);

out:
	release_firmware(fw);
	वापस err;
पूर्ण

अटल पूर्णांक idtcm_output_enable(काष्ठा idtcm_channel *channel,
			       bool enable, अचिन्हित पूर्णांक outn)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	पूर्णांक base;
	पूर्णांक err;
	u8 val;

	base = get_output_base_addr(outn);

	अगर (!(base > 0)) अणु
		dev_err(&idtcm->client->dev,
			"%s - Unsupported out%d", __func__, outn);
		वापस base;
	पूर्ण

	err = idtcm_पढ़ो(idtcm, (u16)base, OUT_CTRL_1, &val, माप(val));
	अगर (err)
		वापस err;

	अगर (enable)
		val |= SQUELCH_DISABLE;
	अन्यथा
		val &= ~SQUELCH_DISABLE;

	वापस idtcm_ग_लिखो(idtcm, (u16)base, OUT_CTRL_1, &val, माप(val));
पूर्ण

अटल पूर्णांक idtcm_output_mask_enable(काष्ठा idtcm_channel *channel,
				    bool enable)
अणु
	u16 mask;
	पूर्णांक err;
	u8 outn;

	mask = channel->output_mask;
	outn = 0;

	जबतक (mask) अणु
		अगर (mask & 0x1) अणु
			err = idtcm_output_enable(channel, enable, outn);
			अगर (err)
				वापस err;
		पूर्ण

		mask >>= 0x1;
		outn++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक idtcm_perout_enable(काष्ठा idtcm_channel *channel,
			       bool enable,
			       काष्ठा ptp_perout_request *perout)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	अचिन्हित पूर्णांक flags = perout->flags;
	काष्ठा बारpec64 ts = अणु0, 0पूर्ण;
	पूर्णांक err;

	अगर (flags == PEROUT_ENABLE_OUTPUT_MASK)
		err = idtcm_output_mask_enable(channel, enable);
	अन्यथा
		err = idtcm_output_enable(channel, enable, perout->index);

	अगर (err) अणु
		dev_err(&idtcm->client->dev, "Unable to set output enable");
		वापस err;
	पूर्ण

	/* Align output to पूर्णांकernal 1 PPS */
	वापस _idtcm_समय_रखो(channel, &ts, SCSR_TOD_WR_TYPE_SEL_DELTA_PLUS);
पूर्ण

अटल पूर्णांक idtcm_get_pll_mode(काष्ठा idtcm_channel *channel,
			      क्रमागत pll_mode *pll_mode)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	पूर्णांक err;
	u8 dpll_mode;

	err = idtcm_पढ़ो(idtcm, channel->dpll_n, DPLL_MODE,
			 &dpll_mode, माप(dpll_mode));
	अगर (err)
		वापस err;

	*pll_mode = (dpll_mode >> PLL_MODE_SHIFT) & PLL_MODE_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक idtcm_set_pll_mode(काष्ठा idtcm_channel *channel,
			      क्रमागत pll_mode pll_mode)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	पूर्णांक err;
	u8 dpll_mode;

	err = idtcm_पढ़ो(idtcm, channel->dpll_n, DPLL_MODE,
			 &dpll_mode, माप(dpll_mode));
	अगर (err)
		वापस err;

	dpll_mode &= ~(PLL_MODE_MASK << PLL_MODE_SHIFT);

	dpll_mode |= (pll_mode << PLL_MODE_SHIFT);

	channel->pll_mode = pll_mode;

	err = idtcm_ग_लिखो(idtcm, channel->dpll_n, DPLL_MODE,
			  &dpll_mode, माप(dpll_mode));
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/* PTP Hardware Clock पूर्णांकerface */

/*
 * Maximum असलolute value क्रम ग_लिखो phase offset in picoseconds
 *
 * Destination चिन्हित रेजिस्टर is 32-bit रेजिस्टर in resolution of 50ps
 *
 * 0x7fffffff * 50 =  2147483647 * 50 = 107374182350
 */
अटल पूर्णांक _idtcm_adjphase(काष्ठा idtcm_channel *channel, s32 delta_ns)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	पूर्णांक err;
	u8 i;
	u8 buf[4] = अणु0पूर्ण;
	s32 phase_50ps;
	s64 offset_ps;

	अगर (channel->pll_mode != PLL_MODE_WRITE_PHASE) अणु
		err = idtcm_set_pll_mode(channel, PLL_MODE_WRITE_PHASE);
		अगर (err)
			वापस err;
	पूर्ण

	offset_ps = (s64)delta_ns * 1000;

	/*
	 * Check क्रम 32-bit चिन्हित max * 50:
	 *
	 * 0x7fffffff * 50 =  2147483647 * 50 = 107374182350
	 */
	अगर (offset_ps > MAX_ABS_WRITE_PHASE_PICOSECONDS)
		offset_ps = MAX_ABS_WRITE_PHASE_PICOSECONDS;
	अन्यथा अगर (offset_ps < -MAX_ABS_WRITE_PHASE_PICOSECONDS)
		offset_ps = -MAX_ABS_WRITE_PHASE_PICOSECONDS;

	phase_50ps = भाग_s64(offset_ps, 50);

	क्रम (i = 0; i < 4; i++) अणु
		buf[i] = phase_50ps & 0xff;
		phase_50ps >>= 8;
	पूर्ण

	err = idtcm_ग_लिखो(idtcm, channel->dpll_phase, DPLL_WR_PHASE,
			  buf, माप(buf));

	वापस err;
पूर्ण

अटल पूर्णांक _idtcm_adjfine(काष्ठा idtcm_channel *channel, दीर्घ scaled_ppm)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	u8 i;
	पूर्णांक err;
	u8 buf[6] = अणु0पूर्ण;
	s64 fcw;

	अगर (channel->pll_mode  != PLL_MODE_WRITE_FREQUENCY) अणु
		err = idtcm_set_pll_mode(channel, PLL_MODE_WRITE_FREQUENCY);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * Frequency Control Word unit is: 1.11 * 10^-10 ppm
	 *
	 * adjfreq:
	 *       ppb * 10^9
	 * FCW = ----------
	 *          111
	 *
	 * adjfine:
	 *       ppm_16 * 5^12
	 * FCW = -------------
	 *         111 * 2^4
	 */

	/* 2 ^ -53 = 1.1102230246251565404236316680908e-16 */
	fcw = scaled_ppm * 244140625ULL;

	fcw = भाग_s64(fcw, 1776);

	क्रम (i = 0; i < 6; i++) अणु
		buf[i] = fcw & 0xff;
		fcw >>= 8;
	पूर्ण

	err = idtcm_ग_लिखो(idtcm, channel->dpll_freq, DPLL_WR_FREQ,
			  buf, माप(buf));

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	काष्ठा idtcm_channel *channel = container_of(ptp, काष्ठा idtcm_channel, caps);
	काष्ठा idtcm *idtcm = channel->idtcm;
	पूर्णांक err;

	mutex_lock(&idtcm->reg_lock);

	err = _idtcm_समय_लो(channel, ts);
	अगर (err)
		dev_err(&idtcm->client->dev, "Failed at line %d in %s!",
			__LINE__, __func__);

	mutex_unlock(&idtcm->reg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_समय_रखो_deprecated(काष्ठा ptp_घड़ी_info *ptp,
				    स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा idtcm_channel *channel = container_of(ptp, काष्ठा idtcm_channel, caps);
	काष्ठा idtcm *idtcm = channel->idtcm;
	पूर्णांक err;

	mutex_lock(&idtcm->reg_lock);

	err = _idtcm_समय_रखो_deprecated(channel, ts);
	अगर (err)
		dev_err(&idtcm->client->dev,
			"Failed at line %d in %s!", __LINE__, __func__);

	mutex_unlock(&idtcm->reg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			 स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा idtcm_channel *channel = container_of(ptp, काष्ठा idtcm_channel, caps);
	काष्ठा idtcm *idtcm = channel->idtcm;
	पूर्णांक err;

	mutex_lock(&idtcm->reg_lock);

	err = _idtcm_समय_रखो(channel, ts, SCSR_TOD_WR_TYPE_SEL_ABSOLUTE);
	अगर (err)
		dev_err(&idtcm->client->dev,
			"Failed at line %d in %s!", __LINE__, __func__);

	mutex_unlock(&idtcm->reg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_adjसमय_deprecated(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा idtcm_channel *channel = container_of(ptp, काष्ठा idtcm_channel, caps);
	काष्ठा idtcm *idtcm = channel->idtcm;
	पूर्णांक err;

	mutex_lock(&idtcm->reg_lock);

	err = _idtcm_adjसमय_deprecated(channel, delta);
	अगर (err)
		dev_err(&idtcm->client->dev,
			"Failed at line %d in %s!", __LINE__, __func__);

	mutex_unlock(&idtcm->reg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा idtcm_channel *channel = container_of(ptp, काष्ठा idtcm_channel, caps);
	काष्ठा idtcm *idtcm = channel->idtcm;
	काष्ठा बारpec64 ts;
	क्रमागत scsr_tod_ग_लिखो_type_sel type;
	पूर्णांक err;

	अगर (असल(delta) < PHASE_PULL_IN_THRESHOLD_NS) अणु
		err = idtcm_करो_phase_pull_in(channel, delta, 0);
		अगर (err)
			dev_err(&idtcm->client->dev,
				"Failed at line %d in %s!", __LINE__, __func__);
		वापस err;
	पूर्ण

	अगर (delta >= 0) अणु
		ts = ns_to_बारpec64(delta);
		type = SCSR_TOD_WR_TYPE_SEL_DELTA_PLUS;
	पूर्ण अन्यथा अणु
		ts = ns_to_बारpec64(-delta);
		type = SCSR_TOD_WR_TYPE_SEL_DELTA_MINUS;
	पूर्ण

	mutex_lock(&idtcm->reg_lock);

	err = _idtcm_समय_रखो(channel, &ts, type);
	अगर (err)
		dev_err(&idtcm->client->dev,
			"Failed at line %d in %s!", __LINE__, __func__);

	mutex_unlock(&idtcm->reg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_adjphase(काष्ठा ptp_घड़ी_info *ptp, s32 delta)
अणु
	काष्ठा idtcm_channel *channel = container_of(ptp, काष्ठा idtcm_channel, caps);
	काष्ठा idtcm *idtcm = channel->idtcm;
	पूर्णांक err;

	mutex_lock(&idtcm->reg_lock);

	err = _idtcm_adjphase(channel, delta);
	अगर (err)
		dev_err(&idtcm->client->dev,
			"Failed at line %d in %s!", __LINE__, __func__);

	mutex_unlock(&idtcm->reg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_adjfine(काष्ठा ptp_घड़ी_info *ptp,  दीर्घ scaled_ppm)
अणु
	काष्ठा idtcm_channel *channel = container_of(ptp, काष्ठा idtcm_channel, caps);
	काष्ठा idtcm *idtcm = channel->idtcm;
	पूर्णांक err;

	mutex_lock(&idtcm->reg_lock);

	err = _idtcm_adjfine(channel, scaled_ppm);
	अगर (err)
		dev_err(&idtcm->client->dev,
			"Failed at line %d in %s!", __LINE__, __func__);

	mutex_unlock(&idtcm->reg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_enable(काष्ठा ptp_घड़ी_info *ptp,
			काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	पूर्णांक err;
	काष्ठा idtcm_channel *channel = container_of(ptp, काष्ठा idtcm_channel, caps);

	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_PEROUT:
		अगर (!on) अणु
			err = idtcm_perout_enable(channel, false, &rq->perout);
			अगर (err)
				dev_err(&channel->idtcm->client->dev,
					"Failed at line %d in %s!",
					__LINE__, __func__);
			वापस err;
		पूर्ण

		/* Only accept a 1-PPS aligned to the second. */
		अगर (rq->perout.start.nsec || rq->perout.period.sec != 1 ||
		    rq->perout.period.nsec)
			वापस -दुस्फल;

		err = idtcm_perout_enable(channel, true, &rq->perout);
		अगर (err)
			dev_err(&channel->idtcm->client->dev,
				"Failed at line %d in %s!", __LINE__, __func__);
		वापस err;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक _enable_pll_tod_sync(काष्ठा idtcm *idtcm,
				u8 pll,
				u8 sync_src,
				u8 qn,
				u8 qn_plus_1)
अणु
	पूर्णांक err;
	u8 val;
	u16 dpll;
	u16 out0 = 0, out1 = 0;

	अगर (qn == 0 && qn_plus_1 == 0)
		वापस 0;

	चयन (pll) अणु
	हाल 0:
		dpll = DPLL_0;
		अगर (qn)
			out0 = OUTPUT_0;
		अगर (qn_plus_1)
			out1 = OUTPUT_1;
		अवरोध;
	हाल 1:
		dpll = DPLL_1;
		अगर (qn)
			out0 = OUTPUT_2;
		अगर (qn_plus_1)
			out1 = OUTPUT_3;
		अवरोध;
	हाल 2:
		dpll = DPLL_2;
		अगर (qn)
			out0 = OUTPUT_4;
		अगर (qn_plus_1)
			out1 = OUTPUT_5;
		अवरोध;
	हाल 3:
		dpll = DPLL_3;
		अगर (qn)
			out0 = OUTPUT_6;
		अगर (qn_plus_1)
			out1 = OUTPUT_7;
		अवरोध;
	हाल 4:
		dpll = DPLL_4;
		अगर (qn)
			out0 = OUTPUT_8;
		अवरोध;
	हाल 5:
		dpll = DPLL_5;
		अगर (qn)
			out0 = OUTPUT_9;
		अगर (qn_plus_1)
			out1 = OUTPUT_8;
		अवरोध;
	हाल 6:
		dpll = DPLL_6;
		अगर (qn)
			out0 = OUTPUT_10;
		अगर (qn_plus_1)
			out1 = OUTPUT_11;
		अवरोध;
	हाल 7:
		dpll = DPLL_7;
		अगर (qn)
			out0 = OUTPUT_11;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * Enable OUTPUT OUT_SYNC.
	 */
	अगर (out0) अणु
		err = idtcm_पढ़ो(idtcm, out0, OUT_CTRL_1, &val, माप(val));
		अगर (err)
			वापस err;

		val &= ~OUT_SYNC_DISABLE;

		err = idtcm_ग_लिखो(idtcm, out0, OUT_CTRL_1, &val, माप(val));
		अगर (err)
			वापस err;
	पूर्ण

	अगर (out1) अणु
		err = idtcm_पढ़ो(idtcm, out1, OUT_CTRL_1, &val, माप(val));
		अगर (err)
			वापस err;

		val &= ~OUT_SYNC_DISABLE;

		err = idtcm_ग_लिखो(idtcm, out1, OUT_CTRL_1, &val, माप(val));
		अगर (err)
			वापस err;
	पूर्ण

	/* enable dpll sync tod pps, must be set beक्रमe dpll_mode */
	err = idtcm_पढ़ो(idtcm, dpll, DPLL_TOD_SYNC_CFG, &val, माप(val));
	अगर (err)
		वापस err;

	val &= ~(TOD_SYNC_SOURCE_MASK << TOD_SYNC_SOURCE_SHIFT);
	val |= (sync_src << TOD_SYNC_SOURCE_SHIFT);
	val |= TOD_SYNC_EN;

	वापस idtcm_ग_लिखो(idtcm, dpll, DPLL_TOD_SYNC_CFG, &val, माप(val));
पूर्ण

अटल पूर्णांक idtcm_enable_tod_sync(काष्ठा idtcm_channel *channel)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	u8 pll;
	u8 sync_src;
	u8 qn;
	u8 qn_plus_1;
	u8 cfg;
	पूर्णांक err = 0;
	u16 output_mask = channel->output_mask;
	u8 out8_mux = 0;
	u8 out11_mux = 0;
	u8 temp;

	/*
	 * set tod_out_sync_enable to 0.
	 */
	err = idtcm_पढ़ो(idtcm, channel->tod_n, TOD_CFG, &cfg, माप(cfg));
	अगर (err)
		वापस err;

	cfg &= ~TOD_OUT_SYNC_ENABLE;

	err = idtcm_ग_लिखो(idtcm, channel->tod_n, TOD_CFG, &cfg, माप(cfg));
	अगर (err)
		वापस err;

	चयन (channel->tod_n) अणु
	हाल TOD_0:
		sync_src = 0;
		अवरोध;
	हाल TOD_1:
		sync_src = 1;
		अवरोध;
	हाल TOD_2:
		sync_src = 2;
		अवरोध;
	हाल TOD_3:
		sync_src = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	err = idtcm_पढ़ो(idtcm, 0, HW_Q8_CTRL_SPARE, &temp, माप(temp));
	अगर (err)
		वापस err;

	अगर ((temp & Q9_TO_Q8_FANOUT_AND_CLOCK_SYNC_ENABLE_MASK) ==
	    Q9_TO_Q8_FANOUT_AND_CLOCK_SYNC_ENABLE_MASK)
		out8_mux = 1;

	err = idtcm_पढ़ो(idtcm, 0, HW_Q11_CTRL_SPARE, &temp, माप(temp));
	अगर (err)
		वापस err;

	अगर ((temp & Q10_TO_Q11_FANOUT_AND_CLOCK_SYNC_ENABLE_MASK) ==
	    Q10_TO_Q11_FANOUT_AND_CLOCK_SYNC_ENABLE_MASK)
		out11_mux = 1;

	क्रम (pll = 0; pll < 8; pll++) अणु
		qn = 0;
		qn_plus_1 = 0;

		अगर (pll < 4) अणु
			/* First 4 pll has 2 outमाला_दो */
			qn = output_mask & 0x1;
			output_mask = output_mask >> 1;
			qn_plus_1 = output_mask & 0x1;
			output_mask = output_mask >> 1;
		पूर्ण अन्यथा अगर (pll == 4) अणु
			अगर (out8_mux == 0) अणु
				qn = output_mask & 0x1;
				output_mask = output_mask >> 1;
			पूर्ण
		पूर्ण अन्यथा अगर (pll == 5) अणु
			अगर (out8_mux) अणु
				qn_plus_1 = output_mask & 0x1;
				output_mask = output_mask >> 1;
			पूर्ण
			qn = output_mask & 0x1;
			output_mask = output_mask >> 1;
		पूर्ण अन्यथा अगर (pll == 6) अणु
			qn = output_mask & 0x1;
			output_mask = output_mask >> 1;
			अगर (out11_mux) अणु
				qn_plus_1 = output_mask & 0x1;
				output_mask = output_mask >> 1;
			पूर्ण
		पूर्ण अन्यथा अगर (pll == 7) अणु
			अगर (out11_mux == 0) अणु
				qn = output_mask & 0x1;
				output_mask = output_mask >> 1;
			पूर्ण
		पूर्ण

		अगर (qn != 0 || qn_plus_1 != 0)
			err = _enable_pll_tod_sync(idtcm, pll, sync_src, qn,
					       qn_plus_1);
		अगर (err)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_enable_tod(काष्ठा idtcm_channel *channel)
अणु
	काष्ठा idtcm *idtcm = channel->idtcm;
	काष्ठा बारpec64 ts = अणु0, 0पूर्ण;
	u8 cfg;
	पूर्णांक err;

	/*
	 * Start the TOD घड़ी ticking.
	 */
	err = idtcm_पढ़ो(idtcm, channel->tod_n, TOD_CFG, &cfg, माप(cfg));
	अगर (err)
		वापस err;

	cfg |= TOD_ENABLE;

	err = idtcm_ग_लिखो(idtcm, channel->tod_n, TOD_CFG, &cfg, माप(cfg));
	अगर (err)
		वापस err;

	अगर (idtcm->deprecated)
		वापस _idtcm_समय_रखो_deprecated(channel, &ts);
	अन्यथा
		वापस _idtcm_समय_रखो(channel, &ts,
				      SCSR_TOD_WR_TYPE_SEL_ABSOLUTE);
पूर्ण

अटल व्योम idtcm_set_version_info(काष्ठा idtcm *idtcm)
अणु
	u8 major;
	u8 minor;
	u8 hotfix;
	u16 product_id;
	u8 hw_rev_id;
	u8 config_select;

	idtcm_पढ़ो_major_release(idtcm, &major);
	idtcm_पढ़ो_minor_release(idtcm, &minor);
	idtcm_पढ़ो_hotfix_release(idtcm, &hotfix);

	idtcm_पढ़ो_product_id(idtcm, &product_id);
	idtcm_पढ़ो_hw_rev_id(idtcm, &hw_rev_id);

	idtcm_पढ़ो_otp_scsr_config_select(idtcm, &config_select);

	snम_लिखो(idtcm->version, माप(idtcm->version), "%u.%u.%u",
		 major, minor, hotfix);

	अगर (idtcm_strverscmp(idtcm->version, "4.8.7") >= 0)
		idtcm->deprecated = 0;
	अन्यथा
		idtcm->deprecated = 1;

	dev_info(&idtcm->client->dev,
		 "%d.%d.%d, Id: 0x%04x  HW Rev: %d  OTP Config Select: %d",
		 major, minor, hotfix,
		 product_id, hw_rev_id, config_select);
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info idtcm_caps = अणु
	.owner		= THIS_MODULE,
	.max_adj	= 244000,
	.n_per_out	= 12,
	.adjphase	= &idtcm_adjphase,
	.adjfine	= &idtcm_adjfine,
	.adjसमय	= &idtcm_adjसमय,
	.समय_लो64	= &idtcm_समय_लो,
	.समय_रखो64	= &idtcm_समय_रखो,
	.enable		= &idtcm_enable,
पूर्ण;

अटल स्थिर काष्ठा ptp_घड़ी_info idtcm_caps_deprecated = अणु
	.owner		= THIS_MODULE,
	.max_adj	= 244000,
	.n_per_out	= 12,
	.adjphase	= &idtcm_adjphase,
	.adjfine	= &idtcm_adjfine,
	.adjसमय	= &idtcm_adjसमय_deprecated,
	.समय_लो64	= &idtcm_समय_लो,
	.समय_रखो64	= &idtcm_समय_रखो_deprecated,
	.enable		= &idtcm_enable,
पूर्ण;

अटल पूर्णांक configure_channel_pll(काष्ठा idtcm_channel *channel)
अणु
	पूर्णांक err = 0;

	चयन (channel->pll) अणु
	हाल 0:
		channel->dpll_freq = DPLL_FREQ_0;
		channel->dpll_n = DPLL_0;
		channel->hw_dpll_n = HW_DPLL_0;
		channel->dpll_phase = DPLL_PHASE_0;
		channel->dpll_ctrl_n = DPLL_CTRL_0;
		channel->dpll_phase_pull_in = DPLL_PHASE_PULL_IN_0;
		अवरोध;
	हाल 1:
		channel->dpll_freq = DPLL_FREQ_1;
		channel->dpll_n = DPLL_1;
		channel->hw_dpll_n = HW_DPLL_1;
		channel->dpll_phase = DPLL_PHASE_1;
		channel->dpll_ctrl_n = DPLL_CTRL_1;
		channel->dpll_phase_pull_in = DPLL_PHASE_PULL_IN_1;
		अवरोध;
	हाल 2:
		channel->dpll_freq = DPLL_FREQ_2;
		channel->dpll_n = DPLL_2;
		channel->hw_dpll_n = HW_DPLL_2;
		channel->dpll_phase = DPLL_PHASE_2;
		channel->dpll_ctrl_n = DPLL_CTRL_2;
		channel->dpll_phase_pull_in = DPLL_PHASE_PULL_IN_2;
		अवरोध;
	हाल 3:
		channel->dpll_freq = DPLL_FREQ_3;
		channel->dpll_n = DPLL_3;
		channel->hw_dpll_n = HW_DPLL_3;
		channel->dpll_phase = DPLL_PHASE_3;
		channel->dpll_ctrl_n = DPLL_CTRL_3;
		channel->dpll_phase_pull_in = DPLL_PHASE_PULL_IN_3;
		अवरोध;
	हाल 4:
		channel->dpll_freq = DPLL_FREQ_4;
		channel->dpll_n = DPLL_4;
		channel->hw_dpll_n = HW_DPLL_4;
		channel->dpll_phase = DPLL_PHASE_4;
		channel->dpll_ctrl_n = DPLL_CTRL_4;
		channel->dpll_phase_pull_in = DPLL_PHASE_PULL_IN_4;
		अवरोध;
	हाल 5:
		channel->dpll_freq = DPLL_FREQ_5;
		channel->dpll_n = DPLL_5;
		channel->hw_dpll_n = HW_DPLL_5;
		channel->dpll_phase = DPLL_PHASE_5;
		channel->dpll_ctrl_n = DPLL_CTRL_5;
		channel->dpll_phase_pull_in = DPLL_PHASE_PULL_IN_5;
		अवरोध;
	हाल 6:
		channel->dpll_freq = DPLL_FREQ_6;
		channel->dpll_n = DPLL_6;
		channel->hw_dpll_n = HW_DPLL_6;
		channel->dpll_phase = DPLL_PHASE_6;
		channel->dpll_ctrl_n = DPLL_CTRL_6;
		channel->dpll_phase_pull_in = DPLL_PHASE_PULL_IN_6;
		अवरोध;
	हाल 7:
		channel->dpll_freq = DPLL_FREQ_7;
		channel->dpll_n = DPLL_7;
		channel->hw_dpll_n = HW_DPLL_7;
		channel->dpll_phase = DPLL_PHASE_7;
		channel->dpll_ctrl_n = DPLL_CTRL_7;
		channel->dpll_phase_pull_in = DPLL_PHASE_PULL_IN_7;
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक idtcm_enable_channel(काष्ठा idtcm *idtcm, u32 index)
अणु
	काष्ठा idtcm_channel *channel;
	पूर्णांक err;

	अगर (!(index < MAX_TOD))
		वापस -EINVAL;

	channel = &idtcm->channel[index];

	/* Set pll addresses */
	err = configure_channel_pll(channel);
	अगर (err)
		वापस err;

	/* Set tod addresses */
	चयन (index) अणु
	हाल 0:
		channel->tod_पढ़ो_primary = TOD_READ_PRIMARY_0;
		channel->tod_ग_लिखो = TOD_WRITE_0;
		channel->tod_n = TOD_0;
		अवरोध;
	हाल 1:
		channel->tod_पढ़ो_primary = TOD_READ_PRIMARY_1;
		channel->tod_ग_लिखो = TOD_WRITE_1;
		channel->tod_n = TOD_1;
		अवरोध;
	हाल 2:
		channel->tod_पढ़ो_primary = TOD_READ_PRIMARY_2;
		channel->tod_ग_लिखो = TOD_WRITE_2;
		channel->tod_n = TOD_2;
		अवरोध;
	हाल 3:
		channel->tod_पढ़ो_primary = TOD_READ_PRIMARY_3;
		channel->tod_ग_लिखो = TOD_WRITE_3;
		channel->tod_n = TOD_3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	channel->idtcm = idtcm;

	अगर (idtcm->deprecated)
		channel->caps = idtcm_caps_deprecated;
	अन्यथा
		channel->caps = idtcm_caps;

	snम_लिखो(channel->caps.name, माप(channel->caps.name),
		 "IDT CM TOD%u", index);

	अगर (!idtcm->deprecated) अणु
		err = idtcm_enable_tod_sync(channel);
		अगर (err) अणु
			dev_err(&idtcm->client->dev,
				"Failed at line %d in %s!", __LINE__, __func__);
			वापस err;
		पूर्ण
	पूर्ण

	/* Sync pll mode with hardware */
	err = idtcm_get_pll_mode(channel, &channel->pll_mode);
	अगर (err) अणु
		dev_err(&idtcm->client->dev,
			"Error: %s - Unable to read pll mode", __func__);
		वापस err;
	पूर्ण

	err = idtcm_enable_tod(channel);
	अगर (err) अणु
		dev_err(&idtcm->client->dev,
			"Failed at line %d in %s!", __LINE__, __func__);
		वापस err;
	पूर्ण

	channel->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&channel->caps, शून्य);

	अगर (IS_ERR(channel->ptp_घड़ी)) अणु
		err = PTR_ERR(channel->ptp_घड़ी);
		channel->ptp_घड़ी = शून्य;
		वापस err;
	पूर्ण

	अगर (!channel->ptp_घड़ी)
		वापस -ENOTSUPP;

	dev_info(&idtcm->client->dev, "PLL%d registered as ptp%d",
		 index, channel->ptp_घड़ी->index);

	वापस 0;
पूर्ण

अटल व्योम ptp_घड़ी_unरेजिस्टर_all(काष्ठा idtcm *idtcm)
अणु
	u8 i;
	काष्ठा idtcm_channel *channel;

	क्रम (i = 0; i < MAX_TOD; i++) अणु
		channel = &idtcm->channel[i];

		अगर (channel->ptp_घड़ी)
			ptp_घड़ी_unरेजिस्टर(channel->ptp_घड़ी);
	पूर्ण
पूर्ण

अटल व्योम set_शेष_masks(काष्ठा idtcm *idtcm)
अणु
	idtcm->tod_mask = DEFAULT_TOD_MASK;

	idtcm->channel[0].pll = DEFAULT_TOD0_PTP_PLL;
	idtcm->channel[1].pll = DEFAULT_TOD1_PTP_PLL;
	idtcm->channel[2].pll = DEFAULT_TOD2_PTP_PLL;
	idtcm->channel[3].pll = DEFAULT_TOD3_PTP_PLL;

	idtcm->channel[0].output_mask = DEFAULT_OUTPUT_MASK_PLL0;
	idtcm->channel[1].output_mask = DEFAULT_OUTPUT_MASK_PLL1;
	idtcm->channel[2].output_mask = DEFAULT_OUTPUT_MASK_PLL2;
	idtcm->channel[3].output_mask = DEFAULT_OUTPUT_MASK_PLL3;
पूर्ण

अटल पूर्णांक idtcm_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा idtcm *idtcm;
	पूर्णांक err;
	u8 i;

	/* Unused क्रम now */
	(व्योम)id;

	idtcm = devm_kzalloc(&client->dev, माप(काष्ठा idtcm), GFP_KERNEL);

	अगर (!idtcm)
		वापस -ENOMEM;

	idtcm->client = client;
	idtcm->page_offset = 0xff;
	idtcm->calculate_overhead_flag = 0;

	set_शेष_masks(idtcm);

	mutex_init(&idtcm->reg_lock);
	mutex_lock(&idtcm->reg_lock);

	idtcm_set_version_info(idtcm);

	err = idtcm_load_firmware(idtcm, &client->dev);
	अगर (err)
		dev_warn(&idtcm->client->dev, "loading firmware failed with %d", err);

	रुको_क्रम_chip_पढ़ोy(idtcm);

	अगर (idtcm->tod_mask) अणु
		क्रम (i = 0; i < MAX_TOD; i++) अणु
			अगर (idtcm->tod_mask & (1 << i)) अणु
				err = idtcm_enable_channel(idtcm, i);
				अगर (err) अणु
					dev_err(&idtcm->client->dev,
						"idtcm_enable_channel %d failed!", i);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&idtcm->client->dev,
			"no PLLs flagged as PHCs, nothing to do");
		err = -ENODEV;
	पूर्ण

	mutex_unlock(&idtcm->reg_lock);

	अगर (err) अणु
		ptp_घड़ी_unरेजिस्टर_all(idtcm);
		वापस err;
	पूर्ण

	i2c_set_clientdata(client, idtcm);

	वापस 0;
पूर्ण

अटल पूर्णांक idtcm_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा idtcm *idtcm = i2c_get_clientdata(client);

	ptp_घड़ी_unरेजिस्टर_all(idtcm);

	mutex_destroy(&idtcm->reg_lock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id idtcm_dt_id[] = अणु
	अणु .compatible = "idt,8a34000" पूर्ण,
	अणु .compatible = "idt,8a34001" पूर्ण,
	अणु .compatible = "idt,8a34002" पूर्ण,
	अणु .compatible = "idt,8a34003" पूर्ण,
	अणु .compatible = "idt,8a34004" पूर्ण,
	अणु .compatible = "idt,8a34005" पूर्ण,
	अणु .compatible = "idt,8a34006" पूर्ण,
	अणु .compatible = "idt,8a34007" पूर्ण,
	अणु .compatible = "idt,8a34008" पूर्ण,
	अणु .compatible = "idt,8a34009" पूर्ण,
	अणु .compatible = "idt,8a34010" पूर्ण,
	अणु .compatible = "idt,8a34011" पूर्ण,
	अणु .compatible = "idt,8a34012" पूर्ण,
	अणु .compatible = "idt,8a34013" पूर्ण,
	अणु .compatible = "idt,8a34014" पूर्ण,
	अणु .compatible = "idt,8a34015" पूर्ण,
	अणु .compatible = "idt,8a34016" पूर्ण,
	अणु .compatible = "idt,8a34017" पूर्ण,
	अणु .compatible = "idt,8a34018" पूर्ण,
	अणु .compatible = "idt,8a34019" पूर्ण,
	अणु .compatible = "idt,8a34040" पूर्ण,
	अणु .compatible = "idt,8a34041" पूर्ण,
	अणु .compatible = "idt,8a34042" पूर्ण,
	अणु .compatible = "idt,8a34043" पूर्ण,
	अणु .compatible = "idt,8a34044" पूर्ण,
	अणु .compatible = "idt,8a34045" पूर्ण,
	अणु .compatible = "idt,8a34046" पूर्ण,
	अणु .compatible = "idt,8a34047" पूर्ण,
	अणु .compatible = "idt,8a34048" पूर्ण,
	अणु .compatible = "idt,8a34049" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, idtcm_dt_id);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id idtcm_i2c_id[] = अणु
	अणु "8a34000" पूर्ण,
	अणु "8a34001" पूर्ण,
	अणु "8a34002" पूर्ण,
	अणु "8a34003" पूर्ण,
	अणु "8a34004" पूर्ण,
	अणु "8a34005" पूर्ण,
	अणु "8a34006" पूर्ण,
	अणु "8a34007" पूर्ण,
	अणु "8a34008" पूर्ण,
	अणु "8a34009" पूर्ण,
	अणु "8a34010" पूर्ण,
	अणु "8a34011" पूर्ण,
	अणु "8a34012" पूर्ण,
	अणु "8a34013" पूर्ण,
	अणु "8a34014" पूर्ण,
	अणु "8a34015" पूर्ण,
	अणु "8a34016" पूर्ण,
	अणु "8a34017" पूर्ण,
	अणु "8a34018" पूर्ण,
	अणु "8a34019" पूर्ण,
	अणु "8a34040" पूर्ण,
	अणु "8a34041" पूर्ण,
	अणु "8a34042" पूर्ण,
	अणु "8a34043" पूर्ण,
	अणु "8a34044" पूर्ण,
	अणु "8a34045" पूर्ण,
	अणु "8a34046" पूर्ण,
	अणु "8a34047" पूर्ण,
	अणु "8a34048" पूर्ण,
	अणु "8a34049" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, idtcm_i2c_id);

अटल काष्ठा i2c_driver idtcm_driver = अणु
	.driver = अणु
		.of_match_table	= of_match_ptr(idtcm_dt_id),
		.name		= "idtcm",
	पूर्ण,
	.probe		= idtcm_probe,
	.हटाओ		= idtcm_हटाओ,
	.id_table	= idtcm_i2c_id,
पूर्ण;

module_i2c_driver(idtcm_driver);
