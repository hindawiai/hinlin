<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __IA_CSS_3A_H
#घोषणा __IA_CSS_3A_H

/* @file
 * This file contains types used क्रम 3A statistics
 */

#समावेश <type_support.h>
#समावेश "ia_css_types.h"
#समावेश "ia_css_err.h"
#समावेश "system_global.h"

क्रमागत ia_css_3a_tables अणु
	IA_CSS_S3A_TBL_HI,
	IA_CSS_S3A_TBL_LO,
	IA_CSS_RGBY_TBL,
	IA_CSS_NUM_3A_TABLES
पूर्ण;

/* Structure that holds 3A statistics in the ISP पूर्णांकernal
 * क्रमmat. Use ia_css_get_3a_statistics() to translate
 * this to the क्रमmat used on the host (3A library).
 * */
काष्ठा ia_css_isp_3a_statistics अणु
	जोड़ अणु
		काष्ठा अणु
			ia_css_ptr s3a_tbl;
		पूर्ण dmem;
		काष्ठा अणु
			ia_css_ptr s3a_tbl_hi;
			ia_css_ptr s3a_tbl_lo;
		पूर्ण vmem;
	पूर्ण data;
	काष्ठा अणु
		ia_css_ptr rgby_tbl;
	पूर्ण data_hmem;
	u32 exp_id;     /** exposure id, to match statistics to a frame,
				  see ia_css_event_खुला.h क्रम more detail. */
	u32 isp_config_id;/** Unique ID to track which config was actually applied to a particular frame */
	ia_css_ptr data_ptr; /** poपूर्णांकer to base of all data */
	u32   size;     /** total size of all data */
	u32   dmem_size;
	u32   vmem_size; /** both lo and hi have this size */
	u32   hmem_size;
पूर्ण;

#घोषणा SIZE_OF_DMEM_STRUCT						\
	(SIZE_OF_IA_CSS_PTR)

#घोषणा SIZE_OF_VMEM_STRUCT						\
	(2 * SIZE_OF_IA_CSS_PTR)

#घोषणा SIZE_OF_DATA_UNION						\
	(MAX(SIZE_OF_DMEM_STRUCT, SIZE_OF_VMEM_STRUCT))

#घोषणा SIZE_OF_DATA_HMEM_STRUCT					\
	(SIZE_OF_IA_CSS_PTR)

#घोषणा SIZE_OF_IA_CSS_ISP_3A_STATISTICS_STRUCT				\
	(SIZE_OF_DATA_UNION +						\
	 SIZE_OF_DATA_HMEM_STRUCT +					\
	 माप(uपूर्णांक32_t) +						\
	 माप(uपूर्णांक32_t) +						\
	 SIZE_OF_IA_CSS_PTR +						\
	 4 * माप(uपूर्णांक32_t))

/* Map with host-side poपूर्णांकers to ISP-क्रमmat statistics.
 * These poपूर्णांकers can either be copies of ISP data or memory mapped
 * ISP poपूर्णांकers.
 * All of the data behind these poपूर्णांकers is allocated contiguously, the
 * allocated poपूर्णांकer is stored in the data_ptr field. The other fields
 * poपूर्णांक पूर्णांकo this one block of data.
 */
काष्ठा ia_css_isp_3a_statistics_map अणु
	व्योम                    *data_ptr; /** Poपूर्णांकer to start of memory */
	काष्ठा ia_css_3a_output *dmem_stats;
	u16                *vmem_stats_hi;
	u16                *vmem_stats_lo;
	काष्ठा ia_css_bh_table  *hmem_stats;
	u32                 size; /** total size in bytes of data_ptr */
	u32                 data_allocated; /** indicate whether data_ptr
						    was allocated or not. */
पूर्ण;

/* @brief Copy and translate 3A statistics from an ISP buffer to a host buffer
 * @param[out]	host_stats Host buffer.
 * @param[in]	isp_stats ISP buffer.
 * @वापस	error value अगर temporary memory cannot be allocated
 *
 * This copies 3a statistics from an ISP poपूर्णांकer to a host poपूर्णांकer and then
 * translates some of the statistics, details depend on which ISP binary is
 * used.
 * Always use this function, never copy the buffer directly.
 */
