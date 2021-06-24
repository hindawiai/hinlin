<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/9p/clnt.c
 *
 * 9P Client
 *
 *  Copyright (C) 2008 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2007 by Latchesar Ionkov <lucho@ionkov.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/idr.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/uपन.स>
#समावेश <net/9p/9p.h>
#समावेश <linux/parser.h>
#समावेश <linux/seq_file.h>
#समावेश <net/9p/client.h>
#समावेश <net/9p/transport.h>
#समावेश "protocol.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/9p.h>

/*
  * Client Option Parsing (code inspired by NFS code)
  *  - a little lazy - parse all client options
  */

क्रमागत अणु
	Opt_msize,
	Opt_trans,
	Opt_legacy,
	Opt_version,
	Opt_err,
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_msize, "msize=%u"पूर्ण,
	अणुOpt_legacy, "noextend"पूर्ण,
	अणुOpt_trans, "trans=%s"पूर्ण,
	अणुOpt_version, "version=%s"पूर्ण,
	अणुOpt_err, शून्यपूर्ण,
पूर्ण;

अंतरभूत पूर्णांक p9_is_proto_करोtl(काष्ठा p9_client *clnt)
अणु
	वापस clnt->proto_version == p9_proto_2000L;
पूर्ण
EXPORT_SYMBOL(p9_is_proto_करोtl);

अंतरभूत पूर्णांक p9_is_proto_करोtu(काष्ठा p9_client *clnt)
अणु
	वापस clnt->proto_version == p9_proto_2000u;
पूर्ण
EXPORT_SYMBOL(p9_is_proto_करोtu);

पूर्णांक p9_show_client_options(काष्ठा seq_file *m, काष्ठा p9_client *clnt)
अणु
	अगर (clnt->msize != 8192)
		seq_म_लिखो(m, ",msize=%u", clnt->msize);
	seq_म_लिखो(m, ",trans=%s", clnt->trans_mod->name);

	चयन (clnt->proto_version) अणु
	हाल p9_proto_legacy:
		seq_माला_दो(m, ",noextend");
		अवरोध;
	हाल p9_proto_2000u:
		seq_माला_दो(m, ",version=9p2000.u");
		अवरोध;
	हाल p9_proto_2000L:
		/* Default */
		अवरोध;
	पूर्ण

	अगर (clnt->trans_mod->show_options)
		वापस clnt->trans_mod->show_options(m, clnt);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(p9_show_client_options);

/*
 * Some error codes are taken directly from the server replies,
 * make sure they are valid.
 */
अटल पूर्णांक safe_त्रुटि_सं(पूर्णांक err)
अणु
	अगर ((err > 0) || (err < -MAX_ERRNO)) अणु
		p9_debug(P9_DEBUG_ERROR, "Invalid error code %d\n", err);
		वापस -EPROTO;
	पूर्ण
	वापस err;
पूर्ण


/* Interpret mount option क्रम protocol version */
अटल पूर्णांक get_protocol_version(अक्षर *s)
अणु
	पूर्णांक version = -EINVAL;

	अगर (!म_भेद(s, "9p2000")) अणु
		version = p9_proto_legacy;
		p9_debug(P9_DEBUG_9P, "Protocol version: Legacy\n");
	पूर्ण अन्यथा अगर (!म_भेद(s, "9p2000.u")) अणु
		version = p9_proto_2000u;
		p9_debug(P9_DEBUG_9P, "Protocol version: 9P2000.u\n");
	पूर्ण अन्यथा अगर (!म_भेद(s, "9p2000.L")) अणु
		version = p9_proto_2000L;
		p9_debug(P9_DEBUG_9P, "Protocol version: 9P2000.L\n");
	पूर्ण अन्यथा
		pr_info("Unknown protocol version %s\n", s);

	वापस version;
पूर्ण

/**
 * parse_opts - parse mount options पूर्णांकo client काष्ठाure
 * @opts: options string passed from mount
 * @clnt: existing v9fs client inक्रमmation
 *
 * Return 0 upon success, -ERRNO upon failure
 */

अटल पूर्णांक parse_opts(अक्षर *opts, काष्ठा p9_client *clnt)
अणु
	अक्षर *options, *पंचांगp_options;
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक option;
	अक्षर *s;
	पूर्णांक ret = 0;

	clnt->proto_version = p9_proto_2000L;
	clnt->msize = 8192;

	अगर (!opts)
		वापस 0;

	पंचांगp_options = kstrdup(opts, GFP_KERNEL);
	अगर (!पंचांगp_options) अणु
		p9_debug(P9_DEBUG_ERROR,
			 "failed to allocate copy of option string\n");
		वापस -ENOMEM;
	पूर्ण
	options = पंचांगp_options;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token, r;
		अगर (!*p)
			जारी;
		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_msize:
			r = match_पूर्णांक(&args[0], &option);
			अगर (r < 0) अणु
				p9_debug(P9_DEBUG_ERROR,
					 "integer field, but no integer?\n");
				ret = r;
				जारी;
			पूर्ण
			अगर (option < 4096) अणु
				p9_debug(P9_DEBUG_ERROR,
					 "msize should be at least 4k\n");
				ret = -EINVAL;
				जारी;
			पूर्ण
			clnt->msize = option;
			अवरोध;
		हाल Opt_trans:
			s = match_strdup(&args[0]);
			अगर (!s) अणु
				ret = -ENOMEM;
				p9_debug(P9_DEBUG_ERROR,
					 "problem allocating copy of trans arg\n");
				जाओ मुक्त_and_वापस;
			पूर्ण

			v9fs_put_trans(clnt->trans_mod);
			clnt->trans_mod = v9fs_get_trans_by_name(s);
			अगर (clnt->trans_mod == शून्य) अणु
				pr_info("Could not find request transport: %s\n",
					s);
				ret = -EINVAL;
			पूर्ण
			kमुक्त(s);
			अवरोध;
		हाल Opt_legacy:
			clnt->proto_version = p9_proto_legacy;
			अवरोध;
		हाल Opt_version:
			s = match_strdup(&args[0]);
			अगर (!s) अणु
				ret = -ENOMEM;
				p9_debug(P9_DEBUG_ERROR,
					 "problem allocating copy of version arg\n");
				जाओ मुक्त_and_वापस;
			पूर्ण
			r = get_protocol_version(s);
			अगर (r < 0)
				ret = r;
			अन्यथा
				clnt->proto_version = r;
			kमुक्त(s);
			अवरोध;
		शेष:
			जारी;
		पूर्ण
	पूर्ण

मुक्त_and_वापस:
	अगर (ret)
		v9fs_put_trans(clnt->trans_mod);
	kमुक्त(पंचांगp_options);
	वापस ret;
पूर्ण

अटल पूर्णांक p9_fcall_init(काष्ठा p9_client *c, काष्ठा p9_fcall *fc,
			 पूर्णांक alloc_msize)
अणु
	अगर (likely(c->fcall_cache) && alloc_msize == c->msize) अणु
		fc->sdata = kmem_cache_alloc(c->fcall_cache, GFP_NOFS);
		fc->cache = c->fcall_cache;
	पूर्ण अन्यथा अणु
		fc->sdata = kदो_स्मृति(alloc_msize, GFP_NOFS);
		fc->cache = शून्य;
	पूर्ण
	अगर (!fc->sdata)
		वापस -ENOMEM;
	fc->capacity = alloc_msize;
	वापस 0;
पूर्ण

व्योम p9_fcall_fini(काष्ठा p9_fcall *fc)
अणु
	/* sdata can be शून्य क्रम पूर्णांकerrupted requests in trans_rdma,
	 * and kmem_cache_मुक्त करोes not करो शून्य-check क्रम us
	 */
	अगर (unlikely(!fc->sdata))
		वापस;

	अगर (fc->cache)
		kmem_cache_मुक्त(fc->cache, fc->sdata);
	अन्यथा
		kमुक्त(fc->sdata);
पूर्ण
EXPORT_SYMBOL(p9_fcall_fini);

अटल काष्ठा kmem_cache *p9_req_cache;

/**
 * p9_tag_alloc - Allocate a new request.
 * @c: Client session.
 * @type: Transaction type.
 * @max_size: Maximum packet size क्रम this request.
 *
 * Context: Process context.
 * Return: Poपूर्णांकer to new request.
 */
अटल काष्ठा p9_req_t *
p9_tag_alloc(काष्ठा p9_client *c, पूर्णांक8_t type, अचिन्हित पूर्णांक max_size)
अणु
	काष्ठा p9_req_t *req = kmem_cache_alloc(p9_req_cache, GFP_NOFS);
	पूर्णांक alloc_msize = min(c->msize, max_size);
	पूर्णांक tag;

	अगर (!req)
		वापस ERR_PTR(-ENOMEM);

	अगर (p9_fcall_init(c, &req->tc, alloc_msize))
		जाओ मुक्त_req;
	अगर (p9_fcall_init(c, &req->rc, alloc_msize))
		जाओ मुक्त;

	p9pdu_reset(&req->tc);
	p9pdu_reset(&req->rc);
	req->t_err = 0;
	req->status = REQ_STATUS_ALLOC;
	init_रुकोqueue_head(&req->wq);
	INIT_LIST_HEAD(&req->req_list);

	idr_preload(GFP_NOFS);
	spin_lock_irq(&c->lock);
	अगर (type == P9_TVERSION)
		tag = idr_alloc(&c->reqs, req, P9_NOTAG, P9_NOTAG + 1,
				GFP_NOWAIT);
	अन्यथा
		tag = idr_alloc(&c->reqs, req, 0, P9_NOTAG, GFP_NOWAIT);
	req->tc.tag = tag;
	spin_unlock_irq(&c->lock);
	idr_preload_end();
	अगर (tag < 0)
		जाओ मुक्त;

	/* Init ref to two because in the general हाल there is one ref
	 * that is put asynchronously by a ग_लिखोr thपढ़ो, one ref
	 * temporarily given by p9_tag_lookup and put by p9_client_cb
	 * in the recv thपढ़ो, and one ref put by p9_tag_हटाओ in the
	 * मुख्य thपढ़ो. The only exception is virtio that करोes not use
	 * p9_tag_lookup but करोes not have a ग_लिखोr thपढ़ो either
	 * (the ग_लिखो happens synchronously in the request/zc_request
	 * callback), so p9_client_cb eats the second ref there
	 * as the poपूर्णांकer is duplicated directly by virtqueue_add_sgs()
	 */
	refcount_set(&req->refcount.refcount, 2);

	वापस req;

