<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c)  2009-2013 QLogic Corporation
 */

#समावेश <linux/types.h>
#समावेश "qlcnic.h"

#घोषणा QLC_DCB_NUM_PARAM		3
#घोषणा QLC_DCB_LOCAL_IDX		0
#घोषणा QLC_DCB_OPER_IDX		1
#घोषणा QLC_DCB_PEER_IDX		2

#घोषणा QLC_DCB_GET_MAP(V)		(1 << V)

#घोषणा QLC_DCB_FW_VER			0x2
#घोषणा QLC_DCB_MAX_TC			0x8
#घोषणा QLC_DCB_MAX_APP			0x8
#घोषणा QLC_DCB_MAX_PRIO		QLC_DCB_MAX_TC
#घोषणा QLC_DCB_MAX_PG			QLC_DCB_MAX_TC

#घोषणा QLC_DCB_TSA_SUPPORT(V)		(V & 0x1)
#घोषणा QLC_DCB_ETS_SUPPORT(V)		((V >> 1) & 0x1)
#घोषणा QLC_DCB_VERSION_SUPPORT(V)	((V >> 2) & 0xf)
#घोषणा QLC_DCB_MAX_NUM_TC(V)		((V >> 20) & 0xf)
#घोषणा QLC_DCB_MAX_NUM_ETS_TC(V)	((V >> 24) & 0xf)
#घोषणा QLC_DCB_MAX_NUM_PFC_TC(V)	((V >> 28) & 0xf)
#घोषणा QLC_DCB_GET_TC_PRIO(X, P)	((X >> (P * 3)) & 0x7)
#घोषणा QLC_DCB_GET_PGID_PRIO(X, P)	((X >> (P * 8)) & 0xff)
#घोषणा QLC_DCB_GET_BWPER_PG(X, P)	((X >> (P * 8)) & 0xff)
#घोषणा QLC_DCB_GET_TSA_PG(X, P)	((X >> (P * 8)) & 0xff)
#घोषणा QLC_DCB_GET_PFC_PRIO(X, P)	(((X >> 24) >> P) & 0x1)
#घोषणा QLC_DCB_GET_PROTO_ID_APP(X)	((X >> 8) & 0xffff)
#घोषणा QLC_DCB_GET_SELECTOR_APP(X)	(X & 0xff)

#घोषणा QLC_DCB_LOCAL_PARAM_FWID	0x3
#घोषणा QLC_DCB_OPER_PARAM_FWID		0x1
#घोषणा QLC_DCB_PEER_PARAM_FWID		0x2

#घोषणा QLC_83XX_DCB_GET_NUMAPP(X)	((X >> 2) & 0xf)
#घोषणा QLC_83XX_DCB_TSA_VALID(X)	(X & 0x1)
#घोषणा QLC_83XX_DCB_PFC_VALID(X)	((X >> 1) & 0x1)
#घोषणा QLC_83XX_DCB_GET_PRIOMAP_APP(X)	(X >> 24)

#घोषणा QLC_82XX_DCB_GET_NUMAPP(X)	((X >> 12) & 0xf)
#घोषणा QLC_82XX_DCB_TSA_VALID(X)	((X >> 4) & 0x1)
#घोषणा QLC_82XX_DCB_PFC_VALID(X)	((X >> 5) & 0x1)
#घोषणा QLC_82XX_DCB_GET_PRIOVAL_APP(X)	((X >> 24) & 0x7)
#घोषणा QLC_82XX_DCB_GET_PRIOMAP_APP(X)	(1 << X)
#घोषणा QLC_82XX_DCB_PRIO_TC_MAP	(0x76543210)

अटल स्थिर काष्ठा dcbnl_rtnl_ops qlcnic_dcbnl_ops;

अटल व्योम qlcnic_dcb_aen_work(काष्ठा work_काष्ठा *);
अटल व्योम qlcnic_dcb_data_cee_param_map(काष्ठा qlcnic_adapter *);

अटल अंतरभूत व्योम __qlcnic_init_dcbnl_ops(काष्ठा qlcnic_dcb *);
अटल व्योम __qlcnic_dcb_मुक्त(काष्ठा qlcnic_dcb *);
अटल पूर्णांक __qlcnic_dcb_attach(काष्ठा qlcnic_dcb *);
अटल पूर्णांक __qlcnic_dcb_query_hw_capability(काष्ठा qlcnic_dcb *, अक्षर *);
अटल व्योम __qlcnic_dcb_get_info(काष्ठा qlcnic_dcb *);

अटल पूर्णांक qlcnic_82xx_dcb_get_hw_capability(काष्ठा qlcnic_dcb *);
अटल पूर्णांक qlcnic_82xx_dcb_query_cee_param(काष्ठा qlcnic_dcb *, अक्षर *, u8);
अटल पूर्णांक qlcnic_82xx_dcb_get_cee_cfg(काष्ठा qlcnic_dcb *);
अटल व्योम qlcnic_82xx_dcb_aen_handler(काष्ठा qlcnic_dcb *, व्योम *);

अटल पूर्णांक qlcnic_83xx_dcb_get_hw_capability(काष्ठा qlcnic_dcb *);
अटल पूर्णांक qlcnic_83xx_dcb_query_cee_param(काष्ठा qlcnic_dcb *, अक्षर *, u8);
अटल पूर्णांक qlcnic_83xx_dcb_get_cee_cfg(काष्ठा qlcnic_dcb *);
अटल व्योम qlcnic_83xx_dcb_aen_handler(काष्ठा qlcnic_dcb *, व्योम *);

काष्ठा qlcnic_dcb_capability अणु
	bool	tsa_capability;
	bool	ets_capability;
	u8	max_num_tc;
	u8	max_ets_tc;
	u8	max_pfc_tc;
	u8	dcb_capability;
पूर्ण;

