<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/9p/protocol.c
 *
 * 9P Protocol Support Code
 *
 *  Copyright (C) 2008 by Eric Van Hensbergen <ericvh@gmail.com>
 *
 *  Base on code from Anthony Liguori <aliguori@us.ibm.com>
 *  Copyright (C) 2008 by IBM, Corp.
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <linux/uपन.स>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>
#समावेश "protocol.h"

#समावेश <trace/events/9p.h>

अटल पूर्णांक
p9pdu_ग_लिखोf(काष्ठा p9_fcall *pdu, पूर्णांक proto_version, स्थिर अक्षर *fmt, ...);

व्योम p9stat_मुक्त(काष्ठा p9_wstat *stbuf)
अणु
	kमुक्त(stbuf->name);
	stbuf->name = शून्य;
	kमुक्त(stbuf->uid);
	stbuf->uid = शून्य;
	kमुक्त(stbuf->gid);
	stbuf->gid = शून्य;
	kमुक्त(stbuf->muid);
	stbuf->muid = शून्य;
	kमुक्त(stbuf->extension);
	stbuf->extension = शून्य;
पूर्ण
EXPORT_SYMBOL(p9stat_मुक्त);

माप_प्रकार pdu_पढ़ो(काष्ठा p9_fcall *pdu, व्योम *data, माप_प्रकार size)
अणु
	माप_प्रकार len = min(pdu->size - pdu->offset, size);
	स_नकल(data, &pdu->sdata[pdu->offset], len);
	pdu->offset += len;
	वापस size - len;
पूर्ण

अटल माप_प्रकार pdu_ग_लिखो(काष्ठा p9_fcall *pdu, स्थिर व्योम *data, माप_प्रकार size)
अणु
	माप_प्रकार len = min(pdu->capacity - pdu->size, size);
	स_नकल(&pdu->sdata[pdu->size], data, len);
	pdu->size += len;
	वापस size - len;
पूर्ण

अटल माप_प्रकार
pdu_ग_लिखो_u(काष्ठा p9_fcall *pdu, काष्ठा iov_iter *from, माप_प्रकार size)
अणु
	माप_प्रकार len = min(pdu->capacity - pdu->size, size);
	काष्ठा iov_iter i = *from;
	अगर (!copy_from_iter_full(&pdu->sdata[pdu->size], len, &i))
		len = 0;

	pdu->size += len;
	वापस size - len;
पूर्ण

/*
	b - पूर्णांक8_t
	w - पूर्णांक16_t
	d - पूर्णांक32_t
	q - पूर्णांक64_t
	s - string
	u - numeric uid
	g - numeric gid
	S - stat
	Q - qid
	D - data blob (पूर्णांक32_t size followed by व्योम *, results are not मुक्तd)
	T - array of strings (पूर्णांक16_t count, followed by strings)
	R - array of qids (पूर्णांक16_t count, followed by qids)
	A - stat क्रम 9p2000.L (p9_stat_करोtl)
	? - अगर optional = 1, जारी parsing
*/

अटल पूर्णांक
p9pdu_vपढ़ोf(काष्ठा p9_fcall *pdu, पूर्णांक proto_version, स्थिर अक्षर *fmt,
	बहु_सूची ap)
