<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 NVIDIA Corporation
 */

#अगर_अघोषित DRM_TEGRA_MIPI_PHY_H
#घोषणा DRM_TEGRA_MIPI_PHY_H

/*
 * D-PHY timing parameters
 *
 * A detailed description of these parameters can be found in the  MIPI
 * Alliance Specअगरication क्रम D-PHY, Section 5.9 "Global Operation Timing
 * Parameters".
 *
 * All parameters are specअगरied in nanoseconds.
 */
काष्ठा mipi_dphy_timing अणु
	अचिन्हित पूर्णांक clkmiss;
	अचिन्हित पूर्णांक clkpost;
	अचिन्हित पूर्णांक clkpre;
	अचिन्हित पूर्णांक clkprepare;
	अचिन्हित पूर्णांक clksettle;
	अचिन्हित पूर्णांक clktermen;
	अचिन्हित पूर्णांक clktrail;
	अचिन्हित पूर्णांक clkzero;
	अचिन्हित पूर्णांक dtermen;
	अचिन्हित पूर्णांक eot;
	अचिन्हित पूर्णांक hsनिकास;
	अचिन्हित पूर्णांक hsprepare;
	अचिन्हित पूर्णांक hszero;
	अचिन्हित पूर्णांक hssettle;
	अचिन्हित पूर्णांक hsskip;
	अचिन्हित पूर्णांक hstrail;
	अचिन्हित पूर्णांक init;
	अचिन्हित पूर्णांक lpx;
	अचिन्हित पूर्णांक taget;
	अचिन्हित पूर्णांक tago;
	अचिन्हित पूर्णांक tasure;
	अचिन्हित पूर्णांक wakeup;
पूर्ण;

पूर्णांक mipi_dphy_timing_get_शेष(काष्ठा mipi_dphy_timing *timing,
				 अचिन्हित दीर्घ period);
पूर्णांक mipi_dphy_timing_validate(काष्ठा mipi_dphy_timing *timing,
			      अचिन्हित दीर्घ period);

#पूर्ण_अगर
