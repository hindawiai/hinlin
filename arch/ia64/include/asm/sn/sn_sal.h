<शैली गुरु>
#अगर_अघोषित _ASM_IA64_SN_SN_SAL_H
#घोषणा _ASM_IA64_SN_SN_SAL_H

/*
 * System Abstraction Layer definitions क्रम IA64
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.  All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/sal.h>

// SGI Specअगरic Calls
#घोषणा  SN_SAL_GET_PARTITION_ADDR		   0x02000009
#घोषणा  SN_SAL_MEMPROTECT                         0x0200003e

#घोषणा  SN_SAL_WATCHLIST_ALLOC			   0x02000070
#घोषणा  SN_SAL_WATCHLIST_FREE			   0x02000071

/*
 * SAL Error Codes
 */
#घोषणा SALRET_MORE_PASSES	1
#घोषणा SALRET_OK		0
#घोषणा SALRET_NOT_IMPLEMENTED	(-1)
#घोषणा SALRET_INVALID_ARG	(-2)
#घोषणा SALRET_ERROR		(-3)

/*
 * Returns the physical address of the partition's reserved page through
 * an iterative number of calls.
 *
 * On first call, 'cookie' and 'len' should be set to 0, and 'addr'
 * set to the nasid of the partition whose reserved page's address is
 * being sought.
 * On subsequent calls, pass the values, that were passed back on the
 * previous call.
 *
 * While the वापस status equals SALRET_MORE_PASSES, keep calling
 * this function after first copying 'len' bytes starting at 'addr'
 * पूर्णांकo 'buf'. Once the return status equals SALRET_OK, 'addr' will
 * be the physical address of the partition's reserved page. If the
 * वापस status equals neither of these, an error as occurred.
 */
अटल अंतरभूत s64
sn_partition_reserved_page_pa(u64 buf, u64 *cookie, u64 *addr, u64 *len)
अणु
	काष्ठा ia64_sal_retval rv;
	ia64_sal_oemcall_reentrant(&rv, SN_SAL_GET_PARTITION_ADDR, *cookie,
				   *addr, buf, *len, 0, 0, 0);
	*cookie = rv.v0;
	*addr = rv.v1;
	*len = rv.v2;
	वापस rv.status;
पूर्ण

/*
 * Change memory access protections क्रम a physical address range.
 * nasid_array is not used on Altix, but may be in future architectures.
 * Available memory protection access classes are defined after the function.
 */
अटल अंतरभूत पूर्णांक
sn_change_memprotect(u64 paddr, u64 len, u64 perms, u64 *nasid_array)
अणु
	काष्ठा ia64_sal_retval ret_stuff;

	ia64_sal_oemcall_nolock(&ret_stuff, SN_SAL_MEMPROTECT, paddr, len,
				(u64)nasid_array, perms, 0, 0, 0);
	वापस ret_stuff.status;
पूर्ण
#घोषणा SN_MEMPROT_ACCESS_CLASS_0		0x14a080
#घोषणा SN_MEMPROT_ACCESS_CLASS_1		0x2520c2
#घोषणा SN_MEMPROT_ACCESS_CLASS_2		0x14a1ca
#घोषणा SN_MEMPROT_ACCESS_CLASS_3		0x14a290
#घोषणा SN_MEMPROT_ACCESS_CLASS_6		0x084080
#घोषणा SN_MEMPROT_ACCESS_CLASS_7		0x021080

जोड़ sn_watchlist_u अणु
	u64     val;
	काष्ठा अणु
		u64	blade	: 16,
			size	: 32,
			filler	: 16;
	पूर्ण;
पूर्ण;

अटल अंतरभूत पूर्णांक
sn_mq_watchlist_alloc(पूर्णांक blade, व्योम *mq, अचिन्हित पूर्णांक mq_size,
				अचिन्हित दीर्घ *पूर्णांकr_mmr_offset)
अणु
	काष्ठा ia64_sal_retval rv;
	अचिन्हित दीर्घ addr;
	जोड़ sn_watchlist_u size_blade;
	पूर्णांक watchlist;

	addr = (अचिन्हित दीर्घ)mq;
	size_blade.size = mq_size;
	size_blade.blade = blade;

	/*
	 * bios वापसs watchlist number or negative error number.
	 */
	ia64_sal_oemcall_nolock(&rv, SN_SAL_WATCHLIST_ALLOC, addr,
			size_blade.val, (u64)पूर्णांकr_mmr_offset,
			(u64)&watchlist, 0, 0, 0);
	अगर (rv.status < 0)
		वापस rv.status;

	वापस watchlist;
पूर्ण

अटल अंतरभूत पूर्णांक
sn_mq_watchlist_मुक्त(पूर्णांक blade, पूर्णांक watchlist_num)
अणु
	काष्ठा ia64_sal_retval rv;
	ia64_sal_oemcall_nolock(&rv, SN_SAL_WATCHLIST_FREE, blade,
			watchlist_num, 0, 0, 0, 0, 0);
	वापस rv.status;
पूर्ण
#पूर्ण_अगर /* _ASM_IA64_SN_SN_SAL_H */