अणु
	स्थिर अक्षर *ptr;
	पूर्णांक errcode = 0;

	क्रम (ptr = fmt; *ptr; ptr++) अणु
		चयन (*ptr) अणु
		हाल 'b':अणु
				पूर्णांक8_t *val = बहु_तर्क(ap, पूर्णांक8_t *);
				अगर (pdu_पढ़ो(pdu, val, माप(*val))) अणु
					errcode = -EFAULT;
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 'w':अणु
				पूर्णांक16_t *val = बहु_तर्क(ap, पूर्णांक16_t *);
				__le16 le_val;
				अगर (pdu_पढ़ो(pdu, &le_val, माप(le_val))) अणु
					errcode = -EFAULT;
					अवरोध;
				पूर्ण
				*val = le16_to_cpu(le_val);
			पूर्ण
			अवरोध;
		हाल 'd':अणु
				पूर्णांक32_t *val = बहु_तर्क(ap, पूर्णांक32_t *);
				__le32 le_val;
				अगर (pdu_पढ़ो(pdu, &le_val, माप(le_val))) अणु
					errcode = -EFAULT;
					अवरोध;
				पूर्ण
				*val = le32_to_cpu(le_val);
			पूर्ण
			अवरोध;
		हाल 'q':अणु
				पूर्णांक64_t *val = बहु_तर्क(ap, पूर्णांक64_t *);
				__le64 le_val;
				अगर (pdu_पढ़ो(pdu, &le_val, माप(le_val))) अणु
					errcode = -EFAULT;
					अवरोध;
				पूर्ण
				*val = le64_to_cpu(le_val);
			पूर्ण
			अवरोध;
		हाल 's':अणु
				अक्षर **sptr = बहु_तर्क(ap, अक्षर **);
				uपूर्णांक16_t len;

				errcode = p9pdu_पढ़ोf(pdu, proto_version,
								"w", &len);
				अगर (errcode)
					अवरोध;

				*sptr = kदो_स्मृति(len + 1, GFP_NOFS);
				अगर (*sptr == शून्य) अणु
					errcode = -ENOMEM;
					अवरोध;
				पूर्ण
				अगर (pdu_पढ़ो(pdu, *sptr, len)) अणु
					errcode = -EFAULT;
					kमुक्त(*sptr);
					*sptr = शून्य;
				पूर्ण अन्यथा
					(*sptr)[len] = 0;
			पूर्ण
			अवरोध;
		हाल 'u': अणु
				kuid_t *uid = बहु_तर्क(ap, kuid_t *);
				__le32 le_val;
				अगर (pdu_पढ़ो(pdu, &le_val, माप(le_val))) अणु
					errcode = -EFAULT;
					अवरोध;
				पूर्ण
				*uid = make_kuid(&init_user_ns,
						 le32_to_cpu(le_val));
			पूर्ण अवरोध;
		हाल 'g': अणु
				kgid_t *gid = बहु_तर्क(ap, kgid_t *);
				__le32 le_val;
				अगर (pdu_पढ़ो(pdu, &le_val, माप(le_val))) अणु
					errcode = -EFAULT;
					अवरोध;
				पूर्ण
				*gid = make_kgid(&init_user_ns,
						 le32_to_cpu(le_val));
			पूर्ण अवरोध;
		हाल 'Q':अणु
				काष्ठा p9_qid *qid =
				    बहु_तर्क(ap, काष्ठा p9_qid *);

				errcode = p9pdu_पढ़ोf(pdu, proto_version, "bdq",
						      &qid->type, &qid->version,
						      &qid->path);
			पूर्ण
			अवरोध;
		हाल 'S':अणु
				काष्ठा p9_wstat *stbuf =
				    बहु_तर्क(ap, काष्ठा p9_wstat *);

				स_रखो(stbuf, 0, माप(काष्ठा p9_wstat));
				stbuf->n_uid = stbuf->n_muid = INVALID_UID;
				stbuf->n_gid = INVALID_GID;

				errcode =
				    p9pdu_पढ़ोf(pdu, proto_version,
						"wwdQdddqssss?sugu",
						&stbuf->size, &stbuf->type,
						&stbuf->dev, &stbuf->qid,
						&stbuf->mode, &stbuf->aसमय,
						&stbuf->mसमय, &stbuf->length,
						&stbuf->name, &stbuf->uid,
						&stbuf->gid, &stbuf->muid,
						&stbuf->extension,
						&stbuf->n_uid, &stbuf->n_gid,
						&stbuf->n_muid);
				अगर (errcode)
					p9stat_मुक्त(stbuf);
			पूर्ण
			अवरोध;
		हाल 'D':अणु
				uपूर्णांक32_t *count = बहु_तर्क(ap, uपूर्णांक32_t *);
				व्योम **data = बहु_तर्क(ap, व्योम **);

				errcode =
				    p9pdu_पढ़ोf(pdu, proto_version, "d", count);
				अगर (!errcode) अणु
					*count =
					    min_t(uपूर्णांक32_t, *count,
						  pdu->size - pdu->offset);
					*data = &pdu->sdata[pdu->offset];
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 'T':अणु
				uपूर्णांक16_t *nwname = बहु_तर्क(ap, uपूर्णांक16_t *);
				अक्षर ***wnames = बहु_तर्क(ap, अक्षर ***);

				errcode = p9pdu_पढ़ोf(pdu, proto_version,
								"w", nwname);
				अगर (!errcode) अणु
					*wnames =
					    kदो_स्मृति_array(*nwname,
							  माप(अक्षर *),
							  GFP_NOFS);
					अगर (!*wnames)
						errcode = -ENOMEM;
				पूर्ण

				अगर (!errcode) अणु
					पूर्णांक i;

					क्रम (i = 0; i < *nwname; i++) अणु
						errcode =
						    p9pdu_पढ़ोf(pdu,
								proto_version,
								"s",
								&(*wnames)[i]);
						अगर (errcode)
							अवरोध;
					पूर्ण
				पूर्ण

				अगर (errcode) अणु
					अगर (*wnames) अणु
						पूर्णांक i;

						क्रम (i = 0; i < *nwname; i++)
							kमुक्त((*wnames)[i]);
					पूर्ण
					kमुक्त(*wnames);
					*wnames = शून्य;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 'R':अणु
				uपूर्णांक16_t *nwqid = बहु_तर्क(ap, uपूर्णांक16_t *);
				काष्ठा p9_qid **wqids =
				    बहु_तर्क(ap, काष्ठा p9_qid **);

				*wqids = शून्य;

				errcode =
				    p9pdu_पढ़ोf(pdu, proto_version, "w", nwqid);
				अगर (!errcode) अणु
					*wqids =
					    kदो_स्मृति_array(*nwqid,
							  माप(काष्ठा p9_qid),
							  GFP_NOFS);
					अगर (*wqids == शून्य)
						errcode = -ENOMEM;
				पूर्ण

				अगर (!errcode) अणु
					पूर्णांक i;

					क्रम (i = 0; i < *nwqid; i++) अणु
						errcode =
						    p9pdu_पढ़ोf(pdu,
								proto_version,
								"Q",
								&(*wqids)[i]);
						अगर (errcode)
							अवरोध;
					पूर्ण
				पूर्ण

				अगर (errcode) अणु
					kमुक्त(*wqids);
					*wqids = शून्य;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 'A': अणु
				काष्ठा p9_stat_करोtl *stbuf =
				    बहु_तर्क(ap, काष्ठा p9_stat_करोtl *);

				स_रखो(stbuf, 0, माप(काष्ठा p9_stat_करोtl));
				errcode =
				    p9pdu_पढ़ोf(pdu, proto_version,
					"qQdugqqqqqqqqqqqqqqq",
					&stbuf->st_result_mask,
					&stbuf->qid,
					&stbuf->st_mode,
					&stbuf->st_uid, &stbuf->st_gid,
					&stbuf->st_nlink,
					&stbuf->st_rdev, &stbuf->st_size,
					&stbuf->st_blksize, &stbuf->st_blocks,
					&stbuf->st_aसमय_sec,
					&stbuf->st_aसमय_nsec,
					&stbuf->st_mसमय_sec,
					&stbuf->st_mसमय_nsec,
					&stbuf->st_स_समय_sec,
					&stbuf->st_स_समय_nsec,
					&stbuf->st_bसमय_sec,
					&stbuf->st_bसमय_nsec,
					&stbuf->st_gen,
					&stbuf->st_data_version);
			पूर्ण
			अवरोध;
		हाल '?':
			अगर ((proto_version != p9_proto_2000u) &&
				(proto_version != p9_proto_2000L))
				वापस 0;
			अवरोध;
		शेष:
			BUG();
			अवरोध;
		पूर्ण

		अगर (errcode)
			अवरोध;
	पूर्ण

	वापस errcode;
