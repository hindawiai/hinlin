<शैली गुरु>
/*
 * Defines, काष्ठाures, APIs क्रम edac_pci and edac_pci_sysfs
 *
 * (C) 2007 Linux Networx (http://lnxi.com)
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Written by Thayne Harbaugh
 * Based on work by Dan Hollis <goemon at anime करोt net> and others.
 *	http://www.anime.net/~goemon/linux-ecc/
 *
 * NMI handling support added by
 *     Dave Peterson <dsp@llnl.gov> <dave_peterson@pobox.com>
 *
 * Refactored क्रम multi-source files:
 *	Doug Thompson <norsk5@xmission.com>
 *
 * Please look at Documentation/driver-api/edac.rst क्रम more info about
 * EDAC core काष्ठाs and functions.
 */

#अगर_अघोषित _EDAC_PCI_H_
#घोषणा _EDAC_PCI_H_

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/edac.h>
#समावेश <linux/kobject.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#अगर_घोषित CONFIG_PCI

काष्ठा edac_pci_counter अणु
	atomic_t pe_count;
	atomic_t npe_count;
पूर्ण;

/*
 * Abstract edac_pci control info काष्ठाure
 *
 */
काष्ठा edac_pci_ctl_info अणु
	/* क्रम global list of edac_pci_ctl_info काष्ठाs */
	काष्ठा list_head link;

	पूर्णांक pci_idx;

	काष्ठा bus_type *edac_subsys;	/* poपूर्णांकer to subप्रणाली */

	/* the पूर्णांकernal state of this controller instance */
	पूर्णांक op_state;
	/* work काष्ठा क्रम this instance */
	काष्ठा delayed_work work;

	/* poपूर्णांकer to edac polling checking routine:
	 *      If NOT शून्य: poपूर्णांकs to polling check routine
	 *      If शून्य: Then assumes INTERRUPT operation, where
	 *              MC driver will receive events
	 */
	व्योम (*edac_check) (काष्ठा edac_pci_ctl_info * edac_dev);

	काष्ठा device *dev;	/* poपूर्णांकer to device काष्ठाure */

	स्थिर अक्षर *mod_name;	/* module name */
	स्थिर अक्षर *ctl_name;	/* edac controller  name */
	स्थिर अक्षर *dev_name;	/* pci/platक्रमm/etc... name */

	व्योम *pvt_info;		/* poपूर्णांकer to 'private driver' info */

	अचिन्हित दीर्घ start_समय;	/* edac_pci load start समय (jअगरfies) */

	काष्ठा completion complete;

	/* sysfs top name under 'edac' directory
	 * and instance name:
	 *      cpu/cpu0/...
	 *      cpu/cpu1/...
	 *      cpu/cpu2/...
	 *      ...
	 */
	अक्षर name[EDAC_DEVICE_NAME_LEN + 1];

	/* Event counters क्रम the this whole EDAC Device */
	काष्ठा edac_pci_counter counters;

	/* edac sysfs device control क्रम the 'name'
	 * device this काष्ठाure controls
	 */
	काष्ठा kobject kobj;
पूर्ण;

#घोषणा to_edac_pci_ctl_work(w) \
		container_of(w, काष्ठा edac_pci_ctl_info,work)

/* ग_लिखो all or some bits in a byte-रेजिस्टर*/
अटल अंतरभूत व्योम pci_ग_लिखो_bits8(काष्ठा pci_dev *pdev, पूर्णांक offset, u8 value,
				   u8 mask)
अणु
	अगर (mask != 0xff) अणु
		u8 buf;

		pci_पढ़ो_config_byte(pdev, offset, &buf);
		value &= mask;
		buf &= ~mask;
		value |= buf;
	पूर्ण

	pci_ग_लिखो_config_byte(pdev, offset, value);
पूर्ण

/* ग_लिखो all or some bits in a word-रेजिस्टर*/
अटल अंतरभूत व्योम pci_ग_लिखो_bits16(काष्ठा pci_dev *pdev, पूर्णांक offset,
				    u16 value, u16 mask)
अणु
	अगर (mask != 0xffff) अणु
		u16 buf;

		pci_पढ़ो_config_word(pdev, offset, &buf);
		value &= mask;
		buf &= ~mask;
		value |= buf;
	पूर्ण

	pci_ग_लिखो_config_word(pdev, offset, value);
पूर्ण

/*
 * pci_ग_लिखो_bits32
 *
 * edac local routine to करो pci_ग_लिखो_config_dword, but adds
 * a mask parameter. If mask is all ones, ignore the mask.
 * Otherwise utilize the mask to isolate specअगरied bits
 *
 * ग_लिखो all or some bits in a dword-रेजिस्टर
 */
अटल अंतरभूत व्योम pci_ग_लिखो_bits32(काष्ठा pci_dev *pdev, पूर्णांक offset,
				    u32 value, u32 mask)
