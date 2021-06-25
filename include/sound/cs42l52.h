<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/cs42l52.h -- Platक्रमm data क्रम CS42L52
 *
 * Copyright (c) 2012 Cirrus Logic Inc.
 */

#अगर_अघोषित __CS42L52_H
#घोषणा __CS42L52_H

काष्ठा cs42l52_platक्रमm_data अणु

	/* MICBIAS Level. Check datasheet Pg48 */
	अचिन्हित पूर्णांक micbias_lvl;

	/* MICA mode selection Dअगरferential or Single-ended */
	bool mica_dअगरf_cfg;

	/* MICB mode selection Dअगरferential or Single-ended */
	bool micb_dअगरf_cfg;

	/* Charge Pump Freq. Check datasheet Pg73 */
	अचिन्हित पूर्णांक chgfreq;

	/* Reset GPIO */
	अचिन्हित पूर्णांक reset_gpio;
पूर्ण;

#पूर्ण_अगर /* __CS42L52_H */
