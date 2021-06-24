<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2018 NXP.
 */

#समावेश <dt-bindings/firmware/imx/rsrc.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/firmware/imx/sci.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

#घोषणा IMX_SC_TIMER_FUNC_GET_RTC_SEC1970	9
#घोषणा IMX_SC_TIMER_FUNC_SET_RTC_ALARM		8
#घोषणा IMX_SC_TIMER_FUNC_SET_RTC_TIME		6

#घोषणा IMX_SIP_SRTC			0xC2000002
#घोषणा IMX_SIP_SRTC_SET_TIME		0x0

#घोषणा SC_IRQ_GROUP_RTC    2
#घोषणा SC_IRQ_RTC          1

अटल काष्ठा imx_sc_ipc *rtc_ipc_handle;
अटल काष्ठा rtc_device *imx_sc_rtc;

काष्ठा imx_sc_msg_समयr_get_rtc_समय अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u32 समय;
पूर्ण __packed;

काष्ठा imx_sc_msg_समयr_rtc_set_alarm अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u16 year;
	u8 mon;
	u8 day;
	u8 hour;
	u8 min;
	u8 sec;
पूर्ण __packed __aligned(4);

अटल पूर्णांक imx_sc_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा imx_sc_msg_समयr_get_rtc_समय msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	पूर्णांक ret;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_TIMER;
	hdr->func = IMX_SC_TIMER_FUNC_GET_RTC_SEC1970;
	hdr->size = 1;

	ret = imx_scu_call_rpc(rtc_ipc_handle, &msg, true);
	अगर (ret) अणु
		dev_err(dev, "read rtc time failed, ret %d\n", ret);
		वापस ret;
	पूर्ण

	rtc_समय64_to_पंचांग(msg.समय, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_sc_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा arm_smccc_res res;

	/* pack 2 समय parameters पूर्णांकo 1 रेजिस्टर, 16 bits क्रम each */
	arm_smccc_smc(IMX_SIP_SRTC, IMX_SIP_SRTC_SET_TIME,
		      ((पंचांग->पंचांग_year + 1900) << 16) | (पंचांग->पंचांग_mon + 1),
		      (पंचांग->पंचांग_mday << 16) | पंचांग->पंचांग_hour,
		      (पंचांग->पंचांग_min << 16) | पंचांग->पंचांग_sec,
		      0, 0, 0, &res);

	वापस res.a0;
पूर्ण

अटल पूर्णांक imx_sc_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enable)
अणु
	वापस imx_scu_irq_group_enable(SC_IRQ_GROUP_RTC, SC_IRQ_RTC, enable);
पूर्ण

अटल पूर्णांक imx_sc_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा imx_sc_msg_समयr_rtc_set_alarm msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	पूर्णांक ret;
	काष्ठा rtc_समय *alrm_पंचांग = &alrm->समय;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_TIMER;
	hdr->func = IMX_SC_TIMER_FUNC_SET_RTC_ALARM;
	hdr->size = 3;

	msg.year = alrm_पंचांग->पंचांग_year + 1900;
	msg.mon = alrm_पंचांग->पंचांग_mon + 1;
	msg.day = alrm_पंचांग->पंचांग_mday;
	msg.hour = alrm_पंचांग->पंचांग_hour;
	msg.min = alrm_पंचांग->पंचांग_min;
	msg.sec = alrm_पंचांग->पंचांग_sec;

	ret = imx_scu_call_rpc(rtc_ipc_handle, &msg, true);
	अगर (ret) अणु
		dev_err(dev, "set rtc alarm failed, ret %d\n", ret);
		वापस ret;
	पूर्ण

	ret = imx_sc_rtc_alarm_irq_enable(dev, alrm->enabled);
	अगर (ret) अणु
		dev_err(dev, "enable rtc alarm failed, ret %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops imx_sc_rtc_ops = अणु
	.पढ़ो_समय = imx_sc_rtc_पढ़ो_समय,
	.set_समय = imx_sc_rtc_set_समय,
	.set_alarm = imx_sc_rtc_set_alarm,
	.alarm_irq_enable = imx_sc_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक imx_sc_rtc_alarm_notअगरy(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ event, व्योम *group)
अणु
	/* ignore non-rtc irq */
	अगर (!((event & SC_IRQ_RTC) && (*(u8 *)group == SC_IRQ_GROUP_RTC)))
		वापस 0;

	rtc_update_irq(imx_sc_rtc, 1, RTC_IRQF | RTC_AF);

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block imx_sc_rtc_alarm_sc_notअगरier = अणु
	.notअगरier_call = imx_sc_rtc_alarm_notअगरy,
पूर्ण;

अटल पूर्णांक imx_sc_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = imx_scu_get_handle(&rtc_ipc_handle);
	अगर (ret)
		वापस ret;

	device_init_wakeup(&pdev->dev, true);

	imx_sc_rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(imx_sc_rtc))
		वापस PTR_ERR(imx_sc_rtc);

	imx_sc_rtc->ops = &imx_sc_rtc_ops;
	imx_sc_rtc->range_min = 0;
	imx_sc_rtc->range_max = U32_MAX;

	ret = devm_rtc_रेजिस्टर_device(imx_sc_rtc);
	अगर (ret)
		वापस ret;

	imx_scu_irq_रेजिस्टर_notअगरier(&imx_sc_rtc_alarm_sc_notअगरier);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_sc_dt_ids[] = अणु
	अणु .compatible = "fsl,imx8qxp-sc-rtc", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_sc_dt_ids);

अटल काष्ठा platक्रमm_driver imx_sc_rtc_driver = अणु
	.driver = अणु
		.name	= "imx-sc-rtc",
		.of_match_table = imx_sc_dt_ids,
	पूर्ण,
	.probe		= imx_sc_rtc_probe,
पूर्ण;
module_platक्रमm_driver(imx_sc_rtc_driver);

MODULE_AUTHOR("Anson Huang <Anson.Huang@nxp.com>");
MODULE_DESCRIPTION("NXP i.MX System Controller RTC Driver");
MODULE_LICENSE("GPL");
