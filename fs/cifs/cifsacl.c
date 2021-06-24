<शैली गुरु>
/*
 *   fs/cअगरs/cअगरsacl.c
 *
 *   Copyright (C) International Business Machines  Corp., 2007,2008
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *
 *   Contains the routines क्रम mapping CIFS/NTFS ACLs
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/keyctl.h>
#समावेश <linux/key-type.h>
#समावेश <keys/user-type.h>
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsacl.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"
#समावेश "fs_context.h"

/* security id क्रम everyone/world प्रणाली group */
अटल स्थिर काष्ठा cअगरs_sid sid_everyone = अणु
	1, 1, अणु0, 0, 0, 0, 0, 1पूर्ण, अणु0पूर्ण पूर्ण;
/* security id क्रम Authenticated Users प्रणाली group */
अटल स्थिर काष्ठा cअगरs_sid sid_authusers = अणु
	1, 1, अणु0, 0, 0, 0, 0, 5पूर्ण, अणुcpu_to_le32(11)पूर्ण पूर्ण;

/* S-1-22-1 Unmapped Unix users */
अटल स्थिर काष्ठा cअगरs_sid sid_unix_users = अणु1, 1, अणु0, 0, 0, 0, 0, 22पूर्ण,
		अणुcpu_to_le32(1), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण;

/* S-1-22-2 Unmapped Unix groups */
अटल स्थिर काष्ठा cअगरs_sid sid_unix_groups = अणु 1, 1, अणु0, 0, 0, 0, 0, 22पूर्ण,
		अणुcpu_to_le32(2), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण;

/*
 * See https://technet.microsoft.com/en-us/library/hh509017(v=ws.10).aspx
 */

/* S-1-5-88 MS NFS and Apple style UID/GID/mode */

/* S-1-5-88-1 Unix uid */
अटल स्थिर काष्ठा cअगरs_sid sid_unix_NFS_users = अणु 1, 2, अणु0, 0, 0, 0, 0, 5पूर्ण,
	अणुcpu_to_le32(88),
	 cpu_to_le32(1), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण;

/* S-1-5-88-2 Unix gid */
अटल स्थिर काष्ठा cअगरs_sid sid_unix_NFS_groups = अणु 1, 2, अणु0, 0, 0, 0, 0, 5पूर्ण,
	अणुcpu_to_le32(88),
	 cpu_to_le32(2), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण;

/* S-1-5-88-3 Unix mode */
अटल स्थिर काष्ठा cअगरs_sid sid_unix_NFS_mode = अणु 1, 2, अणु0, 0, 0, 0, 0, 5पूर्ण,
	अणुcpu_to_le32(88),
	 cpu_to_le32(3), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण;

अटल स्थिर काष्ठा cred *root_cred;

अटल पूर्णांक
cअगरs_idmap_key_instantiate(काष्ठा key *key, काष्ठा key_preparsed_payload *prep)
अणु
	अक्षर *payload;

	/*
	 * If the payload is less than or equal to the size of a poपूर्णांकer, then
	 * an allocation here is wasteful. Just copy the data directly to the
	 * payload.value जोड़ member instead.
	 *
	 * With this however, you must check the datalen beक्रमe trying to
	 * dereference payload.data!
	 */
	अगर (prep->datalen <= माप(key->payload)) अणु
		key->payload.data[0] = शून्य;
		स_नकल(&key->payload, prep->data, prep->datalen);
	पूर्ण अन्यथा अणु
		payload = kmemdup(prep->data, prep->datalen, GFP_KERNEL);
		अगर (!payload)
			वापस -ENOMEM;
		key->payload.data[0] = payload;
	पूर्ण

	key->datalen = prep->datalen;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
cअगरs_idmap_key_destroy(काष्ठा key *key)
अणु
	अगर (key->datalen > माप(key->payload))
		kमुक्त(key->payload.data[0]);
पूर्ण

अटल काष्ठा key_type cअगरs_idmap_key_type = अणु
	.name        = "cifs.idmap",
	.instantiate = cअगरs_idmap_key_instantiate,
	.destroy     = cअगरs_idmap_key_destroy,
	.describe    = user_describe,
पूर्ण;

अटल अक्षर *
sid_to_key_str(काष्ठा cअगरs_sid *sidptr, अचिन्हित पूर्णांक type)
अणु
	पूर्णांक i, len;
	अचिन्हित पूर्णांक saval;
	अक्षर *sidstr, *strptr;
	अचिन्हित दीर्घ दीर्घ id_auth_val;

	/* 3 bytes क्रम prefix */
	sidstr = kदो_स्मृति(3 + SID_STRING_BASE_SIZE +
			 (SID_STRING_SUBAUTH_SIZE * sidptr->num_subauth),
			 GFP_KERNEL);
	अगर (!sidstr)
		वापस sidstr;

	strptr = sidstr;
	len = प्र_लिखो(strptr, "%cs:S-%hhu", type == SIDOWNER ? 'o' : 'g',
			sidptr->revision);
	strptr += len;

	/* The authority field is a single 48-bit number */
	id_auth_val = (अचिन्हित दीर्घ दीर्घ)sidptr->authority[5];
	id_auth_val |= (अचिन्हित दीर्घ दीर्घ)sidptr->authority[4] << 8;
	id_auth_val |= (अचिन्हित दीर्घ दीर्घ)sidptr->authority[3] << 16;
	id_auth_val |= (अचिन्हित दीर्घ दीर्घ)sidptr->authority[2] << 24;
	id_auth_val |= (अचिन्हित दीर्घ दीर्घ)sidptr->authority[1] << 32;
	id_auth_val |= (अचिन्हित दीर्घ दीर्घ)sidptr->authority[0] << 48;

	/*
	 * MS-DTYP states that अगर the authority is >= 2^32, then it should be
	 * expressed as a hex value.
	 */
	अगर (id_auth_val <= अच_पूर्णांक_उच्च)
		len = प्र_लिखो(strptr, "-%llu", id_auth_val);
	अन्यथा
		len = प्र_लिखो(strptr, "-0x%llx", id_auth_val);

	strptr += len;

	क्रम (i = 0; i < sidptr->num_subauth; ++i) अणु
		saval = le32_to_cpu(sidptr->sub_auth[i]);
		len = प्र_लिखो(strptr, "-%u", saval);
		strptr += len;
	पूर्ण

	वापस sidstr;
पूर्ण

/*
 * अगर the two SIDs (roughly equivalent to a UUID क्रम a user or group) are
 * the same वापसs zero, अगर they करो not match वापसs non-zero.
 */
अटल पूर्णांक
compare_sids(स्थिर काष्ठा cअगरs_sid *ctsid, स्थिर काष्ठा cअगरs_sid *cwsid)
अणु
	पूर्णांक i;
	पूर्णांक num_subauth, num_sat, num_saw;

	अगर ((!ctsid) || (!cwsid))
		वापस 1;

	/* compare the revision */
	अगर (ctsid->revision != cwsid->revision) अणु
		अगर (ctsid->revision > cwsid->revision)
			वापस 1;
		अन्यथा
			वापस -1;
	पूर्ण

	/* compare all of the six auth values */
	क्रम (i = 0; i < NUM_AUTHS; ++i) अणु
		अगर (ctsid->authority[i] != cwsid->authority[i]) अणु
			अगर (ctsid->authority[i] > cwsid->authority[i])
				वापस 1;
			अन्यथा
				वापस -1;
		पूर्ण
	पूर्ण

	/* compare all of the subauth values अगर any */
	num_sat = ctsid->num_subauth;
	num_saw = cwsid->num_subauth;
	num_subauth = num_sat < num_saw ? num_sat : num_saw;
	अगर (num_subauth) अणु
		क्रम (i = 0; i < num_subauth; ++i) अणु
			अगर (ctsid->sub_auth[i] != cwsid->sub_auth[i]) अणु
				अगर (le32_to_cpu(ctsid->sub_auth[i]) >
					le32_to_cpu(cwsid->sub_auth[i]))
					वापस 1;
				अन्यथा
					वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0; /* sids compare/match */
पूर्ण

