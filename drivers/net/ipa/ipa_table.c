<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2021 Linaro Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bits.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/पन.स>
#समावेश <linux/build_bug.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>

#समावेश "ipa.h"
#समावेश "ipa_version.h"
#समावेश "ipa_endpoint.h"
#समावेश "ipa_table.h"
#समावेश "ipa_reg.h"
#समावेश "ipa_mem.h"
#समावेश "ipa_cmd.h"
#समावेश "gsi.h"
#समावेश "gsi_trans.h"

/**
 * DOC: IPA Filter and Route Tables
 *
 * The IPA has tables defined in its local (IPA-resident) memory that define
 * filter and routing rules.  An entry in either of these tables is a little
 * endian 64-bit "slot" that holds the address of a rule definition.  (The
 * size of these slots is 64 bits regardless of the host DMA address size.)
 *
 * Separate tables (both filter and route) used क्रम IPv4 and IPv6.  There
 * are normally another set of "hashed" filter and route tables, which are
 * used with a hash of message metadata.  Hashed operation is not supported
 * by all IPA hardware (IPA v4.2 करोesn't support hashed tables).
 *
 * Rules can be in local memory or in DRAM (प्रणाली memory).  The offset of
 * an object (such as a route or filter table) in IPA-resident memory must
 * 128-byte aligned.  An object in प्रणाली memory (such as a route or filter
 * rule) must be at an 8-byte aligned address.  We currently only place
 * route or filter rules in प्रणाली memory.
 *
 * A rule consists of a contiguous block of 32-bit values terminated with
 * 32 zero bits.  A special "zero entry" rule consisting of 64 zero bits
 * represents "no filtering" or "no routing," and is the reset value क्रम
 * filter or route table rules.
 *
 * Each filter rule is associated with an AP or modem TX endpoपूर्णांक, though
 * not all TX endpoपूर्णांकs support filtering.  The first 64-bit slot in a
 * filter table is a biपंचांगap indicating which endpoपूर्णांकs have entries in
 * the table.  The low-order bit (bit 0) in this biपंचांगap represents a
 * special global filter, which applies to all traffic.  This is not
 * used in the current code.  Bit 1, अगर set, indicates that there is an
 * entry (i.e. slot containing a प्रणाली address referring to a rule) क्रम
 * endpoपूर्णांक 0 in the table.  Bit 3, अगर set, indicates there is an entry
 * क्रम endpoपूर्णांक 2, and so on.  Space is set aside in IPA local memory to
 * hold as many filter table entries as might be required, but typically
 * they are not all used.
 *
 * The AP initializes all entries in a filter table to refer to a "zero"
 * entry.  Once initialized the modem and AP update the entries क्रम
 * endpoपूर्णांकs they "own" directly.  Currently the AP करोes not use the
 * IPA filtering functionality.
 *
 *                    IPA Filter Table
 *                 ----------------------
 * endpoपूर्णांक biपंचांगap | 0x0000000000000048 | Bits 3 and 6 set (endpoपूर्णांकs 2 and 5)
 *                 |--------------------|
 * 1st endpoपूर्णांक    | 0x000123456789abc0 | DMA address क्रम modem endpoपूर्णांक 2 rule
 *                 |--------------------|
 * 2nd endpoपूर्णांक    | 0x000123456789abf0 | DMA address क्रम AP endpoपूर्णांक 5 rule
 *                 |--------------------|
 * (unused)        |                    | (Unused space in filter table)
 *                 |--------------------|
 *                          . . .
 *                 |--------------------|
 * (unused)        |                    | (Unused space in filter table)
 *                 ----------------------
 *
 * The set of available route rules is भागided about equally between the AP
 * and modem.  The AP initializes all entries in a route table to refer to
 * a "zero entry".  Once initialized, the modem and AP are responsible क्रम
 * updating their own entries.  All entries in a route table are usable,
 * though the AP currently करोes not use the IPA routing functionality.
 *
 *                    IPA Route Table
 *                 ----------------------
 * 1st modem route | 0x0001234500001100 | DMA address क्रम first route rule
 *                 |--------------------|
 * 2nd modem route | 0x0001234500001140 | DMA address क्रम second route rule
 *                 |--------------------|
 *                          . . .
 *                 |--------------------|
 * Last modem route| 0x0001234500002280 | DMA address क्रम Nth route rule
 *                 |--------------------|
 * 1st AP route    | 0x0001234500001100 | DMA address क्रम route rule (N+1)
 *                 |--------------------|
 * 2nd AP route    | 0x0001234500001140 | DMA address क्रम next route rule
 *                 |--------------------|
 *                          . . .
 *                 |--------------------|
 * Last AP route   | 0x0001234500002280 | DMA address क्रम last route rule
 *                 ----------------------
 */

