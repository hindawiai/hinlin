<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file contains the logic to work with MPEG Program-Specअगरic Inक्रमmation.
 * These are defined both in ISO/IEC 13818-1 (प्रणालीs) and ETSI EN 300 468.
 * PSI is carried in the क्रमm of table काष्ठाures, and although each table might
 * technically be broken पूर्णांकo one or more sections, we करो not करो this here,
 * hence 'table' and 'section' are पूर्णांकerchangeable क्रम vidtv.
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#अगर_अघोषित VIDTV_PSI_H
#घोषणा VIDTV_PSI_H

#समावेश <linux/types.h>

/*
 * all section lengths start immediately after the 'section_length' field
 * see ISO/IEC 13818-1 : 2000 and ETSI EN 300 468 V 1.10.1 क्रम
 * reference
 */
#घोषणा PAT_LEN_UNTIL_LAST_SECTION_NUMBER 5
#घोषणा PMT_LEN_UNTIL_PROGRAM_INFO_LENGTH 9
#घोषणा SDT_LEN_UNTIL_RESERVED_FOR_FUTURE_USE 8
#घोषणा NIT_LEN_UNTIL_NETWORK_DESCRIPTOR_LEN 7
#घोषणा EIT_LEN_UNTIL_LAST_TABLE_ID 11
#घोषणा MAX_SECTION_LEN 1021
#घोषणा EIT_MAX_SECTION_LEN 4093 /* see ETSI 300 468 v.1.10.1 p. 26 */
#घोषणा VIDTV_PAT_PID 0 /* mandated by the specs */
#घोषणा VIDTV_SDT_PID 0x0011 /* mandated by the specs */
#घोषणा VIDTV_NIT_PID 0x0010 /* mandated by the specs */
#घोषणा VIDTV_EIT_PID 0x0012 /*mandated by the specs */

क्रमागत vidtv_psi_descriptors अणु
	REGISTRATION_DESCRIPTOR	= 0x05, /* See ISO/IEC 13818-1 section 2.6.8 */
	NETWORK_NAME_DESCRIPTOR = 0x40, /* See ETSI EN 300 468 section 6.2.27 */
	SERVICE_LIST_DESCRIPTOR = 0x41, /* See ETSI EN 300 468 section 6.2.35 */
	SERVICE_DESCRIPTOR = 0x48, /* See ETSI EN 300 468 section 6.2.33 */
	SHORT_EVENT_DESCRIPTOR = 0x4d, /* See ETSI EN 300 468 section 6.2.37 */
पूर्ण;

क्रमागत vidtv_psi_stream_types अणु
	STREAM_PRIVATE_DATA = 0x06, /* see ISO/IEC 13818-1 2000 p. 48 */
पूर्ण;

/*
 * काष्ठा vidtv_psi_desc - A generic PSI descriptor type.
 * The descriptor length is an 8-bit field specअगरying the total number of bytes of the data portion
 * of the descriptor following the byte defining the value of this field.
 */
काष्ठा vidtv_psi_desc अणु
	काष्ठा vidtv_psi_desc *next;
	u8 type;
	u8 length;
	u8 data[];
पूर्ण __packed;

/*
 * काष्ठा vidtv_psi_desc_service - Service descriptor.
 * See ETSI EN 300 468 section 6.2.33.
 */
काष्ठा vidtv_psi_desc_service अणु
	काष्ठा vidtv_psi_desc *next;
	u8 type;
	u8 length;

	u8 service_type;
	u8 provider_name_len;
	अक्षर *provider_name;
	u8 service_name_len;
	अक्षर *service_name;
पूर्ण __packed;

/*
 * काष्ठा vidtv_psi_desc_registration - A registration descriptor.
 * See ISO/IEC 13818-1 section 2.6.8
 */
काष्ठा vidtv_psi_desc_registration अणु
	काष्ठा vidtv_psi_desc *next;
	u8 type;
	u8 length;

	/*
	 * The क्रमmat_identअगरier is a 32-bit value obtained from a Registration
	 * Authority as designated by ISO/IEC JTC 1/SC 29.
	 */
	__be32 क्रमmat_id;
	/*
	 * The meaning of additional_identअगरication_info bytes, अगर any, are
	 * defined by the assignee of that क्रमmat_identअगरier, and once defined
	 * they shall not change.
	 */
	u8 additional_identअगरication_info[];
पूर्ण __packed;

/*
 * काष्ठा vidtv_psi_desc_network_name - A network name descriptor
 * see ETSI EN 300 468 v1.15.1 section 6.2.27
 */
