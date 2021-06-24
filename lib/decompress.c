<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * decompress.c
 *
 * Detect the decompression method based on magic number
 */

#समावेश <linux/decompress/generic.h>

#समावेश <linux/decompress/bunzip2.h>
#समावेश <linux/decompress/unlzma.h>
#समावेश <linux/decompress/unxz.h>
#समावेश <linux/decompress/inflate.h>
#समावेश <linux/decompress/unlzo.h>
#समावेश <linux/decompress/unlz4.h>
#समावेश <linux/decompress/unzstd.h>

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/prपूर्णांकk.h>

#अगर_अघोषित CONFIG_DECOMPRESS_GZIP
# define gunzip शून्य
#पूर्ण_अगर
#अगर_अघोषित CONFIG_DECOMPRESS_BZIP2
# define bunzip2 शून्य
#पूर्ण_अगर
#अगर_अघोषित CONFIG_DECOMPRESS_LZMA
# define unlzma शून्य
#पूर्ण_अगर
#अगर_अघोषित CONFIG_DECOMPRESS_XZ
# define unxz शून्य
#पूर्ण_अगर
#अगर_अघोषित CONFIG_DECOMPRESS_LZO
# define unlzo शून्य
#पूर्ण_अगर
#अगर_अघोषित CONFIG_DECOMPRESS_LZ4
# define unlz4 शून्य
#पूर्ण_अगर
#अगर_अघोषित CONFIG_DECOMPRESS_ZSTD
# define unzstd शून्य
#पूर्ण_अगर

काष्ठा compress_क्रमmat अणु
	अचिन्हित अक्षर magic[2];
	स्थिर अक्षर *name;
	decompress_fn decompressor;
पूर्ण;

अटल स्थिर काष्ठा compress_क्रमmat compressed_क्रमmats[] __initस्थिर = अणु
	अणु अणु0x1f, 0x8bपूर्ण, "gzip", gunzip पूर्ण,
	अणु अणु0x1f, 0x9eपूर्ण, "gzip", gunzip पूर्ण,
	अणु अणु0x42, 0x5aपूर्ण, "bzip2", bunzip2 पूर्ण,
	अणु अणु0x5d, 0x00पूर्ण, "lzma", unlzma पूर्ण,
	अणु अणु0xfd, 0x37पूर्ण, "xz", unxz पूर्ण,
	अणु अणु0x89, 0x4cपूर्ण, "lzo", unlzo पूर्ण,
	अणु अणु0x02, 0x21पूर्ण, "lz4", unlz4 पूर्ण,
	अणु अणु0x28, 0xb5पूर्ण, "zstd", unzstd पूर्ण,
	अणु अणु0, 0पूर्ण, शून्य, शून्य पूर्ण
पूर्ण;

decompress_fn __init decompress_method(स्थिर अचिन्हित अक्षर *inbuf, दीर्घ len,
				स्थिर अक्षर **name)
अणु
	स्थिर काष्ठा compress_क्रमmat *cf;

	अगर (len < 2) अणु
		अगर (name)
			*name = शून्य;
		वापस शून्य;	/* Need at least this much... */
	पूर्ण

	pr_debug("Compressed data magic: %#.2x %#.2x\n", inbuf[0], inbuf[1]);

	क्रम (cf = compressed_क्रमmats; cf->name; cf++) अणु
		अगर (!स_भेद(inbuf, cf->magic, 2))
			अवरोध;

	पूर्ण
	अगर (name)
		*name = cf->name;
	वापस cf->decompressor;
पूर्ण
