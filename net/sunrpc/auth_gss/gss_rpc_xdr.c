<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * GSS Proxy upcall module
 *
 *  Copyright (C) 2012 Simo Sorce <simo@redhat.com>
 */

#समावेश <linux/sunrpc/svcauth.h>
#समावेश "gss_rpc_xdr.h"

अटल पूर्णांक gssx_enc_bool(काष्ठा xdr_stream *xdr, पूर्णांक v)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -ENOSPC;
	*p = v ? xdr_one : xdr_zero;
	वापस 0;
पूर्ण

अटल पूर्णांक gssx_dec_bool(काष्ठा xdr_stream *xdr, u32 *v)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -ENOSPC;
	*v = be32_to_cpu(*p);
	वापस 0;
पूर्ण

अटल पूर्णांक gssx_enc_buffer(काष्ठा xdr_stream *xdr,
			   स्थिर gssx_buffer *buf)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, माप(u32) + buf->len);
	अगर (!p)
		वापस -ENOSPC;
	xdr_encode_opaque(p, buf->data, buf->len);
	वापस 0;
पूर्ण

अटल पूर्णांक gssx_enc_in_token(काष्ठा xdr_stream *xdr,
			     स्थिर काष्ठा gssp_in_token *in)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस -ENOSPC;
	*p = cpu_to_be32(in->page_len);

	/* all we need to करो is to ग_लिखो pages */
	xdr_ग_लिखो_pages(xdr, in->pages, in->page_base, in->page_len);

	वापस 0;
पूर्ण


अटल पूर्णांक gssx_dec_buffer(काष्ठा xdr_stream *xdr,
			   gssx_buffer *buf)
अणु
	u32 length;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -ENOSPC;

	length = be32_to_cpup(p);
	p = xdr_अंतरभूत_decode(xdr, length);
	अगर (unlikely(p == शून्य))
		वापस -ENOSPC;

	अगर (buf->len == 0) अणु
		/* we पूर्णांकentionally are not पूर्णांकerested in this buffer */
		वापस 0;
	पूर्ण
	अगर (length > buf->len)
		वापस -ENOSPC;

	अगर (!buf->data) अणु
		buf->data = kmemdup(p, length, GFP_KERNEL);
		अगर (!buf->data)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		स_नकल(buf->data, p, length);
	पूर्ण
	buf->len = length;
	वापस 0;
पूर्ण

अटल पूर्णांक gssx_enc_option(काष्ठा xdr_stream *xdr,
			   काष्ठा gssx_option *opt)
अणु
	पूर्णांक err;

	err = gssx_enc_buffer(xdr, &opt->option);
	अगर (err)
		वापस err;
	err = gssx_enc_buffer(xdr, &opt->value);
	वापस err;
पूर्ण

अटल पूर्णांक gssx_dec_option(काष्ठा xdr_stream *xdr,
			   काष्ठा gssx_option *opt)
अणु
	पूर्णांक err;

	err = gssx_dec_buffer(xdr, &opt->option);
	अगर (err)
		वापस err;
	err = gssx_dec_buffer(xdr, &opt->value);
	वापस err;
पूर्ण

अटल पूर्णांक dummy_enc_opt_array(काष्ठा xdr_stream *xdr,
				स्थिर काष्ठा gssx_option_array *oa)
अणु
	__be32 *p;

	अगर (oa->count != 0)
		वापस -EINVAL;

	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस -ENOSPC;
	*p = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक dummy_dec_opt_array(काष्ठा xdr_stream *xdr,
				काष्ठा gssx_option_array *oa)
अणु
	काष्ठा gssx_option dummy;
	u32 count, i;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -ENOSPC;
	count = be32_to_cpup(p++);
	स_रखो(&dummy, 0, माप(dummy));
	क्रम (i = 0; i < count; i++) अणु
		gssx_dec_option(xdr, &dummy);
	पूर्ण

	oa->count = 0;
	oa->data = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक get_host_u32(काष्ठा xdr_stream *xdr, u32 *res)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (!p)
		वापस -EINVAL;
	/* Contents of linux creds are all host-endian: */
	स_नकल(res, p, माप(u32));
	वापस 0;
