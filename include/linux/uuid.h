<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * UUID/GUID definition
 *
 * Copyright (C) 2010, 2016 Intel Corp.
 *	Huang Ying <ying.huang@पूर्णांकel.com>
 */
#अगर_अघोषित _LINUX_UUID_H_
#घोषणा _LINUX_UUID_H_

#समावेश <uapi/linux/uuid.h>
#समावेश <linux/माला.स>

#घोषणा UUID_SIZE 16

प्रकार काष्ठा अणु
	__u8 b[UUID_SIZE];
पूर्ण uuid_t;

#घोषणा UUID_INIT(a, b, c, d0, d1, d2, d3, d4, d5, d6, d7)			\
((uuid_t)								\
अणुअणु ((a) >> 24) & 0xff, ((a) >> 16) & 0xff, ((a) >> 8) & 0xff, (a) & 0xff, \
   ((b) >> 8) & 0xff, (b) & 0xff,					\
   ((c) >> 8) & 0xff, (c) & 0xff,					\
   (d0), (d1), (d2), (d3), (d4), (d5), (d6), (d7) पूर्णपूर्ण)

/*
 * The length of a UUID string ("aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee")
 * not including trailing NUL.
 */
#घोषणा	UUID_STRING_LEN		36

बाह्य स्थिर guid_t guid_null;
बाह्य स्थिर uuid_t uuid_null;

अटल अंतरभूत bool guid_equal(स्थिर guid_t *u1, स्थिर guid_t *u2)
अणु
	वापस स_भेद(u1, u2, माप(guid_t)) == 0;
पूर्ण

अटल अंतरभूत व्योम guid_copy(guid_t *dst, स्थिर guid_t *src)
अणु
	स_नकल(dst, src, माप(guid_t));
पूर्ण

अटल अंतरभूत व्योम import_guid(guid_t *dst, स्थिर __u8 *src)
अणु
	स_नकल(dst, src, माप(guid_t));
पूर्ण

अटल अंतरभूत व्योम export_guid(__u8 *dst, स्थिर guid_t *src)
अणु
	स_नकल(dst, src, माप(guid_t));
पूर्ण

अटल अंतरभूत bool guid_is_null(स्थिर guid_t *guid)
अणु
	वापस guid_equal(guid, &guid_null);
पूर्ण

अटल अंतरभूत bool uuid_equal(स्थिर uuid_t *u1, स्थिर uuid_t *u2)
अणु
	वापस स_भेद(u1, u2, माप(uuid_t)) == 0;
पूर्ण

अटल अंतरभूत व्योम uuid_copy(uuid_t *dst, स्थिर uuid_t *src)
अणु
	स_नकल(dst, src, माप(uuid_t));
पूर्ण

अटल अंतरभूत व्योम import_uuid(uuid_t *dst, स्थिर __u8 *src)
अणु
	स_नकल(dst, src, माप(uuid_t));
पूर्ण

अटल अंतरभूत व्योम export_uuid(__u8 *dst, स्थिर uuid_t *src)
अणु
	स_नकल(dst, src, माप(uuid_t));
पूर्ण

अटल अंतरभूत bool uuid_is_null(स्थिर uuid_t *uuid)
अणु
	वापस uuid_equal(uuid, &uuid_null);
पूर्ण

व्योम generate_अक्रमom_uuid(अचिन्हित अक्षर uuid[16]);
व्योम generate_अक्रमom_guid(अचिन्हित अक्षर guid[16]);

बाह्य व्योम guid_gen(guid_t *u);
बाह्य व्योम uuid_gen(uuid_t *u);

bool __must_check uuid_is_valid(स्थिर अक्षर *uuid);

बाह्य स्थिर u8 guid_index[16];
बाह्य स्थिर u8 uuid_index[16];

पूर्णांक guid_parse(स्थिर अक्षर *uuid, guid_t *u);
पूर्णांक uuid_parse(स्थिर अक्षर *uuid, uuid_t *u);

/* backwards compatibility, करोn't use in new code */
अटल अंतरभूत पूर्णांक uuid_le_cmp(स्थिर guid_t u1, स्थिर guid_t u2)
अणु
	वापस स_भेद(&u1, &u2, माप(guid_t));
पूर्ण

#पूर्ण_अगर
