<शैली गुरु>
/*
 * OMAP L3 Interconnect error handling driver
 *
 * Copyright (C) 2011-2015 Texas Instruments Incorporated - http://www.ti.com/
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 *	Sriअक्षरan <r.sriअक्षरan@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "omap_l3_noc.h"

/**
 * l3_handle_target() - Handle Target specअगरic parse and reporting
 * @l3:		poपूर्णांकer to l3 काष्ठा
 * @base:	base address of clkdm
 * @flag_mux:	flagmux corresponding to the event
 * @err_src:	error source index of the slave (target)
 *
 * This करोes the second part of the error पूर्णांकerrupt handling:
 *	3) Parse in the slave inक्रमmation
 *	4) Prपूर्णांक the logged inक्रमmation.
 *	5) Add dump stack to provide kernel trace.
 *	6) Clear the source अगर known.
 *
 * This handles two types of errors:
 *	1) Custom errors in L3 :
 *		Target like DMM/FW/EMIF generates SRESP=ERR error
 *	2) Standard L3 error:
 *		- Unsupported CMD.
 *			L3 tries to access target जबतक it is idle
 *		- OCP disconnect.
 *		- Address hole error:
 *			If DSS/ISS/FDIF/USBHOSTFS access a target where they
 *			करो not have connectivity, the error is logged in
 *			their शेष target which is DMM2.
 *
 *	On High Secure devices, firewall errors are possible and those
 *	can be trapped as well. But the trapping is implemented as part
 *	secure software and hence need not be implemented here.
 */
अटल पूर्णांक l3_handle_target(काष्ठा omap_l3 *l3, व्योम __iomem *base,
			    काष्ठा l3_flagmux_data *flag_mux, पूर्णांक err_src)
अणु
	पूर्णांक k;
	u32 std_err_मुख्य, clear, masterid;
	u8 op_code, m_req_info;
	व्योम __iomem *l3_targ_base;
	व्योम __iomem *l3_targ_मानक_त्रुटि, *l3_targ_slvofslsb, *l3_targ_mstaddr;
	व्योम __iomem *l3_targ_hdr, *l3_targ_info;
	काष्ठा l3_target_data *l3_targ_inst;
	काष्ठा l3_masters_data *master;
	अक्षर *target_name, *master_name = "UN IDENTIFIED";
	अक्षर *err_description;
	अक्षर err_string[30] = अणु 0 पूर्ण;
	अक्षर info_string[60] = अणु 0 पूर्ण;

	/* We DONOT expect err_src to go out of bounds */
	BUG_ON(err_src > MAX_CLKDM_TARGETS);

	अगर (err_src < flag_mux->num_targ_data) अणु
		l3_targ_inst = &flag_mux->l3_targ[err_src];
		target_name = l3_targ_inst->name;
		l3_targ_base = base + l3_targ_inst->offset;
	पूर्ण अन्यथा अणु
		target_name = L3_TARGET_NOT_SUPPORTED;
	पूर्ण

	अगर (target_name == L3_TARGET_NOT_SUPPORTED)
		वापस -ENODEV;

	/* Read the मानक_त्रुटिlog_मुख्य_source from clk करोमुख्य */
	l3_targ_मानक_त्रुटि = l3_targ_base + L3_TARG_STDERRLOG_MAIN;
	l3_targ_slvofslsb = l3_targ_base + L3_TARG_STDERRLOG_SLVOFSLSB;

	std_err_मुख्य = पढ़ोl_relaxed(l3_targ_मानक_त्रुटि);

	चयन (std_err_मुख्य & CUSTOM_ERROR) अणु
	हाल STANDARD_ERROR:
		err_description = "Standard";
		snम_लिखो(err_string, माप(err_string),
			 ": At Address: 0x%08X ",
			 पढ़ोl_relaxed(l3_targ_slvofslsb));

		l3_targ_mstaddr = l3_targ_base + L3_TARG_STDERRLOG_MSTADDR;
		l3_targ_hdr = l3_targ_base + L3_TARG_STDERRLOG_HDR;
		l3_targ_info = l3_targ_base + L3_TARG_STDERRLOG_INFO;
		अवरोध;

	हाल CUSTOM_ERROR:
		err_description = "Custom";

		l3_targ_mstaddr = l3_targ_base +
				  L3_TARG_STDERRLOG_CINFO_MSTADDR;
		l3_targ_hdr = l3_targ_base + L3_TARG_STDERRLOG_CINFO_OPCODE;
		l3_targ_info = l3_targ_base + L3_TARG_STDERRLOG_CINFO_INFO;
		अवरोध;

	शेष:
		/* Nothing to be handled here as of now */
		वापस 0;
	पूर्ण

	/* STDERRLOG_MSTADDR Stores the NTTP master address. */
	masterid = (पढ़ोl_relaxed(l3_targ_mstaddr) &
		    l3->mst_addr_mask) >> __ffs(l3->mst_addr_mask);

	क्रम (k = 0, master = l3->l3_masters; k < l3->num_masters;
	     k++, master++) अणु
		अगर (masterid == master->id) अणु
			master_name = master->name;
			अवरोध;
		पूर्ण
	पूर्ण

	op_code = पढ़ोl_relaxed(l3_targ_hdr) & 0x7;

	m_req_info = पढ़ोl_relaxed(l3_targ_info) & 0xF;
	snम_लिखो(info_string, माप(info_string),
		 ": %s in %s mode during %s access",
		 (m_req_info & BIT(0)) ? "Opcode Fetch" : "Data Access",
		 (m_req_info & BIT(1)) ? "Supervisor" : "User",
		 (m_req_info & BIT(3)) ? "Debug" : "Functional");

	WARN(true,
	     "%s:L3 %s Error: MASTER %s TARGET %s (%s)%s%s\n",
	     dev_name(l3->dev),
	     err_description,
	     master_name, target_name,
	     l3_transaction_type[op_code],
	     err_string, info_string);

	/* clear the std error log*/
	clear = std_err_मुख्य | CLEAR_STDERR_LOG;
	ग_लिखोl_relaxed(clear, l3_targ_मानक_त्रुटि);

	वापस 0;
