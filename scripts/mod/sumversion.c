<शैली गुरु>
#समावेश <netinet/in.h>
#अगर_घोषित __sun__
#समावेश <पूर्णांकtypes.h>
#अन्यथा
#समावेश <मानक_निवेशt.h>
#पूर्ण_अगर
#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <सीमा.स>
#समावेश "modpost.h"

/*
 * Stolen क्रमm Cryptographic API.
 *
 * MD4 Message Digest Algorithm (RFC1320).
 *
 * Implementation derived from Andrew Tridgell and Steve French's
 * CIFS MD4 implementation, and the cryptoapi implementation
 * originally based on the खुला करोमुख्य implementation written
 * by Colin Plumb in 1993.
 *
 * Copyright (c) Andrew Tridgell 1997-1998.
 * Modअगरied by Steve French (sfrench@us.ibm.com) 2002
 * Copyright (c) Cryptoapi developers.
 * Copyright (c) 2002 David S. Miller (davem@redhat.com)
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */
#घोषणा MD4_DIGEST_SIZE		16
#घोषणा MD4_HMAC_BLOCK_SIZE	64
#घोषणा MD4_BLOCK_WORDS		16
#घोषणा MD4_HASH_WORDS		4

काष्ठा md4_ctx अणु
	uपूर्णांक32_t hash[MD4_HASH_WORDS];
	uपूर्णांक32_t block[MD4_BLOCK_WORDS];
	uपूर्णांक64_t byte_count;
पूर्ण;

अटल अंतरभूत uपूर्णांक32_t lshअगरt(uपूर्णांक32_t x, अचिन्हित पूर्णांक s)
अणु
	x &= 0xFFFFFFFF;
	वापस ((x << s) & 0xFFFFFFFF) | (x >> (32 - s));
पूर्ण

अटल अंतरभूत uपूर्णांक32_t F(uपूर्णांक32_t x, uपूर्णांक32_t y, uपूर्णांक32_t z)
अणु
	वापस (x & y) | ((~x) & z);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t G(uपूर्णांक32_t x, uपूर्णांक32_t y, uपूर्णांक32_t z)
अणु
	वापस (x & y) | (x & z) | (y & z);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t H(uपूर्णांक32_t x, uपूर्णांक32_t y, uपूर्णांक32_t z)
अणु
	वापस x ^ y ^ z;
पूर्ण

#घोषणा ROUND1(a,b,c,d,k,s) (a = lshअगरt(a + F(b,c,d) + k, s))
#घोषणा ROUND2(a,b,c,d,k,s) (a = lshअगरt(a + G(b,c,d) + k + (uपूर्णांक32_t)0x5A827999,s))
#घोषणा ROUND3(a,b,c,d,k,s) (a = lshअगरt(a + H(b,c,d) + k + (uपूर्णांक32_t)0x6ED9EBA1,s))

/* XXX: this stuff can be optimized */
अटल अंतरभूत व्योम le32_to_cpu_array(uपूर्णांक32_t *buf, अचिन्हित पूर्णांक words)
अणु
	जबतक (words--) अणु
		*buf = ntohl(*buf);
		buf++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_to_le32_array(uपूर्णांक32_t *buf, अचिन्हित पूर्णांक words)
अणु
	जबतक (words--) अणु
		*buf = htonl(*buf);
		buf++;
	पूर्ण
पूर्ण

