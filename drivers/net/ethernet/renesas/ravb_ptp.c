<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* PTP 1588 घड़ी using the Renesas Ethernet AVB
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 * Copyright (C) 2015 Renesas Solutions Corp.
 * Copyright (C) 2015-2016 Cogent Embedded, Inc. <source@cogentembedded.com>
 */

#समावेश "ravb.h"

अटल पूर्णांक ravb_ptp_tcr_request(काष्ठा ravb_निजी *priv, u32 request)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	पूर्णांक error;

	error = ravb_रुको(ndev, GCCR, GCCR_TCR, GCCR_TCR_NOREQ);
	अगर (error)
		वापस error;

	ravb_modअगरy(ndev, GCCR, request, request);
	वापस ravb_रुको(ndev, GCCR, GCCR_TCR, GCCR_TCR_NOREQ);
पूर्ण

/* Caller must hold the lock */
अटल पूर्णांक ravb_ptp_समय_पढ़ो(काष्ठा ravb_निजी *priv, काष्ठा बारpec64 *ts)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	पूर्णांक error;

	error = ravb_ptp_tcr_request(priv, GCCR_TCR_CAPTURE);
	अगर (error)
		वापस error;

	ts->tv_nsec = ravb_पढ़ो(ndev, GCT0);
	ts->tv_sec  = ravb_पढ़ो(ndev, GCT1) |
		((s64)ravb_पढ़ो(ndev, GCT2) << 32);

	वापस 0;
पूर्ण

