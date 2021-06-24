<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __INCLUDE_SOUND_SOF_XTENSA_H__
#घोषणा __INCLUDE_SOUND_SOF_XTENSA_H__

#समावेश <sound/sof/header.h>

/*
 * Architecture specअगरic debug
 */

/* Xtensa Firmware Oops data */
काष्ठा sof_ipc_dsp_oops_xtensa अणु
	काष्ठा sof_ipc_dsp_oops_arch_hdr arch_hdr;
	काष्ठा sof_ipc_dsp_oops_plat_hdr plat_hdr;
	uपूर्णांक32_t exccause;
	uपूर्णांक32_t excvaddr;
	uपूर्णांक32_t ps;
	uपूर्णांक32_t epc1;
	uपूर्णांक32_t epc2;
	uपूर्णांक32_t epc3;
	uपूर्णांक32_t epc4;
	uपूर्णांक32_t epc5;
	uपूर्णांक32_t epc6;
	uपूर्णांक32_t epc7;
	uपूर्णांक32_t eps2;
	uपूर्णांक32_t eps3;
	uपूर्णांक32_t eps4;
	uपूर्णांक32_t eps5;
	uपूर्णांक32_t eps6;
	uपूर्णांक32_t eps7;
	uपूर्णांक32_t depc;
	uपूर्णांक32_t पूर्णांकenable;
	uपूर्णांक32_t पूर्णांकerrupt;
	uपूर्णांक32_t sar;
	uपूर्णांक32_t debugcause;
	uपूर्णांक32_t winकरोwbase;
	uपूर्णांक32_t winकरोwstart;
	uपूर्णांक32_t excsave1;
	uपूर्णांक32_t ar[];
पूर्ण  __packed;

#पूर्ण_अगर
