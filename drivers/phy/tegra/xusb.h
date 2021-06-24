<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014-2015, NVIDIA CORPORATION.  All rights reserved.
 * Copyright (c) 2015, Google Inc.
 */

#अगर_अघोषित __PHY_TEGRA_XUSB_H
#घोषणा __PHY_TEGRA_XUSB_H

#समावेश <linux/पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/role.h>

/* legacy entry poपूर्णांकs क्रम backwards-compatibility */
पूर्णांक tegra_xusb_padctl_legacy_probe(काष्ठा platक्रमm_device *pdev);
पूर्णांक tegra_xusb_padctl_legacy_हटाओ(काष्ठा platक्रमm_device *pdev);

काष्ठा phy;
काष्ठा phy_provider;
काष्ठा platक्रमm_device;
काष्ठा regulator;

/*
 * lanes
 */
काष्ठा tegra_xusb_lane_soc अणु
	स्थिर अक्षर *name;

	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक mask;

	स्थिर अक्षर * स्थिर *funcs;
	अचिन्हित पूर्णांक num_funcs;
पूर्ण;

काष्ठा tegra_xusb_lane अणु
	स्थिर काष्ठा tegra_xusb_lane_soc *soc;
	काष्ठा tegra_xusb_pad *pad;
	काष्ठा device_node *np;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक function;
	अचिन्हित पूर्णांक index;
पूर्ण;

पूर्णांक tegra_xusb_lane_parse_dt(काष्ठा tegra_xusb_lane *lane,
			     काष्ठा device_node *np);

काष्ठा tegra_xusb_usb3_lane अणु
	काष्ठा tegra_xusb_lane base;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_usb3_lane *
to_usb3_lane(काष्ठा tegra_xusb_lane *lane)
अणु
	वापस container_of(lane, काष्ठा tegra_xusb_usb3_lane, base);
पूर्ण

काष्ठा tegra_xusb_usb2_lane अणु
	काष्ठा tegra_xusb_lane base;

	u32 hs_curr_level_offset;
	bool घातered_on;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_usb2_lane *
to_usb2_lane(काष्ठा tegra_xusb_lane *lane)
अणु
	वापस container_of(lane, काष्ठा tegra_xusb_usb2_lane, base);
पूर्ण

काष्ठा tegra_xusb_ulpi_lane अणु
	काष्ठा tegra_xusb_lane base;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_ulpi_lane *
to_ulpi_lane(काष्ठा tegra_xusb_lane *lane)
अणु
	वापस container_of(lane, काष्ठा tegra_xusb_ulpi_lane, base);
पूर्ण

काष्ठा tegra_xusb_hsic_lane अणु
	काष्ठा tegra_xusb_lane base;

	u32 strobe_trim;
	u32 rx_strobe_trim;
	u32 rx_data_trim;
	u32 tx_rtune_n;
	u32 tx_rtune_p;
	u32 tx_rslew_n;
	u32 tx_rslew_p;
	bool स्वतः_term;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_hsic_lane *
to_hsic_lane(काष्ठा tegra_xusb_lane *lane)
अणु
	वापस container_of(lane, काष्ठा tegra_xusb_hsic_lane, base);
पूर्ण

काष्ठा tegra_xusb_pcie_lane अणु
	काष्ठा tegra_xusb_lane base;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_pcie_lane *
to_pcie_lane(काष्ठा tegra_xusb_lane *lane)
अणु
	वापस container_of(lane, काष्ठा tegra_xusb_pcie_lane, base);
पूर्ण

काष्ठा tegra_xusb_sata_lane अणु
	काष्ठा tegra_xusb_lane base;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_sata_lane *
to_sata_lane(काष्ठा tegra_xusb_lane *lane)
अणु
	वापस container_of(lane, काष्ठा tegra_xusb_sata_lane, base);
पूर्ण

काष्ठा tegra_xusb_lane_ops अणु
	काष्ठा tegra_xusb_lane *(*probe)(काष्ठा tegra_xusb_pad *pad,
					 काष्ठा device_node *np,
					 अचिन्हित पूर्णांक index);
	व्योम (*हटाओ)(काष्ठा tegra_xusb_lane *lane);
पूर्ण;

/*
 * pads
 */
काष्ठा tegra_xusb_pad_soc;
काष्ठा tegra_xusb_padctl;

