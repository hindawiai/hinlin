<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 Texas Instruments, Inc.
 */

#अगर_अघोषित __OMAPDSS_PDATA_H
#घोषणा __OMAPDSS_PDATA_H

क्रमागत omapdss_version अणु
	OMAPDSS_VER_UNKNOWN = 0,
	OMAPDSS_VER_OMAP24xx,
	OMAPDSS_VER_OMAP34xx_ES1,	/* OMAP3430 ES1.0, 2.0 */
	OMAPDSS_VER_OMAP34xx_ES3,	/* OMAP3430 ES3.0+ */
	OMAPDSS_VER_OMAP3630,
	OMAPDSS_VER_AM35xx,
	OMAPDSS_VER_OMAP4430_ES1,	/* OMAP4430 ES1.0 */
	OMAPDSS_VER_OMAP4430_ES2,	/* OMAP4430 ES2.0, 2.1, 2.2 */
	OMAPDSS_VER_OMAP4,		/* All other OMAP4s */
	OMAPDSS_VER_OMAP5,
	OMAPDSS_VER_AM43xx,
	OMAPDSS_VER_DRA7xx,
पूर्ण;

/* Board specअगरic data */
काष्ठा omap_dss_board_info अणु
	पूर्णांक (*dsi_enable_pads)(पूर्णांक dsi_id, अचिन्हित पूर्णांक lane_mask);
	व्योम (*dsi_disable_pads)(पूर्णांक dsi_id, अचिन्हित पूर्णांक lane_mask);
	पूर्णांक (*set_min_bus_tput)(काष्ठा device *dev, अचिन्हित दीर्घ r);
	क्रमागत omapdss_version version;
पूर्ण;

#पूर्ण_अगर /* __OMAPDSS_PDATA_H */
