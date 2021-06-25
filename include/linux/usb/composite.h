<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * composite.h -- framework क्रम usb gadमाला_लो which are composite devices
 *
 * Copyright (C) 2006-2008 David Brownell
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA  02110-1301  USA
 */

#अगर_अघोषित	__LINUX_USB_COMPOSITE_H
#घोषणा	__LINUX_USB_COMPOSITE_H

/*
 * This framework is an optional layer on top of the USB Gadget पूर्णांकerface,
 * making it easier to build (a) Composite devices, supporting multiple
 * functions within any single configuration, and (b) Multi-configuration
 * devices, also supporting multiple functions but without necessarily
 * having more than one function per configuration.
 *
 * Example:  a device with a single configuration supporting both network
 * link and mass storage functions is a composite device.  Those functions
 * might alternatively be packaged in inभागidual configurations, but in
 * the composite model the host can use both functions at the same समय.
 */

#समावेश <linux/bcd.h>
#समावेश <linux/version.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/log2.h>
#समावेश <linux/configfs.h>

/*
 * USB function drivers should वापस USB_GADGET_DELAYED_STATUS अगर they
 * wish to delay the data/status stages of the control transfer till they
 * are पढ़ोy. The control transfer will then be kept from completing till
 * all the function drivers that requested क्रम USB_GADGET_DELAYED_STAUS
 * invoke usb_composite_setup_जारी().
 */
#घोषणा USB_GADGET_DELAYED_STATUS       0x7fff	/* Impossibly large value */

/* big enough to hold our biggest descriptor */
#घोषणा USB_COMP_EP0_बफ_मान	4096

/* OS feature descriptor length <= 4kB */
#घोषणा USB_COMP_EP0_OS_DESC_बफ_मान	4096

#घोषणा USB_MS_TO_HS_INTERVAL(x)	(ilog2((x * 1000 / 125)) + 1)
काष्ठा usb_configuration;

/**
 * काष्ठा usb_os_desc_ext_prop - describes one "Extended Property"
 * @entry: used to keep a list of extended properties
 * @type: Extended Property type
 * @name_len: Extended Property unicode name length, including terminating '\0'
 * @name: Extended Property name
 * @data_len: Length of Extended Property blob (क्रम unicode store द्विगुन len)
 * @data: Extended Property blob
 * @item: Represents this Extended Property in configfs
 */
काष्ठा usb_os_desc_ext_prop अणु
	काष्ठा list_head	entry;
	u8			type;
	पूर्णांक			name_len;
	अक्षर			*name;
	पूर्णांक			data_len;
	अक्षर			*data;
	काष्ठा config_item	item;
पूर्ण;

/**
 * काष्ठा usb_os_desc - describes OS descriptors associated with one पूर्णांकerface
 * @ext_compat_id: 16 bytes of "Compatible ID" and "Subcompatible ID"
 * @ext_prop: Extended Properties list
 * @ext_prop_len: Total length of Extended Properties blobs
 * @ext_prop_count: Number of Extended Properties
 * @opts_mutex: Optional mutex protecting config data of a usb_function_instance
 * @group: Represents OS descriptors associated with an पूर्णांकerface in configfs
 * @owner: Module associated with this OS descriptor
 */
काष्ठा usb_os_desc अणु
	अक्षर			*ext_compat_id;
	काष्ठा list_head	ext_prop;
	पूर्णांक			ext_prop_len;
	पूर्णांक			ext_prop_count;
	काष्ठा mutex		*opts_mutex;
	काष्ठा config_group	group;
	काष्ठा module		*owner;
पूर्ण;

/**
 * काष्ठा usb_os_desc_table - describes OS descriptors associated with one
 * पूर्णांकerface of a usb_function
 * @अगर_id: Interface id
 * @os_desc: "Extended Compatibility ID" and "Extended Properties" of the
 *	पूर्णांकerface
 *
 * Each पूर्णांकerface can have at most one "Extended Compatibility ID" and a
 * number of "Extended Properties".
 */
