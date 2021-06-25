<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "ixgbe.h"
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/घड़ीsource.h>

/*
 * The 82599 and the X540 करो not have true 64bit nanosecond scale
 * counter रेजिस्टरs. Instead, SYSTIME is defined by a fixed poपूर्णांक
 * प्रणाली which allows the user to define the scale counter increment
 * value at every level change of the oscillator driving the SYSTIME
 * value. For both devices the TIMINCA:IV field defines this
 * increment. On the X540 device, 31 bits are provided. However on the
 * 82599 only provides 24 bits. The समय unit is determined by the
 * घड़ी frequency of the oscillator in combination with the TIMINCA
 * रेजिस्टर. When these devices link at 10Gb the oscillator has a
 * period of 6.4ns. In order to convert the scale counter पूर्णांकo
 * nanoseconds the cyclecounter and समयcounter काष्ठाures are
 * used. The SYSTIME रेजिस्टरs need to be converted to ns values by use
 * of only a right shअगरt (भागision by घातer of 2). The following math
 * determines the largest incvalue that will fit पूर्णांकo the available
 * bits in the TIMINCA रेजिस्टर.
 *
 * PeriodWidth: Number of bits to store the घड़ी period
 * MaxWidth: The maximum width value of the TIMINCA रेजिस्टर
 * Period: The घड़ी period क्रम the oscillator
 * round(): discard the fractional portion of the calculation
 *
 * Period * [ 2 ^ ( MaxWidth - PeriodWidth ) ]
 *
 * For the X540, MaxWidth is 31 bits, and the base period is 6.4 ns
 * For the 82599, MaxWidth is 24 bits, and the base period is 6.4 ns
 *
 * The period also changes based on the link speed:
 * At 10Gb link or no link, the period reमुख्यs the same.
 * At 1Gb link, the period is multiplied by 10. (64ns)
 * At 100Mb link, the period is multiplied by 100. (640ns)
 *
 * The calculated value allows us to right shअगरt the SYSTIME रेजिस्टर
 * value in order to quickly convert it पूर्णांकo a nanosecond घड़ी,
 * जबतक allowing क्रम the maximum possible adjusपंचांगent value.
 *
 * These diagrams are only क्रम the 10Gb link period
 *
 *           SYSTIMEH            SYSTIMEL
 *       +--------------+  +--------------+
 * X540  |      32      |  | 1 | 3 |  28  |
 *       *--------------+  +--------------+
 *        \________ 36 bits ______/  fract
 *
 *       +--------------+  +--------------+
 * 82599 |      32      |  | 8 | 3 |  21  |
 *       *--------------+  +--------------+
 *        \________ 43 bits ______/  fract
 *
 * The 36 bit X540 SYSTIME overflows every
 *   2^36 * 10^-9 / 60 = 1.14 minutes or 69 seconds
 *
 * The 43 bit 82599 SYSTIME overflows every
 *   2^43 * 10^-9 / 3600 = 2.4 hours
 */
#घोषणा IXGBE_INCVAL_10GB 0x66666666
#घोषणा IXGBE_INCVAL_1GB  0x40000000
#घोषणा IXGBE_INCVAL_100  0x50000000

#घोषणा IXGBE_INCVAL_SHIFT_10GB  28
#घोषणा IXGBE_INCVAL_SHIFT_1GB   24
#घोषणा IXGBE_INCVAL_SHIFT_100   21

#घोषणा IXGBE_INCVAL_SHIFT_82599 7
#घोषणा IXGBE_INCPER_SHIFT_82599 24

#घोषणा IXGBE_OVERFLOW_PERIOD    (HZ * 30)
#घोषणा IXGBE_PTP_TX_TIMEOUT     (HZ)

/* We use our own definitions instead of NSEC_PER_SEC because we want to mark
 * the value as a ULL to क्रमce precision when bit shअगरting.
 */
#घोषणा NS_PER_SEC      1000000000ULL
#घोषणा NS_PER_HALF_SEC  500000000ULL

/* In contrast, the X550 controller has two रेजिस्टरs, SYSTIMEH and SYSTIMEL
 * which contain measurements of seconds and nanoseconds respectively. This
 * matches the standard linux representation of समय in the kernel. In addition,
 * the X550 also has a SYSTIMER रेजिस्टर which represents residue, or
 * subnanosecond overflow adjusपंचांगents. To control घड़ी adjusपंचांगent, the TIMINCA
 * रेजिस्टर is used, but it is unlike the X540 and 82599 devices. TIMINCA
 * represents units of 2^-32 nanoseconds, and uses 31 bits क्रम this, with the
 * high bit representing whether the adjustent is positive or negative. Every
 * घड़ी cycle, the X550 will add 12.5 ns + TIMINCA which can result in a range
 * of 12 to 13 nanoseconds adjusपंचांगent. Unlike the 82599 and X540 devices, the
 * X550's घड़ी क्रम purposes of SYSTIME generation is स्थिरant and not dependent
 * on the link speed.
 *
 *           SYSTIMEH           SYSTIMEL        SYSTIMER
 *       +--------------+  +--------------+  +-------------+
 * X550  |      32      |  |      32      |  |     32      |
 *       *--------------+  +--------------+  +-------------+
 *       \____seconds___/   \_nanoseconds_/  \__2^-32 ns__/
 *
 * This results in a full 96 bits to represent the घड़ी, with 32 bits क्रम
 * seconds, 32 bits क्रम nanoseconds (largest value is 0d999999999 or just under
 * 1 second) and an additional 32 bits to measure sub nanosecond adjusपंचांगents क्रम
 * underflow of adjusपंचांगents.
 *
 * The 32 bits of seconds क्रम the X550 overflows every
 *   2^32 / ( 365.25 * 24 * 60 * 60 ) = ~136 years.
 *
 * In order to adjust the घड़ी frequency क्रम the X550, the TIMINCA रेजिस्टर is
 * provided. This रेजिस्टर represents a + or minus nearly 0.5 ns adjusपंचांगent to
 * the base frequency. It is measured in 2^-32 ns units, with the high bit being
 * the sign bit. This रेजिस्टर enables software to calculate frequency
 * adjusपंचांगents and apply them directly to the घड़ी rate.
 *
 * The math क्रम converting ppb पूर्णांकo TIMINCA values is fairly straightक्रमward.
 *   TIMINCA value = ( Base_Frequency * ppb ) / 1000000000ULL
 *
 * This assumes that ppb is never high enough to create a value bigger than
 * TIMINCA's 31 bits can store. This is ensured by the stack. Calculating this
 * value is also simple.
 *   Max ppb = ( Max Adjusपंचांगent / Base Frequency ) / 1000000000ULL
 *
 * For the X550, the Max adjusपंचांगent is +/- 0.5 ns, and the base frequency is
 * 12.5 nanoseconds. This means that the Max ppb is 39999999
 *   Note: We subtract one in order to ensure no overflow, because the TIMINCA
 *         रेजिस्टर can only hold slightly under 0.5 nanoseconds.
 *
 * Because TIMINCA is measured in 2^-32 ns units, we have to convert 12.5 ns
 * पूर्णांकo 2^-32 units, which is
 *
 *  12.5 * 2^32 = C80000000
 *
 * Some revisions of hardware have a faster base frequency than the रेजिस्टरs
 * were defined क्रम. To fix this, we use a समयcounter काष्ठाure with the
 * proper mult and shअगरt to convert the cycles पूर्णांकo nanoseconds of समय.
 */
#घोषणा IXGBE_X550_BASE_PERIOD 0xC80000000ULL
#घोषणा INCVALUE_MASK	0x7FFFFFFF
#घोषणा ISGN		0x80000000
#घोषणा MAX_TIMADJ	0x7FFFFFFF

/**
 * ixgbe_ptp_setup_sdp_X540
 * @adapter: निजी adapter काष्ठाure
 *
 * this function enables or disables the घड़ी out feature on SDP0 क्रम
 * the X540 device. It will create a 1 second periodic output that can
 * be used as the PPS (via an पूर्णांकerrupt).
 *
 * It calculates when the प्रणाली समय will be on an exact second, and then
 * aligns the start of the PPS संकेत to that value.
 *
 * This works by using the cycle counter shअगरt and mult values in reverse, and
 * assumes that the values we're shअगरting will not overflow.
 */
