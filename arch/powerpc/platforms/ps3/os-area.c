<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 flash memory os area.
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/fs.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/export.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/memblock.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/prom.h>

#समावेश "platform.h"

क्रमागत अणु
	OS_AREA_SEGMENT_SIZE = 0X200,
पूर्ण;

क्रमागत os_area_ldr_क्रमmat अणु
	HEADER_LDR_FORMAT_RAW = 0,
	HEADER_LDR_FORMAT_GZIP = 1,
पूर्ण;

#घोषणा OS_AREA_HEADER_MAGIC_NUM "cell_ext_os_area"

/**
 * काष्ठा os_area_header - os area header segment.
 * @magic_num: Always 'cell_ext_os_area'.
 * @hdr_version: Header क्रमmat version number.
 * @db_area_offset: Starting segment number of other os database area.
 * @ldr_area_offset: Starting segment number of bootloader image area.
 * @ldr_क्रमmat: HEADER_LDR_FORMAT flag.
 * @ldr_size: Size of bootloader image in bytes.
 *
 * Note that the करोcs refer to area offsets.  These are offsets in units of
 * segments from the start of the os area (top of the header).  These are
 * better thought of as segment numbers.  The os area of the os area is
 * reserved क्रम the os image.
 */

काष्ठा os_area_header अणु
	u8 magic_num[16];
	u32 hdr_version;
	u32 db_area_offset;
	u32 ldr_area_offset;
	u32 _reserved_1;
	u32 ldr_क्रमmat;
	u32 ldr_size;
	u32 _reserved_2[6];
पूर्ण;

क्रमागत os_area_boot_flag अणु
	PARAM_BOOT_FLAG_GAME_OS = 0,
	PARAM_BOOT_FLAG_OTHER_OS = 1,
पूर्ण;

क्रमागत os_area_ctrl_button अणु
	PARAM_CTRL_BUTTON_O_IS_YES = 0,
	PARAM_CTRL_BUTTON_X_IS_YES = 1,
पूर्ण;

/**
 * काष्ठा os_area_params - os area params segment.
 * @boot_flag: User preference of operating प्रणाली, PARAM_BOOT_FLAG flag.
 * @num_params: Number of params in this (params) segment.
 * @rtc_dअगरf: Dअगरference in seconds between 1970 and the ps3 rtc value.
 * @av_multi_out: User preference of AV output, PARAM_AV_MULTI_OUT flag.
 * @ctrl_button: User preference of controller button config, PARAM_CTRL_BUTTON
 *	flag.
 * @अटल_ip_addr: User preference of अटल IP address.
 * @network_mask: User preference of अटल network mask.
 * @शेष_gateway: User preference of अटल शेष gateway.
 * @dns_primary: User preference of अटल primary dns server.
 * @dns_secondary: User preference of अटल secondary dns server.
 *
 * The ps3 rtc मुख्यtains a पढ़ो-only value that approximates seconds since
 * 2000-01-01 00:00:00 UTC.
 *
 * User preference of zero क्रम अटल_ip_addr means use dhcp.
 */

काष्ठा os_area_params अणु
	u32 boot_flag;
	u32 _reserved_1[3];
	u32 num_params;
	u32 _reserved_2[3];
	/* param 0 */
	s64 rtc_dअगरf;
	u8 av_multi_out;
	u8 ctrl_button;
	u8 _reserved_3[6];
	/* param 1 */
	u8 अटल_ip_addr[4];
	u8 network_mask[4];
	u8 शेष_gateway[4];
	u8 _reserved_4[4];
	/* param 2 */
	u8 dns_primary[4];
	u8 dns_secondary[4];
	u8 _reserved_5[8];
पूर्ण;

#घोषणा OS_AREA_DB_MAGIC_NUM "-db-"

