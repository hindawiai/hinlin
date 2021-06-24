<शैली गुरु>
/*
 * Copyright (c) 2015 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "ath9k.h"
#समावेश "hw.h"
#समावेश "ar9003_phy.h"

#घोषणा ATH9K_RNG_BUF_SIZE	320
#घोषणा ATH9K_RNG_ENTROPY(x)	(((x) * 8 * 10) >> 5) /* quality: 10/32 */

अटल DECLARE_WAIT_QUEUE_HEAD(rng_queue);

अटल पूर्णांक ath9k_rng_data_पढ़ो(काष्ठा ath_softc *sc, u32 *buf, u32 buf_size)
अणु
	पूर्णांक i, j;
	u32  v1, v2, rng_last = sc->rng_last;
	काष्ठा ath_hw *ah = sc->sc_ah;

	ath9k_ps_wakeup(sc);

	REG_RMW_FIELD(ah, AR_PHY_TEST, AR_PHY_TEST_BBB_OBS_SEL, 1);
	REG_CLR_BIT(ah, AR_PHY_TEST, AR_PHY_TEST_RX_OBS_SEL_BIT5);
	REG_RMW_FIELD(ah, AR_PHY_TEST_CTL_STATUS, AR_PHY_TEST_CTL_RX_OBS_SEL, 0);

	क्रम (i = 0, j = 0; i < buf_size; i++) अणु
		v1 = REG_READ(ah, AR_PHY_TST_ADC) & 0xffff;
		v2 = REG_READ(ah, AR_PHY_TST_ADC) & 0xffff;

		/* रुको क्रम data पढ़ोy */
		अगर (v1 && v2 && rng_last != v1 && v1 != v2 && v1 != 0xffff &&
		    v2 != 0xffff)
			buf[j++] = (v1 << 16) | v2;

		rng_last = v2;
	पूर्ण

	ath9k_ps_restore(sc);

	sc->rng_last = rng_last;

	वापस j << 2;
पूर्ण

अटल u32 ath9k_rng_delay_get(u32 fail_stats)
अणु
	u32 delay;

	अगर (fail_stats < 100)
		delay = 10;
	अन्यथा अगर (fail_stats < 105)
		delay = 1000;
	अन्यथा
		delay = 10000;

	वापस delay;
पूर्ण

अटल पूर्णांक ath9k_rng_kthपढ़ो(व्योम *data)
अणु
	पूर्णांक bytes_पढ़ो;
	काष्ठा ath_softc *sc = data;
	u32 *rng_buf;
	u32 delay, fail_stats = 0;

	rng_buf = kदो_स्मृति_array(ATH9K_RNG_BUF_SIZE, माप(u32), GFP_KERNEL);
	अगर (!rng_buf)
		जाओ out;

	जबतक (!kthपढ़ो_should_stop()) अणु
		bytes_पढ़ो = ath9k_rng_data_पढ़ो(sc, rng_buf,
						 ATH9K_RNG_BUF_SIZE);
		अगर (unlikely(!bytes_पढ़ो)) अणु
			delay = ath9k_rng_delay_get(++fail_stats);
			रुको_event_पूर्णांकerruptible_समयout(rng_queue,
							 kthपढ़ो_should_stop(),
							 msecs_to_jअगरfies(delay));
			जारी;
		पूर्ण

		fail_stats = 0;

		/* sleep until entropy bits under ग_लिखो_wakeup_threshold */
		add_hwgenerator_अक्रमomness((व्योम *)rng_buf, bytes_पढ़ो,
					   ATH9K_RNG_ENTROPY(bytes_पढ़ो));
	पूर्ण

	kमुक्त(rng_buf);
out:
	sc->rng_task = शून्य;

	वापस 0;
पूर्ण

व्योम ath9k_rng_start(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;

	अगर (sc->rng_task)
		वापस;

	अगर (!AR_SREV_9300_20_OR_LATER(ah))
		वापस;

	sc->rng_task = kthपढ़ो_run(ath9k_rng_kthपढ़ो, sc, "ath9k-hwrng");
	अगर (IS_ERR(sc->rng_task))
		sc->rng_task = शून्य;
पूर्ण

व्योम ath9k_rng_stop(काष्ठा ath_softc *sc)
अणु
	अगर (sc->rng_task) अणु
		kthपढ़ो_stop(sc->rng_task);
		sc->rng_task = शून्य;
	पूर्ण
पूर्ण