काष्ठा vidtv_psi_desc_network_name अणु
	काष्ठा vidtv_psi_desc *next;
	u8 type;
	u8 length;
	अक्षर *network_name;
पूर्ण __packed;

काष्ठा vidtv_psi_desc_service_list_entry अणु
	__be16 service_id;
	u8 service_type;
	काष्ठा vidtv_psi_desc_service_list_entry *next;
पूर्ण __packed;

/*
 * काष्ठा vidtv_psi_desc_service_list - A service list descriptor
 * see ETSI EN 300 468 v1.15.1 section 6.2.35
 */
काष्ठा vidtv_psi_desc_service_list अणु
	काष्ठा vidtv_psi_desc *next;
	u8 type;
	u8 length;
	काष्ठा vidtv_psi_desc_service_list_entry *service_list;
पूर्ण __packed;

/*
 * काष्ठा vidtv_psi_desc_लघु_event - A लघु event descriptor
 * see ETSI EN 300 468 v1.15.1 section 6.2.37
 */
काष्ठा vidtv_psi_desc_लघु_event अणु
	काष्ठा vidtv_psi_desc *next;
	u8 type;
	u8 length;
	अक्षर *iso_language_code;
	u8 event_name_len;
	अक्षर *event_name;
	u8 text_len;
	अक्षर *text;
पूर्ण __packed;

काष्ठा vidtv_psi_desc_लघु_event
*vidtv_psi_लघु_event_desc_init(काष्ठा vidtv_psi_desc *head,
				 अक्षर *iso_language_code,
				 अक्षर *event_name,
				 अक्षर *text);

/*
 * काष्ठा vidtv_psi_table_header - A header that is present क्रम all PSI tables.
 */
काष्ठा vidtv_psi_table_header अणु
	u8  table_id;

	__be16 bitfield; /* syntax: 1, zero: 1, one: 2, section_length: 13 */

	__be16 id; /* TS ID */
	u8  current_next:1;
	u8  version:5;
	u8  one2:2;
	u8  section_id;	/* section_number */
	u8  last_section; /* last_section_number */
पूर्ण __packed;

/*
 * काष्ठा vidtv_psi_table_pat_program - A single program in the PAT
 * See ISO/IEC 13818-1 : 2000 p.43
 */
काष्ठा vidtv_psi_table_pat_program अणु
	__be16 service_id;
	__be16 bitfield; /* reserved: 3, program_map_pid/network_pid: 13 */
	काष्ठा vidtv_psi_table_pat_program *next;
पूर्ण __packed;

/*
 * काष्ठा vidtv_psi_table_pat - The Program Allocation Table (PAT)
 * See ISO/IEC 13818-1 : 2000 p.43
 */
काष्ठा vidtv_psi_table_pat अणु
	काष्ठा vidtv_psi_table_header header;
	u16 num_pat;
	u16 num_pmt;
	काष्ठा vidtv_psi_table_pat_program *program;
पूर्ण __packed;

/*
 * काष्ठा vidtv_psi_table_sdt_service - Represents a service in the SDT.
 * see ETSI EN 300 468 v1.15.1 section 5.2.3.
 */
काष्ठा vidtv_psi_table_sdt_service अणु
	__be16 service_id;
	u8 EIT_present_following:1;
	u8 EIT_schedule:1;
	u8 reserved:6;
	__be16 bitfield; /* running_status: 3, मुक्त_ca:1, desc_loop_len:12 */
	काष्ठा vidtv_psi_desc *descriptor;
	काष्ठा vidtv_psi_table_sdt_service *next;
पूर्ण __packed;

/*
 * काष्ठा vidtv_psi_table_sdt - Represents the Service Description Table
 * see ETSI EN 300 468 v1.15.1 section 5.2.3.
 */

काष्ठा vidtv_psi_table_sdt अणु
	काष्ठा vidtv_psi_table_header header;
	__be16 network_id; /* original_network_id */
	u8  reserved;
	काष्ठा vidtv_psi_table_sdt_service *service;
पूर्ण __packed;

/*
 * क्रमागत service_running_status - Status of a SDT service.
 * see ETSI EN 300 468 v1.15.1 section 5.2.3 table 6.
 */
क्रमागत service_running_status अणु
	RUNNING = 0x4,
पूर्ण;

/*
 * क्रमागत service_type - The type of a SDT service.
 * see ETSI EN 300 468 v1.15.1 section 6.2.33, table 81.
 */