पूर्ण

अटल पूर्णांक gssx_dec_linux_creds(काष्ठा xdr_stream *xdr,
				काष्ठा svc_cred *creds)
अणु
	u32 length;
	__be32 *p;
	u32 पंचांगp;
	u32 N;
	पूर्णांक i, err;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -ENOSPC;

	length = be32_to_cpup(p);

	अगर (length > (3 + NGROUPS_MAX) * माप(u32))
		वापस -ENOSPC;

	/* uid */
	err = get_host_u32(xdr, &पंचांगp);
	अगर (err)
		वापस err;
	creds->cr_uid = make_kuid(&init_user_ns, पंचांगp);

	/* gid */
	err = get_host_u32(xdr, &पंचांगp);
	अगर (err)
		वापस err;
	creds->cr_gid = make_kgid(&init_user_ns, पंचांगp);

	/* number of additional gid's */
	err = get_host_u32(xdr, &पंचांगp);
	अगर (err)
		वापस err;
	N = पंचांगp;
	अगर ((3 + N) * माप(u32) != length)
		वापस -EINVAL;
	creds->cr_group_info = groups_alloc(N);
	अगर (creds->cr_group_info == शून्य)
		वापस -ENOMEM;

	/* gid's */
	क्रम (i = 0; i < N; i++) अणु
		kgid_t kgid;
		err = get_host_u32(xdr, &पंचांगp);
		अगर (err)
			जाओ out_मुक्त_groups;
		err = -EINVAL;
		kgid = make_kgid(&init_user_ns, पंचांगp);
		अगर (!gid_valid(kgid))
			जाओ out_मुक्त_groups;
		creds->cr_group_info->gid[i] = kgid;
	पूर्ण
	groups_sort(creds->cr_group_info);

	वापस 0;
out_मुक्त_groups:
	groups_मुक्त(creds->cr_group_info);
	वापस err;
पूर्ण

अटल पूर्णांक gssx_dec_option_array(काष्ठा xdr_stream *xdr,
				 काष्ठा gssx_option_array *oa)
अणु
	काष्ठा svc_cred *creds;
	u32 count, i;
	__be32 *p;
	पूर्णांक err;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -ENOSPC;
	count = be32_to_cpup(p++);
	अगर (!count)
		वापस 0;

	/* we recognize only 1 currently: CREDS_VALUE */
	oa->count = 1;

	oa->data = kदो_स्मृति(माप(काष्ठा gssx_option), GFP_KERNEL);
	अगर (!oa->data)
		वापस -ENOMEM;

	creds = kzalloc(माप(काष्ठा svc_cred), GFP_KERNEL);
	अगर (!creds) अणु
		kमुक्त(oa->data);
		वापस -ENOMEM;
	पूर्ण

	oa->data[0].option.data = CREDS_VALUE;
	oa->data[0].option.len = माप(CREDS_VALUE);
	oa->data[0].value.data = (व्योम *)creds;
	oa->data[0].value.len = 0;

	क्रम (i = 0; i < count; i++) अणु
		gssx_buffer dummy = अणु 0, शून्य पूर्ण;
		u32 length;

		/* option buffer */
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(p == शून्य))
			वापस -ENOSPC;

		length = be32_to_cpup(p);
		p = xdr_अंतरभूत_decode(xdr, length);
		अगर (unlikely(p == शून्य))
			वापस -ENOSPC;

		अगर (length == माप(CREDS_VALUE) &&
		    स_भेद(p, CREDS_VALUE, माप(CREDS_VALUE)) == 0) अणु
			/* We have creds here. parse them */
			err = gssx_dec_linux_creds(xdr, creds);
			अगर (err)
				वापस err;
			oa->data[0].value.len = 1; /* presence */
		पूर्ण अन्यथा अणु
			/* consume unपूर्णांकeresting buffer */
			err = gssx_dec_buffer(xdr, &dummy);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gssx_dec_status(काष्ठा xdr_stream *xdr,
			   काष्ठा gssx_status *status)
