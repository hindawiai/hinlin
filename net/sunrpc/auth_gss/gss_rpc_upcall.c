<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  linux/net/sunrpc/gss_rpc_upcall.c
 *
 *  Copyright (C) 2012 Simo Sorce <simo@redhat.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/un.h>

#समावेश <linux/sunrpc/svcauth.h>
#समावेश "gss_rpc_upcall.h"

#घोषणा GSSPROXY_SOCK_PATHNAME	"/var/run/gssproxy.sock"

#घोषणा GSSPROXY_PROGRAM	(400112u)
#घोषणा GSSPROXY_VERS_1		(1u)

/*
 * Encoding/Decoding functions
 */

क्रमागत अणु
	GSSX_शून्य = 0,	/* Unused */
        GSSX_INDICATE_MECHS = 1,
        GSSX_GET_CALL_CONTEXT = 2,
        GSSX_IMPORT_AND_CANON_NAME = 3,
        GSSX_EXPORT_CRED = 4,
        GSSX_IMPORT_CRED = 5,
        GSSX_ACQUIRE_CRED = 6,
        GSSX_STORE_CRED = 7,
        GSSX_INIT_SEC_CONTEXT = 8,
        GSSX_ACCEPT_SEC_CONTEXT = 9,
        GSSX_RELEASE_HANDLE = 10,
        GSSX_GET_MIC = 11,
        GSSX_VERIFY = 12,
        GSSX_WRAP = 13,
        GSSX_UNWRAP = 14,
        GSSX_WRAP_SIZE_LIMIT = 15,
पूर्ण;

