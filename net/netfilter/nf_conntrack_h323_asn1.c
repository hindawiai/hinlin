<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * BER and PER decoding library क्रम H.323 conntrack/NAT module.
 *
 * Copyright (c) 2006 by Jing Min Zhao <zhaojingmin@users.sourceक्रमge.net>
 *
 * See nf_conntrack_helper_h323_asn1.h क्रम details.
 */

#अगर_घोषित __KERNEL__
#समावेश <linux/kernel.h>
#अन्यथा
#समावेश <मानकपन.स>
#पूर्ण_अगर
#समावेश <linux/netfilter/nf_conntrack_h323_asn1.h>

/* Trace Flag */
#अगर_अघोषित H323_TRACE
#घोषणा H323_TRACE 0
#पूर्ण_अगर

#अगर H323_TRACE
#घोषणा TAB_SIZE 4
#घोषणा IFTHEN(cond, act) अगर(cond)अणुact;पूर्ण
#अगर_घोषित __KERNEL__
#घोषणा PRINT prपूर्णांकk
#अन्यथा
#घोषणा PRINT म_लिखो
#पूर्ण_अगर
#घोषणा FNAME(name) name,
#अन्यथा
#घोषणा IFTHEN(cond, act)
#घोषणा PRINT(fmt, args...)
#घोषणा FNAME(name)
#पूर्ण_अगर

/* ASN.1 Types */
#घोषणा NUL 0
#घोषणा BOOL 1
#घोषणा OID 2
#घोषणा INT 3
#घोषणा ENUM 4
#घोषणा BITSTR 5
#घोषणा NUMSTR 6
#घोषणा NUMDGT 6
#घोषणा TBCDSTR 6
#घोषणा OCTSTR 7
#घोषणा PRTSTR 7
#घोषणा IA5STR 7
#घोषणा GENSTR 7
#घोषणा BMPSTR 8
#घोषणा SEQ 9
#घोषणा SET 9
#घोषणा SEQOF 10
#घोषणा SETOF 10
#घोषणा CHOICE 11

/* Constraपूर्णांक Types */
#घोषणा FIXD 0
/* #घोषणा BITS 1-8 */
#घोषणा BYTE 9
#घोषणा WORD 10
#घोषणा CONS 11
#घोषणा SEMI 12
#घोषणा UNCO 13

/* ASN.1 Type Attributes */
#घोषणा SKIP 0
#घोषणा STOP 1
#घोषणा DECODE 2
#घोषणा EXT 4
#घोषणा OPEN 8
#घोषणा OPT 16


/* ASN.1 Field Structure */
प्रकार काष्ठा field_t अणु
#अगर H323_TRACE
	अक्षर *name;
#पूर्ण_अगर
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर sz;
	अचिन्हित अक्षर lb;
	अचिन्हित अक्षर ub;
	अचिन्हित लघु attr;
	अचिन्हित लघु offset;
	स्थिर काष्ठा field_t *fields;
पूर्ण field_t;

/* Bit Stream */
काष्ठा bitstr अणु
	अचिन्हित अक्षर *buf;
	अचिन्हित अक्षर *beg;
	अचिन्हित अक्षर *end;
	अचिन्हित अक्षर *cur;
	अचिन्हित पूर्णांक bit;
पूर्ण;

/* Tool Functions */
#घोषणा INC_BIT(bs) अगर((++(bs)->bit)>7)अणु(bs)->cur++;(bs)->bit=0;पूर्ण
#घोषणा INC_BITS(bs,b) अगर(((bs)->bit+=(b))>7)अणु(bs)->cur+=(bs)->bit>>3;(bs)->bit&=7;पूर्ण
#घोषणा BYTE_ALIGN(bs) अगर((bs)->bit)अणु(bs)->cur++;(bs)->bit=0;पूर्ण
अटल अचिन्हित पूर्णांक get_len(काष्ठा bitstr *bs);
अटल अचिन्हित पूर्णांक get_bit(काष्ठा bitstr *bs);
अटल अचिन्हित पूर्णांक get_bits(काष्ठा bitstr *bs, अचिन्हित पूर्णांक b);
अटल अचिन्हित पूर्णांक get_biपंचांगap(काष्ठा bitstr *bs, अचिन्हित पूर्णांक b);
अटल अचिन्हित पूर्णांक get_uपूर्णांक(काष्ठा bitstr *bs, पूर्णांक b);

