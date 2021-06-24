<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/lppaca.h>

/*
 * The associativity करोमुख्य numbers are वापसed from the hypervisor as a
 * stream of mixed 16-bit and 32-bit fields. The stream is terminated by the
 * special value of "all ones" (aka. 0xffff) and its size may not exceed 48
 * bytes.
 *
 *    --- 16-bit fields -->
 *  _________________________
 *  |  0  |  1  |  2  |  3  |   be_packed[0]
 *  ------+-----+-----+------
 *  _________________________
 *  |  4  |  5  |  6  |  7  |   be_packed[1]
 *  -------------------------
 *            ...
 *  _________________________
 *  | 20  | 21  | 22  | 23  |   be_packed[5]
 *  -------------------------
 *
 * Convert to the sequence they would appear in the ibm,associativity property.
 */
अटल पूर्णांक vphn_unpack_associativity(स्थिर दीर्घ *packed, __be32 *unpacked)
अणु
	__be64 be_packed[VPHN_REGISTER_COUNT];
	पूर्णांक i, nr_assoc_करोms = 0;
	स्थिर __be16 *field = (स्थिर __be16 *) be_packed;
	u16 last = 0;
	bool is_32bit = false;

#घोषणा VPHN_FIELD_UNUSED	(0xffff)
#घोषणा VPHN_FIELD_MSB		(0x8000)
#घोषणा VPHN_FIELD_MASK		(~VPHN_FIELD_MSB)

	/* Let's fix the values वापसed by plpar_hcall9() */
	क्रम (i = 0; i < VPHN_REGISTER_COUNT; i++)
		be_packed[i] = cpu_to_be64(packed[i]);

	क्रम (i = 1; i < VPHN_ASSOC_बफ_मानE; i++) अणु
		u16 new = be16_to_cpup(field++);

		अगर (is_32bit) अणु
			/*
			 * Let's concatenate the 16 bits of this field to the
			 * 15 lower bits of the previous field
			 */
			unpacked[++nr_assoc_करोms] =
				cpu_to_be32(last << 16 | new);
			is_32bit = false;
		पूर्ण अन्यथा अगर (new == VPHN_FIELD_UNUSED)
			/* This is the list terminator */
			अवरोध;
		अन्यथा अगर (new & VPHN_FIELD_MSB) अणु
			/* Data is in the lower 15 bits of this field */
			unpacked[++nr_assoc_करोms] =
				cpu_to_be32(new & VPHN_FIELD_MASK);
		पूर्ण अन्यथा अणु
			/*
			 * Data is in the lower 15 bits of this field
			 * concatenated with the next 16 bit field
			 */
			last = new;
			is_32bit = true;
		पूर्ण
	पूर्ण

	/* The first cell contains the length of the property */
	unpacked[0] = cpu_to_be32(nr_assoc_करोms);

	वापस nr_assoc_करोms;
पूर्ण

/* NOTE: This file is included by a selftest and built in userspace. */
#अगर_घोषित __KERNEL__
#समावेश <यंत्र/hvcall.h>

दीर्घ hcall_vphn(अचिन्हित दीर्घ cpu, u64 flags, __be32 *associativity)
अणु
	दीर्घ rc;
	दीर्घ retbuf[PLPAR_HCALL9_बफ_मानE] = अणु0पूर्ण;

	rc = plpar_hcall9(H_HOME_NODE_ASSOCIATIVITY, retbuf, flags, cpu);
	अगर (rc == H_SUCCESS)
		vphn_unpack_associativity(retbuf, associativity);

	वापस rc;
पूर्ण
#पूर्ण_अगर
