<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2016, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _EMAC_SGMII_H_
#घोषणा _EMAC_SGMII_H_

काष्ठा emac_adapter;
काष्ठा platक्रमm_device;

/** emac_sgmii - पूर्णांकernal emac phy
 * @init initialization function
 * @खोलो called when the driver is खोलोed
 * @बंद called when the driver is बंदd
 * @link_change called when the link state changes
 */
काष्ठा sgmii_ops अणु
	पूर्णांक (*init)(काष्ठा emac_adapter *adpt);
	पूर्णांक (*खोलो)(काष्ठा emac_adapter *adpt);
	व्योम (*बंद)(काष्ठा emac_adapter *adpt);
	पूर्णांक (*link_change)(काष्ठा emac_adapter *adpt, bool link_state);
	व्योम (*reset)(काष्ठा emac_adapter *adpt);
पूर्ण;

/** emac_sgmii - पूर्णांकernal emac phy
 * @base base address
 * @digital per-lane digital block
 * @irq the पूर्णांकerrupt number
 * @decode_error_count reference count of consecutive decode errors
 * @sgmii_ops sgmii ops
 */
काष्ठा emac_sgmii अणु
	व्योम __iomem		*base;
	व्योम __iomem		*digital;
	अचिन्हित पूर्णांक		irq;
	atomic_t		decode_error_count;
	काष्ठा	sgmii_ops	*sgmii_ops;
पूर्ण;

पूर्णांक emac_sgmii_config(काष्ठा platक्रमm_device *pdev, काष्ठा emac_adapter *adpt);

पूर्णांक emac_sgmii_init_fsm9900(काष्ठा emac_adapter *adpt);
पूर्णांक emac_sgmii_init_qdf2432(काष्ठा emac_adapter *adpt);
पूर्णांक emac_sgmii_init_qdf2400(काष्ठा emac_adapter *adpt);

पूर्णांक emac_sgmii_init(काष्ठा emac_adapter *adpt);
पूर्णांक emac_sgmii_खोलो(काष्ठा emac_adapter *adpt);
व्योम emac_sgmii_बंद(काष्ठा emac_adapter *adpt);
पूर्णांक emac_sgmii_link_change(काष्ठा emac_adapter *adpt, bool link_state);
व्योम emac_sgmii_reset(काष्ठा emac_adapter *adpt);
#पूर्ण_अगर
