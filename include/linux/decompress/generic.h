<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DECOMPRESS_GENERIC_H
#घोषणा DECOMPRESS_GENERIC_H

प्रकार पूर्णांक (*decompress_fn) (अचिन्हित अक्षर *inbuf, दीर्घ len,
			      दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
			      दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ),
			      अचिन्हित अक्षर *outbuf,
			      दीर्घ *posp,
			      व्योम(*error)(अक्षर *x));

/* inbuf   - input buffer
 *len     - len of pre-पढ़ो data in inbuf
 *fill    - function to fill inbuf when empty
 *flush   - function to ग_लिखो out outbuf
 *outbuf  - output buffer
 *posp    - अगर non-null, input position (number of bytes पढ़ो) will be
 *	  वापसed here
 *
 *If len != 0, inbuf should contain all the necessary input data, and fill
 *should be शून्य
 *If len = 0, inbuf can be शून्य, in which हाल the decompressor will allocate
 *the input buffer.  If inbuf != शून्य it must be at least XXX_IOBUF_SIZE bytes.
 *fill will be called (repeatedly...) to पढ़ो data, at most XXX_IOBUF_SIZE
 *bytes should be पढ़ो per call.  Replace XXX with the appropriate decompressor
 *name, i.e. LZMA_IOBUF_SIZE.
 *
 *If flush = शून्य, outbuf must be large enough to buffer all the expected
 *output.  If flush != शून्य, the output buffer will be allocated by the
 *decompressor (outbuf = शून्य), and the flush function will be called to
 *flush the output buffer at the appropriate समय (decompressor and stream
 *dependent).
 */


/* Utility routine to detect the decompression method */
decompress_fn decompress_method(स्थिर अचिन्हित अक्षर *inbuf, दीर्घ len,
				स्थिर अक्षर **name);

#पूर्ण_अगर
