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
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/jffs2.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश "compr.h"


#घोषणा RUBIN_REG_SIZE   16
#घोषणा UPPER_BIT_RUBIN    (((दीर्घ) 1)<<(RUBIN_REG_SIZE-1))
#घोषणा LOWER_BITS_RUBIN   ((((दीर्घ) 1)<<(RUBIN_REG_SIZE-1))-1)


#घोषणा BIT_DIVIDER_MIPS 1043
अटल पूर्णांक bits_mips[8] = अणु 277, 249, 290, 267, 229, 341, 212, 241पूर्ण;

काष्ठा pushpull अणु
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक buflen;
	अचिन्हित पूर्णांक ofs;
	अचिन्हित पूर्णांक reserve;
पूर्ण;

काष्ठा rubin_state अणु
	अचिन्हित दीर्घ p;
	अचिन्हित दीर्घ q;
	अचिन्हित दीर्घ rec_q;
	दीर्घ bit_number;
	काष्ठा pushpull pp;
	पूर्णांक bit_भागider;
	पूर्णांक bits[8];
पूर्ण;

अटल अंतरभूत व्योम init_pushpull(काष्ठा pushpull *pp, अक्षर *buf,
				 अचिन्हित buflen, अचिन्हित ofs,
				 अचिन्हित reserve)
अणु
	pp->buf = buf;
	pp->buflen = buflen;
	pp->ofs = ofs;
	pp->reserve = reserve;
पूर्ण

अटल अंतरभूत पूर्णांक pushbit(काष्ठा pushpull *pp, पूर्णांक bit, पूर्णांक use_reserved)
अणु
	अगर (pp->ofs >= pp->buflen - (use_reserved?0:pp->reserve))
		वापस -ENOSPC;

	अगर (bit)
		pp->buf[pp->ofs >> 3] |= (1<<(7-(pp->ofs & 7)));
	अन्यथा
		pp->buf[pp->ofs >> 3] &= ~(1<<(7-(pp->ofs & 7)));

	pp->ofs++;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pushedbits(काष्ठा pushpull *pp)
अणु
	वापस pp->ofs;
पूर्ण

अटल अंतरभूत पूर्णांक pullbit(काष्ठा pushpull *pp)
अणु
	पूर्णांक bit;

	bit = (pp->buf[pp->ofs >> 3] >> (7-(pp->ofs & 7))) & 1;

	pp->ofs++;
	वापस bit;
पूर्ण


अटल व्योम init_rubin(काष्ठा rubin_state *rs, पूर्णांक भाग, पूर्णांक *bits)
अणु
	पूर्णांक c;

	rs->q = 0;
	rs->p = (दीर्घ) (2 * UPPER_BIT_RUBIN);
	rs->bit_number = (दीर्घ) 0;
	rs->bit_भागider = भाग;

	क्रम (c=0; c<8; c++)
		rs->bits[c] = bits[c];
पूर्ण


अटल पूर्णांक encode(काष्ठा rubin_state *rs, दीर्घ A, दीर्घ B, पूर्णांक symbol)
अणु

	दीर्घ i0, i1;
	पूर्णांक ret;

	जबतक ((rs->q >= UPPER_BIT_RUBIN) ||
	       ((rs->p + rs->q) <= UPPER_BIT_RUBIN)) अणु
		rs->bit_number++;

		ret = pushbit(&rs->pp, (rs->q & UPPER_BIT_RUBIN) ? 1 : 0, 0);
		अगर (ret)
			वापस ret;
		rs->q &= LOWER_BITS_RUBIN;
		rs->q <<= 1;
		rs->p <<= 1;
	पूर्ण
	i0 = A * rs->p / (A + B);
	अगर (i0 <= 0)
		i0 = 1;

	अगर (i0 >= rs->p)
		i0 = rs->p - 1;

	i1 = rs->p - i0;

	अगर (symbol == 0)
		rs->p = i0;
	अन्यथा अणु
		rs->p = i1;
		rs->q += i0;
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम end_rubin(काष्ठा rubin_state *rs)
अणु

	पूर्णांक i;

	क्रम (i = 0; i < RUBIN_REG_SIZE; i++) अणु
		pushbit(&rs->pp, (UPPER_BIT_RUBIN & rs->q) ? 1 : 0, 1);
		rs->q &= LOWER_BITS_RUBIN;
		rs->q <<= 1;
	पूर्ण
पूर्ण


अटल व्योम init_decode(काष्ठा rubin_state *rs, पूर्णांक भाग, पूर्णांक *bits)
अणु
	init_rubin(rs, भाग, bits);

	/* behalve lower */
	rs->rec_q = 0;

	क्रम (rs->bit_number = 0; rs->bit_number++ < RUBIN_REG_SIZE;
	     rs->rec_q = rs->rec_q * 2 + (दीर्घ) (pullbit(&rs->pp)))
		;
पूर्ण

अटल व्योम __करो_decode(काष्ठा rubin_state *rs, अचिन्हित दीर्घ p,
			अचिन्हित दीर्घ q)