पूर्ण

/**
 * l3_पूर्णांकerrupt_handler() - पूर्णांकerrupt handler क्रम l3 events
 * @irq:	irq number
 * @_l3:	poपूर्णांकer to l3 काष्ठाure
 *
 * Interrupt Handler क्रम L3 error detection.
 *	1) Identअगरy the L3 घड़ीकरोमुख्य partition to which the error beदीर्घs to.
 *	2) Identअगरy the slave where the error inक्रमmation is logged
 *	... handle the slave event..
 *	7) अगर the slave is unknown, mask out the slave.
 */
अटल irqवापस_t l3_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *_l3)
अणु
	काष्ठा omap_l3 *l3 = _l3;
	पूर्णांक पूर्णांकtype, i, ret;
	पूर्णांक err_src = 0;
	u32 err_reg, mask_val;
	व्योम __iomem *base, *mask_reg;
	काष्ठा l3_flagmux_data *flag_mux;

	/* Get the Type of पूर्णांकerrupt */
	पूर्णांकtype = irq == l3->app_irq ? L3_APPLICATION_ERROR : L3_DEBUG_ERROR;

	क्रम (i = 0; i < l3->num_modules; i++) अणु
		/*
		 * Read the regerr रेजिस्टर of the घड़ी करोमुख्य
		 * to determine the source
		 */
		base = l3->l3_base[i];
		flag_mux = l3->l3_flagmux[i];
		err_reg = पढ़ोl_relaxed(base + flag_mux->offset +
					L3_FLAGMUX_REGERR0 + (पूर्णांकtype << 3));

		err_reg &= ~(पूर्णांकtype ? flag_mux->mask_app_bits :
				flag_mux->mask_dbg_bits);

		/* Get the corresponding error and analyse */
		अगर (err_reg) अणु
			/* Identअगरy the source from control status रेजिस्टर */
			err_src = __ffs(err_reg);

			ret = l3_handle_target(l3, base, flag_mux, err_src);

			/*
			 * Certain plaक्रमms may have "undocumented" status
			 * pending on boot. So करोnt generate a severe warning
			 * here. Just mask it off to prevent the error from
			 * reoccuring and locking up the प्रणाली.
			 */
			अगर (ret) अणु
				dev_err(l3->dev,
					"L3 %s error: target %d mod:%d %s\n",
					पूर्णांकtype ? "debug" : "application",
					err_src, i, "(unclearable)");

				mask_reg = base + flag_mux->offset +
					   L3_FLAGMUX_MASK0 + (पूर्णांकtype << 3);
				mask_val = पढ़ोl_relaxed(mask_reg);
				mask_val &= ~(1 << err_src);
				ग_लिखोl_relaxed(mask_val, mask_reg);

				/* Mark these bits as to be ignored */
				अगर (पूर्णांकtype)
					flag_mux->mask_app_bits |= 1 << err_src;
				अन्यथा
					flag_mux->mask_dbg_bits |= 1 << err_src;
			पूर्ण

			/* Error found so अवरोध the क्रम loop */
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण

	dev_err(l3->dev, "L3 %s IRQ not handled!!\n",
		पूर्णांकtype ? "debug" : "application");

	वापस IRQ_NONE;
पूर्ण

अटल स्थिर काष्ठा of_device_id l3_noc_match[] = अणु
	अणु.compatible = "ti,omap4-l3-noc", .data = &omap4_l3_dataपूर्ण,
	अणु.compatible = "ti,omap5-l3-noc", .data = &omap5_l3_dataपूर्ण,
	अणु.compatible = "ti,dra7-l3-noc", .data = &dra_l3_dataपूर्ण,
	अणु.compatible = "ti,am4372-l3-noc", .data = &am4372_l3_dataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, l3_noc_match);