/* Decoder Functions */
अटल पूर्णांक decode_nul(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f, अक्षर *base, पूर्णांक level);
अटल पूर्णांक decode_bool(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f, अक्षर *base, पूर्णांक level);
अटल पूर्णांक decode_oid(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f, अक्षर *base, पूर्णांक level);
अटल पूर्णांक decode_पूर्णांक(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f, अक्षर *base, पूर्णांक level);
अटल पूर्णांक decode_क्रमागत(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f, अक्षर *base, पूर्णांक level);
अटल पूर्णांक decode_bitstr(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f, अक्षर *base, पूर्णांक level);
अटल पूर्णांक decode_numstr(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f, अक्षर *base, पूर्णांक level);
अटल पूर्णांक decode_octstr(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f, अक्षर *base, पूर्णांक level);
अटल पूर्णांक decode_bmpstr(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f, अक्षर *base, पूर्णांक level);
अटल पूर्णांक decode_seq(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f, अक्षर *base, पूर्णांक level);
अटल पूर्णांक decode_seqof(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f, अक्षर *base, पूर्णांक level);
अटल पूर्णांक decode_choice(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f, अक्षर *base, पूर्णांक level);

/* Decoder Functions Vector */
प्रकार पूर्णांक (*decoder_t)(काष्ठा bitstr *, स्थिर काष्ठा field_t *, अक्षर *, पूर्णांक);
अटल स्थिर decoder_t Decoders[] = अणु
	decode_nul,
	decode_bool,
	decode_oid,
	decode_पूर्णांक,
	decode_क्रमागत,
	decode_bitstr,
	decode_numstr,
	decode_octstr,
	decode_bmpstr,
	decode_seq,
	decode_seqof,
	decode_choice,
पूर्ण;

/*
 * H.323 Types
 */
#समावेश "nf_conntrack_h323_types.c"

/*
 * Functions
 */

/* Assume bs is aligned && v < 16384 */
अटल अचिन्हित पूर्णांक get_len(काष्ठा bitstr *bs)
अणु
	अचिन्हित पूर्णांक v;

	v = *bs->cur++;

	अगर (v & 0x80) अणु
		v &= 0x3f;
		v <<= 8;
		v += *bs->cur++;
	पूर्ण

	वापस v;
पूर्ण

अटल पूर्णांक nf_h323_error_boundary(काष्ठा bitstr *bs, माप_प्रकार bytes, माप_प्रकार bits)
अणु
	bits += bs->bit;
	bytes += bits / BITS_PER_BYTE;
	अगर (bits % BITS_PER_BYTE > 0)
		bytes++;

	अगर (bs->cur + bytes > bs->end)
		वापस 1;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक get_bit(काष्ठा bitstr *bs)
अणु
	अचिन्हित पूर्णांक b = (*bs->cur) & (0x80 >> bs->bit);

	INC_BIT(bs);

	वापस b;
पूर्ण

/* Assume b <= 8 */
अटल अचिन्हित पूर्णांक get_bits(काष्ठा bitstr *bs, अचिन्हित पूर्णांक b)
अणु
	अचिन्हित पूर्णांक v, l;

	v = (*bs->cur) & (0xffU >> bs->bit);
	l = b + bs->bit;

	अगर (l < 8) अणु
		v >>= 8 - l;
		bs->bit = l;
	पूर्ण अन्यथा अगर (l == 8) अणु
		bs->cur++;
		bs->bit = 0;
	पूर्ण अन्यथा अणु		/* l > 8 */

		v <<= 8;
		v += *(++bs->cur);
		v >>= 16 - l;
		bs->bit = l - 8;
	पूर्ण

	वापस v;
पूर्ण

