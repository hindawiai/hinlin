<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2018 NXP
 *   Dong Aisheng <aisheng.करोng@nxp.com>
 */

#समावेश <dt-bindings/firmware/imx/rsrc.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#समावेश "clk-scu.h"

#घोषणा IMX_SIP_CPUFREQ			0xC2000001
#घोषणा IMX_SIP_SET_CPUFREQ		0x00

अटल काष्ठा imx_sc_ipc *ccm_ipc_handle;
अटल काष्ठा device_node *pd_np;
अटल काष्ठा platक्रमm_driver imx_clk_scu_driver;

काष्ठा imx_scu_clk_node अणु
	स्थिर अक्षर *name;
	u32 rsrc;
	u8 clk_type;
	स्थिर अक्षर * स्थिर *parents;
	पूर्णांक num_parents;

	काष्ठा clk_hw *hw;
	काष्ठा list_head node;
पूर्ण;

काष्ठा list_head imx_scu_clks[IMX_SC_R_LAST];

/*
 * काष्ठा clk_scu - Description of one SCU घड़ी
 * @hw: the common clk_hw
 * @rsrc_id: resource ID of this SCU घड़ी
 * @clk_type: type of this घड़ी resource
 */
काष्ठा clk_scu अणु
	काष्ठा clk_hw hw;
	u16 rsrc_id;
	u8 clk_type;

	/* क्रम state save&restore */
	bool is_enabled;
	u32 rate;
पूर्ण;

/*
 * काष्ठा imx_sc_msg_req_set_घड़ी_rate - घड़ी set rate protocol
 * @hdr: SCU protocol header
 * @rate: rate to set
 * @resource: घड़ी resource to set rate
 * @clk: clk type of this resource
 *
 * This काष्ठाure describes the SCU protocol of घड़ी rate set
 */
काष्ठा imx_sc_msg_req_set_घड़ी_rate अणु
	काष्ठा imx_sc_rpc_msg hdr;
	__le32 rate;
	__le16 resource;
	u8 clk;
पूर्ण __packed __aligned(4);

काष्ठा req_get_घड़ी_rate अणु
	__le16 resource;
	u8 clk;
पूर्ण __packed __aligned(4);

काष्ठा resp_get_घड़ी_rate अणु
	__le32 rate;
पूर्ण;

/*
 * काष्ठा imx_sc_msg_get_घड़ी_rate - घड़ी get rate protocol
 * @hdr: SCU protocol header
 * @req: get rate request protocol
 * @resp: get rate response protocol
 *
 * This काष्ठाure describes the SCU protocol of घड़ी rate get
 */
काष्ठा imx_sc_msg_get_घड़ी_rate अणु
	काष्ठा imx_sc_rpc_msg hdr;
	जोड़ अणु
		काष्ठा req_get_घड़ी_rate req;
		काष्ठा resp_get_घड़ी_rate resp;
	पूर्ण data;
पूर्ण;

/*
 * काष्ठा imx_sc_msg_get_घड़ी_parent - घड़ी get parent protocol
 * @hdr: SCU protocol header
 * @req: get parent request protocol
 * @resp: get parent response protocol
 *
 * This काष्ठाure describes the SCU protocol of घड़ी get parent
 */
काष्ठा imx_sc_msg_get_घड़ी_parent अणु
	काष्ठा imx_sc_rpc_msg hdr;
	जोड़ अणु
		काष्ठा req_get_घड़ी_parent अणु
			__le16 resource;
			u8 clk;
		पूर्ण __packed __aligned(4) req;
		काष्ठा resp_get_घड़ी_parent अणु
			u8 parent;
		पूर्ण resp;
	पूर्ण data;
पूर्ण;

/*
 * काष्ठा imx_sc_msg_set_घड़ी_parent - घड़ी set parent protocol
 * @hdr: SCU protocol header
 * @req: set parent request protocol
 *
 * This काष्ठाure describes the SCU protocol of घड़ी set parent
 */