अटल bool
is_well_known_sid(स्थिर काष्ठा cअगरs_sid *psid, uपूर्णांक32_t *puid, bool is_group)
अणु
	पूर्णांक i;
	पूर्णांक num_subauth;
	स्थिर काष्ठा cअगरs_sid *pwell_known_sid;

	अगर (!psid || (puid == शून्य))
		वापस false;

	num_subauth = psid->num_subauth;

	/* check अगर Mac (or Winकरोws NFS) vs. Samba क्रमmat क्रम Unix owner SID */
	अगर (num_subauth == 2) अणु
		अगर (is_group)
			pwell_known_sid = &sid_unix_groups;
		अन्यथा
			pwell_known_sid = &sid_unix_users;
	पूर्ण अन्यथा अगर (num_subauth == 3) अणु
		अगर (is_group)
			pwell_known_sid = &sid_unix_NFS_groups;
		अन्यथा
			pwell_known_sid = &sid_unix_NFS_users;
	पूर्ण अन्यथा
		वापस false;

	/* compare the revision */
	अगर (psid->revision != pwell_known_sid->revision)
		वापस false;

	/* compare all of the six auth values */
	क्रम (i = 0; i < NUM_AUTHS; ++i) अणु
		अगर (psid->authority[i] != pwell_known_sid->authority[i]) अणु
			cअगरs_dbg(FYI, "auth %d did not match\n", i);
			वापस false;
		पूर्ण
	पूर्ण

	अगर (num_subauth == 2) अणु
		अगर (psid->sub_auth[0] != pwell_known_sid->sub_auth[0])
			वापस false;

		*puid = le32_to_cpu(psid->sub_auth[1]);
	पूर्ण अन्यथा /* 3 subauths, ie Winकरोws/Mac style */ अणु
		*puid = le32_to_cpu(psid->sub_auth[0]);
		अगर ((psid->sub_auth[0] != pwell_known_sid->sub_auth[0]) ||
		    (psid->sub_auth[1] != pwell_known_sid->sub_auth[1]))
			वापस false;

		*puid = le32_to_cpu(psid->sub_auth[2]);
	पूर्ण

	cअगरs_dbg(FYI, "Unix UID %d returned from SID\n", *puid);
	वापस true; /* well known sid found, uid वापसed */
पूर्ण

अटल __u16
cअगरs_copy_sid(काष्ठा cअगरs_sid *dst, स्थिर काष्ठा cअगरs_sid *src)
अणु
	पूर्णांक i;
	__u16 size = 1 + 1 + 6;

	dst->revision = src->revision;
	dst->num_subauth = min_t(u8, src->num_subauth, SID_MAX_SUB_AUTHORITIES);
	क्रम (i = 0; i < NUM_AUTHS; ++i)
		dst->authority[i] = src->authority[i];
	क्रम (i = 0; i < dst->num_subauth; ++i)
		dst->sub_auth[i] = src->sub_auth[i];
	size += (dst->num_subauth * 4);

	वापस size;
पूर्ण

अटल पूर्णांक
id_to_sid(अचिन्हित पूर्णांक cid, uपूर्णांक sidtype, काष्ठा cअगरs_sid *ssid)
अणु
	पूर्णांक rc;
	काष्ठा key *sidkey;
	काष्ठा cअगरs_sid *ksid;
	अचिन्हित पूर्णांक ksid_size;
	अक्षर desc[3 + 10 + 1]; /* 3 byte prefix + 10 bytes क्रम value + शून्य */
	स्थिर काष्ठा cred *saved_cred;

	rc = snम_लिखो(desc, माप(desc), "%ci:%u",
			sidtype == SIDOWNER ? 'o' : 'g', cid);
	अगर (rc >= माप(desc))
		वापस -EINVAL;

	rc = 0;
	saved_cred = override_creds(root_cred);
	sidkey = request_key(&cअगरs_idmap_key_type, desc, "");
	अगर (IS_ERR(sidkey)) अणु
		rc = -EINVAL;
		cअगरs_dbg(FYI, "%s: Can't map %cid %u to a SID\n",
			 __func__, sidtype == SIDOWNER ? 'u' : 'g', cid);
		जाओ out_revert_creds;
	पूर्ण अन्यथा अगर (sidkey->datalen < CIFS_SID_BASE_SIZE) अणु
		rc = -EIO;
		cअगरs_dbg(FYI, "%s: Downcall contained malformed key (datalen=%hu)\n",
			 __func__, sidkey->datalen);
		जाओ invalidate_key;
	पूर्ण

	/*
	 * A sid is usually too large to be embedded in payload.value, but अगर
	 * there are no subauthorities and the host has 8-byte poपूर्णांकers, then
	 * it could be.
	 */
	ksid = sidkey->datalen <= माप(sidkey->payload) ?
		(काष्ठा cअगरs_sid *)&sidkey->payload :
		(काष्ठा cअगरs_sid *)sidkey->payload.data[0];

	ksid_size = CIFS_SID_BASE_SIZE + (ksid->num_subauth * माप(__le32));
	अगर (ksid_size > sidkey->datalen) अणु
		rc = -EIO;
		cअगरs_dbg(FYI, "%s: Downcall contained malformed key (datalen=%hu, ksid_size=%u)\n",
			 __func__, sidkey->datalen, ksid_size);
		जाओ invalidate_key;
	पूर्ण

	cअगरs_copy_sid(ssid, ksid);
out_key_put:
	key_put(sidkey);
out_revert_creds:
	revert_creds(saved_cred);
	वापस rc;

invalidate_key:
	key_invalidate(sidkey);
	जाओ out_key_put;
पूर्ण

पूर्णांक
sid_to_id(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा cअगरs_sid *psid,
		काष्ठा cअगरs_fattr *fattr, uपूर्णांक sidtype)
अणु
	पूर्णांक rc = 0;
	काष्ठा key *sidkey;
	अक्षर *sidstr;
	स्थिर काष्ठा cred *saved_cred;
	kuid_t fuid = cअगरs_sb->ctx->linux_uid;
	kgid_t fgid = cअगरs_sb->ctx->linux_gid;

	/*
	 * If we have too many subauthorities, then something is really wrong.
	 * Just वापस an error.
	 */
	अगर (unlikely(psid->num_subauth > SID_MAX_SUB_AUTHORITIES)) अणु
		cअगरs_dbg(FYI, "%s: %u subauthorities is too many!\n",
			 __func__, psid->num_subauth);
		वापस -EIO;
	पूर्ण

	अगर ((cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_UID_FROM_ACL) ||
	    (cअगरs_sb_master_tcon(cअगरs_sb)->posix_extensions)) अणु
		uपूर्णांक32_t unix_id;
		bool is_group;

		अगर (sidtype != SIDOWNER)
			is_group = true;
		अन्यथा
			is_group = false;

		अगर (is_well_known_sid(psid, &unix_id, is_group) == false)
			जाओ try_upcall_to_get_id;

		अगर (is_group) अणु
			kgid_t gid;
			gid_t id;

			id = (gid_t)unix_id;
			gid = make_kgid(&init_user_ns, id);
			अगर (gid_valid(gid)) अणु
				fgid = gid;
				जाओ got_valid_id;
			पूर्ण
		पूर्ण अन्यथा अणु
			kuid_t uid;
			uid_t id;

			id = (uid_t)unix_id;
			uid = make_kuid(&init_user_ns, id);
			अगर (uid_valid(uid)) अणु
				fuid = uid;
				जाओ got_valid_id;
			पूर्ण
		पूर्ण
		/* If unable to find uid/gid easily from SID try via upcall */
	पूर्ण

try_upcall_to_get_id:
	sidstr = sid_to_key_str(psid, sidtype);
	अगर (!sidstr)
		वापस -ENOMEM;

	saved_cred = override_creds(root_cred);
	sidkey = request_key(&cअगरs_idmap_key_type, sidstr, "");
	अगर (IS_ERR(sidkey)) अणु
		rc = -EINVAL;
		cअगरs_dbg(FYI, "%s: Can't map SID %s to a %cid\n",
			 __func__, sidstr, sidtype == SIDOWNER ? 'u' : 'g');
		जाओ out_revert_creds;
	पूर्ण

	/*
	 * FIXME: Here we assume that uid_t and gid_t are same size. It's
	 * probably a safe assumption but might be better to check based on
	 * sidtype.
	 */
	BUILD_BUG_ON(माप(uid_t) != माप(gid_t));
	अगर (sidkey->datalen != माप(uid_t)) अणु
		rc = -EIO;
		cअगरs_dbg(FYI, "%s: Downcall contained malformed key (datalen=%hu)\n",
			 __func__, sidkey->datalen);
		key_invalidate(sidkey);
		जाओ out_key_put;
	पूर्ण

	अगर (sidtype == SIDOWNER) अणु
		kuid_t uid;
		uid_t id;
		स_नकल(&id, &sidkey->payload.data[0], माप(uid_t));
		uid = make_kuid(&init_user_ns, id);
		अगर (uid_valid(uid))
			fuid = uid;
	पूर्ण अन्यथा अणु
		kgid_t gid;
		gid_t id;
		स_नकल(&id, &sidkey->payload.data[0], माप(gid_t));
		gid = make_kgid(&init_user_ns, id);
		अगर (gid_valid(gid))
			fgid = gid;
	पूर्ण

out_key_put:
	key_put(sidkey);