/* Assume b <= 32 */
अटल अचिन्हित पूर्णांक get_biपंचांगap(काष्ठा bitstr *bs, अचिन्हित पूर्णांक b)
अणु
	अचिन्हित पूर्णांक v, l, shअगरt, bytes;

	अगर (!b)
		वापस 0;

	l = bs->bit + b;

	अगर (l < 8) अणु
		v = (अचिन्हित पूर्णांक)(*bs->cur) << (bs->bit + 24);
		bs->bit = l;
	पूर्ण अन्यथा अगर (l == 8) अणु
		v = (अचिन्हित पूर्णांक)(*bs->cur++) << (bs->bit + 24);
		bs->bit = 0;
	पूर्ण अन्यथा अणु
		क्रम (bytes = l >> 3, shअगरt = 24, v = 0; bytes;
		     bytes--, shअगरt -= 8)
			v |= (अचिन्हित पूर्णांक)(*bs->cur++) << shअगरt;

		अगर (l < 32) अणु
			v |= (अचिन्हित पूर्णांक)(*bs->cur) << shअगरt;
			v <<= bs->bit;
		पूर्ण अन्यथा अगर (l > 32) अणु
			v <<= bs->bit;
			v |= (*bs->cur) >> (8 - bs->bit);
		पूर्ण

		bs->bit = l & 0x7;
	पूर्ण

	v &= 0xffffffff << (32 - b);

	वापस v;
पूर्ण

/*
 * Assume bs is aligned and माप(अचिन्हित पूर्णांक) == 4
 */
अटल अचिन्हित पूर्णांक get_uपूर्णांक(काष्ठा bitstr *bs, पूर्णांक b)
अणु
	अचिन्हित पूर्णांक v = 0;

	चयन (b) अणु
	हाल 4:
		v |= *bs->cur++;
		v <<= 8;
		fallthrough;
	हाल 3:
		v |= *bs->cur++;
		v <<= 8;
		fallthrough;
	हाल 2:
		v |= *bs->cur++;
		v <<= 8;
		fallthrough;
	हाल 1:
		v |= *bs->cur++;
		अवरोध;
	पूर्ण
	वापस v;
पूर्ण

अटल पूर्णांक decode_nul(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f,
                      अक्षर *base, पूर्णांक level)
अणु
	PRINT("%*.s%s\n", level * TAB_SIZE, " ", f->name);

	वापस H323_ERROR_NONE;
पूर्ण

अटल पूर्णांक decode_bool(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f,
                       अक्षर *base, पूर्णांक level)
अणु
	PRINT("%*.s%s\n", level * TAB_SIZE, " ", f->name);

	INC_BIT(bs);
	अगर (nf_h323_error_boundary(bs, 0, 0))
		वापस H323_ERROR_BOUND;
	वापस H323_ERROR_NONE;
पूर्ण

अटल पूर्णांक decode_oid(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f,
                      अक्षर *base, पूर्णांक level)
अणु
	पूर्णांक len;

	PRINT("%*.s%s\n", level * TAB_SIZE, " ", f->name);

	BYTE_ALIGN(bs);
	अगर (nf_h323_error_boundary(bs, 1, 0))
		वापस H323_ERROR_BOUND;

	len = *bs->cur++;
	bs->cur += len;
	अगर (nf_h323_error_boundary(bs, 0, 0))
		वापस H323_ERROR_BOUND;

	वापस H323_ERROR_NONE;
पूर्ण

अटल पूर्णांक decode_पूर्णांक(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f,
                      अक्षर *base, पूर्णांक level)
अणु
	अचिन्हित पूर्णांक len;

	PRINT("%*.s%s", level * TAB_SIZE, " ", f->name);

	चयन (f->sz) अणु
	हाल BYTE:		/* Range == 256 */
		BYTE_ALIGN(bs);
		bs->cur++;
		अवरोध;
	हाल WORD:		/* 257 <= Range <= 64K */
		BYTE_ALIGN(bs);
		bs->cur += 2;
		अवरोध;
	हाल CONS:		/* 64K < Range < 4G */
		अगर (nf_h323_error_boundary(bs, 0, 2))
			वापस H323_ERROR_BOUND;
		len = get_bits(bs, 2) + 1;
		BYTE_ALIGN(bs);
		अगर (base && (f->attr & DECODE)) अणु	/* समयToLive */
			अचिन्हित पूर्णांक v = get_uपूर्णांक(bs, len) + f->lb;
			PRINT(" = %u", v);
			*((अचिन्हित पूर्णांक *)(base + f->offset)) = v;
		पूर्ण
		bs->cur += len;
		अवरोध;
	हाल UNCO:
		BYTE_ALIGN(bs);
		अगर (nf_h323_error_boundary(bs, 2, 0))
			वापस H323_ERROR_BOUND;
		len = get_len(bs);
		bs->cur += len;
		अवरोध;
	शेष:		/* 2 <= Range <= 255 */
		INC_BITS(bs, f->sz);
		अवरोध;
	पूर्ण

	PRINT("\n");

	अगर (nf_h323_error_boundary(bs, 0, 0))
		वापस H323_ERROR_BOUND;
	वापस H323_ERROR_NONE;
