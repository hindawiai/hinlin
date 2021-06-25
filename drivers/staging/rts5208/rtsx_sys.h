<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG (wei_wang@realsil.com.cn)
 *   Micky Ching (micky_ching@realsil.com.cn)
 */

#अगर_अघोषित __RTSX_SYS_H
#घोषणा __RTSX_SYS_H

#समावेश "rtsx.h"
#समावेश "rtsx_chip.h"
#समावेश "rtsx_card.h"

अटल अंतरभूत व्योम rtsx_exclusive_enter_ss(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा rtsx_dev *dev = chip->rtsx;

	spin_lock(&dev->reg_lock);
	rtsx_enter_ss(chip);
	spin_unlock(&dev->reg_lock);
पूर्ण

अटल अंतरभूत व्योम rtsx_reset_detected_cards(काष्ठा rtsx_chip *chip, पूर्णांक flag)
अणु
	rtsx_reset_cards(chip);
पूर्ण

#घोषणा RTSX_MSG_IN_INT(x)

#पूर्ण_अगर  /* __RTSX_SYS_H */