अणु
	रेजिस्टर अचिन्हित दीर्घ lower_bits_rubin = LOWER_BITS_RUBIN;
	अचिन्हित दीर्घ rec_q;
	पूर्णांक c, bits = 0;

	/*
	 * First, work out how many bits we need from the input stream.
	 * Note that we have alपढ़ोy करोne the initial check on this
	 * loop prior to calling this function.
	 */
	करो अणु
		bits++;
		q &= lower_bits_rubin;
		q <<= 1;
		p <<= 1;
	पूर्ण जबतक ((q >= UPPER_BIT_RUBIN) || ((p + q) <= UPPER_BIT_RUBIN));

	rs->p = p;
	rs->q = q;

	rs->bit_number += bits;

	/*
	 * Now get the bits.  We really want this to be "get n bits".
	 */
	rec_q = rs->rec_q;
	करो अणु
		c = pullbit(&rs->pp);
		rec_q &= lower_bits_rubin;
		rec_q <<= 1;
		rec_q += c;
	पूर्ण जबतक (--bits);
	rs->rec_q = rec_q;
पूर्ण

अटल पूर्णांक decode(काष्ठा rubin_state *rs, दीर्घ A, दीर्घ B)
अणु
	अचिन्हित दीर्घ p = rs->p, q = rs->q;
	दीर्घ i0, threshold;
	पूर्णांक symbol;

	अगर (q >= UPPER_BIT_RUBIN || ((p + q) <= UPPER_BIT_RUBIN))
		__करो_decode(rs, p, q);

	i0 = A * rs->p / (A + B);
	अगर (i0 <= 0)
		i0 = 1;

	अगर (i0 >= rs->p)
		i0 = rs->p - 1;

	threshold = rs->q + i0;
	symbol = rs->rec_q >= threshold;
	अगर (rs->rec_q >= threshold) अणु
		rs->q += i0;
		i0 = rs->p - i0;
	पूर्ण

	rs->p = i0;

	वापस symbol;
पूर्ण



अटल पूर्णांक out_byte(काष्ठा rubin_state *rs, अचिन्हित अक्षर byte)
अणु
	पूर्णांक i, ret;
	काष्ठा rubin_state rs_copy;
	rs_copy = *rs;

	क्रम (i=0; i<8; i++) अणु
		ret = encode(rs, rs->bit_भागider-rs->bits[i],
			     rs->bits[i], byte & 1);
		अगर (ret) अणु
			/* Failed. Restore old state */
			*rs = rs_copy;
			वापस ret;
		पूर्ण
		byte >>= 1 ;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक in_byte(काष्ठा rubin_state *rs)
अणु
	पूर्णांक i, result = 0, bit_भागider = rs->bit_भागider;

	क्रम (i = 0; i < 8; i++)
		result |= decode(rs, bit_भागider - rs->bits[i],
				 rs->bits[i]) << i;

	वापस result;
पूर्ण



अटल पूर्णांक rubin_करो_compress(पूर्णांक bit_भागider, पूर्णांक *bits, अचिन्हित अक्षर *data_in,
			     अचिन्हित अक्षर *cpage_out, uपूर्णांक32_t *sourcelen,
			     uपूर्णांक32_t *dstlen)
	अणु
	पूर्णांक outpos = 0;
	पूर्णांक pos=0;
	काष्ठा rubin_state rs;

	init_pushpull(&rs.pp, cpage_out, *dstlen * 8, 0, 32);

	init_rubin(&rs, bit_भागider, bits);

	जबतक (pos < (*sourcelen) && !out_byte(&rs, data_in[pos]))
		pos++;

	end_rubin(&rs);

	अगर (outpos > pos) अणु
		/* We failed */
		वापस -1;
	पूर्ण

	/* Tell the caller how much we managed to compress,
	 * and how much space it took */

	outpos = (pushedbits(&rs.pp)+7)/8;

	अगर (outpos >= pos)
		वापस -1; /* We didn't actually compress */
	*sourcelen = pos;
	*dstlen = outpos;
	वापस 0;
पूर्ण
#अगर 0
/* _compress वापसs the compressed size, -1 अगर bigger */
पूर्णांक jffs2_rubinmips_compress(अचिन्हित अक्षर *data_in, अचिन्हित अक्षर *cpage_out,
		   uपूर्णांक32_t *sourcelen, uपूर्णांक32_t *dstlen)
अणु
	वापस rubin_करो_compress(BIT_DIVIDER_MIPS, bits_mips, data_in,
				 cpage_out, sourcelen, dstlen);
पूर्ण
#पूर्ण_अगर
अटल पूर्णांक jffs2_dynrubin_compress(अचिन्हित अक्षर *data_in,
				   अचिन्हित अक्षर *cpage_out,
				   uपूर्णांक32_t *sourcelen, uपूर्णांक32_t *dstlen)
