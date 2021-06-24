<शैली गुरु>
/* mpicoder.c  -  Coder क्रम the बाह्यal representation of MPIs
 * Copyright (C) 1998, 1999 Free Software Foundation, Inc.
 *
 * This file is part of GnuPG.
 *
 * GnuPG is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GnuPG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#समावेश <linux/bitops.h>
#समावेश <linux/count_zeros.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/माला.स>
#समावेश "mpi-internal.h"

#घोषणा MAX_EXTERN_SCAN_BYTES (16*1024*1024)
#घोषणा MAX_EXTERN_MPI_BITS 16384

/**
 * mpi_पढ़ो_raw_data - Read a raw byte stream as a positive पूर्णांकeger
 * @xbuffer: The data to पढ़ो
 * @nbytes: The amount of data to पढ़ो
 */
MPI mpi_पढ़ो_raw_data(स्थिर व्योम *xbuffer, माप_प्रकार nbytes)
अणु
	स्थिर uपूर्णांक8_t *buffer = xbuffer;
	पूर्णांक i, j;
	अचिन्हित nbits, nlimbs;
	mpi_limb_t a;
	MPI val = शून्य;

	जबतक (nbytes > 0 && buffer[0] == 0) अणु
		buffer++;
		nbytes--;
	पूर्ण

	nbits = nbytes * 8;
	अगर (nbits > MAX_EXTERN_MPI_BITS) अणु
		pr_info("MPI: mpi too large (%u bits)\n", nbits);
		वापस शून्य;
	पूर्ण
	अगर (nbytes > 0)
		nbits -= count_leading_zeros(buffer[0]) - (BITS_PER_LONG - 8);

	nlimbs = DIV_ROUND_UP(nbytes, BYTES_PER_MPI_LIMB);
	val = mpi_alloc(nlimbs);
	अगर (!val)
		वापस शून्य;
	val->nbits = nbits;
	val->sign = 0;
	val->nlimbs = nlimbs;

	अगर (nbytes > 0) अणु
		i = BYTES_PER_MPI_LIMB - nbytes % BYTES_PER_MPI_LIMB;
		i %= BYTES_PER_MPI_LIMB;
		क्रम (j = nlimbs; j > 0; j--) अणु
			a = 0;
			क्रम (; i < BYTES_PER_MPI_LIMB; i++) अणु
				a <<= 8;
				a |= *buffer++;
			पूर्ण
			i = 0;
			val->d[j - 1] = a;
		पूर्ण
	पूर्ण
	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_पढ़ो_raw_data);

MPI mpi_पढ़ो_from_buffer(स्थिर व्योम *xbuffer, अचिन्हित *ret_nपढ़ो)
अणु
	स्थिर uपूर्णांक8_t *buffer = xbuffer;
	अचिन्हित पूर्णांक nbits, nbytes;
	MPI val;

	अगर (*ret_nपढ़ो < 2)
		वापस ERR_PTR(-EINVAL);
	nbits = buffer[0] << 8 | buffer[1];

	अगर (nbits > MAX_EXTERN_MPI_BITS) अणु
		pr_info("MPI: mpi too large (%u bits)\n", nbits);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	nbytes = DIV_ROUND_UP(nbits, 8);
	अगर (nbytes + 2 > *ret_nपढ़ो) अणु
		pr_info("MPI: mpi larger than buffer nbytes=%u ret_nread=%u\n",
				nbytes, *ret_nपढ़ो);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	val = mpi_पढ़ो_raw_data(buffer + 2, nbytes);
	अगर (!val)
		वापस ERR_PTR(-ENOMEM);

	*ret_nपढ़ो = nbytes + 2;
	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_पढ़ो_from_buffer);

/****************
 * Fill the mpi VAL from the hex string in STR.
 */
