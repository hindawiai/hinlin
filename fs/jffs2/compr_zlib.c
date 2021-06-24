<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#अगर !defined(__KERNEL__) && !defined(__ECOS)
#त्रुटि "The userspace support got too messy and was removed. Update your mkfs.jffs2"
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/zlib.h>
#समावेश <linux/zutil.h>
#समावेश "nodelist.h"
#समावेश "compr.h"

	/* Plan: call deflate() with avail_in == *sourcelen,
		avail_out = *dstlen - 12 and flush == Z_FINISH.
		If it करोesn't manage to finish,	call it again with
		avail_in == 0 and avail_out set to the reमुख्यing 12
		bytes क्रम it to clean up.
	   Q: Is 12 bytes sufficient?
	*/
#घोषणा STREAM_END_SPACE 12

अटल DEFINE_MUTEX(deflate_mutex);
अटल DEFINE_MUTEX(inflate_mutex);
अटल z_stream inf_strm, def_strm;

#अगर_घोषित __KERNEL__ /* Linux-only */
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>

अटल पूर्णांक __init alloc_workspaces(व्योम)
अणु
	def_strm.workspace = vदो_स्मृति(zlib_deflate_workspacesize(MAX_WBITS,
							MAX_MEM_LEVEL));
	अगर (!def_strm.workspace)
		वापस -ENOMEM;

	jffs2_dbg(1, "Allocated %d bytes for deflate workspace\n",
		  zlib_deflate_workspacesize(MAX_WBITS, MAX_MEM_LEVEL));
	inf_strm.workspace = vदो_स्मृति(zlib_inflate_workspacesize());
	अगर (!inf_strm.workspace) अणु
		vमुक्त(def_strm.workspace);
		वापस -ENOMEM;
	पूर्ण
	jffs2_dbg(1, "Allocated %d bytes for inflate workspace\n",
		  zlib_inflate_workspacesize());
	वापस 0;
पूर्ण

अटल व्योम मुक्त_workspaces(व्योम)
अणु
	vमुक्त(def_strm.workspace);
	vमुक्त(inf_strm.workspace);
पूर्ण
#अन्यथा
#घोषणा alloc_workspaces() (0)
#घोषणा मुक्त_workspaces() करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर /* __KERNEL__ */

अटल पूर्णांक jffs2_zlib_compress(अचिन्हित अक्षर *data_in,
			       अचिन्हित अक्षर *cpage_out,
			       uपूर्णांक32_t *sourcelen, uपूर्णांक32_t *dstlen)
