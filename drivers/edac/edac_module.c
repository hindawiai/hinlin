<शैली गुरु>
/*
 * edac_module.c
 *
 * (C) 2007 www.softwarebiपंचांगaker.com
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * Author: Doug Thompson <करोugthompson@xmission.com>
 *
 */
#समावेश <linux/edac.h>

#समावेश "edac_mc.h"
#समावेश "edac_module.h"

#घोषणा EDAC_VERSION "Ver: 3.0.0"

#अगर_घोषित CONFIG_EDAC_DEBUG

अटल पूर्णांक edac_set_debug_level(स्थिर अक्षर *buf,
				स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val > 4)
		वापस -EINVAL;

	वापस param_set_पूर्णांक(buf, kp);
पूर्ण

/* Values of 0 to 4 will generate output */
पूर्णांक edac_debug_level = 2;
EXPORT_SYMBOL_GPL(edac_debug_level);

module_param_call(edac_debug_level, edac_set_debug_level, param_get_पूर्णांक,
		  &edac_debug_level, 0644);
MODULE_PARM_DESC(edac_debug_level, "EDAC debug level: [0-4], default: 2");
#पूर्ण_अगर

/*
 * edac_op_state_to_string()
 */
अक्षर *edac_op_state_to_string(पूर्णांक opstate)
अणु
	अगर (opstate == OP_RUNNING_POLL)
		वापस "POLLED";
	अन्यथा अगर (opstate == OP_RUNNING_INTERRUPT)
		वापस "INTERRUPT";
	अन्यथा अगर (opstate == OP_RUNNING_POLL_INTR)
		वापस "POLL-INTR";
	अन्यथा अगर (opstate == OP_ALLOC)
		वापस "ALLOC";
	अन्यथा अगर (opstate == OP_OFFLINE)
		वापस "OFFLINE";

	वापस "UNKNOWN";
पूर्ण

/*
 * sysfs object: /sys/devices/प्रणाली/edac
 *	need to export to other files
 */
अटल काष्ठा bus_type edac_subsys = अणु
	.name = "edac",
	.dev_name = "edac",
पूर्ण;

अटल पूर्णांक edac_subsys_init(व्योम)
अणु
	पूर्णांक err;

	/* create the /sys/devices/प्रणाली/edac directory */
	err = subsys_प्रणाली_रेजिस्टर(&edac_subsys, शून्य);
	अगर (err)
		prपूर्णांकk(KERN_ERR "Error registering toplevel EDAC sysfs dir\n");

	वापस err;
पूर्ण

अटल व्योम edac_subsys_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&edac_subsys);
पूर्ण

/* वापस poपूर्णांकer to the 'edac' node in sysfs */
काष्ठा bus_type *edac_get_sysfs_subsys(व्योम)
अणु
	वापस &edac_subsys;
पूर्ण
EXPORT_SYMBOL_GPL(edac_get_sysfs_subsys);
/*
 * edac_init
 *      module initialization entry poपूर्णांक
 */
अटल पूर्णांक __init edac_init(व्योम)
अणु
	पूर्णांक err = 0;

	edac_prपूर्णांकk(KERN_INFO, EDAC_MC, EDAC_VERSION "\n");

	err = edac_subsys_init();
	अगर (err)
		वापस err;

	/*
	 * Harvest and clear any boot/initialization PCI parity errors
	 *
	 * FIXME: This only clears errors logged by devices present at समय of
	 *      module initialization.  We should also करो an initial clear
	 *      of each newly hotplugged device.
	 */
	edac_pci_clear_parity_errors();

	err = edac_mc_sysfs_init();
	अगर (err)
		जाओ err_sysfs;

	edac_debugfs_init();

	err = edac_workqueue_setup();
	अगर (err) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC, "Failure initializing workqueue\n");
		जाओ err_wq;
	पूर्ण

	वापस 0;

err_wq:
	edac_debugfs_निकास();
	edac_mc_sysfs_निकास();

err_sysfs:
	edac_subsys_निकास();

	वापस err;
पूर्ण

/*
 * edac_निकास()
 *      module निकास/termination function
 */
अटल व्योम __निकास edac_निकास(व्योम)
अणु
	edac_dbg(0, "\n");

	/* tear करोwn the various subप्रणालीs */
	edac_workqueue_tearकरोwn();
	edac_mc_sysfs_निकास();
	edac_debugfs_निकास();
	edac_subsys_निकास();
पूर्ण

/*
 * Inक्रमm the kernel of our entry and निकास poपूर्णांकs
 */
subsys_initcall(edac_init);
module_निकास(edac_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Doug Thompson www.softwarebitmaker.com, et al");
MODULE_DESCRIPTION("Core library routines for EDAC reporting");
