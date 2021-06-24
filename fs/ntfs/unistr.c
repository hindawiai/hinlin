<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * unistr.c - NTFS Unicode string handling. Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2006 Anton Altaparmakov
 */

#समावेश <linux/slab.h>

#समावेश "types.h"
#समावेश "debug.h"
#समावेश "ntfs.h"

/*
 * IMPORTANT
 * =========
 *
 * All these routines assume that the Unicode अक्षरacters are in little endian
 * encoding inside the strings!!!
 */

/*
 * This is used by the name collation functions to quickly determine what
 * अक्षरacters are (in)valid.
 */
अटल स्थिर u8 legal_ansi_अक्षर_array[0x40] = अणु
	0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,

	0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,

	0x17, 0x07, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17,
	0x17, 0x17, 0x18, 0x16, 0x16, 0x17, 0x07, 0x00,

	0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17,
	0x17, 0x17, 0x04, 0x16, 0x18, 0x16, 0x18, 0x18,
पूर्ण;

/**
 * ntfs_are_names_equal - compare two Unicode names क्रम equality
 * @s1:			name to compare to @s2
 * @s1_len:		length in Unicode अक्षरacters of @s1
 * @s2:			name to compare to @s1
 * @s2_len:		length in Unicode अक्षरacters of @s2
 * @ic:			ignore हाल bool
 * @upहाल:		upहाल table (only अगर @ic == IGNORE_CASE)
 * @upहाल_size:	length in Unicode अक्षरacters of @upहाल (अगर present)
 *
 * Compare the names @s1 and @s2 and वापस 'true' (1) अगर the names are
 * identical, or 'false' (0) अगर they are not identical. If @ic is IGNORE_CASE,
 * the @upहाल table is used to perक्रमma a हाल insensitive comparison.
 */
bool ntfs_are_names_equal(स्थिर ntfsअक्षर *s1, माप_प्रकार s1_len,
		स्थिर ntfsअक्षर *s2, माप_प्रकार s2_len, स्थिर IGNORE_CASE_BOOL ic,
		स्थिर ntfsअक्षर *upहाल, स्थिर u32 upहाल_size)
अणु
	अगर (s1_len != s2_len)
		वापस false;
	अगर (ic == CASE_SENSITIVE)
		वापस !ntfs_ucsncmp(s1, s2, s1_len);
	वापस !ntfs_ucsnहालcmp(s1, s2, s1_len, upहाल, upहाल_size);
पूर्ण

/**
 * ntfs_collate_names - collate two Unicode names
 * @name1:	first Unicode name to compare
 * @name2:	second Unicode name to compare
 * @err_val:	अगर @name1 contains an invalid अक्षरacter वापस this value
 * @ic:		either CASE_SENSITIVE or IGNORE_CASE
 * @upहाल:	upहाल table (ignored अगर @ic is CASE_SENSITIVE)
 * @upहाल_len:	upहाल table size (ignored अगर @ic is CASE_SENSITIVE)
 *
 * ntfs_collate_names collates two Unicode names and वापसs:
 *
 *  -1 अगर the first name collates beक्रमe the second one,
 *   0 अगर the names match,
 *   1 अगर the second name collates beक्रमe the first one, or
 * @err_val अगर an invalid अक्षरacter is found in @name1 during the comparison.
 *
 * The following अक्षरacters are considered invalid: '"', '*', '<', '>' and '?'.
 */
पूर्णांक ntfs_collate_names(स्थिर ntfsअक्षर *name1, स्थिर u32 name1_len,
		स्थिर ntfsअक्षर *name2, स्थिर u32 name2_len,
		स्थिर पूर्णांक err_val, स्थिर IGNORE_CASE_BOOL ic,
		स्थिर ntfsअक्षर *upहाल, स्थिर u32 upहाल_len)
