<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains the logic to work with MPEG Program-Specअगरic Inक्रमmation.
 * These are defined both in ISO/IEC 13818-1 (प्रणालीs) and ETSI EN 300 468.
 * PSI is carried in the क्रमm of table काष्ठाures, and although each table might
 * technically be broken पूर्णांकo one or more sections, we करो not करो this here,
 * hence 'table' and 'section' are पूर्णांकerchangeable क्रम vidtv.
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s, %d: " fmt, __func__, __LINE__

#समावेश <linux/bcd.h>
#समावेश <linux/crc32.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय.स>
#समावेश <linux/types.h>

#समावेश "vidtv_common.h"
#समावेश "vidtv_psi.h"
#समावेश "vidtv_ts.h"

#घोषणा CRC_SIZE_IN_BYTES 4
#घोषणा MAX_VERSION_NUM 32
#घोषणा INITIAL_CRC 0xffffffff
#घोषणा ISO_LANGUAGE_CODE_LEN 3

अटल स्थिर u32 CRC_LUT[256] = अणु
	/* from libdvbv5 */
	0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b,
	0x1a864db2, 0x1e475005, 0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
	0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd, 0x4c11db70, 0x48d0c6c7,
	0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
	0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3,
	0x709f7b7a, 0x745e66cd, 0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,
	0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5, 0xbe2b5b58, 0xbaea46ef,
	0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
	0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb,
	0xceb42022, 0xca753d95, 0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
	0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d, 0x34867077, 0x30476dc0,
	0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
	0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4,
	0x0808d07d, 0x0cc9cdca, 0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,
	0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02, 0x5e9f46bf, 0x5a5e5b08,
	0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
	0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc,
	0xb6238b25, 0xb2e29692, 0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,
	0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a, 0xe0b41de7, 0xe4750050,
	0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
	0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34,
	0xdc3abded, 0xd8fba05a, 0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,
	0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb, 0x4f040d56, 0x4bc510e1,
	0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
	0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5,
	0x3f9b762c, 0x3b5a6b9b, 0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,
	0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623, 0xf12f560e, 0xf5ee4bb9,
	0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
	0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd,
	0xcda1f604, 0xc960ebb3, 0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
	0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b, 0x9b3660c6, 0x9ff77d71,
	0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
	0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2,
	0x470cdd2b, 0x43cdc09c, 0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,
	0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24, 0x119b4be9, 0x155a565e,
	0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
	0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a,
	0x2d15ebe3, 0x29d4f654, 0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,
	0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c, 0xe3a1cbc1, 0xe760d676,
	0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
	0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662,
	0x933eb0bb, 0x97ffad0c, 0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,
	0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
पूर्ण;

अटल u32 dvb_crc32(u32 crc, u8 *data, u32 len)
अणु
	/* from libdvbv5 */
	जबतक (len--)
		crc = (crc << 8) ^ CRC_LUT[((crc >> 24) ^ *data++) & 0xff];
	वापस crc;
पूर्ण

अटल व्योम vidtv_psi_update_version_num(काष्ठा vidtv_psi_table_header *h)
अणु
	h->version++;
पूर्ण

अटल u16 vidtv_psi_get_sec_len(काष्ठा vidtv_psi_table_header *h)
अणु
	u16 mask;
	u16 ret;

	mask = GENMASK(11, 0);

	ret = be16_to_cpu(h->bitfield) & mask;
	वापस ret;
पूर्ण

u16 vidtv_psi_get_pat_program_pid(काष्ठा vidtv_psi_table_pat_program *p)
अणु
	u16 mask;
	u16 ret;

	mask = GENMASK(12, 0);

	ret = be16_to_cpu(p->bitfield) & mask;
	वापस ret;
पूर्ण

u16 vidtv_psi_pmt_stream_get_elem_pid(काष्ठा vidtv_psi_table_pmt_stream *s)
अणु
	u16 mask;
	u16 ret;

	mask = GENMASK(12, 0);

	ret = be16_to_cpu(s->bitfield) & mask;
	वापस ret;
पूर्ण

अटल व्योम vidtv_psi_set_desc_loop_len(__be16 *bitfield, u16 new_len,
					u8 desc_len_nbits)
अणु
	__be16 new;
	u16 mask;

	mask = GENMASK(15, desc_len_nbits);

	new = cpu_to_be16((be16_to_cpu(*bitfield) & mask) | new_len);
	*bitfield = new;
पूर्ण

अटल व्योम vidtv_psi_set_sec_len(काष्ठा vidtv_psi_table_header *h, u16 new_len)
अणु
	u16 old_len = vidtv_psi_get_sec_len(h);
	__be16 new;
	u16 mask;

	mask = GENMASK(15, 13);

	new = cpu_to_be16((be16_to_cpu(h->bitfield) & mask) | new_len);

	अगर (old_len > MAX_SECTION_LEN)
		pr_warn_ratelimited("section length: %d > %d, old len was %d\n",
				    new_len,
				    MAX_SECTION_LEN,
				    old_len);

	h->bitfield = new;
पूर्ण

/*
 * Packetize PSI sections पूर्णांकo TS packets:
 * push a TS header (4bytes) every 184 bytes
 * manage the continuity_counter
 * add stuffing (i.e. padding bytes) after the CRC
 */
अटल u32 vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(काष्ठा psi_ग_लिखो_args *args)
अणु
	काष्ठा vidtv_mpeg_ts ts_header = अणु
		.sync_byte = TS_SYNC_BYTE,
		.bitfield = cpu_to_be16((args->new_psi_section << 14) | args->pid),
		.scrambling = 0,
		.payload = 1,
		.adaptation_field = 0, /* no adaptation field */
	पूर्ण;
	u32 nbytes_past_boundary = (args->dest_offset % TS_PACKET_LEN);
	bool aligned = (nbytes_past_boundary == 0);
	u32 reमुख्यing_len = args->len;
	u32 payload_ग_लिखो_len = 0;
	u32 payload_offset = 0;
	u32 nbytes = 0;

	अगर (!args->crc && !args->is_crc)
		pr_warn_ratelimited("Missing CRC for chunk\n");

	अगर (args->crc)
		*args->crc = dvb_crc32(*args->crc, args->from, args->len);

	अगर (args->new_psi_section && !aligned) अणु
		pr_warn_ratelimited("Cannot write a new PSI section in a misaligned buffer\n");

		/* क्रमcibly align and hope क्रम the best */
		nbytes += vidtv_स_रखो(args->dest_buf,
				       args->dest_offset + nbytes,
				       args->dest_buf_sz,
				       TS_FILL_BYTE,
				       TS_PACKET_LEN - nbytes_past_boundary);
	पूर्ण

	जबतक (reमुख्यing_len) अणु
		nbytes_past_boundary = (args->dest_offset + nbytes) % TS_PACKET_LEN;
		aligned = (nbytes_past_boundary == 0);

		अगर (aligned) अणु
			/* अगर at a packet boundary, ग_लिखो a new TS header */
			ts_header.continuity_counter = *args->continuity_counter;

			nbytes += vidtv_स_नकल(args->dest_buf,
					       args->dest_offset + nbytes,
					       args->dest_buf_sz,
					       &ts_header,
					       माप(ts_header));
			/*
			 * This will trigger a discontinuity अगर the buffer is full,
			 * effectively dropping the packet.
			 */
			vidtv_ts_inc_cc(args->continuity_counter);
		पूर्ण

		/* ग_लिखो the poपूर्णांकer_field in the first byte of the payload */
		अगर (args->new_psi_section)
			nbytes += vidtv_स_रखो(args->dest_buf,
					       args->dest_offset + nbytes,
					       args->dest_buf_sz,
					       0x0,
					       1);

		/* ग_लिखो as much of the payload as possible */
		nbytes_past_boundary = (args->dest_offset + nbytes) % TS_PACKET_LEN;
		payload_ग_लिखो_len = min(TS_PACKET_LEN - nbytes_past_boundary, reमुख्यing_len);

		nbytes += vidtv_स_नकल(args->dest_buf,
				       args->dest_offset + nbytes,
				       args->dest_buf_sz,
				       args->from + payload_offset,
				       payload_ग_लिखो_len);

		/* 'payload_write_len' written from a total of 'len' requested*/
		reमुख्यing_len -= payload_ग_लिखो_len;
		payload_offset += payload_ग_लिखो_len;
	पूर्ण

	/*
	 * fill the rest of the packet अगर there is any reमुख्यing space unused
	 */

	nbytes_past_boundary = (args->dest_offset + nbytes) % TS_PACKET_LEN;

	अगर (args->is_crc)
		nbytes += vidtv_स_रखो(args->dest_buf,
				       args->dest_offset + nbytes,
				       args->dest_buf_sz,
				       TS_FILL_BYTE,
				       TS_PACKET_LEN - nbytes_past_boundary);

	वापस nbytes;
पूर्ण

