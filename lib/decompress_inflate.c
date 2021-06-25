<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_घोषित STATIC
#घोषणा PREBOOT
/* Pre-boot environment: included */

/* prevent inclusion of _LINUX_KERNEL_H in pre-boot environment: lots
 * errors about console_prपूर्णांकk etc... on ARM */
#घोषणा _LINUX_KERNEL_H

#समावेश "zlib_inflate/inftrees.c"
#समावेश "zlib_inflate/inffast.c"
#समावेश "zlib_inflate/inflate.c"
#अगर_घोषित CONFIG_ZLIB_DFLTCC
#समावेश "zlib_dfltcc/dfltcc.c"
#समावेश "zlib_dfltcc/dfltcc_inflate.c"
#पूर्ण_अगर

#अन्यथा /* STATIC */
/* initramfs et al: linked */

#समावेश <linux/zutil.h>

#समावेश "zlib_inflate/inftrees.h"
#समावेश "zlib_inflate/inffast.h"
#समावेश "zlib_inflate/inflate.h"

#समावेश "zlib_inflate/infutil.h"
#समावेश <linux/decompress/inflate.h>

#पूर्ण_अगर /* STATIC */

#समावेश <linux/decompress/mm.h>

#घोषणा GZIP_IOBUF_SIZE (16*1024)

अटल दीर्घ INIT nofill(व्योम *buffer, अचिन्हित दीर्घ len)
अणु
	वापस -1;
पूर्ण

/* Included from initramfs et al code */
STATIC पूर्णांक INIT __gunzip(अचिन्हित अक्षर *buf, दीर्घ len,
		       दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
		       दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ),
		       अचिन्हित अक्षर *out_buf, दीर्घ out_len,
		       दीर्घ *pos,
		       व्योम(*error)(अक्षर *x)) अणु
	u8 *zbuf;
	काष्ठा z_stream_s *strm;
	पूर्णांक rc;

	rc = -1;
	अगर (flush) अणु
		out_len = 0x8000; /* 32 K */
		out_buf = दो_स्मृति(out_len);
	पूर्ण अन्यथा अणु
		अगर (!out_len)
			out_len = ((माप_प्रकार)~0) - (माप_प्रकार)out_buf; /* no limit */
	पूर्ण
	अगर (!out_buf) अणु
		error("Out of memory while allocating output buffer");
		जाओ gunzip_nomem1;
	पूर्ण

	अगर (buf)
		zbuf = buf;
	अन्यथा अणु
		zbuf = दो_स्मृति(GZIP_IOBUF_SIZE);
		len = 0;
	पूर्ण
	अगर (!zbuf) अणु
		error("Out of memory while allocating input buffer");
		जाओ gunzip_nomem2;
	पूर्ण

	strm = दो_स्मृति(माप(*strm));
	अगर (strm == शून्य) अणु
		error("Out of memory while allocating z_stream");
		जाओ gunzip_nomem3;
	पूर्ण

	strm->workspace = दो_स्मृति(flush ? zlib_inflate_workspacesize() :
#अगर_घोषित CONFIG_ZLIB_DFLTCC
	/* Always allocate the full workspace क्रम DFLTCC */
				 zlib_inflate_workspacesize());
#अन्यथा
				 माप(काष्ठा inflate_state));