अणु
	u32 cnt, min_len;
	u16 c1, c2;

	min_len = name1_len;
	अगर (name1_len > name2_len)
		min_len = name2_len;
	क्रम (cnt = 0; cnt < min_len; ++cnt) अणु
		c1 = le16_to_cpu(*name1++);
		c2 = le16_to_cpu(*name2++);
		अगर (ic) अणु
			अगर (c1 < upहाल_len)
				c1 = le16_to_cpu(upहाल[c1]);
			अगर (c2 < upहाल_len)
				c2 = le16_to_cpu(upहाल[c2]);
		पूर्ण
		अगर (c1 < 64 && legal_ansi_अक्षर_array[c1] & 8)
			वापस err_val;
		अगर (c1 < c2)
			वापस -1;
		अगर (c1 > c2)
			वापस 1;
	पूर्ण
	अगर (name1_len < name2_len)
		वापस -1;
	अगर (name1_len == name2_len)
		वापस 0;
	/* name1_len > name2_len */
	c1 = le16_to_cpu(*name1);
	अगर (c1 < 64 && legal_ansi_अक्षर_array[c1] & 8)
		वापस err_val;
	वापस 1;
पूर्ण

/**
 * ntfs_ucsncmp - compare two little endian Unicode strings
 * @s1:		first string
 * @s2:		second string
 * @n:		maximum unicode अक्षरacters to compare
 *
 * Compare the first @n अक्षरacters of the Unicode strings @s1 and @s2,
 * The strings in little endian क्रमmat and appropriate le16_to_cpu()
 * conversion is perक्रमmed on non-little endian machines.
 *
 * The function वापसs an पूर्णांकeger less than, equal to, or greater than zero
 * अगर @s1 (or the first @n Unicode अक्षरacters thereof) is found, respectively,
 * to be less than, to match, or be greater than @s2.
 */
पूर्णांक ntfs_ucsncmp(स्थिर ntfsअक्षर *s1, स्थिर ntfsअक्षर *s2, माप_प्रकार n)
अणु
	u16 c1, c2;
	माप_प्रकार i;

	क्रम (i = 0; i < n; ++i) अणु
		c1 = le16_to_cpu(s1[i]);
		c2 = le16_to_cpu(s2[i]);
		अगर (c1 < c2)
			वापस -1;
		अगर (c1 > c2)
			वापस 1;
		अगर (!c1)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ntfs_ucsnहालcmp - compare two little endian Unicode strings, ignoring हाल
 * @s1:			first string
 * @s2:			second string
 * @n:			maximum unicode अक्षरacters to compare
 * @upहाल:		upहाल table
 * @upहाल_size:	upहाल table size in Unicode अक्षरacters
 *
 * Compare the first @n अक्षरacters of the Unicode strings @s1 and @s2,
 * ignoring हाल. The strings in little endian क्रमmat and appropriate
 * le16_to_cpu() conversion is perक्रमmed on non-little endian machines.
 *
 * Each अक्षरacter is upperहालd using the @upहाल table beक्रमe the comparison.
 *
 * The function वापसs an पूर्णांकeger less than, equal to, or greater than zero
 * अगर @s1 (or the first @n Unicode अक्षरacters thereof) is found, respectively,
 * to be less than, to match, or be greater than @s2.
 */
पूर्णांक ntfs_ucsnहालcmp(स्थिर ntfsअक्षर *s1, स्थिर ntfsअक्षर *s2, माप_प्रकार n,
		स्थिर ntfsअक्षर *upहाल, स्थिर u32 upहाल_size)
अणु
	माप_प्रकार i;
	u16 c1, c2;

	क्रम (i = 0; i < n; ++i) अणु
		अगर ((c1 = le16_to_cpu(s1[i])) < upहाल_size)
			c1 = le16_to_cpu(upहाल[c1]);
		अगर ((c2 = le16_to_cpu(s2[i])) < upहाल_size)
			c2 = le16_to_cpu(upहाल[c2]);
		अगर (c1 < c2)
			वापस -1;
		अगर (c1 > c2)
			वापस 1;
		अगर (!c1)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

व्योम ntfs_upहाल_name(ntfsअक्षर *name, u32 name_len, स्थिर ntfsअक्षर *upहाल,
		स्थिर u32 upहाल_len)
अणु
	u32 i;
	u16 u;

	क्रम (i = 0; i < name_len; i++)
		अगर ((u = le16_to_cpu(name[i])) < upहाल_len)
			name[i] = upहाल[u];
पूर्ण

