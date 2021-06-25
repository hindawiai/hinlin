<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश "nfpcore/nfp_cpp.h"
#समावेश "nfpcore/nfp_nsp.h"
#समावेश "nfp_app.h"
#समावेश "nfp_main.h"
#समावेश "nfp_net.h"
#समावेश "nfp_port.h"

पूर्णांक nfp_app_nic_vnic_init_phy_port(काष्ठा nfp_pf *pf, काष्ठा nfp_app *app,
				   काष्ठा nfp_net *nn, अचिन्हित पूर्णांक id)
अणु
	पूर्णांक err;

	अगर (!pf->eth_tbl)
		वापस 0;

	nn->port = nfp_port_alloc(app, NFP_PORT_PHYS_PORT, nn->dp.netdev);
	अगर (IS_ERR(nn->port))
		वापस PTR_ERR(nn->port);

	err = nfp_port_init_phy_port(pf, app, nn->port, id);
	अगर (err) अणु
		nfp_port_मुक्त(nn->port);
		वापस err;
	पूर्ण

	वापस nn->port->type == NFP_PORT_INVALID;
पूर्ण

पूर्णांक nfp_app_nic_vnic_alloc(काष्ठा nfp_app *app, काष्ठा nfp_net *nn,
			   अचिन्हित पूर्णांक id)
अणु
	पूर्णांक err;

	err = nfp_app_nic_vnic_init_phy_port(app->pf, app, nn, id);
	अगर (err)
		वापस err < 0 ? err : 0;

	nfp_net_get_mac_addr(app->pf, nn->dp.netdev, nn->port);

	वापस 0;
पूर्ण