पूर्ण

अटल पूर्णांक decode_क्रमागत(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f,
                       अक्षर *base, पूर्णांक level)
अणु
	PRINT("%*.s%s\n", level * TAB_SIZE, " ", f->name);

	अगर ((f->attr & EXT) && get_bit(bs)) अणु
		INC_BITS(bs, 7);
	पूर्ण अन्यथा अणु
		INC_BITS(bs, f->sz);
	पूर्ण

	अगर (nf_h323_error_boundary(bs, 0, 0))
		वापस H323_ERROR_BOUND;
	वापस H323_ERROR_NONE;
पूर्ण

अटल पूर्णांक decode_bitstr(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f,
                         अक्षर *base, पूर्णांक level)
अणु
	अचिन्हित पूर्णांक len;

	PRINT("%*.s%s\n", level * TAB_SIZE, " ", f->name);

	BYTE_ALIGN(bs);
	चयन (f->sz) अणु
	हाल FIXD:		/* fixed length > 16 */
		len = f->lb;
		अवरोध;
	हाल WORD:		/* 2-byte length */
		अगर (nf_h323_error_boundary(bs, 2, 0))
			वापस H323_ERROR_BOUND;
		len = (*bs->cur++) << 8;
		len += (*bs->cur++) + f->lb;
		अवरोध;
	हाल SEMI:
		अगर (nf_h323_error_boundary(bs, 2, 0))
			वापस H323_ERROR_BOUND;
		len = get_len(bs);
		अवरोध;
	शेष:
		len = 0;
		अवरोध;
	पूर्ण

	bs->cur += len >> 3;
	bs->bit = len & 7;

	अगर (nf_h323_error_boundary(bs, 0, 0))
		वापस H323_ERROR_BOUND;
	वापस H323_ERROR_NONE;
पूर्ण

अटल पूर्णांक decode_numstr(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f,
                         अक्षर *base, पूर्णांक level)
अणु
	अचिन्हित पूर्णांक len;

	PRINT("%*.s%s\n", level * TAB_SIZE, " ", f->name);

	/* 2 <= Range <= 255 */
	अगर (nf_h323_error_boundary(bs, 0, f->sz))
		वापस H323_ERROR_BOUND;
	len = get_bits(bs, f->sz) + f->lb;

	BYTE_ALIGN(bs);
	INC_BITS(bs, (len << 2));

	अगर (nf_h323_error_boundary(bs, 0, 0))
		वापस H323_ERROR_BOUND;
	वापस H323_ERROR_NONE;
पूर्ण

अटल पूर्णांक decode_octstr(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f,
                         अक्षर *base, पूर्णांक level)
अणु
	अचिन्हित पूर्णांक len;

	PRINT("%*.s%s", level * TAB_SIZE, " ", f->name);

	चयन (f->sz) अणु
	हाल FIXD:		/* Range == 1 */
		अगर (f->lb > 2) अणु
			BYTE_ALIGN(bs);
			अगर (base && (f->attr & DECODE)) अणु
				/* The IP Address */
				IFTHEN(f->lb == 4,
				       PRINT(" = %d.%d.%d.%d:%d",
					     bs->cur[0], bs->cur[1],
					     bs->cur[2], bs->cur[3],
					     bs->cur[4] * 256 + bs->cur[5]));
				*((अचिन्हित पूर्णांक *)(base + f->offset)) =
				    bs->cur - bs->buf;
			पूर्ण
		पूर्ण
		len = f->lb;
		अवरोध;
	हाल BYTE:		/* Range == 256 */
		BYTE_ALIGN(bs);
		अगर (nf_h323_error_boundary(bs, 1, 0))
			वापस H323_ERROR_BOUND;
		len = (*bs->cur++) + f->lb;
		अवरोध;
	हाल SEMI:
		BYTE_ALIGN(bs);
		अगर (nf_h323_error_boundary(bs, 2, 0))
			वापस H323_ERROR_BOUND;
		len = get_len(bs) + f->lb;
		अवरोध;
	शेष:		/* 2 <= Range <= 255 */
		अगर (nf_h323_error_boundary(bs, 0, f->sz))
			वापस H323_ERROR_BOUND;
		len = get_bits(bs, f->sz) + f->lb;
		BYTE_ALIGN(bs);
		अवरोध;
	पूर्ण

	bs->cur += len;

	PRINT("\n");

	अगर (nf_h323_error_boundary(bs, 0, 0))
		वापस H323_ERROR_BOUND;
	वापस H323_ERROR_NONE;