/* Caller must hold the lock */
अटल पूर्णांक ravb_ptp_समय_ग_लिखो(काष्ठा ravb_निजी *priv,
				स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	पूर्णांक error;
	u32 gccr;

	error = ravb_ptp_tcr_request(priv, GCCR_TCR_RESET);
	अगर (error)
		वापस error;

	gccr = ravb_पढ़ो(ndev, GCCR);
	अगर (gccr & GCCR_LTO)
		वापस -EBUSY;
	ravb_ग_लिखो(ndev, ts->tv_nsec, GTO0);
	ravb_ग_लिखो(ndev, ts->tv_sec,  GTO1);
	ravb_ग_लिखो(ndev, (ts->tv_sec >> 32) & 0xffff, GTO2);
	ravb_ग_लिखो(ndev, gccr | GCCR_LTO, GCCR);

	वापस 0;
पूर्ण

/* Caller must hold the lock */
अटल पूर्णांक ravb_ptp_update_compare(काष्ठा ravb_निजी *priv, u32 ns)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	/* When the comparison value (GPTC.PTCV) is in range of
	 * [x-1 to x+1] (x is the configured increment value in
	 * GTI.TIV), it may happen that a comparison match is
	 * not detected when the समयr wraps around.
	 */
	u32 gti_ns_plus_1 = (priv->ptp.current_addend >> 20) + 1;
	u32 gccr;

	अगर (ns < gti_ns_plus_1)
		ns = gti_ns_plus_1;
	अन्यथा अगर (ns > 0 - gti_ns_plus_1)
		ns = 0 - gti_ns_plus_1;

	gccr = ravb_पढ़ो(ndev, GCCR);
	अगर (gccr & GCCR_LPTC)
		वापस -EBUSY;
	ravb_ग_लिखो(ndev, ns, GPTC);
	ravb_ग_लिखो(ndev, gccr | GCCR_LPTC, GCCR);

	वापस 0;
पूर्ण

/* PTP घड़ी operations */
अटल पूर्णांक ravb_ptp_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	काष्ठा ravb_निजी *priv = container_of(ptp, काष्ठा ravb_निजी,
						 ptp.info);
	काष्ठा net_device *ndev = priv->ndev;
	अचिन्हित दीर्घ flags;
	u32 dअगरf, addend;
	bool neg_adj = false;
	u32 gccr;

	अगर (ppb < 0) अणु
		neg_adj = true;
		ppb = -ppb;
	पूर्ण
	addend = priv->ptp.शेष_addend;
	dअगरf = भाग_u64((u64)addend * ppb, NSEC_PER_SEC);

	addend = neg_adj ? addend - dअगरf : addend + dअगरf;

	spin_lock_irqsave(&priv->lock, flags);

	priv->ptp.current_addend = addend;

	gccr = ravb_पढ़ो(ndev, GCCR);
	अगर (gccr & GCCR_LTI) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस -EBUSY;
	पूर्ण
	ravb_ग_लिखो(ndev, addend & GTI_TIV, GTI);
	ravb_ग_लिखो(ndev, gccr | GCCR_LTI, GCCR);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ravb_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा ravb_निजी *priv = container_of(ptp, काष्ठा ravb_निजी,
						 ptp.info);
	काष्ठा बारpec64 ts;
	अचिन्हित दीर्घ flags;
	पूर्णांक error;

	spin_lock_irqsave(&priv->lock, flags);
	error = ravb_ptp_समय_पढ़ो(priv, &ts);
	अगर (!error) अणु
		u64 now = kसमय_प्रकारo_ns(बारpec64_to_kसमय(ts));

		ts = ns_to_बारpec64(now + delta);
		error = ravb_ptp_समय_ग_लिखो(priv, &ts);
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस error;
पूर्ण

अटल पूर्णांक ravb_ptp_समय_लो64(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	काष्ठा ravb_निजी *priv = container_of(ptp, काष्ठा ravb_निजी,
						 ptp.info);
	अचिन्हित दीर्घ flags;
	पूर्णांक error;

	spin_lock_irqsave(&priv->lock, flags);
	error = ravb_ptp_समय_पढ़ो(priv, ts);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस error;
पूर्ण

अटल पूर्णांक ravb_ptp_समय_रखो64(काष्ठा ptp_घड़ी_info *ptp,
			      स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा ravb_निजी *priv = container_of(ptp, काष्ठा ravb_निजी,
						 ptp.info);
	अचिन्हित दीर्घ flags;
	पूर्णांक error;

	spin_lock_irqsave(&priv->lock, flags);
	error = ravb_ptp_समय_ग_लिखो(priv, ts);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस error;
पूर्ण

अटल पूर्णांक ravb_ptp_extts(काष्ठा ptp_घड़ी_info *ptp,
			  काष्ठा ptp_extts_request *req, पूर्णांक on)
अणु
	काष्ठा ravb_निजी *priv = container_of(ptp, काष्ठा ravb_निजी,
						 ptp.info);
	काष्ठा net_device *ndev = priv->ndev;
	अचिन्हित दीर्घ flags;

	/* Reject requests with unsupported flags */
	अगर (req->flags & ~(PTP_ENABLE_FEATURE |
			   PTP_RISING_EDGE |
			   PTP_FALLING_EDGE |
			   PTP_STRICT_FLAGS))
		वापस -EOPNOTSUPP;

	अगर (req->index)
		वापस -EINVAL;

	अगर (priv->ptp.extts[req->index] == on)
		वापस 0;
	priv->ptp.extts[req->index] = on;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->chip_id == RCAR_GEN2)
		ravb_modअगरy(ndev, GIC, GIC_PTCE, on ? GIC_PTCE : 0);
	अन्यथा अगर (on)
		ravb_ग_लिखो(ndev, GIE_PTCS, GIE);
	अन्यथा
		ravb_ग_लिखो(ndev, GID_PTCD, GID);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ravb_ptp_perout(काष्ठा ptp_घड़ी_info *ptp,
			   काष्ठा ptp_perout_request *req, पूर्णांक on)
अणु
	काष्ठा ravb_निजी *priv = container_of(ptp, काष्ठा ravb_निजी,
						 ptp.info);
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा ravb_ptp_perout *perout;
	अचिन्हित दीर्घ flags;
	पूर्णांक error = 0;

	/* Reject requests with unsupported flags */
	अगर (req->flags)
		वापस -EOPNOTSUPP;

	अगर (req->index)
		वापस -EINVAL;

	अगर (on) अणु
		u64 start_ns;
		u64 period_ns;

		start_ns = req->start.sec * NSEC_PER_SEC + req->start.nsec;
		period_ns = req->period.sec * NSEC_PER_SEC + req->period.nsec;

		अगर (start_ns > U32_MAX) अणु
			netdev_warn(ndev,
				    "ptp: start value (nsec) is over limit. Maximum size of start is only 32 bits\n");
			वापस -दुस्फल;
		पूर्ण

		अगर (period_ns > U32_MAX) अणु
			netdev_warn(ndev,
				    "ptp: period value (nsec) is over limit. Maximum size of period is only 32 bits\n");
			वापस -दुस्फल;
		पूर्ण

		spin_lock_irqsave(&priv->lock, flags);

		perout = &priv->ptp.perout[req->index];
		perout->target = (u32)start_ns;
		perout->period = (u32)period_ns;
		error = ravb_ptp_update_compare(priv, (u32)start_ns);
		अगर (!error) अणु
			/* Unmask पूर्णांकerrupt */
			अगर (priv->chip_id == RCAR_GEN2)
				ravb_modअगरy(ndev, GIC, GIC_PTME, GIC_PTME);
			अन्यथा
				ravb_ग_लिखो(ndev, GIE_PTMS0, GIE);
		पूर्ण
	पूर्ण अन्यथा	अणु
		spin_lock_irqsave(&priv->lock, flags);

		perout = &priv->ptp.perout[req->index];
		perout->period = 0;

		/* Mask पूर्णांकerrupt */
		अगर (priv->chip_id == RCAR_GEN2)
			ravb_modअगरy(ndev, GIC, GIC_PTME, 0);
		अन्यथा
			ravb_ग_लिखो(ndev, GID_PTMD0, GID);
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस error;
पूर्ण

अटल पूर्णांक ravb_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
			   काष्ठा ptp_घड़ी_request *req, पूर्णांक on)
अणु
	चयन (req->type) अणु
	हाल PTP_CLK_REQ_EXTTS:
		वापस ravb_ptp_extts(ptp, &req->extts, on);
	हाल PTP_CLK_REQ_PEROUT:
		वापस ravb_ptp_perout(ptp, &req->perout, on);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info ravb_ptp_info = अणु
	.owner		= THIS_MODULE,
	.name		= "ravb clock",
	.max_adj	= 50000000,
	.n_ext_ts	= N_EXT_TS,
	.n_per_out	= N_PER_OUT,
	.adjfreq	= ravb_ptp_adjfreq,
	.adjसमय	= ravb_ptp_adjसमय,
	.समय_लो64	= ravb_ptp_समय_लो64,
	.समय_रखो64	= ravb_ptp_समय_रखो64,
	.enable		= ravb_ptp_enable,
पूर्ण;

/* Caller must hold the lock */
व्योम ravb_ptp_पूर्णांकerrupt(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	u32 gis = ravb_पढ़ो(ndev, GIS);

	gis &= ravb_पढ़ो(ndev, GIC);
	अगर (gis & GIS_PTCF) अणु
		काष्ठा ptp_घड़ी_event event;

		event.type = PTP_CLOCK_EXTTS;
		event.index = 0;
		event.बारtamp = ravb_पढ़ो(ndev, GCPT);
		ptp_घड़ी_event(priv->ptp.घड़ी, &event);
	पूर्ण
	अगर (gis & GIS_PTMF) अणु
		काष्ठा ravb_ptp_perout *perout = priv->ptp.perout;

		अगर (perout->period) अणु
			perout->target += perout->period;
			ravb_ptp_update_compare(priv, perout->target);
		पूर्ण
	पूर्ण

	ravb_ग_लिखो(ndev, ~(gis | GIS_RESERVED), GIS);
पूर्ण

व्योम ravb_ptp_init(काष्ठा net_device *ndev, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	अचिन्हित दीर्घ flags;

	priv->ptp.info = ravb_ptp_info;

	priv->ptp.शेष_addend = ravb_पढ़ो(ndev, GTI);
	priv->ptp.current_addend = priv->ptp.शेष_addend;

	spin_lock_irqsave(&priv->lock, flags);
	ravb_रुको(ndev, GCCR, GCCR_TCR, GCCR_TCR_NOREQ);
	ravb_modअगरy(ndev, GCCR, GCCR_TCSS, GCCR_TCSS_ADJGPTP);
	spin_unlock_irqrestore(&priv->lock, flags);

	priv->ptp.घड़ी = ptp_घड़ी_रेजिस्टर(&priv->ptp.info, &pdev->dev);
पूर्ण

व्योम ravb_ptp_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	ravb_ग_लिखो(ndev, 0, GIC);
	ravb_ग_लिखो(ndev, 0, GIS);

	ptp_घड़ी_unरेजिस्टर(priv->ptp.घड़ी);
पूर्ण
