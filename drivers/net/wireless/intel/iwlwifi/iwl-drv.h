<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014, 2020 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 */
#अगर_अघोषित __iwl_drv_h__
#घोषणा __iwl_drv_h__
#समावेश <linux/export.h>

/* क्रम all modules */
#घोषणा DRV_NAME        "iwlwifi"
#घोषणा DRV_AUTHOR	"Intel Corporation <linuxwifi@intel.com>"

/* radio config bits (actual values from NVM definition) */
#घोषणा NVM_RF_CFG_DASH_MSK(x)   (x & 0x3)         /* bits 0-1   */
#घोषणा NVM_RF_CFG_STEP_MSK(x)   ((x >> 2)  & 0x3) /* bits 2-3   */
#घोषणा NVM_RF_CFG_TYPE_MSK(x)   ((x >> 4)  & 0x3) /* bits 4-5   */
#घोषणा NVM_RF_CFG_PNUM_MSK(x)   ((x >> 6)  & 0x3) /* bits 6-7   */
#घोषणा NVM_RF_CFG_TX_ANT_MSK(x) ((x >> 8)  & 0xF) /* bits 8-11  */
#घोषणा NVM_RF_CFG_RX_ANT_MSK(x) ((x >> 12) & 0xF) /* bits 12-15 */

#घोषणा EXT_NVM_RF_CFG_FLAVOR_MSK(x)   ((x) & 0xF)
#घोषणा EXT_NVM_RF_CFG_DASH_MSK(x)   (((x) >> 4) & 0xF)
#घोषणा EXT_NVM_RF_CFG_STEP_MSK(x)   (((x) >> 8) & 0xF)
#घोषणा EXT_NVM_RF_CFG_TYPE_MSK(x)   (((x) >> 12) & 0xFFF)
#घोषणा EXT_NVM_RF_CFG_TX_ANT_MSK(x) (((x) >> 24) & 0xF)
#घोषणा EXT_NVM_RF_CFG_RX_ANT_MSK(x) (((x) >> 28) & 0xF)

/**
 * DOC: Driver प्रणाली flows - drv component
 *
 * This component implements the प्रणाली flows such as bus क्रमागतeration, bus
 * removal. Bus dependent parts of प्रणाली flows (such as iwl_pci_probe) are in
 * bus specअगरic files (transport files). This is the code that is common among
 * dअगरferent buses.
 *
 * This component is also in अक्षरge of managing the several implementations of
 * the wअगरi flows: it will allow to have several fw API implementation. These
 * dअगरferent implementations will dअगरfer in the way they implement mac80211's
 * handlers too.

 * The init flow wrt to the drv component looks like this:
 * 1) The bus specअगरic component is called from module_init
 * 2) The bus specअगरic component रेजिस्टरs the bus driver
 * 3) The bus driver calls the probe function
 * 4) The bus specअगरic component configures the bus
 * 5) The bus specअगरic component calls to the drv bus agnostic part
 *    (iwl_drv_start)
 * 6) iwl_drv_start fetches the fw ASYNC, iwl_req_fw_callback
 * 7) iwl_req_fw_callback parses the fw file
 * 8) iwl_req_fw_callback starts the wअगरi implementation to matches the fw
 */

काष्ठा iwl_drv;
काष्ठा iwl_trans;
काष्ठा iwl_cfg;
/**
 * iwl_drv_start - start the drv
 *
 * @trans_ops: the ops of the transport
 *
 * starts the driver: fetches the firmware. This should be called by bus
 * specअगरic प्रणाली flows implementations. For example, the bus specअगरic probe
 * function should करो bus related operations only, and then call to this
 * function. It वापसs the driver object or %शून्य अगर an error occurred.
 */
काष्ठा iwl_drv *iwl_drv_start(काष्ठा iwl_trans *trans);

/**
 * iwl_drv_stop - stop the drv
 *
 * @drv:
 *
 * Stop the driver. This should be called by bus specअगरic प्रणाली flows
 * implementations. For example, the bus specअगरic हटाओ function should first
 * call this function and then करो the bus related operations only.
 */
व्योम iwl_drv_stop(काष्ठा iwl_drv *drv);

/*
 * exported symbol management
 *
 * The driver can be split पूर्णांकo multiple modules, in which हाल some symbols
 * must be exported क्रम the sub-modules. However, अगर it's not split and
 * everything is built-in, then we can aव्योम that.
 */
#अगर_घोषित CONFIG_IWLWIFI_OPMODE_MODULAR
#घोषणा IWL_EXPORT_SYMBOL(sym)	EXPORT_SYMBOL_GPL(sym)
#अन्यथा
#घोषणा IWL_EXPORT_SYMBOL(sym)
#पूर्ण_अगर

#पूर्ण_अगर /* __iwl_drv_h__ */
