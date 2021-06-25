<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Yannick Fertre <yannick.fertre@st.com>
 *          Hugues Fruchet <hugues.fruchet@st.com>
 */

#अगर_अघोषित HVA_HW_H
#घोषणा HVA_HW_H

#समावेश "hva-mem.h"

/* HVA Versions */
#घोषणा HVA_VERSION_UNKNOWN    0x000
#घोषणा HVA_VERSION_V400       0x400

/* HVA command types */
क्रमागत hva_hw_cmd_type अणु
	/* RESERVED = 0x00 */
	/* RESERVED = 0x01 */
	H264_ENC = 0x02,
	/* RESERVED = 0x03 */
	/* RESERVED = 0x04 */
	/* RESERVED = 0x05 */
	/* RESERVED = 0x06 */
	/* RESERVED = 0x07 */
	REMOVE_CLIENT = 0x08,
	FREEZE_CLIENT = 0x09,
	START_CLIENT = 0x0A,
	FREEZE_ALL = 0x0B,
	START_ALL = 0x0C,
	REMOVE_ALL = 0x0D
पूर्ण;

पूर्णांक hva_hw_probe(काष्ठा platक्रमm_device *pdev, काष्ठा hva_dev *hva);
व्योम hva_hw_हटाओ(काष्ठा hva_dev *hva);
पूर्णांक hva_hw_runसमय_suspend(काष्ठा device *dev);
पूर्णांक hva_hw_runसमय_resume(काष्ठा device *dev);
पूर्णांक hva_hw_execute_task(काष्ठा hva_ctx *ctx, क्रमागत hva_hw_cmd_type cmd,
			काष्ठा hva_buffer *task);
#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
व्योम hva_hw_dump_regs(काष्ठा hva_dev *hva, काष्ठा seq_file *s);
#पूर्ण_अगर

#पूर्ण_अगर /* HVA_HW_H */
