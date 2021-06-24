<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/sunrpc/auth_gss.h
 *
 * Declarations क्रम RPCSEC_GSS
 *
 * Dug Song <dugsong@monkey.org>
 * Andy Adamson <andros@umich.edu>
 * Bruce Fields <bfields@umich.edu>
 * Copyright (c) 2000 The Regents of the University of Michigan
 */

#अगर_अघोषित _LINUX_SUNRPC_AUTH_GSS_H
#घोषणा _LINUX_SUNRPC_AUTH_GSS_H

#समावेश <linux/refcount.h>
#समावेश <linux/sunrpc/auth.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/sunrpc/gss_api.h>

#घोषणा RPC_GSS_VERSION		1

#घोषणा MAXSEQ 0x80000000 /* maximum legal sequence number, from rfc 2203 */

क्रमागत rpc_gss_proc अणु
	RPC_GSS_PROC_DATA = 0,
	RPC_GSS_PROC_INIT = 1,
	RPC_GSS_PROC_CONTINUE_INIT = 2,
	RPC_GSS_PROC_DESTROY = 3
पूर्ण;

क्रमागत rpc_gss_svc अणु
	RPC_GSS_SVC_NONE = 1,
	RPC_GSS_SVC_INTEGRITY = 2,
	RPC_GSS_SVC_PRIVACY = 3
पूर्ण;

/* on-the-wire gss cred: */
काष्ठा rpc_gss_wire_cred अणु
	u32			gc_v;		/* version */
	u32			gc_proc;	/* control procedure */
	u32			gc_seq;		/* sequence number */
	u32			gc_svc;		/* service */
	काष्ठा xdr_netobj	gc_ctx;		/* context handle */
पूर्ण;

/* on-the-wire gss verअगरier: */
काष्ठा rpc_gss_wire_verf अणु
	u32			gv_flavor;
	काष्ठा xdr_netobj	gv_verf;
पूर्ण;

/* वापस from gss शून्य PROC init sec context */
काष्ठा rpc_gss_init_res अणु
	काष्ठा xdr_netobj	gr_ctx;		/* context handle */
	u32			gr_major;	/* major status */
	u32			gr_minor;	/* minor status */
	u32			gr_win;		/* sequence winकरोw */
	काष्ठा xdr_netobj	gr_token;	/* token */
पूर्ण;

/* The gss_cl_ctx काष्ठा holds all the inक्रमmation the rpcsec_gss client
 * code needs to know about a single security context.  In particular,
 * gc_gss_ctx is the context handle that is used to करो gss-api calls, जबतक
 * gc_wire_ctx is the context handle that is used to identअगरy the context on
 * the wire when communicating with a server. */

काष्ठा gss_cl_ctx अणु
	refcount_t		count;
	क्रमागत rpc_gss_proc	gc_proc;
	u32			gc_seq;
	u32			gc_seq_xmit;
	spinlock_t		gc_seq_lock;
	काष्ठा gss_ctx		*gc_gss_ctx;
	काष्ठा xdr_netobj	gc_wire_ctx;
	काष्ठा xdr_netobj	gc_acceptor;
	u32			gc_win;
	अचिन्हित दीर्घ		gc_expiry;
	काष्ठा rcu_head		gc_rcu;
पूर्ण;

काष्ठा gss_upcall_msg;
काष्ठा gss_cred अणु
	काष्ठा rpc_cred		gc_base;
	क्रमागत rpc_gss_svc	gc_service;
	काष्ठा gss_cl_ctx __rcu	*gc_ctx;
	काष्ठा gss_upcall_msg	*gc_upcall;
	स्थिर अक्षर		*gc_principal;
	अचिन्हित दीर्घ		gc_upcall_बारtamp;
पूर्ण;

#पूर्ण_अगर /* _LINUX_SUNRPC_AUTH_GSS_H */

