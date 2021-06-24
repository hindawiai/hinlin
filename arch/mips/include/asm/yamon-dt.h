<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#अगर_अघोषित __MIPS_ASM_YAMON_DT_H__
#घोषणा __MIPS_ASM_YAMON_DT_H__

#समावेश <linux/types.h>

/**
 * काष्ठा yamon_mem_region - Represents a contiguous range of physical RAM.
 * @start:	Start physical address.
 * @size:	Maximum size of region.
 * @discard:	Length of additional memory to discard after the region.
 */
काष्ठा yamon_mem_region अणु
	phys_addr_t	start;
	phys_addr_t	size;
	phys_addr_t	discard;
पूर्ण;

/**
 * yamon_dt_append_cmdline() - Append YAMON-provided command line to /chosen
 * @fdt: the FDT blob
 *
 * Write the YAMON-provided command line to the bootargs property of the
 * /chosen node in @fdt.
 *
 * Return: 0 on success, अन्यथा -त्रुटि_सं
 */
बाह्य __init पूर्णांक yamon_dt_append_cmdline(व्योम *fdt);

/**
 * yamon_dt_append_memory() - Append YAMON-provided memory info to /memory
 * @fdt:	the FDT blob
 * @regions:	zero size terminated array of physical memory regions
 *
 * Generate a /memory node in @fdt based upon memory size inक्रमmation provided
 * by YAMON in its environment and the @regions array.
 *
 * Return: 0 on success, अन्यथा -त्रुटि_सं
 */
बाह्य __init पूर्णांक yamon_dt_append_memory(व्योम *fdt,
					स्थिर काष्ठा yamon_mem_region *regions);

/**
 * yamon_dt_serial_config() - Append YAMON-provided serial config to /chosen
 * @fdt: the FDT blob
 *
 * Generate a मानक_निकास-path property in the /chosen node of @fdt, based upon
 * inक्रमmation provided in the YAMON environment about the UART configuration
 * of the प्रणाली.
 *
 * Return: 0 on success, अन्यथा -त्रुटि_सं
 */
बाह्य __init पूर्णांक yamon_dt_serial_config(व्योम *fdt);

#पूर्ण_अगर /* __MIPS_ASM_YAMON_DT_H__ */
