<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2021 Linaro Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/dma-direction.h>

#समावेश "gsi.h"
#समावेश "gsi_trans.h"
#समावेश "ipa.h"
#समावेश "ipa_endpoint.h"
#समावेश "ipa_table.h"
#समावेश "ipa_cmd.h"
#समावेश "ipa_mem.h"

/**
 * DOC:  IPA Immediate Commands
 *
 * The AP command TX endpoपूर्णांक is used to issue immediate commands to the IPA.
 * An immediate command is generally used to request the IPA करो something
 * other than data transfer to another endpoपूर्णांक.
 *
 * Immediate commands are represented by GSI transactions just like other
 * transfer requests, represented by a single GSI TRE.  Each immediate
 * command has a well-defined क्रमmat, having a payload of a known length.
 * This allows the transfer element's length field to be used to hold an
 * immediate command's opcode.  The payload क्रम a command resides in DRAM
 * and is described by a single scatterlist entry in its transaction.
 * Commands करो not require a transaction completion callback.  To commit
 * an immediate command transaction, either gsi_trans_commit_रुको() or
 * gsi_trans_commit_रुको_समयout() is used.
 */

/* Some commands can रुको until indicated pipeline stages are clear */
क्रमागत pipeline_clear_options अणु
	pipeline_clear_hps		= 0x0,
	pipeline_clear_src_grp		= 0x1,
	pipeline_clear_full		= 0x2,
पूर्ण;

/* IPA_CMD_IP_Vअणु4,6पूर्ण_अणुFILTER,ROUTINGपूर्ण_INIT */

काष्ठा ipa_cmd_hw_ip_fltrt_init अणु
	__le64 hash_rules_addr;
	__le64 flags;
	__le64 nhash_rules_addr;
पूर्ण;

/* Field masks क्रम ipa_cmd_hw_ip_fltrt_init काष्ठाure fields */
#घोषणा IP_FLTRT_FLAGS_HASH_SIZE_FMASK			GENMASK_ULL(11, 0)
#घोषणा IP_FLTRT_FLAGS_HASH_ADDR_FMASK			GENMASK_ULL(27, 12)
#घोषणा IP_FLTRT_FLAGS_NHASH_SIZE_FMASK			GENMASK_ULL(39, 28)
#घोषणा IP_FLTRT_FLAGS_NHASH_ADDR_FMASK			GENMASK_ULL(55, 40)

/* IPA_CMD_HDR_INIT_LOCAL */

काष्ठा ipa_cmd_hw_hdr_init_local अणु
	__le64 hdr_table_addr;
	__le32 flags;
	__le32 reserved;
पूर्ण;

/* Field masks क्रम ipa_cmd_hw_hdr_init_local काष्ठाure fields */
#घोषणा HDR_INIT_LOCAL_FLAGS_TABLE_SIZE_FMASK		GENMASK(11, 0)
#घोषणा HDR_INIT_LOCAL_FLAGS_HDR_ADDR_FMASK		GENMASK(27, 12)

/* IPA_CMD_REGISTER_WRITE */

/* For IPA v4.0+, the pipeline clear options are encoded in the opcode */
#घोषणा REGISTER_WRITE_OPCODE_SKIP_CLEAR_FMASK		GENMASK(8, 8)
#घोषणा REGISTER_WRITE_OPCODE_CLEAR_OPTION_FMASK	GENMASK(10, 9)

काष्ठा ipa_cmd_रेजिस्टर_ग_लिखो अणु
	__le16 flags;		/* Unused/reserved prior to IPA v4.0 */
	__le16 offset;
	__le32 value;
	__le32 value_mask;
	__le32 clear_options;	/* Unused/reserved क्रम IPA v4.0+ */
पूर्ण;

/* Field masks क्रम ipa_cmd_रेजिस्टर_ग_लिखो काष्ठाure fields */
/* The next field is present क्रम IPA v4.0+ */
#घोषणा REGISTER_WRITE_FLAGS_OFFSET_HIGH_FMASK		GENMASK(14, 11)
/* The next field is not present क्रम IPA v4.0+ */
#घोषणा REGISTER_WRITE_FLAGS_SKIP_CLEAR_FMASK		GENMASK(15, 15)