काष्ठा tegra_xusb_pad_ops अणु
	काष्ठा tegra_xusb_pad *(*probe)(काष्ठा tegra_xusb_padctl *padctl,
					स्थिर काष्ठा tegra_xusb_pad_soc *soc,
					काष्ठा device_node *np);
	व्योम (*हटाओ)(काष्ठा tegra_xusb_pad *pad);
पूर्ण;

काष्ठा tegra_xusb_pad_soc अणु
	स्थिर अक्षर *name;

	स्थिर काष्ठा tegra_xusb_lane_soc *lanes;
	अचिन्हित पूर्णांक num_lanes;

	स्थिर काष्ठा tegra_xusb_pad_ops *ops;
पूर्ण;

काष्ठा tegra_xusb_pad अणु
	स्थिर काष्ठा tegra_xusb_pad_soc *soc;
	काष्ठा tegra_xusb_padctl *padctl;
	काष्ठा phy_provider *provider;
	काष्ठा phy **lanes;
	काष्ठा device dev;

	स्थिर काष्ठा tegra_xusb_lane_ops *ops;

	काष्ठा list_head list;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_pad *to_tegra_xusb_pad(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा tegra_xusb_pad, dev);
पूर्ण

पूर्णांक tegra_xusb_pad_init(काष्ठा tegra_xusb_pad *pad,
			काष्ठा tegra_xusb_padctl *padctl,
			काष्ठा device_node *np);
पूर्णांक tegra_xusb_pad_रेजिस्टर(काष्ठा tegra_xusb_pad *pad,
			    स्थिर काष्ठा phy_ops *ops);
व्योम tegra_xusb_pad_unरेजिस्टर(काष्ठा tegra_xusb_pad *pad);

काष्ठा tegra_xusb_usb3_pad अणु
	काष्ठा tegra_xusb_pad base;

	अचिन्हित पूर्णांक enable;
	काष्ठा mutex lock;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_usb3_pad *
to_usb3_pad(काष्ठा tegra_xusb_pad *pad)
अणु
	वापस container_of(pad, काष्ठा tegra_xusb_usb3_pad, base);
पूर्ण

काष्ठा tegra_xusb_usb2_pad अणु
	काष्ठा tegra_xusb_pad base;

	काष्ठा clk *clk;
	अचिन्हित पूर्णांक enable;
	काष्ठा mutex lock;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_usb2_pad *
to_usb2_pad(काष्ठा tegra_xusb_pad *pad)
अणु
	वापस container_of(pad, काष्ठा tegra_xusb_usb2_pad, base);
पूर्ण

काष्ठा tegra_xusb_ulpi_pad अणु
	काष्ठा tegra_xusb_pad base;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_ulpi_pad *
to_ulpi_pad(काष्ठा tegra_xusb_pad *pad)
अणु
	वापस container_of(pad, काष्ठा tegra_xusb_ulpi_pad, base);
पूर्ण

काष्ठा tegra_xusb_hsic_pad अणु
	काष्ठा tegra_xusb_pad base;

	काष्ठा regulator *supply;
	काष्ठा clk *clk;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_hsic_pad *
to_hsic_pad(काष्ठा tegra_xusb_pad *pad)
अणु
	वापस container_of(pad, काष्ठा tegra_xusb_hsic_pad, base);
पूर्ण

काष्ठा tegra_xusb_pcie_pad अणु
	काष्ठा tegra_xusb_pad base;

	काष्ठा reset_control *rst;
	काष्ठा clk *pll;

	अचिन्हित पूर्णांक enable;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_pcie_pad *
to_pcie_pad(काष्ठा tegra_xusb_pad *pad)
अणु
	वापस container_of(pad, काष्ठा tegra_xusb_pcie_pad, base);
पूर्ण

काष्ठा tegra_xusb_sata_pad अणु
	काष्ठा tegra_xusb_pad base;

	काष्ठा reset_control *rst;
	काष्ठा clk *pll;

	अचिन्हित पूर्णांक enable;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_sata_pad *
to_sata_pad(काष्ठा tegra_xusb_pad *pad)
अणु
	वापस container_of(pad, काष्ठा tegra_xusb_sata_pad, base);
पूर्ण

/*
 * ports
 */
काष्ठा tegra_xusb_port_ops;

