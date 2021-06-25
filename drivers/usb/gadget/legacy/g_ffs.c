<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * g_ffs.c -- user mode file प्रणाली API क्रम USB composite function controllers
 *
 * Copyright (C) 2010 Samsung Electronics
 * Author: Michal Nazarewicz <mina86@mina86.com>
 */

#घोषणा pr_fmt(fmt) "g_ffs: " fmt

#समावेश <linux/module.h>

#अगर defined CONFIG_USB_FUNCTIONFS_ETH || defined CONFIG_USB_FUNCTIONFS_RNDIS
#समावेश <linux/netdevice.h>

#  अगर defined USB_ETH_RNDIS
#    undef USB_ETH_RNDIS
#  endअगर
#  अगरdef CONFIG_USB_FUNCTIONFS_RNDIS
#    define USB_ETH_RNDIS y
#  endअगर

#  include "u_ecm.h"
#  include "u_gether.h"
#  अगरdef USB_ETH_RNDIS
#    include "u_rndis.h"
#    include "rndis.h"
#  endअगर
#  include "u_ether.h"

USB_ETHERNET_MODULE_PARAMETERS();

#  अगरdef CONFIG_USB_FUNCTIONFS_ETH
अटल पूर्णांक eth_bind_config(काष्ठा usb_configuration *c);
अटल काष्ठा usb_function_instance *fi_ecm;
अटल काष्ठा usb_function *f_ecm;
अटल काष्ठा usb_function_instance *fi_geth;
अटल काष्ठा usb_function *f_geth;
#  endअगर
#  अगरdef CONFIG_USB_FUNCTIONFS_RNDIS
अटल पूर्णांक bind_rndis_config(काष्ठा usb_configuration *c);
अटल काष्ठा usb_function_instance *fi_rndis;
अटल काष्ठा usb_function *f_rndis;
#  endअगर
#पूर्ण_अगर

#समावेश "u_fs.h"

#घोषणा DRIVER_NAME	"g_ffs"
#घोषणा DRIVER_DESC	"USB Function Filesystem"
#घोषणा DRIVER_VERSION	"24 Aug 2004"

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Michal Nazarewicz");
MODULE_LICENSE("GPL");

#घोषणा GFS_VENDOR_ID	0x1d6b	/* Linux Foundation */
#घोषणा GFS_PRODUCT_ID	0x0105	/* FunctionFS Gadget */

#घोषणा GFS_MAX_DEVS	10

USB_GADGET_COMPOSITE_OPTIONS();

अटल काष्ठा usb_device_descriptor gfs_dev_desc = अणु
	.bLength		= माप gfs_dev_desc,
	.bDescriptorType	= USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */
	.bDeviceClass		= USB_CLASS_PER_INTERFACE,

	.idVenकरोr		= cpu_to_le16(GFS_VENDOR_ID),
	.idProduct		= cpu_to_le16(GFS_PRODUCT_ID),
पूर्ण;

अटल अक्षर *func_names[GFS_MAX_DEVS];
अटल अचिन्हित पूर्णांक func_num;

module_param_named(bDeviceClass,    gfs_dev_desc.bDeviceClass,    byte,   0644);
MODULE_PARM_DESC(bDeviceClass, "USB Device class");
module_param_named(bDeviceSubClass, gfs_dev_desc.bDeviceSubClass, byte,   0644);
MODULE_PARM_DESC(bDeviceSubClass, "USB Device subclass");
module_param_named(bDeviceProtocol, gfs_dev_desc.bDeviceProtocol, byte,   0644);
MODULE_PARM_DESC(bDeviceProtocol, "USB Device protocol");
module_param_array_named(functions, func_names, अक्षरp, &func_num, 0);
MODULE_PARM_DESC(functions, "USB Functions list");

अटल स्थिर काष्ठा usb_descriptor_header *gfs_otg_desc[2];

/* String IDs are asचिन्हित dynamically */
अटल काष्ठा usb_string gfs_strings[] = अणु
	[USB_GADGET_MANUFACTURER_IDX].s = "",
	[USB_GADGET_PRODUCT_IDX].s = DRIVER_DESC,
	[USB_GADGET_SERIAL_IDX].s = "",
