<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ADAU7118_H
#घोषणा _LINUX_ADAU7118_H

काष्ठा regmap;
काष्ठा device;

/* रेजिस्टर map */
#घोषणा ADAU7118_REG_VENDOR_ID		0x00
#घोषणा ADAU7118_REG_DEVICE_ID1		0x01
#घोषणा ADAU7118_REG_DEVICE_ID2		0x02
#घोषणा ADAU7118_REG_REVISION_ID	0x03
#घोषणा ADAU7118_REG_ENABLES		0x04
#घोषणा ADAU7118_REG_DEC_RATIO_CLK_MAP	0x05
#घोषणा ADAU7118_REG_HPF_CONTROL	0x06
#घोषणा ADAU7118_REG_SPT_CTRL1		0x07
#घोषणा ADAU7118_REG_SPT_CTRL2		0x08
#घोषणा ADAU7118_REG_SPT_CX(num)	(0x09 + (num))
#घोषणा ADAU7118_REG_DRIVE_STRENGTH	0x11
#घोषणा ADAU7118_REG_RESET		0x12

पूर्णांक adau7118_probe(काष्ठा device *dev, काष्ठा regmap *map, bool hw_mode);

#पूर्ण_अगर