/* Assignment of route table entries to the modem and AP */
#घोषणा IPA_ROUTE_MODEM_MIN		0
#घोषणा IPA_ROUTE_MODEM_COUNT		8

#घोषणा IPA_ROUTE_AP_MIN		IPA_ROUTE_MODEM_COUNT
#घोषणा IPA_ROUTE_AP_COUNT \
		(IPA_ROUTE_COUNT_MAX - IPA_ROUTE_MODEM_COUNT)

/* Filter or route rules consist of a set of 32-bit values followed by a
 * 32-bit all-zero rule list terminator.  The "zero rule" is simply an
 * all-zero rule followed by the list terminator.
 */
#घोषणा IPA_ZERO_RULE_SIZE		(2 * माप(__le32))

#अगर_घोषित IPA_VALIDATE

/* Check things that can be validated at build समय. */
अटल व्योम ipa_table_validate_build(व्योम)
अणु
	/* Filter and route tables contain DMA addresses that refer
	 * to filter or route rules.  But the size of a table entry
	 * is 64 bits regardless of what the size of an AP DMA address
	 * is.  A fixed स्थिरant defines the size of an entry, and
	 * code in ipa_table_init() uses a poपूर्णांकer to __le64 to
	 * initialize tables.
	 */
	BUILD_BUG_ON(माप(dma_addr_t) > माप(__le64));

	/* A "zero rule" is used to represent no filtering or no routing.
	 * It is a 64-bit block of zeroed memory.  Code in ipa_table_init()
	 * assumes that it can be written using a poपूर्णांकer to __le64.
	 */
	BUILD_BUG_ON(IPA_ZERO_RULE_SIZE != माप(__le64));

	/* Impose a practical limit on the number of routes */
	BUILD_BUG_ON(IPA_ROUTE_COUNT_MAX > 32);
	/* The modem must be allotted at least one route table entry */
	BUILD_BUG_ON(!IPA_ROUTE_MODEM_COUNT);
	/* But it can't have more than what is available */
	BUILD_BUG_ON(IPA_ROUTE_MODEM_COUNT > IPA_ROUTE_COUNT_MAX);

पूर्ण

अटल bool
ipa_table_valid_one(काष्ठा ipa *ipa, bool route, bool ipv6, bool hashed)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	स्थिर काष्ठा ipa_mem *mem;
	u32 size;

	अगर (route) अणु
		अगर (ipv6)
			mem = hashed ? &ipa->mem[IPA_MEM_V6_ROUTE_HASHED]
				     : &ipa->mem[IPA_MEM_V6_ROUTE];
		अन्यथा
			mem = hashed ? &ipa->mem[IPA_MEM_V4_ROUTE_HASHED]
				     : &ipa->mem[IPA_MEM_V4_ROUTE];
		size = IPA_ROUTE_COUNT_MAX * माप(__le64);
	पूर्ण अन्यथा अणु
		अगर (ipv6)
			mem = hashed ? &ipa->mem[IPA_MEM_V6_FILTER_HASHED]
				     : &ipa->mem[IPA_MEM_V6_FILTER];
		अन्यथा
			mem = hashed ? &ipa->mem[IPA_MEM_V4_FILTER_HASHED]
				     : &ipa->mem[IPA_MEM_V4_FILTER];
		size = (1 + IPA_FILTER_COUNT_MAX) * माप(__le64);
	पूर्ण

	अगर (!ipa_cmd_table_valid(ipa, mem, route, ipv6, hashed))
		वापस false;

	/* mem->size >= size is sufficient, but we'll demand more */
	अगर (mem->size == size)
		वापस true;

	/* Hashed table regions can be zero size अगर hashing is not supported */
	अगर (hashed && !mem->size)
		वापस true;

	dev_err(dev, "IPv%c %s%s table region size 0x%02x, expected 0x%02x\n",
		ipv6 ? '6' : '4', hashed ? "hashed " : "",
		route ? "route" : "filter", mem->size, size);

	वापस false;