काष्ठा qlcnic_dcb_param अणु
	u32 hdr_prio_pfc_map[2];
	u32 prio_pg_map[2];
	u32 pg_bw_map[2];
	u32 pg_tsa_map[2];
	u32 app[QLC_DCB_MAX_APP];
पूर्ण;

काष्ठा qlcnic_dcb_mbx_params अणु
	/* 1st local, 2nd operational 3rd remote */
	काष्ठा qlcnic_dcb_param type[3];
	u32 prio_tc_map;
पूर्ण;

काष्ठा qlcnic_82xx_dcb_param_mbx_le अणु
	__le32 hdr_prio_pfc_map[2];
	__le32 prio_pg_map[2];
	__le32 pg_bw_map[2];
	__le32 pg_tsa_map[2];
	__le32 app[QLC_DCB_MAX_APP];
पूर्ण;

क्रमागत qlcnic_dcb_selector अणु
	QLC_SELECTOR_DEF = 0x0,
	QLC_SELECTOR_ETHER,
	QLC_SELECTOR_TCP,
	QLC_SELECTOR_UDP,
पूर्ण;

क्रमागत qlcnic_dcb_prio_type अणु
	QLC_PRIO_NONE = 0,
	QLC_PRIO_GROUP,
	QLC_PRIO_LINK,
पूर्ण;

क्रमागत qlcnic_dcb_pfc_type अणु
	QLC_PFC_DISABLED = 0,
	QLC_PFC_FULL,
	QLC_PFC_TX,
	QLC_PFC_RX
पूर्ण;

काष्ठा qlcnic_dcb_prio_cfg अणु
	bool valid;
	क्रमागत qlcnic_dcb_pfc_type pfc_type;
पूर्ण;

काष्ठा qlcnic_dcb_pg_cfg अणु
	bool valid;
	u8 total_bw_percent;		/* of Link/ port BW */
	u8 prio_count;
	u8 tsa_type;
पूर्ण;

काष्ठा qlcnic_dcb_tc_cfg अणु
	bool valid;
	काष्ठा qlcnic_dcb_prio_cfg prio_cfg[QLC_DCB_MAX_PRIO];
	क्रमागत qlcnic_dcb_prio_type prio_type;	/* always prio_link */
	u8 link_percent;			/* % of link bandwidth */
	u8 bwg_percent;				/* % of BWG's bandwidth */
	u8 up_tc_map;
	u8 pgid;
पूर्ण;

काष्ठा qlcnic_dcb_app अणु
	bool valid;
	क्रमागत qlcnic_dcb_selector selector;
	u16 protocol;
	u8 priority;
पूर्ण;

काष्ठा qlcnic_dcb_cee अणु
	काष्ठा qlcnic_dcb_tc_cfg tc_cfg[QLC_DCB_MAX_TC];
	काष्ठा qlcnic_dcb_pg_cfg pg_cfg[QLC_DCB_MAX_PG];
	काष्ठा qlcnic_dcb_app app[QLC_DCB_MAX_APP];
	bool tc_param_valid;
	bool pfc_mode_enable;
पूर्ण;

काष्ठा qlcnic_dcb_cfg अणु
	/* 0 - local, 1 - operational, 2 - remote */
	काष्ठा qlcnic_dcb_cee type[QLC_DCB_NUM_PARAM];
	काष्ठा qlcnic_dcb_capability capability;
	u32 version;
पूर्ण;

अटल स्थिर काष्ठा qlcnic_dcb_ops qlcnic_83xx_dcb_ops = अणु
	.init_dcbnl_ops		= __qlcnic_init_dcbnl_ops,
	.मुक्त			= __qlcnic_dcb_मुक्त,
	.attach			= __qlcnic_dcb_attach,
	.query_hw_capability	= __qlcnic_dcb_query_hw_capability,
	.get_info		= __qlcnic_dcb_get_info,

	.get_hw_capability	= qlcnic_83xx_dcb_get_hw_capability,
	.query_cee_param	= qlcnic_83xx_dcb_query_cee_param,
	.get_cee_cfg		= qlcnic_83xx_dcb_get_cee_cfg,
	.aen_handler		= qlcnic_83xx_dcb_aen_handler,
पूर्ण;

अटल स्थिर काष्ठा qlcnic_dcb_ops qlcnic_82xx_dcb_ops = अणु
	.init_dcbnl_ops		= __qlcnic_init_dcbnl_ops,
	.मुक्त			= __qlcnic_dcb_मुक्त,
	.attach			= __qlcnic_dcb_attach,
	.query_hw_capability	= __qlcnic_dcb_query_hw_capability,
	.get_info		= __qlcnic_dcb_get_info,

	.get_hw_capability	= qlcnic_82xx_dcb_get_hw_capability,
	.query_cee_param	= qlcnic_82xx_dcb_query_cee_param,
	.get_cee_cfg		= qlcnic_82xx_dcb_get_cee_cfg,
	.aen_handler		= qlcnic_82xx_dcb_aen_handler,
पूर्ण;

अटल u8 qlcnic_dcb_get_num_app(काष्ठा qlcnic_adapter *adapter, u32 val)
अणु
	अगर (qlcnic_82xx_check(adapter))
		वापस QLC_82XX_DCB_GET_NUMAPP(val);
	अन्यथा
		वापस QLC_83XX_DCB_GET_NUMAPP(val);
पूर्ण

अटल अंतरभूत u8 qlcnic_dcb_pfc_hdr_valid(काष्ठा qlcnic_adapter *adapter,
					  u32 val)
अणु
	अगर (qlcnic_82xx_check(adapter))
		वापस QLC_82XX_DCB_PFC_VALID(val);
	अन्यथा
		वापस QLC_83XX_DCB_PFC_VALID(val);
पूर्ण