व्योम ntfs_file_upहाल_value(खाता_NAME_ATTR *file_name_attr,
		स्थिर ntfsअक्षर *upहाल, स्थिर u32 upहाल_len)
अणु
	ntfs_upहाल_name((ntfsअक्षर*)&file_name_attr->file_name,
			file_name_attr->file_name_length, upहाल, upहाल_len);
पूर्ण

पूर्णांक ntfs_file_compare_values(खाता_NAME_ATTR *file_name_attr1,
		खाता_NAME_ATTR *file_name_attr2,
		स्थिर पूर्णांक err_val, स्थिर IGNORE_CASE_BOOL ic,
		स्थिर ntfsअक्षर *upहाल, स्थिर u32 upहाल_len)
अणु
	वापस ntfs_collate_names((ntfsअक्षर*)&file_name_attr1->file_name,
			file_name_attr1->file_name_length,
			(ntfsअक्षर*)&file_name_attr2->file_name,
			file_name_attr2->file_name_length,
			err_val, ic, upहाल, upहाल_len);
पूर्ण

/**
 * ntfs_nlstoucs - convert NLS string to little endian Unicode string
 * @vol:	ntfs volume which we are working with
 * @ins:	input NLS string buffer
 * @ins_len:	length of input string in bytes
 * @outs:	on वापस contains the allocated output Unicode string buffer
 *
 * Convert the input string @ins, which is in whatever क्रमmat the loaded NLS
 * map dictates, पूर्णांकo a little endian, 2-byte Unicode string.
 *
 * This function allocates the string and the caller is responsible क्रम
 * calling kmem_cache_मुक्त(ntfs_name_cache, *@outs); when finished with it.
 *
 * On success the function वापसs the number of Unicode अक्षरacters written to
 * the output string *@outs (>= 0), not counting the terminating Unicode शून्य
 * अक्षरacter. *@outs is set to the allocated output string buffer.
 *
 * On error, a negative number corresponding to the error code is वापसed. In
 * that हाल the output string is not allocated. Both *@outs and *@outs_len
 * are then undefined.
 *
 * This might look a bit odd due to fast path optimization...
 */
पूर्णांक ntfs_nlstoucs(स्थिर ntfs_volume *vol, स्थिर अक्षर *ins,
		स्थिर पूर्णांक ins_len, ntfsअक्षर **outs)
अणु
	काष्ठा nls_table *nls = vol->nls_map;
	ntfsअक्षर *ucs;
	ब_अक्षर_प्रकार wc;
	पूर्णांक i, o, wc_len;

	/* We करो not trust outside sources. */
	अगर (likely(ins)) अणु
		ucs = kmem_cache_alloc(ntfs_name_cache, GFP_NOFS);
		अगर (likely(ucs)) अणु
			क्रम (i = o = 0; i < ins_len; i += wc_len) अणु
				wc_len = nls->अक्षर2uni(ins + i, ins_len - i,
						&wc);
				अगर (likely(wc_len >= 0 &&
						o < NTFS_MAX_NAME_LEN)) अणु
					अगर (likely(wc)) अणु
						ucs[o++] = cpu_to_le16(wc);
						जारी;
					पूर्ण /* अन्यथा अगर (!wc) */
					अवरोध;
				पूर्ण /* अन्यथा अगर (wc_len < 0 ||
						o >= NTFS_MAX_NAME_LEN) */
				जाओ name_err;
			पूर्ण
			ucs[o] = 0;
			*outs = ucs;
			वापस o;
		पूर्ण /* अन्यथा अगर (!ucs) */
		ntfs_error(vol->sb, "Failed to allocate buffer for converted "
				"name from ntfs_name_cache.");
		वापस -ENOMEM;
	पूर्ण /* अन्यथा अगर (!ins) */
	ntfs_error(vol->sb, "Received NULL pointer.");
	वापस -EINVAL;
name_err:
	kmem_cache_मुक्त(ntfs_name_cache, ucs);
	अगर (wc_len < 0) अणु
		ntfs_error(vol->sb, "Name using character set %s contains "
				"characters that cannot be converted to "
				"Unicode.", nls->अक्षरset);
		i = -EILSEQ;
	पूर्ण अन्यथा /* अगर (o >= NTFS_MAX_NAME_LEN) */ अणु
		ntfs_error(vol->sb, "Name is too long (maximum length for a "
				"name on NTFS is %d Unicode characters.",
				NTFS_MAX_NAME_LEN);
		i = -ENAMETOOLONG;
	पूर्ण
	वापस i;
