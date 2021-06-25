<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-ctrls.h - control support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _VIVID_CTRLS_H_
#घोषणा _VIVID_CTRLS_H_

क्रमागत vivid_hw_seek_modes अणु
	VIVID_HW_SEEK_BOUNDED,
	VIVID_HW_SEEK_WRAP,
	VIVID_HW_SEEK_BOTH,
पूर्ण;

पूर्णांक vivid_create_controls(काष्ठा vivid_dev *dev, bool show_ccs_cap,
		bool show_ccs_out, bool no_error_inj,
		bool has_sdtv, bool has_hdmi);
व्योम vivid_मुक्त_controls(काष्ठा vivid_dev *dev);

#पूर्ण_अगर