अटल अंतरभूत u8 qlcnic_dcb_tsa_hdr_valid(काष्ठा qlcnic_adapter *adapter,
					  u32 val)
अणु
	अगर (qlcnic_82xx_check(adapter))
		वापस QLC_82XX_DCB_TSA_VALID(val);
	अन्यथा
		वापस QLC_83XX_DCB_TSA_VALID(val);
पूर्ण

अटल अंतरभूत u8 qlcnic_dcb_get_prio_map_app(काष्ठा qlcnic_adapter *adapter,
					     u32 val)
अणु
	अगर (qlcnic_82xx_check(adapter))
		वापस QLC_82XX_DCB_GET_PRIOMAP_APP(val);
	अन्यथा
		वापस QLC_83XX_DCB_GET_PRIOMAP_APP(val);
पूर्ण

अटल पूर्णांक qlcnic_dcb_prio_count(u8 up_tc_map)
अणु
	पूर्णांक j;

	क्रम (j = 0; j < QLC_DCB_MAX_TC; j++)
		अगर (up_tc_map & QLC_DCB_GET_MAP(j))
			अवरोध;

	वापस j;
पूर्ण

अटल अंतरभूत व्योम __qlcnic_init_dcbnl_ops(काष्ठा qlcnic_dcb *dcb)
अणु
	अगर (test_bit(QLCNIC_DCB_STATE, &dcb->state))
		dcb->adapter->netdev->dcbnl_ops = &qlcnic_dcbnl_ops;
पूर्ण

अटल व्योम qlcnic_set_dcb_ops(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (qlcnic_82xx_check(adapter))
		adapter->dcb->ops = &qlcnic_82xx_dcb_ops;
	अन्यथा अगर (qlcnic_83xx_check(adapter))
		adapter->dcb->ops = &qlcnic_83xx_dcb_ops;
पूर्ण

पूर्णांक qlcnic_रेजिस्टर_dcb(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_dcb *dcb;

	अगर (qlcnic_sriov_vf_check(adapter))
		वापस 0;

	dcb = kzalloc(माप(काष्ठा qlcnic_dcb), GFP_ATOMIC);
	अगर (!dcb)
		वापस -ENOMEM;

	adapter->dcb = dcb;
	dcb->adapter = adapter;
	qlcnic_set_dcb_ops(adapter);
	dcb->state = 0;

	वापस 0;
पूर्ण

अटल व्योम __qlcnic_dcb_मुक्त(काष्ठा qlcnic_dcb *dcb)
अणु
	काष्ठा qlcnic_adapter *adapter;

	अगर (!dcb)
		वापस;

	adapter = dcb->adapter;

	जबतक (test_bit(QLCNIC_DCB_AEN_MODE, &dcb->state))
		usleep_range(10000, 11000);

	cancel_delayed_work_sync(&dcb->aen_work);

	अगर (dcb->wq) अणु
		destroy_workqueue(dcb->wq);
		dcb->wq = शून्य;
	पूर्ण

	kमुक्त(dcb->cfg);
	dcb->cfg = शून्य;
	kमुक्त(dcb->param);
	dcb->param = शून्य;
	kमुक्त(dcb);
	adapter->dcb = शून्य;
पूर्ण

अटल व्योम __qlcnic_dcb_get_info(काष्ठा qlcnic_dcb *dcb)
अणु
	qlcnic_dcb_get_hw_capability(dcb);
	qlcnic_dcb_get_cee_cfg(dcb);
पूर्ण

अटल पूर्णांक __qlcnic_dcb_attach(काष्ठा qlcnic_dcb *dcb)
अणु
	पूर्णांक err = 0;

	INIT_DELAYED_WORK(&dcb->aen_work, qlcnic_dcb_aen_work);

	dcb->wq = create_singlethपढ़ो_workqueue("qlcnic-dcb");
	अगर (!dcb->wq) अणु
		dev_err(&dcb->adapter->pdev->dev,
			"DCB workqueue allocation failed. DCB will be disabled\n");
		वापस -1;
	पूर्ण

	dcb->cfg = kzalloc(माप(काष्ठा qlcnic_dcb_cfg), GFP_ATOMIC);
	अगर (!dcb->cfg) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_wq;
	पूर्ण

	dcb->param = kzalloc(माप(काष्ठा qlcnic_dcb_mbx_params), GFP_ATOMIC);
	अगर (!dcb->param) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_cfg;
	पूर्ण

	वापस 0;
out_मुक्त_cfg:
	kमुक्त(dcb->cfg);
	dcb->cfg = शून्य;

out_मुक्त_wq:
	destroy_workqueue(dcb->wq);
	dcb->wq = शून्य;

	वापस err;
पूर्ण

अटल पूर्णांक __qlcnic_dcb_query_hw_capability(काष्ठा qlcnic_dcb *dcb, अक्षर *buf)
अणु
	काष्ठा qlcnic_adapter *adapter = dcb->adapter;
	काष्ठा qlcnic_cmd_args cmd;
	u32 mbx_out;
	पूर्णांक err;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_DCB_QUERY_CAP);
	अगर (err)
		वापस err;

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to query DCBX capability, err %d\n", err);
	पूर्ण अन्यथा अणु
		mbx_out = cmd.rsp.arg[1];
		अगर (buf)
			स_नकल(buf, &mbx_out, माप(u32));
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);

	वापस err;
पूर्ण

