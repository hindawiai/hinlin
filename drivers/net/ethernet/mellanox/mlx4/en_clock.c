<शैली गुरु>
/*
 * Copyright (c) 2012 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
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

#समावेश <linux/mlx4/device.h>
#समावेश <linux/घड़ीsource.h>

#समावेश "mlx4_en.h"

/* mlx4_en_पढ़ो_घड़ी - पढ़ो raw cycle counter (to be used by समय counter)
 */
अटल u64 mlx4_en_पढ़ो_घड़ी(स्थिर काष्ठा cyclecounter *tc)
अणु
	काष्ठा mlx4_en_dev *mdev =
		container_of(tc, काष्ठा mlx4_en_dev, cycles);
	काष्ठा mlx4_dev *dev = mdev->dev;

	वापस mlx4_पढ़ो_घड़ी(dev) & tc->mask;
पूर्ण

u64 mlx4_en_get_cqe_ts(काष्ठा mlx4_cqe *cqe)
अणु
	u64 hi, lo;
	काष्ठा mlx4_ts_cqe *ts_cqe = (काष्ठा mlx4_ts_cqe *)cqe;

	lo = (u64)be16_to_cpu(ts_cqe->बारtamp_lo);
	hi = ((u64)be32_to_cpu(ts_cqe->बारtamp_hi) + !lo) << 16;

	वापस hi | lo;
पूर्ण

व्योम mlx4_en_fill_hwtstamps(काष्ठा mlx4_en_dev *mdev,
			    काष्ठा skb_shared_hwtstamps *hwts,
			    u64 बारtamp)
अणु
	अचिन्हित पूर्णांक seq;
	u64 nsec;

	करो अणु
		seq = पढ़ो_seqbegin(&mdev->घड़ी_lock);
		nsec = समयcounter_cyc2समय(&mdev->घड़ी, बारtamp);
	पूर्ण जबतक (पढ़ो_seqretry(&mdev->घड़ी_lock, seq));

	स_रखो(hwts, 0, माप(काष्ठा skb_shared_hwtstamps));
	hwts->hwtstamp = ns_to_kसमय(nsec);
पूर्ण

/**
 * mlx4_en_हटाओ_बारtamp - disable PTP device
 * @mdev: board निजी काष्ठाure
 *
 * Stop the PTP support.
 **/
व्योम mlx4_en_हटाओ_बारtamp(काष्ठा mlx4_en_dev *mdev)
अणु
	अगर (mdev->ptp_घड़ी) अणु
		ptp_घड़ी_unरेजिस्टर(mdev->ptp_घड़ी);
		mdev->ptp_घड़ी = शून्य;
		mlx4_info(mdev, "removed PHC\n");
	पूर्ण
पूर्ण

#घोषणा MLX4_EN_WRAP_AROUND_SEC	10UL
/* By scheduling the overflow check every 5 seconds, we have a reasonably
 * good chance we wont miss a wrap around.
 * TOTO: Use a समयr instead of a work queue to increase the guarantee.
 */
#घोषणा MLX4_EN_OVERFLOW_PERIOD (MLX4_EN_WRAP_AROUND_SEC * HZ / 2)

व्योम mlx4_en_ptp_overflow_check(काष्ठा mlx4_en_dev *mdev)
अणु
	bool समयout = समय_is_beक्रमe_jअगरfies(mdev->last_overflow_check +
					      MLX4_EN_OVERFLOW_PERIOD);
	अचिन्हित दीर्घ flags;

	अगर (समयout) अणु
		ग_लिखो_seqlock_irqsave(&mdev->घड़ी_lock, flags);
		समयcounter_पढ़ो(&mdev->घड़ी);
		ग_लिखो_sequnlock_irqrestore(&mdev->घड़ी_lock, flags);
		mdev->last_overflow_check = jअगरfies;
	पूर्ण
पूर्ण

/**
 * mlx4_en_phc_adjfreq - adjust the frequency of the hardware घड़ी
 * @ptp: ptp घड़ी काष्ठाure
 * @delta: Desired frequency change in parts per billion
 *
 * Adjust the frequency of the PHC cycle counter by the indicated delta from
 * the base frequency.
 **/
