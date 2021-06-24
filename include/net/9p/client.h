<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/net/9p/client.h
 *
 * 9P Client Definitions
 *
 *  Copyright (C) 2008 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2007 by Latchesar Ionkov <lucho@ionkov.net>
 */

#अगर_अघोषित NET_9P_CLIENT_H
#घोषणा NET_9P_CLIENT_H

#समावेश <linux/utsname.h>
#समावेश <linux/idr.h>

/* Number of requests per row */
#घोषणा P9_ROW_MAXTAG 255

/** क्रमागत p9_proto_versions - 9P protocol versions
 * @p9_proto_legacy: 9P Legacy mode, pre-9P2000.u
 * @p9_proto_2000u: 9P2000.u extension
 * @p9_proto_2000L: 9P2000.L extension
 */

क्रमागत p9_proto_versionsअणु
	p9_proto_legacy,
	p9_proto_2000u,
	p9_proto_2000L,
पूर्ण;


/**
 * क्रमागत p9_trans_status - dअगरferent states of underlying transports
 * @Connected: transport is connected and healthy
 * @Disconnected: transport has been disconnected
 * @Hung: transport is connected by wedged
 *
 * This क्रमागतeration details the various states a transport
 * instatiation can be in.
 */

क्रमागत p9_trans_status अणु
	Connected,
	BeginDisconnect,
	Disconnected,
	Hung,
पूर्ण;

/**
 * क्रमागत p9_req_status_t - status of a request
 * @REQ_STATUS_ALLOC: request has been allocated but not sent
 * @REQ_STATUS_UNSENT: request रुकोing to be sent
 * @REQ_STATUS_SENT: request sent to server
 * @REQ_STATUS_RCVD: response received from server
 * @REQ_STATUS_FLSHD: request has been flushed
 * @REQ_STATUS_ERROR: request encountered an error on the client side
 */

क्रमागत p9_req_status_t अणु
	REQ_STATUS_ALLOC,
	REQ_STATUS_UNSENT,
	REQ_STATUS_SENT,
	REQ_STATUS_RCVD,
	REQ_STATUS_FLSHD,
	REQ_STATUS_ERROR,
पूर्ण;

/**
 * काष्ठा p9_req_t - request slots
 * @status: status of this request slot
 * @t_err: transport error
 * @wq: रुको_queue क्रम the client to block on क्रम this request
 * @tc: the request fcall काष्ठाure
 * @rc: the response fcall काष्ठाure
 * @req_list: link क्रम higher level objects to chain requests
 */
काष्ठा p9_req_t अणु
	पूर्णांक status;
	पूर्णांक t_err;
	काष्ठा kref refcount;
	रुको_queue_head_t wq;
	काष्ठा p9_fcall tc;
	काष्ठा p9_fcall rc;
	काष्ठा list_head req_list;
पूर्ण;

/**
 * काष्ठा p9_client - per client instance state
 * @lock: protect @fids and @reqs
 * @msize: maximum data size negotiated by protocol
 * @proto_version: 9P protocol version to use
 * @trans_mod: module API instantiated with this client
 * @status: connection state
 * @trans: tranport instance state and API
 * @fids: All active FID handles
 * @reqs: All active requests.
 * @name: node name used as client id
 *
 * The client काष्ठाure is used to keep track of various per-client
 * state that has been instantiated.
 */
काष्ठा p9_client अणु
	spinlock_t lock;
	अचिन्हित पूर्णांक msize;
	अचिन्हित अक्षर proto_version;
	काष्ठा p9_trans_module *trans_mod;
	क्रमागत p9_trans_status status;
	व्योम *trans;
	काष्ठा kmem_cache *fcall_cache;

	जोड़ अणु
		काष्ठा अणु
			पूर्णांक rfd;
			पूर्णांक wfd;
		पूर्ण fd;
		काष्ठा अणु
			u16 port;
			bool privport;

		पूर्ण tcp;
	पूर्ण trans_opts;

	काष्ठा idr fids;
	काष्ठा idr reqs;

	अक्षर name[__NEW_UTS_LEN + 1];
पूर्ण;