अटल पूर्णांक __qlcnic_dcb_get_capability(काष्ठा qlcnic_dcb *dcb, u32 *val)
अणु
	काष्ठा qlcnic_dcb_capability *cap = &dcb->cfg->capability;
	u32 mbx_out;
	पूर्णांक err;

	स_रखो(cap, 0, माप(काष्ठा qlcnic_dcb_capability));

	err = qlcnic_dcb_query_hw_capability(dcb, (अक्षर *)val);
	अगर (err)
		वापस err;

	mbx_out = *val;
	अगर (QLC_DCB_TSA_SUPPORT(mbx_out))
		cap->tsa_capability = true;

	अगर (QLC_DCB_ETS_SUPPORT(mbx_out))
		cap->ets_capability = true;

	cap->max_num_tc = QLC_DCB_MAX_NUM_TC(mbx_out);
	cap->max_ets_tc = QLC_DCB_MAX_NUM_ETS_TC(mbx_out);
	cap->max_pfc_tc = QLC_DCB_MAX_NUM_PFC_TC(mbx_out);

	अगर (cap->max_num_tc > QLC_DCB_MAX_TC ||
	    cap->max_ets_tc > cap->max_num_tc ||
	    cap->max_pfc_tc > cap->max_num_tc) अणु
		dev_err(&dcb->adapter->pdev->dev, "Invalid DCB configuration\n");
		वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_82xx_dcb_get_hw_capability(काष्ठा qlcnic_dcb *dcb)
अणु
	काष्ठा qlcnic_dcb_cfg *cfg = dcb->cfg;
	काष्ठा qlcnic_dcb_capability *cap;
	u32 mbx_out;
	पूर्णांक err;

	err = __qlcnic_dcb_get_capability(dcb, &mbx_out);
	अगर (err)
		वापस err;

	cap = &cfg->capability;
	cap->dcb_capability = DCB_CAP_DCBX_VER_CEE | DCB_CAP_DCBX_LLD_MANAGED;

	अगर (cap->dcb_capability && cap->tsa_capability && cap->ets_capability)
		set_bit(QLCNIC_DCB_STATE, &dcb->state);

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_82xx_dcb_query_cee_param(काष्ठा qlcnic_dcb *dcb,
					   अक्षर *buf, u8 type)
अणु
	u16 size = माप(काष्ठा qlcnic_82xx_dcb_param_mbx_le);
	काष्ठा qlcnic_adapter *adapter = dcb->adapter;
	काष्ठा qlcnic_82xx_dcb_param_mbx_le *prsp_le;
	काष्ठा device *dev = &adapter->pdev->dev;
	dma_addr_t cardrsp_phys_addr;
	काष्ठा qlcnic_dcb_param rsp;
	काष्ठा qlcnic_cmd_args cmd;
	u64 phys_addr;
	व्योम *addr;
	पूर्णांक err, i;

	चयन (type) अणु
	हाल QLC_DCB_LOCAL_PARAM_FWID:
	हाल QLC_DCB_OPER_PARAM_FWID:
	हाल QLC_DCB_PEER_PARAM_FWID:
		अवरोध;
	शेष:
		dev_err(dev, "Invalid parameter type %d\n", type);
		वापस -EINVAL;
	पूर्ण

	addr = dma_alloc_coherent(dev, size, &cardrsp_phys_addr, GFP_KERNEL);
	अगर (addr == शून्य)
		वापस -ENOMEM;

	prsp_le = addr;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_DCB_QUERY_PARAM);
	अगर (err)
		जाओ out_मुक्त_rsp;

	phys_addr = cardrsp_phys_addr;
	cmd.req.arg[1] = size | (type << 16);
	cmd.req.arg[2] = MSD(phys_addr);
	cmd.req.arg[3] = LSD(phys_addr);

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_err(dev, "Failed to query DCBX parameter, err %d\n", err);
		जाओ out;
	पूर्ण

	स_रखो(&rsp, 0, माप(काष्ठा qlcnic_dcb_param));
	rsp.hdr_prio_pfc_map[0] = le32_to_cpu(prsp_le->hdr_prio_pfc_map[0]);
	rsp.hdr_prio_pfc_map[1] = le32_to_cpu(prsp_le->hdr_prio_pfc_map[1]);
	rsp.prio_pg_map[0] = le32_to_cpu(prsp_le->prio_pg_map[0]);
	rsp.prio_pg_map[1] = le32_to_cpu(prsp_le->prio_pg_map[1]);
	rsp.pg_bw_map[0] = le32_to_cpu(prsp_le->pg_bw_map[0]);
	rsp.pg_bw_map[1] = le32_to_cpu(prsp_le->pg_bw_map[1]);
	rsp.pg_tsa_map[0] = le32_to_cpu(prsp_le->pg_tsa_map[0]);
	rsp.pg_tsa_map[1] = le32_to_cpu(prsp_le->pg_tsa_map[1]);

	क्रम (i = 0; i < QLC_DCB_MAX_APP; i++)
		rsp.app[i] = le32_to_cpu(prsp_le->app[i]);

	अगर (buf)
		स_नकल(buf, &rsp, size);
out:
	qlcnic_मुक्त_mbx_args(&cmd);

out_मुक्त_rsp:
	dma_मुक्त_coherent(dev, size, addr, cardrsp_phys_addr);

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_82xx_dcb_get_cee_cfg(काष्ठा qlcnic_dcb *dcb)
अणु
	काष्ठा qlcnic_dcb_mbx_params *mbx;
	पूर्णांक err;

	mbx = dcb->param;
	अगर (!mbx)
		वापस 0;

	err = qlcnic_dcb_query_cee_param(dcb, (अक्षर *)&mbx->type[0],
					 QLC_DCB_LOCAL_PARAM_FWID);
	अगर (err)
		वापस err;

	err = qlcnic_dcb_query_cee_param(dcb, (अक्षर *)&mbx->type[1],
					 QLC_DCB_OPER_PARAM_FWID);
	अगर (err)
		वापस err;

	err = qlcnic_dcb_query_cee_param(dcb, (अक्षर *)&mbx->type[2],
					 QLC_DCB_PEER_PARAM_FWID);
	अगर (err)
		वापस err;

	mbx->prio_tc_map = QLC_82XX_DCB_PRIO_TC_MAP;

	qlcnic_dcb_data_cee_param_map(dcb->adapter);

	वापस err;