पूर्णांक mpi_fromstr(MPI val, स्थिर अक्षर *str)
अणु
	पूर्णांक sign = 0;
	पूर्णांक prepend_zero = 0;
	पूर्णांक i, j, c, c1, c2;
	अचिन्हित पूर्णांक nbits, nbytes, nlimbs;
	mpi_limb_t a;

	अगर (*str == '-') अणु
		sign = 1;
		str++;
	पूर्ण

	/* Skip optional hex prefix.  */
	अगर (*str == '0' && str[1] == 'x')
		str += 2;

	nbits = म_माप(str);
	अगर (nbits > MAX_EXTERN_SCAN_BYTES) अणु
		mpi_clear(val);
		वापस -EINVAL;
	पूर्ण
	nbits *= 4;
	अगर ((nbits % 8))
		prepend_zero = 1;

	nbytes = (nbits+7) / 8;
	nlimbs = (nbytes+BYTES_PER_MPI_LIMB-1) / BYTES_PER_MPI_LIMB;

	अगर (val->alloced < nlimbs)
		mpi_resize(val, nlimbs);

	i = BYTES_PER_MPI_LIMB - (nbytes % BYTES_PER_MPI_LIMB);
	i %= BYTES_PER_MPI_LIMB;
	j = val->nlimbs = nlimbs;
	val->sign = sign;
	क्रम (; j > 0; j--) अणु
		a = 0;
		क्रम (; i < BYTES_PER_MPI_LIMB; i++) अणु
			अगर (prepend_zero) अणु
				c1 = '0';
				prepend_zero = 0;
			पूर्ण अन्यथा
				c1 = *str++;

			अगर (!c1) अणु
				mpi_clear(val);
				वापस -EINVAL;
			पूर्ण
			c2 = *str++;
			अगर (!c2) अणु
				mpi_clear(val);
				वापस -EINVAL;
			पूर्ण
			अगर (c1 >= '0' && c1 <= '9')
				c = c1 - '0';
			अन्यथा अगर (c1 >= 'a' && c1 <= 'f')
				c = c1 - 'a' + 10;
			अन्यथा अगर (c1 >= 'A' && c1 <= 'F')
				c = c1 - 'A' + 10;
			अन्यथा अणु
				mpi_clear(val);
				वापस -EINVAL;
			पूर्ण
			c <<= 4;
			अगर (c2 >= '0' && c2 <= '9')
				c |= c2 - '0';
			अन्यथा अगर (c2 >= 'a' && c2 <= 'f')
				c |= c2 - 'a' + 10;
			अन्यथा अगर (c2 >= 'A' && c2 <= 'F')
				c |= c2 - 'A' + 10;
			अन्यथा अणु
				mpi_clear(val);
				वापस -EINVAL;
			पूर्ण
			a <<= 8;
			a |= c;
		पूर्ण
		i = 0;
		val->d[j-1] = a;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_fromstr);

MPI mpi_scanval(स्थिर अक्षर *string)
अणु
	MPI a;

	a = mpi_alloc(0);
	अगर (!a)
		वापस शून्य;

	अगर (mpi_fromstr(a, string)) अणु
		mpi_मुक्त(a);
		वापस शून्य;
	पूर्ण
	mpi_normalize(a);
	वापस a;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_scanval);

अटल पूर्णांक count_lzeros(MPI a)
अणु
	mpi_limb_t alimb;
	पूर्णांक i, lzeros = 0;

	क्रम (i = a->nlimbs - 1; i >= 0; i--) अणु
		alimb = a->d[i];
		अगर (alimb == 0) अणु
			lzeros += माप(mpi_limb_t);
		पूर्ण अन्यथा अणु
			lzeros += count_leading_zeros(alimb) / 8;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस lzeros;
पूर्ण

/**
 * mpi_पढ़ो_buffer() - पढ़ो MPI to a bufer provided by user (msb first)
 *
 * @a:		a multi precision पूर्णांकeger
 * @buf:	bufer to which the output will be written to. Needs to be at
 *		leaset mpi_get_size(a) दीर्घ.
 * @buf_len:	size of the buf.
 * @nbytes:	receives the actual length of the data written on success and
 *		the data to-be-written on -EOVERFLOW in हाल buf_len was too
 *		small.
 * @sign:	अगर not शून्य, it will be set to the sign of a.
 *
 * Return:	0 on success or error code in हाल of error
 */
पूर्णांक mpi_पढ़ो_buffer(MPI a, uपूर्णांक8_t *buf, अचिन्हित buf_len, अचिन्हित *nbytes,
		    पूर्णांक *sign)
अणु
	uपूर्णांक8_t *p;
#अगर BYTES_PER_MPI_LIMB == 4
	__be32 alimb;
#या_अगर BYTES_PER_MPI_LIMB == 8
	__be64 alimb;