#अगर_घोषित CONFIG_USB_FUNCTIONFS_RNDIS
	अणु .s = "FunctionFS + RNDIS" पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_USB_FUNCTIONFS_ETH
	अणु .s = "FunctionFS + ECM" पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_USB_FUNCTIONFS_GENERIC
	अणु .s = "FunctionFS" पूर्ण,
#पूर्ण_अगर
	अणु  पूर्ण /* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings *gfs_dev_strings[] = अणु
	&(काष्ठा usb_gadget_strings) अणु
		.language	= 0x0409,	/* en-us */
		.strings	= gfs_strings,
	पूर्ण,
	शून्य,
पूर्ण;

काष्ठा gfs_configuration अणु
	काष्ठा usb_configuration c;
	पूर्णांक (*eth)(काष्ठा usb_configuration *c);
	पूर्णांक num;
पूर्ण;

अटल काष्ठा gfs_configuration gfs_configurations[] = अणु
#अगर_घोषित CONFIG_USB_FUNCTIONFS_RNDIS
	अणु
		.eth		= bind_rndis_config,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_FUNCTIONFS_ETH
	अणु
		.eth		= eth_bind_config,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_FUNCTIONFS_GENERIC
	अणु
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल व्योम *functionfs_acquire_dev(काष्ठा ffs_dev *dev);
अटल व्योम functionfs_release_dev(काष्ठा ffs_dev *dev);
अटल पूर्णांक functionfs_पढ़ोy_callback(काष्ठा ffs_data *ffs);
अटल व्योम functionfs_बंदd_callback(काष्ठा ffs_data *ffs);
अटल पूर्णांक gfs_bind(काष्ठा usb_composite_dev *cdev);
अटल पूर्णांक gfs_unbind(काष्ठा usb_composite_dev *cdev);
अटल पूर्णांक gfs_करो_config(काष्ठा usb_configuration *c);


अटल काष्ठा usb_composite_driver gfs_driver = अणु
	.name		= DRIVER_NAME,
	.dev		= &gfs_dev_desc,
	.strings	= gfs_dev_strings,
	.max_speed	= USB_SPEED_SUPER,
	.bind		= gfs_bind,
	.unbind		= gfs_unbind,
पूर्ण;

अटल अचिन्हित पूर्णांक missing_funcs;
अटल bool gfs_रेजिस्टरed;
अटल bool gfs_single_func;
अटल काष्ठा usb_function_instance **fi_ffs;
अटल काष्ठा usb_function **f_ffs[] = अणु
#अगर_घोषित CONFIG_USB_FUNCTIONFS_RNDIS
	शून्य,
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_FUNCTIONFS_ETH
	शून्य,
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_FUNCTIONFS_GENERIC
	शून्य,
#पूर्ण_अगर
पूर्ण;

#घोषणा N_CONF ARRAY_SIZE(f_ffs)

अटल पूर्णांक __init gfs_init(व्योम)
अणु
	काष्ठा f_fs_opts *opts;
	पूर्णांक i;
	पूर्णांक ret = 0;

	ENTER();

	अगर (func_num < 2) अणु
		gfs_single_func = true;
		func_num = 1;
	पूर्ण

	/*
	 * Allocate in one chunk क्रम easier मुख्यtenance
	 */
	f_ffs[0] = kसुस्मृति(func_num * N_CONF, माप(*f_ffs), GFP_KERNEL);
	अगर (!f_ffs[0]) अणु
		ret = -ENOMEM;
		जाओ no_func;
	पूर्ण
	क्रम (i = 1; i < N_CONF; ++i)
		f_ffs[i] = f_ffs[0] + i * func_num;

	fi_ffs = kसुस्मृति(func_num, माप(*fi_ffs), GFP_KERNEL);
	अगर (!fi_ffs) अणु
		ret = -ENOMEM;
		जाओ no_func;
	पूर्ण

	क्रम (i = 0; i < func_num; i++) अणु
		fi_ffs[i] = usb_get_function_instance("ffs");
		अगर (IS_ERR(fi_ffs[i])) अणु
			ret = PTR_ERR(fi_ffs[i]);
			--i;
			जाओ no_dev;
		पूर्ण
		opts = to_f_fs_opts(fi_ffs[i]);
		अगर (gfs_single_func)
			ret = ffs_single_dev(opts->dev);
		अन्यथा
			ret = ffs_name_dev(opts->dev, func_names[i]);
		अगर (ret)
			जाओ no_dev;
		opts->dev->ffs_पढ़ोy_callback = functionfs_पढ़ोy_callback;
		opts->dev->ffs_बंदd_callback = functionfs_बंदd_callback;
		opts->dev->ffs_acquire_dev_callback = functionfs_acquire_dev;
		opts->dev->ffs_release_dev_callback = functionfs_release_dev;
		opts->no_configfs = true;
	पूर्ण

	missing_funcs = func_num;

	वापस 0;
