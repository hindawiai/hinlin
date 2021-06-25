<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010-2013 Bluecherry, LLC <https://www.bluecherrydvr.com>
 *
 * Original author:
 * Ben Collins <bcollins@ubuntu.com>
 *
 * Additional work by:
 * John Brooks <john.brooks@bluecherry.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>

#समावेश "solo6x10.h"

/* Control */
#घोषणा EE_SHIFT_CLK	0x04
#घोषणा EE_CS		0x08
#घोषणा EE_DATA_WRITE	0x02
#घोषणा EE_DATA_READ	0x01
#घोषणा EE_ENB		(0x80 | EE_CS)

#घोषणा eeprom_delay()	udelay(100)
#अगर 0
#घोषणा eeprom_delay()	solo_reg_पढ़ो(solo_dev, SOLO_EEPROM_CTRL)
#घोषणा eeprom_delay()	(अणु				\
	पूर्णांक i, ret;					\
	udelay(100);					\
	क्रम (i = ret = 0; i < 1000 && !ret; i++)	\
		ret = solo_eeprom_reg_पढ़ो(solo_dev);	\
पूर्ण)
#पूर्ण_अगर
#घोषणा ADDR_LEN	6

/* Commands */
#घोषणा EE_EWEN_CMD	4
#घोषणा EE_EWDS_CMD	4
#घोषणा EE_WRITE_CMD	5
#घोषणा EE_READ_CMD	6
#घोषणा EE_ERASE_CMD	7

अटल अचिन्हित पूर्णांक solo_eeprom_reg_पढ़ो(काष्ठा solo_dev *solo_dev)
अणु
	वापस solo_reg_पढ़ो(solo_dev, SOLO_EEPROM_CTRL) & EE_DATA_READ;
पूर्ण

अटल व्योम solo_eeprom_reg_ग_लिखो(काष्ठा solo_dev *solo_dev, u32 data)
अणु
	solo_reg_ग_लिखो(solo_dev, SOLO_EEPROM_CTRL, data);
	eeprom_delay();
पूर्ण

अटल व्योम solo_eeprom_cmd(काष्ठा solo_dev *solo_dev, पूर्णांक cmd)
अणु
	पूर्णांक i;

	solo_eeprom_reg_ग_लिखो(solo_dev, SOLO_EEPROM_ACCESS_EN);
	solo_eeprom_reg_ग_लिखो(solo_dev, SOLO_EEPROM_ENABLE);

	क्रम (i = 4 + ADDR_LEN; i >= 0; i--) अणु
		पूर्णांक dataval = (cmd & (1 << i)) ? EE_DATA_WRITE : 0;

		solo_eeprom_reg_ग_लिखो(solo_dev, SOLO_EEPROM_ENABLE | dataval);
		solo_eeprom_reg_ग_लिखो(solo_dev, SOLO_EEPROM_ENABLE |
				      EE_SHIFT_CLK | dataval);
	पूर्ण

	solo_eeprom_reg_ग_लिखो(solo_dev, SOLO_EEPROM_ENABLE);
पूर्ण

अचिन्हित पूर्णांक solo_eeprom_ewen(काष्ठा solo_dev *solo_dev, पूर्णांक w_en)
अणु
	पूर्णांक ewen_cmd = (w_en ? 0x3f : 0) | (EE_EWEN_CMD << ADDR_LEN);
	अचिन्हित पूर्णांक retval = 0;
	पूर्णांक i;

	solo_eeprom_cmd(solo_dev, ewen_cmd);

	क्रम (i = 0; i < 16; i++) अणु
		solo_eeprom_reg_ग_लिखो(solo_dev, SOLO_EEPROM_ENABLE |
				      EE_SHIFT_CLK);
		retval = (retval << 1) | solo_eeprom_reg_पढ़ो(solo_dev);
		solo_eeprom_reg_ग_लिखो(solo_dev, SOLO_EEPROM_ENABLE);
		retval = (retval << 1) | solo_eeprom_reg_पढ़ो(solo_dev);
	पूर्ण

	solo_eeprom_reg_ग_लिखो(solo_dev, ~EE_CS);
	retval = (retval << 1) | solo_eeprom_reg_पढ़ो(solo_dev);

	वापस retval;
पूर्ण

__be16 solo_eeprom_पढ़ो(काष्ठा solo_dev *solo_dev, पूर्णांक loc)
अणु
	पूर्णांक पढ़ो_cmd = loc | (EE_READ_CMD << ADDR_LEN);
	u16 retval = 0;
	पूर्णांक i;

	solo_eeprom_cmd(solo_dev, पढ़ो_cmd);

	क्रम (i = 0; i < 16; i++) अणु
		solo_eeprom_reg_ग_लिखो(solo_dev, SOLO_EEPROM_ENABLE |
				      EE_SHIFT_CLK);
		retval = (retval << 1) | solo_eeprom_reg_पढ़ो(solo_dev);
		solo_eeprom_reg_ग_लिखो(solo_dev, SOLO_EEPROM_ENABLE);
	पूर्ण

	solo_eeprom_reg_ग_लिखो(solo_dev, ~EE_CS);

	वापस (__क्रमce __be16)retval;
पूर्ण

पूर्णांक solo_eeprom_ग_लिखो(काष्ठा solo_dev *solo_dev, पूर्णांक loc,
		      __be16 data)
अणु
	पूर्णांक ग_लिखो_cmd = loc | (EE_WRITE_CMD << ADDR_LEN);
	अचिन्हित पूर्णांक retval;
	पूर्णांक i;

	solo_eeprom_cmd(solo_dev, ग_लिखो_cmd);

	क्रम (i = 15; i >= 0; i--) अणु
		अचिन्हित पूर्णांक dataval = ((__क्रमce अचिन्हित)data >> i) & 1;

		solo_eeprom_reg_ग_लिखो(solo_dev, EE_ENB);
		solo_eeprom_reg_ग_लिखो(solo_dev,
				      EE_ENB | (dataval << 1) | EE_SHIFT_CLK);
	पूर्ण

	solo_eeprom_reg_ग_लिखो(solo_dev, EE_ENB);
	solo_eeprom_reg_ग_लिखो(solo_dev, ~EE_CS);
	solo_eeprom_reg_ग_लिखो(solo_dev, EE_ENB);

	क्रम (i = retval = 0; i < 10000 && !retval; i++)
		retval = solo_eeprom_reg_पढ़ो(solo_dev);

	solo_eeprom_reg_ग_लिखो(solo_dev, ~EE_CS);

	वापस !retval;
पूर्ण