#अन्यथा
#त्रुटि please implement क्रम this limb size.
#पूर्ण_अगर
	अचिन्हित पूर्णांक n = mpi_get_size(a);
	पूर्णांक i, lzeros;

	अगर (!buf || !nbytes)
		वापस -EINVAL;

	अगर (sign)
		*sign = a->sign;

	lzeros = count_lzeros(a);

	अगर (buf_len < n - lzeros) अणु
		*nbytes = n - lzeros;
		वापस -EOVERFLOW;
	पूर्ण

	p = buf;
	*nbytes = n - lzeros;

	क्रम (i = a->nlimbs - 1 - lzeros / BYTES_PER_MPI_LIMB,
			lzeros %= BYTES_PER_MPI_LIMB;
		i >= 0; i--) अणु
#अगर BYTES_PER_MPI_LIMB == 4
		alimb = cpu_to_be32(a->d[i]);
#या_अगर BYTES_PER_MPI_LIMB == 8
		alimb = cpu_to_be64(a->d[i]);
#अन्यथा
#त्रुटि please implement क्रम this limb size.
#पूर्ण_अगर
		स_नकल(p, (u8 *)&alimb + lzeros, BYTES_PER_MPI_LIMB - lzeros);
		p += BYTES_PER_MPI_LIMB - lzeros;
		lzeros = 0;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_पढ़ो_buffer);

/*
 * mpi_get_buffer() - Returns an allocated buffer with the MPI (msb first).
 * Caller must मुक्त the वापस string.
 * This function करोes वापस a 0 byte buffer with nbytes set to zero अगर the
 * value of A is zero.
 *
 * @a:		a multi precision पूर्णांकeger.
 * @nbytes:	receives the length of this buffer.
 * @sign:	अगर not शून्य, it will be set to the sign of the a.
 *
 * Return:	Poपूर्णांकer to MPI buffer or शून्य on error
 */
व्योम *mpi_get_buffer(MPI a, अचिन्हित *nbytes, पूर्णांक *sign)
अणु
	uपूर्णांक8_t *buf;
	अचिन्हित पूर्णांक n;
	पूर्णांक ret;

	अगर (!nbytes)
		वापस शून्य;

	n = mpi_get_size(a);

	अगर (!n)
		n++;

	buf = kदो_स्मृति(n, GFP_KERNEL);

	अगर (!buf)
		वापस शून्य;

	ret = mpi_पढ़ो_buffer(a, buf, n, nbytes, sign);

	अगर (ret) अणु
		kमुक्त(buf);
		वापस शून्य;
	पूर्ण
	वापस buf;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_get_buffer);

/**
 * mpi_ग_लिखो_to_sgl() - Funnction exports MPI to an sgl (msb first)
 *
 * This function works in the same way as the mpi_पढ़ो_buffer, but it
 * takes an sgl instead of u8 * buf.
 *
 * @a:		a multi precision पूर्णांकeger
 * @sgl:	scatterlist to ग_लिखो to. Needs to be at least
 *		mpi_get_size(a) दीर्घ.
 * @nbytes:	the number of bytes to ग_लिखो.  Leading bytes will be
 *		filled with zero.
 * @sign:	अगर not शून्य, it will be set to the sign of a.
 *
 * Return:	0 on success or error code in हाल of error
 */
पूर्णांक mpi_ग_लिखो_to_sgl(MPI a, काष्ठा scatterlist *sgl, अचिन्हित nbytes,
		     पूर्णांक *sign)
अणु
	u8 *p, *p2;
#अगर BYTES_PER_MPI_LIMB == 4
	__be32 alimb;
#या_अगर BYTES_PER_MPI_LIMB == 8
	__be64 alimb;
#अन्यथा
#त्रुटि please implement क्रम this limb size.
#पूर्ण_अगर
	अचिन्हित पूर्णांक n = mpi_get_size(a);
	काष्ठा sg_mapping_iter miter;
	पूर्णांक i, x, buf_len;
	पूर्णांक nents;

	अगर (sign)
		*sign = a->sign;

	अगर (nbytes < n)
		वापस -EOVERFLOW;

	nents = sg_nents_क्रम_len(sgl, nbytes);
	अगर (nents < 0)
		वापस -EINVAL;

	sg_miter_start(&miter, sgl, nents, SG_MITER_ATOMIC | SG_MITER_TO_SG);
	sg_miter_next(&miter);
	buf_len = miter.length;
	p2 = miter.addr;

	जबतक (nbytes > n) अणु
		i = min_t(अचिन्हित, nbytes - n, buf_len);
		स_रखो(p2, 0, i);
		p2 += i;
		nbytes -= i;

		buf_len -= i;
		अगर (!buf_len) अणु
			sg_miter_next(&miter);
			buf_len = miter.length;
			p2 = miter.addr;
		पूर्ण
	पूर्ण

	क्रम (i = a->nlimbs - 1; i >= 0; i--) अणु
