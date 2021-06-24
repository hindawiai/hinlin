<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2006  NEC Corporation
 *
 * Created by KaiGai Kohei <kaigai@ak.jp.nec.com>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/समय.स>
#समावेश <linux/crc32.h>
#समावेश <linux/jffs2.h>
#समावेश <linux/xattr.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/mtd/mtd.h>
#समावेश "nodelist.h"

अटल माप_प्रकार jffs2_acl_size(पूर्णांक count)
अणु
	अगर (count <= 4) अणु
		वापस माप(काष्ठा jffs2_acl_header)
		       + count * माप(काष्ठा jffs2_acl_entry_लघु);
	पूर्ण अन्यथा अणु
		वापस माप(काष्ठा jffs2_acl_header)
		       + 4 * माप(काष्ठा jffs2_acl_entry_लघु)
		       + (count - 4) * माप(काष्ठा jffs2_acl_entry);
	पूर्ण
पूर्ण

अटल पूर्णांक jffs2_acl_count(माप_प्रकार size)
अणु
	माप_प्रकार s;

	size -= माप(काष्ठा jffs2_acl_header);
	अगर (size < 4 * माप(काष्ठा jffs2_acl_entry_लघु)) अणु
		अगर (size % माप(काष्ठा jffs2_acl_entry_लघु))
			वापस -1;
		वापस size / माप(काष्ठा jffs2_acl_entry_लघु);
	पूर्ण अन्यथा अणु
		s = size - 4 * माप(काष्ठा jffs2_acl_entry_लघु);
		अगर (s % माप(काष्ठा jffs2_acl_entry))
			वापस -1;
		वापस s / माप(काष्ठा jffs2_acl_entry) + 4;
	पूर्ण
पूर्ण

अटल काष्ठा posix_acl *jffs2_acl_from_medium(व्योम *value, माप_प्रकार size)
अणु
	व्योम *end = value + size;
	काष्ठा jffs2_acl_header *header = value;
	काष्ठा jffs2_acl_entry *entry;
	काष्ठा posix_acl *acl;
	uपूर्णांक32_t ver;
	पूर्णांक i, count;

	अगर (!value)
		वापस शून्य;
	अगर (size < माप(काष्ठा jffs2_acl_header))
		वापस ERR_PTR(-EINVAL);
	ver = je32_to_cpu(header->a_version);
	अगर (ver != JFFS2_ACL_VERSION) अणु
		JFFS2_WARNING("Invalid ACL version. (=%u)\n", ver);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	value += माप(काष्ठा jffs2_acl_header);
	count = jffs2_acl_count(size);
	अगर (count < 0)
		वापस ERR_PTR(-EINVAL);
	अगर (count == 0)
		वापस शून्य;

	acl = posix_acl_alloc(count, GFP_KERNEL);
	अगर (!acl)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i=0; i < count; i++) अणु
		entry = value;
		अगर (value + माप(काष्ठा jffs2_acl_entry_लघु) > end)
			जाओ fail;
		acl->a_entries[i].e_tag = je16_to_cpu(entry->e_tag);
		acl->a_entries[i].e_perm = je16_to_cpu(entry->e_perm);
		चयन (acl->a_entries[i].e_tag) अणु
			हाल ACL_USER_OBJ:
			हाल ACL_GROUP_OBJ:
			हाल ACL_MASK:
			हाल ACL_OTHER:
				value += माप(काष्ठा jffs2_acl_entry_लघु);
				अवरोध;

			हाल ACL_USER:
				value += माप(काष्ठा jffs2_acl_entry);
				अगर (value > end)
					जाओ fail;
				acl->a_entries[i].e_uid =
					make_kuid(&init_user_ns,
						  je32_to_cpu(entry->e_id));
				अवरोध;
			हाल ACL_GROUP:
				value += माप(काष्ठा jffs2_acl_entry);
				अगर (value > end)
					जाओ fail;
				acl->a_entries[i].e_gid =
					make_kgid(&init_user_ns,
						  je32_to_cpu(entry->e_id));
				अवरोध;

			शेष:
				जाओ fail;
		पूर्ण
	पूर्ण
	अगर (value != end)
		जाओ fail;
	वापस acl;
 fail:
	posix_acl_release(acl);
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल व्योम *jffs2_acl_to_medium(स्थिर काष्ठा posix_acl *acl, माप_प्रकार *size)
अणु
	काष्ठा jffs2_acl_header *header;
	काष्ठा jffs2_acl_entry *entry;
	व्योम *e;
	माप_प्रकार i;

	*size = jffs2_acl_size(acl->a_count);
	header = kदो_स्मृति(काष्ठा_size(header, a_entries, acl->a_count),
			GFP_KERNEL);
	अगर (!header)
		वापस ERR_PTR(-ENOMEM);
	header->a_version = cpu_to_je32(JFFS2_ACL_VERSION);
	e = header + 1;
	क्रम (i=0; i < acl->a_count; i++) अणु
		स्थिर काष्ठा posix_acl_entry *acl_e = &acl->a_entries[i];
		entry = e;
		entry->e_tag = cpu_to_je16(acl_e->e_tag);
		entry->e_perm = cpu_to_je16(acl_e->e_perm);
		चयन(acl_e->e_tag) अणु
			हाल ACL_USER:
				entry->e_id = cpu_to_je32(
					from_kuid(&init_user_ns, acl_e->e_uid));
				e += माप(काष्ठा jffs2_acl_entry);
				अवरोध;
			हाल ACL_GROUP:
				entry->e_id = cpu_to_je32(
					from_kgid(&init_user_ns, acl_e->e_gid));
				e += माप(काष्ठा jffs2_acl_entry);
				अवरोध;

			हाल ACL_USER_OBJ:
			हाल ACL_GROUP_OBJ:
			हाल ACL_MASK:
			हाल ACL_OTHER:
				e += माप(काष्ठा jffs2_acl_entry_लघु);
				अवरोध;

			शेष:
				जाओ fail;
		पूर्ण
	पूर्ण
	वापस header;
 fail:
	kमुक्त(header);
	वापस ERR_PTR(-EINVAL);
