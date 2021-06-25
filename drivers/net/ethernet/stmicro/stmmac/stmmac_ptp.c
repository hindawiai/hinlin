<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  PTP 1588 घड़ी using the STMMAC.

  Copyright (C) 2013  Vayavya Lअसल Pvt Ltd


  Author: Rayagond Kokatanur <rayagond@vayavyaद_असल.com>
*******************************************************************************/
#समावेश "stmmac.h"
#समावेश "stmmac_ptp.h"
#समावेश "dwmac4.h"

/**
 * sपंचांगmac_adjust_freq
 *
 * @ptp: poपूर्णांकer to ptp_घड़ी_info काष्ठाure
 * @ppb: desired period change in parts ber billion
 *
 * Description: this function will adjust the frequency of hardware घड़ी.
 */
अटल पूर्णांक sपंचांगmac_adjust_freq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	काष्ठा sपंचांगmac_priv *priv =
	    container_of(ptp, काष्ठा sपंचांगmac_priv, ptp_घड़ी_ops);
	अचिन्हित दीर्घ flags;
	u32 dअगरf, addend;
	पूर्णांक neg_adj = 0;
	u64 adj;

	अगर (ppb < 0) अणु
		neg_adj = 1;
		ppb = -ppb;
	पूर्ण

	addend = priv->शेष_addend;
	adj = addend;
	adj *= ppb;
	dअगरf = भाग_u64(adj, 1000000000ULL);
	addend = neg_adj ? (addend - dअगरf) : (addend + dअगरf);

	spin_lock_irqsave(&priv->ptp_lock, flags);
	sपंचांगmac_config_addend(priv, priv->ptpaddr, addend);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	वापस 0;
पूर्ण

/**
 * sपंचांगmac_adjust_समय
 *
 * @ptp: poपूर्णांकer to ptp_घड़ी_info काष्ठाure
 * @delta: desired change in nanoseconds
 *
 * Description: this function will shअगरt/adjust the hardware घड़ी समय.
 */
अटल पूर्णांक sपंचांगmac_adjust_समय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा sपंचांगmac_priv *priv =
	    container_of(ptp, काष्ठा sपंचांगmac_priv, ptp_घड़ी_ops);
	अचिन्हित दीर्घ flags;
	u32 sec, nsec;
	u32 quotient, reminder;
	पूर्णांक neg_adj = 0;
	bool xmac;

	xmac = priv->plat->has_gmac4 || priv->plat->has_xgmac;

	अगर (delta < 0) अणु
		neg_adj = 1;
		delta = -delta;
	पूर्ण

	quotient = भाग_u64_rem(delta, 1000000000ULL, &reminder);
	sec = quotient;
	nsec = reminder;

	spin_lock_irqsave(&priv->ptp_lock, flags);
	sपंचांगmac_adjust_sysसमय(priv, priv->ptpaddr, sec, nsec, neg_adj, xmac);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	वापस 0;
पूर्ण

/**
 * sपंचांगmac_get_समय
 *
 * @ptp: poपूर्णांकer to ptp_घड़ी_info काष्ठाure
 * @ts: poपूर्णांकer to hold समय/result
 *
 * Description: this function will पढ़ो the current समय from the
 * hardware घड़ी and store it in @ts.
 */