काष्ठा usb_os_desc_table अणु
	पूर्णांक			अगर_id;
	काष्ठा usb_os_desc	*os_desc;
पूर्ण;

/**
 * काष्ठा usb_function - describes one function of a configuration
 * @name: For diagnostics, identअगरies the function.
 * @strings: tables of strings, keyed by identअगरiers asचिन्हित during bind()
 *	and by language IDs provided in control requests
 * @fs_descriptors: Table of full (or low) speed descriptors, using पूर्णांकerface and
 *	string identअगरiers asचिन्हित during @bind().  If this poपूर्णांकer is null,
 *	the function will not be available at full speed (or at low speed).
 * @hs_descriptors: Table of high speed descriptors, using पूर्णांकerface and
 *	string identअगरiers asचिन्हित during @bind().  If this poपूर्णांकer is null,
 *	the function will not be available at high speed.
 * @ss_descriptors: Table of super speed descriptors, using पूर्णांकerface and
 *	string identअगरiers asचिन्हित during @bind(). If this
 *	poपूर्णांकer is null after initiation, the function will not
 *	be available at super speed.
 * @ssp_descriptors: Table of super speed plus descriptors, using
 *	पूर्णांकerface and string identअगरiers asचिन्हित during @bind(). If
 *	this poपूर्णांकer is null after initiation, the function will not
 *	be available at super speed plus.
 * @config: asचिन्हित when @usb_add_function() is called; this is the
 *	configuration with which this function is associated.
 * @os_desc_table: Table of (पूर्णांकerface id, os descriptors) pairs. The function
 *	can expose more than one पूर्णांकerface. If an पूर्णांकerface is a member of
 *	an IAD, only the first पूर्णांकerface of IAD has its entry in the table.
 * @os_desc_n: Number of entries in os_desc_table
 * @bind: Beक्रमe the gadget can रेजिस्टर, all of its functions bind() to the
 *	available resources including string and पूर्णांकerface identअगरiers used
 *	in पूर्णांकerface or class descriptors; endpoपूर्णांकs; I/O buffers; and so on.
 * @unbind: Reverses @bind; called as a side effect of unरेजिस्टरing the
 *	driver which added this function.
 * @मुक्त_func: मुक्त the काष्ठा usb_function.
 * @mod: (पूर्णांकernal) poपूर्णांकs to the module that created this काष्ठाure.
 * @set_alt: (REQUIRED) Reconfigures altsettings; function drivers may
 *	initialize usb_ep.driver data at this समय (when it is used).
 *	Note that setting an पूर्णांकerface to its current altsetting resets
 *	पूर्णांकerface state, and that all पूर्णांकerfaces have a disabled state.
 * @get_alt: Returns the active altsetting.  If this is not provided,
 *	then only altsetting zero is supported.
 * @disable: (REQUIRED) Indicates the function should be disabled.  Reasons
 *	include host resetting or reconfiguring the gadget, and disconnection.
 * @setup: Used क्रम पूर्णांकerface-specअगरic control requests.
 * @req_match: Tests अगर a given class request can be handled by this function.
 * @suspend: Notअगरies functions when the host stops sending USB traffic.
 * @resume: Notअगरies functions when the host restarts USB traffic.
 * @get_status: Returns function status as a reply to
 *	GetStatus() request when the recipient is Interface.
 * @func_suspend: callback to be called when
 *	SetFeature(FUNCTION_SUSPEND) is reseived
 *
 * A single USB function uses one or more पूर्णांकerfaces, and should in most
 * हालs support operation at both full and high speeds.  Each function is
 * associated by @usb_add_function() with a one configuration; that function
 * causes @bind() to be called so resources can be allocated as part of
 * setting up a gadget driver.  Those resources include endpoपूर्णांकs, which
 * should be allocated using @usb_ep_स्वतःconfig().
 *
 * To support dual speed operation, a function driver provides descriptors
 * क्रम both high and full speed operation.  Except in rare हालs that करोn't
 * involve bulk endpoपूर्णांकs, each speed needs dअगरferent endpoपूर्णांक descriptors.
 *
 * Function drivers choose their own strategies क्रम managing instance data.
 * The simplest strategy just declares it "अटल', which means the function
 * can only be activated once.  If the function needs to be exposed in more
 * than one configuration at a given speed, it needs to support multiple
 * usb_function काष्ठाures (one क्रम each configuration).
 *
 * A more complex strategy might encapsulate a @usb_function काष्ठाure inside
 * a driver-specअगरic instance काष्ठाure to allows multiple activations.  An
 * example of multiple activations might be a CDC ACM function that supports
 * two or more distinct instances within the same configuration, providing
 * several independent logical data links to a USB host.
 */