क्रमागत service_type अणु
	/* see ETSI EN 300 468 v1.15.1 p. 77 */
	DIGITAL_TELEVISION_SERVICE = 0x1,
	DIGITAL_RADIO_SOUND_SERVICE = 0X2,
पूर्ण;

/*
 * काष्ठा vidtv_psi_table_pmt_stream - A single stream in the PMT.
 * See ISO/IEC 13818-1 : 2000 p.46.
 */
काष्ठा vidtv_psi_table_pmt_stream अणु
	u8 type;
	__be16 bitfield; /* reserved: 3, elementary_pid: 13 */
	__be16 bitfield2; /*reserved: 4, zero: 2, desc_length: 10 */
	काष्ठा vidtv_psi_desc *descriptor;
	काष्ठा vidtv_psi_table_pmt_stream *next;
पूर्ण __packed;

/*
 * काष्ठा vidtv_psi_table_pmt - The Program Map Table (PMT).
 * See ISO/IEC 13818-1 : 2000 p.46.
 */
काष्ठा vidtv_psi_table_pmt अणु
	काष्ठा vidtv_psi_table_header header;
	__be16 bitfield; /* reserved:3, pcr_pid: 13 */
	__be16 bitfield2; /* reserved: 4, zero: 2, desc_len: 10 */
	काष्ठा vidtv_psi_desc *descriptor;
	काष्ठा vidtv_psi_table_pmt_stream *stream;
पूर्ण __packed;

/**
 * काष्ठा psi_ग_लिखो_args - Arguments क्रम the PSI packetizer.
 * @dest_buf: The buffer to ग_लिखो पूर्णांकo.
 * @from: PSI data to be copied.
 * @len: How much to ग_लिखो.
 * @dest_offset: where to start writing in the dest_buffer.
 * @pid: TS packet ID.
 * @new_psi_section: Set when starting a table section.
 * @continuity_counter: Incremented on every new packet.
 * @is_crc: Set when writing the CRC at the end.
 * @dest_buf_sz: The size of the dest_buffer
 * @crc: a poपूर्णांकer to store the crc क्रम this chunk
 */
काष्ठा psi_ग_लिखो_args अणु
	व्योम *dest_buf;
	व्योम *from;
	माप_प्रकार len;
	u32 dest_offset;
	u16 pid;
	bool new_psi_section;
	u8 *continuity_counter;
	bool is_crc;
	u32 dest_buf_sz;
	u32 *crc;
पूर्ण;

/**
 * काष्ठा desc_ग_लिखो_args - Arguments in order to ग_लिखो a descriptor.
 * @dest_buf: The buffer to ग_लिखो पूर्णांकo.
 * @dest_offset: where to start writing in the dest_buffer.
 * @desc: A poपूर्णांकer to the descriptor
 * @pid: TS packet ID.
 * @continuity_counter: Incremented on every new packet.
 * @dest_buf_sz: The size of the dest_buffer
 * @crc: a poपूर्णांकer to store the crc क्रम this chunk
 */
काष्ठा desc_ग_लिखो_args अणु
	व्योम *dest_buf;
	u32 dest_offset;
	काष्ठा vidtv_psi_desc *desc;
	u16 pid;
	u8 *continuity_counter;
	u32 dest_buf_sz;
	u32 *crc;
पूर्ण;

/**
 * काष्ठा crc32_ग_लिखो_args - Arguments in order to ग_लिखो the CRC at the end of
 * the PSI tables.
 * @dest_buf: The buffer to ग_लिखो पूर्णांकo.
 * @dest_offset: where to start writing in the dest_buffer.
 * @crc: the CRC value to ग_लिखो
 * @pid: TS packet ID.
 * @continuity_counter: Incremented on every new packet.
 * @dest_buf_sz: The size of the dest_buffer
 */
काष्ठा crc32_ग_लिखो_args अणु
	व्योम *dest_buf;
	u32 dest_offset;
	__be32 crc;
	u16 pid;
	u8 *continuity_counter;
	u32 dest_buf_sz;
पूर्ण;

/**
 * काष्ठा header_ग_लिखो_args - Arguments in order to ग_लिखो the common table
 * header
 * @dest_buf: The buffer to ग_लिखो पूर्णांकo.
 * @dest_offset: where to start writing in the dest_buffer.
 * @h: a poपूर्णांकer to the header.
 * @pid: TS packet ID.
 * @continuity_counter: Incremented on every new packet.
 * @dest_buf_sz: The size of the dest_buffer
 * @crc: a poपूर्णांकer to store the crc क्रम this chunk
 */