#पूर्ण_अगर
	अगर (strm->workspace == शून्य) अणु
		error("Out of memory while allocating workspace");
		जाओ gunzip_nomem4;
	पूर्ण

	अगर (!fill)
		fill = nofill;

	अगर (len == 0)
		len = fill(zbuf, GZIP_IOBUF_SIZE);

	/* verअगरy the gzip header */
	अगर (len < 10 ||
	   zbuf[0] != 0x1f || zbuf[1] != 0x8b || zbuf[2] != 0x08) अणु
		अगर (pos)
			*pos = 0;
		error("Not a gzip file");
		जाओ gunzip_5;
	पूर्ण

	/* skip over gzip header (1f,8b,08... 10 bytes total +
	 * possible asciz filename)
	 */
	strm->next_in = zbuf + 10;
	strm->avail_in = len - 10;
	/* skip over asciz filename */
	अगर (zbuf[3] & 0x8) अणु
		करो अणु
			/*
			 * If the filename करोesn't fit पूर्णांकo the buffer,
			 * the file is very probably corrupt. Don't try
			 * to पढ़ो more data.
			 */
			अगर (strm->avail_in == 0) अणु
				error("header error");
				जाओ gunzip_5;
			पूर्ण
			--strm->avail_in;
		पूर्ण जबतक (*strm->next_in++);
	पूर्ण

	strm->next_out = out_buf;
	strm->avail_out = out_len;

	rc = zlib_inflateInit2(strm, -MAX_WBITS);

#अगर_घोषित CONFIG_ZLIB_DFLTCC
	/* Always keep the winकरोw क्रम DFLTCC */
#अन्यथा
	अगर (!flush) अणु
		WS(strm)->inflate_state.wsize = 0;
		WS(strm)->inflate_state.winकरोw = शून्य;
	पूर्ण
#पूर्ण_अगर

	जबतक (rc == Z_OK) अणु
		अगर (strm->avail_in == 0) अणु
			/* TODO: handle हाल where both pos and fill are set */
			len = fill(zbuf, GZIP_IOBUF_SIZE);
			अगर (len < 0) अणु
				rc = -1;
				error("read error");
				अवरोध;
			पूर्ण
			strm->next_in = zbuf;
			strm->avail_in = len;
		पूर्ण
		rc = zlib_inflate(strm, 0);

		/* Write any data generated */
		अगर (flush && strm->next_out > out_buf) अणु
			दीर्घ l = strm->next_out - out_buf;
			अगर (l != flush(out_buf, l)) अणु
				rc = -1;
				error("write error");
				अवरोध;
			पूर्ण
			strm->next_out = out_buf;
			strm->avail_out = out_len;
		पूर्ण

		/* after Z_FINISH, only Z_STREAM_END is "we unpacked it all" */
		अगर (rc == Z_STREAM_END) अणु
			rc = 0;
			अवरोध;
		पूर्ण अन्यथा अगर (rc != Z_OK) अणु
			error("uncompression error");
			rc = -1;
		पूर्ण
	पूर्ण

	zlib_inflateEnd(strm);
	अगर (pos)
		/* add + 8 to skip over trailer */
		*pos = strm->next_in - zbuf+8;

gunzip_5:
	मुक्त(strm->workspace);
gunzip_nomem4:
	मुक्त(strm);
gunzip_nomem3:
	अगर (!buf)
		मुक्त(zbuf);
gunzip_nomem2:
	अगर (flush)
		मुक्त(out_buf);
gunzip_nomem1:
	वापस rc; /* वापसs Z_OK (0) अगर successful */
पूर्ण

#अगर_अघोषित PREBOOT
STATIC पूर्णांक INIT gunzip(अचिन्हित अक्षर *buf, दीर्घ len,
		       दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
		       दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ),
		       अचिन्हित अक्षर *out_buf,
		       दीर्घ *pos,
		       व्योम (*error)(अक्षर *x))
अणु
	वापस __gunzip(buf, len, fill, flush, out_buf, 0, pos, error);
पूर्ण
#अन्यथा
STATIC पूर्णांक INIT __decompress(अचिन्हित अक्षर *buf, दीर्घ len,
			   दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
			   दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ),
			   अचिन्हित अक्षर *out_buf, दीर्घ out_len,
			   दीर्घ *pos,
			   व्योम (*error)(अक्षर *x))
अणु
	वापस __gunzip(buf, len, fill, flush, out_buf, out_len, pos, error);
पूर्ण
#पूर्ण_अगर
