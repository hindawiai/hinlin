<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DRBD_STATE_CHANGE_H
#घोषणा DRBD_STATE_CHANGE_H

काष्ठा drbd_resource_state_change अणु
	काष्ठा drbd_resource *resource;
	क्रमागत drbd_role role[2];
	bool susp[2];
	bool susp_nod[2];
	bool susp_fen[2];
पूर्ण;

काष्ठा drbd_device_state_change अणु
	काष्ठा drbd_device *device;
	क्रमागत drbd_disk_state disk_state[2];
पूर्ण;

काष्ठा drbd_connection_state_change अणु
	काष्ठा drbd_connection *connection;
	क्रमागत drbd_conns cstate[2];  /* drbd9: क्रमागत drbd_conn_state */
	क्रमागत drbd_role peer_role[2];
पूर्ण;

काष्ठा drbd_peer_device_state_change अणु
	काष्ठा drbd_peer_device *peer_device;
	क्रमागत drbd_disk_state disk_state[2];
	क्रमागत drbd_conns repl_state[2];  /* drbd9: क्रमागत drbd_repl_state */
	bool resync_susp_user[2];
	bool resync_susp_peer[2];
	bool resync_susp_dependency[2];
पूर्ण;

काष्ठा drbd_state_change अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक n_devices;
	अचिन्हित पूर्णांक n_connections;
	काष्ठा drbd_resource_state_change resource[1];
	काष्ठा drbd_device_state_change *devices;
	काष्ठा drbd_connection_state_change *connections;
	काष्ठा drbd_peer_device_state_change *peer_devices;
पूर्ण;

बाह्य काष्ठा drbd_state_change *remember_old_state(काष्ठा drbd_resource *, gfp_t);
बाह्य व्योम copy_old_to_new_state_change(काष्ठा drbd_state_change *);
बाह्य व्योम क्रमget_state_change(काष्ठा drbd_state_change *);

बाह्य व्योम notअगरy_resource_state_change(काष्ठा sk_buff *,
					 अचिन्हित पूर्णांक,
					 काष्ठा drbd_resource_state_change *,
					 क्रमागत drbd_notअगरication_type type);
बाह्य व्योम notअगरy_connection_state_change(काष्ठा sk_buff *,
					   अचिन्हित पूर्णांक,
					   काष्ठा drbd_connection_state_change *,
					   क्रमागत drbd_notअगरication_type type);
बाह्य व्योम notअगरy_device_state_change(काष्ठा sk_buff *,
				       अचिन्हित पूर्णांक,
				       काष्ठा drbd_device_state_change *,
				       क्रमागत drbd_notअगरication_type type);
बाह्य व्योम notअगरy_peer_device_state_change(काष्ठा sk_buff *,
					    अचिन्हित पूर्णांक,
					    काष्ठा drbd_peer_device_state_change *,
					    क्रमागत drbd_notअगरication_type type);

#पूर्ण_अगर  /* DRBD_STATE_CHANGE_H */