पूर्ण

/* Verअगरy the filter and route table memory regions are the expected size */
bool ipa_table_valid(काष्ठा ipa *ipa)
अणु
	bool valid = true;

	valid = valid && ipa_table_valid_one(ipa, false, false, false);
	valid = valid && ipa_table_valid_one(ipa, false, false, true);
	valid = valid && ipa_table_valid_one(ipa, false, true, false);
	valid = valid && ipa_table_valid_one(ipa, false, true, true);
	valid = valid && ipa_table_valid_one(ipa, true, false, false);
	valid = valid && ipa_table_valid_one(ipa, true, false, true);
	valid = valid && ipa_table_valid_one(ipa, true, true, false);
	valid = valid && ipa_table_valid_one(ipa, true, true, true);

	वापस valid;
पूर्ण

bool ipa_filter_map_valid(काष्ठा ipa *ipa, u32 filter_map)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	u32 count;

	अगर (!filter_map) अणु
		dev_err(dev, "at least one filtering endpoint is required\n");

		वापस false;
	पूर्ण

	count = hweight32(filter_map);
	अगर (count > IPA_FILTER_COUNT_MAX) अणु
		dev_err(dev, "too many filtering endpoints (%u, max %u)\n",
			count, IPA_FILTER_COUNT_MAX);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

#अन्यथा /* !IPA_VALIDATE */
अटल व्योम ipa_table_validate_build(व्योम)

अणु
पूर्ण

#पूर्ण_अगर /* !IPA_VALIDATE */

/* Zero entry count means no table, so just वापस a 0 address */
अटल dma_addr_t ipa_table_addr(काष्ठा ipa *ipa, bool filter_mask, u16 count)
अणु
	u32 skip;

	अगर (!count)
		वापस 0;

/* निश्चित(count <= max_t(u32, IPA_FILTER_COUNT_MAX, IPA_ROUTE_COUNT_MAX)); */

	/* Skip over the zero rule and possibly the filter mask */
	skip = filter_mask ? 1 : 2;

	वापस ipa->table_addr + skip * माप(*ipa->table_virt);
पूर्ण

अटल व्योम ipa_table_reset_add(काष्ठा gsi_trans *trans, bool filter,
				u16 first, u16 count, स्थिर काष्ठा ipa_mem *mem)
अणु
	काष्ठा ipa *ipa = container_of(trans->gsi, काष्ठा ipa, gsi);
	dma_addr_t addr;
	u32 offset;
	u16 size;

	/* Nothing to करो अगर the table memory regions is empty */
	अगर (!mem->size)
		वापस;

	अगर (filter)
		first++;	/* skip over biपंचांगap */

	offset = mem->offset + first * माप(__le64);
	size = count * माप(__le64);
	addr = ipa_table_addr(ipa, false, count);

	ipa_cmd_dma_shared_mem_add(trans, offset, size, addr, true);
पूर्ण

/* Reset entries in a single filter table beदीर्घing to either the AP or
 * modem to refer to the zero entry.  The memory region supplied will be
 * क्रम the IPv4 and IPv6 non-hashed and hashed filter tables.
 */
