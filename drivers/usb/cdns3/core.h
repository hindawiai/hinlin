<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Cadence USBSS and USBSSP DRD Header File.
 *
 * Copyright (C) 2017-2018 NXP
 * Copyright (C) 2018-2019 Cadence.
 *
 * Authors: Peter Chen <peter.chen@nxp.com>
 *          Pawel Laszczak <pawell@cadence.com>
 */
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/role.h>

#अगर_अघोषित __LINUX_CDNS3_CORE_H
#घोषणा __LINUX_CDNS3_CORE_H

काष्ठा cdns;

/**
 * काष्ठा cdns_role_driver - host/gadget role driver
 * @start: start this role
 * @stop: stop this role
 * @suspend: suspend callback क्रम this role
 * @resume: resume callback क्रम this role
 * @irq: irq handler क्रम this role
 * @name: role name string (host/gadget)
 * @state: current state
 */
काष्ठा cdns_role_driver अणु
	पूर्णांक (*start)(काष्ठा cdns *cdns);
	व्योम (*stop)(काष्ठा cdns *cdns);
	पूर्णांक (*suspend)(काष्ठा cdns *cdns, bool करो_wakeup);
	पूर्णांक (*resume)(काष्ठा cdns *cdns, bool hibernated);
	स्थिर अक्षर *name;
#घोषणा CDNS_ROLE_STATE_INACTIVE	0
#घोषणा CDNS_ROLE_STATE_ACTIVE		1
	पूर्णांक state;
पूर्ण;

#घोषणा CDNS_XHCI_RESOURCES_NUM	2

काष्ठा cdns3_platक्रमm_data अणु
	पूर्णांक (*platक्रमm_suspend)(काष्ठा device *dev,
			bool suspend, bool wakeup);
	अचिन्हित दीर्घ quirks;
#घोषणा CDNS3_DEFAULT_PM_RUNTIME_ALLOW	BIT(0)
पूर्ण;

/**
 * काष्ठा cdns - Representation of Cadence USB3 DRD controller.
 * @dev: poपूर्णांकer to Cadence device काष्ठा
 * @xhci_regs: poपूर्णांकer to base of xhci रेजिस्टरs
 * @xhci_res: the resource क्रम xhci
 * @dev_regs: poपूर्णांकer to base of dev रेजिस्टरs
 * @otg_res: the resource क्रम otg
 * @otg_v0_regs: poपूर्णांकer to base of v0 otg रेजिस्टरs
 * @otg_v1_regs: poपूर्णांकer to base of v1 otg रेजिस्टरs
 * @otg_cdnsp_regs: poपूर्णांकer to base of CDNSP otg रेजिस्टरs
 * @otg_regs: poपूर्णांकer to base of otg रेजिस्टरs
 * @otg_irq_regs: poपूर्णांकer to पूर्णांकerrupt रेजिस्टरs
 * @otg_irq: irq number क्रम otg controller
 * @dev_irq: irq number क्रम device controller
 * @wakeup_irq: irq number क्रम wakeup event, it is optional
 * @roles: array of supported roles क्रम this controller
 * @role: current role
 * @host_dev: the child host device poपूर्णांकer क्रम cdns core
 * @gadget_dev: the child gadget device poपूर्णांकer
 * @usb2_phy: poपूर्णांकer to USB2 PHY
 * @usb3_phy: poपूर्णांकer to USB3 PHY
 * @mutex: the mutex क्रम concurrent code at driver
 * @dr_mode: supported mode of operation it can be only Host, only Device
 *           or OTG mode that allow to चयन between Device and Host mode.
 *           This field based on firmware setting, kernel configuration
 *           and hardware configuration.
 * @role_sw: poपूर्णांकer to role चयन object.
 * @in_lpm: indicate the controller is in low घातer mode
 * @wakeup_pending: wakeup पूर्णांकerrupt pending
 * @pdata: platक्रमm data from glue layer
 * @lock: spinlock काष्ठाure
 * @xhci_plat_data: xhci निजी data काष्ठाure poपूर्णांकer
 * @gadget_init: poपूर्णांकer to gadget initialization function
 */
काष्ठा cdns अणु
	काष्ठा device			*dev;
	व्योम __iomem			*xhci_regs;
	काष्ठा resource			xhci_res[CDNS_XHCI_RESOURCES_NUM];
	काष्ठा cdns3_usb_regs __iomem	*dev_regs;

	काष्ठा resource				otg_res;
	काष्ठा cdns3_otg_legacy_regs __iomem	*otg_v0_regs;
	काष्ठा cdns3_otg_regs __iomem		*otg_v1_regs;
	काष्ठा cdnsp_otg_regs __iomem		*otg_cdnsp_regs;
	काष्ठा cdns_otg_common_regs __iomem	*otg_regs;
	काष्ठा cdns_otg_irq_regs __iomem	*otg_irq_regs;
#घोषणा CDNS3_CONTROLLER_V0	0
#घोषणा CDNS3_CONTROLLER_V1	1
#घोषणा CDNSP_CONTROLLER_V2	2
	u32				version;
	bool				phyrst_a_enable;

	पूर्णांक				otg_irq;
	पूर्णांक				dev_irq;
	पूर्णांक				wakeup_irq;
	काष्ठा cdns_role_driver	*roles[USB_ROLE_DEVICE + 1];
	क्रमागत usb_role			role;
	काष्ठा platक्रमm_device		*host_dev;
	व्योम				*gadget_dev;
	काष्ठा phy			*usb2_phy;
	काष्ठा phy			*usb3_phy;
	/* mutext used in workqueue*/
	काष्ठा mutex			mutex;
	क्रमागत usb_dr_mode		dr_mode;
	काष्ठा usb_role_चयन		*role_sw;
	bool				in_lpm;
	bool				wakeup_pending;
	काष्ठा cdns3_platक्रमm_data	*pdata;
	spinlock_t			lock;
	काष्ठा xhci_plat_priv		*xhci_plat_data;

	पूर्णांक (*gadget_init)(काष्ठा cdns *cdns);
पूर्ण;

पूर्णांक cdns_hw_role_चयन(काष्ठा cdns *cdns);
पूर्णांक cdns_init(काष्ठा cdns *cdns);
पूर्णांक cdns_हटाओ(काष्ठा cdns *cdns);

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक cdns_resume(काष्ठा cdns *cdns, u8 set_active);
पूर्णांक cdns_suspend(काष्ठा cdns *cdns);
#अन्यथा /* CONFIG_PM_SLEEP */
अटल अंतरभूत पूर्णांक cdns_resume(काष्ठा cdns *cdns, u8 set_active)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक cdns_suspend(काष्ठा cdns *cdns)
अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */
#पूर्ण_अगर /* __LINUX_CDNS3_CORE_H */