मुक्त:
	p9_fcall_fini(&req->tc);
	p9_fcall_fini(&req->rc);
मुक्त_req:
	kmem_cache_मुक्त(p9_req_cache, req);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/**
 * p9_tag_lookup - Look up a request by tag.
 * @c: Client session.
 * @tag: Transaction ID.
 *
 * Context: Any context.
 * Return: A request, or %शून्य अगर there is no request with that tag.
 */
काष्ठा p9_req_t *p9_tag_lookup(काष्ठा p9_client *c, u16 tag)
अणु
	काष्ठा p9_req_t *req;

	rcu_पढ़ो_lock();
again:
	req = idr_find(&c->reqs, tag);
	अगर (req) अणु
		/* We have to be careful with the req found under rcu_पढ़ो_lock
		 * Thanks to SLAB_TYPESAFE_BY_RCU we can safely try to get the
		 * ref again without corrupting other data, then check again
		 * that the tag matches once we have the ref
		 */
		अगर (!p9_req_try_get(req))
			जाओ again;
		अगर (req->tc.tag != tag) अणु
			p9_req_put(req);
			जाओ again;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस req;
पूर्ण
EXPORT_SYMBOL(p9_tag_lookup);

/**
 * p9_tag_हटाओ - Remove a tag.
 * @c: Client session.
 * @r: Request of reference.
 *
 * Context: Any context.
 */
अटल पूर्णांक p9_tag_हटाओ(काष्ठा p9_client *c, काष्ठा p9_req_t *r)
अणु
	अचिन्हित दीर्घ flags;
	u16 tag = r->tc.tag;

	p9_debug(P9_DEBUG_MUX, "clnt %p req %p tag: %d\n", c, r, tag);
	spin_lock_irqsave(&c->lock, flags);
	idr_हटाओ(&c->reqs, tag);
	spin_unlock_irqrestore(&c->lock, flags);
	वापस p9_req_put(r);
पूर्ण

अटल व्योम p9_req_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा p9_req_t *r = container_of(ref, काष्ठा p9_req_t, refcount);
	p9_fcall_fini(&r->tc);
	p9_fcall_fini(&r->rc);
	kmem_cache_मुक्त(p9_req_cache, r);
पूर्ण

पूर्णांक p9_req_put(काष्ठा p9_req_t *r)
अणु
	वापस kref_put(&r->refcount, p9_req_मुक्त);
पूर्ण
EXPORT_SYMBOL(p9_req_put);

/**
 * p9_tag_cleanup - cleans up tags काष्ठाure and reclaims resources
 * @c:  v9fs client काष्ठा
 *
 * This मुक्तs resources associated with the tags काष्ठाure
 *
 */
अटल व्योम p9_tag_cleanup(काष्ठा p9_client *c)
अणु
	काष्ठा p9_req_t *req;
	पूर्णांक id;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&c->reqs, req, id) अणु
		pr_info("Tag %d still in use\n", id);
		अगर (p9_tag_हटाओ(c, req) == 0)
			pr_warn("Packet with tag %d has still references",
				req->tc.tag);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * p9_client_cb - call back from transport to client
 * @c: client state
 * @req: request received
 * @status: request status, one of REQ_STATUS_*
 *
 */
व्योम p9_client_cb(काष्ठा p9_client *c, काष्ठा p9_req_t *req, पूर्णांक status)
अणु
	p9_debug(P9_DEBUG_MUX, " tag %d\n", req->tc.tag);

	/*
	 * This barrier is needed to make sure any change made to req beक्रमe
	 * the status change is visible to another thपढ़ो
	 */
	smp_wmb();
	req->status = status;

	wake_up(&req->wq);
	p9_debug(P9_DEBUG_MUX, "wakeup: %d\n", req->tc.tag);
	p9_req_put(req);
पूर्ण
EXPORT_SYMBOL(p9_client_cb);

/**
 * p9_parse_header - parse header arguments out of a packet
 * @pdu: packet to parse
 * @size: size of packet
 * @type: type of request
 * @tag: tag of packet
 * @शुरुआत: set अगर we need to शुरुआत offset afterwards
 */

पूर्णांक
p9_parse_header(काष्ठा p9_fcall *pdu, पूर्णांक32_t *size, पूर्णांक8_t *type, पूर्णांक16_t *tag,
								पूर्णांक शुरुआत)
अणु
	पूर्णांक8_t r_type;
	पूर्णांक16_t r_tag;
	पूर्णांक32_t r_size;
	पूर्णांक offset = pdu->offset;
	पूर्णांक err;

	pdu->offset = 0;

	err = p9pdu_पढ़ोf(pdu, 0, "dbw", &r_size, &r_type, &r_tag);
	अगर (err)
		जाओ शुरुआत_and_निकास;

	अगर (type)
		*type = r_type;
	अगर (tag)
		*tag = r_tag;
	अगर (size)
		*size = r_size;

	अगर (pdu->size != r_size || r_size < 7) अणु
		err = -EINVAL;
		जाओ शुरुआत_and_निकास;
	पूर्ण

	pdu->id = r_type;
	pdu->tag = r_tag;

	p9_debug(P9_DEBUG_9P, "<<< size=%d type: %d tag: %d\n",
		 pdu->size, pdu->id, pdu->tag);

शुरुआत_and_निकास:
	अगर (शुरुआत)
		pdu->offset = offset;
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_parse_header);

/**
 * p9_check_errors - check 9p packet क्रम error वापस and process it
 * @c: current client instance
 * @req: request to parse and check क्रम error conditions
 *
 * वापसs error code अगर one is discovered, otherwise वापसs 0
 *
 * this will have to be more complicated अगर we have multiple
 * error packet types
 */

अटल पूर्णांक p9_check_errors(काष्ठा p9_client *c, काष्ठा p9_req_t *req)
अणु
	पूर्णांक8_t type;
	पूर्णांक err;
	पूर्णांक ecode;

	err = p9_parse_header(&req->rc, शून्य, &type, शून्य, 0);
	अगर (req->rc.size >= c->msize) अणु
		p9_debug(P9_DEBUG_ERROR,
			 "requested packet size too big: %d\n",
			 req->rc.size);
		वापस -EIO;
	पूर्ण
	/*
	 * dump the response from server
	 * This should be after check errors which poplulate pdu_fcall.
	 */
	trace_9p_protocol_dump(c, &req->rc);
	अगर (err) अणु
		p9_debug(P9_DEBUG_ERROR, "couldn't parse header %d\n", err);
		वापस err;
	पूर्ण
	अगर (type != P9_RERROR && type != P9_RLERROR)
		वापस 0;

	अगर (!p9_is_proto_करोtl(c)) अणु
		अक्षर *ename;
		err = p9pdu_पढ़ोf(&req->rc, c->proto_version, "s?d",
				  &ename, &ecode);
		अगर (err)
			जाओ out_err;

		अगर (p9_is_proto_करोtu(c) && ecode < 512)
			err = -ecode;

		अगर (!err) अणु
			err = p9_errstr2त्रुटि_सं(ename, म_माप(ename));

			p9_debug(P9_DEBUG_9P, "<<< RERROR (%d) %s\n",
				 -ecode, ename);
		पूर्ण
		kमुक्त(ename);
	पूर्ण अन्यथा अणु
		err = p9pdu_पढ़ोf(&req->rc, c->proto_version, "d", &ecode);
		err = -ecode;

		p9_debug(P9_DEBUG_9P, "<<< RLERROR (%d)\n", -ecode);
	पूर्ण

	वापस err;

out_err:
	p9_debug(P9_DEBUG_ERROR, "couldn't parse error%d\n", err);

	वापस err;
पूर्ण

/**
 * p9_check_zc_errors - check 9p packet क्रम error वापस and process it
 * @c: current client instance
 * @req: request to parse and check क्रम error conditions
 * @uidata: बाह्यal buffer containing error
 * @in_hdrlen: Size of response protocol buffer.
 *
 * वापसs error code अगर one is discovered, otherwise वापसs 0
 *
 * this will have to be more complicated अगर we have multiple
 * error packet types
 */

अटल पूर्णांक p9_check_zc_errors(काष्ठा p9_client *c, काष्ठा p9_req_t *req,
			      काष्ठा iov_iter *uidata, पूर्णांक in_hdrlen)
