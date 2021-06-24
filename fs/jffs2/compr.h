<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2004   Ferenc Havasi <havasi@inf.u-szeged.hu>,
 *		      University of Szeged, Hungary
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#अगर_अघोषित __JFFS2_COMPR_H__
#घोषणा __JFFS2_COMPR_H__

#समावेश <linux/kernel.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/jffs2.h>
#समावेश "jffs2_fs_i.h"
#समावेश "jffs2_fs_sb.h"
#समावेश "nodelist.h"

#घोषणा JFFS2_RUBINMIPS_PRIORITY 10
#घोषणा JFFS2_DYNRUBIN_PRIORITY  20
#घोषणा JFFS2_LZARI_PRIORITY     30
#घोषणा JFFS2_RTIME_PRIORITY     50
#घोषणा JFFS2_ZLIB_PRIORITY      60
#घोषणा JFFS2_LZO_PRIORITY       80


#घोषणा JFFS2_RUBINMIPS_DISABLED /* RUBINs will be used only */
#घोषणा JFFS2_DYNRUBIN_DISABLED  /*	   क्रम decompression */

#घोषणा JFFS2_COMPR_MODE_NONE       0
#घोषणा JFFS2_COMPR_MODE_PRIORITY   1
#घोषणा JFFS2_COMPR_MODE_SIZE       2
#घोषणा JFFS2_COMPR_MODE_FAVOURLZO  3
#घोषणा JFFS2_COMPR_MODE_FORCELZO   4
#घोषणा JFFS2_COMPR_MODE_FORCEZLIB  5

#घोषणा FAVOUR_LZO_PERCENT 80

काष्ठा jffs2_compressor अणु
	काष्ठा list_head list;
	पूर्णांक priority;			/* used by prirority comr. mode */
	अक्षर *name;
	अक्षर compr;			/* JFFS2_COMPR_XXX */
	पूर्णांक (*compress)(अचिन्हित अक्षर *data_in, अचिन्हित अक्षर *cpage_out,
			uपूर्णांक32_t *srclen, uपूर्णांक32_t *destlen);
	पूर्णांक (*decompress)(अचिन्हित अक्षर *cdata_in, अचिन्हित अक्षर *data_out,
			  uपूर्णांक32_t cdatalen, uपूर्णांक32_t datalen);
	पूर्णांक usecount;
	पूर्णांक disabled;		/* अगर set the compressor won't compress */
	अचिन्हित अक्षर *compr_buf;	/* used by size compr. mode */
	uपूर्णांक32_t compr_buf_size;	/* used by size compr. mode */
	uपूर्णांक32_t stat_compr_orig_size;
	uपूर्णांक32_t stat_compr_new_size;
	uपूर्णांक32_t stat_compr_blocks;
	uपूर्णांक32_t stat_decompr_blocks;
पूर्ण;

पूर्णांक jffs2_रेजिस्टर_compressor(काष्ठा jffs2_compressor *comp);
पूर्णांक jffs2_unरेजिस्टर_compressor(काष्ठा jffs2_compressor *comp);

पूर्णांक jffs2_compressors_init(व्योम);
पूर्णांक jffs2_compressors_निकास(व्योम);

uपूर्णांक16_t jffs2_compress(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
			अचिन्हित अक्षर *data_in, अचिन्हित अक्षर **cpage_out,
			uपूर्णांक32_t *datalen, uपूर्णांक32_t *cdatalen);

पूर्णांक jffs2_decompress(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
		     uपूर्णांक16_t comprtype, अचिन्हित अक्षर *cdata_in,
		     अचिन्हित अक्षर *data_out, uपूर्णांक32_t cdatalen, uपूर्णांक32_t datalen);

व्योम jffs2_मुक्त_comprbuf(अचिन्हित अक्षर *comprbuf, अचिन्हित अक्षर *orig);

/* Compressor modules */
/* These functions will be called by jffs2_compressors_init/निकास */

#अगर_घोषित CONFIG_JFFS2_RUBIN
पूर्णांक jffs2_rubinmips_init(व्योम);
व्योम jffs2_rubinmips_निकास(व्योम);
पूर्णांक jffs2_dynrubin_init(व्योम);
व्योम jffs2_dynrubin_निकास(व्योम);
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_RTIME
पूर्णांक jffs2_rसमय_init(व्योम);
व्योम jffs2_rसमय_निकास(व्योम);
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_ZLIB
पूर्णांक jffs2_zlib_init(व्योम);
व्योम jffs2_zlib_निकास(व्योम);
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_LZO
पूर्णांक jffs2_lzo_init(व्योम);
व्योम jffs2_lzo_निकास(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर /* __JFFS2_COMPR_H__ */
