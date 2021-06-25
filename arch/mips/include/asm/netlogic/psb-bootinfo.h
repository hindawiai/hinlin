<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _ASM_NETLOGIC_BOOTINFO_H
#घोषणा _ASM_NETLOGIC_BOOTINFO_H

काष्ठा psb_info अणु
	uपूर्णांक64_t boot_level;
	uपूर्णांक64_t io_base;
	uपूर्णांक64_t output_device;
	uपूर्णांक64_t uart_prपूर्णांक;
	uपूर्णांक64_t led_output;
	uपूर्णांक64_t init;
	uपूर्णांक64_t निकास;
	uपूर्णांक64_t warm_reset;
	uपूर्णांक64_t wakeup;
	uपूर्णांक64_t online_cpu_map;
	uपूर्णांक64_t master_reentry_sp;
	uपूर्णांक64_t master_reentry_gp;
	uपूर्णांक64_t master_reentry_fn;
	uपूर्णांक64_t slave_reentry_fn;
	uपूर्णांक64_t magic_dword;
	uपूर्णांक64_t uart_अक्षर_दो;
	uपूर्णांक64_t size;
	uपूर्णांक64_t uart_अक्षर_लो;
	uपूर्णांक64_t nmi_handler;
	uपूर्णांक64_t psb_version;
	uपूर्णांक64_t mac_addr;
	uपूर्णांक64_t cpu_frequency;
	uपूर्णांक64_t board_version;
	uपूर्णांक64_t दो_स्मृति;
	uपूर्णांक64_t मुक्त;
	uपूर्णांक64_t global_shmem_addr;
	uपूर्णांक64_t global_shmem_size;
	uपूर्णांक64_t psb_os_cpu_map;
	uपूर्णांक64_t userapp_cpu_map;
	uपूर्णांक64_t wakeup_os;
	uपूर्णांक64_t psb_mem_map;
	uपूर्णांक64_t board_major_version;
	uपूर्णांक64_t board_minor_version;
	uपूर्णांक64_t board_manf_revision;
	uपूर्णांक64_t board_serial_number;
	uपूर्णांक64_t psb_physaddr_map;
	uपूर्णांक64_t xlr_loaderip_config;
	uपूर्णांक64_t bldr_envp;
	uपूर्णांक64_t avail_mem_map;
पूर्ण;

/* This is what netlboot passes and linux boot_mem_map is subtly dअगरferent */
#घोषणा NLM_BOOT_MEM_MAP_MAX	32
काष्ठा nlm_boot_mem_map अणु
	पूर्णांक nr_map;
	काष्ठा nlm_boot_mem_map_entry अणु
		uपूर्णांक64_t addr;		/* start of memory segment */
		uपूर्णांक64_t size;		/* size of memory segment */
		uपूर्णांक32_t type;		/* type of memory segment */
	पूर्ण map[NLM_BOOT_MEM_MAP_MAX];
पूर्ण;
#घोषणा NLM_BOOT_MEM_RAM	1

/* Poपूर्णांकer to saved boot loader info */
बाह्य काष्ठा psb_info nlm_prom_info;

#पूर्ण_अगर