पूर्ण

काष्ठा posix_acl *jffs2_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा posix_acl *acl;
	अक्षर *value = शून्य;
	पूर्णांक rc, xprefix;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		xprefix = JFFS2_XPREFIX_ACL_ACCESS;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		xprefix = JFFS2_XPREFIX_ACL_DEFAULT;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	rc = करो_jffs2_getxattr(inode, xprefix, "", शून्य, 0);
	अगर (rc > 0) अणु
		value = kदो_स्मृति(rc, GFP_KERNEL);
		अगर (!value)
			वापस ERR_PTR(-ENOMEM);
		rc = करो_jffs2_getxattr(inode, xprefix, "", value, rc);
	पूर्ण
	अगर (rc > 0) अणु
		acl = jffs2_acl_from_medium(value, rc);
	पूर्ण अन्यथा अगर (rc == -ENODATA || rc == -ENOSYS) अणु
		acl = शून्य;
	पूर्ण अन्यथा अणु
		acl = ERR_PTR(rc);
	पूर्ण
	kमुक्त(value);
	वापस acl;
पूर्ण

अटल पूर्णांक __jffs2_set_acl(काष्ठा inode *inode, पूर्णांक xprefix, काष्ठा posix_acl *acl)
अणु
	अक्षर *value = शून्य;
	माप_प्रकार size = 0;
	पूर्णांक rc;

	अगर (acl) अणु
		value = jffs2_acl_to_medium(acl, &size);
		अगर (IS_ERR(value))
			वापस PTR_ERR(value);
	पूर्ण
	rc = करो_jffs2_setxattr(inode, xprefix, "", value, size, 0);
	अगर (!value && rc == -ENODATA)
		rc = 0;
	kमुक्त(value);

	वापस rc;
पूर्ण

पूर्णांक jffs2_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		  काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	पूर्णांक rc, xprefix;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		xprefix = JFFS2_XPREFIX_ACL_ACCESS;
		अगर (acl) अणु
			umode_t mode;

			rc = posix_acl_update_mode(&init_user_ns, inode, &mode,
						   &acl);
			अगर (rc)
				वापस rc;
			अगर (inode->i_mode != mode) अणु
				काष्ठा iattr attr;

				attr.ia_valid = ATTR_MODE | ATTR_CTIME;
				attr.ia_mode = mode;
				attr.ia_स_समय = current_समय(inode);
				rc = jffs2_करो_setattr(inode, &attr);
				अगर (rc < 0)
					वापस rc;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		xprefix = JFFS2_XPREFIX_ACL_DEFAULT;
		अगर (!S_ISसूची(inode->i_mode))
			वापस acl ? -EACCES : 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	rc = __jffs2_set_acl(inode, xprefix, acl);
	अगर (!rc)
		set_cached_acl(inode, type, acl);
	वापस rc;
पूर्ण

पूर्णांक jffs2_init_acl_pre(काष्ठा inode *dir_i, काष्ठा inode *inode, umode_t *i_mode)
अणु
	काष्ठा posix_acl *शेष_acl, *acl;
	पूर्णांक rc;

	cache_no_acl(inode);

	rc = posix_acl_create(dir_i, i_mode, &शेष_acl, &acl);
	अगर (rc)
		वापस rc;

	अगर (शेष_acl) अणु
		set_cached_acl(inode, ACL_TYPE_DEFAULT, शेष_acl);
		posix_acl_release(शेष_acl);
	पूर्ण
	अगर (acl) अणु
		set_cached_acl(inode, ACL_TYPE_ACCESS, acl);
		posix_acl_release(acl);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक jffs2_init_acl_post(काष्ठा inode *inode)
अणु
	पूर्णांक rc;

	अगर (inode->i_शेष_acl) अणु
		rc = __jffs2_set_acl(inode, JFFS2_XPREFIX_ACL_DEFAULT, inode->i_शेष_acl);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (inode->i_acl) अणु
		rc = __jffs2_set_acl(inode, JFFS2_XPREFIX_ACL_ACCESS, inode->i_acl);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण
