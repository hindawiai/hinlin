<शैली गुरु>
/*
 * Marvell EBU SoC ID and revision definitions.
 *
 * Copyright (C) 2014 Marvell Semiconductor
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __LINUX_MVEBU_SOC_ID_H
#घोषणा __LINUX_MVEBU_SOC_ID_H

/* Armada XP ID */
#घोषणा MV78230_DEV_ID	    0x7823
#घोषणा MV78260_DEV_ID	    0x7826
#घोषणा MV78460_DEV_ID	    0x7846

/* Armada XP Revision */
#घोषणा MV78XX0_A0_REV	    0x1
#घोषणा MV78XX0_B0_REV	    0x2

/* Amada 370 ID */
#घोषणा ARMADA_370_DEV_ID   0x6710

/* Amada 370 Revision */
#घोषणा ARMADA_370_A1_REV   0x1

/* Armada 375 ID */
#घोषणा ARMADA_375_DEV_ID   0x6720

/* Armada 375 */
#घोषणा ARMADA_375_Z1_REV   0x0
#घोषणा ARMADA_375_A0_REV   0x3

/* Armada 38x ID */
#घोषणा ARMADA_380_DEV_ID   0x6810
#घोषणा ARMADA_385_DEV_ID   0x6820
#घोषणा ARMADA_388_DEV_ID   0x6828

/* Armada 38x Revision */
#घोषणा ARMADA_38x_Z1_REV   0x0
#घोषणा ARMADA_38x_A0_REV   0x4

#अगर_घोषित CONFIG_ARCH_MVEBU
पूर्णांक mvebu_get_soc_id(u32 *dev, u32 *rev);
#अन्यथा
अटल अंतरभूत पूर्णांक mvebu_get_soc_id(u32 *dev, u32 *rev)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_MVEBU_SOC_ID_H */
