<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) Copyright David Gibson <dwg@au1.ibm.com>, IBM Corporation.  2005.
 */

#समावेश "dtc.h"

व्योम data_मुक्त(काष्ठा data d)
अणु
	काष्ठा marker *m, *nm;

	m = d.markers;
	जबतक (m) अणु
		nm = m->next;
		मुक्त(m->ref);
		मुक्त(m);
		m = nm;
	पूर्ण

	अगर (d.val)
		मुक्त(d.val);
पूर्ण

काष्ठा data data_grow_क्रम(काष्ठा data d, अचिन्हित पूर्णांक xlen)
अणु
	काष्ठा data nd;
	अचिन्हित पूर्णांक newsize;

	अगर (xlen == 0)
		वापस d;

	nd = d;

	newsize = xlen;

	जबतक ((d.len + xlen) > newsize)
		newsize *= 2;

	nd.val = xपुनः_स्मृति(d.val, newsize);

	वापस nd;
पूर्ण

काष्ठा data data_copy_mem(स्थिर अक्षर *mem, पूर्णांक len)
अणु
	काष्ठा data d;

	d = data_grow_क्रम(empty_data, len);

	d.len = len;
	स_नकल(d.val, mem, len);

	वापस d;
पूर्ण

काष्ठा data data_copy_escape_string(स्थिर अक्षर *s, पूर्णांक len)
अणु
	पूर्णांक i = 0;
	काष्ठा data d;
	अक्षर *q;

	d = data_add_marker(empty_data, TYPE_STRING, शून्य);
	d = data_grow_क्रम(d, len + 1);

	q = d.val;
	जबतक (i < len) अणु
		अक्षर c = s[i++];

		अगर (c == '\\')
			c = get_escape_अक्षर(s, &i);

		q[d.len++] = c;
	पूर्ण

	q[d.len++] = '\0';
	वापस d;
पूर्ण

काष्ठा data data_copy_file(खाता *f, माप_प्रकार maxlen)
अणु
	काष्ठा data d = empty_data;

	d = data_add_marker(d, TYPE_NONE, शून्य);
	जबतक (!ख_पूर्ण(f) && (d.len < maxlen)) अणु
		माप_प्रकार chunksize, ret;

		अगर (maxlen == (माप_प्रकार)-1)
			chunksize = 4096;
		अन्यथा
			chunksize = maxlen - d.len;

		d = data_grow_क्रम(d, chunksize);
		ret = ख_पढ़ो(d.val + d.len, 1, chunksize, f);

		अगर (ख_त्रुटि(f))
			die("Error reading file into data: %s", म_त्रुटि(त्रुटि_सं));

		अगर (d.len + ret < d.len)
			die("Overflow reading file into data\n");

		d.len += ret;
	पूर्ण

	वापस d;
पूर्ण

काष्ठा data data_append_data(काष्ठा data d, स्थिर व्योम *p, पूर्णांक len)
अणु
	d = data_grow_क्रम(d, len);
	स_नकल(d.val + d.len, p, len);
	d.len += len;
	वापस d;
पूर्ण

काष्ठा data data_insert_at_marker(काष्ठा data d, काष्ठा marker *m,
				  स्थिर व्योम *p, पूर्णांक len)
अणु
	d = data_grow_क्रम(d, len);
	स_हटाओ(d.val + m->offset + len, d.val + m->offset, d.len - m->offset);
	स_नकल(d.val + m->offset, p, len);
	d.len += len;

	/* Adjust all markers after the one we're inserting at */
	m = m->next;
	क्रम_each_marker(m)
		m->offset += len;
	वापस d;
पूर्ण

अटल काष्ठा data data_append_markers(काष्ठा data d, काष्ठा marker *m)
अणु
	काष्ठा marker **mp = &d.markers;

	/* Find the end of the markerlist */
	जबतक (*mp)
		mp = &((*mp)->next);
	*mp = m;
	वापस d;
पूर्ण

काष्ठा data data_merge(काष्ठा data d1, काष्ठा data d2)
अणु
	काष्ठा data d;
	काष्ठा marker *m2 = d2.markers;

	d = data_append_markers(data_append_data(d1, d2.val, d2.len), m2);

	/* Adjust क्रम the length of d1 */
	क्रम_each_marker(m2)
		m2->offset += d1.len;

	d2.markers = शून्य; /* So data_मुक्त() करोesn't clobber them */
	data_मुक्त(d2);

	वापस d;
पूर्ण

काष्ठा data data_append_पूर्णांकeger(काष्ठा data d, uपूर्णांक64_t value, पूर्णांक bits)
अणु
	uपूर्णांक8_t value_8;
	fdt16_t value_16;
	fdt32_t value_32;
	fdt64_t value_64;

	चयन (bits) अणु
	हाल 8:
		value_8 = value;
		वापस data_append_data(d, &value_8, 1);

	हाल 16:
		value_16 = cpu_to_fdt16(value);
		वापस data_append_data(d, &value_16, 2);

	हाल 32:
		value_32 = cpu_to_fdt32(value);
		वापस data_append_data(d, &value_32, 4);

	हाल 64:
		value_64 = cpu_to_fdt64(value);
		वापस data_append_data(d, &value_64, 8);

	शेष:
		die("Invalid literal size (%d)\n", bits);
	पूर्ण
पूर्ण

काष्ठा data data_append_re(काष्ठा data d, uपूर्णांक64_t address, uपूर्णांक64_t size)
अणु
	काष्ठा fdt_reserve_entry re;

	re.address = cpu_to_fdt64(address);
	re.size = cpu_to_fdt64(size);

	वापस data_append_data(d, &re, माप(re));
पूर्ण

काष्ठा data data_append_cell(काष्ठा data d, cell_t word)
अणु
	वापस data_append_पूर्णांकeger(d, word, माप(word) * 8);
पूर्ण

काष्ठा data data_append_addr(काष्ठा data d, uपूर्णांक64_t addr)
अणु
	वापस data_append_पूर्णांकeger(d, addr, माप(addr) * 8);
पूर्ण

काष्ठा data data_append_byte(काष्ठा data d, uपूर्णांक8_t byte)
अणु
	वापस data_append_data(d, &byte, 1);
पूर्ण

काष्ठा data data_append_zeroes(काष्ठा data d, पूर्णांक len)
अणु
	d = data_grow_क्रम(d, len);

	स_रखो(d.val + d.len, 0, len);
	d.len += len;
	वापस d;
पूर्ण

काष्ठा data data_append_align(काष्ठा data d, पूर्णांक align)
अणु
	पूर्णांक newlen = ALIGN(d.len, align);
	वापस data_append_zeroes(d, newlen - d.len);
पूर्ण

काष्ठा data data_add_marker(काष्ठा data d, क्रमागत markertype type, अक्षर *ref)
अणु
	काष्ठा marker *m;

	m = xदो_स्मृति(माप(*m));
	m->offset = d.len;
	m->type = type;
	m->ref = ref;
	m->next = शून्य;

	वापस data_append_markers(d, m);
पूर्ण

bool data_is_one_string(काष्ठा data d)
अणु
	पूर्णांक i;
	पूर्णांक len = d.len;

	अगर (len == 0)
		वापस false;

	क्रम (i = 0; i < len-1; i++)
		अगर (d.val[i] == '\0')
			वापस false;

	अगर (d.val[len-1] != '\0')
		वापस false;

	वापस true;
पूर्ण
