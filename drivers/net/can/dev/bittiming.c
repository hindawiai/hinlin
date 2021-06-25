<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2005 Marc Kleine-Budde, Pengutronix
 * Copyright (C) 2006 Andrey Volkov, Varma Electronics
 * Copyright (C) 2008-2009 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 */

#समावेश <linux/can/dev.h>

#अगर_घोषित CONFIG_CAN_CALC_BITTIMING
#घोषणा CAN_CALC_MAX_ERROR 50 /* in one-tenth of a percent */

/* Bit-timing calculation derived from:
 *
 * Code based on LinCAN sources and H8S2638 project
 * Copyright 2004-2006 Pavel Pisa - DCE FELK CVUT cz
 * Copyright 2005      Stanislav Marek
 * email: pisa@cmp.felk.cvut.cz
 *
 * Calculates proper bit-timing parameters क्रम a specअगरied bit-rate
 * and sample-poपूर्णांक, which can then be used to set the bit-timing
 * रेजिस्टरs of the CAN controller. You can find more inक्रमmation
 * in the header file linux/can/netlink.h.
 */
अटल पूर्णांक
can_update_sample_poपूर्णांक(स्थिर काष्ठा can_bittiming_स्थिर *btc,
			अचिन्हित पूर्णांक sample_poपूर्णांक_nominal, अचिन्हित पूर्णांक tseg,
			अचिन्हित पूर्णांक *tseg1_ptr, अचिन्हित पूर्णांक *tseg2_ptr,
			अचिन्हित पूर्णांक *sample_poपूर्णांक_error_ptr)
अणु
	अचिन्हित पूर्णांक sample_poपूर्णांक_error, best_sample_poपूर्णांक_error = अच_पूर्णांक_उच्च;
	अचिन्हित पूर्णांक sample_poपूर्णांक, best_sample_poपूर्णांक = 0;
	अचिन्हित पूर्णांक tseg1, tseg2;
	पूर्णांक i;

	क्रम (i = 0; i <= 1; i++) अणु
		tseg2 = tseg + CAN_SYNC_SEG -
			(sample_poपूर्णांक_nominal * (tseg + CAN_SYNC_SEG)) /
			1000 - i;
		tseg2 = clamp(tseg2, btc->tseg2_min, btc->tseg2_max);
		tseg1 = tseg - tseg2;
		अगर (tseg1 > btc->tseg1_max) अणु
			tseg1 = btc->tseg1_max;
			tseg2 = tseg - tseg1;
		पूर्ण

		sample_poपूर्णांक = 1000 * (tseg + CAN_SYNC_SEG - tseg2) /
			(tseg + CAN_SYNC_SEG);
		sample_poपूर्णांक_error = असल(sample_poपूर्णांक_nominal - sample_poपूर्णांक);

		अगर (sample_poपूर्णांक <= sample_poपूर्णांक_nominal &&
		    sample_poपूर्णांक_error < best_sample_poपूर्णांक_error) अणु
			best_sample_poपूर्णांक = sample_poपूर्णांक;
			best_sample_poपूर्णांक_error = sample_poपूर्णांक_error;
			*tseg1_ptr = tseg1;
			*tseg2_ptr = tseg2;
		पूर्ण
	पूर्ण

	अगर (sample_poपूर्णांक_error_ptr)
		*sample_poपूर्णांक_error_ptr = best_sample_poपूर्णांक_error;

	वापस best_sample_poपूर्णांक;
पूर्ण

