<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2019-2020 Marvell International Ltd. All rights reserved. */

#अगर_अघोषित _PRESTERA_DEVLINK_H_
#घोषणा _PRESTERA_DEVLINK_H_

#समावेश "prestera.h"

काष्ठा prestera_चयन *prestera_devlink_alloc(व्योम);
व्योम prestera_devlink_मुक्त(काष्ठा prestera_चयन *sw);

पूर्णांक prestera_devlink_रेजिस्टर(काष्ठा prestera_चयन *sw);
व्योम prestera_devlink_unरेजिस्टर(काष्ठा prestera_चयन *sw);

पूर्णांक prestera_devlink_port_रेजिस्टर(काष्ठा prestera_port *port);
व्योम prestera_devlink_port_unरेजिस्टर(काष्ठा prestera_port *port);

व्योम prestera_devlink_port_set(काष्ठा prestera_port *port);
व्योम prestera_devlink_port_clear(काष्ठा prestera_port *port);

काष्ठा devlink_port *prestera_devlink_get_port(काष्ठा net_device *dev);

#पूर्ण_अगर /* _PRESTERA_DEVLINK_H_ */