पूर्ण

पूर्णांक
p9pdu_vग_लिखोf(काष्ठा p9_fcall *pdu, पूर्णांक proto_version, स्थिर अक्षर *fmt,
	बहु_सूची ap)
अणु
	स्थिर अक्षर *ptr;
	पूर्णांक errcode = 0;

	क्रम (ptr = fmt; *ptr; ptr++) अणु
		चयन (*ptr) अणु
		हाल 'b':अणु
				पूर्णांक8_t val = बहु_तर्क(ap, पूर्णांक);
				अगर (pdu_ग_लिखो(pdu, &val, माप(val)))
					errcode = -EFAULT;
			पूर्ण
			अवरोध;
		हाल 'w':अणु
				__le16 val = cpu_to_le16(बहु_तर्क(ap, पूर्णांक));
				अगर (pdu_ग_लिखो(pdu, &val, माप(val)))
					errcode = -EFAULT;
			पूर्ण
			अवरोध;
		हाल 'd':अणु
				__le32 val = cpu_to_le32(बहु_तर्क(ap, पूर्णांक32_t));
				अगर (pdu_ग_लिखो(pdu, &val, माप(val)))
					errcode = -EFAULT;
			पूर्ण
			अवरोध;
		हाल 'q':अणु
				__le64 val = cpu_to_le64(बहु_तर्क(ap, पूर्णांक64_t));
				अगर (pdu_ग_लिखो(pdu, &val, माप(val)))
					errcode = -EFAULT;
			पूर्ण
			अवरोध;
		हाल 's':अणु
				स्थिर अक्षर *sptr = बहु_तर्क(ap, स्थिर अक्षर *);
				uपूर्णांक16_t len = 0;
				अगर (sptr)
					len = min_t(माप_प्रकार, म_माप(sptr),
								अच_लघु_उच्च);

				errcode = p9pdu_ग_लिखोf(pdu, proto_version,
								"w", len);
				अगर (!errcode && pdu_ग_लिखो(pdu, sptr, len))
					errcode = -EFAULT;
			पूर्ण
			अवरोध;
		हाल 'u': अणु
				kuid_t uid = बहु_तर्क(ap, kuid_t);
				__le32 val = cpu_to_le32(
						from_kuid(&init_user_ns, uid));
				अगर (pdu_ग_लिखो(pdu, &val, माप(val)))
					errcode = -EFAULT;
			पूर्ण अवरोध;
		हाल 'g': अणु
				kgid_t gid = बहु_तर्क(ap, kgid_t);
				__le32 val = cpu_to_le32(
						from_kgid(&init_user_ns, gid));
				अगर (pdu_ग_लिखो(pdu, &val, माप(val)))
					errcode = -EFAULT;
			पूर्ण अवरोध;
		हाल 'Q':अणु
				स्थिर काष्ठा p9_qid *qid =
				    बहु_तर्क(ap, स्थिर काष्ठा p9_qid *);
				errcode =
				    p9pdu_ग_लिखोf(pdu, proto_version, "bdq",
						 qid->type, qid->version,
						 qid->path);
			पूर्ण अवरोध;
		हाल 'S':अणु
				स्थिर काष्ठा p9_wstat *stbuf =
				    बहु_तर्क(ap, स्थिर काष्ठा p9_wstat *);
				errcode =
				    p9pdu_ग_लिखोf(pdu, proto_version,
						 "wwdQdddqssss?sugu",
						 stbuf->size, stbuf->type,
						 stbuf->dev, &stbuf->qid,
						 stbuf->mode, stbuf->aसमय,
						 stbuf->mसमय, stbuf->length,
						 stbuf->name, stbuf->uid,
						 stbuf->gid, stbuf->muid,
						 stbuf->extension, stbuf->n_uid,
						 stbuf->n_gid, stbuf->n_muid);
			पूर्ण अवरोध;
		हाल 'V':अणु
				uपूर्णांक32_t count = बहु_तर्क(ap, uपूर्णांक32_t);
				काष्ठा iov_iter *from =
						बहु_तर्क(ap, काष्ठा iov_iter *);
				errcode = p9pdu_ग_लिखोf(pdu, proto_version, "d",
									count);
				अगर (!errcode && pdu_ग_लिखो_u(pdu, from, count))
					errcode = -EFAULT;
			पूर्ण
			अवरोध;
		हाल 'T':अणु
				uपूर्णांक16_t nwname = बहु_तर्क(ap, पूर्णांक);
				स्थिर अक्षर **wnames = बहु_तर्क(ap, स्थिर अक्षर **);

				errcode = p9pdu_ग_लिखोf(pdu, proto_version, "w",
									nwname);
				अगर (!errcode) अणु
					पूर्णांक i;

					क्रम (i = 0; i < nwname; i++) अणु
						errcode =
						    p9pdu_ग_लिखोf(pdu,
								proto_version,
								 "s",
								 wnames[i]);
						अगर (errcode)
							अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 'R':अणु
				uपूर्णांक16_t nwqid = बहु_तर्क(ap, पूर्णांक);
				काष्ठा p9_qid *wqids =
				    बहु_तर्क(ap, काष्ठा p9_qid *);

				errcode = p9pdu_ग_लिखोf(pdu, proto_version, "w",
									nwqid);
				अगर (!errcode) अणु
					पूर्णांक i;

					क्रम (i = 0; i < nwqid; i++) अणु
						errcode =
						    p9pdu_ग_लिखोf(pdu,
								proto_version,
								 "Q",
								 &wqids[i]);
						अगर (errcode)
							अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 'I':अणु
				काष्ठा p9_iattr_करोtl *p9attr = बहु_तर्क(ap,
							काष्ठा p9_iattr_करोtl *);

				errcode = p9pdu_ग_लिखोf(pdu, proto_version,
							"ddugqqqqq",
							p9attr->valid,
							p9attr->mode,
							p9attr->uid,
							p9attr->gid,
							p9attr->size,
							p9attr->aसमय_sec,
							p9attr->aसमय_nsec,
							p9attr->mसमय_sec,
							p9attr->mसमय_nsec);
			पूर्ण
			अवरोध;
		हाल '?':
			अगर ((proto_version != p9_proto_2000u) &&
				(proto_version != p9_proto_2000L))
				वापस 0;
			अवरोध;
		शेष:
			BUG();
			अवरोध;
		पूर्ण

		अगर (errcode)
			अवरोध;
	पूर्ण

	वापस errcode;