पूर्णांक can_calc_bittiming(काष्ठा net_device *dev, काष्ठा can_bittiming *bt,
		       स्थिर काष्ठा can_bittiming_स्थिर *btc)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक bitrate;			/* current bitrate */
	अचिन्हित पूर्णांक bitrate_error;		/* dअगरference between current and nominal value */
	अचिन्हित पूर्णांक best_bitrate_error = अच_पूर्णांक_उच्च;
	अचिन्हित पूर्णांक sample_poपूर्णांक_error;	/* dअगरference between current and nominal value */
	अचिन्हित पूर्णांक best_sample_poपूर्णांक_error = अच_पूर्णांक_उच्च;
	अचिन्हित पूर्णांक sample_poपूर्णांक_nominal;	/* nominal sample poपूर्णांक */
	अचिन्हित पूर्णांक best_tseg = 0;		/* current best value क्रम tseg */
	अचिन्हित पूर्णांक best_brp = 0;		/* current best value क्रम brp */
	अचिन्हित पूर्णांक brp, tsegall, tseg, tseg1 = 0, tseg2 = 0;
	u64 v64;

	/* Use CiA recommended sample poपूर्णांकs */
	अगर (bt->sample_poपूर्णांक) अणु
		sample_poपूर्णांक_nominal = bt->sample_poपूर्णांक;
	पूर्ण अन्यथा अणु
		अगर (bt->bitrate > 800 * CAN_KBPS)
			sample_poपूर्णांक_nominal = 750;
		अन्यथा अगर (bt->bitrate > 500 * CAN_KBPS)
			sample_poपूर्णांक_nominal = 800;
		अन्यथा
			sample_poपूर्णांक_nominal = 875;
	पूर्ण

	/* tseg even = round करोwn, odd = round up */
	क्रम (tseg = (btc->tseg1_max + btc->tseg2_max) * 2 + 1;
	     tseg >= (btc->tseg1_min + btc->tseg2_min) * 2; tseg--) अणु
		tsegall = CAN_SYNC_SEG + tseg / 2;

		/* Compute all possible tseg choices (tseg=tseg1+tseg2) */
		brp = priv->घड़ी.freq / (tsegall * bt->bitrate) + tseg % 2;

		/* choose brp step which is possible in प्रणाली */
		brp = (brp / btc->brp_inc) * btc->brp_inc;
		अगर (brp < btc->brp_min || brp > btc->brp_max)
			जारी;

		bitrate = priv->घड़ी.freq / (brp * tsegall);
		bitrate_error = असल(bt->bitrate - bitrate);

		/* tseg brp biterror */
		अगर (bitrate_error > best_bitrate_error)
			जारी;

		/* reset sample poपूर्णांक error अगर we have a better bitrate */
		अगर (bitrate_error < best_bitrate_error)
			best_sample_poपूर्णांक_error = अच_पूर्णांक_उच्च;

		can_update_sample_poपूर्णांक(btc, sample_poपूर्णांक_nominal, tseg / 2,
					&tseg1, &tseg2, &sample_poपूर्णांक_error);
		अगर (sample_poपूर्णांक_error > best_sample_poपूर्णांक_error)
			जारी;

		best_sample_poपूर्णांक_error = sample_poपूर्णांक_error;
		best_bitrate_error = bitrate_error;
		best_tseg = tseg / 2;
		best_brp = brp;

		अगर (bitrate_error == 0 && sample_poपूर्णांक_error == 0)
			अवरोध;
	पूर्ण

	अगर (best_bitrate_error) अणु
		/* Error in one-tenth of a percent */
		v64 = (u64)best_bitrate_error * 1000;
		करो_भाग(v64, bt->bitrate);
		bitrate_error = (u32)v64;
		अगर (bitrate_error > CAN_CALC_MAX_ERROR) अणु
			netdev_err(dev,
				   "bitrate error %d.%d%% too high\n",
				   bitrate_error / 10, bitrate_error % 10);
			वापस -गलत_तर्क;
		पूर्ण
		netdev_warn(dev, "bitrate error %d.%d%%\n",
			    bitrate_error / 10, bitrate_error % 10);
	पूर्ण

	/* real sample poपूर्णांक */
	bt->sample_poपूर्णांक = can_update_sample_poपूर्णांक(btc, sample_poपूर्णांक_nominal,
						   best_tseg, &tseg1, &tseg2,
						   शून्य);

	v64 = (u64)best_brp * 1000 * 1000 * 1000;
	करो_भाग(v64, priv->घड़ी.freq);
	bt->tq = (u32)v64;
	bt->prop_seg = tseg1 / 2;
	bt->phase_seg1 = tseg1 - bt->prop_seg;
	bt->phase_seg2 = tseg2;

	/* check क्रम sjw user settings */
	अगर (!bt->sjw || !btc->sjw_max) अणु
		bt->sjw = 1;
	पूर्ण अन्यथा अणु
		/* bt->sjw is at least 1 -> sanitize upper bound to sjw_max */
		अगर (bt->sjw > btc->sjw_max)
			bt->sjw = btc->sjw_max;
		/* bt->sjw must not be higher than tseg2 */
		अगर (tseg2 < bt->sjw)
			bt->sjw = tseg2;
	पूर्ण

	bt->brp = best_brp;

	/* real bitrate */
	bt->bitrate = priv->घड़ी.freq /
		(bt->brp * (CAN_SYNC_SEG + tseg1 + tseg2));

	वापस 0;
पूर्ण