अणु
	पूर्णांक bits[8];
	अचिन्हित अक्षर histo[256];
	पूर्णांक i;
	पूर्णांक ret;
	uपूर्णांक32_t mysrclen, mydstlen;

	mysrclen = *sourcelen;
	mydstlen = *dstlen - 8;

	अगर (*dstlen <= 12)
		वापस -1;

	स_रखो(histo, 0, 256);
	क्रम (i=0; i<mysrclen; i++)
		histo[data_in[i]]++;
	स_रखो(bits, 0, माप(पूर्णांक)*8);
	क्रम (i=0; i<256; i++) अणु
		अगर (i&128)
			bits[7] += histo[i];
		अगर (i&64)
			bits[6] += histo[i];
		अगर (i&32)
			bits[5] += histo[i];
		अगर (i&16)
			bits[4] += histo[i];
		अगर (i&8)
			bits[3] += histo[i];
		अगर (i&4)
			bits[2] += histo[i];
		अगर (i&2)
			bits[1] += histo[i];
		अगर (i&1)
			bits[0] += histo[i];
	पूर्ण

	क्रम (i=0; i<8; i++) अणु
		bits[i] = (bits[i] * 256) / mysrclen;
		अगर (!bits[i]) bits[i] = 1;
		अगर (bits[i] > 255) bits[i] = 255;
		cpage_out[i] = bits[i];
	पूर्ण

	ret = rubin_करो_compress(256, bits, data_in, cpage_out+8, &mysrclen,
				&mydstlen);
	अगर (ret)
		वापस ret;

	/* Add back the 8 bytes we took क्रम the probabilities */
	mydstlen += 8;

	अगर (mysrclen <= mydstlen) अणु
		/* We compressed */
		वापस -1;
	पूर्ण

	*sourcelen = mysrclen;
	*dstlen = mydstlen;
	वापस 0;
पूर्ण

अटल व्योम rubin_करो_decompress(पूर्णांक bit_भागider, पूर्णांक *bits,
				अचिन्हित अक्षर *cdata_in, 
				अचिन्हित अक्षर *page_out, uपूर्णांक32_t srclen,
				uपूर्णांक32_t destlen)
अणु
	पूर्णांक outpos = 0;
	काष्ठा rubin_state rs;

	init_pushpull(&rs.pp, cdata_in, srclen, 0, 0);
	init_decode(&rs, bit_भागider, bits);

	जबतक (outpos < destlen)
		page_out[outpos++] = in_byte(&rs);
पूर्ण


अटल पूर्णांक jffs2_rubinmips_decompress(अचिन्हित अक्षर *data_in,
				      अचिन्हित अक्षर *cpage_out,
				      uपूर्णांक32_t sourcelen, uपूर्णांक32_t dstlen)
अणु
	rubin_करो_decompress(BIT_DIVIDER_MIPS, bits_mips, data_in,
			    cpage_out, sourcelen, dstlen);
	वापस 0;
पूर्ण

अटल पूर्णांक jffs2_dynrubin_decompress(अचिन्हित अक्षर *data_in,
				     अचिन्हित अक्षर *cpage_out,
				     uपूर्णांक32_t sourcelen, uपूर्णांक32_t dstlen)
अणु
	पूर्णांक bits[8];
	पूर्णांक c;

	क्रम (c=0; c<8; c++)
		bits[c] = data_in[c];

	rubin_करो_decompress(256, bits, data_in+8, cpage_out, sourcelen-8,
			    dstlen);
	वापस 0;
पूर्ण

अटल काष्ठा jffs2_compressor jffs2_rubinmips_comp = अणु
	.priority = JFFS2_RUBINMIPS_PRIORITY,
	.name = "rubinmips",
	.compr = JFFS2_COMPR_DYNRUBIN,
	.compress = शून्य, /*&jffs2_rubinmips_compress,*/
	.decompress = &jffs2_rubinmips_decompress,
#अगर_घोषित JFFS2_RUBINMIPS_DISABLED
	.disabled = 1,
#अन्यथा
	.disabled = 0,
#पूर्ण_अगर
पूर्ण;

पूर्णांक jffs2_rubinmips_init(व्योम)
अणु
	वापस jffs2_रेजिस्टर_compressor(&jffs2_rubinmips_comp);
पूर्ण

व्योम jffs2_rubinmips_निकास(व्योम)
अणु
	jffs2_unरेजिस्टर_compressor(&jffs2_rubinmips_comp);
पूर्ण

अटल काष्ठा jffs2_compressor jffs2_dynrubin_comp = अणु
	.priority = JFFS2_DYNRUBIN_PRIORITY,
	.name = "dynrubin",
	.compr = JFFS2_COMPR_RUBINMIPS,
	.compress = jffs2_dynrubin_compress,
	.decompress = &jffs2_dynrubin_decompress,
#अगर_घोषित JFFS2_DYNRUBIN_DISABLED
	.disabled = 1,
#अन्यथा
	.disabled = 0,
#पूर्ण_अगर
पूर्ण;

पूर्णांक jffs2_dynrubin_init(व्योम)
अणु
	वापस jffs2_रेजिस्टर_compressor(&jffs2_dynrubin_comp);
पूर्ण

व्योम jffs2_dynrubin_निकास(व्योम)
अणु
	jffs2_unरेजिस्टर_compressor(&jffs2_dynrubin_comp);
पूर्ण