अणु
	पूर्णांक err;
	पूर्णांक ecode;
	पूर्णांक8_t type;
	अक्षर *ename = शून्य;

	err = p9_parse_header(&req->rc, शून्य, &type, शून्य, 0);
	/*
	 * dump the response from server
	 * This should be after parse_header which poplulate pdu_fcall.
	 */
	trace_9p_protocol_dump(c, &req->rc);
	अगर (err) अणु
		p9_debug(P9_DEBUG_ERROR, "couldn't parse header %d\n", err);
		वापस err;
	पूर्ण

	अगर (type != P9_RERROR && type != P9_RLERROR)
		वापस 0;

	अगर (!p9_is_proto_करोtl(c)) अणु
		/* Error is reported in string क्रमmat */
		पूर्णांक len;
		/* 7 = header size क्रम RERROR; */
		पूर्णांक अंतरभूत_len = in_hdrlen - 7;

		len = req->rc.size - req->rc.offset;
		अगर (len > (P9_ZC_HDR_SZ - 7)) अणु
			err = -EFAULT;
			जाओ out_err;
		पूर्ण

		ename = &req->rc.sdata[req->rc.offset];
		अगर (len > अंतरभूत_len) अणु
			/* We have error in बाह्यal buffer */
			अगर (!copy_from_iter_full(ename + अंतरभूत_len,
					     len - अंतरभूत_len, uidata)) अणु
				err = -EFAULT;
				जाओ out_err;
			पूर्ण
		पूर्ण
		ename = शून्य;
		err = p9pdu_पढ़ोf(&req->rc, c->proto_version, "s?d",
				  &ename, &ecode);
		अगर (err)
			जाओ out_err;

		अगर (p9_is_proto_करोtu(c) && ecode < 512)
			err = -ecode;

		अगर (!err) अणु
			err = p9_errstr2त्रुटि_सं(ename, म_माप(ename));

			p9_debug(P9_DEBUG_9P, "<<< RERROR (%d) %s\n",
				 -ecode, ename);
		पूर्ण
		kमुक्त(ename);
	पूर्ण अन्यथा अणु
		err = p9pdu_पढ़ोf(&req->rc, c->proto_version, "d", &ecode);
		err = -ecode;

		p9_debug(P9_DEBUG_9P, "<<< RLERROR (%d)\n", -ecode);
	पूर्ण
	वापस err;

out_err:
	p9_debug(P9_DEBUG_ERROR, "couldn't parse error%d\n", err);
	वापस err;
पूर्ण

अटल काष्ठा p9_req_t *
p9_client_rpc(काष्ठा p9_client *c, पूर्णांक8_t type, स्थिर अक्षर *fmt, ...);

/**
 * p9_client_flush - flush (cancel) a request
 * @c: client state
 * @oldreq: request to cancel
 *
 * This sents a flush क्रम a particular request and links
 * the flush request to the original request.  The current
 * code only supports a single flush request although the protocol
 * allows क्रम multiple flush requests to be sent क्रम a single request.
 *
 */

अटल पूर्णांक p9_client_flush(काष्ठा p9_client *c, काष्ठा p9_req_t *oldreq)
अणु
	काष्ठा p9_req_t *req;
	पूर्णांक16_t oldtag;
	पूर्णांक err;

	err = p9_parse_header(&oldreq->tc, शून्य, शून्य, &oldtag, 1);
	अगर (err)
		वापस err;

	p9_debug(P9_DEBUG_9P, ">>> TFLUSH tag %d\n", oldtag);

	req = p9_client_rpc(c, P9_TFLUSH, "w", oldtag);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	/*
	 * अगर we haven't received a response क्रम oldreq,
	 * हटाओ it from the list
	 */
	अगर (oldreq->status == REQ_STATUS_SENT) अणु
		अगर (c->trans_mod->cancelled)
			c->trans_mod->cancelled(c, oldreq);
	पूर्ण

	p9_tag_हटाओ(c, req);
	वापस 0;
पूर्ण