out_revert_creds:
	revert_creds(saved_cred);
	kमुक्त(sidstr);

	/*
	 * Note that we वापस 0 here unconditionally. If the mapping
	 * fails then we just fall back to using the ctx->linux_uid/linux_gid.
	 */
got_valid_id:
	rc = 0;
	अगर (sidtype == SIDOWNER)
		fattr->cf_uid = fuid;
	अन्यथा
		fattr->cf_gid = fgid;
	वापस rc;
पूर्ण

पूर्णांक
init_cअगरs_idmap(व्योम)
अणु
	काष्ठा cred *cred;
	काष्ठा key *keyring;
	पूर्णांक ret;

	cअगरs_dbg(FYI, "Registering the %s key type\n",
		 cअगरs_idmap_key_type.name);

	/* create an override credential set with a special thपढ़ो keyring in
	 * which requests are cached
	 *
	 * this is used to prevent malicious redirections from being installed
	 * with add_key().
	 */
	cred = prepare_kernel_cred(शून्य);
	अगर (!cred)
		वापस -ENOMEM;

	keyring = keyring_alloc(".cifs_idmap",
				GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, cred,
				(KEY_POS_ALL & ~KEY_POS_SETATTR) |
				KEY_USR_VIEW | KEY_USR_READ,
				KEY_ALLOC_NOT_IN_QUOTA, शून्य, शून्य);
	अगर (IS_ERR(keyring)) अणु
		ret = PTR_ERR(keyring);
		जाओ failed_put_cred;
	पूर्ण

	ret = रेजिस्टर_key_type(&cअगरs_idmap_key_type);
	अगर (ret < 0)
		जाओ failed_put_key;

	/* inकाष्ठा request_key() to use this special keyring as a cache क्रम
	 * the results it looks up */
	set_bit(KEY_FLAG_ROOT_CAN_CLEAR, &keyring->flags);
	cred->thपढ़ो_keyring = keyring;
	cred->jit_keyring = KEY_REQKEY_DEFL_THREAD_KEYRING;
	root_cred = cred;

	cअगरs_dbg(FYI, "cifs idmap keyring: %d\n", key_serial(keyring));
	वापस 0;

failed_put_key:
	key_put(keyring);
failed_put_cred:
	put_cred(cred);
	वापस ret;
पूर्ण

व्योम
निकास_cअगरs_idmap(व्योम)
अणु
	key_revoke(root_cred->thपढ़ो_keyring);
	unरेजिस्टर_key_type(&cअगरs_idmap_key_type);
	put_cred(root_cred);
	cअगरs_dbg(FYI, "Unregistered %s key type\n", cअगरs_idmap_key_type.name);
पूर्ण

/* copy ntsd, owner sid, and group sid from a security descriptor to another */
अटल __u32 copy_sec_desc(स्थिर काष्ठा cअगरs_ntsd *pntsd,
				काष्ठा cअगरs_ntsd *pnntsd,
				__u32 sidsoffset,
				काष्ठा cअगरs_sid *घातnersid,
				काष्ठा cअगरs_sid *pgrpsid)
अणु
	काष्ठा cअगरs_sid *owner_sid_ptr, *group_sid_ptr;
	काष्ठा cअगरs_sid *nowner_sid_ptr, *ngroup_sid_ptr;

	/* copy security descriptor control portion */
	pnntsd->revision = pntsd->revision;
	pnntsd->type = pntsd->type;
	pnntsd->dacloffset = cpu_to_le32(माप(काष्ठा cअगरs_ntsd));
	pnntsd->sacloffset = 0;
	pnntsd->osiकरोffset = cpu_to_le32(sidsoffset);
	pnntsd->gsiकरोffset = cpu_to_le32(sidsoffset + माप(काष्ठा cअगरs_sid));

	/* copy owner sid */
	अगर (घातnersid)
		owner_sid_ptr = घातnersid;
	अन्यथा
		owner_sid_ptr = (काष्ठा cअगरs_sid *)((अक्षर *)pntsd +
				le32_to_cpu(pntsd->osiकरोffset));
	nowner_sid_ptr = (काष्ठा cअगरs_sid *)((अक्षर *)pnntsd + sidsoffset);
	cअगरs_copy_sid(nowner_sid_ptr, owner_sid_ptr);

	/* copy group sid */
	अगर (pgrpsid)
		group_sid_ptr = pgrpsid;
	अन्यथा
		group_sid_ptr = (काष्ठा cअगरs_sid *)((अक्षर *)pntsd +
				le32_to_cpu(pntsd->gsiकरोffset));
	ngroup_sid_ptr = (काष्ठा cअगरs_sid *)((अक्षर *)pnntsd + sidsoffset +
					माप(काष्ठा cअगरs_sid));
	cअगरs_copy_sid(ngroup_sid_ptr, group_sid_ptr);

	वापस sidsoffset + (2 * माप(काष्ठा cअगरs_sid));
पूर्ण


/*
   change posix mode to reflect permissions
   pmode is the existing mode (we only want to overग_लिखो part of this
   bits to set can be: S_IRWXU, S_IRWXG or S_IRWXO ie 00700 or 00070 or 00007
*/
अटल व्योम access_flags_to_mode(__le32 ace_flags, पूर्णांक type, umode_t *pmode,
				 umode_t *pdenied, umode_t mask)
अणु
	__u32 flags = le32_to_cpu(ace_flags);
	/*
	 * Do not assume "preferred" or "canonical" order.
	 * The first DENY or ALLOW ACE which matches perfectly is
	 * the permission to be used. Once allowed or denied, same
	 * permission in later ACEs करो not matter.
	 */

	/* If not alपढ़ोy allowed, deny these bits */
	अगर (type == ACCESS_DENIED) अणु
		अगर (flags & GENERIC_ALL &&
				!(*pmode & mask & 0777))
			*pdenied |= mask & 0777;

		अगर (((flags & GENERIC_WRITE) ||
				((flags & खाता_WRITE_RIGHTS) == खाता_WRITE_RIGHTS)) &&
				!(*pmode & mask & 0222))
			*pdenied |= mask & 0222;

		अगर (((flags & GENERIC_READ) ||
				((flags & खाता_READ_RIGHTS) == खाता_READ_RIGHTS)) &&
				!(*pmode & mask & 0444))
			*pdenied |= mask & 0444;

		अगर (((flags & GENERIC_EXECUTE) ||
				((flags & खाता_EXEC_RIGHTS) == खाता_EXEC_RIGHTS)) &&
				!(*pmode & mask & 0111))
			*pdenied |= mask & 0111;

		वापस;
	पूर्ण अन्यथा अगर (type != ACCESS_ALLOWED) अणु
		cअगरs_dbg(VFS, "unknown access control type %d\n", type);
		वापस;
	पूर्ण
	/* अन्यथा ACCESS_ALLOWED type */

	अगर ((flags & GENERIC_ALL) &&
			!(*pdenied & mask & 0777)) अणु
		*pmode |= mask & 0777;
		cअगरs_dbg(NOISY, "all perms\n");
		वापस;
	पूर्ण

	अगर (((flags & GENERIC_WRITE) ||
			((flags & खाता_WRITE_RIGHTS) == खाता_WRITE_RIGHTS)) &&
			!(*pdenied & mask & 0222))
		*pmode |= mask & 0222;

	अगर (((flags & GENERIC_READ) ||
			((flags & खाता_READ_RIGHTS) == खाता_READ_RIGHTS)) &&
			!(*pdenied & mask & 0444))
		*pmode |= mask & 0444;

	अगर (((flags & GENERIC_EXECUTE) ||
			((flags & खाता_EXEC_RIGHTS) == खाता_EXEC_RIGHTS)) &&
			!(*pdenied & mask & 0111))
		*pmode |= mask & 0111;

	/* If DELETE_CHILD is set only on an owner ACE, set sticky bit */
	अगर (flags & खाता_DELETE_CHILD) अणु
		अगर (mask == ACL_OWNER_MASK) अणु
			अगर (!(*pdenied & 01000))
				*pmode |= 01000;
		पूर्ण अन्यथा अगर (!(*pdenied & 01000)) अणु
			*pmode &= ~01000;
			*pdenied |= 01000;
		पूर्ण
	पूर्ण

	cअगरs_dbg(NOISY, "access flags 0x%x mode now %04o\n", flags, *pmode);
	वापस;
पूर्ण

/*
   Generate access flags to reflect permissions mode is the existing mode.
   This function is called क्रम every ACE in the DACL whose SID matches
   with either owner or group or everyone.
*/

अटल व्योम mode_to_access_flags(umode_t mode, umode_t bits_to_use,
				__u32 *pace_flags)
