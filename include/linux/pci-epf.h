<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
 * PCI Endpoपूर्णांक *Function* (EPF) header file
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#अगर_अघोषित __LINUX_PCI_EPF_H
#घोषणा __LINUX_PCI_EPF_H

#समावेश <linux/configfs.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pci.h>

काष्ठा pci_epf;
क्रमागत pci_epc_पूर्णांकerface_type;

क्रमागत pci_notअगरy_event अणु
	CORE_INIT,
	LINK_UP,
पूर्ण;

क्रमागत pci_barno अणु
	NO_BAR = -1,
	BAR_0,
	BAR_1,
	BAR_2,
	BAR_3,
	BAR_4,
	BAR_5,
पूर्ण;

/**
 * काष्ठा pci_epf_header - represents standard configuration header
 * @venकरोrid: identअगरies device manufacturer
 * @deviceid: identअगरies a particular device
 * @revid: specअगरies a device-specअगरic revision identअगरier
 * @progअगर_code: identअगरies a specअगरic रेजिस्टर-level programming पूर्णांकerface
 * @subclass_code: identअगरies more specअगरically the function of the device
 * @baseclass_code: broadly classअगरies the type of function the device perक्रमms
 * @cache_line_size: specअगरies the प्रणाली cacheline size in units of DWORDs
 * @subsys_venकरोr_id: venकरोr of the add-in card or subप्रणाली
 * @subsys_id: id specअगरic to venकरोr
 * @पूर्णांकerrupt_pin: पूर्णांकerrupt pin the device (or device function) uses
 */
काष्ठा pci_epf_header अणु
	u16	venकरोrid;
	u16	deviceid;
	u8	revid;
	u8	progअगर_code;
	u8	subclass_code;
	u8	baseclass_code;
	u8	cache_line_size;
	u16	subsys_venकरोr_id;
	u16	subsys_id;
	क्रमागत pci_पूर्णांकerrupt_pin पूर्णांकerrupt_pin;
पूर्ण;

/**
 * काष्ठा pci_epf_ops - set of function poपूर्णांकers क्रम perक्रमming EPF operations
 * @bind: ops to perक्रमm when a EPC device has been bound to EPF device
 * @unbind: ops to perक्रमm when a binding has been lost between a EPC device
 *	    and EPF device
 * @add_cfs: ops to initialize function specअगरic configfs attributes
 */
काष्ठा pci_epf_ops अणु
	पूर्णांक	(*bind)(काष्ठा pci_epf *epf);
	व्योम	(*unbind)(काष्ठा pci_epf *epf);
	काष्ठा config_group *(*add_cfs)(काष्ठा pci_epf *epf,
					काष्ठा config_group *group);
पूर्ण;

/**
 * काष्ठा pci_epf_driver - represents the PCI EPF driver
 * @probe: ops to perक्रमm when a new EPF device has been bound to the EPF driver
 * @हटाओ: ops to perक्रमm when the binding between the EPF device and EPF
 *	    driver is broken
 * @driver: PCI EPF driver
 * @ops: set of function poपूर्णांकers क्रम perक्रमming EPF operations
 * @owner: the owner of the module that रेजिस्टरs the PCI EPF driver
 * @epf_group: list of configfs group corresponding to the PCI EPF driver
 * @id_table: identअगरies EPF devices क्रम probing
 */
काष्ठा pci_epf_driver अणु
	पूर्णांक	(*probe)(काष्ठा pci_epf *epf);
	पूर्णांक	(*हटाओ)(काष्ठा pci_epf *epf);

	काष्ठा device_driver	driver;
	काष्ठा pci_epf_ops	*ops;
	काष्ठा module		*owner;
	काष्ठा list_head	epf_group;
	स्थिर काष्ठा pci_epf_device_id	*id_table;
पूर्ण;

#घोषणा to_pci_epf_driver(drv) (container_of((drv), काष्ठा pci_epf_driver, \
				driver))

/**
 * काष्ठा pci_epf_bar - represents the BAR of EPF device
 * @phys_addr: physical address that should be mapped to the BAR
 * @addr: भव address corresponding to the @phys_addr
 * @size: the size of the address space present in BAR
 */
काष्ठा pci_epf_bar अणु
	dma_addr_t	phys_addr;
	व्योम		*addr;
	माप_प्रकार		size;
	क्रमागत pci_barno	barno;
	पूर्णांक		flags;
पूर्ण;

