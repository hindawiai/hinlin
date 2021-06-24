<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/vfat/namei.c
 *
 *  Written 1992,1993 by Werner Almesberger
 *
 *  Winकरोws95/Winकरोws NT compatible extended MSDOS fileप्रणाली
 *    by Gorकरोn Chaffee Copyright (C) 1995.  Send bug reports क्रम the
 *    VFAT fileप्रणाली to <chaffee@cs.berkeley.edu>.  Specअगरy
 *    what file operation caused you trouble and अगर you can duplicate
 *    the problem, send a script that demonstrates it.
 *
 *  Short name translation 1999, 2001 by Wolfram Pienkoss <wp@bszh.de>
 *
 *  Support Multibyte अक्षरacters and cleanup by
 *				OGAWA Hirofumi <hirofumi@mail.parknet.co.jp>
 */

#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/namei.h>
#समावेश <linux/kernel.h>
#समावेश <linux/iversion.h>
#समावेश "fat.h"

अटल अंतरभूत अचिन्हित दीर्घ vfat_d_version(काष्ठा dentry *dentry)
अणु
	वापस (अचिन्हित दीर्घ) dentry->d_fsdata;
पूर्ण

अटल अंतरभूत व्योम vfat_d_version_set(काष्ठा dentry *dentry,
				      अचिन्हित दीर्घ version)
अणु
	dentry->d_fsdata = (व्योम *) version;
पूर्ण

/*
 * If new entry was created in the parent, it could create the 8.3
 * alias (the लघुname of logname).  So, the parent may have the
 * negative-dentry which matches the created 8.3 alias.
 *
 * If it happened, the negative dentry isn't actually negative
 * anymore.  So, drop it.
 */