काष्ठा header_ग_लिखो_args अणु
	व्योम *dest_buf;
	u32 dest_offset;
	काष्ठा vidtv_psi_table_header *h;
	u16 pid;
	u8 *continuity_counter;
	u32 dest_buf_sz;
	u32 *crc;
पूर्ण;

काष्ठा vidtv_psi_desc_service *vidtv_psi_service_desc_init(काष्ठा vidtv_psi_desc *head,
							   क्रमागत service_type service_type,
							   अक्षर *service_name,
							   अक्षर *provider_name);

काष्ठा vidtv_psi_desc_registration
*vidtv_psi_registration_desc_init(काष्ठा vidtv_psi_desc *head,
				  __be32 क्रमmat_id,
				  u8 *additional_ident_info,
				  u32 additional_info_len);

काष्ठा vidtv_psi_desc_network_name
*vidtv_psi_network_name_desc_init(काष्ठा vidtv_psi_desc *head, अक्षर *network_name);

काष्ठा vidtv_psi_desc_service_list
*vidtv_psi_service_list_desc_init(काष्ठा vidtv_psi_desc *head,
				  काष्ठा vidtv_psi_desc_service_list_entry *entry);

काष्ठा vidtv_psi_table_pat_program
*vidtv_psi_pat_program_init(काष्ठा vidtv_psi_table_pat_program *head,
			    u16 service_id,
			    u16 program_map_pid);

काष्ठा vidtv_psi_table_pmt_stream*
vidtv_psi_pmt_stream_init(काष्ठा vidtv_psi_table_pmt_stream *head,
			  क्रमागत vidtv_psi_stream_types stream_type,
			  u16 es_pid);

काष्ठा vidtv_psi_table_pat *vidtv_psi_pat_table_init(u16 transport_stream_id);

काष्ठा vidtv_psi_table_pmt *vidtv_psi_pmt_table_init(u16 program_number,
						     u16 pcr_pid);

काष्ठा vidtv_psi_table_sdt *vidtv_psi_sdt_table_init(u16 network_id,
						     u16 transport_stream_id);

काष्ठा vidtv_psi_table_sdt_service*
vidtv_psi_sdt_service_init(काष्ठा vidtv_psi_table_sdt_service *head,
			   u16 service_id,
			   bool eit_schedule,
			   bool eit_present_following);

व्योम
vidtv_psi_desc_destroy(काष्ठा vidtv_psi_desc *desc);

व्योम
vidtv_psi_pat_program_destroy(काष्ठा vidtv_psi_table_pat_program *p);

व्योम
vidtv_psi_pat_table_destroy(काष्ठा vidtv_psi_table_pat *p);

व्योम
vidtv_psi_pmt_stream_destroy(काष्ठा vidtv_psi_table_pmt_stream *s);

व्योम
vidtv_psi_pmt_table_destroy(काष्ठा vidtv_psi_table_pmt *pmt);

व्योम
vidtv_psi_sdt_table_destroy(काष्ठा vidtv_psi_table_sdt *sdt);

व्योम
vidtv_psi_sdt_service_destroy(काष्ठा vidtv_psi_table_sdt_service *service);

/**
 * vidtv_psi_sdt_service_assign - Assigns the service loop to the SDT.
 * @sdt: The SDT to assign to.
 * @service: The service loop (one or more services)
 *
 * This will मुक्त the previous service loop in the table.
 * This will assign ownership of the service loop to the table, i.e. the table
 * will मुक्त this service loop when a call to its destroy function is made.
 */
व्योम
vidtv_psi_sdt_service_assign(काष्ठा vidtv_psi_table_sdt *sdt,
			     काष्ठा vidtv_psi_table_sdt_service *service);

/**
 * vidtv_psi_desc_assign - Assigns a descriptor loop at some poपूर्णांक
 * @to: Where to assign this descriptor loop to
 * @desc: The descriptor loop that will be asचिन्हित.
 *
 * This will मुक्त the loop in 'to', अगर any.
 */
व्योम vidtv_psi_desc_assign(काष्ठा vidtv_psi_desc **to,
			   काष्ठा vidtv_psi_desc *desc);

/**
 * vidtv_pmt_desc_assign - Assigns a descriptor loop at some poपूर्णांक in a PMT section.
 * @pmt: The PMT section that will contain the descriptor loop
 * @to: Where in the PMT to assign this descriptor loop to
 * @desc: The descriptor loop that will be asचिन्हित.
 *
 * This will मुक्त the loop in 'to', अगर any.
 * This will assign ownership of the loop to the table, i.e. the table
 * will मुक्त this loop when a call to its destroy function is made.
 */