#घोषणा PROC(proc, name)				\
[GSSX_##proc] = अणु					\
	.p_proc   = GSSX_##proc,			\
	.p_encode = gssx_enc_##name,	\
	.p_decode = gssx_dec_##name,	\
	.p_arglen = GSSX_ARG_##name##_sz,		\
	.p_replen = GSSX_RES_##name##_sz, 		\
	.p_statidx = GSSX_##proc,			\
	.p_name   = #proc,				\
पूर्ण

अटल स्थिर काष्ठा rpc_procinfo gssp_procedures[] = अणु
	PROC(INDICATE_MECHS, indicate_mechs),
        PROC(GET_CALL_CONTEXT, get_call_context),
        PROC(IMPORT_AND_CANON_NAME, import_and_canon_name),
        PROC(EXPORT_CRED, export_cred),
        PROC(IMPORT_CRED, import_cred),
        PROC(ACQUIRE_CRED, acquire_cred),
        PROC(STORE_CRED, store_cred),
        PROC(INIT_SEC_CONTEXT, init_sec_context),
        PROC(ACCEPT_SEC_CONTEXT, accept_sec_context),
        PROC(RELEASE_HANDLE, release_handle),
        PROC(GET_MIC, get_mic),
        PROC(VERIFY, verअगरy),
        PROC(WRAP, wrap),
        PROC(UNWRAP, unwrap),
        PROC(WRAP_SIZE_LIMIT, wrap_size_limit),
पूर्ण;



/*
 * Common transport functions
 */

अटल स्थिर काष्ठा rpc_program gssp_program;

अटल पूर्णांक gssp_rpc_create(काष्ठा net *net, काष्ठा rpc_clnt **_clnt)
अणु
	अटल स्थिर काष्ठा sockaddr_un gssp_localaddr = अणु
		.sun_family		= AF_LOCAL,
		.sun_path		= GSSPROXY_SOCK_PATHNAME,
	पूर्ण;
	काष्ठा rpc_create_args args = अणु
		.net		= net,
		.protocol	= XPRT_TRANSPORT_LOCAL,
		.address	= (काष्ठा sockaddr *)&gssp_localaddr,
		.addrsize	= माप(gssp_localaddr),
		.servername	= "localhost",
		.program	= &gssp_program,
		.version	= GSSPROXY_VERS_1,
		.authflavor	= RPC_AUTH_शून्य,
		/*
		 * Note we want connection to be करोne in the caller's
		 * fileप्रणाली namespace.  We thereक्रमe turn off the idle
		 * समयout, which would result in reconnections being
		 * करोne without the correct namespace:
		 */
		.flags		= RPC_CLNT_CREATE_NOPING |
				  RPC_CLNT_CREATE_NO_IDLE_TIMEOUT
	पूर्ण;
	काष्ठा rpc_clnt *clnt;
	पूर्णांक result = 0;

	clnt = rpc_create(&args);
	अगर (IS_ERR(clnt)) अणु
		dprपूर्णांकk("RPC:       failed to create AF_LOCAL gssproxy "
				"client (errno %ld).\n", PTR_ERR(clnt));
		result = PTR_ERR(clnt);
		*_clnt = शून्य;
		जाओ out;
	पूर्ण

	dprपूर्णांकk("RPC:       created new gssp local client (gssp_local_clnt: "
			"%p)\n", clnt);
	*_clnt = clnt;

out:
	वापस result;
पूर्ण

व्योम init_gssp_clnt(काष्ठा sunrpc_net *sn)
अणु
	mutex_init(&sn->gssp_lock);
	sn->gssp_clnt = शून्य;
पूर्ण

पूर्णांक set_gssp_clnt(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा rpc_clnt *clnt;
	पूर्णांक ret;

	mutex_lock(&sn->gssp_lock);
	ret = gssp_rpc_create(net, &clnt);
	अगर (!ret) अणु
		अगर (sn->gssp_clnt)
			rpc_shutकरोwn_client(sn->gssp_clnt);
		sn->gssp_clnt = clnt;
	पूर्ण
	mutex_unlock(&sn->gssp_lock);
	वापस ret;
पूर्ण

व्योम clear_gssp_clnt(काष्ठा sunrpc_net *sn)
अणु
	mutex_lock(&sn->gssp_lock);
	अगर (sn->gssp_clnt) अणु
		rpc_shutकरोwn_client(sn->gssp_clnt);
		sn->gssp_clnt = शून्य;
	पूर्ण
	mutex_unlock(&sn->gssp_lock);
पूर्ण

अटल काष्ठा rpc_clnt *get_gssp_clnt(काष्ठा sunrpc_net *sn)
अणु
	काष्ठा rpc_clnt *clnt;

	mutex_lock(&sn->gssp_lock);
	clnt = sn->gssp_clnt;
	अगर (clnt)
		atomic_inc(&clnt->cl_count);
	mutex_unlock(&sn->gssp_lock);
	वापस clnt;
पूर्ण

अटल पूर्णांक gssp_call(काष्ठा net *net, काष्ठा rpc_message *msg)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा rpc_clnt *clnt;
	पूर्णांक status;

	clnt = get_gssp_clnt(sn);
	अगर (!clnt)
		वापस -EIO;
	status = rpc_call_sync(clnt, msg, 0);
	अगर (status < 0) अणु
		dprपूर्णांकk("gssp: rpc_call returned error %d\n", -status);
		चयन (status) अणु
		हाल -EPROTONOSUPPORT:
			status = -EINVAL;
			अवरोध;
		हाल -ECONNREFUSED:
		हाल -ETIMEDOUT:
		हाल -ENOTCONN:
			status = -EAGAIN;
			अवरोध;
		हाल -ERESTARTSYS:
			अगर (संकेतled ())
				status = -EINTR;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	rpc_release_client(clnt);
	वापस status;
पूर्ण

अटल व्योम gssp_मुक्त_receive_pages(काष्ठा gssx_arg_accept_sec_context *arg)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < arg->npages && arg->pages[i]; i++)
		__मुक्त_page(arg->pages[i]);

	kमुक्त(arg->pages);
पूर्ण

अटल पूर्णांक gssp_alloc_receive_pages(काष्ठा gssx_arg_accept_sec_context *arg)
अणु
	अचिन्हित पूर्णांक i;

	arg->npages = DIV_ROUND_UP(NGROUPS_MAX * 4, PAGE_SIZE);
	arg->pages = kसुस्मृति(arg->npages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!arg->pages)
		वापस -ENOMEM;
	क्रम (i = 0; i < arg->npages; i++) अणु
		arg->pages[i] = alloc_page(GFP_KERNEL);
		अगर (!arg->pages[i]) अणु
			gssp_मुक्त_receive_pages(arg);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अक्षर *gssp_stringअगरy(काष्ठा xdr_netobj *netobj)
अणु
	वापस kmemdup_nul(netobj->data, netobj->len, GFP_KERNEL);
पूर्ण

अटल व्योम gssp_hostbased_service(अक्षर **principal)
अणु
	अक्षर *c;

	अगर (!*principal)
		वापस;

	/* terminate and हटाओ realm part */
	c = म_अक्षर(*principal, '@');
	अगर (c) अणु
		*c = '\0';

		/* change service-hostname delimiter */
		c = म_अक्षर(*principal, '/');
		अगर (c)
			*c = '@';
	पूर्ण
	अगर (!c) अणु
		/* not a service principal */
		kमुक्त(*principal);
		*principal = शून्य;
	पूर्ण
पूर्ण

/*
 * Public functions
 */

/* numbers somewhat arbitrary but large enough क्रम current needs */
#घोषणा GSSX_MAX_OUT_HANDLE	128
#घोषणा GSSX_MAX_SRC_PRINC	256
#घोषणा GSSX_KMEMBUF (GSSX_max_output_handle_sz + \
			GSSX_max_oid_sz + \
			GSSX_max_princ_sz + \
			माप(काष्ठा svc_cred))

पूर्णांक gssp_accept_sec_context_upcall(काष्ठा net *net,
				काष्ठा gssp_upcall_data *data)
