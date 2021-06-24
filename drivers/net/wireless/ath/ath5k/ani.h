<शैली गुरु>
/*
 * Copyright (C) 2010 Bruno Ranकरोlf <br1@einfach.org>
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
#अगर_अघोषित ANI_H
#घोषणा ANI_H

#समावेश "../ath.h"

क्रमागत ath5k_phy_error_code;

/* these thresholds are relative to the ATH5K_ANI_LISTEN_PERIOD */
#घोषणा ATH5K_ANI_LISTEN_PERIOD		100
#घोषणा ATH5K_ANI_OFDM_TRIG_HIGH	500
#घोषणा ATH5K_ANI_OFDM_TRIG_LOW		200
#घोषणा ATH5K_ANI_CCK_TRIG_HIGH		200
#घोषणा ATH5K_ANI_CCK_TRIG_LOW		100

/* average beacon RSSI thresholds */
#घोषणा ATH5K_ANI_RSSI_THR_HIGH		40
#घोषणा ATH5K_ANI_RSSI_THR_LOW		7

/* maximum available levels */
#घोषणा ATH5K_ANI_MAX_FIRSTEP_LVL	2
#घोषणा ATH5K_ANI_MAX_NOISE_IMM_LVL	1


/**
 * क्रमागत ath5k_ani_mode - mode क्रम ANI / noise sensitivity
 *
 * @ATH5K_ANI_MODE_OFF: Turn ANI off. This can be useful to just stop the ANI
 *			algorithm after it has been on स्वतः mode.
 * @ATH5K_ANI_MODE_MANUAL_LOW: Manually set all immunity parameters to low,
 *			maximizing sensitivity. ANI will not run.
 * @ATH5K_ANI_MODE_MANUAL_HIGH: Manually set all immunity parameters to high,
 *			minimizing sensitivity. ANI will not run.
 * @ATH5K_ANI_MODE_AUTO: Automatically control immunity parameters based on the
 *			amount of OFDM and CCK frame errors (शेष).
 */
क्रमागत ath5k_ani_mode अणु
	ATH5K_ANI_MODE_OFF		= 0,
	ATH5K_ANI_MODE_MANUAL_LOW	= 1,
	ATH5K_ANI_MODE_MANUAL_HIGH	= 2,
	ATH5K_ANI_MODE_AUTO		= 3
पूर्ण;


/**
 * काष्ठा ath5k_ani_state - ANI state and associated counters
 * @ani_mode: One of क्रमागत ath5k_ani_mode
 * @noise_imm_level: Noise immunity level
 * @spur_level: Spur immunity level
 * @firstep_level: FIRstep level
 * @ofdm_weak_sig: OFDM weak संकेत detection state (on/off)
 * @cck_weak_sig: CCK weak संकेत detection state (on/off)
 * @max_spur_level: Max spur immunity level (chip specअगरic)
 * @listen_समय: Listen समय
 * @ofdm_errors: OFDM timing error count
 * @cck_errors: CCK timing error count
 * @last_cc: The &काष्ठा ath_cycle_counters (क्रम stats)
 * @last_listen: Listen समय from previous run (क्रम stats)
 * @last_ofdm_errors: OFDM timing error count from previous run (क्रम tats)
 * @last_cck_errors: CCK timing error count from previous run (क्रम stats)
 * @sum_ofdm_errors: Sum of OFDM timing errors (क्रम stats)
 * @sum_cck_errors: Sum of all CCK timing errors (क्रम stats)
 */
काष्ठा ath5k_ani_state अणु
	क्रमागत ath5k_ani_mode	ani_mode;

	/* state */
	पूर्णांक			noise_imm_level;
	पूर्णांक			spur_level;
	पूर्णांक			firstep_level;
	bool			ofdm_weak_sig;
	bool			cck_weak_sig;

	पूर्णांक			max_spur_level;

	/* used by the algorithm */
	अचिन्हित पूर्णांक		listen_समय;
	अचिन्हित पूर्णांक		ofdm_errors;
	अचिन्हित पूर्णांक		cck_errors;

	/* debug/statistics only: numbers from last ANI calibration */
	काष्ठा ath_cycle_counters last_cc;
	अचिन्हित पूर्णांक		last_listen;
	अचिन्हित पूर्णांक		last_ofdm_errors;
	अचिन्हित पूर्णांक		last_cck_errors;
	अचिन्हित पूर्णांक		sum_ofdm_errors;
	अचिन्हित पूर्णांक		sum_cck_errors;
पूर्ण;

व्योम ath5k_ani_init(काष्ठा ath5k_hw *ah, क्रमागत ath5k_ani_mode mode);
व्योम ath5k_ani_mib_पूर्णांकr(काष्ठा ath5k_hw *ah);
व्योम ath5k_ani_calibration(काष्ठा ath5k_hw *ah);
व्योम ath5k_ani_phy_error_report(काष्ठा ath5k_hw *ah,
				क्रमागत ath5k_phy_error_code phyerr);

/* क्रम manual control */
व्योम ath5k_ani_set_noise_immunity_level(काष्ठा ath5k_hw *ah, पूर्णांक level);
व्योम ath5k_ani_set_spur_immunity_level(काष्ठा ath5k_hw *ah, पूर्णांक level);
व्योम ath5k_ani_set_firstep_level(काष्ठा ath5k_hw *ah, पूर्णांक level);
व्योम ath5k_ani_set_ofdm_weak_संकेत_detection(काष्ठा ath5k_hw *ah, bool on);
व्योम ath5k_ani_set_cck_weak_संकेत_detection(काष्ठा ath5k_hw *ah, bool on);

व्योम ath5k_ani_prपूर्णांक_counters(काष्ठा ath5k_hw *ah);

#पूर्ण_अगर /* ANI_H */