पूर्ण

/**
 * ntfs_ucstonls - convert little endian Unicode string to NLS string
 * @vol:	ntfs volume which we are working with
 * @ins:	input Unicode string buffer
 * @ins_len:	length of input string in Unicode अक्षरacters
 * @outs:	on वापस contains the (allocated) output NLS string buffer
 * @outs_len:	length of output string buffer in bytes
 *
 * Convert the input little endian, 2-byte Unicode string @ins, of length
 * @ins_len पूर्णांकo the string क्रमmat dictated by the loaded NLS.
 *
 * If *@outs is शून्य, this function allocates the string and the caller is
 * responsible क्रम calling kमुक्त(*@outs); when finished with it. In this हाल
 * @outs_len is ignored and can be 0.
 *
 * On success the function वापसs the number of bytes written to the output
 * string *@outs (>= 0), not counting the terminating शून्य byte. If the output
 * string buffer was allocated, *@outs is set to it.
 *
 * On error, a negative number corresponding to the error code is वापसed. In
 * that हाल the output string is not allocated. The contents of *@outs are
 * then undefined.
 *
 * This might look a bit odd due to fast path optimization...
 */
पूर्णांक ntfs_ucstonls(स्थिर ntfs_volume *vol, स्थिर ntfsअक्षर *ins,
		स्थिर पूर्णांक ins_len, अचिन्हित अक्षर **outs, पूर्णांक outs_len)
अणु
	काष्ठा nls_table *nls = vol->nls_map;
	अचिन्हित अक्षर *ns;
	पूर्णांक i, o, ns_len, wc;

	/* We करोn't trust outside sources. */
	अगर (ins) अणु
		ns = *outs;
		ns_len = outs_len;
		अगर (ns && !ns_len) अणु
			wc = -ENAMETOOLONG;
			जाओ conversion_err;
		पूर्ण
		अगर (!ns) अणु
			ns_len = ins_len * NLS_MAX_CHARSET_SIZE;
			ns = kदो_स्मृति(ns_len + 1, GFP_NOFS);
			अगर (!ns)
				जाओ mem_err_out;
		पूर्ण
		क्रम (i = o = 0; i < ins_len; i++) अणु
retry:			wc = nls->uni2अक्षर(le16_to_cpu(ins[i]), ns + o,
					ns_len - o);
			अगर (wc > 0) अणु
				o += wc;
				जारी;
			पूर्ण अन्यथा अगर (!wc)
				अवरोध;
			अन्यथा अगर (wc == -ENAMETOOLONG && ns != *outs) अणु
				अचिन्हित अक्षर *tc;
				/* Grow in multiples of 64 bytes. */
				tc = kदो_स्मृति((ns_len + 64) &
						~63, GFP_NOFS);
				अगर (tc) अणु
					स_नकल(tc, ns, ns_len);
					ns_len = ((ns_len + 64) & ~63) - 1;
					kमुक्त(ns);
					ns = tc;
					जाओ retry;
				पूर्ण /* No memory so जाओ conversion_error; */
			पूर्ण /* wc < 0, real error. */
			जाओ conversion_err;
		पूर्ण
		ns[o] = 0;
		*outs = ns;
		वापस o;
	पूर्ण /* अन्यथा (!ins) */
	ntfs_error(vol->sb, "Received NULL pointer.");
	वापस -EINVAL;
conversion_err:
	ntfs_error(vol->sb, "Unicode name contains characters that cannot be "
			"converted to character set %s.  You might want to "
			"try to use the mount option nls=utf8.", nls->अक्षरset);
	अगर (ns != *outs)
		kमुक्त(ns);
	अगर (wc != -ENAMETOOLONG)
		wc = -EILSEQ;
	वापस wc;
mem_err_out:
	ntfs_error(vol->sb, "Failed to allocate name!");
	वापस -ENOMEM;
पूर्ण
