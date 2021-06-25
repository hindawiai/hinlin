<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (C) 2010 Google, Inc.
 * Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 * Author: Dima Zavin <dima@android.com>
 */

#अगर_अघोषित _LINUX_SSBI_H
#घोषणा _LINUX_SSBI_H

#समावेश <linux/types.h>

पूर्णांक ssbi_ग_लिखो(काष्ठा device *dev, u16 addr, स्थिर u8 *buf, पूर्णांक len);
पूर्णांक ssbi_पढ़ो(काष्ठा device *dev, u16 addr, u8 *buf, पूर्णांक len);

अटल अंतरभूत पूर्णांक
ssbi_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;
	u8 v;

	ret = ssbi_पढ़ो(context, reg, &v, 1);
	अगर (!ret)
		*val = v;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
ssbi_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	u8 v = val;
	वापस ssbi_ग_लिखो(context, reg, &v, 1);
पूर्ण

#पूर्ण_अगर