अणु
	__be32 *p;
	पूर्णांक err;

	/* status->major_status */
	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(p == शून्य))
		वापस -ENOSPC;
	p = xdr_decode_hyper(p, &status->major_status);

	/* status->mech */
	err = gssx_dec_buffer(xdr, &status->mech);
	अगर (err)
		वापस err;

	/* status->minor_status */
	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(p == शून्य))
		वापस -ENOSPC;
	p = xdr_decode_hyper(p, &status->minor_status);

	/* status->major_status_string */
	err = gssx_dec_buffer(xdr, &status->major_status_string);
	अगर (err)
		वापस err;

	/* status->minor_status_string */
	err = gssx_dec_buffer(xdr, &status->minor_status_string);
	अगर (err)
		वापस err;

	/* status->server_ctx */
	err = gssx_dec_buffer(xdr, &status->server_ctx);
	अगर (err)
		वापस err;

	/* we assume we have no options क्रम now, so simply consume them */
	/* status->options */
	err = dummy_dec_opt_array(xdr, &status->options);

	वापस err;
पूर्ण

अटल पूर्णांक gssx_enc_call_ctx(काष्ठा xdr_stream *xdr,
			     स्थिर काष्ठा gssx_call_ctx *ctx)
अणु
	काष्ठा gssx_option opt;
	__be32 *p;
	पूर्णांक err;

	/* ctx->locale */
	err = gssx_enc_buffer(xdr, &ctx->locale);
	अगर (err)
		वापस err;

	/* ctx->server_ctx */
	err = gssx_enc_buffer(xdr, &ctx->server_ctx);
	अगर (err)
		वापस err;

	/* we always want to ask क्रम lucid contexts */
	/* ctx->options */
	p = xdr_reserve_space(xdr, 4);
	*p = cpu_to_be32(2);

	/* we want a lucid_v1 context */
	opt.option.data = LUCID_OPTION;
	opt.option.len = माप(LUCID_OPTION);
	opt.value.data = LUCID_VALUE;
	opt.value.len = माप(LUCID_VALUE);
	err = gssx_enc_option(xdr, &opt);

	/* ..and user creds */
	opt.option.data = CREDS_OPTION;
	opt.option.len = माप(CREDS_OPTION);
	opt.value.data = CREDS_VALUE;
	opt.value.len = माप(CREDS_VALUE);
	err = gssx_enc_option(xdr, &opt);

	वापस err;
पूर्ण

अटल पूर्णांक gssx_dec_name_attr(काष्ठा xdr_stream *xdr,
			     काष्ठा gssx_name_attr *attr)
अणु
	पूर्णांक err;

	/* attr->attr */
	err = gssx_dec_buffer(xdr, &attr->attr);
	अगर (err)
		वापस err;

	/* attr->value */
	err = gssx_dec_buffer(xdr, &attr->value);
	अगर (err)
		वापस err;

	/* attr->extensions */
	err = dummy_dec_opt_array(xdr, &attr->extensions);

	वापस err;
पूर्ण

अटल पूर्णांक dummy_enc_nameattr_array(काष्ठा xdr_stream *xdr,
				    काष्ठा gssx_name_attr_array *naa)
अणु
	__be32 *p;

	अगर (naa->count != 0)
		वापस -EINVAL;

	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस -ENOSPC;
	*p = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक dummy_dec_nameattr_array(काष्ठा xdr_stream *xdr,
				    काष्ठा gssx_name_attr_array *naa)
अणु
	काष्ठा gssx_name_attr dummy = अणु .attr = अणु.len = 0पूर्ण पूर्ण;
	u32 count, i;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -ENOSPC;
	count = be32_to_cpup(p++);
	क्रम (i = 0; i < count; i++) अणु
		gssx_dec_name_attr(xdr, &dummy);
	पूर्ण

	naa->count = 0;
	naa->data = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा xdr_netobj zero_netobj = अणुपूर्ण;

अटल काष्ठा gssx_name_attr_array zero_name_attr_array = अणुपूर्ण;

अटल काष्ठा gssx_option_array zero_option_array = अणुपूर्ण;