काष्ठा usb_function अणु
	स्थिर अक्षर			*name;
	काष्ठा usb_gadget_strings	**strings;
	काष्ठा usb_descriptor_header	**fs_descriptors;
	काष्ठा usb_descriptor_header	**hs_descriptors;
	काष्ठा usb_descriptor_header	**ss_descriptors;
	काष्ठा usb_descriptor_header	**ssp_descriptors;

	काष्ठा usb_configuration	*config;

	काष्ठा usb_os_desc_table	*os_desc_table;
	अचिन्हित			os_desc_n;

	/* REVISIT:  bind() functions can be marked __init, which
	 * makes trouble क्रम section mismatch analysis.  See अगर
	 * we can't reकाष्ठाure things to aव्योम mismatching.
	 * Related:  unbind() may kमुक्त() but bind() won't...
	 */

	/* configuration management:  bind/unbind */
	पूर्णांक			(*bind)(काष्ठा usb_configuration *,
					काष्ठा usb_function *);
	व्योम			(*unbind)(काष्ठा usb_configuration *,
					काष्ठा usb_function *);
	व्योम			(*मुक्त_func)(काष्ठा usb_function *f);
	काष्ठा module		*mod;

	/* runसमय state management */
	पूर्णांक			(*set_alt)(काष्ठा usb_function *,
					अचिन्हित पूर्णांकerface, अचिन्हित alt);
	पूर्णांक			(*get_alt)(काष्ठा usb_function *,
					अचिन्हित पूर्णांकerface);
	व्योम			(*disable)(काष्ठा usb_function *);
	पूर्णांक			(*setup)(काष्ठा usb_function *,
					स्थिर काष्ठा usb_ctrlrequest *);
	bool			(*req_match)(काष्ठा usb_function *,
					स्थिर काष्ठा usb_ctrlrequest *,
					bool config0);
	व्योम			(*suspend)(काष्ठा usb_function *);
	व्योम			(*resume)(काष्ठा usb_function *);

	/* USB 3.0 additions */
	पूर्णांक			(*get_status)(काष्ठा usb_function *);
	पूर्णांक			(*func_suspend)(काष्ठा usb_function *,
						u8 suspend_opt);
	/* निजी: */
	/* पूर्णांकernals */
	काष्ठा list_head		list;
	DECLARE_BITMAP(endpoपूर्णांकs, 32);
	स्थिर काष्ठा usb_function_instance *fi;

	अचिन्हित पूर्णांक		bind_deactivated:1;
पूर्ण;

पूर्णांक usb_add_function(काष्ठा usb_configuration *, काष्ठा usb_function *);

पूर्णांक usb_function_deactivate(काष्ठा usb_function *);
पूर्णांक usb_function_activate(काष्ठा usb_function *);

पूर्णांक usb_पूर्णांकerface_id(काष्ठा usb_configuration *, काष्ठा usb_function *);

पूर्णांक config_ep_by_speed_and_alt(काष्ठा usb_gadget *g, काष्ठा usb_function *f,
				काष्ठा usb_ep *_ep, u8 alt);

