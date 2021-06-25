<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2019 Microchip Technology Inc. and its subsidiaries
 *
 * Author: Eugen Hristev <eugen.hristev@microchip.com>
 */

#अगर_अघोषित __LINUX_ATMEL_ISC_MEDIA_H__
#घोषणा __LINUX_ATMEL_ISC_MEDIA_H__

/*
 * There are 8 controls available:
 * 4 gain controls, sliders, क्रम each of the BAYER components: R, B, GR, GB.
 * These gains are multipliers क्रम each component, in क्रमmat अचिन्हित 0:4:9 with
 * a शेष value of 512 (1.0 multiplier).
 * 4 offset controls, sliders, क्रम each of the BAYER components: R, B, GR, GB.
 * These offsets are added/substracted from each component, in क्रमmat चिन्हित
 * 1:12:0 with a शेष value of 0 (+/- 0)
 *
 * To expose this to userspace, added 8 custom controls, in an स्वतः cluster.
 *
 * To summarize the functionality:
 * The स्वतः cluster चयन is the स्वतः white balance control, and it works
 * like this:
 * AWB == 1: स्वतःwhitebalance is on, the करो_white_balance button is inactive,
 * the gains/offsets are inactive, but अस्थिर and पढ़ोable.
 * Thus, the results of the whitebalance algorithm are available to userspace to
 * पढ़ो at any समय.
 * AWB == 0: स्वतःwhitebalance is off, cluster is in manual mode, user can
 * configure the gain/offsets directly.
 * More than that, अगर the करो_white_balance button is
 * pressed, the driver will perक्रमm one-समय-adjusपंचांगent, (preferably with color
 * checker card) and the userspace can पढ़ो again the new values.
 *
 * With this feature, the userspace can save the coefficients and reinstall them
 * क्रम example after reboot or reprobing the driver.
 */

क्रमागत aपंचांगel_isc_ctrl_id अणु
	/* Red component gain control */
	ISC_CID_R_GAIN = (V4L2_CID_USER_ATMEL_ISC_BASE + 0),
	/* Blue component gain control */
	ISC_CID_B_GAIN,
	/* Green Red component gain control */
	ISC_CID_GR_GAIN,
	/* Green Blue gain control */
	ISC_CID_GB_GAIN,
	/* Red component offset control */
	ISC_CID_R_OFFSET,
	/* Blue component offset control */
	ISC_CID_B_OFFSET,
	/* Green Red component offset control */
	ISC_CID_GR_OFFSET,
	/* Green Blue component offset control */
	ISC_CID_GB_OFFSET,
पूर्ण;

#पूर्ण_अगर
