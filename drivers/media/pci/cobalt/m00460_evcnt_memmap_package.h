<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright 2014-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#अगर_अघोषित M00460_EVCNT_MEMMAP_PACKAGE_H
#घोषणा M00460_EVCNT_MEMMAP_PACKAGE_H

/*******************************************************************
 * Register Block
 * M00460_EVCNT_MEMMAP_PACKAGE_VHD_REGMAP
 *******************************************************************/
काष्ठा m00460_evcnt_regmap अणु
	uपूर्णांक32_t control; /* Reg 0x0000, Default=0x0 */
	uपूर्णांक32_t count;   /* Reg 0x0004 */
पूर्ण;

#घोषणा M00460_EVCNT_REG_CONTROL_OFST 0
#घोषणा M00460_EVCNT_REG_COUNT_OFST 4

/*******************************************************************
 * Bit Mask क्रम रेजिस्टर
 * M00460_EVCNT_MEMMAP_PACKAGE_VHD_BITMAP
 *******************************************************************/
/* control [1:0] */
#घोषणा M00460_CONTROL_BITMAP_ENABLE_OFST (0)
#घोषणा M00460_CONTROL_BITMAP_ENABLE_MSK  (0x1 << M00460_CONTROL_BITMAP_ENABLE_OFST)
#घोषणा M00460_CONTROL_BITMAP_CLEAR_OFST  (1)
#घोषणा M00460_CONTROL_BITMAP_CLEAR_MSK   (0x1 << M00460_CONTROL_BITMAP_CLEAR_OFST)

#पूर्ण_अगर /*M00460_EVCNT_MEMMAP_PACKAGE_H*/