अटल u32 table_section_crc32_ग_लिखो_पूर्णांकo(काष्ठा crc32_ग_लिखो_args *args)
अणु
	काष्ठा psi_ग_लिखो_args psi_args = अणु
		.dest_buf           = args->dest_buf,
		.from               = &args->crc,
		.len                = CRC_SIZE_IN_BYTES,
		.dest_offset        = args->dest_offset,
		.pid                = args->pid,
		.new_psi_section    = false,
		.continuity_counter = args->continuity_counter,
		.is_crc             = true,
		.dest_buf_sz        = args->dest_buf_sz,
	पूर्ण;

	/* the CRC is the last entry in the section */

	वापस vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);
पूर्ण

अटल व्योम vidtv_psi_desc_chain(काष्ठा vidtv_psi_desc *head, काष्ठा vidtv_psi_desc *desc)
अणु
	अगर (head) अणु
		जबतक (head->next)
			head = head->next;

		head->next = desc;
	पूर्ण
पूर्ण

काष्ठा vidtv_psi_desc_service *vidtv_psi_service_desc_init(काष्ठा vidtv_psi_desc *head,
							   क्रमागत service_type service_type,
							   अक्षर *service_name,
							   अक्षर *provider_name)
अणु
	काष्ठा vidtv_psi_desc_service *desc;
	u32 service_name_len = service_name ? म_माप(service_name) : 0;
	u32 provider_name_len = provider_name ? म_माप(provider_name) : 0;

	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस शून्य;

	desc->type = SERVICE_DESCRIPTOR;

	desc->length = माप_field(काष्ठा vidtv_psi_desc_service, service_type)
		       + माप_field(काष्ठा vidtv_psi_desc_service, provider_name_len)
		       + provider_name_len
		       + माप_field(काष्ठा vidtv_psi_desc_service, service_name_len)
		       + service_name_len;

	desc->service_type = service_type;

	desc->service_name_len = service_name_len;

	अगर (service_name && service_name_len)
		desc->service_name = kstrdup(service_name, GFP_KERNEL);

	desc->provider_name_len = provider_name_len;

	अगर (provider_name && provider_name_len)
		desc->provider_name = kstrdup(provider_name, GFP_KERNEL);

	vidtv_psi_desc_chain(head, (काष्ठा vidtv_psi_desc *)desc);
	वापस desc;
पूर्ण

काष्ठा vidtv_psi_desc_registration
*vidtv_psi_registration_desc_init(काष्ठा vidtv_psi_desc *head,
				  __be32 क्रमmat_id,
				  u8 *additional_ident_info,
				  u32 additional_info_len)
अणु
	काष्ठा vidtv_psi_desc_registration *desc;

	desc = kzalloc(माप(*desc) + माप(क्रमmat_id) + additional_info_len, GFP_KERNEL);
	अगर (!desc)
		वापस शून्य;

	desc->type = REGISTRATION_DESCRIPTOR;

	desc->length = माप_field(काष्ठा vidtv_psi_desc_registration, क्रमmat_id)
		       + additional_info_len;

	desc->क्रमmat_id = क्रमmat_id;

	अगर (additional_ident_info && additional_info_len)
		स_नकल(desc->additional_identअगरication_info,
		       additional_ident_info,
		       additional_info_len);

	vidtv_psi_desc_chain(head, (काष्ठा vidtv_psi_desc *)desc);
	वापस desc;
पूर्ण

काष्ठा vidtv_psi_desc_network_name
*vidtv_psi_network_name_desc_init(काष्ठा vidtv_psi_desc *head, अक्षर *network_name)
अणु
	u32 network_name_len = network_name ? म_माप(network_name) : 0;
	काष्ठा vidtv_psi_desc_network_name *desc;

	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस शून्य;

	desc->type = NETWORK_NAME_DESCRIPTOR;

	desc->length = network_name_len;

	अगर (network_name && network_name_len)
		desc->network_name = kstrdup(network_name, GFP_KERNEL);

	vidtv_psi_desc_chain(head, (काष्ठा vidtv_psi_desc *)desc);
	वापस desc;
पूर्ण

काष्ठा vidtv_psi_desc_service_list
*vidtv_psi_service_list_desc_init(काष्ठा vidtv_psi_desc *head,
				  काष्ठा vidtv_psi_desc_service_list_entry *entry)
अणु
	काष्ठा vidtv_psi_desc_service_list_entry *curr_e = शून्य;
	काष्ठा vidtv_psi_desc_service_list_entry *head_e = शून्य;
	काष्ठा vidtv_psi_desc_service_list_entry *prev_e = शून्य;
	काष्ठा vidtv_psi_desc_service_list *desc;
	u16 length = 0;

	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस शून्य;

	desc->type = SERVICE_LIST_DESCRIPTOR;

	जबतक (entry) अणु
		curr_e = kzalloc(माप(*curr_e), GFP_KERNEL);
		अगर (!curr_e) अणु
			जबतक (head_e) अणु
				curr_e = head_e;
				head_e = head_e->next;
				kमुक्त(curr_e);
			पूर्ण
			kमुक्त(desc);
			वापस शून्य;
		पूर्ण

		curr_e->service_id = entry->service_id;
		curr_e->service_type = entry->service_type;

		length += माप(काष्ठा vidtv_psi_desc_service_list_entry) -
			  माप(काष्ठा vidtv_psi_desc_service_list_entry *);

		अगर (!head_e)
			head_e = curr_e;
		अगर (prev_e)
			prev_e->next = curr_e;

		prev_e = curr_e;
		entry = entry->next;
	पूर्ण

	desc->length = length;
	desc->service_list = head_e;

	vidtv_psi_desc_chain(head, (काष्ठा vidtv_psi_desc *)desc);
	वापस desc;
पूर्ण

काष्ठा vidtv_psi_desc_लघु_event
*vidtv_psi_लघु_event_desc_init(काष्ठा vidtv_psi_desc *head,
				 अक्षर *iso_language_code,
				 अक्षर *event_name,
				 अक्षर *text)
अणु
	u32 iso_len =  iso_language_code ? म_माप(iso_language_code) : 0;
	u32 event_name_len = event_name ? म_माप(event_name) : 0;
	काष्ठा vidtv_psi_desc_लघु_event *desc;
	u32 text_len =  text ? म_माप(text) : 0;

	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस शून्य;

	desc->type = SHORT_EVENT_DESCRIPTOR;

	desc->length = ISO_LANGUAGE_CODE_LEN +
		       माप_field(काष्ठा vidtv_psi_desc_लघु_event, event_name_len) +
		       event_name_len +
		       माप_field(काष्ठा vidtv_psi_desc_लघु_event, text_len) +
		       text_len;

	desc->event_name_len = event_name_len;
	desc->text_len = text_len;

	अगर (iso_len != ISO_LANGUAGE_CODE_LEN)
		iso_language_code = "eng";

	desc->iso_language_code = kstrdup(iso_language_code, GFP_KERNEL);

	अगर (event_name && event_name_len)
		desc->event_name = kstrdup(event_name, GFP_KERNEL);

	अगर (text && text_len)
		desc->text = kstrdup(text, GFP_KERNEL);

	vidtv_psi_desc_chain(head, (काष्ठा vidtv_psi_desc *)desc);
	वापस desc;
पूर्ण

काष्ठा vidtv_psi_desc *vidtv_psi_desc_clone(काष्ठा vidtv_psi_desc *desc)
अणु
	काष्ठा vidtv_psi_desc_network_name *desc_network_name;
	काष्ठा vidtv_psi_desc_service_list *desc_service_list;
	काष्ठा vidtv_psi_desc_लघु_event  *desc_लघु_event;
	काष्ठा vidtv_psi_desc_service *service;
	काष्ठा vidtv_psi_desc *head = शून्य;
	काष्ठा vidtv_psi_desc *prev = शून्य;
	काष्ठा vidtv_psi_desc *curr = शून्य;

	जबतक (desc) अणु
		चयन (desc->type) अणु
		हाल SERVICE_DESCRIPTOR:
			service = (काष्ठा vidtv_psi_desc_service *)desc;
			curr = (काष्ठा vidtv_psi_desc *)
			       vidtv_psi_service_desc_init(head,
							   service->service_type,
							   service->service_name,
							   service->provider_name);
		अवरोध;

		हाल NETWORK_NAME_DESCRIPTOR:
			desc_network_name = (काष्ठा vidtv_psi_desc_network_name *)desc;
			curr = (काष्ठा vidtv_psi_desc *)
			       vidtv_psi_network_name_desc_init(head,
								desc_network_name->network_name);
		अवरोध;

		हाल SERVICE_LIST_DESCRIPTOR:
			desc_service_list = (काष्ठा vidtv_psi_desc_service_list *)desc;
			curr = (काष्ठा vidtv_psi_desc *)
			       vidtv_psi_service_list_desc_init(head,
								desc_service_list->service_list);
		अवरोध;

		हाल SHORT_EVENT_DESCRIPTOR:
			desc_लघु_event = (काष्ठा vidtv_psi_desc_लघु_event *)desc;
			curr = (काष्ठा vidtv_psi_desc *)
			       vidtv_psi_लघु_event_desc_init(head,
							       desc_लघु_event->iso_language_code,
							       desc_लघु_event->event_name,
							       desc_लघु_event->text);
		अवरोध;

		हाल REGISTRATION_DESCRIPTOR:
		शेष:
			curr = kmemdup(desc, माप(*desc) + desc->length, GFP_KERNEL);
			अगर (!curr)
				वापस शून्य;
		पूर्ण

		अगर (!curr)
			वापस शून्य;

		curr->next = शून्य;
		अगर (!head)
			head = curr;
		अगर (prev)
			prev->next = curr;

		prev = curr;
		desc = desc->next;
	पूर्ण

	वापस head;