अटल पूर्णांक mlx4_en_phc_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 delta)
अणु
	u64 adj;
	u32 dअगरf, mult;
	पूर्णांक neg_adj = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा mlx4_en_dev *mdev = container_of(ptp, काष्ठा mlx4_en_dev,
						ptp_घड़ी_info);

	अगर (delta < 0) अणु
		neg_adj = 1;
		delta = -delta;
	पूर्ण
	mult = mdev->nominal_c_mult;
	adj = mult;
	adj *= delta;
	dअगरf = भाग_u64(adj, 1000000000ULL);

	ग_लिखो_seqlock_irqsave(&mdev->घड़ी_lock, flags);
	समयcounter_पढ़ो(&mdev->घड़ी);
	mdev->cycles.mult = neg_adj ? mult - dअगरf : mult + dअगरf;
	ग_लिखो_sequnlock_irqrestore(&mdev->घड़ी_lock, flags);

	वापस 0;
पूर्ण

/**
 * mlx4_en_phc_adjसमय - Shअगरt the समय of the hardware घड़ी
 * @ptp: ptp घड़ी काष्ठाure
 * @delta: Desired change in nanoseconds
 *
 * Adjust the समयr by resetting the समयcounter काष्ठाure.
 **/
अटल पूर्णांक mlx4_en_phc_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा mlx4_en_dev *mdev = container_of(ptp, काष्ठा mlx4_en_dev,
						ptp_घड़ी_info);
	अचिन्हित दीर्घ flags;

	ग_लिखो_seqlock_irqsave(&mdev->घड़ी_lock, flags);
	समयcounter_adjसमय(&mdev->घड़ी, delta);
	ग_लिखो_sequnlock_irqrestore(&mdev->घड़ी_lock, flags);

	वापस 0;
पूर्ण

/**
 * mlx4_en_phc_समय_लो - Reads the current समय from the hardware घड़ी
 * @ptp: ptp घड़ी काष्ठाure
 * @ts: बारpec काष्ठाure to hold the current समय value
 *
 * Read the समयcounter and वापस the correct value in ns after converting
 * it पूर्णांकo a काष्ठा बारpec.
 **/
अटल पूर्णांक mlx4_en_phc_समय_लो(काष्ठा ptp_घड़ी_info *ptp,
			       काष्ठा बारpec64 *ts)
अणु
	काष्ठा mlx4_en_dev *mdev = container_of(ptp, काष्ठा mlx4_en_dev,
						ptp_घड़ी_info);
	अचिन्हित दीर्घ flags;
	u64 ns;

	ग_लिखो_seqlock_irqsave(&mdev->घड़ी_lock, flags);
	ns = समयcounter_पढ़ो(&mdev->घड़ी);
	ग_लिखो_sequnlock_irqrestore(&mdev->घड़ी_lock, flags);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

/**
 * mlx4_en_phc_समय_रखो - Set the current समय on the hardware घड़ी
 * @ptp: ptp घड़ी काष्ठाure
 * @ts: बारpec containing the new समय क्रम the cycle counter
 *
 * Reset the समयcounter to use a new base value instead of the kernel
 * wall समयr value.
 **/
अटल पूर्णांक mlx4_en_phc_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			       स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा mlx4_en_dev *mdev = container_of(ptp, काष्ठा mlx4_en_dev,
						ptp_घड़ी_info);
	u64 ns = बारpec64_to_ns(ts);
	अचिन्हित दीर्घ flags;

	/* reset the समयcounter */
	ग_लिखो_seqlock_irqsave(&mdev->घड़ी_lock, flags);
	समयcounter_init(&mdev->घड़ी, &mdev->cycles, ns);
	ग_लिखो_sequnlock_irqrestore(&mdev->घड़ी_lock, flags);

	वापस 0;
पूर्ण

