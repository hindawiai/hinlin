<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/wm9090.h -- Platक्रमm data क्रम WM9090
 *
 * Copyright 2009, 2010 Wolfson Microelectronics. PLC.
 */

#अगर_अघोषित __LINUX_SND_WM9090_H
#घोषणा __LINUX_SND_WM9090_H

काष्ठा wm9090_platक्रमm_data अणु
	/* Line inमाला_दो 1 & 2 can optionally be dअगरferential */
	अचिन्हित पूर्णांक lin1_dअगरf:1;
	अचिन्हित पूर्णांक lin2_dअगरf:1;

	/* AGC configuration.  This is पूर्णांकended to protect the speaker
	 * against overdriving and will thereक्रमe depend on the
	 * hardware setup with incorrect runसमय configuration
	 * potentially causing hardware damage.
	 */
	अचिन्हित पूर्णांक agc_ena:1;
	u16 agc[3];
पूर्ण;

#पूर्ण_अगर