काष्ठा tegra_xusb_port अणु
	काष्ठा tegra_xusb_padctl *padctl;
	काष्ठा tegra_xusb_lane *lane;
	अचिन्हित पूर्णांक index;

	काष्ठा list_head list;
	काष्ठा device dev;

	काष्ठा usb_role_चयन *usb_role_sw;
	काष्ठा work_काष्ठा usb_phy_work;
	काष्ठा usb_phy usb_phy;

	स्थिर काष्ठा tegra_xusb_port_ops *ops;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_port *to_tegra_xusb_port(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा tegra_xusb_port, dev);
पूर्ण

काष्ठा tegra_xusb_lane_map अणु
	अचिन्हित पूर्णांक port;
	स्थिर अक्षर *type;
	अचिन्हित पूर्णांक index;
	स्थिर अक्षर *func;
पूर्ण;

काष्ठा tegra_xusb_lane *
tegra_xusb_port_find_lane(काष्ठा tegra_xusb_port *port,
			  स्थिर काष्ठा tegra_xusb_lane_map *map,
			  स्थिर अक्षर *function);

काष्ठा tegra_xusb_port *
tegra_xusb_find_port(काष्ठा tegra_xusb_padctl *padctl, स्थिर अक्षर *type,
		     अचिन्हित पूर्णांक index);

काष्ठा tegra_xusb_usb2_port अणु
	काष्ठा tegra_xusb_port base;

	काष्ठा regulator *supply;
	क्रमागत usb_dr_mode mode;
	bool पूर्णांकernal;
	पूर्णांक usb3_port_fake;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_usb2_port *
to_usb2_port(काष्ठा tegra_xusb_port *port)
अणु
	वापस container_of(port, काष्ठा tegra_xusb_usb2_port, base);
पूर्ण

काष्ठा tegra_xusb_usb2_port *
tegra_xusb_find_usb2_port(काष्ठा tegra_xusb_padctl *padctl,
			  अचिन्हित पूर्णांक index);
व्योम tegra_xusb_usb2_port_release(काष्ठा tegra_xusb_port *port);
व्योम tegra_xusb_usb2_port_हटाओ(काष्ठा tegra_xusb_port *port);

काष्ठा tegra_xusb_ulpi_port अणु
	काष्ठा tegra_xusb_port base;

	काष्ठा regulator *supply;
	bool पूर्णांकernal;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_ulpi_port *
to_ulpi_port(काष्ठा tegra_xusb_port *port)
अणु
	वापस container_of(port, काष्ठा tegra_xusb_ulpi_port, base);
पूर्ण

व्योम tegra_xusb_ulpi_port_release(काष्ठा tegra_xusb_port *port);

काष्ठा tegra_xusb_hsic_port अणु
	काष्ठा tegra_xusb_port base;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_hsic_port *
to_hsic_port(काष्ठा tegra_xusb_port *port)
अणु
	वापस container_of(port, काष्ठा tegra_xusb_hsic_port, base);
पूर्ण

व्योम tegra_xusb_hsic_port_release(काष्ठा tegra_xusb_port *port);

काष्ठा tegra_xusb_usb3_port अणु
	काष्ठा tegra_xusb_port base;
	काष्ठा regulator *supply;
	bool context_saved;
	अचिन्हित पूर्णांक port;
	bool पूर्णांकernal;
	bool disable_gen2;

	u32 tap1;
	u32 amp;
	u32 ctle_z;
	u32 ctle_g;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_xusb_usb3_port *
to_usb3_port(काष्ठा tegra_xusb_port *port)
अणु
	वापस container_of(port, काष्ठा tegra_xusb_usb3_port, base);
पूर्ण

काष्ठा tegra_xusb_usb3_port *
tegra_xusb_find_usb3_port(काष्ठा tegra_xusb_padctl *padctl,
			  अचिन्हित पूर्णांक index);
व्योम tegra_xusb_usb3_port_release(काष्ठा tegra_xusb_port *port);
व्योम tegra_xusb_usb3_port_हटाओ(काष्ठा tegra_xusb_port *port);

काष्ठा tegra_xusb_port_ops अणु
	व्योम (*release)(काष्ठा tegra_xusb_port *port);
	व्योम (*हटाओ)(काष्ठा tegra_xusb_port *port);
	पूर्णांक (*enable)(काष्ठा tegra_xusb_port *port);
	व्योम (*disable)(काष्ठा tegra_xusb_port *port);
	काष्ठा tegra_xusb_lane *(*map)(काष्ठा tegra_xusb_port *port);
पूर्ण;

/*
 * pad controller
 */