पूर्ण

अटल व्योम qlcnic_dcb_aen_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlcnic_dcb *dcb;

	dcb = container_of(work, काष्ठा qlcnic_dcb, aen_work.work);

	qlcnic_dcb_get_cee_cfg(dcb);
	clear_bit(QLCNIC_DCB_AEN_MODE, &dcb->state);
पूर्ण

अटल व्योम qlcnic_82xx_dcb_aen_handler(काष्ठा qlcnic_dcb *dcb, व्योम *data)
अणु
	अगर (test_and_set_bit(QLCNIC_DCB_AEN_MODE, &dcb->state))
		वापस;

	queue_delayed_work(dcb->wq, &dcb->aen_work, 0);
पूर्ण

अटल पूर्णांक qlcnic_83xx_dcb_get_hw_capability(काष्ठा qlcnic_dcb *dcb)
अणु
	काष्ठा qlcnic_dcb_capability *cap = &dcb->cfg->capability;
	u32 mbx_out;
	पूर्णांक err;

	err = __qlcnic_dcb_get_capability(dcb, &mbx_out);
	अगर (err)
		वापस err;

	अगर (mbx_out & BIT_2)
		cap->dcb_capability = DCB_CAP_DCBX_VER_CEE;
	अगर (mbx_out & BIT_3)
		cap->dcb_capability |= DCB_CAP_DCBX_VER_IEEE;
	अगर (cap->dcb_capability)
		cap->dcb_capability |= DCB_CAP_DCBX_LLD_MANAGED;

	अगर (cap->dcb_capability && cap->tsa_capability && cap->ets_capability)
		set_bit(QLCNIC_DCB_STATE, &dcb->state);

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_83xx_dcb_query_cee_param(काष्ठा qlcnic_dcb *dcb,
					   अक्षर *buf, u8 idx)
अणु
	काष्ठा qlcnic_adapter *adapter = dcb->adapter;
	काष्ठा qlcnic_dcb_mbx_params mbx_out;
	पूर्णांक err, i, j, k, max_app, size;
	काष्ठा qlcnic_dcb_param *each;
	काष्ठा qlcnic_cmd_args cmd;
	u32 val;
	अक्षर *p;

	size = 0;
	स_रखो(&mbx_out, 0, माप(काष्ठा qlcnic_dcb_mbx_params));
	स_रखो(buf, 0, माप(काष्ठा qlcnic_dcb_mbx_params));

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_DCB_QUERY_PARAM);
	अगर (err)
		वापस err;

	cmd.req.arg[0] |= QLC_DCB_FW_VER << 29;
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to query DCBX param, err %d\n", err);
		जाओ out;
	पूर्ण

	mbx_out.prio_tc_map = cmd.rsp.arg[1];
	p = स_नकल(buf, &mbx_out, माप(u32));
	k = 2;
	p += माप(u32);

	क्रम (j = 0; j < QLC_DCB_NUM_PARAM; j++) अणु
		each = &mbx_out.type[j];

		each->hdr_prio_pfc_map[0] = cmd.rsp.arg[k++];
		each->hdr_prio_pfc_map[1] = cmd.rsp.arg[k++];
		each->prio_pg_map[0] = cmd.rsp.arg[k++];
		each->prio_pg_map[1] = cmd.rsp.arg[k++];
		each->pg_bw_map[0] = cmd.rsp.arg[k++];
		each->pg_bw_map[1] = cmd.rsp.arg[k++];
		each->pg_tsa_map[0] = cmd.rsp.arg[k++];
		each->pg_tsa_map[1] = cmd.rsp.arg[k++];
		val = each->hdr_prio_pfc_map[0];

		max_app = qlcnic_dcb_get_num_app(adapter, val);
		क्रम (i = 0; i < max_app; i++)
			each->app[i] = cmd.rsp.arg[i + k];

		size = 16 * माप(u32);
		स_नकल(p, &each->hdr_prio_pfc_map[0], size);
		p += size;
		अगर (j == 0)
			k = 18;
		अन्यथा
			k = 34;
	पूर्ण
out:
	qlcnic_मुक्त_mbx_args(&cmd);

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_83xx_dcb_get_cee_cfg(काष्ठा qlcnic_dcb *dcb)
अणु
	पूर्णांक err;

	err = qlcnic_dcb_query_cee_param(dcb, (अक्षर *)dcb->param, 0);
	अगर (err)
		वापस err;

	qlcnic_dcb_data_cee_param_map(dcb->adapter);

	वापस err;
पूर्ण

अटल व्योम qlcnic_83xx_dcb_aen_handler(काष्ठा qlcnic_dcb *dcb, व्योम *data)
अणु
	u32 *val = data;

	अगर (test_and_set_bit(QLCNIC_DCB_AEN_MODE, &dcb->state))
		वापस;

	अगर (*val & BIT_8)
		set_bit(QLCNIC_DCB_STATE, &dcb->state);
	अन्यथा
		clear_bit(QLCNIC_DCB_STATE, &dcb->state);

	queue_delayed_work(dcb->wq, &dcb->aen_work, 0);
पूर्ण

अटल व्योम qlcnic_dcb_fill_cee_tc_params(काष्ठा qlcnic_dcb_mbx_params *mbx,
					  काष्ठा qlcnic_dcb_param *each,
					  काष्ठा qlcnic_dcb_cee *type)