पूर्णांक config_ep_by_speed(काष्ठा usb_gadget *g, काष्ठा usb_function *f,
			काष्ठा usb_ep *_ep);

#घोषणा	MAX_CONFIG_INTERFACES		16	/* arbitrary; max 255 */

/**
 * काष्ठा usb_configuration - represents one gadget configuration
 * @label: For diagnostics, describes the configuration.
 * @strings: Tables of strings, keyed by identअगरiers asचिन्हित during @bind()
 *	and by language IDs provided in control requests.
 * @descriptors: Table of descriptors preceding all function descriptors.
 *	Examples include OTG and venकरोr-specअगरic descriptors.
 * @unbind: Reverses @bind; called as a side effect of unरेजिस्टरing the
 *	driver which added this configuration.
 * @setup: Used to delegate control requests that aren't handled by standard
 *	device infraकाष्ठाure or directed at a specअगरic पूर्णांकerface.
 * @bConfigurationValue: Copied पूर्णांकo configuration descriptor.
 * @iConfiguration: Copied पूर्णांकo configuration descriptor.
 * @bmAttributes: Copied पूर्णांकo configuration descriptor.
 * @MaxPower: Power consumtion in mA. Used to compute bMaxPower in the
 *	configuration descriptor after considering the bus speed.
 * @cdev: asचिन्हित by @usb_add_config() beक्रमe calling @bind(); this is
 *	the device associated with this configuration.
 *
 * Configurations are building blocks क्रम gadget drivers काष्ठाured around
 * function drivers.  Simple USB gadमाला_लो require only one function and one
 * configuration, and handle dual-speed hardware by always providing the same
 * functionality.  Slightly more complex gadमाला_लो may have more than one
 * single-function configuration at a given speed; or have configurations
 * that only work at one speed.
 *
 * Composite devices are, by definition, ones with configurations which
 * include more than one function.
 *
 * The lअगरecycle of a usb_configuration includes allocation, initialization
 * of the fields described above, and calling @usb_add_config() to set up
 * पूर्णांकernal data and bind it to a specअगरic device.  The configuration's
 * @bind() method is then used to initialize all the functions and then
 * call @usb_add_function() क्रम them.
 *
 * Those functions would normally be independent of each other, but that's
 * not mandatory.  CDC WMC devices are an example where functions often
 * depend on other functions, with some functions subsidiary to others.
 * Such पूर्णांकerdependency may be managed in any way, so दीर्घ as all of the
 * descriptors complete by the समय the composite driver वापसs from
 * its bind() routine.
 */
काष्ठा usb_configuration अणु
	स्थिर अक्षर			*label;
	काष्ठा usb_gadget_strings	**strings;
	स्थिर काष्ठा usb_descriptor_header **descriptors;

	/* REVISIT:  bind() functions can be marked __init, which
	 * makes trouble क्रम section mismatch analysis.  See अगर
	 * we can't reकाष्ठाure things to aव्योम mismatching...
	 */

	/* configuration management: unbind/setup */
	व्योम			(*unbind)(काष्ठा usb_configuration *);
	पूर्णांक			(*setup)(काष्ठा usb_configuration *,
					स्थिर काष्ठा usb_ctrlrequest *);

	/* fields in the config descriptor */
	u8			bConfigurationValue;
	u8			iConfiguration;
	u8			bmAttributes;
	u16			MaxPower;

	काष्ठा usb_composite_dev	*cdev;

	/* निजी: */
	/* पूर्णांकernals */
	काष्ठा list_head	list;
	काष्ठा list_head	functions;
	u8			next_पूर्णांकerface_id;
	अचिन्हित		superspeed:1;
	अचिन्हित		highspeed:1;
	अचिन्हित		fullspeed:1;
	अचिन्हित		superspeed_plus:1;
	काष्ठा usb_function	*पूर्णांकerface[MAX_CONFIG_INTERFACES];
पूर्ण;

