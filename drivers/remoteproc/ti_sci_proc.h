<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Texas Instruments TI-SCI Processor Controller Helper Functions
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - https://www.ti.com/
 *	Suman Anna <s-anna@ti.com>
 */

#अगर_अघोषित REMOTEPROC_TI_SCI_PROC_H
#घोषणा REMOTEPROC_TI_SCI_PROC_H

#समावेश <linux/soc/ti/ti_sci_protocol.h>

/**
 * काष्ठा ti_sci_proc - काष्ठाure representing a processor control client
 * @sci: cached TI-SCI protocol handle
 * @ops: cached TI-SCI proc ops
 * @dev: cached client device poपूर्णांकer
 * @proc_id: processor id क्रम the consumer remoteproc device
 * @host_id: host id to pass the control over क्रम this consumer remoteproc
 *	     device
 */
काष्ठा ti_sci_proc अणु
	स्थिर काष्ठा ti_sci_handle *sci;
	स्थिर काष्ठा ti_sci_proc_ops *ops;
	काष्ठा device *dev;
	u8 proc_id;
	u8 host_id;
पूर्ण;

अटल अंतरभूत पूर्णांक ti_sci_proc_request(काष्ठा ti_sci_proc *tsp)
अणु
	पूर्णांक ret;

	ret = tsp->ops->request(tsp->sci, tsp->proc_id);
	अगर (ret)
		dev_err(tsp->dev, "ti-sci processor request failed: %d\n",
			ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ti_sci_proc_release(काष्ठा ti_sci_proc *tsp)
अणु
	पूर्णांक ret;

	ret = tsp->ops->release(tsp->sci, tsp->proc_id);
	अगर (ret)
		dev_err(tsp->dev, "ti-sci processor release failed: %d\n",
			ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ti_sci_proc_hanकरोver(काष्ठा ti_sci_proc *tsp)
अणु
	पूर्णांक ret;

	ret = tsp->ops->hanकरोver(tsp->sci, tsp->proc_id, tsp->host_id);
	अगर (ret)
		dev_err(tsp->dev, "ti-sci processor handover of %d to %d failed: %d\n",
			tsp->proc_id, tsp->host_id, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ti_sci_proc_set_config(काष्ठा ti_sci_proc *tsp,
					 u64 boot_vector,
					 u32 cfg_set, u32 cfg_clr)
अणु
	पूर्णांक ret;

	ret = tsp->ops->set_config(tsp->sci, tsp->proc_id, boot_vector,
				   cfg_set, cfg_clr);
	अगर (ret)
		dev_err(tsp->dev, "ti-sci processor set_config failed: %d\n",
			ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ti_sci_proc_set_control(काष्ठा ti_sci_proc *tsp,
					  u32 ctrl_set, u32 ctrl_clr)
अणु
	पूर्णांक ret;

	ret = tsp->ops->set_control(tsp->sci, tsp->proc_id, ctrl_set, ctrl_clr);
	अगर (ret)
		dev_err(tsp->dev, "ti-sci processor set_control failed: %d\n",
			ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ti_sci_proc_get_status(काष्ठा ti_sci_proc *tsp,
					 u64 *boot_vector, u32 *cfg_flags,
					 u32 *ctrl_flags, u32 *status_flags)
अणु
	पूर्णांक ret;

	ret = tsp->ops->get_status(tsp->sci, tsp->proc_id, boot_vector,
				   cfg_flags, ctrl_flags, status_flags);
	अगर (ret)
		dev_err(tsp->dev, "ti-sci processor get_status failed: %d\n",
			ret);
	वापस ret;
पूर्ण

#पूर्ण_अगर /* REMOTEPROC_TI_SCI_PROC_H */
