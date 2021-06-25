<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <lzma.h>
#समावेश <मानकपन.स>
#समावेश <linux/compiler.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश "compress.h"
#समावेश "debug.h"
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <पूर्णांकernal/lib.h>

#घोषणा बफ_मानE 8192

अटल स्थिर अक्षर *lzma_म_त्रुटि(lzma_ret ret)
अणु
	चयन ((पूर्णांक) ret) अणु
	हाल LZMA_MEM_ERROR:
		वापस "Memory allocation failed";
	हाल LZMA_OPTIONS_ERROR:
		वापस "Unsupported decompressor flags";
	हाल LZMA_FORMAT_ERROR:
		वापस "The input is not in the .xz format";
	हाल LZMA_DATA_ERROR:
		वापस "Compressed file is corrupt";
	हाल LZMA_BUF_ERROR:
		वापस "Compressed file is truncated or otherwise corrupt";
	शेष:
		वापस "Unknown error, possibly a bug";
	पूर्ण
पूर्ण

पूर्णांक lzma_decompress_to_file(स्थिर अक्षर *input, पूर्णांक output_fd)
अणु
	lzma_action action = LZMA_RUN;
	lzma_stream strm   = LZMA_STREAM_INIT;
	lzma_ret ret;
	पूर्णांक err = -1;

	u8 buf_in[बफ_मानE];
	u8 buf_out[बफ_मानE];
	खाता *infile;

	infile = ख_खोलो(input, "rb");
	अगर (!infile) अणु
		pr_err("lzma: fopen failed on %s: '%s'\n",
		       input, म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	ret = lzma_stream_decoder(&strm, UINT64_MAX, LZMA_CONCATENATED);
	अगर (ret != LZMA_OK) अणु
		pr_err("lzma: lzma_stream_decoder failed %s (%d)\n",
			lzma_म_त्रुटि(ret), ret);
		जाओ err_ख_बंद;
	पूर्ण

	strm.next_in   = शून्य;
	strm.avail_in  = 0;
	strm.next_out  = buf_out;
	strm.avail_out = माप(buf_out);

	जबतक (1) अणु
		अगर (strm.avail_in == 0 && !ख_पूर्ण(infile)) अणु
			strm.next_in  = buf_in;
			strm.avail_in = ख_पढ़ो(buf_in, 1, माप(buf_in), infile);

			अगर (ख_त्रुटि(infile)) अणु
				pr_err("lzma: read error: %s\n", म_त्रुटि(त्रुटि_सं));
				जाओ err_ख_बंद;
			पूर्ण

			अगर (ख_पूर्ण(infile))
				action = LZMA_FINISH;
		पूर्ण

		ret = lzma_code(&strm, action);

		अगर (strm.avail_out == 0 || ret == LZMA_STREAM_END) अणु
			sमाप_प्रकार ग_लिखो_size = माप(buf_out) - strm.avail_out;

			अगर (ग_लिखोn(output_fd, buf_out, ग_लिखो_size) != ग_लिखो_size) अणु
				pr_err("lzma: write error: %s\n", म_त्रुटि(त्रुटि_सं));
				जाओ err_ख_बंद;
			पूर्ण

			strm.next_out  = buf_out;
			strm.avail_out = माप(buf_out);
		पूर्ण

		अगर (ret != LZMA_OK) अणु
			अगर (ret == LZMA_STREAM_END)
				अवरोध;

			pr_err("lzma: failed %s\n", lzma_म_त्रुटि(ret));
			जाओ err_ख_बंद;
		पूर्ण
	पूर्ण

	err = 0;
err_ख_बंद:
	ख_बंद(infile);
	वापस err;
पूर्ण

bool lzma_is_compressed(स्थिर अक्षर *input)
अणु
	पूर्णांक fd = खोलो(input, O_RDONLY);
	स्थिर uपूर्णांक8_t magic[6] = अणु 0xFD, '7', 'z', 'X', 'Z', 0x00 पूर्ण;
	अक्षर buf[6] = अणु 0 पूर्ण;
	sमाप_प्रकार rc;

	अगर (fd < 0)
		वापस -1;

	rc = पढ़ो(fd, buf, माप(buf));
	बंद(fd);
	वापस rc == माप(buf) ?
	       स_भेद(buf, magic, माप(buf)) == 0 : false;
पूर्ण