/**
 * mlx4_en_phc_enable - enable or disable an ancillary feature
 * @ptp: ptp घड़ी काष्ठाure
 * @request: Desired resource to enable or disable
 * @on: Caller passes one to enable or zero to disable
 *
 * Enable (or disable) ancillary features of the PHC subप्रणाली.
 * Currently, no ancillary features are supported.
 **/
अटल पूर्णांक mlx4_en_phc_enable(काष्ठा ptp_घड़ी_info __always_unused *ptp,
			      काष्ठा ptp_घड़ी_request __always_unused *request,
			      पूर्णांक __always_unused on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info mlx4_en_ptp_घड़ी_info = अणु
	.owner		= THIS_MODULE,
	.max_adj	= 100000000,
	.n_alarm	= 0,
	.n_ext_ts	= 0,
	.n_per_out	= 0,
	.n_pins		= 0,
	.pps		= 0,
	.adjfreq	= mlx4_en_phc_adjfreq,
	.adjसमय	= mlx4_en_phc_adjसमय,
	.समय_लो64	= mlx4_en_phc_समय_लो,
	.समय_रखो64	= mlx4_en_phc_समय_रखो,
	.enable		= mlx4_en_phc_enable,
पूर्ण;


/* This function calculates the max shअगरt that enables the user range
 * of MLX4_EN_WRAP_AROUND_SEC values in the cycles रेजिस्टर.
 */
अटल u32 freq_to_shअगरt(u16 freq)
अणु
	u32 freq_khz = freq * 1000;
	u64 max_val_cycles = freq_khz * 1000 * MLX4_EN_WRAP_AROUND_SEC;
	u64 max_val_cycles_rounded = 1ULL << fls64(max_val_cycles - 1);
	/* calculate max possible multiplier in order to fit in 64bit */
	u64 max_mul = भाग64_u64(ULदीर्घ_उच्च, max_val_cycles_rounded);

	/* This comes from the reverse of घड़ीsource_khz2mult */
	वापस ilog2(भाग_u64(max_mul * freq_khz, 1000000));
पूर्ण

व्योम mlx4_en_init_बारtamp(काष्ठा mlx4_en_dev *mdev)
अणु
	काष्ठा mlx4_dev *dev = mdev->dev;
	अचिन्हित दीर्घ flags;

	/* mlx4_en_init_बारtamp is called क्रम each netdev.
	 * mdev->ptp_घड़ी is common क्रम all ports, skip initialization अगर
	 * was करोne क्रम other port.
	 */
	अगर (mdev->ptp_घड़ी)
		वापस;

	seqlock_init(&mdev->घड़ी_lock);

	स_रखो(&mdev->cycles, 0, माप(mdev->cycles));
	mdev->cycles.पढ़ो = mlx4_en_पढ़ो_घड़ी;
	mdev->cycles.mask = CLOCKSOURCE_MASK(48);
	mdev->cycles.shअगरt = freq_to_shअगरt(dev->caps.hca_core_घड़ी);
	mdev->cycles.mult =
		घड़ीsource_khz2mult(1000 * dev->caps.hca_core_घड़ी, mdev->cycles.shअगरt);
	mdev->nominal_c_mult = mdev->cycles.mult;

	ग_लिखो_seqlock_irqsave(&mdev->घड़ी_lock, flags);
	समयcounter_init(&mdev->घड़ी, &mdev->cycles,
			 kसमय_प्रकारo_ns(kसमय_get_real()));
	ग_लिखो_sequnlock_irqrestore(&mdev->घड़ी_lock, flags);

	/* Configure the PHC */
	mdev->ptp_घड़ी_info = mlx4_en_ptp_घड़ी_info;
	snम_लिखो(mdev->ptp_घड़ी_info.name, 16, "mlx4 ptp");

	mdev->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&mdev->ptp_घड़ी_info,
					     &mdev->pdev->dev);
	अगर (IS_ERR(mdev->ptp_घड़ी)) अणु
		mdev->ptp_घड़ी = शून्य;
		mlx4_err(mdev, "ptp_clock_register failed\n");
	पूर्ण अन्यथा अगर (mdev->ptp_घड़ी) अणु
		mlx4_info(mdev, "registered PHC clock\n");
	पूर्ण

पूर्ण
