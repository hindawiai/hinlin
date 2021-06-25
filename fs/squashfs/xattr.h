<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2010
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * xattr.h
 */

#अगर_घोषित CONFIG_SQUASHFS_XATTR
बाह्य __le64 *squashfs_पढ़ो_xattr_id_table(काष्ठा super_block *, u64,
		u64 *, पूर्णांक *);
बाह्य पूर्णांक squashfs_xattr_lookup(काष्ठा super_block *, अचिन्हित पूर्णांक, पूर्णांक *,
		अचिन्हित पूर्णांक *, अचिन्हित दीर्घ दीर्घ *);
#अन्यथा
अटल अंतरभूत __le64 *squashfs_पढ़ो_xattr_id_table(काष्ठा super_block *sb,
		u64 start, u64 *xattr_table_start, पूर्णांक *xattr_ids)
अणु
	काष्ठा squashfs_xattr_id_table *id_table;

	id_table = squashfs_पढ़ो_table(sb, start, माप(*id_table));
	अगर (IS_ERR(id_table))
		वापस (__le64 *) id_table;

	*xattr_table_start = le64_to_cpu(id_table->xattr_table_start);
	kमुक्त(id_table);

	ERROR("Xattrs in filesystem, these will be ignored\n");
	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत पूर्णांक squashfs_xattr_lookup(काष्ठा super_block *sb,
		अचिन्हित पूर्णांक index, पूर्णांक *count, अचिन्हित पूर्णांक *size,
		अचिन्हित दीर्घ दीर्घ *xattr)
अणु
	वापस 0;
पूर्ण
#घोषणा squashfs_listxattr शून्य
#घोषणा squashfs_xattr_handlers शून्य
#पूर्ण_अगर