अणु
	काष्ठा qlcnic_dcb_tc_cfg *tc_cfg;
	u8 i, tc, pgid;

	क्रम (i = 0; i < QLC_DCB_MAX_PRIO; i++) अणु
		tc = QLC_DCB_GET_TC_PRIO(mbx->prio_tc_map, i);
		tc_cfg = &type->tc_cfg[tc];
		tc_cfg->valid = true;
		tc_cfg->up_tc_map |= QLC_DCB_GET_MAP(i);

		अगर (QLC_DCB_GET_PFC_PRIO(each->hdr_prio_pfc_map[1], i) &&
		    type->pfc_mode_enable) अणु
			tc_cfg->prio_cfg[i].valid = true;
			tc_cfg->prio_cfg[i].pfc_type = QLC_PFC_FULL;
		पूर्ण

		अगर (i < 4)
			pgid = QLC_DCB_GET_PGID_PRIO(each->prio_pg_map[0], i);
		अन्यथा
			pgid = QLC_DCB_GET_PGID_PRIO(each->prio_pg_map[1], i);

		tc_cfg->pgid = pgid;

		tc_cfg->prio_type = QLC_PRIO_LINK;
		type->pg_cfg[tc_cfg->pgid].prio_count++;
	पूर्ण
पूर्ण

अटल व्योम qlcnic_dcb_fill_cee_pg_params(काष्ठा qlcnic_dcb_param *each,
					  काष्ठा qlcnic_dcb_cee *type)
अणु
	काष्ठा qlcnic_dcb_pg_cfg *pg_cfg;
	u8 i, tsa, bw_per;

	क्रम (i = 0; i < QLC_DCB_MAX_PG; i++) अणु
		pg_cfg = &type->pg_cfg[i];
		pg_cfg->valid = true;

		अगर (i < 4) अणु
			bw_per = QLC_DCB_GET_BWPER_PG(each->pg_bw_map[0], i);
			tsa = QLC_DCB_GET_TSA_PG(each->pg_tsa_map[0], i);
		पूर्ण अन्यथा अणु
			bw_per = QLC_DCB_GET_BWPER_PG(each->pg_bw_map[1], i);
			tsa = QLC_DCB_GET_TSA_PG(each->pg_tsa_map[1], i);
		पूर्ण

		pg_cfg->total_bw_percent = bw_per;
		pg_cfg->tsa_type = tsa;
	पूर्ण
पूर्ण

अटल व्योम
qlcnic_dcb_fill_cee_app_params(काष्ठा qlcnic_adapter *adapter, u8 idx,
			       काष्ठा qlcnic_dcb_param *each,
			       काष्ठा qlcnic_dcb_cee *type)
अणु
	काष्ठा qlcnic_dcb_app *app;
	u8 i, num_app, map, cnt;
	काष्ठा dcb_app new_app;

	num_app = qlcnic_dcb_get_num_app(adapter, each->hdr_prio_pfc_map[0]);
	क्रम (i = 0; i < num_app; i++) अणु
		app = &type->app[i];
		app->valid = true;

		/* Only क्रम CEE (-1) */
		app->selector = QLC_DCB_GET_SELECTOR_APP(each->app[i]) - 1;
		new_app.selector = app->selector;
		app->protocol = QLC_DCB_GET_PROTO_ID_APP(each->app[i]);
		new_app.protocol = app->protocol;
		map = qlcnic_dcb_get_prio_map_app(adapter, each->app[i]);
		cnt = qlcnic_dcb_prio_count(map);

		अगर (cnt >= QLC_DCB_MAX_TC)
			cnt = 0;

		app->priority = cnt;
		new_app.priority = cnt;

		अगर (idx == QLC_DCB_OPER_IDX && adapter->netdev->dcbnl_ops)
			dcb_setapp(adapter->netdev, &new_app);
	पूर्ण
पूर्ण

अटल व्योम qlcnic_dcb_map_cee_params(काष्ठा qlcnic_adapter *adapter, u8 idx)
अणु
	काष्ठा qlcnic_dcb_mbx_params *mbx = adapter->dcb->param;
	काष्ठा qlcnic_dcb_param *each = &mbx->type[idx];
	काष्ठा qlcnic_dcb_cfg *cfg = adapter->dcb->cfg;
	काष्ठा qlcnic_dcb_cee *type = &cfg->type[idx];

	type->tc_param_valid = false;
	type->pfc_mode_enable = false;
	स_रखो(type->tc_cfg, 0,
	       माप(काष्ठा qlcnic_dcb_tc_cfg) * QLC_DCB_MAX_TC);
	स_रखो(type->pg_cfg, 0,
	       माप(काष्ठा qlcnic_dcb_pg_cfg) * QLC_DCB_MAX_TC);

	अगर (qlcnic_dcb_pfc_hdr_valid(adapter, each->hdr_prio_pfc_map[0]) &&
	    cfg->capability.max_pfc_tc)
		type->pfc_mode_enable = true;

	अगर (qlcnic_dcb_tsa_hdr_valid(adapter, each->hdr_prio_pfc_map[0]) &&
	    cfg->capability.max_ets_tc)
		type->tc_param_valid = true;

	qlcnic_dcb_fill_cee_tc_params(mbx, each, type);
	qlcnic_dcb_fill_cee_pg_params(each, type);
	qlcnic_dcb_fill_cee_app_params(adapter, idx, each, type);
पूर्ण

अटल व्योम qlcnic_dcb_data_cee_param_map(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < QLC_DCB_NUM_PARAM; i++)
		qlcnic_dcb_map_cee_params(adapter, i);

	dcbnl_cee_notअगरy(adapter->netdev, RTM_GETDCB, DCB_CMD_CEE_GET, 0, 0);
पूर्ण

अटल u8 qlcnic_dcb_get_state(काष्ठा net_device *netdev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);

	वापस test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state);
पूर्ण

अटल व्योम qlcnic_dcb_get_perm_hw_addr(काष्ठा net_device *netdev, u8 *addr)
अणु
	स_नकल(addr, netdev->perm_addr, netdev->addr_len);
पूर्ण

