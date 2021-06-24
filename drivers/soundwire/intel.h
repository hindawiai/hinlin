<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/* Copyright(c) 2015-17 Intel Corporation. */

#अगर_अघोषित __SDW_INTEL_LOCAL_H
#घोषणा __SDW_INTEL_LOCAL_H

/**
 * काष्ठा sdw_पूर्णांकel_link_res - Soundwire Intel link resource काष्ठाure,
 * typically populated by the controller driver.
 * @pdev: platक्रमm_device
 * @mmio_base: mmio base of SoundWire रेजिस्टरs
 * @रेजिस्टरs: Link IO रेजिस्टरs base
 * @shim: Audio shim poपूर्णांकer
 * @alh: ALH (Audio Link Hub) poपूर्णांकer
 * @irq: Interrupt line
 * @ops: Shim callback ops
 * @dev: device implementing hw_params and मुक्त callbacks
 * @shim_lock: mutex to handle access to shared SHIM रेजिस्टरs
 * @shim_mask: global poपूर्णांकer to check SHIM रेजिस्टर initialization
 * @घड़ी_stop_quirks: mask defining requested behavior on pm_suspend
 * @link_mask: global mask needed क्रम घातer-up/करोwn sequences
 * @cdns: Cadence master descriptor
 * @list: used to walk-through all masters exposed by the same controller
 */
काष्ठा sdw_पूर्णांकel_link_res अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *mmio_base; /* not strictly needed, useful क्रम debug */
	व्योम __iomem *रेजिस्टरs;
	व्योम __iomem *shim;
	व्योम __iomem *alh;
	पूर्णांक irq;
	स्थिर काष्ठा sdw_पूर्णांकel_ops *ops;
	काष्ठा device *dev;
	काष्ठा mutex *shim_lock; /* protect shared रेजिस्टरs */
	u32 *shim_mask;
	u32 घड़ी_stop_quirks;
	u32 link_mask;
	काष्ठा sdw_cdns *cdns;
	काष्ठा list_head list;
पूर्ण;

काष्ठा sdw_पूर्णांकel अणु
	काष्ठा sdw_cdns cdns;
	पूर्णांक instance;
	काष्ठा sdw_पूर्णांकel_link_res *link_res;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs;
#पूर्ण_अगर
पूर्ण;

पूर्णांक पूर्णांकel_master_startup(काष्ठा platक्रमm_device *pdev);
पूर्णांक पूर्णांकel_master_process_wakeen_event(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर /* __SDW_INTEL_LOCAL_H */