पूर्ण

व्योम vidtv_psi_desc_destroy(काष्ठा vidtv_psi_desc *desc)
अणु
	काष्ठा vidtv_psi_desc_service_list_entry *sl_entry_पंचांगp = शून्य;
	काष्ठा vidtv_psi_desc_service_list_entry *sl_entry = शून्य;
	काष्ठा vidtv_psi_desc *curr = desc;
	काष्ठा vidtv_psi_desc *पंचांगp  = शून्य;

	जबतक (curr) अणु
		पंचांगp  = curr;
		curr = curr->next;

		चयन (पंचांगp->type) अणु
		हाल SERVICE_DESCRIPTOR:
			kमुक्त(((काष्ठा vidtv_psi_desc_service *)पंचांगp)->provider_name);
			kमुक्त(((काष्ठा vidtv_psi_desc_service *)पंचांगp)->service_name);

			अवरोध;
		हाल REGISTRATION_DESCRIPTOR:
			/* nothing to करो */
			अवरोध;

		हाल NETWORK_NAME_DESCRIPTOR:
			kमुक्त(((काष्ठा vidtv_psi_desc_network_name *)पंचांगp)->network_name);
			अवरोध;

		हाल SERVICE_LIST_DESCRIPTOR:
			sl_entry = ((काष्ठा vidtv_psi_desc_service_list *)पंचांगp)->service_list;
			जबतक (sl_entry) अणु
				sl_entry_पंचांगp = sl_entry;
				sl_entry = sl_entry->next;
				kमुक्त(sl_entry_पंचांगp);
			पूर्ण
			अवरोध;

		हाल SHORT_EVENT_DESCRIPTOR:
			kमुक्त(((काष्ठा vidtv_psi_desc_लघु_event *)पंचांगp)->iso_language_code);
			kमुक्त(((काष्ठा vidtv_psi_desc_लघु_event *)पंचांगp)->event_name);
			kमुक्त(((काष्ठा vidtv_psi_desc_लघु_event *)पंचांगp)->text);
		अवरोध;

		शेष:
			pr_warn_ratelimited("Possible leak: not handling descriptor type %d\n",
					    पंचांगp->type);
			अवरोध;
		पूर्ण

		kमुक्त(पंचांगp);
	पूर्ण
पूर्ण

अटल u16
vidtv_psi_desc_comp_loop_len(काष्ठा vidtv_psi_desc *desc)
अणु
	u32 length = 0;

	अगर (!desc)
		वापस 0;

	जबतक (desc) अणु
		length += माप_field(काष्ठा vidtv_psi_desc, type);
		length += माप_field(काष्ठा vidtv_psi_desc, length);
		length += desc->length; /* from 'length' field until the end of the descriptor */
		desc    = desc->next;
	पूर्ण

	वापस length;
पूर्ण

व्योम vidtv_psi_desc_assign(काष्ठा vidtv_psi_desc **to,
			   काष्ठा vidtv_psi_desc *desc)
अणु
	अगर (desc == *to)
		वापस;

	अगर (*to)
		vidtv_psi_desc_destroy(*to);

	*to = desc;
पूर्ण

व्योम vidtv_pmt_desc_assign(काष्ठा vidtv_psi_table_pmt *pmt,
			   काष्ठा vidtv_psi_desc **to,
			   काष्ठा vidtv_psi_desc *desc)
अणु
	vidtv_psi_desc_assign(to, desc);
	vidtv_psi_pmt_table_update_sec_len(pmt);

	अगर (vidtv_psi_get_sec_len(&pmt->header) > MAX_SECTION_LEN)
		vidtv_psi_desc_assign(to, शून्य);

	vidtv_psi_update_version_num(&pmt->header);
पूर्ण

व्योम vidtv_sdt_desc_assign(काष्ठा vidtv_psi_table_sdt *sdt,
			   काष्ठा vidtv_psi_desc **to,
			   काष्ठा vidtv_psi_desc *desc)
अणु
	vidtv_psi_desc_assign(to, desc);
	vidtv_psi_sdt_table_update_sec_len(sdt);

	अगर (vidtv_psi_get_sec_len(&sdt->header) > MAX_SECTION_LEN)
		vidtv_psi_desc_assign(to, शून्य);

	vidtv_psi_update_version_num(&sdt->header);
पूर्ण

अटल u32 vidtv_psi_desc_ग_लिखो_पूर्णांकo(काष्ठा desc_ग_लिखो_args *args)
अणु
	काष्ठा psi_ग_लिखो_args psi_args = अणु
		.dest_buf           = args->dest_buf,
		.from               = &args->desc->type,
		.pid                = args->pid,
		.new_psi_section    = false,
		.continuity_counter = args->continuity_counter,
		.is_crc             = false,
		.dest_buf_sz        = args->dest_buf_sz,
		.crc                = args->crc,
		.len		    = माप_field(काष्ठा vidtv_psi_desc, type) +
				      माप_field(काष्ठा vidtv_psi_desc, length),
	पूर्ण;
	काष्ठा vidtv_psi_desc_service_list_entry *serv_list_entry = शून्य;
	u32 nbytes = 0;

	psi_args.dest_offset        = args->dest_offset + nbytes;

	nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

	चयन (args->desc->type) अणु
	हाल SERVICE_DESCRIPTOR:
		psi_args.dest_offset = args->dest_offset + nbytes;
		psi_args.len = माप_field(काष्ठा vidtv_psi_desc_service, service_type) +
			       माप_field(काष्ठा vidtv_psi_desc_service, provider_name_len);
		psi_args.from = &((काष्ठा vidtv_psi_desc_service *)args->desc)->service_type;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

		psi_args.dest_offset = args->dest_offset + nbytes;
		psi_args.len = ((काष्ठा vidtv_psi_desc_service *)args->desc)->provider_name_len;
		psi_args.from = ((काष्ठा vidtv_psi_desc_service *)args->desc)->provider_name;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

		psi_args.dest_offset = args->dest_offset + nbytes;
		psi_args.len = माप_field(काष्ठा vidtv_psi_desc_service, service_name_len);
		psi_args.from = &((काष्ठा vidtv_psi_desc_service *)args->desc)->service_name_len;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

		psi_args.dest_offset = args->dest_offset + nbytes;
		psi_args.len = ((काष्ठा vidtv_psi_desc_service *)args->desc)->service_name_len;
		psi_args.from = ((काष्ठा vidtv_psi_desc_service *)args->desc)->service_name;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);
		अवरोध;

	हाल NETWORK_NAME_DESCRIPTOR:
		psi_args.dest_offset = args->dest_offset + nbytes;
		psi_args.len = args->desc->length;
		psi_args.from = ((काष्ठा vidtv_psi_desc_network_name *)args->desc)->network_name;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);
		अवरोध;

	हाल SERVICE_LIST_DESCRIPTOR:
		serv_list_entry = ((काष्ठा vidtv_psi_desc_service_list *)args->desc)->service_list;
		जबतक (serv_list_entry) अणु
			psi_args.dest_offset = args->dest_offset + nbytes;
			psi_args.len = माप(काष्ठा vidtv_psi_desc_service_list_entry) -
				       माप(काष्ठा vidtv_psi_desc_service_list_entry *);
			psi_args.from = serv_list_entry;

			nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

			serv_list_entry = serv_list_entry->next;
		पूर्ण
		अवरोध;

	हाल SHORT_EVENT_DESCRIPTOR:
		psi_args.dest_offset = args->dest_offset + nbytes;
		psi_args.len = ISO_LANGUAGE_CODE_LEN;
		psi_args.from = ((काष्ठा vidtv_psi_desc_लघु_event *)
				  args->desc)->iso_language_code;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

		psi_args.dest_offset = args->dest_offset + nbytes;
		psi_args.len = माप_field(काष्ठा vidtv_psi_desc_लघु_event, event_name_len);
		psi_args.from = &((काष्ठा vidtv_psi_desc_लघु_event *)
				  args->desc)->event_name_len;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

		psi_args.dest_offset = args->dest_offset + nbytes;
		psi_args.len = ((काष्ठा vidtv_psi_desc_लघु_event *)args->desc)->event_name_len;
		psi_args.from = ((काष्ठा vidtv_psi_desc_लघु_event *)args->desc)->event_name;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

		psi_args.dest_offset = args->dest_offset + nbytes;
		psi_args.len = माप_field(काष्ठा vidtv_psi_desc_लघु_event, text_len);
		psi_args.from = &((काष्ठा vidtv_psi_desc_लघु_event *)args->desc)->text_len;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

		psi_args.dest_offset = args->dest_offset + nbytes;
		psi_args.len = ((काष्ठा vidtv_psi_desc_लघु_event *)args->desc)->text_len;
		psi_args.from = ((काष्ठा vidtv_psi_desc_लघु_event *)args->desc)->text;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

		अवरोध;

	हाल REGISTRATION_DESCRIPTOR:
	शेष:
		psi_args.dest_offset = args->dest_offset + nbytes;
		psi_args.len = args->desc->length;
		psi_args.from = &args->desc->data;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);
		अवरोध;
	पूर्ण

	वापस nbytes;
