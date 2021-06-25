<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __IA_CSS_PRBS_H
#घोषणा __IA_CSS_PRBS_H

/* @file
 * This file contains support क्रम Pseuकरो Ranकरोm Bit Sequence (PRBS) inमाला_दो
 */

/* Enumerate the PRBS IDs.
 */
क्रमागत ia_css_prbs_id अणु
	IA_CSS_PRBS_ID0,
	IA_CSS_PRBS_ID1,
	IA_CSS_PRBS_ID2
पूर्ण;

/**
 * Maximum number of PRBS IDs.
 *
 * Make sure the value of this define माला_लो changed to reflect the correct
 * number of ia_css_prbs_id क्रमागत अगर you add/delete an item in the क्रमागत.
 */
#घोषणा N_CSS_PRBS_IDS (IA_CSS_PRBS_ID2 + 1)

/**
 * PRBS configuration काष्ठाure.
 *
 * Seed the क्रम the Pseuकरो Ranकरोm Bit Sequence.
 *
 * @deprecatedअणुThis पूर्णांकerface is deprecated, it is not portable -> move to input प्रणाली APIपूर्ण
 */
काष्ठा ia_css_prbs_config अणु
	क्रमागत ia_css_prbs_id	id;
	अचिन्हित पूर्णांक		h_blank;	/** horizontal blank */
	अचिन्हित पूर्णांक		v_blank;	/** vertical blank */
	पूर्णांक			seed;	/** अक्रमom seed क्रम the 1st 2-pixel-components/घड़ी */
	पूर्णांक			seed1;	/** अक्रमom seed क्रम the 2nd 2-pixel-components/घड़ी */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_PRBS_H */