काष्ठा imx_sc_msg_set_घड़ी_parent अणु
	काष्ठा imx_sc_rpc_msg hdr;
	__le16 resource;
	u8 clk;
	u8 parent;
पूर्ण __packed;

/*
 * काष्ठा imx_sc_msg_req_घड़ी_enable - घड़ी gate protocol
 * @hdr: SCU protocol header
 * @resource: घड़ी resource to gate
 * @clk: clk type of this resource
 * @enable: whether gate off the घड़ी
 * @स्वतःg: HW स्वतः gate enable
 *
 * This काष्ठाure describes the SCU protocol of घड़ी gate
 */
काष्ठा imx_sc_msg_req_घड़ी_enable अणु
	काष्ठा imx_sc_rpc_msg hdr;
	__le16 resource;
	u8 clk;
	u8 enable;
	u8 स्वतःg;
पूर्ण __packed __aligned(4);

अटल अंतरभूत काष्ठा clk_scu *to_clk_scu(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा clk_scu, hw);
पूर्ण

पूर्णांक imx_clk_scu_init(काष्ठा device_node *np)
अणु
	u32 clk_cells;
	पूर्णांक ret, i;

	ret = imx_scu_get_handle(&ccm_ipc_handle);
	अगर (ret)
		वापस ret;

	of_property_पढ़ो_u32(np, "#clock-cells", &clk_cells);

	अगर (clk_cells == 2) अणु
		क्रम (i = 0; i < IMX_SC_R_LAST; i++)
			INIT_LIST_HEAD(&imx_scu_clks[i]);

		/* pd_np will be used to attach घातer करोमुख्यs later */
		pd_np = of_find_compatible_node(शून्य, शून्य, "fsl,scu-pd");
		अगर (!pd_np)
			वापस -EINVAL;
	पूर्ण

	वापस platक्रमm_driver_रेजिस्टर(&imx_clk_scu_driver);
पूर्ण

/*
 * clk_scu_recalc_rate - Get घड़ी rate क्रम a SCU घड़ी
 * @hw: घड़ी to get rate क्रम
 * @parent_rate: parent rate provided by common घड़ी framework, not used
 *
 * Gets the current घड़ी rate of a SCU घड़ी. Returns the current
 * घड़ी rate, or zero in failure.
 */
अटल अचिन्हित दीर्घ clk_scu_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_scu *clk = to_clk_scu(hw);
	काष्ठा imx_sc_msg_get_घड़ी_rate msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	पूर्णांक ret;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PM;
	hdr->func = IMX_SC_PM_FUNC_GET_CLOCK_RATE;
	hdr->size = 2;

	msg.data.req.resource = cpu_to_le16(clk->rsrc_id);
	msg.data.req.clk = clk->clk_type;

	ret = imx_scu_call_rpc(ccm_ipc_handle, &msg, true);
	अगर (ret) अणु
		pr_err("%s: failed to get clock rate %d\n",
		       clk_hw_get_name(hw), ret);
		वापस 0;
	पूर्ण

	वापस le32_to_cpu(msg.data.resp.rate);
पूर्ण

/*
 * clk_scu_round_rate - Round घड़ी rate क्रम a SCU घड़ी
 * @hw: घड़ी to round rate क्रम
 * @rate: rate to round
 * @parent_rate: parent rate provided by common घड़ी framework, not used
 *
 * Returns the current घड़ी rate, or zero in failure.
 */
अटल दीर्घ clk_scu_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate)
अणु
	/*
	 * Assume we support all the requested rate and let the SCU firmware
	 * to handle the left work
	 */
	वापस rate;
पूर्ण

