<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2021 Linaro Ltd.
 */
#अगर_अघोषित _IPA_MEM_H_
#घोषणा _IPA_MEM_H_

काष्ठा ipa;
काष्ठा ipa_mem_data;

/**
 * DOC: IPA Local Memory
 *
 * The IPA has a block of shared memory, भागided पूर्णांकo regions used क्रम
 * specअगरic purposes.
 *
 * The regions within the shared block are bounded by an offset (relative to
 * the "ipa-shared" memory range) and size found in the IPA_SHARED_MEM_SIZE
 * रेजिस्टर.
 *
 * Each region is optionally preceded by one or more 32-bit "canary" values.
 * These are meant to detect out-of-range ग_लिखोs (अगर they become corrupted).
 * A given region (such as a filter or routing table) has the same number
 * of canaries क्रम all IPA hardware versions.  Still, the number used is
 * defined in the config data, allowing क्रम generic handling of regions.
 *
 * The set of memory regions is defined in configuration data.  They are
 * subject to these स्थिरraपूर्णांकs:
 * - a zero offset and zero size represents and undefined region
 * - a region's size करोes not include space क्रम its "canary" values
 * - a region's offset is defined to be *past* all "canary" values
 * - offset must be large enough to account क्रम all canaries
 * - a region's size may be zero, but may still have canaries
 * - all offsets must be 8-byte aligned
 * - most sizes must be a multiple of 8
 * - modem memory size must be a multiple of 4
 * - the microcontroller ring offset must be a multiple of 1024
 */

/* The maximum allowed size क्रम any memory region */
#घोषणा IPA_MEM_MAX	(2 * PAGE_SIZE)

/* IPA-resident memory region ids */
क्रमागत ipa_mem_id अणु
	IPA_MEM_UC_SHARED,		/* 0 canaries */
	IPA_MEM_UC_INFO,		/* 0 canaries */
	IPA_MEM_V4_FILTER_HASHED,	/* 2 canaries */
	IPA_MEM_V4_FILTER,		/* 2 canaries */
	IPA_MEM_V6_FILTER_HASHED,	/* 2 canaries */
	IPA_MEM_V6_FILTER,		/* 2 canaries */
	IPA_MEM_V4_ROUTE_HASHED,	/* 2 canaries */
	IPA_MEM_V4_ROUTE,		/* 2 canaries */
	IPA_MEM_V6_ROUTE_HASHED,	/* 2 canaries */
	IPA_MEM_V6_ROUTE,		/* 2 canaries */
	IPA_MEM_MODEM_HEADER,		/* 2 canaries */
	IPA_MEM_AP_HEADER,		/* 0 canaries */
	IPA_MEM_MODEM_PROC_CTX,		/* 2 canaries */
	IPA_MEM_AP_PROC_CTX,		/* 0 canaries */
	IPA_MEM_NAT_TABLE,		/* 4 canaries (IPA v4.5 and above) */
	IPA_MEM_PDN_CONFIG,		/* 0/2 canaries (IPA v4.0 and above) */
	IPA_MEM_STATS_QUOTA_MODEM,	/* 2/4 canaries (IPA v4.0 and above) */
	IPA_MEM_STATS_QUOTA_AP,		/* 0 canaries (IPA v4.0 and above) */
	IPA_MEM_STATS_TETHERING,	/* 0 canaries (IPA v4.0 and above) */
	IPA_MEM_STATS_V4_FILTER,	/* 0 canaries (IPA v4.0-v4.2) */
	IPA_MEM_STATS_V6_FILTER,	/* 0 canaries (IPA v4.0-v4.2) */
	IPA_MEM_STATS_V4_ROUTE,		/* 0 canaries (IPA v4.0-v4.2) */
	IPA_MEM_STATS_V6_ROUTE,		/* 0 canaries (IPA v4.0-v4.2) */
	IPA_MEM_STATS_FILTER_ROUTE,	/* 0 canaries (IPA v4.5 and above) */
	IPA_MEM_STATS_DROP,		/* 0 canaries (IPA v4.0 and above) */
	IPA_MEM_MODEM,			/* 0/2 canaries */
	IPA_MEM_UC_EVENT_RING,		/* 1 canary */
	IPA_MEM_COUNT,			/* Number of regions (not an index) */
पूर्ण;

/**
 * काष्ठा ipa_mem - IPA local memory region description
 * @offset:		offset in IPA memory space to base of the region
 * @size:		size in bytes base of the region
 * @canary_count:	Number of 32-bit "canary" values that precede region
 */
काष्ठा ipa_mem अणु
	u32 offset;
	u16 size;
	u16 canary_count;
पूर्ण;

पूर्णांक ipa_mem_config(काष्ठा ipa *ipa);
व्योम ipa_mem_deconfig(काष्ठा ipa *ipa);

पूर्णांक ipa_mem_setup(काष्ठा ipa *ipa);	/* No ipa_mem_tearकरोwn() needed */

पूर्णांक ipa_mem_zero_modem(काष्ठा ipa *ipa);

पूर्णांक ipa_mem_init(काष्ठा ipa *ipa, स्थिर काष्ठा ipa_mem_data *mem_data);
व्योम ipa_mem_निकास(काष्ठा ipa *ipa);

#पूर्ण_अगर /* _IPA_MEM_H_ */
