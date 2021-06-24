<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   drbd_state.c

   This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

   Copyright (C) 2001-2008, LINBIT Inक्रमmation Technologies GmbH.
   Copyright (C) 1999-2008, Philipp Reisner <philipp.reisner@linbit.com>.
   Copyright (C) 2002-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.

   Thanks to Carter Burden, Bart Grantham and Gennadiy Nerubayev
   from Logicworks, Inc. क्रम making SDP replication support possible.

 */

#समावेश <linux/drbd_सीमा.स>
#समावेश "drbd_int.h"
#समावेश "drbd_protocol.h"
#समावेश "drbd_req.h"
#समावेश "drbd_state_change.h"

काष्ठा after_state_chg_work अणु
	काष्ठा drbd_work w;
	काष्ठा drbd_device *device;
	जोड़ drbd_state os;
	जोड़ drbd_state ns;
	क्रमागत chg_state_flags flags;
	काष्ठा completion *करोne;
	काष्ठा drbd_state_change *state_change;
पूर्ण;

क्रमागत sanitize_state_warnings अणु
	NO_WARNING,
	ABORTED_ONLINE_VERIFY,
	ABORTED_RESYNC,
	CONNECTION_LOST_NEGOTIATING,
	IMPLICITLY_UPGRADED_DISK,
	IMPLICITLY_UPGRADED_PDSK,
पूर्ण;

अटल व्योम count_objects(काष्ठा drbd_resource *resource,
			  अचिन्हित पूर्णांक *n_devices,
			  अचिन्हित पूर्णांक *n_connections)
अणु
	काष्ठा drbd_device *device;
	काष्ठा drbd_connection *connection;
	पूर्णांक vnr;

	*n_devices = 0;
	*n_connections = 0;

	idr_क्रम_each_entry(&resource->devices, device, vnr)
		(*n_devices)++;
	क्रम_each_connection(connection, resource)
		(*n_connections)++;
पूर्ण

अटल काष्ठा drbd_state_change *alloc_state_change(अचिन्हित पूर्णांक n_devices, अचिन्हित पूर्णांक n_connections, gfp_t gfp)
अणु
	काष्ठा drbd_state_change *state_change;
	अचिन्हित पूर्णांक size, n;

	size = माप(काष्ठा drbd_state_change) +
	       n_devices * माप(काष्ठा drbd_device_state_change) +
	       n_connections * माप(काष्ठा drbd_connection_state_change) +
	       n_devices * n_connections * माप(काष्ठा drbd_peer_device_state_change);
	state_change = kदो_स्मृति(size, gfp);
	अगर (!state_change)
		वापस शून्य;
	state_change->n_devices = n_devices;
	state_change->n_connections = n_connections;
	state_change->devices = (व्योम *)(state_change + 1);
	state_change->connections = (व्योम *)&state_change->devices[n_devices];
	state_change->peer_devices = (व्योम *)&state_change->connections[n_connections];
	state_change->resource->resource = शून्य;
	क्रम (n = 0; n < n_devices; n++)
		state_change->devices[n].device = शून्य;
	क्रम (n = 0; n < n_connections; n++)
		state_change->connections[n].connection = शून्य;
	वापस state_change;
पूर्ण

काष्ठा drbd_state_change *remember_old_state(काष्ठा drbd_resource *resource, gfp_t gfp)
अणु
	काष्ठा drbd_state_change *state_change;
	काष्ठा drbd_device *device;
	अचिन्हित पूर्णांक n_devices;
	काष्ठा drbd_connection *connection;
	अचिन्हित पूर्णांक n_connections;
	पूर्णांक vnr;

	काष्ठा drbd_device_state_change *device_state_change;
	काष्ठा drbd_peer_device_state_change *peer_device_state_change;
	काष्ठा drbd_connection_state_change *connection_state_change;

	/* Caller holds req_lock spinlock.
	 * No state, no device IDR, no connections lists can change. */
	count_objects(resource, &n_devices, &n_connections);
	state_change = alloc_state_change(n_devices, n_connections, gfp);
	अगर (!state_change)
		वापस शून्य;

	kref_get(&resource->kref);
	state_change->resource->resource = resource;
	state_change->resource->role[OLD] =
		conn_highest_role(first_connection(resource));
	state_change->resource->susp[OLD] = resource->susp;
	state_change->resource->susp_nod[OLD] = resource->susp_nod;
	state_change->resource->susp_fen[OLD] = resource->susp_fen;

	connection_state_change = state_change->connections;
	क्रम_each_connection(connection, resource) अणु
		kref_get(&connection->kref);
		connection_state_change->connection = connection;
		connection_state_change->cstate[OLD] =
			connection->cstate;
		connection_state_change->peer_role[OLD] =
			conn_highest_peer(connection);
		connection_state_change++;
	पूर्ण

	device_state_change = state_change->devices;
	peer_device_state_change = state_change->peer_devices;
	idr_क्रम_each_entry(&resource->devices, device, vnr) अणु
		kref_get(&device->kref);
		device_state_change->device = device;
		device_state_change->disk_state[OLD] = device->state.disk;

		/* The peer_devices क्रम each device have to be क्रमागतerated in
		   the order of the connections. We may not use क्रम_each_peer_device() here. */
		क्रम_each_connection(connection, resource) अणु
			काष्ठा drbd_peer_device *peer_device;

			peer_device = conn_peer_device(connection, device->vnr);
			peer_device_state_change->peer_device = peer_device;
			peer_device_state_change->disk_state[OLD] =
				device->state.pdsk;
			peer_device_state_change->repl_state[OLD] =
				max_t(क्रमागत drbd_conns,
				      C_WF_REPORT_PARAMS, device->state.conn);
			peer_device_state_change->resync_susp_user[OLD] =
				device->state.user_isp;
			peer_device_state_change->resync_susp_peer[OLD] =
				device->state.peer_isp;
			peer_device_state_change->resync_susp_dependency[OLD] =
				device->state.aftr_isp;
			peer_device_state_change++;
		पूर्ण
		device_state_change++;
	पूर्ण

	वापस state_change;
पूर्ण

अटल व्योम remember_new_state(काष्ठा drbd_state_change *state_change)
अणु
	काष्ठा drbd_resource_state_change *resource_state_change;
	काष्ठा drbd_resource *resource;
	अचिन्हित पूर्णांक n;

	अगर (!state_change)
		वापस;

	resource_state_change = &state_change->resource[0];
	resource = resource_state_change->resource;

	resource_state_change->role[NEW] =
		conn_highest_role(first_connection(resource));
	resource_state_change->susp[NEW] = resource->susp;
	resource_state_change->susp_nod[NEW] = resource->susp_nod;
	resource_state_change->susp_fen[NEW] = resource->susp_fen;

	क्रम (n = 0; n < state_change->n_devices; n++) अणु
		काष्ठा drbd_device_state_change *device_state_change =
			&state_change->devices[n];
		काष्ठा drbd_device *device = device_state_change->device;

		device_state_change->disk_state[NEW] = device->state.disk;
	पूर्ण

	क्रम (n = 0; n < state_change->n_connections; n++) अणु
		काष्ठा drbd_connection_state_change *connection_state_change =
			&state_change->connections[n];
		काष्ठा drbd_connection *connection =
			connection_state_change->connection;

		connection_state_change->cstate[NEW] = connection->cstate;
		connection_state_change->peer_role[NEW] =
			conn_highest_peer(connection);
	पूर्ण

	क्रम (n = 0; n < state_change->n_devices * state_change->n_connections; n++) अणु
		काष्ठा drbd_peer_device_state_change *peer_device_state_change =
			&state_change->peer_devices[n];
		काष्ठा drbd_device *device =
			peer_device_state_change->peer_device->device;
		जोड़ drbd_dev_state state = device->state;

		peer_device_state_change->disk_state[NEW] = state.pdsk;
		peer_device_state_change->repl_state[NEW] =
			max_t(क्रमागत drbd_conns, C_WF_REPORT_PARAMS, state.conn);
		peer_device_state_change->resync_susp_user[NEW] =
			state.user_isp;
		peer_device_state_change->resync_susp_peer[NEW] =
			state.peer_isp;
		peer_device_state_change->resync_susp_dependency[NEW] =
			state.aftr_isp;
	पूर्ण
पूर्ण

व्योम copy_old_to_new_state_change(काष्ठा drbd_state_change *state_change)
अणु
	काष्ठा drbd_resource_state_change *resource_state_change = &state_change->resource[0];
	अचिन्हित पूर्णांक n_device, n_connection, n_peer_device, n_peer_devices;

#घोषणा OLD_TO_NEW(x) \
	(x[NEW] = x[OLD])

	OLD_TO_NEW(resource_state_change->role);
	OLD_TO_NEW(resource_state_change->susp);
	OLD_TO_NEW(resource_state_change->susp_nod);
	OLD_TO_NEW(resource_state_change->susp_fen);

	क्रम (n_connection = 0; n_connection < state_change->n_connections; n_connection++) अणु
		काष्ठा drbd_connection_state_change *connection_state_change =
				&state_change->connections[n_connection];

		OLD_TO_NEW(connection_state_change->peer_role);
		OLD_TO_NEW(connection_state_change->cstate);
	पूर्ण

	क्रम (n_device = 0; n_device < state_change->n_devices; n_device++) अणु
		काष्ठा drbd_device_state_change *device_state_change =
			&state_change->devices[n_device];

		OLD_TO_NEW(device_state_change->disk_state);
	पूर्ण

	n_peer_devices = state_change->n_devices * state_change->n_connections;
	क्रम (n_peer_device = 0; n_peer_device < n_peer_devices; n_peer_device++) अणु
		काष्ठा drbd_peer_device_state_change *p =
			&state_change->peer_devices[n_peer_device];

		OLD_TO_NEW(p->disk_state);
		OLD_TO_NEW(p->repl_state);
		OLD_TO_NEW(p->resync_susp_user);
		OLD_TO_NEW(p->resync_susp_peer);
		OLD_TO_NEW(p->resync_susp_dependency);
	पूर्ण

#अघोषित OLD_TO_NEW
पूर्ण

व्योम क्रमget_state_change(काष्ठा drbd_state_change *state_change)
अणु
	अचिन्हित पूर्णांक n;

	अगर (!state_change)
		वापस;

	अगर (state_change->resource->resource)
		kref_put(&state_change->resource->resource->kref, drbd_destroy_resource);
	क्रम (n = 0; n < state_change->n_devices; n++) अणु
		काष्ठा drbd_device *device = state_change->devices[n].device;

		अगर (device)
			kref_put(&device->kref, drbd_destroy_device);
	पूर्ण
	क्रम (n = 0; n < state_change->n_connections; n++) अणु
		काष्ठा drbd_connection *connection =
			state_change->connections[n].connection;

		अगर (connection)
			kref_put(&connection->kref, drbd_destroy_connection);
	पूर्ण
	kमुक्त(state_change);
पूर्ण

अटल पूर्णांक w_after_state_ch(काष्ठा drbd_work *w, पूर्णांक unused);
अटल व्योम after_state_ch(काष्ठा drbd_device *device, जोड़ drbd_state os,
			   जोड़ drbd_state ns, क्रमागत chg_state_flags flags,
			   काष्ठा drbd_state_change *);
अटल क्रमागत drbd_state_rv is_valid_state(काष्ठा drbd_device *, जोड़ drbd_state);
अटल क्रमागत drbd_state_rv is_valid_soft_transition(जोड़ drbd_state, जोड़ drbd_state, काष्ठा drbd_connection *);
अटल क्रमागत drbd_state_rv is_valid_transition(जोड़ drbd_state os, जोड़ drbd_state ns);
अटल जोड़ drbd_state sanitize_state(काष्ठा drbd_device *device, जोड़ drbd_state os,
				       जोड़ drbd_state ns, क्रमागत sanitize_state_warnings *warn);

अटल अंतरभूत bool is_susp(जोड़ drbd_state s)
अणु
        वापस s.susp || s.susp_nod || s.susp_fen;
पूर्ण

