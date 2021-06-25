<शैली गुरु>
/*
 * Copyright (c) 2015, Mellanox Technologies. All rights reserved.
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
 */

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <rdma/mlx5-abi.h>
#समावेश "lib/eq.h"
#समावेश "en.h"
#समावेश "clock.h"

क्रमागत अणु
	MLX5_CYCLES_SHIFT	= 23
पूर्ण;

क्रमागत अणु
	MLX5_PIN_MODE_IN		= 0x0,
	MLX5_PIN_MODE_OUT		= 0x1,
पूर्ण;

क्रमागत अणु
	MLX5_OUT_PATTERN_PULSE		= 0x0,
	MLX5_OUT_PATTERN_PERIODIC	= 0x1,
पूर्ण;

क्रमागत अणु
	MLX5_EVENT_MODE_DISABLE	= 0x0,
	MLX5_EVENT_MODE_REPETETIVE	= 0x1,
	MLX5_EVENT_MODE_ONCE_TILL_ARM	= 0x2,
पूर्ण;

क्रमागत अणु
	MLX5_MTPPS_FS_ENABLE			= BIT(0x0),
	MLX5_MTPPS_FS_PATTERN			= BIT(0x2),
	MLX5_MTPPS_FS_PIN_MODE			= BIT(0x3),
	MLX5_MTPPS_FS_TIME_STAMP		= BIT(0x4),
	MLX5_MTPPS_FS_OUT_PULSE_DURATION	= BIT(0x5),
	MLX5_MTPPS_FS_ENH_OUT_PER_ADJ		= BIT(0x7),
पूर्ण;