अटल पूर्णांक gssx_enc_name(काष्ठा xdr_stream *xdr,
			 काष्ठा gssx_name *name)
अणु
	पूर्णांक err;

	/* name->display_name */
	err = gssx_enc_buffer(xdr, &name->display_name);
	अगर (err)
		वापस err;

	/* name->name_type */
	err = gssx_enc_buffer(xdr, &zero_netobj);
	अगर (err)
		वापस err;

	/* name->exported_name */
	err = gssx_enc_buffer(xdr, &zero_netobj);
	अगर (err)
		वापस err;

	/* name->exported_composite_name */
	err = gssx_enc_buffer(xdr, &zero_netobj);
	अगर (err)
		वापस err;

	/* leave name_attributes empty क्रम now, will add once we have any
	 * to pass up at all */
	/* name->name_attributes */
	err = dummy_enc_nameattr_array(xdr, &zero_name_attr_array);
	अगर (err)
		वापस err;

	/* leave options empty क्रम now, will add once we have any options
	 * to pass up at all */
	/* name->extensions */
	err = dummy_enc_opt_array(xdr, &zero_option_array);

	वापस err;
पूर्ण


अटल पूर्णांक gssx_dec_name(काष्ठा xdr_stream *xdr,
			 काष्ठा gssx_name *name)
अणु
	काष्ठा xdr_netobj dummy_netobj = अणु .len = 0 पूर्ण;
	काष्ठा gssx_name_attr_array dummy_name_attr_array = अणु .count = 0 पूर्ण;
	काष्ठा gssx_option_array dummy_option_array = अणु .count = 0 पूर्ण;
	पूर्णांक err;

	/* name->display_name */
	err = gssx_dec_buffer(xdr, &name->display_name);
	अगर (err)
		वापस err;

	/* name->name_type */
	err = gssx_dec_buffer(xdr, &dummy_netobj);
	अगर (err)
		वापस err;

	/* name->exported_name */
	err = gssx_dec_buffer(xdr, &dummy_netobj);
	अगर (err)
		वापस err;

	/* name->exported_composite_name */
	err = gssx_dec_buffer(xdr, &dummy_netobj);
	अगर (err)
		वापस err;

	/* we assume we have no attributes क्रम now, so simply consume them */
	/* name->name_attributes */
	err = dummy_dec_nameattr_array(xdr, &dummy_name_attr_array);
	अगर (err)
		वापस err;

	/* we assume we have no options क्रम now, so simply consume them */
	/* name->extensions */
	err = dummy_dec_opt_array(xdr, &dummy_option_array);

	वापस err;
पूर्ण

अटल पूर्णांक dummy_enc_credel_array(काष्ठा xdr_stream *xdr,
				  काष्ठा gssx_cred_element_array *cea)
अणु
	__be32 *p;

	अगर (cea->count != 0)
		वापस -EINVAL;

	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस -ENOSPC;
	*p = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक gssx_enc_cred(काष्ठा xdr_stream *xdr,
			 काष्ठा gssx_cred *cred)
अणु
	पूर्णांक err;

	/* cred->desired_name */
	err = gssx_enc_name(xdr, &cred->desired_name);
	अगर (err)
		वापस err;

	/* cred->elements */
	err = dummy_enc_credel_array(xdr, &cred->elements);
	अगर (err)
		वापस err;

	/* cred->cred_handle_reference */
	err = gssx_enc_buffer(xdr, &cred->cred_handle_reference);
	अगर (err)
		वापस err;

	/* cred->needs_release */
	err = gssx_enc_bool(xdr, cred->needs_release);

	वापस err;
पूर्ण

अटल पूर्णांक gssx_enc_ctx(काष्ठा xdr_stream *xdr,
			काष्ठा gssx_ctx *ctx)