/* The next field and its values are not present क्रम IPA v4.0+ */
#घोषणा REGISTER_WRITE_CLEAR_OPTIONS_FMASK		GENMASK(1, 0)

/* IPA_CMD_IP_PACKET_INIT */

काष्ठा ipa_cmd_ip_packet_init अणु
	u8 dest_endpoपूर्णांक;
	u8 reserved[7];
पूर्ण;

/* Field masks क्रम ipa_cmd_ip_packet_init dest_endpoपूर्णांक field */
#घोषणा IPA_PACKET_INIT_DEST_ENDPOINT_FMASK		GENMASK(4, 0)

/* IPA_CMD_DMA_SHARED_MEM */

/* For IPA v4.0+, this opcode माला_लो modअगरied with pipeline clear options */

#घोषणा DMA_SHARED_MEM_OPCODE_SKIP_CLEAR_FMASK		GENMASK(8, 8)
#घोषणा DMA_SHARED_MEM_OPCODE_CLEAR_OPTION_FMASK	GENMASK(10, 9)

काष्ठा ipa_cmd_hw_dma_mem_mem अणु
	__le16 clear_after_पढ़ो; /* 0 or DMA_SHARED_MEM_CLEAR_AFTER_READ */
	__le16 size;
	__le16 local_addr;
	__le16 flags;
	__le64 प्रणाली_addr;
पूर्ण;

/* Flag allowing atomic clear of target region after पढ़ोing data (v4.0+)*/
#घोषणा DMA_SHARED_MEM_CLEAR_AFTER_READ			GENMASK(15, 15)

/* Field masks क्रम ipa_cmd_hw_dma_mem_mem काष्ठाure fields */
#घोषणा DMA_SHARED_MEM_FLAGS_सूचीECTION_FMASK		GENMASK(0, 0)
/* The next two fields are not present क्रम IPA v4.0+ */
#घोषणा DMA_SHARED_MEM_FLAGS_SKIP_CLEAR_FMASK		GENMASK(1, 1)
#घोषणा DMA_SHARED_MEM_FLAGS_CLEAR_OPTIONS_FMASK	GENMASK(3, 2)

/* IPA_CMD_IP_PACKET_TAG_STATUS */

काष्ठा ipa_cmd_ip_packet_tag_status अणु
	__le64 tag;
पूर्ण;

#घोषणा IP_PACKET_TAG_STATUS_TAG_FMASK			GENMASK_ULL(63, 16)

/* Immediate command payload */
जोड़ ipa_cmd_payload अणु
	काष्ठा ipa_cmd_hw_ip_fltrt_init table_init;
	काष्ठा ipa_cmd_hw_hdr_init_local hdr_init_local;
	काष्ठा ipa_cmd_रेजिस्टर_ग_लिखो रेजिस्टर_ग_लिखो;
	काष्ठा ipa_cmd_ip_packet_init ip_packet_init;
	काष्ठा ipa_cmd_hw_dma_mem_mem dma_shared_mem;
	काष्ठा ipa_cmd_ip_packet_tag_status ip_packet_tag_status;
पूर्ण;

अटल व्योम ipa_cmd_validate_build(व्योम)
अणु
	/* The sizes of a filter and route tables need to fit पूर्णांकo fields
	 * in the ipa_cmd_hw_ip_fltrt_init काष्ठाure.  Although hashed tables
	 * might not be used, non-hashed and hashed tables have the same
	 * maximum size.  IPv4 and IPv6 filter tables have the same number
	 * of entries, as and IPv4 and IPv6 route tables have the same number
	 * of entries.
	 */
#घोषणा TABLE_SIZE	(TABLE_COUNT_MAX * माप(__le64))
#घोषणा TABLE_COUNT_MAX	max_t(u32, IPA_ROUTE_COUNT_MAX, IPA_FILTER_COUNT_MAX)
	BUILD_BUG_ON(TABLE_SIZE > field_max(IP_FLTRT_FLAGS_HASH_SIZE_FMASK));
	BUILD_BUG_ON(TABLE_SIZE > field_max(IP_FLTRT_FLAGS_NHASH_SIZE_FMASK));