bool conn_all_vols_unconf(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_peer_device *peer_device;
	bool rv = true;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		अगर (device->state.disk != D_DISKLESS ||
		    device->state.conn != C_STANDALONE ||
		    device->state.role != R_SECONDARY) अणु
			rv = false;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस rv;
पूर्ण

/* Unक्रमtunately the states where not correctly ordered, when
   they where defined. thereक्रमe can not use max_t() here. */
अटल क्रमागत drbd_role max_role(क्रमागत drbd_role role1, क्रमागत drbd_role role2)
अणु
	अगर (role1 == R_PRIMARY || role2 == R_PRIMARY)
		वापस R_PRIMARY;
	अगर (role1 == R_SECONDARY || role2 == R_SECONDARY)
		वापस R_SECONDARY;
	वापस R_UNKNOWN;
पूर्ण

अटल क्रमागत drbd_role min_role(क्रमागत drbd_role role1, क्रमागत drbd_role role2)
अणु
	अगर (role1 == R_UNKNOWN || role2 == R_UNKNOWN)
		वापस R_UNKNOWN;
	अगर (role1 == R_SECONDARY || role2 == R_SECONDARY)
		वापस R_SECONDARY;
	वापस R_PRIMARY;
पूर्ण

क्रमागत drbd_role conn_highest_role(काष्ठा drbd_connection *connection)
अणु
	क्रमागत drbd_role role = R_SECONDARY;
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		role = max_role(role, device->state.role);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस role;
पूर्ण

क्रमागत drbd_role conn_highest_peer(काष्ठा drbd_connection *connection)
अणु
	क्रमागत drbd_role peer = R_UNKNOWN;
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		peer = max_role(peer, device->state.peer);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस peer;
पूर्ण

क्रमागत drbd_disk_state conn_highest_disk(काष्ठा drbd_connection *connection)
अणु
	क्रमागत drbd_disk_state disk_state = D_DISKLESS;
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		disk_state = max_t(क्रमागत drbd_disk_state, disk_state, device->state.disk);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस disk_state;
पूर्ण

क्रमागत drbd_disk_state conn_lowest_disk(काष्ठा drbd_connection *connection)
अणु
	क्रमागत drbd_disk_state disk_state = D_MASK;
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		disk_state = min_t(क्रमागत drbd_disk_state, disk_state, device->state.disk);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस disk_state;
पूर्ण

क्रमागत drbd_disk_state conn_highest_pdsk(काष्ठा drbd_connection *connection)
अणु
	क्रमागत drbd_disk_state disk_state = D_DISKLESS;
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		disk_state = max_t(क्रमागत drbd_disk_state, disk_state, device->state.pdsk);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस disk_state;
पूर्ण

क्रमागत drbd_conns conn_lowest_conn(काष्ठा drbd_connection *connection)
अणु
	क्रमागत drbd_conns conn = C_MASK;
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		conn = min_t(क्रमागत drbd_conns, conn, device->state.conn);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस conn;
पूर्ण

अटल bool no_peer_wf_report_params(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;
	bool rv = true;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr)
		अगर (peer_device->device->state.conn == C_WF_REPORT_PARAMS) अणु
			rv = false;
			अवरोध;
		पूर्ण
	rcu_पढ़ो_unlock();

	वापस rv;
पूर्ण

अटल व्योम wake_up_all_devices(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr)
		wake_up(&peer_device->device->state_रुको);
	rcu_पढ़ो_unlock();

पूर्ण


/**
 * cl_wide_st_chg() - true अगर the state change is a cluster wide one
 * @device:	DRBD device.
 * @os:		old (current) state.
 * @ns:		new (wanted) state.
 */
अटल पूर्णांक cl_wide_st_chg(काष्ठा drbd_device *device,
			  जोड़ drbd_state os, जोड़ drbd_state ns)
अणु
	वापस (os.conn >= C_CONNECTED && ns.conn >= C_CONNECTED &&
		 ((os.role != R_PRIMARY && ns.role == R_PRIMARY) ||
		  (os.conn != C_STARTING_SYNC_T && ns.conn == C_STARTING_SYNC_T) ||
		  (os.conn != C_STARTING_SYNC_S && ns.conn == C_STARTING_SYNC_S) ||
		  (os.disk != D_FAILED && ns.disk == D_FAILED))) ||
		(os.conn >= C_CONNECTED && ns.conn == C_DISCONNECTING) ||
		(os.conn == C_CONNECTED && ns.conn == C_VERIFY_S) ||
		(os.conn == C_CONNECTED && ns.conn == C_WF_REPORT_PARAMS);
पूर्ण

अटल जोड़ drbd_state
apply_mask_val(जोड़ drbd_state os, जोड़ drbd_state mask, जोड़ drbd_state val)
अणु
	जोड़ drbd_state ns;
	ns.i = (os.i & ~mask.i) | val.i;
	वापस ns;
पूर्ण

क्रमागत drbd_state_rv
drbd_change_state(काष्ठा drbd_device *device, क्रमागत chg_state_flags f,
		  जोड़ drbd_state mask, जोड़ drbd_state val)
अणु
	अचिन्हित दीर्घ flags;
	जोड़ drbd_state ns;
	क्रमागत drbd_state_rv rv;

	spin_lock_irqsave(&device->resource->req_lock, flags);
	ns = apply_mask_val(drbd_पढ़ो_state(device), mask, val);
	rv = _drbd_set_state(device, ns, f, शून्य);
	spin_unlock_irqrestore(&device->resource->req_lock, flags);

	वापस rv;
पूर्ण

/**
 * drbd_क्रमce_state() - Impose a change which happens outside our control on our state
 * @device:	DRBD device.
 * @mask:	mask of state bits to change.
 * @val:	value of new state bits.
 */
व्योम drbd_क्रमce_state(काष्ठा drbd_device *device,
	जोड़ drbd_state mask, जोड़ drbd_state val)
अणु
	drbd_change_state(device, CS_HARD, mask, val);
पूर्ण

अटल क्रमागत drbd_state_rv
_req_st_cond(काष्ठा drbd_device *device, जोड़ drbd_state mask,
	     जोड़ drbd_state val)
अणु
	जोड़ drbd_state os, ns;
	अचिन्हित दीर्घ flags;
	क्रमागत drbd_state_rv rv;

	अगर (test_and_clear_bit(CL_ST_CHG_SUCCESS, &device->flags))
		वापस SS_CW_SUCCESS;

	अगर (test_and_clear_bit(CL_ST_CHG_FAIL, &device->flags))
		वापस SS_CW_FAILED_BY_PEER;

	spin_lock_irqsave(&device->resource->req_lock, flags);
	os = drbd_पढ़ो_state(device);
	ns = sanitize_state(device, os, apply_mask_val(os, mask, val), शून्य);
	rv = is_valid_transition(os, ns);
	अगर (rv >= SS_SUCCESS)
		rv = SS_UNKNOWN_ERROR;  /* cont रुकोing, otherwise fail. */

	अगर (!cl_wide_st_chg(device, os, ns))
		rv = SS_CW_NO_NEED;
	अगर (rv == SS_UNKNOWN_ERROR) अणु
		rv = is_valid_state(device, ns);
		अगर (rv >= SS_SUCCESS) अणु
			rv = is_valid_soft_transition(os, ns, first_peer_device(device)->connection);
			अगर (rv >= SS_SUCCESS)
				rv = SS_UNKNOWN_ERROR; /* cont रुकोing, otherwise fail. */
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&device->resource->req_lock, flags);

	वापस rv;
पूर्ण

/**
 * drbd_req_state() - Perक्रमm an eventually cluster wide state change
 * @device:	DRBD device.
 * @mask:	mask of state bits to change.
 * @val:	value of new state bits.
 * @f:		flags
 *
 * Should not be called directly, use drbd_request_state() or
 * _drbd_request_state().
 */
अटल क्रमागत drbd_state_rv
drbd_req_state(काष्ठा drbd_device *device, जोड़ drbd_state mask,
	       जोड़ drbd_state val, क्रमागत chg_state_flags f)
अणु
	काष्ठा completion करोne;
	अचिन्हित दीर्घ flags;
	जोड़ drbd_state os, ns;
	क्रमागत drbd_state_rv rv;
	व्योम *buffer = शून्य;

	init_completion(&करोne);

	अगर (f & CS_SERIALIZE)
		mutex_lock(device->state_mutex);
	अगर (f & CS_INHIBIT_MD_IO)
		buffer = drbd_md_get_buffer(device, __func__);

	spin_lock_irqsave(&device->resource->req_lock, flags);
	os = drbd_पढ़ो_state(device);
	ns = sanitize_state(device, os, apply_mask_val(os, mask, val), शून्य);
	rv = is_valid_transition(os, ns);
	अगर (rv < SS_SUCCESS) अणु
		spin_unlock_irqrestore(&device->resource->req_lock, flags);
		जाओ पात;
	पूर्ण

	अगर (cl_wide_st_chg(device, os, ns)) अणु
		rv = is_valid_state(device, ns);
		अगर (rv == SS_SUCCESS)
			rv = is_valid_soft_transition(os, ns, first_peer_device(device)->connection);
		spin_unlock_irqrestore(&device->resource->req_lock, flags);

		अगर (rv < SS_SUCCESS) अणु
			अगर (f & CS_VERBOSE)
				prपूर्णांक_st_err(device, os, ns, rv);
			जाओ पात;
		पूर्ण

		अगर (drbd_send_state_req(first_peer_device(device), mask, val)) अणु
			rv = SS_CW_FAILED_BY_PEER;
			अगर (f & CS_VERBOSE)
				prपूर्णांक_st_err(device, os, ns, rv);
			जाओ पात;
		पूर्ण

		रुको_event(device->state_रुको,
			(rv = _req_st_cond(device, mask, val)));

		अगर (rv < SS_SUCCESS) अणु
			अगर (f & CS_VERBOSE)
				prपूर्णांक_st_err(device, os, ns, rv);
			जाओ पात;
		पूर्ण
		spin_lock_irqsave(&device->resource->req_lock, flags);
		ns = apply_mask_val(drbd_पढ़ो_state(device), mask, val);
		rv = _drbd_set_state(device, ns, f, &करोne);
	पूर्ण अन्यथा अणु
		rv = _drbd_set_state(device, ns, f, &करोne);
	पूर्ण

	spin_unlock_irqrestore(&device->resource->req_lock, flags);

	अगर (f & CS_WAIT_COMPLETE && rv == SS_SUCCESS) अणु
		D_ASSERT(device, current != first_peer_device(device)->connection->worker.task);
		रुको_क्रम_completion(&करोne);
	पूर्ण

पात:
	अगर (buffer)
		drbd_md_put_buffer(device);
	अगर (f & CS_SERIALIZE)
		mutex_unlock(device->state_mutex);

	वापस rv;
पूर्ण

/**
 * _drbd_request_state() - Request a state change (with flags)
 * @device:	DRBD device.
 * @mask:	mask of state bits to change.
 * @val:	value of new state bits.
 * @f:		flags
 *
 * Cousin of drbd_request_state(), useful with the CS_WAIT_COMPLETE
 * flag, or when logging of failed state change requests is not desired.
 */
क्रमागत drbd_state_rv
_drbd_request_state(काष्ठा drbd_device *device, जोड़ drbd_state mask,
		    जोड़ drbd_state val, क्रमागत chg_state_flags f)
अणु
	क्रमागत drbd_state_rv rv;

	रुको_event(device->state_रुको,
		   (rv = drbd_req_state(device, mask, val, f)) != SS_IN_TRANSIENT_STATE);

	वापस rv;
पूर्ण

/*
 * We grab drbd_md_get_buffer(), because we करोn't want to "fail" the disk जबतक
 * there is IO in-flight: the transition पूर्णांकo D_FAILED क्रम detach purposes
 * may get misपूर्णांकerpreted as actual IO error in a confused endio function.
 *
 * We wrap it all पूर्णांकo रुको_event(), to retry in हाल the drbd_req_state()
 * वापसs SS_IN_TRANSIENT_STATE.
 *
 * To aव्योम potential deadlock with e.g. the receiver thपढ़ो trying to grab
 * drbd_md_get_buffer() जबतक trying to get out of the "transient state", we
 * need to grab and release the meta data buffer inside of that रुको_event loop.
 */
अटल क्रमागत drbd_state_rv
request_detach(काष्ठा drbd_device *device)
अणु
	वापस drbd_req_state(device, NS(disk, D_FAILED),
			CS_VERBOSE | CS_ORDERED | CS_INHIBIT_MD_IO);
पूर्ण

पूर्णांक drbd_request_detach_पूर्णांकerruptible(काष्ठा drbd_device *device)
अणु
	पूर्णांक ret, rv;

	drbd_suspend_io(device); /* so no-one is stuck in drbd_al_begin_io */
	रुको_event_पूर्णांकerruptible(device->state_रुको,
		(rv = request_detach(device)) != SS_IN_TRANSIENT_STATE);
	drbd_resume_io(device);

	ret = रुको_event_पूर्णांकerruptible(device->misc_रुको,
			device->state.disk != D_FAILED);

	अगर (rv == SS_IS_DISKLESS)
		rv = SS_NOTHING_TO_DO;
	अगर (ret)
		rv = ERR_INTR;

	वापस rv;
पूर्ण

क्रमागत drbd_state_rv
_drbd_request_state_holding_state_mutex(काष्ठा drbd_device *device, जोड़ drbd_state mask,
		    जोड़ drbd_state val, क्रमागत chg_state_flags f)