व्योम vidtv_pmt_desc_assign(काष्ठा vidtv_psi_table_pmt *pmt,
			   काष्ठा vidtv_psi_desc **to,
			   काष्ठा vidtv_psi_desc *desc);

/**
 * vidtv_sdt_desc_assign - Assigns a descriptor loop at some poपूर्णांक in a SDT.
 * @sdt: The SDT that will contain the descriptor loop
 * @to: Where in the PMT to assign this descriptor loop to
 * @desc: The descriptor loop that will be asचिन्हित.
 *
 * This will मुक्त the loop in 'to', अगर any.
 * This will assign ownership of the loop to the table, i.e. the table
 * will मुक्त this loop when a call to its destroy function is made.
 */
व्योम vidtv_sdt_desc_assign(काष्ठा vidtv_psi_table_sdt *sdt,
			   काष्ठा vidtv_psi_desc **to,
			   काष्ठा vidtv_psi_desc *desc);

/**
 * vidtv_psi_pat_program_assign - Assigns the program loop to the PAT.
 * @pat: The PAT to assign to.
 * @p: The program loop (one or more programs)
 *
 * This will मुक्त the previous program loop in the table.
 * This will assign ownership of the program loop to the table, i.e. the table
 * will मुक्त this program loop when a call to its destroy function is made.
 */
व्योम vidtv_psi_pat_program_assign(काष्ठा vidtv_psi_table_pat *pat,
				  काष्ठा vidtv_psi_table_pat_program *p);

/**
 * vidtv_psi_pmt_stream_assign - Assigns the stream loop to the PAT.
 * @pmt: The PMT to assign to.
 * @s: The stream loop (one or more streams)
 *
 * This will मुक्त the previous stream loop in the table.
 * This will assign ownership of the stream loop to the table, i.e. the table
 * will मुक्त this stream loop when a call to its destroy function is made.
 */
व्योम vidtv_psi_pmt_stream_assign(काष्ठा vidtv_psi_table_pmt *pmt,
				 काष्ठा vidtv_psi_table_pmt_stream *s);

काष्ठा vidtv_psi_desc *vidtv_psi_desc_clone(काष्ठा vidtv_psi_desc *desc);

/**
 * vidtv_psi_pmt_create_sec_क्रम_each_pat_entry - Create a PMT section क्रम each
 * program found in the PAT
 * @pat: The PAT to look क्रम programs.
 * @pcr_pid: packet ID क्रम the PCR to be used क्रम the program described in this
 * PMT section
 */
काष्ठा vidtv_psi_table_pmt**
vidtv_psi_pmt_create_sec_क्रम_each_pat_entry(काष्ठा vidtv_psi_table_pat *pat, u16 pcr_pid);

/**
 * vidtv_psi_pmt_get_pid - Get the TS PID क्रम a PMT section.
 * @section: The PMT section whose PID we want to retrieve.
 * @pat: The PAT table to look पूर्णांकo.
 *
 * Returns: the TS PID क्रम 'section'
 */
u16 vidtv_psi_pmt_get_pid(काष्ठा vidtv_psi_table_pmt *section,
			  काष्ठा vidtv_psi_table_pat *pat);

/**
 * vidtv_psi_pat_table_update_sec_len - Recompute and update the PAT section length.
 * @pat: The PAT whose length is to be updated.
 *
 * This will traverse the table and accumulate the length of its components,
 * which is then used to replace the 'section_length' field.
 *
 * If section_length > MAX_SECTION_LEN, the operation fails.
 */
व्योम vidtv_psi_pat_table_update_sec_len(काष्ठा vidtv_psi_table_pat *pat);

/**
 * vidtv_psi_pmt_table_update_sec_len - Recompute and update the PMT section length.
 * @pmt: The PMT whose length is to be updated.
 *
 * This will traverse the table and accumulate the length of its components,
 * which is then used to replace the 'section_length' field.
 *
 * If section_length > MAX_SECTION_LEN, the operation fails.
 */
व्योम vidtv_psi_pmt_table_update_sec_len(काष्ठा vidtv_psi_table_pmt *pmt);

/**
 * vidtv_psi_sdt_table_update_sec_len - Recompute and update the SDT section length.
 * @sdt: The SDT whose length is to be updated.
 *
 * This will traverse the table and accumulate the length of its components,
 * which is then used to replace the 'section_length' field.
 *
 * If section_length > MAX_SECTION_LEN, the operation fails.
 */