पूर्णांक usb_add_config(काष्ठा usb_composite_dev *,
		काष्ठा usb_configuration *,
		पूर्णांक (*)(काष्ठा usb_configuration *));

व्योम usb_हटाओ_config(काष्ठा usb_composite_dev *,
		काष्ठा usb_configuration *);

/* predefined index क्रम usb_composite_driver */
क्रमागत अणु
	USB_GADGET_MANUFACTURER_IDX	= 0,
	USB_GADGET_PRODUCT_IDX,
	USB_GADGET_SERIAL_IDX,
	USB_GADGET_FIRST_AVAIL_IDX,
पूर्ण;

/**
 * काष्ठा usb_composite_driver - groups configurations पूर्णांकo a gadget
 * @name: For diagnostics, identअगरies the driver.
 * @dev: Template descriptor क्रम the device, including शेष device
 *	identअगरiers.
 * @strings: tables of strings, keyed by identअगरiers asचिन्हित during @bind
 *	and language IDs provided in control requests. Note: The first entries
 *	are predefined. The first entry that may be used is
 *	USB_GADGET_FIRST_AVAIL_IDX
 * @max_speed: Highest speed the driver supports.
 * @needs_serial: set to 1 अगर the gadget needs userspace to provide
 * 	a serial number.  If one is not provided, warning will be prपूर्णांकed.
 * @bind: (REQUIRED) Used to allocate resources that are shared across the
 *	whole device, such as string IDs, and add its configurations using
 *	@usb_add_config(). This may fail by वापसing a negative त्रुटि_सं
 *	value; it should वापस zero on successful initialization.
 * @unbind: Reverses @bind; called as a side effect of unरेजिस्टरing
 *	this driver.
 * @disconnect: optional driver disconnect method
 * @suspend: Notअगरies when the host stops sending USB traffic,
 *	after function notअगरications
 * @resume: Notअगरies configuration when the host restarts USB traffic,
 *	beक्रमe function notअगरications
 * @gadget_driver: Gadget driver controlling this driver
 *
 * Devices शेष to reporting self घातered operation.  Devices which rely
 * on bus घातered operation should report this in their @bind method.
 *
 * Beक्रमe वापसing from @bind, various fields in the ढाँचा descriptor
 * may be overridden.  These include the idVenकरोr/idProduct/bcdDevice values
 * normally to bind the appropriate host side driver, and the three strings
 * (iManufacturer, iProduct, iSerialNumber) normally used to provide user
 * meaningful device identअगरiers.  (The strings will not be defined unless
 * they are defined in @dev and @strings.)  The correct ep0 maxpacket size
 * is also reported, as defined by the underlying controller driver.
 */
काष्ठा usb_composite_driver अणु
	स्थिर अक्षर				*name;
	स्थिर काष्ठा usb_device_descriptor	*dev;
	काष्ठा usb_gadget_strings		**strings;
	क्रमागत usb_device_speed			max_speed;
	अचिन्हित		needs_serial:1;

	पूर्णांक			(*bind)(काष्ठा usb_composite_dev *cdev);
	पूर्णांक			(*unbind)(काष्ठा usb_composite_dev *);

	व्योम			(*disconnect)(काष्ठा usb_composite_dev *);

	/* global suspend hooks */
	व्योम			(*suspend)(काष्ठा usb_composite_dev *);
	व्योम			(*resume)(काष्ठा usb_composite_dev *);
	काष्ठा usb_gadget_driver		gadget_driver;
पूर्ण;

बाह्य पूर्णांक usb_composite_probe(काष्ठा usb_composite_driver *driver);
बाह्य व्योम usb_composite_unरेजिस्टर(काष्ठा usb_composite_driver *driver);

/**
 * module_usb_composite_driver() - Helper macro क्रम रेजिस्टरing a USB gadget
 * composite driver
 * @__usb_composite_driver: usb_composite_driver काष्ठा
 *
 * Helper macro क्रम USB gadget composite drivers which करो not करो anything
 * special in module init/निकास. This eliminates a lot of boilerplate. Each
 * module may only use this macro once, and calling it replaces module_init()
 * and module_निकास()
 */