#अघोषित TABLE_COUNT_MAX
#अघोषित TABLE_SIZE
पूर्ण

#अगर_घोषित IPA_VALIDATE

/* Validate a memory region holding a table */
bool ipa_cmd_table_valid(काष्ठा ipa *ipa, स्थिर काष्ठा ipa_mem *mem,
			 bool route, bool ipv6, bool hashed)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	u32 offset_max;

	offset_max = hashed ? field_max(IP_FLTRT_FLAGS_HASH_ADDR_FMASK)
			    : field_max(IP_FLTRT_FLAGS_NHASH_ADDR_FMASK);
	अगर (mem->offset > offset_max ||
	    ipa->mem_offset > offset_max - mem->offset) अणु
		dev_err(dev, "IPv%c %s%s table region offset too large\n",
			ipv6 ? '6' : '4', hashed ? "hashed " : "",
			route ? "route" : "filter");
		dev_err(dev, "    (0x%04x + 0x%04x > 0x%04x)\n",
			ipa->mem_offset, mem->offset, offset_max);

		वापस false;
	पूर्ण

	अगर (mem->offset > ipa->mem_size ||
	    mem->size > ipa->mem_size - mem->offset) अणु
		dev_err(dev, "IPv%c %s%s table region out of range\n",
			ipv6 ? '6' : '4', hashed ? "hashed " : "",
			route ? "route" : "filter");
		dev_err(dev, "    (0x%04x + 0x%04x > 0x%04x)\n",
			mem->offset, mem->size, ipa->mem_size);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Validate the memory region that holds headers */
अटल bool ipa_cmd_header_valid(काष्ठा ipa *ipa)
अणु
	स्थिर काष्ठा ipa_mem *mem = &ipa->mem[IPA_MEM_MODEM_HEADER];
	काष्ठा device *dev = &ipa->pdev->dev;
	u32 offset_max;
	u32 size_max;
	u32 size;

	/* In ipa_cmd_hdr_init_local_add() we record the offset and size
	 * of the header table memory area.  Make sure the offset and size
	 * fit in the fields that need to hold them, and that the entire
	 * range is within the overall IPA memory range.
	 */
	offset_max = field_max(HDR_INIT_LOCAL_FLAGS_HDR_ADDR_FMASK);
	अगर (mem->offset > offset_max ||
	    ipa->mem_offset > offset_max - mem->offset) अणु
		dev_err(dev, "header table region offset too large\n");
		dev_err(dev, "    (0x%04x + 0x%04x > 0x%04x)\n",
			ipa->mem_offset, mem->offset, offset_max);

		वापस false;
	पूर्ण

	size_max = field_max(HDR_INIT_LOCAL_FLAGS_TABLE_SIZE_FMASK);
	size = ipa->mem[IPA_MEM_MODEM_HEADER].size;
	size += ipa->mem[IPA_MEM_AP_HEADER].size;

	अगर (size > size_max) अणु
		dev_err(dev, "header table region size too large\n");
		dev_err(dev, "    (0x%04x > 0x%08x)\n", size, size_max);

		वापस false;
	पूर्ण
	अगर (size > ipa->mem_size || mem->offset > ipa->mem_size - size) अणु
		dev_err(dev, "header table region out of range\n");
		dev_err(dev, "    (0x%04x + 0x%04x > 0x%04x)\n",
			mem->offset, size, ipa->mem_size);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Indicate whether an offset can be used with a रेजिस्टर_ग_लिखो command */
अटल bool ipa_cmd_रेजिस्टर_ग_लिखो_offset_valid(काष्ठा ipa *ipa,
						स्थिर अक्षर *name, u32 offset)
