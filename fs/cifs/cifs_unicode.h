<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * cअगरs_unicode:  Unicode kernel हाल support
 *
 * Function:
 *     Convert a unicode अक्षरacter to upper or lower हाल using
 *     compressed tables.
 *
 *   Copyright (c) International Business Machines  Corp., 2000,2009
 *
 * Notes:
 *     These APIs are based on the C library functions.  The semantics
 *     should match the C functions but with expanded size opeअक्रमs.
 *
 *     The upper/lower functions are based on a table created by mkupr.
 *     This is a compressed table of upper and lower हाल conversion.
 */
#अगर_अघोषित _CIFS_UNICODE_H
#घोषणा _CIFS_UNICODE_H

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/types.h>
#समावेश <linux/nls.h>

#घोषणा  UNIUPR_NOLOWER		/* Example to not expand lower हाल tables */

/*
 * Winकरोws maps these to the user defined 16 bit Unicode range since they are
 * reserved symbols (aदीर्घ with \ and /), otherwise illegal to store
 * in filenames in NTFS
 */
#घोषणा UNI_ASTERISK    (__u16) ('*' + 0xF000)
#घोषणा UNI_QUESTION    (__u16) ('?' + 0xF000)
#घोषणा UNI_COLON       (__u16) (':' + 0xF000)
#घोषणा UNI_GRTRTHAN    (__u16) ('>' + 0xF000)
#घोषणा UNI_LESSTHAN    (__u16) ('<' + 0xF000)
#घोषणा UNI_PIPE        (__u16) ('|' + 0xF000)
#घोषणा UNI_SLASH       (__u16) ('\\' + 0xF000)

/*
 * Macs use an older "SFM" mapping of the symbols above. Fortunately it करोes
 * not conflict (although almost करोes) with the mapping above.
 */

#घोषणा SFM_DOUBLEQUOTE ((__u16) 0xF020)
#घोषणा SFM_ASTERISK    ((__u16) 0xF021)
#घोषणा SFM_QUESTION    ((__u16) 0xF025)
#घोषणा SFM_COLON       ((__u16) 0xF022)
#घोषणा SFM_GRTRTHAN    ((__u16) 0xF024)
#घोषणा SFM_LESSTHAN    ((__u16) 0xF023)
#घोषणा SFM_PIPE        ((__u16) 0xF027)
#घोषणा SFM_SLASH       ((__u16) 0xF026)
#घोषणा SFM_SPACE	((__u16) 0xF028)
#घोषणा SFM_PERIOD	((__u16) 0xF029)

/*
 * Mapping mechanism to use when one of the seven reserved अक्षरacters is
 * encountered.  We can only map using one of the mechanisms at a समय
 * since otherwise सूची_पढ़ो could वापस directory entries which we would
 * not be able to खोलो
 *
 * NO_MAP_UNI_RSVD  = करो not perक्रमm any remapping of the अक्षरacter
 * SFM_MAP_UNI_RSVD = map reserved अक्षरacters using SFM scheme (MAC compatible)
 * SFU_MAP_UNI_RSVD = map reserved अक्षरacters ala SFU ("mapchars" option)
 *
 */
#घोषणा NO_MAP_UNI_RSVD		0
#घोषणा SFM_MAP_UNI_RSVD	1
#घोषणा SFU_MAP_UNI_RSVD	2

/* Just define what we want from uniupr.h.  We करोn't want to define the tables
 * in each source file.
 */
#अगर_अघोषित	UNICASदुस्फल_DEFINED
काष्ठा UniCaseRange अणु
	ब_अक्षर_प्रकार start;
	ब_अक्षर_प्रकार end;
	चिन्हित अक्षर *table;
पूर्ण;
#पूर्ण_अगर				/* UNICASदुस्फल_DEFINED */

#अगर_अघोषित UNIUPR_NOUPPER
बाह्य चिन्हित अक्षर CअगरsUniUpperTable[512];
बाह्य स्थिर काष्ठा UniCaseRange CअगरsUniUpperRange[];
#पूर्ण_अगर				/* UNIUPR_NOUPPER */

#अगर_अघोषित UNIUPR_NOLOWER
बाह्य चिन्हित अक्षर CअगरsUniLowerTable[512];
बाह्य स्थिर काष्ठा UniCaseRange CअगरsUniLowerRange[];
#पूर्ण_अगर				/* UNIUPR_NOLOWER */

