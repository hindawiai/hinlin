<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright Intel Corporation (C) 2014-2016. All Rights Reserved
 *
 * Declarations क्रम Altera Arria10 MAX5 System Resource Chip
 *
 * Adapted from DA9052
 */

#अगर_अघोषित __MFD_ALTERA_A10SR_H
#घोषणा __MFD_ALTERA_A10SR_H

#समावेश <linux/completion.h>
#समावेश <linux/list.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

/* Write रेजिस्टरs are always on even addresses */
#घोषणा  WRITE_REG_MASK              0xFE
/* Odd रेजिस्टरs are always on odd addresses */
#घोषणा  READ_REG_MASK               0x01

#घोषणा ALTR_A10SR_BITS_PER_REGISTER  8
/*
 * To find the correct रेजिस्टर, we भागide the input GPIO by
 * the number of GPIO in each रेजिस्टर. We then need to multiply
 * by 2 because the पढ़ोs are at odd addresses.
 */
#घोषणा ALTR_A10SR_REG_OFFSET(X)     (((X) / ALTR_A10SR_BITS_PER_REGISTER) << 1)
#घोषणा ALTR_A10SR_REG_BIT(X)        ((X) % ALTR_A10SR_BITS_PER_REGISTER)
#घोषणा ALTR_A10SR_REG_BIT_CHG(X, Y) ((X) << ALTR_A10SR_REG_BIT(Y))
#घोषणा ALTR_A10SR_REG_BIT_MASK(X)   (1 << ALTR_A10SR_REG_BIT(X))

/* Arria10 System Controller Register Defines */
#घोषणा ALTR_A10SR_NOP                0x00    /* No Change */
#घोषणा ALTR_A10SR_VERSION_READ       0x00    /* MAX5 Version Read */

#घोषणा ALTR_A10SR_LED_REG            0x02    /* LED - Upper 4 bits */
/* LED रेजिस्टर Bit Definitions */
#घोषणा ALTR_A10SR_LED_VALID_SHIFT        4       /* LED - Upper 4 bits valid */
#घोषणा ALTR_A10SR_OUT_VALID_RANGE_LO     ALTR_A10SR_LED_VALID_SHIFT
#घोषणा ALTR_A10SR_OUT_VALID_RANGE_HI     7

#घोषणा ALTR_A10SR_PBDSW_REG          0x04    /* PB & DIP SW - Input only */
#घोषणा ALTR_A10SR_PBDSW_IRQ_REG      0x06    /* PB & DIP SW Flag Clear */
/* Pushbutton & DIP Switch Bit Definitions */
#घोषणा ALTR_A10SR_IN_VALID_RANGE_LO      8
#घोषणा ALTR_A10SR_IN_VALID_RANGE_HI      15

#घोषणा ALTR_A10SR_PWR_GOOD1_REG      0x08    /* Power Good1 Read */
#घोषणा ALTR_A10SR_PWR_GOOD2_REG      0x0A    /* Power Good2 Read */
#घोषणा ALTR_A10SR_PWR_GOOD3_REG      0x0C    /* Power Good3 Read */
#घोषणा ALTR_A10SR_FMCAB_REG          0x0E    /* FMCA/B & PCIe Pwr Enable */
#घोषणा ALTR_A10SR_HPS_RST_REG        0x10    /* HPS Reset */
#घोषणा ALTR_A10SR_USB_QSPI_REG       0x12    /* USB, BQSPI, खाता Reset */
#घोषणा ALTR_A10SR_SFPA_REG           0x14    /* SFPA Control Reg */
#घोषणा ALTR_A10SR_SFPB_REG           0x16    /* SFPB Control Reg */
#घोषणा ALTR_A10SR_I2C_M_REG          0x18    /* I2C Master Select */
#घोषणा ALTR_A10SR_WARM_RST_REG       0x1A    /* HPS Warm Reset */
#घोषणा ALTR_A10SR_WR_KEY_REG         0x1C    /* HPS Warm Reset Key */
#घोषणा ALTR_A10SR_PMBUS_REG          0x1E    /* HPS PM Bus */

/**
 * काष्ठा altr_a10sr - Altera Max5 MFD device निजी data काष्ठाure
 * @dev:  : this device
 * @regmap: the regmap asचिन्हित to the parent device.
 */
काष्ठा altr_a10sr अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
पूर्ण;

#पूर्ण_अगर /* __MFD_ALTERA_A10SR_H */
