<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित __SOC_MEDIATEK_MTK_PM_DOMAINS_H
#घोषणा __SOC_MEDIATEK_MTK_PM_DOMAINS_H

#घोषणा MTK_SCPD_ACTIVE_WAKEUP		BIT(0)
#घोषणा MTK_SCPD_FWAIT_SRAM		BIT(1)
#घोषणा MTK_SCPD_SRAM_ISO		BIT(2)
#घोषणा MTK_SCPD_KEEP_DEFAULT_OFF	BIT(3)
#घोषणा MTK_SCPD_DOMAIN_SUPPLY		BIT(4)
#घोषणा MTK_SCPD_CAPS(_scpd, _x)	((_scpd)->data->caps & (_x))

#घोषणा SPM_VDE_PWR_CON			0x0210
#घोषणा SPM_MFG_PWR_CON			0x0214
#घोषणा SPM_VEN_PWR_CON			0x0230
#घोषणा SPM_ISP_PWR_CON			0x0238
#घोषणा SPM_DIS_PWR_CON			0x023c
#घोषणा SPM_CONN_PWR_CON		0x0280
#घोषणा SPM_VEN2_PWR_CON		0x0298
#घोषणा SPM_AUDIO_PWR_CON		0x029c
#घोषणा SPM_MFG_2D_PWR_CON		0x02c0
#घोषणा SPM_MFG_ASYNC_PWR_CON		0x02c4
#घोषणा SPM_USB_PWR_CON			0x02cc

#घोषणा SPM_PWR_STATUS			0x060c
#घोषणा SPM_PWR_STATUS_2ND		0x0610

#घोषणा PWR_STATUS_CONN			BIT(1)
#घोषणा PWR_STATUS_DISP			BIT(3)
#घोषणा PWR_STATUS_MFG			BIT(4)
#घोषणा PWR_STATUS_ISP			BIT(5)
#घोषणा PWR_STATUS_VDEC			BIT(7)
#घोषणा PWR_STATUS_VENC_LT		BIT(20)
#घोषणा PWR_STATUS_VENC			BIT(21)
#घोषणा PWR_STATUS_MFG_2D		BIT(22)
#घोषणा PWR_STATUS_MFG_ASYNC		BIT(23)
#घोषणा PWR_STATUS_AUDIO		BIT(24)
#घोषणा PWR_STATUS_USB			BIT(25)

#घोषणा SPM_MAX_BUS_PROT_DATA		5

#घोषणा _BUS_PROT(_mask, _set, _clr, _sta, _update, _ignore) अणु	\
		.bus_prot_mask = (_mask),			\
		.bus_prot_set = _set,				\
		.bus_prot_clr = _clr,				\
		.bus_prot_sta = _sta,				\
		.bus_prot_reg_update = _update,			\
		.ignore_clr_ack = _ignore,			\
	पूर्ण

#घोषणा BUS_PROT_WR(_mask, _set, _clr, _sta)			\
		_BUS_PROT(_mask, _set, _clr, _sta, false, false)

#घोषणा BUS_PROT_WR_IGN(_mask, _set, _clr, _sta)		\
		_BUS_PROT(_mask, _set, _clr, _sta, false, true)

#घोषणा BUS_PROT_UPDATE(_mask, _set, _clr, _sta)		\
		_BUS_PROT(_mask, _set, _clr, _sta, true, false)

#घोषणा BUS_PROT_UPDATE_TOPAXI(_mask)				\
		BUS_PROT_UPDATE(_mask,				\
				INFRA_TOPAXI_PROTECTEN,		\
				INFRA_TOPAXI_PROTECTEN_CLR,	\
				INFRA_TOPAXI_PROTECTSTA1)

काष्ठा scpsys_bus_prot_data अणु
	u32 bus_prot_mask;
	u32 bus_prot_set;
	u32 bus_prot_clr;
	u32 bus_prot_sta;
	bool bus_prot_reg_update;
	bool ignore_clr_ack;
पूर्ण;

#घोषणा MAX_SUBSYS_CLKS 10

/**
 * काष्ठा scpsys_करोमुख्य_data - scp करोमुख्य data क्रम घातer on/off flow
 * @name: The name of the घातer करोमुख्य.
 * @sta_mask: The mask क्रम घातer on/off status bit.
 * @ctl_offs: The offset क्रम मुख्य घातer control रेजिस्टर.
 * @sram_pdn_bits: The mask क्रम sram घातer control bits.
 * @sram_pdn_ack_bits: The mask क्रम sram घातer control acked bits.
 * @caps: The flag क्रम active wake-up action.
 * @bp_infracfg: bus protection क्रम infracfg subप्रणाली
 * @bp_smi: bus protection क्रम smi subप्रणाली
 */
काष्ठा scpsys_करोमुख्य_data अणु
	स्थिर अक्षर *name;
	u32 sta_mask;
	पूर्णांक ctl_offs;
	u32 sram_pdn_bits;
	u32 sram_pdn_ack_bits;
	u8 caps;
	स्थिर काष्ठा scpsys_bus_prot_data bp_infracfg[SPM_MAX_BUS_PROT_DATA];
	स्थिर काष्ठा scpsys_bus_prot_data bp_smi[SPM_MAX_BUS_PROT_DATA];
पूर्ण;

काष्ठा scpsys_soc_data अणु
	स्थिर काष्ठा scpsys_करोमुख्य_data *करोमुख्यs_data;
	पूर्णांक num_करोमुख्यs;
	पूर्णांक pwr_sta_offs;
	पूर्णांक pwr_sta2nd_offs;
पूर्ण;

#पूर्ण_अगर /* __SOC_MEDIATEK_MTK_PM_DOMAINS_H */