/**
 * काष्ठा p9_fid - file प्रणाली entity handle
 * @clnt: back poपूर्णांकer to instantiating &p9_client
 * @fid: numeric identअगरier क्रम this handle
 * @mode: current mode of this fid (क्रमागत?)
 * @qid: the &p9_qid server identअगरier this handle poपूर्णांकs to
 * @iounit: the server reported maximum transaction size क्रम this file
 * @uid: the numeric uid of the local user who owns this handle
 * @rdir: सूची_पढ़ो accounting काष्ठाure (allocated on demand)
 * @dlist: per-dentry fid tracking
 *
 * TODO: This needs lots of explanation.
 */
क्रमागत fid_source अणु
	FID_FROM_OTHER,
	FID_FROM_INODE,
	FID_FROM_DENTRY,
पूर्ण;

काष्ठा p9_fid अणु
	काष्ठा p9_client *clnt;
	u32 fid;
	refcount_t count;
	पूर्णांक mode;
	काष्ठा p9_qid qid;
	u32 iounit;
	kuid_t uid;

	व्योम *rdir;

	काष्ठा hlist_node dlist;	/* list of all fids attached to a dentry */
	काष्ठा hlist_node ilist;
पूर्ण;

/**
 * काष्ठा p9_dirent - directory entry काष्ठाure
 * @qid: The p9 server qid क्रम this dirent
 * @d_off: offset to the next dirent
 * @d_type: type of file
 * @d_name: file name
 */

काष्ठा p9_dirent अणु
	काष्ठा p9_qid qid;
	u64 d_off;
	अचिन्हित अक्षर d_type;
	अक्षर d_name[256];
पूर्ण;

काष्ठा iov_iter;

पूर्णांक p9_show_client_options(काष्ठा seq_file *m, काष्ठा p9_client *clnt);
पूर्णांक p9_client_statfs(काष्ठा p9_fid *fid, काष्ठा p9_rstatfs *sb);
पूर्णांक p9_client_नाम(काष्ठा p9_fid *fid, काष्ठा p9_fid *newdirfid,
		     स्थिर अक्षर *name);
पूर्णांक p9_client_नामat(काष्ठा p9_fid *olddirfid, स्थिर अक्षर *old_name,
		       काष्ठा p9_fid *newdirfid, स्थिर अक्षर *new_name);
काष्ठा p9_client *p9_client_create(स्थिर अक्षर *dev_name, अक्षर *options);
व्योम p9_client_destroy(काष्ठा p9_client *clnt);
व्योम p9_client_disconnect(काष्ठा p9_client *clnt);
व्योम p9_client_begin_disconnect(काष्ठा p9_client *clnt);
काष्ठा p9_fid *p9_client_attach(काष्ठा p9_client *clnt, काष्ठा p9_fid *afid,
				स्थिर अक्षर *uname, kuid_t n_uname, स्थिर अक्षर *aname);
काष्ठा p9_fid *p9_client_walk(काष्ठा p9_fid *oldfid, uपूर्णांक16_t nwname,
		स्थिर अचिन्हित अक्षर * स्थिर *wnames, पूर्णांक clone);
पूर्णांक p9_client_खोलो(काष्ठा p9_fid *fid, पूर्णांक mode);
पूर्णांक p9_client_fcreate(काष्ठा p9_fid *fid, स्थिर अक्षर *name, u32 perm, पूर्णांक mode,
							अक्षर *extension);
पूर्णांक p9_client_link(काष्ठा p9_fid *fid, काष्ठा p9_fid *oldfid, स्थिर अक्षर *newname);
पूर्णांक p9_client_symlink(काष्ठा p9_fid *fid, स्थिर अक्षर *name, स्थिर अक्षर *symname,
		kgid_t gid, काष्ठा p9_qid *qid);
पूर्णांक p9_client_create_करोtl(काष्ठा p9_fid *ofid, स्थिर अक्षर *name, u32 flags, u32 mode,
		kgid_t gid, काष्ठा p9_qid *qid);
