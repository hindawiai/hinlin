<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic Reed Solomon encoder / decoder library
 *
 * Copyright (C) 2004 Thomas Gleixner (tglx@linutronix.de)
 *
 * Reed Solomon code lअगरted from reed solomon library written by Phil Karn
 * Copyright 2002 Phil Karn, KA9Q
 *
 * Description:
 *
 * The generic Reed Solomon library provides runसमय configurable
 * encoding / decoding of RS codes.
 *
 * Each user must call init_rs to get a poपूर्णांकer to a rs_control काष्ठाure
 * क्रम the given rs parameters. The control काष्ठा is unique per instance.
 * It poपूर्णांकs to a codec which can be shared by multiple control काष्ठाures.
 * If a codec is newly allocated then the polynomial arrays क्रम fast
 * encoding / decoding are built. This can take some समय so make sure not
 * to call this function from a समय critical path.  Usually a module /
 * driver should initialize the necessary rs_control काष्ठाure on module /
 * driver init and release it on निकास.
 *
 * The encoding माला_दो the calculated syndrome पूर्णांकo a given syndrome buffer.
 *
 * The decoding is a two step process. The first step calculates the
 * syndrome over the received (data + syndrome) and calls the second stage,
 * which करोes the decoding / error correction itself.  Many hw encoders
 * provide a syndrome calculation over the received data + syndrome and can
 * call the second stage directly.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/rslib.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

क्रमागत अणु
	RS_DECODE_LAMBDA,
	RS_DECODE_SYN,
	RS_DECODE_B,
	RS_DECODE_T,
	RS_DECODE_OMEGA,
	RS_DECODE_ROOT,
	RS_DECODE_REG,
	RS_DECODE_LOC,
	RS_DECODE_NUM_BUFFERS
पूर्ण;

/* This list holds all currently allocated rs codec काष्ठाures */
अटल LIST_HEAD(codec_list);
/* Protection क्रम the list */
अटल DEFINE_MUTEX(rslistlock);

/**
 * codec_init - Initialize a Reed-Solomon codec
 * @symsize:	symbol size, bits (1-8)
 * @gfpoly:	Field generator polynomial coefficients
 * @gffunc:	Field generator function
 * @fcr:	first root of RS code generator polynomial, index क्रमm
 * @prim:	primitive element to generate polynomial roots
 * @nroots:	RS code generator polynomial degree (number of roots)
 * @gfp:	GFP_ flags क्रम allocations
 *
 * Allocate a codec काष्ठाure and the polynom arrays क्रम faster
 * en/decoding. Fill the arrays according to the given parameters.
 */
अटल काष्ठा rs_codec *codec_init(पूर्णांक symsize, पूर्णांक gfpoly, पूर्णांक (*gffunc)(पूर्णांक),
				   पूर्णांक fcr, पूर्णांक prim, पूर्णांक nroots, gfp_t gfp)