पूर्णांक
ia_css_get_3a_statistics(काष्ठा ia_css_3a_statistics           *host_stats,
			 स्थिर काष्ठा ia_css_isp_3a_statistics *isp_stats);

/* @brief Translate 3A statistics from ISP क्रमmat to host क्रमmat.
 * @param[out]	host_stats host-क्रमmat statistics
 * @param[in]	isp_stats  ISP-क्रमmat statistics
 * @वापस	None
 *
 * This function translates statistics from the पूर्णांकernal ISP-क्रमmat to
 * the host-क्रमmat. This function करोes not include an additional copy
 * step.
 * */
व्योम
ia_css_translate_3a_statistics(
    काष्ठा ia_css_3a_statistics               *host_stats,
    स्थिर काष्ठा ia_css_isp_3a_statistics_map *isp_stats);

/* Convenience functions क्रम alloc/मुक्त of certain datatypes */

/* @brief Allocate memory क्रम the 3a statistics on the ISP
 * @param[in]	grid The grid.
 * @वापस		Poपूर्णांकer to the allocated 3a statistics buffer on the ISP
*/
काष्ठा ia_css_isp_3a_statistics *
ia_css_isp_3a_statistics_allocate(स्थिर काष्ठा ia_css_3a_grid_info *grid);

/* @brief Free the 3a statistics memory on the isp
 * @param[in]	me Poपूर्णांकer to the 3a statistics buffer on the ISP.
 * @वापस		None
*/
व्योम
ia_css_isp_3a_statistics_मुक्त(काष्ठा ia_css_isp_3a_statistics *me);

/* @brief Allocate memory क्रम the 3a statistics on the host
 * @param[in]	grid The grid.
 * @वापस		Poपूर्णांकer to the allocated 3a statistics buffer on the host
*/
काष्ठा ia_css_3a_statistics *
ia_css_3a_statistics_allocate(स्थिर काष्ठा ia_css_3a_grid_info *grid);

/* @brief Free the 3a statistics memory on the host
 * @param[in]	me Poपूर्णांकer to the 3a statistics buffer on the host.
 * @वापस		None
 */
व्योम
ia_css_3a_statistics_मुक्त(काष्ठा ia_css_3a_statistics *me);

/* @brief Allocate a 3a statistics map काष्ठाure
 * @param[in]	isp_stats poपूर्णांकer to ISP 3a statistis काष्ठा
 * @param[in]	data_ptr  host-side poपूर्णांकer to ISP 3a statistics.
 * @वापस		Poपूर्णांकer to the allocated 3a statistics map
 *
 * This function allocates the ISP 3a statistics map काष्ठाure
 * and uses the data_ptr as base poपूर्णांकer to set the appropriate
 * poपूर्णांकers to all relevant subsets of the 3a statistics (dmem,
 * vmem, hmem).
 * If the data_ptr is शून्य, this function will allocate the host-side
 * memory. This inक्रमmation is stored in the काष्ठा and used in the
 * ia_css_isp_3a_statistics_map_मुक्त() function to determine whether
 * the memory should be मुक्तd or not.
 * Note that this function करोes not allocate or map any ISP
 * memory.
*/
काष्ठा ia_css_isp_3a_statistics_map *
ia_css_isp_3a_statistics_map_allocate(
    स्थिर काष्ठा ia_css_isp_3a_statistics *isp_stats,
    व्योम *data_ptr);

/* @brief Free the 3a statistics map
 * @param[in]	me Poपूर्णांकer to the 3a statistics map
 * @वापस		None
 *
 * This function मुक्तs the map काष्ठा. If the data_ptr inside it
 * was allocated inside ia_css_isp_3a_statistics_map_allocate(), it
 * will be मुक्तd in this function. Otherwise it will not be मुक्तd.
 */
व्योम
ia_css_isp_3a_statistics_map_मुक्त(काष्ठा ia_css_isp_3a_statistics_map *me);

#पूर्ण_अगर /* __IA_CSS_3A_H */
