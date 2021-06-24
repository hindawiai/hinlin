<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <zlib.h>
#समावेश <linux/compiler.h>
#समावेश <पूर्णांकernal/lib.h>

#समावेश "util/compress.h"

#घोषणा CHUNK_SIZE  16384

पूर्णांक gzip_decompress_to_file(स्थिर अक्षर *input, पूर्णांक output_fd)
अणु
	पूर्णांक ret = Z_STREAM_ERROR;
	पूर्णांक input_fd;
	व्योम *ptr;
	पूर्णांक len;
	काष्ठा stat stbuf;
	अचिन्हित अक्षर buf[CHUNK_SIZE];
	z_stream zs = अणु
		.zalloc		= Z_शून्य,
		.zमुक्त		= Z_शून्य,
		.opaque		= Z_शून्य,
		.avail_in	= 0,
		.next_in	= Z_शून्य,
	पूर्ण;

	input_fd = खोलो(input, O_RDONLY);
	अगर (input_fd < 0)
		वापस -1;

	अगर (ख_स्थिति(input_fd, &stbuf) < 0)
		जाओ out_बंद;

	ptr = mmap(शून्य, stbuf.st_size, PROT_READ, MAP_PRIVATE, input_fd, 0);
	अगर (ptr == MAP_FAILED)
		जाओ out_बंद;

	अगर (inflateInit2(&zs, 16 + MAX_WBITS) != Z_OK)
		जाओ out_unmap;

	zs.next_in = ptr;
	zs.avail_in = stbuf.st_size;

	करो अणु
		zs.next_out = buf;
		zs.avail_out = CHUNK_SIZE;

		ret = inflate(&zs, Z_NO_FLUSH);
		चयन (ret) अणु
		हाल Z_NEED_DICT:
			ret = Z_DATA_ERROR;
			/* fall through */
		हाल Z_DATA_ERROR:
		हाल Z_MEM_ERROR:
			जाओ out;
		शेष:
			अवरोध;
		पूर्ण

		len = CHUNK_SIZE - zs.avail_out;
		अगर (ग_लिखोn(output_fd, buf, len) != len) अणु
			ret = Z_DATA_ERROR;
			जाओ out;
		पूर्ण

	पूर्ण जबतक (ret != Z_STREAM_END);

out:
	inflateEnd(&zs);
out_unmap:
	munmap(ptr, stbuf.st_size);
out_बंद:
	बंद(input_fd);

	वापस ret == Z_STREAM_END ? 0 : -1;
पूर्ण

bool gzip_is_compressed(स्थिर अक्षर *input)
अणु
	पूर्णांक fd = खोलो(input, O_RDONLY);
	स्थिर uपूर्णांक8_t magic[2] = अणु 0x1f, 0x8b पूर्ण;
	अक्षर buf[2] = अणु 0 पूर्ण;
	sमाप_प्रकार rc;

	अगर (fd < 0)
		वापस -1;

	rc = पढ़ो(fd, buf, माप(buf));
	बंद(fd);
	वापस rc == माप(buf) ?
	       स_भेद(buf, magic, माप(buf)) == 0 : false;
पूर्ण