अणु
	पूर्णांक i, j, sr, root, iprim;
	काष्ठा rs_codec *rs;

	rs = kzalloc(माप(*rs), gfp);
	अगर (!rs)
		वापस शून्य;

	INIT_LIST_HEAD(&rs->list);

	rs->mm = symsize;
	rs->nn = (1 << symsize) - 1;
	rs->fcr = fcr;
	rs->prim = prim;
	rs->nroots = nroots;
	rs->gfpoly = gfpoly;
	rs->gffunc = gffunc;

	/* Allocate the arrays */
	rs->alpha_to = kदो_स्मृति_array(rs->nn + 1, माप(uपूर्णांक16_t), gfp);
	अगर (rs->alpha_to == शून्य)
		जाओ err;

	rs->index_of = kदो_स्मृति_array(rs->nn + 1, माप(uपूर्णांक16_t), gfp);
	अगर (rs->index_of == शून्य)
		जाओ err;

	rs->genpoly = kदो_स्मृति_array(rs->nroots + 1, माप(uपूर्णांक16_t), gfp);
	अगर(rs->genpoly == शून्य)
		जाओ err;

	/* Generate Galois field lookup tables */
	rs->index_of[0] = rs->nn;	/* log(zero) = -inf */
	rs->alpha_to[rs->nn] = 0;	/* alpha**-inf = 0 */
	अगर (gfpoly) अणु
		sr = 1;
		क्रम (i = 0; i < rs->nn; i++) अणु
			rs->index_of[sr] = i;
			rs->alpha_to[i] = sr;
			sr <<= 1;
			अगर (sr & (1 << symsize))
				sr ^= gfpoly;
			sr &= rs->nn;
		पूर्ण
	पूर्ण अन्यथा अणु
		sr = gffunc(0);
		क्रम (i = 0; i < rs->nn; i++) अणु
			rs->index_of[sr] = i;
			rs->alpha_to[i] = sr;
			sr = gffunc(sr);
		पूर्ण
	पूर्ण
	/* If it's not primitive, निकास */
	अगर(sr != rs->alpha_to[0])
		जाओ err;

	/* Find prim-th root of 1, used in decoding */
	क्रम(iprim = 1; (iprim % prim) != 0; iprim += rs->nn);
	/* prim-th root of 1, index क्रमm */
	rs->iprim = iprim / prim;

	/* Form RS code generator polynomial from its roots */
	rs->genpoly[0] = 1;
	क्रम (i = 0, root = fcr * prim; i < nroots; i++, root += prim) अणु
		rs->genpoly[i + 1] = 1;
		/* Multiply rs->genpoly[] by  @**(root + x) */
		क्रम (j = i; j > 0; j--) अणु
			अगर (rs->genpoly[j] != 0) अणु
				rs->genpoly[j] = rs->genpoly[j -1] ^
					rs->alpha_to[rs_modnn(rs,
					rs->index_of[rs->genpoly[j]] + root)];
			पूर्ण अन्यथा
				rs->genpoly[j] = rs->genpoly[j - 1];
		पूर्ण
		/* rs->genpoly[0] can never be zero */
		rs->genpoly[0] =
			rs->alpha_to[rs_modnn(rs,
				rs->index_of[rs->genpoly[0]] + root)];
	पूर्ण
	/* convert rs->genpoly[] to index क्रमm क्रम quicker encoding */
	क्रम (i = 0; i <= nroots; i++)
		rs->genpoly[i] = rs->index_of[rs->genpoly[i]];

	rs->users = 1;
	list_add(&rs->list, &codec_list);
	वापस rs;

err:
	kमुक्त(rs->genpoly);
	kमुक्त(rs->index_of);
	kमुक्त(rs->alpha_to);
	kमुक्त(rs);
	वापस शून्य;
पूर्ण


/**
 *  मुक्त_rs - Free the rs control काष्ठाure
 *  @rs:	The control काष्ठाure which is not दीर्घer used by the
 *		caller
 *
 * Free the control काष्ठाure. If @rs is the last user of the associated
 * codec, मुक्त the codec as well.
 */
व्योम मुक्त_rs(काष्ठा rs_control *rs)
अणु
	काष्ठा rs_codec *cd;

	अगर (!rs)
		वापस;

	cd = rs->codec;
	mutex_lock(&rslistlock);
	cd->users--;
	अगर(!cd->users) अणु
		list_del(&cd->list);
		kमुक्त(cd->alpha_to);
		kमुक्त(cd->index_of);
		kमुक्त(cd->genpoly);
		kमुक्त(cd);
	पूर्ण
	mutex_unlock(&rslistlock);
	kमुक्त(rs);
पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_rs);

/**
 * init_rs_पूर्णांकernal - Allocate rs control, find a matching codec or allocate a new one
 *  @symsize:	the symbol size (number of bits)
 *  @gfpoly:	the extended Galois field generator polynomial coefficients,
 *		with the 0th coefficient in the low order bit. The polynomial
 *		must be primitive;
 *  @gffunc:	poपूर्णांकer to function to generate the next field element,
 *		or the multiplicative identity element अगर given 0.  Used
 *		instead of gfpoly अगर gfpoly is 0
 *  @fcr:	the first consecutive root of the rs code generator polynomial
 *		in index क्रमm
 *  @prim:	primitive element to generate polynomial roots
 *  @nroots:	RS code generator polynomial degree (number of roots)
 *  @gfp:	GFP_ flags क्रम allocations
 */
अटल काष्ठा rs_control *init_rs_पूर्णांकernal(पूर्णांक symsize, पूर्णांक gfpoly,
					   पूर्णांक (*gffunc)(पूर्णांक), पूर्णांक fcr,
					   पूर्णांक prim, पूर्णांक nroots, gfp_t gfp)
