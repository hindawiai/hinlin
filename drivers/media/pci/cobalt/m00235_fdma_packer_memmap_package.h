<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright 2014-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#अगर_अघोषित M00235_FDMA_PACKER_MEMMAP_PACKAGE_H
#घोषणा M00235_FDMA_PACKER_MEMMAP_PACKAGE_H

/*******************************************************************
 * Register Block
 * M00235_FDMA_PACKER_MEMMAP_PACKAGE_VHD_REGMAP
 *******************************************************************/
काष्ठा m00235_fdma_packer_regmap अणु
	uपूर्णांक32_t control; /* Reg 0x0000, Default=0x0 */
पूर्ण;

#घोषणा M00235_FDMA_PACKER_REG_CONTROL_OFST 0

/*******************************************************************
 * Bit Mask क्रम रेजिस्टर
 * M00235_FDMA_PACKER_MEMMAP_PACKAGE_VHD_BITMAP
 *******************************************************************/
/* control [3:0] */
#घोषणा M00235_CONTROL_BITMAP_ENABLE_OFST        (0)
#घोषणा M00235_CONTROL_BITMAP_ENABLE_MSK         (0x1 << M00235_CONTROL_BITMAP_ENABLE_OFST)
#घोषणा M00235_CONTROL_BITMAP_PACK_FORMAT_OFST   (1)
#घोषणा M00235_CONTROL_BITMAP_PACK_FORMAT_MSK    (0x3 << M00235_CONTROL_BITMAP_PACK_FORMAT_OFST)
#घोषणा M00235_CONTROL_BITMAP_ENDIAN_FORMAT_OFST (3)
#घोषणा M00235_CONTROL_BITMAP_ENDIAN_FORMAT_MSK  (0x1 << M00235_CONTROL_BITMAP_ENDIAN_FORMAT_OFST)

#पूर्ण_अगर /*M00235_FDMA_PACKER_MEMMAP_PACKAGE_H*/