अटल व्योम md4_transक्रमm(uपूर्णांक32_t *hash, uपूर्णांक32_t स्थिर *in)
अणु
	uपूर्णांक32_t a, b, c, d;

	a = hash[0];
	b = hash[1];
	c = hash[2];
	d = hash[3];

	ROUND1(a, b, c, d, in[0], 3);
	ROUND1(d, a, b, c, in[1], 7);
	ROUND1(c, d, a, b, in[2], 11);
	ROUND1(b, c, d, a, in[3], 19);
	ROUND1(a, b, c, d, in[4], 3);
	ROUND1(d, a, b, c, in[5], 7);
	ROUND1(c, d, a, b, in[6], 11);
	ROUND1(b, c, d, a, in[7], 19);
	ROUND1(a, b, c, d, in[8], 3);
	ROUND1(d, a, b, c, in[9], 7);
	ROUND1(c, d, a, b, in[10], 11);
	ROUND1(b, c, d, a, in[11], 19);
	ROUND1(a, b, c, d, in[12], 3);
	ROUND1(d, a, b, c, in[13], 7);
	ROUND1(c, d, a, b, in[14], 11);
	ROUND1(b, c, d, a, in[15], 19);

	ROUND2(a, b, c, d,in[ 0], 3);
	ROUND2(d, a, b, c, in[4], 5);
	ROUND2(c, d, a, b, in[8], 9);
	ROUND2(b, c, d, a, in[12], 13);
	ROUND2(a, b, c, d, in[1], 3);
	ROUND2(d, a, b, c, in[5], 5);
	ROUND2(c, d, a, b, in[9], 9);
	ROUND2(b, c, d, a, in[13], 13);
	ROUND2(a, b, c, d, in[2], 3);
	ROUND2(d, a, b, c, in[6], 5);
	ROUND2(c, d, a, b, in[10], 9);
	ROUND2(b, c, d, a, in[14], 13);
	ROUND2(a, b, c, d, in[3], 3);
	ROUND2(d, a, b, c, in[7], 5);
	ROUND2(c, d, a, b, in[11], 9);
	ROUND2(b, c, d, a, in[15], 13);

	ROUND3(a, b, c, d,in[ 0], 3);
	ROUND3(d, a, b, c, in[8], 9);
	ROUND3(c, d, a, b, in[4], 11);
	ROUND3(b, c, d, a, in[12], 15);
	ROUND3(a, b, c, d, in[2], 3);
	ROUND3(d, a, b, c, in[10], 9);
	ROUND3(c, d, a, b, in[6], 11);
	ROUND3(b, c, d, a, in[14], 15);
	ROUND3(a, b, c, d, in[1], 3);
	ROUND3(d, a, b, c, in[9], 9);
	ROUND3(c, d, a, b, in[5], 11);
	ROUND3(b, c, d, a, in[13], 15);
	ROUND3(a, b, c, d, in[3], 3);
	ROUND3(d, a, b, c, in[11], 9);
	ROUND3(c, d, a, b, in[7], 11);
	ROUND3(b, c, d, a, in[15], 15);

	hash[0] += a;
	hash[1] += b;
	hash[2] += c;
	hash[3] += d;
पूर्ण

अटल अंतरभूत व्योम md4_transक्रमm_helper(काष्ठा md4_ctx *ctx)
अणु
	le32_to_cpu_array(ctx->block, माप(ctx->block) / माप(uपूर्णांक32_t));
	md4_transक्रमm(ctx->hash, ctx->block);
पूर्ण

अटल व्योम md4_init(काष्ठा md4_ctx *mctx)
अणु
	mctx->hash[0] = 0x67452301;
	mctx->hash[1] = 0xefcdab89;
	mctx->hash[2] = 0x98badcfe;
	mctx->hash[3] = 0x10325476;
	mctx->byte_count = 0;
पूर्ण

अटल व्योम md4_update(काष्ठा md4_ctx *mctx,
		       स्थिर अचिन्हित अक्षर *data, अचिन्हित पूर्णांक len)
अणु
	स्थिर uपूर्णांक32_t avail = माप(mctx->block) - (mctx->byte_count & 0x3f);

	mctx->byte_count += len;

	अगर (avail > len) अणु
		स_नकल((अक्षर *)mctx->block + (माप(mctx->block) - avail),
		       data, len);
		वापस;
	पूर्ण

	स_नकल((अक्षर *)mctx->block + (माप(mctx->block) - avail),
	       data, avail);

	md4_transक्रमm_helper(mctx);
	data += avail;
	len -= avail;

	जबतक (len >= माप(mctx->block)) अणु
		स_नकल(mctx->block, data, माप(mctx->block));
		md4_transक्रमm_helper(mctx);
		data += माप(mctx->block);
		len -= माप(mctx->block);
	पूर्ण

	स_नकल(mctx->block, data, len);
