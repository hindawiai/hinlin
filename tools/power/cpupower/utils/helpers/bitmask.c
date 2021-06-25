<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <helpers/biपंचांगask.h>

/* How many bits in an अचिन्हित दीर्घ */
#घोषणा bitsperदीर्घ (8 * माप(अचिन्हित दीर्घ))

/* howmany(a,b) : how many elements of size b needed to hold all of a */
#घोषणा howmany(x, y) (((x)+((y)-1))/(y))

/* How many दीर्घs in mask of n bits */
#घोषणा दीर्घsperbits(n) howmany(n, bitsperदीर्घ)

#घोषणा max(a, b) ((a) > (b) ? (a) : (b))

/*
 * Allocate and मुक्त `काष्ठा biपंचांगask *`
 */

/* Allocate a new `काष्ठा biपंचांगask` with a size of n bits */
काष्ठा biपंचांगask *biपंचांगask_alloc(अचिन्हित पूर्णांक n)
अणु
	काष्ठा biपंचांगask *bmp;

	bmp = दो_स्मृति(माप(*bmp));
	अगर (!bmp)
		वापस 0;
	bmp->size = n;
	bmp->maskp = सुस्मृति(दीर्घsperbits(n), माप(अचिन्हित दीर्घ));
	अगर (!bmp->maskp) अणु
		मुक्त(bmp);
		वापस 0;
	पूर्ण
	वापस bmp;
पूर्ण

/* Free `काष्ठा biपंचांगask` */
व्योम biपंचांगask_मुक्त(काष्ठा biपंचांगask *bmp)
अणु
	अगर (!bmp)
		वापस;
	मुक्त(bmp->maskp);
	bmp->maskp = (अचिन्हित दीर्घ *)0xdeadcdef;  /* द्विगुन मुक्त tripwire */
	मुक्त(bmp);
पूर्ण

/*
 * The routines _getbit() and _setbit() are the only
 * routines that actually understand the layout of bmp->maskp[].
 *
 * On little endian architectures, this could simply be an array of
 * bytes.  But the kernel layout of biपंचांगasks _is_ visible to userspace
 * via the sched_(set/get)affinity calls in Linux 2.6, and on big
 * endian architectures, it is painfully obvious that this is an
 * array of अचिन्हित दीर्घs.
 */

/* Return the value (0 or 1) of bit n in biपंचांगask bmp */
अटल अचिन्हित पूर्णांक _getbit(स्थिर काष्ठा biपंचांगask *bmp, अचिन्हित पूर्णांक n)
अणु
	अगर (n < bmp->size)
		वापस (bmp->maskp[n/bitsperदीर्घ] >> (n % bitsperदीर्घ)) & 1;
	अन्यथा
		वापस 0;
पूर्ण

/* Set bit n in biपंचांगask bmp to value v (0 or 1) */
अटल व्योम _setbit(काष्ठा biपंचांगask *bmp, अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक v)
अणु
	अगर (n < bmp->size) अणु
		अगर (v)
			bmp->maskp[n/bitsperदीर्घ] |= 1UL << (n % bitsperदीर्घ);
		अन्यथा
			bmp->maskp[n/bitsperदीर्घ] &=
				~(1UL << (n % bitsperदीर्घ));
	पूर्ण
पूर्ण

/*
 * When parsing biपंचांगask lists, only allow numbers, separated by one
 * of the allowed next अक्षरacters.
 *
 * The parameter 'sret' is the वापस from a माला_पूछो "%u%c".  It is
 * -1 अगर the माला_पूछो input string was empty.  It is 0 अगर the first
 * अक्षरacter in the माला_पूछो input string was not a decimal number.
 * It is 1 अगर the अचिन्हित number matching the "%u" was the end of the
 * input string.  It is 2 अगर one or more additional अक्षरacters followed
 * the matched अचिन्हित number.  If it is 2, then 'nextc' is the first
 * अक्षरacter following the number.  The parameter 'ok_next_chars'
 * is the nul-terminated list of allowed next अक्षरacters.
 *
 * The mask term just scanned was ok अगर and only अगर either the numbers
 * matching the %u were all of the input or अगर the next अक्षरacter in
 * the input past the numbers was one of the allowed next अक्षरacters.
 */