पूर्ण

अटल u32
vidtv_psi_table_header_ग_लिखो_पूर्णांकo(काष्ठा header_ग_लिखो_args *args)
अणु
	काष्ठा psi_ग_लिखो_args psi_args = अणु
		.dest_buf           = args->dest_buf,
		.from               = args->h,
		.len                = माप(काष्ठा vidtv_psi_table_header),
		.dest_offset        = args->dest_offset,
		.pid                = args->pid,
		.new_psi_section    = true,
		.continuity_counter = args->continuity_counter,
		.is_crc             = false,
		.dest_buf_sz        = args->dest_buf_sz,
		.crc                = args->crc,
	पूर्ण;

	वापस vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);
पूर्ण

व्योम
vidtv_psi_pat_table_update_sec_len(काष्ठा vidtv_psi_table_pat *pat)
अणु
	u16 length = 0;
	u32 i;

	/* see ISO/IEC 13818-1 : 2000 p.43 */

	/* from immediately after 'section_length' until 'last_section_number'*/
	length += PAT_LEN_UNTIL_LAST_SECTION_NUMBER;

	/* करो not count the poपूर्णांकer */
	क्रम (i = 0; i < pat->num_pat; ++i)
		length += माप(काष्ठा vidtv_psi_table_pat_program) -
			  माप(काष्ठा vidtv_psi_table_pat_program *);

	length += CRC_SIZE_IN_BYTES;

	vidtv_psi_set_sec_len(&pat->header, length);
पूर्ण

व्योम vidtv_psi_pmt_table_update_sec_len(काष्ठा vidtv_psi_table_pmt *pmt)
अणु
	काष्ठा vidtv_psi_table_pmt_stream *s = pmt->stream;
	u16 desc_loop_len;
	u16 length = 0;

	/* see ISO/IEC 13818-1 : 2000 p.46 */

	/* from immediately after 'section_length' until 'program_info_length'*/
	length += PMT_LEN_UNTIL_PROGRAM_INFO_LENGTH;

	desc_loop_len = vidtv_psi_desc_comp_loop_len(pmt->descriptor);
	vidtv_psi_set_desc_loop_len(&pmt->bitfield2, desc_loop_len, 10);

	length += desc_loop_len;

	जबतक (s) अणु
		/* skip both poपूर्णांकers at the end */
		length += माप(काष्ठा vidtv_psi_table_pmt_stream) -
			  माप(काष्ठा vidtv_psi_desc *) -
			  माप(काष्ठा vidtv_psi_table_pmt_stream *);

		desc_loop_len = vidtv_psi_desc_comp_loop_len(s->descriptor);
		vidtv_psi_set_desc_loop_len(&s->bitfield2, desc_loop_len, 10);

		length += desc_loop_len;

		s = s->next;
	पूर्ण

	length += CRC_SIZE_IN_BYTES;

	vidtv_psi_set_sec_len(&pmt->header, length);
पूर्ण

व्योम vidtv_psi_sdt_table_update_sec_len(काष्ठा vidtv_psi_table_sdt *sdt)
अणु
	काष्ठा vidtv_psi_table_sdt_service *s = sdt->service;
	u16 desc_loop_len;
	u16 length = 0;

	/* see ETSI EN 300 468 V 1.10.1 p.24 */

	/*
	 * from immediately after 'section_length' until
	 * 'reserved_for_future_use'
	 */
	length += SDT_LEN_UNTIL_RESERVED_FOR_FUTURE_USE;

	जबतक (s) अणु
		/* skip both poपूर्णांकers at the end */
		length += माप(काष्ठा vidtv_psi_table_sdt_service) -
			  माप(काष्ठा vidtv_psi_desc *) -
			  माप(काष्ठा vidtv_psi_table_sdt_service *);

		desc_loop_len = vidtv_psi_desc_comp_loop_len(s->descriptor);
		vidtv_psi_set_desc_loop_len(&s->bitfield, desc_loop_len, 12);

		length += desc_loop_len;

		s = s->next;
	पूर्ण

	length += CRC_SIZE_IN_BYTES;
	vidtv_psi_set_sec_len(&sdt->header, length);
पूर्ण

काष्ठा vidtv_psi_table_pat_program*
vidtv_psi_pat_program_init(काष्ठा vidtv_psi_table_pat_program *head,
			   u16 service_id,
			   u16 program_map_pid)
अणु
	काष्ठा vidtv_psi_table_pat_program *program;
	स्थिर u16 RESERVED = 0x07;

	program = kzalloc(माप(*program), GFP_KERNEL);
	अगर (!program)
		वापस शून्य;

	program->service_id = cpu_to_be16(service_id);

	/* pid क्रम the PMT section in the TS */
	program->bitfield = cpu_to_be16((RESERVED << 13) | program_map_pid);
	program->next = शून्य;

	अगर (head) अणु
		जबतक (head->next)
			head = head->next;

		head->next = program;
	पूर्ण

	वापस program;
पूर्ण

व्योम
vidtv_psi_pat_program_destroy(काष्ठा vidtv_psi_table_pat_program *p)
अणु
	काष्ठा vidtv_psi_table_pat_program *पंचांगp  = शून्य;
	काष्ठा vidtv_psi_table_pat_program *curr = p;

	जबतक (curr) अणु
		पंचांगp  = curr;
		curr = curr->next;
		kमुक्त(पंचांगp);
	पूर्ण
पूर्ण

/* This function transfers ownership of p to the table */
व्योम
vidtv_psi_pat_program_assign(काष्ठा vidtv_psi_table_pat *pat,
			     काष्ठा vidtv_psi_table_pat_program *p)
अणु
	काष्ठा vidtv_psi_table_pat_program *program;
	u16 program_count;

	करो अणु
		program_count = 0;
		program = p;

		अगर (p == pat->program)
			वापस;

		जबतक (program) अणु
			++program_count;
			program = program->next;
		पूर्ण

		pat->num_pat = program_count;
		pat->program  = p;

		/* Recompute section length */
		vidtv_psi_pat_table_update_sec_len(pat);

		p = शून्य;
	पूर्ण जबतक (vidtv_psi_get_sec_len(&pat->header) > MAX_SECTION_LEN);

	vidtv_psi_update_version_num(&pat->header);
पूर्ण

काष्ठा vidtv_psi_table_pat *vidtv_psi_pat_table_init(u16 transport_stream_id)
अणु
	काष्ठा vidtv_psi_table_pat *pat;
	स्थिर u16 SYNTAX = 0x1;
	स्थिर u16 ZERO = 0x0;
	स्थिर u16 ONES = 0x03;

	pat = kzalloc(माप(*pat), GFP_KERNEL);
	अगर (!pat)
		वापस शून्य;

	pat->header.table_id = 0x0;

	pat->header.bitfield = cpu_to_be16((SYNTAX << 15) | (ZERO << 14) | (ONES << 12));
	pat->header.id           = cpu_to_be16(transport_stream_id);
	pat->header.current_next = 0x1;

	pat->header.version = 0x1f;

	pat->header.one2         = 0x03;
	pat->header.section_id   = 0x0;
	pat->header.last_section = 0x0;

	vidtv_psi_pat_table_update_sec_len(pat);

	वापस pat;
पूर्ण

u32 vidtv_psi_pat_ग_लिखो_पूर्णांकo(काष्ठा vidtv_psi_pat_ग_लिखो_args *args)
अणु
	काष्ठा vidtv_psi_table_pat_program *p = args->pat->program;
	काष्ठा header_ग_लिखो_args h_args       = अणु
		.dest_buf           = args->buf,
		.dest_offset        = args->offset,
		.pid                = VIDTV_PAT_PID,
		.h                  = &args->pat->header,
		.continuity_counter = args->continuity_counter,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा psi_ग_लिखो_args psi_args        = अणु
		.dest_buf           = args->buf,
		.pid                = VIDTV_PAT_PID,
		.new_psi_section    = false,
		.continuity_counter = args->continuity_counter,
		.is_crc             = false,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा crc32_ग_लिखो_args c_args        = अणु
		.dest_buf           = args->buf,
		.pid                = VIDTV_PAT_PID,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	u32 crc = INITIAL_CRC;
	u32 nbytes = 0;

	vidtv_psi_pat_table_update_sec_len(args->pat);

	h_args.crc = &crc;

	nbytes += vidtv_psi_table_header_ग_लिखो_पूर्णांकo(&h_args);

	/* note that the field 'u16 programs' is not really part of the PAT */

	psi_args.crc = &crc;

	जबतक (p) अणु
		/* copy the PAT programs */
		psi_args.from = p;
		/* skip the poपूर्णांकer */
		psi_args.len = माप(*p) -
			       माप(काष्ठा vidtv_psi_table_pat_program *);
		psi_args.dest_offset = args->offset + nbytes;
		psi_args.continuity_counter = args->continuity_counter;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

		p = p->next;
	पूर्ण

	c_args.dest_offset        = args->offset + nbytes;
	c_args.continuity_counter = args->continuity_counter;
	c_args.crc                = cpu_to_be32(crc);

	/* Write the CRC32 at the end */
	nbytes += table_section_crc32_ग_लिखो_पूर्णांकo(&c_args);

	वापस nbytes;
