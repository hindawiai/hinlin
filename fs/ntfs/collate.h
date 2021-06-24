<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * collate.h - Defines क्रम NTFS kernel collation handling.  Part of the
 *	       Linux-NTFS project.
 *
 * Copyright (c) 2004 Anton Altaparmakov
 */

#अगर_अघोषित _LINUX_NTFS_COLLATE_H
#घोषणा _LINUX_NTFS_COLLATE_H

#समावेश "types.h"
#समावेश "volume.h"

अटल अंतरभूत bool ntfs_is_collation_rule_supported(COLLATION_RULE cr) अणु
	पूर्णांक i;

	/*
	 * FIXME:  At the moment we only support COLLATION_BINARY and
	 * COLLATION_NTOFS_ULONG, so we वापस false क्रम everything अन्यथा क्रम
	 * now.
	 */
	अगर (unlikely(cr != COLLATION_BINARY && cr != COLLATION_NTOFS_ULONG))
		वापस false;
	i = le32_to_cpu(cr);
	अगर (likely(((i >= 0) && (i <= 0x02)) ||
			((i >= 0x10) && (i <= 0x13))))
		वापस true;
	वापस false;
पूर्ण

बाह्य पूर्णांक ntfs_collate(ntfs_volume *vol, COLLATION_RULE cr,
		स्थिर व्योम *data1, स्थिर पूर्णांक data1_len,
		स्थिर व्योम *data2, स्थिर पूर्णांक data2_len);

#पूर्ण_अगर /* _LINUX_NTFS_COLLATE_H */
