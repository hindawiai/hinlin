<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This is the official version 1.1 of sdb.h
 */
#अगर_अघोषित __SDB_H__
#घोषणा __SDB_H__
#अगर_घोषित __KERNEL__
#समावेश <linux/types.h>
#अन्यथा
#समावेश <मानक_निवेशt.h>
#पूर्ण_अगर

/*
 * All काष्ठाures are 64 bytes दीर्घ and are expected
 * to live in an array, one क्रम each पूर्णांकerconnect.
 * Most fields of the काष्ठाures are shared among the
 * various types, and most-specअगरic fields are at the
 * beginning (क्रम alignment reasons, and to keep the
 * magic number at the head of the पूर्णांकerconnect record
 */

/* Product, 40 bytes at offset 24, 8-byte aligned
 *
 * device_id is venकरोr-asचिन्हित; version is device-specअगरic,
 * date is hex (e.g 0x20120501), name is UTF-8, blank-filled
 * and not terminated with a 0 byte.
 */
काष्ठा sdb_product अणु
	uपूर्णांक64_t		venकरोr_id;	/* 0x18..0x1f */
	uपूर्णांक32_t		device_id;	/* 0x20..0x23 */
	uपूर्णांक32_t		version;	/* 0x24..0x27 */
	uपूर्णांक32_t		date;		/* 0x28..0x2b */
	uपूर्णांक8_t			name[19];	/* 0x2c..0x3e */
	uपूर्णांक8_t			record_type;	/* 0x3f */
पूर्ण;

/*
 * Component, 56 bytes at offset 8, 8-byte aligned
 *
 * The address range is first to last, inclusive
 * (क्रम example 0x100000 - 0x10ffff)
 */
काष्ठा sdb_component अणु
	uपूर्णांक64_t		addr_first;	/* 0x08..0x0f */
	uपूर्णांक64_t		addr_last;	/* 0x10..0x17 */
	काष्ठा sdb_product	product;	/* 0x18..0x3f */
पूर्ण;

/* Type of the SDB record */
क्रमागत sdb_record_type अणु
	sdb_type_पूर्णांकerconnect	= 0x00,
	sdb_type_device		= 0x01,
	sdb_type_bridge		= 0x02,
	sdb_type_पूर्णांकegration	= 0x80,
	sdb_type_repo_url	= 0x81,
	sdb_type_synthesis	= 0x82,
	sdb_type_empty		= 0xFF,
पूर्ण;

/* Type 0: पूर्णांकerconnect (first of the array)
 *
 * sdb_records is the length of the table including this first
 * record, version is 1. The bus type is क्रमागतerated later.
 */
#घोषणा				SDB_MAGIC	0x5344422d /* "SDB-" */
काष्ठा sdb_पूर्णांकerconnect अणु
	uपूर्णांक32_t		sdb_magic;	/* 0x00-0x03 */
	uपूर्णांक16_t		sdb_records;	/* 0x04-0x05 */
	uपूर्णांक8_t			sdb_version;	/* 0x06 */
	uपूर्णांक8_t			sdb_bus_type;	/* 0x07 */
	काष्ठा sdb_component	sdb_component;	/* 0x08-0x3f */
पूर्ण;

/* Type 1: device
 *
 * class is 0 क्रम "custom device", other values are
 * to be standardized; ABI version is क्रम the driver,
 * bus-specअगरic bits are defined by each bus (see below)
 */
काष्ठा sdb_device अणु
	uपूर्णांक16_t		abi_class;	/* 0x00-0x01 */
	uपूर्णांक8_t			abi_ver_major;	/* 0x02 */
	uपूर्णांक8_t			abi_ver_minor;	/* 0x03 */
	uपूर्णांक32_t		bus_specअगरic;	/* 0x04-0x07 */
	काष्ठा sdb_component	sdb_component;	/* 0x08-0x3f */
पूर्ण;

/* Type 2: bridge
 *
 * child is the address of the nested SDB table
 */
काष्ठा sdb_bridge अणु
	uपूर्णांक64_t		sdb_child;	/* 0x00-0x07 */
	काष्ठा sdb_component	sdb_component;	/* 0x08-0x3f */
पूर्ण;

/* Type 0x80: पूर्णांकegration
 *
 * all types with bit 7 set are meta-inक्रमmation, so
 * software can ignore the types it करोesn't know. Here we
 * just provide product inक्रमmation क्रम an aggregate device
 */
काष्ठा sdb_पूर्णांकegration अणु
	uपूर्णांक8_t			reserved[24];	/* 0x00-0x17 */
	काष्ठा sdb_product	product;	/* 0x08-0x3f */
पूर्ण;

/* Type 0x81: Top module repository url
 *
 * again, an inक्रमmative field that software can ignore
 */
काष्ठा sdb_repo_url अणु
	uपूर्णांक8_t			repo_url[63];	/* 0x00-0x3e */
	uपूर्णांक8_t			record_type;	/* 0x3f */
पूर्ण;

/* Type 0x82: Synthesis tool inक्रमmation
 *
 * this inक्रमmative record
 */
काष्ठा sdb_synthesis अणु
	uपूर्णांक8_t			syn_name[16];	/* 0x00-0x0f */
	uपूर्णांक8_t			commit_id[16];	/* 0x10-0x1f */
	uपूर्णांक8_t			tool_name[8];	/* 0x20-0x27 */
	uपूर्णांक32_t		tool_version;	/* 0x28-0x2b */
	uपूर्णांक32_t		date;		/* 0x2c-0x2f */
	uपूर्णांक8_t			user_name[15];	/* 0x30-0x3e */
	uपूर्णांक8_t			record_type;	/* 0x3f */
पूर्ण;

/* Type 0xff: empty
 *
 * this allows keeping empty slots during development,
 * so they can be filled later with minimal efक्रमts and
 * no misleading description is ever shipped -- hopefully.
 * It can also be used to pad a table to a desired length.
 */
काष्ठा sdb_empty अणु
	uपूर्णांक8_t			reserved[63];	/* 0x00-0x3e */
	uपूर्णांक8_t			record_type;	/* 0x3f */
पूर्ण;

/* The type of bus, क्रम bus-specअगरic flags */
क्रमागत sdb_bus_type अणु
	sdb_wishbone = 0x00,
	sdb_data     = 0x01,
पूर्ण;

#घोषणा SDB_WB_WIDTH_MASK	0x0f
#घोषणा SDB_WB_ACCESS8			0x01
#घोषणा SDB_WB_ACCESS16			0x02
#घोषणा SDB_WB_ACCESS32			0x04
#घोषणा SDB_WB_ACCESS64			0x08
#घोषणा SDB_WB_LITTLE_ENDIAN	0x80

#घोषणा SDB_DATA_READ		0x04
#घोषणा SDB_DATA_WRITE		0x02
#घोषणा SDB_DATA_EXEC		0x01

#पूर्ण_अगर /* __SDB_H__ */