/**
 * काष्ठा os_area_db - Shared flash memory database.
 * @magic_num: Always '-db-'.
 * @version: os_area_db क्रमmat version number.
 * @index_64: byte offset of the database id index क्रम 64 bit variables.
 * @count_64: number of usable 64 bit index entries
 * @index_32: byte offset of the database id index क्रम 32 bit variables.
 * @count_32: number of usable 32 bit index entries
 * @index_16: byte offset of the database id index क्रम 16 bit variables.
 * @count_16: number of usable 16 bit index entries
 *
 * Flash rom storage क्रम exclusive use by guests running in the other os lpar.
 * The current प्रणाली configuration allocates 1K (two segments) क्रम other os
 * use.
 */

काष्ठा os_area_db अणु
	u8 magic_num[4];
	u16 version;
	u16 _reserved_1;
	u16 index_64;
	u16 count_64;
	u16 index_32;
	u16 count_32;
	u16 index_16;
	u16 count_16;
	u32 _reserved_2;
	u8 _db_data[1000];
पूर्ण;

/**
 * क्रमागत os_area_db_owner - Data owners.
 */

क्रमागत os_area_db_owner अणु
	OS_AREA_DB_OWNER_ANY = -1,
	OS_AREA_DB_OWNER_NONE = 0,
	OS_AREA_DB_OWNER_PROTOTYPE = 1,
	OS_AREA_DB_OWNER_LINUX = 2,
	OS_AREA_DB_OWNER_PETITBOOT = 3,
	OS_AREA_DB_OWNER_MAX = 32,
पूर्ण;

क्रमागत os_area_db_key अणु
	OS_AREA_DB_KEY_ANY = -1,
	OS_AREA_DB_KEY_NONE = 0,
	OS_AREA_DB_KEY_RTC_DIFF = 1,
	OS_AREA_DB_KEY_VIDEO_MODE = 2,
	OS_AREA_DB_KEY_MAX = 8,
पूर्ण;

काष्ठा os_area_db_id अणु
	पूर्णांक owner;
	पूर्णांक key;
पूर्ण;

अटल स्थिर काष्ठा os_area_db_id os_area_db_id_empty = अणु
	.owner = OS_AREA_DB_OWNER_NONE,
	.key = OS_AREA_DB_KEY_NONE
पूर्ण;

अटल स्थिर काष्ठा os_area_db_id os_area_db_id_any = अणु
	.owner = OS_AREA_DB_OWNER_ANY,
	.key = OS_AREA_DB_KEY_ANY
पूर्ण;

अटल स्थिर काष्ठा os_area_db_id os_area_db_id_rtc_dअगरf = अणु
	.owner = OS_AREA_DB_OWNER_LINUX,
	.key = OS_AREA_DB_KEY_RTC_DIFF
पूर्ण;

#घोषणा SECONDS_FROM_1970_TO_2000 946684800LL

/**
 * काष्ठा saved_params - Static working copies of data from the PS3 'os area'.
 *
 * The order of preference we use क्रम the rtc_dअगरf source:
 *  1) The database value.
 *  2) The game os value.
 *  3) The number of seconds from 1970 to 2000.
 */

अटल काष्ठा saved_params अणु
	अचिन्हित पूर्णांक valid;
	s64 rtc_dअगरf;
	अचिन्हित पूर्णांक av_multi_out;
पूर्ण saved_params;

अटल काष्ठा property property_rtc_dअगरf = अणु
	.name = "linux,rtc_diff",
	.length = माप(saved_params.rtc_dअगरf),
	.value = &saved_params.rtc_dअगरf,
पूर्ण;

अटल काष्ठा property property_av_multi_out = अणु
	.name = "linux,av_multi_out",
	.length = माप(saved_params.av_multi_out),
	.value = &saved_params.av_multi_out,
पूर्ण;


अटल DEFINE_MUTEX(os_area_flash_mutex);

अटल स्थिर काष्ठा ps3_os_area_flash_ops *os_area_flash_ops;

