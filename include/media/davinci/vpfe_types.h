<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2008-2009 Texas Instruments Inc
 */
#अगर_अघोषित _VPFE_TYPES_H
#घोषणा _VPFE_TYPES_H

#अगर_घोषित __KERNEL__

क्रमागत vpfe_pin_pol अणु
	VPFE_PINPOL_POSITIVE,
	VPFE_PINPOL_NEGATIVE
पूर्ण;

क्रमागत vpfe_hw_अगर_type अणु
	/* BT656 - 8 bit */
	VPFE_BT656,
	/* BT1120 - 16 bit */
	VPFE_BT1120,
	/* Raw Bayer */
	VPFE_RAW_BAYER,
	/* YCbCr - 8 bit with बाह्यal sync */
	VPFE_YCBCR_SYNC_8,
	/* YCbCr - 16 bit with बाह्यal sync */
	VPFE_YCBCR_SYNC_16,
	/* BT656 - 10 bit */
	VPFE_BT656_10BIT
पूर्ण;

/* पूर्णांकerface description */
काष्ठा vpfe_hw_अगर_param अणु
	क्रमागत vpfe_hw_अगर_type अगर_type;
	क्रमागत vpfe_pin_pol hdpol;
	क्रमागत vpfe_pin_pol vdpol;
पूर्ण;

#पूर्ण_अगर
#पूर्ण_अगर
