<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Ultravisor API.
 *
 * Copyright 2019, IBM Corporation.
 *
 */
#अगर_अघोषित _ASM_POWERPC_ULTRAVISOR_API_H
#घोषणा _ASM_POWERPC_ULTRAVISOR_API_H

#समावेश <यंत्र/hvcall.h>

/* Return codes */
#घोषणा U_BUSY			H_BUSY
#घोषणा U_FUNCTION		H_FUNCTION
#घोषणा U_NOT_AVAILABLE		H_NOT_AVAILABLE
#घोषणा U_P2			H_P2
#घोषणा U_P3			H_P3
#घोषणा U_P4			H_P4
#घोषणा U_P5			H_P5
#घोषणा U_PARAMETER		H_PARAMETER
#घोषणा U_PERMISSION		H_PERMISSION
#घोषणा U_SUCCESS		H_SUCCESS

/* opcodes */
#घोषणा UV_WRITE_PATE			0xF104
#घोषणा UV_RETURN			0xF11C
#घोषणा UV_ESM				0xF110
#घोषणा UV_REGISTER_MEM_SLOT		0xF120
#घोषणा UV_UNREGISTER_MEM_SLOT		0xF124
#घोषणा UV_PAGE_IN			0xF128
#घोषणा UV_PAGE_OUT			0xF12C
#घोषणा UV_SHARE_PAGE			0xF130
#घोषणा UV_UNSHARE_PAGE			0xF134
#घोषणा UV_UNSHARE_ALL_PAGES		0xF140
#घोषणा UV_PAGE_INVAL			0xF138
#घोषणा UV_SVM_TERMINATE		0xF13C

#पूर्ण_अगर /* _ASM_POWERPC_ULTRAVISOR_API_H */