अटल काष्ठा p9_req_t *p9_client_prepare_req(काष्ठा p9_client *c,
					      पूर्णांक8_t type, पूर्णांक req_size,
					      स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	पूर्णांक err;
	काष्ठा p9_req_t *req;

	p9_debug(P9_DEBUG_MUX, "client %p op %d\n", c, type);

	/* we allow क्रम any status other than disconnected */
	अगर (c->status == Disconnected)
		वापस ERR_PTR(-EIO);

	/* अगर status is begin_disconnected we allow only clunk request */
	अगर ((c->status == BeginDisconnect) && (type != P9_TCLUNK))
		वापस ERR_PTR(-EIO);

	req = p9_tag_alloc(c, type, req_size);
	अगर (IS_ERR(req))
		वापस req;

	/* marshall the data */
	p9pdu_prepare(&req->tc, req->tc.tag, type);
	err = p9pdu_vग_लिखोf(&req->tc, c->proto_version, fmt, ap);
	अगर (err)
		जाओ reterr;
	p9pdu_finalize(c, &req->tc);
	trace_9p_client_req(c, type, req->tc.tag);
	वापस req;
reterr:
	p9_tag_हटाओ(c, req);
	/* We have to put also the 2nd reference as it won't be used */
	p9_req_put(req);
	वापस ERR_PTR(err);
पूर्ण

/**
 * p9_client_rpc - issue a request and रुको क्रम a response
 * @c: client session
 * @type: type of request
 * @fmt: protocol क्रमmat string (see protocol.c)
 *
 * Returns request काष्ठाure (which client must मुक्त using p9_tag_हटाओ)
 */

अटल काष्ठा p9_req_t *
p9_client_rpc(काष्ठा p9_client *c, पूर्णांक8_t type, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक संक_बाकी, err;
	अचिन्हित दीर्घ flags;
	काष्ठा p9_req_t *req;

	बहु_शुरू(ap, fmt);
	req = p9_client_prepare_req(c, type, c->msize, fmt, ap);
	बहु_पूर्ण(ap);
	अगर (IS_ERR(req))
		वापस req;

	अगर (संकेत_pending(current)) अणु
		संक_बाकी = 1;
		clear_thपढ़ो_flag(TIF_SIGPENDING);
	पूर्ण अन्यथा
		संक_बाकी = 0;

	err = c->trans_mod->request(c, req);
	अगर (err < 0) अणु
		/* ग_लिखो won't happen */
		p9_req_put(req);
		अगर (err != -ERESTARTSYS && err != -EFAULT)
			c->status = Disconnected;
		जाओ recalc_संक_बाकी;
	पूर्ण
again:
	/* Wait क्रम the response */
	err = रुको_event_समाप्तable(req->wq, req->status >= REQ_STATUS_RCVD);

	/*
	 * Make sure our req is coherent with regard to updates in other
	 * thपढ़ोs - echoes to wmb() in the callback
	 */
	smp_rmb();

	अगर ((err == -ERESTARTSYS) && (c->status == Connected)
				  && (type == P9_TFLUSH)) अणु
		संक_बाकी = 1;
		clear_thपढ़ो_flag(TIF_SIGPENDING);
		जाओ again;
	पूर्ण

	अगर (req->status == REQ_STATUS_ERROR) अणु
		p9_debug(P9_DEBUG_ERROR, "req_status error %d\n", req->t_err);
		err = req->t_err;
	पूर्ण
	अगर ((err == -ERESTARTSYS) && (c->status == Connected)) अणु
		p9_debug(P9_DEBUG_MUX, "flushing\n");
		संक_बाकी = 1;
		clear_thपढ़ो_flag(TIF_SIGPENDING);

		अगर (c->trans_mod->cancel(c, req))
			p9_client_flush(c, req);

		/* अगर we received the response anyway, करोn't संकेत error */
		अगर (req->status == REQ_STATUS_RCVD)
			err = 0;
	पूर्ण
recalc_संक_बाकी:
	अगर (संक_बाकी) अणु
		spin_lock_irqsave(&current->sighand->siglock, flags);
		recalc_संक_बाकी();
		spin_unlock_irqrestore(&current->sighand->siglock, flags);
	पूर्ण
	अगर (err < 0)
		जाओ reterr;

	err = p9_check_errors(c, req);
	trace_9p_client_res(c, type, req->rc.tag, err);
	अगर (!err)
		वापस req;
reterr:
	p9_tag_हटाओ(c, req);
	वापस ERR_PTR(safe_त्रुटि_सं(err));
पूर्ण

/**
 * p9_client_zc_rpc - issue a request and रुको क्रम a response
 * @c: client session
 * @type: type of request
 * @uidata: destination क्रम zero copy पढ़ो
 * @uodata: source क्रम zero copy ग_लिखो
 * @inlen: पढ़ो buffer size
 * @olen: ग_लिखो buffer size
 * @in_hdrlen: पढ़ोer header size, This is the size of response protocol data
 * @fmt: protocol क्रमmat string (see protocol.c)
 *
 * Returns request काष्ठाure (which client must मुक्त using p9_tag_हटाओ)
 */
अटल काष्ठा p9_req_t *p9_client_zc_rpc(काष्ठा p9_client *c, पूर्णांक8_t type,
					 काष्ठा iov_iter *uidata,
					 काष्ठा iov_iter *uodata,
					 पूर्णांक inlen, पूर्णांक olen, पूर्णांक in_hdrlen,
					 स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक संक_बाकी, err;
	अचिन्हित दीर्घ flags;
	काष्ठा p9_req_t *req;

	बहु_शुरू(ap, fmt);
	/*
	 * We allocate a अंतरभूत protocol data of only 4k bytes.
	 * The actual content is passed in zero-copy fashion.
	 */
	req = p9_client_prepare_req(c, type, P9_ZC_HDR_SZ, fmt, ap);
	बहु_पूर्ण(ap);
	अगर (IS_ERR(req))
		वापस req;

	अगर (संकेत_pending(current)) अणु
		संक_बाकी = 1;
		clear_thपढ़ो_flag(TIF_SIGPENDING);
	पूर्ण अन्यथा
		संक_बाकी = 0;

	err = c->trans_mod->zc_request(c, req, uidata, uodata,
				       inlen, olen, in_hdrlen);
	अगर (err < 0) अणु
		अगर (err == -EIO)
			c->status = Disconnected;
		अगर (err != -ERESTARTSYS)
			जाओ recalc_संक_बाकी;
	पूर्ण
	अगर (req->status == REQ_STATUS_ERROR) अणु
		p9_debug(P9_DEBUG_ERROR, "req_status error %d\n", req->t_err);
		err = req->t_err;
	पूर्ण
	अगर ((err == -ERESTARTSYS) && (c->status == Connected)) अणु
		p9_debug(P9_DEBUG_MUX, "flushing\n");
		संक_बाकी = 1;
		clear_thपढ़ो_flag(TIF_SIGPENDING);

		अगर (c->trans_mod->cancel(c, req))
			p9_client_flush(c, req);

		/* अगर we received the response anyway, करोn't संकेत error */
		अगर (req->status == REQ_STATUS_RCVD)
			err = 0;
	पूर्ण
recalc_संक_बाकी:
	अगर (संक_बाकी) अणु
		spin_lock_irqsave(&current->sighand->siglock, flags);
		recalc_संक_बाकी();
		spin_unlock_irqrestore(&current->sighand->siglock, flags);
	पूर्ण
	अगर (err < 0)
		जाओ reterr;

	err = p9_check_zc_errors(c, req, uidata, in_hdrlen);
	trace_9p_client_res(c, type, req->rc.tag, err);
	अगर (!err)
		वापस req;
reterr:
	p9_tag_हटाओ(c, req);
	वापस ERR_PTR(safe_त्रुटि_सं(err));
पूर्ण

अटल काष्ठा p9_fid *p9_fid_create(काष्ठा p9_client *clnt)
अणु
	पूर्णांक ret;
	काष्ठा p9_fid *fid;

	p9_debug(P9_DEBUG_FID, "clnt %p\n", clnt);
	fid = kदो_स्मृति(माप(काष्ठा p9_fid), GFP_KERNEL);
	अगर (!fid)
		वापस शून्य;

	स_रखो(&fid->qid, 0, माप(काष्ठा p9_qid));
	fid->mode = -1;
	fid->uid = current_fsuid();
	fid->clnt = clnt;
	fid->rdir = शून्य;
	fid->fid = 0;
	refcount_set(&fid->count, 1);

	idr_preload(GFP_KERNEL);
	spin_lock_irq(&clnt->lock);
	ret = idr_alloc_u32(&clnt->fids, fid, &fid->fid, P9_NOFID - 1,
			    GFP_NOWAIT);
	spin_unlock_irq(&clnt->lock);
	idr_preload_end();
	अगर (!ret)
		वापस fid;

	kमुक्त(fid);
	वापस शून्य;
पूर्ण

अटल व्योम p9_fid_destroy(काष्ठा p9_fid *fid)
अणु
	काष्ठा p9_client *clnt;
	अचिन्हित दीर्घ flags;

	p9_debug(P9_DEBUG_FID, "fid %d\n", fid->fid);
	clnt = fid->clnt;
	spin_lock_irqsave(&clnt->lock, flags);
	idr_हटाओ(&clnt->fids, fid->fid);
	spin_unlock_irqrestore(&clnt->lock, flags);
	kमुक्त(fid->rdir);
	kमुक्त(fid);
पूर्ण

अटल पूर्णांक p9_client_version(काष्ठा p9_client *c)
अणु
	पूर्णांक err = 0;
	काष्ठा p9_req_t *req;
	अक्षर *version = शून्य;
	पूर्णांक msize;

	p9_debug(P9_DEBUG_9P, ">>> TVERSION msize %d protocol %d\n",
		 c->msize, c->proto_version);

	चयन (c->proto_version) अणु
	हाल p9_proto_2000L:
		req = p9_client_rpc(c, P9_TVERSION, "ds",
					c->msize, "9P2000.L");
		अवरोध;
	हाल p9_proto_2000u:
		req = p9_client_rpc(c, P9_TVERSION, "ds",
					c->msize, "9P2000.u");
		अवरोध;
	हाल p9_proto_legacy:
		req = p9_client_rpc(c, P9_TVERSION, "ds",
					c->msize, "9P2000");
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	err = p9pdu_पढ़ोf(&req->rc, c->proto_version, "ds", &msize, &version);
	अगर (err) अणु
		p9_debug(P9_DEBUG_9P, "version error %d\n", err);
		trace_9p_protocol_dump(c, &req->rc);
		जाओ error;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RVERSION msize %d %s\n", msize, version);
	अगर (!म_भेदन(version, "9P2000.L", 8))
		c->proto_version = p9_proto_2000L;
	अन्यथा अगर (!म_भेदन(version, "9P2000.u", 8))
		c->proto_version = p9_proto_2000u;
	अन्यथा अगर (!म_भेदन(version, "9P2000", 6))
		c->proto_version = p9_proto_legacy;
	अन्यथा अणु
		p9_debug(P9_DEBUG_ERROR,
			 "server returned an unknown version: %s\n", version);
		err = -EREMOTEIO;
		जाओ error;
	पूर्ण

	अगर (msize < 4096) अणु
		p9_debug(P9_DEBUG_ERROR,
			 "server returned a msize < 4096: %d\n", msize);
		err = -EREMOTEIO;
		जाओ error;
	पूर्ण
	अगर (msize < c->msize)
		c->msize = msize;

error:
	kमुक्त(version);
	p9_tag_हटाओ(c, req);

	वापस err;
पूर्ण

काष्ठा p9_client *p9_client_create(स्थिर अक्षर *dev_name, अक्षर *options)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	अक्षर *client_id;

	err = 0;
	clnt = kदो_स्मृति(माप(काष्ठा p9_client), GFP_KERNEL);
	अगर (!clnt)
		वापस ERR_PTR(-ENOMEM);

	clnt->trans_mod = शून्य;
	clnt->trans = शून्य;
	clnt->fcall_cache = शून्य;

	client_id = utsname()->nodename;
	स_नकल(clnt->name, client_id, म_माप(client_id) + 1);

	spin_lock_init(&clnt->lock);
	idr_init(&clnt->fids);
	idr_init(&clnt->reqs);

	err = parse_opts(options, clnt);
	अगर (err < 0)
		जाओ मुक्त_client;

	अगर (!clnt->trans_mod)
		clnt->trans_mod = v9fs_get_शेष_trans();

	अगर (clnt->trans_mod == शून्य) अणु
		err = -EPROTONOSUPPORT;
		p9_debug(P9_DEBUG_ERROR,
			 "No transport defined or default transport\n");
		जाओ मुक्त_client;
	पूर्ण

	p9_debug(P9_DEBUG_MUX, "clnt %p trans %p msize %d protocol %d\n",
		 clnt, clnt->trans_mod, clnt->msize, clnt->proto_version);

	err = clnt->trans_mod->create(clnt, dev_name, options);
	अगर (err)
		जाओ put_trans;

	अगर (clnt->msize > clnt->trans_mod->maxsize)
		clnt->msize = clnt->trans_mod->maxsize;

	अगर (clnt->msize < 4096) अणु
		p9_debug(P9_DEBUG_ERROR,
			 "Please specify a msize of at least 4k\n");
		err = -EINVAL;
		जाओ बंद_trans;
	पूर्ण

	err = p9_client_version(clnt);
	अगर (err)
		जाओ बंद_trans;

	/* P9_HDRSZ + 4 is the smallest packet header we can have that is
	 * followed by data accessed from userspace by पढ़ो
	 */
	clnt->fcall_cache =
		kmem_cache_create_usercopy("9p-fcall-cache", clnt->msize,
					   0, 0, P9_HDRSZ + 4,
					   clnt->msize - (P9_HDRSZ + 4),
					   शून्य);

	वापस clnt;

बंद_trans:
	clnt->trans_mod->बंद(clnt);
put_trans:
	v9fs_put_trans(clnt->trans_mod);
मुक्त_client:
	kमुक्त(clnt);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(p9_client_create);

व्योम p9_client_destroy(काष्ठा p9_client *clnt)
अणु
	काष्ठा p9_fid *fid;
	पूर्णांक id;

	p9_debug(P9_DEBUG_MUX, "clnt %p\n", clnt);

	अगर (clnt->trans_mod)
		clnt->trans_mod->बंद(clnt);

	v9fs_put_trans(clnt->trans_mod);

	idr_क्रम_each_entry(&clnt->fids, fid, id) अणु
		pr_info("Found fid %d not clunked\n", fid->fid);
		p9_fid_destroy(fid);
	पूर्ण

	p9_tag_cleanup(clnt);

	kmem_cache_destroy(clnt->fcall_cache);
	kमुक्त(clnt);
पूर्ण
EXPORT_SYMBOL(p9_client_destroy);

व्योम p9_client_disconnect(काष्ठा p9_client *clnt)
अणु
	p9_debug(P9_DEBUG_9P, "clnt %p\n", clnt);
	clnt->status = Disconnected;
पूर्ण
EXPORT_SYMBOL(p9_client_disconnect);

व्योम p9_client_begin_disconnect(काष्ठा p9_client *clnt)
अणु
	p9_debug(P9_DEBUG_9P, "clnt %p\n", clnt);
	clnt->status = BeginDisconnect;
पूर्ण
EXPORT_SYMBOL(p9_client_begin_disconnect);

काष्ठा p9_fid *p9_client_attach(काष्ठा p9_client *clnt, काष्ठा p9_fid *afid,
	स्थिर अक्षर *uname, kuid_t n_uname, स्थिर अक्षर *aname)
अणु
	पूर्णांक err = 0;
	काष्ठा p9_req_t *req;
	काष्ठा p9_fid *fid;
	काष्ठा p9_qid qid;


	p9_debug(P9_DEBUG_9P, ">>> TATTACH afid %d uname %s aname %s\n",
		 afid ? afid->fid : -1, uname, aname);
	fid = p9_fid_create(clnt);
	अगर (!fid) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण
	fid->uid = n_uname;

	req = p9_client_rpc(clnt, P9_TATTACH, "ddss?u", fid->fid,
			afid ? afid->fid : P9_NOFID, uname, aname, n_uname);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "Q", &qid);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		p9_tag_हटाओ(clnt, req);
		जाओ error;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RATTACH qid %x.%llx.%x\n",
		 qid.type, (अचिन्हित दीर्घ दीर्घ)qid.path, qid.version);

	स_हटाओ(&fid->qid, &qid, माप(काष्ठा p9_qid));

	p9_tag_हटाओ(clnt, req);
	वापस fid;

error:
	अगर (fid)
		p9_fid_destroy(fid);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(p9_client_attach);

काष्ठा p9_fid *p9_client_walk(काष्ठा p9_fid *oldfid, uपूर्णांक16_t nwname,
		स्थिर अचिन्हित अक्षर * स्थिर *wnames, पूर्णांक clone)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	काष्ठा p9_fid *fid;
	काष्ठा p9_qid *wqids;
	काष्ठा p9_req_t *req;
	uपूर्णांक16_t nwqids, count;

	err = 0;
	wqids = शून्य;
	clnt = oldfid->clnt;
	अगर (clone) अणु
		fid = p9_fid_create(clnt);
		अगर (!fid) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण

		fid->uid = oldfid->uid;
	पूर्ण अन्यथा
		fid = oldfid;


	p9_debug(P9_DEBUG_9P, ">>> TWALK fids %d,%d nwname %ud wname[0] %s\n",
		 oldfid->fid, fid->fid, nwname, wnames ? wnames[0] : शून्य);
	req = p9_client_rpc(clnt, P9_TWALK, "ddT", oldfid->fid, fid->fid,
								nwname, wnames);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "R", &nwqids, &wqids);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		p9_tag_हटाओ(clnt, req);
		जाओ clunk_fid;
	पूर्ण
	p9_tag_हटाओ(clnt, req);

	p9_debug(P9_DEBUG_9P, "<<< RWALK nwqid %d:\n", nwqids);

	अगर (nwqids != nwname) अणु
		err = -ENOENT;
		जाओ clunk_fid;
	पूर्ण

	क्रम (count = 0; count < nwqids; count++)
		p9_debug(P9_DEBUG_9P, "<<<     [%d] %x.%llx.%x\n",
			count, wqids[count].type,
			(अचिन्हित दीर्घ दीर्घ)wqids[count].path,
			wqids[count].version);

	अगर (nwname)
		स_हटाओ(&fid->qid, &wqids[nwqids - 1], माप(काष्ठा p9_qid));
	अन्यथा
		स_हटाओ(&fid->qid, &oldfid->qid, माप(काष्ठा p9_qid));

	kमुक्त(wqids);
	वापस fid;

