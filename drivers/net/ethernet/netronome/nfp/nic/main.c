<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017 Netronome Systems, Inc. */

#समावेश "../nfpcore/nfp_cpp.h"
#समावेश "../nfpcore/nfp_nsp.h"
#समावेश "../nfp_app.h"
#समावेश "../nfp_main.h"

अटल पूर्णांक nfp_nic_init(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_pf *pf = app->pf;

	अगर (pf->eth_tbl && pf->max_data_vnics != pf->eth_tbl->count) अणु
		nfp_err(pf->cpp, "ETH entries don't match vNICs (%d vs %d)\n",
			pf->max_data_vnics, pf->eth_tbl->count);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_nic_sriov_enable(काष्ठा nfp_app *app, पूर्णांक num_vfs)
अणु
	वापस 0;
पूर्ण

अटल व्योम nfp_nic_sriov_disable(काष्ठा nfp_app *app)
अणु
पूर्ण

स्थिर काष्ठा nfp_app_type app_nic = अणु
	.id		= NFP_APP_CORE_NIC,
	.name		= "nic",

	.init		= nfp_nic_init,
	.vnic_alloc	= nfp_app_nic_vnic_alloc,

	.sriov_enable	= nfp_nic_sriov_enable,
	.sriov_disable	= nfp_nic_sriov_disable,
पूर्ण;