अणु
	काष्ठा ipa_cmd_रेजिस्टर_ग_लिखो *payload;
	काष्ठा device *dev = &ipa->pdev->dev;
	u32 offset_max;
	u32 bit_count;

	/* The maximum offset in a रेजिस्टर_ग_लिखो immediate command depends
	 * on the version of IPA.  A 16 bit offset is always supported,
	 * but starting with IPA v4.0 some additional high-order bits are
	 * allowed.
	 */
	bit_count = BITS_PER_BYTE * माप(payload->offset);
	अगर (ipa->version >= IPA_VERSION_4_0)
		bit_count += hweight32(REGISTER_WRITE_FLAGS_OFFSET_HIGH_FMASK);
	BUILD_BUG_ON(bit_count > 32);
	offset_max = ~0U >> (32 - bit_count);

	/* Make sure the offset can be represented by the field(s)
	 * that holds it.  Also make sure the offset is not outside
	 * the overall IPA memory range.
	 */
	अगर (offset > offset_max || ipa->mem_offset > offset_max - offset) अणु
		dev_err(dev, "%s offset too large 0x%04x + 0x%04x > 0x%04x)\n",
			name, ipa->mem_offset, offset, offset_max);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Check whether offsets passed to रेजिस्टर_ग_लिखो are valid */
अटल bool ipa_cmd_रेजिस्टर_ग_लिखो_valid(काष्ठा ipa *ipa)
अणु
	स्थिर अक्षर *name;
	u32 offset;

	/* If hashed tables are supported, ensure the hash flush रेजिस्टर
	 * offset will fit in a रेजिस्टर ग_लिखो IPA immediate command.
	 */
	अगर (ipa_table_hash_support(ipa)) अणु
		offset = ipa_reg_filt_rout_hash_flush_offset(ipa->version);
		name = "filter/route hash flush";
		अगर (!ipa_cmd_रेजिस्टर_ग_लिखो_offset_valid(ipa, name, offset))
			वापस false;
	पूर्ण

	/* Each endpoपूर्णांक can have a status endpoपूर्णांक associated with it,
	 * and this is recorded in an endpoपूर्णांक रेजिस्टर.  If the modem
	 * crashes, we reset the status endpoपूर्णांक क्रम all modem endpoपूर्णांकs
	 * using a रेजिस्टर ग_लिखो IPA immediate command.  Make sure the
	 * worst हाल (highest endpoपूर्णांक number) offset of that endpoपूर्णांक
	 * fits in the रेजिस्टर ग_लिखो command field(s) that must hold it.
	 */
	offset = IPA_REG_ENDP_STATUS_N_OFFSET(IPA_ENDPOINT_COUNT - 1);
	name = "maximal endpoint status";
	अगर (!ipa_cmd_रेजिस्टर_ग_लिखो_offset_valid(ipa, name, offset))
		वापस false;

	वापस true;
पूर्ण

bool ipa_cmd_data_valid(काष्ठा ipa *ipa)
अणु
	अगर (!ipa_cmd_header_valid(ipa))
		वापस false;

	अगर (!ipa_cmd_रेजिस्टर_ग_लिखो_valid(ipa))
		वापस false;

	वापस true;
पूर्ण

#पूर्ण_अगर /* IPA_VALIDATE */

पूर्णांक ipa_cmd_pool_init(काष्ठा gsi_channel *channel, u32 tre_max)
अणु
	काष्ठा gsi_trans_info *trans_info = &channel->trans_info;
	काष्ठा device *dev = channel->gsi->dev;
	पूर्णांक ret;

	/* This is as good a place as any to validate build स्थिरants */
	ipa_cmd_validate_build();

	/* Even though command payloads are allocated one at a समय,
	 * a single transaction can require up to tlv_count of them,
	 * so we treat them as अगर that many can be allocated at once.
	 */
	ret = gsi_trans_pool_init_dma(dev, &trans_info->cmd_pool,
				      माप(जोड़ ipa_cmd_payload),
				      tre_max, channel->tlv_count);
	अगर (ret)
		वापस ret;

	/* Each TRE needs a command info काष्ठाure */
	ret = gsi_trans_pool_init(&trans_info->info_pool,
				   माप(काष्ठा ipa_cmd_info),
				   tre_max, channel->tlv_count);
	अगर (ret)
		gsi_trans_pool_निकास_dma(dev, &trans_info->cmd_pool);

	वापस ret;