clunk_fid:
	kमुक्त(wqids);
	p9_client_clunk(fid);
	fid = शून्य;

error:
	अगर (fid && (fid != oldfid))
		p9_fid_destroy(fid);

	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(p9_client_walk);

पूर्णांक p9_client_खोलो(काष्ठा p9_fid *fid, पूर्णांक mode)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;
	काष्ठा p9_qid qid;
	पूर्णांक iounit;

	clnt = fid->clnt;
	p9_debug(P9_DEBUG_9P, ">>> %s fid %d mode %d\n",
		p9_is_proto_करोtl(clnt) ? "TLOPEN" : "TOPEN", fid->fid, mode);
	err = 0;

	अगर (fid->mode != -1)
		वापस -EINVAL;

	अगर (p9_is_proto_करोtl(clnt))
		req = p9_client_rpc(clnt, P9_TLOPEN, "dd", fid->fid, mode);
	अन्यथा
		req = p9_client_rpc(clnt, P9_TOPEN, "db", fid->fid, mode);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "Qd", &qid, &iounit);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		जाओ मुक्त_and_error;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< %s qid %x.%llx.%x iounit %x\n",
		p9_is_proto_करोtl(clnt) ? "RLOPEN" : "ROPEN",  qid.type,
		(अचिन्हित दीर्घ दीर्घ)qid.path, qid.version, iounit);

	स_हटाओ(&fid->qid, &qid, माप(काष्ठा p9_qid));
	fid->mode = mode;
	fid->iounit = iounit;

मुक्त_and_error:
	p9_tag_हटाओ(clnt, req);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_खोलो);

पूर्णांक p9_client_create_करोtl(काष्ठा p9_fid *ofid, स्थिर अक्षर *name, u32 flags, u32 mode,
		kgid_t gid, काष्ठा p9_qid *qid)
अणु
	पूर्णांक err = 0;
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;
	पूर्णांक iounit;

	p9_debug(P9_DEBUG_9P,
			">>> TLCREATE fid %d name %s flags %d mode %d gid %d\n",
			ofid->fid, name, flags, mode,
		 	from_kgid(&init_user_ns, gid));
	clnt = ofid->clnt;

	अगर (ofid->mode != -1)
		वापस -EINVAL;

	req = p9_client_rpc(clnt, P9_TLCREATE, "dsddg", ofid->fid, name, flags,
			mode, gid);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "Qd", qid, &iounit);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		जाओ मुक्त_and_error;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RLCREATE qid %x.%llx.%x iounit %x\n",
			qid->type,
			(अचिन्हित दीर्घ दीर्घ)qid->path,
			qid->version, iounit);

	स_हटाओ(&ofid->qid, qid, माप(काष्ठा p9_qid));
	ofid->mode = mode;
	ofid->iounit = iounit;

मुक्त_and_error:
	p9_tag_हटाओ(clnt, req);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_create_करोtl);

पूर्णांक p9_client_fcreate(काष्ठा p9_fid *fid, स्थिर अक्षर *name, u32 perm, पूर्णांक mode,
		     अक्षर *extension)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;
	काष्ठा p9_qid qid;
	पूर्णांक iounit;

	p9_debug(P9_DEBUG_9P, ">>> TCREATE fid %d name %s perm %d mode %d\n",
						fid->fid, name, perm, mode);
	err = 0;
	clnt = fid->clnt;

	अगर (fid->mode != -1)
		वापस -EINVAL;

	req = p9_client_rpc(clnt, P9_TCREATE, "dsdb?s", fid->fid, name, perm,
				mode, extension);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "Qd", &qid, &iounit);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		जाओ मुक्त_and_error;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RCREATE qid %x.%llx.%x iounit %x\n",
				qid.type,
				(अचिन्हित दीर्घ दीर्घ)qid.path,
				qid.version, iounit);

	स_हटाओ(&fid->qid, &qid, माप(काष्ठा p9_qid));
	fid->mode = mode;
	fid->iounit = iounit;

मुक्त_and_error:
	p9_tag_हटाओ(clnt, req);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_fcreate);

पूर्णांक p9_client_symlink(काष्ठा p9_fid *dfid, स्थिर अक्षर *name,
		स्थिर अक्षर *symtgt, kgid_t gid, काष्ठा p9_qid *qid)
अणु
	पूर्णांक err = 0;
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;

	p9_debug(P9_DEBUG_9P, ">>> TSYMLINK dfid %d name %s  symtgt %s\n",
			dfid->fid, name, symtgt);
	clnt = dfid->clnt;

	req = p9_client_rpc(clnt, P9_TSYMLINK, "dssg", dfid->fid, name, symtgt,
			gid);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "Q", qid);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		जाओ मुक्त_and_error;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RSYMLINK qid %x.%llx.%x\n",
			qid->type, (अचिन्हित दीर्घ दीर्घ)qid->path, qid->version);

मुक्त_and_error:
	p9_tag_हटाओ(clnt, req);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_symlink);

पूर्णांक p9_client_link(काष्ठा p9_fid *dfid, काष्ठा p9_fid *oldfid, स्थिर अक्षर *newname)
अणु
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;

	p9_debug(P9_DEBUG_9P, ">>> TLINK dfid %d oldfid %d newname %s\n",
			dfid->fid, oldfid->fid, newname);
	clnt = dfid->clnt;
	req = p9_client_rpc(clnt, P9_TLINK, "dds", dfid->fid, oldfid->fid,
			newname);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	p9_debug(P9_DEBUG_9P, "<<< RLINK\n");
	p9_tag_हटाओ(clnt, req);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(p9_client_link);

पूर्णांक p9_client_fsync(काष्ठा p9_fid *fid, पूर्णांक datasync)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;

	p9_debug(P9_DEBUG_9P, ">>> TFSYNC fid %d datasync:%d\n",
			fid->fid, datasync);
	err = 0;
	clnt = fid->clnt;

	req = p9_client_rpc(clnt, P9_TFSYNC, "dd", fid->fid, datasync);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RFSYNC fid %d\n", fid->fid);

	p9_tag_हटाओ(clnt, req);

error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_fsync);

पूर्णांक p9_client_clunk(काष्ठा p9_fid *fid)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;
	पूर्णांक retries = 0;

	अगर (!fid || IS_ERR(fid)) अणु
		pr_warn("%s (%d): Trying to clunk with invalid fid\n",
			__func__, task_pid_nr(current));
		dump_stack();
		वापस 0;
	पूर्ण
	अगर (!refcount_dec_and_test(&fid->count))
		वापस 0;