पूर्णांक p9_client_clunk(काष्ठा p9_fid *fid);
पूर्णांक p9_client_fsync(काष्ठा p9_fid *fid, पूर्णांक datasync);
पूर्णांक p9_client_हटाओ(काष्ठा p9_fid *fid);
पूर्णांक p9_client_unlinkat(काष्ठा p9_fid *dfid, स्थिर अक्षर *name, पूर्णांक flags);
पूर्णांक p9_client_पढ़ो(काष्ठा p9_fid *fid, u64 offset, काष्ठा iov_iter *to, पूर्णांक *err);
पूर्णांक p9_client_पढ़ो_once(काष्ठा p9_fid *fid, u64 offset, काष्ठा iov_iter *to,
		पूर्णांक *err);
पूर्णांक p9_client_ग_लिखो(काष्ठा p9_fid *fid, u64 offset, काष्ठा iov_iter *from, पूर्णांक *err);
पूर्णांक p9_client_सूची_पढ़ो(काष्ठा p9_fid *fid, अक्षर *data, u32 count, u64 offset);
पूर्णांक p9dirent_पढ़ो(काष्ठा p9_client *clnt, अक्षर *buf, पूर्णांक len,
		  काष्ठा p9_dirent *dirent);
काष्ठा p9_wstat *p9_client_stat(काष्ठा p9_fid *fid);
पूर्णांक p9_client_wstat(काष्ठा p9_fid *fid, काष्ठा p9_wstat *wst);
पूर्णांक p9_client_setattr(काष्ठा p9_fid *fid, काष्ठा p9_iattr_करोtl *attr);

काष्ठा p9_stat_करोtl *p9_client_getattr_करोtl(काष्ठा p9_fid *fid,
							u64 request_mask);

पूर्णांक p9_client_mknod_करोtl(काष्ठा p9_fid *oldfid, स्थिर अक्षर *name, पूर्णांक mode,
			dev_t rdev, kgid_t gid, काष्ठा p9_qid *);
पूर्णांक p9_client_सूची_गढ़ो_करोtl(काष्ठा p9_fid *fid, स्थिर अक्षर *name, पूर्णांक mode,
				kgid_t gid, काष्ठा p9_qid *);
पूर्णांक p9_client_lock_करोtl(काष्ठा p9_fid *fid, काष्ठा p9_flock *flock, u8 *status);
पूर्णांक p9_client_getlock_करोtl(काष्ठा p9_fid *fid, काष्ठा p9_getlock *fl);
व्योम p9_fcall_fini(काष्ठा p9_fcall *fc);
काष्ठा p9_req_t *p9_tag_lookup(काष्ठा p9_client *, u16);

अटल अंतरभूत व्योम p9_req_get(काष्ठा p9_req_t *r)
अणु
	kref_get(&r->refcount);
पूर्ण

अटल अंतरभूत पूर्णांक p9_req_try_get(काष्ठा p9_req_t *r)
अणु
	वापस kref_get_unless_zero(&r->refcount);
पूर्ण

पूर्णांक p9_req_put(काष्ठा p9_req_t *r);

व्योम p9_client_cb(काष्ठा p9_client *c, काष्ठा p9_req_t *req, पूर्णांक status);

पूर्णांक p9_parse_header(काष्ठा p9_fcall *, पूर्णांक32_t *, पूर्णांक8_t *, पूर्णांक16_t *, पूर्णांक);
पूर्णांक p9stat_पढ़ो(काष्ठा p9_client *, अक्षर *, पूर्णांक, काष्ठा p9_wstat *);
व्योम p9stat_मुक्त(काष्ठा p9_wstat *);

पूर्णांक p9_is_proto_करोtu(काष्ठा p9_client *clnt);
पूर्णांक p9_is_proto_करोtl(काष्ठा p9_client *clnt);
काष्ठा p9_fid *p9_client_xattrwalk(काष्ठा p9_fid *, स्थिर अक्षर *, u64 *);
पूर्णांक p9_client_xattrcreate(काष्ठा p9_fid *, स्थिर अक्षर *, u64, पूर्णांक);
पूर्णांक p9_client_पढ़ोlink(काष्ठा p9_fid *fid, अक्षर **target);

पूर्णांक p9_client_init(व्योम);
व्योम p9_client_निकास(व्योम);

#पूर्ण_अगर /* NET_9P_CLIENT_H */