अटल पूर्णांक
ipa_filter_reset_table(काष्ठा ipa *ipa, स्थिर काष्ठा ipa_mem *mem, bool modem)
अणु
	u32 ep_mask = ipa->filter_map;
	u32 count = hweight32(ep_mask);
	काष्ठा gsi_trans *trans;
	क्रमागत gsi_ee_id ee_id;

	अगर (!mem->size)
		वापस 0;

	trans = ipa_cmd_trans_alloc(ipa, count);
	अगर (!trans) अणु
		dev_err(&ipa->pdev->dev,
			"no transaction for %s filter reset\n",
			modem ? "modem" : "AP");
		वापस -EBUSY;
	पूर्ण

	ee_id = modem ? GSI_EE_MODEM : GSI_EE_AP;
	जबतक (ep_mask) अणु
		u32 endpoपूर्णांक_id = __ffs(ep_mask);
		काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक;

		ep_mask ^= BIT(endpoपूर्णांक_id);

		endpoपूर्णांक = &ipa->endpoपूर्णांक[endpoपूर्णांक_id];
		अगर (endpoपूर्णांक->ee_id != ee_id)
			जारी;

		ipa_table_reset_add(trans, true, endpoपूर्णांक_id, 1, mem);
	पूर्ण

	gsi_trans_commit_रुको(trans);

	वापस 0;
पूर्ण

/* Theoretically, each filter table could have more filter slots to
 * update than the maximum number of commands in a transaction.  So
 * we करो each table separately.
 */
अटल पूर्णांक ipa_filter_reset(काष्ठा ipa *ipa, bool modem)
अणु
	पूर्णांक ret;

	ret = ipa_filter_reset_table(ipa, &ipa->mem[IPA_MEM_V4_FILTER], modem);
	अगर (ret)
		वापस ret;

	ret = ipa_filter_reset_table(ipa, &ipa->mem[IPA_MEM_V4_FILTER_HASHED],
				     modem);
	अगर (ret)
		वापस ret;

	ret = ipa_filter_reset_table(ipa, &ipa->mem[IPA_MEM_V6_FILTER], modem);
	अगर (ret)
		वापस ret;
	ret = ipa_filter_reset_table(ipa, &ipa->mem[IPA_MEM_V6_FILTER_HASHED],
				     modem);

	वापस ret;
पूर्ण

/* The AP routes and modem routes are each contiguous within the
 * table.  We can update each table with a single command, and we
 * won't exceed the per-transaction command limit.
 * */
अटल पूर्णांक ipa_route_reset(काष्ठा ipa *ipa, bool modem)
अणु
	काष्ठा gsi_trans *trans;
	u16 first;
	u16 count;

	trans = ipa_cmd_trans_alloc(ipa, 4);
	अगर (!trans) अणु
		dev_err(&ipa->pdev->dev,
			"no transaction for %s route reset\n",
			modem ? "modem" : "AP");
		वापस -EBUSY;
	पूर्ण

	अगर (modem) अणु
		first = IPA_ROUTE_MODEM_MIN;
		count = IPA_ROUTE_MODEM_COUNT;
	पूर्ण अन्यथा अणु
		first = IPA_ROUTE_AP_MIN;
		count = IPA_ROUTE_AP_COUNT;
	पूर्ण

	ipa_table_reset_add(trans, false, first, count,
			    &ipa->mem[IPA_MEM_V4_ROUTE]);
	ipa_table_reset_add(trans, false, first, count,
			    &ipa->mem[IPA_MEM_V4_ROUTE_HASHED]);

	ipa_table_reset_add(trans, false, first, count,
			    &ipa->mem[IPA_MEM_V6_ROUTE]);
	ipa_table_reset_add(trans, false, first, count,
			    &ipa->mem[IPA_MEM_V6_ROUTE_HASHED]);

	gsi_trans_commit_रुको(trans);

	वापस 0;
पूर्ण

व्योम ipa_table_reset(काष्ठा ipa *ipa, bool modem)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	स्थिर अक्षर *ee_name;
	पूर्णांक ret;

	ee_name = modem ? "modem" : "AP";

	/* Report errors, but reset filter and route tables */
	ret = ipa_filter_reset(ipa, modem);
	अगर (ret)
		dev_err(dev, "error %d resetting filter table for %s\n",
				ret, ee_name);

	ret = ipa_route_reset(ipa, modem);
	अगर (ret)
		dev_err(dev, "error %d resetting route table for %s\n",
				ret, ee_name);
