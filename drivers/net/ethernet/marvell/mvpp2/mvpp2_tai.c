<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell PP2.2 TAI support
 *
 * Note:
 *   Do NOT use the event capture support.
 *   Do Not even set the MPP muxes to allow PTP_EVENT_REQ to be used.
 *   It will disrupt the operation of this driver, and there is nothing
 *   that this driver can करो to prevent that.  Even using PTP_EVENT_REQ
 *   as an output will be seen as a trigger input, which can't be masked.
 *   When ever a trigger input is seen, the action in the TCFCR0_TCF
 *   field will be perक्रमmed - whether it is a set, increment, decrement
 *   पढ़ो, or frequency update.
 *
 * Other notes (useful, not specअगरied in the करोcumentation):
 * - PTP_PULSE_OUT (PTP_EVENT_REQ MPP)
 *   It looks like the hardware can't generate a pulse at nsec=0. (The
 *   output करोesn't trigger अगर the nsec field is zero.)
 *   Note: when configured as an output via the रेजिस्टर at 0xfX441120,
 *   the input is still very much alive, and will trigger the current TCF
 *   function.
 * - PTP_CLK_OUT (PTP_TRIG_GEN MPP)
 *   This generates a "PPS" संकेत determined by the CCC रेजिस्टरs. It
 *   seems this is not aligned to the TOD counter in any way (it may be
 *   initially, but अगर you specअगरy a non-round second पूर्णांकerval, it won't,
 *   and you can't easily get it back.)
 * - PTP_PCLK_OUT
 *   This generates a 50% duty cycle घड़ी based on the TOD counter, and
 *   seems it can be set to any period of 1ns resolution. It is probably
 *   limited by the TOD step size. Its period is defined by the PCLK_CCC
 *   रेजिस्टरs. Again, its alignment to the second is questionable.
 *
 * Consequently, we support none of these.
 */
#समावेश <linux/पन.स>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/slab.h>

#समावेश "mvpp2.h"

#घोषणा CR0_SW_NRESET			BIT(0)

#घोषणा TCFCR0_PHASE_UPDATE_ENABLE	BIT(8)
#घोषणा TCFCR0_TCF_MASK			(7 << 2)
#घोषणा TCFCR0_TCF_UPDATE		(0 << 2)
#घोषणा TCFCR0_TCF_FREQUPDATE		(1 << 2)
#घोषणा TCFCR0_TCF_INCREMENT		(2 << 2)
#घोषणा TCFCR0_TCF_DECREMENT		(3 << 2)
#घोषणा TCFCR0_TCF_CAPTURE		(4 << 2)
#घोषणा TCFCR0_TCF_NOP			(7 << 2)
#घोषणा TCFCR0_TCF_TRIGGER		BIT(0)

#घोषणा TCSR_CAPTURE_1_VALID		BIT(1)
#घोषणा TCSR_CAPTURE_0_VALID		BIT(0)

काष्ठा mvpp2_tai अणु
	काष्ठा ptp_घड़ी_info caps;
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	व्योम __iomem *base;
	spinlock_t lock;
	u64 period;		// nanosecond period in 32.32 fixed poपूर्णांक
	/* This बारtamp is updated every two seconds */
	काष्ठा बारpec64 stamp;
पूर्ण;

अटल व्योम mvpp2_tai_modअगरy(व्योम __iomem *reg, u32 mask, u32 set)
अणु
	u32 val;

	val = पढ़ोl_relaxed(reg) & ~mask;
	val |= set & mask;
	ग_लिखोl(val, reg);
पूर्ण

अटल व्योम mvpp2_tai_ग_लिखो(u32 val, व्योम __iomem *reg)
अणु
	ग_लिखोl_relaxed(val & 0xffff, reg);
पूर्ण

अटल u32 mvpp2_tai_पढ़ो(व्योम __iomem *reg)
अणु
	वापस पढ़ोl_relaxed(reg) & 0xffff;
पूर्ण

अटल काष्ठा mvpp2_tai *ptp_to_tai(काष्ठा ptp_घड़ी_info *ptp)
अणु
	वापस container_of(ptp, काष्ठा mvpp2_tai, caps);
पूर्ण

अटल व्योम mvpp22_tai_पढ़ो_ts(काष्ठा बारpec64 *ts, व्योम __iomem *base)
अणु
	ts->tv_sec = (u64)mvpp2_tai_पढ़ो(base + 0) << 32 |
		     mvpp2_tai_पढ़ो(base + 4) << 16 |
		     mvpp2_tai_पढ़ो(base + 8);

	ts->tv_nsec = mvpp2_tai_पढ़ो(base + 12) << 16 |
		      mvpp2_tai_पढ़ो(base + 16);

	/* Read and discard fractional part */
	पढ़ोl_relaxed(base + 20);
	पढ़ोl_relaxed(base + 24);
पूर्ण

अटल व्योम mvpp2_tai_ग_लिखो_tlv(स्थिर काष्ठा बारpec64 *ts, u32 frac,
			        व्योम __iomem *base)
अणु
	mvpp2_tai_ग_लिखो(ts->tv_sec >> 32, base + MVPP22_TAI_TLV_SEC_HIGH);
	mvpp2_tai_ग_लिखो(ts->tv_sec >> 16, base + MVPP22_TAI_TLV_SEC_MED);
	mvpp2_tai_ग_लिखो(ts->tv_sec, base + MVPP22_TAI_TLV_SEC_LOW);
	mvpp2_tai_ग_लिखो(ts->tv_nsec >> 16, base + MVPP22_TAI_TLV_न_अंकO_HIGH);
	mvpp2_tai_ग_लिखो(ts->tv_nsec, base + MVPP22_TAI_TLV_न_अंकO_LOW);
	mvpp2_tai_ग_लिखो(frac >> 16, base + MVPP22_TAI_TLV_FRAC_HIGH);
	mvpp2_tai_ग_लिखो(frac, base + MVPP22_TAI_TLV_FRAC_LOW);
पूर्ण

अटल व्योम mvpp2_tai_op(u32 op, व्योम __iomem *base)
अणु
	/* Trigger the operation. Note that an बाह्यal unmaskable
	 * event on PTP_EVENT_REQ will also trigger this action.
	 */
	mvpp2_tai_modअगरy(base + MVPP22_TAI_TCFCR0,
			 TCFCR0_TCF_MASK | TCFCR0_TCF_TRIGGER,
			 op | TCFCR0_TCF_TRIGGER);
	mvpp2_tai_modअगरy(base + MVPP22_TAI_TCFCR0, TCFCR0_TCF_MASK,
			 TCFCR0_TCF_NOP);
पूर्ण

/* The adjusपंचांगent has a range of +0.5ns to -0.5ns in 2^32 steps, so has units
 * of 2^-32 ns.
 *
 * units(s) = 1 / (2^32 * 10^9)
 * fractional = असल_scaled_ppm / (2^16 * 10^6)
 *
 * What we want to achieve:
 *  freq_adjusted = freq_nominal * (1 + fractional)
 *  freq_delta = freq_adjusted - freq_nominal => positive = faster
 *  freq_delta = freq_nominal * (1 + fractional) - freq_nominal
 * So: freq_delta = freq_nominal * fractional
 *
 * However, we are dealing with periods, so:
 *  period_adjusted = period_nominal / (1 + fractional)
 *  period_delta = period_nominal - period_adjusted => positive = faster
 *  period_delta = period_nominal * fractional / (1 + fractional)
 *
 * Hence:
 *  period_delta = period_nominal * असल_scaled_ppm /
 *		   (2^16 * 10^6 + असल_scaled_ppm)
 *
 * To aव्योम overflow, we reduce both sides of the भागide operation by a factor
 * of 16.
 */
अटल u64 mvpp22_calc_frac_ppm(काष्ठा mvpp2_tai *tai, दीर्घ असल_scaled_ppm)
अणु
	u64 val = tai->period * असल_scaled_ppm >> 4;

	वापस भाग_u64(val, (1000000 << 12) + (असल_scaled_ppm >> 4));
पूर्ण

अटल s32 mvpp22_calc_max_adj(काष्ठा mvpp2_tai *tai)
अणु
	वापस 1000000;
पूर्ण

अटल पूर्णांक mvpp22_tai_adjfine(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm)
अणु
	काष्ठा mvpp2_tai *tai = ptp_to_tai(ptp);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *base;
	bool neg_adj;
	s32 frac;
	u64 val;

	neg_adj = scaled_ppm < 0;
	अगर (neg_adj)
		scaled_ppm = -scaled_ppm;

	val = mvpp22_calc_frac_ppm(tai, scaled_ppm);

	/* Convert to a चिन्हित 32-bit adjusपंचांगent */
	अगर (neg_adj) अणु
		/* -S32_MIN warns, -val < S32_MIN fails, so go क्रम the easy
		 * solution.
		 */
		अगर (val > 0x80000000)
			वापस -दुस्फल;

		frac = -val;
	पूर्ण अन्यथा अणु
		अगर (val > S32_MAX)
			वापस -दुस्फल;

		frac = val;
	पूर्ण

	base = tai->base;
	spin_lock_irqsave(&tai->lock, flags);
	mvpp2_tai_ग_लिखो(frac >> 16, base + MVPP22_TAI_TLV_FRAC_HIGH);
	mvpp2_tai_ग_लिखो(frac, base + MVPP22_TAI_TLV_FRAC_LOW);
	mvpp2_tai_op(TCFCR0_TCF_FREQUPDATE, base);
	spin_unlock_irqrestore(&tai->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp22_tai_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा mvpp2_tai *tai = ptp_to_tai(ptp);
	काष्ठा बारpec64 ts;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *base;
	u32 tcf;

	/* We can't deal with S64_MIN */
	अगर (delta == S64_MIN)
		वापस -दुस्फल;

	अगर (delta < 0) अणु
		delta = -delta;
		tcf = TCFCR0_TCF_DECREMENT;
	पूर्ण अन्यथा अणु
		tcf = TCFCR0_TCF_INCREMENT;
	पूर्ण

	ts = ns_to_बारpec64(delta);

	base = tai->base;
	spin_lock_irqsave(&tai->lock, flags);
	mvpp2_tai_ग_लिखो_tlv(&ts, 0, base);
	mvpp2_tai_op(tcf, base);
	spin_unlock_irqrestore(&tai->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp22_tai_समय_लोx64(काष्ठा ptp_घड़ी_info *ptp,
				 काष्ठा बारpec64 *ts,
				 काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा mvpp2_tai *tai = ptp_to_tai(ptp);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *base;
	u32 tcsr;
	पूर्णांक ret;

	base = tai->base;
	spin_lock_irqsave(&tai->lock, flags);
	/* XXX: the only way to पढ़ो the PTP समय is क्रम the CPU to trigger
	 * an event. However, there is no way to distinguish between the CPU
	 * triggered event, and an बाह्यal event on PTP_EVENT_REQ. So this
	 * is incompatible with बाह्यal use of PTP_EVENT_REQ.
	 */
	ptp_पढ़ो_प्रणाली_prets(sts);
	mvpp2_tai_modअगरy(base + MVPP22_TAI_TCFCR0,
			 TCFCR0_TCF_MASK | TCFCR0_TCF_TRIGGER,
			 TCFCR0_TCF_CAPTURE | TCFCR0_TCF_TRIGGER);
	ptp_पढ़ो_प्रणाली_postts(sts);
	mvpp2_tai_modअगरy(base + MVPP22_TAI_TCFCR0, TCFCR0_TCF_MASK,
			 TCFCR0_TCF_NOP);

	tcsr = पढ़ोl(base + MVPP22_TAI_TCSR);
	अगर (tcsr & TCSR_CAPTURE_1_VALID) अणु
		mvpp22_tai_पढ़ो_ts(ts, base + MVPP22_TAI_TCV1_SEC_HIGH);
		ret = 0;
	पूर्ण अन्यथा अगर (tcsr & TCSR_CAPTURE_0_VALID) अणु
		mvpp22_tai_पढ़ो_ts(ts, base + MVPP22_TAI_TCV0_SEC_HIGH);
		ret = 0;
	पूर्ण अन्यथा अणु
		/* We करोn't seem to have a पढ़ोing... */
		ret = -EBUSY;
	पूर्ण
	spin_unlock_irqrestore(&tai->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक mvpp22_tai_समय_रखो64(काष्ठा ptp_घड़ी_info *ptp,
				स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा mvpp2_tai *tai = ptp_to_tai(ptp);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *base;

	base = tai->base;
	spin_lock_irqsave(&tai->lock, flags);
	mvpp2_tai_ग_लिखो_tlv(ts, 0, base);

	/* Trigger an update to load the value from the TLV रेजिस्टरs
	 * पूर्णांकo the TOD counter. Note that an बाह्यal unmaskable event on
	 * PTP_EVENT_REQ will also trigger this action.
	 */
	mvpp2_tai_modअगरy(base + MVPP22_TAI_TCFCR0,
			 TCFCR0_PHASE_UPDATE_ENABLE |
			 TCFCR0_TCF_MASK | TCFCR0_TCF_TRIGGER,
			 TCFCR0_TCF_UPDATE | TCFCR0_TCF_TRIGGER);
	mvpp2_tai_modअगरy(base + MVPP22_TAI_TCFCR0, TCFCR0_TCF_MASK,
			 TCFCR0_TCF_NOP);
	spin_unlock_irqrestore(&tai->lock, flags);

	वापस 0;
पूर्ण

अटल दीर्घ mvpp22_tai_aux_work(काष्ठा ptp_घड़ी_info *ptp)
अणु
	काष्ठा mvpp2_tai *tai = ptp_to_tai(ptp);

	mvpp22_tai_समय_लोx64(ptp, &tai->stamp, शून्य);

	वापस msecs_to_jअगरfies(2000);
पूर्ण

अटल व्योम mvpp22_tai_set_step(काष्ठा mvpp2_tai *tai)
अणु
	व्योम __iomem *base = tai->base;
	u32 nano, frac;

	nano = upper_32_bits(tai->period);
	frac = lower_32_bits(tai->period);

	/* As the fractional nanosecond is a चिन्हित offset, अगर the MSB (sign)
	 * bit is set, we have to increment the whole nanoseconds.
	 */
	अगर (frac >= 0x80000000)
		nano += 1;

	mvpp2_tai_ग_लिखो(nano, base + MVPP22_TAI_TOD_STEP_न_अंकO_CR);
	mvpp2_tai_ग_लिखो(frac >> 16, base + MVPP22_TAI_TOD_STEP_FRAC_HIGH);
	mvpp2_tai_ग_लिखो(frac, base + MVPP22_TAI_TOD_STEP_FRAC_LOW);
पूर्ण

अटल व्योम mvpp22_tai_init(काष्ठा mvpp2_tai *tai)
अणु
	व्योम __iomem *base = tai->base;

	mvpp22_tai_set_step(tai);

	/* Release the TAI reset */
	mvpp2_tai_modअगरy(base + MVPP22_TAI_CR0, CR0_SW_NRESET, CR0_SW_NRESET);
पूर्ण

पूर्णांक mvpp22_tai_ptp_घड़ी_index(काष्ठा mvpp2_tai *tai)
अणु
	वापस ptp_घड़ी_index(tai->ptp_घड़ी);
पूर्ण

व्योम mvpp22_tai_tstamp(काष्ठा mvpp2_tai *tai, u32 tstamp,
		       काष्ठा skb_shared_hwtstamps *hwtstamp)
अणु
	काष्ठा बारpec64 ts;
	पूर्णांक delta;

	/* The tstamp consists of 2 bits of seconds and 30 bits of nanoseconds.
	 * We use our stored बारtamp (tai->stamp) to क्रमm a full बारtamp,
	 * and we must पढ़ो the seconds exactly once.
	 */
	ts.tv_sec = READ_ONCE(tai->stamp.tv_sec);
	ts.tv_nsec = tstamp & 0x3fffffff;

	/* Calculate the delta in seconds between our stored बारtamp and
	 * the value पढ़ो from the queue. Allow बारtamps one second in the
	 * past, otherwise consider them to be in the future.
	 */
	delta = ((tstamp >> 30) - (ts.tv_sec & 3)) & 3;
	अगर (delta == 3)
		delta -= 4;
	ts.tv_sec += delta;

	स_रखो(hwtstamp, 0, माप(*hwtstamp));
	hwtstamp->hwtstamp = बारpec64_to_kसमय(ts);
पूर्ण

व्योम mvpp22_tai_start(काष्ठा mvpp2_tai *tai)
अणु
	दीर्घ delay;

	delay = mvpp22_tai_aux_work(&tai->caps);

	ptp_schedule_worker(tai->ptp_घड़ी, delay);
पूर्ण

व्योम mvpp22_tai_stop(काष्ठा mvpp2_tai *tai)
अणु
	ptp_cancel_worker_sync(tai->ptp_घड़ी);
पूर्ण

अटल व्योम mvpp22_tai_हटाओ(व्योम *priv)
अणु
	काष्ठा mvpp2_tai *tai = priv;

	अगर (!IS_ERR(tai->ptp_घड़ी))
		ptp_घड़ी_unरेजिस्टर(tai->ptp_घड़ी);
पूर्ण

पूर्णांक mvpp22_tai_probe(काष्ठा device *dev, काष्ठा mvpp2 *priv)
अणु
	काष्ठा mvpp2_tai *tai;
	पूर्णांक ret;

	tai = devm_kzalloc(dev, माप(*tai), GFP_KERNEL);
	अगर (!tai)
		वापस -ENOMEM;

	spin_lock_init(&tai->lock);

	tai->base = priv->अगरace_base;

	/* The step size consists of three रेजिस्टरs - a 16-bit nanosecond step
	 * size, and a 32-bit fractional nanosecond step size split over two
	 * रेजिस्टरs. The fractional nanosecond step size has units of 2^-32ns.
	 *
	 * To calculate this, we calculate:
	 *   (10^9 + freq / 2) / (freq * 2^-32)
	 * which gives us the nanosecond step to the nearest पूर्णांकeger in 16.32
	 * fixed poपूर्णांक क्रमmat, and the fractional part of the step size with
	 * the MSB inverted.  With rounding of the fractional nanosecond, and
	 * simplअगरication, this becomes:
	 *   (10^9 << 32 + freq << 31 + (freq + 1) >> 1) / freq
	 *
	 * So:
	 *   भाग = (10^9 << 32 + freq << 31 + (freq + 1) >> 1) / freq
	 *   nano = upper_32_bits(भाग);
	 *   frac = lower_32_bits(भाग) ^ 0x80000000;
	 * Will give the values क्रम the रेजिस्टरs.
	 *
	 * This is all seems perfect, but alas it is not when considering the
	 * whole story.  The प्रणाली is घड़ीed from 25MHz, which is multiplied
	 * by a PLL to 1GHz, and then भागided by three, giving 333333333Hz
	 * (recurring).  This gives exactly 3ns, but using 333333333Hz with
	 * the above gives an error of 13*2^-32ns.
	 *
	 * Consequently, we use the period rather than calculating from the
	 * frequency.
	 */
	tai->period = 3ULL << 32;

	mvpp22_tai_init(tai);

	tai->caps.owner = THIS_MODULE;
	strscpy(tai->caps.name, "Marvell PP2.2", माप(tai->caps.name));
	tai->caps.max_adj = mvpp22_calc_max_adj(tai);
	tai->caps.adjfine = mvpp22_tai_adjfine;
	tai->caps.adjसमय = mvpp22_tai_adjसमय;
	tai->caps.समय_लोx64 = mvpp22_tai_समय_लोx64;
	tai->caps.समय_रखो64 = mvpp22_tai_समय_रखो64;
	tai->caps.करो_aux_work = mvpp22_tai_aux_work;

	ret = devm_add_action(dev, mvpp22_tai_हटाओ, tai);
	अगर (ret)
		वापस ret;

	tai->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&tai->caps, dev);
	अगर (IS_ERR(tai->ptp_घड़ी))
		वापस PTR_ERR(tai->ptp_घड़ी);

	priv->tai = tai;

	वापस 0;
पूर्ण
