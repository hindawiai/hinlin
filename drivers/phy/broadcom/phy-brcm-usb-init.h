<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014-2017 Broadcom
 */

#अगर_अघोषित _USB_BRCM_COMMON_INIT_H
#घोषणा _USB_BRCM_COMMON_INIT_H

#समावेश <linux/regmap.h>

#घोषणा USB_CTLR_MODE_HOST 0
#घोषणा USB_CTLR_MODE_DEVICE 1
#घोषणा USB_CTLR_MODE_DRD 2
#घोषणा USB_CTLR_MODE_TYPEC_PD 3

क्रमागत brcmusb_reg_sel अणु
	BRCM_REGS_CTRL = 0,
	BRCM_REGS_XHCI_EC,
	BRCM_REGS_XHCI_GBL,
	BRCM_REGS_USB_PHY,
	BRCM_REGS_USB_MDIO,
	BRCM_REGS_BDC_EC,
	BRCM_REGS_MAX
पूर्ण;

#घोषणा USB_CTRL_REG(base, reg)	((व्योम __iomem *)base + USB_CTRL_##reg)
#घोषणा USB_XHCI_EC_REG(base, reg) ((व्योम __iomem *)base + USB_XHCI_EC_##reg)
#घोषणा USB_CTRL_MASK(reg, field) \
	USB_CTRL_##reg##_##field##_MASK
#घोषणा USB_CTRL_SET(base, reg, field)	\
	brcm_usb_ctrl_set(USB_CTRL_REG(base, reg),	\
			  USB_CTRL_##reg##_##field##_MASK)
#घोषणा USB_CTRL_UNSET(base, reg, field)	\
	brcm_usb_ctrl_unset(USB_CTRL_REG(base, reg),		\
			    USB_CTRL_##reg##_##field##_MASK)

काष्ठा  brcm_usb_init_params;

काष्ठा brcm_usb_init_ops अणु
	व्योम (*init_ipp)(काष्ठा brcm_usb_init_params *params);
	व्योम (*init_common)(काष्ठा brcm_usb_init_params *params);
	व्योम (*init_eohci)(काष्ठा brcm_usb_init_params *params);
	व्योम (*init_xhci)(काष्ठा brcm_usb_init_params *params);
	व्योम (*uninit_common)(काष्ठा brcm_usb_init_params *params);
	व्योम (*uninit_eohci)(काष्ठा brcm_usb_init_params *params);
	व्योम (*uninit_xhci)(काष्ठा brcm_usb_init_params *params);
	पूर्णांक  (*get_dual_select)(काष्ठा brcm_usb_init_params *params);
	व्योम (*set_dual_select)(काष्ठा brcm_usb_init_params *params, पूर्णांक mode);
पूर्ण;

काष्ठा  brcm_usb_init_params अणु
	व्योम __iomem *regs[BRCM_REGS_MAX];
	पूर्णांक ioc;
	पूर्णांक ipp;
	पूर्णांक mode;
	u32 family_id;
	u32 product_id;
	पूर्णांक selected_family;
	स्थिर अक्षर *family_name;
	स्थिर u32 *usb_reg_bits_map;
	स्थिर काष्ठा brcm_usb_init_ops *ops;
	काष्ठा regmap *syscon_piarbctl;
	bool wake_enabled;
	bool suspend_with_घड़ीs;
पूर्ण;

व्योम brcm_usb_dvr_init_7445(काष्ठा brcm_usb_init_params *params);
व्योम brcm_usb_dvr_init_7216(काष्ठा brcm_usb_init_params *params);
व्योम brcm_usb_dvr_init_7211b0(काष्ठा brcm_usb_init_params *params);

अटल अंतरभूत u32 brcm_usb_पढ़ोl(व्योम __iomem *addr)
अणु
	/*
	 * MIPS endianness is configured by boot strap, which also reverses all
	 * bus endianness (i.e., big-endian CPU + big endian bus ==> native
	 * endian I/O).
	 *
	 * Other architectures (e.g., ARM) either करो not support big endian, or
	 * अन्यथा leave I/O in little endian mode.
	 */
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		वापस __raw_पढ़ोl(addr);
	अन्यथा
		वापस पढ़ोl_relaxed(addr);
पूर्ण

अटल अंतरभूत व्योम brcm_usb_ग_लिखोl(u32 val, व्योम __iomem *addr)
अणु
	/* See brcmnand_पढ़ोl() comments */
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		__raw_ग_लिखोl(val, addr);
	अन्यथा
		ग_लिखोl_relaxed(val, addr);
पूर्ण

अटल अंतरभूत व्योम brcm_usb_ctrl_unset(व्योम __iomem *reg, u32 mask)
अणु
	brcm_usb_ग_लिखोl(brcm_usb_पढ़ोl(reg) & ~(mask), reg);
पूर्ण;

अटल अंतरभूत व्योम brcm_usb_ctrl_set(व्योम __iomem *reg, u32 mask)
अणु
	brcm_usb_ग_लिखोl(brcm_usb_पढ़ोl(reg) | (mask), reg);
पूर्ण;

अटल अंतरभूत व्योम brcm_usb_init_ipp(काष्ठा brcm_usb_init_params *ini)
अणु
	अगर (ini->ops->init_ipp)
		ini->ops->init_ipp(ini);
पूर्ण

अटल अंतरभूत व्योम brcm_usb_init_common(काष्ठा brcm_usb_init_params *ini)
अणु
	अगर (ini->ops->init_common)
		ini->ops->init_common(ini);
पूर्ण

अटल अंतरभूत व्योम brcm_usb_init_eohci(काष्ठा brcm_usb_init_params *ini)
अणु
	अगर (ini->ops->init_eohci)
		ini->ops->init_eohci(ini);
पूर्ण

अटल अंतरभूत व्योम brcm_usb_init_xhci(काष्ठा brcm_usb_init_params *ini)
अणु
	अगर (ini->ops->init_xhci)
		ini->ops->init_xhci(ini);
पूर्ण

अटल अंतरभूत व्योम brcm_usb_uninit_common(काष्ठा brcm_usb_init_params *ini)
अणु
	अगर (ini->ops->uninit_common)
		ini->ops->uninit_common(ini);
पूर्ण

अटल अंतरभूत व्योम brcm_usb_uninit_eohci(काष्ठा brcm_usb_init_params *ini)
अणु
	अगर (ini->ops->uninit_eohci)
		ini->ops->uninit_eohci(ini);
पूर्ण

अटल अंतरभूत व्योम brcm_usb_uninit_xhci(काष्ठा brcm_usb_init_params *ini)
अणु
	अगर (ini->ops->uninit_xhci)
		ini->ops->uninit_xhci(ini);
पूर्ण

अटल अंतरभूत पूर्णांक brcm_usb_get_dual_select(काष्ठा brcm_usb_init_params *ini)
अणु
	अगर (ini->ops->get_dual_select)
		वापस ini->ops->get_dual_select(ini);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम brcm_usb_set_dual_select(काष्ठा brcm_usb_init_params *ini,
	पूर्णांक mode)
अणु
	अगर (ini->ops->set_dual_select)
		ini->ops->set_dual_select(ini, mode);
पूर्ण

#पूर्ण_अगर /* _USB_BRCM_COMMON_INIT_H */