अणु
	/* reset access mask */
	*pace_flags = 0x0;

	/* bits to use are either S_IRWXU or S_IRWXG or S_IRWXO */
	mode &= bits_to_use;

	/* check क्रम R/W/X UGO since we करो not know whose flags
	   is this but we have cleared all the bits sans RWX क्रम
	   either user or group or other as per bits_to_use */
	अगर (mode & S_IRUGO)
		*pace_flags |= SET_खाता_READ_RIGHTS;
	अगर (mode & S_IWUGO)
		*pace_flags |= SET_खाता_WRITE_RIGHTS;
	अगर (mode & S_IXUGO)
		*pace_flags |= SET_खाता_EXEC_RIGHTS;

	cअगरs_dbg(NOISY, "mode: %04o, access flags now 0x%x\n",
		 mode, *pace_flags);
	वापस;
पूर्ण

अटल __u16 cअगरs_copy_ace(काष्ठा cअगरs_ace *dst, काष्ठा cअगरs_ace *src, काष्ठा cअगरs_sid *psid)
अणु
	__u16 size = 1 + 1 + 2 + 4;

	dst->type = src->type;
	dst->flags = src->flags;
	dst->access_req = src->access_req;

	/* Check अगर there's a replacement sid specअगरied */
	अगर (psid)
		size += cअगरs_copy_sid(&dst->sid, psid);
	अन्यथा
		size += cअगरs_copy_sid(&dst->sid, &src->sid);

	dst->size = cpu_to_le16(size);

	वापस size;
पूर्ण

अटल __u16 fill_ace_क्रम_sid(काष्ठा cअगरs_ace *pntace,
			स्थिर काष्ठा cअगरs_sid *psid, __u64 nmode,
			umode_t bits, __u8 access_type,
			bool allow_delete_child)
अणु
	पूर्णांक i;
	__u16 size = 0;
	__u32 access_req = 0;

	pntace->type = access_type;
	pntace->flags = 0x0;
	mode_to_access_flags(nmode, bits, &access_req);

	अगर (access_type == ACCESS_ALLOWED && allow_delete_child)
		access_req |= खाता_DELETE_CHILD;

	अगर (access_type == ACCESS_ALLOWED && !access_req)
		access_req = SET_MINIMUM_RIGHTS;
	अन्यथा अगर (access_type == ACCESS_DENIED)
		access_req &= ~SET_MINIMUM_RIGHTS;

	pntace->access_req = cpu_to_le32(access_req);

	pntace->sid.revision = psid->revision;
	pntace->sid.num_subauth = psid->num_subauth;
	क्रम (i = 0; i < NUM_AUTHS; i++)
		pntace->sid.authority[i] = psid->authority[i];
	क्रम (i = 0; i < psid->num_subauth; i++)
		pntace->sid.sub_auth[i] = psid->sub_auth[i];

	size = 1 + 1 + 2 + 4 + 1 + 1 + 6 + (psid->num_subauth * 4);
	pntace->size = cpu_to_le16(size);

	वापस size;
पूर्ण


#अगर_घोषित CONFIG_CIFS_DEBUG2
अटल व्योम dump_ace(काष्ठा cअगरs_ace *pace, अक्षर *end_of_acl)
अणु
	पूर्णांक num_subauth;

	/* validate that we करो not go past end of acl */

	अगर (le16_to_cpu(pace->size) < 16) अणु
		cअगरs_dbg(VFS, "ACE too small %d\n", le16_to_cpu(pace->size));
		वापस;
	पूर्ण

	अगर (end_of_acl < (अक्षर *)pace + le16_to_cpu(pace->size)) अणु
		cअगरs_dbg(VFS, "ACL too small to parse ACE\n");
		वापस;
	पूर्ण

	num_subauth = pace->sid.num_subauth;
	अगर (num_subauth) अणु
		पूर्णांक i;
		cअगरs_dbg(FYI, "ACE revision %d num_auth %d type %d flags %d size %d\n",
			 pace->sid.revision, pace->sid.num_subauth, pace->type,
			 pace->flags, le16_to_cpu(pace->size));
		क्रम (i = 0; i < num_subauth; ++i) अणु
			cअगरs_dbg(FYI, "ACE sub_auth[%d]: 0x%x\n",
				 i, le32_to_cpu(pace->sid.sub_auth[i]));
		पूर्ण

		/* BB add length check to make sure that we करो not have huge
			num auths and thereक्रमe go off the end */
	पूर्ण

	वापस;
पूर्ण
#पूर्ण_अगर

अटल व्योम parse_dacl(काष्ठा cअगरs_acl *pdacl, अक्षर *end_of_acl,
		       काष्ठा cअगरs_sid *घातnersid, काष्ठा cअगरs_sid *pgrpsid,
		       काष्ठा cअगरs_fattr *fattr, bool mode_from_special_sid)
अणु
	पूर्णांक i;
	पूर्णांक num_aces = 0;
	पूर्णांक acl_size;
	अक्षर *acl_base;
	काष्ठा cअगरs_ace **ppace;

	/* BB need to add parm so we can store the SID BB */

	अगर (!pdacl) अणु
		/* no DACL in the security descriptor, set
		   all the permissions क्रम user/group/other */
		fattr->cf_mode |= 0777;
		वापस;
	पूर्ण

	/* validate that we करो not go past end of acl */
	अगर (end_of_acl < (अक्षर *)pdacl + le16_to_cpu(pdacl->size)) अणु
		cअगरs_dbg(VFS, "ACL too small to parse DACL\n");
		वापस;
	पूर्ण

	cअगरs_dbg(NOISY, "DACL revision %d size %d num aces %d\n",
		 le16_to_cpu(pdacl->revision), le16_to_cpu(pdacl->size),
		 le32_to_cpu(pdacl->num_aces));

	/* reset rwx permissions क्रम user/group/other.
	   Also, अगर num_aces is 0 i.e. DACL has no ACEs,
	   user/group/other have no permissions */
	fattr->cf_mode &= ~(0777);

	acl_base = (अक्षर *)pdacl;
	acl_size = माप(काष्ठा cअगरs_acl);

	num_aces = le32_to_cpu(pdacl->num_aces);
	अगर (num_aces > 0) अणु
		umode_t denied_mode = 0;

		अगर (num_aces > अच_दीर्घ_उच्च / माप(काष्ठा cअगरs_ace *))
			वापस;
		ppace = kदो_स्मृति_array(num_aces, माप(काष्ठा cअगरs_ace *),
				      GFP_KERNEL);
		अगर (!ppace)
			वापस;

		क्रम (i = 0; i < num_aces; ++i) अणु
			ppace[i] = (काष्ठा cअगरs_ace *) (acl_base + acl_size);
#अगर_घोषित CONFIG_CIFS_DEBUG2
			dump_ace(ppace[i], end_of_acl);
#पूर्ण_अगर
			अगर (mode_from_special_sid &&
			    (compare_sids(&(ppace[i]->sid),
					  &sid_unix_NFS_mode) == 0)) अणु
				/*
				 * Full permissions are:
				 * 07777 = S_ISUID | S_ISGID | S_ISVTX |
				 *         S_IRWXU | S_IRWXG | S_IRWXO
				 */
				fattr->cf_mode &= ~07777;
				fattr->cf_mode |=
					le32_to_cpu(ppace[i]->sid.sub_auth[2]);
				अवरोध;
			पूर्ण अन्यथा अणु
				अगर (compare_sids(&(ppace[i]->sid), घातnersid) == 0) अणु
					access_flags_to_mode(ppace[i]->access_req,
							ppace[i]->type,
							&fattr->cf_mode,
							&denied_mode,
							ACL_OWNER_MASK);
				पूर्ण अन्यथा अगर (compare_sids(&(ppace[i]->sid), pgrpsid) == 0) अणु
					access_flags_to_mode(ppace[i]->access_req,
							ppace[i]->type,
							&fattr->cf_mode,
							&denied_mode,
							ACL_GROUP_MASK);
				पूर्ण अन्यथा अगर ((compare_sids(&(ppace[i]->sid), &sid_everyone) == 0) ||
						(compare_sids(&(ppace[i]->sid), &sid_authusers) == 0)) अणु
					access_flags_to_mode(ppace[i]->access_req,
							ppace[i]->type,
							&fattr->cf_mode,
							&denied_mode,
							ACL_EVERYONE_MASK);
				पूर्ण
			पूर्ण


/*			स_नकल((व्योम *)(&(cअगरscred->aces[i])),
				(व्योम *)ppace[i],
				माप(काष्ठा cअगरs_ace)); */

			acl_base = (अक्षर *)ppace[i];
			acl_size = le16_to_cpu(ppace[i]->size);
		पूर्ण

		kमुक्त(ppace);
	पूर्ण

	वापस;
पूर्ण