अटल पूर्णांक clk_scu_atf_set_cpu_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_scu *clk = to_clk_scu(hw);
	काष्ठा arm_smccc_res res;
	अचिन्हित दीर्घ cluster_id;

	अगर (clk->rsrc_id == IMX_SC_R_A35)
		cluster_id = 0;
	अन्यथा
		वापस -EINVAL;

	/* CPU frequency scaling can ONLY be करोne by ARM-Trusted-Firmware */
	arm_smccc_smc(IMX_SIP_CPUFREQ, IMX_SIP_SET_CPUFREQ,
		      cluster_id, rate, 0, 0, 0, 0, &res);

	वापस 0;
पूर्ण

/*
 * clk_scu_set_rate - Set rate क्रम a SCU घड़ी
 * @hw: घड़ी to change rate क्रम
 * @rate: target rate क्रम the घड़ी
 * @parent_rate: rate of the घड़ी parent, not used क्रम SCU घड़ीs
 *
 * Sets a घड़ी frequency क्रम a SCU घड़ी. Returns the SCU
 * protocol status.
 */
अटल पूर्णांक clk_scu_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_scu *clk = to_clk_scu(hw);
	काष्ठा imx_sc_msg_req_set_घड़ी_rate msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PM;
	hdr->func = IMX_SC_PM_FUNC_SET_CLOCK_RATE;
	hdr->size = 3;

	msg.rate = cpu_to_le32(rate);
	msg.resource = cpu_to_le16(clk->rsrc_id);
	msg.clk = clk->clk_type;

	वापस imx_scu_call_rpc(ccm_ipc_handle, &msg, true);
पूर्ण

अटल u8 clk_scu_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_scu *clk = to_clk_scu(hw);
	काष्ठा imx_sc_msg_get_घड़ी_parent msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	पूर्णांक ret;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PM;
	hdr->func = IMX_SC_PM_FUNC_GET_CLOCK_PARENT;
	hdr->size = 2;

	msg.data.req.resource = cpu_to_le16(clk->rsrc_id);
	msg.data.req.clk = clk->clk_type;

	ret = imx_scu_call_rpc(ccm_ipc_handle, &msg, true);
	अगर (ret) अणु
		pr_err("%s: failed to get clock parent %d\n",
		       clk_hw_get_name(hw), ret);
		वापस 0;
	पूर्ण

	वापस msg.data.resp.parent;
पूर्ण

अटल पूर्णांक clk_scu_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_scu *clk = to_clk_scu(hw);
	काष्ठा imx_sc_msg_set_घड़ी_parent msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PM;
	hdr->func = IMX_SC_PM_FUNC_SET_CLOCK_PARENT;
	hdr->size = 2;

	msg.resource = cpu_to_le16(clk->rsrc_id);
	msg.clk = clk->clk_type;
	msg.parent = index;

	वापस imx_scu_call_rpc(ccm_ipc_handle, &msg, true);
पूर्ण

अटल पूर्णांक sc_pm_घड़ी_enable(काष्ठा imx_sc_ipc *ipc, u16 resource,
			      u8 clk, bool enable, bool स्वतःg)
अणु
	काष्ठा imx_sc_msg_req_घड़ी_enable msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PM;
	hdr->func = IMX_SC_PM_FUNC_CLOCK_ENABLE;
	hdr->size = 3;

	msg.resource = cpu_to_le16(resource);
	msg.clk = clk;
	msg.enable = enable;
	msg.स्वतःg = स्वतःg;

	वापस imx_scu_call_rpc(ccm_ipc_handle, &msg, true);
पूर्ण

/*
 * clk_scu_prepare - Enable a SCU घड़ी
 * @hw: घड़ी to enable
 *
 * Enable the घड़ी at the DSC slice level
 */
अटल पूर्णांक clk_scu_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_scu *clk = to_clk_scu(hw);

	वापस sc_pm_घड़ी_enable(ccm_ipc_handle, clk->rsrc_id,
				  clk->clk_type, true, false);
पूर्ण

/*
 * clk_scu_unprepare - Disable a SCU घड़ी
 * @hw: घड़ी to enable
 *
 * Disable the घड़ी at the DSC slice level
 */
