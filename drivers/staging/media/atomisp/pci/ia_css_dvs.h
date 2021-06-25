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

#अगर_अघोषित __IA_CSS_DVS_H
#घोषणा __IA_CSS_DVS_H

/* @file
 * This file contains types क्रम DVS statistics
 */

#समावेश <type_support.h>
#समावेश "ia_css_types.h"
#समावेश "ia_css_err.h"
#समावेश "ia_css_stream_public.h"

क्रमागत dvs_statistics_type अणु
	DVS_STATISTICS,
	DVS2_STATISTICS,
	SKC_DVS_STATISTICS
पूर्ण;

/* Structure that holds DVS statistics in the ISP पूर्णांकernal
 * क्रमmat. Use ia_css_get_dvs_statistics() to translate
 * this to the क्रमmat used on the host (DVS engine).
 * */
काष्ठा ia_css_isp_dvs_statistics अणु
	ia_css_ptr hor_proj;
	ia_css_ptr ver_proj;
	u32   hor_size;
	u32   ver_size;
	u32   exp_id;   /** see ia_css_event_खुला.h क्रम more detail */
	ia_css_ptr data_ptr; /* base poपूर्णांकer containing all memory */
	u32   size;     /* size of allocated memory in data_ptr */
पूर्ण;

/* Structure that holds SKC DVS statistics in the ISP पूर्णांकernal
 * क्रमmat. Use ia_css_dvs_statistics_get() to translate this to
 * the क्रमmat used on the host.
 * */
काष्ठा ia_css_isp_skc_dvs_statistics;

#घोषणा SIZE_OF_IA_CSS_ISP_DVS_STATISTICS_STRUCT			\
	((3 * SIZE_OF_IA_CSS_PTR) +					\
	 (4 * माप(uपूर्णांक32_t)))

/* Map with host-side poपूर्णांकers to ISP-क्रमmat statistics.
 * These poपूर्णांकers can either be copies of ISP data or memory mapped
 * ISP poपूर्णांकers.
 * All of the data behind these poपूर्णांकers is allocatd contiguously, the
 * allocated poपूर्णांकer is stored in the data_ptr field. The other fields
 * poपूर्णांक पूर्णांकo this one block of data.
 */
काष्ठा ia_css_isp_dvs_statistics_map अणु
	व्योम    *data_ptr;
	s32 *hor_proj;
	s32 *ver_proj;
	u32 size;		 /* total size in bytes */
	u32 data_allocated; /* indicate whether data was allocated */
पूर्ण;

जोड़ ia_css_dvs_statistics_isp अणु
	काष्ठा ia_css_isp_dvs_statistics *p_dvs_statistics_isp;
	काष्ठा ia_css_isp_skc_dvs_statistics *p_skc_dvs_statistics_isp;
पूर्ण;

जोड़ ia_css_dvs_statistics_host अणु
	काष्ठा ia_css_dvs_statistics *p_dvs_statistics_host;
	काष्ठा ia_css_dvs2_statistics *p_dvs2_statistics_host;
	काष्ठा ia_css_skc_dvs_statistics *p_skc_dvs_statistics_host;
पूर्ण;

/* @brief Copy DVS statistics from an ISP buffer to a host buffer.
 * @param[in]	host_stats Host buffer
 * @param[in]	isp_stats ISP buffer
 * @वापस	error value अगर temporary memory cannot be allocated
 *
 * This may include a translation step as well depending
 * on the ISP version.
 * Always use this function, never copy the buffer directly.
 * Note that this function uses the mem_load function from the CSS
 * environment काष्ठा.
 * In certain environments this may be slow. In those हालs it is
 * advised to map the ISP memory पूर्णांकo a host-side poपूर्णांकer and use
 * the ia_css_translate_dvs_statistics() function instead.
 */
पूर्णांक
ia_css_get_dvs_statistics(काष्ठा ia_css_dvs_statistics *host_stats,
			  स्थिर काष्ठा ia_css_isp_dvs_statistics *isp_stats);

/* @brief Translate DVS statistics from ISP क्रमmat to host क्रमmat
 * @param[in]	host_stats Host buffer
 * @param[in]	isp_stats ISP buffer
 * @वापस	None
 *
 * This function translates the dvs statistics from the ISP-पूर्णांकernal
 * क्रमmat to the क्रमmat used by the DVS library on the CPU.
 * This function takes a host-side poपूर्णांकer as input. This can either
 * poपूर्णांक to a copy of the data or be a memory mapped poपूर्णांकer to the
 * ISP memory pages.
 */
