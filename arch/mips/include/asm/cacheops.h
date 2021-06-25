<शैली गुरु>
/*
 * Cache operations क्रम the cache inकाष्ठाion.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) Copyright 1996, 97, 99, 2002, 03 Ralf Baechle
 * (C) Copyright 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित __ASM_CACHEOPS_H
#घोषणा __ASM_CACHEOPS_H

/*
 * Most cache ops are split पूर्णांकo a 2 bit field identअगरying the cache, and a 3
 * bit field identअगरying the cache operation.
 */
#घोषणा CacheOp_Cache			0x03
#घोषणा CacheOp_Op			0x1c

#घोषणा Cache_I				0x00
#घोषणा Cache_D				0x01
#घोषणा Cache_T				0x02
#घोषणा Cache_V				0x02 /* Loongson-3 */
#घोषणा Cache_S				0x03

#घोषणा Index_Writeback_Inv		0x00
#घोषणा Index_Load_Tag			0x04
#घोषणा Index_Store_Tag			0x08
#घोषणा Hit_Invalidate			0x10
#घोषणा Hit_Writeback_Inv		0x14	/* not with Cache_I though */
#घोषणा Hit_Writeback			0x18

/*
 * Cache Operations available on all MIPS processors with R4000-style caches
 */
#घोषणा Index_Invalidate_I		(Cache_I | Index_Writeback_Inv)
#घोषणा Index_Writeback_Inv_D		(Cache_D | Index_Writeback_Inv)
#घोषणा Index_Load_Tag_I		(Cache_I | Index_Load_Tag)
#घोषणा Index_Load_Tag_D		(Cache_D | Index_Load_Tag)
#घोषणा Index_Store_Tag_I		(Cache_I | Index_Store_Tag)
#घोषणा Index_Store_Tag_D		(Cache_D | Index_Store_Tag)
#घोषणा Hit_Invalidate_I		(Cache_I | Hit_Invalidate)
#घोषणा Hit_Invalidate_D		(Cache_D | Hit_Invalidate)
#घोषणा Hit_Writeback_Inv_D		(Cache_D | Hit_Writeback_Inv)

/*
 * R4000-specअगरic cacheops
 */
#घोषणा Create_Dirty_Excl_D		(Cache_D | 0x0c)
#घोषणा Fill_I				(Cache_I | 0x14)
#घोषणा Hit_Writeback_I			(Cache_I | Hit_Writeback)
#घोषणा Hit_Writeback_D			(Cache_D | Hit_Writeback)

/*
 * R4000SC and R4400SC-specअगरic cacheops
 */
#घोषणा Cache_SI			0x02
#घोषणा Cache_SD			0x03

#घोषणा Index_Invalidate_SI		(Cache_SI | Index_Writeback_Inv)
#घोषणा Index_Writeback_Inv_SD		(Cache_SD | Index_Writeback_Inv)
#घोषणा Index_Load_Tag_SI		(Cache_SI | Index_Load_Tag)
#घोषणा Index_Load_Tag_SD		(Cache_SD | Index_Load_Tag)
#घोषणा Index_Store_Tag_SI		(Cache_SI | Index_Store_Tag)
#घोषणा Index_Store_Tag_SD		(Cache_SD | Index_Store_Tag)
#घोषणा Create_Dirty_Excl_SD		(Cache_SD | 0x0c)
#घोषणा Hit_Invalidate_SI		(Cache_SI | Hit_Invalidate)
#घोषणा Hit_Invalidate_SD		(Cache_SD | Hit_Invalidate)
#घोषणा Hit_Writeback_Inv_SD		(Cache_SD | Hit_Writeback_Inv)
#घोषणा Hit_Writeback_SD		(Cache_SD | Hit_Writeback)
#घोषणा Hit_Set_Virtual_SI		(Cache_SI | 0x1c)
#घोषणा Hit_Set_Virtual_SD		(Cache_SD | 0x1c)

/*
 * R5000-specअगरic cacheops
 */
#घोषणा R5K_Page_Invalidate_S		(Cache_S | 0x14)

/*
 * RM7000-specअगरic cacheops
 */
#घोषणा Page_Invalidate_T		(Cache_T | 0x14)
#घोषणा Index_Store_Tag_T		(Cache_T | Index_Store_Tag)
#घोषणा Index_Load_Tag_T		(Cache_T | Index_Load_Tag)

/*
 * R10000-specअगरic cacheops
 *
 * Cacheops 0x02, 0x06, 0x0a, 0x0c-0x0e, 0x16, 0x1a and 0x1e are unused.
 * Most of the _S cacheops are identical to the R4000SC _SD cacheops.
 */
#घोषणा Index_Writeback_Inv_S		(Cache_S | Index_Writeback_Inv)
#घोषणा Index_Load_Tag_S		(Cache_S | Index_Load_Tag)
#घोषणा Index_Store_Tag_S		(Cache_S | Index_Store_Tag)
#घोषणा Hit_Invalidate_S		(Cache_S | Hit_Invalidate)
#घोषणा Cache_Barrier			0x14
#घोषणा Hit_Writeback_Inv_S		(Cache_S | Hit_Writeback_Inv)
#घोषणा Index_Load_Data_I		(Cache_I | 0x18)
#घोषणा Index_Load_Data_D		(Cache_D | 0x18)
#घोषणा Index_Load_Data_S		(Cache_S | 0x18)
#घोषणा Index_Store_Data_I		(Cache_I | 0x1c)
#घोषणा Index_Store_Data_D		(Cache_D | 0x1c)
#घोषणा Index_Store_Data_S		(Cache_S | 0x1c)

/*
 * Loongson2-specअगरic cacheops
 */
#घोषणा Hit_Invalidate_I_Loongson2	(Cache_I | 0x00)

/*
 * Loongson3-specअगरic cacheops
 */
#घोषणा Index_Writeback_Inv_V		(Cache_V | Index_Writeback_Inv)

#पूर्ण_अगर	/* __ASM_CACHEOPS_H */