पूर्ण

अटल व्योम md4_final_ascii(काष्ठा md4_ctx *mctx, अक्षर *out, अचिन्हित पूर्णांक len)
अणु
	स्थिर अचिन्हित पूर्णांक offset = mctx->byte_count & 0x3f;
	अक्षर *p = (अक्षर *)mctx->block + offset;
	पूर्णांक padding = 56 - (offset + 1);

	*p++ = 0x80;
	अगर (padding < 0) अणु
		स_रखो(p, 0x00, padding + माप (uपूर्णांक64_t));
		md4_transक्रमm_helper(mctx);
		p = (अक्षर *)mctx->block;
		padding = 56;
	पूर्ण

	स_रखो(p, 0, padding);
	mctx->block[14] = mctx->byte_count << 3;
	mctx->block[15] = mctx->byte_count >> 29;
	le32_to_cpu_array(mctx->block, (माप(mctx->block) -
			  माप(uपूर्णांक64_t)) / माप(uपूर्णांक32_t));
	md4_transक्रमm(mctx->hash, mctx->block);
	cpu_to_le32_array(mctx->hash, माप(mctx->hash) / माप(uपूर्णांक32_t));

	snम_लिखो(out, len, "%08X%08X%08X%08X",
		 mctx->hash[0], mctx->hash[1], mctx->hash[2], mctx->hash[3]);
पूर्ण

अटल अंतरभूत व्योम add_अक्षर(अचिन्हित अक्षर c, काष्ठा md4_ctx *md)
अणु
	md4_update(md, &c, 1);
पूर्ण

अटल पूर्णांक parse_string(स्थिर अक्षर *file, अचिन्हित दीर्घ len,
			काष्ठा md4_ctx *md)
अणु
	अचिन्हित दीर्घ i;

	add_अक्षर(file[0], md);
	क्रम (i = 1; i < len; i++) अणु
		add_अक्षर(file[i], md);
		अगर (file[i] == '"' && file[i-1] != '\\')
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

अटल पूर्णांक parse_comment(स्थिर अक्षर *file, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 2; i < len; i++) अणु
		अगर (file[i-1] == '*' && file[i] == '/')
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

/* FIXME: Handle .s files dअगरferently (eg. # starts comments) --RR */
अटल पूर्णांक parse_file(स्थिर अक्षर *fname, काष्ठा md4_ctx *md)
अणु
	अक्षर *file;
	अचिन्हित दीर्घ i, len;

	file = पढ़ो_text_file(fname);
	len = म_माप(file);

	क्रम (i = 0; i < len; i++) अणु
		/* Collapse and ignore \ and CR. */
		अगर (file[i] == '\\' && (i+1 < len) && file[i+1] == '\n') अणु
			i++;
			जारी;
		पूर्ण

		/* Ignore whitespace */
		अगर (है_खाली(file[i]))
			जारी;

		/* Handle strings as whole units */
		अगर (file[i] == '"') अणु
			i += parse_string(file+i, len - i, md);
			जारी;
		पूर्ण

		/* Comments: ignore */
		अगर (file[i] == '/' && file[i+1] == '*') अणु
			i += parse_comment(file+i, len - i);
			जारी;
		पूर्ण

		add_अक्षर(file[i], md);
	पूर्ण
	मुक्त(file);
	वापस 1;
पूर्ण
/* Check whether the file is a अटल library or not */
अटल पूर्णांक is_अटल_library(स्थिर अक्षर *objfile)
अणु
	पूर्णांक len = म_माप(objfile);
	अगर (objfile[len - 2] == '.' && objfile[len - 1] == 'a')
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/* We have dir/file.o.  Open dir/.file.o.cmd, look क्रम source_ and deps_ line
 * to figure out source files. */
