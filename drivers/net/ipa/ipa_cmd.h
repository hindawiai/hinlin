<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2020 Linaro Ltd.
 */
#अगर_अघोषित _IPA_CMD_H_
#घोषणा _IPA_CMD_H_

#समावेश <linux/types.h>
#समावेश <linux/dma-direction.h>

काष्ठा sk_buff;
काष्ठा scatterlist;

काष्ठा ipa;
काष्ठा ipa_mem;
काष्ठा gsi_trans;
काष्ठा gsi_channel;

/**
 * क्रमागत ipa_cmd_opcode:	IPA immediate commands
 *
 * @IPA_CMD_IP_V4_FILTER_INIT:	Initialize IPv4 filter table
 * @IPA_CMD_IP_V6_FILTER_INIT:	Initialize IPv6 filter table
 * @IPA_CMD_IP_V4_ROUTING_INIT:	Initialize IPv4 routing table
 * @IPA_CMD_IP_V6_ROUTING_INIT:	Initialize IPv6 routing table
 * @IPA_CMD_HDR_INIT_LOCAL:	Initialize IPA-local header memory
 * @IPA_CMD_REGISTER_WRITE:	Register ग_लिखो perक्रमmed by IPA
 * @IPA_CMD_IP_PACKET_INIT:	Set up next packet's destination endpoपूर्णांक
 * @IPA_CMD_DMA_SHARED_MEM:	DMA command perक्रमmed by IPA
 * @IPA_CMD_IP_PACKET_TAG_STATUS: Have next packet generate tag * status
 * @IPA_CMD_NONE:		Special (invalid) "not a command" value
 *
 * All immediate commands are issued using the AP command TX endpoपूर्णांक.
 */
क्रमागत ipa_cmd_opcode अणु
	IPA_CMD_NONE			= 0x0,
	IPA_CMD_IP_V4_FILTER_INIT	= 0x3,
	IPA_CMD_IP_V6_FILTER_INIT	= 0x4,
	IPA_CMD_IP_V4_ROUTING_INIT	= 0x7,
	IPA_CMD_IP_V6_ROUTING_INIT	= 0x8,
	IPA_CMD_HDR_INIT_LOCAL		= 0x9,
	IPA_CMD_REGISTER_WRITE		= 0xc,
	IPA_CMD_IP_PACKET_INIT		= 0x10,
	IPA_CMD_DMA_SHARED_MEM		= 0x13,
	IPA_CMD_IP_PACKET_TAG_STATUS	= 0x14,
पूर्ण;

/**
 * काष्ठा ipa_cmd_info - inक्रमmation needed क्रम an IPA immediate command
 *
 * @opcode:	The command opcode.
 * @direction:	Direction of data transfer क्रम DMA commands
 */
काष्ठा ipa_cmd_info अणु
	क्रमागत ipa_cmd_opcode opcode;
	क्रमागत dma_data_direction direction;
पूर्ण;

#अगर_घोषित IPA_VALIDATE

/**
 * ipa_cmd_table_valid() - Validate a memory region holding a table
 * @ipa:	- IPA poपूर्णांकer
 * @mem:	- IPA memory region descriptor
 * @route:	- Whether the region holds a route or filter table
 * @ipv6:	- Whether the table is क्रम IPv6 or IPv4
 * @hashed:	- Whether the table is hashed or non-hashed
 *
 * Return:	true अगर region is valid, false otherwise
 */
bool ipa_cmd_table_valid(काष्ठा ipa *ipa, स्थिर काष्ठा ipa_mem *mem,
			    bool route, bool ipv6, bool hashed);

/**
 * ipa_cmd_data_valid() - Validate command-realted configuration is valid
 * @ipa:	- IPA poपूर्णांकer
 *
 * Return:	true अगर assumptions required क्रम command are valid
 */
bool ipa_cmd_data_valid(काष्ठा ipa *ipa);

#अन्यथा /* !IPA_VALIDATE */

अटल अंतरभूत bool ipa_cmd_table_valid(काष्ठा ipa *ipa,
				       स्थिर काष्ठा ipa_mem *mem, bool route,
				       bool ipv6, bool hashed)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool ipa_cmd_data_valid(काष्ठा ipa *ipa)
अणु
	वापस true;
पूर्ण

#पूर्ण_अगर /* !IPA_VALIDATE */

/**
 * ipa_cmd_pool_init() - initialize command channel pools
 * @channel:	AP->IPA command TX GSI channel poपूर्णांकer
 * @tre_count:	Number of pool elements to allocate
 *
 * Return:	0 अगर successful, or a negative error code
 */