अणु
	अगर (mask != 0xffffffff) अणु
		u32 buf;

		pci_पढ़ो_config_dword(pdev, offset, &buf);
		value &= mask;
		buf &= ~mask;
		value |= buf;
	पूर्ण

	pci_ग_लिखो_config_dword(pdev, offset, value);
पूर्ण

#पूर्ण_अगर				/* CONFIG_PCI */

/*
 * edac_pci APIs
 */

/**
 * edac_pci_alloc_ctl_info:
 *	The alloc() function क्रम the 'edac_pci' control info
 *	काष्ठाure.
 *
 * @sz_pvt: size of the निजी info at काष्ठा &edac_pci_ctl_info
 * @edac_pci_name: name of the PCI device
 *
 * The chip driver will allocate one of these क्रम each
 * edac_pci it is going to control/रेजिस्टर with the EDAC CORE.
 *
 * Returns: a poपूर्णांकer to काष्ठा &edac_pci_ctl_info on success; %शून्य otherwise.
 */
बाह्य काष्ठा edac_pci_ctl_info *edac_pci_alloc_ctl_info(अचिन्हित पूर्णांक sz_pvt,
				स्थिर अक्षर *edac_pci_name);

/**
 * edac_pci_मुक्त_ctl_info():
 *	Last action on the pci control काष्ठाure.
 *
 * @pci: poपूर्णांकer to काष्ठा &edac_pci_ctl_info
 *
 * Calls the हटाओ sysfs inक्रमmation, which will unरेजिस्टर
 * this control काष्ठा's kobj. When that kobj's ref count
 * goes to zero, its release function will be call and then
 * kमुक्त() the memory.
 */
बाह्य व्योम edac_pci_मुक्त_ctl_info(काष्ठा edac_pci_ctl_info *pci);

/**
 * edac_pci_alloc_index: Allocate a unique PCI index number
 *
 * Returns:
 *      allocated index number
 *
 */
बाह्य पूर्णांक edac_pci_alloc_index(व्योम);

/**
 * edac_pci_add_device(): Insert the 'edac_dev' काष्ठाure पूर्णांकo the
 *	edac_pci global list and create sysfs entries associated with
 *	edac_pci काष्ठाure.
 *
 * @pci: poपूर्णांकer to the edac_device काष्ठाure to be added to the list
 * @edac_idx: A unique numeric identअगरier to be asचिन्हित to the
 *	'edac_pci' काष्ठाure.
 *
 * Returns:
 *	0 on Success, or an error code on failure
 */
बाह्य पूर्णांक edac_pci_add_device(काष्ठा edac_pci_ctl_info *pci, पूर्णांक edac_idx);

/**
 * edac_pci_del_device()
 *	Remove sysfs entries क्रम specअगरied edac_pci काष्ठाure and
 *	then हटाओ edac_pci काष्ठाure from global list
 *
 * @dev:
 *	Poपूर्णांकer to 'struct device' representing edac_pci काष्ठाure
 *	to हटाओ
 *
 * Returns:
 *	Poपूर्णांकer to हटाओd edac_pci काष्ठाure,
 *	or %शून्य अगर device not found
 */
बाह्य काष्ठा edac_pci_ctl_info *edac_pci_del_device(काष्ठा device *dev);

/**
 * edac_pci_create_generic_ctl()
 *	A generic स्थिरructor क्रम a PCI parity polling device
 *	Some प्रणालीs have more than one करोमुख्य of PCI busses.
 *	For प्रणालीs with one करोमुख्य, then this API will
 *	provide क्रम a generic poller.
 *
 * @dev: poपूर्णांकer to काष्ठा &device;
 * @mod_name: name of the PCI device
 *
 * This routine calls the edac_pci_alloc_ctl_info() क्रम
 * the generic device, with शेष values
 *
 * Returns: Poपूर्णांकer to काष्ठा &edac_pci_ctl_info on success, %शून्य on
 *	failure.
 */
बाह्य काष्ठा edac_pci_ctl_info *edac_pci_create_generic_ctl(
				काष्ठा device *dev,
				स्थिर अक्षर *mod_name);

/**
 * edac_pci_release_generic_ctl
 *	The release function of a generic EDAC PCI polling device
 *
 * @pci: poपूर्णांकer to काष्ठा &edac_pci_ctl_info
 */
बाह्य व्योम edac_pci_release_generic_ctl(काष्ठा edac_pci_ctl_info *pci);

/**
 * edac_pci_create_sysfs
 *	Create the controls/attributes क्रम the specअगरied EDAC PCI device
 *
 * @pci: poपूर्णांकer to काष्ठा &edac_pci_ctl_info
 */
बाह्य पूर्णांक edac_pci_create_sysfs(काष्ठा edac_pci_ctl_info *pci);

/**
 * edac_pci_हटाओ_sysfs()
 *	हटाओ the controls and attributes क्रम this EDAC PCI device
 *
 * @pci: poपूर्णांकer to काष्ठा &edac_pci_ctl_info
 */
बाह्य व्योम edac_pci_हटाओ_sysfs(काष्ठा edac_pci_ctl_info *pci);

#पूर्ण_अगर
