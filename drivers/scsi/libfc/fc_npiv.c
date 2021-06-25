<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2009 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

/*
 * NPIV VN_Port helper functions क्रम libfc
 */

#समावेश <scsi/libfc.h>
#समावेश <linux/export.h>

/**
 * libfc_vport_create() - Create a new NPIV vport instance
 * @vport: fc_vport काष्ठाure from scsi_transport_fc
 * @privsize: driver निजी data size to allocate aदीर्घ with the Scsi_Host
 */

काष्ठा fc_lport *libfc_vport_create(काष्ठा fc_vport *vport, पूर्णांक privsize)
अणु
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);
	काष्ठा fc_lport *n_port = shost_priv(shost);
	काष्ठा fc_lport *vn_port;

	vn_port = libfc_host_alloc(shost->hostt, privsize);
	अगर (!vn_port)
		वापस vn_port;

	vn_port->vport = vport;
	vport->dd_data = vn_port;

	mutex_lock(&n_port->lp_mutex);
	list_add_tail(&vn_port->list, &n_port->vports);
	mutex_unlock(&n_port->lp_mutex);

	वापस vn_port;
पूर्ण
EXPORT_SYMBOL(libfc_vport_create);

/**
 * fc_vport_id_lookup() - find NPIV lport that matches a given fabric ID
 * @n_port: Top level N_Port which may have multiple NPIV VN_Ports
 * @port_id: Fabric ID to find a match क्रम
 *
 * Returns: matching lport poपूर्णांकer or शून्य अगर there is no match
 */
काष्ठा fc_lport *fc_vport_id_lookup(काष्ठा fc_lport *n_port, u32 port_id)
अणु
	काष्ठा fc_lport *lport = शून्य;
	काष्ठा fc_lport *vn_port;

	अगर (n_port->port_id == port_id)
		वापस n_port;

	अगर (port_id == FC_FID_FLOGI)
		वापस n_port;		/* क्रम poपूर्णांक-to-poपूर्णांक */

	mutex_lock(&n_port->lp_mutex);
	list_क्रम_each_entry(vn_port, &n_port->vports, list) अणु
		अगर (vn_port->port_id == port_id) अणु
			lport = vn_port;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&n_port->lp_mutex);

	वापस lport;
पूर्ण
EXPORT_SYMBOL(fc_vport_id_lookup);

/*
 * When setting the link state of vports during an lport state change, it's
 * necessary to hold the lp_mutex of both the N_Port and the VN_Port.
 * This tells the lockdep engine to treat the nested locking of the VN_Port
 * as a dअगरferent lock class.
 */
क्रमागत libfc_lport_mutex_class अणु
	LPORT_MUTEX_NORMAL = 0,
	LPORT_MUTEX_VN_PORT = 1,
पूर्ण;

/**
 * __fc_vport_setlink() - update link and status on a VN_Port
 * @n_port: parent N_Port
 * @vn_port: VN_Port to update
 *
 * Locking: must be called with both the N_Port and VN_Port lp_mutex held
 */
अटल व्योम __fc_vport_setlink(काष्ठा fc_lport *n_port,
			       काष्ठा fc_lport *vn_port)
अणु
	काष्ठा fc_vport *vport = vn_port->vport;

	अगर (vn_port->state == LPORT_ST_DISABLED)
		वापस;

	अगर (n_port->state == LPORT_ST_READY) अणु
		अगर (n_port->npiv_enabled) अणु
			fc_vport_set_state(vport, FC_VPORT_INITIALIZING);
			__fc_linkup(vn_port);
		पूर्ण अन्यथा अणु
			fc_vport_set_state(vport, FC_VPORT_NO_FABRIC_SUPP);
			__fc_linkकरोwn(vn_port);
		पूर्ण
	पूर्ण अन्यथा अणु
		fc_vport_set_state(vport, FC_VPORT_LINKDOWN);
		__fc_linkकरोwn(vn_port);
	पूर्ण
पूर्ण

/**
 * fc_vport_setlink() - update link and status on a VN_Port
 * @vn_port: भव port to update
 */
व्योम fc_vport_setlink(काष्ठा fc_lport *vn_port)
अणु
	काष्ठा fc_vport *vport = vn_port->vport;
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);
	काष्ठा fc_lport *n_port = shost_priv(shost);

	mutex_lock(&n_port->lp_mutex);
	mutex_lock_nested(&vn_port->lp_mutex, LPORT_MUTEX_VN_PORT);
	__fc_vport_setlink(n_port, vn_port);
	mutex_unlock(&vn_port->lp_mutex);
	mutex_unlock(&n_port->lp_mutex);
पूर्ण
EXPORT_SYMBOL(fc_vport_setlink);

/**
 * fc_vports_linkchange() - change the link state of all vports
 * @n_port: Parent N_Port that has changed state
 *
 * Locking: called with the n_port lp_mutex held
 */
व्योम fc_vports_linkchange(काष्ठा fc_lport *n_port)
अणु
	काष्ठा fc_lport *vn_port;

	list_क्रम_each_entry(vn_port, &n_port->vports, list) अणु
		mutex_lock_nested(&vn_port->lp_mutex, LPORT_MUTEX_VN_PORT);
		__fc_vport_setlink(n_port, vn_port);
		mutex_unlock(&vn_port->lp_mutex);
	पूर्ण
पूर्ण