पूर्ण

व्योम ipa_cmd_pool_निकास(काष्ठा gsi_channel *channel)
अणु
	काष्ठा gsi_trans_info *trans_info = &channel->trans_info;
	काष्ठा device *dev = channel->gsi->dev;

	gsi_trans_pool_निकास(&trans_info->info_pool);
	gsi_trans_pool_निकास_dma(dev, &trans_info->cmd_pool);
पूर्ण

अटल जोड़ ipa_cmd_payload *
ipa_cmd_payload_alloc(काष्ठा ipa *ipa, dma_addr_t *addr)
अणु
	काष्ठा gsi_trans_info *trans_info;
	काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक;

	endpoपूर्णांक = ipa->name_map[IPA_ENDPOINT_AP_COMMAND_TX];
	trans_info = &ipa->gsi.channel[endpoपूर्णांक->channel_id].trans_info;

	वापस gsi_trans_pool_alloc_dma(&trans_info->cmd_pool, addr);
पूर्ण

/* If hash_size is 0, hash_offset and hash_addr ignored. */
व्योम ipa_cmd_table_init_add(काष्ठा gsi_trans *trans,
			    क्रमागत ipa_cmd_opcode opcode, u16 size, u32 offset,
			    dma_addr_t addr, u16 hash_size, u32 hash_offset,
			    dma_addr_t hash_addr)
अणु
	काष्ठा ipa *ipa = container_of(trans->gsi, काष्ठा ipa, gsi);
	क्रमागत dma_data_direction direction = DMA_TO_DEVICE;
	काष्ठा ipa_cmd_hw_ip_fltrt_init *payload;
	जोड़ ipa_cmd_payload *cmd_payload;
	dma_addr_t payload_addr;
	u64 val;

	/* Record the non-hash table offset and size */
	offset += ipa->mem_offset;
	val = u64_encode_bits(offset, IP_FLTRT_FLAGS_NHASH_ADDR_FMASK);
	val |= u64_encode_bits(size, IP_FLTRT_FLAGS_NHASH_SIZE_FMASK);

	/* The hash table offset and address are zero अगर its size is 0 */
	अगर (hash_size) अणु
		/* Record the hash table offset and size */
		hash_offset += ipa->mem_offset;
		val |= u64_encode_bits(hash_offset,
				       IP_FLTRT_FLAGS_HASH_ADDR_FMASK);
		val |= u64_encode_bits(hash_size,
				       IP_FLTRT_FLAGS_HASH_SIZE_FMASK);
	पूर्ण

	cmd_payload = ipa_cmd_payload_alloc(ipa, &payload_addr);
	payload = &cmd_payload->table_init;

	/* Fill in all offsets and sizes and the non-hash table address */
	अगर (hash_size)
		payload->hash_rules_addr = cpu_to_le64(hash_addr);
	payload->flags = cpu_to_le64(val);
	payload->nhash_rules_addr = cpu_to_le64(addr);

	gsi_trans_cmd_add(trans, payload, माप(*payload), payload_addr,
			  direction, opcode);
पूर्ण

/* Initialize header space in IPA-local memory */
व्योम ipa_cmd_hdr_init_local_add(काष्ठा gsi_trans *trans, u32 offset, u16 size,
				dma_addr_t addr)
अणु
	काष्ठा ipa *ipa = container_of(trans->gsi, काष्ठा ipa, gsi);
	क्रमागत ipa_cmd_opcode opcode = IPA_CMD_HDR_INIT_LOCAL;
	क्रमागत dma_data_direction direction = DMA_TO_DEVICE;
	काष्ठा ipa_cmd_hw_hdr_init_local *payload;
	जोड़ ipa_cmd_payload *cmd_payload;
	dma_addr_t payload_addr;
	u32 flags;

	offset += ipa->mem_offset;

	/* With this command we tell the IPA where in its local memory the
	 * header tables reside.  The content of the buffer provided is
	 * also written via DMA पूर्णांकo that space.  The IPA hardware owns
	 * the table, but the AP must initialize it.
	 */
	cmd_payload = ipa_cmd_payload_alloc(ipa, &payload_addr);
	payload = &cmd_payload->hdr_init_local;

	payload->hdr_table_addr = cpu_to_le64(addr);
	flags = u32_encode_bits(size, HDR_INIT_LOCAL_FLAGS_TABLE_SIZE_FMASK);
	flags |= u32_encode_bits(offset, HDR_INIT_LOCAL_FLAGS_HDR_ADDR_FMASK);
	payload->flags = cpu_to_le32(flags);

	gsi_trans_cmd_add(trans, payload, माप(*payload), payload_addr,
			  direction, opcode);