पूर्ण

व्योम
vidtv_psi_pat_table_destroy(काष्ठा vidtv_psi_table_pat *p)
अणु
	vidtv_psi_pat_program_destroy(p->program);
	kमुक्त(p);
पूर्ण

काष्ठा vidtv_psi_table_pmt_stream*
vidtv_psi_pmt_stream_init(काष्ठा vidtv_psi_table_pmt_stream *head,
			  क्रमागत vidtv_psi_stream_types stream_type,
			  u16 es_pid)
अणु
	काष्ठा vidtv_psi_table_pmt_stream *stream;
	स्थिर u16 RESERVED1 = 0x07;
	स्थिर u16 RESERVED2 = 0x0f;
	स्थिर u16 ZERO = 0x0;
	u16 desc_loop_len;

	stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (!stream)
		वापस शून्य;

	stream->type = stream_type;

	stream->bitfield = cpu_to_be16((RESERVED1 << 13) | es_pid);

	desc_loop_len = vidtv_psi_desc_comp_loop_len(stream->descriptor);

	stream->bitfield2 = cpu_to_be16((RESERVED2 << 12) |
					(ZERO << 10)      |
					desc_loop_len);
	stream->next = शून्य;

	अगर (head) अणु
		जबतक (head->next)
			head = head->next;

		head->next = stream;
	पूर्ण

	वापस stream;
पूर्ण

व्योम vidtv_psi_pmt_stream_destroy(काष्ठा vidtv_psi_table_pmt_stream *s)
अणु
	काष्ठा vidtv_psi_table_pmt_stream *पंचांगp_stream  = शून्य;
	काष्ठा vidtv_psi_table_pmt_stream *curr_stream = s;

	जबतक (curr_stream) अणु
		पंचांगp_stream  = curr_stream;
		curr_stream = curr_stream->next;
		vidtv_psi_desc_destroy(पंचांगp_stream->descriptor);
		kमुक्त(पंचांगp_stream);
	पूर्ण
पूर्ण

व्योम vidtv_psi_pmt_stream_assign(काष्ठा vidtv_psi_table_pmt *pmt,
				 काष्ठा vidtv_psi_table_pmt_stream *s)
अणु
	करो अणु
		/* This function transfers ownership of s to the table */
		अगर (s == pmt->stream)
			वापस;

		pmt->stream = s;
		vidtv_psi_pmt_table_update_sec_len(pmt);

		s = शून्य;
	पूर्ण जबतक (vidtv_psi_get_sec_len(&pmt->header) > MAX_SECTION_LEN);

	vidtv_psi_update_version_num(&pmt->header);
पूर्ण

u16 vidtv_psi_pmt_get_pid(काष्ठा vidtv_psi_table_pmt *section,
			  काष्ठा vidtv_psi_table_pat *pat)
अणु
	काष्ठा vidtv_psi_table_pat_program *program = pat->program;

	/*
	 * service_id is the same as program_number in the
	 * corresponding program_map_section
	 * see ETSI EN 300 468 v1.15.1 p. 24
	 */
	जबतक (program) अणु
		अगर (program->service_id == section->header.id)
			वापस vidtv_psi_get_pat_program_pid(program);

		program = program->next;
	पूर्ण

	वापस TS_LAST_VALID_PID + 1; /* not found */
पूर्ण

काष्ठा vidtv_psi_table_pmt *vidtv_psi_pmt_table_init(u16 program_number,
						     u16 pcr_pid)
अणु
	काष्ठा vidtv_psi_table_pmt *pmt;
	स्थिर u16 RESERVED1 = 0x07;
	स्थिर u16 RESERVED2 = 0x0f;
	स्थिर u16 SYNTAX = 0x1;
	स्थिर u16 ONES = 0x03;
	स्थिर u16 ZERO = 0x0;
	u16 desc_loop_len;

	pmt = kzalloc(माप(*pmt), GFP_KERNEL);
	अगर (!pmt)
		वापस शून्य;

	अगर (!pcr_pid)
		pcr_pid = 0x1fff;

	pmt->header.table_id = 0x2;

	pmt->header.bitfield = cpu_to_be16((SYNTAX << 15) | (ZERO << 14) | (ONES << 12));

	pmt->header.id = cpu_to_be16(program_number);
	pmt->header.current_next = 0x1;

	pmt->header.version = 0x1f;

	pmt->header.one2 = ONES;
	pmt->header.section_id   = 0;
	pmt->header.last_section = 0;

	pmt->bitfield = cpu_to_be16((RESERVED1 << 13) | pcr_pid);

	desc_loop_len = vidtv_psi_desc_comp_loop_len(pmt->descriptor);

	pmt->bitfield2 = cpu_to_be16((RESERVED2 << 12) |
				     (ZERO << 10)      |
				     desc_loop_len);

	vidtv_psi_pmt_table_update_sec_len(pmt);

	वापस pmt;
पूर्ण

u32 vidtv_psi_pmt_ग_लिखो_पूर्णांकo(काष्ठा vidtv_psi_pmt_ग_लिखो_args *args)
अणु
	काष्ठा vidtv_psi_desc *table_descriptor   = args->pmt->descriptor;
	काष्ठा vidtv_psi_table_pmt_stream *stream = args->pmt->stream;
	काष्ठा vidtv_psi_desc *stream_descriptor;
	u32 crc = INITIAL_CRC;
	u32 nbytes = 0;
	काष्ठा header_ग_लिखो_args h_args = अणु
		.dest_buf           = args->buf,
		.dest_offset        = args->offset,
		.h                  = &args->pmt->header,
		.pid                = args->pid,
		.continuity_counter = args->continuity_counter,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा psi_ग_लिखो_args psi_args  = अणु
		.dest_buf = args->buf,
		.from     = &args->pmt->bitfield,
		.len      = माप_field(काष्ठा vidtv_psi_table_pmt, bitfield) +
			    माप_field(काष्ठा vidtv_psi_table_pmt, bitfield2),
		.pid                = args->pid,
		.new_psi_section    = false,
		.is_crc             = false,
		.dest_buf_sz        = args->buf_sz,
		.crc                = &crc,
	पूर्ण;
	काष्ठा desc_ग_लिखो_args d_args   = अणु
		.dest_buf           = args->buf,
		.desc               = table_descriptor,
		.pid                = args->pid,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा crc32_ग_लिखो_args c_args  = अणु
		.dest_buf           = args->buf,
		.pid                = args->pid,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;

	vidtv_psi_pmt_table_update_sec_len(args->pmt);

	h_args.crc                = &crc;

	nbytes += vidtv_psi_table_header_ग_लिखो_पूर्णांकo(&h_args);

	/* ग_लिखो the two bitfields */
	psi_args.dest_offset        = args->offset + nbytes;
	psi_args.continuity_counter = args->continuity_counter;
	nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

	जबतक (table_descriptor) अणु
		/* ग_लिखो the descriptors, अगर any */
		d_args.dest_offset        = args->offset + nbytes;
		d_args.continuity_counter = args->continuity_counter;
		d_args.crc                = &crc;

		nbytes += vidtv_psi_desc_ग_लिखो_पूर्णांकo(&d_args);

		table_descriptor = table_descriptor->next;
	पूर्ण

	psi_args.len += माप_field(काष्ठा vidtv_psi_table_pmt_stream, type);
	जबतक (stream) अणु
		/* ग_लिखो the streams, अगर any */
		psi_args.from = stream;
		psi_args.dest_offset = args->offset + nbytes;
		psi_args.continuity_counter = args->continuity_counter;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

		stream_descriptor = stream->descriptor;

		जबतक (stream_descriptor) अणु
			/* ग_लिखो the stream descriptors, अगर any */
			d_args.dest_offset        = args->offset + nbytes;
			d_args.desc               = stream_descriptor;
			d_args.continuity_counter = args->continuity_counter;
			d_args.crc                = &crc;

			nbytes += vidtv_psi_desc_ग_लिखो_पूर्णांकo(&d_args);

			stream_descriptor = stream_descriptor->next;
		पूर्ण

		stream = stream->next;
	पूर्ण

	c_args.dest_offset        = args->offset + nbytes;
	c_args.crc                = cpu_to_be32(crc);
	c_args.continuity_counter = args->continuity_counter;

	/* Write the CRC32 at the end */
	nbytes += table_section_crc32_ग_लिखो_पूर्णांकo(&c_args);

	वापस nbytes;
पूर्ण

व्योम vidtv_psi_pmt_table_destroy(काष्ठा vidtv_psi_table_pmt *pmt)
अणु
	vidtv_psi_desc_destroy(pmt->descriptor);
	vidtv_psi_pmt_stream_destroy(pmt->stream);
	kमुक्त(pmt);
पूर्ण

काष्ठा vidtv_psi_table_sdt *vidtv_psi_sdt_table_init(u16 network_id,
						     u16 transport_stream_id)