#अगर_घोषित __KERNEL__
पूर्णांक cअगरs_from_utf16(अक्षर *to, स्थिर __le16 *from, पूर्णांक tolen, पूर्णांक fromlen,
		    स्थिर काष्ठा nls_table *cp, पूर्णांक map_type);
पूर्णांक cअगरs_utf16_bytes(स्थिर __le16 *from, पूर्णांक maxbytes,
		     स्थिर काष्ठा nls_table *codepage);
पूर्णांक cअगरs_strtoUTF16(__le16 *, स्थिर अक्षर *, पूर्णांक, स्थिर काष्ठा nls_table *);
अक्षर *cअगरs_strndup_from_utf16(स्थिर अक्षर *src, स्थिर पूर्णांक maxlen,
			      स्थिर bool is_unicode,
			      स्थिर काष्ठा nls_table *codepage);
बाह्य पूर्णांक cअगरsConvertToUTF16(__le16 *target, स्थिर अक्षर *source, पूर्णांक maxlen,
			      स्थिर काष्ठा nls_table *cp, पूर्णांक mapChars);
बाह्य पूर्णांक cअगरs_remap(काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य __le16 *cअगरs_strndup_to_utf16(स्थिर अक्षर *src, स्थिर पूर्णांक maxlen,
				     पूर्णांक *utf16_len, स्थिर काष्ठा nls_table *cp,
				     पूर्णांक remap);
#पूर्ण_अगर

ब_अक्षर_प्रकार cअगरs_बड़े(ब_अक्षर_प्रकार in);

/*
 * UniStrcat:  Concatenate the second string to the first
 *
 * Returns:
 *     Address of the first string
 */
अटल अंतरभूत __le16 *
UniStrcat(__le16 *ucs1, स्थिर __le16 *ucs2)
अणु
	__le16 *anchor = ucs1;	/* save a poपूर्णांकer to start of ucs1 */

	जबतक (*ucs1++) ;	/* To end of first string */
	ucs1--;			/* Return to the null */
	जबतक ((*ucs1++ = *ucs2++)) ;	/* copy string 2 over */
	वापस anchor;
पूर्ण

/*
 * UniStrchr:  Find a अक्षरacter in a string
 *
 * Returns:
 *     Address of first occurrence of अक्षरacter in string
 *     or शून्य अगर the अक्षरacter is not in the string
 */
अटल अंतरभूत ब_अक्षर_प्रकार *
UniStrchr(स्थिर ब_अक्षर_प्रकार *ucs, ब_अक्षर_प्रकार uc)
अणु
	जबतक ((*ucs != uc) && *ucs)
		ucs++;

	अगर (*ucs == uc)
		वापस (ब_अक्षर_प्रकार *) ucs;
	वापस शून्य;
पूर्ण

/*
 * UniStrcmp:  Compare two strings
 *
 * Returns:
 *     < 0:  First string is less than second
 *     = 0:  Strings are equal
 *     > 0:  First string is greater than second
 */
अटल अंतरभूत पूर्णांक
UniStrcmp(स्थिर ब_अक्षर_प्रकार *ucs1, स्थिर ब_अक्षर_प्रकार *ucs2)
अणु
	जबतक ((*ucs1 == *ucs2) && *ucs1) अणु
		ucs1++;
		ucs2++;
	पूर्ण
	वापस (पूर्णांक) *ucs1 - (पूर्णांक) *ucs2;
पूर्ण

/*
 * UniStrcpy:  Copy a string
 */
अटल अंतरभूत ब_अक्षर_प्रकार *
UniStrcpy(ब_अक्षर_प्रकार *ucs1, स्थिर ब_अक्षर_प्रकार *ucs2)
अणु
	ब_अक्षर_प्रकार *anchor = ucs1;	/* save the start of result string */

	जबतक ((*ucs1++ = *ucs2++)) ;
	वापस anchor;
पूर्ण

/*
 * UniStrlen:  Return the length of a string (in 16 bit Unicode अक्षरs not bytes)
 */
अटल अंतरभूत माप_प्रकार
UniStrlen(स्थिर ब_अक्षर_प्रकार *ucs1)
अणु
	पूर्णांक i = 0;

	जबतक (*ucs1++)
		i++;
	वापस i;
पूर्ण

/*
 * UniStrnlen:  Return the length (in 16 bit Unicode अक्षरs not bytes) of a
 *		string (length limited)
 */
अटल अंतरभूत माप_प्रकार
UniStrnlen(स्थिर ब_अक्षर_प्रकार *ucs1, पूर्णांक maxlen)
अणु
	पूर्णांक i = 0;

	जबतक (*ucs1++) अणु
		i++;
		अगर (i >= maxlen)
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

/*
 * UniStrncat:  Concatenate length limited string
 */
अटल अंतरभूत ब_अक्षर_प्रकार *
UniStrncat(ब_अक्षर_प्रकार *ucs1, स्थिर ब_अक्षर_प्रकार *ucs2, माप_प्रकार n)
अणु
	ब_अक्षर_प्रकार *anchor = ucs1;	/* save poपूर्णांकer to string 1 */

	जबतक (*ucs1++) ;
	ucs1--;			/* poपूर्णांक to null terminator of s1 */
	जबतक (n-- && (*ucs1 = *ucs2)) अणु	/* copy s2 after s1 */
		ucs1++;
		ucs2++;
	पूर्ण
	*ucs1 = 0;		/* Null terminate the result */
	वापस (anchor);
पूर्ण

/*
 * UniStrncmp:  Compare length limited string
 */
अटल अंतरभूत पूर्णांक
UniStrncmp(स्थिर ब_अक्षर_प्रकार *ucs1, स्थिर ब_अक्षर_प्रकार *ucs2, माप_प्रकार n)
अणु
	अगर (!n)
		वापस 0;	/* Null strings are equal */
	जबतक ((*ucs1 == *ucs2) && *ucs1 && --n) अणु
		ucs1++;
		ucs2++;
	पूर्ण
	वापस (पूर्णांक) *ucs1 - (पूर्णांक) *ucs2;
पूर्ण

/*
 * UniStrncmp_le:  Compare length limited string - native to little-endian
 */
अटल अंतरभूत पूर्णांक
UniStrncmp_le(स्थिर ब_अक्षर_प्रकार *ucs1, स्थिर ब_अक्षर_प्रकार *ucs2, माप_प्रकार n)
अणु
	अगर (!n)
		वापस 0;	/* Null strings are equal */
	जबतक ((*ucs1 == __le16_to_cpu(*ucs2)) && *ucs1 && --n) अणु
		ucs1++;
		ucs2++;
	पूर्ण
	वापस (पूर्णांक) *ucs1 - (पूर्णांक) __le16_to_cpu(*ucs2);
पूर्ण

/*
 * UniStrncpy:  Copy length limited string with pad
 */
अटल अंतरभूत ब_अक्षर_प्रकार *
UniStrncpy(ब_अक्षर_प्रकार *ucs1, स्थिर ब_अक्षर_प्रकार *ucs2, माप_प्रकार n)
अणु
	ब_अक्षर_प्रकार *anchor = ucs1;

	जबतक (n-- && *ucs2)	/* Copy the strings */
		*ucs1++ = *ucs2++;

	n++;
	जबतक (n--)		/* Pad with nulls */
		*ucs1++ = 0;
	वापस anchor;
पूर्ण

/*
 * UniStrncpy_le:  Copy length limited string with pad to little-endian
 */
अटल अंतरभूत ब_अक्षर_प्रकार *
UniStrncpy_le(ब_अक्षर_प्रकार *ucs1, स्थिर ब_अक्षर_प्रकार *ucs2, माप_प्रकार n)
अणु
	ब_अक्षर_प्रकार *anchor = ucs1;

	जबतक (n-- && *ucs2)	/* Copy the strings */
		*ucs1++ = __le16_to_cpu(*ucs2++);

	n++;
	जबतक (n--)		/* Pad with nulls */
		*ucs1++ = 0;
	वापस anchor;
पूर्ण

/*
 * UniStrstr:  Find a string in a string
 *
 * Returns:
 *     Address of first match found
 *     शून्य अगर no matching string is found
 */
अटल अंतरभूत ब_अक्षर_प्रकार *
UniStrstr(स्थिर ब_अक्षर_प्रकार *ucs1, स्थिर ब_अक्षर_प्रकार *ucs2)
अणु
	स्थिर ब_अक्षर_प्रकार *anchor1 = ucs1;
	स्थिर ब_अक्षर_प्रकार *anchor2 = ucs2;

	जबतक (*ucs1) अणु
		अगर (*ucs1 == *ucs2) अणु
			/* Partial match found */
			ucs1++;
			ucs2++;
		पूर्ण अन्यथा अणु
			अगर (!*ucs2)	/* Match found */
				वापस (ब_अक्षर_प्रकार *) anchor1;
			ucs1 = ++anchor1;	/* No match */
			ucs2 = anchor2;
		पूर्ण
	पूर्ण

	अगर (!*ucs2)		/* Both end together */
		वापस (ब_अक्षर_प्रकार *) anchor1;	/* Match found */
	वापस शून्य;		/* No match */
पूर्ण

#अगर_अघोषित UNIUPR_NOUPPER
/*
 * UniToupper:  Convert a unicode अक्षरacter to upper हाल
 */
अटल अंतरभूत ब_अक्षर_प्रकार
UniToupper(रेजिस्टर ब_अक्षर_प्रकार uc)
अणु
	रेजिस्टर स्थिर काष्ठा UniCaseRange *rp;

	अगर (uc < माप(CअगरsUniUpperTable)) अणु
		/* Latin अक्षरacters */
		वापस uc + CअगरsUniUpperTable[uc];	/* Use base tables */
	पूर्ण अन्यथा अणु
		rp = CअगरsUniUpperRange;	/* Use range tables */
		जबतक (rp->start) अणु
			अगर (uc < rp->start)	/* Beक्रमe start of range */
				वापस uc;	/* Upperहाल = input */
			अगर (uc <= rp->end)	/* In range */
				वापस uc + rp->table[uc - rp->start];
			rp++;	/* Try next range */
		पूर्ण
	पूर्ण
	वापस uc;		/* Past last range */
पूर्ण

/*
 * UniStrupr:  Upper हाल a unicode string
 */
अटल अंतरभूत __le16 *
UniStrupr(रेजिस्टर __le16 *upin)
अणु
	रेजिस्टर __le16 *up;

	up = upin;
	जबतक (*up) अणु		/* For all अक्षरacters */
		*up = cpu_to_le16(UniToupper(le16_to_cpu(*up)));
		up++;
	पूर्ण
	वापस upin;		/* Return input poपूर्णांकer */
पूर्ण
#पूर्ण_अगर				/* UNIUPR_NOUPPER */

#अगर_अघोषित UNIUPR_NOLOWER
/*
 * UniTolower:  Convert a unicode अक्षरacter to lower हाल
 */
अटल अंतरभूत ब_अक्षर_प्रकार
UniTolower(रेजिस्टर ब_अक्षर_प्रकार uc)
अणु
	रेजिस्टर स्थिर काष्ठा UniCaseRange *rp;

	अगर (uc < माप(CअगरsUniLowerTable)) अणु
		/* Latin अक्षरacters */
		वापस uc + CअगरsUniLowerTable[uc];	/* Use base tables */
	पूर्ण अन्यथा अणु
		rp = CअगरsUniLowerRange;	/* Use range tables */
		जबतक (rp->start) अणु
			अगर (uc < rp->start)	/* Beक्रमe start of range */
				वापस uc;	/* Upperहाल = input */
			अगर (uc <= rp->end)	/* In range */
				वापस uc + rp->table[uc - rp->start];
			rp++;	/* Try next range */
		पूर्ण
	पूर्ण
	वापस uc;		/* Past last range */
पूर्ण

/*
 * UniStrlwr:  Lower हाल a unicode string
 */
अटल अंतरभूत ब_अक्षर_प्रकार *
UniStrlwr(रेजिस्टर ब_अक्षर_प्रकार *upin)
अणु
	रेजिस्टर ब_अक्षर_प्रकार *up;

	up = upin;
	जबतक (*up) अणु		/* For all अक्षरacters */
		*up = UniTolower(*up);
		up++;
	पूर्ण
	वापस upin;		/* Return input poपूर्णांकer */
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _CIFS_UNICODE_H */
