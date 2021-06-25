<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_POWERPC_PERF_HV_24X7_CATALOG_H_
#घोषणा LINUX_POWERPC_PERF_HV_24X7_CATALOG_H_

#समावेश <linux/types.h>

/* From करोcument "24x7 Event and Group Catalog Formats Proposal" v0.15 */

काष्ठा hv_24x7_catalog_page_0 अणु
#घोषणा HV_24X7_CATALOG_MAGIC 0x32347837 /* "24x7" in ASCII */
	__be32 magic;
	__be32 length; /* In 4096 byte pages */
	__be64 version; /* XXX: arbitrary? what's the meaning/useage/purpose? */
	__u8 build_समय_stamp[16]; /* "YYYYMMDDHHMMSS\0\0" */
	__u8 reserved2[32];
	__be16 schema_data_offs; /* in 4096 byte pages */
	__be16 schema_data_len;  /* in 4096 byte pages */
	__be16 schema_entry_count;
	__u8 reserved3[2];
	__be16 event_data_offs;
	__be16 event_data_len;
	__be16 event_entry_count;
	__u8 reserved4[2];
	__be16 group_data_offs; /* in 4096 byte pages */
	__be16 group_data_len;  /* in 4096 byte pages */
	__be16 group_entry_count;
	__u8 reserved5[2];
	__be16 क्रमmula_data_offs; /* in 4096 byte pages */
	__be16 क्रमmula_data_len;  /* in 4096 byte pages */
	__be16 क्रमmula_entry_count;
	__u8 reserved6[2];
पूर्ण __packed;

काष्ठा hv_24x7_event_data अणु
	__be16 length; /* in bytes, must be a multiple of 16 */
	__u8 reserved1[2];
	__u8 करोमुख्य; /* Chip = 1, Core = 2 */
	__u8 reserved2[1];
	__be16 event_group_record_offs; /* in bytes, must be 8 byte aligned */
	__be16 event_group_record_len; /* in bytes */

	/* in bytes, offset from event_group_record */
	__be16 event_counter_offs;

	/* verअगरied_state, unverअगरied_state, caveat_state, broken_state, ... */
	__be32 flags;

	__be16 primary_group_ix;
	__be16 group_count;
	__be16 event_name_len;
	__u8 reमुख्यder[];
	/* __u8 event_name[event_name_len - 2]; */
	/* __be16 event_description_len; */
	/* __u8 event_desc[event_description_len - 2]; */
	/* __be16 detailed_desc_len; */
	/* __u8 detailed_desc[detailed_desc_len - 2]; */
पूर्ण __packed;

#पूर्ण_अगर
