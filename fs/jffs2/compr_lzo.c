<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2007 Nokia Corporation. All rights reserved.
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Created by Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/lzo.h>
#समावेश "compr.h"

अटल व्योम *lzo_mem;
अटल व्योम *lzo_compress_buf;
अटल DEFINE_MUTEX(deflate_mutex);	/* क्रम lzo_mem and lzo_compress_buf */

अटल व्योम मुक्त_workspace(व्योम)
अणु
	vमुक्त(lzo_mem);
	vमुक्त(lzo_compress_buf);
पूर्ण

अटल पूर्णांक __init alloc_workspace(व्योम)
अणु
	lzo_mem = vदो_स्मृति(LZO1X_MEM_COMPRESS);
	lzo_compress_buf = vदो_स्मृति(lzo1x_worst_compress(PAGE_SIZE));

	अगर (!lzo_mem || !lzo_compress_buf) अणु
		मुक्त_workspace();
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jffs2_lzo_compress(अचिन्हित अक्षर *data_in, अचिन्हित अक्षर *cpage_out,
			      uपूर्णांक32_t *sourcelen, uपूर्णांक32_t *dstlen)
अणु
	माप_प्रकार compress_size;
	पूर्णांक ret;

	mutex_lock(&deflate_mutex);
	ret = lzo1x_1_compress(data_in, *sourcelen, lzo_compress_buf, &compress_size, lzo_mem);
	अगर (ret != LZO_E_OK)
		जाओ fail;

	अगर (compress_size > *dstlen)
		जाओ fail;

	स_नकल(cpage_out, lzo_compress_buf, compress_size);
	mutex_unlock(&deflate_mutex);

	*dstlen = compress_size;
	वापस 0;

 fail:
	mutex_unlock(&deflate_mutex);
	वापस -1;
पूर्ण

अटल पूर्णांक jffs2_lzo_decompress(अचिन्हित अक्षर *data_in, अचिन्हित अक्षर *cpage_out,
				 uपूर्णांक32_t srclen, uपूर्णांक32_t destlen)
अणु
	माप_प्रकार dl = destlen;
	पूर्णांक ret;

	ret = lzo1x_decompress_safe(data_in, srclen, cpage_out, &dl);

	अगर (ret != LZO_E_OK || dl != destlen)
		वापस -1;

	वापस 0;
पूर्ण

अटल काष्ठा jffs2_compressor jffs2_lzo_comp = अणु
	.priority = JFFS2_LZO_PRIORITY,
	.name = "lzo",
	.compr = JFFS2_COMPR_LZO,
	.compress = &jffs2_lzo_compress,
	.decompress = &jffs2_lzo_decompress,
	.disabled = 0,
पूर्ण;

पूर्णांक __init jffs2_lzo_init(व्योम)
अणु
	पूर्णांक ret;

	ret = alloc_workspace();
	अगर (ret < 0)
		वापस ret;

	ret = jffs2_रेजिस्टर_compressor(&jffs2_lzo_comp);
	अगर (ret)
		मुक्त_workspace();

	वापस ret;
पूर्ण

व्योम jffs2_lzo_निकास(व्योम)
अणु
	jffs2_unरेजिस्टर_compressor(&jffs2_lzo_comp);
	मुक्त_workspace();
पूर्ण