no_dev:
	जबतक (i >= 0)
		usb_put_function_instance(fi_ffs[i--]);
	kमुक्त(fi_ffs);
no_func:
	kमुक्त(f_ffs[0]);
	वापस ret;
पूर्ण
module_init(gfs_init);

अटल व्योम __निकास gfs_निकास(व्योम)
अणु
	पूर्णांक i;

	ENTER();

	अगर (gfs_रेजिस्टरed)
		usb_composite_unरेजिस्टर(&gfs_driver);
	gfs_रेजिस्टरed = false;

	kमुक्त(f_ffs[0]);

	क्रम (i = 0; i < func_num; i++)
		usb_put_function_instance(fi_ffs[i]);

	kमुक्त(fi_ffs);
पूर्ण
module_निकास(gfs_निकास);

अटल व्योम *functionfs_acquire_dev(काष्ठा ffs_dev *dev)
अणु
	अगर (!try_module_get(THIS_MODULE))
		वापस ERR_PTR(-ENOENT);

	वापस शून्य;
पूर्ण

अटल व्योम functionfs_release_dev(काष्ठा ffs_dev *dev)
अणु
	module_put(THIS_MODULE);
पूर्ण

/*
 * The caller of this function takes ffs_lock
 */
अटल पूर्णांक functionfs_पढ़ोy_callback(काष्ठा ffs_data *ffs)
अणु
	पूर्णांक ret = 0;

	अगर (--missing_funcs)
		वापस 0;

	अगर (gfs_रेजिस्टरed)
		वापस -EBUSY;

	gfs_रेजिस्टरed = true;

	ret = usb_composite_probe(&gfs_driver);
	अगर (unlikely(ret < 0)) अणु
		++missing_funcs;
		gfs_रेजिस्टरed = false;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * The caller of this function takes ffs_lock
 */
अटल व्योम functionfs_बंदd_callback(काष्ठा ffs_data *ffs)
अणु
	missing_funcs++;

	अगर (gfs_रेजिस्टरed)
		usb_composite_unरेजिस्टर(&gfs_driver);
	gfs_रेजिस्टरed = false;
पूर्ण

/*
 * It is assumed that gfs_bind is called from a context where ffs_lock is held
 */
अटल पूर्णांक gfs_bind(काष्ठा usb_composite_dev *cdev)
अणु
#अगर defined CONFIG_USB_FUNCTIONFS_ETH || defined CONFIG_USB_FUNCTIONFS_RNDIS
	काष्ठा net_device *net;
#पूर्ण_अगर
	पूर्णांक ret, i;

	ENTER();

	अगर (missing_funcs)
		वापस -ENODEV;
#अगर defined CONFIG_USB_FUNCTIONFS_ETH
	अगर (can_support_ecm(cdev->gadget)) अणु
		काष्ठा f_ecm_opts *ecm_opts;

		fi_ecm = usb_get_function_instance("ecm");
		अगर (IS_ERR(fi_ecm))
			वापस PTR_ERR(fi_ecm);
		ecm_opts = container_of(fi_ecm, काष्ठा f_ecm_opts, func_inst);
		net = ecm_opts->net;
	पूर्ण अन्यथा अणु
		काष्ठा f_gether_opts *geth_opts;

		fi_geth = usb_get_function_instance("geth");
		अगर (IS_ERR(fi_geth))
			वापस PTR_ERR(fi_geth);
		geth_opts = container_of(fi_geth, काष्ठा f_gether_opts,
					 func_inst);
		net = geth_opts->net;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_FUNCTIONFS_RNDIS
	अणु
		fi_rndis = usb_get_function_instance("rndis");
		अगर (IS_ERR(fi_rndis)) अणु
			ret = PTR_ERR(fi_rndis);
			जाओ error;
		पूर्ण
