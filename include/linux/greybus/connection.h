<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus connections
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#अगर_अघोषित __CONNECTION_H
#घोषणा __CONNECTION_H

#समावेश <linux/bits.h>
#समावेश <linux/list.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/kref.h>
#समावेश <linux/workqueue.h>

#घोषणा GB_CONNECTION_FLAG_CSD		BIT(0)
#घोषणा GB_CONNECTION_FLAG_NO_FLOWCTRL	BIT(1)
#घोषणा GB_CONNECTION_FLAG_OFFLOADED	BIT(2)
#घोषणा GB_CONNECTION_FLAG_CDSI1	BIT(3)
#घोषणा GB_CONNECTION_FLAG_CONTROL	BIT(4)
#घोषणा GB_CONNECTION_FLAG_HIGH_PRIO	BIT(5)

#घोषणा GB_CONNECTION_FLAG_CORE_MASK	GB_CONNECTION_FLAG_CONTROL

क्रमागत gb_connection_state अणु
	GB_CONNECTION_STATE_DISABLED		= 0,
	GB_CONNECTION_STATE_ENABLED_TX		= 1,
	GB_CONNECTION_STATE_ENABLED		= 2,
	GB_CONNECTION_STATE_DISCONNECTING	= 3,
पूर्ण;

काष्ठा gb_operation;

प्रकार पूर्णांक (*gb_request_handler_t)(काष्ठा gb_operation *);

काष्ठा gb_connection अणु
	काष्ठा gb_host_device		*hd;
	काष्ठा gb_पूर्णांकerface		*पूर्णांकf;
	काष्ठा gb_bundle		*bundle;
	काष्ठा kref			kref;
	u16				hd_cport_id;
	u16				पूर्णांकf_cport_id;

	काष्ठा list_head		hd_links;
	काष्ठा list_head		bundle_links;

	gb_request_handler_t		handler;
	अचिन्हित दीर्घ			flags;

	काष्ठा mutex			mutex;
	spinlock_t			lock;
	क्रमागत gb_connection_state	state;
	काष्ठा list_head		operations;

	अक्षर				name[16];
	काष्ठा workqueue_काष्ठा		*wq;

	atomic_t			op_cycle;

	व्योम				*निजी;

	bool				mode_चयन;
पूर्ण;

काष्ठा gb_connection *gb_connection_create_अटल(काष्ठा gb_host_device *hd,
				u16 hd_cport_id, gb_request_handler_t handler);
काष्ठा gb_connection *gb_connection_create_control(काष्ठा gb_पूर्णांकerface *पूर्णांकf);
काष्ठा gb_connection *gb_connection_create(काष्ठा gb_bundle *bundle,
				u16 cport_id, gb_request_handler_t handler);
काष्ठा gb_connection *gb_connection_create_flags(काष्ठा gb_bundle *bundle,
				u16 cport_id, gb_request_handler_t handler,
				अचिन्हित दीर्घ flags);
काष्ठा gb_connection *gb_connection_create_offloaded(काष्ठा gb_bundle *bundle,
				u16 cport_id, अचिन्हित दीर्घ flags);
व्योम gb_connection_destroy(काष्ठा gb_connection *connection);

अटल अंतरभूत bool gb_connection_is_अटल(काष्ठा gb_connection *connection)
अणु
	वापस !connection->पूर्णांकf;
पूर्ण

पूर्णांक gb_connection_enable(काष्ठा gb_connection *connection);
पूर्णांक gb_connection_enable_tx(काष्ठा gb_connection *connection);
व्योम gb_connection_disable_rx(काष्ठा gb_connection *connection);
व्योम gb_connection_disable(काष्ठा gb_connection *connection);
व्योम gb_connection_disable_क्रमced(काष्ठा gb_connection *connection);

व्योम gb_connection_mode_चयन_prepare(काष्ठा gb_connection *connection);
व्योम gb_connection_mode_चयन_complete(काष्ठा gb_connection *connection);

व्योम greybus_data_rcvd(काष्ठा gb_host_device *hd, u16 cport_id,
		       u8 *data, माप_प्रकार length);

व्योम gb_connection_latency_tag_enable(काष्ठा gb_connection *connection);
व्योम gb_connection_latency_tag_disable(काष्ठा gb_connection *connection);

अटल अंतरभूत bool gb_connection_e2efc_enabled(काष्ठा gb_connection *connection)
अणु
	वापस !(connection->flags & GB_CONNECTION_FLAG_CSD);
पूर्ण

अटल अंतरभूत bool
gb_connection_flow_control_disabled(काष्ठा gb_connection *connection)
अणु
	वापस connection->flags & GB_CONNECTION_FLAG_NO_FLOWCTRL;
पूर्ण

अटल अंतरभूत bool gb_connection_is_offloaded(काष्ठा gb_connection *connection)
अणु
	वापस connection->flags & GB_CONNECTION_FLAG_OFFLOADED;
पूर्ण

अटल अंतरभूत bool gb_connection_is_control(काष्ठा gb_connection *connection)
अणु
	वापस connection->flags & GB_CONNECTION_FLAG_CONTROL;
पूर्ण

अटल अंतरभूत व्योम *gb_connection_get_data(काष्ठा gb_connection *connection)
अणु
	वापस connection->निजी;
पूर्ण

अटल अंतरभूत व्योम gb_connection_set_data(काष्ठा gb_connection *connection,
					  व्योम *data)
अणु
	connection->निजी = data;
पूर्ण

#पूर्ण_अगर /* __CONNECTION_H */