अणु
	पूर्णांक ret;

	अगर (*dstlen <= STREAM_END_SPACE)
		वापस -1;

	mutex_lock(&deflate_mutex);

	अगर (Z_OK != zlib_deflateInit(&def_strm, 3)) अणु
		pr_warn("deflateInit failed\n");
		mutex_unlock(&deflate_mutex);
		वापस -1;
	पूर्ण

	def_strm.next_in = data_in;
	def_strm.total_in = 0;

	def_strm.next_out = cpage_out;
	def_strm.total_out = 0;

	जबतक (def_strm.total_out < *dstlen - STREAM_END_SPACE && def_strm.total_in < *sourcelen) अणु
		def_strm.avail_out = *dstlen - (def_strm.total_out + STREAM_END_SPACE);
		def_strm.avail_in = min_t(अचिन्हित दीर्घ,
			(*sourcelen-def_strm.total_in), def_strm.avail_out);
		jffs2_dbg(1, "calling deflate with avail_in %ld, avail_out %ld\n",
			  def_strm.avail_in, def_strm.avail_out);
		ret = zlib_deflate(&def_strm, Z_PARTIAL_FLUSH);
		jffs2_dbg(1, "deflate returned with avail_in %ld, avail_out %ld, total_in %ld, total_out %ld\n",
			  def_strm.avail_in, def_strm.avail_out,
			  def_strm.total_in, def_strm.total_out);
		अगर (ret != Z_OK) अणु
			jffs2_dbg(1, "deflate in loop returned %d\n", ret);
			zlib_deflateEnd(&def_strm);
			mutex_unlock(&deflate_mutex);
			वापस -1;
		पूर्ण
	पूर्ण
	def_strm.avail_out += STREAM_END_SPACE;
	def_strm.avail_in = 0;
	ret = zlib_deflate(&def_strm, Z_FINISH);
	zlib_deflateEnd(&def_strm);

	अगर (ret != Z_STREAM_END) अणु
		jffs2_dbg(1, "final deflate returned %d\n", ret);
		ret = -1;
		जाओ out;
	पूर्ण

	अगर (def_strm.total_out >= def_strm.total_in) अणु
		jffs2_dbg(1, "zlib compressed %ld bytes into %ld; failing\n",
			  def_strm.total_in, def_strm.total_out);
		ret = -1;
		जाओ out;
	पूर्ण

	jffs2_dbg(1, "zlib compressed %ld bytes into %ld\n",
		  def_strm.total_in, def_strm.total_out);

	*dstlen = def_strm.total_out;
	*sourcelen = def_strm.total_in;
	ret = 0;
 out:
	mutex_unlock(&deflate_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक jffs2_zlib_decompress(अचिन्हित अक्षर *data_in,
				 अचिन्हित अक्षर *cpage_out,
				 uपूर्णांक32_t srclen, uपूर्णांक32_t destlen)
अणु
	पूर्णांक ret;
	पूर्णांक wbits = MAX_WBITS;

	mutex_lock(&inflate_mutex);

	inf_strm.next_in = data_in;
	inf_strm.avail_in = srclen;
	inf_strm.total_in = 0;

	inf_strm.next_out = cpage_out;
	inf_strm.avail_out = destlen;
	inf_strm.total_out = 0;

	/* If it's deflate, and it's got no preset dictionary, then
	   we can tell zlib to skip the adler32 check. */
	अगर (srclen > 2 && !(data_in[1] & PRESET_DICT) &&
	    ((data_in[0] & 0x0f) == Z_DEFLATED) &&
	    !(((data_in[0]<<8) + data_in[1]) % 31)) अणु

		jffs2_dbg(2, "inflate skipping adler32\n");
		wbits = -((data_in[0] >> 4) + 8);
		inf_strm.next_in += 2;
		inf_strm.avail_in -= 2;
	पूर्ण अन्यथा अणु
		/* Let this reमुख्य D1 क्रम now -- it should never happen */
		jffs2_dbg(1, "inflate not skipping adler32\n");
	पूर्ण


	अगर (Z_OK != zlib_inflateInit2(&inf_strm, wbits)) अणु
		pr_warn("inflateInit failed\n");
		mutex_unlock(&inflate_mutex);
		वापस 1;
	पूर्ण

	जबतक((ret = zlib_inflate(&inf_strm, Z_FINISH)) == Z_OK)
		;
	अगर (ret != Z_STREAM_END) अणु
		pr_notice("inflate returned %d\n", ret);
	पूर्ण
	zlib_inflateEnd(&inf_strm);
	mutex_unlock(&inflate_mutex);
	वापस 0;
पूर्ण

अटल काष्ठा jffs2_compressor jffs2_zlib_comp = अणु
    .priority = JFFS2_ZLIB_PRIORITY,
    .name = "zlib",
    .compr = JFFS2_COMPR_ZLIB,
    .compress = &jffs2_zlib_compress,
    .decompress = &jffs2_zlib_decompress,
#अगर_घोषित JFFS2_ZLIB_DISABLED
    .disabled = 1,
#अन्यथा
    .disabled = 0,
#पूर्ण_अगर
पूर्ण;

पूर्णांक __init jffs2_zlib_init(व्योम)
अणु
    पूर्णांक ret;

    ret = alloc_workspaces();
    अगर (ret)
	    वापस ret;

    ret = jffs2_रेजिस्टर_compressor(&jffs2_zlib_comp);
    अगर (ret)
	    मुक्त_workspaces();

    वापस ret;
पूर्ण

व्योम jffs2_zlib_निकास(व्योम)
अणु
    jffs2_unरेजिस्टर_compressor(&jffs2_zlib_comp);
    मुक्त_workspaces();
पूर्ण
