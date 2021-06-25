<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ddbridge-पन.स: Digital Devices bridge I/O अंतरभूत functions
 *
 * Copyright (C) 2010-2017 Digital Devices GmbH
 *                         Ralph Metzler <rjkm@metzlerbros.de>
 *                         Marcus Metzler <mocm@metzlerbros.de>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 only, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित __DDBRIDGE_IO_H__
#घोषणा __DDBRIDGE_IO_H__

#समावेश <linux/पन.स>

#समावेश "ddbridge.h"

/******************************************************************************/

अटल अंतरभूत u32 ddblपढ़ोl(काष्ठा ddb_link *link, u32 adr)
अणु
	वापस पढ़ोl(link->dev->regs + adr);
पूर्ण

अटल अंतरभूत व्योम ddblग_लिखोl(काष्ठा ddb_link *link, u32 val, u32 adr)
अणु
	ग_लिखोl(val, link->dev->regs + adr);
पूर्ण

अटल अंतरभूत u32 ddbपढ़ोl(काष्ठा ddb *dev, u32 adr)
अणु
	वापस पढ़ोl(dev->regs + adr);
पूर्ण

अटल अंतरभूत व्योम ddbग_लिखोl(काष्ठा ddb *dev, u32 val, u32 adr)
अणु
	ग_लिखोl(val, dev->regs + adr);
पूर्ण

अटल अंतरभूत व्योम ddbcpyto(काष्ठा ddb *dev, u32 adr, व्योम *src, दीर्घ count)
अणु
	स_नकल_toio(dev->regs + adr, src, count);
पूर्ण

अटल अंतरभूत व्योम ddbcpyfrom(काष्ठा ddb *dev, व्योम *dst, u32 adr, दीर्घ count)
अणु
	स_नकल_fromio(dst, dev->regs + adr, count);
पूर्ण

अटल अंतरभूत u32 safe_ddbपढ़ोl(काष्ठा ddb *dev, u32 adr)
अणु
	u32 val = ddbपढ़ोl(dev, adr);

	/* (ddb)पढ़ोl वापसs (uपूर्णांक)-1 (all bits set) on failure, catch that */
	अगर (val == ~0) अणु
		dev_err(&dev->pdev->dev, "ddbreadl failure, adr=%08x\n", adr);
		वापस 0;
	पूर्ण

	वापस val;
पूर्ण

#पूर्ण_अगर /* __DDBRIDGE_IO_H__ */