again:
	p9_debug(P9_DEBUG_9P, ">>> TCLUNK fid %d (try %d)\n", fid->fid,
								retries);
	err = 0;
	clnt = fid->clnt;

	req = p9_client_rpc(clnt, P9_TCLUNK, "d", fid->fid);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RCLUNK fid %d\n", fid->fid);

	p9_tag_हटाओ(clnt, req);
error:
	/*
	 * Fid is not valid even after a failed clunk
	 * If पूर्णांकerrupted, retry once then give up and
	 * leak fid until umount.
	 */
	अगर (err == -ERESTARTSYS) अणु
		अगर (retries++ == 0)
			जाओ again;
	पूर्ण अन्यथा
		p9_fid_destroy(fid);
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_clunk);

पूर्णांक p9_client_हटाओ(काष्ठा p9_fid *fid)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;

	p9_debug(P9_DEBUG_9P, ">>> TREMOVE fid %d\n", fid->fid);
	err = 0;
	clnt = fid->clnt;

	req = p9_client_rpc(clnt, P9_TREMOVE, "d", fid->fid);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RREMOVE fid %d\n", fid->fid);

	p9_tag_हटाओ(clnt, req);
error:
	अगर (err == -ERESTARTSYS)
		p9_client_clunk(fid);
	अन्यथा
		p9_fid_destroy(fid);
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_हटाओ);

पूर्णांक p9_client_unlinkat(काष्ठा p9_fid *dfid, स्थिर अक्षर *name, पूर्णांक flags)
अणु
	पूर्णांक err = 0;
	काष्ठा p9_req_t *req;
	काष्ठा p9_client *clnt;

	p9_debug(P9_DEBUG_9P, ">>> TUNLINKAT fid %d %s %d\n",
		   dfid->fid, name, flags);

	clnt = dfid->clnt;
	req = p9_client_rpc(clnt, P9_TUNLINKAT, "dsd", dfid->fid, name, flags);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण
	p9_debug(P9_DEBUG_9P, "<<< RUNLINKAT fid %d %s\n", dfid->fid, name);

	p9_tag_हटाओ(clnt, req);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_unlinkat);

पूर्णांक
p9_client_पढ़ो(काष्ठा p9_fid *fid, u64 offset, काष्ठा iov_iter *to, पूर्णांक *err)
अणु
	पूर्णांक total = 0;
	*err = 0;

	जबतक (iov_iter_count(to)) अणु
		पूर्णांक count;

		count = p9_client_पढ़ो_once(fid, offset, to, err);
		अगर (!count || *err)
			अवरोध;
		offset += count;
		total += count;
	पूर्ण
	वापस total;
पूर्ण
EXPORT_SYMBOL(p9_client_पढ़ो);

पूर्णांक
p9_client_पढ़ो_once(काष्ठा p9_fid *fid, u64 offset, काष्ठा iov_iter *to,
		    पूर्णांक *err)
अणु
	काष्ठा p9_client *clnt = fid->clnt;
	काष्ठा p9_req_t *req;
	पूर्णांक count = iov_iter_count(to);
	पूर्णांक rsize, non_zc = 0;
	अक्षर *dataptr;

	*err = 0;
	p9_debug(P9_DEBUG_9P, ">>> TREAD fid %d offset %llu %d\n",
		   fid->fid, (अचिन्हित दीर्घ दीर्घ) offset, (पूर्णांक)iov_iter_count(to));

	rsize = fid->iounit;
	अगर (!rsize || rsize > clnt->msize - P9_IOHDRSZ)
		rsize = clnt->msize - P9_IOHDRSZ;

	अगर (count < rsize)
		rsize = count;

	/* Don't bother zerocopy क्रम small IO (< 1024) */
	अगर (clnt->trans_mod->zc_request && rsize > 1024) अणु
		/* response header len is 11
		 * PDU Header(7) + IO Size (4)
		 */
		req = p9_client_zc_rpc(clnt, P9_TREAD, to, शून्य, rsize,
				       0, 11, "dqd", fid->fid,
				       offset, rsize);
	पूर्ण अन्यथा अणु
		non_zc = 1;
		req = p9_client_rpc(clnt, P9_TREAD, "dqd", fid->fid, offset,
				    rsize);
	पूर्ण
	अगर (IS_ERR(req)) अणु
		*err = PTR_ERR(req);
		वापस 0;
	पूर्ण

	*err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version,
			   "D", &count, &dataptr);
	अगर (*err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		p9_tag_हटाओ(clnt, req);
		वापस 0;
	पूर्ण
	अगर (rsize < count) अणु
		pr_err("bogus RREAD count (%d > %d)\n", count, rsize);
		count = rsize;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RREAD count %d\n", count);

	अगर (non_zc) अणु
		पूर्णांक n = copy_to_iter(dataptr, count, to);

		अगर (n != count) अणु
			*err = -EFAULT;
			p9_tag_हटाओ(clnt, req);
			वापस n;
		पूर्ण
	पूर्ण अन्यथा अणु
		iov_iter_advance(to, count);
	पूर्ण
	p9_tag_हटाओ(clnt, req);
	वापस count;
पूर्ण
EXPORT_SYMBOL(p9_client_पढ़ो_once);

पूर्णांक
p9_client_ग_लिखो(काष्ठा p9_fid *fid, u64 offset, काष्ठा iov_iter *from, पूर्णांक *err)
अणु
	काष्ठा p9_client *clnt = fid->clnt;
	काष्ठा p9_req_t *req;
	पूर्णांक total = 0;
	*err = 0;

	p9_debug(P9_DEBUG_9P, ">>> TWRITE fid %d offset %llu count %zd\n",
				fid->fid, (अचिन्हित दीर्घ दीर्घ) offset,
				iov_iter_count(from));

	जबतक (iov_iter_count(from)) अणु
		पूर्णांक count = iov_iter_count(from);
		पूर्णांक rsize = fid->iounit;
		अगर (!rsize || rsize > clnt->msize-P9_IOHDRSZ)
			rsize = clnt->msize - P9_IOHDRSZ;

		अगर (count < rsize)
			rsize = count;

		/* Don't bother zerocopy क्रम small IO (< 1024) */
		अगर (clnt->trans_mod->zc_request && rsize > 1024) अणु
			req = p9_client_zc_rpc(clnt, P9_TWRITE, शून्य, from, 0,
					       rsize, P9_ZC_HDR_SZ, "dqd",
					       fid->fid, offset, rsize);
		पूर्ण अन्यथा अणु
			req = p9_client_rpc(clnt, P9_TWRITE, "dqV", fid->fid,
						    offset, rsize, from);
		पूर्ण
		अगर (IS_ERR(req)) अणु
			*err = PTR_ERR(req);
			अवरोध;
		पूर्ण

		*err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "d", &count);
		अगर (*err) अणु
			trace_9p_protocol_dump(clnt, &req->rc);
			p9_tag_हटाओ(clnt, req);
			अवरोध;
		पूर्ण
		अगर (rsize < count) अणु
			pr_err("bogus RWRITE count (%d > %d)\n", count, rsize);
			count = rsize;
		पूर्ण

		p9_debug(P9_DEBUG_9P, "<<< RWRITE count %d\n", count);

		p9_tag_हटाओ(clnt, req);
		iov_iter_advance(from, count);
		total += count;
		offset += count;
	पूर्ण
	वापस total;
पूर्ण
EXPORT_SYMBOL(p9_client_ग_लिखो);

काष्ठा p9_wstat *p9_client_stat(काष्ठा p9_fid *fid)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	काष्ठा p9_wstat *ret = kदो_स्मृति(माप(काष्ठा p9_wstat), GFP_KERNEL);
	काष्ठा p9_req_t *req;
	u16 ignored;

	p9_debug(P9_DEBUG_9P, ">>> TSTAT fid %d\n", fid->fid);

	अगर (!ret)
		वापस ERR_PTR(-ENOMEM);

	err = 0;
	clnt = fid->clnt;

	req = p9_client_rpc(clnt, P9_TSTAT, "d", fid->fid);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "wS", &ignored, ret);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		p9_tag_हटाओ(clnt, req);
		जाओ error;
	पूर्ण

	p9_debug(P9_DEBUG_9P,
		"<<< RSTAT sz=%x type=%x dev=%x qid=%x.%llx.%x\n"
		"<<<    mode=%8.8x atime=%8.8x mtime=%8.8x length=%llx\n"
		"<<<    name=%s uid=%s gid=%s muid=%s extension=(%s)\n"
		"<<<    uid=%d gid=%d n_muid=%d\n",
		ret->size, ret->type, ret->dev, ret->qid.type,
		(अचिन्हित दीर्घ दीर्घ)ret->qid.path, ret->qid.version, ret->mode,
		ret->aसमय, ret->mसमय, (अचिन्हित दीर्घ दीर्घ)ret->length,
		ret->name, ret->uid, ret->gid, ret->muid, ret->extension,
		from_kuid(&init_user_ns, ret->n_uid),
		from_kgid(&init_user_ns, ret->n_gid),
		from_kuid(&init_user_ns, ret->n_muid));

	p9_tag_हटाओ(clnt, req);
	वापस ret;

error:
	kमुक्त(ret);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(p9_client_stat);