पूर्ण

अटल पूर्णांक decode_bmpstr(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f,
                         अक्षर *base, पूर्णांक level)
अणु
	अचिन्हित पूर्णांक len;

	PRINT("%*.s%s\n", level * TAB_SIZE, " ", f->name);

	चयन (f->sz) अणु
	हाल BYTE:		/* Range == 256 */
		BYTE_ALIGN(bs);
		अगर (nf_h323_error_boundary(bs, 1, 0))
			वापस H323_ERROR_BOUND;
		len = (*bs->cur++) + f->lb;
		अवरोध;
	शेष:		/* 2 <= Range <= 255 */
		अगर (nf_h323_error_boundary(bs, 0, f->sz))
			वापस H323_ERROR_BOUND;
		len = get_bits(bs, f->sz) + f->lb;
		BYTE_ALIGN(bs);
		अवरोध;
	पूर्ण

	bs->cur += len << 1;

	अगर (nf_h323_error_boundary(bs, 0, 0))
		वापस H323_ERROR_BOUND;
	वापस H323_ERROR_NONE;
पूर्ण

अटल पूर्णांक decode_seq(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f,
                      अक्षर *base, पूर्णांक level)
अणु
	अचिन्हित पूर्णांक ext, bmp, i, opt, len = 0, bmp2, bmp2_len;
	पूर्णांक err;
	स्थिर काष्ठा field_t *son;
	अचिन्हित अक्षर *beg = शून्य;

	PRINT("%*.s%s\n", level * TAB_SIZE, " ", f->name);

	/* Decode? */
	base = (base && (f->attr & DECODE)) ? base + f->offset : शून्य;

	/* Extensible? */
	अगर (nf_h323_error_boundary(bs, 0, 1))
		वापस H323_ERROR_BOUND;
	ext = (f->attr & EXT) ? get_bit(bs) : 0;

	/* Get fields biपंचांगap */
	अगर (nf_h323_error_boundary(bs, 0, f->sz))
		वापस H323_ERROR_BOUND;
	bmp = get_biपंचांगap(bs, f->sz);
	अगर (base)
		*(अचिन्हित पूर्णांक *)base = bmp;

	/* Decode the root components */
	क्रम (i = opt = 0, son = f->fields; i < f->lb; i++, son++) अणु
		अगर (son->attr & STOP) अणु
			PRINT("%*.s%s\n", (level + 1) * TAB_SIZE, " ",
			      son->name);
			वापस H323_ERROR_STOP;
		पूर्ण

		अगर (son->attr & OPT) अणु	/* Optional component */
			अगर (!((0x80000000U >> (opt++)) & bmp))	/* Not exist */
				जारी;
		पूर्ण

		/* Decode */
		अगर (son->attr & OPEN) अणु	/* Open field */
			अगर (nf_h323_error_boundary(bs, 2, 0))
				वापस H323_ERROR_BOUND;
			len = get_len(bs);
			अगर (nf_h323_error_boundary(bs, len, 0))
				वापस H323_ERROR_BOUND;
			अगर (!base || !(son->attr & DECODE)) अणु
				PRINT("%*.s%s\n", (level + 1) * TAB_SIZE,
				      " ", son->name);
				bs->cur += len;
				जारी;
			पूर्ण
			beg = bs->cur;

			/* Decode */
			अगर ((err = (Decoders[son->type]) (bs, son, base,
							  level + 1)) <
			    H323_ERROR_NONE)
				वापस err;

			bs->cur = beg + len;
			bs->bit = 0;
		पूर्ण अन्यथा अगर ((err = (Decoders[son->type]) (bs, son, base,
							 level + 1)) <
			   H323_ERROR_NONE)
			वापस err;
	पूर्ण

	/* No extension? */
	अगर (!ext)
		वापस H323_ERROR_NONE;

	/* Get the extension biपंचांगap */
	अगर (nf_h323_error_boundary(bs, 0, 7))
		वापस H323_ERROR_BOUND;
	bmp2_len = get_bits(bs, 7) + 1;
	अगर (nf_h323_error_boundary(bs, 0, bmp2_len))
		वापस H323_ERROR_BOUND;
	bmp2 = get_biपंचांगap(bs, bmp2_len);
	bmp |= bmp2 >> f->sz;
	अगर (base)
		*(अचिन्हित पूर्णांक *)base = bmp;
	BYTE_ALIGN(bs);

	/* Decode the extension components */
	क्रम (opt = 0; opt < bmp2_len; opt++, i++, son++) अणु
		/* Check Range */
		अगर (i >= f->ub) अणु	/* Newer Version? */
			अगर (nf_h323_error_boundary(bs, 2, 0))
				वापस H323_ERROR_BOUND;
			len = get_len(bs);
			अगर (nf_h323_error_boundary(bs, len, 0))
				वापस H323_ERROR_BOUND;
			bs->cur += len;
			जारी;
		पूर्ण

		अगर (son->attr & STOP) अणु
			PRINT("%*.s%s\n", (level + 1) * TAB_SIZE, " ",
			      son->name);
			वापस H323_ERROR_STOP;
		पूर्ण

		अगर (!((0x80000000 >> opt) & bmp2))	/* Not present */
			जारी;

		अगर (nf_h323_error_boundary(bs, 2, 0))
			वापस H323_ERROR_BOUND;
		len = get_len(bs);
		अगर (nf_h323_error_boundary(bs, len, 0))
			वापस H323_ERROR_BOUND;
		अगर (!base || !(son->attr & DECODE)) अणु
			PRINT("%*.s%s\n", (level + 1) * TAB_SIZE, " ",
			      son->name);
			bs->cur += len;
			जारी;
		पूर्ण
		beg = bs->cur;

		अगर ((err = (Decoders[son->type]) (bs, son, base,
						  level + 1)) <
		    H323_ERROR_NONE)
			वापस err;

		bs->cur = beg + len;
		bs->bit = 0;
	पूर्ण
	वापस H323_ERROR_NONE;
