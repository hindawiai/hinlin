<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c)  2009-2013 QLogic Corporation
 */

#अगर_अघोषित __QLCNIC_DCBX_H
#घोषणा __QLCNIC_DCBX_H

#घोषणा QLCNIC_DCB_STATE	0
#घोषणा QLCNIC_DCB_AEN_MODE	1

#अगर_घोषित CONFIG_QLCNIC_DCB
पूर्णांक qlcnic_रेजिस्टर_dcb(काष्ठा qlcnic_adapter *);
#अन्यथा
अटल अंतरभूत पूर्णांक qlcnic_रेजिस्टर_dcb(काष्ठा qlcnic_adapter *adapter)
अणु वापस 0; पूर्ण
#पूर्ण_अगर

काष्ठा qlcnic_dcb;

काष्ठा qlcnic_dcb_ops अणु
	पूर्णांक (*query_hw_capability) (काष्ठा qlcnic_dcb *, अक्षर *);
	पूर्णांक (*get_hw_capability) (काष्ठा qlcnic_dcb *);
	पूर्णांक (*query_cee_param) (काष्ठा qlcnic_dcb *, अक्षर *, u8);
	व्योम (*init_dcbnl_ops) (काष्ठा qlcnic_dcb *);
	व्योम (*aen_handler) (काष्ठा qlcnic_dcb *, व्योम *);
	पूर्णांक (*get_cee_cfg) (काष्ठा qlcnic_dcb *);
	व्योम (*get_info) (काष्ठा qlcnic_dcb *);
	पूर्णांक (*attach) (काष्ठा qlcnic_dcb *);
	व्योम (*मुक्त) (काष्ठा qlcnic_dcb *);
पूर्ण;

काष्ठा qlcnic_dcb अणु
	काष्ठा qlcnic_dcb_mbx_params	*param;
	काष्ठा qlcnic_adapter		*adapter;
	काष्ठा delayed_work		aen_work;
	काष्ठा workqueue_काष्ठा		*wq;
	स्थिर काष्ठा qlcnic_dcb_ops	*ops;
	काष्ठा qlcnic_dcb_cfg		*cfg;
	अचिन्हित दीर्घ			state;
पूर्ण;

अटल अंतरभूत व्योम qlcnic_clear_dcb_ops(काष्ठा qlcnic_dcb *dcb)
अणु
	kमुक्त(dcb);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_dcb_get_hw_capability(काष्ठा qlcnic_dcb *dcb)
अणु
	अगर (dcb && dcb->ops->get_hw_capability)
		वापस dcb->ops->get_hw_capability(dcb);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qlcnic_dcb_मुक्त(काष्ठा qlcnic_dcb *dcb)
अणु
	अगर (dcb && dcb->ops->मुक्त)
		dcb->ops->मुक्त(dcb);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_dcb_attach(काष्ठा qlcnic_dcb *dcb)
अणु
	अगर (dcb && dcb->ops->attach)
		वापस dcb->ops->attach(dcb);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
qlcnic_dcb_query_hw_capability(काष्ठा qlcnic_dcb *dcb, अक्षर *buf)
अणु
	अगर (dcb && dcb->ops->query_hw_capability)
		वापस dcb->ops->query_hw_capability(dcb, buf);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qlcnic_dcb_get_info(काष्ठा qlcnic_dcb *dcb)
अणु
	अगर (dcb && dcb->ops->get_info)
		dcb->ops->get_info(dcb);
पूर्ण

अटल अंतरभूत पूर्णांक
qlcnic_dcb_query_cee_param(काष्ठा qlcnic_dcb *dcb, अक्षर *buf, u8 type)
अणु
	अगर (dcb && dcb->ops->query_cee_param)
		वापस dcb->ops->query_cee_param(dcb, buf, type);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_dcb_get_cee_cfg(काष्ठा qlcnic_dcb *dcb)
अणु
	अगर (dcb && dcb->ops->get_cee_cfg)
		वापस dcb->ops->get_cee_cfg(dcb);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qlcnic_dcb_aen_handler(काष्ठा qlcnic_dcb *dcb, व्योम *msg)
अणु
	अगर (dcb && dcb->ops->aen_handler)
		dcb->ops->aen_handler(dcb, msg);
पूर्ण

अटल अंतरभूत व्योम qlcnic_dcb_init_dcbnl_ops(काष्ठा qlcnic_dcb *dcb)
अणु
	अगर (dcb && dcb->ops->init_dcbnl_ops)
		dcb->ops->init_dcbnl_ops(dcb);
पूर्ण

अटल अंतरभूत व्योम qlcnic_dcb_enable(काष्ठा qlcnic_dcb *dcb)
अणु
	अगर (dcb && qlcnic_dcb_attach(dcb))
		qlcnic_clear_dcb_ops(dcb);
पूर्ण
#पूर्ण_अगर