व्योम vidtv_psi_sdt_table_update_sec_len(काष्ठा vidtv_psi_table_sdt *sdt);

/**
 * काष्ठा vidtv_psi_pat_ग_लिखो_args - Arguments क्रम writing a PAT table
 * @buf: The destination buffer.
 * @offset: The offset पूर्णांकo the destination buffer.
 * @pat: A poपूर्णांकer to the PAT.
 * @buf_sz: The size of the destination buffer.
 * @continuity_counter: A poपूर्णांकer to the CC. Incremented on every new packet.
 *
 */
काष्ठा vidtv_psi_pat_ग_लिखो_args अणु
	अक्षर *buf;
	u32 offset;
	काष्ठा vidtv_psi_table_pat *pat;
	u32 buf_sz;
	u8 *continuity_counter;
पूर्ण;

/**
 * vidtv_psi_pat_ग_लिखो_पूर्णांकo - Write PAT as MPEG-TS packets पूर्णांकo a buffer.
 * @args: An instance of काष्ठा vidtv_psi_pat_ग_लिखो_args
 *
 * This function ग_लिखोs the MPEG TS packets क्रम a PAT table पूर्णांकo a buffer.
 * Calling code will usually generate the PAT via a call to its init function
 * and thus is responsible क्रम मुक्तing it.
 *
 * Return: The number of bytes written पूर्णांकo the buffer. This is NOT
 * equal to the size of the PAT, since more space is needed क्रम TS headers during TS
 * encapsulation.
 */
u32 vidtv_psi_pat_ग_लिखो_पूर्णांकo(काष्ठा vidtv_psi_pat_ग_लिखो_args *args);

/**
 * काष्ठा vidtv_psi_sdt_ग_लिखो_args - Arguments क्रम writing a SDT table
 * @buf: The destination buffer.
 * @offset: The offset पूर्णांकo the destination buffer.
 * @sdt: A poपूर्णांकer to the SDT.
 * @buf_sz: The size of the destination buffer.
 * @continuity_counter: A poपूर्णांकer to the CC. Incremented on every new packet.
 *
 */

काष्ठा vidtv_psi_sdt_ग_लिखो_args अणु
	अक्षर *buf;
	u32 offset;
	काष्ठा vidtv_psi_table_sdt *sdt;
	u32 buf_sz;
	u8 *continuity_counter;
पूर्ण;

/**
 * vidtv_psi_sdt_ग_लिखो_पूर्णांकo - Write SDT as MPEG-TS packets पूर्णांकo a buffer.
 * @args: an instance of काष्ठा vidtv_psi_sdt_ग_लिखो_args
 *
 * This function ग_लिखोs the MPEG TS packets क्रम a SDT table पूर्णांकo a buffer.
 * Calling code will usually generate the SDT via a call to its init function
 * and thus is responsible क्रम मुक्तing it.
 *
 * Return: The number of bytes written पूर्णांकo the buffer. This is NOT
 * equal to the size of the SDT, since more space is needed क्रम TS headers during TS
 * encapsulation.
 */
u32 vidtv_psi_sdt_ग_लिखो_पूर्णांकo(काष्ठा vidtv_psi_sdt_ग_लिखो_args *args);

/**
 * काष्ठा vidtv_psi_pmt_ग_लिखो_args - Arguments क्रम writing a PMT section
 * @buf: The destination buffer.
 * @offset: The offset पूर्णांकo the destination buffer.
 * @pmt: A poपूर्णांकer to the PMT.
 * @pid: Program ID
 * @buf_sz: The size of the destination buffer.
 * @continuity_counter: A poपूर्णांकer to the CC. Incremented on every new packet.
 * @pcr_pid: The TS PID used क्रम the PSI packets. All channels will share the
 * same PCR.
 */
काष्ठा vidtv_psi_pmt_ग_लिखो_args अणु
	अक्षर *buf;
	u32 offset;
	काष्ठा vidtv_psi_table_pmt *pmt;
	u16 pid;
	u32 buf_sz;
	u8 *continuity_counter;
	u16 pcr_pid;
पूर्ण;