अणु
	काष्ठा list_head *पंचांगp;
	काष्ठा rs_control *rs;
	अचिन्हित पूर्णांक bsize;

	/* Sanity checks */
	अगर (symsize < 1)
		वापस शून्य;
	अगर (fcr < 0 || fcr >= (1<<symsize))
		वापस शून्य;
	अगर (prim <= 0 || prim >= (1<<symsize))
		वापस शून्य;
	अगर (nroots < 0 || nroots >= (1<<symsize))
		वापस शून्य;

	/*
	 * The decoder needs buffers in each control काष्ठा instance to
	 * aव्योम variable size or large fixed size allocations on
	 * stack. Size the buffers to arrays of [nroots + 1].
	 */
	bsize = माप(uपूर्णांक16_t) * RS_DECODE_NUM_BUFFERS * (nroots + 1);
	rs = kzalloc(माप(*rs) + bsize, gfp);
	अगर (!rs)
		वापस शून्य;

	mutex_lock(&rslistlock);

	/* Walk through the list and look क्रम a matching entry */
	list_क्रम_each(पंचांगp, &codec_list) अणु
		काष्ठा rs_codec *cd = list_entry(पंचांगp, काष्ठा rs_codec, list);

		अगर (symsize != cd->mm)
			जारी;
		अगर (gfpoly != cd->gfpoly)
			जारी;
		अगर (gffunc != cd->gffunc)
			जारी;
		अगर (fcr != cd->fcr)
			जारी;
		अगर (prim != cd->prim)
			जारी;
		अगर (nroots != cd->nroots)
			जारी;
		/* We have a matching one alपढ़ोy */
		cd->users++;
		rs->codec = cd;
		जाओ out;
	पूर्ण

	/* Create a new one */
	rs->codec = codec_init(symsize, gfpoly, gffunc, fcr, prim, nroots, gfp);
	अगर (!rs->codec) अणु
		kमुक्त(rs);
		rs = शून्य;
	पूर्ण
out:
	mutex_unlock(&rslistlock);
	वापस rs;
पूर्ण

/**
 * init_rs_gfp - Create a RS control काष्ठा and initialize it
 *  @symsize:	the symbol size (number of bits)
 *  @gfpoly:	the extended Galois field generator polynomial coefficients,
 *		with the 0th coefficient in the low order bit. The polynomial
 *		must be primitive;
 *  @fcr:	the first consecutive root of the rs code generator polynomial
 *		in index क्रमm
 *  @prim:	primitive element to generate polynomial roots
 *  @nroots:	RS code generator polynomial degree (number of roots)
 *  @gfp:	Memory allocation flags.
 */
काष्ठा rs_control *init_rs_gfp(पूर्णांक symsize, पूर्णांक gfpoly, पूर्णांक fcr, पूर्णांक prim,
			       पूर्णांक nroots, gfp_t gfp)
अणु
	वापस init_rs_पूर्णांकernal(symsize, gfpoly, शून्य, fcr, prim, nroots, gfp);
पूर्ण
EXPORT_SYMBOL_GPL(init_rs_gfp);

/**
 * init_rs_non_canonical - Allocate rs control काष्ठा क्रम fields with
 *                         non-canonical representation
 *  @symsize:	the symbol size (number of bits)
 *  @gffunc:	poपूर्णांकer to function to generate the next field element,
 *		or the multiplicative identity element अगर given 0.  Used
 *		instead of gfpoly अगर gfpoly is 0
 *  @fcr:	the first consecutive root of the rs code generator polynomial
 *		in index क्रमm
 *  @prim:	primitive element to generate polynomial roots
 *  @nroots:	RS code generator polynomial degree (number of roots)
 */
काष्ठा rs_control *init_rs_non_canonical(पूर्णांक symsize, पूर्णांक (*gffunc)(पूर्णांक),
					 पूर्णांक fcr, पूर्णांक prim, पूर्णांक nroots)
