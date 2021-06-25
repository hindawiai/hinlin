<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor functions क्रम unpacking policy loaded from
 * userspace.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 *
 * AppArmor uses a serialized binary क्रमmat क्रम loading policy. To find
 * policy क्रमmat करोcumentation see Documentation/admin-guide/LSM/apparmor.rst
 * All policy is validated beक्रमe it is used.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/zlib.h>

#समावेश "include/apparmor.h"
#समावेश "include/audit.h"
#समावेश "include/cred.h"
#समावेश "include/crypto.h"
#समावेश "include/match.h"
#समावेश "include/path.h"
#समावेश "include/policy.h"
#समावेश "include/policy_unpack.h"

#घोषणा K_ABI_MASK 0x3ff
#घोषणा FORCE_COMPLAIN_FLAG 0x800
#घोषणा VERSION_LT(X, Y) (((X) & K_ABI_MASK) < ((Y) & K_ABI_MASK))
#घोषणा VERSION_GT(X, Y) (((X) & K_ABI_MASK) > ((Y) & K_ABI_MASK))

#घोषणा v5	5	/* base version */
#घोषणा v6	6	/* per entry policydb mediation check */
#घोषणा v7	7
#घोषणा v8	8	/* full network masking */

/*
 * The AppArmor पूर्णांकerface treats data as a type byte followed by the
 * actual data.  The पूर्णांकerface has the notion of a a named entry
 * which has a name (AA_NAME typecode followed by name string) followed by
 * the entries typecode and data.  Named types allow क्रम optional
 * elements and extensions to be added and tested क्रम without अवरोधing
 * backwards compatibility.
 */

क्रमागत aa_code अणु
	AA_U8,
	AA_U16,
	AA_U32,
	AA_U64,
	AA_NAME,		/* same as string except it is items name */
	AA_STRING,
	AA_BLOB,
	AA_STRUCT,
	AA_STRUCTEND,
	AA_LIST,
	AA_LISTEND,
	AA_ARRAY,
	AA_ARRAYEND,
पूर्ण;

/*
 * aa_ext is the पढ़ो of the buffer containing the serialized profile.  The
 * data is copied पूर्णांकo a kernel buffer in apparmorfs and then handed off to
 * the unpack routines.
 */
काष्ठा aa_ext अणु
	व्योम *start;
	व्योम *end;
	व्योम *pos;		/* poपूर्णांकer to current position in the buffer */
	u32 version;
पूर्ण;

/* audit callback क्रम unpack fields */
अटल व्योम audit_cb(काष्ठा audit_buffer *ab, व्योम *va)
अणु
	काष्ठा common_audit_data *sa = va;

	अगर (aad(sa)->अगरace.ns) अणु
		audit_log_क्रमmat(ab, " ns=");
		audit_log_untrustedstring(ab, aad(sa)->अगरace.ns);
	पूर्ण
	अगर (aad(sa)->name) अणु
		audit_log_क्रमmat(ab, " name=");
		audit_log_untrustedstring(ab, aad(sa)->name);
	पूर्ण
	अगर (aad(sa)->अगरace.pos)
		audit_log_क्रमmat(ab, " offset=%ld", aad(sa)->अगरace.pos);
पूर्ण

/**
 * audit_अगरace - करो audit message क्रम policy unpacking/load/replace/हटाओ
 * @new: profile अगर it has been allocated (MAYBE शून्य)
 * @ns_name: name of the ns the profile is to be loaded to (MAY BE शून्य)
 * @name: name of the profile being manipulated (MAYBE शून्य)
 * @info: any extra info about the failure (MAYBE शून्य)
 * @e: buffer position info
 * @error: error code
 *
 * Returns: %0 or error
 */
अटल पूर्णांक audit_अगरace(काष्ठा aa_profile *new, स्थिर अक्षर *ns_name,
		       स्थिर अक्षर *name, स्थिर अक्षर *info, काष्ठा aa_ext *e,
		       पूर्णांक error)
अणु
	काष्ठा aa_profile *profile = labels_profile(aa_current_raw_label());
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_NONE, शून्य);
	अगर (e)
		aad(&sa)->अगरace.pos = e->pos - e->start;
	aad(&sa)->अगरace.ns = ns_name;
	अगर (new)
		aad(&sa)->name = new->base.hname;
	अन्यथा
		aad(&sa)->name = name;
	aad(&sa)->info = info;
	aad(&sa)->error = error;

	वापस aa_audit(AUDIT_APPARMOR_STATUS, profile, &sa, audit_cb);
पूर्ण

व्योम __aa_loaddata_update(काष्ठा aa_loaddata *data, दीर्घ revision)
अणु
	AA_BUG(!data);
	AA_BUG(!data->ns);
	AA_BUG(!data->dents[AAFS_LOADDATA_REVISION]);
	AA_BUG(!mutex_is_locked(&data->ns->lock));
	AA_BUG(data->revision > revision);

	data->revision = revision;
	d_inode(data->dents[AAFS_LOADDATA_सूची])->i_mसमय =
		current_समय(d_inode(data->dents[AAFS_LOADDATA_सूची]));
	d_inode(data->dents[AAFS_LOADDATA_REVISION])->i_mसमय =
		current_समय(d_inode(data->dents[AAFS_LOADDATA_REVISION]));
पूर्ण

bool aa_rawdata_eq(काष्ठा aa_loaddata *l, काष्ठा aa_loaddata *r)
अणु
	अगर (l->size != r->size)
		वापस false;
	अगर (l->compressed_size != r->compressed_size)
		वापस false;
	अगर (aa_g_hash_policy && स_भेद(l->hash, r->hash, aa_hash_size()) != 0)
		वापस false;
	वापस स_भेद(l->data, r->data, r->compressed_size ?: r->size) == 0;