#अगर BYTES_PER_MPI_LIMB == 4
		alimb = a->d[i] ? cpu_to_be32(a->d[i]) : 0;
#या_अगर BYTES_PER_MPI_LIMB == 8
		alimb = a->d[i] ? cpu_to_be64(a->d[i]) : 0;
#अन्यथा
#त्रुटि please implement क्रम this limb size.
#पूर्ण_अगर
		p = (u8 *)&alimb;

		क्रम (x = 0; x < माप(alimb); x++) अणु
			*p2++ = *p++;
			अगर (!--buf_len) अणु
				sg_miter_next(&miter);
				buf_len = miter.length;
				p2 = miter.addr;
			पूर्ण
		पूर्ण
	पूर्ण

	sg_miter_stop(&miter);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_ग_लिखो_to_sgl);

/*
 * mpi_पढ़ो_raw_from_sgl() - Function allocates an MPI and populates it with
 *			     data from the sgl
 *
 * This function works in the same way as the mpi_पढ़ो_raw_data, but it
 * takes an sgl instead of व्योम * buffer. i.e. it allocates
 * a new MPI and पढ़ोs the content of the sgl to the MPI.
 *
 * @sgl:	scatterlist to पढ़ो from
 * @nbytes:	number of bytes to पढ़ो
 *
 * Return:	Poपूर्णांकer to a new MPI or शून्य on error
 */
MPI mpi_पढ़ो_raw_from_sgl(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nbytes)
अणु
	काष्ठा sg_mapping_iter miter;
	अचिन्हित पूर्णांक nbits, nlimbs;
	पूर्णांक x, j, z, lzeros, ents;
	अचिन्हित पूर्णांक len;
	स्थिर u8 *buff;
	mpi_limb_t a;
	MPI val = शून्य;

	ents = sg_nents_क्रम_len(sgl, nbytes);
	अगर (ents < 0)
		वापस शून्य;

	sg_miter_start(&miter, sgl, ents, SG_MITER_ATOMIC | SG_MITER_FROM_SG);

	lzeros = 0;
	len = 0;
	जबतक (nbytes > 0) अणु
		जबतक (len && !*buff) अणु
			lzeros++;
			len--;
			buff++;
		पूर्ण

		अगर (len && *buff)
			अवरोध;

		sg_miter_next(&miter);
		buff = miter.addr;
		len = miter.length;

		nbytes -= lzeros;
		lzeros = 0;
	पूर्ण

	miter.consumed = lzeros;

	nbytes -= lzeros;
	nbits = nbytes * 8;
	अगर (nbits > MAX_EXTERN_MPI_BITS) अणु
		sg_miter_stop(&miter);
		pr_info("MPI: mpi too large (%u bits)\n", nbits);
		वापस शून्य;
	पूर्ण

	अगर (nbytes > 0)
		nbits -= count_leading_zeros(*buff) - (BITS_PER_LONG - 8);

	sg_miter_stop(&miter);

	nlimbs = DIV_ROUND_UP(nbytes, BYTES_PER_MPI_LIMB);
	val = mpi_alloc(nlimbs);
	अगर (!val)
		वापस शून्य;

	val->nbits = nbits;
	val->sign = 0;
	val->nlimbs = nlimbs;

	अगर (nbytes == 0)
		वापस val;

	j = nlimbs - 1;
	a = 0;
	z = BYTES_PER_MPI_LIMB - nbytes % BYTES_PER_MPI_LIMB;
	z %= BYTES_PER_MPI_LIMB;

	जबतक (sg_miter_next(&miter)) अणु
		buff = miter.addr;
		len = miter.length;

		क्रम (x = 0; x < len; x++) अणु
			a <<= 8;
			a |= *buff++;
			अगर (((z + x + 1) % BYTES_PER_MPI_LIMB) == 0) अणु
				val->d[j--] = a;
				a = 0;
			पूर्ण
		पूर्ण
		z += x;
	पूर्ण

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_पढ़ो_raw_from_sgl);