पूर्ण

अटल पूर्णांक decode_seqof(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f,
                        अक्षर *base, पूर्णांक level)
अणु
	अचिन्हित पूर्णांक count, effective_count = 0, i, len = 0;
	पूर्णांक err;
	स्थिर काष्ठा field_t *son;
	अचिन्हित अक्षर *beg = शून्य;

	PRINT("%*.s%s\n", level * TAB_SIZE, " ", f->name);

	/* Decode? */
	base = (base && (f->attr & DECODE)) ? base + f->offset : शून्य;

	/* Decode item count */
	चयन (f->sz) अणु
	हाल BYTE:
		BYTE_ALIGN(bs);
		अगर (nf_h323_error_boundary(bs, 1, 0))
			वापस H323_ERROR_BOUND;
		count = *bs->cur++;
		अवरोध;
	हाल WORD:
		BYTE_ALIGN(bs);
		अगर (nf_h323_error_boundary(bs, 2, 0))
			वापस H323_ERROR_BOUND;
		count = *bs->cur++;
		count <<= 8;
		count += *bs->cur++;
		अवरोध;
	हाल SEMI:
		BYTE_ALIGN(bs);
		अगर (nf_h323_error_boundary(bs, 2, 0))
			वापस H323_ERROR_BOUND;
		count = get_len(bs);
		अवरोध;
	शेष:
		अगर (nf_h323_error_boundary(bs, 0, f->sz))
			वापस H323_ERROR_BOUND;
		count = get_bits(bs, f->sz);
		अवरोध;
	पूर्ण
	count += f->lb;

	/* Write Count */
	अगर (base) अणु
		effective_count = count > f->ub ? f->ub : count;
		*(अचिन्हित पूर्णांक *)base = effective_count;
		base += माप(अचिन्हित पूर्णांक);
	पूर्ण

	/* Decode nested field */
	son = f->fields;
	अगर (base)
		base -= son->offset;
	क्रम (i = 0; i < count; i++) अणु
		अगर (son->attr & OPEN) अणु
			BYTE_ALIGN(bs);
			अगर (nf_h323_error_boundary(bs, 2, 0))
				वापस H323_ERROR_BOUND;
			len = get_len(bs);
			अगर (nf_h323_error_boundary(bs, len, 0))
				वापस H323_ERROR_BOUND;
			अगर (!base || !(son->attr & DECODE)) अणु
				PRINT("%*.s%s\n", (level + 1) * TAB_SIZE,
				      " ", son->name);
				bs->cur += len;
				जारी;
			पूर्ण
			beg = bs->cur;

			अगर ((err = (Decoders[son->type]) (bs, son,
							  i <
							  effective_count ?
							  base : शून्य,
							  level + 1)) <
			    H323_ERROR_NONE)
				वापस err;

			bs->cur = beg + len;
			bs->bit = 0;
		पूर्ण अन्यथा
			अगर ((err = (Decoders[son->type]) (bs, son,
							  i <
							  effective_count ?
							  base : शून्य,
							  level + 1)) <
			    H323_ERROR_NONE)
				वापस err;

		अगर (base)
			base += son->offset;
	पूर्ण

	वापस H323_ERROR_NONE;