#घोषणा module_usb_composite_driver(__usb_composite_driver) \
	module_driver(__usb_composite_driver, usb_composite_probe, \
		       usb_composite_unरेजिस्टर)

बाह्य व्योम usb_composite_setup_जारी(काष्ठा usb_composite_dev *cdev);
बाह्य पूर्णांक composite_dev_prepare(काष्ठा usb_composite_driver *composite,
		काष्ठा usb_composite_dev *cdev);
बाह्य पूर्णांक composite_os_desc_req_prepare(काष्ठा usb_composite_dev *cdev,
					 काष्ठा usb_ep *ep0);
व्योम composite_dev_cleanup(काष्ठा usb_composite_dev *cdev);

अटल अंतरभूत काष्ठा usb_composite_driver *to_cdriver(
		काष्ठा usb_gadget_driver *gdrv)
अणु
	वापस container_of(gdrv, काष्ठा usb_composite_driver, gadget_driver);
पूर्ण

#घोषणा OS_STRING_QW_SIGN_LEN		14
#घोषणा OS_STRING_IDX			0xEE

/**
 * काष्ठा usb_composite_dev - represents one composite usb gadget
 * @gadget: पढ़ो-only, असलtracts the gadget's usb peripheral controller
 * @req: used क्रम control responses; buffer is pre-allocated
 * @os_desc_req: used क्रम OS descriptors responses; buffer is pre-allocated
 * @config: the currently active configuration
 * @qw_sign: qwSignature part of the OS string
 * @b_venकरोr_code: bMS_VenकरोrCode part of the OS string
 * @use_os_string: false by शेष, पूर्णांकerested gadमाला_लो set it
 * @os_desc_config: the configuration to be used with OS descriptors
 * @setup_pending: true when setup request is queued but not completed
 * @os_desc_pending: true when os_desc request is queued but not completed
 *
 * One of these devices is allocated and initialized beक्रमe the
 * associated device driver's bind() is called.
 *
 * OPEN ISSUE:  it appears that some WUSB devices will need to be
 * built by combining a normal (wired) gadget with a wireless one.
 * This revision of the gadget framework should probably try to make
 * sure करोing that won't hurt too much.
 *
 * One notion क्रम how to handle Wireless USB devices involves:
 *
 * (a) a second gadget here, discovery mechanism TBD, but likely
 *     needing separate "register/unregister WUSB gadget" calls;
 * (b) updates to usb_gadget to include flags "is it wireless",
 *     "is it wired", plus (presumably in a wrapper काष्ठाure)
 *     bandgroup and PHY info;
 * (c) presumably a wireless_ep wrapping a usb_ep, and reporting
 *     wireless-specअगरic parameters like maxburst and maxsequence;
 * (d) configurations that are specअगरic to wireless links;
 * (e) function drivers that understand wireless configs and will
 *     support wireless क्रम (additional) function instances;
 * (f) a function to support association setup (like CBAF), not
 *     necessarily requiring a wireless adapter;
 * (g) composite device setup that can create one or more wireless
 *     configs, including appropriate association setup support;
 * (h) more, TBD.
 */