अटल पूर्णांक sपंचांगmac_get_समय(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	काष्ठा sपंचांगmac_priv *priv =
	    container_of(ptp, काष्ठा sपंचांगmac_priv, ptp_घड़ी_ops);
	अचिन्हित दीर्घ flags;
	u64 ns = 0;

	spin_lock_irqsave(&priv->ptp_lock, flags);
	sपंचांगmac_get_sysसमय(priv, priv->ptpaddr, &ns);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

/**
 * sपंचांगmac_set_समय
 *
 * @ptp: poपूर्णांकer to ptp_घड़ी_info काष्ठाure
 * @ts: समय value to set
 *
 * Description: this function will set the current समय on the
 * hardware घड़ी.
 */
अटल पूर्णांक sपंचांगmac_set_समय(काष्ठा ptp_घड़ी_info *ptp,
			   स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा sपंचांगmac_priv *priv =
	    container_of(ptp, काष्ठा sपंचांगmac_priv, ptp_घड़ी_ops);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->ptp_lock, flags);
	sपंचांगmac_init_sysसमय(priv, priv->ptpaddr, ts->tv_sec, ts->tv_nsec);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_enable(काष्ठा ptp_घड़ी_info *ptp,
			 काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा sपंचांगmac_priv *priv =
	    container_of(ptp, काष्ठा sपंचांगmac_priv, ptp_घड़ी_ops);
	व्योम __iomem *ptpaddr = priv->ptpaddr;
	व्योम __iomem *ioaddr = priv->hw->pcsr;
	काष्ठा sपंचांगmac_pps_cfg *cfg;
	u32 पूर्णांकr_value, acr_value;
	पूर्णांक ret = -EOPNOTSUPP;
	अचिन्हित दीर्घ flags;

	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_PEROUT:
		/* Reject requests with unsupported flags */
		अगर (rq->perout.flags)
			वापस -EOPNOTSUPP;

		cfg = &priv->pps[rq->perout.index];

		cfg->start.tv_sec = rq->perout.start.sec;
		cfg->start.tv_nsec = rq->perout.start.nsec;
		cfg->period.tv_sec = rq->perout.period.sec;
		cfg->period.tv_nsec = rq->perout.period.nsec;

		spin_lock_irqsave(&priv->ptp_lock, flags);
		ret = sपंचांगmac_flex_pps_config(priv, priv->ioaddr,
					     rq->perout.index, cfg, on,
					     priv->sub_second_inc,
					     priv->sysसमय_flags);
		spin_unlock_irqrestore(&priv->ptp_lock, flags);
		अवरोध;
	हाल PTP_CLK_REQ_EXTTS:
		priv->plat->ext_snapshot_en = on;
		mutex_lock(&priv->aux_ts_lock);
		acr_value = पढ़ोl(ptpaddr + PTP_ACR);
		acr_value &= ~PTP_ACR_MASK;
		अगर (on) अणु
			/* Enable External snapshot trigger */
			acr_value |= priv->plat->ext_snapshot_num;
			acr_value |= PTP_ACR_ATSFC;
			netdev_dbg(priv->dev, "Auxiliary Snapshot %d enabled.\n",
				   priv->plat->ext_snapshot_num >>
				   PTP_ACR_ATSEN_SHIFT);
			/* Enable Timestamp Interrupt */
			पूर्णांकr_value = पढ़ोl(ioaddr + GMAC_INT_EN);
			पूर्णांकr_value |= GMAC_INT_TSIE;
			ग_लिखोl(पूर्णांकr_value, ioaddr + GMAC_INT_EN);

		पूर्ण अन्यथा अणु
			netdev_dbg(priv->dev, "Auxiliary Snapshot %d disabled.\n",
				   priv->plat->ext_snapshot_num >>
				   PTP_ACR_ATSEN_SHIFT);
			/* Disable Timestamp Interrupt */
			पूर्णांकr_value = पढ़ोl(ioaddr + GMAC_INT_EN);
			पूर्णांकr_value &= ~GMAC_INT_TSIE;
			ग_लिखोl(पूर्णांकr_value, ioaddr + GMAC_INT_EN);
		पूर्ण
		ग_लिखोl(acr_value, ptpaddr + PTP_ACR);
		mutex_unlock(&priv->aux_ts_lock);
		ret = 0;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * sपंचांगmac_get_syncdeviceसमय
 * @device: current device समय
 * @प्रणाली: प्रणाली counter value पढ़ो synchronously with device समय
 * @ctx: context provided by समयkeeping code
 * Description: Read device and प्रणाली घड़ी simultaneously and वापस the
 * corrected घड़ी values in ns.
 **/
अटल पूर्णांक sपंचांगmac_get_syncdeviceसमय(kसमय_प्रकार *device,
				     काष्ठा प्रणाली_counterval_t *प्रणाली,
				     व्योम *ctx)
अणु
	काष्ठा sपंचांगmac_priv *priv = (काष्ठा sपंचांगmac_priv *)ctx;

	अगर (priv->plat->crosststamp)
		वापस priv->plat->crosststamp(device, प्रणाली, ctx);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक sपंचांगmac_अ_लोrosststamp(काष्ठा ptp_घड़ी_info *ptp,
				 काष्ठा प्रणाली_device_crosststamp *xtstamp)
अणु
	काष्ठा sपंचांगmac_priv *priv =
		container_of(ptp, काष्ठा sपंचांगmac_priv, ptp_घड़ी_ops);

	वापस get_device_प्रणाली_crosststamp(sपंचांगmac_get_syncdeviceसमय,
					     priv, शून्य, xtstamp);
पूर्ण

/* काष्ठाure describing a PTP hardware घड़ी */
अटल काष्ठा ptp_घड़ी_info sपंचांगmac_ptp_घड़ी_ops = अणु
	.owner = THIS_MODULE,
	.name = "stmmac ptp",
	.max_adj = 62500000,
	.n_alarm = 0,
	.n_ext_ts = 0, /* will be overwritten in sपंचांगmac_ptp_रेजिस्टर */
	.n_per_out = 0, /* will be overwritten in sपंचांगmac_ptp_रेजिस्टर */
	.n_pins = 0,
	.pps = 0,
	.adjfreq = sपंचांगmac_adjust_freq,
	.adjसमय = sपंचांगmac_adjust_समय,
	.समय_लो64 = sपंचांगmac_get_समय,
	.समय_रखो64 = sपंचांगmac_set_समय,
	.enable = sपंचांगmac_enable,
	.अ_लोrosststamp = sपंचांगmac_अ_लोrosststamp,
पूर्ण;

/**
 * sपंचांगmac_ptp_रेजिस्टर
 * @priv: driver निजी काष्ठाure
 * Description: this function will रेजिस्टर the ptp घड़ी driver
 * to kernel. It also करोes some house keeping work.
 */
व्योम sपंचांगmac_ptp_रेजिस्टर(काष्ठा sपंचांगmac_priv *priv)
अणु
	पूर्णांक i;

	अगर (priv->plat->ptp_clk_freq_config)
		priv->plat->ptp_clk_freq_config(priv);

	क्रम (i = 0; i < priv->dma_cap.pps_out_num; i++) अणु
		अगर (i >= STMMAC_PPS_MAX)
			अवरोध;
		priv->pps[i].available = true;
	पूर्ण

	अगर (priv->plat->ptp_max_adj)
		sपंचांगmac_ptp_घड़ी_ops.max_adj = priv->plat->ptp_max_adj;

	sपंचांगmac_ptp_घड़ी_ops.n_per_out = priv->dma_cap.pps_out_num;
	sपंचांगmac_ptp_घड़ी_ops.n_ext_ts = priv->dma_cap.aux_snapshot_n;

	spin_lock_init(&priv->ptp_lock);
	mutex_init(&priv->aux_ts_lock);
	priv->ptp_घड़ी_ops = sपंचांगmac_ptp_घड़ी_ops;

	priv->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&priv->ptp_घड़ी_ops,
					     priv->device);
	अगर (IS_ERR(priv->ptp_घड़ी)) अणु
		netdev_err(priv->dev, "ptp_clock_register failed\n");
		priv->ptp_घड़ी = शून्य;
	पूर्ण अन्यथा अगर (priv->ptp_घड़ी)
		netdev_info(priv->dev, "registered PTP clock\n");
पूर्ण

/**
 * sपंचांगmac_ptp_unरेजिस्टर
 * @priv: driver निजी काष्ठाure
 * Description: this function will हटाओ/unरेजिस्टर the ptp घड़ी driver
 * from the kernel.
 */
व्योम sपंचांगmac_ptp_unरेजिस्टर(काष्ठा sपंचांगmac_priv *priv)
अणु
	अगर (priv->ptp_घड़ी) अणु
		ptp_घड़ी_unरेजिस्टर(priv->ptp_घड़ी);
		priv->ptp_घड़ी = शून्य;
		pr_debug("Removed PTP HW clock successfully on %s\n",
			 priv->dev->name);
	पूर्ण

	mutex_destroy(&priv->aux_ts_lock);
पूर्ण