अणु
	__be32 *p;
	पूर्णांक err;

	/* ctx->exported_context_token */
	err = gssx_enc_buffer(xdr, &ctx->exported_context_token);
	अगर (err)
		वापस err;

	/* ctx->state */
	err = gssx_enc_buffer(xdr, &ctx->state);
	अगर (err)
		वापस err;

	/* ctx->need_release */
	err = gssx_enc_bool(xdr, ctx->need_release);
	अगर (err)
		वापस err;

	/* ctx->mech */
	err = gssx_enc_buffer(xdr, &ctx->mech);
	अगर (err)
		वापस err;

	/* ctx->src_name */
	err = gssx_enc_name(xdr, &ctx->src_name);
	अगर (err)
		वापस err;

	/* ctx->targ_name */
	err = gssx_enc_name(xdr, &ctx->targ_name);
	अगर (err)
		वापस err;

	/* ctx->lअगरeसमय */
	p = xdr_reserve_space(xdr, 8+8);
	अगर (!p)
		वापस -ENOSPC;
	p = xdr_encode_hyper(p, ctx->lअगरeसमय);

	/* ctx->ctx_flags */
	p = xdr_encode_hyper(p, ctx->ctx_flags);

	/* ctx->locally_initiated */
	err = gssx_enc_bool(xdr, ctx->locally_initiated);
	अगर (err)
		वापस err;

	/* ctx->खोलो */
	err = gssx_enc_bool(xdr, ctx->खोलो);
	अगर (err)
		वापस err;

	/* leave options empty क्रम now, will add once we have any options
	 * to pass up at all */
	/* ctx->options */
	err = dummy_enc_opt_array(xdr, &ctx->options);

	वापस err;
पूर्ण

अटल पूर्णांक gssx_dec_ctx(काष्ठा xdr_stream *xdr,
			काष्ठा gssx_ctx *ctx)
अणु
	__be32 *p;
	पूर्णांक err;

	/* ctx->exported_context_token */
	err = gssx_dec_buffer(xdr, &ctx->exported_context_token);
	अगर (err)
		वापस err;

	/* ctx->state */
	err = gssx_dec_buffer(xdr, &ctx->state);
	अगर (err)
		वापस err;

	/* ctx->need_release */
	err = gssx_dec_bool(xdr, &ctx->need_release);
	अगर (err)
		वापस err;

	/* ctx->mech */
	err = gssx_dec_buffer(xdr, &ctx->mech);
	अगर (err)
		वापस err;

	/* ctx->src_name */
	err = gssx_dec_name(xdr, &ctx->src_name);
	अगर (err)
		वापस err;

	/* ctx->targ_name */
	err = gssx_dec_name(xdr, &ctx->targ_name);
	अगर (err)
		वापस err;

	/* ctx->lअगरeसमय */
	p = xdr_अंतरभूत_decode(xdr, 8+8);
	अगर (unlikely(p == शून्य))
		वापस -ENOSPC;
	p = xdr_decode_hyper(p, &ctx->lअगरeसमय);

	/* ctx->ctx_flags */
	p = xdr_decode_hyper(p, &ctx->ctx_flags);

	/* ctx->locally_initiated */
	err = gssx_dec_bool(xdr, &ctx->locally_initiated);
	अगर (err)
		वापस err;

	/* ctx->खोलो */
	err = gssx_dec_bool(xdr, &ctx->खोलो);
	अगर (err)
		वापस err;

	/* we assume we have no options क्रम now, so simply consume them */
	/* ctx->options */
	err = dummy_dec_opt_array(xdr, &ctx->options);

	वापस err;
पूर्ण

अटल पूर्णांक gssx_enc_cb(काष्ठा xdr_stream *xdr, काष्ठा gssx_cb *cb)
अणु
	__be32 *p;
	पूर्णांक err;

	/* cb->initiator_addrtype */
	p = xdr_reserve_space(xdr, 8);
	अगर (!p)
		वापस -ENOSPC;
	p = xdr_encode_hyper(p, cb->initiator_addrtype);

	/* cb->initiator_address */
	err = gssx_enc_buffer(xdr, &cb->initiator_address);
	अगर (err)
		वापस err;

	/* cb->acceptor_addrtype */
	p = xdr_reserve_space(xdr, 8);
	अगर (!p)
		वापस -ENOSPC;
	p = xdr_encode_hyper(p, cb->acceptor_addrtype);

	/* cb->acceptor_address */
	err = gssx_enc_buffer(xdr, &cb->acceptor_address);
	अगर (err)
		वापस err;

	/* cb->application_data */
	err = gssx_enc_buffer(xdr, &cb->application_data);

	वापस err;
