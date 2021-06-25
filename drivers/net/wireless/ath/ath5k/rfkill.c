<शैली गुरु>
/*
 * RFKILL support क्रम ath5k
 *
 * Copyright (c) 2009 Tobias Doerffel <tobias.करोerffel@gmail.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    similar to the "NO WARRANTY" disclaimer below ("Disclaimer") and any
 *    redistribution must be conditioned upon including a substantially
 *    similar Disclaimer requirement क्रम further binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF NONINFRINGEMENT, MERCHANTIBILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.
 */

#समावेश "ath5k.h"


अटल अंतरभूत व्योम ath5k_rfसमाप्त_disable(काष्ठा ath5k_hw *ah)
अणु
	ATH5K_DBG(ah, ATH5K_DEBUG_ANY, "rfkill disable (gpio:%d polarity:%d)\n",
		ah->rf_समाप्त.gpio, ah->rf_समाप्त.polarity);
	ath5k_hw_set_gpio_output(ah, ah->rf_समाप्त.gpio);
	ath5k_hw_set_gpio(ah, ah->rf_समाप्त.gpio, !ah->rf_समाप्त.polarity);
पूर्ण


अटल अंतरभूत व्योम ath5k_rfसमाप्त_enable(काष्ठा ath5k_hw *ah)
अणु
	ATH5K_DBG(ah, ATH5K_DEBUG_ANY, "rfkill enable (gpio:%d polarity:%d)\n",
		ah->rf_समाप्त.gpio, ah->rf_समाप्त.polarity);
	ath5k_hw_set_gpio_output(ah, ah->rf_समाप्त.gpio);
	ath5k_hw_set_gpio(ah, ah->rf_समाप्त.gpio, ah->rf_समाप्त.polarity);
पूर्ण

अटल अंतरभूत व्योम ath5k_rfसमाप्त_set_पूर्णांकr(काष्ठा ath5k_hw *ah, bool enable)
अणु
	u32 curval;

	ath5k_hw_set_gpio_input(ah, ah->rf_समाप्त.gpio);
	curval = ath5k_hw_get_gpio(ah, ah->rf_समाप्त.gpio);
	ath5k_hw_set_gpio_पूर्णांकr(ah, ah->rf_समाप्त.gpio, enable ?
					!!curval : !curval);
पूर्ण

अटल bool
ath5k_is_rfसमाप्त_set(काष्ठा ath5k_hw *ah)
अणु
	/* configuring GPIO क्रम input क्रम some reason disables rfसमाप्त */
	/*ath5k_hw_set_gpio_input(ah, ah->rf_समाप्त.gpio);*/
	वापस ath5k_hw_get_gpio(ah, ah->rf_समाप्त.gpio) ==
							ah->rf_समाप्त.polarity;
पूर्ण

अटल व्योम
ath5k_tasklet_rfसमाप्त_toggle(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ath5k_hw *ah = from_tasklet(ah, t, rf_समाप्त.toggleq);
	bool blocked;

	blocked = ath5k_is_rfसमाप्त_set(ah);
	wiphy_rfसमाप्त_set_hw_state(ah->hw->wiphy, blocked);
पूर्ण


व्योम
ath5k_rfसमाप्त_hw_start(काष्ठा ath5k_hw *ah)
अणु
	/* पढ़ो rfसमाप्त GPIO configuration from EEPROM header */
	ah->rf_समाप्त.gpio = ah->ah_capabilities.cap_eeprom.ee_rfसमाप्त_pin;
	ah->rf_समाप्त.polarity = ah->ah_capabilities.cap_eeprom.ee_rfसमाप्त_pol;

	tasklet_setup(&ah->rf_समाप्त.toggleq, ath5k_tasklet_rfसमाप्त_toggle);

	ath5k_rfसमाप्त_disable(ah);

	/* enable पूर्णांकerrupt क्रम rfसमाप्त चयन */
	अगर (AR5K_EEPROM_HDR_RFKILL(ah->ah_capabilities.cap_eeprom.ee_header))
		ath5k_rfसमाप्त_set_पूर्णांकr(ah, true);
पूर्ण


व्योम
ath5k_rfसमाप्त_hw_stop(काष्ठा ath5k_hw *ah)
अणु
	/* disable पूर्णांकerrupt क्रम rfसमाप्त चयन */
	अगर (AR5K_EEPROM_HDR_RFKILL(ah->ah_capabilities.cap_eeprom.ee_header))
		ath5k_rfसमाप्त_set_पूर्णांकr(ah, false);

	tasklet_समाप्त(&ah->rf_समाप्त.toggleq);

	/* enable RFKILL when stopping HW so Wअगरi LED is turned off */
	ath5k_rfसमाप्त_enable(ah);
पूर्ण

