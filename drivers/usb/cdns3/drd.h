<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Cadence USB3 and USBSSP DRD header file.
 *
 * Copyright (C) 2018-2020 Cadence.
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 */
#अगर_अघोषित __LINUX_CDNS3_DRD
#घोषणा __LINUX_CDNS3_DRD

#समावेश <linux/usb/otg.h>
#समावेश "core.h"

/*  DRD रेजिस्टर पूर्णांकerface क्रम version v1 of cdns3 driver. */
काष्ठा cdns3_otg_regs अणु
	__le32 did;
	__le32 rid;
	__le32 capabilities;
	__le32 reserved1;
	__le32 cmd;
	__le32 sts;
	__le32 state;
	__le32 reserved2;
	__le32 ien;
	__le32 ivect;
	__le32 refclk;
	__le32 पंचांगr;
	__le32 reserved3[4];
	__le32 simulate;
	__le32 override;
	__le32 susp_ctrl;
	__le32 phyrst_cfg;
	__le32 anasts;
	__le32 adp_ramp_समय;
	__le32 ctrl1;
	__le32 ctrl2;
पूर्ण;

/*  DRD रेजिस्टर पूर्णांकerface क्रम version v0 of cdns3 driver. */
काष्ठा cdns3_otg_legacy_regs अणु
	__le32 cmd;
	__le32 sts;
	__le32 state;
	__le32 refclk;
	__le32 ien;
	__le32 ivect;
	__le32 reserved1[3];
	__le32 पंचांगr;
	__le32 reserved2[2];
	__le32 version;
	__le32 capabilities;
	__le32 reserved3[2];
	__le32 simulate;
	__le32 reserved4[5];
	__le32 ctrl1;
पूर्ण;

/* DRD रेजिस्टर पूर्णांकerface क्रम cdnsp driver */
काष्ठा cdnsp_otg_regs अणु
	__le32 did;
	__le32 rid;
	__le32 cfgs1;
	__le32 cfgs2;
	__le32 cmd;
	__le32 sts;
	__le32 state;
	__le32 ien;
	__le32 ivect;
	__le32 पंचांगr;
	__le32 simulate;
	__le32 adpbc_sts;
	__le32 adp_ramp_समय;
	__le32 adpbc_ctrl1;
	__le32 adpbc_ctrl2;
	__le32 override;
	__le32 vbusvalid_dbnc_cfg;
	__le32 sessvalid_dbnc_cfg;
	__le32 susp_timing_ctrl;
पूर्ण;

#घोषणा OTG_CDNSP_DID	0x0004034E

/*
 * Common रेजिस्टरs पूर्णांकerface क्रम both CDNS3 and CDNSP version of DRD.
 */
काष्ठा cdns_otg_common_regs अणु
	__le32 cmd;
	__le32 sts;
	__le32 state;
पूर्ण;

/*
 * Interrupt related रेजिस्टरs. This रेजिस्टरs are mapped in dअगरferent
 * location क्रम CDNSP controller.
 */
काष्ठा cdns_otg_irq_regs अणु
	__le32 ien;
	__le32 ivect;
पूर्ण;

/* CDNS_RID - biपंचांगasks */
#घोषणा CDNS_RID(p)			((p) & GENMASK(15, 0))

/* CDNS_VID - biपंचांगasks */
#घोषणा CDNS_DID(p)			((p) & GENMASK(31, 0))

/* OTGCMD - biपंचांगasks */
/* "Request the bus क्रम Device mode. */
#घोषणा OTGCMD_DEV_BUS_REQ		BIT(0)
/* Request the bus क्रम Host mode */
#घोषणा OTGCMD_HOST_BUS_REQ		BIT(1)
/* Enable OTG mode. */
#घोषणा OTGCMD_OTG_EN			BIT(2)
/* Disable OTG mode */
#घोषणा OTGCMD_OTG_DIS			BIT(3)
/*"Configure OTG as A-Device. */
#घोषणा OTGCMD_A_DEV_EN			BIT(4)
/*"Configure OTG as A-Device. */
#घोषणा OTGCMD_A_DEV_DIS		BIT(5)
/* Drop the bus क्रम Device mod	e. */
#घोषणा OTGCMD_DEV_BUS_DROP		BIT(8)
/* Drop the bus क्रम Host mode*/
#घोषणा OTGCMD_HOST_BUS_DROP		BIT(9)
/* Power Down USBSS-DEV - only क्रम CDNS3.*/
#घोषणा OTGCMD_DEV_POWER_OFF		BIT(11)
/* Power Down CDNSXHCI - only क्रम CDNS3. */
#घोषणा OTGCMD_HOST_POWER_OFF		BIT(12)

/* OTGIEN - biपंचांगasks */
/* ID change पूर्णांकerrupt enable */
#घोषणा OTGIEN_ID_CHANGE_INT		BIT(0)
/* Vbusvalid fall detected पूर्णांकerrupt enable.*/
#घोषणा OTGIEN_VBUSVALID_RISE_INT	BIT(4)
/* Vbusvalid fall detected पूर्णांकerrupt enable */
#घोषणा OTGIEN_VBUSVALID_FALL_INT	BIT(5)