/**
 * vidtv_psi_pmt_ग_लिखो_पूर्णांकo - Write PMT as MPEG-TS packets पूर्णांकo a buffer.
 * @args: an instance of काष्ठा vidtv_psi_pmt_ग_लिखो_args
 *
 * This function ग_लिखोs the MPEG TS packets क्रम a PMT section पूर्णांकo a buffer.
 * Calling code will usually generate the PMT section via a call to its init function
 * and thus is responsible क्रम मुक्तing it.
 *
 * Return: The number of bytes written पूर्णांकo the buffer. This is NOT
 * equal to the size of the PMT section, since more space is needed क्रम TS headers
 * during TS encapsulation.
 */
u32 vidtv_psi_pmt_ग_लिखो_पूर्णांकo(काष्ठा vidtv_psi_pmt_ग_लिखो_args *args);

/**
 * vidtv_psi_find_pmt_sec - Finds the PMT section क्रम 'program_num'
 * @pmt_sections: The sections to look पूर्णांकo.
 * @nsections: The number of sections.
 * @program_num: The 'program_num' from PAT poपूर्णांकing to a PMT section.
 *
 * Return: A poपूर्णांकer to the PMT, अगर found, or शून्य.
 */
काष्ठा vidtv_psi_table_pmt *vidtv_psi_find_pmt_sec(काष्ठा vidtv_psi_table_pmt **pmt_sections,
						   u16 nsections,
						   u16 program_num);

u16 vidtv_psi_get_pat_program_pid(काष्ठा vidtv_psi_table_pat_program *p);
u16 vidtv_psi_pmt_stream_get_elem_pid(काष्ठा vidtv_psi_table_pmt_stream *s);

/**
 * काष्ठा vidtv_psi_table_transport - A entry in the TS loop क्रम the NIT and/or other tables.
 * See ETSI 300 468 section 5.2.1
 * @transport_id: The TS ID being described
 * @network_id: The network_id that contains the TS ID
 * @bitfield: Contains the descriptor loop length
 * @descriptor: A descriptor loop
 * @next: Poपूर्णांकer to the next entry
 *
 */
काष्ठा vidtv_psi_table_transport अणु
	__be16 transport_id;
	__be16 network_id;
	__be16 bitfield; /* desc_len: 12, reserved: 4 */
	काष्ठा vidtv_psi_desc *descriptor;
	काष्ठा vidtv_psi_table_transport *next;
पूर्ण __packed;

/**
 * काष्ठा vidtv_psi_table_nit - A Network Inक्रमmation Table (NIT). See ETSI 300
 * 468 section 5.2.1
 * @header: A PSI table header
 * @bitfield: Contains the network descriptor length
 * @descriptor: A descriptor loop describing the network
 * @bitfield2: Contains the transport stream loop length
 * @transport: The transport stream loop
 *
 */
काष्ठा vidtv_psi_table_nit अणु
	काष्ठा vidtv_psi_table_header header;
	__be16 bitfield; /* network_desc_len: 12, reserved:4 */
	काष्ठा vidtv_psi_desc *descriptor;
	__be16 bitfield2; /* ts_loop_len: 12, reserved: 4 */
	काष्ठा vidtv_psi_table_transport *transport;
पूर्ण __packed;

काष्ठा vidtv_psi_table_nit
*vidtv_psi_nit_table_init(u16 network_id,
			  u16 transport_stream_id,
			  अक्षर *network_name,
			  काष्ठा vidtv_psi_desc_service_list_entry *service_list);

/**
 * काष्ठा vidtv_psi_nit_ग_लिखो_args - Arguments क्रम writing a NIT section
 * @buf: The destination buffer.
 * @offset: The offset पूर्णांकo the destination buffer.
 * @nit: A poपूर्णांकer to the NIT
 * @buf_sz: The size of the destination buffer.
 * @continuity_counter: A poपूर्णांकer to the CC. Incremented on every new packet.
 *
 */
काष्ठा vidtv_psi_nit_ग_लिखो_args अणु
	अक्षर *buf;
	u32 offset;
	काष्ठा vidtv_psi_table_nit *nit;
	u32 buf_sz;
	u8 *continuity_counter;
पूर्ण;

/**
 * vidtv_psi_nit_ग_लिखो_पूर्णांकo - Write NIT as MPEG-TS packets पूर्णांकo a buffer.
 * @args: an instance of काष्ठा vidtv_psi_nit_ग_लिखो_args
 *
 * This function ग_लिखोs the MPEG TS packets क्रम a NIT table पूर्णांकo a buffer.
 * Calling code will usually generate the NIT via a call to its init function
 * and thus is responsible क्रम मुक्तing it.
 *
 * Return: The number of bytes written पूर्णांकo the buffer. This is NOT
 * equal to the size of the NIT, since more space is needed क्रम TS headers during TS
 * encapsulation.
 */
