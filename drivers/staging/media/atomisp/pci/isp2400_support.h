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

#अगर_अघोषित _isp2400_support_h
#घोषणा _isp2400_support_h

#अगर_अघोषित ISP2400_VECTOR_TYPES
/* This प्रकार is to be able to include hive header files
   in the host code which is useful in crun */
प्रकार अक्षर *पंचांगemvectors, *पंचांगemvectoru, *tvector;
#पूर्ण_अगर

#घोषणा hrt_isp_vamem1_store_16(cell, addr, val) hrt_mem_store_16(cell, HRT_PROC_TYPE_PROP(cell, _simd_vamem1), addr, val)
#घोषणा hrt_isp_vamem2_store_16(cell, addr, val) hrt_mem_store_16(cell, HRT_PROC_TYPE_PROP(cell, _simd_vamem2), addr, val)

#घोषणा hrt_isp_dmem(cell) HRT_PROC_TYPE_PROP(cell, _base_dmem)
#घोषणा hrt_isp_vmem(cell) HRT_PROC_TYPE_PROP(cell, _simd_vmem)

#घोषणा hrt_isp_dmem_master_port_address(cell) hrt_mem_master_port_address(cell, hrt_isp_dmem(cell))
#घोषणा hrt_isp_vmem_master_port_address(cell) hrt_mem_master_port_address(cell, hrt_isp_vmem(cell))

#अगर ISP_HAS_HIST
#घोषणा hrt_isp_hist(cell) HRT_PROC_TYPE_PROP(cell, _simd_histogram)
#घोषणा hrt_isp_hist_master_port_address(cell) hrt_mem_master_port_address(cell, hrt_isp_hist(cell))
#पूर्ण_अगर

#पूर्ण_अगर /* _isp2400_support_h */
