<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  linux/net/sunrpc/gss_rpc_upcall.h
 *
 *  Copyright (C) 2012 Simo Sorce <simo@redhat.com>
 */

#अगर_अघोषित _GSS_RPC_UPCALL_H
#घोषणा _GSS_RPC_UPCALL_H

#समावेश <linux/sunrpc/gss_api.h>
#समावेश <linux/sunrpc/auth_gss.h>
#समावेश "gss_rpc_xdr.h"
#समावेश "../netns.h"

काष्ठा gssp_upcall_data अणु
	काष्ठा xdr_netobj in_handle;
	काष्ठा gssp_in_token in_token;
	काष्ठा xdr_netobj out_handle;
	काष्ठा xdr_netobj out_token;
	काष्ठा rpcsec_gss_oid mech_oid;
	काष्ठा svc_cred creds;
	पूर्णांक found_creds;
	पूर्णांक major_status;
	पूर्णांक minor_status;
पूर्ण;

पूर्णांक gssp_accept_sec_context_upcall(काष्ठा net *net,
				काष्ठा gssp_upcall_data *data);
व्योम gssp_मुक्त_upcall_data(काष्ठा gssp_upcall_data *data);

व्योम init_gssp_clnt(काष्ठा sunrpc_net *);
पूर्णांक set_gssp_clnt(काष्ठा net *);
व्योम clear_gssp_clnt(काष्ठा sunrpc_net *);

#पूर्ण_अगर /* _GSS_RPC_UPCALL_H */