/* OTGSTS - biपंचांगasks */
/*
 * Current value of the ID pin. It is only valid when idpullup in
 *  OTGCTRL1_TYPE रेजिस्टर is set to '1'.
 */
#घोषणा OTGSTS_ID_VALUE			BIT(0)
/* Current value of the vbus_valid */
#घोषणा OTGSTS_VBUS_VALID		BIT(1)
/* Current value of the b_sess_vld */
#घोषणा OTGSTS_SESSION_VALID		BIT(2)
/*Device mode is active*/
#घोषणा OTGSTS_DEV_ACTIVE		BIT(3)
/* Host mode is active. */
#घोषणा OTGSTS_HOST_ACTIVE		BIT(4)
/* OTG Controller not पढ़ोy. */
#घोषणा OTGSTS_OTG_NRDY_MASK		BIT(11)
#घोषणा OTGSTS_OTG_NRDY(p)		((p) & OTGSTS_OTG_NRDY_MASK)
/*
 * Value of the strap pins क्रम:
 * CDNS3:
 * 000 - no शेष configuration
 * 010 - Controller initiall configured as Host
 * 100 - Controller initially configured as Device
 * CDNSP:
 * 000 - No शेष configuration.
 * 010 - Controller initiall configured as Host.
 * 100 - Controller initially configured as Device.
 */
#घोषणा OTGSTS_STRAP(p)			(((p) & GENMASK(14, 12)) >> 12)
#घोषणा OTGSTS_STRAP_NO_DEFAULT_CFG	0x00
#घोषणा OTGSTS_STRAP_HOST_OTG		0x01
#घोषणा OTGSTS_STRAP_HOST		0x02
#घोषणा OTGSTS_STRAP_GADGET		0x04
#घोषणा OTGSTS_CDNSP_STRAP_HOST		0x01
#घोषणा OTGSTS_CDNSP_STRAP_GADGET	0x02

/* Host mode is turned on. */
#घोषणा OTGSTS_CDNS3_XHCI_READY		BIT(26)
#घोषणा OTGSTS_CDNSP_XHCI_READY		BIT(27)

/* "Device mode is turned on .*/
#घोषणा OTGSTS_CDNS3_DEV_READY		BIT(27)
#घोषणा OTGSTS_CDNSP_DEV_READY		BIT(26)

/* OTGSTATE- biपंचांगasks */
#घोषणा OTGSTATE_DEV_STATE_MASK		GENMASK(2, 0)
#घोषणा OTGSTATE_HOST_STATE_MASK	GENMASK(5, 3)
#घोषणा OTGSTATE_HOST_STATE_IDLE	0x0
#घोषणा OTGSTATE_HOST_STATE_VBUS_FALL	0x7
#घोषणा OTGSTATE_HOST_STATE(p)		(((p) & OTGSTATE_HOST_STATE_MASK) >> 3)

/* OTGREFCLK - biपंचांगasks */
#घोषणा OTGREFCLK_STB_CLK_SWITCH_EN	BIT(31)

/* OVERRIDE - biपंचांगasks */
#घोषणा OVERRIDE_IDPULLUP		BIT(0)
/* Only क्रम CDNS3_CONTROLLER_V0 version */
#घोषणा OVERRIDE_IDPULLUP_V0		BIT(24)
/* Vbusvalid/Sesvalid override select. */
#घोषणा OVERRIDE_SESS_VLD_SEL		BIT(10)

/* PHYRST_CFG - biपंचांगasks */
#घोषणा PHYRST_CFG_PHYRST_A_ENABLE     BIT(0)

#घोषणा CDNS3_ID_PERIPHERAL		1
#घोषणा CDNS3_ID_HOST			0

bool cdns_is_host(काष्ठा cdns *cdns);
bool cdns_is_device(काष्ठा cdns *cdns);
पूर्णांक cdns_get_id(काष्ठा cdns *cdns);
पूर्णांक cdns_get_vbus(काष्ठा cdns *cdns);
व्योम cdns_clear_vbus(काष्ठा cdns *cdns);
व्योम cdns_set_vbus(काष्ठा cdns *cdns);
पूर्णांक cdns_drd_init(काष्ठा cdns *cdns);
पूर्णांक cdns_drd_निकास(काष्ठा cdns *cdns);
पूर्णांक cdns_drd_update_mode(काष्ठा cdns *cdns);
पूर्णांक cdns_drd_gadget_on(काष्ठा cdns *cdns);
व्योम cdns_drd_gadget_off(काष्ठा cdns *cdns);
पूर्णांक cdns_drd_host_on(काष्ठा cdns *cdns);
व्योम cdns_drd_host_off(काष्ठा cdns *cdns);
bool cdns_घातer_is_lost(काष्ठा cdns *cdns);
#पूर्ण_अगर /* __LINUX_CDNS3_DRD */