अणु
	काष्ठा vidtv_psi_table_sdt *sdt;
	स्थिर u16 RESERVED = 0xff;
	स्थिर u16 SYNTAX = 0x1;
	स्थिर u16 ONES = 0x03;
	स्थिर u16 ONE = 0x1;

	sdt  = kzalloc(माप(*sdt), GFP_KERNEL);
	अगर (!sdt)
		वापस शून्य;

	sdt->header.table_id = 0x42;
	sdt->header.bitfield = cpu_to_be16((SYNTAX << 15) | (ONE << 14) | (ONES << 12));

	/*
	 * This is a 16-bit field which serves as a label क्रम identअगरication
	 * of the TS, about which the SDT inक्रमms, from any other multiplex
	 * within the delivery प्रणाली.
	 */
	sdt->header.id = cpu_to_be16(transport_stream_id);
	sdt->header.current_next = ONE;

	sdt->header.version = 0x1f;

	sdt->header.one2  = ONES;
	sdt->header.section_id   = 0;
	sdt->header.last_section = 0;

	/*
	 * FIXME: The network_id range from 0xFF01 to 0xFFFF is used to
	 * indicate temporary निजी use. For now, let's use the first
	 * value.
	 * This can be changed to something more useful, when support क्रम
	 * NIT माला_लो added
	 */
	sdt->network_id = cpu_to_be16(network_id);
	sdt->reserved = RESERVED;

	vidtv_psi_sdt_table_update_sec_len(sdt);

	वापस sdt;
पूर्ण

u32 vidtv_psi_sdt_ग_लिखो_पूर्णांकo(काष्ठा vidtv_psi_sdt_ग_लिखो_args *args)
अणु
	काष्ठा header_ग_लिखो_args h_args = अणु
		.dest_buf           = args->buf,
		.dest_offset        = args->offset,
		.h                  = &args->sdt->header,
		.pid                = VIDTV_SDT_PID,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा psi_ग_लिखो_args psi_args  = अणु
		.dest_buf = args->buf,
		.len = माप_field(काष्ठा vidtv_psi_table_sdt, network_id) +
		       माप_field(काष्ठा vidtv_psi_table_sdt, reserved),
		.pid                = VIDTV_SDT_PID,
		.new_psi_section    = false,
		.is_crc             = false,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा desc_ग_लिखो_args d_args   = अणु
		.dest_buf           = args->buf,
		.pid                = VIDTV_SDT_PID,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा crc32_ग_लिखो_args c_args  = अणु
		.dest_buf           = args->buf,
		.pid                = VIDTV_SDT_PID,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा vidtv_psi_table_sdt_service *service = args->sdt->service;
	काष्ठा vidtv_psi_desc *service_desc;
	u32 nbytes  = 0;
	u32 crc = INITIAL_CRC;

	/* see ETSI EN 300 468 v1.15.1 p. 11 */

	vidtv_psi_sdt_table_update_sec_len(args->sdt);

	h_args.continuity_counter = args->continuity_counter;
	h_args.crc                = &crc;

	nbytes += vidtv_psi_table_header_ग_लिखो_पूर्णांकo(&h_args);

	psi_args.from               = &args->sdt->network_id;
	psi_args.dest_offset        = args->offset + nbytes;
	psi_args.continuity_counter = args->continuity_counter;
	psi_args.crc                = &crc;

	/* copy u16 network_id + u8 reserved)*/
	nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

	/* skip both poपूर्णांकers at the end */
	psi_args.len = माप(काष्ठा vidtv_psi_table_sdt_service) -
		       माप(काष्ठा vidtv_psi_desc *) -
		       माप(काष्ठा vidtv_psi_table_sdt_service *);

	जबतक (service) अणु
		/* copy the services, अगर any */
		psi_args.from = service;
		psi_args.dest_offset = args->offset + nbytes;
		psi_args.continuity_counter = args->continuity_counter;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

		service_desc = service->descriptor;

		जबतक (service_desc) अणु
			/* copy the service descriptors, अगर any */
			d_args.dest_offset        = args->offset + nbytes;
			d_args.desc               = service_desc;
			d_args.continuity_counter = args->continuity_counter;
			d_args.crc                = &crc;

			nbytes += vidtv_psi_desc_ग_लिखो_पूर्णांकo(&d_args);

			service_desc = service_desc->next;
		पूर्ण

		service = service->next;
	पूर्ण

	c_args.dest_offset        = args->offset + nbytes;
	c_args.crc                = cpu_to_be32(crc);
	c_args.continuity_counter = args->continuity_counter;

	/* Write the CRC at the end */
	nbytes += table_section_crc32_ग_लिखो_पूर्णांकo(&c_args);

	वापस nbytes;
पूर्ण

व्योम vidtv_psi_sdt_table_destroy(काष्ठा vidtv_psi_table_sdt *sdt)
अणु
	vidtv_psi_sdt_service_destroy(sdt->service);
	kमुक्त(sdt);
पूर्ण

काष्ठा vidtv_psi_table_sdt_service
*vidtv_psi_sdt_service_init(काष्ठा vidtv_psi_table_sdt_service *head,
			    u16 service_id,
			    bool eit_schedule,
			    bool eit_present_following)
अणु
	काष्ठा vidtv_psi_table_sdt_service *service;

	service = kzalloc(माप(*service), GFP_KERNEL);
	अगर (!service)
		वापस शून्य;

	/*
	 * ETSI 300 468: this is a 16bit field which serves as a label to
	 * identअगरy this service from any other service within the TS.
	 * The service id is the same as the program number in the
	 * corresponding program_map_section
	 */
	service->service_id            = cpu_to_be16(service_id);
	service->EIT_schedule          = eit_schedule;
	service->EIT_present_following = eit_present_following;
	service->reserved              = 0x3f;

	service->bitfield = cpu_to_be16(RUNNING << 13);

	अगर (head) अणु
		जबतक (head->next)
			head = head->next;

		head->next = service;
	पूर्ण

	वापस service;
पूर्ण

व्योम
vidtv_psi_sdt_service_destroy(काष्ठा vidtv_psi_table_sdt_service *service)
अणु
	काष्ठा vidtv_psi_table_sdt_service *curr = service;
	काष्ठा vidtv_psi_table_sdt_service *पंचांगp  = शून्य;

	जबतक (curr) अणु
		पंचांगp  = curr;
		curr = curr->next;
		vidtv_psi_desc_destroy(पंचांगp->descriptor);
		kमुक्त(पंचांगp);
	पूर्ण
पूर्ण

व्योम
vidtv_psi_sdt_service_assign(काष्ठा vidtv_psi_table_sdt *sdt,
			     काष्ठा vidtv_psi_table_sdt_service *service)
अणु
	करो अणु
		अगर (service == sdt->service)
			वापस;

		sdt->service = service;

		/* recompute section length */
		vidtv_psi_sdt_table_update_sec_len(sdt);

		service = शून्य;
	पूर्ण जबतक (vidtv_psi_get_sec_len(&sdt->header) > MAX_SECTION_LEN);

	vidtv_psi_update_version_num(&sdt->header);
पूर्ण

/*
 * PMTs contain inक्रमmation about programs. For each program,
 * there is one PMT section. This function will create a section
 * क्रम each program found in the PAT
 */
काष्ठा vidtv_psi_table_pmt**
vidtv_psi_pmt_create_sec_क्रम_each_pat_entry(काष्ठा vidtv_psi_table_pat *pat,
					    u16 pcr_pid)

अणु
	काष्ठा vidtv_psi_table_pat_program *program;
	काष्ठा vidtv_psi_table_pmt **pmt_secs;
	u32 i = 0, num_pmt = 0;

	/*
	 * The number of PMT entries is the number of PAT entries
	 * that contain service_id. That exclude special tables, like NIT
	 */
	program = pat->program;
	जबतक (program) अणु
		अगर (program->service_id)
			num_pmt++;
		program = program->next;
	पूर्ण

	pmt_secs = kसुस्मृति(num_pmt,
			   माप(काष्ठा vidtv_psi_table_pmt *),
			   GFP_KERNEL);
	अगर (!pmt_secs)
		वापस शून्य;

	क्रम (program = pat->program; program; program = program->next) अणु
		अगर (!program->service_id)
			जारी;
		pmt_secs[i] = vidtv_psi_pmt_table_init(be16_to_cpu(program->service_id),
						       pcr_pid);

		अगर (!pmt_secs[i]) अणु
			जबतक (i > 0) अणु
				i--;
				vidtv_psi_pmt_table_destroy(pmt_secs[i]);
			पूर्ण
			वापस शून्य;
		पूर्ण
		i++;
	पूर्ण
	pat->num_pmt = num_pmt;

	वापस pmt_secs;
पूर्ण

/* find the PMT section associated with 'program_num' */
काष्ठा vidtv_psi_table_pmt
*vidtv_psi_find_pmt_sec(काष्ठा vidtv_psi_table_pmt **pmt_sections,
			u16 nsections,
			u16 program_num)