अटल पूर्णांक vfat_revalidate_लघुname(काष्ठा dentry *dentry)
अणु
	पूर्णांक ret = 1;
	spin_lock(&dentry->d_lock);
	अगर (!inode_eq_iversion(d_inode(dentry->d_parent), vfat_d_version(dentry)))
		ret = 0;
	spin_unlock(&dentry->d_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vfat_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	/* This is not negative dentry. Always valid. */
	अगर (d_really_is_positive(dentry))
		वापस 1;
	वापस vfat_revalidate_लघुname(dentry);
पूर्ण

अटल पूर्णांक vfat_revalidate_ci(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	/*
	 * This is not negative dentry. Always valid.
	 *
	 * Note, नाम() to existing directory entry will have ->d_inode,
	 * and will use existing name which isn't specअगरied name by user.
	 *
	 * We may be able to drop this positive dentry here. But dropping
	 * positive dentry isn't good idea. So it's unsupported like
	 * नाम("filename", "FILENAME") क्रम now.
	 */
	अगर (d_really_is_positive(dentry))
		वापस 1;

	/*
	 * This may be nfsd (or something), anyway, we can't see the
	 * पूर्णांकent of this. So, since this can be क्रम creation, drop it.
	 */
	अगर (!flags)
		वापस 0;

	/*
	 * Drop the negative dentry, in order to make sure to use the
	 * हाल sensitive name which is specअगरied by user अगर this is
	 * क्रम creation.
	 */
	अगर (flags & (LOOKUP_CREATE | LOOKUP_RENAME_TARGET))
		वापस 0;

	वापस vfat_revalidate_लघुname(dentry);
पूर्ण

/* वापसs the length of a काष्ठा qstr, ignoring trailing करोts */
अटल अचिन्हित पूर्णांक __vfat_striptail_len(अचिन्हित पूर्णांक len, स्थिर अक्षर *name)
अणु
	जबतक (len && name[len - 1] == '.')
		len--;
	वापस len;
पूर्ण

अटल अचिन्हित पूर्णांक vfat_striptail_len(स्थिर काष्ठा qstr *qstr)
अणु
	वापस __vfat_striptail_len(qstr->len, qstr->name);
पूर्ण

/*
 * Compute the hash क्रम the vfat name corresponding to the dentry.
 * Note: अगर the name is invalid, we leave the hash code unchanged so
 * that the existing dentry can be used. The vfat fs routines will
 * वापस ENOENT or EINVAL as appropriate.
 */
अटल पूर्णांक vfat_hash(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr)
अणु
	qstr->hash = full_name_hash(dentry, qstr->name, vfat_striptail_len(qstr));
	वापस 0;
पूर्ण

/*
 * Compute the hash क्रम the vfat name corresponding to the dentry.
 * Note: अगर the name is invalid, we leave the hash code unchanged so
 * that the existing dentry can be used. The vfat fs routines will
 * वापस ENOENT or EINVAL as appropriate.
 */
अटल पूर्णांक vfat_hashi(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr)
अणु
	काष्ठा nls_table *t = MSDOS_SB(dentry->d_sb)->nls_io;
	स्थिर अचिन्हित अक्षर *name;
	अचिन्हित पूर्णांक len;
	अचिन्हित दीर्घ hash;

	name = qstr->name;
	len = vfat_striptail_len(qstr);

	hash = init_name_hash(dentry);
	जबतक (len--)
		hash = partial_name_hash(nls_छोटे(t, *name++), hash);
	qstr->hash = end_name_hash(hash);

	वापस 0;
पूर्ण

/*
 * Case insensitive compare of two vfat names.
 */
अटल पूर्णांक vfat_cmpi(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा nls_table *t = MSDOS_SB(dentry->d_sb)->nls_io;
	अचिन्हित पूर्णांक alen, blen;

	/* A filename cannot end in '.' or we treat it like it has none */
	alen = vfat_striptail_len(name);
	blen = __vfat_striptail_len(len, str);
	अगर (alen == blen) अणु
		अगर (nls_strnicmp(t, name->name, str, alen) == 0)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Case sensitive compare of two vfat names.
 */
अटल पूर्णांक vfat_cmp(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	अचिन्हित पूर्णांक alen, blen;

	/* A filename cannot end in '.' or we treat it like it has none */
	alen = vfat_striptail_len(name);
	blen = __vfat_striptail_len(len, str);
	अगर (alen == blen) अणु
		अगर (म_भेदन(name->name, str, alen) == 0)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dentry_operations vfat_ci_dentry_ops = अणु
	.d_revalidate	= vfat_revalidate_ci,
	.d_hash		= vfat_hashi,
	.d_compare	= vfat_cmpi,
पूर्ण;

अटल स्थिर काष्ठा dentry_operations vfat_dentry_ops = अणु
	.d_revalidate	= vfat_revalidate,
	.d_hash		= vfat_hash,
	.d_compare	= vfat_cmp,
पूर्ण;

/* Characters that are undesirable in an MS-DOS file name */

अटल अंतरभूत ब_अक्षर_प्रकार vfat_bad_अक्षर(ब_अक्षर_प्रकार w)
अणु
	वापस (w < 0x0020)
	    || (w == '*') || (w == '?') || (w == '<') || (w == '>')
	    || (w == '|') || (w == '"') || (w == ':') || (w == '/')
	    || (w == '\\');
पूर्ण

अटल अंतरभूत ब_अक्षर_प्रकार vfat_replace_अक्षर(ब_अक्षर_प्रकार w)
अणु
	वापस (w == '[') || (w == ']') || (w == ';') || (w == ',')
	    || (w == '+') || (w == '=');
पूर्ण

अटल ब_अक्षर_प्रकार vfat_skip_अक्षर(ब_अक्षर_प्रकार w)
अणु
	वापस (w == '.') || (w == ' ');
पूर्ण

अटल अंतरभूत पूर्णांक vfat_is_used_badअक्षरs(स्थिर ब_अक्षर_प्रकार *s, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		अगर (vfat_bad_अक्षर(s[i]))
			वापस -EINVAL;

	अगर (s[i - 1] == ' ') /* last अक्षरacter cannot be space */
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक vfat_find_क्रमm(काष्ठा inode *dir, अचिन्हित अक्षर *name)
अणु
	काष्ठा fat_slot_info sinfo;
	पूर्णांक err = fat_scan(dir, name, &sinfo);
	अगर (err)
		वापस -ENOENT;
	brअन्यथा(sinfo.bh);
	वापस 0;
पूर्ण

/*
 * 1) Valid अक्षरacters क्रम the 8.3 क्रमmat alias are any combination of
 * letters, upperहाल alphabets, digits, any of the
 * following special अक्षरacters:
 *     $ % ' ` - @ अणु पूर्ण ~ ! # ( ) & _ ^
 * In this हाल Longfilename is not stored in disk.
 *
 * WinNT's Extension:
 * File name and extension name is contain upperहाल/lowerहाल
 * only. And it is expressed by CASE_LOWER_BASE and CASE_LOWER_EXT.
 *
 * 2) File name is 8.3 क्रमmat, but it contain the upperहाल and
 * lowerहाल अक्षर, muliti bytes अक्षर, etc. In this हाल numtail is not
 * added, but Longfilename is stored.
 *
 * 3) When the one except क्रम the above, or the following special
 * अक्षरacter are contained:
 *        .   [ ] ; , + =
 * numtail is added, and Longfilename must be stored in disk .
 */
काष्ठा लघुname_info अणु
	अचिन्हित अक्षर lower:1,
		      upper:1,
		      valid:1;
पूर्ण;
#घोषणा INIT_SHORTNAME_INFO(x)	करो अणु		\
	(x)->lower = 1;				\
	(x)->upper = 1;				\
	(x)->valid = 1;				\
पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक to_लघुname_अक्षर(काष्ठा nls_table *nls,
				    अचिन्हित अक्षर *buf, पूर्णांक buf_size,
				    ब_अक्षर_प्रकार *src, काष्ठा लघुname_info *info)
अणु
	पूर्णांक len;

	अगर (vfat_skip_अक्षर(*src)) अणु
		info->valid = 0;
		वापस 0;
	पूर्ण
	अगर (vfat_replace_अक्षर(*src)) अणु
		info->valid = 0;
		buf[0] = '_';
		वापस 1;
	पूर्ण

	len = nls->uni2अक्षर(*src, buf, buf_size);
	अगर (len <= 0) अणु
		info->valid = 0;
		buf[0] = '_';
		len = 1;
	पूर्ण अन्यथा अगर (len == 1) अणु
		अचिन्हित अक्षर prev = buf[0];

		अगर (buf[0] >= 0x7F) अणु
			info->lower = 0;
			info->upper = 0;
		पूर्ण

		buf[0] = nls_बड़े(nls, buf[0]);
		अगर (है_अक्षर(buf[0])) अणु
			अगर (buf[0] == prev)
				info->lower = 0;
			अन्यथा
				info->upper = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		info->lower = 0;
		info->upper = 0;
	पूर्ण

	वापस len;
पूर्ण

/*
 * Given a valid दीर्घname, create a unique लघुname.  Make sure the
 * लघुname करोes not exist
 * Returns negative number on error, 0 क्रम a normal
 * वापस, and 1 क्रम valid लघुname
 */
अटल पूर्णांक vfat_create_लघुname(काष्ठा inode *dir, काष्ठा nls_table *nls,
				 ब_अक्षर_प्रकार *uname, पूर्णांक ulen,
				 अचिन्हित अक्षर *name_res, अचिन्हित अक्षर *lहाल)
अणु
	काष्ठा fat_mount_options *opts = &MSDOS_SB(dir->i_sb)->options;
	ब_अक्षर_प्रकार *ip, *ext_start, *end, *name_start;
	अचिन्हित अक्षर base[9], ext[4], buf[5], *p;
	अचिन्हित अक्षर अक्षरbuf[NLS_MAX_CHARSET_SIZE];
	पूर्णांक chl, chi;
	पूर्णांक sz = 0, extlen, baselen, i, numtail_baselen, numtail2_baselen;
	पूर्णांक is_लघुname;
	काष्ठा लघुname_info base_info, ext_info;

	is_लघुname = 1;
	INIT_SHORTNAME_INFO(&base_info);
	INIT_SHORTNAME_INFO(&ext_info);

	/* Now, we need to create a लघुname from the दीर्घ name */
	ext_start = end = &uname[ulen];
	जबतक (--ext_start >= uname) अणु
		अगर (*ext_start == 0x002E) अणु	/* is `.' */
			अगर (ext_start == end - 1) अणु
				sz = ulen;
				ext_start = शून्य;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ext_start == uname - 1) अणु
		sz = ulen;
		ext_start = शून्य;
	पूर्ण अन्यथा अगर (ext_start) अणु
		/*
		 * Names which start with a करोt could be just
		 * an extension eg. "...test".  In this हाल Win95
		 * uses the extension as the name and sets no extension.
		 */
		name_start = &uname[0];
		जबतक (name_start < ext_start) अणु
			अगर (!vfat_skip_अक्षर(*name_start))
				अवरोध;
			name_start++;
		पूर्ण
		अगर (name_start != ext_start) अणु
			sz = ext_start - uname;
			ext_start++;
		पूर्ण अन्यथा अणु
			sz = ulen;
			ext_start = शून्य;
		पूर्ण
	पूर्ण

	numtail_baselen = 6;
	numtail2_baselen = 2;
	क्रम (baselen = i = 0, p = base, ip = uname; i < sz; i++, ip++) अणु
		chl = to_लघुname_अक्षर(nls, अक्षरbuf, माप(अक्षरbuf),
					ip, &base_info);
		अगर (chl == 0)
			जारी;

		अगर (baselen < 2 && (baselen + chl) > 2)
			numtail2_baselen = baselen;
		अगर (baselen < 6 && (baselen + chl) > 6)
			numtail_baselen = baselen;
		क्रम (chi = 0; chi < chl; chi++) अणु
			*p++ = अक्षरbuf[chi];
			baselen++;
			अगर (baselen >= 8)
				अवरोध;
		पूर्ण
		अगर (baselen >= 8) अणु
			अगर ((chi < chl - 1) || (ip + 1) - uname < sz)
				is_लघुname = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (baselen == 0) अणु
		वापस -EINVAL;
	पूर्ण

	extlen = 0;
	अगर (ext_start) अणु
		क्रम (p = ext, ip = ext_start; extlen < 3 && ip < end; ip++) अणु
			chl = to_लघुname_अक्षर(nls, अक्षरbuf, माप(अक्षरbuf),
						ip, &ext_info);
			अगर (chl == 0)
				जारी;

			अगर ((extlen + chl) > 3) अणु
				is_लघुname = 0;
				अवरोध;
			पूर्ण
			क्रम (chi = 0; chi < chl; chi++) अणु
				*p++ = अक्षरbuf[chi];
				extlen++;
			पूर्ण
			अगर (extlen >= 3) अणु
				अगर (ip + 1 != end)
					is_लघुname = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	ext[extlen] = '\0';
	base[baselen] = '\0';

	/* Yes, it can happen. ".\xe5" would करो it. */
	अगर (base[0] == DELETED_FLAG)
		base[0] = 0x05;

	/* OK, at this poपूर्णांक we know that base is not दीर्घer than 8 symbols,
	 * ext is not दीर्घer than 3, base is nonempty, both करोn't contain
	 * any bad symbols (lowerहाल transक्रमmed to upperहाल).
	 */

	स_रखो(name_res, ' ', MSDOS_NAME);
	स_नकल(name_res, base, baselen);
	स_नकल(name_res + 8, ext, extlen);
	*lहाल = 0;
	अगर (is_लघुname && base_info.valid && ext_info.valid) अणु
		अगर (vfat_find_क्रमm(dir, name_res) == 0)
			वापस -EEXIST;

		अगर (opts->लघुname & VFAT_SFN_CREATE_WIN95) अणु
			वापस (base_info.upper && ext_info.upper);
		पूर्ण अन्यथा अगर (opts->लघुname & VFAT_SFN_CREATE_WINNT) अणु
			अगर ((base_info.upper || base_info.lower) &&
			    (ext_info.upper || ext_info.lower)) अणु
				अगर (!base_info.upper && base_info.lower)
					*lहाल |= CASE_LOWER_BASE;
				अगर (!ext_info.upper && ext_info.lower)
					*lहाल |= CASE_LOWER_EXT;
				वापस 1;
			पूर्ण
			वापस 0;
		पूर्ण अन्यथा अणु
			BUG();
		पूर्ण
	पूर्ण

	अगर (opts->numtail == 0)
		अगर (vfat_find_क्रमm(dir, name_res) < 0)
			वापस 0;

	/*
	 * Try to find a unique extension.  This used to
	 * iterate through all possibilities sequentially,
	 * but that gave extremely bad perक्रमmance.  Winकरोws
	 * only tries a few हालs beक्रमe using अक्रमom
	 * values क्रम part of the base.
	 */

	अगर (baselen > 6) अणु
		baselen = numtail_baselen;
		name_res[7] = ' ';
	पूर्ण
	name_res[baselen] = '~';
	क्रम (i = 1; i < 10; i++) अणु
		name_res[baselen + 1] = i + '0';
		अगर (vfat_find_क्रमm(dir, name_res) < 0)
			वापस 0;
	पूर्ण

	i = jअगरfies;
	sz = (jअगरfies >> 16) & 0x7;
	अगर (baselen > 2) अणु
		baselen = numtail2_baselen;
		name_res[7] = ' ';
	पूर्ण
	name_res[baselen + 4] = '~';
	name_res[baselen + 5] = '1' + sz;
	जबतक (1) अणु
		snम_लिखो(buf, माप(buf), "%04X", i & 0xffff);
		स_नकल(&name_res[baselen], buf, 4);
		अगर (vfat_find_क्रमm(dir, name_res) < 0)
			अवरोध;
		i -= 11;
	पूर्ण
	वापस 0;
पूर्ण

/* Translate a string, including coded sequences पूर्णांकo Unicode */
अटल पूर्णांक
xlate_to_uni(स्थिर अचिन्हित अक्षर *name, पूर्णांक len, अचिन्हित अक्षर *outname,
	     पूर्णांक *दीर्घlen, पूर्णांक *outlen, पूर्णांक escape, पूर्णांक utf8,
	     काष्ठा nls_table *nls)
अणु
	स्थिर अचिन्हित अक्षर *ip;
	अचिन्हित अक्षर *op;
	पूर्णांक i, fill;
	पूर्णांक अक्षरlen;

	अगर (utf8) अणु
		*outlen = utf8s_to_utf16s(name, len, UTF16_HOST_ENDIAN,
				(ब_अक्षर_प्रकार *) outname, FAT_LFN_LEN + 2);
		अगर (*outlen < 0)
			वापस *outlen;
		अन्यथा अगर (*outlen > FAT_LFN_LEN)
			वापस -ENAMETOOLONG;

		op = &outname[*outlen * माप(ब_अक्षर_प्रकार)];
	पूर्ण अन्यथा अणु
		क्रम (i = 0, ip = name, op = outname, *outlen = 0;
			 i < len && *outlen < FAT_LFN_LEN;
			 *outlen += 1) अणु
			अगर (escape && (*ip == ':')) अणु
				u8 uc[2];

				अगर (i > len - 5)
					वापस -EINVAL;

				अगर (hex2bin(uc, ip + 1, 2) < 0)
					वापस -EINVAL;

				*(ब_अक्षर_प्रकार *)op = uc[0] << 8 | uc[1];

				op += 2;
				ip += 5;
				i += 5;
			पूर्ण अन्यथा अणु
				अक्षरlen = nls->अक्षर2uni(ip, len - i,
							(ब_अक्षर_प्रकार *)op);
				अगर (अक्षरlen < 0)
					वापस -EINVAL;
				ip += अक्षरlen;
				i += अक्षरlen;
				op += 2;
			पूर्ण
		पूर्ण
		अगर (i < len)
			वापस -ENAMETOOLONG;
	पूर्ण

	*दीर्घlen = *outlen;
	अगर (*outlen % 13) अणु
		*op++ = 0;
		*op++ = 0;
		*outlen += 1;
		अगर (*outlen % 13) अणु
			fill = 13 - (*outlen % 13);
			क्रम (i = 0; i < fill; i++) अणु
				*op++ = 0xff;
				*op++ = 0xff;
			पूर्ण
			*outlen += fill;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfat_build_slots(काष्ठा inode *dir, स्थिर अचिन्हित अक्षर *name,
			    पूर्णांक len, पूर्णांक is_dir, पूर्णांक cluster,
			    काष्ठा बारpec64 *ts,
			    काष्ठा msकरोs_dir_slot *slots, पूर्णांक *nr_slots)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(dir->i_sb);
	काष्ठा fat_mount_options *opts = &sbi->options;
	काष्ठा msकरोs_dir_slot *ps;
	काष्ठा msकरोs_dir_entry *de;
	अचिन्हित अक्षर cksum, lहाल;
	अचिन्हित अक्षर msकरोs_name[MSDOS_NAME];
	ब_अक्षर_प्रकार *uname;
	__le16 समय, date;
	u8 समय_cs;
	पूर्णांक err, ulen, usize, i;
	loff_t offset;

	*nr_slots = 0;

	uname = __getname();
	अगर (!uname)
		वापस -ENOMEM;

	err = xlate_to_uni(name, len, (अचिन्हित अक्षर *)uname, &ulen, &usize,
			   opts->unicode_xlate, opts->utf8, sbi->nls_io);
	अगर (err)
		जाओ out_मुक्त;

	err = vfat_is_used_badअक्षरs(uname, ulen);
	अगर (err)
		जाओ out_मुक्त;

	err = vfat_create_लघुname(dir, sbi->nls_disk, uname, ulen,
				    msकरोs_name, &lहाल);
	अगर (err < 0)
		जाओ out_मुक्त;
	अन्यथा अगर (err == 1) अणु
		de = (काष्ठा msकरोs_dir_entry *)slots;
		err = 0;
		जाओ लघुname;
	पूर्ण

	/* build the entry of दीर्घ file name */
	cksum = fat_checksum(msकरोs_name);

	*nr_slots = usize / 13;
	क्रम (ps = slots, i = *nr_slots; i > 0; i--, ps++) अणु
		ps->id = i;
		ps->attr = ATTR_EXT;
		ps->reserved = 0;
		ps->alias_checksum = cksum;
		ps->start = 0;
		offset = (i - 1) * 13;
		fatब_अक्षर_प्रकारo16(ps->name0_4, uname + offset, 5);
		fatब_अक्षर_प्रकारo16(ps->name5_10, uname + offset + 5, 6);
		fatब_अक्षर_प्रकारo16(ps->name11_12, uname + offset + 11, 2);
	पूर्ण
	slots[0].id |= 0x40;
	de = (काष्ठा msकरोs_dir_entry *)ps;

लघुname:
	/* build the entry of 8.3 alias name */
	(*nr_slots)++;
	स_नकल(de->name, msकरोs_name, MSDOS_NAME);
	de->attr = is_dir ? ATTR_सूची : ATTR_ARCH;
	de->lहाल = lहाल;
	fat_समय_unix2fat(sbi, ts, &समय, &date, &समय_cs);
	de->समय = de->स_समय = समय;
	de->date = de->cdate = de->adate = date;
	de->स_समय_cs = समय_cs;
	fat_set_start(de, cluster);
	de->size = 0;
out_मुक्त:
	__putname(uname);
	वापस err;
पूर्ण

अटल पूर्णांक vfat_add_entry(काष्ठा inode *dir, स्थिर काष्ठा qstr *qname,
			  पूर्णांक is_dir, पूर्णांक cluster, काष्ठा बारpec64 *ts,
			  काष्ठा fat_slot_info *sinfo)
अणु
	काष्ठा msकरोs_dir_slot *slots;
	अचिन्हित पूर्णांक len;
	पूर्णांक err, nr_slots;

	len = vfat_striptail_len(qname);
	अगर (len == 0)
		वापस -ENOENT;

	slots = kदो_स्मृति_array(MSDOS_SLOTS, माप(*slots), GFP_NOFS);
	अगर (slots == शून्य)
		वापस -ENOMEM;

	err = vfat_build_slots(dir, qname->name, len, is_dir, cluster, ts,
			       slots, &nr_slots);
	अगर (err)
		जाओ cleanup;

	err = fat_add_entries(dir, slots, nr_slots, sinfo);
	अगर (err)
		जाओ cleanup;

	/* update बारtamp */
	fat_truncate_समय(dir, ts, S_CTIME|S_MTIME);
	अगर (IS_सूचीSYNC(dir))
		(व्योम)fat_sync_inode(dir);
	अन्यथा
		mark_inode_dirty(dir);
cleanup:
	kमुक्त(slots);
	वापस err;
पूर्ण

अटल पूर्णांक vfat_find(काष्ठा inode *dir, स्थिर काष्ठा qstr *qname,
		     काष्ठा fat_slot_info *sinfo)
अणु
	अचिन्हित पूर्णांक len = vfat_striptail_len(qname);
	अगर (len == 0)
		वापस -ENOENT;
	वापस fat_search_दीर्घ(dir, qname->name, len, sinfo);
पूर्ण

अटल काष्ठा dentry *vfat_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा fat_slot_info sinfo;
	काष्ठा inode *inode;
	काष्ठा dentry *alias;
	पूर्णांक err;

	mutex_lock(&MSDOS_SB(sb)->s_lock);

	err = vfat_find(dir, &dentry->d_name, &sinfo);
	अगर (err) अणु
		अगर (err == -ENOENT) अणु
			inode = शून्य;
			जाओ out;
		पूर्ण
		जाओ error;
	पूर्ण

	inode = fat_build_inode(sb, sinfo.de, sinfo.i_pos);
	brअन्यथा(sinfo.bh);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		जाओ error;
	पूर्ण

	alias = d_find_alias(inode);
	/*
	 * Checking "alias->d_parent == dentry->d_parent" to make sure
	 * FS is not corrupted (especially द्विगुन linked dir).
	 */
	अगर (alias && alias->d_parent == dentry->d_parent) अणु
		/*
		 * This inode has non anonymous-DCACHE_DISCONNECTED
		 * dentry. This means, the user did ->lookup() by an
		 * another name (दीर्घname vs 8.3 alias of it) in past.
		 *
		 * Switch to new one क्रम reason of locality अगर possible.
		 */
		अगर (!S_ISसूची(inode->i_mode))
			d_move(alias, dentry);
		iput(inode);
		mutex_unlock(&MSDOS_SB(sb)->s_lock);
		वापस alias;
	पूर्ण अन्यथा
		dput(alias);

out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	अगर (!inode)
		vfat_d_version_set(dentry, inode_query_iversion(dir));
	वापस d_splice_alias(inode, dentry);
error:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक vfat_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा inode *inode;
	काष्ठा fat_slot_info sinfo;
	काष्ठा बारpec64 ts;
	पूर्णांक err;

	mutex_lock(&MSDOS_SB(sb)->s_lock);

	ts = current_समय(dir);
	err = vfat_add_entry(dir, &dentry->d_name, 0, 0, &ts, &sinfo);
	अगर (err)
		जाओ out;
	inode_inc_iversion(dir);

	inode = fat_build_inode(sb, sinfo.de, sinfo.i_pos);
	brअन्यथा(sinfo.bh);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		जाओ out;
	पूर्ण
	inode_inc_iversion(inode);
	fat_truncate_समय(inode, &ts, S_ATIME|S_CTIME|S_MTIME);
	/* बारtamp is alपढ़ोy written, so mark_inode_dirty() is unneeded. */

	d_instantiate(dentry, inode);
out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	वापस err;
पूर्ण

अटल पूर्णांक vfat_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा fat_slot_info sinfo;
	पूर्णांक err;

	mutex_lock(&MSDOS_SB(sb)->s_lock);

	err = fat_dir_empty(inode);
	अगर (err)
		जाओ out;
	err = vfat_find(dir, &dentry->d_name, &sinfo);
	अगर (err)
		जाओ out;

	err = fat_हटाओ_entries(dir, &sinfo);	/* and releases bh */
	अगर (err)
		जाओ out;
	drop_nlink(dir);

	clear_nlink(inode);
	fat_truncate_समय(inode, शून्य, S_ATIME|S_MTIME);
	fat_detach(inode);
	vfat_d_version_set(dentry, inode_query_iversion(dir));
out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);

	वापस err;
पूर्ण

अटल पूर्णांक vfat_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा fat_slot_info sinfo;
	पूर्णांक err;

	mutex_lock(&MSDOS_SB(sb)->s_lock);

	err = vfat_find(dir, &dentry->d_name, &sinfo);
	अगर (err)
		जाओ out;

	err = fat_हटाओ_entries(dir, &sinfo);	/* and releases bh */
	अगर (err)
		जाओ out;
	clear_nlink(inode);
	fat_truncate_समय(inode, शून्य, S_ATIME|S_MTIME);
	fat_detach(inode);
	vfat_d_version_set(dentry, inode_query_iversion(dir));
out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);

	वापस err;
पूर्ण

अटल पूर्णांक vfat_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा inode *inode;
	काष्ठा fat_slot_info sinfo;
	काष्ठा बारpec64 ts;
	पूर्णांक err, cluster;

	mutex_lock(&MSDOS_SB(sb)->s_lock);

	ts = current_समय(dir);
	cluster = fat_alloc_new_dir(dir, &ts);
	अगर (cluster < 0) अणु
		err = cluster;
		जाओ out;
	पूर्ण
	err = vfat_add_entry(dir, &dentry->d_name, 1, cluster, &ts, &sinfo);
	अगर (err)
		जाओ out_मुक्त;
	inode_inc_iversion(dir);
	inc_nlink(dir);

	inode = fat_build_inode(sb, sinfo.de, sinfo.i_pos);
	brअन्यथा(sinfo.bh);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		/* the directory was completed, just वापस a error */
		जाओ out;
	पूर्ण
	inode_inc_iversion(inode);
	set_nlink(inode, 2);
	fat_truncate_समय(inode, &ts, S_ATIME|S_CTIME|S_MTIME);
	/* बारtamp is alपढ़ोy written, so mark_inode_dirty() is unneeded. */

	d_instantiate(dentry, inode);

	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	वापस 0;

out_मुक्त:
	fat_मुक्त_clusters(dir, cluster);
out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	वापस err;
पूर्ण

अटल पूर्णांक vfat_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		       काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		       काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा buffer_head *करोtकरोt_bh;
	काष्ठा msकरोs_dir_entry *करोtकरोt_de;
	काष्ठा inode *old_inode, *new_inode;
	काष्ठा fat_slot_info old_sinfo, sinfo;
	काष्ठा बारpec64 ts;
	loff_t new_i_pos;
	पूर्णांक err, is_dir, update_करोtकरोt, corrupt = 0;
	काष्ठा super_block *sb = old_dir->i_sb;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	old_sinfo.bh = sinfo.bh = करोtकरोt_bh = शून्य;
	old_inode = d_inode(old_dentry);
	new_inode = d_inode(new_dentry);
	mutex_lock(&MSDOS_SB(sb)->s_lock);
	err = vfat_find(old_dir, &old_dentry->d_name, &old_sinfo);
	अगर (err)
		जाओ out;

	is_dir = S_ISसूची(old_inode->i_mode);
	update_करोtकरोt = (is_dir && old_dir != new_dir);
	अगर (update_करोtकरोt) अणु
		अगर (fat_get_करोtकरोt_entry(old_inode, &करोtकरोt_bh, &करोtकरोt_de)) अणु
			err = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	ts = current_समय(old_dir);
	अगर (new_inode) अणु
		अगर (is_dir) अणु
			err = fat_dir_empty(new_inode);
			अगर (err)
				जाओ out;
		पूर्ण
		new_i_pos = MSDOS_I(new_inode)->i_pos;
		fat_detach(new_inode);
	पूर्ण अन्यथा अणु
		err = vfat_add_entry(new_dir, &new_dentry->d_name, is_dir, 0,
				     &ts, &sinfo);
		अगर (err)
			जाओ out;
		new_i_pos = sinfo.i_pos;
	पूर्ण
	inode_inc_iversion(new_dir);

	fat_detach(old_inode);
	fat_attach(old_inode, new_i_pos);
	अगर (IS_सूचीSYNC(new_dir)) अणु
		err = fat_sync_inode(old_inode);
		अगर (err)
			जाओ error_inode;
	पूर्ण अन्यथा
		mark_inode_dirty(old_inode);

	अगर (update_करोtकरोt) अणु
		fat_set_start(करोtकरोt_de, MSDOS_I(new_dir)->i_logstart);
		mark_buffer_dirty_inode(करोtकरोt_bh, old_inode);
		अगर (IS_सूचीSYNC(new_dir)) अणु
			err = sync_dirty_buffer(करोtकरोt_bh);
			अगर (err)
				जाओ error_करोtकरोt;
		पूर्ण
		drop_nlink(old_dir);
		अगर (!new_inode)
 			inc_nlink(new_dir);
	पूर्ण

	err = fat_हटाओ_entries(old_dir, &old_sinfo);	/* and releases bh */
	old_sinfo.bh = शून्य;
	अगर (err)
		जाओ error_करोtकरोt;
	inode_inc_iversion(old_dir);
	fat_truncate_समय(old_dir, &ts, S_CTIME|S_MTIME);
	अगर (IS_सूचीSYNC(old_dir))
		(व्योम)fat_sync_inode(old_dir);
	अन्यथा
		mark_inode_dirty(old_dir);

	अगर (new_inode) अणु
		drop_nlink(new_inode);
		अगर (is_dir)
			drop_nlink(new_inode);
		fat_truncate_समय(new_inode, &ts, S_CTIME);
	पूर्ण
out:
	brअन्यथा(sinfo.bh);
	brअन्यथा(करोtकरोt_bh);
	brअन्यथा(old_sinfo.bh);
	mutex_unlock(&MSDOS_SB(sb)->s_lock);

	वापस err;

error_करोtकरोt:
	/* data cluster is shared, serious corruption */
	corrupt = 1;

	अगर (update_करोtकरोt) अणु
		fat_set_start(करोtकरोt_de, MSDOS_I(old_dir)->i_logstart);
		mark_buffer_dirty_inode(करोtकरोt_bh, old_inode);
		corrupt |= sync_dirty_buffer(करोtकरोt_bh);
	पूर्ण
error_inode:
	fat_detach(old_inode);
	fat_attach(old_inode, old_sinfo.i_pos);
	अगर (new_inode) अणु
		fat_attach(new_inode, new_i_pos);
		अगर (corrupt)
			corrupt |= fat_sync_inode(new_inode);
	पूर्ण अन्यथा अणु
		/*
		 * If new entry was not sharing the data cluster, it
		 * shouldn't be serious corruption.
		 */
		पूर्णांक err2 = fat_हटाओ_entries(new_dir, &sinfo);
		अगर (corrupt)
			corrupt |= err2;
		sinfo.bh = शून्य;
	पूर्ण
	अगर (corrupt < 0) अणु
		fat_fs_error(new_dir->i_sb,
			     "%s: Filesystem corrupted (i_pos %lld)",
			     __func__, sinfo.i_pos);
	पूर्ण
	जाओ out;
पूर्ण

अटल स्थिर काष्ठा inode_operations vfat_dir_inode_operations = अणु
	.create		= vfat_create,
	.lookup		= vfat_lookup,
	.unlink		= vfat_unlink,
	.सूची_गढ़ो		= vfat_सूची_गढ़ो,
	.सूची_हटाओ		= vfat_सूची_हटाओ,
	.नाम		= vfat_नाम,
	.setattr	= fat_setattr,
	.getattr	= fat_getattr,
	.update_समय	= fat_update_समय,
पूर्ण;

अटल व्योम setup(काष्ठा super_block *sb)
अणु
	MSDOS_SB(sb)->dir_ops = &vfat_dir_inode_operations;
	अगर (MSDOS_SB(sb)->options.name_check != 's')
		sb->s_d_op = &vfat_ci_dentry_ops;
	अन्यथा
		sb->s_d_op = &vfat_dentry_ops;
पूर्ण

अटल पूर्णांक vfat_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	वापस fat_fill_super(sb, data, silent, 1, setup);
पूर्ण

अटल काष्ठा dentry *vfat_mount(काष्ठा file_प्रणाली_type *fs_type,
		       पूर्णांक flags, स्थिर अक्षर *dev_name,
		       व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, vfat_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type vfat_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "vfat",
	.mount		= vfat_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV | FS_ALLOW_IDMAP,
पूर्ण;
MODULE_ALIAS_FS("vfat");

अटल पूर्णांक __init init_vfat_fs(व्योम)
अणु
	वापस रेजिस्टर_fileप्रणाली(&vfat_fs_type);
पूर्ण

अटल व्योम __निकास निकास_vfat_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&vfat_fs_type);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("VFAT filesystem support");
MODULE_AUTHOR("Gordon Chaffee");

module_init(init_vfat_fs)
module_निकास(निकास_vfat_fs)
