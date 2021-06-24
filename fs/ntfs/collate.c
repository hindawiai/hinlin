<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * collate.c - NTFS kernel collation handling.  Part of the Linux-NTFS project.
 *
 * Copyright (c) 2004 Anton Altaparmakov
 */

#समावेश "collate.h"
#समावेश "debug.h"
#समावेश "ntfs.h"

अटल पूर्णांक ntfs_collate_binary(ntfs_volume *vol,
		स्थिर व्योम *data1, स्थिर पूर्णांक data1_len,
		स्थिर व्योम *data2, स्थिर पूर्णांक data2_len)
अणु
	पूर्णांक rc;

	ntfs_debug("Entering.");
	rc = स_भेद(data1, data2, min(data1_len, data2_len));
	अगर (!rc && (data1_len != data2_len)) अणु
		अगर (data1_len < data2_len)
			rc = -1;
		अन्यथा
			rc = 1;
	पूर्ण
	ntfs_debug("Done, returning %i", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक ntfs_collate_ntofs_uदीर्घ(ntfs_volume *vol,
		स्थिर व्योम *data1, स्थिर पूर्णांक data1_len,
		स्थिर व्योम *data2, स्थिर पूर्णांक data2_len)
अणु
	पूर्णांक rc;
	u32 d1, d2;

	ntfs_debug("Entering.");
	// FIXME:  We करोn't really want to bug here.
	BUG_ON(data1_len != data2_len);
	BUG_ON(data1_len != 4);
	d1 = le32_to_cpup(data1);
	d2 = le32_to_cpup(data2);
	अगर (d1 < d2)
		rc = -1;
	अन्यथा अणु
		अगर (d1 == d2)
			rc = 0;
		अन्यथा
			rc = 1;
	पूर्ण
	ntfs_debug("Done, returning %i", rc);
	वापस rc;
पूर्ण

प्रकार पूर्णांक (*ntfs_collate_func_t)(ntfs_volume *, स्थिर व्योम *, स्थिर पूर्णांक,
		स्थिर व्योम *, स्थिर पूर्णांक);

अटल ntfs_collate_func_t ntfs_करो_collate0x0[3] = अणु
	ntfs_collate_binary,
	शून्य/*ntfs_collate_file_name*/,
	शून्य/*ntfs_collate_unicode_string*/,
पूर्ण;

अटल ntfs_collate_func_t ntfs_करो_collate0x1[4] = अणु
	ntfs_collate_ntofs_uदीर्घ,
	शून्य/*ntfs_collate_ntofs_sid*/,
	शून्य/*ntfs_collate_ntofs_security_hash*/,
	शून्य/*ntfs_collate_ntofs_uदीर्घs*/,
पूर्ण;

/**
 * ntfs_collate - collate two data items using a specअगरied collation rule
 * @vol:	ntfs volume to which the data items beदीर्घ
 * @cr:		collation rule to use when comparing the items
 * @data1:	first data item to collate
 * @data1_len:	length in bytes of @data1
 * @data2:	second data item to collate
 * @data2_len:	length in bytes of @data2
 *
 * Collate the two data items @data1 and @data2 using the collation rule @cr
 * and वापस -1, 0, ir 1 अगर @data1 is found, respectively, to collate beक्रमe,
 * to match, or to collate after @data2.
 *
 * For speed we use the collation rule @cr as an index पूर्णांकo two tables of
 * function poपूर्णांकers to call the appropriate collation function.
 */
पूर्णांक ntfs_collate(ntfs_volume *vol, COLLATION_RULE cr,
		स्थिर व्योम *data1, स्थिर पूर्णांक data1_len,
		स्थिर व्योम *data2, स्थिर पूर्णांक data2_len) अणु
	पूर्णांक i;

	ntfs_debug("Entering.");
	/*
	 * FIXME:  At the moment we only support COLLATION_BINARY and
	 * COLLATION_NTOFS_ULONG, so we BUG() क्रम everything अन्यथा क्रम now.
	 */
	BUG_ON(cr != COLLATION_BINARY && cr != COLLATION_NTOFS_ULONG);
	i = le32_to_cpu(cr);
	BUG_ON(i < 0);
	अगर (i <= 0x02)
		वापस ntfs_करो_collate0x0[i](vol, data1, data1_len,
				data2, data2_len);
	BUG_ON(i < 0x10);
	i -= 0x10;
	अगर (likely(i <= 3))
		वापस ntfs_करो_collate0x1[i](vol, data1, data1_len,
				data2, data2_len);
	BUG();
	वापस 0;
पूर्ण
