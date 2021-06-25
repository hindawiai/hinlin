<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * edac_module.h
 *
 * For defining functions/data क्रम within the EDAC_CORE module only
 *
 * written by करोug thompson <norsk5@xmission.h>
 */

#अगर_अघोषित	__EDAC_MODULE_H__
#घोषणा	__EDAC_MODULE_H__

#समावेश "edac_mc.h"
#समावेश "edac_pci.h"
#समावेश "edac_device.h"

/*
 * INTERNAL EDAC MODULE:
 * EDAC memory controller sysfs create/हटाओ functions
 * and setup/tearकरोwn functions
 *
 * edac_mc objects
 */
	/* on edac_mc_sysfs.c */
पूर्णांक edac_mc_sysfs_init(व्योम);
व्योम edac_mc_sysfs_निकास(व्योम);
बाह्य पूर्णांक edac_create_sysfs_mci_device(काष्ठा mem_ctl_info *mci,
					स्थिर काष्ठा attribute_group **groups);
बाह्य व्योम edac_हटाओ_sysfs_mci_device(काष्ठा mem_ctl_info *mci);
बाह्य पूर्णांक edac_get_log_ue(व्योम);
बाह्य पूर्णांक edac_get_log_ce(व्योम);
बाह्य पूर्णांक edac_get_panic_on_ue(व्योम);
बाह्य पूर्णांक edac_mc_get_log_ue(व्योम);
बाह्य पूर्णांक edac_mc_get_log_ce(व्योम);
बाह्य पूर्णांक edac_mc_get_panic_on_ue(व्योम);
बाह्य पूर्णांक edac_get_poll_msec(व्योम);
बाह्य अचिन्हित पूर्णांक edac_mc_get_poll_msec(व्योम);

अचिन्हित edac_dimm_info_location(काष्ठा dimm_info *dimm, अक्षर *buf,
				 अचिन्हित len);

	/* on edac_device.c */
बाह्य पूर्णांक edac_device_रेजिस्टर_sysfs_मुख्य_kobj(
				काष्ठा edac_device_ctl_info *edac_dev);
बाह्य व्योम edac_device_unरेजिस्टर_sysfs_मुख्य_kobj(
				काष्ठा edac_device_ctl_info *edac_dev);
बाह्य पूर्णांक edac_device_create_sysfs(काष्ठा edac_device_ctl_info *edac_dev);
बाह्य व्योम edac_device_हटाओ_sysfs(काष्ठा edac_device_ctl_info *edac_dev);

/* edac core workqueue: single CPU mode */
पूर्णांक edac_workqueue_setup(व्योम);
व्योम edac_workqueue_tearकरोwn(व्योम);
bool edac_queue_work(काष्ठा delayed_work *work, अचिन्हित दीर्घ delay);
bool edac_stop_work(काष्ठा delayed_work *work);
bool edac_mod_work(काष्ठा delayed_work *work, अचिन्हित दीर्घ delay);

बाह्य व्योम edac_device_reset_delay_period(काष्ठा edac_device_ctl_info
					   *edac_dev, अचिन्हित दीर्घ value);
बाह्य व्योम edac_mc_reset_delay_period(अचिन्हित दीर्घ value);

बाह्य व्योम *edac_align_ptr(व्योम **p, अचिन्हित size, पूर्णांक n_elems);

/*
 * EDAC debugfs functions
 */

#घोषणा edac_debugfs_हटाओ_recursive debugfs_हटाओ_recursive
#घोषणा edac_debugfs_हटाओ debugfs_हटाओ
#अगर_घोषित CONFIG_EDAC_DEBUG
व्योम edac_debugfs_init(व्योम);
व्योम edac_debugfs_निकास(व्योम);
व्योम edac_create_debugfs_nodes(काष्ठा mem_ctl_info *mci);
काष्ठा dentry *edac_debugfs_create_dir(स्थिर अक्षर *स_नाम);
काष्ठा dentry *
edac_debugfs_create_dir_at(स्थिर अक्षर *स_नाम, काष्ठा dentry *parent);
काष्ठा dentry *
edac_debugfs_create_file(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			 व्योम *data, स्थिर काष्ठा file_operations *fops);
व्योम edac_debugfs_create_x8(स्थिर अक्षर *name, umode_t mode,
			    काष्ठा dentry *parent, u8 *value);
व्योम edac_debugfs_create_x16(स्थिर अक्षर *name, umode_t mode,
			     काष्ठा dentry *parent, u16 *value);
व्योम edac_debugfs_create_x32(स्थिर अक्षर *name, umode_t mode,
			     काष्ठा dentry *parent, u32 *value);
#अन्यथा
अटल अंतरभूत व्योम edac_debugfs_init(व्योम)					अणु पूर्ण
अटल अंतरभूत व्योम edac_debugfs_निकास(व्योम)					अणु पूर्ण
अटल अंतरभूत व्योम edac_create_debugfs_nodes(काष्ठा mem_ctl_info *mci)		अणु पूर्ण
अटल अंतरभूत काष्ठा dentry *edac_debugfs_create_dir(स्थिर अक्षर *स_नाम)	अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा dentry *
edac_debugfs_create_dir_at(स्थिर अक्षर *स_नाम, काष्ठा dentry *parent)		अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा dentry *
edac_debugfs_create_file(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			 व्योम *data, स्थिर काष्ठा file_operations *fops)	अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम edac_debugfs_create_x8(स्थिर अक्षर *name, umode_t mode,
					  काष्ठा dentry *parent, u8 *value)	अणु पूर्ण
अटल अंतरभूत व्योम edac_debugfs_create_x16(स्थिर अक्षर *name, umode_t mode,
					   काष्ठा dentry *parent, u16 *value)	अणु पूर्ण
अटल अंतरभूत व्योम edac_debugfs_create_x32(स्थिर अक्षर *name, umode_t mode,
		       काष्ठा dentry *parent, u32 *value)			अणु पूर्ण
#पूर्ण_अगर

/*
 * EDAC PCI functions
 */
#अगर_घोषित	CONFIG_PCI
बाह्य व्योम edac_pci_करो_parity_check(व्योम);
बाह्य व्योम edac_pci_clear_parity_errors(व्योम);
बाह्य पूर्णांक edac_sysfs_pci_setup(व्योम);
बाह्य व्योम edac_sysfs_pci_tearकरोwn(व्योम);
बाह्य पूर्णांक edac_pci_get_check_errors(व्योम);
बाह्य पूर्णांक edac_pci_get_poll_msec(व्योम);
बाह्य व्योम edac_pci_हटाओ_sysfs(काष्ठा edac_pci_ctl_info *pci);
बाह्य व्योम edac_pci_handle_pe(काष्ठा edac_pci_ctl_info *pci, स्थिर अक्षर *msg);
बाह्य व्योम edac_pci_handle_npe(काष्ठा edac_pci_ctl_info *pci,
				स्थिर अक्षर *msg);
#अन्यथा				/* CONFIG_PCI */
/* pre-process these away */
#घोषणा edac_pci_करो_parity_check()
#घोषणा edac_pci_clear_parity_errors()
#घोषणा edac_sysfs_pci_setup()  (0)
#घोषणा edac_sysfs_pci_tearकरोwn()
#घोषणा edac_pci_get_check_errors()
#घोषणा edac_pci_get_poll_msec()
#घोषणा edac_pci_handle_pe()
#घोषणा edac_pci_handle_npe()
#पूर्ण_अगर				/* CONFIG_PCI */

#पूर्ण_अगर				/* __EDAC_MODULE_H__ */
