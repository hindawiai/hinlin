<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम MT9M032 CMOS Image Sensor from Micron
 *
 * Copyright (C) 2010-2011 Lund Engineering
 * Contact: Gil Lund <gwlund@lundeng.com>
 * Author: Martin Hostettler <martin@neutronstar.dyndns.org>
 */

#अगर_अघोषित MT9M032_H
#घोषणा MT9M032_H

#घोषणा MT9M032_NAME		"mt9m032"
#घोषणा MT9M032_I2C_ADDR	(0xb8 >> 1)

काष्ठा mt9m032_platक्रमm_data अणु
	u32 ext_घड़ी;
	u32 pix_घड़ी;
	bool invert_pixघड़ी;

पूर्ण;
#पूर्ण_अगर /* MT9M032_H */