पूर्ण

अटल पूर्णांक decode_choice(काष्ठा bitstr *bs, स्थिर काष्ठा field_t *f,
                         अक्षर *base, पूर्णांक level)
अणु
	अचिन्हित पूर्णांक type, ext, len = 0;
	पूर्णांक err;
	स्थिर काष्ठा field_t *son;
	अचिन्हित अक्षर *beg = शून्य;

	PRINT("%*.s%s\n", level * TAB_SIZE, " ", f->name);

	/* Decode? */
	base = (base && (f->attr & DECODE)) ? base + f->offset : शून्य;

	/* Decode the choice index number */
	अगर (nf_h323_error_boundary(bs, 0, 1))
		वापस H323_ERROR_BOUND;
	अगर ((f->attr & EXT) && get_bit(bs)) अणु
		ext = 1;
		अगर (nf_h323_error_boundary(bs, 0, 7))
			वापस H323_ERROR_BOUND;
		type = get_bits(bs, 7) + f->lb;
	पूर्ण अन्यथा अणु
		ext = 0;
		अगर (nf_h323_error_boundary(bs, 0, f->sz))
			वापस H323_ERROR_BOUND;
		type = get_bits(bs, f->sz);
		अगर (type >= f->lb)
			वापस H323_ERROR_RANGE;
	पूर्ण

	/* Write Type */
	अगर (base)
		*(अचिन्हित पूर्णांक *)base = type;

	/* Check Range */
	अगर (type >= f->ub) अणु	/* Newer version? */
		BYTE_ALIGN(bs);
		अगर (nf_h323_error_boundary(bs, 2, 0))
			वापस H323_ERROR_BOUND;
		len = get_len(bs);
		अगर (nf_h323_error_boundary(bs, len, 0))
			वापस H323_ERROR_BOUND;
		bs->cur += len;
		वापस H323_ERROR_NONE;
	पूर्ण

	/* Transfer to son level */
	son = &f->fields[type];
	अगर (son->attr & STOP) अणु
		PRINT("%*.s%s\n", (level + 1) * TAB_SIZE, " ", son->name);
		वापस H323_ERROR_STOP;
	पूर्ण

	अगर (ext || (son->attr & OPEN)) अणु
		BYTE_ALIGN(bs);
		अगर (nf_h323_error_boundary(bs, len, 0))
			वापस H323_ERROR_BOUND;
		len = get_len(bs);
		अगर (nf_h323_error_boundary(bs, len, 0))
			वापस H323_ERROR_BOUND;
		अगर (!base || !(son->attr & DECODE)) अणु
			PRINT("%*.s%s\n", (level + 1) * TAB_SIZE, " ",
			      son->name);
			bs->cur += len;
			वापस H323_ERROR_NONE;
		पूर्ण
		beg = bs->cur;

		अगर ((err = (Decoders[son->type]) (bs, son, base, level + 1)) <
		    H323_ERROR_NONE)
			वापस err;

		bs->cur = beg + len;
		bs->bit = 0;
	पूर्ण अन्यथा अगर ((err = (Decoders[son->type]) (bs, son, base, level + 1)) <
		   H323_ERROR_NONE)
		वापस err;

	वापस H323_ERROR_NONE;