अटल पूर्णांक parse_source_files(स्थिर अक्षर *objfile, काष्ठा md4_ctx *md)
अणु
	अक्षर *cmd, *file, *line, *dir, *pos;
	स्थिर अक्षर *base;
	पूर्णांक dirlen, ret = 0, check_files = 0;

	cmd = NOFAIL(दो_स्मृति(म_माप(objfile) + माप("..cmd")));

	base = म_खोजप(objfile, '/');
	अगर (base) अणु
		base++;
		dirlen = base - objfile;
		प्र_लिखो(cmd, "%.*s.%s.cmd", dirlen, objfile, base);
	पूर्ण अन्यथा अणु
		dirlen = 0;
		प्र_लिखो(cmd, ".%s.cmd", objfile);
	पूर्ण
	dir = NOFAIL(दो_स्मृति(dirlen + 1));
	म_नकलन(dir, objfile, dirlen);
	dir[dirlen] = '\0';

	file = पढ़ो_text_file(cmd);

	pos = file;

	/* Sum all files in the same dir or subdirs. */
	जबतक ((line = get_line(&pos))) अणु
		अक्षर* p = line;

		अगर (म_भेदन(line, "source_", माप("source_")-1) == 0) अणु
			p = म_खोजप(line, ' ');
			अगर (!p) अणु
				warn("malformed line: %s\n", line);
				जाओ out_file;
			पूर्ण
			p++;
			अगर (!parse_file(p, md)) अणु
				warn("could not open %s: %s\n",
				     p, म_त्रुटि(त्रुटि_सं));
				जाओ out_file;
			पूर्ण
			जारी;
		पूर्ण
		अगर (म_भेदन(line, "deps_", माप("deps_")-1) == 0) अणु
			check_files = 1;
			जारी;
		पूर्ण
		अगर (!check_files)
			जारी;

		/* Continue until line करोes not end with '\' */
		अगर ( *(p + म_माप(p)-1) != '\\')
			अवरोध;
		/* Terminate line at first space, to get rid of final ' \' */
		जबतक (*p) अणु
			अगर (है_खाली(*p)) अणु
				*p = '\0';
				अवरोध;
			पूर्ण
			p++;
		पूर्ण

		/* Check अगर this file is in same dir as objfile */
		अगर ((म_माला(line, dir)+म_माप(dir)-1) == म_खोजप(line, '/')) अणु
			अगर (!parse_file(line, md)) अणु
				warn("could not open %s: %s\n",
				     line, म_त्रुटि(त्रुटि_सं));
				जाओ out_file;
			पूर्ण

		पूर्ण

	पूर्ण

	/* Everyone parsed OK */
	ret = 1;
out_file:
	मुक्त(file);
	मुक्त(dir);
	मुक्त(cmd);
	वापस ret;
पूर्ण

/* Calc and record src checksum. */
व्योम get_src_version(स्थिर अक्षर *modname, अक्षर sum[], अचिन्हित sumlen)
अणु
	अक्षर *buf, *pos, *firstline;
	काष्ठा md4_ctx md;
	अक्षर *fname;
	अक्षर filelist[PATH_MAX + 1];
	पूर्णांक postfix_len = 1;

	अगर (strends(modname, ".lto.o"))
		postfix_len = 5;

	/* objects क्रम a module are listed in the first line of *.mod file. */
	snम_लिखो(filelist, माप(filelist), "%.*smod",
		 (पूर्णांक)म_माप(modname) - postfix_len, modname);

	buf = पढ़ो_text_file(filelist);

	pos = buf;
	firstline = get_line(&pos);
	अगर (!firstline) अणु
		warn("bad ending versions file for %s\n", modname);
		जाओ मुक्त;
	पूर्ण

	md4_init(&md);
	जबतक ((fname = strsep(&firstline, " "))) अणु
		अगर (!*fname)
			जारी;
		अगर (!(is_अटल_library(fname)) &&
				!parse_source_files(fname, &md))
			जाओ मुक्त;
	पूर्ण

	md4_final_ascii(&md, sum, sumlen);
मुक्त:
	मुक्त(buf);
पूर्ण