अणु
	क्रमागत drbd_state_rv rv;

	BUG_ON(f & CS_SERIALIZE);

	रुको_event_cmd(device->state_रुको,
		       (rv = drbd_req_state(device, mask, val, f)) != SS_IN_TRANSIENT_STATE,
		       mutex_unlock(device->state_mutex),
		       mutex_lock(device->state_mutex));

	वापस rv;
पूर्ण

अटल व्योम prपूर्णांक_st(काष्ठा drbd_device *device, स्थिर अक्षर *name, जोड़ drbd_state ns)
अणु
	drbd_err(device, " %s = { cs:%s ro:%s/%s ds:%s/%s %c%c%c%c%c%c }\n",
	    name,
	    drbd_conn_str(ns.conn),
	    drbd_role_str(ns.role),
	    drbd_role_str(ns.peer),
	    drbd_disk_str(ns.disk),
	    drbd_disk_str(ns.pdsk),
	    is_susp(ns) ? 's' : 'r',
	    ns.aftr_isp ? 'a' : '-',
	    ns.peer_isp ? 'p' : '-',
	    ns.user_isp ? 'u' : '-',
	    ns.susp_fen ? 'F' : '-',
	    ns.susp_nod ? 'N' : '-'
	    );
पूर्ण

व्योम prपूर्णांक_st_err(काष्ठा drbd_device *device, जोड़ drbd_state os,
	          जोड़ drbd_state ns, क्रमागत drbd_state_rv err)
अणु
	अगर (err == SS_IN_TRANSIENT_STATE)
		वापस;
	drbd_err(device, "State change failed: %s\n", drbd_set_st_err_str(err));
	prपूर्णांक_st(device, " state", os);
	prपूर्णांक_st(device, "wanted", ns);
पूर्ण

अटल दीर्घ prपूर्णांक_state_change(अक्षर *pb, जोड़ drbd_state os, जोड़ drbd_state ns,
			       क्रमागत chg_state_flags flags)
अणु
	अक्षर *pbp;
	pbp = pb;
	*pbp = 0;

	अगर (ns.role != os.role && flags & CS_DC_ROLE)
		pbp += प्र_लिखो(pbp, "role( %s -> %s ) ",
			       drbd_role_str(os.role),
			       drbd_role_str(ns.role));
	अगर (ns.peer != os.peer && flags & CS_DC_PEER)
		pbp += प्र_लिखो(pbp, "peer( %s -> %s ) ",
			       drbd_role_str(os.peer),
			       drbd_role_str(ns.peer));
	अगर (ns.conn != os.conn && flags & CS_DC_CONN)
		pbp += प्र_लिखो(pbp, "conn( %s -> %s ) ",
			       drbd_conn_str(os.conn),
			       drbd_conn_str(ns.conn));
	अगर (ns.disk != os.disk && flags & CS_DC_DISK)
		pbp += प्र_लिखो(pbp, "disk( %s -> %s ) ",
			       drbd_disk_str(os.disk),
			       drbd_disk_str(ns.disk));
	अगर (ns.pdsk != os.pdsk && flags & CS_DC_PDSK)
		pbp += प्र_लिखो(pbp, "pdsk( %s -> %s ) ",
			       drbd_disk_str(os.pdsk),
			       drbd_disk_str(ns.pdsk));

	वापस pbp - pb;
पूर्ण

अटल व्योम drbd_pr_state_change(काष्ठा drbd_device *device, जोड़ drbd_state os, जोड़ drbd_state ns,
				 क्रमागत chg_state_flags flags)
अणु
	अक्षर pb[300];
	अक्षर *pbp = pb;

	pbp += prपूर्णांक_state_change(pbp, os, ns, flags ^ CS_DC_MASK);

	अगर (ns.aftr_isp != os.aftr_isp)
		pbp += प्र_लिखो(pbp, "aftr_isp( %d -> %d ) ",
			       os.aftr_isp,
			       ns.aftr_isp);
	अगर (ns.peer_isp != os.peer_isp)
		pbp += प्र_लिखो(pbp, "peer_isp( %d -> %d ) ",
			       os.peer_isp,
			       ns.peer_isp);
	अगर (ns.user_isp != os.user_isp)
		pbp += प्र_लिखो(pbp, "user_isp( %d -> %d ) ",
			       os.user_isp,
			       ns.user_isp);

	अगर (pbp != pb)
		drbd_info(device, "%s\n", pb);
पूर्ण

अटल व्योम conn_pr_state_change(काष्ठा drbd_connection *connection, जोड़ drbd_state os, जोड़ drbd_state ns,
				 क्रमागत chg_state_flags flags)
अणु
	अक्षर pb[300];
	अक्षर *pbp = pb;

	pbp += prपूर्णांक_state_change(pbp, os, ns, flags);

	अगर (is_susp(ns) != is_susp(os) && flags & CS_DC_SUSP)
		pbp += प्र_लिखो(pbp, "susp( %d -> %d ) ",
			       is_susp(os),
			       is_susp(ns));

	अगर (pbp != pb)
		drbd_info(connection, "%s\n", pb);
पूर्ण


/**
 * is_valid_state() - Returns an SS_ error code अगर ns is not valid
 * @device:	DRBD device.
 * @ns:		State to consider.
 */
अटल क्रमागत drbd_state_rv
is_valid_state(काष्ठा drbd_device *device, जोड़ drbd_state ns)
अणु
	/* See drbd_state_sw_errors in drbd_strings.c */

	क्रमागत drbd_fencing_p fp;
	क्रमागत drbd_state_rv rv = SS_SUCCESS;
	काष्ठा net_conf *nc;

	rcu_पढ़ो_lock();
	fp = FP_DONT_CARE;
	अगर (get_ldev(device)) अणु
		fp = rcu_dereference(device->ldev->disk_conf)->fencing;
		put_ldev(device);
	पूर्ण

	nc = rcu_dereference(first_peer_device(device)->connection->net_conf);
	अगर (nc) अणु
		अगर (!nc->two_primaries && ns.role == R_PRIMARY) अणु
			अगर (ns.peer == R_PRIMARY)
				rv = SS_TWO_PRIMARIES;
			अन्यथा अगर (conn_highest_peer(first_peer_device(device)->connection) == R_PRIMARY)
				rv = SS_O_VOL_PEER_PRI;
		पूर्ण
	पूर्ण

	अगर (rv <= 0)
		जाओ out; /* alपढ़ोy found a reason to पात */
	अन्यथा अगर (ns.role == R_SECONDARY && device->खोलो_cnt)
		rv = SS_DEVICE_IN_USE;

	अन्यथा अगर (ns.role == R_PRIMARY && ns.conn < C_CONNECTED && ns.disk < D_UP_TO_DATE)
		rv = SS_NO_UP_TO_DATE_DISK;

	अन्यथा अगर (fp >= FP_RESOURCE &&
		 ns.role == R_PRIMARY && ns.conn < C_CONNECTED && ns.pdsk >= D_UNKNOWN)
		rv = SS_PRIMARY_NOP;

	अन्यथा अगर (ns.role == R_PRIMARY && ns.disk <= D_INCONSISTENT && ns.pdsk <= D_INCONSISTENT)
		rv = SS_NO_UP_TO_DATE_DISK;

	अन्यथा अगर (ns.conn > C_CONNECTED && ns.disk < D_INCONSISTENT)
		rv = SS_NO_LOCAL_DISK;

	अन्यथा अगर (ns.conn > C_CONNECTED && ns.pdsk < D_INCONSISTENT)
		rv = SS_NO_REMOTE_DISK;

	अन्यथा अगर (ns.conn > C_CONNECTED && ns.disk < D_UP_TO_DATE && ns.pdsk < D_UP_TO_DATE)
		rv = SS_NO_UP_TO_DATE_DISK;

	अन्यथा अगर ((ns.conn == C_CONNECTED ||
		  ns.conn == C_WF_BITMAP_S ||
		  ns.conn == C_SYNC_SOURCE ||
		  ns.conn == C_PAUSED_SYNC_S) &&
		  ns.disk == D_OUTDATED)
		rv = SS_CONNECTED_OUTDATES;

	अन्यथा अगर ((ns.conn == C_VERIFY_S || ns.conn == C_VERIFY_T) &&
		 (nc->verअगरy_alg[0] == 0))
		rv = SS_NO_VERIFY_ALG;

	अन्यथा अगर ((ns.conn == C_VERIFY_S || ns.conn == C_VERIFY_T) &&
		  first_peer_device(device)->connection->agreed_pro_version < 88)
		rv = SS_NOT_SUPPORTED;

	अन्यथा अगर (ns.role == R_PRIMARY && ns.disk < D_UP_TO_DATE && ns.pdsk < D_UP_TO_DATE)
		rv = SS_NO_UP_TO_DATE_DISK;

	अन्यथा अगर ((ns.conn == C_STARTING_SYNC_S || ns.conn == C_STARTING_SYNC_T) &&
                 ns.pdsk == D_UNKNOWN)
		rv = SS_NEED_CONNECTION;

	अन्यथा अगर (ns.conn >= C_CONNECTED && ns.pdsk == D_UNKNOWN)
		rv = SS_CONNECTED_OUTDATES;

out:
	rcu_पढ़ो_unlock();

	वापस rv;
पूर्ण

/**
 * is_valid_soft_transition() - Returns an SS_ error code अगर the state transition is not possible
 * This function limits state transitions that may be declined by DRBD. I.e.
 * user requests (aka soft transitions).
 * @os:		old state.
 * @ns:		new state.
 * @connection:  DRBD connection.
 */
अटल क्रमागत drbd_state_rv
is_valid_soft_transition(जोड़ drbd_state os, जोड़ drbd_state ns, काष्ठा drbd_connection *connection)
अणु
	क्रमागत drbd_state_rv rv = SS_SUCCESS;

	अगर ((ns.conn == C_STARTING_SYNC_T || ns.conn == C_STARTING_SYNC_S) &&
	    os.conn > C_CONNECTED)
		rv = SS_RESYNC_RUNNING;

	अगर (ns.conn == C_DISCONNECTING && os.conn == C_STANDALONE)
		rv = SS_ALREADY_STANDALONE;

	अगर (ns.disk > D_ATTACHING && os.disk == D_DISKLESS)
		rv = SS_IS_DISKLESS;

	अगर (ns.conn == C_WF_CONNECTION && os.conn < C_UNCONNECTED)
		rv = SS_NO_NET_CONFIG;

	अगर (ns.disk == D_OUTDATED && os.disk < D_OUTDATED && os.disk != D_ATTACHING)
		rv = SS_LOWER_THAN_OUTDATED;

	अगर (ns.conn == C_DISCONNECTING && os.conn == C_UNCONNECTED)
		rv = SS_IN_TRANSIENT_STATE;

	/* While establishing a connection only allow cstate to change.
	   Delay/refuse role changes, detach attach etc... (they करो not touch cstate) */
	अगर (test_bit(STATE_SENT, &connection->flags) &&
	    !((ns.conn == C_WF_REPORT_PARAMS && os.conn == C_WF_CONNECTION) ||
	      (ns.conn >= C_CONNECTED && os.conn == C_WF_REPORT_PARAMS)))
		rv = SS_IN_TRANSIENT_STATE;

	/* Do not promote during resync handshake triggered by "force primary".
	 * This is a hack. It should really be rejected by the peer during the
	 * cluster wide state change request. */
	अगर (os.role != R_PRIMARY && ns.role == R_PRIMARY
		&& ns.pdsk == D_UP_TO_DATE
		&& ns.disk != D_UP_TO_DATE && ns.disk != D_DISKLESS
		&& (ns.conn <= C_WF_SYNC_UUID || ns.conn != os.conn))
			rv = SS_IN_TRANSIENT_STATE;

	अगर ((ns.conn == C_VERIFY_S || ns.conn == C_VERIFY_T) && os.conn < C_CONNECTED)
		rv = SS_NEED_CONNECTION;

	अगर ((ns.conn == C_VERIFY_S || ns.conn == C_VERIFY_T) &&
	    ns.conn != os.conn && os.conn > C_CONNECTED)
		rv = SS_RESYNC_RUNNING;

	अगर ((ns.conn == C_STARTING_SYNC_S || ns.conn == C_STARTING_SYNC_T) &&
	    os.conn < C_CONNECTED)
		rv = SS_NEED_CONNECTION;

	अगर ((ns.conn == C_SYNC_TARGET || ns.conn == C_SYNC_SOURCE)
	    && os.conn < C_WF_REPORT_PARAMS)
		rv = SS_NEED_CONNECTION; /* No NetworkFailure -> SyncTarget etc... */

	अगर (ns.conn == C_DISCONNECTING && ns.pdsk == D_OUTDATED &&
	    os.conn < C_CONNECTED && os.pdsk > D_OUTDATED)
		rv = SS_OUTDATE_WO_CONN;

	वापस rv;
