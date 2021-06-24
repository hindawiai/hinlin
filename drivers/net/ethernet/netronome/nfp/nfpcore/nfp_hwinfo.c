<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2017 Netronome Systems, Inc. */

/* Parse the hwinfo table that the ARM firmware builds in the ARM scratch SRAM
 * after chip reset.
 *
 * Examples of the fields:
 *   me.count = 40
 *   me.mask = 0x7f_ffff_ffff
 *
 *   me.count is the total number of MEs on the प्रणाली.
 *   me.mask is the biपंचांगask of MEs that are available क्रम application usage.
 *
 *   (ie, in this example, ME 39 has been reserved by boardconfig.)
 */

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/delay.h>
#समावेश <linux/log2.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#घोषणा NFP_SUBSYS "nfp_hwinfo"

#समावेश "crc32.h"
#समावेश "nfp.h"
#समावेश "nfp_cpp.h"
#समावेश "nfp6000/nfp6000.h"

#घोषणा HWINFO_SIZE_MIN	0x100
#घोषणा HWINFO_WAIT	20	/* seconds */

/* The Hardware Info Table defines the properties of the प्रणाली.
 *
 * HWInfo v1 Table (fixed size)
 *
 * 0x0000: u32 version	        Hardware Info Table version (1.0)
 * 0x0004: u32 size	        Total size of the table, including
 *			        the CRC32 (IEEE 802.3)
 * 0x0008: u32 jumptab	        Offset of key/value table
 * 0x000c: u32 keys	        Total number of keys in the key/value table
 * NNNNNN:		        Key/value jump table and string data
 * (size - 4): u32 crc32	CRC32 (same as IEEE 802.3, POSIX csum, etc)
 *				CRC32("",0) = ~0, CRC32("a",1) = 0x48C279FE
 *
 * HWInfo v2 Table (variable size)
 *
 * 0x0000: u32 version	        Hardware Info Table version (2.0)
 * 0x0004: u32 size	        Current size of the data area, excluding CRC32
 * 0x0008: u32 limit	        Maximum size of the table
 * 0x000c: u32 reserved	        Unused, set to zero
 * NNNNNN:			Key/value data
 * (size - 4): u32 crc32	CRC32 (same as IEEE 802.3, POSIX csum, etc)
 *				CRC32("",0) = ~0, CRC32("a",1) = 0x48C279FE
 *
 * If the HWInfo table is in the process of being updated, the low bit
 * of version will be set.
 *
 * HWInfo v1 Key/Value Table
 * -------------------------
 *
 *  The key/value table is a set of offsets to ASCIIZ strings which have
 *  been म_भेद(3) sorted (yes, please use द्वा_खोज(3) on the table).
 *
 *  All keys are guaranteed to be unique.
 *
 * N+0:	u32 key_1		Offset to the first key
 * N+4:	u32 val_1		Offset to the first value
 * N+8: u32 key_2		Offset to the second key
 * N+c: u32 val_2		Offset to the second value
 * ...
 *
 * HWInfo v2 Key/Value Table
 * -------------------------
 *
 * Packed UTF8Z strings, ie 'key1\000value1\000key2\000value2\000'
 *
 * Unsorted.
 */

#घोषणा NFP_HWINFO_VERSION_1 ('H' << 24 | 'I' << 16 | 1 << 8 | 0 << 1 | 0)
#घोषणा NFP_HWINFO_VERSION_2 ('H' << 24 | 'I' << 16 | 2 << 8 | 0 << 1 | 0)
#घोषणा NFP_HWINFO_VERSION_UPDATING	BIT(0)

काष्ठा nfp_hwinfo अणु
	u8 start[0];

	__le32 version;
	__le32 size;

	/* v2 specअगरic fields */
	__le32 limit;
	__le32 resv;

	अक्षर data[];
पूर्ण;

अटल bool nfp_hwinfo_is_updating(काष्ठा nfp_hwinfo *hwinfo)
अणु
	वापस le32_to_cpu(hwinfo->version) & NFP_HWINFO_VERSION_UPDATING;
पूर्ण

