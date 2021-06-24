<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2018 Integrated Device Technology, Inc
//

#घोषणा pr_fmt(fmt) "IDT_82p33xxx: " fmt

#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयkeeping.h>
#समावेश <linux/bitops.h>

#समावेश "ptp_private.h"
#समावेश "ptp_idt82p33.h"

MODULE_DESCRIPTION("Driver for IDT 82p33xxx clock devices");
MODULE_AUTHOR("IDT support-1588 <IDT-support-1588@lm.renesas.com>");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FW_खाताNAME);

/* Module Parameters */
अटल u32 sync_tod_समयout = SYNC_TOD_TIMEOUT_SEC;
module_param(sync_tod_समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(sync_tod_समयout,
"duration in second to keep SYNC_TOD on (set to 0 to keep it always on)");

अटल u32 phase_snap_threshold = SNAP_THRESHOLD_NS;
module_param(phase_snap_threshold, uपूर्णांक, 0);
MODULE_PARM_DESC(phase_snap_threshold,
"threshold (150000ns by default) below which adjtime would ignore");

अटल व्योम idt82p33_byte_array_to_बारpec(काष्ठा बारpec64 *ts,
					    u8 buf[TOD_BYTE_COUNT])
अणु
	समय64_t sec;
	s32 nsec;
	u8 i;

	nsec = buf[3];
	क्रम (i = 0; i < 3; i++) अणु
		nsec <<= 8;
		nsec |= buf[2 - i];
	पूर्ण

	sec = buf[9];
	क्रम (i = 0; i < 5; i++) अणु
		sec <<= 8;
		sec |= buf[8 - i];
	पूर्ण

	ts->tv_sec = sec;
	ts->tv_nsec = nsec;
पूर्ण

अटल व्योम idt82p33_बारpec_to_byte_array(काष्ठा बारpec64 स्थिर *ts,
					    u8 buf[TOD_BYTE_COUNT])
अणु
	समय64_t sec;
	s32 nsec;
	u8 i;

	nsec = ts->tv_nsec;
	sec = ts->tv_sec;

	क्रम (i = 0; i < 4; i++) अणु
		buf[i] = nsec & 0xff;
		nsec >>= 8;
	पूर्ण

	क्रम (i = 4; i < TOD_BYTE_COUNT; i++) अणु
		buf[i] = sec & 0xff;
		sec >>= 8;
	पूर्ण
पूर्ण

अटल पूर्णांक idt82p33_xfer_पढ़ो(काष्ठा idt82p33 *idt82p33,
			      अचिन्हित अक्षर regaddr,
			      अचिन्हित अक्षर *buf,
			      अचिन्हित पूर्णांक count)
अणु
	काष्ठा i2c_client *client = idt82p33->client;
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
		dev_err(&client->dev, "i2c_transfer returned %d\n", cnt);
		वापस cnt;
	पूर्ण अन्यथा अगर (cnt != 2) अणु
		dev_err(&client->dev,
			"i2c_transfer sent only %d of %d messages\n", cnt, 2);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक idt82p33_xfer_ग_लिखो(काष्ठा idt82p33 *idt82p33,
			       u8 regaddr,
			       u8 *buf,
			       u16 count)
अणु
	काष्ठा i2c_client *client = idt82p33->client;
	/* we add 1 byte क्रम device रेजिस्टर */
	u8 msg[IDT82P33_MAX_WRITE_COUNT + 1];
	पूर्णांक err;

	अगर (count > IDT82P33_MAX_WRITE_COUNT)
		वापस -EINVAL;

	msg[0] = regaddr;
	स_नकल(&msg[1], buf, count);

	err = i2c_master_send(client, msg, count + 1);
	अगर (err < 0) अणु
		dev_err(&client->dev, "i2c_master_send returned %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक idt82p33_page_offset(काष्ठा idt82p33 *idt82p33, अचिन्हित अक्षर val)
अणु
	पूर्णांक err;

	अगर (idt82p33->page_offset == val)
		वापस 0;

	err = idt82p33_xfer_ग_लिखो(idt82p33, PAGE_ADDR, &val, माप(val));
	अगर (err)
		dev_err(&idt82p33->client->dev,
			"failed to set page offset %d\n", val);
	अन्यथा
		idt82p33->page_offset = val;

	वापस err;
पूर्ण

अटल पूर्णांक idt82p33_rdwr(काष्ठा idt82p33 *idt82p33, अचिन्हित पूर्णांक regaddr,
			 अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक count, bool ग_लिखो)
अणु
	u8 offset, page;
	पूर्णांक err;

	page = _PAGE(regaddr);
	offset = _OFFSET(regaddr);

	err = idt82p33_page_offset(idt82p33, page);
	अगर (err)
		वापस err;

	अगर (ग_लिखो)
		वापस idt82p33_xfer_ग_लिखो(idt82p33, offset, buf, count);

	वापस idt82p33_xfer_पढ़ो(idt82p33, offset, buf, count);
पूर्ण

अटल पूर्णांक idt82p33_पढ़ो(काष्ठा idt82p33 *idt82p33, अचिन्हित पूर्णांक regaddr,
			अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक count)
अणु
	वापस idt82p33_rdwr(idt82p33, regaddr, buf, count, false);
पूर्ण

अटल पूर्णांक idt82p33_ग_लिखो(काष्ठा idt82p33 *idt82p33, अचिन्हित पूर्णांक regaddr,
			अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक count)
अणु
	वापस idt82p33_rdwr(idt82p33, regaddr, buf, count, true);
पूर्ण

अटल पूर्णांक idt82p33_dpll_set_mode(काष्ठा idt82p33_channel *channel,
				  क्रमागत pll_mode mode)
अणु
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	u8 dpll_mode;
	पूर्णांक err;

	अगर (channel->pll_mode == mode)
		वापस 0;

	err = idt82p33_पढ़ो(idt82p33, channel->dpll_mode_cnfg,
			    &dpll_mode, माप(dpll_mode));
	अगर (err)
		वापस err;

	dpll_mode &= ~(PLL_MODE_MASK << PLL_MODE_SHIFT);

	dpll_mode |= (mode << PLL_MODE_SHIFT);

	err = idt82p33_ग_लिखो(idt82p33, channel->dpll_mode_cnfg,
			     &dpll_mode, माप(dpll_mode));
	अगर (err)
		वापस err;

	channel->pll_mode = dpll_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक _idt82p33_समय_लो(काष्ठा idt82p33_channel *channel,
			     काष्ठा बारpec64 *ts)
अणु
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	u8 buf[TOD_BYTE_COUNT];
	u8 trigger;
	पूर्णांक err;

	trigger = TOD_TRIGGER(HW_TOD_WR_TRIG_SEL_MSB_TOD_CNFG,
			      HW_TOD_RD_TRIG_SEL_LSB_TOD_STS);


	err = idt82p33_ग_लिखो(idt82p33, channel->dpll_tod_trigger,
			     &trigger, माप(trigger));

	अगर (err)
		वापस err;

	अगर (idt82p33->calculate_overhead_flag)
		idt82p33->start_समय = kसमय_get_raw();

	err = idt82p33_पढ़ो(idt82p33, channel->dpll_tod_sts, buf, माप(buf));

	अगर (err)
		वापस err;

	idt82p33_byte_array_to_बारpec(ts, buf);

	वापस 0;
पूर्ण

/*
 *   TOD Trigger:
 *   Bits[7:4] Write 0x9, MSB ग_लिखो
 *   Bits[3:0] Read 0x9, LSB पढ़ो
 */

अटल पूर्णांक _idt82p33_समय_रखो(काष्ठा idt82p33_channel *channel,
			     काष्ठा बारpec64 स्थिर *ts)
अणु
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	काष्ठा बारpec64 local_ts = *ts;
	अक्षर buf[TOD_BYTE_COUNT];
	s64 dynamic_overhead_ns;
	अचिन्हित अक्षर trigger;
	पूर्णांक err;
	u8 i;

	trigger = TOD_TRIGGER(HW_TOD_WR_TRIG_SEL_MSB_TOD_CNFG,
			      HW_TOD_RD_TRIG_SEL_LSB_TOD_STS);

	err = idt82p33_ग_लिखो(idt82p33, channel->dpll_tod_trigger,
			&trigger, माप(trigger));

	अगर (err)
		वापस err;

	अगर (idt82p33->calculate_overhead_flag) अणु
		dynamic_overhead_ns = kसमय_प्रकारo_ns(kसमय_get_raw())
					- kसमय_प्रकारo_ns(idt82p33->start_समय);

		बारpec64_add_ns(&local_ts, dynamic_overhead_ns);

		idt82p33->calculate_overhead_flag = 0;
	पूर्ण

	idt82p33_बारpec_to_byte_array(&local_ts, buf);

	/*
	 * Store the new समय value.
	 */
	क्रम (i = 0; i < TOD_BYTE_COUNT; i++) अणु
		err = idt82p33_ग_लिखो(idt82p33, channel->dpll_tod_cnfg + i,
				     &buf[i], माप(buf[i]));
		अगर (err)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक _idt82p33_adjसमय(काष्ठा idt82p33_channel *channel, s64 delta_ns)
अणु
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	काष्ठा बारpec64 ts;
	s64 now_ns;
	पूर्णांक err;

	idt82p33->calculate_overhead_flag = 1;

	err = _idt82p33_समय_लो(channel, &ts);

	अगर (err)
		वापस err;

	now_ns = बारpec64_to_ns(&ts);
	now_ns += delta_ns + idt82p33->tod_ग_लिखो_overhead_ns;

	ts = ns_to_बारpec64(now_ns);

	err = _idt82p33_समय_रखो(channel, &ts);

	वापस err;
पूर्ण

अटल पूर्णांक _idt82p33_adjfine(काष्ठा idt82p33_channel *channel, दीर्घ scaled_ppm)
अणु
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	अचिन्हित अक्षर buf[5] = अणु0पूर्ण;
	पूर्णांक err, i;
	s64 fcw;

	अगर (scaled_ppm == channel->current_freq_ppb)
		वापस 0;

	/*
	 * Frequency Control Word unit is: 1.68 * 10^-10 ppm
	 *
	 * adjfreq:
	 *       ppb * 10^9
	 * FCW = ----------
	 *          168
	 *
	 * adjfine:
	 *       scaled_ppm * 5^12
	 * FCW = -------------
	 *         168 * 2^4
	 */

	fcw = scaled_ppm * 244140625ULL;
	fcw = भाग_s64(fcw, 2688);

	क्रम (i = 0; i < 5; i++) अणु
		buf[i] = fcw & 0xff;
		fcw >>= 8;
	पूर्ण

	err = idt82p33_dpll_set_mode(channel, PLL_MODE_DCO);

	अगर (err)
		वापस err;

	err = idt82p33_ग_लिखो(idt82p33, channel->dpll_freq_cnfg,
			     buf, माप(buf));

	अगर (err == 0)
		channel->current_freq_ppb = scaled_ppm;

	वापस err;
पूर्ण

अटल पूर्णांक idt82p33_measure_one_byte_ग_लिखो_overhead(
		काष्ठा idt82p33_channel *channel, s64 *overhead_ns)
अणु
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	kसमय_प्रकार start, stop;
	s64 total_ns;
	u8 trigger;
	पूर्णांक err;
	u8 i;

	total_ns = 0;
	*overhead_ns = 0;
	trigger = TOD_TRIGGER(HW_TOD_WR_TRIG_SEL_MSB_TOD_CNFG,
			      HW_TOD_RD_TRIG_SEL_LSB_TOD_STS);

	क्रम (i = 0; i < MAX_MEASURMENT_COUNT; i++) अणु

		start = kसमय_get_raw();

		err = idt82p33_ग_लिखो(idt82p33, channel->dpll_tod_trigger,
				     &trigger, माप(trigger));

		stop = kसमय_get_raw();

		अगर (err)
			वापस err;

		total_ns += kसमय_प्रकारo_ns(stop) - kसमय_प्रकारo_ns(start);
	पूर्ण

	*overhead_ns = भाग_s64(total_ns, MAX_MEASURMENT_COUNT);

	वापस err;
पूर्ण

अटल पूर्णांक idt82p33_measure_tod_ग_लिखो_9_byte_overhead(
			काष्ठा idt82p33_channel *channel)
अणु
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	u8 buf[TOD_BYTE_COUNT];
	kसमय_प्रकार start, stop;
	s64 total_ns;
	पूर्णांक err = 0;
	u8 i, j;

	total_ns = 0;
	idt82p33->tod_ग_लिखो_overhead_ns = 0;

	क्रम (i = 0; i < MAX_MEASURMENT_COUNT; i++) अणु

		start = kसमय_get_raw();

		/* Need one less byte क्रम applicable overhead */
		क्रम (j = 0; j < (TOD_BYTE_COUNT - 1); j++) अणु
			err = idt82p33_ग_लिखो(idt82p33,
					     channel->dpll_tod_cnfg + i,
					     &buf[i], माप(buf[i]));
			अगर (err)
				वापस err;
		पूर्ण

		stop = kसमय_get_raw();

		total_ns += kसमय_प्रकारo_ns(stop) - kसमय_प्रकारo_ns(start);
	पूर्ण

	idt82p33->tod_ग_लिखो_overhead_ns = भाग_s64(total_ns,
						  MAX_MEASURMENT_COUNT);

	वापस err;
पूर्ण

अटल पूर्णांक idt82p33_measure_समय_रखो_समय_लो_gap_overhead(
		काष्ठा idt82p33_channel *channel, s64 *overhead_ns)
अणु
	काष्ठा बारpec64 ts1 = अणु0, 0पूर्ण;
	काष्ठा बारpec64 ts2;
	पूर्णांक err;

	*overhead_ns = 0;

	err = _idt82p33_समय_रखो(channel, &ts1);

	अगर (err)
		वापस err;

	err = _idt82p33_समय_लो(channel, &ts2);

	अगर (!err)
		*overhead_ns = बारpec64_to_ns(&ts2) - बारpec64_to_ns(&ts1);

	वापस err;
पूर्ण

अटल पूर्णांक idt82p33_measure_tod_ग_लिखो_overhead(काष्ठा idt82p33_channel *channel)
अणु
	s64 trailing_overhead_ns, one_byte_ग_लिखो_ns, gap_ns;
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	पूर्णांक err;

	idt82p33->tod_ग_लिखो_overhead_ns = 0;

	err = idt82p33_measure_समय_रखो_समय_लो_gap_overhead(channel, &gap_ns);

	अगर (err) अणु
		dev_err(&idt82p33->client->dev,
			"Failed in %s with err %d!\n", __func__, err);
		वापस err;
	पूर्ण

	err = idt82p33_measure_one_byte_ग_लिखो_overhead(channel,
						       &one_byte_ग_लिखो_ns);

	अगर (err)
		वापस err;

	err = idt82p33_measure_tod_ग_लिखो_9_byte_overhead(channel);

	अगर (err)
		वापस err;

	trailing_overhead_ns = gap_ns - (2 * one_byte_ग_लिखो_ns);

	idt82p33->tod_ग_लिखो_overhead_ns -= trailing_overhead_ns;

	वापस err;
पूर्ण

अटल पूर्णांक idt82p33_check_and_set_masks(काष्ठा idt82p33 *idt82p33,
					u8 page,
					u8 offset,
					u8 val)
अणु
	पूर्णांक err = 0;

	अगर (page == PLLMASK_ADDR_HI && offset == PLLMASK_ADDR_LO) अणु
		अगर ((val & 0xfc) || !(val & 0x3)) अणु
			dev_err(&idt82p33->client->dev,
				"Invalid PLL mask 0x%hhx\n", val);
			err = -EINVAL;
		पूर्ण अन्यथा अणु
			idt82p33->pll_mask = val;
		पूर्ण
	पूर्ण अन्यथा अगर (page == PLL0_OUTMASK_ADDR_HI &&
		offset == PLL0_OUTMASK_ADDR_LO) अणु
		idt82p33->channel[0].output_mask = val;
	पूर्ण अन्यथा अगर (page == PLL1_OUTMASK_ADDR_HI &&
		offset == PLL1_OUTMASK_ADDR_LO) अणु
		idt82p33->channel[1].output_mask = val;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम idt82p33_display_masks(काष्ठा idt82p33 *idt82p33)
अणु
	u8 mask, i;

	dev_info(&idt82p33->client->dev,
		 "pllmask = 0x%02x\n", idt82p33->pll_mask);

	क्रम (i = 0; i < MAX_PHC_PLL; i++) अणु
		mask = 1 << i;

		अगर (mask & idt82p33->pll_mask)
			dev_info(&idt82p33->client->dev,
				 "PLL%d output_mask = 0x%04x\n",
				 i, idt82p33->channel[i].output_mask);
	पूर्ण
पूर्ण

अटल पूर्णांक idt82p33_sync_tod(काष्ठा idt82p33_channel *channel, bool enable)
अणु
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	u8 sync_cnfg;
	पूर्णांक err;

	/* Turn it off after sync_tod_समयout seconds */
	अगर (enable && sync_tod_समयout)
		ptp_schedule_worker(channel->ptp_घड़ी,
				    sync_tod_समयout * HZ);

	err = idt82p33_पढ़ो(idt82p33, channel->dpll_sync_cnfg,
			    &sync_cnfg, माप(sync_cnfg));
	अगर (err)
		वापस err;

	sync_cnfg &= ~SYNC_TOD;
	अगर (enable)
		sync_cnfg |= SYNC_TOD;

	वापस idt82p33_ग_लिखो(idt82p33, channel->dpll_sync_cnfg,
			      &sync_cnfg, माप(sync_cnfg));
पूर्ण

अटल दीर्घ idt82p33_sync_tod_work_handler(काष्ठा ptp_घड़ी_info *ptp)
अणु
	काष्ठा idt82p33_channel *channel =
			container_of(ptp, काष्ठा idt82p33_channel, caps);
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;

	mutex_lock(&idt82p33->reg_lock);

	(व्योम)idt82p33_sync_tod(channel, false);

	mutex_unlock(&idt82p33->reg_lock);

	/* Return a negative value here to not reschedule */
	वापस -1;
पूर्ण

अटल पूर्णांक idt82p33_output_enable(काष्ठा idt82p33_channel *channel,
				  bool enable, अचिन्हित पूर्णांक outn)
अणु
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	पूर्णांक err;
	u8 val;

	err = idt82p33_पढ़ो(idt82p33, OUT_MUX_CNFG(outn), &val, माप(val));
	अगर (err)
		वापस err;
	अगर (enable)
		val &= ~SQUELCH_ENABLE;
	अन्यथा
		val |= SQUELCH_ENABLE;

	वापस idt82p33_ग_लिखो(idt82p33, OUT_MUX_CNFG(outn), &val, माप(val));
पूर्ण

अटल पूर्णांक idt82p33_output_mask_enable(काष्ठा idt82p33_channel *channel,
				       bool enable)
अणु
	u16 mask;
	पूर्णांक err;
	u8 outn;

	mask = channel->output_mask;
	outn = 0;

	जबतक (mask) अणु
		अगर (mask & 0x1) अणु
			err = idt82p33_output_enable(channel, enable, outn);
			अगर (err)
				वापस err;
		पूर्ण

		mask >>= 0x1;
		outn++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक idt82p33_perout_enable(काष्ठा idt82p33_channel *channel,
				  bool enable,
				  काष्ठा ptp_perout_request *perout)
अणु
	अचिन्हित पूर्णांक flags = perout->flags;

	/* Enable/disable output based on output_mask */
	अगर (flags == PEROUT_ENABLE_OUTPUT_MASK)
		वापस idt82p33_output_mask_enable(channel, enable);

	/* Enable/disable inभागidual output instead */
	वापस idt82p33_output_enable(channel, enable, perout->index);
पूर्ण

अटल पूर्णांक idt82p33_enable_tod(काष्ठा idt82p33_channel *channel)
अणु
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	काष्ठा बारpec64 ts = अणु0, 0पूर्ण;
	पूर्णांक err;
	u8 val;

	val = 0;
	err = idt82p33_ग_लिखो(idt82p33, channel->dpll_input_mode_cnfg,
			     &val, माप(val));
	अगर (err)
		वापस err;

	err = idt82p33_measure_tod_ग_लिखो_overhead(channel);

	अगर (err) अणु
		dev_err(&idt82p33->client->dev,
			"Failed in %s with err %d!\n", __func__, err);
		वापस err;
	पूर्ण

	err = _idt82p33_समय_रखो(channel, &ts);

	अगर (err)
		वापस err;

	वापस idt82p33_sync_tod(channel, true);
पूर्ण

अटल व्योम idt82p33_ptp_घड़ी_unरेजिस्टर_all(काष्ठा idt82p33 *idt82p33)
अणु
	काष्ठा idt82p33_channel *channel;
	u8 i;

	क्रम (i = 0; i < MAX_PHC_PLL; i++) अणु

		channel = &idt82p33->channel[i];

		अगर (channel->ptp_घड़ी)
			ptp_घड़ी_unरेजिस्टर(channel->ptp_घड़ी);
	पूर्ण
पूर्ण

अटल पूर्णांक idt82p33_enable(काष्ठा ptp_घड़ी_info *ptp,
			 काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा idt82p33_channel *channel =
			container_of(ptp, काष्ठा idt82p33_channel, caps);
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	पूर्णांक err;

	err = -EOPNOTSUPP;

	mutex_lock(&idt82p33->reg_lock);

	अगर (rq->type == PTP_CLK_REQ_PEROUT) अणु
		अगर (!on)
			err = idt82p33_perout_enable(channel, false,
						     &rq->perout);
		/* Only accept a 1-PPS aligned to the second. */
		अन्यथा अगर (rq->perout.start.nsec || rq->perout.period.sec != 1 ||
		    rq->perout.period.nsec) अणु
			err = -दुस्फल;
		पूर्ण अन्यथा
			err = idt82p33_perout_enable(channel, true,
						     &rq->perout);
	पूर्ण

	mutex_unlock(&idt82p33->reg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक idt82p33_adjग_लिखोphase(काष्ठा ptp_घड़ी_info *ptp, s32 offset_ns)
अणु
	काष्ठा idt82p33_channel *channel =
		container_of(ptp, काष्ठा idt82p33_channel, caps);
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	s64 offset_regval, offset_fs;
	u8 val[4] = अणु0पूर्ण;
	पूर्णांक err;

	offset_fs = (s64)(-offset_ns) * 1000000;

	अगर (offset_fs > WRITE_PHASE_OFFSET_LIMIT)
		offset_fs = WRITE_PHASE_OFFSET_LIMIT;
	अन्यथा अगर (offset_fs < -WRITE_PHASE_OFFSET_LIMIT)
		offset_fs = -WRITE_PHASE_OFFSET_LIMIT;

	/* Convert from phaseoffset_fs to रेजिस्टर value */
	offset_regval = भाग_s64(offset_fs * 1000, IDT_T0DPLL_PHASE_RESOL);

	val[0] = offset_regval & 0xFF;
	val[1] = (offset_regval >> 8) & 0xFF;
	val[2] = (offset_regval >> 16) & 0xFF;
	val[3] = (offset_regval >> 24) & 0x1F;
	val[3] |= PH_OFFSET_EN;

	mutex_lock(&idt82p33->reg_lock);

	err = idt82p33_dpll_set_mode(channel, PLL_MODE_WPH);
	अगर (err) अणु
		dev_err(&idt82p33->client->dev,
			"Failed in %s with err %d!\n", __func__, err);
		जाओ out;
	पूर्ण

	err = idt82p33_ग_लिखो(idt82p33, channel->dpll_phase_cnfg, val,
			     माप(val));

out:
	mutex_unlock(&idt82p33->reg_lock);
	वापस err;
पूर्ण

अटल पूर्णांक idt82p33_adjfine(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm)
अणु
	काष्ठा idt82p33_channel *channel =
			container_of(ptp, काष्ठा idt82p33_channel, caps);
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	पूर्णांक err;

	mutex_lock(&idt82p33->reg_lock);
	err = _idt82p33_adjfine(channel, scaled_ppm);
	अगर (err)
		dev_err(&idt82p33->client->dev,
			"Failed in %s with err %d!\n", __func__, err);
	mutex_unlock(&idt82p33->reg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक idt82p33_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta_ns)
अणु
	काष्ठा idt82p33_channel *channel =
			container_of(ptp, काष्ठा idt82p33_channel, caps);
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	पूर्णांक err;

	mutex_lock(&idt82p33->reg_lock);

	अगर (असल(delta_ns) < phase_snap_threshold) अणु
		mutex_unlock(&idt82p33->reg_lock);
		वापस 0;
	पूर्ण

	err = _idt82p33_adjसमय(channel, delta_ns);

	अगर (err) अणु
		mutex_unlock(&idt82p33->reg_lock);
		dev_err(&idt82p33->client->dev,
			"Adjtime failed in %s with err %d!\n", __func__, err);
		वापस err;
	पूर्ण

	err = idt82p33_sync_tod(channel, true);
	अगर (err)
		dev_err(&idt82p33->client->dev,
			"Sync_tod failed in %s with err %d!\n", __func__, err);

	mutex_unlock(&idt82p33->reg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक idt82p33_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	काष्ठा idt82p33_channel *channel =
			container_of(ptp, काष्ठा idt82p33_channel, caps);
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	पूर्णांक err;

	mutex_lock(&idt82p33->reg_lock);
	err = _idt82p33_समय_लो(channel, ts);
	अगर (err)
		dev_err(&idt82p33->client->dev,
			"Failed in %s with err %d!\n", __func__, err);
	mutex_unlock(&idt82p33->reg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक idt82p33_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा idt82p33_channel *channel =
			container_of(ptp, काष्ठा idt82p33_channel, caps);
	काष्ठा idt82p33 *idt82p33 = channel->idt82p33;
	पूर्णांक err;

	mutex_lock(&idt82p33->reg_lock);
	err = _idt82p33_समय_रखो(channel, ts);
	अगर (err)
		dev_err(&idt82p33->client->dev,
			"Failed in %s with err %d!\n", __func__, err);
	mutex_unlock(&idt82p33->reg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक idt82p33_channel_init(काष्ठा idt82p33_channel *channel, पूर्णांक index)
अणु
	चयन (index) अणु
	हाल 0:
		channel->dpll_tod_cnfg = DPLL1_TOD_CNFG;
		channel->dpll_tod_trigger = DPLL1_TOD_TRIGGER;
		channel->dpll_tod_sts = DPLL1_TOD_STS;
		channel->dpll_mode_cnfg = DPLL1_OPERATING_MODE_CNFG;
		channel->dpll_freq_cnfg = DPLL1_HOLDOVER_FREQ_CNFG;
		channel->dpll_phase_cnfg = DPLL1_PHASE_OFFSET_CNFG;
		channel->dpll_sync_cnfg = DPLL1_SYNC_EDGE_CNFG;
		channel->dpll_input_mode_cnfg = DPLL1_INPUT_MODE_CNFG;
		अवरोध;
	हाल 1:
		channel->dpll_tod_cnfg = DPLL2_TOD_CNFG;
		channel->dpll_tod_trigger = DPLL2_TOD_TRIGGER;
		channel->dpll_tod_sts = DPLL2_TOD_STS;
		channel->dpll_mode_cnfg = DPLL2_OPERATING_MODE_CNFG;
		channel->dpll_freq_cnfg = DPLL2_HOLDOVER_FREQ_CNFG;
		channel->dpll_phase_cnfg = DPLL2_PHASE_OFFSET_CNFG;
		channel->dpll_sync_cnfg = DPLL2_SYNC_EDGE_CNFG;
		channel->dpll_input_mode_cnfg = DPLL2_INPUT_MODE_CNFG;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	channel->current_freq_ppb = 0;

	वापस 0;
पूर्ण

अटल व्योम idt82p33_caps_init(काष्ठा ptp_घड़ी_info *caps)
अणु
	caps->owner = THIS_MODULE;
	caps->max_adj = 92000;
	caps->n_per_out = 11;
	caps->adjphase = idt82p33_adjग_लिखोphase;
	caps->adjfine = idt82p33_adjfine;
	caps->adjसमय = idt82p33_adjसमय;
	caps->समय_लो64 = idt82p33_समय_लो;
	caps->समय_रखो64 = idt82p33_समय_रखो;
	caps->enable = idt82p33_enable;
	caps->करो_aux_work = idt82p33_sync_tod_work_handler;
पूर्ण

अटल पूर्णांक idt82p33_enable_channel(काष्ठा idt82p33 *idt82p33, u32 index)
अणु
	काष्ठा idt82p33_channel *channel;
	पूर्णांक err;

	अगर (!(index < MAX_PHC_PLL))
		वापस -EINVAL;

	channel = &idt82p33->channel[index];

	err = idt82p33_channel_init(channel, index);
	अगर (err) अणु
		dev_err(&idt82p33->client->dev,
			"Channel_init failed in %s with err %d!\n",
			__func__, err);
		वापस err;
	पूर्ण

	channel->idt82p33 = idt82p33;

	idt82p33_caps_init(&channel->caps);
	snम_लिखो(channel->caps.name, माप(channel->caps.name),
		 "IDT 82P33 PLL%u", index);

	channel->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&channel->caps, शून्य);

	अगर (IS_ERR(channel->ptp_घड़ी)) अणु
		err = PTR_ERR(channel->ptp_घड़ी);
		channel->ptp_घड़ी = शून्य;
		वापस err;
	पूर्ण

	अगर (!channel->ptp_घड़ी)
		वापस -ENOTSUPP;

	err = idt82p33_dpll_set_mode(channel, PLL_MODE_DCO);
	अगर (err) अणु
		dev_err(&idt82p33->client->dev,
			"Dpll_set_mode failed in %s with err %d!\n",
			__func__, err);
		वापस err;
	पूर्ण

	err = idt82p33_enable_tod(channel);
	अगर (err) अणु
		dev_err(&idt82p33->client->dev,
			"Enable_tod failed in %s with err %d!\n",
			__func__, err);
		वापस err;
	पूर्ण

	dev_info(&idt82p33->client->dev, "PLL%d registered as ptp%d\n",
		 index, channel->ptp_घड़ी->index);

	वापस 0;
पूर्ण

अटल पूर्णांक idt82p33_load_firmware(काष्ठा idt82p33 *idt82p33)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा idt82p33_fwrc *rec;
	u8 loaddr, page, val;
	पूर्णांक err;
	s32 len;

	dev_dbg(&idt82p33->client->dev,
		"requesting firmware '%s'\n", FW_खाताNAME);

	err = request_firmware(&fw, FW_खाताNAME, &idt82p33->client->dev);

	अगर (err) अणु
		dev_err(&idt82p33->client->dev,
			"Failed in %s with err %d!\n", __func__, err);
		वापस err;
	पूर्ण

	dev_dbg(&idt82p33->client->dev, "firmware size %zu bytes\n", fw->size);

	rec = (काष्ठा idt82p33_fwrc *) fw->data;

	क्रम (len = fw->size; len > 0; len -= माप(*rec)) अणु

		अगर (rec->reserved) अणु
			dev_err(&idt82p33->client->dev,
				"bad firmware, reserved field non-zero\n");
			err = -EINVAL;
		पूर्ण अन्यथा अणु
			val = rec->value;
			loaddr = rec->loaddr;
			page = rec->hiaddr;

			rec++;

			err = idt82p33_check_and_set_masks(idt82p33, page,
							   loaddr, val);
		पूर्ण

		अगर (err == 0) अणु
			/* maximum 8 pages  */
			अगर (page >= PAGE_NUM)
				जारी;

			/* Page size 128, last 4 bytes of page skipped */
			अगर (((loaddr > 0x7b) && (loaddr <= 0x7f))
			     || loaddr > 0xfb)
				जारी;

			err = idt82p33_ग_लिखो(idt82p33, _ADDR(page, loaddr),
					     &val, माप(val));
		पूर्ण

		अगर (err)
			जाओ out;
	पूर्ण

	idt82p33_display_masks(idt82p33);
out:
	release_firmware(fw);
	वापस err;
पूर्ण


अटल पूर्णांक idt82p33_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा idt82p33 *idt82p33;
	पूर्णांक err;
	u8 i;

	(व्योम)id;

	idt82p33 = devm_kzalloc(&client->dev,
				माप(काष्ठा idt82p33), GFP_KERNEL);
	अगर (!idt82p33)
		वापस -ENOMEM;

	mutex_init(&idt82p33->reg_lock);

	idt82p33->client = client;
	idt82p33->page_offset = 0xff;
	idt82p33->tod_ग_लिखो_overhead_ns = 0;
	idt82p33->calculate_overhead_flag = 0;
	idt82p33->pll_mask = DEFAULT_PLL_MASK;
	idt82p33->channel[0].output_mask = DEFAULT_OUTPUT_MASK_PLL0;
	idt82p33->channel[1].output_mask = DEFAULT_OUTPUT_MASK_PLL1;

	mutex_lock(&idt82p33->reg_lock);

	err = idt82p33_load_firmware(idt82p33);

	अगर (err)
		dev_warn(&idt82p33->client->dev,
			 "loading firmware failed with %d\n", err);

	अगर (idt82p33->pll_mask) अणु
		क्रम (i = 0; i < MAX_PHC_PLL; i++) अणु
			अगर (idt82p33->pll_mask & (1 << i)) अणु
				err = idt82p33_enable_channel(idt82p33, i);
				अगर (err) अणु
					dev_err(&idt82p33->client->dev,
						"Failed in %s with err %d!\n",
						__func__, err);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&idt82p33->client->dev,
			"no PLLs flagged as PHCs, nothing to do\n");
		err = -ENODEV;
	पूर्ण

	mutex_unlock(&idt82p33->reg_lock);

	अगर (err) अणु
		idt82p33_ptp_घड़ी_unरेजिस्टर_all(idt82p33);
		वापस err;
	पूर्ण

	i2c_set_clientdata(client, idt82p33);

	वापस 0;
पूर्ण

अटल पूर्णांक idt82p33_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा idt82p33 *idt82p33 = i2c_get_clientdata(client);

	idt82p33_ptp_घड़ी_unरेजिस्टर_all(idt82p33);
	mutex_destroy(&idt82p33->reg_lock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id idt82p33_dt_id[] = अणु
	अणु .compatible = "idt,82p33810" पूर्ण,
	अणु .compatible = "idt,82p33813" पूर्ण,
	अणु .compatible = "idt,82p33814" पूर्ण,
	अणु .compatible = "idt,82p33831" पूर्ण,
	अणु .compatible = "idt,82p33910" पूर्ण,
	अणु .compatible = "idt,82p33913" पूर्ण,
	अणु .compatible = "idt,82p33914" पूर्ण,
	अणु .compatible = "idt,82p33931" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, idt82p33_dt_id);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id idt82p33_i2c_id[] = अणु
	अणु "idt82p33810", पूर्ण,
	अणु "idt82p33813", पूर्ण,
	अणु "idt82p33814", पूर्ण,
	अणु "idt82p33831", पूर्ण,
	अणु "idt82p33910", पूर्ण,
	अणु "idt82p33913", पूर्ण,
	अणु "idt82p33914", पूर्ण,
	अणु "idt82p33931", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, idt82p33_i2c_id);

अटल काष्ठा i2c_driver idt82p33_driver = अणु
	.driver = अणु
		.of_match_table	= of_match_ptr(idt82p33_dt_id),
		.name		= "idt82p33",
	पूर्ण,
	.probe		= idt82p33_probe,
	.हटाओ		= idt82p33_हटाओ,
	.id_table	= idt82p33_i2c_id,
पूर्ण;

module_i2c_driver(idt82p33_driver);
