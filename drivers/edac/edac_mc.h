<शैली गुरु>
/*
 * Defines, काष्ठाures, APIs क्रम edac_mc module
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

#अगर_अघोषित _EDAC_MC_H_
#घोषणा _EDAC_MC_H_

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/pci.h>
#समावेश <linux/समय.स>
#समावेश <linux/nmi.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/completion.h>
#समावेश <linux/kobject.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/edac.h>

#अगर PAGE_SHIFT < 20
#घोषणा PAGES_TO_MiB(pages)	((pages) >> (20 - PAGE_SHIFT))
#घोषणा MiB_TO_PAGES(mb)	((mb) << (20 - PAGE_SHIFT))
#अन्यथा				/* PAGE_SHIFT > 20 */
#घोषणा PAGES_TO_MiB(pages)	((pages) << (PAGE_SHIFT - 20))
#घोषणा MiB_TO_PAGES(mb)	((mb) >> (PAGE_SHIFT - 20))
#पूर्ण_अगर

#घोषणा edac_prपूर्णांकk(level, prefix, fmt, arg...) \
	prपूर्णांकk(level "EDAC " prefix ": " fmt, ##arg)

#घोषणा edac_mc_prपूर्णांकk(mci, level, fmt, arg...) \
	prपूर्णांकk(level "EDAC MC%d: " fmt, mci->mc_idx, ##arg)

#घोषणा edac_mc_chipset_prपूर्णांकk(mci, level, prefix, fmt, arg...) \
	prपूर्णांकk(level "EDAC " prefix " MC%d: " fmt, mci->mc_idx, ##arg)

#घोषणा edac_device_prपूर्णांकk(ctl, level, fmt, arg...) \
	prपूर्णांकk(level "EDAC DEVICE%d: " fmt, ctl->dev_idx, ##arg)

#घोषणा edac_pci_prपूर्णांकk(ctl, level, fmt, arg...) \
	prपूर्णांकk(level "EDAC PCI%d: " fmt, ctl->pci_idx, ##arg)

/* prefixes क्रम edac_prपूर्णांकk() and edac_mc_prपूर्णांकk() */
#घोषणा EDAC_MC "MC"
#घोषणा EDAC_PCI "PCI"
#घोषणा EDAC_DEBUG "DEBUG"

बाह्य स्थिर अक्षर * स्थिर edac_mem_types[];

#अगर_घोषित CONFIG_EDAC_DEBUG
बाह्य पूर्णांक edac_debug_level;

#घोषणा edac_dbg(level, fmt, ...)					\
करो अणु									\
	अगर (level <= edac_debug_level)					\
		edac_prपूर्णांकk(KERN_DEBUG, EDAC_DEBUG,			\
			    "%s: " fmt, __func__, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#अन्यथा				/* !CONFIG_EDAC_DEBUG */

#घोषणा edac_dbg(level, fmt, ...)					\
करो अणु									\
	अगर (0)								\
		edac_prपूर्णांकk(KERN_DEBUG, EDAC_DEBUG,			\
			    "%s: " fmt, __func__, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#पूर्ण_अगर				/* !CONFIG_EDAC_DEBUG */

#घोषणा PCI_VEND_DEV(vend, dev) PCI_VENDOR_ID_ ## vend, \
	PCI_DEVICE_ID_ ## vend ## _ ## dev

#घोषणा edac_dev_name(dev) (dev)->dev_name

#घोषणा to_mci(k) container_of(k, काष्ठा mem_ctl_info, dev)

/**
 * edac_mc_alloc() - Allocate and partially fill a काष्ठा &mem_ctl_info.
 *
 * @mc_num:		Memory controller number
 * @n_layers:		Number of MC hierarchy layers
 * @layers:		Describes each layer as seen by the Memory Controller
 * @sz_pvt:		size of निजी storage needed
 *
 *
 * Everything is kदो_स्मृति'ed as one big chunk - more efficient.
 * Only can be used अगर all काष्ठाures have the same lअगरeसमय - otherwise
 * you have to allocate and initialize your own काष्ठाures.
 *
 * Use edac_mc_मुक्त() to मुक्त mc काष्ठाures allocated by this function.
 *
 * .. note::
 *
 *   drivers handle multi-rank memories in dअगरferent ways: in some
 *   drivers, one multi-rank memory stick is mapped as one entry, जबतक, in
 *   others, a single multi-rank memory stick would be mapped पूर्णांकo several
 *   entries. Currently, this function will allocate multiple काष्ठा dimm_info
 *   on such scenarios, as grouping the multiple ranks require drivers change.
 *
 * Returns:
 *	On success, वापस a poपूर्णांकer to काष्ठा mem_ctl_info poपूर्णांकer;
 *	%शून्य otherwise
 */
काष्ठा mem_ctl_info *edac_mc_alloc(अचिन्हित पूर्णांक mc_num,
				   अचिन्हित पूर्णांक n_layers,
				   काष्ठा edac_mc_layer *layers,
				   अचिन्हित पूर्णांक sz_pvt);

/**
 * edac_get_owner - Return the owner's mod_name of EDAC MC
 *
 * Returns:
 *	Poपूर्णांकer to mod_name string when EDAC MC is owned. शून्य otherwise.
 */
बाह्य स्थिर अक्षर *edac_get_owner(व्योम);

/*
 * edac_mc_add_mc_with_groups() - Insert the @mci काष्ठाure पूर्णांकo the mci
 *	global list and create sysfs entries associated with @mci काष्ठाure.
 *
 * @mci: poपूर्णांकer to the mci काष्ठाure to be added to the list
 * @groups: optional attribute groups क्रम the driver-specअगरic sysfs entries
 *
 * Returns:
 *	0 on Success, or an error code on failure
 */
बाह्य पूर्णांक edac_mc_add_mc_with_groups(काष्ठा mem_ctl_info *mci,
				      स्थिर काष्ठा attribute_group **groups);
#घोषणा edac_mc_add_mc(mci)	edac_mc_add_mc_with_groups(mci, शून्य)

/**
 * edac_mc_मुक्त() -  Frees a previously allocated @mci काष्ठाure
 *
 * @mci: poपूर्णांकer to a काष्ठा mem_ctl_info काष्ठाure
 */
बाह्य व्योम edac_mc_मुक्त(काष्ठा mem_ctl_info *mci);

/**
 * edac_has_mcs() - Check अगर any MCs have been allocated.
 *
 * Returns:
 *	True अगर MC instances have been रेजिस्टरed successfully.
 *	False otherwise.
 */
बाह्य bool edac_has_mcs(व्योम);

/**
 * edac_mc_find() - Search क्रम a mem_ctl_info काष्ठाure whose index is @idx.
 *
 * @idx: index to be seek
 *
 * If found, वापस a poपूर्णांकer to the काष्ठाure.
 * Else वापस शून्य.
 */
बाह्य काष्ठा mem_ctl_info *edac_mc_find(पूर्णांक idx);

/**
 * find_mci_by_dev() - Scan list of controllers looking क्रम the one that
 *	manages the @dev device.
 *
 * @dev: poपूर्णांकer to a काष्ठा device related with the MCI
 *
 * Returns: on success, वापसs a poपूर्णांकer to काष्ठा &mem_ctl_info;
 * %शून्य otherwise.
 */
बाह्य काष्ठा mem_ctl_info *find_mci_by_dev(काष्ठा device *dev);

/**
 * edac_mc_del_mc() - Remove sysfs entries क्रम mci काष्ठाure associated with
 *	@dev and हटाओ mci काष्ठाure from global list.
 *
 * @dev: Poपूर्णांकer to काष्ठा &device representing mci काष्ठाure to हटाओ.
 *
 * Returns: poपूर्णांकer to हटाओd mci काष्ठाure, or %शून्य अगर device not found.
 */
बाह्य काष्ठा mem_ctl_info *edac_mc_del_mc(काष्ठा device *dev);

/**
 * edac_mc_find_csrow_by_page() - Ancillary routine to identअगरy what csrow
 *	contains a memory page.
 *
 * @mci: poपूर्णांकer to a काष्ठा mem_ctl_info काष्ठाure
 * @page: memory page to find
 *
 * Returns: on success, वापसs the csrow. -1 अगर not found.
 */
बाह्य पूर्णांक edac_mc_find_csrow_by_page(काष्ठा mem_ctl_info *mci,
				      अचिन्हित दीर्घ page);

/**
 * edac_raw_mc_handle_error() - Reports a memory event to userspace without
 *	करोing anything to discover the error location.
 *
 * @e:			error description
 *
 * This raw function is used पूर्णांकernally by edac_mc_handle_error(). It should
 * only be called directly when the hardware error come directly from BIOS,
 * like in the हाल of APEI GHES driver.
 */
व्योम edac_raw_mc_handle_error(काष्ठा edac_raw_error_desc *e);

/**
 * edac_mc_handle_error() - Reports a memory event to userspace.
 *
 * @type:		severity of the error (CE/UE/Fatal)
 * @mci:		a काष्ठा mem_ctl_info poपूर्णांकer
 * @error_count:	Number of errors of the same type
 * @page_frame_number:	mem page where the error occurred
 * @offset_in_page:	offset of the error inside the page
 * @syndrome:		ECC syndrome
 * @top_layer:		Memory layer[0] position
 * @mid_layer:		Memory layer[1] position
 * @low_layer:		Memory layer[2] position
 * @msg:		Message meaningful to the end users that
 *			explains the event
 * @other_detail:	Technical details about the event that
 *			may help hardware manufacturers and
 *			EDAC developers to analyse the event
 */
व्योम edac_mc_handle_error(स्थिर क्रमागत hw_event_mc_err_type type,
			  काष्ठा mem_ctl_info *mci,
			  स्थिर u16 error_count,
			  स्थिर अचिन्हित दीर्घ page_frame_number,
			  स्थिर अचिन्हित दीर्घ offset_in_page,
			  स्थिर अचिन्हित दीर्घ syndrome,
			  स्थिर पूर्णांक top_layer,
			  स्थिर पूर्णांक mid_layer,
			  स्थिर पूर्णांक low_layer,
			  स्थिर अक्षर *msg,
			  स्थिर अक्षर *other_detail);

/*
 * edac misc APIs
 */
बाह्य अक्षर *edac_op_state_to_string(पूर्णांक op_state);

#पूर्ण_अगर				/* _EDAC_MC_H_ */