/* Perक्रमm a two's complement operation on buffer P of size N bytes.  */
अटल व्योम twocompl(अचिन्हित अक्षर *p, अचिन्हित पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = n-1; i >= 0 && !p[i]; i--)
		;
	अगर (i >= 0) अणु
		अगर ((p[i] & 0x01))
			p[i] = (((p[i] ^ 0xfe) | 0x01) & 0xff);
		अन्यथा अगर ((p[i] & 0x02))
			p[i] = (((p[i] ^ 0xfc) | 0x02) & 0xfe);
		अन्यथा अगर ((p[i] & 0x04))
			p[i] = (((p[i] ^ 0xf8) | 0x04) & 0xfc);
		अन्यथा अगर ((p[i] & 0x08))
			p[i] = (((p[i] ^ 0xf0) | 0x08) & 0xf8);
		अन्यथा अगर ((p[i] & 0x10))
			p[i] = (((p[i] ^ 0xe0) | 0x10) & 0xf0);
		अन्यथा अगर ((p[i] & 0x20))
			p[i] = (((p[i] ^ 0xc0) | 0x20) & 0xe0);
		अन्यथा अगर ((p[i] & 0x40))
			p[i] = (((p[i] ^ 0x80) | 0x40) & 0xc0);
		अन्यथा
			p[i] = 0x80;

		क्रम (i--; i >= 0; i--)
			p[i] ^= 0xff;
	पूर्ण
पूर्ण

पूर्णांक mpi_prपूर्णांक(क्रमागत gcry_mpi_क्रमmat क्रमmat, अचिन्हित अक्षर *buffer,
			माप_प्रकार buflen, माप_प्रकार *nwritten, MPI a)