अचिन्हित पूर्णांक setup_authusers_ACE(काष्ठा cअगरs_ace *pntace)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक ace_size = 20;

	pntace->type = ACCESS_ALLOWED_ACE_TYPE;
	pntace->flags = 0x0;
	pntace->access_req = cpu_to_le32(GENERIC_ALL);
	pntace->sid.num_subauth = 1;
	pntace->sid.revision = 1;
	क्रम (i = 0; i < NUM_AUTHS; i++)
		pntace->sid.authority[i] =  sid_authusers.authority[i];

	pntace->sid.sub_auth[0] =  sid_authusers.sub_auth[0];

	/* size = 1 + 1 + 2 + 4 + 1 + 1 + 6 + (psid->num_subauth*4) */
	pntace->size = cpu_to_le16(ace_size);
	वापस ace_size;
पूर्ण

/*
 * Fill in the special SID based on the mode. See
 * https://technet.microsoft.com/en-us/library/hh509017(v=ws.10).aspx
 */
अचिन्हित पूर्णांक setup_special_mode_ACE(काष्ठा cअगरs_ace *pntace, __u64 nmode)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक ace_size = 28;

	pntace->type = ACCESS_DENIED_ACE_TYPE;
	pntace->flags = 0x0;
	pntace->access_req = 0;
	pntace->sid.num_subauth = 3;
	pntace->sid.revision = 1;
	क्रम (i = 0; i < NUM_AUTHS; i++)
		pntace->sid.authority[i] = sid_unix_NFS_mode.authority[i];

	pntace->sid.sub_auth[0] = sid_unix_NFS_mode.sub_auth[0];
	pntace->sid.sub_auth[1] = sid_unix_NFS_mode.sub_auth[1];
	pntace->sid.sub_auth[2] = cpu_to_le32(nmode & 07777);

	/* size = 1 + 1 + 2 + 4 + 1 + 1 + 6 + (psid->num_subauth*4) */
	pntace->size = cpu_to_le16(ace_size);
	वापस ace_size;
पूर्ण

अचिन्हित पूर्णांक setup_special_user_owner_ACE(काष्ठा cअगरs_ace *pntace)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक ace_size = 28;

	pntace->type = ACCESS_ALLOWED_ACE_TYPE;
	pntace->flags = 0x0;
	pntace->access_req = cpu_to_le32(GENERIC_ALL);
	pntace->sid.num_subauth = 3;
	pntace->sid.revision = 1;
	क्रम (i = 0; i < NUM_AUTHS; i++)
		pntace->sid.authority[i] = sid_unix_NFS_users.authority[i];

	pntace->sid.sub_auth[0] = sid_unix_NFS_users.sub_auth[0];
	pntace->sid.sub_auth[1] = sid_unix_NFS_users.sub_auth[1];
	pntace->sid.sub_auth[2] = cpu_to_le32(current_fsgid().val);

	/* size = 1 + 1 + 2 + 4 + 1 + 1 + 6 + (psid->num_subauth*4) */
	pntace->size = cpu_to_le16(ace_size);
	वापस ace_size;
पूर्ण

अटल व्योम populate_new_aces(अक्षर *nacl_base,
		काष्ठा cअगरs_sid *घातnersid,
		काष्ठा cअगरs_sid *pgrpsid,
		__u64 *pnmode, u32 *pnum_aces, u16 *pnsize,
		bool modefromsid)
अणु
	__u64 nmode;
	u32 num_aces = 0;
	u16 nsize = 0;
	__u64 user_mode;
	__u64 group_mode;
	__u64 other_mode;
	__u64 deny_user_mode = 0;
	__u64 deny_group_mode = 0;
	bool sticky_set = false;
	काष्ठा cअगरs_ace *pnntace = शून्य;

	nmode = *pnmode;
	num_aces = *pnum_aces;
	nsize = *pnsize;

	अगर (modefromsid) अणु
		pnntace = (काष्ठा cअगरs_ace *) (nacl_base + nsize);
		nsize += setup_special_mode_ACE(pnntace, nmode);
		num_aces++;
		जाओ set_size;
	पूर्ण

	/*
	 * We'll try to keep the mode as requested by the user.
	 * But in हालs where we cannot meaningfully convert that
	 * पूर्णांकo ACL, वापस back the updated mode, so that it is
	 * updated in the inode.
	 */

	अगर (!स_भेद(घातnersid, pgrpsid, माप(काष्ठा cअगरs_sid))) अणु
		/*
		 * Case when owner and group SIDs are the same.
		 * Set the more restrictive of the two modes.
		 */
		user_mode = nmode & (nmode << 3) & 0700;
		group_mode = nmode & (nmode >> 3) & 0070;
	पूर्ण अन्यथा अणु
		user_mode = nmode & 0700;
		group_mode = nmode & 0070;
	पूर्ण

	other_mode = nmode & 0007;

	/* We need DENY ACE when the perm is more restrictive than the next sets. */
	deny_user_mode = ~(user_mode) & ((group_mode << 3) | (other_mode << 6)) & 0700;
	deny_group_mode = ~(group_mode) & (other_mode << 3) & 0070;

	*pnmode = user_mode | group_mode | other_mode | (nmode & ~0777);

	/* This tells अगर we should allow delete child क्रम group and everyone. */
	अगर (nmode & 01000)
		sticky_set = true;

	अगर (deny_user_mode) अणु
		pnntace = (काष्ठा cअगरs_ace *) (nacl_base + nsize);
		nsize += fill_ace_क्रम_sid(pnntace, घातnersid, deny_user_mode,
				0700, ACCESS_DENIED, false);
		num_aces++;
	पूर्ण

	/* Group DENY ACE करोes not conflict with owner ALLOW ACE. Keep in preferred order*/
	अगर (deny_group_mode && !(deny_group_mode & (user_mode >> 3))) अणु
		pnntace = (काष्ठा cअगरs_ace *) (nacl_base + nsize);
		nsize += fill_ace_क्रम_sid(pnntace, pgrpsid, deny_group_mode,
				0070, ACCESS_DENIED, false);
		num_aces++;
	पूर्ण

	pnntace = (काष्ठा cअगरs_ace *) (nacl_base + nsize);
	nsize += fill_ace_क्रम_sid(pnntace, घातnersid, user_mode,
			0700, ACCESS_ALLOWED, true);
	num_aces++;

	/* Group DENY ACE conflicts with owner ALLOW ACE. So keep it after. */
	अगर (deny_group_mode && (deny_group_mode & (user_mode >> 3))) अणु
		pnntace = (काष्ठा cअगरs_ace *) (nacl_base + nsize);
		nsize += fill_ace_क्रम_sid(pnntace, pgrpsid, deny_group_mode,
				0070, ACCESS_DENIED, false);
		num_aces++;
	पूर्ण

	pnntace = (काष्ठा cअगरs_ace *) (nacl_base + nsize);
	nsize += fill_ace_क्रम_sid(pnntace, pgrpsid, group_mode,
			0070, ACCESS_ALLOWED, !sticky_set);
	num_aces++;

	pnntace = (काष्ठा cअगरs_ace *) (nacl_base + nsize);
	nsize += fill_ace_क्रम_sid(pnntace, &sid_everyone, other_mode,
			0007, ACCESS_ALLOWED, !sticky_set);
	num_aces++;

set_size:
	*pnum_aces = num_aces;
	*pnsize = nsize;
पूर्ण

अटल __u16 replace_sids_and_copy_aces(काष्ठा cअगरs_acl *pdacl, काष्ठा cअगरs_acl *pndacl,
		काष्ठा cअगरs_sid *घातnersid, काष्ठा cअगरs_sid *pgrpsid,
		काष्ठा cअगरs_sid *pnownersid, काष्ठा cअगरs_sid *pngrpsid)
अणु
	पूर्णांक i;
	u16 size = 0;
	काष्ठा cअगरs_ace *pntace = शून्य;
	अक्षर *acl_base = शून्य;
	u32 src_num_aces = 0;
	u16 nsize = 0;
	काष्ठा cअगरs_ace *pnntace = शून्य;
	अक्षर *nacl_base = शून्य;
	u16 ace_size = 0;

	acl_base = (अक्षर *)pdacl;
	size = माप(काष्ठा cअगरs_acl);
	src_num_aces = le32_to_cpu(pdacl->num_aces);

	nacl_base = (अक्षर *)pndacl;
	nsize = माप(काष्ठा cअगरs_acl);

	/* Go through all the ACEs */
	क्रम (i = 0; i < src_num_aces; ++i) अणु
		pntace = (काष्ठा cअगरs_ace *) (acl_base + size);
		pnntace = (काष्ठा cअगरs_ace *) (nacl_base + nsize);

		अगर (pnownersid && compare_sids(&pntace->sid, घातnersid) == 0)
			ace_size = cअगरs_copy_ace(pnntace, pntace, pnownersid);
		अन्यथा अगर (pngrpsid && compare_sids(&pntace->sid, pgrpsid) == 0)
			ace_size = cअगरs_copy_ace(pnntace, pntace, pngrpsid);
		अन्यथा
			ace_size = cअगरs_copy_ace(pnntace, pntace, शून्य);

		size += le16_to_cpu(pntace->size);
		nsize += ace_size;
	पूर्ण

	वापस nsize;