u32 vidtv_psi_nit_ग_लिखो_पूर्णांकo(काष्ठा vidtv_psi_nit_ग_लिखो_args *args);

व्योम vidtv_psi_nit_table_destroy(काष्ठा vidtv_psi_table_nit *nit);

/*
 * काष्ठा vidtv_psi_desc_लघु_event - A लघु event descriptor
 * see ETSI EN 300 468 v1.15.1 section 6.2.37
 */
काष्ठा vidtv_psi_table_eit_event अणु
	__be16 event_id;
	u8 start_समय[5];
	u8 duration[3];
	__be16 bitfield; /* desc_length: 12, मुक्त_CA_mode: 1, running_status: 1 */
	काष्ठा vidtv_psi_desc *descriptor;
	काष्ठा vidtv_psi_table_eit_event *next;
पूर्ण __packed;

/*
 * काष्ठा vidtv_psi_table_eit - A Event Inक्रमmation Table (EIT)
 * See ETSI 300 468 section 5.2.4
 */
काष्ठा vidtv_psi_table_eit अणु
	काष्ठा vidtv_psi_table_header header;
	__be16 transport_id;
	__be16 network_id;
	u8 last_segment;
	u8 last_table_id;
	काष्ठा vidtv_psi_table_eit_event *event;
पूर्ण __packed;

काष्ठा vidtv_psi_table_eit
*vidtv_psi_eit_table_init(u16 network_id,
			  u16 transport_stream_id,
			  __be16 service_id);

/**
 * काष्ठा vidtv_psi_eit_ग_लिखो_args - Arguments क्रम writing an EIT section
 * @buf: The destination buffer.
 * @offset: The offset पूर्णांकo the destination buffer.
 * @eit: A poपूर्णांकer to the EIT
 * @buf_sz: The size of the destination buffer.
 * @continuity_counter: A poपूर्णांकer to the CC. Incremented on every new packet.
 *
 */
काष्ठा vidtv_psi_eit_ग_लिखो_args अणु
	अक्षर *buf;
	u32 offset;
	काष्ठा vidtv_psi_table_eit *eit;
	u32 buf_sz;
	u8 *continuity_counter;
पूर्ण;

/**
 * vidtv_psi_eit_ग_लिखो_पूर्णांकo - Write EIT as MPEG-TS packets पूर्णांकo a buffer.
 * @args: an instance of काष्ठा vidtv_psi_nit_ग_लिखो_args
 *
 * This function ग_लिखोs the MPEG TS packets क्रम a EIT table पूर्णांकo a buffer.
 * Calling code will usually generate the EIT via a call to its init function
 * and thus is responsible क्रम मुक्तing it.
 *
 * Return: The number of bytes written पूर्णांकo the buffer. This is NOT
 * equal to the size of the EIT, since more space is needed क्रम TS headers during TS
 * encapsulation.
 */
u32 vidtv_psi_eit_ग_लिखो_पूर्णांकo(काष्ठा vidtv_psi_eit_ग_लिखो_args *args);

व्योम vidtv_psi_eit_table_destroy(काष्ठा vidtv_psi_table_eit *eit);

/**
 * vidtv_psi_eit_table_update_sec_len - Recompute and update the EIT section length.
 * @eit: The EIT whose length is to be updated.
 *
 * This will traverse the table and accumulate the length of its components,
 * which is then used to replace the 'section_length' field.
 *
 * If section_length > EIT_MAX_SECTION_LEN, the operation fails.
 */
व्योम vidtv_psi_eit_table_update_sec_len(काष्ठा vidtv_psi_table_eit *eit);

/**
 * vidtv_psi_eit_event_assign - Assigns the event loop to the EIT.
 * @eit: The EIT to assign to.
 * @e: The event loop
 *
 * This will मुक्त the previous event loop in the table.
 * This will assign ownership of the stream loop to the table, i.e. the table
 * will मुक्त this stream loop when a call to its destroy function is made.
 */
व्योम vidtv_psi_eit_event_assign(काष्ठा vidtv_psi_table_eit *eit,
				काष्ठा vidtv_psi_table_eit_event *e);

काष्ठा vidtv_psi_table_eit_event
*vidtv_psi_eit_event_init(काष्ठा vidtv_psi_table_eit_event *head, u16 event_id);

व्योम vidtv_psi_eit_event_destroy(काष्ठा vidtv_psi_table_eit_event *e);

#पूर्ण_अगर // VIDTV_PSI_H
