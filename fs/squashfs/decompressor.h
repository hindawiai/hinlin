<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित DECOMPRESSOR_H
#घोषणा DECOMPRESSOR_H
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * decompressor.h
 */

#समावेश <linux/bपन.स>

काष्ठा squashfs_decompressor अणु
	व्योम	*(*init)(काष्ठा squashfs_sb_info *, व्योम *);
	व्योम	*(*comp_opts)(काष्ठा squashfs_sb_info *, व्योम *, पूर्णांक);
	व्योम	(*मुक्त)(व्योम *);
	पूर्णांक	(*decompress)(काष्ठा squashfs_sb_info *, व्योम *,
		काष्ठा bio *, पूर्णांक, पूर्णांक, काष्ठा squashfs_page_actor *);
	पूर्णांक	id;
	अक्षर	*name;
	पूर्णांक	supported;
पूर्ण;

अटल अंतरभूत व्योम *squashfs_comp_opts(काष्ठा squashfs_sb_info *msblk,
							व्योम *buff, पूर्णांक length)
अणु
	वापस msblk->decompressor->comp_opts ?
		msblk->decompressor->comp_opts(msblk, buff, length) : शून्य;
पूर्ण

#अगर_घोषित CONFIG_SQUASHFS_XZ
बाह्य स्थिर काष्ठा squashfs_decompressor squashfs_xz_comp_ops;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SQUASHFS_LZ4
बाह्य स्थिर काष्ठा squashfs_decompressor squashfs_lz4_comp_ops;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SQUASHFS_LZO
बाह्य स्थिर काष्ठा squashfs_decompressor squashfs_lzo_comp_ops;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SQUASHFS_ZLIB
बाह्य स्थिर काष्ठा squashfs_decompressor squashfs_zlib_comp_ops;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SQUASHFS_ZSTD
बाह्य स्थिर काष्ठा squashfs_decompressor squashfs_zstd_comp_ops;
#पूर्ण_अगर

#पूर्ण_अगर