काष्ठा usb_composite_dev अणु
	काष्ठा usb_gadget		*gadget;
	काष्ठा usb_request		*req;
	काष्ठा usb_request		*os_desc_req;

	काष्ठा usb_configuration	*config;

	/* OS String is a custom (yet popular) extension to the USB standard. */
	u8				qw_sign[OS_STRING_QW_SIGN_LEN];
	u8				b_venकरोr_code;
	काष्ठा usb_configuration	*os_desc_config;
	अचिन्हित पूर्णांक			use_os_string:1;

	/* निजी: */
	/* पूर्णांकernals */
	अचिन्हित पूर्णांक			suspended:1;
	काष्ठा usb_device_descriptor	desc;
	काष्ठा list_head		configs;
	काष्ठा list_head		gstrings;
	काष्ठा usb_composite_driver	*driver;
	u8				next_string_id;
	अक्षर				*def_manufacturer;

	/* the gadget driver won't enable the data pullup
	 * जबतक the deactivation count is nonzero.
	 */
	अचिन्हित			deactivations;

	/* the composite driver won't complete the control transfer's
	 * data/status stages till delayed_status is zero.
	 */
	पूर्णांक				delayed_status;

	/* protects deactivations and delayed_status counts*/
	spinlock_t			lock;

	/* खुला: */
	अचिन्हित पूर्णांक			setup_pending:1;
	अचिन्हित पूर्णांक			os_desc_pending:1;
पूर्ण;

बाह्य पूर्णांक usb_string_id(काष्ठा usb_composite_dev *c);
बाह्य पूर्णांक usb_string_ids_tab(काष्ठा usb_composite_dev *c,
			      काष्ठा usb_string *str);
बाह्य काष्ठा usb_string *usb_gstrings_attach(काष्ठा usb_composite_dev *cdev,
		काष्ठा usb_gadget_strings **sp, अचिन्हित n_strings);

बाह्य पूर्णांक usb_string_ids_n(काष्ठा usb_composite_dev *c, अचिन्हित n);

बाह्य व्योम composite_disconnect(काष्ठा usb_gadget *gadget);
बाह्य व्योम composite_reset(काष्ठा usb_gadget *gadget);

बाह्य पूर्णांक composite_setup(काष्ठा usb_gadget *gadget,
		स्थिर काष्ठा usb_ctrlrequest *ctrl);
बाह्य व्योम composite_suspend(काष्ठा usb_gadget *gadget);
बाह्य व्योम composite_resume(काष्ठा usb_gadget *gadget);

/*
 * Some प्रणालीs will need runसमय overrides क्रम the  product identअगरiers
 * published in the device descriptor, either numbers or strings or both.
 * String parameters are in UTF-8 (superset of ASCII's 7 bit अक्षरacters).
 */
काष्ठा usb_composite_overग_लिखो अणु
	u16	idVenकरोr;
	u16	idProduct;
	u16	bcdDevice;
	अक्षर	*serial_number;
	अक्षर	*manufacturer;
	अक्षर	*product;
पूर्ण;
#घोषणा USB_GADGET_COMPOSITE_OPTIONS()					\
	अटल काष्ठा usb_composite_overग_लिखो coverग_लिखो;		\
									\
	module_param_named(idVenकरोr, coverग_लिखो.idVenकरोr, uलघु, S_IRUGO); \
	MODULE_PARM_DESC(idVenकरोr, "USB Vendor ID");			\
									\
	module_param_named(idProduct, coverग_लिखो.idProduct, uलघु, S_IRUGO); \
	MODULE_PARM_DESC(idProduct, "USB Product ID");			\
									\
	module_param_named(bcdDevice, coverग_लिखो.bcdDevice, uलघु, S_IRUGO); \
	MODULE_PARM_DESC(bcdDevice, "USB Device version (BCD)");	\
									\
	module_param_named(iSerialNumber, coverग_लिखो.serial_number, अक्षरp, \
			S_IRUGO); \
	MODULE_PARM_DESC(iSerialNumber, "SerialNumber string");		\
									\
	module_param_named(iManufacturer, coverग_लिखो.manufacturer, अक्षरp, \
			S_IRUGO); \
	MODULE_PARM_DESC(iManufacturer, "USB Manufacturer string");	\
									\
	module_param_named(iProduct, coverग_लिखो.product, अक्षरp, S_IRUGO); \
	MODULE_PARM_DESC(iProduct, "USB Product string")

व्योम usb_composite_overग_लिखो_options(काष्ठा usb_composite_dev *cdev,
		काष्ठा usb_composite_overग_लिखो *covr);

