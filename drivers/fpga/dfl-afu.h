<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Header file क्रम FPGA Accelerated Function Unit (AFU) Driver
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *     Wu Hao <hao.wu@पूर्णांकel.com>
 *     Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 *     Joseph Grecco <joe.grecco@पूर्णांकel.com>
 *     Enno Luebbers <enno.luebbers@पूर्णांकel.com>
 *     Tim Whisonant <tim.whisonant@पूर्णांकel.com>
 *     Ananda Ravuri <ananda.ravuri@पूर्णांकel.com>
 *     Henry Mitchel <henry.mitchel@पूर्णांकel.com>
 */

#अगर_अघोषित __DFL_AFU_H
#घोषणा __DFL_AFU_H

#समावेश <linux/mm.h>

#समावेश "dfl.h"

/**
 * काष्ठा dfl_afu_mmio_region - afu mmio region data काष्ठाure
 *
 * @index: region index.
 * @flags: region flags (access permission).
 * @size: region size.
 * @offset: region offset from start of the device fd.
 * @phys: region's physical address.
 * @node: node to add to afu feature dev's region list.
 */
काष्ठा dfl_afu_mmio_region अणु
	u32 index;
	u32 flags;
	u64 size;
	u64 offset;
	u64 phys;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा fpga_afu_dma_region - afu DMA region data काष्ठाure
 *
 * @user_addr: region userspace भव address.
 * @length: region length.
 * @iova: region IO भव address.
 * @pages: ptr to pages of this region.
 * @node: rb tree node.
 * @in_use: flag to indicate अगर this region is in_use.
 */
काष्ठा dfl_afu_dma_region अणु
	u64 user_addr;
	u64 length;
	u64 iova;
	काष्ठा page **pages;
	काष्ठा rb_node node;
	bool in_use;
पूर्ण;

/**
 * काष्ठा dfl_afu - afu device data काष्ठाure
 *
 * @region_cur_offset: current region offset from start to the device fd.
 * @num_regions: num of mmio regions.
 * @regions: the mmio region linked list of this afu feature device.
 * @dma_regions: root of dma regions rb tree.
 * @num_umsgs: num of umsgs.
 * @pdata: afu platक्रमm device's pdata.
 */
काष्ठा dfl_afu अणु
	u64 region_cur_offset;
	पूर्णांक num_regions;
	u8 num_umsgs;
	काष्ठा list_head regions;
	काष्ठा rb_root dma_regions;

	काष्ठा dfl_feature_platक्रमm_data *pdata;
पूर्ण;

/* hold pdata->lock when call __afu_port_enable/disable */
पूर्णांक __afu_port_enable(काष्ठा platक्रमm_device *pdev);
पूर्णांक __afu_port_disable(काष्ठा platक्रमm_device *pdev);

व्योम afu_mmio_region_init(काष्ठा dfl_feature_platक्रमm_data *pdata);
पूर्णांक afu_mmio_region_add(काष्ठा dfl_feature_platक्रमm_data *pdata,
			u32 region_index, u64 region_size, u64 phys, u32 flags);
व्योम afu_mmio_region_destroy(काष्ठा dfl_feature_platक्रमm_data *pdata);
पूर्णांक afu_mmio_region_get_by_index(काष्ठा dfl_feature_platक्रमm_data *pdata,
				 u32 region_index,
				 काष्ठा dfl_afu_mmio_region *pregion);
पूर्णांक afu_mmio_region_get_by_offset(काष्ठा dfl_feature_platक्रमm_data *pdata,
				  u64 offset, u64 size,
				  काष्ठा dfl_afu_mmio_region *pregion);
व्योम afu_dma_region_init(काष्ठा dfl_feature_platक्रमm_data *pdata);
व्योम afu_dma_region_destroy(काष्ठा dfl_feature_platक्रमm_data *pdata);
पूर्णांक afu_dma_map_region(काष्ठा dfl_feature_platक्रमm_data *pdata,
		       u64 user_addr, u64 length, u64 *iova);
पूर्णांक afu_dma_unmap_region(काष्ठा dfl_feature_platक्रमm_data *pdata, u64 iova);
काष्ठा dfl_afu_dma_region *
afu_dma_region_find(काष्ठा dfl_feature_platक्रमm_data *pdata,
		    u64 iova, u64 size);

बाह्य स्थिर काष्ठा dfl_feature_ops port_err_ops;
बाह्य स्थिर काष्ठा dfl_feature_id port_err_id_table[];
बाह्य स्थिर काष्ठा attribute_group port_err_group;

#पूर्ण_अगर /* __DFL_AFU_H */
