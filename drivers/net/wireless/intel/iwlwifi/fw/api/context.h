<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_context_h__
#घोषणा __iwl_fw_api_context_h__

/**
 * क्रमागत iwl_ctxt_id_and_color - ID and color fields in context dword
 * @FW_CTXT_ID_POS: position of the ID
 * @FW_CTXT_ID_MSK: mask of the ID
 * @FW_CTXT_COLOR_POS: position of the color
 * @FW_CTXT_COLOR_MSK: mask of the color
 * @FW_CTXT_INVALID: value used to indicate unused/invalid
 */
क्रमागत iwl_ctxt_id_and_color अणु
	FW_CTXT_ID_POS		= 0,
	FW_CTXT_ID_MSK		= 0xff << FW_CTXT_ID_POS,
	FW_CTXT_COLOR_POS	= 8,
	FW_CTXT_COLOR_MSK	= 0xff << FW_CTXT_COLOR_POS,
	FW_CTXT_INVALID		= 0xffffffff,
पूर्ण;

#घोषणा FW_CMD_ID_AND_COLOR(_id, _color) (((_id) << FW_CTXT_ID_POS) |\
					  ((_color) << FW_CTXT_COLOR_POS))

/* Possible actions on PHYs, MACs and Bindings */
क्रमागत iwl_ctxt_action अणु
	FW_CTXT_ACTION_STUB = 0,
	FW_CTXT_ACTION_ADD,
	FW_CTXT_ACTION_MODIFY,
	FW_CTXT_ACTION_REMOVE,
	FW_CTXT_ACTION_NUM
पूर्ण; /* COMMON_CONTEXT_ACTION_API_E_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_context_h__ */