अटल व्योम
qlcnic_dcb_get_pg_tc_cfg_tx(काष्ठा net_device *netdev, पूर्णांक tc, u8 *prio,
			    u8 *pgid, u8 *bw_per, u8 *up_tc_map)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_dcb_tc_cfg *tc_cfg, *temp;
	काष्ठा qlcnic_dcb_cee *type;
	u8 i, cnt, pg;

	type = &adapter->dcb->cfg->type[QLC_DCB_OPER_IDX];
	*prio = *pgid = *bw_per = *up_tc_map = 0;

	अगर (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state) ||
	    !type->tc_param_valid)
		वापस;

	अगर (tc < 0 || (tc >= QLC_DCB_MAX_TC))
		वापस;

	tc_cfg = &type->tc_cfg[tc];
	अगर (!tc_cfg->valid)
		वापस;

	*pgid = tc_cfg->pgid;
	*prio = tc_cfg->prio_type;
	*up_tc_map = tc_cfg->up_tc_map;
	pg = *pgid;

	क्रम (i = 0, cnt = 0; i < QLC_DCB_MAX_TC; i++) अणु
		temp = &type->tc_cfg[i];
		अगर (temp->valid && (pg == temp->pgid))
			cnt++;
	पूर्ण

	tc_cfg->bwg_percent = (100 / cnt);
	*bw_per = tc_cfg->bwg_percent;
पूर्ण

अटल व्योम qlcnic_dcb_get_pg_bwg_cfg_tx(काष्ठा net_device *netdev, पूर्णांक pgid,
					 u8 *bw_pct)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_dcb_pg_cfg *pgcfg;
	काष्ठा qlcnic_dcb_cee *type;

	*bw_pct = 0;
	type = &adapter->dcb->cfg->type[QLC_DCB_OPER_IDX];

	अगर (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state) ||
	    !type->tc_param_valid)
		वापस;

	अगर (pgid < 0 || pgid >= QLC_DCB_MAX_PG)
		वापस;

	pgcfg = &type->pg_cfg[pgid];
	अगर (!pgcfg->valid)
		वापस;

	*bw_pct = pgcfg->total_bw_percent;
पूर्ण

अटल व्योम qlcnic_dcb_get_pfc_cfg(काष्ठा net_device *netdev, पूर्णांक prio,
				   u8 *setting)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_dcb_tc_cfg *tc_cfg;
	u8 val = QLC_DCB_GET_MAP(prio);
	काष्ठा qlcnic_dcb_cee *type;
	u8 i;

	*setting = 0;
	type = &adapter->dcb->cfg->type[QLC_DCB_OPER_IDX];

	अगर (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state) ||
	    !type->pfc_mode_enable)
		वापस;

	क्रम (i = 0; i < QLC_DCB_MAX_TC; i++) अणु
		tc_cfg = &type->tc_cfg[i];
		अगर (!tc_cfg->valid)
			जारी;

		अगर ((val & tc_cfg->up_tc_map) && (tc_cfg->prio_cfg[prio].valid))
			*setting = tc_cfg->prio_cfg[prio].pfc_type;
	पूर्ण
पूर्ण

