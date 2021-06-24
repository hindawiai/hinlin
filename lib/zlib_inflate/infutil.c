<शैली गुरु>
#समावेश <linux/zutil.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

/* Utility function: initialize zlib, unpack binary blob, clean up zlib,
 * वापस len or negative error code.
 */
पूर्णांक zlib_inflate_blob(व्योम *gunzip_buf, अचिन्हित पूर्णांक sz,
		      स्थिर व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	स्थिर u8 *zbuf = buf;
	काष्ठा z_stream_s *strm;
	पूर्णांक rc;

	rc = -ENOMEM;
	strm = kदो_स्मृति(माप(*strm), GFP_KERNEL);
	अगर (strm == शून्य)
		जाओ gunzip_nomem1;
	strm->workspace = kदो_स्मृति(zlib_inflate_workspacesize(), GFP_KERNEL);
	अगर (strm->workspace == शून्य)
		जाओ gunzip_nomem2;

	/* gzip header (1f,8b,08... 10 bytes total + possible asciz filename)
	 * expected to be stripped from input
	 */
	strm->next_in = zbuf;
	strm->avail_in = len;
	strm->next_out = gunzip_buf;
	strm->avail_out = sz;

	rc = zlib_inflateInit2(strm, -MAX_WBITS);
	अगर (rc == Z_OK) अणु
		rc = zlib_inflate(strm, Z_FINISH);
		/* after Z_FINISH, only Z_STREAM_END is "we unpacked it all" */
		अगर (rc == Z_STREAM_END)
			rc = sz - strm->avail_out;
		अन्यथा
			rc = -EINVAL;
		zlib_inflateEnd(strm);
	पूर्ण अन्यथा
		rc = -EINVAL;

	kमुक्त(strm->workspace);
gunzip_nomem2:
	kमुक्त(strm);
gunzip_nomem1:
	वापस rc; /* वापसs Z_OK (0) अगर successful */
पूर्ण
