<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "hinic_common.h"

/**
 * hinic_cpu_to_be32 - convert data to big endian 32 bit क्रमmat
 * @data: the data to convert
 * @len: length of data to convert
 **/
व्योम hinic_cpu_to_be32(व्योम *data, पूर्णांक len)
अणु
	u32 *mem = data;
	पूर्णांक i;

	len = len / माप(u32);

	क्रम (i = 0; i < len; i++) अणु
		*mem = cpu_to_be32(*mem);
		mem++;
	पूर्ण
पूर्ण

/**
 * hinic_be32_to_cpu - convert data from big endian 32 bit क्रमmat
 * @data: the data to convert
 * @len: length of data to convert
 **/
व्योम hinic_be32_to_cpu(व्योम *data, पूर्णांक len)
अणु
	u32 *mem = data;
	पूर्णांक i;

	len = len / माप(u32);

	क्रम (i = 0; i < len; i++) अणु
		*mem = be32_to_cpu(*mem);
		mem++;
	पूर्ण
पूर्ण

/**
 * hinic_set_sge - set dma area in scatter gather entry
 * @sge: scatter gather entry
 * @addr: dma address
 * @len: length of relevant data in the dma address
 **/
व्योम hinic_set_sge(काष्ठा hinic_sge *sge, dma_addr_t addr, पूर्णांक len)
अणु
	sge->hi_addr = upper_32_bits(addr);
	sge->lo_addr = lower_32_bits(addr);
	sge->len  = len;
पूर्ण

/**
 * hinic_sge_to_dma - get dma address from scatter gather entry
 * @sge: scatter gather entry
 *
 * Return dma address of sg entry
 **/
dma_addr_t hinic_sge_to_dma(काष्ठा hinic_sge *sge)
अणु
	वापस (dma_addr_t)((((u64)sge->hi_addr) << 32) | sge->lo_addr);
पूर्ण