व्योम
ia_css_translate_dvs_statistics(
    काष्ठा ia_css_dvs_statistics *host_stats,
    स्थिर काष्ठा ia_css_isp_dvs_statistics_map *isp_stats);

/* @brief Copy DVS 2.0 statistics from an ISP buffer to a host buffer.
 * @param[in]	host_stats Host buffer
 * @param[in]	isp_stats ISP buffer
 * @वापस	error value अगर temporary memory cannot be allocated
 *
 * This may include a translation step as well depending
 * on the ISP version.
 * Always use this function, never copy the buffer directly.
 * Note that this function uses the mem_load function from the CSS
 * environment काष्ठा.
 * In certain environments this may be slow. In those हालs it is
 * advised to map the ISP memory पूर्णांकo a host-side poपूर्णांकer and use
 * the ia_css_translate_dvs2_statistics() function instead.
 */
पूर्णांक
ia_css_get_dvs2_statistics(काष्ठा ia_css_dvs2_statistics *host_stats,
			   स्थिर काष्ठा ia_css_isp_dvs_statistics *isp_stats);

/* @brief Translate DVS2 statistics from ISP क्रमmat to host क्रमmat
 * @param[in]	host_stats Host buffer
 * @param[in]	isp_stats ISP buffer
 * @वापस		None
 *
 * This function translates the dvs2 statistics from the ISP-पूर्णांकernal
 * क्रमmat to the क्रमmat used by the DVS2 library on the CPU.
 * This function takes a host-side poपूर्णांकer as input. This can either
 * poपूर्णांक to a copy of the data or be a memory mapped poपूर्णांकer to the
 * ISP memory pages.
 */
व्योम
ia_css_translate_dvs2_statistics(
    काष्ठा ia_css_dvs2_statistics	   *host_stats,
    स्थिर काष्ठा ia_css_isp_dvs_statistics_map *isp_stats);

/* @brief Copy DVS statistics from an ISP buffer to a host buffer.
 * @param[in] type - DVS statistics type
 * @param[in] host_stats Host buffer
 * @param[in] isp_stats ISP buffer
 * @वापस None
 */
व्योम
ia_css_dvs_statistics_get(क्रमागत dvs_statistics_type type,
			  जोड़ ia_css_dvs_statistics_host  *host_stats,
			  स्थिर जोड़ ia_css_dvs_statistics_isp *isp_stats);

/* @brief Allocate the DVS statistics memory on the ISP
 * @param[in]	grid The grid.
 * @वापस	Poपूर्णांकer to the allocated DVS statistics buffer on the ISP
*/
काष्ठा ia_css_isp_dvs_statistics *
ia_css_isp_dvs_statistics_allocate(स्थिर काष्ठा ia_css_dvs_grid_info *grid);

/* @brief Free the DVS statistics memory on the ISP
 * @param[in]	me Poपूर्णांकer to the DVS statistics buffer on the ISP.
 * @वापस	None
*/
व्योम
ia_css_isp_dvs_statistics_मुक्त(काष्ठा ia_css_isp_dvs_statistics *me);

/* @brief Allocate the DVS 2.0 statistics memory
 * @param[in]	grid The grid.
 * @वापस	Poपूर्णांकer to the allocated DVS statistics buffer on the ISP
*/
काष्ठा ia_css_isp_dvs_statistics *
ia_css_isp_dvs2_statistics_allocate(स्थिर काष्ठा ia_css_dvs_grid_info *grid);

/* @brief Free the DVS 2.0 statistics memory
 * @param[in]	me Poपूर्णांकer to the DVS statistics buffer on the ISP.
 * @वापस	None
*/
व्योम
ia_css_isp_dvs2_statistics_मुक्त(काष्ठा ia_css_isp_dvs_statistics *me);

/* @brief Allocate the DVS statistics memory on the host
 * @param[in]	grid The grid.
 * @वापस	Poपूर्णांकer to the allocated DVS statistics buffer on the host
*/
काष्ठा ia_css_dvs_statistics *
ia_css_dvs_statistics_allocate(स्थिर काष्ठा ia_css_dvs_grid_info *grid);

/* @brief Free the DVS statistics memory on the host
 * @param[in]	me Poपूर्णांकer to the DVS statistics buffer on the host.
 * @वापस	None
*/
व्योम
ia_css_dvs_statistics_मुक्त(काष्ठा ia_css_dvs_statistics *me);

/* @brief Allocate the DVS coefficients memory
 * @param[in]	grid The grid.
 * @वापस	Poपूर्णांकer to the allocated DVS coefficients buffer
*/
काष्ठा ia_css_dvs_coefficients *
ia_css_dvs_coefficients_allocate(स्थिर काष्ठा ia_css_dvs_grid_info *grid);

