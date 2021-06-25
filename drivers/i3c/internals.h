<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Cadence Design Systems Inc.
 *
 * Author: Boris Brezillon <boris.brezillon@bootlin.com>
 */

#अगर_अघोषित I3C_INTERNALS_H
#घोषणा I3C_INTERNALS_H

#समावेश <linux/i3c/master.h>

बाह्य काष्ठा bus_type i3c_bus_type;

व्योम i3c_bus_normaluse_lock(काष्ठा i3c_bus *bus);
व्योम i3c_bus_normaluse_unlock(काष्ठा i3c_bus *bus);

पूर्णांक i3c_dev_करो_priv_xfers_locked(काष्ठा i3c_dev_desc *dev,
				 काष्ठा i3c_priv_xfer *xfers,
				 पूर्णांक nxfers);
पूर्णांक i3c_dev_disable_ibi_locked(काष्ठा i3c_dev_desc *dev);
पूर्णांक i3c_dev_enable_ibi_locked(काष्ठा i3c_dev_desc *dev);
पूर्णांक i3c_dev_request_ibi_locked(काष्ठा i3c_dev_desc *dev,
			       स्थिर काष्ठा i3c_ibi_setup *req);
व्योम i3c_dev_मुक्त_ibi_locked(काष्ठा i3c_dev_desc *dev);
#पूर्ण_अगर /* I3C_INTERNAL_H */