#अगर_अघोषित CONFIG_USB_FUNCTIONFS_ETH
		net = container_of(fi_rndis, काष्ठा f_rndis_opts,
				   func_inst)->net;
#पूर्ण_अगर
	पूर्ण
#पूर्ण_अगर

#अगर defined CONFIG_USB_FUNCTIONFS_ETH || defined CONFIG_USB_FUNCTIONFS_RNDIS
	gether_set_qmult(net, qmult);
	अगर (!gether_set_host_addr(net, host_addr))
		pr_info("using host ethernet address: %s", host_addr);
	अगर (!gether_set_dev_addr(net, dev_addr))
		pr_info("using self ethernet address: %s", dev_addr);
#पूर्ण_अगर

#अगर defined CONFIG_USB_FUNCTIONFS_RNDIS && defined CONFIG_USB_FUNCTIONFS_ETH
	gether_set_gadget(net, cdev->gadget);
	ret = gether_रेजिस्टर_netdev(net);
	अगर (ret)
		जाओ error_rndis;

	अगर (can_support_ecm(cdev->gadget)) अणु
		काष्ठा f_ecm_opts *ecm_opts;

		ecm_opts = container_of(fi_ecm, काष्ठा f_ecm_opts, func_inst);
		ecm_opts->bound = true;
	पूर्ण अन्यथा अणु
		काष्ठा f_gether_opts *geth_opts;

		geth_opts = container_of(fi_geth, काष्ठा f_gether_opts,
					 func_inst);
		geth_opts->bound = true;
	पूर्ण

	rndis_borrow_net(fi_rndis, net);
#पूर्ण_अगर

	/* TODO: gstrings_attach? */
	ret = usb_string_ids_tab(cdev, gfs_strings);
	अगर (unlikely(ret < 0))
		जाओ error_rndis;
	gfs_dev_desc.iProduct = gfs_strings[USB_GADGET_PRODUCT_IDX].id;

	अगर (gadget_is_otg(cdev->gadget) && !gfs_otg_desc[0]) अणु
		काष्ठा usb_descriptor_header *usb_desc;

		usb_desc = usb_otg_descriptor_alloc(cdev->gadget);
		अगर (!usb_desc)
			जाओ error_rndis;
		usb_otg_descriptor_init(cdev->gadget, usb_desc);
		gfs_otg_desc[0] = usb_desc;
		gfs_otg_desc[1] = शून्य;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(gfs_configurations); ++i) अणु
		काष्ठा gfs_configuration *c = gfs_configurations + i;
		पूर्णांक sid = USB_GADGET_FIRST_AVAIL_IDX + i;

		c->c.label			= gfs_strings[sid].s;
		c->c.iConfiguration		= gfs_strings[sid].id;
		c->c.bConfigurationValue	= 1 + i;
		c->c.bmAttributes		= USB_CONFIG_ATT_SELFPOWER;

		c->num = i;

		ret = usb_add_config(cdev, &c->c, gfs_करो_config);
		अगर (unlikely(ret < 0))
			जाओ error_unbind;
	पूर्ण
	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);
	वापस 0;

/* TODO */
error_unbind:
	kमुक्त(gfs_otg_desc[0]);
	gfs_otg_desc[0] = शून्य;
error_rndis:
#अगर_घोषित CONFIG_USB_FUNCTIONFS_RNDIS
	usb_put_function_instance(fi_rndis);
error:
#पूर्ण_अगर
#अगर defined CONFIG_USB_FUNCTIONFS_ETH
	अगर (can_support_ecm(cdev->gadget))
		usb_put_function_instance(fi_ecm);
	अन्यथा
		usb_put_function_instance(fi_geth);
#पूर्ण_अगर
	वापस ret;
पूर्ण

/*
 * It is assumed that gfs_unbind is called from a context where ffs_lock is held
 */
अटल पूर्णांक gfs_unbind(काष्ठा usb_composite_dev *cdev)
अणु
	पूर्णांक i;

	ENTER();


#अगर_घोषित CONFIG_USB_FUNCTIONFS_RNDIS
	usb_put_function(f_rndis);
	usb_put_function_instance(fi_rndis);
#पूर्ण_अगर