पूर्ण

अटल क्रमागत drbd_state_rv
is_valid_conn_transition(क्रमागत drbd_conns oc, क्रमागत drbd_conns nc)
अणु
	/* no change -> nothing to करो, at least क्रम the connection part */
	अगर (oc == nc)
		वापस SS_NOTHING_TO_DO;

	/* disconnect of an unconfigured connection करोes not make sense */
	अगर (oc == C_STANDALONE && nc == C_DISCONNECTING)
		वापस SS_ALREADY_STANDALONE;

	/* from C_STANDALONE, we start with C_UNCONNECTED */
	अगर (oc == C_STANDALONE && nc != C_UNCONNECTED)
		वापस SS_NEED_CONNECTION;

	/* When establishing a connection we need to go through WF_REPORT_PARAMS!
	   Necessary to करो the right thing upon invalidate-remote on a disconnected resource */
	अगर (oc < C_WF_REPORT_PARAMS && nc >= C_CONNECTED)
		वापस SS_NEED_CONNECTION;

	/* After a network error only C_UNCONNECTED or C_DISCONNECTING may follow. */
	अगर (oc >= C_TIMEOUT && oc <= C_TEAR_DOWN && nc != C_UNCONNECTED && nc != C_DISCONNECTING)
		वापस SS_IN_TRANSIENT_STATE;

	/* After C_DISCONNECTING only C_STANDALONE may follow */
	अगर (oc == C_DISCONNECTING && nc != C_STANDALONE)
		वापस SS_IN_TRANSIENT_STATE;

	वापस SS_SUCCESS;
पूर्ण


/**
 * is_valid_transition() - Returns an SS_ error code अगर the state transition is not possible
 * This limits hard state transitions. Hard state transitions are facts there are
 * imposed on DRBD by the environment. E.g. disk broke or network broke करोwn.
 * But those hard state transitions are still not allowed to करो everything.
 * @ns:		new state.
 * @os:		old state.
 */
अटल क्रमागत drbd_state_rv
is_valid_transition(जोड़ drbd_state os, जोड़ drbd_state ns)
अणु
	क्रमागत drbd_state_rv rv;

	rv = is_valid_conn_transition(os.conn, ns.conn);

	/* we cannot fail (again) अगर we alपढ़ोy detached */
	अगर (ns.disk == D_FAILED && os.disk == D_DISKLESS)
		rv = SS_IS_DISKLESS;

	वापस rv;
पूर्ण

अटल व्योम prपूर्णांक_sanitize_warnings(काष्ठा drbd_device *device, क्रमागत sanitize_state_warnings warn)
अणु
	अटल स्थिर अक्षर *msg_table[] = अणु
		[NO_WARNING] = "",
		[ABORTED_ONLINE_VERIFY] = "Online-verify aborted.",
		[ABORTED_RESYNC] = "Resync aborted.",
		[CONNECTION_LOST_NEGOTIATING] = "Connection lost while negotiating, no data!",
		[IMPLICITLY_UPGRADED_DISK] = "Implicitly upgraded disk",
		[IMPLICITLY_UPGRADED_PDSK] = "Implicitly upgraded pdsk",
	पूर्ण;

	अगर (warn != NO_WARNING)
		drbd_warn(device, "%s\n", msg_table[warn]);
पूर्ण

/**
 * sanitize_state() - Resolves implicitly necessary additional changes to a state transition
 * @device:	DRBD device.
 * @os:		old state.
 * @ns:		new state.
 * @warn:	placeholder क्रम वापसed state warning.
 *
 * When we loose connection, we have to set the state of the peers disk (pdsk)
 * to D_UNKNOWN. This rule and many more aदीर्घ those lines are in this function.
 */
अटल जोड़ drbd_state sanitize_state(काष्ठा drbd_device *device, जोड़ drbd_state os,
				       जोड़ drbd_state ns, क्रमागत sanitize_state_warnings *warn)
अणु
	क्रमागत drbd_fencing_p fp;
	क्रमागत drbd_disk_state disk_min, disk_max, pdsk_min, pdsk_max;

	अगर (warn)
		*warn = NO_WARNING;

	fp = FP_DONT_CARE;
	अगर (get_ldev(device)) अणु
		rcu_पढ़ो_lock();
		fp = rcu_dereference(device->ldev->disk_conf)->fencing;
		rcu_पढ़ो_unlock();
		put_ldev(device);
	पूर्ण

	/* Implications from connection to peer and peer_isp */
	अगर (ns.conn < C_CONNECTED) अणु
		ns.peer_isp = 0;
		ns.peer = R_UNKNOWN;
		अगर (ns.pdsk > D_UNKNOWN || ns.pdsk < D_INCONSISTENT)
			ns.pdsk = D_UNKNOWN;
	पूर्ण

	/* Clear the aftr_isp when becoming unconfigured */
	अगर (ns.conn == C_STANDALONE && ns.disk == D_DISKLESS && ns.role == R_SECONDARY)
		ns.aftr_isp = 0;

	/* An implication of the disk states onto the connection state */
	/* Abort resync अगर a disk fails/detaches */
	अगर (ns.conn > C_CONNECTED && (ns.disk <= D_FAILED || ns.pdsk <= D_FAILED)) अणु
		अगर (warn)
			*warn = ns.conn == C_VERIFY_S || ns.conn == C_VERIFY_T ?
				ABORTED_ONLINE_VERIFY : ABORTED_RESYNC;
		ns.conn = C_CONNECTED;
	पूर्ण

	/* Connection अवरोधs करोwn beक्रमe we finished "Negotiating" */
	अगर (ns.conn < C_CONNECTED && ns.disk == D_NEGOTIATING &&
	    get_ldev_अगर_state(device, D_NEGOTIATING)) अणु
		अगर (device->ed_uuid == device->ldev->md.uuid[UI_CURRENT]) अणु
			ns.disk = device->new_state_पंचांगp.disk;
			ns.pdsk = device->new_state_पंचांगp.pdsk;
		पूर्ण अन्यथा अणु
			अगर (warn)
				*warn = CONNECTION_LOST_NEGOTIATING;
			ns.disk = D_DISKLESS;
			ns.pdsk = D_UNKNOWN;
		पूर्ण
		put_ldev(device);
	पूर्ण

	/* D_CONSISTENT and D_OUTDATED vanish when we get connected */
	अगर (ns.conn >= C_CONNECTED && ns.conn < C_AHEAD) अणु
		अगर (ns.disk == D_CONSISTENT || ns.disk == D_OUTDATED)
			ns.disk = D_UP_TO_DATE;
		अगर (ns.pdsk == D_CONSISTENT || ns.pdsk == D_OUTDATED)
			ns.pdsk = D_UP_TO_DATE;
	पूर्ण

	/* Implications of the connection state on the disk states */
	disk_min = D_DISKLESS;
	disk_max = D_UP_TO_DATE;
	pdsk_min = D_INCONSISTENT;
	pdsk_max = D_UNKNOWN;
	चयन ((क्रमागत drbd_conns)ns.conn) अणु
	हाल C_WF_BITMAP_T:
	हाल C_PAUSED_SYNC_T:
	हाल C_STARTING_SYNC_T:
	हाल C_WF_SYNC_UUID:
	हाल C_BEHIND:
		disk_min = D_INCONSISTENT;
		disk_max = D_OUTDATED;
		pdsk_min = D_UP_TO_DATE;
		pdsk_max = D_UP_TO_DATE;
		अवरोध;
	हाल C_VERIFY_S:
	हाल C_VERIFY_T:
		disk_min = D_UP_TO_DATE;
		disk_max = D_UP_TO_DATE;
		pdsk_min = D_UP_TO_DATE;
		pdsk_max = D_UP_TO_DATE;
		अवरोध;
	हाल C_CONNECTED:
		disk_min = D_DISKLESS;
		disk_max = D_UP_TO_DATE;
		pdsk_min = D_DISKLESS;
		pdsk_max = D_UP_TO_DATE;
		अवरोध;
	हाल C_WF_BITMAP_S:
	हाल C_PAUSED_SYNC_S:
	हाल C_STARTING_SYNC_S:
	हाल C_AHEAD:
		disk_min = D_UP_TO_DATE;
		disk_max = D_UP_TO_DATE;
		pdsk_min = D_INCONSISTENT;
		pdsk_max = D_CONSISTENT; /* D_OUTDATED would be nice. But explicit outdate necessary*/
		अवरोध;
	हाल C_SYNC_TARGET:
		disk_min = D_INCONSISTENT;
		disk_max = D_INCONSISTENT;
		pdsk_min = D_UP_TO_DATE;
		pdsk_max = D_UP_TO_DATE;
		अवरोध;
	हाल C_SYNC_SOURCE:
		disk_min = D_UP_TO_DATE;
		disk_max = D_UP_TO_DATE;
		pdsk_min = D_INCONSISTENT;
		pdsk_max = D_INCONSISTENT;
		अवरोध;
	हाल C_STANDALONE:
	हाल C_DISCONNECTING:
	हाल C_UNCONNECTED:
	हाल C_TIMEOUT:
	हाल C_BROKEN_PIPE:
	हाल C_NETWORK_FAILURE:
	हाल C_PROTOCOL_ERROR:
	हाल C_TEAR_DOWN:
	हाल C_WF_CONNECTION:
	हाल C_WF_REPORT_PARAMS:
	हाल C_MASK:
		अवरोध;
	पूर्ण
	अगर (ns.disk > disk_max)
		ns.disk = disk_max;

	अगर (ns.disk < disk_min) अणु
		अगर (warn)
			*warn = IMPLICITLY_UPGRADED_DISK;
		ns.disk = disk_min;
	पूर्ण
	अगर (ns.pdsk > pdsk_max)
		ns.pdsk = pdsk_max;

	अगर (ns.pdsk < pdsk_min) अणु
		अगर (warn)
			*warn = IMPLICITLY_UPGRADED_PDSK;
		ns.pdsk = pdsk_min;
	पूर्ण

	अगर (fp == FP_STONITH &&
	    (ns.role == R_PRIMARY && ns.conn < C_CONNECTED && ns.pdsk > D_OUTDATED) &&
	    !(os.role == R_PRIMARY && os.conn < C_CONNECTED && os.pdsk > D_OUTDATED))
		ns.susp_fen = 1; /* Suspend IO जबतक fence-peer handler runs (peer lost) */

	अगर (device->resource->res_opts.on_no_data == OND_SUSPEND_IO &&
	    (ns.role == R_PRIMARY && ns.disk < D_UP_TO_DATE && ns.pdsk < D_UP_TO_DATE) &&
	    !(os.role == R_PRIMARY && os.disk < D_UP_TO_DATE && os.pdsk < D_UP_TO_DATE))
		ns.susp_nod = 1; /* Suspend IO जबतक no data available (no accessible data available) */

	अगर (ns.aftr_isp || ns.peer_isp || ns.user_isp) अणु
		अगर (ns.conn == C_SYNC_SOURCE)
			ns.conn = C_PAUSED_SYNC_S;
		अगर (ns.conn == C_SYNC_TARGET)
			ns.conn = C_PAUSED_SYNC_T;
	पूर्ण अन्यथा अणु
		अगर (ns.conn == C_PAUSED_SYNC_S)
			ns.conn = C_SYNC_SOURCE;
		अगर (ns.conn == C_PAUSED_SYNC_T)
			ns.conn = C_SYNC_TARGET;
	पूर्ण

	वापस ns;
पूर्ण

व्योम drbd_resume_al(काष्ठा drbd_device *device)
अणु
	अगर (test_and_clear_bit(AL_SUSPENDED, &device->flags))
		drbd_info(device, "Resumed AL updates\n");
पूर्ण

/* helper क्रम _drbd_set_state */
अटल व्योम set_ov_position(काष्ठा drbd_device *device, क्रमागत drbd_conns cs)
अणु
	अगर (first_peer_device(device)->connection->agreed_pro_version < 90)
		device->ov_start_sector = 0;
	device->rs_total = drbd_bm_bits(device);
	device->ov_position = 0;
	अगर (cs == C_VERIFY_T) अणु
		/* starting online verअगरy from an arbitrary position
		 * करोes not fit well पूर्णांकo the existing protocol.
		 * on C_VERIFY_T, we initialize ov_left and मित्रs
		 * implicitly in receive_DataRequest once the
		 * first P_OV_REQUEST is received */
		device->ov_start_sector = ~(sector_t)0;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ bit = BM_SECT_TO_BIT(device->ov_start_sector);
		अगर (bit >= device->rs_total) अणु
			device->ov_start_sector =
				BM_BIT_TO_SECT(device->rs_total - 1);
			device->rs_total = 1;
		पूर्ण अन्यथा
			device->rs_total -= bit;
		device->ov_position = device->ov_start_sector;
	पूर्ण
	device->ov_left = device->rs_total;
