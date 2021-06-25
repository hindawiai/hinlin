<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ssip_slave.h
 *
 * SSIP slave support header file
 *
 * Copyright (C) 2010 Nokia Corporation. All rights reserved.
 *
 * Contact: Carlos Chinea <carlos.chinea@nokia.com>
 */

#अगर_अघोषित __LINUX_SSIP_SLAVE_H__
#घोषणा __LINUX_SSIP_SLAVE_H__

#समावेश <linux/hsi/hsi.h>

अटल अंतरभूत व्योम ssip_slave_put_master(काष्ठा hsi_client *master)
अणु
पूर्ण

काष्ठा hsi_client *ssip_slave_get_master(काष्ठा hsi_client *slave);
पूर्णांक ssip_slave_start_tx(काष्ठा hsi_client *master);
पूर्णांक ssip_slave_stop_tx(काष्ठा hsi_client *master);
व्योम ssip_reset_event(काष्ठा hsi_client *master);

पूर्णांक ssip_slave_running(काष्ठा hsi_client *master);

#पूर्ण_अगर /* __LINUX_SSIP_SLAVE_H__ */