पूर्ण

अटल पूर्णांक set_chmod_dacl(काष्ठा cअगरs_acl *pdacl, काष्ठा cअगरs_acl *pndacl,
		काष्ठा cअगरs_sid *घातnersid,	काष्ठा cअगरs_sid *pgrpsid,
		__u64 *pnmode, bool mode_from_sid)
अणु
	पूर्णांक i;
	u16 size = 0;
	काष्ठा cअगरs_ace *pntace = शून्य;
	अक्षर *acl_base = शून्य;
	u32 src_num_aces = 0;
	u16 nsize = 0;
	काष्ठा cअगरs_ace *pnntace = शून्य;
	अक्षर *nacl_base = शून्य;
	u32 num_aces = 0;
	bool new_aces_set = false;

	/* Assuming that pndacl and pnmode are never शून्य */
	nacl_base = (अक्षर *)pndacl;
	nsize = माप(काष्ठा cअगरs_acl);

	/* If pdacl is शून्य, we करोn't have a src. Simply populate new ACL. */
	अगर (!pdacl) अणु
		populate_new_aces(nacl_base,
				घातnersid, pgrpsid,
				pnmode, &num_aces, &nsize,
				mode_from_sid);
		जाओ finalize_dacl;
	पूर्ण

	acl_base = (अक्षर *)pdacl;
	size = माप(काष्ठा cअगरs_acl);
	src_num_aces = le32_to_cpu(pdacl->num_aces);

	/* Retain old ACEs which we can retain */
	क्रम (i = 0; i < src_num_aces; ++i) अणु
		pntace = (काष्ठा cअगरs_ace *) (acl_base + size);

		अगर (!new_aces_set && (pntace->flags & INHERITED_ACE)) अणु
			/* Place the new ACEs in between existing explicit and inherited */
			populate_new_aces(nacl_base,
					घातnersid, pgrpsid,
					pnmode, &num_aces, &nsize,
					mode_from_sid);

			new_aces_set = true;
		पूर्ण

		/* If it's any one of the ACE we're replacing, skip! */
		अगर (((compare_sids(&pntace->sid, &sid_unix_NFS_mode) == 0) ||
				(compare_sids(&pntace->sid, घातnersid) == 0) ||
				(compare_sids(&pntace->sid, pgrpsid) == 0) ||
				(compare_sids(&pntace->sid, &sid_everyone) == 0) ||
				(compare_sids(&pntace->sid, &sid_authusers) == 0))) अणु
			जाओ next_ace;
		पूर्ण

		/* update the poपूर्णांकer to the next ACE to populate*/
		pnntace = (काष्ठा cअगरs_ace *) (nacl_base + nsize);

		nsize += cअगरs_copy_ace(pnntace, pntace, शून्य);
		num_aces++;

next_ace:
		size += le16_to_cpu(pntace->size);
	पूर्ण

	/* If inherited ACEs are not present, place the new ones at the tail */
	अगर (!new_aces_set) अणु
		populate_new_aces(nacl_base,
				घातnersid, pgrpsid,
				pnmode, &num_aces, &nsize,
				mode_from_sid);

		new_aces_set = true;
	पूर्ण

finalize_dacl:
	pndacl->num_aces = cpu_to_le32(num_aces);
	pndacl->size = cpu_to_le16(nsize);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_sid(काष्ठा cअगरs_sid *psid, अक्षर *end_of_acl)
अणु
	/* BB need to add parm so we can store the SID BB */

	/* validate that we करो not go past end of ACL - sid must be at least 8
	   bytes दीर्घ (assuming no sub-auths - e.g. the null SID */
	अगर (end_of_acl < (अक्षर *)psid + 8) अणु
		cअगरs_dbg(VFS, "ACL too small to parse SID %p\n", psid);
		वापस -EINVAL;
	पूर्ण

#अगर_घोषित CONFIG_CIFS_DEBUG2
	अगर (psid->num_subauth) अणु
		पूर्णांक i;
		cअगरs_dbg(FYI, "SID revision %d num_auth %d\n",
			 psid->revision, psid->num_subauth);

		क्रम (i = 0; i < psid->num_subauth; i++) अणु
			cअगरs_dbg(FYI, "SID sub_auth[%d]: 0x%x\n",
				 i, le32_to_cpu(psid->sub_auth[i]));
		पूर्ण

		/* BB add length check to make sure that we करो not have huge
			num auths and thereक्रमe go off the end */
		cअगरs_dbg(FYI, "RID 0x%x\n",
			 le32_to_cpu(psid->sub_auth[psid->num_subauth-1]));
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण


/* Convert CIFS ACL to POSIX क्रमm */
अटल पूर्णांक parse_sec_desc(काष्ठा cअगरs_sb_info *cअगरs_sb,
		काष्ठा cअगरs_ntsd *pntsd, पूर्णांक acl_len, काष्ठा cअगरs_fattr *fattr,
		bool get_mode_from_special_sid)
अणु
	पूर्णांक rc = 0;
	काष्ठा cअगरs_sid *owner_sid_ptr, *group_sid_ptr;
	काष्ठा cअगरs_acl *dacl_ptr; /* no need क्रम SACL ptr */
	अक्षर *end_of_acl = ((अक्षर *)pntsd) + acl_len;
	__u32 dacloffset;

	अगर (pntsd == शून्य)
		वापस -EIO;

	owner_sid_ptr = (काष्ठा cअगरs_sid *)((अक्षर *)pntsd +
				le32_to_cpu(pntsd->osiकरोffset));
	group_sid_ptr = (काष्ठा cअगरs_sid *)((अक्षर *)pntsd +
				le32_to_cpu(pntsd->gsiकरोffset));
	dacloffset = le32_to_cpu(pntsd->dacloffset);
	dacl_ptr = (काष्ठा cअगरs_acl *)((अक्षर *)pntsd + dacloffset);
	cअगरs_dbg(NOISY, "revision %d type 0x%x ooffset 0x%x goffset 0x%x sacloffset 0x%x dacloffset 0x%x\n",
		 pntsd->revision, pntsd->type, le32_to_cpu(pntsd->osiकरोffset),
		 le32_to_cpu(pntsd->gsiकरोffset),
		 le32_to_cpu(pntsd->sacloffset), dacloffset);
/*	cअगरs_dump_mem("owner_sid: ", owner_sid_ptr, 64); */
	rc = parse_sid(owner_sid_ptr, end_of_acl);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "%s: Error %d parsing Owner SID\n", __func__, rc);
		वापस rc;
	पूर्ण
	rc = sid_to_id(cअगरs_sb, owner_sid_ptr, fattr, SIDOWNER);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "%s: Error %d mapping Owner SID to uid\n",
			 __func__, rc);
		वापस rc;
	पूर्ण

	rc = parse_sid(group_sid_ptr, end_of_acl);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "%s: Error %d mapping Owner SID to gid\n",
			 __func__, rc);
		वापस rc;
	पूर्ण
	rc = sid_to_id(cअगरs_sb, group_sid_ptr, fattr, SIDGROUP);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "%s: Error %d mapping Group SID to gid\n",
			 __func__, rc);
		वापस rc;
	पूर्ण

	अगर (dacloffset)
		parse_dacl(dacl_ptr, end_of_acl, owner_sid_ptr,
			   group_sid_ptr, fattr, get_mode_from_special_sid);
	अन्यथा
		cअगरs_dbg(FYI, "no ACL\n"); /* BB grant all or शेष perms? */

	वापस rc;
पूर्ण

/* Convert permission bits from mode to equivalent CIFS ACL */
अटल पूर्णांक build_sec_desc(काष्ठा cअगरs_ntsd *pntsd, काष्ठा cअगरs_ntsd *pnntsd,
	__u32 secdesclen, __u32 *pnsecdesclen, __u64 *pnmode, kuid_t uid, kgid_t gid,
	bool mode_from_sid, bool id_from_sid, पूर्णांक *aclflag)