पूर्ण

व्योम ipa_cmd_रेजिस्टर_ग_लिखो_add(काष्ठा gsi_trans *trans, u32 offset, u32 value,
				u32 mask, bool clear_full)
अणु
	काष्ठा ipa *ipa = container_of(trans->gsi, काष्ठा ipa, gsi);
	काष्ठा ipa_cmd_रेजिस्टर_ग_लिखो *payload;
	जोड़ ipa_cmd_payload *cmd_payload;
	u32 opcode = IPA_CMD_REGISTER_WRITE;
	dma_addr_t payload_addr;
	u32 clear_option;
	u32 options;
	u16 flags;

	/* pipeline_clear_src_grp is not used */
	clear_option = clear_full ? pipeline_clear_full : pipeline_clear_hps;

	/* IPA v4.0+ represents the pipeline clear options in the opcode.  It
	 * also supports a larger offset by encoding additional high-order
	 * bits in the payload flags field.
	 */
	अगर (ipa->version >= IPA_VERSION_4_0) अणु
		u16 offset_high;
		u32 val;

		/* Opcode encodes pipeline clear options */
		/* SKIP_CLEAR is always 0 (करोn't skip pipeline clear) */
		val = u16_encode_bits(clear_option,
				      REGISTER_WRITE_OPCODE_CLEAR_OPTION_FMASK);
		opcode |= val;

		/* Extract the high 4 bits from the offset */
		offset_high = (u16)u32_get_bits(offset, GENMASK(19, 16));
		offset &= (1 << 16) - 1;

		/* Extract the top 4 bits and encode it पूर्णांकo the flags field */
		flags = u16_encode_bits(offset_high,
				REGISTER_WRITE_FLAGS_OFFSET_HIGH_FMASK);
		options = 0;	/* reserved */

	पूर्ण अन्यथा अणु
		flags = 0;	/* SKIP_CLEAR flag is always 0 */
		options = u16_encode_bits(clear_option,
					  REGISTER_WRITE_CLEAR_OPTIONS_FMASK);
	पूर्ण

	cmd_payload = ipa_cmd_payload_alloc(ipa, &payload_addr);
	payload = &cmd_payload->रेजिस्टर_ग_लिखो;

	payload->flags = cpu_to_le16(flags);
	payload->offset = cpu_to_le16((u16)offset);
	payload->value = cpu_to_le32(value);
	payload->value_mask = cpu_to_le32(mask);
	payload->clear_options = cpu_to_le32(options);

	gsi_trans_cmd_add(trans, payload, माप(*payload), payload_addr,
			  DMA_NONE, opcode);
पूर्ण

/* Skip IP packet processing on the next data transfer on a TX channel */
अटल व्योम ipa_cmd_ip_packet_init_add(काष्ठा gsi_trans *trans, u8 endpoपूर्णांक_id)
अणु
	काष्ठा ipa *ipa = container_of(trans->gsi, काष्ठा ipa, gsi);
	क्रमागत ipa_cmd_opcode opcode = IPA_CMD_IP_PACKET_INIT;
	क्रमागत dma_data_direction direction = DMA_TO_DEVICE;
	काष्ठा ipa_cmd_ip_packet_init *payload;
	जोड़ ipa_cmd_payload *cmd_payload;
	dma_addr_t payload_addr;

	/* निश्चित(endpoपूर्णांक_id <
		  field_max(IPA_PACKET_INIT_DEST_ENDPOINT_FMASK)); */

	cmd_payload = ipa_cmd_payload_alloc(ipa, &payload_addr);
	payload = &cmd_payload->ip_packet_init;

	payload->dest_endpoपूर्णांक = u8_encode_bits(endpoपूर्णांक_id,
					IPA_PACKET_INIT_DEST_ENDPOINT_FMASK);

	gsi_trans_cmd_add(trans, payload, माप(*payload), payload_addr,
			  direction, opcode);