अटल व्योम ixgbe_ptp_setup_sdp_X540(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा cyclecounter *cc = &adapter->hw_cc;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 esdp, tsauxc, clktiml, clktimh, trgttiml, trgttimh, rem;
	u64 ns = 0, घड़ी_edge = 0, घड़ी_period;
	अचिन्हित दीर्घ flags;

	/* disable the pin first */
	IXGBE_WRITE_REG(hw, IXGBE_TSAUXC, 0x0);
	IXGBE_WRITE_FLUSH(hw);

	अगर (!(adapter->flags2 & IXGBE_FLAG2_PTP_PPS_ENABLED))
		वापस;

	esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);

	/* enable the SDP0 pin as output, and connected to the
	 * native function क्रम Timesync (ClockOut)
	 */
	esdp |= IXGBE_ESDP_SDP0_सूची |
		IXGBE_ESDP_SDP0_NATIVE;

	/* enable the Clock Out feature on SDP0, and allow
	 * पूर्णांकerrupts to occur when the pin changes
	 */
	tsauxc = (IXGBE_TSAUXC_EN_CLK |
		  IXGBE_TSAUXC_SYNCLK |
		  IXGBE_TSAUXC_SDP0_INT);

	/* Determine the घड़ी समय period to use. This assumes that the
	 * cycle counter shअगरt is small enough to aव्योम overflow.
	 */
	घड़ी_period = भाग_u64((NS_PER_HALF_SEC << cc->shअगरt), cc->mult);
	clktiml = (u32)(घड़ी_period);
	clktimh = (u32)(घड़ी_period >> 32);

	/* Read the current घड़ी समय, and save the cycle counter value */
	spin_lock_irqsave(&adapter->पंचांगreg_lock, flags);
	ns = समयcounter_पढ़ो(&adapter->hw_tc);
	घड़ी_edge = adapter->hw_tc.cycle_last;
	spin_unlock_irqrestore(&adapter->पंचांगreg_lock, flags);

	/* Figure out how many seconds to add in order to round up */
	भाग_u64_rem(ns, NS_PER_SEC, &rem);

	/* Figure out how many nanoseconds to add to round the घड़ी edge up
	 * to the next full second
	 */
	rem = (NS_PER_SEC - rem);

	/* Adjust the घड़ी edge to align with the next full second. */
	घड़ी_edge += भाग_u64(((u64)rem << cc->shअगरt), cc->mult);
	trgttiml = (u32)घड़ी_edge;
	trgttimh = (u32)(घड़ी_edge >> 32);

	IXGBE_WRITE_REG(hw, IXGBE_CLKTIML, clktiml);
	IXGBE_WRITE_REG(hw, IXGBE_CLKTIMH, clktimh);
	IXGBE_WRITE_REG(hw, IXGBE_TRGTTIML0, trgttiml);
	IXGBE_WRITE_REG(hw, IXGBE_TRGTTIMH0, trgttimh);

	IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
	IXGBE_WRITE_REG(hw, IXGBE_TSAUXC, tsauxc);

	IXGBE_WRITE_FLUSH(hw);
पूर्ण

/**
 * ixgbe_ptp_setup_sdp_X550
 * @adapter: निजी adapter काष्ठाure
 *
 * Enable or disable a घड़ी output संकेत on SDP 0 क्रम X550 hardware.
 *
 * Use the target समय feature to align the output संकेत on the next full
 * second.
 *
 * This works by using the cycle counter shअगरt and mult values in reverse, and
 * assumes that the values we're shअगरting will not overflow.
 */
अटल व्योम ixgbe_ptp_setup_sdp_X550(काष्ठा ixgbe_adapter *adapter)
अणु
	u32 esdp, tsauxc, freqout, trgttiml, trgttimh, rem, tssdp;
	काष्ठा cyclecounter *cc = &adapter->hw_cc;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u64 ns = 0, घड़ी_edge = 0;
	काष्ठा बारpec64 ts;
	अचिन्हित दीर्घ flags;

	/* disable the pin first */
	IXGBE_WRITE_REG(hw, IXGBE_TSAUXC, 0x0);
	IXGBE_WRITE_FLUSH(hw);

	अगर (!(adapter->flags2 & IXGBE_FLAG2_PTP_PPS_ENABLED))
		वापस;

	esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);

	/* enable the SDP0 pin as output, and connected to the
	 * native function क्रम Timesync (ClockOut)
	 */
	esdp |= IXGBE_ESDP_SDP0_सूची |
		IXGBE_ESDP_SDP0_NATIVE;

	/* enable the Clock Out feature on SDP0, and use Target Time 0 to
	 * enable generation of पूर्णांकerrupts on the घड़ी change.
	 */
#घोषणा IXGBE_TSAUXC_DIS_TS_CLEAR 0x40000000
	tsauxc = (IXGBE_TSAUXC_EN_CLK | IXGBE_TSAUXC_ST0 |
		  IXGBE_TSAUXC_EN_TT0 | IXGBE_TSAUXC_SDP0_INT |
		  IXGBE_TSAUXC_DIS_TS_CLEAR);

	tssdp = (IXGBE_TSSDP_TS_SDP0_EN |
		 IXGBE_TSSDP_TS_SDP0_CLK0);

	/* Determine the घड़ी समय period to use. This assumes that the
	 * cycle counter shअगरt is small enough to aव्योम overflowing a 32bit
	 * value.
	 */
	freqout = भाग_u64(NS_PER_HALF_SEC << cc->shअगरt,  cc->mult);

	/* Read the current घड़ी समय, and save the cycle counter value */
	spin_lock_irqsave(&adapter->पंचांगreg_lock, flags);
	ns = समयcounter_पढ़ो(&adapter->hw_tc);
	घड़ी_edge = adapter->hw_tc.cycle_last;
	spin_unlock_irqrestore(&adapter->पंचांगreg_lock, flags);

	/* Figure out how far past the next second we are */
	भाग_u64_rem(ns, NS_PER_SEC, &rem);

	/* Figure out how many nanoseconds to add to round the घड़ी edge up
	 * to the next full second
	 */
	rem = (NS_PER_SEC - rem);

	/* Adjust the घड़ी edge to align with the next full second. */
	घड़ी_edge += भाग_u64(((u64)rem << cc->shअगरt), cc->mult);

	/* X550 hardware stores the समय in 32bits of 'billions of cycles' and
	 * 32bits of 'cycles'. There's no guarantee that cycles represents
	 * nanoseconds. However, we can use the math from a बारpec64 to
	 * convert पूर्णांकo the hardware representation.
	 *
	 * See ixgbe_ptp_पढ़ो_X550() क्रम more details.
	 */
	ts = ns_to_बारpec64(घड़ी_edge);
	trgttiml = (u32)ts.tv_nsec;
	trgttimh = (u32)ts.tv_sec;

	IXGBE_WRITE_REG(hw, IXGBE_FREQOUT0, freqout);
	IXGBE_WRITE_REG(hw, IXGBE_TRGTTIML0, trgttiml);
	IXGBE_WRITE_REG(hw, IXGBE_TRGTTIMH0, trgttimh);

	IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
	IXGBE_WRITE_REG(hw, IXGBE_TSSDP, tssdp);
	IXGBE_WRITE_REG(hw, IXGBE_TSAUXC, tsauxc);

	IXGBE_WRITE_FLUSH(hw);
पूर्ण

/**
 * ixgbe_ptp_पढ़ो_X550 - पढ़ो cycle counter value
 * @cc: cyclecounter काष्ठाure
 *
 * This function पढ़ोs SYSTIME रेजिस्टरs. It is called by the cyclecounter
 * काष्ठाure to convert from पूर्णांकernal representation पूर्णांकo nanoseconds. We need
 * this क्रम X550 since some skews करो not have expected घड़ी frequency and
 * result of SYSTIME is 32bits of "billions of cycles" and 32 bits of
 * "cycles", rather than seconds and nanoseconds.
 */
