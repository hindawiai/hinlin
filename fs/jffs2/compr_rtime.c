<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Created by Arjan van de Ven <arjanv@redhat.com>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 *
 *
 * Very simple lz77-ish encoder.
 *
 * Theory of operation: Both encoder and decoder have a list of "last
 * occurrences" क्रम every possible source-value; after sending the
 * first source-byte, the second byte indicated the "run" length of
 * matches
 *
 * The algorithm is पूर्णांकended to only send "whole bytes", no bit-messing.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/jffs2.h>
#समावेश "compr.h"

/* _compress वापसs the compressed size, -1 अगर bigger */
अटल पूर्णांक jffs2_rसमय_compress(अचिन्हित अक्षर *data_in,
				अचिन्हित अक्षर *cpage_out,
				uपूर्णांक32_t *sourcelen, uपूर्णांक32_t *dstlen)
अणु
	अचिन्हित लघु positions[256];
	पूर्णांक outpos = 0;
	पूर्णांक pos=0;

	अगर (*dstlen <= 3)
		वापस -1;

	स_रखो(positions,0,माप(positions));

	जबतक (pos < (*sourcelen) && outpos <= (*dstlen)-2) अणु
		पूर्णांक backpos, runlen=0;
		अचिन्हित अक्षर value;

		value = data_in[pos];

		cpage_out[outpos++] = data_in[pos++];

		backpos = positions[value];
		positions[value]=pos;

		जबतक ((backpos < pos) && (pos < (*sourcelen)) &&
		       (data_in[pos]==data_in[backpos++]) && (runlen<255)) अणु
			pos++;
			runlen++;
		पूर्ण
		cpage_out[outpos++] = runlen;
	पूर्ण

	अगर (outpos >= pos) अणु
		/* We failed */
		वापस -1;
	पूर्ण

	/* Tell the caller how much we managed to compress, and how much space it took */
	*sourcelen = pos;
	*dstlen = outpos;
	वापस 0;
पूर्ण


अटल पूर्णांक jffs2_rसमय_decompress(अचिन्हित अक्षर *data_in,
				  अचिन्हित अक्षर *cpage_out,
				  uपूर्णांक32_t srclen, uपूर्णांक32_t destlen)
अणु
	अचिन्हित लघु positions[256];
	पूर्णांक outpos = 0;
	पूर्णांक pos=0;

	स_रखो(positions,0,माप(positions));

	जबतक (outpos<destlen) अणु
		अचिन्हित अक्षर value;
		पूर्णांक backoffs;
		पूर्णांक repeat;

		value = data_in[pos++];
		cpage_out[outpos++] = value; /* first the verbatim copied byte */
		repeat = data_in[pos++];
		backoffs = positions[value];

		positions[value]=outpos;
		अगर (repeat) अणु
			अगर (backoffs + repeat >= outpos) अणु
				जबतक(repeat) अणु
					cpage_out[outpos++] = cpage_out[backoffs++];
					repeat--;
				पूर्ण
			पूर्ण अन्यथा अणु
				स_नकल(&cpage_out[outpos],&cpage_out[backoffs],repeat);
				outpos+=repeat;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा jffs2_compressor jffs2_rसमय_comp = अणु
    .priority = JFFS2_RTIME_PRIORITY,
    .name = "rtime",
    .compr = JFFS2_COMPR_RTIME,
    .compress = &jffs2_rसमय_compress,
    .decompress = &jffs2_rसमय_decompress,
#अगर_घोषित JFFS2_RTIME_DISABLED
    .disabled = 1,
#अन्यथा
    .disabled = 0,
#पूर्ण_अगर
पूर्ण;

पूर्णांक jffs2_rसमय_init(व्योम)
अणु
    वापस jffs2_रेजिस्टर_compressor(&jffs2_rसमय_comp);
पूर्ण

व्योम jffs2_rसमय_निकास(व्योम)
अणु
    jffs2_unरेजिस्टर_compressor(&jffs2_rसमय_comp);
पूर्ण