अटल अंतरभूत u16 get_शेष_bcdDevice(व्योम)
अणु
	u16 bcdDevice;

	bcdDevice = bin2bcd(LINUX_VERSION_MAJOR) << 8;
	bcdDevice |= bin2bcd(LINUX_VERSION_PATCHLEVEL);
	वापस bcdDevice;
पूर्ण

काष्ठा usb_function_driver अणु
	स्थिर अक्षर *name;
	काष्ठा module *mod;
	काष्ठा list_head list;
	काष्ठा usb_function_instance *(*alloc_inst)(व्योम);
	काष्ठा usb_function *(*alloc_func)(काष्ठा usb_function_instance *inst);
पूर्ण;

काष्ठा usb_function_instance अणु
	काष्ठा config_group group;
	काष्ठा list_head cfs_list;
	काष्ठा usb_function_driver *fd;
	पूर्णांक (*set_inst_name)(काष्ठा usb_function_instance *inst,
			      स्थिर अक्षर *name);
	व्योम (*मुक्त_func_inst)(काष्ठा usb_function_instance *inst);
पूर्ण;

व्योम usb_function_unरेजिस्टर(काष्ठा usb_function_driver *f);
पूर्णांक usb_function_रेजिस्टर(काष्ठा usb_function_driver *newf);
व्योम usb_put_function_instance(काष्ठा usb_function_instance *fi);
व्योम usb_put_function(काष्ठा usb_function *f);
काष्ठा usb_function_instance *usb_get_function_instance(स्थिर अक्षर *name);
काष्ठा usb_function *usb_get_function(काष्ठा usb_function_instance *fi);

काष्ठा usb_configuration *usb_get_config(काष्ठा usb_composite_dev *cdev,
		पूर्णांक val);
पूर्णांक usb_add_config_only(काष्ठा usb_composite_dev *cdev,
		काष्ठा usb_configuration *config);
व्योम usb_हटाओ_function(काष्ठा usb_configuration *c, काष्ठा usb_function *f);

#घोषणा DECLARE_USB_FUNCTION(_name, _inst_alloc, _func_alloc)		\
	अटल काष्ठा usb_function_driver _name ## usb_func = अणु		\
		.name = __stringअगरy(_name),				\
		.mod  = THIS_MODULE,					\
		.alloc_inst = _inst_alloc,				\
		.alloc_func = _func_alloc,				\
	पूर्ण;								\
	MODULE_ALIAS("usbfunc:"__stringअगरy(_name));

#घोषणा DECLARE_USB_FUNCTION_INIT(_name, _inst_alloc, _func_alloc)	\
	DECLARE_USB_FUNCTION(_name, _inst_alloc, _func_alloc)		\
	अटल पूर्णांक __init _name ## mod_init(व्योम)			\
	अणु								\
		वापस usb_function_रेजिस्टर(&_name ## usb_func);	\
	पूर्ण								\
	अटल व्योम __निकास _name ## mod_निकास(व्योम)			\
	अणु								\
		usb_function_unरेजिस्टर(&_name ## usb_func);		\
	पूर्ण								\
	module_init(_name ## mod_init);					\
	module_निकास(_name ## mod_निकास)

/* messaging utils */
#घोषणा DBG(d, fmt, args...) \
	dev_dbg(&(d)->gadget->dev , fmt , ## args)
#घोषणा VDBG(d, fmt, args...) \
	dev_vdbg(&(d)->gadget->dev , fmt , ## args)
#घोषणा ERROR(d, fmt, args...) \
	dev_err(&(d)->gadget->dev , fmt , ## args)
#घोषणा WARNING(d, fmt, args...) \
	dev_warn(&(d)->gadget->dev , fmt , ## args)
#घोषणा INFO(d, fmt, args...) \
	dev_info(&(d)->gadget->dev , fmt , ## args)

#पूर्ण_अगर	/* __LINUX_USB_COMPOSITE_H */