अटल u64 ixgbe_ptp_पढ़ो_X550(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा ixgbe_adapter *adapter =
		container_of(cc, काष्ठा ixgbe_adapter, hw_cc);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा बारpec64 ts;

	/* storage is 32 bits of 'billions of cycles' and 32 bits of 'cycles'.
	 * Some revisions of hardware run at a higher frequency and so the
	 * cycles are not guaranteed to be nanoseconds. The बारpec64 created
	 * here is used क्रम its math/conversions but करोes not necessarily
	 * represent nominal समय.
	 *
	 * It should be noted that this cyclecounter will overflow at a
	 * non-biपंचांगask field since we have to convert our billions of cycles
	 * पूर्णांकo an actual cycles count. This results in some possible weird
	 * situations at high cycle counter stamps. However given that 32 bits
	 * of "seconds" is ~138 years this isn't a problem. Even at the
	 * increased frequency of some revisions, this is still ~103 years.
	 * Since the SYSTIME values start at 0 and we never ग_लिखो them, it is
	 * highly unlikely क्रम the cyclecounter to overflow in practice.
	 */
	IXGBE_READ_REG(hw, IXGBE_SYSTIMR);
	ts.tv_nsec = IXGBE_READ_REG(hw, IXGBE_SYSTIML);
	ts.tv_sec = IXGBE_READ_REG(hw, IXGBE_SYSTIMH);

	वापस (u64)बारpec64_to_ns(&ts);
पूर्ण

/**
 * ixgbe_ptp_पढ़ो_82599 - पढ़ो raw cycle counter (to be used by समय counter)
 * @cc: the cyclecounter काष्ठाure
 *
 * this function पढ़ोs the cyclecounter रेजिस्टरs and is called by the
 * cyclecounter काष्ठाure used to स्थिरruct a ns counter from the
 * arbitrary fixed poपूर्णांक रेजिस्टरs
 */
अटल u64 ixgbe_ptp_पढ़ो_82599(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा ixgbe_adapter *adapter =
		container_of(cc, काष्ठा ixgbe_adapter, hw_cc);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u64 stamp = 0;

	stamp |= (u64)IXGBE_READ_REG(hw, IXGBE_SYSTIML);
	stamp |= (u64)IXGBE_READ_REG(hw, IXGBE_SYSTIMH) << 32;

	वापस stamp;
पूर्ण

/**
 * ixgbe_ptp_convert_to_hwtstamp - convert रेजिस्टर value to hw बारtamp
 * @adapter: निजी adapter काष्ठाure
 * @hwtstamp: stack बारtamp काष्ठाure
 * @बारtamp: अचिन्हित 64bit प्रणाली समय value
 *
 * We need to convert the adapter's RX/TXSTMP रेजिस्टरs पूर्णांकo a hwtstamp value
 * which can be used by the stack's ptp functions.
 *
 * The lock is used to protect consistency of the cyclecounter and the SYSTIME
 * रेजिस्टरs. However, it करोes not need to protect against the Rx or Tx
 * बारtamp रेजिस्टरs, as there can't be a new बारtamp until the old one is
 * unlatched by पढ़ोing.
 *
 * In addition to the बारtamp in hardware, some controllers need a software
 * overflow cyclecounter, and this function takes this पूर्णांकo account as well.
 **/
अटल व्योम ixgbe_ptp_convert_to_hwtstamp(काष्ठा ixgbe_adapter *adapter,
					  काष्ठा skb_shared_hwtstamps *hwtstamp,
					  u64 बारtamp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा बारpec64 sysसमय;
	u64 ns;

	स_रखो(hwtstamp, 0, माप(*hwtstamp));

	चयन (adapter->hw.mac.type) अणु
	/* X550 and later hardware supposedly represent समय using a seconds
	 * and nanoseconds counter, instead of raw 64bits nanoseconds. We need
	 * to convert the बारtamp पूर्णांकo cycles beक्रमe it can be fed to the
	 * cyclecounter. We need an actual cyclecounter because some revisions
	 * of hardware run at a higher frequency and thus the counter करोes
	 * not represent seconds/nanoseconds. Instead it can be thought of as
	 * cycles and billions of cycles.
	 */
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		/* Upper 32 bits represent billions of cycles, lower 32 bits
		 * represent cycles. However, we use बारpec64_to_ns क्रम the
		 * correct math even though the units haven't been corrected
		 * yet.
		 */
		sysसमय.tv_sec = बारtamp >> 32;
		sysसमय.tv_nsec = बारtamp & 0xFFFFFFFF;

		बारtamp = बारpec64_to_ns(&sysसमय);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&adapter->पंचांगreg_lock, flags);
	ns = समयcounter_cyc2समय(&adapter->hw_tc, बारtamp);
	spin_unlock_irqrestore(&adapter->पंचांगreg_lock, flags);

	hwtstamp->hwtstamp = ns_to_kसमय(ns);
पूर्ण

/**
 * ixgbe_ptp_adjfreq_82599
 * @ptp: the ptp घड़ी काष्ठाure
 * @ppb: parts per billion adjusपंचांगent from base
 *
 * adjust the frequency of the ptp cycle counter by the
 * indicated ppb from the base frequency.
 */
अटल पूर्णांक ixgbe_ptp_adjfreq_82599(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	काष्ठा ixgbe_adapter *adapter =
		container_of(ptp, काष्ठा ixgbe_adapter, ptp_caps);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u64 freq, incval;
	u32 dअगरf;
	पूर्णांक neg_adj = 0;

	अगर (ppb < 0) अणु
		neg_adj = 1;
		ppb = -ppb;
	पूर्ण

	smp_mb();
	incval = READ_ONCE(adapter->base_incval);

	freq = incval;
	freq *= ppb;
	dअगरf = भाग_u64(freq, 1000000000ULL);

	incval = neg_adj ? (incval - dअगरf) : (incval + dअगरf);

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_X540:
		अगर (incval > 0xFFFFFFFFULL)
			e_dev_warn("PTP ppb adjusted SYSTIME rate overflowed!\n");
		IXGBE_WRITE_REG(hw, IXGBE_TIMINCA, (u32)incval);
		अवरोध;
	हाल ixgbe_mac_82599EB:
		अगर (incval > 0x00FFFFFFULL)
			e_dev_warn("PTP ppb adjusted SYSTIME rate overflowed!\n");
		IXGBE_WRITE_REG(hw, IXGBE_TIMINCA,
				BIT(IXGBE_INCPER_SHIFT_82599) |
				((u32)incval & 0x00FFFFFFUL));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbe_ptp_adjfreq_X550
 * @ptp: the ptp घड़ी काष्ठाure
 * @ppb: parts per billion adjusपंचांगent from base
 *
 * adjust the frequency of the SYSTIME रेजिस्टरs by the indicated ppb from base
 * frequency
 */
अटल पूर्णांक ixgbe_ptp_adjfreq_X550(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	काष्ठा ixgbe_adapter *adapter =
			container_of(ptp, काष्ठा ixgbe_adapter, ptp_caps);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक neg_adj = 0;
	u64 rate = IXGBE_X550_BASE_PERIOD;
	u32 inca;

	अगर (ppb < 0) अणु
		neg_adj = 1;
		ppb = -ppb;
	पूर्ण
	rate *= ppb;
	rate = भाग_u64(rate, 1000000000ULL);

	/* warn अगर rate is too large */
	अगर (rate >= INCVALUE_MASK)
		e_dev_warn("PTP ppb adjusted SYSTIME rate overflowed!\n");

	inca = rate & INCVALUE_MASK;
	अगर (neg_adj)
		inca |= ISGN;

	IXGBE_WRITE_REG(hw, IXGBE_TIMINCA, inca);

	वापस 0;
पूर्ण

/**
 * ixgbe_ptp_adjसमय
 * @ptp: the ptp घड़ी काष्ठाure
 * @delta: offset to adjust the cycle counter by
 *
 * adjust the समयr by resetting the समयcounter काष्ठाure.
 */
अटल पूर्णांक ixgbe_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा ixgbe_adapter *adapter =
		container_of(ptp, काष्ठा ixgbe_adapter, ptp_caps);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->पंचांगreg_lock, flags);
	समयcounter_adjसमय(&adapter->hw_tc, delta);
	spin_unlock_irqrestore(&adapter->पंचांगreg_lock, flags);

	अगर (adapter->ptp_setup_sdp)
		adapter->ptp_setup_sdp(adapter);

	वापस 0;
पूर्ण

/**
 * ixgbe_ptp_समय_लोx
 * @ptp: the ptp घड़ी काष्ठाure
 * @ts: बारpec to hold the PHC बारtamp
 * @sts: काष्ठाure to hold the प्रणाली समय beक्रमe and after पढ़ोing the PHC
 *
 * पढ़ो the समयcounter and वापस the correct value on ns,
 * after converting it पूर्णांकo a काष्ठा बारpec.
 */
अटल पूर्णांक ixgbe_ptp_समय_लोx(काष्ठा ptp_घड़ी_info *ptp,
			      काष्ठा बारpec64 *ts,
			      काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा ixgbe_adapter *adapter =
		container_of(ptp, काष्ठा ixgbe_adapter, ptp_caps);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ flags;
	u64 ns, stamp;

	spin_lock_irqsave(&adapter->पंचांगreg_lock, flags);

	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		/* Upper 32 bits represent billions of cycles, lower 32 bits
		 * represent cycles. However, we use बारpec64_to_ns क्रम the
		 * correct math even though the units haven't been corrected
		 * yet.
		 */
		ptp_पढ़ो_प्रणाली_prets(sts);
		IXGBE_READ_REG(hw, IXGBE_SYSTIMR);
		ptp_पढ़ो_प्रणाली_postts(sts);
		ts->tv_nsec = IXGBE_READ_REG(hw, IXGBE_SYSTIML);
		ts->tv_sec = IXGBE_READ_REG(hw, IXGBE_SYSTIMH);
		stamp = बारpec64_to_ns(ts);
		अवरोध;
	शेष:
		ptp_पढ़ो_प्रणाली_prets(sts);
		stamp = IXGBE_READ_REG(hw, IXGBE_SYSTIML);
		ptp_पढ़ो_प्रणाली_postts(sts);
		stamp |= (u64)IXGBE_READ_REG(hw, IXGBE_SYSTIMH) << 32;
		अवरोध;
	पूर्ण

	ns = समयcounter_cyc2समय(&adapter->hw_tc, stamp);

	spin_unlock_irqrestore(&adapter->पंचांगreg_lock, flags);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

/**
 * ixgbe_ptp_समय_रखो
 * @ptp: the ptp घड़ी काष्ठाure
 * @ts: the बारpec containing the new समय क्रम the cycle counter
 *
 * reset the समयcounter to use a new base value instead of the kernel
 * wall समयr value.
 */
अटल पूर्णांक ixgbe_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			     स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा ixgbe_adapter *adapter =
		container_of(ptp, काष्ठा ixgbe_adapter, ptp_caps);
	अचिन्हित दीर्घ flags;
	u64 ns = बारpec64_to_ns(ts);

	/* reset the समयcounter */
	spin_lock_irqsave(&adapter->पंचांगreg_lock, flags);
	समयcounter_init(&adapter->hw_tc, &adapter->hw_cc, ns);
	spin_unlock_irqrestore(&adapter->पंचांगreg_lock, flags);

	अगर (adapter->ptp_setup_sdp)
		adapter->ptp_setup_sdp(adapter);
	वापस 0;
पूर्ण

/**
 * ixgbe_ptp_feature_enable
 * @ptp: the ptp घड़ी काष्ठाure
 * @rq: the requested feature to change
 * @on: whether to enable or disable the feature
 *
 * enable (or disable) ancillary features of the phc subप्रणाली.
 * our driver only supports the PPS feature on the X540
 */
अटल पूर्णांक ixgbe_ptp_feature_enable(काष्ठा ptp_घड़ी_info *ptp,
				    काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा ixgbe_adapter *adapter =
		container_of(ptp, काष्ठा ixgbe_adapter, ptp_caps);

	/**
	 * When PPS is enabled, unmask the पूर्णांकerrupt क्रम the ClockOut
	 * feature, so that the पूर्णांकerrupt handler can send the PPS
	 * event when the घड़ी SDP triggers. Clear mask when PPS is
	 * disabled
	 */
	अगर (rq->type != PTP_CLK_REQ_PPS || !adapter->ptp_setup_sdp)
		वापस -ENOTSUPP;

	अगर (on)
		adapter->flags2 |= IXGBE_FLAG2_PTP_PPS_ENABLED;
	अन्यथा
		adapter->flags2 &= ~IXGBE_FLAG2_PTP_PPS_ENABLED;

	adapter->ptp_setup_sdp(adapter);
	वापस 0;
पूर्ण

/**
 * ixgbe_ptp_check_pps_event
 * @adapter: the निजी adapter काष्ठाure
 *
 * This function is called by the पूर्णांकerrupt routine when checking क्रम
 * पूर्णांकerrupts. It will check and handle a pps event.
 */
व्योम ixgbe_ptp_check_pps_event(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ptp_घड़ी_event event;

	event.type = PTP_CLOCK_PPS;

	/* this check is necessary in हाल the पूर्णांकerrupt was enabled via some
	 * alternative means (ex. debug_fs). Better to check here than
	 * everywhere that calls this function.
	 */
	अगर (!adapter->ptp_घड़ी)
		वापस;

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_X540:
		ptp_घड़ी_event(adapter->ptp_घड़ी, &event);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ixgbe_ptp_overflow_check - watchकरोg task to detect SYSTIME overflow
 * @adapter: निजी adapter काष्ठा
 *
 * this watchकरोg task periodically पढ़ोs the समयcounter
 * in order to prevent missing when the प्रणाली समय रेजिस्टरs wrap
 * around. This needs to be run approximately twice a minute.
 */
व्योम ixgbe_ptp_overflow_check(काष्ठा ixgbe_adapter *adapter)
अणु
	bool समयout = समय_is_beक्रमe_jअगरfies(adapter->last_overflow_check +
					     IXGBE_OVERFLOW_PERIOD);
	अचिन्हित दीर्घ flags;

	अगर (समयout) अणु
		/* Update the समयcounter */
		spin_lock_irqsave(&adapter->पंचांगreg_lock, flags);
		समयcounter_पढ़ो(&adapter->hw_tc);
		spin_unlock_irqrestore(&adapter->पंचांगreg_lock, flags);

		adapter->last_overflow_check = jअगरfies;
	पूर्ण
पूर्ण

/**
 * ixgbe_ptp_rx_hang - detect error हाल when Rx बारtamp रेजिस्टरs latched
 * @adapter: निजी network adapter काष्ठाure
 *
 * this watchकरोg task is scheduled to detect error हाल where hardware has
 * dropped an Rx packet that was बारtamped when the ring is full. The
 * particular error is rare but leaves the device in a state unable to बारtamp
 * any future packets.
 */
व्योम ixgbe_ptp_rx_hang(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 tsyncrxctl = IXGBE_READ_REG(hw, IXGBE_TSYNCRXCTL);
	काष्ठा ixgbe_ring *rx_ring;
	अचिन्हित दीर्घ rx_event;
	पूर्णांक n;

	/* अगर we करोn't have a valid बारtamp in the रेजिस्टरs, just update the
	 * समयout counter and निकास
	 */
	अगर (!(tsyncrxctl & IXGBE_TSYNCRXCTL_VALID)) अणु
		adapter->last_rx_ptp_check = jअगरfies;
		वापस;
	पूर्ण

	/* determine the most recent watchकरोg or rx_बारtamp event */
	rx_event = adapter->last_rx_ptp_check;
	क्रम (n = 0; n < adapter->num_rx_queues; n++) अणु
		rx_ring = adapter->rx_ring[n];
		अगर (समय_after(rx_ring->last_rx_बारtamp, rx_event))
			rx_event = rx_ring->last_rx_बारtamp;
	पूर्ण

	/* only need to पढ़ो the high RXSTMP रेजिस्टर to clear the lock */
	अगर (समय_is_beक्रमe_jअगरfies(rx_event + 5 * HZ)) अणु
		IXGBE_READ_REG(hw, IXGBE_RXSTMPH);
		adapter->last_rx_ptp_check = jअगरfies;

		adapter->rx_hwtstamp_cleared++;
		e_warn(drv, "clearing RX Timestamp hang\n");
	पूर्ण
पूर्ण

/**
 * ixgbe_ptp_clear_tx_बारtamp - utility function to clear Tx बारtamp state
 * @adapter: the निजी adapter काष्ठाure
 *
 * This function should be called whenever the state related to a Tx बारtamp
 * needs to be cleared. This helps ensure that all related bits are reset क्रम
 * the next Tx बारtamp event.
 */
अटल व्योम ixgbe_ptp_clear_tx_बारtamp(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	IXGBE_READ_REG(hw, IXGBE_TXSTMPH);
	अगर (adapter->ptp_tx_skb) अणु
		dev_kमुक्त_skb_any(adapter->ptp_tx_skb);
		adapter->ptp_tx_skb = शून्य;
	पूर्ण
	clear_bit_unlock(__IXGBE_PTP_TX_IN_PROGRESS, &adapter->state);
पूर्ण

/**
 * ixgbe_ptp_tx_hang - detect error हाल where Tx बारtamp never finishes
 * @adapter: निजी network adapter काष्ठाure
 */
व्योम ixgbe_ptp_tx_hang(काष्ठा ixgbe_adapter *adapter)
अणु
	bool समयout = समय_is_beक्रमe_jअगरfies(adapter->ptp_tx_start +
					      IXGBE_PTP_TX_TIMEOUT);

	अगर (!adapter->ptp_tx_skb)
		वापस;

	अगर (!test_bit(__IXGBE_PTP_TX_IN_PROGRESS, &adapter->state))
		वापस;

	/* If we haven't received a बारtamp within the समयout, it is
	 * reasonable to assume that it will never occur, so we can unlock the
	 * बारtamp bit when this occurs.
	 */
	अगर (समयout) अणु
		cancel_work_sync(&adapter->ptp_tx_work);
		ixgbe_ptp_clear_tx_बारtamp(adapter);
		adapter->tx_hwtstamp_समयouts++;
		e_warn(drv, "clearing Tx timestamp hang\n");
	पूर्ण
पूर्ण

/**
 * ixgbe_ptp_tx_hwtstamp - utility function which checks क्रम TX समय stamp
 * @adapter: the निजी adapter काष्ठा
 *
 * अगर the बारtamp is valid, we convert it पूर्णांकo the समयcounter ns
 * value, then store that result पूर्णांकo the shhwtstamps काष्ठाure which
 * is passed up the network stack
 */
अटल व्योम ixgbe_ptp_tx_hwtstamp(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा sk_buff *skb = adapter->ptp_tx_skb;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	u64 regval = 0;

	regval |= (u64)IXGBE_READ_REG(hw, IXGBE_TXSTMPL);
	regval |= (u64)IXGBE_READ_REG(hw, IXGBE_TXSTMPH) << 32;
	ixgbe_ptp_convert_to_hwtstamp(adapter, &shhwtstamps, regval);

	/* Handle cleanup of the ptp_tx_skb ourselves, and unlock the state
	 * bit prior to notअगरying the stack via skb_tstamp_tx(). This prevents
	 * well behaved applications from attempting to बारtamp again prior
	 * to the lock bit being clear.
	 */
	adapter->ptp_tx_skb = शून्य;
	clear_bit_unlock(__IXGBE_PTP_TX_IN_PROGRESS, &adapter->state);

	/* Notअगरy the stack and then मुक्त the skb after we've unlocked */
	skb_tstamp_tx(skb, &shhwtstamps);
	dev_kमुक्त_skb_any(skb);
पूर्ण

/**
 * ixgbe_ptp_tx_hwtstamp_work
 * @work: poपूर्णांकer to the work काष्ठा
 *
 * This work item polls TSYNCTXCTL valid bit to determine when a Tx hardware
 * बारtamp has been taken क्रम the current skb. It is necessary, because the
 * descriptor's "done" bit करोes not correlate with the बारtamp event.
 */
अटल व्योम ixgbe_ptp_tx_hwtstamp_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ixgbe_adapter *adapter = container_of(work, काष्ठा ixgbe_adapter,
						     ptp_tx_work);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	bool समयout = समय_is_beक्रमe_jअगरfies(adapter->ptp_tx_start +
					      IXGBE_PTP_TX_TIMEOUT);
	u32 tsynctxctl;

	/* we have to have a valid skb to poll क्रम a बारtamp */
	अगर (!adapter->ptp_tx_skb) अणु
		ixgbe_ptp_clear_tx_बारtamp(adapter);
		वापस;
	पूर्ण

	/* stop polling once we have a valid बारtamp */
	tsynctxctl = IXGBE_READ_REG(hw, IXGBE_TSYNCTXCTL);
	अगर (tsynctxctl & IXGBE_TSYNCTXCTL_VALID) अणु
		ixgbe_ptp_tx_hwtstamp(adapter);
		वापस;
	पूर्ण

	अगर (समयout) अणु
		ixgbe_ptp_clear_tx_बारtamp(adapter);
		adapter->tx_hwtstamp_समयouts++;
		e_warn(drv, "clearing Tx Timestamp hang\n");
	पूर्ण अन्यथा अणु
		/* reschedule to keep checking अगर it's not available yet */
		schedule_work(&adapter->ptp_tx_work);
	पूर्ण
पूर्ण

/**
 * ixgbe_ptp_rx_pktstamp - utility function to get RX समय stamp from buffer
 * @q_vector: काष्ठाure containing पूर्णांकerrupt and ring inक्रमmation
 * @skb: the packet
 *
 * This function will be called by the Rx routine of the बारtamp क्रम this
 * packet is stored in the buffer. The value is stored in little endian क्रमmat
 * starting at the end of the packet data.
 */
व्योम ixgbe_ptp_rx_pktstamp(काष्ठा ixgbe_q_vector *q_vector,
			   काष्ठा sk_buff *skb)
अणु
	__le64 regval;

	/* copy the bits out of the skb, and then trim the skb length */
	skb_copy_bits(skb, skb->len - IXGBE_TS_HDR_LEN, &regval,
		      IXGBE_TS_HDR_LEN);
	__pskb_trim(skb, skb->len - IXGBE_TS_HDR_LEN);

	/* The बारtamp is recorded in little endian क्रमmat, and is stored at
	 * the end of the packet.
	 *
	 * DWORD: N              N + 1      N + 2
	 * Field: End of Packet  SYSTIMH    SYSTIML
	 */
	ixgbe_ptp_convert_to_hwtstamp(q_vector->adapter, skb_hwtstamps(skb),
				      le64_to_cpu(regval));
पूर्ण

/**
 * ixgbe_ptp_rx_rgtstamp - utility function which checks क्रम RX समय stamp
 * @q_vector: काष्ठाure containing पूर्णांकerrupt and ring inक्रमmation
 * @skb: particular skb to send बारtamp with
 *
 * अगर the बारtamp is valid, we convert it पूर्णांकo the समयcounter ns
 * value, then store that result पूर्णांकo the shhwtstamps काष्ठाure which
 * is passed up the network stack
 */
व्योम ixgbe_ptp_rx_rgtstamp(काष्ठा ixgbe_q_vector *q_vector,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा ixgbe_adapter *adapter;
	काष्ठा ixgbe_hw *hw;
	u64 regval = 0;
	u32 tsyncrxctl;

	/* we cannot process बारtamps on a ring without a q_vector */
	अगर (!q_vector || !q_vector->adapter)
		वापस;

	adapter = q_vector->adapter;
	hw = &adapter->hw;

	/* Read the tsyncrxctl रेजिस्टर afterwards in order to prevent taking an
	 * I/O hit on every packet.
	 */

	tsyncrxctl = IXGBE_READ_REG(hw, IXGBE_TSYNCRXCTL);
	अगर (!(tsyncrxctl & IXGBE_TSYNCRXCTL_VALID))
		वापस;

	regval |= (u64)IXGBE_READ_REG(hw, IXGBE_RXSTMPL);
	regval |= (u64)IXGBE_READ_REG(hw, IXGBE_RXSTMPH) << 32;

	ixgbe_ptp_convert_to_hwtstamp(adapter, skb_hwtstamps(skb), regval);
पूर्ण

/**
 * ixgbe_ptp_get_ts_config - get current hardware बारtamping configuration
 * @adapter: poपूर्णांकer to adapter काष्ठाure
 * @अगरr: ioctl data
 *
 * This function वापसs the current बारtamping settings. Rather than
 * attempt to deस्थिरruct रेजिस्टरs to fill in the values, simply keep a copy
 * of the old settings around, and वापस a copy when requested.
 */
पूर्णांक ixgbe_ptp_get_ts_config(काष्ठा ixgbe_adapter *adapter, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config *config = &adapter->tstamp_config;

	वापस copy_to_user(अगरr->अगरr_data, config,
			    माप(*config)) ? -EFAULT : 0;
पूर्ण

/**
 * ixgbe_ptp_set_बारtamp_mode - setup the hardware क्रम the requested mode
 * @adapter: the निजी ixgbe adapter काष्ठाure
 * @config: the hwtstamp configuration requested
 *
 * Outgoing समय stamping can be enabled and disabled. Play nice and
 * disable it when requested, although it shouldn't cause any overhead
 * when no packet needs it. At most one packet in the queue may be
 * marked क्रम समय stamping, otherwise it would be impossible to tell
 * क्रम sure to which packet the hardware समय stamp beदीर्घs.
 *
 * Incoming समय stamping has to be configured via the hardware
 * filters. Not all combinations are supported, in particular event
 * type has to be specअगरied. Matching the kind of event packet is
 * not supported, with the exception of "all V2 events regardless of
 * level 2 or 4".
 *
 * Since hardware always बारtamps Path delay packets when बारtamping V2
 * packets, regardless of the type specअगरied in the रेजिस्टर, only use V2
 * Event mode. This more accurately tells the user what the hardware is going
 * to करो anyways.
 *
 * Note: this may modअगरy the hwtstamp configuration towards a more general
 * mode, अगर required to support the specअगरically requested mode.
 */
अटल पूर्णांक ixgbe_ptp_set_बारtamp_mode(काष्ठा ixgbe_adapter *adapter,
				 काष्ठा hwtstamp_config *config)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 tsync_tx_ctl = IXGBE_TSYNCTXCTL_ENABLED;
	u32 tsync_rx_ctl = IXGBE_TSYNCRXCTL_ENABLED;
	u32 tsync_rx_mtrl = PTP_EV_PORT << 16;
	bool is_l2 = false;
	u32 regval;

	/* reserved क्रम future extensions */
	अगर (config->flags)
		वापस -EINVAL;

	चयन (config->tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		tsync_tx_ctl = 0;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config->rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		tsync_rx_ctl = 0;
		tsync_rx_mtrl = 0;
		adapter->flags &= ~(IXGBE_FLAG_RX_HWTSTAMP_ENABLED |
				    IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER);
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		tsync_rx_ctl |= IXGBE_TSYNCRXCTL_TYPE_L4_V1;
		tsync_rx_mtrl |= IXGBE_RXMTRL_V1_SYNC_MSG;
		adapter->flags |= (IXGBE_FLAG_RX_HWTSTAMP_ENABLED |
				   IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER);
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		tsync_rx_ctl |= IXGBE_TSYNCRXCTL_TYPE_L4_V1;
		tsync_rx_mtrl |= IXGBE_RXMTRL_V1_DELAY_REQ_MSG;
		adapter->flags |= (IXGBE_FLAG_RX_HWTSTAMP_ENABLED |
				   IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER);
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		tsync_rx_ctl |= IXGBE_TSYNCRXCTL_TYPE_EVENT_V2;
		is_l2 = true;
		config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		adapter->flags |= (IXGBE_FLAG_RX_HWTSTAMP_ENABLED |
				   IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER);
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_NTP_ALL:
	हाल HWTSTAMP_FILTER_ALL:
		/* The X550 controller is capable of बारtamping all packets,
		 * which allows it to accept any filter.
		 */
		अगर (hw->mac.type >= ixgbe_mac_X550) अणु
			tsync_rx_ctl |= IXGBE_TSYNCRXCTL_TYPE_ALL;
			config->rx_filter = HWTSTAMP_FILTER_ALL;
			adapter->flags |= IXGBE_FLAG_RX_HWTSTAMP_ENABLED;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		/*
		 * रेजिस्टर RXMTRL must be set in order to करो V1 packets,
		 * thereक्रमe it is not possible to समय stamp both V1 Sync and
		 * Delay_Req messages and hardware करोes not support
		 * बारtamping all packets => वापस error
		 */
		adapter->flags &= ~(IXGBE_FLAG_RX_HWTSTAMP_ENABLED |
				    IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER);
		config->rx_filter = HWTSTAMP_FILTER_NONE;
		वापस -दुस्फल;
	पूर्ण

	अगर (hw->mac.type == ixgbe_mac_82598EB) अणु
		adapter->flags &= ~(IXGBE_FLAG_RX_HWTSTAMP_ENABLED |
				    IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER);
		अगर (tsync_rx_ctl | tsync_tx_ctl)
			वापस -दुस्फल;
		वापस 0;
	पूर्ण

	/* Per-packet बारtamping only works अगर the filter is set to all
	 * packets. Since this is desired, always बारtamp all packets as दीर्घ
	 * as any Rx filter was configured.
	 */
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		/* enable बारtamping all packets only अगर at least some
		 * packets were requested. Otherwise, play nice and disable
		 * बारtamping
		 */
		अगर (config->rx_filter == HWTSTAMP_FILTER_NONE)
			अवरोध;

		tsync_rx_ctl = IXGBE_TSYNCRXCTL_ENABLED |
			       IXGBE_TSYNCRXCTL_TYPE_ALL |
			       IXGBE_TSYNCRXCTL_TSIP_UT_EN;
		config->rx_filter = HWTSTAMP_FILTER_ALL;
		adapter->flags |= IXGBE_FLAG_RX_HWTSTAMP_ENABLED;
		adapter->flags &= ~IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER;
		is_l2 = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* define ethertype filter क्रम बारtamping L2 packets */
	अगर (is_l2)
		IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_1588),
				(IXGBE_ETQF_FILTER_EN | /* enable filter */
				 IXGBE_ETQF_1588 | /* enable बारtamping */
				 ETH_P_1588));     /* 1588 eth protocol type */
	अन्यथा
		IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_1588), 0);

	/* enable/disable TX */
	regval = IXGBE_READ_REG(hw, IXGBE_TSYNCTXCTL);
	regval &= ~IXGBE_TSYNCTXCTL_ENABLED;
	regval |= tsync_tx_ctl;
	IXGBE_WRITE_REG(hw, IXGBE_TSYNCTXCTL, regval);

	/* enable/disable RX */
	regval = IXGBE_READ_REG(hw, IXGBE_TSYNCRXCTL);
	regval &= ~(IXGBE_TSYNCRXCTL_ENABLED | IXGBE_TSYNCRXCTL_TYPE_MASK);
	regval |= tsync_rx_ctl;
	IXGBE_WRITE_REG(hw, IXGBE_TSYNCRXCTL, regval);

	/* define which PTP packets are समय stamped */
	IXGBE_WRITE_REG(hw, IXGBE_RXMTRL, tsync_rx_mtrl);

	IXGBE_WRITE_FLUSH(hw);

	/* clear TX/RX समय stamp रेजिस्टरs, just to be sure */
	ixgbe_ptp_clear_tx_बारtamp(adapter);
	IXGBE_READ_REG(hw, IXGBE_RXSTMPH);

	वापस 0;
पूर्ण

/**
 * ixgbe_ptp_set_ts_config - user entry poपूर्णांक क्रम बारtamp mode
 * @adapter: poपूर्णांकer to adapter काष्ठा
 * @अगरr: ioctl data
 *
 * Set hardware to requested mode. If unsupported, वापस an error with no
 * changes. Otherwise, store the mode क्रम future reference.
 */
पूर्णांक ixgbe_ptp_set_ts_config(काष्ठा ixgbe_adapter *adapter, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
	पूर्णांक err;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	err = ixgbe_ptp_set_बारtamp_mode(adapter, &config);
	अगर (err)
		वापस err;

	/* save these settings क्रम future reference */
	स_नकल(&adapter->tstamp_config, &config,
	       माप(adapter->tstamp_config));

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
		-EFAULT : 0;
पूर्ण

अटल व्योम ixgbe_ptp_link_speed_adjust(काष्ठा ixgbe_adapter *adapter,
					u32 *shअगरt, u32 *incval)
अणु
	/**
	 * Scale the NIC cycle counter by a large factor so that
	 * relatively small corrections to the frequency can be added
	 * or subtracted. The drawbacks of a large factor include
	 * (a) the घड़ी रेजिस्टर overflows more quickly, (b) the cycle
	 * counter काष्ठाure must be able to convert the sysसमय value
	 * to nanoseconds using only a multiplier and a right-shअगरt,
	 * and (c) the value must fit within the timinca रेजिस्टर space
	 * => math based on पूर्णांकernal DMA घड़ी rate and available bits
	 *
	 * Note that when there is no link, पूर्णांकernal DMA घड़ी is same as when
	 * link speed is 10Gb. Set the रेजिस्टरs correctly even when link is
	 * करोwn to preserve the घड़ी setting
	 */
	चयन (adapter->link_speed) अणु
	हाल IXGBE_LINK_SPEED_100_FULL:
		*shअगरt = IXGBE_INCVAL_SHIFT_100;
		*incval = IXGBE_INCVAL_100;
		अवरोध;
	हाल IXGBE_LINK_SPEED_1GB_FULL:
		*shअगरt = IXGBE_INCVAL_SHIFT_1GB;
		*incval = IXGBE_INCVAL_1GB;
		अवरोध;
	हाल IXGBE_LINK_SPEED_10GB_FULL:
	शेष:
		*shअगरt = IXGBE_INCVAL_SHIFT_10GB;
		*incval = IXGBE_INCVAL_10GB;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ixgbe_ptp_start_cyclecounter - create the cycle counter from hw
 * @adapter: poपूर्णांकer to the adapter काष्ठाure
 *
 * This function should be called to set the proper values क्रम the TIMINCA
 * रेजिस्टर and tell the cyclecounter काष्ठाure what the tick rate of SYSTIME
 * is. It करोes not directly modअगरy SYSTIME रेजिस्टरs or the समयcounter
 * काष्ठाure. It should be called whenever a new TIMINCA value is necessary,
 * such as during initialization or when the link speed changes.
 */
व्योम ixgbe_ptp_start_cyclecounter(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा cyclecounter cc;
	अचिन्हित दीर्घ flags;
	u32 incval = 0;
	u32 tsauxc = 0;
	u32 fuse0 = 0;

	/* For some of the boards below this mask is technically incorrect.
	 * The बारtamp mask overflows at approximately 61bits. However the
	 * particular hardware करोes not overflow on an even biपंचांगask value.
	 * Instead, it overflows due to conversion of upper 32bits billions of
	 * cycles. Timecounters are not really पूर्णांकended क्रम this purpose so
	 * they करो not properly function अगर the overflow poपूर्णांक isn't 2^N-1.
	 * However, the actual SYSTIME values in question take ~138 years to
	 * overflow. In practice this means they won't actually overflow. A
	 * proper fix to this problem would require modअगरication of the
	 * समयcounter delta calculations.
	 */
	cc.mask = CLOCKSOURCE_MASK(64);
	cc.mult = 1;
	cc.shअगरt = 0;

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_X550EM_x:
		/* SYSTIME assumes X550EM_x board frequency is 300Mhz, and is
		 * deचिन्हित to represent seconds and nanoseconds when this is
		 * the हाल. However, some revisions of hardware have a 400Mhz
		 * घड़ी and we have to compensate क्रम this frequency
		 * variation using corrected mult and shअगरt values.
		 */
		fuse0 = IXGBE_READ_REG(hw, IXGBE_FUSES0_GROUP(0));
		अगर (!(fuse0 & IXGBE_FUSES0_300MHZ)) अणु
			cc.mult = 3;
			cc.shअगरt = 2;
		पूर्ण
		fallthrough;
	हाल ixgbe_mac_x550em_a:
	हाल ixgbe_mac_X550:
		cc.पढ़ो = ixgbe_ptp_पढ़ो_X550;

		/* enable SYSTIME counter */
		IXGBE_WRITE_REG(hw, IXGBE_SYSTIMR, 0);
		IXGBE_WRITE_REG(hw, IXGBE_SYSTIML, 0);
		IXGBE_WRITE_REG(hw, IXGBE_SYSTIMH, 0);
		tsauxc = IXGBE_READ_REG(hw, IXGBE_TSAUXC);
		IXGBE_WRITE_REG(hw, IXGBE_TSAUXC,
				tsauxc & ~IXGBE_TSAUXC_DISABLE_SYSTIME);
		IXGBE_WRITE_REG(hw, IXGBE_TSIM, IXGBE_TSIM_TXTS);
		IXGBE_WRITE_REG(hw, IXGBE_EIMS, IXGBE_EIMS_TIMESYNC);

		IXGBE_WRITE_FLUSH(hw);
		अवरोध;
	हाल ixgbe_mac_X540:
		cc.पढ़ो = ixgbe_ptp_पढ़ो_82599;

		ixgbe_ptp_link_speed_adjust(adapter, &cc.shअगरt, &incval);
		IXGBE_WRITE_REG(hw, IXGBE_TIMINCA, incval);
		अवरोध;
	हाल ixgbe_mac_82599EB:
		cc.पढ़ो = ixgbe_ptp_पढ़ो_82599;

		ixgbe_ptp_link_speed_adjust(adapter, &cc.shअगरt, &incval);
		incval >>= IXGBE_INCVAL_SHIFT_82599;
		cc.shअगरt -= IXGBE_INCVAL_SHIFT_82599;
		IXGBE_WRITE_REG(hw, IXGBE_TIMINCA,
				BIT(IXGBE_INCPER_SHIFT_82599) | incval);
		अवरोध;
	शेष:
		/* other devices aren't supported */
		वापस;
	पूर्ण

	/* update the base incval used to calculate frequency adjusपंचांगent */
	WRITE_ONCE(adapter->base_incval, incval);
	smp_mb();

	/* need lock to prevent incorrect पढ़ो जबतक modअगरying cyclecounter */
	spin_lock_irqsave(&adapter->पंचांगreg_lock, flags);
	स_नकल(&adapter->hw_cc, &cc, माप(adapter->hw_cc));
	spin_unlock_irqrestore(&adapter->पंचांगreg_lock, flags);
पूर्ण

/**
 * ixgbe_ptp_reset
 * @adapter: the ixgbe निजी board काष्ठाure
 *
 * When the MAC resets, all the hardware bits क्रम बारync are reset. This
 * function is used to re-enable the device क्रम PTP based on current settings.
 * We करो lose the current घड़ी समय, so just reset the cyclecounter to the
 * प्रणाली real घड़ी समय.
 *
 * This function will मुख्यtain hwtstamp_config settings, and resets the SDP
 * output अगर it was enabled.
 */
व्योम ixgbe_ptp_reset(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ flags;

	/* reset the hardware बारtamping mode */
	ixgbe_ptp_set_बारtamp_mode(adapter, &adapter->tstamp_config);

	/* 82598 करोes not support PTP */
	अगर (hw->mac.type == ixgbe_mac_82598EB)
		वापस;

	ixgbe_ptp_start_cyclecounter(adapter);

	spin_lock_irqsave(&adapter->पंचांगreg_lock, flags);
	समयcounter_init(&adapter->hw_tc, &adapter->hw_cc,
			 kसमय_प्रकारo_ns(kसमय_get_real()));
	spin_unlock_irqrestore(&adapter->पंचांगreg_lock, flags);

	adapter->last_overflow_check = jअगरfies;

	/* Now that the shअगरt has been calculated and the sysसमय
	 * रेजिस्टरs reset, (re-)enable the Clock out feature
	 */
	अगर (adapter->ptp_setup_sdp)
		adapter->ptp_setup_sdp(adapter);
पूर्ण

/**
 * ixgbe_ptp_create_घड़ी
 * @adapter: the ixgbe निजी adapter काष्ठाure
 *
 * This function perक्रमms setup of the user entry poपूर्णांक function table and
 * initializes the PTP घड़ी device, which is used to access the घड़ी-like
 * features of the PTP core. It will be called by ixgbe_ptp_init, and may
 * reuse a previously initialized घड़ी (such as during a suspend/resume
 * cycle).
 */
अटल दीर्घ ixgbe_ptp_create_घड़ी(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	दीर्घ err;

	/* करो nothing अगर we alपढ़ोy have a घड़ी device */
	अगर (!IS_ERR_OR_शून्य(adapter->ptp_घड़ी))
		वापस 0;

	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_X540:
		snम_लिखो(adapter->ptp_caps.name,
			 माप(adapter->ptp_caps.name),
			 "%s", netdev->name);
		adapter->ptp_caps.owner = THIS_MODULE;
		adapter->ptp_caps.max_adj = 250000000;
		adapter->ptp_caps.n_alarm = 0;
		adapter->ptp_caps.n_ext_ts = 0;
		adapter->ptp_caps.n_per_out = 0;
		adapter->ptp_caps.pps = 1;
		adapter->ptp_caps.adjfreq = ixgbe_ptp_adjfreq_82599;
		adapter->ptp_caps.adjसमय = ixgbe_ptp_adjसमय;
		adapter->ptp_caps.समय_लोx64 = ixgbe_ptp_समय_लोx;
		adapter->ptp_caps.समय_रखो64 = ixgbe_ptp_समय_रखो;
		adapter->ptp_caps.enable = ixgbe_ptp_feature_enable;
		adapter->ptp_setup_sdp = ixgbe_ptp_setup_sdp_X540;
		अवरोध;
	हाल ixgbe_mac_82599EB:
		snम_लिखो(adapter->ptp_caps.name,
			 माप(adapter->ptp_caps.name),
			 "%s", netdev->name);
		adapter->ptp_caps.owner = THIS_MODULE;
		adapter->ptp_caps.max_adj = 250000000;
		adapter->ptp_caps.n_alarm = 0;
		adapter->ptp_caps.n_ext_ts = 0;
		adapter->ptp_caps.n_per_out = 0;
		adapter->ptp_caps.pps = 0;
		adapter->ptp_caps.adjfreq = ixgbe_ptp_adjfreq_82599;
		adapter->ptp_caps.adjसमय = ixgbe_ptp_adjसमय;
		adapter->ptp_caps.समय_लोx64 = ixgbe_ptp_समय_लोx;
		adapter->ptp_caps.समय_रखो64 = ixgbe_ptp_समय_रखो;
		adapter->ptp_caps.enable = ixgbe_ptp_feature_enable;
		अवरोध;
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		snम_लिखो(adapter->ptp_caps.name, 16, "%s", netdev->name);
		adapter->ptp_caps.owner = THIS_MODULE;
		adapter->ptp_caps.max_adj = 30000000;
		adapter->ptp_caps.n_alarm = 0;
		adapter->ptp_caps.n_ext_ts = 0;
		adapter->ptp_caps.n_per_out = 0;
		adapter->ptp_caps.pps = 1;
		adapter->ptp_caps.adjfreq = ixgbe_ptp_adjfreq_X550;
		adapter->ptp_caps.adjसमय = ixgbe_ptp_adjसमय;
		adapter->ptp_caps.समय_लोx64 = ixgbe_ptp_समय_लोx;
		adapter->ptp_caps.समय_रखो64 = ixgbe_ptp_समय_रखो;
		adapter->ptp_caps.enable = ixgbe_ptp_feature_enable;
		adapter->ptp_setup_sdp = ixgbe_ptp_setup_sdp_X550;
		अवरोध;
	शेष:
		adapter->ptp_घड़ी = शून्य;
		adapter->ptp_setup_sdp = शून्य;
		वापस -EOPNOTSUPP;
	पूर्ण

	adapter->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&adapter->ptp_caps,
						&adapter->pdev->dev);
	अगर (IS_ERR(adapter->ptp_घड़ी)) अणु
		err = PTR_ERR(adapter->ptp_घड़ी);
		adapter->ptp_घड़ी = शून्य;
		e_dev_err("ptp_clock_register failed\n");
		वापस err;
	पूर्ण अन्यथा अगर (adapter->ptp_घड़ी)
		e_dev_info("registered PHC device on %s\n", netdev->name);

	/* set शेष बारtamp mode to disabled here. We करो this in
	 * create_घड़ी instead of init, because we करोn't want to override the
	 * previous settings during a resume cycle.
	 */
	adapter->tstamp_config.rx_filter = HWTSTAMP_FILTER_NONE;
	adapter->tstamp_config.tx_type = HWTSTAMP_TX_OFF;

	वापस 0;
पूर्ण

/**
 * ixgbe_ptp_init
 * @adapter: the ixgbe निजी adapter काष्ठाure
 *
 * This function perक्रमms the required steps क्रम enabling PTP
 * support. If PTP support has alपढ़ोy been loaded it simply calls the
 * cyclecounter init routine and निकासs.
 */
व्योम ixgbe_ptp_init(काष्ठा ixgbe_adapter *adapter)
अणु
	/* initialize the spin lock first since we can't control when a user
	 * will call the entry functions once we have initialized the घड़ी
	 * device
	 */
	spin_lock_init(&adapter->पंचांगreg_lock);

	/* obtain a PTP device, or re-use an existing device */
	अगर (ixgbe_ptp_create_घड़ी(adapter))
		वापस;

	/* we have a घड़ी so we can initialize work now */
	INIT_WORK(&adapter->ptp_tx_work, ixgbe_ptp_tx_hwtstamp_work);

	/* reset the PTP related hardware bits */
	ixgbe_ptp_reset(adapter);

	/* enter the IXGBE_PTP_RUNNING state */
	set_bit(__IXGBE_PTP_RUNNING, &adapter->state);

	वापस;
पूर्ण

/**
 * ixgbe_ptp_suspend - stop PTP work items
 * @adapter: poपूर्णांकer to adapter काष्ठा
 *
 * this function suspends PTP activity, and prevents more PTP work from being
 * generated, but करोes not destroy the PTP घड़ी device.
 */
व्योम ixgbe_ptp_suspend(काष्ठा ixgbe_adapter *adapter)
अणु
	/* Leave the IXGBE_PTP_RUNNING state. */
	अगर (!test_and_clear_bit(__IXGBE_PTP_RUNNING, &adapter->state))
		वापस;

	adapter->flags2 &= ~IXGBE_FLAG2_PTP_PPS_ENABLED;
	अगर (adapter->ptp_setup_sdp)
		adapter->ptp_setup_sdp(adapter);

	/* ensure that we cancel any pending PTP Tx work item in progress */
	cancel_work_sync(&adapter->ptp_tx_work);
	ixgbe_ptp_clear_tx_बारtamp(adapter);
पूर्ण

/**
 * ixgbe_ptp_stop - बंद the PTP device
 * @adapter: poपूर्णांकer to adapter काष्ठा
 *
 * completely destroy the PTP device, should only be called when the device is
 * being fully बंदd.
 */
व्योम ixgbe_ptp_stop(काष्ठा ixgbe_adapter *adapter)
अणु
	/* first, suspend PTP activity */
	ixgbe_ptp_suspend(adapter);

	/* disable the PTP घड़ी device */
	अगर (adapter->ptp_घड़ी) अणु
		ptp_घड़ी_unरेजिस्टर(adapter->ptp_घड़ी);
		adapter->ptp_घड़ी = शून्य;
		e_dev_info("removed PHC on %s\n",
			   adapter->netdev->name);
	पूर्ण
पूर्ण
