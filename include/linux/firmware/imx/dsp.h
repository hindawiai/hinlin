<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright 2019 NXP
 *
 * Header file क्रम the DSP IPC implementation
 */

#अगर_अघोषित _IMX_DSP_IPC_H
#घोषणा _IMX_DSP_IPC_H

#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/mailbox_client.h>

#घोषणा DSP_MU_CHAN_NUM		4

काष्ठा imx_dsp_chan अणु
	काष्ठा imx_dsp_ipc *ipc;
	काष्ठा mbox_client cl;
	काष्ठा mbox_chan *ch;
	अक्षर *name;
	पूर्णांक idx;
पूर्ण;

काष्ठा imx_dsp_ops अणु
	व्योम (*handle_reply)(काष्ठा imx_dsp_ipc *ipc);
	व्योम (*handle_request)(काष्ठा imx_dsp_ipc *ipc);
पूर्ण;

काष्ठा imx_dsp_ipc अणु
	/* Host <-> DSP communication uses 2 txdb and 2 rxdb channels */
	काष्ठा imx_dsp_chan chans[DSP_MU_CHAN_NUM];
	काष्ठा device *dev;
	काष्ठा imx_dsp_ops *ops;
	व्योम *निजी_data;
पूर्ण;

अटल अंतरभूत व्योम imx_dsp_set_data(काष्ठा imx_dsp_ipc *ipc, व्योम *data)
अणु
	अगर (!ipc)
		वापस;

	ipc->निजी_data = data;
पूर्ण

अटल अंतरभूत व्योम *imx_dsp_get_data(काष्ठा imx_dsp_ipc *ipc)
अणु
	अगर (!ipc)
		वापस शून्य;

	वापस ipc->निजी_data;
पूर्ण

#अगर IS_ENABLED(CONFIG_IMX_DSP)

पूर्णांक imx_dsp_ring_करोorbell(काष्ठा imx_dsp_ipc *dsp, अचिन्हित पूर्णांक chan_idx);

काष्ठा mbox_chan *imx_dsp_request_channel(काष्ठा imx_dsp_ipc *ipc, पूर्णांक idx);
व्योम imx_dsp_मुक्त_channel(काष्ठा imx_dsp_ipc *ipc, पूर्णांक idx);

#अन्यथा

अटल अंतरभूत पूर्णांक imx_dsp_ring_करोorbell(काष्ठा imx_dsp_ipc *ipc,
					अचिन्हित पूर्णांक chan_idx)
अणु
	वापस -ENOTSUPP;
पूर्ण

काष्ठा mbox_chan *imx_dsp_request_channel(काष्ठा imx_dsp_ipc *ipc, पूर्णांक idx)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

व्योम imx_dsp_मुक्त_channel(काष्ठा imx_dsp_ipc *ipc, पूर्णांक idx) अणु पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर /* _IMX_DSP_IPC_H */