पूर्ण

/* Use a DMA command to पढ़ो or ग_लिखो a block of IPA-resident memory */
व्योम ipa_cmd_dma_shared_mem_add(काष्ठा gsi_trans *trans, u32 offset, u16 size,
				dma_addr_t addr, bool toward_ipa)
अणु
	काष्ठा ipa *ipa = container_of(trans->gsi, काष्ठा ipa, gsi);
	क्रमागत ipa_cmd_opcode opcode = IPA_CMD_DMA_SHARED_MEM;
	काष्ठा ipa_cmd_hw_dma_mem_mem *payload;
	जोड़ ipa_cmd_payload *cmd_payload;
	क्रमागत dma_data_direction direction;
	dma_addr_t payload_addr;
	u16 flags;

	/* size and offset must fit in 16 bit fields */
	/* निश्चित(size > 0 && size <= U16_MAX); */
	/* निश्चित(offset <= U16_MAX && ipa->mem_offset <= U16_MAX - offset); */

	offset += ipa->mem_offset;

	cmd_payload = ipa_cmd_payload_alloc(ipa, &payload_addr);
	payload = &cmd_payload->dma_shared_mem;

	/* payload->clear_after_पढ़ो was reserved prior to IPA v4.0.  It's
	 * never needed क्रम current code, so it's 0 regardless of version.
	 */
	payload->size = cpu_to_le16(size);
	payload->local_addr = cpu_to_le16(offset);
	/* payload->flags:
	 *   direction:		0 = ग_लिखो to IPA, 1 पढ़ो from IPA
	 * Starting at v4.0 these are reserved; either way, all zero:
	 *   pipeline clear:	0 = रुको क्रम pipeline clear (करोn't skip)
	 *   clear_options:	0 = pipeline_clear_hps
	 * Instead, क्रम v4.0+ these are encoded in the opcode.  But again
	 * since both values are 0 we won't bother OR'ing them in.
	 */
	flags = toward_ipa ? 0 : DMA_SHARED_MEM_FLAGS_सूचीECTION_FMASK;
	payload->flags = cpu_to_le16(flags);
	payload->प्रणाली_addr = cpu_to_le64(addr);

	direction = toward_ipa ? DMA_TO_DEVICE : DMA_FROM_DEVICE;

	gsi_trans_cmd_add(trans, payload, माप(*payload), payload_addr,
			  direction, opcode);
पूर्ण

अटल व्योम ipa_cmd_ip_tag_status_add(काष्ठा gsi_trans *trans)
अणु
	काष्ठा ipa *ipa = container_of(trans->gsi, काष्ठा ipa, gsi);
	क्रमागत ipa_cmd_opcode opcode = IPA_CMD_IP_PACKET_TAG_STATUS;
	क्रमागत dma_data_direction direction = DMA_TO_DEVICE;
	काष्ठा ipa_cmd_ip_packet_tag_status *payload;
	जोड़ ipa_cmd_payload *cmd_payload;
	dma_addr_t payload_addr;

	/* निश्चित(tag <= field_max(IP_PACKET_TAG_STATUS_TAG_FMASK)); */

	cmd_payload = ipa_cmd_payload_alloc(ipa, &payload_addr);
	payload = &cmd_payload->ip_packet_tag_status;

	payload->tag = le64_encode_bits(0, IP_PACKET_TAG_STATUS_TAG_FMASK);

	gsi_trans_cmd_add(trans, payload, माप(*payload), payload_addr,
			  direction, opcode);
पूर्ण