पूर्ण

/**
 * _drbd_set_state() - Set a new DRBD state
 * @device:	DRBD device.
 * @ns:		new state.
 * @flags:	Flags
 * @करोne:	Optional completion, that will get completed after the after_state_ch() finished
 *
 * Caller needs to hold req_lock. Do not call directly.
 */
क्रमागत drbd_state_rv
_drbd_set_state(काष्ठा drbd_device *device, जोड़ drbd_state ns,
	        क्रमागत chg_state_flags flags, काष्ठा completion *करोne)
अणु
	काष्ठा drbd_peer_device *peer_device = first_peer_device(device);
	काष्ठा drbd_connection *connection = peer_device ? peer_device->connection : शून्य;
	जोड़ drbd_state os;
	क्रमागत drbd_state_rv rv = SS_SUCCESS;
	क्रमागत sanitize_state_warnings ssw;
	काष्ठा after_state_chg_work *ascw;
	काष्ठा drbd_state_change *state_change;

	os = drbd_पढ़ो_state(device);

	ns = sanitize_state(device, os, ns, &ssw);
	अगर (ns.i == os.i)
		वापस SS_NOTHING_TO_DO;

	rv = is_valid_transition(os, ns);
	अगर (rv < SS_SUCCESS)
		वापस rv;

	अगर (!(flags & CS_HARD)) अणु
		/*  pre-state-change checks ; only look at ns  */
		/* See drbd_state_sw_errors in drbd_strings.c */

		rv = is_valid_state(device, ns);
		अगर (rv < SS_SUCCESS) अणु
			/* If the old state was illegal as well, then let
			   this happen...*/

			अगर (is_valid_state(device, os) == rv)
				rv = is_valid_soft_transition(os, ns, connection);
		पूर्ण अन्यथा
			rv = is_valid_soft_transition(os, ns, connection);
	पूर्ण

	अगर (rv < SS_SUCCESS) अणु
		अगर (flags & CS_VERBOSE)
			prपूर्णांक_st_err(device, os, ns, rv);
		वापस rv;
	पूर्ण

	prपूर्णांक_sanitize_warnings(device, ssw);

	drbd_pr_state_change(device, os, ns, flags);

	/* Display changes to the susp* flags that where caused by the call to
	   sanitize_state(). Only display it here अगर we where not called from
	   _conn_request_state() */
	अगर (!(flags & CS_DC_SUSP))
		conn_pr_state_change(connection, os, ns,
				     (flags & ~CS_DC_MASK) | CS_DC_SUSP);

	/* अगर we are going -> D_FAILED or D_DISKLESS, grab one extra reference
	 * on the ldev here, to be sure the transition -> D_DISKLESS resp.
	 * drbd_ldev_destroy() won't happen beक्रमe our corresponding
	 * after_state_ch works run, where we put_ldev again. */
	अगर ((os.disk != D_FAILED && ns.disk == D_FAILED) ||
	    (os.disk != D_DISKLESS && ns.disk == D_DISKLESS))
		atomic_inc(&device->local_cnt);

	अगर (!is_sync_state(os.conn) && is_sync_state(ns.conn))
		clear_bit(RS_DONE, &device->flags);

	/* FIXME: Have any flags been set earlier in this function alपढ़ोy? */
	state_change = remember_old_state(device->resource, GFP_ATOMIC);

	/* changes to local_cnt and device flags should be visible beक्रमe
	 * changes to state, which again should be visible beक्रमe anything अन्यथा
	 * depending on that change happens. */
	smp_wmb();
	device->state.i = ns.i;
	device->resource->susp = ns.susp;
	device->resource->susp_nod = ns.susp_nod;
	device->resource->susp_fen = ns.susp_fen;
	smp_wmb();

	remember_new_state(state_change);

	/* put replicated vs not-replicated requests in seperate epochs */
	अगर (drbd_should_करो_remote((जोड़ drbd_dev_state)os.i) !=
	    drbd_should_करो_remote((जोड़ drbd_dev_state)ns.i))
		start_new_tl_epoch(connection);

	अगर (os.disk == D_ATTACHING && ns.disk >= D_NEGOTIATING)
		drbd_prपूर्णांक_uuids(device, "attached to UUIDs");

	/* Wake up role changes, that were delayed because of connection establishing */
	अगर (os.conn == C_WF_REPORT_PARAMS && ns.conn != C_WF_REPORT_PARAMS &&
	    no_peer_wf_report_params(connection)) अणु
		clear_bit(STATE_SENT, &connection->flags);
		wake_up_all_devices(connection);
	पूर्ण

	wake_up(&device->misc_रुको);
	wake_up(&device->state_रुको);
	wake_up(&connection->ping_रुको);

	/* Aborted verअगरy run, or we reached the stop sector.
	 * Log the last position, unless end-of-device. */
	अगर ((os.conn == C_VERIFY_S || os.conn == C_VERIFY_T) &&
	    ns.conn <= C_CONNECTED) अणु
		device->ov_start_sector =
			BM_BIT_TO_SECT(drbd_bm_bits(device) - device->ov_left);
		अगर (device->ov_left)
			drbd_info(device, "Online Verify reached sector %llu\n",
				(अचिन्हित दीर्घ दीर्घ)device->ov_start_sector);
	पूर्ण

	अगर ((os.conn == C_PAUSED_SYNC_T || os.conn == C_PAUSED_SYNC_S) &&
	    (ns.conn == C_SYNC_TARGET  || ns.conn == C_SYNC_SOURCE)) अणु
		drbd_info(device, "Syncer continues.\n");
		device->rs_छोड़ोd += (दीर्घ)jअगरfies
				  -(दीर्घ)device->rs_mark_समय[device->rs_last_mark];
		अगर (ns.conn == C_SYNC_TARGET)
			mod_समयr(&device->resync_समयr, jअगरfies);
	पूर्ण

	अगर ((os.conn == C_SYNC_TARGET  || os.conn == C_SYNC_SOURCE) &&
	    (ns.conn == C_PAUSED_SYNC_T || ns.conn == C_PAUSED_SYNC_S)) अणु
		drbd_info(device, "Resync suspended\n");
		device->rs_mark_समय[device->rs_last_mark] = jअगरfies;
	पूर्ण

	अगर (os.conn == C_CONNECTED &&
	    (ns.conn == C_VERIFY_S || ns.conn == C_VERIFY_T)) अणु
		अचिन्हित दीर्घ now = jअगरfies;
		पूर्णांक i;

		set_ov_position(device, ns.conn);
		device->rs_start = now;
		device->rs_last_sect_ev = 0;
		device->ov_last_oos_size = 0;
		device->ov_last_oos_start = 0;

		क्रम (i = 0; i < DRBD_SYNC_MARKS; i++) अणु
			device->rs_mark_left[i] = device->ov_left;
			device->rs_mark_समय[i] = now;
		पूर्ण

		drbd_rs_controller_reset(device);

		अगर (ns.conn == C_VERIFY_S) अणु
			drbd_info(device, "Starting Online Verify from sector %llu\n",
					(अचिन्हित दीर्घ दीर्घ)device->ov_position);
			mod_समयr(&device->resync_समयr, jअगरfies);
		पूर्ण
	पूर्ण

	अगर (get_ldev(device)) अणु
		u32 mdf = device->ldev->md.flags & ~(MDF_CONSISTENT|MDF_PRIMARY_IND|
						 MDF_CONNECTED_IND|MDF_WAS_UP_TO_DATE|
						 MDF_PEER_OUT_DATED|MDF_CRASHED_PRIMARY);

		mdf &= ~MDF_AL_CLEAN;
		अगर (test_bit(CRASHED_PRIMARY, &device->flags))
			mdf |= MDF_CRASHED_PRIMARY;
		अगर (device->state.role == R_PRIMARY ||
		    (device->state.pdsk < D_INCONSISTENT && device->state.peer == R_PRIMARY))
			mdf |= MDF_PRIMARY_IND;
		अगर (device->state.conn > C_WF_REPORT_PARAMS)
			mdf |= MDF_CONNECTED_IND;
		अगर (device->state.disk > D_INCONSISTENT)
			mdf |= MDF_CONSISTENT;
		अगर (device->state.disk > D_OUTDATED)
			mdf |= MDF_WAS_UP_TO_DATE;
		अगर (device->state.pdsk <= D_OUTDATED && device->state.pdsk >= D_INCONSISTENT)
			mdf |= MDF_PEER_OUT_DATED;
		अगर (mdf != device->ldev->md.flags) अणु
			device->ldev->md.flags = mdf;
			drbd_md_mark_dirty(device);
		पूर्ण
		अगर (os.disk < D_CONSISTENT && ns.disk >= D_CONSISTENT)
			drbd_set_ed_uuid(device, device->ldev->md.uuid[UI_CURRENT]);
		put_ldev(device);
	पूर्ण

	/* Peer was क्रमced D_UP_TO_DATE & R_PRIMARY, consider to resync */
	अगर (os.disk == D_INCONSISTENT && os.pdsk == D_INCONSISTENT &&
	    os.peer == R_SECONDARY && ns.peer == R_PRIMARY)
		set_bit(CONSIDER_RESYNC, &device->flags);

	/* Receiver should clean up itself */
	अगर (os.conn != C_DISCONNECTING && ns.conn == C_DISCONNECTING)
		drbd_thपढ़ो_stop_noरुको(&connection->receiver);

	/* Now the receiver finished cleaning up itself, it should die */
	अगर (os.conn != C_STANDALONE && ns.conn == C_STANDALONE)
		drbd_thपढ़ो_stop_noरुको(&connection->receiver);

	/* Upon network failure, we need to restart the receiver. */
	अगर (os.conn > C_WF_CONNECTION &&
	    ns.conn <= C_TEAR_DOWN && ns.conn >= C_TIMEOUT)
		drbd_thपढ़ो_restart_noरुको(&connection->receiver);

	/* Resume AL writing अगर we get a connection */
	अगर (os.conn < C_CONNECTED && ns.conn >= C_CONNECTED) अणु
		drbd_resume_al(device);
		connection->connect_cnt++;
	पूर्ण

	/* remember last attach समय so request_समयr_fn() won't
	 * समाप्त newly established sessions जबतक we are still trying to thaw
	 * previously frozen IO */
	अगर ((os.disk == D_ATTACHING || os.disk == D_NEGOTIATING) &&
	    ns.disk > D_NEGOTIATING)
		device->last_reattach_jअगर = jअगरfies;

	ascw = kदो_स्मृति(माप(*ascw), GFP_ATOMIC);
	अगर (ascw) अणु
		ascw->os = os;
		ascw->ns = ns;
		ascw->flags = flags;
		ascw->w.cb = w_after_state_ch;
		ascw->device = device;
		ascw->करोne = करोne;
		ascw->state_change = state_change;
		drbd_queue_work(&connection->sender_work,
				&ascw->w);
	पूर्ण अन्यथा अणु
		drbd_err(device, "Could not kmalloc an ascw\n");
	पूर्ण

	वापस rv;
पूर्ण

अटल पूर्णांक w_after_state_ch(काष्ठा drbd_work *w, पूर्णांक unused)
अणु
	काष्ठा after_state_chg_work *ascw =
		container_of(w, काष्ठा after_state_chg_work, w);
	काष्ठा drbd_device *device = ascw->device;

	after_state_ch(device, ascw->os, ascw->ns, ascw->flags, ascw->state_change);
	क्रमget_state_change(ascw->state_change);
	अगर (ascw->flags & CS_WAIT_COMPLETE)
		complete(ascw->करोne);
	kमुक्त(ascw);

	वापस 0;
पूर्ण

अटल व्योम abw_start_sync(काष्ठा drbd_device *device, पूर्णांक rv)
अणु
	अगर (rv) अणु
		drbd_err(device, "Writing the bitmap failed not starting resync.\n");
		_drbd_request_state(device, NS(conn, C_CONNECTED), CS_VERBOSE);
		वापस;
	पूर्ण

	चयन (device->state.conn) अणु
	हाल C_STARTING_SYNC_T:
		_drbd_request_state(device, NS(conn, C_WF_SYNC_UUID), CS_VERBOSE);
		अवरोध;
	हाल C_STARTING_SYNC_S:
		drbd_start_resync(device, C_SYNC_SOURCE);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक drbd_biपंचांगap_io_from_worker(काष्ठा drbd_device *device,
		पूर्णांक (*io_fn)(काष्ठा drbd_device *),
		अक्षर *why, क्रमागत bm_flag flags)
