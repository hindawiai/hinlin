<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/export.h>
#समावेश <linux/माला.स>

#समावेश <rdma/ib_pack.h>

अटल u64 value_पढ़ो(पूर्णांक offset, पूर्णांक size, व्योम *काष्ठाure)
अणु
	चयन (size) अणु
	हाल 1: वापस                *(u8  *) (काष्ठाure + offset);
	हाल 2: वापस be16_to_cpup((__be16 *) (काष्ठाure + offset));
	हाल 4: वापस be32_to_cpup((__be32 *) (काष्ठाure + offset));
	हाल 8: वापस be64_to_cpup((__be64 *) (काष्ठाure + offset));
	शेष:
		pr_warn("Field size %d bits not handled\n", size * 8);
		वापस 0;
	पूर्ण
पूर्ण

/**
 * ib_pack - Pack a काष्ठाure पूर्णांकo a buffer
 * @desc:Array of काष्ठाure field descriptions
 * @desc_len:Number of entries in @desc
 * @काष्ठाure:Structure to pack from
 * @buf:Buffer to pack पूर्णांकo
 *
 * ib_pack() packs a list of काष्ठाure fields पूर्णांकo a buffer,
 * controlled by the array of fields in @desc.
 */
व्योम ib_pack(स्थिर काष्ठा ib_field        *desc,
	     पूर्णांक                           desc_len,
	     व्योम                         *काष्ठाure,
	     व्योम                         *buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < desc_len; ++i) अणु
		अगर (desc[i].size_bits <= 32) अणु
			पूर्णांक shअगरt;
			u32 val;
			__be32 mask;
			__be32 *addr;

			shअगरt = 32 - desc[i].offset_bits - desc[i].size_bits;
			अगर (desc[i].काष्ठा_size_bytes)
				val = value_पढ़ो(desc[i].काष्ठा_offset_bytes,
						 desc[i].काष्ठा_size_bytes,
						 काष्ठाure) << shअगरt;
			अन्यथा
				val = 0;

			mask = cpu_to_be32(((1ull << desc[i].size_bits) - 1) << shअगरt);
			addr = (__be32 *) buf + desc[i].offset_words;
			*addr = (*addr & ~mask) | (cpu_to_be32(val) & mask);
		पूर्ण अन्यथा अगर (desc[i].size_bits <= 64) अणु
			पूर्णांक shअगरt;
			u64 val;
			__be64 mask;
			__be64 *addr;

			shअगरt = 64 - desc[i].offset_bits - desc[i].size_bits;
			अगर (desc[i].काष्ठा_size_bytes)
				val = value_पढ़ो(desc[i].काष्ठा_offset_bytes,
						 desc[i].काष्ठा_size_bytes,
						 काष्ठाure) << shअगरt;
			अन्यथा
				val = 0;

			mask = cpu_to_be64((~0ull >> (64 - desc[i].size_bits)) << shअगरt);
			addr = (__be64 *) ((__be32 *) buf + desc[i].offset_words);
			*addr = (*addr & ~mask) | (cpu_to_be64(val) & mask);
		पूर्ण अन्यथा अणु
			अगर (desc[i].offset_bits % 8 ||
			    desc[i].size_bits   % 8) अणु
				pr_warn("Structure field %s of size %d bits is not byte-aligned\n",
					desc[i].field_name, desc[i].size_bits);
			पूर्ण

			अगर (desc[i].काष्ठा_size_bytes)
				स_नकल(buf + desc[i].offset_words * 4 +
				       desc[i].offset_bits / 8,
				       काष्ठाure + desc[i].काष्ठा_offset_bytes,
				       desc[i].size_bits / 8);
			अन्यथा
				स_रखो(buf + desc[i].offset_words * 4 +
				       desc[i].offset_bits / 8,
				       0,
				       desc[i].size_bits / 8);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ib_pack);

अटल व्योम value_ग_लिखो(पूर्णांक offset, पूर्णांक size, u64 val, व्योम *काष्ठाure)
अणु
	चयन (size * 8) अणु
	हाल 8:  *(    u8 *) (काष्ठाure + offset) = val; अवरोध;
	हाल 16: *(__be16 *) (काष्ठाure + offset) = cpu_to_be16(val); अवरोध;
	हाल 32: *(__be32 *) (काष्ठाure + offset) = cpu_to_be32(val); अवरोध;
	हाल 64: *(__be64 *) (काष्ठाure + offset) = cpu_to_be64(val); अवरोध;
	शेष:
		pr_warn("Field size %d bits not handled\n", size * 8);
	पूर्ण
पूर्ण

/**
 * ib_unpack - Unpack a buffer पूर्णांकo a काष्ठाure
 * @desc:Array of काष्ठाure field descriptions
 * @desc_len:Number of entries in @desc
 * @buf:Buffer to unpack from
 * @काष्ठाure:Structure to unpack पूर्णांकo
 *
 * ib_pack() unpacks a list of काष्ठाure fields from a buffer,
 * controlled by the array of fields in @desc.
 */
व्योम ib_unpack(स्थिर काष्ठा ib_field        *desc,
	       पूर्णांक                           desc_len,
	       व्योम                         *buf,
	       व्योम                         *काष्ठाure)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < desc_len; ++i) अणु
		अगर (!desc[i].काष्ठा_size_bytes)
			जारी;

		अगर (desc[i].size_bits <= 32) अणु
			पूर्णांक shअगरt;
			u32  val;
			u32  mask;
			__be32 *addr;

			shअगरt = 32 - desc[i].offset_bits - desc[i].size_bits;
			mask = ((1ull << desc[i].size_bits) - 1) << shअगरt;
			addr = (__be32 *) buf + desc[i].offset_words;
			val = (be32_to_cpup(addr) & mask) >> shअगरt;
			value_ग_लिखो(desc[i].काष्ठा_offset_bytes,
				    desc[i].काष्ठा_size_bytes,
				    val,
				    काष्ठाure);
		पूर्ण अन्यथा अगर (desc[i].size_bits <= 64) अणु
			पूर्णांक shअगरt;
			u64  val;
			u64  mask;
			__be64 *addr;

			shअगरt = 64 - desc[i].offset_bits - desc[i].size_bits;
			mask = (~0ull >> (64 - desc[i].size_bits)) << shअगरt;
			addr = (__be64 *) buf + desc[i].offset_words;
			val = (be64_to_cpup(addr) & mask) >> shअगरt;
			value_ग_लिखो(desc[i].काष्ठा_offset_bytes,
				    desc[i].काष्ठा_size_bytes,
				    val,
				    काष्ठाure);
		पूर्ण अन्यथा अणु
			अगर (desc[i].offset_bits % 8 ||
			    desc[i].size_bits   % 8) अणु
				pr_warn("Structure field %s of size %d bits is not byte-aligned\n",
					desc[i].field_name, desc[i].size_bits);
			पूर्ण

			स_नकल(काष्ठाure + desc[i].काष्ठा_offset_bytes,
			       buf + desc[i].offset_words * 4 +
			       desc[i].offset_bits / 8,
			       desc[i].size_bits / 8);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ib_unpack);