अटल u8 qlcnic_dcb_get_capability(काष्ठा net_device *netdev, पूर्णांक capid,
				    u8 *cap)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);

	अगर (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		वापस 1;

	चयन (capid) अणु
	हाल DCB_CAP_ATTR_PG:
	हाल DCB_CAP_ATTR_UP2TC:
	हाल DCB_CAP_ATTR_PFC:
	हाल DCB_CAP_ATTR_GSP:
		*cap = true;
		अवरोध;
	हाल DCB_CAP_ATTR_PG_TCS:
	हाल DCB_CAP_ATTR_PFC_TCS:
		*cap = 0x80;	/* 8 priorities क्रम PGs */
		अवरोध;
	हाल DCB_CAP_ATTR_DCBX:
		*cap = adapter->dcb->cfg->capability.dcb_capability;
		अवरोध;
	शेष:
		*cap = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_dcb_get_num_tcs(काष्ठा net_device *netdev, पूर्णांक attr, u8 *num)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_dcb_cfg *cfg = adapter->dcb->cfg;

	अगर (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		वापस -EINVAL;

	चयन (attr) अणु
	हाल DCB_NUMTCS_ATTR_PG:
		*num = cfg->capability.max_ets_tc;
		वापस 0;
	हाल DCB_NUMTCS_ATTR_PFC:
		*num = cfg->capability.max_pfc_tc;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक qlcnic_dcb_get_app(काष्ठा net_device *netdev, u8 idtype, u16 id)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा dcb_app app = अणु
				.selector = idtype,
				.protocol = id,
			     पूर्ण;

	अगर (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		वापस -EINVAL;

	वापस dcb_getapp(netdev, &app);
पूर्ण

अटल u8 qlcnic_dcb_get_pfc_state(काष्ठा net_device *netdev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_dcb *dcb = adapter->dcb;

	अगर (!test_bit(QLCNIC_DCB_STATE, &dcb->state))
		वापस 0;

	वापस dcb->cfg->type[QLC_DCB_OPER_IDX].pfc_mode_enable;
पूर्ण

अटल u8 qlcnic_dcb_get_dcbx(काष्ठा net_device *netdev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_dcb_cfg *cfg = adapter->dcb->cfg;

	अगर (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		वापस 0;

	वापस cfg->capability.dcb_capability;
पूर्ण

अटल u8 qlcnic_dcb_get_feat_cfg(काष्ठा net_device *netdev, पूर्णांक fid, u8 *flag)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_dcb_cee *type;

	अगर (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		वापस 1;

	type = &adapter->dcb->cfg->type[QLC_DCB_OPER_IDX];
	*flag = 0;

	चयन (fid) अणु
	हाल DCB_FEATCFG_ATTR_PG:
		अगर (type->tc_param_valid)
			*flag |= DCB_FEATCFG_ENABLE;
		अन्यथा
			*flag |= DCB_FEATCFG_ERROR;
		अवरोध;
	हाल DCB_FEATCFG_ATTR_PFC:
		अगर (type->pfc_mode_enable) अणु
			अगर (type->tc_cfg[0].prio_cfg[0].pfc_type)
				*flag |= DCB_FEATCFG_ENABLE;
		पूर्ण अन्यथा अणु
			*flag |= DCB_FEATCFG_ERROR;
		पूर्ण
		अवरोध;
	हाल DCB_FEATCFG_ATTR_APP:
		*flag |= DCB_FEATCFG_ENABLE;
		अवरोध;
	शेष:
		netdev_err(netdev, "Invalid Feature ID %d\n", fid);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
qlcnic_dcb_get_pg_tc_cfg_rx(काष्ठा net_device *netdev, पूर्णांक prio, u8 *prio_type,
			    u8 *pgid, u8 *bw_pct, u8 *up_map)
अणु
	*prio_type = *pgid = *bw_pct = *up_map = 0;
पूर्ण

अटल अंतरभूत व्योम
qlcnic_dcb_get_pg_bwg_cfg_rx(काष्ठा net_device *netdev, पूर्णांक pgid, u8 *bw_pct)
अणु
	*bw_pct = 0;
पूर्ण

अटल पूर्णांक qlcnic_dcb_peer_app_info(काष्ठा net_device *netdev,
				    काष्ठा dcb_peer_app_info *info,
				    u16 *app_count)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_dcb_cee *peer;
	पूर्णांक i;

	स_रखो(info, 0, माप(*info));
	*app_count = 0;

	अगर (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		वापस 0;

	peer = &adapter->dcb->cfg->type[QLC_DCB_PEER_IDX];

	क्रम (i = 0; i < QLC_DCB_MAX_APP; i++) अणु
		अगर (peer->app[i].valid)
			(*app_count)++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_dcb_peer_app_table(काष्ठा net_device *netdev,
				     काष्ठा dcb_app *table)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_dcb_cee *peer;
	काष्ठा qlcnic_dcb_app *app;
	पूर्णांक i, j;

	अगर (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		वापस 0;

	peer = &adapter->dcb->cfg->type[QLC_DCB_PEER_IDX];

	क्रम (i = 0, j = 0; i < QLC_DCB_MAX_APP; i++) अणु
		app = &peer->app[i];
		अगर (!app->valid)
			जारी;

		table[j].selector = app->selector;
		table[j].priority = app->priority;
		table[j++].protocol = app->protocol;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_dcb_cee_peer_get_pg(काष्ठा net_device *netdev,
				      काष्ठा cee_pg *pg)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_dcb_cee *peer;
	u8 i, j, k, map;

	अगर (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		वापस 0;

	peer = &adapter->dcb->cfg->type[QLC_DCB_PEER_IDX];

	क्रम (i = 0, j = 0; i < QLC_DCB_MAX_PG; i++) अणु
		अगर (!peer->pg_cfg[i].valid)
			जारी;

		pg->pg_bw[j] = peer->pg_cfg[i].total_bw_percent;

		क्रम (k = 0; k < QLC_DCB_MAX_TC; k++) अणु
			अगर (peer->tc_cfg[i].valid &&
			    (peer->tc_cfg[i].pgid == i)) अणु
				map = peer->tc_cfg[i].up_tc_map;
				pg->prio_pg[j++] = map;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_dcb_cee_peer_get_pfc(काष्ठा net_device *netdev,
				       काष्ठा cee_pfc *pfc)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_dcb_cfg *cfg = adapter->dcb->cfg;
	काष्ठा qlcnic_dcb_tc_cfg *tc;
	काष्ठा qlcnic_dcb_cee *peer;
	u8 i, setting, prio;

	pfc->pfc_en = 0;

	अगर (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		वापस 0;

	peer = &cfg->type[QLC_DCB_PEER_IDX];

	क्रम (i = 0; i < QLC_DCB_MAX_TC; i++) अणु
		tc = &peer->tc_cfg[i];
		prio = qlcnic_dcb_prio_count(tc->up_tc_map);

		setting = 0;
		qlcnic_dcb_get_pfc_cfg(netdev, prio, &setting);
		अगर (setting)
			pfc->pfc_en |= QLC_DCB_GET_MAP(i);
	पूर्ण

	pfc->tcs_supported = cfg->capability.max_pfc_tc;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dcbnl_rtnl_ops qlcnic_dcbnl_ops = अणु
	.माला_लोtate		= qlcnic_dcb_get_state,
	.getpermhwaddr		= qlcnic_dcb_get_perm_hw_addr,
	.getpgtccfgtx		= qlcnic_dcb_get_pg_tc_cfg_tx,
	.getpgbwgcfgtx		= qlcnic_dcb_get_pg_bwg_cfg_tx,
	.getpfccfg		= qlcnic_dcb_get_pfc_cfg,
	.अ_लोap			= qlcnic_dcb_get_capability,
	.getnumtcs		= qlcnic_dcb_get_num_tcs,
	.getapp			= qlcnic_dcb_get_app,
	.getpfcstate		= qlcnic_dcb_get_pfc_state,
	.getdcbx		= qlcnic_dcb_get_dcbx,
	.getfeatcfg		= qlcnic_dcb_get_feat_cfg,

	.getpgtccfgrx		= qlcnic_dcb_get_pg_tc_cfg_rx,
	.getpgbwgcfgrx		= qlcnic_dcb_get_pg_bwg_cfg_rx,

	.peer_getappinfo	= qlcnic_dcb_peer_app_info,
	.peer_getapptable	= qlcnic_dcb_peer_app_table,
	.cee_peer_getpg		= qlcnic_dcb_cee_peer_get_pg,
	.cee_peer_getpfc	= qlcnic_dcb_cee_peer_get_pfc,
पूर्ण;
