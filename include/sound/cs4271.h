<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Definitions क्रम CS4271 ASoC codec driver
 *
 * Copyright (c) 2010 Alexander Sverdlin <subaparts@yandex.ru>
 */

#अगर_अघोषित __CS4271_H
#घोषणा __CS4271_H

काष्ठा cs4271_platक्रमm_data अणु
	पूर्णांक gpio_nreset;	/* GPIO driving Reset pin, अगर any */
	bool amutec_eq_bmutec;	/* flag to enable AMUTEC=BMUTEC */

	/*
	 * The CS4271 requires its LRCLK and MCLK to be stable beक्रमe its RESET
	 * line is de-निश्चितed. That also means that घड़ीs cannot be changed
	 * without putting the chip back पूर्णांकo hardware reset, which also requires
	 * a complete re-initialization of all रेजिस्टरs.
	 *
	 * One (unकरोcumented) workaround is to निश्चित and de-निश्चित the PDN bit
	 * in the MODE2 रेजिस्टर. This workaround can be enabled with the
	 * following flag.
	 *
	 * Note that this is not needed in हाल the घड़ीs are stable
	 * throughout the entire runसमय of the codec.
	 */
	bool enable_soft_reset;
पूर्ण;

#पूर्ण_अगर /* __CS4271_H */