अणु
	वापस init_rs_पूर्णांकernal(symsize, 0, gffunc, fcr, prim, nroots,
				GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL_GPL(init_rs_non_canonical);

#अगर_घोषित CONFIG_REED_SOLOMON_ENC8
/**
 *  encode_rs8 - Calculate the parity क्रम data values (8bit data width)
 *  @rsc:	the rs control काष्ठाure
 *  @data:	data field of a given type
 *  @len:	data length
 *  @par:	parity data, must be initialized by caller (usually all 0)
 *  @invmsk:	invert data mask (will be xored on data)
 *
 *  The parity uses a uपूर्णांक16_t data type to enable
 *  symbol size > 8. The calling code must take care of encoding of the
 *  syndrome result क्रम storage itself.
 */
पूर्णांक encode_rs8(काष्ठा rs_control *rsc, uपूर्णांक8_t *data, पूर्णांक len, uपूर्णांक16_t *par,
	       uपूर्णांक16_t invmsk)
अणु
#समावेश "encode_rs.c"
पूर्ण
EXPORT_SYMBOL_GPL(encode_rs8);
#पूर्ण_अगर

#अगर_घोषित CONFIG_REED_SOLOMON_DEC8
/**
 *  decode_rs8 - Decode codeword (8bit data width)
 *  @rsc:	the rs control काष्ठाure
 *  @data:	data field of a given type
 *  @par:	received parity data field
 *  @len:	data length
 *  @s: 	syndrome data field, must be in index क्रमm
 *		(अगर शून्य, syndrome is calculated)
 *  @no_eras:	number of erasures
 *  @eras_pos:	position of erasures, can be शून्य
 *  @invmsk:	invert data mask (will be xored on data, not on parity!)
 *  @corr:	buffer to store correction biपंचांगask on eras_pos
 *
 *  The syndrome and parity uses a uपूर्णांक16_t data type to enable
 *  symbol size > 8. The calling code must take care of decoding of the
 *  syndrome result and the received parity beक्रमe calling this code.
 *
 *  Note: The rs_control काष्ठा @rsc contains buffers which are used क्रम
 *  decoding, so the caller has to ensure that decoder invocations are
 *  serialized.
 *
 *  Returns the number of corrected symbols or -EBADMSG क्रम uncorrectable
 *  errors. The count includes errors in the parity.
 */
पूर्णांक decode_rs8(काष्ठा rs_control *rsc, uपूर्णांक8_t *data, uपूर्णांक16_t *par, पूर्णांक len,
	       uपूर्णांक16_t *s, पूर्णांक no_eras, पूर्णांक *eras_pos, uपूर्णांक16_t invmsk,
	       uपूर्णांक16_t *corr)
अणु
#समावेश "decode_rs.c"
पूर्ण
EXPORT_SYMBOL_GPL(decode_rs8);
#पूर्ण_अगर

#अगर_घोषित CONFIG_REED_SOLOMON_ENC16
/**
 *  encode_rs16 - Calculate the parity क्रम data values (16bit data width)
 *  @rsc:	the rs control काष्ठाure
 *  @data:	data field of a given type
 *  @len:	data length
 *  @par:	parity data, must be initialized by caller (usually all 0)
 *  @invmsk:	invert data mask (will be xored on data, not on parity!)
 *
 *  Each field in the data array contains up to symbol size bits of valid data.
 */
पूर्णांक encode_rs16(काष्ठा rs_control *rsc, uपूर्णांक16_t *data, पूर्णांक len, uपूर्णांक16_t *par,
	uपूर्णांक16_t invmsk)
अणु
#समावेश "encode_rs.c"
पूर्ण
EXPORT_SYMBOL_GPL(encode_rs16);
#पूर्ण_अगर

#अगर_घोषित CONFIG_REED_SOLOMON_DEC16
/**
 *  decode_rs16 - Decode codeword (16bit data width)
 *  @rsc:	the rs control काष्ठाure
 *  @data:	data field of a given type
 *  @par:	received parity data field
 *  @len:	data length
 *  @s: 	syndrome data field, must be in index क्रमm
 *		(अगर शून्य, syndrome is calculated)
 *  @no_eras:	number of erasures
 *  @eras_pos:	position of erasures, can be शून्य
 *  @invmsk:	invert data mask (will be xored on data, not on parity!)
 *  @corr:	buffer to store correction biपंचांगask on eras_pos
 *
 *  Each field in the data array contains up to symbol size bits of valid data.
 *
 *  Note: The rc_control काष्ठा @rsc contains buffers which are used क्रम
 *  decoding, so the caller has to ensure that decoder invocations are
 *  serialized.
 *
 *  Returns the number of corrected symbols or -EBADMSG क्रम uncorrectable
 *  errors. The count includes errors in the parity.
 */
पूर्णांक decode_rs16(काष्ठा rs_control *rsc, uपूर्णांक16_t *data, uपूर्णांक16_t *par, पूर्णांक len,
		uपूर्णांक16_t *s, पूर्णांक no_eras, पूर्णांक *eras_pos, uपूर्णांक16_t invmsk,
		uपूर्णांक16_t *corr)
अणु
#समावेश "decode_rs.c"
पूर्ण
EXPORT_SYMBOL_GPL(decode_rs16);
#पूर्ण_अगर

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Reed Solomon encoder/decoder");
MODULE_AUTHOR("Phil Karn, Thomas Gleixner");