अणु
	काष्ठा gssx_ctx ctxh = अणु
		.state = data->in_handle
	पूर्ण;
	काष्ठा gssx_arg_accept_sec_context arg = अणु
		.input_token = data->in_token,
	पूर्ण;
	काष्ठा gssx_ctx rctxh = अणु
		/*
		 * pass in the max length we expect क्रम each of these
		 * buffers but let the xdr code kदो_स्मृति them:
		 */
		.exported_context_token.len = GSSX_max_output_handle_sz,
		.mech.len = GSS_OID_MAX_LEN,
		.targ_name.display_name.len = GSSX_max_princ_sz,
		.src_name.display_name.len = GSSX_max_princ_sz
	पूर्ण;
	काष्ठा gssx_res_accept_sec_context res = अणु
		.context_handle = &rctxh,
		.output_token = &data->out_token
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &gssp_procedures[GSSX_ACCEPT_SEC_CONTEXT],
		.rpc_argp = &arg,
		.rpc_resp = &res,
		.rpc_cred = शून्य, /* FIXME ? */
	पूर्ण;
	काष्ठा xdr_netobj client_name = अणु 0 , शून्य पूर्ण;
	काष्ठा xdr_netobj target_name = अणु 0, शून्य पूर्ण;
	पूर्णांक ret;

	अगर (data->in_handle.len != 0)
		arg.context_handle = &ctxh;
	res.output_token->len = GSSX_max_output_token_sz;

	ret = gssp_alloc_receive_pages(&arg);
	अगर (ret)
		वापस ret;

	ret = gssp_call(net, &msg);

	gssp_मुक्त_receive_pages(&arg);

	/* we need to fetch all data even in हाल of error so
	 * that we can मुक्त special strctures is they have been allocated */
	data->major_status = res.status.major_status;
	data->minor_status = res.status.minor_status;
	अगर (res.context_handle) अणु
		data->out_handle = rctxh.exported_context_token;
		data->mech_oid.len = rctxh.mech.len;
		अगर (rctxh.mech.data) अणु
			स_नकल(data->mech_oid.data, rctxh.mech.data,
						data->mech_oid.len);
			kमुक्त(rctxh.mech.data);
		पूर्ण
		client_name = rctxh.src_name.display_name;
		target_name = rctxh.targ_name.display_name;
	पूर्ण

	अगर (res.options.count == 1) अणु
		gssx_buffer *value = &res.options.data[0].value;
		/* Currently we only decode CREDS_VALUE, अगर we add
		 * anything अन्यथा we'll have to loop and match on the
		 * option name */
		अगर (value->len == 1) अणु
			/* steal group info from काष्ठा svc_cred */
			data->creds = *(काष्ठा svc_cred *)value->data;
			data->found_creds = 1;
		पूर्ण
		/* whether we use it or not, मुक्त data */
		kमुक्त(value->data);
	पूर्ण

	अगर (res.options.count != 0) अणु
		kमुक्त(res.options.data);
	पूर्ण

	/* convert to GSS_NT_HOSTBASED_SERVICE क्रमm and set पूर्णांकo creds */
	अगर (data->found_creds) अणु
		अगर (client_name.data) अणु
			data->creds.cr_raw_principal =
					gssp_stringअगरy(&client_name);
			data->creds.cr_principal =
					gssp_stringअगरy(&client_name);
			gssp_hostbased_service(&data->creds.cr_principal);
		पूर्ण
		अगर (target_name.data) अणु
			data->creds.cr_targ_princ =
					gssp_stringअगरy(&target_name);
			gssp_hostbased_service(&data->creds.cr_targ_princ);
		पूर्ण
	पूर्ण
	kमुक्त(client_name.data);
	kमुक्त(target_name.data);

	वापस ret;
पूर्ण

व्योम gssp_मुक्त_upcall_data(काष्ठा gssp_upcall_data *data)
अणु
	kमुक्त(data->in_handle.data);
	kमुक्त(data->out_handle.data);
	kमुक्त(data->out_token.data);
	मुक्त_svc_cred(&data->creds);
पूर्ण

/*
 * Initialization stuff
 */
अटल अचिन्हित पूर्णांक gssp_version1_counts[ARRAY_SIZE(gssp_procedures)];
अटल स्थिर काष्ठा rpc_version gssp_version1 = अणु
	.number		= GSSPROXY_VERS_1,
	.nrprocs	= ARRAY_SIZE(gssp_procedures),
	.procs		= gssp_procedures,
	.counts		= gssp_version1_counts,
पूर्ण;

अटल स्थिर काष्ठा rpc_version *gssp_version[] = अणु
	शून्य,
	&gssp_version1,
पूर्ण;

अटल काष्ठा rpc_stat gssp_stats;

अटल स्थिर काष्ठा rpc_program gssp_program = अणु
	.name		= "gssproxy",
	.number		= GSSPROXY_PROGRAM,
	.nrvers		= ARRAY_SIZE(gssp_version),
	.version	= gssp_version,
	.stats		= &gssp_stats,
पूर्ण;