अटल पूर्णांक scan_was_ok(पूर्णांक sret, अक्षर nextc, स्थिर अक्षर *ok_next_अक्षरs)
अणु
	वापस sret == 1 ||
		(sret == 2 && म_अक्षर(ok_next_अक्षरs, nextc) != शून्य);
पूर्ण

अटल स्थिर अक्षर *nexttoken(स्थिर अक्षर *q,  पूर्णांक sep)
अणु
	अगर (q)
		q = म_अक्षर(q, sep);
	अगर (q)
		q++;
	वापस q;
पूर्ण

/* Set a single bit i in biपंचांगask */
काष्ठा biपंचांगask *biपंचांगask_setbit(काष्ठा biपंचांगask *bmp, अचिन्हित पूर्णांक i)
अणु
	_setbit(bmp, i, 1);
	वापस bmp;
पूर्ण

/* Set all bits in biपंचांगask: bmp = ~0 */
काष्ठा biपंचांगask *biपंचांगask_setall(काष्ठा biपंचांगask *bmp)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < bmp->size; i++)
		_setbit(bmp, i, 1);
	वापस bmp;
पूर्ण

/* Clear all bits in biपंचांगask: bmp = 0 */
काष्ठा biपंचांगask *biपंचांगask_clearall(काष्ठा biपंचांगask *bmp)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < bmp->size; i++)
		_setbit(bmp, i, 0);
	वापस bmp;
पूर्ण

/* True अगर all bits are clear */
पूर्णांक biपंचांगask_isallclear(स्थिर काष्ठा biपंचांगask *bmp)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < bmp->size; i++)
		अगर (_getbit(bmp, i))
			वापस 0;
	वापस 1;
पूर्ण

/* True अगर specअगरied bit i is set */
पूर्णांक biपंचांगask_isbitset(स्थिर काष्ठा biपंचांगask *bmp, अचिन्हित पूर्णांक i)
अणु
	वापस _getbit(bmp, i);
पूर्ण

/* Number of lowest set bit (min) */
अचिन्हित पूर्णांक biपंचांगask_first(स्थिर काष्ठा biपंचांगask *bmp)
अणु
	वापस biपंचांगask_next(bmp, 0);
पूर्ण

/* Number of highest set bit (max) */
अचिन्हित पूर्णांक biपंचांगask_last(स्थिर काष्ठा biपंचांगask *bmp)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक m = bmp->size;
	क्रम (i = 0; i < bmp->size; i++)
		अगर (_getbit(bmp, i))
			m = i;
	वापस m;
पूर्ण

/* Number of next set bit at or above given bit i */
अचिन्हित पूर्णांक biपंचांगask_next(स्थिर काष्ठा biपंचांगask *bmp, अचिन्हित पूर्णांक i)
अणु
	अचिन्हित पूर्णांक n;
	क्रम (n = i; n < bmp->size; n++)
		अगर (_getbit(bmp, n))
			अवरोध;
	वापस n;
पूर्ण

/*
 * Parses a comma-separated list of numbers and ranges of numbers,
 * with optional ':%u' strides modअगरying ranges, पूर्णांकo provided biपंचांगask.
 * Some examples of input lists and their equivalent simple list:
 *	Input		Equivalent to
 *	0-3		0,1,2,3
 *	0-7:2		0,2,4,6
 *	1,3,5-7		1,3,5,6,7
 *	0-3:2,8-15:4	0,2,8,12
 */