पूर्णांक ipa_cmd_pool_init(काष्ठा gsi_channel *channel, u32 tre_count);

/**
 * ipa_cmd_pool_निकास() - Inverse of ipa_cmd_pool_init()
 * @channel:	AP->IPA command TX GSI channel poपूर्णांकer
 */
व्योम ipa_cmd_pool_निकास(काष्ठा gsi_channel *channel);

/**
 * ipa_cmd_table_init_add() - Add table init command to a transaction
 * @trans:	GSI transaction
 * @opcode:	IPA immediate command opcode
 * @size:	Size of non-hashed routing table memory
 * @offset:	Offset in IPA shared memory of non-hashed routing table memory
 * @addr:	DMA address of non-hashed table data to ग_लिखो
 * @hash_size:	Size of hashed routing table memory
 * @hash_offset: Offset in IPA shared memory of hashed routing table memory
 * @hash_addr:	DMA address of hashed table data to ग_लिखो
 *
 * If hash_size is 0, hash_offset and hash_addr are ignored.
 */
व्योम ipa_cmd_table_init_add(काष्ठा gsi_trans *trans, क्रमागत ipa_cmd_opcode opcode,
			    u16 size, u32 offset, dma_addr_t addr,
			    u16 hash_size, u32 hash_offset,
			    dma_addr_t hash_addr);

/**
 * ipa_cmd_hdr_init_local_add() - Add a header init command to a transaction
 * @trans:	GSI transaction
 * @offset:	Offset of header memory in IPA local space
 * @size:	Size of header memory
 * @addr:	DMA address of buffer to be written from
 *
 * Defines and fills the location in IPA memory to use क्रम headers.
 */
व्योम ipa_cmd_hdr_init_local_add(काष्ठा gsi_trans *trans, u32 offset, u16 size,
				dma_addr_t addr);

/**
 * ipa_cmd_रेजिस्टर_ग_लिखो_add() - Add a रेजिस्टर ग_लिखो command to a transaction
 * @trans:	GSI transaction
 * @offset:	Offset of रेजिस्टर to be written
 * @value:	Value to be written
 * @mask:	Mask of bits in रेजिस्टर to update with bits from value
 * @clear_full: Pipeline clear option; true means full pipeline clear
 */
व्योम ipa_cmd_रेजिस्टर_ग_लिखो_add(काष्ठा gsi_trans *trans, u32 offset, u32 value,
				u32 mask, bool clear_full);

/**
 * ipa_cmd_dma_shared_mem_add() - Add a DMA memory command to a transaction
 * @trans:	GSI transaction
 * @offset:	Offset of IPA memory to be पढ़ो or written
 * @size:	Number of bytes of memory to be transferred
 * @addr:	DMA address of buffer to be पढ़ो पूर्णांकo or written from
 * @toward_ipa:	true means ग_लिखो to IPA memory; false means पढ़ो
 */
व्योम ipa_cmd_dma_shared_mem_add(काष्ठा gsi_trans *trans, u32 offset,
				u16 size, dma_addr_t addr, bool toward_ipa);

/**
 * ipa_cmd_pipeline_clear_add() - Add pipeline clear commands to a transaction
 * @trans:	GSI transaction
 */
व्योम ipa_cmd_pipeline_clear_add(काष्ठा gsi_trans *trans);

/**
 * ipa_cmd_pipeline_clear_count() - # commands required to clear pipeline
 *
 * Return:	The number of elements to allocate in a transaction
 *		to hold commands to clear the pipeline
 */
u32 ipa_cmd_pipeline_clear_count(व्योम);

/**
 * ipa_cmd_pipeline_clear_रुको() - Wait pipeline clear to complete
 * @ipa:	- IPA poपूर्णांकer
 */
व्योम ipa_cmd_pipeline_clear_रुको(काष्ठा ipa *ipa);

/**
 * ipa_cmd_pipeline_clear() - Clear the hardware pipeline
 * @ipa:	- IPA poपूर्णांकer
 */
व्योम ipa_cmd_pipeline_clear(काष्ठा ipa *ipa);

/**
 * ipa_cmd_trans_alloc() - Allocate a transaction क्रम the command TX endpoपूर्णांक
 * @ipa:	IPA poपूर्णांकer
 * @tre_count:	Number of elements in the transaction
 *
 * Return:	A GSI transaction काष्ठाure, or a null poपूर्णांकer अगर all
 *		available transactions are in use
 */
काष्ठा gsi_trans *ipa_cmd_trans_alloc(काष्ठा ipa *ipa, u32 tre_count);

#पूर्ण_अगर /* _IPA_CMD_H_ */