अणु
	काष्ठा vidtv_psi_table_pmt *sec = शून्य;
	u32 i;

	क्रम (i = 0; i < nsections; ++i) अणु
		sec = pmt_sections[i];
		अगर (be16_to_cpu(sec->header.id) == program_num)
			वापस sec;
	पूर्ण

	वापस शून्य; /* not found */
पूर्ण

अटल व्योम vidtv_psi_nit_table_update_sec_len(काष्ठा vidtv_psi_table_nit *nit)
अणु
	u16 length = 0;
	काष्ठा vidtv_psi_table_transport *t = nit->transport;
	u16 desc_loop_len;
	u16 transport_loop_len = 0;

	/*
	 * from immediately after 'section_length' until
	 * 'network_descriptor_length'
	 */
	length += NIT_LEN_UNTIL_NETWORK_DESCRIPTOR_LEN;

	desc_loop_len = vidtv_psi_desc_comp_loop_len(nit->descriptor);
	vidtv_psi_set_desc_loop_len(&nit->bitfield, desc_loop_len, 12);

	length += desc_loop_len;

	length += माप_field(काष्ठा vidtv_psi_table_nit, bitfield2);

	जबतक (t) अणु
		/* skip both poपूर्णांकers at the end */
		transport_loop_len += माप(काष्ठा vidtv_psi_table_transport) -
				      माप(काष्ठा vidtv_psi_desc *) -
				      माप(काष्ठा vidtv_psi_table_transport *);

		length += transport_loop_len;

		desc_loop_len = vidtv_psi_desc_comp_loop_len(t->descriptor);
		vidtv_psi_set_desc_loop_len(&t->bitfield, desc_loop_len, 12);

		length += desc_loop_len;

		t = t->next;
	पूर्ण

	// Actually sets the transport stream loop len, maybe नाम this function later
	vidtv_psi_set_desc_loop_len(&nit->bitfield2, transport_loop_len, 12);
	length += CRC_SIZE_IN_BYTES;

	vidtv_psi_set_sec_len(&nit->header, length);
पूर्ण

काष्ठा vidtv_psi_table_nit
*vidtv_psi_nit_table_init(u16 network_id,
			  u16 transport_stream_id,
			  अक्षर *network_name,
			  काष्ठा vidtv_psi_desc_service_list_entry *service_list)
अणु
	काष्ठा vidtv_psi_table_transport *transport;
	काष्ठा vidtv_psi_table_nit *nit;
	स्थिर u16 SYNTAX = 0x1;
	स्थिर u16 ONES = 0x03;
	स्थिर u16 ONE = 0x1;

	nit = kzalloc(माप(*nit), GFP_KERNEL);
	अगर (!nit)
		वापस शून्य;

	transport = kzalloc(माप(*transport), GFP_KERNEL);
	अगर (!transport)
		जाओ मुक्त_nit;

	nit->header.table_id = 0x40; // ACTUAL_NETWORK

	nit->header.bitfield = cpu_to_be16((SYNTAX << 15) | (ONE << 14) | (ONES << 12));

	nit->header.id = cpu_to_be16(network_id);
	nit->header.current_next = ONE;

	nit->header.version = 0x1f;

	nit->header.one2  = ONES;
	nit->header.section_id   = 0;
	nit->header.last_section = 0;

	nit->bitfield = cpu_to_be16(0xf);
	nit->bitfield2 = cpu_to_be16(0xf);

	nit->descriptor = (काष्ठा vidtv_psi_desc *)
			  vidtv_psi_network_name_desc_init(शून्य, network_name);
	अगर (!nit->descriptor)
		जाओ मुक्त_transport;

	transport->transport_id = cpu_to_be16(transport_stream_id);
	transport->network_id = cpu_to_be16(network_id);
	transport->bitfield = cpu_to_be16(0xf);
	transport->descriptor = (काष्ठा vidtv_psi_desc *)
				vidtv_psi_service_list_desc_init(शून्य, service_list);
	अगर (!transport->descriptor)
		जाओ मुक्त_nit_desc;

	nit->transport = transport;

	vidtv_psi_nit_table_update_sec_len(nit);

	वापस nit;

मुक्त_nit_desc:
	vidtv_psi_desc_destroy((काष्ठा vidtv_psi_desc *)nit->descriptor);

मुक्त_transport:
	kमुक्त(transport);
मुक्त_nit:
	kमुक्त(nit);
	वापस शून्य;
पूर्ण

u32 vidtv_psi_nit_ग_लिखो_पूर्णांकo(काष्ठा vidtv_psi_nit_ग_लिखो_args *args)
अणु
	काष्ठा header_ग_लिखो_args h_args = अणु
		.dest_buf           = args->buf,
		.dest_offset        = args->offset,
		.h                  = &args->nit->header,
		.pid                = VIDTV_NIT_PID,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा psi_ग_लिखो_args psi_args  = अणु
		.dest_buf           = args->buf,
		.from               = &args->nit->bitfield,
		.len                = माप_field(काष्ठा vidtv_psi_table_nit, bitfield),
		.pid                = VIDTV_NIT_PID,
		.new_psi_section    = false,
		.is_crc             = false,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा desc_ग_लिखो_args d_args   = अणु
		.dest_buf           = args->buf,
		.pid                = VIDTV_NIT_PID,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा crc32_ग_लिखो_args c_args  = अणु
		.dest_buf           = args->buf,
		.pid                = VIDTV_NIT_PID,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा vidtv_psi_desc *table_descriptor     = args->nit->descriptor;
	काष्ठा vidtv_psi_table_transport *transport = args->nit->transport;
	काष्ठा vidtv_psi_desc *transport_descriptor;
	u32 crc = INITIAL_CRC;
	u32 nbytes = 0;

	vidtv_psi_nit_table_update_sec_len(args->nit);

	h_args.continuity_counter = args->continuity_counter;
	h_args.crc                = &crc;

	nbytes += vidtv_psi_table_header_ग_लिखो_पूर्णांकo(&h_args);

	/* ग_लिखो the bitfield */

	psi_args.dest_offset        = args->offset + nbytes;
	psi_args.continuity_counter = args->continuity_counter;
	psi_args.crc                = &crc;

	nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

	जबतक (table_descriptor) अणु
		/* ग_लिखो the descriptors, अगर any */
		d_args.dest_offset        = args->offset + nbytes;
		d_args.desc               = table_descriptor;
		d_args.continuity_counter = args->continuity_counter;
		d_args.crc                = &crc;

		nbytes += vidtv_psi_desc_ग_लिखो_पूर्णांकo(&d_args);

		table_descriptor = table_descriptor->next;
	पूर्ण

	/* ग_लिखो the second bitfield */
	psi_args.from = &args->nit->bitfield2;
	psi_args.len = माप_field(काष्ठा vidtv_psi_table_nit, bitfield2);
	psi_args.dest_offset = args->offset + nbytes;

	nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

	psi_args.len  = माप_field(काष्ठा vidtv_psi_table_transport, transport_id) +
			माप_field(काष्ठा vidtv_psi_table_transport, network_id)   +
			माप_field(काष्ठा vidtv_psi_table_transport, bitfield);
	जबतक (transport) अणु
		/* ग_लिखो the transport sections, अगर any */
		psi_args.from = transport;
		psi_args.dest_offset = args->offset + nbytes;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

		transport_descriptor = transport->descriptor;

		जबतक (transport_descriptor) अणु
			/* ग_लिखो the transport descriptors, अगर any */
			d_args.dest_offset        = args->offset + nbytes;
			d_args.desc               = transport_descriptor;
			d_args.continuity_counter = args->continuity_counter;
			d_args.crc                = &crc;

			nbytes += vidtv_psi_desc_ग_लिखो_पूर्णांकo(&d_args);

			transport_descriptor = transport_descriptor->next;
		पूर्ण

		transport = transport->next;
	पूर्ण

	c_args.dest_offset        = args->offset + nbytes;
	c_args.crc                = cpu_to_be32(crc);
	c_args.continuity_counter = args->continuity_counter;

	/* Write the CRC32 at the end */
	nbytes += table_section_crc32_ग_लिखो_पूर्णांकo(&c_args);

	वापस nbytes;
पूर्ण

अटल व्योम vidtv_psi_transport_destroy(काष्ठा vidtv_psi_table_transport *t)
अणु
	काष्ठा vidtv_psi_table_transport *पंचांगp_t  = शून्य;
	काष्ठा vidtv_psi_table_transport *curr_t = t;

	जबतक (curr_t) अणु
		पंचांगp_t  = curr_t;
		curr_t = curr_t->next;
		vidtv_psi_desc_destroy(पंचांगp_t->descriptor);
		kमुक्त(पंचांगp_t);
	पूर्ण
पूर्ण

व्योम vidtv_psi_nit_table_destroy(काष्ठा vidtv_psi_table_nit *nit)
अणु
	vidtv_psi_desc_destroy(nit->descriptor);
	vidtv_psi_transport_destroy(nit->transport);
	kमुक्त(nit);
पूर्ण