पूर्णांक biपंचांगask_parselist(स्थिर अक्षर *buf, काष्ठा biपंचांगask *bmp)
अणु
	स्थिर अक्षर *p, *q;

	biपंचांगask_clearall(bmp);

	q = buf;
	जबतक (p = q, q = nexttoken(q, ','), p) अणु
		अचिन्हित पूर्णांक a;		/* begin of range */
		अचिन्हित पूर्णांक b;		/* end of range */
		अचिन्हित पूर्णांक s;		/* stride */
		स्थिर अक्षर *c1, *c2;	/* next tokens after '-' or ',' */
		अक्षर nextc;		/* अक्षर after माला_पूछो %u match */
		पूर्णांक sret;		/* माला_पूछो वापस (number of matches) */

		sret = माला_पूछो(p, "%u%c", &a, &nextc);
		अगर (!scan_was_ok(sret, nextc, ",-"))
			जाओ err;
		b = a;
		s = 1;
		c1 = nexttoken(p, '-');
		c2 = nexttoken(p, ',');
		अगर (c1 != शून्य && (c2 == शून्य || c1 < c2)) अणु
			sret = माला_पूछो(c1, "%u%c", &b, &nextc);
			अगर (!scan_was_ok(sret, nextc, ",:"))
				जाओ err;
			c1 = nexttoken(c1, ':');
			अगर (c1 != शून्य && (c2 == शून्य || c1 < c2)) अणु
				sret = माला_पूछो(c1, "%u%c", &s, &nextc);
				अगर (!scan_was_ok(sret, nextc, ","))
					जाओ err;
			पूर्ण
		पूर्ण
		अगर (!(a <= b))
			जाओ err;
		अगर (b >= bmp->size)
			जाओ err;
		जबतक (a <= b) अणु
			_setbit(bmp, a, 1);
			a += s;
		पूर्ण
	पूर्ण
	वापस 0;
err:
	biपंचांगask_clearall(bmp);
	वापस -1;
पूर्ण

/*
 * emit(buf, buflen, rbot, rtop, len)
 *
 * Helper routine क्रम biपंचांगask_displaylist().  Write decimal number
 * or range to buf+len, suppressing output past buf+buflen, with optional
 * comma-prefix.  Return len of what would be written to buf, अगर it
 * all fit.
 */

अटल अंतरभूत पूर्णांक emit(अक्षर *buf, पूर्णांक buflen, पूर्णांक rbot, पूर्णांक rtop, पूर्णांक len)
अणु
	अगर (len > 0)
		len += snम_लिखो(buf + len, max(buflen - len, 0), ",");
	अगर (rbot == rtop)
		len += snम_लिखो(buf + len, max(buflen - len, 0), "%d", rbot);
	अन्यथा
		len += snम_लिखो(buf + len, max(buflen - len, 0), "%d-%d",
				rbot, rtop);
	वापस len;
पूर्ण

/*
 * Write decimal list representation of bmp to buf.
 *
 * Output क्रमmat is a comma-separated list of decimal numbers and
 * ranges.  Consecutively set bits are shown as two hyphen-separated
 * decimal numbers, the smallest and largest bit numbers set in
 * the range.  Output क्रमmat is compatible with the क्रमmat
 * accepted as input by biपंचांगap_parselist().
 *
 * The वापस value is the number of अक्षरacters which would be
 * generated क्रम the given input, excluding the trailing '\0', as
 * per ISO C99.
 */

पूर्णांक biपंचांगask_displaylist(अक्षर *buf, पूर्णांक buflen, स्थिर काष्ठा biपंचांगask *bmp)
अणु
	पूर्णांक len = 0;
	/* current bit is 'cur', most recently seen range is [rbot, rtop] */
	अचिन्हित पूर्णांक cur, rbot, rtop;

	अगर (buflen > 0)
		*buf = 0;
	rbot = cur = biपंचांगask_first(bmp);
	जबतक (cur < bmp->size) अणु
		rtop = cur;
		cur = biपंचांगask_next(bmp, cur+1);
		अगर (cur >= bmp->size || cur > rtop + 1) अणु
			len = emit(buf, buflen, rbot, rtop, len);
			rbot = cur;
		पूर्ण
	पूर्ण
	वापस len;
पूर्ण