अटल bool mlx5_real_समय_mode(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस (mlx5_is_real_समय_rq(mdev) || mlx5_is_real_समय_sq(mdev));
पूर्ण

अटल bool mlx5_modअगरy_mtutc_allowed(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस MLX5_CAP_MCAM_FEATURE(mdev, ptpcyc2realसमय_modअगरy);
पूर्ण

अटल पूर्णांक mlx5_set_mtutc(काष्ठा mlx5_core_dev *dev, u32 *mtutc, u32 size)
अणु
	u32 out[MLX5_ST_SZ_DW(mtutc_reg)] = अणुपूर्ण;

	अगर (!MLX5_CAP_MCAM_REG(dev, mtutc))
		वापस -EOPNOTSUPP;

	वापस mlx5_core_access_reg(dev, mtutc, size, out, माप(out),
				    MLX5_REG_MTUTC, 0, 1);
पूर्ण

अटल u64 mlx5_पढ़ो_समय(काष्ठा mlx5_core_dev *dev,
			  काष्ठा ptp_प्रणाली_बारtamp *sts,
			  bool real_समय)
अणु
	u32 समयr_h, समयr_h1, समयr_l;

	समयr_h = ioपढ़ो32be(real_समय ? &dev->iseg->real_समय_h :
			     &dev->iseg->पूर्णांकernal_समयr_h);
	ptp_पढ़ो_प्रणाली_prets(sts);
	समयr_l = ioपढ़ो32be(real_समय ? &dev->iseg->real_समय_l :
			     &dev->iseg->पूर्णांकernal_समयr_l);
	ptp_पढ़ो_प्रणाली_postts(sts);
	समयr_h1 = ioपढ़ो32be(real_समय ? &dev->iseg->real_समय_h :
			      &dev->iseg->पूर्णांकernal_समयr_h);
	अगर (समयr_h != समयr_h1) अणु
		/* wrap around */
		ptp_पढ़ो_प्रणाली_prets(sts);
		समयr_l = ioपढ़ो32be(real_समय ? &dev->iseg->real_समय_l :
				     &dev->iseg->पूर्णांकernal_समयr_l);
		ptp_पढ़ो_प्रणाली_postts(sts);
	पूर्ण

	वापस real_समय ? REAL_TIME_TO_NS(समयr_h1, समयr_l) :
			   (u64)समयr_l | (u64)समयr_h1 << 32;
पूर्ण

अटल u64 पढ़ो_पूर्णांकernal_समयr(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा mlx5_समयr *समयr = container_of(cc, काष्ठा mlx5_समयr, cycles);
	काष्ठा mlx5_घड़ी *घड़ी = container_of(समयr, काष्ठा mlx5_घड़ी, समयr);
	काष्ठा mlx5_core_dev *mdev = container_of(घड़ी, काष्ठा mlx5_core_dev,
						  घड़ी);

	वापस mlx5_पढ़ो_समय(mdev, शून्य, false) & cc->mask;
पूर्ण

अटल व्योम mlx5_update_घड़ी_info_page(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_ib_घड़ी_info *घड़ी_info = mdev->घड़ी_info;
	काष्ठा mlx5_घड़ी *घड़ी = &mdev->घड़ी;
	काष्ठा mlx5_समयr *समयr;
	u32 sign;

	अगर (!घड़ी_info)
		वापस;

	sign = smp_load_acquire(&घड़ी_info->sign);
	smp_store_mb(घड़ी_info->sign,
		     sign | MLX5_IB_CLOCK_INFO_KERNEL_UPDATING);

	समयr = &घड़ी->समयr;
	घड़ी_info->cycles = समयr->tc.cycle_last;
	घड़ी_info->mult   = समयr->cycles.mult;
	घड़ी_info->nsec   = समयr->tc.nsec;
	घड़ी_info->frac   = समयr->tc.frac;

	smp_store_release(&घड़ी_info->sign,
			  sign + MLX5_IB_CLOCK_INFO_KERNEL_UPDATING * 2);
पूर्ण

अटल व्योम mlx5_pps_out(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_pps *pps_info = container_of(work, काष्ठा mlx5_pps,
						 out_work);
	काष्ठा mlx5_घड़ी *घड़ी = container_of(pps_info, काष्ठा mlx5_घड़ी,
						pps_info);
	काष्ठा mlx5_core_dev *mdev = container_of(घड़ी, काष्ठा mlx5_core_dev,
						  घड़ी);
	u32 in[MLX5_ST_SZ_DW(mtpps_reg)] = अणु0पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	क्रम (i = 0; i < घड़ी->ptp_info.n_pins; i++) अणु
		u64 tstart;

		ग_लिखो_seqlock_irqsave(&घड़ी->lock, flags);
		tstart = घड़ी->pps_info.start[i];
		घड़ी->pps_info.start[i] = 0;
		ग_लिखो_sequnlock_irqrestore(&घड़ी->lock, flags);
		अगर (!tstart)
			जारी;

		MLX5_SET(mtpps_reg, in, pin, i);
		MLX5_SET64(mtpps_reg, in, समय_stamp, tstart);
		MLX5_SET(mtpps_reg, in, field_select, MLX5_MTPPS_FS_TIME_STAMP);
		mlx5_set_mtpps(mdev, in, माप(in));
	पूर्ण
पूर्ण

अटल व्योम mlx5_बारtamp_overflow(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा mlx5_समयr *समयr;
	काष्ठा mlx5_घड़ी *घड़ी;
	अचिन्हित दीर्घ flags;

	समयr = container_of(dwork, काष्ठा mlx5_समयr, overflow_work);
	घड़ी = container_of(समयr, काष्ठा mlx5_घड़ी, समयr);
	mdev = container_of(घड़ी, काष्ठा mlx5_core_dev, घड़ी);

	ग_लिखो_seqlock_irqsave(&घड़ी->lock, flags);
	समयcounter_पढ़ो(&समयr->tc);
	mlx5_update_घड़ी_info_page(mdev);
	ग_लिखो_sequnlock_irqrestore(&घड़ी->lock, flags);
	schedule_delayed_work(&समयr->overflow_work, समयr->overflow_period);
पूर्ण

अटल पूर्णांक mlx5_ptp_समय_रखो_real_समय(काष्ठा mlx5_core_dev *mdev,
				      स्थिर काष्ठा बारpec64 *ts)
अणु
	u32 in[MLX5_ST_SZ_DW(mtutc_reg)] = अणुपूर्ण;

	अगर (!mlx5_modअगरy_mtutc_allowed(mdev))
		वापस 0;

	अगर (ts->tv_sec < 0 || ts->tv_sec > U32_MAX ||
	    ts->tv_nsec < 0 || ts->tv_nsec > NSEC_PER_SEC)
		वापस -EINVAL;

	MLX5_SET(mtutc_reg, in, operation, MLX5_MTUTC_OPERATION_SET_TIME_IMMEDIATE);
	MLX5_SET(mtutc_reg, in, utc_sec, ts->tv_sec);
	MLX5_SET(mtutc_reg, in, utc_nsec, ts->tv_nsec);

	वापस mlx5_set_mtutc(mdev, in, माप(in));
पूर्ण

अटल पूर्णांक mlx5_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp, स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = container_of(ptp, काष्ठा mlx5_घड़ी, ptp_info);
	काष्ठा mlx5_समयr *समयr = &घड़ी->समयr;
	काष्ठा mlx5_core_dev *mdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	mdev = container_of(घड़ी, काष्ठा mlx5_core_dev, घड़ी);
	err = mlx5_ptp_समय_रखो_real_समय(mdev, ts);
	अगर (err)
		वापस err;

	ग_लिखो_seqlock_irqsave(&घड़ी->lock, flags);
	समयcounter_init(&समयr->tc, &समयr->cycles, बारpec64_to_ns(ts));
	mlx5_update_घड़ी_info_page(mdev);
	ग_लिखो_sequnlock_irqrestore(&घड़ी->lock, flags);

	वापस 0;
पूर्ण

अटल
काष्ठा बारpec64 mlx5_ptp_समय_लोx_real_समय(काष्ठा mlx5_core_dev *mdev,
					      काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा बारpec64 ts;
	u64 समय;

	समय = mlx5_पढ़ो_समय(mdev, sts, true);
	ts = ns_to_बारpec64(समय);
	वापस ts;
पूर्ण

अटल पूर्णांक mlx5_ptp_समय_लोx(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts,
			     काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = container_of(ptp, काष्ठा mlx5_घड़ी, ptp_info);
	काष्ठा mlx5_समयr *समयr = &घड़ी->समयr;
	काष्ठा mlx5_core_dev *mdev;
	अचिन्हित दीर्घ flags;
	u64 cycles, ns;

	mdev = container_of(घड़ी, काष्ठा mlx5_core_dev, घड़ी);
	अगर (mlx5_real_समय_mode(mdev)) अणु
		*ts = mlx5_ptp_समय_लोx_real_समय(mdev, sts);
		जाओ out;
	पूर्ण

	ग_लिखो_seqlock_irqsave(&घड़ी->lock, flags);
	cycles = mlx5_पढ़ो_समय(mdev, sts, false);
	ns = समयcounter_cyc2समय(&समयr->tc, cycles);
	ग_लिखो_sequnlock_irqrestore(&घड़ी->lock, flags);
	*ts = ns_to_बारpec64(ns);
out:
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ptp_adjसमय_real_समय(काष्ठा mlx5_core_dev *mdev, s64 delta)
अणु
	u32 in[MLX5_ST_SZ_DW(mtutc_reg)] = अणुपूर्ण;

	अगर (!mlx5_modअगरy_mtutc_allowed(mdev))
		वापस 0;

	/* HW समय adjusपंचांगent range is s16. If out of range, समय_रखो instead */
	अगर (delta < S16_MIN || delta > S16_MAX) अणु
		काष्ठा बारpec64 ts;
		s64 ns;

		ts = mlx5_ptp_समय_लोx_real_समय(mdev, शून्य);
		ns = बारpec64_to_ns(&ts) + delta;
		ts = ns_to_बारpec64(ns);
		वापस mlx5_ptp_समय_रखो_real_समय(mdev, &ts);
	पूर्ण

	MLX5_SET(mtutc_reg, in, operation, MLX5_MTUTC_OPERATION_ADJUST_TIME);
	MLX5_SET(mtutc_reg, in, समय_adjusपंचांगent, delta);

	वापस mlx5_set_mtutc(mdev, in, माप(in));
पूर्ण

अटल पूर्णांक mlx5_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = container_of(ptp, काष्ठा mlx5_घड़ी, ptp_info);
	काष्ठा mlx5_समयr *समयr = &घड़ी->समयr;
	काष्ठा mlx5_core_dev *mdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	mdev = container_of(घड़ी, काष्ठा mlx5_core_dev, घड़ी);

	err = mlx5_ptp_adjसमय_real_समय(mdev, delta);
	अगर (err)
		वापस err;
	ग_लिखो_seqlock_irqsave(&घड़ी->lock, flags);
	समयcounter_adjसमय(&समयr->tc, delta);
	mlx5_update_घड़ी_info_page(mdev);
	ग_लिखो_sequnlock_irqrestore(&घड़ी->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ptp_adjfreq_real_समय(काष्ठा mlx5_core_dev *mdev, s32 freq)
अणु
	u32 in[MLX5_ST_SZ_DW(mtutc_reg)] = अणुपूर्ण;

	अगर (!mlx5_modअगरy_mtutc_allowed(mdev))
		वापस 0;

	MLX5_SET(mtutc_reg, in, operation, MLX5_MTUTC_OPERATION_ADJUST_FREQ_UTC);
	MLX5_SET(mtutc_reg, in, freq_adjusपंचांगent, freq);

	वापस mlx5_set_mtutc(mdev, in, माप(in));
पूर्ण

अटल पूर्णांक mlx5_ptp_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 delta)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = container_of(ptp, काष्ठा mlx5_घड़ी, ptp_info);
	काष्ठा mlx5_समयr *समयr = &घड़ी->समयr;
	काष्ठा mlx5_core_dev *mdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक neg_adj = 0;
	u32 dअगरf;
	u64 adj;
	पूर्णांक err;

	mdev = container_of(घड़ी, काष्ठा mlx5_core_dev, घड़ी);
	err = mlx5_ptp_adjfreq_real_समय(mdev, delta);
	अगर (err)
		वापस err;

	अगर (delta < 0) अणु
		neg_adj = 1;
		delta = -delta;
	पूर्ण

	adj = समयr->nominal_c_mult;
	adj *= delta;
	dअगरf = भाग_u64(adj, 1000000000ULL);

	ग_लिखो_seqlock_irqsave(&घड़ी->lock, flags);
	समयcounter_पढ़ो(&समयr->tc);
	समयr->cycles.mult = neg_adj ? समयr->nominal_c_mult - dअगरf :
				       समयr->nominal_c_mult + dअगरf;
	mlx5_update_घड़ी_info_page(mdev);
	ग_लिखो_sequnlock_irqrestore(&घड़ी->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_extts_configure(काष्ठा ptp_घड़ी_info *ptp,
				काष्ठा ptp_घड़ी_request *rq,
				पूर्णांक on)
अणु
	काष्ठा mlx5_घड़ी *घड़ी =
			container_of(ptp, काष्ठा mlx5_घड़ी, ptp_info);
	काष्ठा mlx5_core_dev *mdev =
			container_of(घड़ी, काष्ठा mlx5_core_dev, घड़ी);
	u32 in[MLX5_ST_SZ_DW(mtpps_reg)] = अणु0पूर्ण;
	u32 field_select = 0;
	u8 pin_mode = 0;
	u8 pattern = 0;
	पूर्णांक pin = -1;
	पूर्णांक err = 0;

	अगर (!MLX5_PPS_CAP(mdev))
		वापस -EOPNOTSUPP;

	/* Reject requests with unsupported flags */
	अगर (rq->extts.flags & ~(PTP_ENABLE_FEATURE |
				PTP_RISING_EDGE |
				PTP_FALLING_EDGE |
				PTP_STRICT_FLAGS))
		वापस -EOPNOTSUPP;

	/* Reject requests to enable समय stamping on both edges. */
	अगर ((rq->extts.flags & PTP_STRICT_FLAGS) &&
	    (rq->extts.flags & PTP_ENABLE_FEATURE) &&
	    (rq->extts.flags & PTP_EXTTS_EDGES) == PTP_EXTTS_EDGES)
		वापस -EOPNOTSUPP;

	अगर (rq->extts.index >= घड़ी->ptp_info.n_pins)
		वापस -EINVAL;

	pin = ptp_find_pin(घड़ी->ptp, PTP_PF_EXTTS, rq->extts.index);
	अगर (pin < 0)
		वापस -EBUSY;

	अगर (on) अणु
		pin_mode = MLX5_PIN_MODE_IN;
		pattern = !!(rq->extts.flags & PTP_FALLING_EDGE);
		field_select = MLX5_MTPPS_FS_PIN_MODE |
			       MLX5_MTPPS_FS_PATTERN |
			       MLX5_MTPPS_FS_ENABLE;
	पूर्ण अन्यथा अणु
		field_select = MLX5_MTPPS_FS_ENABLE;
	पूर्ण

	MLX5_SET(mtpps_reg, in, pin, pin);
	MLX5_SET(mtpps_reg, in, pin_mode, pin_mode);
	MLX5_SET(mtpps_reg, in, pattern, pattern);
	MLX5_SET(mtpps_reg, in, enable, on);
	MLX5_SET(mtpps_reg, in, field_select, field_select);

	err = mlx5_set_mtpps(mdev, in, माप(in));
	अगर (err)
		वापस err;

	वापस mlx5_set_mtppse(mdev, pin, 0,
			       MLX5_EVENT_MODE_REPETETIVE & on);
पूर्ण

अटल u64 find_target_cycles(काष्ठा mlx5_core_dev *mdev, s64 target_ns)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = &mdev->घड़ी;
	u64 cycles_now, cycles_delta;
	u64 nsec_now, nsec_delta;
	काष्ठा mlx5_समयr *समयr;
	अचिन्हित दीर्घ flags;

	समयr = &घड़ी->समयr;

	cycles_now = mlx5_पढ़ो_समय(mdev, शून्य, false);
	ग_लिखो_seqlock_irqsave(&घड़ी->lock, flags);
	nsec_now = समयcounter_cyc2समय(&समयr->tc, cycles_now);
	nsec_delta = target_ns - nsec_now;
	cycles_delta = भाग64_u64(nsec_delta << समयr->cycles.shअगरt,
				 समयr->cycles.mult);
	ग_लिखो_sequnlock_irqrestore(&घड़ी->lock, flags);

	वापस cycles_now + cycles_delta;
पूर्ण

अटल u64 perout_conf_पूर्णांकernal_समयr(काष्ठा mlx5_core_dev *mdev,
				      s64 sec, u32 nsec)
अणु
	काष्ठा बारpec64 ts;
	s64 target_ns;

	ts.tv_sec = sec;
	ts.tv_nsec = nsec;
	target_ns = बारpec64_to_ns(&ts);

	वापस find_target_cycles(mdev, target_ns);
पूर्ण

अटल u64 perout_conf_real_समय(s64 sec, u32 nsec)
अणु
	वापस (u64)nsec | (u64)sec << 32;
पूर्ण

अटल पूर्णांक mlx5_perout_configure(काष्ठा ptp_घड़ी_info *ptp,
				 काष्ठा ptp_घड़ी_request *rq,
				 पूर्णांक on)
अणु
	काष्ठा mlx5_घड़ी *घड़ी =
			container_of(ptp, काष्ठा mlx5_घड़ी, ptp_info);
	काष्ठा mlx5_core_dev *mdev =
			container_of(घड़ी, काष्ठा mlx5_core_dev, घड़ी);
	u32 in[MLX5_ST_SZ_DW(mtpps_reg)] = अणु0पूर्ण;
	काष्ठा बारpec64 ts;
	u32 field_select = 0;
	u64 समय_stamp = 0;
	u8 pin_mode = 0;
	u8 pattern = 0;
	पूर्णांक pin = -1;
	पूर्णांक err = 0;
	s64 ns;

	अगर (!MLX5_PPS_CAP(mdev))
		वापस -EOPNOTSUPP;

	/* Reject requests with unsupported flags */
	अगर (rq->perout.flags)
		वापस -EOPNOTSUPP;

	अगर (rq->perout.index >= घड़ी->ptp_info.n_pins)
		वापस -EINVAL;

	field_select = MLX5_MTPPS_FS_ENABLE;
	pin = ptp_find_pin(घड़ी->ptp, PTP_PF_PEROUT, rq->perout.index);
	अगर (pin < 0)
		वापस -EBUSY;

	अगर (on) अणु
		bool rt_mode = mlx5_real_समय_mode(mdev);
		u32 nsec;
		s64 sec;

		pin_mode = MLX5_PIN_MODE_OUT;
		pattern = MLX5_OUT_PATTERN_PERIODIC;
		ts.tv_sec = rq->perout.period.sec;
		ts.tv_nsec = rq->perout.period.nsec;
		ns = बारpec64_to_ns(&ts);

		अगर ((ns >> 1) != 500000000LL)
			वापस -EINVAL;

		nsec = rq->perout.start.nsec;
		sec = rq->perout.start.sec;

		अगर (rt_mode && sec > U32_MAX)
			वापस -EINVAL;

		समय_stamp = rt_mode ? perout_conf_real_समय(sec, nsec) :
				       perout_conf_पूर्णांकernal_समयr(mdev, sec, nsec);

		field_select |= MLX5_MTPPS_FS_PIN_MODE |
				MLX5_MTPPS_FS_PATTERN |
				MLX5_MTPPS_FS_TIME_STAMP;
	पूर्ण

	MLX5_SET(mtpps_reg, in, pin, pin);
	MLX5_SET(mtpps_reg, in, pin_mode, pin_mode);
	MLX5_SET(mtpps_reg, in, pattern, pattern);
	MLX5_SET(mtpps_reg, in, enable, on);
	MLX5_SET64(mtpps_reg, in, समय_stamp, समय_stamp);
	MLX5_SET(mtpps_reg, in, field_select, field_select);

	err = mlx5_set_mtpps(mdev, in, माप(in));
	अगर (err)
		वापस err;

	वापस mlx5_set_mtppse(mdev, pin, 0,
			       MLX5_EVENT_MODE_REPETETIVE & on);
पूर्ण

अटल पूर्णांक mlx5_pps_configure(काष्ठा ptp_घड़ी_info *ptp,
			      काष्ठा ptp_घड़ी_request *rq,
			      पूर्णांक on)
अणु
	काष्ठा mlx5_घड़ी *घड़ी =
			container_of(ptp, काष्ठा mlx5_घड़ी, ptp_info);

	घड़ी->pps_info.enabled = !!on;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
			   काष्ठा ptp_घड़ी_request *rq,
			   पूर्णांक on)
अणु
	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_EXTTS:
		वापस mlx5_extts_configure(ptp, rq, on);
	हाल PTP_CLK_REQ_PEROUT:
		वापस mlx5_perout_configure(ptp, rq, on);
	हाल PTP_CLK_REQ_PPS:
		वापस mlx5_pps_configure(ptp, rq, on);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

क्रमागत अणु
	MLX5_MTPPS_REG_CAP_PIN_X_MODE_SUPPORT_PPS_IN = BIT(0),
	MLX5_MTPPS_REG_CAP_PIN_X_MODE_SUPPORT_PPS_OUT = BIT(1),
पूर्ण;

अटल पूर्णांक mlx5_ptp_verअगरy(काष्ठा ptp_घड़ी_info *ptp, अचिन्हित पूर्णांक pin,
			   क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = container_of(ptp, काष्ठा mlx5_घड़ी,
						ptp_info);

	चयन (func) अणु
	हाल PTP_PF_NONE:
		वापस 0;
	हाल PTP_PF_EXTTS:
		वापस !(घड़ी->pps_info.pin_caps[pin] &
			 MLX5_MTPPS_REG_CAP_PIN_X_MODE_SUPPORT_PPS_IN);
	हाल PTP_PF_PEROUT:
		वापस !(घड़ी->pps_info.pin_caps[pin] &
			 MLX5_MTPPS_REG_CAP_PIN_X_MODE_SUPPORT_PPS_OUT);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info mlx5_ptp_घड़ी_info = अणु
	.owner		= THIS_MODULE,
	.name		= "mlx5_ptp",
	.max_adj	= 100000000,
	.n_alarm	= 0,
	.n_ext_ts	= 0,
	.n_per_out	= 0,
	.n_pins		= 0,
	.pps		= 0,
	.adjfreq	= mlx5_ptp_adjfreq,
	.adjसमय	= mlx5_ptp_adjसमय,
	.समय_लोx64	= mlx5_ptp_समय_लोx,
	.समय_रखो64	= mlx5_ptp_समय_रखो,
	.enable		= शून्य,
	.verअगरy		= शून्य,
पूर्ण;

अटल पूर्णांक mlx5_query_mtpps_pin_mode(काष्ठा mlx5_core_dev *mdev, u8 pin,
				     u32 *mtpps, u32 mtpps_size)
अणु
	u32 in[MLX5_ST_SZ_DW(mtpps_reg)] = अणुपूर्ण;

	MLX5_SET(mtpps_reg, in, pin, pin);

	वापस mlx5_core_access_reg(mdev, in, माप(in), mtpps,
				    mtpps_size, MLX5_REG_MTPPS, 0, 0);
पूर्ण

अटल पूर्णांक mlx5_get_pps_pin_mode(काष्ठा mlx5_घड़ी *घड़ी, u8 pin)
अणु
	काष्ठा mlx5_core_dev *mdev = container_of(घड़ी, काष्ठा mlx5_core_dev, घड़ी);

	u32 out[MLX5_ST_SZ_DW(mtpps_reg)] = अणुपूर्ण;
	u8 mode;
	पूर्णांक err;

	err = mlx5_query_mtpps_pin_mode(mdev, pin, out, माप(out));
	अगर (err || !MLX5_GET(mtpps_reg, out, enable))
		वापस PTP_PF_NONE;

	mode = MLX5_GET(mtpps_reg, out, pin_mode);

	अगर (mode == MLX5_PIN_MODE_IN)
		वापस PTP_PF_EXTTS;
	अन्यथा अगर (mode == MLX5_PIN_MODE_OUT)
		वापस PTP_PF_PEROUT;

	वापस PTP_PF_NONE;
पूर्ण

अटल व्योम mlx5_init_pin_config(काष्ठा mlx5_घड़ी *घड़ी)
अणु
	पूर्णांक i;

	अगर (!घड़ी->ptp_info.n_pins)
		वापस;

	घड़ी->ptp_info.pin_config =
			kसुस्मृति(घड़ी->ptp_info.n_pins,
				माप(*घड़ी->ptp_info.pin_config),
				GFP_KERNEL);
	अगर (!घड़ी->ptp_info.pin_config)
		वापस;
	घड़ी->ptp_info.enable = mlx5_ptp_enable;
	घड़ी->ptp_info.verअगरy = mlx5_ptp_verअगरy;
	घड़ी->ptp_info.pps = 1;

	क्रम (i = 0; i < घड़ी->ptp_info.n_pins; i++) अणु
		snम_लिखो(घड़ी->ptp_info.pin_config[i].name,
			 माप(घड़ी->ptp_info.pin_config[i].name),
			 "mlx5_pps%d", i);
		घड़ी->ptp_info.pin_config[i].index = i;
		घड़ी->ptp_info.pin_config[i].func = mlx5_get_pps_pin_mode(घड़ी, i);
		घड़ी->ptp_info.pin_config[i].chan = 0;
	पूर्ण
पूर्ण

अटल व्योम mlx5_get_pps_caps(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = &mdev->घड़ी;
	u32 out[MLX5_ST_SZ_DW(mtpps_reg)] = अणु0पूर्ण;

	mlx5_query_mtpps(mdev, out, माप(out));

	घड़ी->ptp_info.n_pins = MLX5_GET(mtpps_reg, out,
					  cap_number_of_pps_pins);
	घड़ी->ptp_info.n_ext_ts = MLX5_GET(mtpps_reg, out,
					    cap_max_num_of_pps_in_pins);
	घड़ी->ptp_info.n_per_out = MLX5_GET(mtpps_reg, out,
					     cap_max_num_of_pps_out_pins);

	घड़ी->pps_info.pin_caps[0] = MLX5_GET(mtpps_reg, out, cap_pin_0_mode);
	घड़ी->pps_info.pin_caps[1] = MLX5_GET(mtpps_reg, out, cap_pin_1_mode);
	घड़ी->pps_info.pin_caps[2] = MLX5_GET(mtpps_reg, out, cap_pin_2_mode);
	घड़ी->pps_info.pin_caps[3] = MLX5_GET(mtpps_reg, out, cap_pin_3_mode);
	घड़ी->pps_info.pin_caps[4] = MLX5_GET(mtpps_reg, out, cap_pin_4_mode);
	घड़ी->pps_info.pin_caps[5] = MLX5_GET(mtpps_reg, out, cap_pin_5_mode);
	घड़ी->pps_info.pin_caps[6] = MLX5_GET(mtpps_reg, out, cap_pin_6_mode);
	घड़ी->pps_info.pin_caps[7] = MLX5_GET(mtpps_reg, out, cap_pin_7_mode);
पूर्ण

अटल व्योम ts_next_sec(काष्ठा बारpec64 *ts)
अणु
	ts->tv_sec += 1;
	ts->tv_nsec = 0;
पूर्ण

अटल u64 perout_conf_next_event_समयr(काष्ठा mlx5_core_dev *mdev,
					काष्ठा mlx5_घड़ी *घड़ी)
अणु
	bool rt_mode = mlx5_real_समय_mode(mdev);
	काष्ठा बारpec64 ts;
	s64 target_ns;

	अगर (rt_mode)
		ts = mlx5_ptp_समय_लोx_real_समय(mdev, शून्य);
	अन्यथा
		mlx5_ptp_समय_लोx(&घड़ी->ptp_info, &ts, शून्य);

	ts_next_sec(&ts);
	target_ns = बारpec64_to_ns(&ts);

	वापस rt_mode ? perout_conf_real_समय(ts.tv_sec, ts.tv_nsec) :
			 find_target_cycles(mdev, target_ns);
पूर्ण

अटल पूर्णांक mlx5_pps_event(काष्ठा notअगरier_block *nb,
			  अचिन्हित दीर्घ type, व्योम *data)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = mlx5_nb_cof(nb, काष्ठा mlx5_घड़ी, pps_nb);
	काष्ठा ptp_घड़ी_event ptp_event;
	काष्ठा mlx5_eqe *eqe = data;
	पूर्णांक pin = eqe->data.pps.pin;
	काष्ठा mlx5_core_dev *mdev;
	अचिन्हित दीर्घ flags;
	u64 ns;

	mdev = container_of(घड़ी, काष्ठा mlx5_core_dev, घड़ी);

	चयन (घड़ी->ptp_info.pin_config[pin].func) अणु
	हाल PTP_PF_EXTTS:
		ptp_event.index = pin;
		ptp_event.बारtamp = mlx5_real_समय_mode(mdev) ?
			mlx5_real_समय_cyc2समय(घड़ी,
						be64_to_cpu(eqe->data.pps.समय_stamp)) :
			mlx5_समयcounter_cyc2समय(घड़ी,
						  be64_to_cpu(eqe->data.pps.समय_stamp));
		अगर (घड़ी->pps_info.enabled) अणु
			ptp_event.type = PTP_CLOCK_PPSUSR;
			ptp_event.pps_बार.ts_real =
					ns_to_बारpec64(ptp_event.बारtamp);
		पूर्ण अन्यथा अणु
			ptp_event.type = PTP_CLOCK_EXTTS;
		पूर्ण
		/* TODOL घड़ी->ptp can be शून्य अगर ptp_घड़ी_रेजिस्टर failes */
		ptp_घड़ी_event(घड़ी->ptp, &ptp_event);
		अवरोध;
	हाल PTP_PF_PEROUT:
		ns = perout_conf_next_event_समयr(mdev, घड़ी);
		ग_लिखो_seqlock_irqsave(&घड़ी->lock, flags);
		घड़ी->pps_info.start[pin] = ns;
		ग_लिखो_sequnlock_irqrestore(&घड़ी->lock, flags);
		schedule_work(&घड़ी->pps_info.out_work);
		अवरोध;
	शेष:
		mlx5_core_err(mdev, " Unhandled clock PPS event, func %d\n",
			      घड़ी->ptp_info.pin_config[pin].func);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल व्योम mlx5_समयcounter_init(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = &mdev->घड़ी;
	काष्ठा mlx5_समयr *समयr = &घड़ी->समयr;
	u32 dev_freq;

	dev_freq = MLX5_CAP_GEN(mdev, device_frequency_khz);
	समयr->cycles.पढ़ो = पढ़ो_पूर्णांकernal_समयr;
	समयr->cycles.shअगरt = MLX5_CYCLES_SHIFT;
	समयr->cycles.mult = घड़ीsource_khz2mult(dev_freq,
						  समयr->cycles.shअगरt);
	समयr->nominal_c_mult = समयr->cycles.mult;
	समयr->cycles.mask = CLOCKSOURCE_MASK(41);

	समयcounter_init(&समयr->tc, &समयr->cycles,
			 kसमय_प्रकारo_ns(kसमय_get_real()));
पूर्ण

अटल व्योम mlx5_init_overflow_period(काष्ठा mlx5_घड़ी *घड़ी)
अणु
	काष्ठा mlx5_core_dev *mdev = container_of(घड़ी, काष्ठा mlx5_core_dev, घड़ी);
	काष्ठा mlx5_ib_घड़ी_info *घड़ी_info = mdev->घड़ी_info;
	काष्ठा mlx5_समयr *समयr = &घड़ी->समयr;
	u64 overflow_cycles;
	u64 frac = 0;
	u64 ns;

	/* Calculate period in seconds to call the overflow watchकरोg - to make
	 * sure counter is checked at least twice every wrap around.
	 * The period is calculated as the minimum between max HW cycles count
	 * (The घड़ी source mask) and max amount of cycles that can be
	 * multiplied by घड़ी multiplier where the result करोesn't exceed
	 * 64bits.
	 */
	overflow_cycles = भाग64_u64(~0ULL >> 1, समयr->cycles.mult);
	overflow_cycles = min(overflow_cycles, भाग_u64(समयr->cycles.mask, 3));

	ns = cyclecounter_cyc2ns(&समयr->cycles, overflow_cycles,
				 frac, &frac);
	करो_भाग(ns, NSEC_PER_SEC / HZ);
	समयr->overflow_period = ns;

	INIT_DELAYED_WORK(&समयr->overflow_work, mlx5_बारtamp_overflow);
	अगर (समयr->overflow_period)
		schedule_delayed_work(&समयr->overflow_work, 0);
	अन्यथा
		mlx5_core_warn(mdev,
			       "invalid overflow period, overflow_work is not scheduled\n");

	अगर (घड़ी_info)
		घड़ी_info->overflow_period = समयr->overflow_period;
पूर्ण

अटल व्योम mlx5_init_घड़ी_info(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = &mdev->घड़ी;
	काष्ठा mlx5_ib_घड़ी_info *info;
	काष्ठा mlx5_समयr *समयr;

	mdev->घड़ी_info = (काष्ठा mlx5_ib_घड़ी_info *)get_zeroed_page(GFP_KERNEL);
	अगर (!mdev->घड़ी_info) अणु
		mlx5_core_warn(mdev, "Failed to allocate IB clock info page\n");
		वापस;
	पूर्ण

	info = mdev->घड़ी_info;
	समयr = &घड़ी->समयr;

	info->nsec = समयr->tc.nsec;
	info->cycles = समयr->tc.cycle_last;
	info->mask = समयr->cycles.mask;
	info->mult = समयr->nominal_c_mult;
	info->shअगरt = समयr->cycles.shअगरt;
	info->frac = समयr->tc.frac;
पूर्ण

अटल व्योम mlx5_init_समयr_घड़ी(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = &mdev->घड़ी;

	mlx5_समयcounter_init(mdev);
	mlx5_init_घड़ी_info(mdev);
	mlx5_init_overflow_period(घड़ी);
	घड़ी->ptp_info = mlx5_ptp_घड़ी_info;

	अगर (mlx5_real_समय_mode(mdev)) अणु
		काष्ठा बारpec64 ts;

		kसमय_get_real_ts64(&ts);
		mlx5_ptp_समय_रखो(&घड़ी->ptp_info, &ts);
	पूर्ण
पूर्ण

अटल व्योम mlx5_init_pps(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = &mdev->घड़ी;

	अगर (!MLX5_PPS_CAP(mdev))
		वापस;

	mlx5_get_pps_caps(mdev);
	mlx5_init_pin_config(घड़ी);
पूर्ण

व्योम mlx5_init_घड़ी(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = &mdev->घड़ी;

	अगर (!MLX5_CAP_GEN(mdev, device_frequency_khz)) अणु
		mlx5_core_warn(mdev, "invalid device_frequency_khz, aborting HW clock init\n");
		वापस;
	पूर्ण

	seqlock_init(&घड़ी->lock);
	mlx5_init_समयr_घड़ी(mdev);
	INIT_WORK(&घड़ी->pps_info.out_work, mlx5_pps_out);

	/* Configure the PHC */
	घड़ी->ptp_info = mlx5_ptp_घड़ी_info;

	/* Initialize 1PPS data काष्ठाures */
	mlx5_init_pps(mdev);

	घड़ी->ptp = ptp_घड़ी_रेजिस्टर(&घड़ी->ptp_info,
					&mdev->pdev->dev);
	अगर (IS_ERR(घड़ी->ptp)) अणु
		mlx5_core_warn(mdev, "ptp_clock_register failed %ld\n",
			       PTR_ERR(घड़ी->ptp));
		घड़ी->ptp = शून्य;
	पूर्ण

	MLX5_NB_INIT(&घड़ी->pps_nb, mlx5_pps_event, PPS_EVENT);
	mlx5_eq_notअगरier_रेजिस्टर(mdev, &घड़ी->pps_nb);
पूर्ण

व्योम mlx5_cleanup_घड़ी(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_घड़ी *घड़ी = &mdev->घड़ी;

	अगर (!MLX5_CAP_GEN(mdev, device_frequency_khz))
		वापस;

	mlx5_eq_notअगरier_unरेजिस्टर(mdev, &घड़ी->pps_nb);
	अगर (घड़ी->ptp) अणु
		ptp_घड़ी_unरेजिस्टर(घड़ी->ptp);
		घड़ी->ptp = शून्य;
	पूर्ण

	cancel_work_sync(&घड़ी->pps_info.out_work);
	cancel_delayed_work_sync(&घड़ी->समयr.overflow_work);

	अगर (mdev->घड़ी_info) अणु
		मुक्त_page((अचिन्हित दीर्घ)mdev->घड़ी_info);
		mdev->घड़ी_info = शून्य;
	पूर्ण

	kमुक्त(घड़ी->ptp_info.pin_config);
पूर्ण