/* @brief Free the DVS coefficients memory
 * @param[in]	me Poपूर्णांकer to the DVS coefficients buffer.
 * @वापस	None
 */
व्योम
ia_css_dvs_coefficients_मुक्त(काष्ठा ia_css_dvs_coefficients *me);

/* @brief Allocate the DVS 2.0 statistics memory on the host
 * @param[in]	grid The grid.
 * @वापस	Poपूर्णांकer to the allocated DVS 2.0 statistics buffer on the host
 */
काष्ठा ia_css_dvs2_statistics *
ia_css_dvs2_statistics_allocate(स्थिर काष्ठा ia_css_dvs_grid_info *grid);

/* @brief Free the DVS 2.0 statistics memory
 * @param[in]	me Poपूर्णांकer to the DVS 2.0 statistics buffer on the host.
 * @वापस	None
*/
व्योम
ia_css_dvs2_statistics_मुक्त(काष्ठा ia_css_dvs2_statistics *me);

/* @brief Allocate the DVS 2.0 coefficients memory
 * @param[in]	grid The grid.
 * @वापस	Poपूर्णांकer to the allocated DVS 2.0 coefficients buffer
*/
काष्ठा ia_css_dvs2_coefficients *
ia_css_dvs2_coefficients_allocate(स्थिर काष्ठा ia_css_dvs_grid_info *grid);

/* @brief Free the DVS 2.0 coefficients memory
 * @param[in]	me Poपूर्णांकer to the DVS 2.0 coefficients buffer.
 * @वापस	None
*/
व्योम
ia_css_dvs2_coefficients_मुक्त(काष्ठा ia_css_dvs2_coefficients *me);

/* @brief Allocate the DVS 2.0 6-axis config memory
 * @param[in]	stream The stream.
 * @वापस	Poपूर्णांकer to the allocated DVS 6axis configuration buffer
*/
काष्ठा ia_css_dvs_6axis_config *
ia_css_dvs2_6axis_config_allocate(स्थिर काष्ठा ia_css_stream *stream);

/* @brief Free the DVS 2.0 6-axis config memory
 * @param[in]	dvs_6axis_config Poपूर्णांकer to the DVS 6axis configuration buffer
 * @वापस	None
 */
व्योम
ia_css_dvs2_6axis_config_मुक्त(काष्ठा ia_css_dvs_6axis_config *dvs_6axis_config);

/* @brief Allocate a dvs statistics map काष्ठाure
 * @param[in]	isp_stats poपूर्णांकer to ISP dvs statistis काष्ठा
 * @param[in]	data_ptr  host-side poपूर्णांकer to ISP dvs statistics.
 * @वापस	Poपूर्णांकer to the allocated dvs statistics map
 *
 * This function allocates the ISP dvs statistics map काष्ठाure
 * and uses the data_ptr as base poपूर्णांकer to set the appropriate
 * poपूर्णांकers to all relevant subsets of the dvs statistics (dmem,
 * vmem, hmem).
 * If the data_ptr is शून्य, this function will allocate the host-side
 * memory. This inक्रमmation is stored in the काष्ठा and used in the
 * ia_css_isp_dvs_statistics_map_मुक्त() function to determine whether
 * the memory should be मुक्तd or not.
 * Note that this function करोes not allocate or map any ISP
 * memory.
*/
काष्ठा ia_css_isp_dvs_statistics_map *
ia_css_isp_dvs_statistics_map_allocate(
    स्थिर काष्ठा ia_css_isp_dvs_statistics *isp_stats,
    व्योम *data_ptr);

/* @brief Free the dvs statistics map
 * @param[in]	me Poपूर्णांकer to the dvs statistics map
 * @वापस	None
 *
 * This function मुक्तs the map काष्ठा. If the data_ptr inside it
 * was allocated inside ia_css_isp_dvs_statistics_map_allocate(), it
 * will be मुक्तd in this function. Otherwise it will not be मुक्तd.
 */
व्योम
ia_css_isp_dvs_statistics_map_मुक्त(काष्ठा ia_css_isp_dvs_statistics_map *me);

/* @brief Allocate memory क्रम the SKC DVS statistics on the ISP
 * @वापस		Poपूर्णांकer to the allocated ACC DVS statistics buffer on the ISP
*/
काष्ठा ia_css_isp_skc_dvs_statistics *ia_css_skc_dvs_statistics_allocate(व्योम);

#पूर्ण_अगर /*  __IA_CSS_DVS_H */