पूर्ण

पूर्णांक ipa_table_hash_flush(काष्ठा ipa *ipa)
अणु
	u32 offset = ipa_reg_filt_rout_hash_flush_offset(ipa->version);
	काष्ठा gsi_trans *trans;
	u32 val;

	अगर (!ipa_table_hash_support(ipa))
		वापस 0;

	trans = ipa_cmd_trans_alloc(ipa, 1);
	अगर (!trans) अणु
		dev_err(&ipa->pdev->dev, "no transaction for hash flush\n");
		वापस -EBUSY;
	पूर्ण

	val = IPV4_FILTER_HASH_FMASK | IPV6_FILTER_HASH_FMASK;
	val |= IPV6_ROUTER_HASH_FMASK | IPV4_ROUTER_HASH_FMASK;

	ipa_cmd_रेजिस्टर_ग_लिखो_add(trans, offset, val, val, false);

	gsi_trans_commit_रुको(trans);

	वापस 0;
पूर्ण

अटल व्योम ipa_table_init_add(काष्ठा gsi_trans *trans, bool filter,
			       क्रमागत ipa_cmd_opcode opcode,
			       स्थिर काष्ठा ipa_mem *mem,
			       स्थिर काष्ठा ipa_mem *hash_mem)
अणु
	काष्ठा ipa *ipa = container_of(trans->gsi, काष्ठा ipa, gsi);
	dma_addr_t hash_addr;
	dma_addr_t addr;
	u16 hash_count;
	u16 hash_size;
	u16 count;
	u16 size;

	/* The number of filtering endpoपूर्णांकs determines number of entries
	 * in the filter table.  The hashed and non-hashed filter table
	 * will have the same number of entries.  The size of the route
	 * table region determines the number of entries it has.
	 */
	अगर (filter) अणु
		count = hweight32(ipa->filter_map);
		hash_count = hash_mem->size ? count : 0;
	पूर्ण अन्यथा अणु
		count = mem->size / माप(__le64);
		hash_count = hash_mem->size / माप(__le64);
	पूर्ण
	size = count * माप(__le64);
	hash_size = hash_count * माप(__le64);

	addr = ipa_table_addr(ipa, filter, count);
	hash_addr = ipa_table_addr(ipa, filter, hash_count);

	ipa_cmd_table_init_add(trans, opcode, size, mem->offset, addr,
			       hash_size, hash_mem->offset, hash_addr);
पूर्ण

पूर्णांक ipa_table_setup(काष्ठा ipa *ipa)
अणु
	काष्ठा gsi_trans *trans;

	trans = ipa_cmd_trans_alloc(ipa, 4);
	अगर (!trans) अणु
		dev_err(&ipa->pdev->dev, "no transaction for table setup\n");
		वापस -EBUSY;
	पूर्ण

	ipa_table_init_add(trans, false, IPA_CMD_IP_V4_ROUTING_INIT,
			   &ipa->mem[IPA_MEM_V4_ROUTE],
			   &ipa->mem[IPA_MEM_V4_ROUTE_HASHED]);

	ipa_table_init_add(trans, false, IPA_CMD_IP_V6_ROUTING_INIT,
			   &ipa->mem[IPA_MEM_V6_ROUTE],
			   &ipa->mem[IPA_MEM_V6_ROUTE_HASHED]);

	ipa_table_init_add(trans, true, IPA_CMD_IP_V4_FILTER_INIT,
			   &ipa->mem[IPA_MEM_V4_FILTER],
			   &ipa->mem[IPA_MEM_V4_FILTER_HASHED]);

	ipa_table_init_add(trans, true, IPA_CMD_IP_V6_FILTER_INIT,
			   &ipa->mem[IPA_MEM_V6_FILTER],
			   &ipa->mem[IPA_MEM_V6_FILTER_HASHED]);

	gsi_trans_commit_रुको(trans);

	वापस 0;