अणु
	पूर्णांक rv;

	D_ASSERT(device, current == first_peer_device(device)->connection->worker.task);

	/* खोलो coded non-blocking drbd_suspend_io(device); */
	atomic_inc(&device->suspend_cnt);

	drbd_bm_lock(device, why, flags);
	rv = io_fn(device);
	drbd_bm_unlock(device);

	drbd_resume_io(device);

	वापस rv;
पूर्ण

व्योम notअगरy_resource_state_change(काष्ठा sk_buff *skb,
				  अचिन्हित पूर्णांक seq,
				  काष्ठा drbd_resource_state_change *resource_state_change,
				  क्रमागत drbd_notअगरication_type type)
अणु
	काष्ठा drbd_resource *resource = resource_state_change->resource;
	काष्ठा resource_info resource_info = अणु
		.res_role = resource_state_change->role[NEW],
		.res_susp = resource_state_change->susp[NEW],
		.res_susp_nod = resource_state_change->susp_nod[NEW],
		.res_susp_fen = resource_state_change->susp_fen[NEW],
	पूर्ण;

	notअगरy_resource_state(skb, seq, resource, &resource_info, type);
पूर्ण

व्योम notअगरy_connection_state_change(काष्ठा sk_buff *skb,
				    अचिन्हित पूर्णांक seq,
				    काष्ठा drbd_connection_state_change *connection_state_change,
				    क्रमागत drbd_notअगरication_type type)
अणु
	काष्ठा drbd_connection *connection = connection_state_change->connection;
	काष्ठा connection_info connection_info = अणु
		.conn_connection_state = connection_state_change->cstate[NEW],
		.conn_role = connection_state_change->peer_role[NEW],
	पूर्ण;

	notअगरy_connection_state(skb, seq, connection, &connection_info, type);
पूर्ण

व्योम notअगरy_device_state_change(काष्ठा sk_buff *skb,
				अचिन्हित पूर्णांक seq,
				काष्ठा drbd_device_state_change *device_state_change,
				क्रमागत drbd_notअगरication_type type)
अणु
	काष्ठा drbd_device *device = device_state_change->device;
	काष्ठा device_info device_info = अणु
		.dev_disk_state = device_state_change->disk_state[NEW],
	पूर्ण;

	notअगरy_device_state(skb, seq, device, &device_info, type);
पूर्ण

व्योम notअगरy_peer_device_state_change(काष्ठा sk_buff *skb,
				     अचिन्हित पूर्णांक seq,
				     काष्ठा drbd_peer_device_state_change *p,
				     क्रमागत drbd_notअगरication_type type)
अणु
	काष्ठा drbd_peer_device *peer_device = p->peer_device;
	काष्ठा peer_device_info peer_device_info = अणु
		.peer_repl_state = p->repl_state[NEW],
		.peer_disk_state = p->disk_state[NEW],
		.peer_resync_susp_user = p->resync_susp_user[NEW],
		.peer_resync_susp_peer = p->resync_susp_peer[NEW],
		.peer_resync_susp_dependency = p->resync_susp_dependency[NEW],
	पूर्ण;

	notअगरy_peer_device_state(skb, seq, peer_device, &peer_device_info, type);
पूर्ण

अटल व्योम broadcast_state_change(काष्ठा drbd_state_change *state_change)
अणु
	काष्ठा drbd_resource_state_change *resource_state_change = &state_change->resource[0];
	bool resource_state_has_changed;
	अचिन्हित पूर्णांक n_device, n_connection, n_peer_device, n_peer_devices;
	व्योम (*last_func)(काष्ठा sk_buff *, अचिन्हित पूर्णांक, व्योम *,
			  क्रमागत drbd_notअगरication_type) = शून्य;
	व्योम *last_arg = शून्य;

#घोषणा HAS_CHANGED(state) ((state)[OLD] != (state)[NEW])
#घोषणा FINAL_STATE_CHANGE(type) \
	(अणु अगर (last_func) \
		last_func(शून्य, 0, last_arg, type); \
	पूर्ण)
#घोषणा REMEMBER_STATE_CHANGE(func, arg, type) \
	(अणु FINAL_STATE_CHANGE(type | NOTIFY_CONTINUES); \
	   last_func = (typeof(last_func))func; \
	   last_arg = arg; \
	 पूर्ण)

	mutex_lock(&notअगरication_mutex);

	resource_state_has_changed =
	    HAS_CHANGED(resource_state_change->role) ||
	    HAS_CHANGED(resource_state_change->susp) ||
	    HAS_CHANGED(resource_state_change->susp_nod) ||
	    HAS_CHANGED(resource_state_change->susp_fen);

	अगर (resource_state_has_changed)
		REMEMBER_STATE_CHANGE(notअगरy_resource_state_change,
				      resource_state_change, NOTIFY_CHANGE);

	क्रम (n_connection = 0; n_connection < state_change->n_connections; n_connection++) अणु
		काष्ठा drbd_connection_state_change *connection_state_change =
				&state_change->connections[n_connection];

		अगर (HAS_CHANGED(connection_state_change->peer_role) ||
		    HAS_CHANGED(connection_state_change->cstate))
			REMEMBER_STATE_CHANGE(notअगरy_connection_state_change,
					      connection_state_change, NOTIFY_CHANGE);
	पूर्ण

	क्रम (n_device = 0; n_device < state_change->n_devices; n_device++) अणु
		काष्ठा drbd_device_state_change *device_state_change =
			&state_change->devices[n_device];

		अगर (HAS_CHANGED(device_state_change->disk_state))
			REMEMBER_STATE_CHANGE(notअगरy_device_state_change,
					      device_state_change, NOTIFY_CHANGE);
	पूर्ण

	n_peer_devices = state_change->n_devices * state_change->n_connections;
	क्रम (n_peer_device = 0; n_peer_device < n_peer_devices; n_peer_device++) अणु
		काष्ठा drbd_peer_device_state_change *p =
			&state_change->peer_devices[n_peer_device];

		अगर (HAS_CHANGED(p->disk_state) ||
		    HAS_CHANGED(p->repl_state) ||
		    HAS_CHANGED(p->resync_susp_user) ||
		    HAS_CHANGED(p->resync_susp_peer) ||
		    HAS_CHANGED(p->resync_susp_dependency))
			REMEMBER_STATE_CHANGE(notअगरy_peer_device_state_change,
					      p, NOTIFY_CHANGE);
	पूर्ण

	FINAL_STATE_CHANGE(NOTIFY_CHANGE);
	mutex_unlock(&notअगरication_mutex);

#अघोषित HAS_CHANGED
#अघोषित FINAL_STATE_CHANGE
#अघोषित REMEMBER_STATE_CHANGE
पूर्ण

/* takes old and new peer disk state */
अटल bool lost_contact_to_peer_data(क्रमागत drbd_disk_state os, क्रमागत drbd_disk_state ns)
अणु
	अगर ((os >= D_INCONSISTENT && os != D_UNKNOWN && os != D_OUTDATED)
	&&  (ns < D_INCONSISTENT || ns == D_UNKNOWN || ns == D_OUTDATED))
		वापस true;

	/* Scenario, starting with normal operation
	 * Connected Primary/Secondary UpToDate/UpToDate
	 * NetworkFailure Primary/Unknown UpToDate/DUnknown (frozen)
	 * ...
	 * Connected Primary/Secondary UpToDate/Diskless (resumed; needs to bump uuid!)
	 */
	अगर (os == D_UNKNOWN
	&&  (ns == D_DISKLESS || ns == D_FAILED || ns == D_OUTDATED))
		वापस true;

	वापस false;
पूर्ण

/**
 * after_state_ch() - Perक्रमm after state change actions that may sleep
 * @device:	DRBD device.
 * @os:		old state.
 * @ns:		new state.
 * @flags:	Flags
 * @state_change: state change to broadcast
 */
अटल व्योम after_state_ch(काष्ठा drbd_device *device, जोड़ drbd_state os,
			   जोड़ drbd_state ns, क्रमागत chg_state_flags flags,
			   काष्ठा drbd_state_change *state_change)