/* Issue a small command TX data transfer */
अटल व्योम ipa_cmd_transfer_add(काष्ठा gsi_trans *trans)
अणु
	काष्ठा ipa *ipa = container_of(trans->gsi, काष्ठा ipa, gsi);
	क्रमागत dma_data_direction direction = DMA_TO_DEVICE;
	क्रमागत ipa_cmd_opcode opcode = IPA_CMD_NONE;
	जोड़ ipa_cmd_payload *payload;
	dma_addr_t payload_addr;

	/* Just transfer a zero-filled payload काष्ठाure */
	payload = ipa_cmd_payload_alloc(ipa, &payload_addr);

	gsi_trans_cmd_add(trans, payload, माप(*payload), payload_addr,
			  direction, opcode);
पूर्ण

/* Add immediate commands to a transaction to clear the hardware pipeline */
व्योम ipa_cmd_pipeline_clear_add(काष्ठा gsi_trans *trans)
अणु
	काष्ठा ipa *ipa = container_of(trans->gsi, काष्ठा ipa, gsi);
	काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक;

	/* This will complete when the transfer is received */
	reinit_completion(&ipa->completion);

	/* Issue a no-op रेजिस्टर ग_लिखो command (mask 0 means no ग_लिखो) */
	ipa_cmd_रेजिस्टर_ग_लिखो_add(trans, 0, 0, 0, true);

	/* Send a data packet through the IPA pipeline.  The packet_init
	 * command says to send the next packet directly to the exception
	 * endpoपूर्णांक without any other IPA processing.  The tag_status
	 * command requests that status be generated on completion of
	 * that transfer, and that it will be tagged with a value.
	 * Finally, the transfer command sends a small packet of data
	 * (instead of a command) using the command endpoपूर्णांक.
	 */
	endpoपूर्णांक = ipa->name_map[IPA_ENDPOINT_AP_LAN_RX];
	ipa_cmd_ip_packet_init_add(trans, endpoपूर्णांक->endpoपूर्णांक_id);
	ipa_cmd_ip_tag_status_add(trans);
	ipa_cmd_transfer_add(trans);
पूर्ण

/* Returns the number of commands required to clear the pipeline */
u32 ipa_cmd_pipeline_clear_count(व्योम)
अणु
	वापस 4;
पूर्ण

व्योम ipa_cmd_pipeline_clear_रुको(काष्ठा ipa *ipa)
अणु
	रुको_क्रम_completion(&ipa->completion);
पूर्ण

व्योम ipa_cmd_pipeline_clear(काष्ठा ipa *ipa)
अणु
	u32 count = ipa_cmd_pipeline_clear_count();
	काष्ठा gsi_trans *trans;

	trans = ipa_cmd_trans_alloc(ipa, count);
	अगर (trans) अणु
		ipa_cmd_pipeline_clear_add(trans);
		gsi_trans_commit_रुको(trans);
		ipa_cmd_pipeline_clear_रुको(ipa);
	पूर्ण अन्यथा अणु
		dev_err(&ipa->pdev->dev,
			"error allocating %u entry tag transaction\n", count);
	पूर्ण
पूर्ण

अटल काष्ठा ipa_cmd_info *
ipa_cmd_info_alloc(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक, u32 tre_count)
अणु
	काष्ठा gsi_channel *channel;

	channel = &endpoपूर्णांक->ipa->gsi.channel[endpoपूर्णांक->channel_id];

	वापस gsi_trans_pool_alloc(&channel->trans_info.info_pool, tre_count);
पूर्ण

/* Allocate a transaction क्रम the command TX endpoपूर्णांक */
काष्ठा gsi_trans *ipa_cmd_trans_alloc(काष्ठा ipa *ipa, u32 tre_count)
अणु
	काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक;
	काष्ठा gsi_trans *trans;

	endpoपूर्णांक = ipa->name_map[IPA_ENDPOINT_AP_COMMAND_TX];

	trans = gsi_channel_trans_alloc(&ipa->gsi, endpoपूर्णांक->channel_id,
					tre_count, DMA_NONE);
	अगर (trans)
		trans->info = ipa_cmd_info_alloc(endpoपूर्णांक, tre_count);

	वापस trans;
पूर्ण