पूर्ण

पूर्णांक DecodeRasMessage(अचिन्हित अक्षर *buf, माप_प्रकार sz, RasMessage *ras)
अणु
	अटल स्थिर काष्ठा field_t ras_message = अणु
		FNAME("RasMessage") CHOICE, 5, 24, 32, DECODE | EXT,
		0, _RasMessage
	पूर्ण;
	काष्ठा bitstr bs;

	bs.buf = bs.beg = bs.cur = buf;
	bs.end = buf + sz;
	bs.bit = 0;

	वापस decode_choice(&bs, &ras_message, (अक्षर *) ras, 0);
पूर्ण

अटल पूर्णांक DecodeH323_UserInक्रमmation(अचिन्हित अक्षर *buf, अचिन्हित अक्षर *beg,
				      माप_प्रकार sz, H323_UserInक्रमmation *uuie)
अणु
	अटल स्थिर काष्ठा field_t h323_userinक्रमmation = अणु
		FNAME("H323-UserInformation") SEQ, 1, 2, 2, DECODE | EXT,
		0, _H323_UserInक्रमmation
	पूर्ण;
	काष्ठा bitstr bs;

	bs.buf = buf;
	bs.beg = bs.cur = beg;
	bs.end = beg + sz;
	bs.bit = 0;

	वापस decode_seq(&bs, &h323_userinक्रमmation, (अक्षर *) uuie, 0);
पूर्ण

पूर्णांक DecodeMulसमयdiaSystemControlMessage(अचिन्हित अक्षर *buf, माप_प्रकार sz,
					 MulसमयdiaSystemControlMessage *
					 mscm)
अणु
	अटल स्थिर काष्ठा field_t mulसमयdiaप्रणालीcontrolmessage = अणु
		FNAME("MultimediaSystemControlMessage") CHOICE, 2, 4, 4,
		DECODE | EXT, 0, _MulसमयdiaSystemControlMessage
	पूर्ण;
	काष्ठा bitstr bs;

	bs.buf = bs.beg = bs.cur = buf;
	bs.end = buf + sz;
	bs.bit = 0;

	वापस decode_choice(&bs, &mulसमयdiaप्रणालीcontrolmessage,
			     (अक्षर *) mscm, 0);
पूर्ण

पूर्णांक DecodeQ931(अचिन्हित अक्षर *buf, माप_प्रकार sz, Q931 *q931)
अणु
	अचिन्हित अक्षर *p = buf;
	पूर्णांक len;

	अगर (!p || sz < 1)
		वापस H323_ERROR_BOUND;

	/* Protocol Discriminator */
	अगर (*p != 0x08) अणु
		PRINT("Unknown Protocol Discriminator\n");
		वापस H323_ERROR_RANGE;
	पूर्ण
	p++;
	sz--;

	/* CallReferenceValue */
	अगर (sz < 1)
		वापस H323_ERROR_BOUND;
	len = *p++;
	sz--;
	अगर (sz < len)
		वापस H323_ERROR_BOUND;
	p += len;
	sz -= len;

	/* Message Type */
	अगर (sz < 2)
		वापस H323_ERROR_BOUND;
	q931->MessageType = *p++;
	sz--;
	PRINT("MessageType = %02X\n", q931->MessageType);
	अगर (*p & 0x80) अणु
		p++;
		sz--;
	पूर्ण

	/* Decode Inक्रमmation Elements */
	जबतक (sz > 0) अणु
		अगर (*p == 0x7e) अणु	/* UserUserIE */
			अगर (sz < 3)
				अवरोध;
			p++;
			len = *p++ << 8;
			len |= *p++;
			sz -= 3;
			अगर (sz < len)
				अवरोध;
			p++;
			len--;
			वापस DecodeH323_UserInक्रमmation(buf, p, len,
							  &q931->UUIE);
		पूर्ण
		p++;
		sz--;
		अगर (sz < 1)
			अवरोध;
		len = *p++;
		sz--;
		अगर (sz < len)
			अवरोध;
		p += len;
		sz -= len;
	पूर्ण

	PRINT("Q.931 UUIE not found\n");

	वापस H323_ERROR_BOUND;
पूर्ण