काष्ठा p9_stat_करोtl *p9_client_getattr_करोtl(काष्ठा p9_fid *fid,
							u64 request_mask)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	काष्ठा p9_stat_करोtl *ret = kदो_स्मृति(माप(काष्ठा p9_stat_करोtl),
								GFP_KERNEL);
	काष्ठा p9_req_t *req;

	p9_debug(P9_DEBUG_9P, ">>> TGETATTR fid %d, request_mask %lld\n",
							fid->fid, request_mask);

	अगर (!ret)
		वापस ERR_PTR(-ENOMEM);

	err = 0;
	clnt = fid->clnt;

	req = p9_client_rpc(clnt, P9_TGETATTR, "dq", fid->fid, request_mask);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "A", ret);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		p9_tag_हटाओ(clnt, req);
		जाओ error;
	पूर्ण

	p9_debug(P9_DEBUG_9P,
		"<<< RGETATTR st_result_mask=%lld\n"
		"<<< qid=%x.%llx.%x\n"
		"<<< st_mode=%8.8x st_nlink=%llu\n"
		"<<< st_uid=%d st_gid=%d\n"
		"<<< st_rdev=%llx st_size=%llx st_blksize=%llu st_blocks=%llu\n"
		"<<< st_atime_sec=%lld st_atime_nsec=%lld\n"
		"<<< st_mtime_sec=%lld st_mtime_nsec=%lld\n"
		"<<< st_ctime_sec=%lld st_ctime_nsec=%lld\n"
		"<<< st_btime_sec=%lld st_btime_nsec=%lld\n"
		"<<< st_gen=%lld st_data_version=%lld\n",
		ret->st_result_mask, ret->qid.type, ret->qid.path,
		ret->qid.version, ret->st_mode, ret->st_nlink,
		from_kuid(&init_user_ns, ret->st_uid),
		from_kgid(&init_user_ns, ret->st_gid),
		ret->st_rdev, ret->st_size, ret->st_blksize,
		ret->st_blocks, ret->st_aसमय_sec, ret->st_aसमय_nsec,
		ret->st_mसमय_sec, ret->st_mसमय_nsec, ret->st_स_समय_sec,
		ret->st_स_समय_nsec, ret->st_bसमय_sec, ret->st_bसमय_nsec,
		ret->st_gen, ret->st_data_version);

	p9_tag_हटाओ(clnt, req);
	वापस ret;

error:
	kमुक्त(ret);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(p9_client_getattr_करोtl);

अटल पूर्णांक p9_client_statsize(काष्ठा p9_wstat *wst, पूर्णांक proto_version)
अणु
	पूर्णांक ret;

	/* NOTE: size shouldn't include its own length */
	/* size[2] type[2] dev[4] qid[13] */
	/* mode[4] aसमय[4] mसमय[4] length[8]*/
	/* name[s] uid[s] gid[s] muid[s] */
	ret = 2+4+13+4+4+4+8+2+2+2+2;

	अगर (wst->name)
		ret += म_माप(wst->name);
	अगर (wst->uid)
		ret += म_माप(wst->uid);
	अगर (wst->gid)
		ret += म_माप(wst->gid);
	अगर (wst->muid)
		ret += म_माप(wst->muid);

	अगर ((proto_version == p9_proto_2000u) ||
		(proto_version == p9_proto_2000L)) अणु
		ret += 2+4+4+4;	/* extension[s] n_uid[4] n_gid[4] n_muid[4] */
		अगर (wst->extension)
			ret += म_माप(wst->extension);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक p9_client_wstat(काष्ठा p9_fid *fid, काष्ठा p9_wstat *wst)
अणु
	पूर्णांक err;
	काष्ठा p9_req_t *req;
	काष्ठा p9_client *clnt;

	err = 0;
	clnt = fid->clnt;
	wst->size = p9_client_statsize(wst, clnt->proto_version);
	p9_debug(P9_DEBUG_9P, ">>> TWSTAT fid %d\n", fid->fid);
	p9_debug(P9_DEBUG_9P,
		"     sz=%x type=%x dev=%x qid=%x.%llx.%x\n"
		"     mode=%8.8x atime=%8.8x mtime=%8.8x length=%llx\n"
		"     name=%s uid=%s gid=%s muid=%s extension=(%s)\n"
		"     uid=%d gid=%d n_muid=%d\n",
		wst->size, wst->type, wst->dev, wst->qid.type,
		(अचिन्हित दीर्घ दीर्घ)wst->qid.path, wst->qid.version, wst->mode,
		wst->aसमय, wst->mसमय, (अचिन्हित दीर्घ दीर्घ)wst->length,
		wst->name, wst->uid, wst->gid, wst->muid, wst->extension,
		from_kuid(&init_user_ns, wst->n_uid),
		from_kgid(&init_user_ns, wst->n_gid),
		from_kuid(&init_user_ns, wst->n_muid));

	req = p9_client_rpc(clnt, P9_TWSTAT, "dwS", fid->fid, wst->size+2, wst);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RWSTAT fid %d\n", fid->fid);

	p9_tag_हटाओ(clnt, req);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_wstat);

पूर्णांक p9_client_setattr(काष्ठा p9_fid *fid, काष्ठा p9_iattr_करोtl *p9attr)
अणु
	पूर्णांक err;
	काष्ठा p9_req_t *req;
	काष्ठा p9_client *clnt;

	err = 0;
	clnt = fid->clnt;
	p9_debug(P9_DEBUG_9P, ">>> TSETATTR fid %d\n", fid->fid);
	p9_debug(P9_DEBUG_9P,
		"    valid=%x mode=%x uid=%d gid=%d size=%lld\n"
		"    atime_sec=%lld atime_nsec=%lld\n"
		"    mtime_sec=%lld mtime_nsec=%lld\n",
		p9attr->valid, p9attr->mode,
		from_kuid(&init_user_ns, p9attr->uid),
		from_kgid(&init_user_ns, p9attr->gid),
		p9attr->size, p9attr->aसमय_sec, p9attr->aसमय_nsec,
		p9attr->mसमय_sec, p9attr->mसमय_nsec);

	req = p9_client_rpc(clnt, P9_TSETATTR, "dI", fid->fid, p9attr);

	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण
	p9_debug(P9_DEBUG_9P, "<<< RSETATTR fid %d\n", fid->fid);
	p9_tag_हटाओ(clnt, req);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_setattr);

पूर्णांक p9_client_statfs(काष्ठा p9_fid *fid, काष्ठा p9_rstatfs *sb)
अणु
	पूर्णांक err;
	काष्ठा p9_req_t *req;
	काष्ठा p9_client *clnt;

	err = 0;
	clnt = fid->clnt;

	p9_debug(P9_DEBUG_9P, ">>> TSTATFS fid %d\n", fid->fid);

	req = p9_client_rpc(clnt, P9_TSTATFS, "d", fid->fid);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "ddqqqqqqd", &sb->type,
			  &sb->bsize, &sb->blocks, &sb->bमुक्त, &sb->bavail,
			  &sb->files, &sb->fमुक्त, &sb->fsid, &sb->namelen);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		p9_tag_हटाओ(clnt, req);
		जाओ error;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RSTATFS fid %d type 0x%lx bsize %ld "
		"blocks %llu bfree %llu bavail %llu files %llu ffree %llu "
		"fsid %llu namelen %ld\n",
		fid->fid, (दीर्घ अचिन्हित पूर्णांक)sb->type, (दीर्घ पूर्णांक)sb->bsize,
		sb->blocks, sb->bमुक्त, sb->bavail, sb->files,  sb->fमुक्त,
		sb->fsid, (दीर्घ पूर्णांक)sb->namelen);

	p9_tag_हटाओ(clnt, req);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_statfs);

पूर्णांक p9_client_नाम(काष्ठा p9_fid *fid,
		     काष्ठा p9_fid *newdirfid, स्थिर अक्षर *name)
अणु
	पूर्णांक err;
	काष्ठा p9_req_t *req;
	काष्ठा p9_client *clnt;

	err = 0;
	clnt = fid->clnt;

	p9_debug(P9_DEBUG_9P, ">>> TRENAME fid %d newdirfid %d name %s\n",
			fid->fid, newdirfid->fid, name);

	req = p9_client_rpc(clnt, P9_TRENAME, "dds", fid->fid,
			newdirfid->fid, name);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RRENAME fid %d\n", fid->fid);

	p9_tag_हटाओ(clnt, req);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_नाम);

पूर्णांक p9_client_नामat(काष्ठा p9_fid *olddirfid, स्थिर अक्षर *old_name,
		       काष्ठा p9_fid *newdirfid, स्थिर अक्षर *new_name)
अणु
	पूर्णांक err;
	काष्ठा p9_req_t *req;
	काष्ठा p9_client *clnt;

	err = 0;
	clnt = olddirfid->clnt;

	p9_debug(P9_DEBUG_9P, ">>> TRENAMEAT olddirfid %d old name %s"
		   " newdirfid %d new name %s\n", olddirfid->fid, old_name,
		   newdirfid->fid, new_name);

	req = p9_client_rpc(clnt, P9_TRENAMEAT, "dsds", olddirfid->fid,
			    old_name, newdirfid->fid, new_name);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RRENAMEAT newdirfid %d new name %s\n",
		   newdirfid->fid, new_name);

	p9_tag_हटाओ(clnt, req);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_नामat);

/*
 * An xattrwalk without @attr_name gives the fid क्रम the lisxattr namespace
 */
काष्ठा p9_fid *p9_client_xattrwalk(काष्ठा p9_fid *file_fid,
				स्थिर अक्षर *attr_name, u64 *attr_size)