पूर्ण

/*
 * need to take the ns mutex lock which is NOT safe most places that
 * put_loaddata is called, so we have to delay मुक्तing it
 */
अटल व्योम करो_loaddata_मुक्त(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा aa_loaddata *d = container_of(work, काष्ठा aa_loaddata, work);
	काष्ठा aa_ns *ns = aa_get_ns(d->ns);

	अगर (ns) अणु
		mutex_lock_nested(&ns->lock, ns->level);
		__aa_fs_हटाओ_rawdata(d);
		mutex_unlock(&ns->lock);
		aa_put_ns(ns);
	पूर्ण

	kमुक्त_sensitive(d->hash);
	kमुक्त_sensitive(d->name);
	kvमुक्त(d->data);
	kमुक्त_sensitive(d);
पूर्ण

व्योम aa_loaddata_kref(काष्ठा kref *kref)
अणु
	काष्ठा aa_loaddata *d = container_of(kref, काष्ठा aa_loaddata, count);

	अगर (d) अणु
		INIT_WORK(&d->work, करो_loaddata_मुक्त);
		schedule_work(&d->work);
	पूर्ण
पूर्ण

काष्ठा aa_loaddata *aa_loaddata_alloc(माप_प्रकार size)
अणु
	काष्ठा aa_loaddata *d;

	d = kzalloc(माप(*d), GFP_KERNEL);
	अगर (d == शून्य)
		वापस ERR_PTR(-ENOMEM);
	d->data = kvzalloc(size, GFP_KERNEL);
	अगर (!d->data) अणु
		kमुक्त(d);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	kref_init(&d->count);
	INIT_LIST_HEAD(&d->list);

	वापस d;
पूर्ण

/* test अगर पढ़ो will be in packed data bounds */
अटल bool inbounds(काष्ठा aa_ext *e, माप_प्रकार size)
अणु
	वापस (size <= e->end - e->pos);
पूर्ण

अटल व्योम *kvmemdup(स्थिर व्योम *src, माप_प्रकार len)
अणु
	व्योम *p = kvदो_स्मृति(len, GFP_KERNEL);

	अगर (p)
		स_नकल(p, src, len);
	वापस p;
पूर्ण

/**
 * aa_u16_chunck - test and करो bounds checking क्रम a u16 size based chunk
 * @e: serialized data पढ़ो head (NOT शून्य)
 * @chunk: start address क्रम chunk of data (NOT शून्य)
 *
 * Returns: the size of chunk found with the पढ़ो head at the end of the chunk.
 */
अटल माप_प्रकार unpack_u16_chunk(काष्ठा aa_ext *e, अक्षर **chunk)
अणु
	माप_प्रकार size = 0;
	व्योम *pos = e->pos;

	अगर (!inbounds(e, माप(u16)))
		जाओ fail;
	size = le16_to_cpu(get_unaligned((__le16 *) e->pos));
	e->pos += माप(__le16);
	अगर (!inbounds(e, size))
		जाओ fail;
	*chunk = e->pos;
	e->pos += size;
	वापस size;

fail:
	e->pos = pos;
	वापस 0;
पूर्ण

/* unpack control byte */
अटल bool unpack_X(काष्ठा aa_ext *e, क्रमागत aa_code code)
अणु
	अगर (!inbounds(e, 1))
		वापस false;
	अगर (*(u8 *) e->pos != code)
		वापस false;
	e->pos++;
	वापस true;
पूर्ण

/**
 * unpack_nameX - check is the next element is of type X with a name of @name
 * @e: serialized data extent inक्रमmation  (NOT शून्य)
 * @code: type code
 * @name: name to match to the serialized element.  (MAYBE शून्य)
 *
 * check that the next serialized data element is of type X and has a tag
 * name @name.  If @name is specअगरied then there must be a matching
 * name element in the stream.  If @name is शून्य any name element will be
 * skipped and only the typecode will be tested.
 *
 * Returns true on success (both type code and name tests match) and the पढ़ो
 * head is advanced past the headers
 *
 * Returns: false अगर either match fails, the पढ़ो head करोes not move
 */
अटल bool unpack_nameX(काष्ठा aa_ext *e, क्रमागत aa_code code, स्थिर अक्षर *name)
अणु
	/*
	 * May need to reset pos अगर name or type करोesn't match
	 */
	व्योम *pos = e->pos;
	/*
	 * Check क्रम presence of a tagname, and अगर present name size
	 * AA_NAME tag value is a u16.
	 */
	अगर (unpack_X(e, AA_NAME)) अणु
		अक्षर *tag = शून्य;
		माप_प्रकार size = unpack_u16_chunk(e, &tag);
		/* अगर a name is specअगरied it must match. otherwise skip tag */
		अगर (name && (!size || tag[size-1] != '\0' || म_भेद(name, tag)))
			जाओ fail;
	पूर्ण अन्यथा अगर (name) अणु
		/* अगर a name is specअगरied and there is no name tag fail */
		जाओ fail;
	पूर्ण

	/* now check अगर type code matches */
	अगर (unpack_X(e, code))
		वापस true;

fail:
	e->pos = pos;
	वापस false;
पूर्ण

अटल bool unpack_u8(काष्ठा aa_ext *e, u8 *data, स्थिर अक्षर *name)
अणु
	व्योम *pos = e->pos;

	अगर (unpack_nameX(e, AA_U8, name)) अणु
		अगर (!inbounds(e, माप(u8)))
			जाओ fail;
		अगर (data)
			*data = get_unaligned((u8 *)e->pos);
		e->pos += माप(u8);
		वापस true;
	पूर्ण

fail:
	e->pos = pos;
	वापस false;
पूर्ण

अटल bool unpack_u32(काष्ठा aa_ext *e, u32 *data, स्थिर अक्षर *name)
अणु
	व्योम *pos = e->pos;

	अगर (unpack_nameX(e, AA_U32, name)) अणु
		अगर (!inbounds(e, माप(u32)))
			जाओ fail;
		अगर (data)
			*data = le32_to_cpu(get_unaligned((__le32 *) e->pos));
		e->pos += माप(u32);
		वापस true;
	पूर्ण

fail:
	e->pos = pos;
	वापस false;
पूर्ण

अटल bool unpack_u64(काष्ठा aa_ext *e, u64 *data, स्थिर अक्षर *name)
अणु
	व्योम *pos = e->pos;

	अगर (unpack_nameX(e, AA_U64, name)) अणु
		अगर (!inbounds(e, माप(u64)))
			जाओ fail;
		अगर (data)
			*data = le64_to_cpu(get_unaligned((__le64 *) e->pos));
		e->pos += माप(u64);
		वापस true;
	पूर्ण

fail:
	e->pos = pos;
	वापस false;
पूर्ण

अटल माप_प्रकार unpack_array(काष्ठा aa_ext *e, स्थिर अक्षर *name)
अणु
	व्योम *pos = e->pos;

	अगर (unpack_nameX(e, AA_ARRAY, name)) अणु
		पूर्णांक size;
		अगर (!inbounds(e, माप(u16)))
			जाओ fail;
		size = (पूर्णांक)le16_to_cpu(get_unaligned((__le16 *) e->pos));
		e->pos += माप(u16);
		वापस size;
	पूर्ण

fail:
	e->pos = pos;
	वापस 0;
पूर्ण

अटल माप_प्रकार unpack_blob(काष्ठा aa_ext *e, अक्षर **blob, स्थिर अक्षर *name)
अणु
	व्योम *pos = e->pos;

	अगर (unpack_nameX(e, AA_BLOB, name)) अणु
		u32 size;
		अगर (!inbounds(e, माप(u32)))
			जाओ fail;
		size = le32_to_cpu(get_unaligned((__le32 *) e->pos));
		e->pos += माप(u32);
		अगर (inbounds(e, (माप_प्रकार) size)) अणु
			*blob = e->pos;
			e->pos += size;
			वापस size;
		पूर्ण
	पूर्ण

fail:
	e->pos = pos;
	वापस 0;
पूर्ण

अटल पूर्णांक unpack_str(काष्ठा aa_ext *e, स्थिर अक्षर **string, स्थिर अक्षर *name)
अणु
	अक्षर *src_str;
	माप_प्रकार size = 0;
	व्योम *pos = e->pos;
	*string = शून्य;
	अगर (unpack_nameX(e, AA_STRING, name)) अणु
		size = unpack_u16_chunk(e, &src_str);
		अगर (size) अणु
			/* strings are null terminated, length is size - 1 */
			अगर (src_str[size - 1] != 0)
				जाओ fail;
			*string = src_str;

			वापस size;
		पूर्ण
	पूर्ण

fail:
	e->pos = pos;
	वापस 0;
पूर्ण

अटल पूर्णांक unpack_strdup(काष्ठा aa_ext *e, अक्षर **string, स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *पंचांगp;
	व्योम *pos = e->pos;
	पूर्णांक res = unpack_str(e, &पंचांगp, name);
	*string = शून्य;

	अगर (!res)
		वापस 0;

	*string = kmemdup(पंचांगp, res, GFP_KERNEL);
	अगर (!*string) अणु
		e->pos = pos;
		वापस 0;
	पूर्ण

	वापस res;
पूर्ण


/**
 * unpack_dfa - unpack a file rule dfa
 * @e: serialized data extent inक्रमmation (NOT शून्य)
 *
 * वापसs dfa or ERR_PTR or शून्य अगर no dfa
 */
अटल काष्ठा aa_dfa *unpack_dfa(काष्ठा aa_ext *e)
अणु
	अक्षर *blob = शून्य;
	माप_प्रकार size;
	काष्ठा aa_dfa *dfa = शून्य;

	size = unpack_blob(e, &blob, "aadfa");
	अगर (size) अणु
		/*
		 * The dfa is aligned with in the blob to 8 bytes
		 * from the beginning of the stream.
		 * alignment adjust needed by dfa unpack
		 */
		माप_प्रकार sz = blob - (अक्षर *) e->start -
			((e->pos - e->start) & 7);
		माप_प्रकार pad = ALIGN(sz, 8) - sz;
		पूर्णांक flags = TO_ACCEPT1_FLAG(YYTD_DATA32) |
			TO_ACCEPT2_FLAG(YYTD_DATA32) | DFA_FLAG_VERIFY_STATES;
		dfa = aa_dfa_unpack(blob + pad, size - pad, flags);

		अगर (IS_ERR(dfa))
			वापस dfa;

	पूर्ण

	वापस dfa;
पूर्ण

/**
 * unpack_trans_table - unpack a profile transition table
 * @e: serialized data extent inक्रमmation  (NOT शून्य)
 * @profile: profile to add the accept table to (NOT शून्य)
 *
 * Returns: true अगर table successfully unpacked
 */
अटल bool unpack_trans_table(काष्ठा aa_ext *e, काष्ठा aa_profile *profile)
अणु
	व्योम *saved_pos = e->pos;

	/* exec table is optional */
	अगर (unpack_nameX(e, AA_STRUCT, "xtable")) अणु
		पूर्णांक i, size;

		size = unpack_array(e, शून्य);
		/* currently 4 exec bits and entries 0-3 are reserved iupcx */
		अगर (size > 16 - 4)
			जाओ fail;
		profile->file.trans.table = kसुस्मृति(size, माप(अक्षर *),
						    GFP_KERNEL);
		अगर (!profile->file.trans.table)
			जाओ fail;

		profile->file.trans.size = size;
		क्रम (i = 0; i < size; i++) अणु
			अक्षर *str;
			पूर्णांक c, j, pos, size2 = unpack_strdup(e, &str, शून्य);
			/* unpack_strdup verअगरies that the last अक्षरacter is
			 * null termination byte.
			 */
			अगर (!size2)
				जाओ fail;
			profile->file.trans.table[i] = str;
			/* verअगरy that name करोesn't start with space */
			अगर (है_खाली(*str))
				जाओ fail;

			/* count पूर्णांकernal #  of पूर्णांकernal \0 */
			क्रम (c = j = 0; j < size2 - 1; j++) अणु
				अगर (!str[j]) अणु
					pos = j;
					c++;
				पूर्ण
			पूर्ण
			अगर (*str == ':') अणु
				/* first अक्षरacter after : must be valid */
				अगर (!str[1])
					जाओ fail;
				/* beginning with : requires an embedded \0,
				 * verअगरy that exactly 1 पूर्णांकernal \0 exists
				 * trailing \0 alपढ़ोy verअगरied by unpack_strdup
				 *
				 * convert \0 back to : क्रम label_parse
				 */
				अगर (c == 1)
					str[pos] = ':';
				अन्यथा अगर (c > 1)
					जाओ fail;
			पूर्ण अन्यथा अगर (c)
				/* fail - all other हालs with embedded \0 */
				जाओ fail;
		पूर्ण
		अगर (!unpack_nameX(e, AA_ARRAYEND, शून्य))
			जाओ fail;
		अगर (!unpack_nameX(e, AA_STRUCTEND, शून्य))
			जाओ fail;
	पूर्ण
	वापस true;

fail:
	aa_मुक्त_करोमुख्य_entries(&profile->file.trans);
	e->pos = saved_pos;
	वापस false;
पूर्ण

अटल bool unpack_xattrs(काष्ठा aa_ext *e, काष्ठा aa_profile *profile)
अणु
	व्योम *pos = e->pos;

	अगर (unpack_nameX(e, AA_STRUCT, "xattrs")) अणु
		पूर्णांक i, size;

		size = unpack_array(e, शून्य);
		profile->xattr_count = size;
		profile->xattrs = kसुस्मृति(size, माप(अक्षर *), GFP_KERNEL);
		अगर (!profile->xattrs)
			जाओ fail;
		क्रम (i = 0; i < size; i++) अणु
			अगर (!unpack_strdup(e, &profile->xattrs[i], शून्य))
				जाओ fail;
		पूर्ण
		अगर (!unpack_nameX(e, AA_ARRAYEND, शून्य))
			जाओ fail;
		अगर (!unpack_nameX(e, AA_STRUCTEND, शून्य))
			जाओ fail;
	पूर्ण

	वापस true;

fail:
	e->pos = pos;
	वापस false;
पूर्ण

अटल bool unpack_secmark(काष्ठा aa_ext *e, काष्ठा aa_profile *profile)
अणु
	व्योम *pos = e->pos;
	पूर्णांक i, size;

	अगर (unpack_nameX(e, AA_STRUCT, "secmark")) अणु
		size = unpack_array(e, शून्य);

		profile->secmark = kसुस्मृति(size, माप(काष्ठा aa_secmark),
					   GFP_KERNEL);
		अगर (!profile->secmark)
			जाओ fail;

		profile->secmark_count = size;

		क्रम (i = 0; i < size; i++) अणु
			अगर (!unpack_u8(e, &profile->secmark[i].audit, शून्य))
				जाओ fail;
			अगर (!unpack_u8(e, &profile->secmark[i].deny, शून्य))
				जाओ fail;
			अगर (!unpack_strdup(e, &profile->secmark[i].label, शून्य))
				जाओ fail;
		पूर्ण
		अगर (!unpack_nameX(e, AA_ARRAYEND, शून्य))
			जाओ fail;
		अगर (!unpack_nameX(e, AA_STRUCTEND, शून्य))
			जाओ fail;
	पूर्ण

	वापस true;

fail:
	अगर (profile->secmark) अणु
		क्रम (i = 0; i < size; i++)
			kमुक्त(profile->secmark[i].label);
		kमुक्त(profile->secmark);
		profile->secmark_count = 0;
		profile->secmark = शून्य;
	पूर्ण

	e->pos = pos;
	वापस false;
पूर्ण

अटल bool unpack_rlimits(काष्ठा aa_ext *e, काष्ठा aa_profile *profile)
अणु
	व्योम *pos = e->pos;

	/* rlimits are optional */
	अगर (unpack_nameX(e, AA_STRUCT, "rlimits")) अणु
		पूर्णांक i, size;
		u32 पंचांगp = 0;
		अगर (!unpack_u32(e, &पंचांगp, शून्य))
			जाओ fail;
		profile->rlimits.mask = पंचांगp;

		size = unpack_array(e, शून्य);
		अगर (size > RLIM_NLIMITS)
			जाओ fail;
		क्रम (i = 0; i < size; i++) अणु
			u64 पंचांगp2 = 0;
			पूर्णांक a = aa_map_resource(i);
			अगर (!unpack_u64(e, &पंचांगp2, शून्य))
				जाओ fail;
			profile->rlimits.limits[a].rlim_max = पंचांगp2;
		पूर्ण
		अगर (!unpack_nameX(e, AA_ARRAYEND, शून्य))
			जाओ fail;
		अगर (!unpack_nameX(e, AA_STRUCTEND, शून्य))
			जाओ fail;
	पूर्ण
	वापस true;

fail:
	e->pos = pos;
	वापस false;
पूर्ण

अटल u32 strhash(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर अक्षर * स्थिर *key = data;

	वापस jhash(*key, म_माप(*key), seed);
पूर्ण

अटल पूर्णांक datacmp(काष्ठा rhashtable_compare_arg *arg, स्थिर व्योम *obj)
अणु
	स्थिर काष्ठा aa_data *data = obj;
	स्थिर अक्षर * स्थिर *key = arg->key;

	वापस म_भेद(data->key, *key);
पूर्ण

/**
 * unpack_profile - unpack a serialized profile
 * @e: serialized data extent inक्रमmation (NOT शून्य)
 *
 * NOTE: unpack profile sets audit काष्ठा अगर there is a failure
 */
अटल काष्ठा aa_profile *unpack_profile(काष्ठा aa_ext *e, अक्षर **ns_name)
अणु
	काष्ठा aa_profile *profile = शून्य;
	स्थिर अक्षर *क्षणिकe, *पंचांगpns = शून्य, *name = शून्य;
	स्थिर अक्षर *info = "failed to unpack profile";
	माप_प्रकार ns_len;
	काष्ठा rhashtable_params params = अणु 0 पूर्ण;
	अक्षर *key = शून्य;
	काष्ठा aa_data *data;
	पूर्णांक i, error = -EPROTO;
	kernel_cap_t पंचांगpcap;
	u32 पंचांगp;

	*ns_name = शून्य;

	/* check that we have the right काष्ठा being passed */
	अगर (!unpack_nameX(e, AA_STRUCT, "profile"))
		जाओ fail;
	अगर (!unpack_str(e, &name, शून्य))
		जाओ fail;
	अगर (*name == '\0')
		जाओ fail;

	क्षणिकe = aa_splitn_fqname(name, म_माप(name), &पंचांगpns, &ns_len);
	अगर (पंचांगpns) अणु
		*ns_name = kstrndup(पंचांगpns, ns_len, GFP_KERNEL);
		अगर (!*ns_name) अणु
			info = "out of memory";
			जाओ fail;
		पूर्ण
		name = क्षणिकe;
	पूर्ण

	profile = aa_alloc_profile(name, शून्य, GFP_KERNEL);
	अगर (!profile)
		वापस ERR_PTR(-ENOMEM);

	/* profile renaming is optional */
	(व्योम) unpack_str(e, &profile->नाम, "rename");

	/* attachment string is optional */
	(व्योम) unpack_str(e, &profile->attach, "attach");

	/* xmatch is optional and may be शून्य */
	profile->xmatch = unpack_dfa(e);
	अगर (IS_ERR(profile->xmatch)) अणु
		error = PTR_ERR(profile->xmatch);
		profile->xmatch = शून्य;
		info = "bad xmatch";
		जाओ fail;
	पूर्ण
	/* xmatch_len is not optional अगर xmatch is set */
	अगर (profile->xmatch) अणु
		अगर (!unpack_u32(e, &पंचांगp, शून्य)) अणु
			info = "missing xmatch len";
			जाओ fail;
		पूर्ण
		profile->xmatch_len = पंचांगp;
	पूर्ण

	/* disconnected attachment string is optional */
	(व्योम) unpack_str(e, &profile->disconnected, "disconnected");

	/* per profile debug flags (complain, audit) */
	अगर (!unpack_nameX(e, AA_STRUCT, "flags")) अणु
		info = "profile missing flags";
		जाओ fail;
	पूर्ण
	info = "failed to unpack profile flags";
	अगर (!unpack_u32(e, &पंचांगp, शून्य))
		जाओ fail;
	अगर (पंचांगp & PACKED_FLAG_HAT)
		profile->label.flags |= FLAG_HAT;
	अगर (!unpack_u32(e, &पंचांगp, शून्य))
		जाओ fail;
	अगर (पंचांगp == PACKED_MODE_COMPLAIN || (e->version & FORCE_COMPLAIN_FLAG))
		profile->mode = APPARMOR_COMPLAIN;
	अन्यथा अगर (पंचांगp == PACKED_MODE_ENFORCE)
		profile->mode = APPARMOR_ENFORCE;
	अन्यथा अगर (पंचांगp == PACKED_MODE_KILL)
		profile->mode = APPARMOR_KILL;
	अन्यथा अगर (पंचांगp == PACKED_MODE_UNCONFINED)
		profile->mode = APPARMOR_UNCONFINED;
	अन्यथा
		जाओ fail;
	अगर (!unpack_u32(e, &पंचांगp, शून्य))
		जाओ fail;
	अगर (पंचांगp)
		profile->audit = AUDIT_ALL;

	अगर (!unpack_nameX(e, AA_STRUCTEND, शून्य))
		जाओ fail;

	/* path_flags is optional */
	अगर (unpack_u32(e, &profile->path_flags, "path_flags"))
		profile->path_flags |= profile->label.flags &
			PATH_MEDIATE_DELETED;
	अन्यथा
		/* set a शेष value अगर path_flags field is not present */
		profile->path_flags = PATH_MEDIATE_DELETED;

	info = "failed to unpack profile capabilities";
	अगर (!unpack_u32(e, &(profile->caps.allow.cap[0]), शून्य))
		जाओ fail;
	अगर (!unpack_u32(e, &(profile->caps.audit.cap[0]), शून्य))
		जाओ fail;
	अगर (!unpack_u32(e, &(profile->caps.quiet.cap[0]), शून्य))
		जाओ fail;
	अगर (!unpack_u32(e, &पंचांगpcap.cap[0], शून्य))
		जाओ fail;

	info = "failed to unpack upper profile capabilities";
	अगर (unpack_nameX(e, AA_STRUCT, "caps64")) अणु
		/* optional upper half of 64 bit caps */
		अगर (!unpack_u32(e, &(profile->caps.allow.cap[1]), शून्य))
			जाओ fail;
		अगर (!unpack_u32(e, &(profile->caps.audit.cap[1]), शून्य))
			जाओ fail;
		अगर (!unpack_u32(e, &(profile->caps.quiet.cap[1]), शून्य))
			जाओ fail;
		अगर (!unpack_u32(e, &(पंचांगpcap.cap[1]), शून्य))
			जाओ fail;
		अगर (!unpack_nameX(e, AA_STRUCTEND, शून्य))
			जाओ fail;
	पूर्ण

	info = "failed to unpack extended profile capabilities";
	अगर (unpack_nameX(e, AA_STRUCT, "capsx")) अणु
		/* optional extended caps mediation mask */
		अगर (!unpack_u32(e, &(profile->caps.extended.cap[0]), शून्य))
			जाओ fail;
		अगर (!unpack_u32(e, &(profile->caps.extended.cap[1]), शून्य))
			जाओ fail;
		अगर (!unpack_nameX(e, AA_STRUCTEND, शून्य))
			जाओ fail;
	पूर्ण

	अगर (!unpack_xattrs(e, profile)) अणु
		info = "failed to unpack profile xattrs";
		जाओ fail;
	पूर्ण

	अगर (!unpack_rlimits(e, profile)) अणु
		info = "failed to unpack profile rlimits";
		जाओ fail;
	पूर्ण

	अगर (!unpack_secmark(e, profile)) अणु
		info = "failed to unpack profile secmark rules";
		जाओ fail;
	पूर्ण

	अगर (unpack_nameX(e, AA_STRUCT, "policydb")) अणु
		/* generic policy dfa - optional and may be शून्य */
		info = "failed to unpack policydb";
		profile->policy.dfa = unpack_dfa(e);
		अगर (IS_ERR(profile->policy.dfa)) अणु
			error = PTR_ERR(profile->policy.dfa);
			profile->policy.dfa = शून्य;
			जाओ fail;
		पूर्ण अन्यथा अगर (!profile->policy.dfa) अणु
			error = -EPROTO;
			जाओ fail;
		पूर्ण
		अगर (!unpack_u32(e, &profile->policy.start[0], "start"))
			/* शेष start state */
			profile->policy.start[0] = DFA_START;
		/* setup class index */
		क्रम (i = AA_CLASS_खाता; i <= AA_CLASS_LAST; i++) अणु
			profile->policy.start[i] =
				aa_dfa_next(profile->policy.dfa,
					    profile->policy.start[0],
					    i);
		पूर्ण
		अगर (!unpack_nameX(e, AA_STRUCTEND, शून्य))
			जाओ fail;
	पूर्ण अन्यथा
		profile->policy.dfa = aa_get_dfa(nulldfa);

	/* get file rules */
	profile->file.dfa = unpack_dfa(e);
	अगर (IS_ERR(profile->file.dfa)) अणु
		error = PTR_ERR(profile->file.dfa);
		profile->file.dfa = शून्य;
		info = "failed to unpack profile file rules";
		जाओ fail;
	पूर्ण अन्यथा अगर (profile->file.dfa) अणु
		अगर (!unpack_u32(e, &profile->file.start, "dfa_start"))
			/* शेष start state */
			profile->file.start = DFA_START;
	पूर्ण अन्यथा अगर (profile->policy.dfa &&
		   profile->policy.start[AA_CLASS_खाता]) अणु
		profile->file.dfa = aa_get_dfa(profile->policy.dfa);
		profile->file.start = profile->policy.start[AA_CLASS_खाता];
	पूर्ण अन्यथा
		profile->file.dfa = aa_get_dfa(nulldfa);

	अगर (!unpack_trans_table(e, profile)) अणु
		info = "failed to unpack profile transition table";
		जाओ fail;
	पूर्ण

	अगर (unpack_nameX(e, AA_STRUCT, "data")) अणु
		info = "out of memory";
		profile->data = kzalloc(माप(*profile->data), GFP_KERNEL);
		अगर (!profile->data)
			जाओ fail;

		params.nelem_hपूर्णांक = 3;
		params.key_len = माप(व्योम *);
		params.key_offset = दुरत्व(काष्ठा aa_data, key);
		params.head_offset = दुरत्व(काष्ठा aa_data, head);
		params.hashfn = strhash;
		params.obj_cmpfn = datacmp;

		अगर (rhashtable_init(profile->data, &params)) अणु
			info = "failed to init key, value hash table";
			जाओ fail;
		पूर्ण

		जबतक (unpack_strdup(e, &key, शून्य)) अणु
			data = kzalloc(माप(*data), GFP_KERNEL);
			अगर (!data) अणु
				kमुक्त_sensitive(key);
				जाओ fail;
			पूर्ण

			data->key = key;
			data->size = unpack_blob(e, &data->data, शून्य);
			data->data = kvmemdup(data->data, data->size);
			अगर (data->size && !data->data) अणु
				kमुक्त_sensitive(data->key);
				kमुक्त_sensitive(data);
				जाओ fail;
			पूर्ण

			rhashtable_insert_fast(profile->data, &data->head,
					       profile->data->p);
		पूर्ण

		अगर (!unpack_nameX(e, AA_STRUCTEND, शून्य)) अणु
			info = "failed to unpack end of key, value data table";
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (!unpack_nameX(e, AA_STRUCTEND, शून्य)) अणु
		info = "failed to unpack end of profile";
		जाओ fail;
	पूर्ण

	वापस profile;

fail:
	अगर (profile)
		name = शून्य;
	अन्यथा अगर (!name)
		name = "unknown";
	audit_अगरace(profile, शून्य, name, info, e, error);
	aa_मुक्त_profile(profile);

	वापस ERR_PTR(error);
पूर्ण

/**
 * verअगरy_head - unpack serialized stream header
 * @e: serialized data पढ़ो head (NOT शून्य)
 * @required: whether the header is required or optional
 * @ns: Returns - namespace अगर one is specअगरied अन्यथा शून्य (NOT शून्य)
 *
 * Returns: error or 0 अगर header is good
 */
अटल पूर्णांक verअगरy_header(काष्ठा aa_ext *e, पूर्णांक required, स्थिर अक्षर **ns)
अणु
	पूर्णांक error = -EPROTONOSUPPORT;
	स्थिर अक्षर *name = शून्य;
	*ns = शून्य;

	/* get the पूर्णांकerface version */
	अगर (!unpack_u32(e, &e->version, "version")) अणु
		अगर (required) अणु
			audit_अगरace(शून्य, शून्य, शून्य, "invalid profile format",
				    e, error);
			वापस error;
		पूर्ण
	पूर्ण

	/* Check that the पूर्णांकerface version is currently supported.
	 * अगर not specअगरied use previous version
	 * Mask off everything that is not kernel abi version
	 */
	अगर (VERSION_LT(e->version, v5) || VERSION_GT(e->version, v7)) अणु
		audit_अगरace(शून्य, शून्य, शून्य, "unsupported interface version",
			    e, error);
		वापस error;
	पूर्ण

	/* पढ़ो the namespace अगर present */
	अगर (unpack_str(e, &name, "namespace")) अणु
		अगर (*name == '\0') अणु
			audit_अगरace(शून्य, शून्य, शून्य, "invalid namespace name",
				    e, error);
			वापस error;
		पूर्ण
		अगर (*ns && म_भेद(*ns, name)) अणु
			audit_अगरace(शून्य, शून्य, शून्य, "invalid ns change", e,
				    error);
		पूर्ण अन्यथा अगर (!*ns) अणु
			*ns = kstrdup(name, GFP_KERNEL);
			अगर (!*ns)
				वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool verअगरy_xindex(पूर्णांक xindex, पूर्णांक table_size)
अणु
	पूर्णांक index, xtype;
	xtype = xindex & AA_X_TYPE_MASK;
	index = xindex & AA_X_INDEX_MASK;
	अगर (xtype == AA_X_TABLE && index >= table_size)
		वापस false;
	वापस true;
पूर्ण

/* verअगरy dfa xindexes are in range of transition tables */
अटल bool verअगरy_dfa_xindex(काष्ठा aa_dfa *dfa, पूर्णांक table_size)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < dfa->tables[YYTD_ID_ACCEPT]->td_lolen; i++) अणु
		अगर (!verअगरy_xindex(dfa_user_xindex(dfa, i), table_size))
			वापस false;
		अगर (!verअगरy_xindex(dfa_other_xindex(dfa, i), table_size))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * verअगरy_profile - Do post unpack analysis to verअगरy profile consistency
 * @profile: profile to verअगरy (NOT शून्य)
 *
 * Returns: 0 अगर passes verअगरication अन्यथा error
 */
अटल पूर्णांक verअगरy_profile(काष्ठा aa_profile *profile)
अणु
	अगर (profile->file.dfa &&
	    !verअगरy_dfa_xindex(profile->file.dfa,
			       profile->file.trans.size)) अणु
		audit_अगरace(profile, शून्य, शून्य, "Invalid named transition",
			    शून्य, -EPROTO);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

व्योम aa_load_ent_मुक्त(काष्ठा aa_load_ent *ent)
अणु
	अगर (ent) अणु
		aa_put_profile(ent->नाम);
		aa_put_profile(ent->old);
		aa_put_profile(ent->new);
		kमुक्त(ent->ns_name);
		kमुक्त_sensitive(ent);
	पूर्ण
पूर्ण

काष्ठा aa_load_ent *aa_load_ent_alloc(व्योम)
अणु
	काष्ठा aa_load_ent *ent = kzalloc(माप(*ent), GFP_KERNEL);
	अगर (ent)
		INIT_LIST_HEAD(&ent->list);
	वापस ent;
पूर्ण

अटल पूर्णांक deflate_compress(स्थिर अक्षर *src, माप_प्रकार slen, अक्षर **dst,
			    माप_प्रकार *dlen)
अणु
	पूर्णांक error;
	काष्ठा z_stream_s strm;
	व्योम *stgbuf, *dstbuf;
	माप_प्रकार stglen = deflateBound(slen);

	स_रखो(&strm, 0, माप(strm));

	अगर (stglen < slen)
		वापस -EFBIG;

	strm.workspace = kvzalloc(zlib_deflate_workspacesize(MAX_WBITS,
							     MAX_MEM_LEVEL),
				  GFP_KERNEL);
	अगर (!strm.workspace)
		वापस -ENOMEM;

	error = zlib_deflateInit(&strm, aa_g_rawdata_compression_level);
	अगर (error != Z_OK) अणु
		error = -ENOMEM;
		जाओ fail_deflate_init;
	पूर्ण

	stgbuf = kvzalloc(stglen, GFP_KERNEL);
	अगर (!stgbuf) अणु
		error = -ENOMEM;
		जाओ fail_stg_alloc;
	पूर्ण

	strm.next_in = src;
	strm.avail_in = slen;
	strm.next_out = stgbuf;
	strm.avail_out = stglen;

	error = zlib_deflate(&strm, Z_FINISH);
	अगर (error != Z_STREAM_END) अणु
		error = -EINVAL;
		जाओ fail_deflate;
	पूर्ण
	error = 0;

	अगर (is_vदो_स्मृति_addr(stgbuf)) अणु
		dstbuf = kvzalloc(strm.total_out, GFP_KERNEL);
		अगर (dstbuf) अणु
			स_नकल(dstbuf, stgbuf, strm.total_out);
			kvमुक्त(stgbuf);
		पूर्ण
	पूर्ण अन्यथा
		/*
		 * If the staging buffer was kदो_स्मृति'd, then using kपुनः_स्मृति is
		 * probably going to be faster. The destination buffer will
		 * always be smaller, so it's just shrunk, aव्योमing a स_नकल
		 */
		dstbuf = kपुनः_स्मृति(stgbuf, strm.total_out, GFP_KERNEL);

	अगर (!dstbuf) अणु
		error = -ENOMEM;
		जाओ fail_deflate;
	पूर्ण

	*dst = dstbuf;
	*dlen = strm.total_out;

fail_stg_alloc:
	zlib_deflateEnd(&strm);
fail_deflate_init:
	kvमुक्त(strm.workspace);
	वापस error;

fail_deflate:
	kvमुक्त(stgbuf);
	जाओ fail_stg_alloc;
पूर्ण

अटल पूर्णांक compress_loaddata(काष्ठा aa_loaddata *data)
अणु

	AA_BUG(data->compressed_size > 0);

	/*
	 * Shortcut the no compression हाल, अन्यथा we increase the amount of
	 * storage required by a small amount
	 */
	अगर (aa_g_rawdata_compression_level != 0) अणु
		व्योम *udata = data->data;
		पूर्णांक error = deflate_compress(udata, data->size, &data->data,
					     &data->compressed_size);
		अगर (error)
			वापस error;

		kvमुक्त(udata);
	पूर्ण अन्यथा
		data->compressed_size = data->size;

	वापस 0;
पूर्ण

/**
 * aa_unpack - unpack packed binary profile(s) data loaded from user space
 * @udata: user data copied to kmem  (NOT शून्य)
 * @lh: list to place unpacked profiles in a aa_repl_ws
 * @ns: Returns namespace profile is in अगर specअगरied अन्यथा शून्य (NOT शून्य)
 *
 * Unpack user data and वापस refcounted allocated profile(s) stored in
 * @lh in order of discovery, with the list chain stored in base.list
 * or error
 *
 * Returns: profile(s) on @lh अन्यथा error poपूर्णांकer अगर fails to unpack
 */
पूर्णांक aa_unpack(काष्ठा aa_loaddata *udata, काष्ठा list_head *lh,
	      स्थिर अक्षर **ns)
अणु
	काष्ठा aa_load_ent *पंचांगp, *ent;
	काष्ठा aa_profile *profile = शून्य;
	पूर्णांक error;
	काष्ठा aa_ext e = अणु
		.start = udata->data,
		.end = udata->data + udata->size,
		.pos = udata->data,
	पूर्ण;

	*ns = शून्य;
	जबतक (e.pos < e.end) अणु
		अक्षर *ns_name = शून्य;
		व्योम *start;
		error = verअगरy_header(&e, e.pos == e.start, ns);
		अगर (error)
			जाओ fail;

		start = e.pos;
		profile = unpack_profile(&e, &ns_name);
		अगर (IS_ERR(profile)) अणु
			error = PTR_ERR(profile);
			जाओ fail;
		पूर्ण

		error = verअगरy_profile(profile);
		अगर (error)
			जाओ fail_profile;

		अगर (aa_g_hash_policy)
			error = aa_calc_profile_hash(profile, e.version, start,
						     e.pos - start);
		अगर (error)
			जाओ fail_profile;

		ent = aa_load_ent_alloc();
		अगर (!ent) अणु
			error = -ENOMEM;
			जाओ fail_profile;
		पूर्ण

		ent->new = profile;
		ent->ns_name = ns_name;
		list_add_tail(&ent->list, lh);
	पूर्ण
	udata->abi = e.version & K_ABI_MASK;
	अगर (aa_g_hash_policy) अणु
		udata->hash = aa_calc_hash(udata->data, udata->size);
		अगर (IS_ERR(udata->hash)) अणु
			error = PTR_ERR(udata->hash);
			udata->hash = शून्य;
			जाओ fail;
		पूर्ण
	पूर्ण
	error = compress_loaddata(udata);
	अगर (error)
		जाओ fail;
	वापस 0;

fail_profile:
	aa_put_profile(profile);

fail:
	list_क्रम_each_entry_safe(ent, पंचांगp, lh, list) अणु
		list_del_init(&ent->list);
		aa_load_ent_मुक्त(ent);
	पूर्ण

	वापस error;
पूर्ण

#अगर_घोषित CONFIG_SECURITY_APPARMOR_KUNIT_TEST
#समावेश "policy_unpack_test.c"
#पूर्ण_अगर /* CONFIG_SECURITY_APPARMOR_KUNIT_TEST */