काष्ठा tegra_xusb_padctl_soc;

काष्ठा tegra_xusb_padctl_ops अणु
	काष्ठा tegra_xusb_padctl *
		(*probe)(काष्ठा device *dev,
			 स्थिर काष्ठा tegra_xusb_padctl_soc *soc);
	व्योम (*हटाओ)(काष्ठा tegra_xusb_padctl *padctl);

	पूर्णांक (*usb3_save_context)(काष्ठा tegra_xusb_padctl *padctl,
				 अचिन्हित पूर्णांक index);
	पूर्णांक (*hsic_set_idle)(काष्ठा tegra_xusb_padctl *padctl,
			     अचिन्हित पूर्णांक index, bool idle);
	पूर्णांक (*usb3_set_lfps_detect)(काष्ठा tegra_xusb_padctl *padctl,
				    अचिन्हित पूर्णांक index, bool enable);
	पूर्णांक (*vbus_override)(काष्ठा tegra_xusb_padctl *padctl, bool set);
	पूर्णांक (*uपंचांगi_port_reset)(काष्ठा phy *phy);
पूर्ण;

काष्ठा tegra_xusb_padctl_soc अणु
	स्थिर काष्ठा tegra_xusb_pad_soc * स्थिर *pads;
	अचिन्हित पूर्णांक num_pads;

	काष्ठा अणु
		काष्ठा अणु
			स्थिर काष्ठा tegra_xusb_port_ops *ops;
			अचिन्हित पूर्णांक count;
		पूर्ण usb2, ulpi, hsic, usb3;
	पूर्ण ports;

	स्थिर काष्ठा tegra_xusb_padctl_ops *ops;

	स्थिर अक्षर * स्थिर *supply_names;
	अचिन्हित पूर्णांक num_supplies;
	bool supports_gen2;
	bool need_fake_usb3_port;
पूर्ण;

काष्ठा tegra_xusb_padctl अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा mutex lock;
	काष्ठा reset_control *rst;

	स्थिर काष्ठा tegra_xusb_padctl_soc *soc;

	काष्ठा tegra_xusb_pad *pcie;
	काष्ठा tegra_xusb_pad *sata;
	काष्ठा tegra_xusb_pad *ulpi;
	काष्ठा tegra_xusb_pad *usb2;
	काष्ठा tegra_xusb_pad *hsic;

	काष्ठा list_head ports;
	काष्ठा list_head lanes;
	काष्ठा list_head pads;

	अचिन्हित पूर्णांक enable;

	काष्ठा clk *clk;

	काष्ठा regulator_bulk_data *supplies;
पूर्ण;

अटल अंतरभूत व्योम padctl_ग_लिखोl(काष्ठा tegra_xusb_padctl *padctl, u32 value,
				 अचिन्हित दीर्घ offset)
अणु
	dev_dbg(padctl->dev, "%08lx < %08x\n", offset, value);
	ग_लिखोl(value, padctl->regs + offset);
पूर्ण

अटल अंतरभूत u32 padctl_पढ़ोl(काष्ठा tegra_xusb_padctl *padctl,
			       अचिन्हित दीर्घ offset)
अणु
	u32 value = पढ़ोl(padctl->regs + offset);
	dev_dbg(padctl->dev, "%08lx > %08x\n", offset, value);
	वापस value;
पूर्ण

काष्ठा tegra_xusb_lane *tegra_xusb_find_lane(काष्ठा tegra_xusb_padctl *padctl,
					     स्थिर अक्षर *name,
					     अचिन्हित पूर्णांक index);

#अगर defined(CONFIG_ARCH_TEGRA_124_SOC) || defined(CONFIG_ARCH_TEGRA_132_SOC)
बाह्य स्थिर काष्ठा tegra_xusb_padctl_soc tegra124_xusb_padctl_soc;
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_TEGRA_210_SOC)
बाह्य स्थिर काष्ठा tegra_xusb_padctl_soc tegra210_xusb_padctl_soc;
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_TEGRA_186_SOC)
बाह्य स्थिर काष्ठा tegra_xusb_padctl_soc tegra186_xusb_padctl_soc;
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_TEGRA_194_SOC)
बाह्य स्थिर काष्ठा tegra_xusb_padctl_soc tegra194_xusb_padctl_soc;
#पूर्ण_अगर

#पूर्ण_अगर /* __PHY_TEGRA_XUSB_H */
