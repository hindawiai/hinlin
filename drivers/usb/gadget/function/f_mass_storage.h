<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित USB_F_MASS_STORAGE_H
#घोषणा USB_F_MASS_STORAGE_H

#समावेश <linux/usb/composite.h>
#समावेश "storage_common.h"

काष्ठा fsg_module_parameters अणु
	अक्षर		*file[FSG_MAX_LUNS];
	bool		ro[FSG_MAX_LUNS];
	bool		removable[FSG_MAX_LUNS];
	bool		cdrom[FSG_MAX_LUNS];
	bool		nofua[FSG_MAX_LUNS];

	अचिन्हित पूर्णांक	file_count, ro_count, removable_count, cdrom_count;
	अचिन्हित पूर्णांक	nofua_count;
	अचिन्हित पूर्णांक	luns;	/* nluns */
	bool		stall;	/* can_stall */
पूर्ण;

#घोषणा _FSG_MODULE_PARAM_ARRAY(prefix, params, name, type, desc)	\
	module_param_array_named(prefix ## name, params.name, type,	\
				 &prefix ## params.name ## _count,	\
				 S_IRUGO);				\
	MODULE_PARM_DESC(prefix ## name, desc)

#घोषणा _FSG_MODULE_PARAM(prefix, params, name, type, desc)		\
	module_param_named(prefix ## name, params.name, type,		\
			   S_IRUGO);					\
	MODULE_PARM_DESC(prefix ## name, desc)

#घोषणा __FSG_MODULE_PARAMETERS(prefix, params)				\
	_FSG_MODULE_PARAM_ARRAY(prefix, params, file, अक्षरp,		\
				"names of backing files or devices");	\
	_FSG_MODULE_PARAM_ARRAY(prefix, params, ro, bool,		\
				"true to force read-only");		\
	_FSG_MODULE_PARAM_ARRAY(prefix, params, removable, bool,	\
				"true to simulate removable media");	\
	_FSG_MODULE_PARAM_ARRAY(prefix, params, cdrom, bool,		\
				"true to simulate CD-ROM instead of disk"); \
	_FSG_MODULE_PARAM_ARRAY(prefix, params, nofua, bool,		\
				"true to ignore SCSI WRITE(10,12) FUA bit"); \
	_FSG_MODULE_PARAM(prefix, params, luns, uपूर्णांक,			\
			  "number of LUNs");				\
	_FSG_MODULE_PARAM(prefix, params, stall, bool,			\
			  "false to prevent bulk stalls")

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS

#घोषणा FSG_MODULE_PARAMETERS(prefix, params)				\
	__FSG_MODULE_PARAMETERS(prefix, params);			\
	module_param_named(num_buffers, fsg_num_buffers, uपूर्णांक, S_IRUGO);\
	MODULE_PARM_DESC(num_buffers, "Number of pipeline buffers")
#अन्यथा

#घोषणा FSG_MODULE_PARAMETERS(prefix, params)				\
	__FSG_MODULE_PARAMETERS(prefix, params)

#पूर्ण_अगर

काष्ठा fsg_common;

/* FSF callback functions */
काष्ठा fsg_lun_opts अणु
	काष्ठा config_group group;
	काष्ठा fsg_lun *lun;
	पूर्णांक lun_id;
पूर्ण;

काष्ठा fsg_opts अणु
	काष्ठा fsg_common *common;
	काष्ठा usb_function_instance func_inst;
	काष्ठा fsg_lun_opts lun0;
	काष्ठा config_group *शेष_groups[2];
	bool no_configfs; /* क्रम legacy gadमाला_लो */

	/*
	 * Read/ग_लिखो access to configfs attributes is handled by configfs.
	 *
	 * This is to protect the data from concurrent access by पढ़ो/ग_लिखो
	 * and create symlink/हटाओ symlink.
	 */
	काष्ठा mutex			lock;
	पूर्णांक				refcnt;
पूर्ण;

काष्ठा fsg_lun_config अणु
	स्थिर अक्षर *filename;
	अक्षर ro;
	अक्षर removable;
	अक्षर cdrom;
	अक्षर nofua;
	अक्षर inquiry_string[INQUIRY_STRING_LEN];
पूर्ण;

काष्ठा fsg_config अणु
	अचिन्हित nluns;
	काष्ठा fsg_lun_config luns[FSG_MAX_LUNS];

	/* Callback functions. */
	स्थिर काष्ठा fsg_operations	*ops;
	/* Gadget's निजी data. */
	व्योम			*निजी_data;

	स्थिर अक्षर *venकरोr_name;		/*  8 अक्षरacters or less */
	स्थिर अक्षर *product_name;		/* 16 अक्षरacters or less */

	अक्षर			can_stall;
	अचिन्हित पूर्णांक		fsg_num_buffers;
पूर्ण;

अटल अंतरभूत काष्ठा fsg_opts *
fsg_opts_from_func_inst(स्थिर काष्ठा usb_function_instance *fi)
अणु
	वापस container_of(fi, काष्ठा fsg_opts, func_inst);
पूर्ण

व्योम fsg_common_set_sysfs(काष्ठा fsg_common *common, bool sysfs);

पूर्णांक fsg_common_set_num_buffers(काष्ठा fsg_common *common, अचिन्हित पूर्णांक n);

व्योम fsg_common_मुक्त_buffers(काष्ठा fsg_common *common);

पूर्णांक fsg_common_set_cdev(काष्ठा fsg_common *common,
			काष्ठा usb_composite_dev *cdev, bool can_stall);

व्योम fsg_common_हटाओ_lun(काष्ठा fsg_lun *lun);

व्योम fsg_common_हटाओ_luns(काष्ठा fsg_common *common);

पूर्णांक fsg_common_create_lun(काष्ठा fsg_common *common, काष्ठा fsg_lun_config *cfg,
			  अचिन्हित पूर्णांक id, स्थिर अक्षर *name,
			  स्थिर अक्षर **name_pfx);

पूर्णांक fsg_common_create_luns(काष्ठा fsg_common *common, काष्ठा fsg_config *cfg);

व्योम fsg_common_set_inquiry_string(काष्ठा fsg_common *common, स्थिर अक्षर *vn,
				   स्थिर अक्षर *pn);

व्योम fsg_config_from_params(काष्ठा fsg_config *cfg,
			    स्थिर काष्ठा fsg_module_parameters *params,
			    अचिन्हित पूर्णांक fsg_num_buffers);

#पूर्ण_अगर /* USB_F_MASS_STORAGE_H */