व्योम vidtv_psi_eit_table_update_sec_len(काष्ठा vidtv_psi_table_eit *eit)
अणु
	काष्ठा vidtv_psi_table_eit_event *e = eit->event;
	u16 desc_loop_len;
	u16 length = 0;

	/*
	 * from immediately after 'section_length' until
	 * 'last_table_id'
	 */
	length += EIT_LEN_UNTIL_LAST_TABLE_ID;

	जबतक (e) अणु
		/* skip both poपूर्णांकers at the end */
		length += माप(काष्ठा vidtv_psi_table_eit_event) -
			  माप(काष्ठा vidtv_psi_desc *) -
			  माप(काष्ठा vidtv_psi_table_eit_event *);

		desc_loop_len = vidtv_psi_desc_comp_loop_len(e->descriptor);
		vidtv_psi_set_desc_loop_len(&e->bitfield, desc_loop_len, 12);

		length += desc_loop_len;

		e = e->next;
	पूर्ण

	length += CRC_SIZE_IN_BYTES;

	vidtv_psi_set_sec_len(&eit->header, length);
पूर्ण

व्योम vidtv_psi_eit_event_assign(काष्ठा vidtv_psi_table_eit *eit,
				काष्ठा vidtv_psi_table_eit_event *e)
अणु
	करो अणु
		अगर (e == eit->event)
			वापस;

		eit->event = e;
		vidtv_psi_eit_table_update_sec_len(eit);

		e = शून्य;
	पूर्ण जबतक (vidtv_psi_get_sec_len(&eit->header) > EIT_MAX_SECTION_LEN);

	vidtv_psi_update_version_num(&eit->header);
पूर्ण

काष्ठा vidtv_psi_table_eit
*vidtv_psi_eit_table_init(u16 network_id,
			  u16 transport_stream_id,
			  __be16 service_id)
अणु
	काष्ठा vidtv_psi_table_eit *eit;
	स्थिर u16 SYNTAX = 0x1;
	स्थिर u16 ONE = 0x1;
	स्थिर u16 ONES = 0x03;

	eit = kzalloc(माप(*eit), GFP_KERNEL);
	अगर (!eit)
		वापस शून्य;

	eit->header.table_id = 0x4e; //actual_transport_stream: present/following

	eit->header.bitfield = cpu_to_be16((SYNTAX << 15) | (ONE << 14) | (ONES << 12));

	eit->header.id = service_id;
	eit->header.current_next = ONE;

	eit->header.version = 0x1f;

	eit->header.one2  = ONES;
	eit->header.section_id   = 0;
	eit->header.last_section = 0;

	eit->transport_id = cpu_to_be16(transport_stream_id);
	eit->network_id = cpu_to_be16(network_id);

	eit->last_segment = eit->header.last_section; /* not implemented */
	eit->last_table_id = eit->header.table_id; /* not implemented */

	vidtv_psi_eit_table_update_sec_len(eit);

	वापस eit;
पूर्ण

u32 vidtv_psi_eit_ग_लिखो_पूर्णांकo(काष्ठा vidtv_psi_eit_ग_लिखो_args *args)
अणु
	काष्ठा header_ग_लिखो_args h_args = अणु
		.dest_buf        = args->buf,
		.dest_offset     = args->offset,
		.h               = &args->eit->header,
		.pid             = VIDTV_EIT_PID,
		.dest_buf_sz     = args->buf_sz,
	पूर्ण;
	काष्ठा psi_ग_लिखो_args psi_args  = अणु
		.dest_buf        = args->buf,
		.len             = माप_field(काष्ठा vidtv_psi_table_eit, transport_id) +
				   माप_field(काष्ठा vidtv_psi_table_eit, network_id)   +
				   माप_field(काष्ठा vidtv_psi_table_eit, last_segment) +
				   माप_field(काष्ठा vidtv_psi_table_eit, last_table_id),
		.pid             = VIDTV_EIT_PID,
		.new_psi_section = false,
		.is_crc          = false,
		.dest_buf_sz     = args->buf_sz,
	पूर्ण;
	काष्ठा desc_ग_लिखो_args d_args   = अणु
		.dest_buf           = args->buf,
		.pid                = VIDTV_EIT_PID,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा crc32_ग_लिखो_args c_args  = अणु
		.dest_buf           = args->buf,
		.pid                = VIDTV_EIT_PID,
		.dest_buf_sz        = args->buf_sz,
	पूर्ण;
	काष्ठा vidtv_psi_table_eit_event *event = args->eit->event;
	काष्ठा vidtv_psi_desc *event_descriptor;
	u32 crc = INITIAL_CRC;
	u32 nbytes  = 0;

	vidtv_psi_eit_table_update_sec_len(args->eit);

	h_args.continuity_counter = args->continuity_counter;
	h_args.crc                = &crc;

	nbytes += vidtv_psi_table_header_ग_लिखो_पूर्णांकo(&h_args);

	psi_args.from               = &args->eit->transport_id;
	psi_args.dest_offset        = args->offset + nbytes;
	psi_args.continuity_counter = args->continuity_counter;
	psi_args.crc                = &crc;

	nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

	/* skip both poपूर्णांकers at the end */
	psi_args.len = माप(काष्ठा vidtv_psi_table_eit_event) -
		       माप(काष्ठा vidtv_psi_desc *) -
		       माप(काष्ठा vidtv_psi_table_eit_event *);
	जबतक (event) अणु
		/* copy the events, अगर any */
		psi_args.from = event;
		psi_args.dest_offset = args->offset + nbytes;

		nbytes += vidtv_psi_ts_psi_ग_लिखो_पूर्णांकo(&psi_args);

		event_descriptor = event->descriptor;

		जबतक (event_descriptor) अणु
			/* copy the event descriptors, अगर any */
			d_args.dest_offset        = args->offset + nbytes;
			d_args.desc               = event_descriptor;
			d_args.continuity_counter = args->continuity_counter;
			d_args.crc                = &crc;

			nbytes += vidtv_psi_desc_ग_लिखो_पूर्णांकo(&d_args);

			event_descriptor = event_descriptor->next;
		पूर्ण

		event = event->next;
	पूर्ण

	c_args.dest_offset        = args->offset + nbytes;
	c_args.crc                = cpu_to_be32(crc);
	c_args.continuity_counter = args->continuity_counter;

	/* Write the CRC at the end */
	nbytes += table_section_crc32_ग_लिखो_पूर्णांकo(&c_args);

	वापस nbytes;
पूर्ण

काष्ठा vidtv_psi_table_eit_event
*vidtv_psi_eit_event_init(काष्ठा vidtv_psi_table_eit_event *head, u16 event_id)
अणु
	स्थिर u8 DURATION[] = अणु0x23, 0x59, 0x59पूर्ण; /* BCD encoded */
	काष्ठा vidtv_psi_table_eit_event *e;
	काष्ठा बारpec64 ts;
	काष्ठा पंचांग समय;
	पूर्णांक mjd, l;
	__be16 mjd_be;

	e = kzalloc(माप(*e), GFP_KERNEL);
	अगर (!e)
		वापस शून्य;

	e->event_id = cpu_to_be16(event_id);

	ts = kसमय_प्रकारo_बारpec64(kसमय_get_real());
	समय64_to_पंचांग(ts.tv_sec, 0, &समय);

	/* Convert date to Modअगरied Julian Date - per EN 300 468 Annex C */
	अगर (समय.पंचांग_mon < 2)
		l = 1;
	अन्यथा
		l = 0;

	mjd = 14956 + समय.पंचांग_mday;
	mjd += (समय.पंचांग_year - l) * 36525 / 100;
	mjd += (समय.पंचांग_mon + 2 + l * 12) * 306001 / 10000;
	mjd_be = cpu_to_be16(mjd);

	/*
	 * Store MJD and hour/min/sec to the event.
	 *
	 * Let's make the event to start on a full hour
	 */
	स_नकल(e->start_समय, &mjd_be, माप(mjd_be));
	e->start_समय[2] = bin2bcd(समय.पंचांग_hour);
	e->start_समय[3] = 0;
	e->start_समय[4] = 0;

	/*
	 * TODO: क्रम now, the event will last क्रम a day. Should be
	 * enough क्रम testing purposes, but अगर one runs the driver
	 * क्रम more than that, the current event will become invalid.
	 * So, we need a better code here in order to change the start
	 * समय once the event expires.
	 */
	स_नकल(e->duration, DURATION, माप(e->duration));

	e->bitfield = cpu_to_be16(RUNNING << 13);

	अगर (head) अणु
		जबतक (head->next)
			head = head->next;

		head->next = e;
	पूर्ण

	वापस e;
पूर्ण

व्योम vidtv_psi_eit_event_destroy(काष्ठा vidtv_psi_table_eit_event *e)
अणु
	काष्ठा vidtv_psi_table_eit_event *पंचांगp_e  = शून्य;
	काष्ठा vidtv_psi_table_eit_event *curr_e = e;

	जबतक (curr_e) अणु
		पंचांगp_e  = curr_e;
		curr_e = curr_e->next;
		vidtv_psi_desc_destroy(पंचांगp_e->descriptor);
		kमुक्त(पंचांगp_e);
	पूर्ण
पूर्ण

व्योम vidtv_psi_eit_table_destroy(काष्ठा vidtv_psi_table_eit *eit)
अणु
	vidtv_psi_eit_event_destroy(eit->event);
	kमुक्त(eit);
पूर्ण