अटल व्योम clk_scu_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_scu *clk = to_clk_scu(hw);
	पूर्णांक ret;

	ret = sc_pm_घड़ी_enable(ccm_ipc_handle, clk->rsrc_id,
				 clk->clk_type, false, false);
	अगर (ret)
		pr_warn("%s: clk unprepare failed %d\n", clk_hw_get_name(hw),
			ret);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_scu_ops = अणु
	.recalc_rate = clk_scu_recalc_rate,
	.round_rate = clk_scu_round_rate,
	.set_rate = clk_scu_set_rate,
	.get_parent = clk_scu_get_parent,
	.set_parent = clk_scu_set_parent,
	.prepare = clk_scu_prepare,
	.unprepare = clk_scu_unprepare,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_scu_cpu_ops = अणु
	.recalc_rate = clk_scu_recalc_rate,
	.round_rate = clk_scu_round_rate,
	.set_rate = clk_scu_atf_set_cpu_rate,
	.prepare = clk_scu_prepare,
	.unprepare = clk_scu_unprepare,
पूर्ण;

काष्ठा clk_hw *__imx_clk_scu(काष्ठा device *dev, स्थिर अक्षर *name,
			     स्थिर अक्षर * स्थिर *parents, पूर्णांक num_parents,
			     u32 rsrc_id, u8 clk_type)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk_scu *clk;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	clk = kzalloc(माप(*clk), GFP_KERNEL);
	अगर (!clk)
		वापस ERR_PTR(-ENOMEM);

	clk->rsrc_id = rsrc_id;
	clk->clk_type = clk_type;

	init.name = name;
	init.ops = &clk_scu_ops;
	अगर (rsrc_id == IMX_SC_R_A35)
		init.ops = &clk_scu_cpu_ops;
	अन्यथा
		init.ops = &clk_scu_ops;
	init.parent_names = parents;
	init.num_parents = num_parents;

	/*
	 * Note on MX8, the घड़ीs are tightly coupled with घातer करोमुख्य
	 * that once the घातer करोमुख्य is off, the घड़ी status may be
	 * lost. So we make it NOCACHE to let user to retrieve the real
	 * घड़ी status from HW instead of using the possible invalid
	 * cached rate.
	 */
	init.flags = CLK_GET_RATE_NOCACHE;
	clk->hw.init = &init;

	hw = &clk->hw;
	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		kमुक्त(clk);
		hw = ERR_PTR(ret);
		वापस hw;
	पूर्ण

	अगर (dev)
		dev_set_drvdata(dev, clk);

	वापस hw;
पूर्ण

काष्ठा clk_hw *imx_scu_of_clk_src_get(काष्ठा of_phandle_args *clkspec,
				      व्योम *data)
अणु
	अचिन्हित पूर्णांक rsrc = clkspec->args[0];
	अचिन्हित पूर्णांक idx = clkspec->args[1];
	काष्ठा list_head *scu_clks = data;
	काष्ठा imx_scu_clk_node *clk;

	list_क्रम_each_entry(clk, &scu_clks[rsrc], node) अणु
		अगर (clk->clk_type == idx)
			वापस clk->hw;
	पूर्ण

	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक imx_clk_scu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा imx_scu_clk_node *clk = dev_get_platdata(dev);
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	pm_runसमय_set_suspended(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, 50);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(dev);

	ret = pm_runसमय_get_sync(dev);
	अगर (ret) अणु
		pm_runसमय_disable(dev);
		वापस ret;
	पूर्ण

	hw = __imx_clk_scu(dev, clk->name, clk->parents, clk->num_parents,
			   clk->rsrc, clk->clk_type);
	अगर (IS_ERR(hw)) अणु
		pm_runसमय_disable(dev);
		वापस PTR_ERR(hw);
	पूर्ण

	clk->hw = hw;
	list_add_tail(&clk->node, &imx_scu_clks[clk->rsrc]);

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	dev_dbg(dev, "register SCU clock rsrc:%d type:%d\n", clk->rsrc,
		clk->clk_type);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_clk_scu_suspend(काष्ठा device *dev)