पूर्ण

पूर्णांक p9pdu_पढ़ोf(काष्ठा p9_fcall *pdu, पूर्णांक proto_version, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;

	बहु_शुरू(ap, fmt);
	ret = p9pdu_vपढ़ोf(pdu, proto_version, fmt, ap);
	बहु_पूर्ण(ap);

	वापस ret;
पूर्ण

अटल पूर्णांक
p9pdu_ग_लिखोf(काष्ठा p9_fcall *pdu, पूर्णांक proto_version, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;

	बहु_शुरू(ap, fmt);
	ret = p9pdu_vग_लिखोf(pdu, proto_version, fmt, ap);
	बहु_पूर्ण(ap);

	वापस ret;
पूर्ण

पूर्णांक p9stat_पढ़ो(काष्ठा p9_client *clnt, अक्षर *buf, पूर्णांक len, काष्ठा p9_wstat *st)
अणु
	काष्ठा p9_fcall fake_pdu;
	पूर्णांक ret;

	fake_pdu.size = len;
	fake_pdu.capacity = len;
	fake_pdu.sdata = buf;
	fake_pdu.offset = 0;

	ret = p9pdu_पढ़ोf(&fake_pdu, clnt->proto_version, "S", st);
	अगर (ret) अणु
		p9_debug(P9_DEBUG_9P, "<<< p9stat_read failed: %d\n", ret);
		trace_9p_protocol_dump(clnt, &fake_pdu);
		वापस ret;
	पूर्ण

	वापस fake_pdu.offset;
पूर्ण
EXPORT_SYMBOL(p9stat_पढ़ो);

पूर्णांक p9pdu_prepare(काष्ठा p9_fcall *pdu, पूर्णांक16_t tag, पूर्णांक8_t type)
अणु
	pdu->id = type;
	वापस p9pdu_ग_लिखोf(pdu, 0, "dbw", 0, type, tag);
पूर्ण

पूर्णांक p9pdu_finalize(काष्ठा p9_client *clnt, काष्ठा p9_fcall *pdu)
अणु
	पूर्णांक size = pdu->size;
	पूर्णांक err;

	pdu->size = 0;
	err = p9pdu_ग_लिखोf(pdu, 0, "d", size);
	pdu->size = size;

	trace_9p_protocol_dump(clnt, pdu);
	p9_debug(P9_DEBUG_9P, ">>> size=%d type: %d tag: %d\n",
		 pdu->size, pdu->id, pdu->tag);

	वापस err;
पूर्ण

व्योम p9pdu_reset(काष्ठा p9_fcall *pdu)
अणु
	pdu->offset = 0;
	pdu->size = 0;
पूर्ण

पूर्णांक p9dirent_पढ़ो(काष्ठा p9_client *clnt, अक्षर *buf, पूर्णांक len,
		  काष्ठा p9_dirent *dirent)
अणु
	काष्ठा p9_fcall fake_pdu;
	पूर्णांक ret;
	अक्षर *nameptr;

	fake_pdu.size = len;
	fake_pdu.capacity = len;
	fake_pdu.sdata = buf;
	fake_pdu.offset = 0;

	ret = p9pdu_पढ़ोf(&fake_pdu, clnt->proto_version, "Qqbs", &dirent->qid,
			  &dirent->d_off, &dirent->d_type, &nameptr);
	अगर (ret) अणु
		p9_debug(P9_DEBUG_9P, "<<< p9dirent_read failed: %d\n", ret);
		trace_9p_protocol_dump(clnt, &fake_pdu);
		वापस ret;
	पूर्ण

	ret = strscpy(dirent->d_name, nameptr, माप(dirent->d_name));
	अगर (ret < 0) अणु
		p9_debug(P9_DEBUG_ERROR,
			 "On the wire dirent name too long: %s\n",
			 nameptr);
		kमुक्त(nameptr);
		वापस ret;
	पूर्ण
	kमुक्त(nameptr);

	वापस fake_pdu.offset;
पूर्ण
EXPORT_SYMBOL(p9dirent_पढ़ो);
