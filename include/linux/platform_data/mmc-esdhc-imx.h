<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2010 Wolfram Sang <kernel@pengutronix.de>
 */

#अगर_अघोषित __ASM_ARCH_IMX_ESDHC_H
#घोषणा __ASM_ARCH_IMX_ESDHC_H

#समावेश <linux/types.h>

क्रमागत wp_types अणु
	ESDHC_WP_NONE,		/* no WP, neither controller nor gpio */
	ESDHC_WP_CONTROLLER,	/* mmc controller पूर्णांकernal WP */
	ESDHC_WP_GPIO,		/* बाह्यal gpio pin क्रम WP */
पूर्ण;

क्रमागत cd_types अणु
	ESDHC_CD_NONE,		/* no CD, neither controller nor gpio */
	ESDHC_CD_CONTROLLER,	/* mmc controller पूर्णांकernal CD */
	ESDHC_CD_GPIO,		/* बाह्यal gpio pin क्रम CD */
	ESDHC_CD_PERMANENT,	/* no CD, card permanently wired to host */
पूर्ण;

/**
 * काष्ठा esdhc_platक्रमm_data - platक्रमm data क्रम esdhc on i.MX
 *
 * ESDHC_WP(CD)_CONTROLLER type is not available on i.MX25/35.
 *
 * @wp_type:	type of ग_लिखो_protect method (see wp_types क्रमागत above)
 * @cd_type:	type of card_detect method (see cd_types क्रमागत above)
 */

काष्ठा esdhc_platक्रमm_data अणु
	क्रमागत wp_types wp_type;
	क्रमागत cd_types cd_type;
	पूर्णांक max_bus_width;
	अचिन्हित पूर्णांक delay_line;
	अचिन्हित पूर्णांक tuning_step;       /* The delay cell steps in tuning procedure */
	अचिन्हित पूर्णांक tuning_start_tap;	/* The start delay cell poपूर्णांक in tuning procedure */
	अचिन्हित पूर्णांक strobe_dll_delay_target;	/* The delay cell क्रम strobe pad (पढ़ो घड़ी) */
पूर्ण;
#पूर्ण_अगर /* __ASM_ARCH_IMX_ESDHC_H */
