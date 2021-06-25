<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2002
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */
#अगर_अघोषित _H_JFS_UNICODE
#घोषणा _H_JFS_UNICODE

#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>
#समावेश "jfs_types.h"

प्रकार काष्ठा अणु
	ब_अक्षर_प्रकार start;
	ब_अक्षर_प्रकार end;
	चिन्हित अक्षर *table;
पूर्ण UNICASदुस्फल;

बाह्य चिन्हित अक्षर UniUpperTable[512];
बाह्य UNICASदुस्फल UniUpperRange[];
बाह्य पूर्णांक get_UCSname(काष्ठा component_name *, काष्ठा dentry *);
बाह्य पूर्णांक jfs_strfromUCS_le(अक्षर *, स्थिर __le16 *, पूर्णांक, काष्ठा nls_table *);

#घोषणा मुक्त_UCSname(COMP) kमुक्त((COMP)->name)

/*
 * UniStrcpy:  Copy a string
 */
अटल अंतरभूत ब_अक्षर_प्रकार *UniStrcpy(ब_अक्षर_प्रकार * ucs1, स्थिर ब_अक्षर_प्रकार * ucs2)
अणु
	ब_अक्षर_प्रकार *anchor = ucs1;	/* save the start of result string */

	जबतक ((*ucs1++ = *ucs2++));
	वापस anchor;
पूर्ण



/*
 * UniStrncpy:  Copy length limited string with pad
 */
अटल अंतरभूत __le16 *UniStrncpy_le(__le16 * ucs1, स्थिर __le16 * ucs2,
				  माप_प्रकार n)
अणु
	__le16 *anchor = ucs1;

	जबतक (n-- && *ucs2)	/* Copy the strings */
		*ucs1++ = *ucs2++;

	n++;
	जबतक (n--)		/* Pad with nulls */
		*ucs1++ = 0;
	वापस anchor;
पूर्ण

/*
 * UniStrncmp_le:  Compare length limited string - native to little-endian
 */
अटल अंतरभूत पूर्णांक UniStrncmp_le(स्थिर ब_अक्षर_प्रकार * ucs1, स्थिर __le16 * ucs2,
				माप_प्रकार n)
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
 * UniStrncpy_to_le:  Copy length limited string with pad to little-endian
 */
अटल अंतरभूत __le16 *UniStrncpy_to_le(__le16 * ucs1, स्थिर ब_अक्षर_प्रकार * ucs2,
				       माप_प्रकार n)
अणु
	__le16 *anchor = ucs1;

	जबतक (n-- && *ucs2)	/* Copy the strings */
		*ucs1++ = cpu_to_le16(*ucs2++);

	n++;
	जबतक (n--)		/* Pad with nulls */
		*ucs1++ = 0;
	वापस anchor;
पूर्ण

/*
 * UniStrncpy_from_le:  Copy length limited string with pad from little-endian
 */
अटल अंतरभूत ब_अक्षर_प्रकार *UniStrncpy_from_le(ब_अक्षर_प्रकार * ucs1, स्थिर __le16 * ucs2,
					  माप_प्रकार n)
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
 * UniToupper:  Convert a unicode अक्षरacter to upper हाल
 */
अटल अंतरभूत ब_अक्षर_प्रकार UniToupper(ब_अक्षर_प्रकार uc)
अणु
	UNICASदुस्फल *rp;

	अगर (uc < माप(UniUpperTable)) अणु	/* Latin अक्षरacters */
		वापस uc + UniUpperTable[uc];	/* Use base tables */
	पूर्ण अन्यथा अणु
		rp = UniUpperRange;	/* Use range tables */
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
अटल अंतरभूत ब_अक्षर_प्रकार *UniStrupr(ब_अक्षर_प्रकार * upin)
अणु
	ब_अक्षर_प्रकार *up;

	up = upin;
	जबतक (*up) अणु		/* For all अक्षरacters */
		*up = UniToupper(*up);
		up++;
	पूर्ण
	वापस upin;		/* Return input poपूर्णांकer */
पूर्ण

#पूर्ण_अगर				/* !_H_JFS_UNICODE */