अणु
	पूर्णांक rc = 0;
	__u32 dacloffset;
	__u32 ndacloffset;
	__u32 sidsoffset;
	काष्ठा cअगरs_sid *owner_sid_ptr, *group_sid_ptr;
	काष्ठा cअगरs_sid *nowner_sid_ptr = शून्य, *ngroup_sid_ptr = शून्य;
	काष्ठा cअगरs_acl *dacl_ptr = शून्य;  /* no need क्रम SACL ptr */
	काष्ठा cअगरs_acl *ndacl_ptr = शून्य; /* no need क्रम SACL ptr */
	अक्षर *end_of_acl = ((अक्षर *)pntsd) + secdesclen;
	u16 size = 0;

	dacloffset = le32_to_cpu(pntsd->dacloffset);
	अगर (dacloffset) अणु
		dacl_ptr = (काष्ठा cअगरs_acl *)((अक्षर *)pntsd + dacloffset);
		अगर (end_of_acl < (अक्षर *)dacl_ptr + le16_to_cpu(dacl_ptr->size)) अणु
			cअगरs_dbg(VFS, "Server returned illegal ACL size\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	owner_sid_ptr = (काष्ठा cअगरs_sid *)((अक्षर *)pntsd +
			le32_to_cpu(pntsd->osiकरोffset));
	group_sid_ptr = (काष्ठा cअगरs_sid *)((अक्षर *)pntsd +
			le32_to_cpu(pntsd->gsiकरोffset));

	अगर (pnmode && *pnmode != NO_CHANGE_64) अणु /* chmod */
		ndacloffset = माप(काष्ठा cअगरs_ntsd);
		ndacl_ptr = (काष्ठा cअगरs_acl *)((अक्षर *)pnntsd + ndacloffset);
		ndacl_ptr->revision =
			dacloffset ? dacl_ptr->revision : cpu_to_le16(ACL_REVISION);

		ndacl_ptr->size = cpu_to_le16(0);
		ndacl_ptr->num_aces = cpu_to_le32(0);

		rc = set_chmod_dacl(dacl_ptr, ndacl_ptr, owner_sid_ptr, group_sid_ptr,
				    pnmode, mode_from_sid);

		sidsoffset = ndacloffset + le16_to_cpu(ndacl_ptr->size);
		/* copy the non-dacl portion of secdesc */
		*pnsecdesclen = copy_sec_desc(pntsd, pnntsd, sidsoffset,
				शून्य, शून्य);

		*aclflag |= CIFS_ACL_DACL;
	पूर्ण अन्यथा अणु
		ndacloffset = माप(काष्ठा cअगरs_ntsd);
		ndacl_ptr = (काष्ठा cअगरs_acl *)((अक्षर *)pnntsd + ndacloffset);
		ndacl_ptr->revision =
			dacloffset ? dacl_ptr->revision : cpu_to_le16(ACL_REVISION);
		ndacl_ptr->num_aces = dacl_ptr->num_aces;

		अगर (uid_valid(uid)) अणु /* chown */
			uid_t id;
			nowner_sid_ptr = kदो_स्मृति(माप(काष्ठा cअगरs_sid),
								GFP_KERNEL);
			अगर (!nowner_sid_ptr) अणु
				rc = -ENOMEM;
				जाओ chown_chgrp_निकास;
			पूर्ण
			id = from_kuid(&init_user_ns, uid);
			अगर (id_from_sid) अणु
				काष्ठा owner_sid *osid = (काष्ठा owner_sid *)nowner_sid_ptr;
				/* Populate the user ownership fields S-1-5-88-1 */
				osid->Revision = 1;
				osid->NumAuth = 3;
				osid->Authority[5] = 5;
				osid->SubAuthorities[0] = cpu_to_le32(88);
				osid->SubAuthorities[1] = cpu_to_le32(1);
				osid->SubAuthorities[2] = cpu_to_le32(id);

			पूर्ण अन्यथा अणु /* lookup sid with upcall */
				rc = id_to_sid(id, SIDOWNER, nowner_sid_ptr);
				अगर (rc) अणु
					cअगरs_dbg(FYI, "%s: Mapping error %d for owner id %d\n",
						 __func__, rc, id);
					जाओ chown_chgrp_निकास;
				पूर्ण
			पूर्ण
			*aclflag |= CIFS_ACL_OWNER;
		पूर्ण
		अगर (gid_valid(gid)) अणु /* chgrp */
			gid_t id;
			ngroup_sid_ptr = kदो_स्मृति(माप(काष्ठा cअगरs_sid),
								GFP_KERNEL);
			अगर (!ngroup_sid_ptr) अणु
				rc = -ENOMEM;
				जाओ chown_chgrp_निकास;
			पूर्ण
			id = from_kgid(&init_user_ns, gid);
			अगर (id_from_sid) अणु
				काष्ठा owner_sid *gsid = (काष्ठा owner_sid *)ngroup_sid_ptr;
				/* Populate the group ownership fields S-1-5-88-2 */
				gsid->Revision = 1;
				gsid->NumAuth = 3;
				gsid->Authority[5] = 5;
				gsid->SubAuthorities[0] = cpu_to_le32(88);
				gsid->SubAuthorities[1] = cpu_to_le32(2);
				gsid->SubAuthorities[2] = cpu_to_le32(id);

			पूर्ण अन्यथा अणु /* lookup sid with upcall */
				rc = id_to_sid(id, SIDGROUP, ngroup_sid_ptr);
				अगर (rc) अणु
					cअगरs_dbg(FYI, "%s: Mapping error %d for group id %d\n",
						 __func__, rc, id);
					जाओ chown_chgrp_निकास;
				पूर्ण
			पूर्ण
			*aclflag |= CIFS_ACL_GROUP;
		पूर्ण

		अगर (dacloffset) अणु
			/* Replace ACEs क्रम old owner with new one */
			size = replace_sids_and_copy_aces(dacl_ptr, ndacl_ptr,
					owner_sid_ptr, group_sid_ptr,
					nowner_sid_ptr, ngroup_sid_ptr);
			ndacl_ptr->size = cpu_to_le16(size);
		पूर्ण

		sidsoffset = ndacloffset + le16_to_cpu(ndacl_ptr->size);
		/* copy the non-dacl portion of secdesc */
		*pnsecdesclen = copy_sec_desc(pntsd, pnntsd, sidsoffset,
				nowner_sid_ptr, ngroup_sid_ptr);

chown_chgrp_निकास:
		/* errors could jump here. So make sure we वापस soon after this */
		kमुक्त(nowner_sid_ptr);
		kमुक्त(ngroup_sid_ptr);
	पूर्ण

	वापस rc;
पूर्ण

काष्ठा cअगरs_ntsd *get_cअगरs_acl_by_fid(काष्ठा cअगरs_sb_info *cअगरs_sb,
				      स्थिर काष्ठा cअगरs_fid *cअगरsfid, u32 *pacllen,
				      u32 __maybe_unused unused)
अणु
	काष्ठा cअगरs_ntsd *pntsd = शून्य;
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc;
	काष्ठा tcon_link *tlink = cअगरs_sb_tlink(cअगरs_sb);

	अगर (IS_ERR(tlink))
		वापस ERR_CAST(tlink);

	xid = get_xid();
	rc = CIFSSMBGetCIFSACL(xid, tlink_tcon(tlink), cअगरsfid->netfid, &pntsd,
				pacllen);
	मुक्त_xid(xid);

	cअगरs_put_tlink(tlink);

	cअगरs_dbg(FYI, "%s: rc = %d ACL len %d\n", __func__, rc, *pacllen);
	अगर (rc)
		वापस ERR_PTR(rc);
	वापस pntsd;
पूर्ण

अटल काष्ठा cअगरs_ntsd *get_cअगरs_acl_by_path(काष्ठा cअगरs_sb_info *cअगरs_sb,
		स्थिर अक्षर *path, u32 *pacllen)
अणु
	काष्ठा cअगरs_ntsd *pntsd = शून्य;
	पूर्णांक oplock = 0;
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा tcon_link *tlink = cअगरs_sb_tlink(cअगरs_sb);
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;

	अगर (IS_ERR(tlink))
		वापस ERR_CAST(tlink);

	tcon = tlink_tcon(tlink);
	xid = get_xid();

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = READ_CONTROL;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
	oparms.disposition = खाता_OPEN;
	oparms.path = path;
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = CIFS_खोलो(xid, &oparms, &oplock, शून्य);
	अगर (!rc) अणु
		rc = CIFSSMBGetCIFSACL(xid, tcon, fid.netfid, &pntsd, pacllen);
		CIFSSMBClose(xid, tcon, fid.netfid);
	पूर्ण

	cअगरs_put_tlink(tlink);
	मुक्त_xid(xid);

	cअगरs_dbg(FYI, "%s: rc = %d ACL len %d\n", __func__, rc, *pacllen);
	अगर (rc)
		वापस ERR_PTR(rc);
	वापस pntsd;
पूर्ण

/* Retrieve an ACL from the server */
काष्ठा cअगरs_ntsd *get_cअगरs_acl(काष्ठा cअगरs_sb_info *cअगरs_sb,
				      काष्ठा inode *inode, स्थिर अक्षर *path,
			       u32 *pacllen, u32 info)