/**
 * काष्ठा pci_epf - represents the PCI EPF device
 * @dev: the PCI EPF device
 * @name: the name of the PCI EPF device
 * @header: represents standard configuration header
 * @bar: represents the BAR of EPF device
 * @msi_पूर्णांकerrupts: number of MSI पूर्णांकerrupts required by this function
 * @func_no: unique function number within this endpoपूर्णांक device
 * @epc: the EPC device to which this EPF device is bound
 * @driver: the EPF driver to which this EPF device is bound
 * @list: to add pci_epf as a list of PCI endpoपूर्णांक functions to pci_epc
 * @nb: notअगरier block to notअगरy EPF of any EPC events (like linkup)
 * @lock: mutex to protect pci_epf_ops
 * @sec_epc: the secondary EPC device to which this EPF device is bound
 * @sec_epc_list: to add pci_epf as list of PCI endpoपूर्णांक functions to secondary
 *   EPC device
 * @sec_epc_bar: represents the BAR of EPF device associated with secondary EPC
 * @sec_epc_func_no: unique (physical) function number within the secondary EPC
 * @group: configfs group associated with the EPF device
 */
काष्ठा pci_epf अणु
	काष्ठा device		dev;
	स्थिर अक्षर		*name;
	काष्ठा pci_epf_header	*header;
	काष्ठा pci_epf_bar	bar[6];
	u8			msi_पूर्णांकerrupts;
	u16			msix_पूर्णांकerrupts;
	u8			func_no;

	काष्ठा pci_epc		*epc;
	काष्ठा pci_epf_driver	*driver;
	काष्ठा list_head	list;
	काष्ठा notअगरier_block   nb;
	/* mutex to protect against concurrent access of pci_epf_ops */
	काष्ठा mutex		lock;

	/* Below members are to attach secondary EPC to an endpoपूर्णांक function */
	काष्ठा pci_epc		*sec_epc;
	काष्ठा list_head	sec_epc_list;
	काष्ठा pci_epf_bar	sec_epc_bar[6];
	u8			sec_epc_func_no;
	काष्ठा config_group	*group;
पूर्ण;

/**
 * काष्ठा pci_epf_msix_tbl - represents the MSIX table entry काष्ठाure
 * @msg_addr: Writes to this address will trigger MSIX पूर्णांकerrupt in host
 * @msg_data: Data that should be written to @msg_addr to trigger MSIX पूर्णांकerrupt
 * @vector_ctrl: Identअगरies अगर the function is prohibited from sending a message
 * using this MSIX table entry
 */
काष्ठा pci_epf_msix_tbl अणु
	u64 msg_addr;
	u32 msg_data;
	u32 vector_ctrl;
पूर्ण;

#घोषणा to_pci_epf(epf_dev) container_of((epf_dev), काष्ठा pci_epf, dev)

#घोषणा pci_epf_रेजिस्टर_driver(driver)    \
		__pci_epf_रेजिस्टर_driver((driver), THIS_MODULE)

अटल अंतरभूत व्योम epf_set_drvdata(काष्ठा pci_epf *epf, व्योम *data)
अणु
	dev_set_drvdata(&epf->dev, data);
पूर्ण

अटल अंतरभूत व्योम *epf_get_drvdata(काष्ठा pci_epf *epf)
अणु
	वापस dev_get_drvdata(&epf->dev);
पूर्ण

काष्ठा pci_epf *pci_epf_create(स्थिर अक्षर *name);
व्योम pci_epf_destroy(काष्ठा pci_epf *epf);
पूर्णांक __pci_epf_रेजिस्टर_driver(काष्ठा pci_epf_driver *driver,
			      काष्ठा module *owner);
व्योम pci_epf_unरेजिस्टर_driver(काष्ठा pci_epf_driver *driver);
व्योम *pci_epf_alloc_space(काष्ठा pci_epf *epf, माप_प्रकार size, क्रमागत pci_barno bar,
			  माप_प्रकार align, क्रमागत pci_epc_पूर्णांकerface_type type);
व्योम pci_epf_मुक्त_space(काष्ठा pci_epf *epf, व्योम *addr, क्रमागत pci_barno bar,
			क्रमागत pci_epc_पूर्णांकerface_type type);
पूर्णांक pci_epf_bind(काष्ठा pci_epf *epf);
व्योम pci_epf_unbind(काष्ठा pci_epf *epf);
काष्ठा config_group *pci_epf_type_add_cfs(काष्ठा pci_epf *epf,
					  काष्ठा config_group *group);
#पूर्ण_अगर /* __LINUX_PCI_EPF_H */