अणु
	काष्ठा drbd_resource *resource = device->resource;
	काष्ठा drbd_peer_device *peer_device = first_peer_device(device);
	काष्ठा drbd_connection *connection = peer_device ? peer_device->connection : शून्य;
	काष्ठा sib_info sib;

	broadcast_state_change(state_change);

	sib.sib_reason = SIB_STATE_CHANGE;
	sib.os = os;
	sib.ns = ns;

	अगर ((os.disk != D_UP_TO_DATE || os.pdsk != D_UP_TO_DATE)
	&&  (ns.disk == D_UP_TO_DATE && ns.pdsk == D_UP_TO_DATE)) अणु
		clear_bit(CRASHED_PRIMARY, &device->flags);
		अगर (device->p_uuid)
			device->p_uuid[UI_FLAGS] &= ~((u64)2);
	पूर्ण

	/* Inक्रमm userspace about the change... */
	drbd_bcast_event(device, &sib);

	अगर (!(os.role == R_PRIMARY && os.disk < D_UP_TO_DATE && os.pdsk < D_UP_TO_DATE) &&
	    (ns.role == R_PRIMARY && ns.disk < D_UP_TO_DATE && ns.pdsk < D_UP_TO_DATE))
		drbd_khelper(device, "pri-on-incon-degr");

	/* Here we have the actions that are perक्रमmed after a
	   state change. This function might sleep */

	अगर (ns.susp_nod) अणु
		क्रमागत drbd_req_event what = NOTHING;

		spin_lock_irq(&device->resource->req_lock);
		अगर (os.conn < C_CONNECTED && conn_lowest_conn(connection) >= C_CONNECTED)
			what = RESEND;

		अगर ((os.disk == D_ATTACHING || os.disk == D_NEGOTIATING) &&
		    conn_lowest_disk(connection) == D_UP_TO_DATE)
			what = RESTART_FROZEN_DISK_IO;

		अगर (resource->susp_nod && what != NOTHING) अणु
			_tl_restart(connection, what);
			_conn_request_state(connection,
					    (जोड़ drbd_state) अणु अणु .susp_nod = 1 पूर्ण पूर्ण,
					    (जोड़ drbd_state) अणु अणु .susp_nod = 0 पूर्ण पूर्ण,
					    CS_VERBOSE);
		पूर्ण
		spin_unlock_irq(&device->resource->req_lock);
	पूर्ण

	अगर (ns.susp_fen) अणु
		spin_lock_irq(&device->resource->req_lock);
		अगर (resource->susp_fen && conn_lowest_conn(connection) >= C_CONNECTED) अणु
			/* हाल2: The connection was established again: */
			काष्ठा drbd_peer_device *peer_device;
			पूर्णांक vnr;

			rcu_पढ़ो_lock();
			idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr)
				clear_bit(NEW_CUR_UUID, &peer_device->device->flags);
			rcu_पढ़ो_unlock();

			/* We should actively create a new uuid, _beक्रमe_
			 * we resume/resent, अगर the peer is diskless
			 * (recovery from a multiple error scenario).
			 * Currently, this happens with a slight delay
			 * below when checking lost_contact_to_peer_data() ...
			 */
			_tl_restart(connection, RESEND);
			_conn_request_state(connection,
					    (जोड़ drbd_state) अणु अणु .susp_fen = 1 पूर्ण पूर्ण,
					    (जोड़ drbd_state) अणु अणु .susp_fen = 0 पूर्ण पूर्ण,
					    CS_VERBOSE);
		पूर्ण
		spin_unlock_irq(&device->resource->req_lock);
	पूर्ण

	/* Became sync source.  With protocol >= 96, we still need to send out
	 * the sync uuid now. Need to करो that beक्रमe any drbd_send_state, or
	 * the other side may go "paused sync" beक्रमe receiving the sync uuids,
	 * which is unexpected. */
	अगर ((os.conn != C_SYNC_SOURCE && os.conn != C_PAUSED_SYNC_S) &&
	    (ns.conn == C_SYNC_SOURCE || ns.conn == C_PAUSED_SYNC_S) &&
	    connection->agreed_pro_version >= 96 && get_ldev(device)) अणु
		drbd_gen_and_send_sync_uuid(peer_device);
		put_ldev(device);
	पूर्ण

	/* Do not change the order of the अगर above and the two below... */
	अगर (os.pdsk == D_DISKLESS &&
	    ns.pdsk > D_DISKLESS && ns.pdsk != D_UNKNOWN) अणु      /* attach on the peer */
		/* we probably will start a resync soon.
		 * make sure those things are properly reset. */
		device->rs_total = 0;
		device->rs_failed = 0;
		atomic_set(&device->rs_pending_cnt, 0);
		drbd_rs_cancel_all(device);

		drbd_send_uuids(peer_device);
		drbd_send_state(peer_device, ns);
	पूर्ण
	/* No poपूर्णांक in queuing send_biपंचांगap अगर we करोn't have a connection
	 * anymore, so check also the _current_ state, not only the new state
	 * at the समय this work was queued. */
	अगर (os.conn != C_WF_BITMAP_S && ns.conn == C_WF_BITMAP_S &&
	    device->state.conn == C_WF_BITMAP_S)
		drbd_queue_biपंचांगap_io(device, &drbd_send_biपंचांगap, शून्य,
				"send_bitmap (WFBitMapS)",
				BM_LOCKED_TEST_ALLOWED);

	/* Lost contact to peer's copy of the data */
	अगर (lost_contact_to_peer_data(os.pdsk, ns.pdsk)) अणु
		अगर (get_ldev(device)) अणु
			अगर ((ns.role == R_PRIMARY || ns.peer == R_PRIMARY) &&
			    device->ldev->md.uuid[UI_BITMAP] == 0 && ns.disk >= D_UP_TO_DATE) अणु
				अगर (drbd_suspended(device)) अणु
					set_bit(NEW_CUR_UUID, &device->flags);
				पूर्ण अन्यथा अणु
					drbd_uuid_new_current(device);
					drbd_send_uuids(peer_device);
				पूर्ण
			पूर्ण
			put_ldev(device);
		पूर्ण
	पूर्ण

	अगर (ns.pdsk < D_INCONSISTENT && get_ldev(device)) अणु
		अगर (os.peer != R_PRIMARY && ns.peer == R_PRIMARY &&
		    device->ldev->md.uuid[UI_BITMAP] == 0 && ns.disk >= D_UP_TO_DATE) अणु
			drbd_uuid_new_current(device);
			drbd_send_uuids(peer_device);
		पूर्ण
		/* D_DISKLESS Peer becomes secondary */
		अगर (os.peer == R_PRIMARY && ns.peer == R_SECONDARY)
			/* We may still be Primary ourselves.
			 * No harm करोne अगर the biपंचांगap still changes,
			 * redirtied pages will follow later. */
			drbd_biपंचांगap_io_from_worker(device, &drbd_bm_ग_लिखो,
				"demote diskless peer", BM_LOCKED_SET_ALLOWED);
		put_ldev(device);
	पूर्ण

	/* Write out all changed bits on demote.
	 * Though, no need to da that just yet
	 * अगर there is a resync going on still */
	अगर (os.role == R_PRIMARY && ns.role == R_SECONDARY &&
		device->state.conn <= C_CONNECTED && get_ldev(device)) अणु
		/* No changes to the biपंचांगap expected this समय, so निश्चित that,
		 * even though no harm was करोne अगर it did change. */
		drbd_biपंचांगap_io_from_worker(device, &drbd_bm_ग_लिखो,
				"demote", BM_LOCKED_TEST_ALLOWED);
		put_ldev(device);
	पूर्ण

	/* Last part of the attaching process ... */
	अगर (ns.conn >= C_CONNECTED &&
	    os.disk == D_ATTACHING && ns.disk == D_NEGOTIATING) अणु
		drbd_send_sizes(peer_device, 0, 0);  /* to start sync... */
		drbd_send_uuids(peer_device);
		drbd_send_state(peer_device, ns);
	पूर्ण

	/* We want to छोड़ो/जारी resync, tell peer. */
	अगर (ns.conn >= C_CONNECTED &&
	     ((os.aftr_isp != ns.aftr_isp) ||
	      (os.user_isp != ns.user_isp)))
		drbd_send_state(peer_device, ns);

	/* In हाल one of the isp bits got set, suspend other devices. */
	अगर ((!os.aftr_isp && !os.peer_isp && !os.user_isp) &&
	    (ns.aftr_isp || ns.peer_isp || ns.user_isp))
		suspend_other_sg(device);

	/* Make sure the peer माला_लो inक्रमmed about eventual state
	   changes (ISP bits) जबतक we were in WFReportParams. */
	अगर (os.conn == C_WF_REPORT_PARAMS && ns.conn >= C_CONNECTED)
		drbd_send_state(peer_device, ns);

	अगर (os.conn != C_AHEAD && ns.conn == C_AHEAD)
		drbd_send_state(peer_device, ns);

	/* We are in the progress to start a full sync... */
	अगर ((os.conn != C_STARTING_SYNC_T && ns.conn == C_STARTING_SYNC_T) ||
	    (os.conn != C_STARTING_SYNC_S && ns.conn == C_STARTING_SYNC_S))
		/* no other biपंचांगap changes expected during this phase */
		drbd_queue_biपंचांगap_io(device,
			&drbd_bmio_set_n_ग_लिखो, &abw_start_sync,
			"set_n_write from StartingSync", BM_LOCKED_TEST_ALLOWED);

	/* first half of local IO error, failure to attach,
	 * or administrative detach */
	अगर (os.disk != D_FAILED && ns.disk == D_FAILED) अणु
		क्रमागत drbd_io_error_p eh = EP_PASS_ON;
		पूर्णांक was_io_error = 0;
		/* corresponding get_ldev was in _drbd_set_state, to serialize
		 * our cleanup here with the transition to D_DISKLESS.
		 * But is is still not save to dreference ldev here, since
		 * we might come from an failed Attach beक्रमe ldev was set. */
		अगर (device->ldev) अणु
			rcu_पढ़ो_lock();
			eh = rcu_dereference(device->ldev->disk_conf)->on_io_error;
			rcu_पढ़ो_unlock();

			was_io_error = test_and_clear_bit(WAS_IO_ERROR, &device->flags);

			/* Intentionally call this handler first, beक्रमe drbd_send_state().
			 * See: 2932204 drbd: call local-io-error handler early
			 * People may chose to hard-reset the box from this handler.
			 * It is useful अगर this looks like a "regular node crash". */
			अगर (was_io_error && eh == EP_CALL_HELPER)
				drbd_khelper(device, "local-io-error");

			/* Immediately allow completion of all application IO,
			 * that रुकोs क्रम completion from the local disk,
			 * अगर this was a क्रमce-detach due to disk_समयout
			 * or administrator request (drbdsetup detach --क्रमce).
			 * Do NOT पात otherwise.
			 * Aborting local requests may cause serious problems,
			 * अगर requests are completed to upper layers alपढ़ोy,
			 * and then later the alपढ़ोy submitted local bio completes.
			 * This can cause DMA पूर्णांकo क्रमmer bio pages that meanजबतक
			 * have been re-used क्रम other things.
			 * So पातing local requests may cause crashes,
			 * or even worse, silent data corruption.
			 */
			अगर (test_and_clear_bit(FORCE_DETACH, &device->flags))
				tl_पात_disk_io(device);

			/* current state still has to be D_FAILED,
			 * there is only one way out: to D_DISKLESS,
			 * and that may only happen after our put_ldev below. */
			अगर (device->state.disk != D_FAILED)
				drbd_err(device,
					"ASSERT FAILED: disk is %s during detach\n",
					drbd_disk_str(device->state.disk));

			अगर (ns.conn >= C_CONNECTED)
				drbd_send_state(peer_device, ns);

			drbd_rs_cancel_all(device);

			/* In हाल we want to get something to stable storage still,
			 * this may be the last chance.
			 * Following put_ldev may transition to D_DISKLESS. */
			drbd_md_sync(device);
		पूर्ण
		put_ldev(device);
	पूर्ण

	/* second half of local IO error, failure to attach,
	 * or administrative detach,
	 * after local_cnt references have reached zero again */
	अगर (os.disk != D_DISKLESS && ns.disk == D_DISKLESS) अणु
		/* We must still be diskless,
		 * re-attach has to be serialized with this! */
		अगर (device->state.disk != D_DISKLESS)
			drbd_err(device,
				 "ASSERT FAILED: disk is %s while going diskless\n",
				 drbd_disk_str(device->state.disk));

		अगर (ns.conn >= C_CONNECTED)
			drbd_send_state(peer_device, ns);
		/* corresponding get_ldev in __drbd_set_state
		 * this may finally trigger drbd_ldev_destroy. */
		put_ldev(device);
	पूर्ण

	/* Notअगरy peer that I had a local IO error, and did not detached.. */
	अगर (os.disk == D_UP_TO_DATE && ns.disk == D_INCONSISTENT && ns.conn >= C_CONNECTED)
		drbd_send_state(peer_device, ns);

	/* Disks got bigger जबतक they were detached */
	अगर (ns.disk > D_NEGOTIATING && ns.pdsk > D_NEGOTIATING &&
	    test_and_clear_bit(RESYNC_AFTER_NEG, &device->flags)) अणु
		अगर (ns.conn == C_CONNECTED)
			resync_after_online_grow(device);
	पूर्ण

	/* A resync finished or पातed, wake छोड़ोd devices... */
	अगर ((os.conn > C_CONNECTED && ns.conn <= C_CONNECTED) ||
	    (os.peer_isp && !ns.peer_isp) ||
	    (os.user_isp && !ns.user_isp))
		resume_next_sg(device);

	/* sync target करोne with resync.  Explicitly notअगरy peer, even though
	 * it should (at least क्रम non-empty resyncs) alपढ़ोy know itself. */
	अगर (os.disk < D_UP_TO_DATE && os.conn >= C_SYNC_SOURCE && ns.conn == C_CONNECTED)
		drbd_send_state(peer_device, ns);

	/* Verअगरy finished, or reached stop sector.  Peer did not know about
	 * the stop sector, and we may even have changed the stop sector during
	 * verअगरy to पूर्णांकerrupt/stop early.  Send the new state. */
	अगर (os.conn == C_VERIFY_S && ns.conn == C_CONNECTED
	&& verअगरy_can_करो_stop_sector(device))
		drbd_send_state(peer_device, ns);

	/* This triggers biपंचांगap ग_लिखोout of potentially still unwritten pages
	 * अगर the resync finished cleanly, or पातed because of peer disk
	 * failure, or on transition from resync back to AHEAD/BEHIND.
	 *
	 * Connection loss is handled in drbd_disconnected() by the receiver.
	 *
	 * For resync पातed because of local disk failure, we cannot करो
	 * any biपंचांगap ग_लिखोout anymore.
	 *
	 * No harm करोne अगर some bits change during this phase.
	 */
	अगर ((os.conn > C_CONNECTED && os.conn < C_AHEAD) &&
	    (ns.conn == C_CONNECTED || ns.conn >= C_AHEAD) && get_ldev(device)) अणु
		drbd_queue_biपंचांगap_io(device, &drbd_bm_ग_लिखो_copy_pages, शून्य,
			"write from resync_finished", BM_LOCKED_CHANGE_ALLOWED);
		put_ldev(device);
	पूर्ण

	अगर (ns.disk == D_DISKLESS &&
	    ns.conn == C_STANDALONE &&
	    ns.role == R_SECONDARY) अणु
		अगर (os.aftr_isp != ns.aftr_isp)
			resume_next_sg(device);
	पूर्ण

	drbd_md_sync(device);
पूर्ण

काष्ठा after_conn_state_chg_work अणु
	काष्ठा drbd_work w;
	क्रमागत drbd_conns oc;
	जोड़ drbd_state ns_min;
	जोड़ drbd_state ns_max; /* new, max state, over all devices */
	क्रमागत chg_state_flags flags;
	काष्ठा drbd_connection *connection;
	काष्ठा drbd_state_change *state_change;
पूर्ण;

अटल पूर्णांक w_after_conn_state_ch(काष्ठा drbd_work *w, पूर्णांक unused)
अणु
	काष्ठा after_conn_state_chg_work *acscw =
		container_of(w, काष्ठा after_conn_state_chg_work, w);
	काष्ठा drbd_connection *connection = acscw->connection;
	क्रमागत drbd_conns oc = acscw->oc;
	जोड़ drbd_state ns_max = acscw->ns_max;
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	broadcast_state_change(acscw->state_change);
	क्रमget_state_change(acscw->state_change);
	kमुक्त(acscw);

	/* Upon network configuration, we need to start the receiver */
	अगर (oc == C_STANDALONE && ns_max.conn == C_UNCONNECTED)
		drbd_thपढ़ो_start(&connection->receiver);

	अगर (oc == C_DISCONNECTING && ns_max.conn == C_STANDALONE) अणु
		काष्ठा net_conf *old_conf;

		mutex_lock(&notअगरication_mutex);
		idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr)
			notअगरy_peer_device_state(शून्य, 0, peer_device, शून्य,
						 NOTIFY_DESTROY | NOTIFY_CONTINUES);
		notअगरy_connection_state(शून्य, 0, connection, शून्य, NOTIFY_DESTROY);
		mutex_unlock(&notअगरication_mutex);

		mutex_lock(&connection->resource->conf_update);
		old_conf = connection->net_conf;
		connection->my_addr_len = 0;
		connection->peer_addr_len = 0;
		RCU_INIT_POINTER(connection->net_conf, शून्य);
		conn_मुक्त_crypto(connection);
		mutex_unlock(&connection->resource->conf_update);

		synchronize_rcu();
		kमुक्त(old_conf);
	पूर्ण

	अगर (ns_max.susp_fen) अणु
		/* हाल1: The outdate peer handler is successful: */
		अगर (ns_max.pdsk <= D_OUTDATED) अणु
			rcu_पढ़ो_lock();
			idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
				काष्ठा drbd_device *device = peer_device->device;
				अगर (test_bit(NEW_CUR_UUID, &device->flags)) अणु
					drbd_uuid_new_current(device);
					clear_bit(NEW_CUR_UUID, &device->flags);
				पूर्ण
			पूर्ण
			rcu_पढ़ो_unlock();
			spin_lock_irq(&connection->resource->req_lock);
			_tl_restart(connection, CONNECTION_LOST_WHILE_PENDING);
			_conn_request_state(connection,
					    (जोड़ drbd_state) अणु अणु .susp_fen = 1 पूर्ण पूर्ण,
					    (जोड़ drbd_state) अणु अणु .susp_fen = 0 पूर्ण पूर्ण,
					    CS_VERBOSE);
			spin_unlock_irq(&connection->resource->req_lock);
		पूर्ण
	पूर्ण
	conn_md_sync(connection);
	kref_put(&connection->kref, drbd_destroy_connection);

	वापस 0;