अणु
	काष्ठा clk_scu *clk = dev_get_drvdata(dev);

	clk->rate = clk_hw_get_rate(&clk->hw);
	clk->is_enabled = clk_hw_is_enabled(&clk->hw);

	अगर (clk->rate)
		dev_dbg(dev, "save rate %d\n", clk->rate);

	अगर (clk->is_enabled)
		dev_dbg(dev, "save enabled state\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_clk_scu_resume(काष्ठा device *dev)
अणु
	काष्ठा clk_scu *clk = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (clk->rate) अणु
		ret = clk_scu_set_rate(&clk->hw, clk->rate, 0);
		dev_dbg(dev, "restore rate %d %s\n", clk->rate,
			!ret ? "success" : "failed");
	पूर्ण

	अगर (clk->is_enabled) अणु
		ret = clk_scu_prepare(&clk->hw);
		dev_dbg(dev, "restore enabled state %s\n",
			!ret ? "success" : "failed");
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops imx_clk_scu_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(imx_clk_scu_suspend,
				      imx_clk_scu_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver imx_clk_scu_driver = अणु
	.driver = अणु
		.name = "imx-scu-clk",
		.suppress_bind_attrs = true,
		.pm = &imx_clk_scu_pm_ops,
	पूर्ण,
	.probe = imx_clk_scu_probe,
पूर्ण;

अटल पूर्णांक imx_clk_scu_attach_pd(काष्ठा device *dev, u32 rsrc_id)
अणु
	काष्ठा of_phandle_args genpdspec = अणु
		.np = pd_np,
		.args_count = 1,
		.args[0] = rsrc_id,
	पूर्ण;

	अगर (rsrc_id == IMX_SC_R_A35 || rsrc_id == IMX_SC_R_A53 ||
	    rsrc_id == IMX_SC_R_A72)
		वापस 0;

	वापस of_genpd_add_device(&genpdspec, dev);
पूर्ण

काष्ठा clk_hw *imx_clk_scu_alloc_dev(स्थिर अक्षर *name,
				     स्थिर अक्षर * स्थिर *parents,
				     पूर्णांक num_parents, u32 rsrc_id, u8 clk_type)
अणु
	काष्ठा imx_scu_clk_node clk = अणु
		.name = name,
		.rsrc = rsrc_id,
		.clk_type = clk_type,
		.parents = parents,
		.num_parents = num_parents,
	पूर्ण;
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	pdev = platक्रमm_device_alloc(name, PLATFORM_DEVID_NONE);
	अगर (!pdev) अणु
		pr_err("%s: failed to allocate scu clk dev rsrc %d type %d\n",
		       name, rsrc_id, clk_type);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	ret = platक्रमm_device_add_data(pdev, &clk, माप(clk));
	अगर (ret) अणु
		platक्रमm_device_put(pdev);
		वापस ERR_PTR(ret);
	पूर्ण

	pdev->driver_override = "imx-scu-clk";

	ret = imx_clk_scu_attach_pd(&pdev->dev, rsrc_id);
	अगर (ret)
		pr_warn("%s: failed to attached the power domain %d\n",
			name, ret);

	platक्रमm_device_add(pdev);

	/* For API backwards compatiblilty, simply वापस शून्य क्रम success */
	वापस शून्य;
पूर्ण

व्योम imx_clk_scu_unरेजिस्टर(व्योम)
अणु
	काष्ठा imx_scu_clk_node *clk;
	पूर्णांक i;

	क्रम (i = 0; i < IMX_SC_R_LAST; i++) अणु
		list_क्रम_each_entry(clk, &imx_scu_clks[i], node) अणु
			clk_hw_unरेजिस्टर(clk->hw);
			kमुक्त(clk);
		पूर्ण
	पूर्ण
पूर्ण