पूर्ण

व्योम gssx_enc_accept_sec_context(काष्ठा rpc_rqst *req,
				 काष्ठा xdr_stream *xdr,
				 स्थिर व्योम *data)
अणु
	स्थिर काष्ठा gssx_arg_accept_sec_context *arg = data;
	पूर्णांक err;

	err = gssx_enc_call_ctx(xdr, &arg->call_ctx);
	अगर (err)
		जाओ करोne;

	/* arg->context_handle */
	अगर (arg->context_handle)
		err = gssx_enc_ctx(xdr, arg->context_handle);
	अन्यथा
		err = gssx_enc_bool(xdr, 0);
	अगर (err)
		जाओ करोne;

	/* arg->cred_handle */
	अगर (arg->cred_handle)
		err = gssx_enc_cred(xdr, arg->cred_handle);
	अन्यथा
		err = gssx_enc_bool(xdr, 0);
	अगर (err)
		जाओ करोne;

	/* arg->input_token */
	err = gssx_enc_in_token(xdr, &arg->input_token);
	अगर (err)
		जाओ करोne;

	/* arg->input_cb */
	अगर (arg->input_cb)
		err = gssx_enc_cb(xdr, arg->input_cb);
	अन्यथा
		err = gssx_enc_bool(xdr, 0);
	अगर (err)
		जाओ करोne;

	err = gssx_enc_bool(xdr, arg->ret_deleg_cred);
	अगर (err)
		जाओ करोne;

	/* leave options empty क्रम now, will add once we have any options
	 * to pass up at all */
	/* arg->options */
	err = dummy_enc_opt_array(xdr, &arg->options);

	xdr_अंतरभूत_pages(&req->rq_rcv_buf,
		PAGE_SIZE/2 /* pretty arbitrary */,
		arg->pages, 0 /* page base */, arg->npages * PAGE_SIZE);
करोne:
	अगर (err)
		dprपूर्णांकk("RPC:       gssx_enc_accept_sec_context: %d\n", err);
पूर्ण

पूर्णांक gssx_dec_accept_sec_context(काष्ठा rpc_rqst *rqstp,
				काष्ठा xdr_stream *xdr,
				व्योम *data)
अणु
	काष्ठा gssx_res_accept_sec_context *res = data;
	u32 value_follows;
	पूर्णांक err;
	काष्ठा page *scratch;

	scratch = alloc_page(GFP_KERNEL);
	अगर (!scratch)
		वापस -ENOMEM;
	xdr_set_scratch_page(xdr, scratch);

	/* res->status */
	err = gssx_dec_status(xdr, &res->status);
	अगर (err)
		जाओ out_मुक्त;

	/* res->context_handle */
	err = gssx_dec_bool(xdr, &value_follows);
	अगर (err)
		जाओ out_मुक्त;
	अगर (value_follows) अणु
		err = gssx_dec_ctx(xdr, res->context_handle);
		अगर (err)
			जाओ out_मुक्त;
	पूर्ण अन्यथा अणु
		res->context_handle = शून्य;
	पूर्ण

	/* res->output_token */
	err = gssx_dec_bool(xdr, &value_follows);
	अगर (err)
		जाओ out_मुक्त;
	अगर (value_follows) अणु
		err = gssx_dec_buffer(xdr, res->output_token);
		अगर (err)
			जाओ out_मुक्त;
	पूर्ण अन्यथा अणु
		res->output_token = शून्य;
	पूर्ण

	/* res->delegated_cred_handle */
	err = gssx_dec_bool(xdr, &value_follows);
	अगर (err)
		जाओ out_मुक्त;
	अगर (value_follows) अणु
		/* we करो not support upcall servers sending this data. */
		err = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	/* res->options */
	err = gssx_dec_option_array(xdr, &res->options);

out_मुक्त:
	__मुक्त_page(scratch);
	वापस err;
पूर्ण
