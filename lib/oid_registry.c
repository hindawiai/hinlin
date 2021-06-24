<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ASN.1 Object identअगरier (OID) registry
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/oid_registry.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bug.h>
#समावेश <linux/asn1.h>
#समावेश "oid_registry_data.c"

MODULE_DESCRIPTION("OID Registry");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");

/**
 * look_up_OID - Find an OID registration क्रम the specअगरied data
 * @data: Binary representation of the OID
 * @datasize: Size of the binary representation
 */
क्रमागत OID look_up_OID(स्थिर व्योम *data, माप_प्रकार datasize)
अणु
	स्थिर अचिन्हित अक्षर *octets = data;
	क्रमागत OID oid;
	अचिन्हित अक्षर xhash;
	अचिन्हित i, j, k, hash;
	माप_प्रकार len;

	/* Hash the OID data */
	hash = datasize - 1;

	क्रम (i = 0; i < datasize; i++)
		hash += octets[i] * 33;
	hash = (hash >> 24) ^ (hash >> 16) ^ (hash >> 8) ^ hash;
	hash &= 0xff;

	/* Binary search the OID registry.  OIDs are stored in ascending order
	 * of hash value then ascending order of size and then in ascending
	 * order of reverse value.
	 */
	i = 0;
	k = OID__NR;
	जबतक (i < k) अणु
		j = (i + k) / 2;

		xhash = oid_search_table[j].hash;
		अगर (xhash > hash) अणु
			k = j;
			जारी;
		पूर्ण
		अगर (xhash < hash) अणु
			i = j + 1;
			जारी;
		पूर्ण

		oid = oid_search_table[j].oid;
		len = oid_index[oid + 1] - oid_index[oid];
		अगर (len > datasize) अणु
			k = j;
			जारी;
		पूर्ण
		अगर (len < datasize) अणु
			i = j + 1;
			जारी;
		पूर्ण

		/* Variation is most likely to be at the tail end of the
		 * OID, so करो the comparison in reverse.
		 */
		जबतक (len > 0) अणु
			अचिन्हित अक्षर a = oid_data[oid_index[oid] + --len];
			अचिन्हित अक्षर b = octets[len];
			अगर (a > b) अणु
				k = j;
				जाओ next;
			पूर्ण
			अगर (a < b) अणु
				i = j + 1;
				जाओ next;
			पूर्ण
		पूर्ण
		वापस oid;
	next:
		;
	पूर्ण

	वापस OID__NR;
पूर्ण
EXPORT_SYMBOL_GPL(look_up_OID);

/**
 * parse_OID - Parse an OID from a bytestream
 * @data: Binary representation of the header + OID
 * @datasize: Size of the binary representation
 * @oid: Poपूर्णांकer to oid to वापस result
 *
 * Parse an OID from a bytestream that holds the OID in the क्रमmat
 * ASN1_OID | length | oid. The length indicator must equal to datasize - 2.
 * -EBADMSG is वापसed अगर the bytestream is too लघु.
 */
पूर्णांक parse_OID(स्थिर व्योम *data, माप_प्रकार datasize, क्रमागत OID *oid)
अणु
	स्थिर अचिन्हित अक्षर *v = data;

	/* we need 2 bytes of header and at least 1 byte क्रम oid */
	अगर (datasize < 3 || v[0] != ASN1_OID || v[1] != datasize - 2)
		वापस -EBADMSG;

	*oid = look_up_OID(data + 2, datasize - 2);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(parse_OID);

/*
 * sprपूर्णांक_OID - Prपूर्णांक an Object Identअगरier पूर्णांकo a buffer
 * @data: The encoded OID to prपूर्णांक
 * @datasize: The size of the encoded OID
 * @buffer: The buffer to render पूर्णांकo
 * @bufsize: The size of the buffer
 *
 * The OID is rendered पूर्णांकo the buffer in "a.b.c.d" क्रमmat and the number of
 * bytes is वापसed.  -EBADMSG is वापसed अगर the data could not be पूर्णांकepreted
 * and -ENOBUFS अगर the buffer was too small.
 */
पूर्णांक sprपूर्णांक_oid(स्थिर व्योम *data, माप_प्रकार datasize, अक्षर *buffer, माप_प्रकार bufsize)
अणु
	स्थिर अचिन्हित अक्षर *v = data, *end = v + datasize;
	अचिन्हित दीर्घ num;
	अचिन्हित अक्षर n;
	माप_प्रकार ret;
	पूर्णांक count;

	अगर (v >= end)
		जाओ bad;

	n = *v++;
	ret = count = snम_लिखो(buffer, bufsize, "%u.%u", n / 40, n % 40);
	अगर (count >= bufsize)
		वापस -ENOBUFS;
	buffer += count;
	bufsize -= count;

	जबतक (v < end) अणु
		num = 0;
		n = *v++;
		अगर (!(n & 0x80)) अणु
			num = n;
		पूर्ण अन्यथा अणु
			num = n & 0x7f;
			करो अणु
				अगर (v >= end)
					जाओ bad;
				n = *v++;
				num <<= 7;
				num |= n & 0x7f;
			पूर्ण जबतक (n & 0x80);
		पूर्ण
		ret += count = snम_लिखो(buffer, bufsize, ".%lu", num);
		अगर (count >= bufsize)
			वापस -ENOBUFS;
		buffer += count;
		bufsize -= count;
	पूर्ण

	वापस ret;

bad:
	snम_लिखो(buffer, bufsize, "(bad)");
	वापस -EBADMSG;
पूर्ण
EXPORT_SYMBOL_GPL(sprपूर्णांक_oid);

/**
 * sprपूर्णांक_OID - Prपूर्णांक an Object Identअगरier पूर्णांकo a buffer
 * @oid: The OID to prपूर्णांक
 * @buffer: The buffer to render पूर्णांकo
 * @bufsize: The size of the buffer
 *
 * The OID is rendered पूर्णांकo the buffer in "a.b.c.d" क्रमmat and the number of
 * bytes is वापसed.
 */
पूर्णांक sprपूर्णांक_OID(क्रमागत OID oid, अक्षर *buffer, माप_प्रकार bufsize)
अणु
	पूर्णांक ret;

	BUG_ON(oid >= OID__NR);

	ret = sprपूर्णांक_oid(oid_data + oid_index[oid],
			 oid_index[oid + 1] - oid_index[oid],
			 buffer, bufsize);
	BUG_ON(ret == -EBADMSG);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sprपूर्णांक_OID);