व्योम can_calc_tdco(काष्ठा net_device *dev)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);
	स्थिर काष्ठा can_bittiming *dbt = &priv->data_bittiming;
	काष्ठा can_tdc *tdc = &priv->tdc;
	स्थिर काष्ठा can_tdc_स्थिर *tdc_स्थिर = priv->tdc_स्थिर;

	अगर (!tdc_स्थिर)
		वापस;

	/* As specअगरied in ISO 11898-1 section 11.3.3 "Transmitter
	 * delay compensation" (TDC) is only applicable अगर data BRP is
	 * one or two.
	 */
	अगर (dbt->brp == 1 || dbt->brp == 2) अणु
		/* Reuse "normal" sample poपूर्णांक and convert it to समय quanta */
		u32 sample_poपूर्णांक_in_tq = can_bit_समय(dbt) * dbt->sample_poपूर्णांक / 1000;

		tdc->tdco = min(sample_poपूर्णांक_in_tq, tdc_स्थिर->tdco_max);
	पूर्ण अन्यथा अणु
		tdc->tdco = 0;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_CAN_CALC_BITTIMING */

/* Checks the validity of the specअगरied bit-timing parameters prop_seg,
 * phase_seg1, phase_seg2 and sjw and tries to determine the bitrate
 * prescaler value brp. You can find more inक्रमmation in the header
 * file linux/can/netlink.h.
 */
अटल पूर्णांक can_fixup_bittiming(काष्ठा net_device *dev, काष्ठा can_bittiming *bt,
			       स्थिर काष्ठा can_bittiming_स्थिर *btc)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);
	पूर्णांक tseg1, alltseg;
	u64 brp64;

	tseg1 = bt->prop_seg + bt->phase_seg1;
	अगर (!bt->sjw)
		bt->sjw = 1;
	अगर (bt->sjw > btc->sjw_max ||
	    tseg1 < btc->tseg1_min || tseg1 > btc->tseg1_max ||
	    bt->phase_seg2 < btc->tseg2_min || bt->phase_seg2 > btc->tseg2_max)
		वापस -दुस्फल;

	brp64 = (u64)priv->घड़ी.freq * (u64)bt->tq;
	अगर (btc->brp_inc > 1)
		करो_भाग(brp64, btc->brp_inc);
	brp64 += 500000000UL - 1;
	करो_भाग(brp64, 1000000000UL); /* the practicable BRP */
	अगर (btc->brp_inc > 1)
		brp64 *= btc->brp_inc;
	bt->brp = (u32)brp64;

	अगर (bt->brp < btc->brp_min || bt->brp > btc->brp_max)
		वापस -EINVAL;

	alltseg = bt->prop_seg + bt->phase_seg1 + bt->phase_seg2 + 1;
	bt->bitrate = priv->घड़ी.freq / (bt->brp * alltseg);
	bt->sample_poपूर्णांक = ((tseg1 + 1) * 1000) / alltseg;

	वापस 0;
पूर्ण

/* Checks the validity of predefined bitrate settings */
अटल पूर्णांक
can_validate_bitrate(काष्ठा net_device *dev, काष्ठा can_bittiming *bt,
		     स्थिर u32 *bitrate_स्थिर,
		     स्थिर अचिन्हित पूर्णांक bitrate_स्थिर_cnt)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < bitrate_स्थिर_cnt; i++) अणु
		अगर (bt->bitrate == bitrate_स्थिर[i])
			अवरोध;
	पूर्ण

	अगर (i >= priv->bitrate_स्थिर_cnt)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक can_get_bittiming(काष्ठा net_device *dev, काष्ठा can_bittiming *bt,
		      स्थिर काष्ठा can_bittiming_स्थिर *btc,
		      स्थिर u32 *bitrate_स्थिर,
		      स्थिर अचिन्हित पूर्णांक bitrate_स्थिर_cnt)
अणु
	पूर्णांक err;

	/* Depending on the given can_bittiming parameter काष्ठाure the CAN
	 * timing parameters are calculated based on the provided bitrate OR
	 * alternatively the CAN timing parameters (tq, prop_seg, etc.) are
	 * provided directly which are then checked and fixed up.
	 */
	अगर (!bt->tq && bt->bitrate && btc)
		err = can_calc_bittiming(dev, bt, btc);
	अन्यथा अगर (bt->tq && !bt->bitrate && btc)
		err = can_fixup_bittiming(dev, bt, btc);
	अन्यथा अगर (!bt->tq && bt->bitrate && bitrate_स्थिर)
		err = can_validate_bitrate(dev, bt, bitrate_स्थिर,
					   bitrate_स्थिर_cnt);
	अन्यथा
		err = -EINVAL;

	वापस err;
पूर्ण