पूर्ण

/**
 * ipa_filter_tuple_zero() - Zero an endpoपूर्णांक's hashed filter tuple
 * @endpoपूर्णांक:	Endpoपूर्णांक whose filter hash tuple should be zeroed
 *
 * Endpoपूर्णांक must be क्रम the AP (not modem) and support filtering. Updates
 * the filter hash values without changing route ones.
 */
अटल व्योम ipa_filter_tuple_zero(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 endpoपूर्णांक_id = endpoपूर्णांक->endpoपूर्णांक_id;
	u32 offset;
	u32 val;

	offset = IPA_REG_ENDP_FILTER_ROUTER_HSH_CFG_N_OFFSET(endpoपूर्णांक_id);

	val = ioपढ़ो32(endpoपूर्णांक->ipa->reg_virt + offset);

	/* Zero all filter-related fields, preserving the rest */
	u32p_replace_bits(&val, 0, IPA_REG_ENDP_FILTER_HASH_MSK_ALL);

	ioग_लिखो32(val, endpoपूर्णांक->ipa->reg_virt + offset);
पूर्ण

/* Configure a hashed filter table; there is no ipa_filter_deconfig() */
अटल व्योम ipa_filter_config(काष्ठा ipa *ipa, bool modem)
अणु
	क्रमागत gsi_ee_id ee_id = modem ? GSI_EE_MODEM : GSI_EE_AP;
	u32 ep_mask = ipa->filter_map;

	अगर (!ipa_table_hash_support(ipa))
		वापस;

	जबतक (ep_mask) अणु
		u32 endpoपूर्णांक_id = __ffs(ep_mask);
		काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक;

		ep_mask ^= BIT(endpoपूर्णांक_id);

		endpoपूर्णांक = &ipa->endpoपूर्णांक[endpoपूर्णांक_id];
		अगर (endpoपूर्णांक->ee_id == ee_id)
			ipa_filter_tuple_zero(endpoपूर्णांक);
	पूर्ण
पूर्ण

अटल bool ipa_route_id_modem(u32 route_id)
अणु
	वापस route_id >= IPA_ROUTE_MODEM_MIN &&
		route_id <= IPA_ROUTE_MODEM_MIN + IPA_ROUTE_MODEM_COUNT - 1;
पूर्ण

/**
 * ipa_route_tuple_zero() - Zero a hashed route table entry tuple
 * @ipa:	IPA poपूर्णांकer
 * @route_id:	Route table entry whose hash tuple should be zeroed
 *
 * Updates the route hash values without changing filter ones.
 */
अटल व्योम ipa_route_tuple_zero(काष्ठा ipa *ipa, u32 route_id)
अणु
	u32 offset = IPA_REG_ENDP_FILTER_ROUTER_HSH_CFG_N_OFFSET(route_id);
	u32 val;

	val = ioपढ़ो32(ipa->reg_virt + offset);

	/* Zero all route-related fields, preserving the rest */
	u32p_replace_bits(&val, 0, IPA_REG_ENDP_ROUTER_HASH_MSK_ALL);

	ioग_लिखो32(val, ipa->reg_virt + offset);
पूर्ण

/* Configure a hashed route table; there is no ipa_route_deconfig() */
अटल व्योम ipa_route_config(काष्ठा ipa *ipa, bool modem)
अणु
	u32 route_id;

	अगर (!ipa_table_hash_support(ipa))
		वापस;

	क्रम (route_id = 0; route_id < IPA_ROUTE_COUNT_MAX; route_id++)
		अगर (ipa_route_id_modem(route_id) == modem)
			ipa_route_tuple_zero(ipa, route_id);
पूर्ण

/* Configure a filter and route tables; there is no ipa_table_deconfig() */
व्योम ipa_table_config(काष्ठा ipa *ipa)
अणु
	ipa_filter_config(ipa, false);
	ipa_filter_config(ipa, true);
	ipa_route_config(ipa, false);
	ipa_route_config(ipa, true);
पूर्ण

/*
 * Initialize a coherent DMA allocation containing initialized filter and
 * route table data.  This is used when initializing or resetting the IPA
 * filter or route table.
 *
 * The first entry in a filter table contains a biपंचांगap indicating which
 * endpoपूर्णांकs contain entries in the table.  In addition to that first entry,
 * there are at most IPA_FILTER_COUNT_MAX entries that follow.  Filter table
 * entries are 64 bits wide, and (other than the biपंचांगap) contain the DMA
 * address of a filter rule.  A "zero rule" indicates no filtering, and
 * consists of 64 bits of zeroes.  When a filter table is initialized (or
 * reset) its entries are made to refer to the zero rule.
 *
 * Each entry in a route table is the DMA address of a routing rule.  For
 * routing there is also a 64-bit "zero rule" that means no routing, and
 * when a route table is initialized or reset, its entries are made to refer
 * to the zero rule.  The zero rule is shared क्रम route and filter tables.
 *
 * Note that the IPA hardware requires a filter or route rule address to be
 * aligned on a 128 byte boundary.  The coherent DMA buffer we allocate here
 * has a minimum alignment, and we place the zero rule at the base of that
 * allocated space.  In ipa_table_init() we verअगरy the minimum DMA allocation
 * meets our requirement.
 *
 *	     +-------------------+
 *	 --> |     zero rule     |
 *	/    |-------------------|
 *	|    |     filter mask   |
 *	|\   |-------------------|
 *	| ---- zero rule address | \
 *	|\   |-------------------|  |
 *	| ---- zero rule address |  |	IPA_FILTER_COUNT_MAX
 *	|    |-------------------|   >	or IPA_ROUTE_COUNT_MAX,
 *	|	      ...	    |	whichever is greater
 *	 \   |-------------------|  |
 *	  ---- zero rule address | /
 *	     +-------------------+
 */
पूर्णांक ipa_table_init(काष्ठा ipa *ipa)
अणु
	u32 count = max_t(u32, IPA_FILTER_COUNT_MAX, IPA_ROUTE_COUNT_MAX);
	काष्ठा device *dev = &ipa->pdev->dev;
	dma_addr_t addr;
	__le64 le_addr;
	__le64 *virt;
	माप_प्रकार size;

	ipa_table_validate_build();

	/* The IPA hardware requires route and filter table rules to be
	 * aligned on a 128-byte boundary.  We put the "zero rule" at the
	 * base of the table area allocated here.  The DMA address वापसed
	 * by dma_alloc_coherent() is guaranteed to be a घातer-of-2 number
	 * of pages, which satisfies the rule alignment requirement.
	 */
	size = IPA_ZERO_RULE_SIZE + (1 + count) * माप(__le64);
	virt = dma_alloc_coherent(dev, size, &addr, GFP_KERNEL);
	अगर (!virt)
		वापस -ENOMEM;

	ipa->table_virt = virt;
	ipa->table_addr = addr;

	/* First slot is the zero rule */
	*virt++ = 0;

	/* Next is the filter table biपंचांगap.  The "soft" biपंचांगap value
	 * must be converted to the hardware representation by shअगरting
	 * it left one position.  (Bit 0 repesents global filtering,
	 * which is possible but not used.)
	 */
	*virt++ = cpu_to_le64((u64)ipa->filter_map << 1);

	/* All the rest contain the DMA address of the zero rule */
	le_addr = cpu_to_le64(addr);
	जबतक (count--)
		*virt++ = le_addr;

	वापस 0;
पूर्ण

व्योम ipa_table_निकास(काष्ठा ipa *ipa)
अणु
	u32 count = max_t(u32, 1 + IPA_FILTER_COUNT_MAX, IPA_ROUTE_COUNT_MAX);
	काष्ठा device *dev = &ipa->pdev->dev;
	माप_प्रकार size;

	size = IPA_ZERO_RULE_SIZE + (1 + count) * माप(__le64);

	dma_मुक्त_coherent(dev, size, ipa->table_virt, ipa->table_addr);
	ipa->table_addr = 0;
	ipa->table_virt = शून्य;
पूर्ण