अणु
	काष्ठा cअगरs_ntsd *pntsd = शून्य;
	काष्ठा cअगरsFileInfo *खोलो_file = शून्य;

	अगर (inode)
		खोलो_file = find_पढ़ोable_file(CIFS_I(inode), true);
	अगर (!खोलो_file)
		वापस get_cअगरs_acl_by_path(cअगरs_sb, path, pacllen);

	pntsd = get_cअगरs_acl_by_fid(cअगरs_sb, &खोलो_file->fid, pacllen, info);
	cअगरsFileInfo_put(खोलो_file);
	वापस pntsd;
पूर्ण

 /* Set an ACL on the server */
पूर्णांक set_cअगरs_acl(काष्ठा cअगरs_ntsd *pnntsd, __u32 acllen,
			काष्ठा inode *inode, स्थिर अक्षर *path, पूर्णांक aclflag)
अणु
	पूर्णांक oplock = 0;
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc, access_flags;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा tcon_link *tlink = cअगरs_sb_tlink(cअगरs_sb);
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;

	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);

	tcon = tlink_tcon(tlink);
	xid = get_xid();

	अगर (aclflag == CIFS_ACL_OWNER || aclflag == CIFS_ACL_GROUP)
		access_flags = WRITE_OWNER;
	अन्यथा
		access_flags = WRITE_DAC;

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = access_flags;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, 0);
	oparms.disposition = खाता_OPEN;
	oparms.path = path;
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = CIFS_खोलो(xid, &oparms, &oplock, शून्य);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "Unable to open file to set ACL\n");
		जाओ out;
	पूर्ण

	rc = CIFSSMBSetCIFSACL(xid, tcon, fid.netfid, pnntsd, acllen, aclflag);
	cअगरs_dbg(NOISY, "SetCIFSACL rc = %d\n", rc);

	CIFSSMBClose(xid, tcon, fid.netfid);
out:
	मुक्त_xid(xid);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

/* Translate the CIFS ACL (similar to NTFS ACL) क्रम a file पूर्णांकo mode bits */
पूर्णांक
cअगरs_acl_to_fattr(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा cअगरs_fattr *fattr,
		  काष्ठा inode *inode, bool mode_from_special_sid,
		  स्थिर अक्षर *path, स्थिर काष्ठा cअगरs_fid *pfid)
अणु
	काष्ठा cअगरs_ntsd *pntsd = शून्य;
	u32 acllen = 0;
	पूर्णांक rc = 0;
	काष्ठा tcon_link *tlink = cअगरs_sb_tlink(cअगरs_sb);
	काष्ठा smb_version_operations *ops;
	स्थिर u32 info = 0;

	cअगरs_dbg(NOISY, "converting ACL to mode for %s\n", path);

	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);

	ops = tlink_tcon(tlink)->ses->server->ops;

	अगर (pfid && (ops->get_acl_by_fid))
		pntsd = ops->get_acl_by_fid(cअगरs_sb, pfid, &acllen, info);
	अन्यथा अगर (ops->get_acl)
		pntsd = ops->get_acl(cअगरs_sb, inode, path, &acllen, info);
	अन्यथा अणु
		cअगरs_put_tlink(tlink);
		वापस -EOPNOTSUPP;
	पूर्ण
	/* अगर we can retrieve the ACL, now parse Access Control Entries, ACEs */
	अगर (IS_ERR(pntsd)) अणु
		rc = PTR_ERR(pntsd);
		cअगरs_dbg(VFS, "%s: error %d getting sec desc\n", __func__, rc);
	पूर्ण अन्यथा अगर (mode_from_special_sid) अणु
		rc = parse_sec_desc(cअगरs_sb, pntsd, acllen, fattr, true);
		kमुक्त(pntsd);
	पूर्ण अन्यथा अणु
		/* get approximated mode from ACL */
		rc = parse_sec_desc(cअगरs_sb, pntsd, acllen, fattr, false);
		kमुक्त(pntsd);
		अगर (rc)
			cअगरs_dbg(VFS, "parse sec desc failed rc = %d\n", rc);
	पूर्ण

	cअगरs_put_tlink(tlink);

	वापस rc;
पूर्ण

/* Convert mode bits to an ACL so we can update the ACL on the server */
पूर्णांक
id_mode_to_cअगरs_acl(काष्ठा inode *inode, स्थिर अक्षर *path, __u64 *pnmode,
			kuid_t uid, kgid_t gid)
अणु
	पूर्णांक rc = 0;
	पूर्णांक aclflag = CIFS_ACL_DACL; /* शेष flag to set */
	__u32 secdesclen = 0;
	__u32 nsecdesclen = 0;
	__u32 dacloffset = 0;
	काष्ठा cअगरs_acl *dacl_ptr = शून्य;
	काष्ठा cअगरs_ntsd *pntsd = शून्य; /* acl obtained from server */
	काष्ठा cअगरs_ntsd *pnntsd = शून्य; /* modअगरied acl to be sent to server */
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा tcon_link *tlink = cअगरs_sb_tlink(cअगरs_sb);
	काष्ठा smb_version_operations *ops;
	bool mode_from_sid, id_from_sid;
	स्थिर u32 info = 0;

	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);

	ops = tlink_tcon(tlink)->ses->server->ops;

	cअगरs_dbg(NOISY, "set ACL from mode for %s\n", path);

	/* Get the security descriptor */

	अगर (ops->get_acl == शून्य) अणु
		cअगरs_put_tlink(tlink);
		वापस -EOPNOTSUPP;
	पूर्ण

	pntsd = ops->get_acl(cअगरs_sb, inode, path, &secdesclen, info);
	अगर (IS_ERR(pntsd)) अणु
		rc = PTR_ERR(pntsd);
		cअगरs_dbg(VFS, "%s: error %d getting sec desc\n", __func__, rc);
		cअगरs_put_tlink(tlink);
		वापस rc;
	पूर्ण

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MODE_FROM_SID)
		mode_from_sid = true;
	अन्यथा
		mode_from_sid = false;

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_UID_FROM_ACL)
		id_from_sid = true;
	अन्यथा
		id_from_sid = false;

	/* Potentially, five new ACEs can be added to the ACL क्रम U,G,O mapping */
	nsecdesclen = secdesclen;
	अगर (pnmode && *pnmode != NO_CHANGE_64) अणु /* chmod */
		अगर (mode_from_sid)
			nsecdesclen += माप(काष्ठा cअगरs_ace);
		अन्यथा /* cअगरsacl */
			nsecdesclen += 5 * माप(काष्ठा cअगरs_ace);
	पूर्ण अन्यथा अणु /* chown */
		/* When ownership changes, changes new owner sid length could be dअगरferent */
		nsecdesclen = माप(काष्ठा cअगरs_ntsd) + (माप(काष्ठा cअगरs_sid) * 2);
		dacloffset = le32_to_cpu(pntsd->dacloffset);
		अगर (dacloffset) अणु
			dacl_ptr = (काष्ठा cअगरs_acl *)((अक्षर *)pntsd + dacloffset);
			अगर (mode_from_sid)
				nsecdesclen +=
					le32_to_cpu(dacl_ptr->num_aces) * माप(काष्ठा cअगरs_ace);
			अन्यथा /* cअगरsacl */
				nsecdesclen += le16_to_cpu(dacl_ptr->size);
		पूर्ण
	पूर्ण

	/*
	 * Add three ACEs क्रम owner, group, everyone getting rid of other ACEs
	 * as chmod disables ACEs and set the security descriptor. Allocate
	 * memory क्रम the smb header, set security descriptor request security
	 * descriptor parameters, and security descriptor itself
	 */
	nsecdesclen = max_t(u32, nsecdesclen, DEFAULT_SEC_DESC_LEN);
	pnntsd = kदो_स्मृति(nsecdesclen, GFP_KERNEL);
	अगर (!pnntsd) अणु
		kमुक्त(pntsd);
		cअगरs_put_tlink(tlink);
		वापस -ENOMEM;
	पूर्ण

	rc = build_sec_desc(pntsd, pnntsd, secdesclen, &nsecdesclen, pnmode, uid, gid,
			    mode_from_sid, id_from_sid, &aclflag);

	cअगरs_dbg(NOISY, "build_sec_desc rc: %d\n", rc);

	अगर (ops->set_acl == शून्य)
		rc = -EOPNOTSUPP;

	अगर (!rc) अणु
		/* Set the security descriptor */
		rc = ops->set_acl(pnntsd, nsecdesclen, inode, path, aclflag);
		cअगरs_dbg(NOISY, "set_cifs_acl rc: %d\n", rc);
	पूर्ण
	cअगरs_put_tlink(tlink);

	kमुक्त(pnntsd);
	kमुक्त(pntsd);
	वापस rc;
पूर्ण