अटल पूर्णांक
hwinfo_db_walk(काष्ठा nfp_cpp *cpp, काष्ठा nfp_hwinfo *hwinfo, u32 size)
अणु
	स्थिर अक्षर *key, *val, *end = hwinfo->data + size;

	क्रम (key = hwinfo->data; *key && key < end;
	     key = val + म_माप(val) + 1) अणु

		val = key + म_माप(key) + 1;
		अगर (val >= end) अणु
			nfp_warn(cpp, "Bad HWINFO - overflowing key\n");
			वापस -EINVAL;
		पूर्ण

		अगर (val + म_माप(val) + 1 > end) अणु
			nfp_warn(cpp, "Bad HWINFO - overflowing value\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
hwinfo_db_validate(काष्ठा nfp_cpp *cpp, काष्ठा nfp_hwinfo *db, u32 len)
अणु
	u32 size, crc;

	size = le32_to_cpu(db->size);
	अगर (size > len) अणु
		nfp_err(cpp, "Unsupported hwinfo size %u > %u\n", size, len);
		वापस -EINVAL;
	पूर्ण

	size -= माप(u32);
	crc = crc32_posix(db, size);
	अगर (crc != get_unaligned_le32(db->start + size)) अणु
		nfp_err(cpp, "Corrupt hwinfo table (CRC mismatch), calculated 0x%x, expected 0x%x\n",
			crc, get_unaligned_le32(db->start + size));

		वापस -EINVAL;
	पूर्ण

	वापस hwinfo_db_walk(cpp, db, size);
पूर्ण

अटल काष्ठा nfp_hwinfo *
hwinfo_try_fetch(काष्ठा nfp_cpp *cpp, माप_प्रकार *cpp_size)
अणु
	काष्ठा nfp_hwinfo *header;
	काष्ठा nfp_resource *res;
	u64 cpp_addr;
	u32 cpp_id;
	पूर्णांक err;
	u8 *db;

	res = nfp_resource_acquire(cpp, NFP_RESOURCE_NFP_HWINFO);
	अगर (!IS_ERR(res)) अणु
		cpp_id = nfp_resource_cpp_id(res);
		cpp_addr = nfp_resource_address(res);
		*cpp_size = nfp_resource_size(res);

		nfp_resource_release(res);

		अगर (*cpp_size < HWINFO_SIZE_MIN)
			वापस शून्य;
	पूर्ण अन्यथा अगर (PTR_ERR(res) == -ENOENT) अणु
		/* Try getting the HWInfo table from the 'classic' location */
		cpp_id = NFP_CPP_ISLAND_ID(NFP_CPP_TARGET_MU,
					   NFP_CPP_ACTION_RW, 0, 1);
		cpp_addr = 0x30000;
		*cpp_size = 0x0e000;
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण

	db = kदो_स्मृति(*cpp_size + 1, GFP_KERNEL);
	अगर (!db)
		वापस शून्य;

	err = nfp_cpp_पढ़ो(cpp, cpp_id, cpp_addr, db, *cpp_size);
	अगर (err != *cpp_size)
		जाओ निकास_मुक्त;

	header = (व्योम *)db;
	अगर (nfp_hwinfo_is_updating(header))
		जाओ निकास_मुक्त;

	अगर (le32_to_cpu(header->version) != NFP_HWINFO_VERSION_2) अणु
		nfp_err(cpp, "Unknown HWInfo version: 0x%08x\n",
			le32_to_cpu(header->version));
		जाओ निकास_मुक्त;
	पूर्ण

	/* शून्य-terminate क्रम safety */
	db[*cpp_size] = '\0';

	वापस (व्योम *)db;
निकास_मुक्त:
	kमुक्त(db);
	वापस शून्य;
पूर्ण

अटल काष्ठा nfp_hwinfo *hwinfo_fetch(काष्ठा nfp_cpp *cpp, माप_प्रकार *hwdb_size)
अणु
	स्थिर अचिन्हित दीर्घ रुको_until = jअगरfies + HWINFO_WAIT * HZ;
	काष्ठा nfp_hwinfo *db;
	पूर्णांक err;

	क्रम (;;) अणु
		स्थिर अचिन्हित दीर्घ start_समय = jअगरfies;

		db = hwinfo_try_fetch(cpp, hwdb_size);
		अगर (db)
			वापस db;

		err = msleep_पूर्णांकerruptible(100);
		अगर (err || समय_after(start_समय, रुको_until)) अणु
			nfp_err(cpp, "NFP access error\n");
			वापस शून्य;
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा nfp_hwinfo *nfp_hwinfo_पढ़ो(काष्ठा nfp_cpp *cpp)
अणु
	काष्ठा nfp_hwinfo *db;
	माप_प्रकार hwdb_size = 0;
	पूर्णांक err;

	db = hwinfo_fetch(cpp, &hwdb_size);
	अगर (!db)
		वापस शून्य;

	err = hwinfo_db_validate(cpp, db, hwdb_size);
	अगर (err) अणु
		kमुक्त(db);
		वापस शून्य;
	पूर्ण

	वापस db;
पूर्ण

/**
 * nfp_hwinfo_lookup() - Find a value in the HWInfo table by name
 * @hwinfo:	NFP HWinfo table
 * @lookup:	HWInfo name to search क्रम
 *
 * Return: Value of the HWInfo name, or शून्य
 */
स्थिर अक्षर *nfp_hwinfo_lookup(काष्ठा nfp_hwinfo *hwinfo, स्थिर अक्षर *lookup)
अणु
	स्थिर अक्षर *key, *val, *end;

	अगर (!hwinfo || !lookup)
		वापस शून्य;

	end = hwinfo->data + le32_to_cpu(hwinfo->size) - माप(u32);

	क्रम (key = hwinfo->data; *key && key < end;
	     key = val + म_माप(val) + 1) अणु

		val = key + म_माप(key) + 1;

		अगर (म_भेद(key, lookup) == 0)
			वापस val;
	पूर्ण

	वापस शून्य;
पूर्ण

अक्षर *nfp_hwinfo_get_packed_strings(काष्ठा nfp_hwinfo *hwinfo)
अणु
	वापस hwinfo->data;
पूर्ण

u32 nfp_hwinfo_get_packed_str_size(काष्ठा nfp_hwinfo *hwinfo)
अणु
	वापस le32_to_cpu(hwinfo->size) - माप(u32);
पूर्ण