अणु
	पूर्णांक err;
	काष्ठा p9_req_t *req;
	काष्ठा p9_client *clnt;
	काष्ठा p9_fid *attr_fid;

	err = 0;
	clnt = file_fid->clnt;
	attr_fid = p9_fid_create(clnt);
	अगर (!attr_fid) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण
	p9_debug(P9_DEBUG_9P,
		">>> TXATTRWALK file_fid %d, attr_fid %d name %s\n",
		file_fid->fid, attr_fid->fid, attr_name);

	req = p9_client_rpc(clnt, P9_TXATTRWALK, "dds",
			file_fid->fid, attr_fid->fid, attr_name);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण
	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "q", attr_size);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		p9_tag_हटाओ(clnt, req);
		जाओ clunk_fid;
	पूर्ण
	p9_tag_हटाओ(clnt, req);
	p9_debug(P9_DEBUG_9P, "<<<  RXATTRWALK fid %d size %llu\n",
		attr_fid->fid, *attr_size);
	वापस attr_fid;
clunk_fid:
	p9_client_clunk(attr_fid);
	attr_fid = शून्य;
error:
	अगर (attr_fid && (attr_fid != file_fid))
		p9_fid_destroy(attr_fid);

	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(p9_client_xattrwalk);

पूर्णांक p9_client_xattrcreate(काष्ठा p9_fid *fid, स्थिर अक्षर *name,
			u64 attr_size, पूर्णांक flags)
अणु
	पूर्णांक err;
	काष्ठा p9_req_t *req;
	काष्ठा p9_client *clnt;

	p9_debug(P9_DEBUG_9P,
		">>> TXATTRCREATE fid %d name  %s size %lld flag %d\n",
		fid->fid, name, (दीर्घ दीर्घ)attr_size, flags);
	err = 0;
	clnt = fid->clnt;
	req = p9_client_rpc(clnt, P9_TXATTRCREATE, "dsqd",
			fid->fid, name, attr_size, flags);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण
	p9_debug(P9_DEBUG_9P, "<<< RXATTRCREATE fid %d\n", fid->fid);
	p9_tag_हटाओ(clnt, req);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(p9_client_xattrcreate);

पूर्णांक p9_client_सूची_पढ़ो(काष्ठा p9_fid *fid, अक्षर *data, u32 count, u64 offset)
अणु
	पूर्णांक err, rsize, non_zc = 0;
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;
	अक्षर *dataptr;
	काष्ठा kvec kv = अणु.iov_base = data, .iov_len = countपूर्ण;
	काष्ठा iov_iter to;

	iov_iter_kvec(&to, READ, &kv, 1, count);

	p9_debug(P9_DEBUG_9P, ">>> TREADDIR fid %d offset %llu count %d\n",
				fid->fid, (अचिन्हित दीर्घ दीर्घ) offset, count);

	err = 0;
	clnt = fid->clnt;

	rsize = fid->iounit;
	अगर (!rsize || rsize > clnt->msize-P9_READसूचीHDRSZ)
		rsize = clnt->msize - P9_READसूचीHDRSZ;

	अगर (count < rsize)
		rsize = count;

	/* Don't bother zerocopy क्रम small IO (< 1024) */
	अगर (clnt->trans_mod->zc_request && rsize > 1024) अणु
		/*
		 * response header len is 11
		 * PDU Header(7) + IO Size (4)
		 */
		req = p9_client_zc_rpc(clnt, P9_TREADसूची, &to, शून्य, rsize, 0,
				       11, "dqd", fid->fid, offset, rsize);
	पूर्ण अन्यथा अणु
		non_zc = 1;
		req = p9_client_rpc(clnt, P9_TREADसूची, "dqd", fid->fid,
				    offset, rsize);
	पूर्ण
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ error;
	पूर्ण

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "D", &count, &dataptr);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		जाओ मुक्त_and_error;
	पूर्ण
	अगर (rsize < count) अणु
		pr_err("bogus RREADDIR count (%d > %d)\n", count, rsize);
		count = rsize;
	पूर्ण

	p9_debug(P9_DEBUG_9P, "<<< RREADDIR count %d\n", count);

	अगर (non_zc)
		स_हटाओ(data, dataptr, count);

	p9_tag_हटाओ(clnt, req);
	वापस count;

मुक्त_and_error:
	p9_tag_हटाओ(clnt, req);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_सूची_पढ़ो);

पूर्णांक p9_client_mknod_करोtl(काष्ठा p9_fid *fid, स्थिर अक्षर *name, पूर्णांक mode,
			dev_t rdev, kgid_t gid, काष्ठा p9_qid *qid)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;

	err = 0;
	clnt = fid->clnt;
	p9_debug(P9_DEBUG_9P, ">>> TMKNOD fid %d name %s mode %d major %d "
		"minor %d\n", fid->fid, name, mode, MAJOR(rdev), MINOR(rdev));
	req = p9_client_rpc(clnt, P9_TMKNOD, "dsdddg", fid->fid, name, mode,
		MAJOR(rdev), MINOR(rdev), gid);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "Q", qid);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		जाओ error;
	पूर्ण
	p9_debug(P9_DEBUG_9P, "<<< RMKNOD qid %x.%llx.%x\n", qid->type,
				(अचिन्हित दीर्घ दीर्घ)qid->path, qid->version);

error:
	p9_tag_हटाओ(clnt, req);
	वापस err;

पूर्ण
EXPORT_SYMBOL(p9_client_mknod_करोtl);

पूर्णांक p9_client_सूची_गढ़ो_करोtl(काष्ठा p9_fid *fid, स्थिर अक्षर *name, पूर्णांक mode,
				kgid_t gid, काष्ठा p9_qid *qid)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;

	err = 0;
	clnt = fid->clnt;
	p9_debug(P9_DEBUG_9P, ">>> TMKDIR fid %d name %s mode %d gid %d\n",
		 fid->fid, name, mode, from_kgid(&init_user_ns, gid));
	req = p9_client_rpc(clnt, P9_TMKसूची, "dsdg", fid->fid, name, mode,
		gid);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "Q", qid);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		जाओ error;
	पूर्ण
	p9_debug(P9_DEBUG_9P, "<<< RMKDIR qid %x.%llx.%x\n", qid->type,
				(अचिन्हित दीर्घ दीर्घ)qid->path, qid->version);

error:
	p9_tag_हटाओ(clnt, req);
	वापस err;

पूर्ण
EXPORT_SYMBOL(p9_client_सूची_गढ़ो_करोtl);

पूर्णांक p9_client_lock_करोtl(काष्ठा p9_fid *fid, काष्ठा p9_flock *flock, u8 *status)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;

	err = 0;
	clnt = fid->clnt;
	p9_debug(P9_DEBUG_9P, ">>> TLOCK fid %d type %i flags %d "
			"start %lld length %lld proc_id %d client_id %s\n",
			fid->fid, flock->type, flock->flags, flock->start,
			flock->length, flock->proc_id, flock->client_id);

	req = p9_client_rpc(clnt, P9_TLOCK, "dbdqqds", fid->fid, flock->type,
				flock->flags, flock->start, flock->length,
					flock->proc_id, flock->client_id);

	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "b", status);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		जाओ error;
	पूर्ण
	p9_debug(P9_DEBUG_9P, "<<< RLOCK status %i\n", *status);
error:
	p9_tag_हटाओ(clnt, req);
	वापस err;

पूर्ण
EXPORT_SYMBOL(p9_client_lock_करोtl);

पूर्णांक p9_client_getlock_करोtl(काष्ठा p9_fid *fid, काष्ठा p9_getlock *glock)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;

	err = 0;
	clnt = fid->clnt;
	p9_debug(P9_DEBUG_9P, ">>> TGETLOCK fid %d, type %i start %lld "
		"length %lld proc_id %d client_id %s\n", fid->fid, glock->type,
		glock->start, glock->length, glock->proc_id, glock->client_id);

	req = p9_client_rpc(clnt, P9_TGETLOCK, "dbqqds", fid->fid,  glock->type,
		glock->start, glock->length, glock->proc_id, glock->client_id);

	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "bqqds", &glock->type,
			  &glock->start, &glock->length, &glock->proc_id,
			  &glock->client_id);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		जाओ error;
	पूर्ण
	p9_debug(P9_DEBUG_9P, "<<< RGETLOCK type %i start %lld length %lld "
		"proc_id %d client_id %s\n", glock->type, glock->start,
		glock->length, glock->proc_id, glock->client_id);
error:
	p9_tag_हटाओ(clnt, req);
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_getlock_करोtl);

पूर्णांक p9_client_पढ़ोlink(काष्ठा p9_fid *fid, अक्षर **target)
अणु
	पूर्णांक err;
	काष्ठा p9_client *clnt;
	काष्ठा p9_req_t *req;

	err = 0;
	clnt = fid->clnt;
	p9_debug(P9_DEBUG_9P, ">>> TREADLINK fid %d\n", fid->fid);

	req = p9_client_rpc(clnt, P9_TREADLINK, "d", fid->fid);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	err = p9pdu_पढ़ोf(&req->rc, clnt->proto_version, "s", target);
	अगर (err) अणु
		trace_9p_protocol_dump(clnt, &req->rc);
		जाओ error;
	पूर्ण
	p9_debug(P9_DEBUG_9P, "<<< RREADLINK target %s\n", *target);
error:
	p9_tag_हटाओ(clnt, req);
	वापस err;
पूर्ण
EXPORT_SYMBOL(p9_client_पढ़ोlink);

पूर्णांक __init p9_client_init(व्योम)
अणु
	p9_req_cache = KMEM_CACHE(p9_req_t, SLAB_TYPESAFE_BY_RCU);
	वापस p9_req_cache ? 0 : -ENOMEM;
पूर्ण

व्योम __निकास p9_client_निकास(व्योम)
अणु
	kmem_cache_destroy(p9_req_cache);
पूर्ण