व्योम ps3_os_area_flash_रेजिस्टर(स्थिर काष्ठा ps3_os_area_flash_ops *ops)
अणु
	mutex_lock(&os_area_flash_mutex);
	os_area_flash_ops = ops;
	mutex_unlock(&os_area_flash_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(ps3_os_area_flash_रेजिस्टर);

अटल sमाप_प्रकार os_area_flash_पढ़ो(व्योम *buf, माप_प्रकार count, loff_t pos)
अणु
	sमाप_प्रकार res = -ENODEV;

	mutex_lock(&os_area_flash_mutex);
	अगर (os_area_flash_ops)
		res = os_area_flash_ops->पढ़ो(buf, count, pos);
	mutex_unlock(&os_area_flash_mutex);

	वापस res;
पूर्ण

अटल sमाप_प्रकार os_area_flash_ग_लिखो(स्थिर व्योम *buf, माप_प्रकार count, loff_t pos)
अणु
	sमाप_प्रकार res = -ENODEV;

	mutex_lock(&os_area_flash_mutex);
	अगर (os_area_flash_ops)
		res = os_area_flash_ops->ग_लिखो(buf, count, pos);
	mutex_unlock(&os_area_flash_mutex);

	वापस res;
पूर्ण


/**
 * os_area_set_property - Add or overग_लिखो a saved_params value to the device tree.
 *
 * Overग_लिखोs an existing property.
 */

अटल व्योम os_area_set_property(काष्ठा device_node *node,
	काष्ठा property *prop)
अणु
	पूर्णांक result;
	काष्ठा property *पंचांगp = of_find_property(node, prop->name, शून्य);

	अगर (पंचांगp) अणु
		pr_debug("%s:%d found %s\n", __func__, __LINE__, prop->name);
		of_हटाओ_property(node, पंचांगp);
	पूर्ण

	result = of_add_property(node, prop);

	अगर (result)
		pr_debug("%s:%d of_set_property failed\n", __func__,
			__LINE__);
पूर्ण

/**
 * os_area_get_property - Get a saved_params value from the device tree.
 *
 */

अटल व्योम __init os_area_get_property(काष्ठा device_node *node,
	काष्ठा property *prop)
अणु
	स्थिर काष्ठा property *पंचांगp = of_find_property(node, prop->name, शून्य);

	अगर (पंचांगp) अणु
		BUG_ON(prop->length != पंचांगp->length);
		स_नकल(prop->value, पंचांगp->value, prop->length);
	पूर्ण अन्यथा
		pr_debug("%s:%d not found %s\n", __func__, __LINE__,
			prop->name);
पूर्ण

अटल व्योम dump_field(अक्षर *s, स्थिर u8 *field, पूर्णांक size_of_field)
अणु
#अगर defined(DEBUG)
	पूर्णांक i;

	क्रम (i = 0; i < size_of_field; i++)
		s[i] = है_छाप(field[i]) ? field[i] : '.';
	s[i] = 0;
#पूर्ण_अगर
पूर्ण

#घोषणा dump_header(_a) _dump_header(_a, __func__, __LINE__)
अटल व्योम _dump_header(स्थिर काष्ठा os_area_header *h, स्थिर अक्षर *func,
	पूर्णांक line)
अणु
	अक्षर str[माप(h->magic_num) + 1];

	dump_field(str, h->magic_num, माप(h->magic_num));
	pr_debug("%s:%d: h.magic_num:       '%s'\n", func, line,
		str);
	pr_debug("%s:%d: h.hdr_version:     %u\n", func, line,
		h->hdr_version);
	pr_debug("%s:%d: h.db_area_offset:  %u\n", func, line,
		h->db_area_offset);
	pr_debug("%s:%d: h.ldr_area_offset: %u\n", func, line,
		h->ldr_area_offset);
	pr_debug("%s:%d: h.ldr_format:      %u\n", func, line,
		h->ldr_क्रमmat);
	pr_debug("%s:%d: h.ldr_size:        %xh\n", func, line,
		h->ldr_size);
पूर्ण

#घोषणा dump_params(_a) _dump_params(_a, __func__, __LINE__)
अटल व्योम _dump_params(स्थिर काष्ठा os_area_params *p, स्थिर अक्षर *func,
	पूर्णांक line)
अणु
	pr_debug("%s:%d: p.boot_flag:       %u\n", func, line, p->boot_flag);
	pr_debug("%s:%d: p.num_params:      %u\n", func, line, p->num_params);
	pr_debug("%s:%d: p.rtc_diff         %lld\n", func, line, p->rtc_dअगरf);
	pr_debug("%s:%d: p.av_multi_out     %u\n", func, line, p->av_multi_out);
	pr_debug("%s:%d: p.ctrl_button:     %u\n", func, line, p->ctrl_button);
	pr_debug("%s:%d: p.static_ip_addr:  %u.%u.%u.%u\n", func, line,
		p->अटल_ip_addr[0], p->अटल_ip_addr[1],
		p->अटल_ip_addr[2], p->अटल_ip_addr[3]);
	pr_debug("%s:%d: p.network_mask:    %u.%u.%u.%u\n", func, line,
		p->network_mask[0], p->network_mask[1],
		p->network_mask[2], p->network_mask[3]);
	pr_debug("%s:%d: p.default_gateway: %u.%u.%u.%u\n", func, line,
		p->शेष_gateway[0], p->शेष_gateway[1],
		p->शेष_gateway[2], p->शेष_gateway[3]);
	pr_debug("%s:%d: p.dns_primary:     %u.%u.%u.%u\n", func, line,
		p->dns_primary[0], p->dns_primary[1],
		p->dns_primary[2], p->dns_primary[3]);
	pr_debug("%s:%d: p.dns_secondary:   %u.%u.%u.%u\n", func, line,
		p->dns_secondary[0], p->dns_secondary[1],
		p->dns_secondary[2], p->dns_secondary[3]);
पूर्ण

अटल पूर्णांक verअगरy_header(स्थिर काष्ठा os_area_header *header)
अणु
	अगर (स_भेद(header->magic_num, OS_AREA_HEADER_MAGIC_NUM,
		माप(header->magic_num))) अणु
		pr_debug("%s:%d magic_num failed\n", __func__, __LINE__);
		वापस -1;
	पूर्ण

	अगर (header->hdr_version < 1) अणु
		pr_debug("%s:%d hdr_version failed\n", __func__, __LINE__);
		वापस -1;
	पूर्ण

	अगर (header->db_area_offset > header->ldr_area_offset) अणु
		pr_debug("%s:%d offsets failed\n", __func__, __LINE__);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक db_verअगरy(स्थिर काष्ठा os_area_db *db)
अणु
	अगर (स_भेद(db->magic_num, OS_AREA_DB_MAGIC_NUM,
		माप(db->magic_num))) अणु
		pr_debug("%s:%d magic_num failed\n", __func__, __LINE__);
		वापस -EINVAL;
	पूर्ण

	अगर (db->version != 1) अणु
		pr_debug("%s:%d version failed\n", __func__, __LINE__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा db_index अणु
       uपूर्णांक8_t owner:5;
       uपूर्णांक8_t key:3;
पूर्ण;

काष्ठा db_iterator अणु
	स्थिर काष्ठा os_area_db *db;
	काष्ठा os_area_db_id match_id;
	काष्ठा db_index *idx;
	काष्ठा db_index *last_idx;
	जोड़ अणु
		uपूर्णांक64_t *value_64;
		uपूर्णांक32_t *value_32;
		uपूर्णांक16_t *value_16;
	पूर्ण;
पूर्ण;

अटल अचिन्हित पूर्णांक db_align_up(अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक size)
अणु
	वापस (val + (size - 1)) & (~(size - 1));
पूर्ण

/**
 * db_क्रम_each_64 - Iterator क्रम 64 bit entries.
 *
 * A शून्य value क्रम id can be used to match all entries.
 * OS_AREA_DB_OWNER_ANY and OS_AREA_DB_KEY_ANY can be used to match all.
 */

अटल पूर्णांक db_क्रम_each_64(स्थिर काष्ठा os_area_db *db,
	स्थिर काष्ठा os_area_db_id *match_id, काष्ठा db_iterator *i)
अणु
next:
	अगर (!i->db) अणु
		i->db = db;
		i->match_id = match_id ? *match_id : os_area_db_id_any;
		i->idx = (व्योम *)db + db->index_64;
		i->last_idx = i->idx + db->count_64;
		i->value_64 = (व्योम *)db + db->index_64
			+ db_align_up(db->count_64, 8);
	पूर्ण अन्यथा अणु
		i->idx++;
		i->value_64++;
	पूर्ण

	अगर (i->idx >= i->last_idx) अणु
		pr_debug("%s:%d: reached end\n", __func__, __LINE__);
		वापस 0;
	पूर्ण

	अगर (i->match_id.owner != OS_AREA_DB_OWNER_ANY
		&& i->match_id.owner != (पूर्णांक)i->idx->owner)
		जाओ next;
	अगर (i->match_id.key != OS_AREA_DB_KEY_ANY
		&& i->match_id.key != (पूर्णांक)i->idx->key)
		जाओ next;

	वापस 1;
पूर्ण

अटल पूर्णांक db_delete_64(काष्ठा os_area_db *db, स्थिर काष्ठा os_area_db_id *id)
अणु
	काष्ठा db_iterator i;

	क्रम (i.db = शून्य; db_क्रम_each_64(db, id, &i); ) अणु

		pr_debug("%s:%d: got (%d:%d) %llxh\n", __func__, __LINE__,
			i.idx->owner, i.idx->key,
			(अचिन्हित दीर्घ दीर्घ)*i.value_64);

		i.idx->owner = 0;
		i.idx->key = 0;
		*i.value_64 = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक db_set_64(काष्ठा os_area_db *db, स्थिर काष्ठा os_area_db_id *id,
	uपूर्णांक64_t value)
अणु
	काष्ठा db_iterator i;

	pr_debug("%s:%d: (%d:%d) <= %llxh\n", __func__, __LINE__,
		id->owner, id->key, (अचिन्हित दीर्घ दीर्घ)value);

	अगर (!id->owner || id->owner == OS_AREA_DB_OWNER_ANY
		|| id->key == OS_AREA_DB_KEY_ANY) अणु
		pr_debug("%s:%d: bad id: (%d:%d)\n", __func__,
			__LINE__, id->owner, id->key);
		वापस -1;
	पूर्ण

	db_delete_64(db, id);

	i.db = शून्य;
	अगर (db_क्रम_each_64(db, &os_area_db_id_empty, &i)) अणु

		pr_debug("%s:%d: got (%d:%d) %llxh\n", __func__, __LINE__,
			i.idx->owner, i.idx->key,
			(अचिन्हित दीर्घ दीर्घ)*i.value_64);

		i.idx->owner = id->owner;
		i.idx->key = id->key;
		*i.value_64 = value;

		pr_debug("%s:%d: set (%d:%d) <= %llxh\n", __func__, __LINE__,
			i.idx->owner, i.idx->key,
			(अचिन्हित दीर्घ दीर्घ)*i.value_64);
		वापस 0;
	पूर्ण
	pr_debug("%s:%d: database full.\n",
		__func__, __LINE__);
	वापस -1;
पूर्ण

अटल पूर्णांक db_get_64(स्थिर काष्ठा os_area_db *db,
	स्थिर काष्ठा os_area_db_id *id, uपूर्णांक64_t *value)
अणु
	काष्ठा db_iterator i;

	i.db = शून्य;
	अगर (db_क्रम_each_64(db, id, &i)) अणु
		*value = *i.value_64;
		pr_debug("%s:%d: found %lld\n", __func__, __LINE__,
				(दीर्घ दीर्घ पूर्णांक)*i.value_64);
		वापस 0;
	पूर्ण
	pr_debug("%s:%d: not found\n", __func__, __LINE__);
	वापस -1;
पूर्ण

अटल पूर्णांक db_get_rtc_dअगरf(स्थिर काष्ठा os_area_db *db, पूर्णांक64_t *rtc_dअगरf)
अणु
	वापस db_get_64(db, &os_area_db_id_rtc_dअगरf, (uपूर्णांक64_t*)rtc_dअगरf);
पूर्ण

#घोषणा dump_db(a) _dump_db(a, __func__, __LINE__)
अटल व्योम _dump_db(स्थिर काष्ठा os_area_db *db, स्थिर अक्षर *func,
	पूर्णांक line)
अणु
	अक्षर str[माप(db->magic_num) + 1];

	dump_field(str, db->magic_num, माप(db->magic_num));
	pr_debug("%s:%d: db.magic_num:      '%s'\n", func, line,
		str);
	pr_debug("%s:%d: db.version:         %u\n", func, line,
		db->version);
	pr_debug("%s:%d: db.index_64:        %u\n", func, line,
		db->index_64);
	pr_debug("%s:%d: db.count_64:        %u\n", func, line,
		db->count_64);
	pr_debug("%s:%d: db.index_32:        %u\n", func, line,
		db->index_32);
	pr_debug("%s:%d: db.count_32:        %u\n", func, line,
		db->count_32);
	pr_debug("%s:%d: db.index_16:        %u\n", func, line,
		db->index_16);
	pr_debug("%s:%d: db.count_16:        %u\n", func, line,
		db->count_16);
पूर्ण

अटल व्योम os_area_db_init(काष्ठा os_area_db *db)
अणु
	क्रमागत अणु
		HEADER_SIZE = दुरत्व(काष्ठा os_area_db, _db_data),
		INDEX_64_COUNT = 64,
		VALUES_64_COUNT = 57,
		INDEX_32_COUNT = 64,
		VALUES_32_COUNT = 57,
		INDEX_16_COUNT = 64,
		VALUES_16_COUNT = 57,
	पूर्ण;

	स_रखो(db, 0, माप(काष्ठा os_area_db));

	स_नकल(db->magic_num, OS_AREA_DB_MAGIC_NUM, माप(db->magic_num));
	db->version = 1;
	db->index_64 = HEADER_SIZE;
	db->count_64 = VALUES_64_COUNT;
	db->index_32 = HEADER_SIZE
			+ INDEX_64_COUNT * माप(काष्ठा db_index)
			+ VALUES_64_COUNT * माप(u64);
	db->count_32 = VALUES_32_COUNT;
	db->index_16 = HEADER_SIZE
			+ INDEX_64_COUNT * माप(काष्ठा db_index)
			+ VALUES_64_COUNT * माप(u64)
			+ INDEX_32_COUNT * माप(काष्ठा db_index)
			+ VALUES_32_COUNT * माप(u32);
	db->count_16 = VALUES_16_COUNT;

	/* Rules to check db layout. */

	BUILD_BUG_ON(माप(काष्ठा db_index) != 1);
	BUILD_BUG_ON(माप(काष्ठा os_area_db) != 2 * OS_AREA_SEGMENT_SIZE);
	BUILD_BUG_ON(INDEX_64_COUNT & 0x7);
	BUILD_BUG_ON(VALUES_64_COUNT > INDEX_64_COUNT);
	BUILD_BUG_ON(INDEX_32_COUNT & 0x7);
	BUILD_BUG_ON(VALUES_32_COUNT > INDEX_32_COUNT);
	BUILD_BUG_ON(INDEX_16_COUNT & 0x7);
	BUILD_BUG_ON(VALUES_16_COUNT > INDEX_16_COUNT);
	BUILD_BUG_ON(HEADER_SIZE
			+ INDEX_64_COUNT * माप(काष्ठा db_index)
			+ VALUES_64_COUNT * माप(u64)
			+ INDEX_32_COUNT * माप(काष्ठा db_index)
			+ VALUES_32_COUNT * माप(u32)
			+ INDEX_16_COUNT * माप(काष्ठा db_index)
			+ VALUES_16_COUNT * माप(u16)
			> माप(काष्ठा os_area_db));
पूर्ण

/**
 * update_flash_db - Helper क्रम os_area_queue_work_handler.
 *
 */

अटल पूर्णांक update_flash_db(व्योम)
अणु
	स्थिर अचिन्हित पूर्णांक buf_len = 8 * OS_AREA_SEGMENT_SIZE;
	काष्ठा os_area_header *header;
	sमाप_प्रकार count;
	पूर्णांक error;
	loff_t pos;
	काष्ठा os_area_db* db;

	/* Read in header and db from flash. */

	header = kदो_स्मृति(buf_len, GFP_KERNEL);
	अगर (!header)
		वापस -ENOMEM;

	count = os_area_flash_पढ़ो(header, buf_len, 0);
	अगर (count < 0) अणु
		pr_debug("%s: os_area_flash_read failed %zd\n", __func__,
			 count);
		error = count;
		जाओ fail;
	पूर्ण

	pos = header->db_area_offset * OS_AREA_SEGMENT_SIZE;
	अगर (count < OS_AREA_SEGMENT_SIZE || verअगरy_header(header) ||
	    count < pos) अणु
		pr_debug("%s: verify_header failed\n", __func__);
		dump_header(header);
		error = -EINVAL;
		जाओ fail;
	पूर्ण

	/* Now got a good db offset and some maybe good db data. */

	db = (व्योम *)header + pos;

	error = db_verअगरy(db);
	अगर (error) अणु
		pr_notice("%s: Verify of flash database failed, formatting.\n",
			  __func__);
		dump_db(db);
		os_area_db_init(db);
	पूर्ण

	/* Now got good db data. */

	db_set_64(db, &os_area_db_id_rtc_dअगरf, saved_params.rtc_dअगरf);

	count = os_area_flash_ग_लिखो(db, माप(काष्ठा os_area_db), pos);
	अगर (count < 0 || count < माप(काष्ठा os_area_db)) अणु
		pr_debug("%s: os_area_flash_write failed %zd\n", __func__,
			 count);
		error = count < 0 ? count : -EIO;
	पूर्ण

fail:
	kमुक्त(header);
	वापस error;
पूर्ण

/**
 * os_area_queue_work_handler - Asynchronous ग_लिखो handler.
 *
 * An asynchronous ग_लिखो क्रम flash memory and the device tree.  Do not
 * call directly, use os_area_queue_work().
 */

अटल व्योम os_area_queue_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा device_node *node;
	पूर्णांक error;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	node = of_find_node_by_path("/");
	अगर (node) अणु
		os_area_set_property(node, &property_rtc_dअगरf);
		of_node_put(node);
	पूर्ण अन्यथा
		pr_debug("%s:%d of_find_node_by_path failed\n",
			__func__, __LINE__);

	error = update_flash_db();
	अगर (error)
		pr_warn("%s: Could not update FLASH ROM\n", __func__);

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
पूर्ण

अटल व्योम os_area_queue_work(व्योम)
अणु
	अटल DECLARE_WORK(q, os_area_queue_work_handler);

	wmb();
	schedule_work(&q);
पूर्ण

/**
 * ps3_os_area_save_params - Copy data from os area mirror to @saved_params.
 *
 * For the convenience of the guest the HV makes a copy of the os area in
 * flash to a high address in the boot memory region and then माला_दो that RAM
 * address and the byte count पूर्णांकo the repository क्रम retrieval by the guest.
 * We copy the data we want पूर्णांकo a अटल variable and allow the memory setup
 * by the HV to be claimed by the memblock manager.
 *
 * The os area mirror will not be available to a second stage kernel, and
 * the header verअगरy will fail.  In this हाल, the saved_params values will
 * be set from flash memory or the passed in device tree in ps3_os_area_init().
 */

व्योम __init ps3_os_area_save_params(व्योम)
अणु
	पूर्णांक result;
	u64 lpar_addr;
	अचिन्हित पूर्णांक size;
	काष्ठा os_area_header *header;
	काष्ठा os_area_params *params;
	काष्ठा os_area_db *db;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	result = ps3_repository_पढ़ो_boot_dat_info(&lpar_addr, &size);

	अगर (result) अणु
		pr_debug("%s:%d ps3_repository_read_boot_dat_info failed\n",
			__func__, __LINE__);
		वापस;
	पूर्ण

	header = (काष्ठा os_area_header *)__va(lpar_addr);
	params = (काष्ठा os_area_params *)__va(lpar_addr
		+ OS_AREA_SEGMENT_SIZE);

	result = verअगरy_header(header);

	अगर (result) अणु
		/* Second stage kernels निकास here. */
		pr_debug("%s:%d verify_header failed\n", __func__, __LINE__);
		dump_header(header);
		वापस;
	पूर्ण

	db = (काष्ठा os_area_db *)__va(lpar_addr
		+ header->db_area_offset * OS_AREA_SEGMENT_SIZE);

	dump_header(header);
	dump_params(params);
	dump_db(db);

	result = db_verअगरy(db) || db_get_rtc_dअगरf(db, &saved_params.rtc_dअगरf);
	अगर (result)
		saved_params.rtc_dअगरf = params->rtc_dअगरf ? params->rtc_dअगरf
			: SECONDS_FROM_1970_TO_2000;
	saved_params.av_multi_out = params->av_multi_out;
	saved_params.valid = 1;

	स_रखो(header, 0, माप(*header));

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
पूर्ण

/**
 * ps3_os_area_init - Setup os area device tree properties as needed.
 */

व्योम __init ps3_os_area_init(व्योम)
अणु
	काष्ठा device_node *node;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	node = of_find_node_by_path("/");

	अगर (!saved_params.valid && node) अणु
		/* Second stage kernels should have a dt entry. */
		os_area_get_property(node, &property_rtc_dअगरf);
		os_area_get_property(node, &property_av_multi_out);
	पूर्ण

	अगर(!saved_params.rtc_dअगरf)
		saved_params.rtc_dअगरf = SECONDS_FROM_1970_TO_2000;

	अगर (node) अणु
		os_area_set_property(node, &property_rtc_dअगरf);
		os_area_set_property(node, &property_av_multi_out);
		of_node_put(node);
	पूर्ण अन्यथा
		pr_debug("%s:%d of_find_node_by_path failed\n",
			__func__, __LINE__);

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
पूर्ण

/**
 * ps3_os_area_get_rtc_dअगरf - Returns the rtc dअगरf value.
 */

u64 ps3_os_area_get_rtc_dअगरf(व्योम)
अणु
	वापस saved_params.rtc_dअगरf;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_os_area_get_rtc_dअगरf);

/**
 * ps3_os_area_set_rtc_dअगरf - Set the rtc dअगरf value.
 *
 * An asynchronous ग_लिखो is needed to support writing updates from
 * the समयr पूर्णांकerrupt context.
 */

व्योम ps3_os_area_set_rtc_dअगरf(u64 rtc_dअगरf)
अणु
	अगर (saved_params.rtc_dअगरf != rtc_dअगरf) अणु
		saved_params.rtc_dअगरf = rtc_dअगरf;
		os_area_queue_work();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ps3_os_area_set_rtc_dअगरf);

/**
 * ps3_os_area_get_av_multi_out - Returns the शेष video mode.
 */

क्रमागत ps3_param_av_multi_out ps3_os_area_get_av_multi_out(व्योम)
अणु
    वापस saved_params.av_multi_out;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_os_area_get_av_multi_out);