अणु
	अचिन्हित पूर्णांक nbits = mpi_get_nbits(a);
	माप_प्रकार len;
	माप_प्रकार dummy_nwritten;
	पूर्णांक negative;

	अगर (!nwritten)
		nwritten = &dummy_nwritten;

	/* Libgcrypt करोes no always care to set clear the sign अगर the value
	 * is 0.  For prपूर्णांकing this is a bit of a surprise, in particular
	 * because अगर some of the क्रमmats करोn't support negative numbers but
	 * should be able to prपूर्णांक a zero.  Thus we need this extra test
	 * क्रम a negative number.
	 */
	अगर (a->sign && mpi_cmp_ui(a, 0))
		negative = 1;
	अन्यथा
		negative = 0;

	len = buflen;
	*nwritten = 0;
	अगर (क्रमmat == GCRYMPI_FMT_STD) अणु
		अचिन्हित अक्षर *पंचांगp;
		पूर्णांक extra = 0;
		अचिन्हित पूर्णांक n;

		पंचांगp = mpi_get_buffer(a, &n, शून्य);
		अगर (!पंचांगp)
			वापस -EINVAL;

		अगर (negative) अणु
			twocompl(पंचांगp, n);
			अगर (!(*पंचांगp & 0x80)) अणु
				/* Need to extend the sign.  */
				n++;
				extra = 2;
			पूर्ण
		पूर्ण अन्यथा अगर (n && (*पंचांगp & 0x80)) अणु
			/* Positive but the high bit of the वापसed buffer is set.
			 * Thus we need to prपूर्णांक an extra leading 0x00 so that the
			 * output is पूर्णांकerpreted as a positive number.
			 */
			n++;
			extra = 1;
		पूर्ण

		अगर (buffer && n > len) अणु
			/* The provided buffer is too लघु. */
			kमुक्त(पंचांगp);
			वापस -E2BIG;
		पूर्ण
		अगर (buffer) अणु
			अचिन्हित अक्षर *s = buffer;

			अगर (extra == 1)
				*s++ = 0;
			अन्यथा अगर (extra)
				*s++ = 0xff;
			स_नकल(s, पंचांगp, n-!!extra);
		पूर्ण
		kमुक्त(पंचांगp);
		*nwritten = n;
		वापस 0;
	पूर्ण अन्यथा अगर (क्रमmat == GCRYMPI_FMT_USG) अणु
		अचिन्हित पूर्णांक n = (nbits + 7)/8;

		/* Note:  We ignore the sign क्रम this क्रमmat.  */
		/* FIXME: क्रम perक्रमmance reasons we should put this पूर्णांकo
		 * mpi_aprपूर्णांक because we can then use the buffer directly.
		 */

		अगर (buffer && n > len)
			वापस -E2BIG;
		अगर (buffer) अणु
			अचिन्हित अक्षर *पंचांगp;

			पंचांगp = mpi_get_buffer(a, &n, शून्य);
			अगर (!पंचांगp)
				वापस -EINVAL;
			स_नकल(buffer, पंचांगp, n);
			kमुक्त(पंचांगp);
		पूर्ण
		*nwritten = n;
		वापस 0;
	पूर्ण अन्यथा अगर (क्रमmat == GCRYMPI_FMT_PGP) अणु
		अचिन्हित पूर्णांक n = (nbits + 7)/8;

		/* The PGP क्रमmat can only handle अचिन्हित पूर्णांकegers.  */
		अगर (negative)
			वापस -EINVAL;

		अगर (buffer && n+2 > len)
			वापस -E2BIG;

		अगर (buffer) अणु
			अचिन्हित अक्षर *पंचांगp;
			अचिन्हित अक्षर *s = buffer;

			s[0] = nbits >> 8;
			s[1] = nbits;

			पंचांगp = mpi_get_buffer(a, &n, शून्य);
			अगर (!पंचांगp)
				वापस -EINVAL;
			स_नकल(s+2, पंचांगp, n);
			kमुक्त(पंचांगp);
		पूर्ण
		*nwritten = n+2;
		वापस 0;
	पूर्ण अन्यथा अगर (क्रमmat == GCRYMPI_FMT_SSH) अणु
		अचिन्हित अक्षर *पंचांगp;
		पूर्णांक extra = 0;
		अचिन्हित पूर्णांक n;

		पंचांगp = mpi_get_buffer(a, &n, शून्य);
		अगर (!पंचांगp)
			वापस -EINVAL;

		अगर (negative) अणु
			twocompl(पंचांगp, n);
			अगर (!(*पंचांगp & 0x80)) अणु
				/* Need to extend the sign.  */
				n++;
				extra = 2;
			पूर्ण
		पूर्ण अन्यथा अगर (n && (*पंचांगp & 0x80)) अणु
			n++;
			extra = 1;
		पूर्ण

		अगर (buffer && n+4 > len) अणु
			kमुक्त(पंचांगp);
			वापस -E2BIG;
		पूर्ण

		अगर (buffer) अणु
			अचिन्हित अक्षर *s = buffer;

			*s++ = n >> 24;
			*s++ = n >> 16;
			*s++ = n >> 8;
			*s++ = n;
			अगर (extra == 1)
				*s++ = 0;
			अन्यथा अगर (extra)
				*s++ = 0xff;
			स_नकल(s, पंचांगp, n-!!extra);
		पूर्ण
		kमुक्त(पंचांगp);
		*nwritten = 4+n;
		वापस 0;
	पूर्ण अन्यथा अगर (क्रमmat == GCRYMPI_FMT_HEX) अणु
		अचिन्हित अक्षर *पंचांगp;
		पूर्णांक i;
		पूर्णांक extra = 0;
		अचिन्हित पूर्णांक n = 0;

		पंचांगp = mpi_get_buffer(a, &n, शून्य);
		अगर (!पंचांगp)
			वापस -EINVAL;
		अगर (!n || (*पंचांगp & 0x80))
			extra = 2;

		अगर (buffer && 2*n + extra + negative + 1 > len) अणु
			kमुक्त(पंचांगp);
			वापस -E2BIG;
		पूर्ण
		अगर (buffer) अणु
			अचिन्हित अक्षर *s = buffer;

			अगर (negative)
				*s++ = '-';
			अगर (extra) अणु
				*s++ = '0';
				*s++ = '0';
			पूर्ण

			क्रम (i = 0; i < n; i++) अणु
				अचिन्हित पूर्णांक c = पंचांगp[i];

				*s++ = (c >> 4) < 10 ? '0'+(c>>4) : 'A'+(c>>4)-10;
				c &= 15;
				*s++ = c < 10 ? '0'+c : 'A'+c-10;
			पूर्ण
			*s++ = 0;
			*nwritten = s - buffer;
		पूर्ण अन्यथा अणु
			*nwritten = 2*n + extra + negative + 1;
		पूर्ण
		kमुक्त(पंचांगp);
		वापस 0;
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_prपूर्णांक);