पूर्ण

अटल व्योम conn_old_common_state(काष्ठा drbd_connection *connection, जोड़ drbd_state *pcs, क्रमागत chg_state_flags *pf)
अणु
	क्रमागत chg_state_flags flags = ~0;
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr, first_vol = 1;
	जोड़ drbd_dev_state os, cs = अणु
		अणु .role = R_SECONDARY,
		  .peer = R_UNKNOWN,
		  .conn = connection->cstate,
		  .disk = D_DISKLESS,
		  .pdsk = D_UNKNOWN,
		पूर्ण पूर्ण;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		os = device->state;

		अगर (first_vol) अणु
			cs = os;
			first_vol = 0;
			जारी;
		पूर्ण

		अगर (cs.role != os.role)
			flags &= ~CS_DC_ROLE;

		अगर (cs.peer != os.peer)
			flags &= ~CS_DC_PEER;

		अगर (cs.conn != os.conn)
			flags &= ~CS_DC_CONN;

		अगर (cs.disk != os.disk)
			flags &= ~CS_DC_DISK;

		अगर (cs.pdsk != os.pdsk)
			flags &= ~CS_DC_PDSK;
	पूर्ण
	rcu_पढ़ो_unlock();

	*pf |= CS_DC_MASK;
	*pf &= flags;
	(*pcs).i = cs.i;
पूर्ण

अटल क्रमागत drbd_state_rv
conn_is_valid_transition(काष्ठा drbd_connection *connection, जोड़ drbd_state mask, जोड़ drbd_state val,
			 क्रमागत chg_state_flags flags)
अणु
	क्रमागत drbd_state_rv rv = SS_SUCCESS;
	जोड़ drbd_state ns, os;
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		os = drbd_पढ़ो_state(device);
		ns = sanitize_state(device, os, apply_mask_val(os, mask, val), शून्य);

		अगर (flags & CS_IGN_OUTD_FAIL && ns.disk == D_OUTDATED && os.disk < D_OUTDATED)
			ns.disk = os.disk;

		अगर (ns.i == os.i)
			जारी;

		rv = is_valid_transition(os, ns);

		अगर (rv >= SS_SUCCESS && !(flags & CS_HARD)) अणु
			rv = is_valid_state(device, ns);
			अगर (rv < SS_SUCCESS) अणु
				अगर (is_valid_state(device, os) == rv)
					rv = is_valid_soft_transition(os, ns, connection);
			पूर्ण अन्यथा
				rv = is_valid_soft_transition(os, ns, connection);
		पूर्ण

		अगर (rv < SS_SUCCESS) अणु
			अगर (flags & CS_VERBOSE)
				prपूर्णांक_st_err(device, os, ns, rv);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस rv;
पूर्ण

अटल व्योम
conn_set_state(काष्ठा drbd_connection *connection, जोड़ drbd_state mask, जोड़ drbd_state val,
	       जोड़ drbd_state *pns_min, जोड़ drbd_state *pns_max, क्रमागत chg_state_flags flags)
अणु
	जोड़ drbd_state ns, os, ns_max = अणु पूर्ण;
	जोड़ drbd_state ns_min = अणु
		अणु .role = R_MASK,
		  .peer = R_MASK,
		  .conn = val.conn,
		  .disk = D_MASK,
		  .pdsk = D_MASK
		पूर्ण पूर्ण;
	काष्ठा drbd_peer_device *peer_device;
	क्रमागत drbd_state_rv rv;
	पूर्णांक vnr, number_of_volumes = 0;

	अगर (mask.conn == C_MASK) अणु
		/* remember last connect समय so request_समयr_fn() won't
		 * समाप्त newly established sessions जबतक we are still trying to thaw
		 * previously frozen IO */
		अगर (connection->cstate != C_WF_REPORT_PARAMS && val.conn == C_WF_REPORT_PARAMS)
			connection->last_reconnect_jअगर = jअगरfies;

		connection->cstate = val.conn;
	पूर्ण

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		number_of_volumes++;
		os = drbd_पढ़ो_state(device);
		ns = apply_mask_val(os, mask, val);
		ns = sanitize_state(device, os, ns, शून्य);

		अगर (flags & CS_IGN_OUTD_FAIL && ns.disk == D_OUTDATED && os.disk < D_OUTDATED)
			ns.disk = os.disk;

		rv = _drbd_set_state(device, ns, flags, शून्य);
		BUG_ON(rv < SS_SUCCESS);
		ns.i = device->state.i;
		ns_max.role = max_role(ns.role, ns_max.role);
		ns_max.peer = max_role(ns.peer, ns_max.peer);
		ns_max.conn = max_t(क्रमागत drbd_conns, ns.conn, ns_max.conn);
		ns_max.disk = max_t(क्रमागत drbd_disk_state, ns.disk, ns_max.disk);
		ns_max.pdsk = max_t(क्रमागत drbd_disk_state, ns.pdsk, ns_max.pdsk);

		ns_min.role = min_role(ns.role, ns_min.role);
		ns_min.peer = min_role(ns.peer, ns_min.peer);
		ns_min.conn = min_t(क्रमागत drbd_conns, ns.conn, ns_min.conn);
		ns_min.disk = min_t(क्रमागत drbd_disk_state, ns.disk, ns_min.disk);
		ns_min.pdsk = min_t(क्रमागत drbd_disk_state, ns.pdsk, ns_min.pdsk);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (number_of_volumes == 0) अणु
		ns_min = ns_max = (जोड़ drbd_state) अणु अणु
				.role = R_SECONDARY,
				.peer = R_UNKNOWN,
				.conn = val.conn,
				.disk = D_DISKLESS,
				.pdsk = D_UNKNOWN
			पूर्ण पूर्ण;
	पूर्ण

	ns_min.susp = ns_max.susp = connection->resource->susp;
	ns_min.susp_nod = ns_max.susp_nod = connection->resource->susp_nod;
	ns_min.susp_fen = ns_max.susp_fen = connection->resource->susp_fen;

	*pns_min = ns_min;
	*pns_max = ns_max;
पूर्ण

अटल क्रमागत drbd_state_rv
_conn_rq_cond(काष्ठा drbd_connection *connection, जोड़ drbd_state mask, जोड़ drbd_state val)
अणु
	क्रमागत drbd_state_rv err, rv = SS_UNKNOWN_ERROR; /* जारी रुकोing */;

	अगर (test_and_clear_bit(CONN_WD_ST_CHG_OKAY, &connection->flags))
		rv = SS_CW_SUCCESS;

	अगर (test_and_clear_bit(CONN_WD_ST_CHG_FAIL, &connection->flags))
		rv = SS_CW_FAILED_BY_PEER;

	err = conn_is_valid_transition(connection, mask, val, 0);
	अगर (err == SS_SUCCESS && connection->cstate == C_WF_REPORT_PARAMS)
		वापस rv;

	वापस err;
पूर्ण

क्रमागत drbd_state_rv
_conn_request_state(काष्ठा drbd_connection *connection, जोड़ drbd_state mask, जोड़ drbd_state val,
		    क्रमागत chg_state_flags flags)
अणु
	क्रमागत drbd_state_rv rv = SS_SUCCESS;
	काष्ठा after_conn_state_chg_work *acscw;
	क्रमागत drbd_conns oc = connection->cstate;
	जोड़ drbd_state ns_max, ns_min, os;
	bool have_mutex = false;
	काष्ठा drbd_state_change *state_change;

	अगर (mask.conn) अणु
		rv = is_valid_conn_transition(oc, val.conn);
		अगर (rv < SS_SUCCESS)
			जाओ पात;
	पूर्ण

	rv = conn_is_valid_transition(connection, mask, val, flags);
	अगर (rv < SS_SUCCESS)
		जाओ पात;

	अगर (oc == C_WF_REPORT_PARAMS && val.conn == C_DISCONNECTING &&
	    !(flags & (CS_LOCAL_ONLY | CS_HARD))) अणु

		/* This will be a cluster-wide state change.
		 * Need to give up the spinlock, grab the mutex,
		 * then send the state change request, ... */
		spin_unlock_irq(&connection->resource->req_lock);
		mutex_lock(&connection->cstate_mutex);
		have_mutex = true;

		set_bit(CONN_WD_ST_CHG_REQ, &connection->flags);
		अगर (conn_send_state_req(connection, mask, val)) अणु
			/* sending failed. */
			clear_bit(CONN_WD_ST_CHG_REQ, &connection->flags);
			rv = SS_CW_FAILED_BY_PEER;
			/* need to re-aquire the spin lock, though */
			जाओ पात_unlocked;
		पूर्ण

		अगर (val.conn == C_DISCONNECTING)
			set_bit(DISCONNECT_SENT, &connection->flags);

		/* ... and re-aquire the spinlock.
		 * If _conn_rq_cond() वापसed >= SS_SUCCESS, we must call
		 * conn_set_state() within the same spinlock. */
		spin_lock_irq(&connection->resource->req_lock);
		रुको_event_lock_irq(connection->ping_रुको,
				(rv = _conn_rq_cond(connection, mask, val)),
				connection->resource->req_lock);
		clear_bit(CONN_WD_ST_CHG_REQ, &connection->flags);
		अगर (rv < SS_SUCCESS)
			जाओ पात;
	पूर्ण

	state_change = remember_old_state(connection->resource, GFP_ATOMIC);
	conn_old_common_state(connection, &os, &flags);
	flags |= CS_DC_SUSP;
	conn_set_state(connection, mask, val, &ns_min, &ns_max, flags);
	conn_pr_state_change(connection, os, ns_max, flags);
	remember_new_state(state_change);

	acscw = kदो_स्मृति(माप(*acscw), GFP_ATOMIC);
	अगर (acscw) अणु
		acscw->oc = os.conn;
		acscw->ns_min = ns_min;
		acscw->ns_max = ns_max;
		acscw->flags = flags;
		acscw->w.cb = w_after_conn_state_ch;
		kref_get(&connection->kref);
		acscw->connection = connection;
		acscw->state_change = state_change;
		drbd_queue_work(&connection->sender_work, &acscw->w);
	पूर्ण अन्यथा अणु
		drbd_err(connection, "Could not kmalloc an acscw\n");
	पूर्ण

 पात:
	अगर (have_mutex) अणु
		/* mutex_unlock() "... must not be used in interrupt context.",
		 * so give up the spinlock, then re-aquire it */
		spin_unlock_irq(&connection->resource->req_lock);
 पात_unlocked:
		mutex_unlock(&connection->cstate_mutex);
		spin_lock_irq(&connection->resource->req_lock);
	पूर्ण
	अगर (rv < SS_SUCCESS && flags & CS_VERBOSE) अणु
		drbd_err(connection, "State change failed: %s\n", drbd_set_st_err_str(rv));
		drbd_err(connection, " mask = 0x%x val = 0x%x\n", mask.i, val.i);
		drbd_err(connection, " old_conn:%s wanted_conn:%s\n", drbd_conn_str(oc), drbd_conn_str(val.conn));
	पूर्ण
	वापस rv;
पूर्ण

क्रमागत drbd_state_rv
conn_request_state(काष्ठा drbd_connection *connection, जोड़ drbd_state mask, जोड़ drbd_state val,
		   क्रमागत chg_state_flags flags)
अणु
	क्रमागत drbd_state_rv rv;

	spin_lock_irq(&connection->resource->req_lock);
	rv = _conn_request_state(connection, mask, val, flags);
	spin_unlock_irq(&connection->resource->req_lock);

	वापस rv;
पूर्ण