#अगर defined CONFIG_USB_FUNCTIONFS_ETH
	अगर (can_support_ecm(cdev->gadget)) अणु
		usb_put_function(f_ecm);
		usb_put_function_instance(fi_ecm);
	पूर्ण अन्यथा अणु
		usb_put_function(f_geth);
		usb_put_function_instance(fi_geth);
	पूर्ण
#पूर्ण_अगर
	क्रम (i = 0; i < N_CONF * func_num; ++i)
		usb_put_function(*(f_ffs[0] + i));

	kमुक्त(gfs_otg_desc[0]);
	gfs_otg_desc[0] = शून्य;

	वापस 0;
पूर्ण

/*
 * It is assumed that gfs_करो_config is called from a context where
 * ffs_lock is held
 */
अटल पूर्णांक gfs_करो_config(काष्ठा usb_configuration *c)
अणु
	काष्ठा gfs_configuration *gc =
		container_of(c, काष्ठा gfs_configuration, c);
	पूर्णांक i;
	पूर्णांक ret;

	अगर (missing_funcs)
		वापस -ENODEV;

	अगर (gadget_is_otg(c->cdev->gadget)) अणु
		c->descriptors = gfs_otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

	अगर (gc->eth) अणु
		ret = gc->eth(c);
		अगर (unlikely(ret < 0))
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < func_num; i++) अणु
		f_ffs[gc->num][i] = usb_get_function(fi_ffs[i]);
		अगर (IS_ERR(f_ffs[gc->num][i])) अणु
			ret = PTR_ERR(f_ffs[gc->num][i]);
			जाओ error;
		पूर्ण
		ret = usb_add_function(c, f_ffs[gc->num][i]);
		अगर (ret < 0) अणु
			usb_put_function(f_ffs[gc->num][i]);
			जाओ error;
		पूर्ण
	पूर्ण

	/*
	 * After previous करो_configs there may be some invalid
	 * poपूर्णांकers in c->पूर्णांकerface array.  This happens every समय
	 * a user space function with fewer पूर्णांकerfaces than a user
	 * space function that was run beक्रमe the new one is run.  The
	 * compasit's set_config() assumes that अगर there is no more
	 * then MAX_CONFIG_INTERFACES पूर्णांकerfaces in a configuration
	 * then there is a शून्य poपूर्णांकer after the last पूर्णांकerface in
	 * c->पूर्णांकerface array.  We need to make sure this is true.
	 */
	अगर (c->next_पूर्णांकerface_id < ARRAY_SIZE(c->पूर्णांकerface))
		c->पूर्णांकerface[c->next_पूर्णांकerface_id] = शून्य;

	वापस 0;
error:
	जबतक (--i >= 0) अणु
		अगर (!IS_ERR(f_ffs[gc->num][i]))
			usb_हटाओ_function(c, f_ffs[gc->num][i]);
		usb_put_function(f_ffs[gc->num][i]);
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_USB_FUNCTIONFS_ETH

अटल पूर्णांक eth_bind_config(काष्ठा usb_configuration *c)
अणु
	पूर्णांक status = 0;

	अगर (can_support_ecm(c->cdev->gadget)) अणु
		f_ecm = usb_get_function(fi_ecm);
		अगर (IS_ERR(f_ecm))
			वापस PTR_ERR(f_ecm);

		status = usb_add_function(c, f_ecm);
		अगर (status < 0)
			usb_put_function(f_ecm);

	पूर्ण अन्यथा अणु
		f_geth = usb_get_function(fi_geth);
		अगर (IS_ERR(f_geth))
			वापस PTR_ERR(f_geth);

		status = usb_add_function(c, f_geth);
		अगर (status < 0)
			usb_put_function(f_geth);
	पूर्ण
	वापस status;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_FUNCTIONFS_RNDIS

अटल पूर्णांक bind_rndis_config(काष्ठा usb_configuration *c)
अणु
	पूर्णांक status = 0;

	f_rndis = usb_get_function(fi_rndis);
	अगर (IS_ERR(f_rndis))
		वापस PTR_ERR(f_rndis);

	status = usb_add_function(c, f_rndis);
	अगर (status < 0)
		usb_put_function(f_rndis);

	वापस status;
पूर्ण

#पूर्ण_अगर