अटल पूर्णांक omap_l3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	अटल काष्ठा omap_l3 *l3;
	पूर्णांक ret, i, res_idx;

	of_id = of_match_device(l3_noc_match, &pdev->dev);
	अगर (!of_id) अणु
		dev_err(&pdev->dev, "OF data missing\n");
		वापस -EINVAL;
	पूर्ण

	l3 = devm_kzalloc(&pdev->dev, माप(*l3), GFP_KERNEL);
	अगर (!l3)
		वापस -ENOMEM;

	स_नकल(l3, of_id->data, माप(*l3));
	l3->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, l3);

	/* Get mem resources */
	क्रम (i = 0, res_idx = 0; i < l3->num_modules; i++) अणु
		काष्ठा resource	*res;

		अगर (l3->l3_base[i] == L3_BASE_IS_SUBMODULE) अणु
			/* First entry cannot be submodule */
			BUG_ON(i == 0);
			l3->l3_base[i] = l3->l3_base[i - 1];
			जारी;
		पूर्ण
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, res_idx);
		l3->l3_base[i] = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(l3->l3_base[i])) अणु
			dev_err(l3->dev, "ioremap %d failed\n", i);
			वापस PTR_ERR(l3->l3_base[i]);
		पूर्ण
		res_idx++;
	पूर्ण

	/*
	 * Setup पूर्णांकerrupt Handlers
	 */
	l3->debug_irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_irq(l3->dev, l3->debug_irq, l3_पूर्णांकerrupt_handler,
			       IRQF_NO_THREAD, "l3-dbg-irq", l3);
	अगर (ret) अणु
		dev_err(l3->dev, "request_irq failed for %d\n",
			l3->debug_irq);
		वापस ret;
	पूर्ण

	l3->app_irq = platक्रमm_get_irq(pdev, 1);
	ret = devm_request_irq(l3->dev, l3->app_irq, l3_पूर्णांकerrupt_handler,
			       IRQF_NO_THREAD, "l3-app-irq", l3);
	अगर (ret)
		dev_err(l3->dev, "request_irq failed for %d\n", l3->app_irq);

	वापस ret;
पूर्ण

#अगर_घोषित	CONFIG_PM_SLEEP

/**
 * l3_resume_noirq() - resume function क्रम l3_noc
 * @dev:	poपूर्णांकer to l3_noc device काष्ठाure
 *
 * We only have the resume handler only since we
 * have alपढ़ोy मुख्यtained the delta रेजिस्टर
 * configuration as part of configuring the प्रणाली
 */
अटल पूर्णांक l3_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा omap_l3 *l3 = dev_get_drvdata(dev);
	पूर्णांक i;
	काष्ठा l3_flagmux_data *flag_mux;
	व्योम __iomem *base, *mask_regx = शून्य;
	u32 mask_val;

	क्रम (i = 0; i < l3->num_modules; i++) अणु
		base = l3->l3_base[i];
		flag_mux = l3->l3_flagmux[i];
		अगर (!flag_mux->mask_app_bits && !flag_mux->mask_dbg_bits)
			जारी;

		mask_regx = base + flag_mux->offset + L3_FLAGMUX_MASK0 +
			   (L3_APPLICATION_ERROR << 3);
		mask_val = पढ़ोl_relaxed(mask_regx);
		mask_val &= ~(flag_mux->mask_app_bits);

		ग_लिखोl_relaxed(mask_val, mask_regx);
		mask_regx = base + flag_mux->offset + L3_FLAGMUX_MASK0 +
			   (L3_DEBUG_ERROR << 3);
		mask_val = पढ़ोl_relaxed(mask_regx);
		mask_val &= ~(flag_mux->mask_dbg_bits);

		ग_लिखोl_relaxed(mask_val, mask_regx);
	पूर्ण

	/* Dummy पढ़ो to क्रमce OCP barrier */
	अगर (mask_regx)
		(व्योम)पढ़ोl(mask_regx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops l3_dev_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(शून्य, l3_resume_noirq)
पूर्ण;

#घोषणा L3_DEV_PM_OPS (&l3_dev_pm_ops)
#अन्यथा
#घोषणा L3_DEV_PM_OPS शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver omap_l3_driver = अणु
	.probe		= omap_l3_probe,
	.driver		= अणु
		.name		= "omap_l3_noc",
		.pm		= L3_DEV_PM_OPS,
		.of_match_table = of_match_ptr(l3_noc_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init omap_l3_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omap_l3_driver);
पूर्ण
postcore_initcall_sync(omap_l3_init);

अटल व्योम __निकास omap_l3_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_l3_driver);
पूर्ण
module_निकास(omap_l3_निकास);

MODULE_AUTHOR("Santosh Shilimkar");
MODULE_AUTHOR("Sricharan R");
MODULE_DESCRIPTION("OMAP L3 Interconnect error handling driver");
MODULE_LICENSE("GPL v2");
