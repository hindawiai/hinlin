<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_USB_H
#घोषणा __LINUX_USB_H

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/usb/ch9.h>

#घोषणा USB_MAJOR			180
#घोषणा USB_DEVICE_MAJOR		189


#अगर_घोषित __KERNEL__

#समावेश <linux/त्रुटिसं.स>        /* क्रम -ENODEV */
#समावेश <linux/delay.h>	/* क्रम mdelay() */
#समावेश <linux/पूर्णांकerrupt.h>	/* क्रम in_पूर्णांकerrupt() */
#समावेश <linux/list.h>		/* क्रम काष्ठा list_head */
#समावेश <linux/kref.h>		/* क्रम काष्ठा kref */
#समावेश <linux/device.h>	/* क्रम काष्ठा device */
#समावेश <linux/fs.h>		/* क्रम काष्ठा file_operations */
#समावेश <linux/completion.h>	/* क्रम काष्ठा completion */
#समावेश <linux/sched.h>	/* क्रम current && schedule_समयout */
#समावेश <linux/mutex.h>	/* क्रम काष्ठा mutex */
#समावेश <linux/pm_runसमय.स>	/* क्रम runसमय PM */

काष्ठा usb_device;
काष्ठा usb_driver;
काष्ठा wusb_dev;

/*-------------------------------------------------------------------------*/

/*
 * Host-side wrappers क्रम standard USB descriptors ... these are parsed
 * from the data provided by devices.  Parsing turns them from a flat
 * sequence of descriptors पूर्णांकo a hierarchy:
 *
 *  - devices have one (usually) or more configs;
 *  - configs have one (often) or more पूर्णांकerfaces;
 *  - पूर्णांकerfaces have one (usually) or more settings;
 *  - each पूर्णांकerface setting has zero or (usually) more endpoपूर्णांकs.
 *  - a SuperSpeed endpoपूर्णांक has a companion descriptor
 *
 * And there might be other descriptors mixed in with those.
 *
 * Devices may also have class-specअगरic or venकरोr-specअगरic descriptors.
 */

काष्ठा ep_device;

/**
 * काष्ठा usb_host_endpoपूर्णांक - host-side endpoपूर्णांक descriptor and queue
 * @desc: descriptor क्रम this endpoपूर्णांक, wMaxPacketSize in native byteorder
 * @ss_ep_comp: SuperSpeed companion descriptor क्रम this endpoपूर्णांक
 * @ssp_isoc_ep_comp: SuperSpeedPlus isoc companion descriptor क्रम this endpoपूर्णांक
 * @urb_list: urbs queued to this endpoपूर्णांक; मुख्यtained by usbcore
 * @hcpriv: क्रम use by HCD; typically holds hardware dma queue head (QH)
 *	with one or more transfer descriptors (TDs) per urb
 * @ep_dev: ep_device क्रम sysfs info
 * @extra: descriptors following this endpoपूर्णांक in the configuration
 * @extralen: how many bytes of "extra" are valid
 * @enabled: URBs may be submitted to this endpoपूर्णांक
 * @streams: number of USB-3 streams allocated on the endpoपूर्णांक
 *
 * USB requests are always queued to a given endpoपूर्णांक, identअगरied by a
 * descriptor within an active पूर्णांकerface in a given USB configuration.
 */
काष्ठा usb_host_endpoपूर्णांक अणु
	काष्ठा usb_endpoपूर्णांक_descriptor		desc;
	काष्ठा usb_ss_ep_comp_descriptor	ss_ep_comp;
	काष्ठा usb_ssp_isoc_ep_comp_descriptor	ssp_isoc_ep_comp;
	काष्ठा list_head		urb_list;
	व्योम				*hcpriv;
	काष्ठा ep_device		*ep_dev;	/* For sysfs info */

	अचिन्हित अक्षर *extra;   /* Extra descriptors */
	पूर्णांक extralen;
	पूर्णांक enabled;
	पूर्णांक streams;
पूर्ण;

/* host-side wrapper क्रम one पूर्णांकerface setting's parsed descriptors */
काष्ठा usb_host_पूर्णांकerface अणु
	काष्ठा usb_पूर्णांकerface_descriptor	desc;

	पूर्णांक extralen;
	अचिन्हित अक्षर *extra;   /* Extra descriptors */

	/* array of desc.bNumEndpoपूर्णांकs endpoपूर्णांकs associated with this
	 * पूर्णांकerface setting.  these will be in no particular order.
	 */
	काष्ठा usb_host_endpoपूर्णांक *endpoपूर्णांक;

	अक्षर *string;		/* iInterface string, अगर present */
पूर्ण;

क्रमागत usb_पूर्णांकerface_condition अणु
	USB_INTERFACE_UNBOUND = 0,
	USB_INTERFACE_BINDING,
	USB_INTERFACE_BOUND,
	USB_INTERFACE_UNBINDING,
पूर्ण;

पूर्णांक __must_check
usb_find_common_endpoपूर्णांकs(काष्ठा usb_host_पूर्णांकerface *alt,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_in,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_out,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_in,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_out);

पूर्णांक __must_check
usb_find_common_endpoपूर्णांकs_reverse(काष्ठा usb_host_पूर्णांकerface *alt,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_in,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_out,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_in,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_out);

अटल अंतरभूत पूर्णांक __must_check
usb_find_bulk_in_endpoपूर्णांक(काष्ठा usb_host_पूर्णांकerface *alt,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_in)
अणु
	वापस usb_find_common_endpoपूर्णांकs(alt, bulk_in, शून्य, शून्य, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check
usb_find_bulk_out_endpoपूर्णांक(काष्ठा usb_host_पूर्णांकerface *alt,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_out)
अणु
	वापस usb_find_common_endpoपूर्णांकs(alt, शून्य, bulk_out, शून्य, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check
usb_find_पूर्णांक_in_endpoपूर्णांक(काष्ठा usb_host_पूर्णांकerface *alt,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_in)
अणु
	वापस usb_find_common_endpoपूर्णांकs(alt, शून्य, शून्य, पूर्णांक_in, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check
usb_find_पूर्णांक_out_endpoपूर्णांक(काष्ठा usb_host_पूर्णांकerface *alt,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_out)
अणु
	वापस usb_find_common_endpoपूर्णांकs(alt, शून्य, शून्य, शून्य, पूर्णांक_out);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check
usb_find_last_bulk_in_endpoपूर्णांक(काष्ठा usb_host_पूर्णांकerface *alt,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_in)
अणु
	वापस usb_find_common_endpoपूर्णांकs_reverse(alt, bulk_in, शून्य, शून्य, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check
usb_find_last_bulk_out_endpoपूर्णांक(काष्ठा usb_host_पूर्णांकerface *alt,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_out)
अणु
	वापस usb_find_common_endpoपूर्णांकs_reverse(alt, शून्य, bulk_out, शून्य, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check
usb_find_last_पूर्णांक_in_endpoपूर्णांक(काष्ठा usb_host_पूर्णांकerface *alt,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_in)
अणु
	वापस usb_find_common_endpoपूर्णांकs_reverse(alt, शून्य, शून्य, पूर्णांक_in, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check
usb_find_last_पूर्णांक_out_endpoपूर्णांक(काष्ठा usb_host_पूर्णांकerface *alt,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_out)
अणु
	वापस usb_find_common_endpoपूर्णांकs_reverse(alt, शून्य, शून्य, शून्य, पूर्णांक_out);
पूर्ण

/**
 * काष्ठा usb_पूर्णांकerface - what usb device drivers talk to
 * @altsetting: array of पूर्णांकerface काष्ठाures, one क्रम each alternate
 *	setting that may be selected.  Each one includes a set of
 *	endpoपूर्णांक configurations.  They will be in no particular order.
 * @cur_altsetting: the current altsetting.
 * @num_altsetting: number of altsettings defined.
 * @पूर्णांकf_assoc: पूर्णांकerface association descriptor
 * @minor: the minor number asचिन्हित to this पूर्णांकerface, अगर this
 *	पूर्णांकerface is bound to a driver that uses the USB major number.
 *	If this पूर्णांकerface करोes not use the USB major, this field should
 *	be unused.  The driver should set this value in the probe()
 *	function of the driver, after it has been asचिन्हित a minor
 *	number from the USB core by calling usb_रेजिस्टर_dev().
 * @condition: binding state of the पूर्णांकerface: not bound, binding
 *	(in probe()), bound to a driver, or unbinding (in disconnect())
 * @sysfs_files_created: sysfs attributes exist
 * @ep_devs_created: endpoपूर्णांक child pseuकरो-devices exist
 * @unरेजिस्टरing: flag set when the पूर्णांकerface is being unरेजिस्टरed
 * @needs_remote_wakeup: flag set when the driver requires remote-wakeup
 *	capability during स्वतःsuspend.
 * @needs_altsetting0: flag set when a set-पूर्णांकerface request क्रम altsetting 0
 *	has been deferred.
 * @needs_binding: flag set when the driver should be re-probed or unbound
 *	following a reset or suspend operation it करोesn't support.
 * @authorized: This allows to (de)authorize inभागidual पूर्णांकerfaces instead
 *	a whole device in contrast to the device authorization.
 * @dev: driver model's view of this device
 * @usb_dev: अगर an पूर्णांकerface is bound to the USB major, this will poपूर्णांक
 *	to the sysfs representation क्रम that device.
 * @reset_ws: Used क्रम scheduling resets from atomic context.
 * @resetting_device: USB core reset the device, so use alt setting 0 as
 *	current; needs bandwidth alloc after reset.
 *
 * USB device drivers attach to पूर्णांकerfaces on a physical device.  Each
 * पूर्णांकerface encapsulates a single high level function, such as feeding
 * an audio stream to a speaker or reporting a change in a volume control.
 * Many USB devices only have one पूर्णांकerface.  The protocol used to talk to
 * an पूर्णांकerface's endpoपूर्णांकs can be defined in a usb "class" specअगरication,
 * or by a product's venकरोr.  The (शेष) control endpoपूर्णांक is part of
 * every पूर्णांकerface, but is never listed among the पूर्णांकerface's descriptors.
 *
 * The driver that is bound to the पूर्णांकerface can use standard driver model
 * calls such as dev_get_drvdata() on the dev member of this काष्ठाure.
 *
 * Each पूर्णांकerface may have alternate settings.  The initial configuration
 * of a device sets altsetting 0, but the device driver can change
 * that setting using usb_set_पूर्णांकerface().  Alternate settings are often
 * used to control the use of periodic endpoपूर्णांकs, such as by having
 * dअगरferent endpoपूर्णांकs use dअगरferent amounts of reserved USB bandwidth.
 * All standards-conक्रमmant USB devices that use isochronous endpoपूर्णांकs
 * will use them in non-शेष settings.
 *
 * The USB specअगरication says that alternate setting numbers must run from
 * 0 to one less than the total number of alternate settings.  But some
 * devices manage to mess this up, and the काष्ठाures aren't necessarily
 * stored in numerical order anyhow.  Use usb_altnum_to_altsetting() to
 * look up an alternate setting in the altsetting array based on its number.
 */
काष्ठा usb_पूर्णांकerface अणु
	/* array of alternate settings क्रम this पूर्णांकerface,
	 * stored in no particular order */
	काष्ठा usb_host_पूर्णांकerface *altsetting;

	काष्ठा usb_host_पूर्णांकerface *cur_altsetting;	/* the currently
					 * active alternate setting */
	अचिन्हित num_altsetting;	/* number of alternate settings */

	/* If there is an पूर्णांकerface association descriptor then it will list
	 * the associated पूर्णांकerfaces */
	काष्ठा usb_पूर्णांकerface_assoc_descriptor *पूर्णांकf_assoc;

	पूर्णांक minor;			/* minor number this पूर्णांकerface is
					 * bound to */
	क्रमागत usb_पूर्णांकerface_condition condition;		/* state of binding */
	अचिन्हित sysfs_files_created:1;	/* the sysfs attributes exist */
	अचिन्हित ep_devs_created:1;	/* endpoपूर्णांक "devices" exist */
	अचिन्हित unरेजिस्टरing:1;	/* unregistration is in progress */
	अचिन्हित needs_remote_wakeup:1;	/* driver requires remote wakeup */
	अचिन्हित needs_altsetting0:1;	/* चयन to altsetting 0 is pending */
	अचिन्हित needs_binding:1;	/* needs delayed unbind/rebind */
	अचिन्हित resetting_device:1;	/* true: bandwidth alloc after reset */
	अचिन्हित authorized:1;		/* used क्रम पूर्णांकerface authorization */

	काष्ठा device dev;		/* पूर्णांकerface specअगरic device info */
	काष्ठा device *usb_dev;
	काष्ठा work_काष्ठा reset_ws;	/* क्रम resets in atomic context */
पूर्ण;
#घोषणा	to_usb_पूर्णांकerface(d) container_of(d, काष्ठा usb_पूर्णांकerface, dev)

अटल अंतरभूत व्योम *usb_get_पूर्णांकfdata(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस dev_get_drvdata(&पूर्णांकf->dev);
पूर्ण

अटल अंतरभूत व्योम usb_set_पूर्णांकfdata(काष्ठा usb_पूर्णांकerface *पूर्णांकf, व्योम *data)
अणु
	dev_set_drvdata(&पूर्णांकf->dev, data);
पूर्ण

काष्ठा usb_पूर्णांकerface *usb_get_पूर्णांकf(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
व्योम usb_put_पूर्णांकf(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

/* Hard limit */
#घोषणा USB_MAXENDPOINTS	30
/* this maximum is arbitrary */
#घोषणा USB_MAXINTERFACES	32
#घोषणा USB_MAXIADS		(USB_MAXINTERFACES/2)

/*
 * USB Resume Timer: Every Host controller driver should drive the resume
 * संकेतling on the bus क्रम the amount of समय defined by this macro.
 *
 * That way we will have a 'stable' behavior among all HCDs supported by Linux.
 *
 * Note that the USB Specअगरication states we should drive resume क्रम *at least*
 * 20 ms, but it करोesn't give an upper bound. This creates two possible
 * situations which we want to aव्योम:
 *
 * (a) someबार an msleep(20) might expire slightly beक्रमe 20 ms, which causes
 * us to fail USB Electrical Tests, thus failing Certअगरication
 *
 * (b) Some (many) devices actually need more than 20 ms of resume संकेतling,
 * and जबतक we can argue that's against the USB Specification, we don't have
 * control over which devices a certअगरication laboratory will be using क्रम
 * certअगरication. If CertLab uses a device which was tested against Winकरोws and
 * that happens to have relaxed resume संकेतling rules, we might fall पूर्णांकo
 * situations where we fail पूर्णांकeroperability and electrical tests.
 *
 * In order to aव्योम both conditions, we're using a 40 ms resume समयout, which
 * should cope with both LPJ calibration errors and devices not following every
 * detail of the USB Specअगरication.
 */
#घोषणा USB_RESUME_TIMEOUT	40 /* ms */

/**
 * काष्ठा usb_पूर्णांकerface_cache - दीर्घ-term representation of a device पूर्णांकerface
 * @num_altsetting: number of altsettings defined.
 * @ref: reference counter.
 * @altsetting: variable-length array of पूर्णांकerface काष्ठाures, one क्रम
 *	each alternate setting that may be selected.  Each one includes a
 *	set of endpoपूर्णांक configurations.  They will be in no particular order.
 *
 * These काष्ठाures persist क्रम the lअगरeसमय of a usb_device, unlike
 * काष्ठा usb_पूर्णांकerface (which persists only as दीर्घ as its configuration
 * is installed).  The altsetting arrays can be accessed through these
 * काष्ठाures at any समय, permitting comparison of configurations and
 * providing support क्रम the /sys/kernel/debug/usb/devices pseuकरो-file.
 */
काष्ठा usb_पूर्णांकerface_cache अणु
	अचिन्हित num_altsetting;	/* number of alternate settings */
	काष्ठा kref ref;		/* reference counter */

	/* variable-length array of alternate settings क्रम this पूर्णांकerface,
	 * stored in no particular order */
	काष्ठा usb_host_पूर्णांकerface altsetting[];
पूर्ण;
#घोषणा	ref_to_usb_पूर्णांकerface_cache(r) \
		container_of(r, काष्ठा usb_पूर्णांकerface_cache, ref)
#घोषणा	altsetting_to_usb_पूर्णांकerface_cache(a) \
		container_of(a, काष्ठा usb_पूर्णांकerface_cache, altsetting[0])

/**
 * काष्ठा usb_host_config - representation of a device's configuration
 * @desc: the device's configuration descriptor.
 * @string: poपूर्णांकer to the cached version of the iConfiguration string, अगर
 *	present क्रम this configuration.
 * @पूर्णांकf_assoc: list of any पूर्णांकerface association descriptors in this config
 * @पूर्णांकerface: array of poपूर्णांकers to usb_पूर्णांकerface काष्ठाures, one क्रम each
 *	पूर्णांकerface in the configuration.  The number of पूर्णांकerfaces is stored
 *	in desc.bNumInterfaces.  These poपूर्णांकers are valid only जबतक the
 *	configuration is active.
 * @पूर्णांकf_cache: array of poपूर्णांकers to usb_पूर्णांकerface_cache काष्ठाures, one
 *	क्रम each पूर्णांकerface in the configuration.  These काष्ठाures exist
 *	क्रम the entire lअगरe of the device.
 * @extra: poपूर्णांकer to buffer containing all extra descriptors associated
 *	with this configuration (those preceding the first पूर्णांकerface
 *	descriptor).
 * @extralen: length of the extra descriptors buffer.
 *
 * USB devices may have multiple configurations, but only one can be active
 * at any समय.  Each encapsulates a dअगरferent operational environment;
 * क्रम example, a dual-speed device would have separate configurations क्रम
 * full-speed and high-speed operation.  The number of configurations
 * available is stored in the device descriptor as bNumConfigurations.
 *
 * A configuration can contain multiple पूर्णांकerfaces.  Each corresponds to
 * a dअगरferent function of the USB device, and all are available whenever
 * the configuration is active.  The USB standard says that पूर्णांकerfaces
 * are supposed to be numbered from 0 to desc.bNumInterfaces-1, but a lot
 * of devices get this wrong.  In addition, the पूर्णांकerface array is not
 * guaranteed to be sorted in numerical order.  Use usb_अगरnum_to_अगर() to
 * look up an पूर्णांकerface entry based on its number.
 *
 * Device drivers should not attempt to activate configurations.  The choice
 * of which configuration to install is a policy decision based on such
 * considerations as available घातer, functionality provided, and the user's
 * desires (expressed through userspace tools).  However, drivers can call
 * usb_reset_configuration() to reinitialize the current configuration and
 * all its पूर्णांकerfaces.
 */
काष्ठा usb_host_config अणु
	काष्ठा usb_config_descriptor	desc;

	अक्षर *string;		/* iConfiguration string, अगर present */

	/* List of any Interface Association Descriptors in this
	 * configuration. */
	काष्ठा usb_पूर्णांकerface_assoc_descriptor *पूर्णांकf_assoc[USB_MAXIADS];

	/* the पूर्णांकerfaces associated with this configuration,
	 * stored in no particular order */
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface[USB_MAXINTERFACES];

	/* Interface inक्रमmation available even when this is not the
	 * active configuration */
	काष्ठा usb_पूर्णांकerface_cache *पूर्णांकf_cache[USB_MAXINTERFACES];

	अचिन्हित अक्षर *extra;   /* Extra descriptors */
	पूर्णांक extralen;
पूर्ण;

/* USB2.0 and USB3.0 device BOS descriptor set */
काष्ठा usb_host_bos अणु
	काष्ठा usb_bos_descriptor	*desc;

	/* wireless cap descriptor is handled by wusb */
	काष्ठा usb_ext_cap_descriptor	*ext_cap;
	काष्ठा usb_ss_cap_descriptor	*ss_cap;
	काष्ठा usb_ssp_cap_descriptor	*ssp_cap;
	काष्ठा usb_ss_container_id_descriptor	*ss_id;
	काष्ठा usb_pपंचांग_cap_descriptor	*pपंचांग_cap;
पूर्ण;

पूर्णांक __usb_get_extra_descriptor(अक्षर *buffer, अचिन्हित size,
	अचिन्हित अक्षर type, व्योम **ptr, माप_प्रकार min);
#घोषणा usb_get_extra_descriptor(अगरpoपूर्णांक, type, ptr) \
				__usb_get_extra_descriptor((अगरpoपूर्णांक)->extra, \
				(अगरpoपूर्णांक)->extralen, \
				type, (व्योम **)ptr, माप(**(ptr)))

/* ----------------------------------------------------------------------- */

/* USB device number allocation biपंचांगap */
काष्ठा usb_devmap अणु
	अचिन्हित दीर्घ devicemap[128 / (8*माप(अचिन्हित दीर्घ))];
पूर्ण;

/*
 * Allocated per bus (tree of devices) we have:
 */
काष्ठा usb_bus अणु
	काष्ठा device *controller;	/* host side hardware */
	काष्ठा device *sysdev;		/* as seen from firmware or bus */
	पूर्णांक busnum;			/* Bus number (in order of reg) */
	स्थिर अक्षर *bus_name;		/* stable id (PCI slot_name etc) */
	u8 uses_pio_क्रम_control;	/*
					 * Does the host controller use PIO
					 * क्रम control transfers?
					 */
	u8 otg_port;			/* 0, or number of OTG/HNP port */
	अचिन्हित is_b_host:1;		/* true during some HNP roleचयनes */
	अचिन्हित b_hnp_enable:1;	/* OTG: did A-Host enable HNP? */
	अचिन्हित no_stop_on_लघु:1;    /*
					 * Quirk: some controllers करोn't stop
					 * the ep queue on a लघु transfer
					 * with the URB_SHORT_NOT_OK flag set.
					 */
	अचिन्हित no_sg_स्थिरraपूर्णांक:1;	/* no sg स्थिरraपूर्णांक */
	अचिन्हित sg_tablesize;		/* 0 or largest number of sg list entries */

	पूर्णांक devnum_next;		/* Next खोलो device number in
					 * round-robin allocation */
	काष्ठा mutex devnum_next_mutex; /* devnum_next mutex */

	काष्ठा usb_devmap devmap;	/* device address allocation map */
	काष्ठा usb_device *root_hub;	/* Root hub */
	काष्ठा usb_bus *hs_companion;	/* Companion EHCI bus, अगर any */

	पूर्णांक bandwidth_allocated;	/* on this bus: how much of the समय
					 * reserved क्रम periodic (पूर्णांकr/iso)
					 * requests is used, on average?
					 * Units: microseconds/frame.
					 * Limits: Full/low speed reserve 90%,
					 * जबतक high speed reserves 80%.
					 */
	पूर्णांक bandwidth_पूर्णांक_reqs;		/* number of Interrupt requests */
	पूर्णांक bandwidth_isoc_reqs;	/* number of Isoc. requests */

	अचिन्हित resuming_ports;	/* bit array: resuming root-hub ports */

#अगर defined(CONFIG_USB_MON) || defined(CONFIG_USB_MON_MODULE)
	काष्ठा mon_bus *mon_bus;	/* non-null when associated */
	पूर्णांक monitored;			/* non-zero when monitored */
#पूर्ण_अगर
पूर्ण;

काष्ठा usb_dev_state;

/* ----------------------------------------------------------------------- */

काष्ठा usb_tt;

क्रमागत usb_device_removable अणु
	USB_DEVICE_REMOVABLE_UNKNOWN = 0,
	USB_DEVICE_REMOVABLE,
	USB_DEVICE_FIXED,
पूर्ण;

क्रमागत usb_port_connect_type अणु
	USB_PORT_CONNECT_TYPE_UNKNOWN = 0,
	USB_PORT_CONNECT_TYPE_HOT_PLUG,
	USB_PORT_CONNECT_TYPE_HARD_WIRED,
	USB_PORT_NOT_USED,
पूर्ण;

/*
 * USB port quirks.
 */

/* For the given port, prefer the old (faster) क्रमागतeration scheme. */
#घोषणा USB_PORT_QUIRK_OLD_SCHEME	BIT(0)

/* Decrease TRSTRCY to 10ms during device क्रमागतeration. */
#घोषणा USB_PORT_QUIRK_FAST_ENUM	BIT(1)

/*
 * USB 2.0 Link Power Management (LPM) parameters.
 */
काष्ठा usb2_lpm_parameters अणु
	/* Best efक्रमt service latency indicate how दीर्घ the host will drive
	 * resume on an निकास from L1.
	 */
	अचिन्हित पूर्णांक besl;

	/* Timeout value in microseconds क्रम the L1 inactivity (LPM) समयr.
	 * When the समयr counts to zero, the parent hub will initiate a LPM
	 * transition to L1.
	 */
	पूर्णांक समयout;
पूर्ण;

/*
 * USB 3.0 Link Power Management (LPM) parameters.
 *
 * PEL and SEL are USB 3.0 Link PM latencies क्रम device-initiated LPM निकास.
 * MEL is the USB 3.0 Link PM latency क्रम host-initiated LPM निकास.
 * All three are stored in nanoseconds.
 */
काष्ठा usb3_lpm_parameters अणु
	/*
	 * Maximum निकास latency (MEL) क्रम the host to send a packet to the
	 * device (either a Ping क्रम isoc endpoपूर्णांकs, or a data packet क्रम
	 * पूर्णांकerrupt endpoपूर्णांकs), the hubs to decode the packet, and क्रम all hubs
	 * in the path to transition the links to U0.
	 */
	अचिन्हित पूर्णांक mel;
	/*
	 * Maximum निकास latency क्रम a device-initiated LPM transition to bring
	 * all links पूर्णांकo U0.  Abbreviated as "PEL" in section 9.4.12 of the USB
	 * 3.0 spec, with no explanation of what "P" stands क्रम.  "Path"?
	 */
	अचिन्हित पूर्णांक pel;

	/*
	 * The System Exit Latency (SEL) includes PEL, and three other
	 * latencies.  After a device initiates a U0 transition, it will take
	 * some समय from when the device sends the ERDY to when it will finally
	 * receive the data packet.  Basically, SEL should be the worse-हाल
	 * latency from when a device starts initiating a U0 transition to when
	 * it will get data.
	 */
	अचिन्हित पूर्णांक sel;
	/*
	 * The idle समयout value that is currently programmed पूर्णांकo the parent
	 * hub क्रम this device.  When the समयr counts to zero, the parent hub
	 * will initiate an LPM transition to either U1 or U2.
	 */
	पूर्णांक समयout;
पूर्ण;

/**
 * काष्ठा usb_device - kernel's representation of a USB device
 * @devnum: device number; address on a USB bus
 * @devpath: device ID string क्रम use in messages (e.g., /port/...)
 * @route: tree topology hex string क्रम use with xHCI
 * @state: device state: configured, not attached, etc.
 * @speed: device speed: high/full/low (or error)
 * @rx_lanes: number of rx lanes in use, USB 3.2 adds dual-lane support
 * @tx_lanes: number of tx lanes in use, USB 3.2 adds dual-lane support
 * @ssp_rate: SuperSpeed Plus phy संकेतing rate and lane count
 * @tt: Transaction Translator info; used with low/full speed dev, highspeed hub
 * @ttport: device port on that tt hub
 * @toggle: one bit क्रम each endpoपूर्णांक, with ([0] = IN, [1] = OUT) endpoपूर्णांकs
 * @parent: our hub, unless we're the root
 * @bus: bus we're part of
 * @ep0: endpoपूर्णांक 0 data (शेष control pipe)
 * @dev: generic device पूर्णांकerface
 * @descriptor: USB device descriptor
 * @bos: USB device BOS descriptor set
 * @config: all of the device's configs
 * @actconfig: the active configuration
 * @ep_in: array of IN endpoपूर्णांकs
 * @ep_out: array of OUT endpoपूर्णांकs
 * @rawdescriptors: raw descriptors क्रम each config
 * @bus_mA: Current available from the bus
 * @portnum: parent port number (origin 1)
 * @level: number of USB hub ancestors
 * @devaddr: device address, XHCI: asचिन्हित by HW, others: same as devnum
 * @can_submit: URBs may be submitted
 * @persist_enabled:  USB_PERSIST enabled क्रम this device
 * @have_langid: whether string_langid is valid
 * @authorized: policy has said we can use it;
 *	(user space) policy determines अगर we authorize this device to be
 *	used or not. By शेष, wired USB devices are authorized.
 *	WUSB devices are not, until we authorize them from user space.
 *	FIXME -- complete करोc
 * @authenticated: Crypto authentication passed
 * @wusb: device is Wireless USB
 * @lpm_capable: device supports LPM
 * @usb2_hw_lpm_capable: device can perक्रमm USB2 hardware LPM
 * @usb2_hw_lpm_besl_capable: device can perक्रमm USB2 hardware BESL LPM
 * @usb2_hw_lpm_enabled: USB2 hardware LPM is enabled
 * @usb2_hw_lpm_allowed: Userspace allows USB 2.0 LPM to be enabled
 * @usb3_lpm_u1_enabled: USB3 hardware U1 LPM enabled
 * @usb3_lpm_u2_enabled: USB3 hardware U2 LPM enabled
 * @string_langid: language ID क्रम strings
 * @product: iProduct string, अगर present (अटल)
 * @manufacturer: iManufacturer string, अगर present (अटल)
 * @serial: iSerialNumber string, अगर present (अटल)
 * @filelist: usbfs files that are खोलो to this device
 * @maxchild: number of ports अगर hub
 * @quirks: quirks of the whole device
 * @urbnum: number of URBs submitted क्रम the whole device
 * @active_duration: total समय device is not suspended
 * @connect_समय: समय device was first connected
 * @करो_remote_wakeup:  remote wakeup should be enabled
 * @reset_resume: needs reset instead of resume
 * @port_is_suspended: the upstream port is suspended (L2 or U3)
 * @wusb_dev: अगर this is a Wireless USB device, link to the WUSB
 *	specअगरic data क्रम the device.
 * @slot_id: Slot ID asचिन्हित by xHCI
 * @removable: Device can be physically हटाओd from this port
 * @l1_params: best efक्रम service latency क्रम USB2 L1 LPM state, and L1 समयout.
 * @u1_params: निकास latencies क्रम USB3 U1 LPM state, and hub-initiated समयout.
 * @u2_params: निकास latencies क्रम USB3 U2 LPM state, and hub-initiated समयout.
 * @lpm_disable_count: Ref count used by usb_disable_lpm() and usb_enable_lpm()
 *	to keep track of the number of functions that require USB 3.0 Link Power
 *	Management to be disabled क्रम this usb_device.  This count should only
 *	be manipulated by those functions, with the bandwidth_mutex is held.
 * @hub_delay: cached value consisting of:
 *	parent->hub_delay + wHubDelay + tTPTransmissionDelay (40ns)
 *	Will be used as wValue क्रम SetIsochDelay requests.
 * @use_generic_driver: ask driver core to reprobe using the generic driver.
 *
 * Notes:
 * Usbcore drivers should not set usbdev->state directly.  Instead use
 * usb_set_device_state().
 */
काष्ठा usb_device अणु
	पूर्णांक		devnum;
	अक्षर		devpath[16];
	u32		route;
	क्रमागत usb_device_state	state;
	क्रमागत usb_device_speed	speed;
	अचिन्हित पूर्णांक		rx_lanes;
	अचिन्हित पूर्णांक		tx_lanes;
	क्रमागत usb_ssp_rate	ssp_rate;

	काष्ठा usb_tt	*tt;
	पूर्णांक		ttport;

	अचिन्हित पूर्णांक toggle[2];

	काष्ठा usb_device *parent;
	काष्ठा usb_bus *bus;
	काष्ठा usb_host_endpoपूर्णांक ep0;

	काष्ठा device dev;

	काष्ठा usb_device_descriptor descriptor;
	काष्ठा usb_host_bos *bos;
	काष्ठा usb_host_config *config;

	काष्ठा usb_host_config *actconfig;
	काष्ठा usb_host_endpoपूर्णांक *ep_in[16];
	काष्ठा usb_host_endpoपूर्णांक *ep_out[16];

	अक्षर **rawdescriptors;

	अचिन्हित लघु bus_mA;
	u8 portnum;
	u8 level;
	u8 devaddr;

	अचिन्हित can_submit:1;
	अचिन्हित persist_enabled:1;
	अचिन्हित have_langid:1;
	अचिन्हित authorized:1;
	अचिन्हित authenticated:1;
	अचिन्हित wusb:1;
	अचिन्हित lpm_capable:1;
	अचिन्हित usb2_hw_lpm_capable:1;
	अचिन्हित usb2_hw_lpm_besl_capable:1;
	अचिन्हित usb2_hw_lpm_enabled:1;
	अचिन्हित usb2_hw_lpm_allowed:1;
	अचिन्हित usb3_lpm_u1_enabled:1;
	अचिन्हित usb3_lpm_u2_enabled:1;
	पूर्णांक string_langid;

	/* अटल strings from the device */
	अक्षर *product;
	अक्षर *manufacturer;
	अक्षर *serial;

	काष्ठा list_head filelist;

	पूर्णांक maxchild;

	u32 quirks;
	atomic_t urbnum;

	अचिन्हित दीर्घ active_duration;

#अगर_घोषित CONFIG_PM
	अचिन्हित दीर्घ connect_समय;

	अचिन्हित करो_remote_wakeup:1;
	अचिन्हित reset_resume:1;
	अचिन्हित port_is_suspended:1;
#पूर्ण_अगर
	काष्ठा wusb_dev *wusb_dev;
	पूर्णांक slot_id;
	क्रमागत usb_device_removable removable;
	काष्ठा usb2_lpm_parameters l1_params;
	काष्ठा usb3_lpm_parameters u1_params;
	काष्ठा usb3_lpm_parameters u2_params;
	अचिन्हित lpm_disable_count;

	u16 hub_delay;
	अचिन्हित use_generic_driver:1;
पूर्ण;
#घोषणा	to_usb_device(d) container_of(d, काष्ठा usb_device, dev)

अटल अंतरभूत काष्ठा usb_device *पूर्णांकerface_to_usbdev(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस to_usb_device(पूर्णांकf->dev.parent);
पूर्ण

बाह्य काष्ठा usb_device *usb_get_dev(काष्ठा usb_device *dev);
बाह्य व्योम usb_put_dev(काष्ठा usb_device *dev);
बाह्य काष्ठा usb_device *usb_hub_find_child(काष्ठा usb_device *hdev,
	पूर्णांक port1);

/**
 * usb_hub_क्रम_each_child - iterate over all child devices on the hub
 * @hdev:  USB device beदीर्घing to the usb hub
 * @port1: portnum associated with child device
 * @child: child device poपूर्णांकer
 */
#घोषणा usb_hub_क्रम_each_child(hdev, port1, child) \
	क्रम (port1 = 1,	child =	usb_hub_find_child(hdev, port1); \
			port1 <= hdev->maxchild; \
			child = usb_hub_find_child(hdev, ++port1)) \
		अगर (!child) जारी; अन्यथा

/* USB device locking */
#घोषणा usb_lock_device(udev)			device_lock(&(udev)->dev)
#घोषणा usb_unlock_device(udev)			device_unlock(&(udev)->dev)
#घोषणा usb_lock_device_पूर्णांकerruptible(udev)	device_lock_पूर्णांकerruptible(&(udev)->dev)
#घोषणा usb_trylock_device(udev)		device_trylock(&(udev)->dev)
बाह्य पूर्णांक usb_lock_device_क्रम_reset(काष्ठा usb_device *udev,
				     स्थिर काष्ठा usb_पूर्णांकerface *अगरace);

/* USB port reset क्रम device reinitialization */
बाह्य पूर्णांक usb_reset_device(काष्ठा usb_device *dev);
बाह्य व्योम usb_queue_reset_device(काष्ठा usb_पूर्णांकerface *dev);

बाह्य काष्ठा device *usb_पूर्णांकf_get_dma_device(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

#अगर_घोषित CONFIG_ACPI
बाह्य पूर्णांक usb_acpi_set_घातer_state(काष्ठा usb_device *hdev, पूर्णांक index,
	bool enable);
बाह्य bool usb_acpi_घातer_manageable(काष्ठा usb_device *hdev, पूर्णांक index);
#अन्यथा
अटल अंतरभूत पूर्णांक usb_acpi_set_घातer_state(काष्ठा usb_device *hdev, पूर्णांक index,
	bool enable) अणु वापस 0; पूर्ण
अटल अंतरभूत bool usb_acpi_घातer_manageable(काष्ठा usb_device *hdev, पूर्णांक index)
	अणु वापस true; पूर्ण
#पूर्ण_अगर

/* USB स्वतःsuspend and स्वतःresume */
#अगर_घोषित CONFIG_PM
बाह्य व्योम usb_enable_स्वतःsuspend(काष्ठा usb_device *udev);
बाह्य व्योम usb_disable_स्वतःsuspend(काष्ठा usb_device *udev);

बाह्य पूर्णांक usb_स्वतःpm_get_पूर्णांकerface(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
बाह्य व्योम usb_स्वतःpm_put_पूर्णांकerface(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
बाह्य पूर्णांक usb_स्वतःpm_get_पूर्णांकerface_async(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
बाह्य व्योम usb_स्वतःpm_put_पूर्णांकerface_async(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
बाह्य व्योम usb_स्वतःpm_get_पूर्णांकerface_no_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
बाह्य व्योम usb_स्वतःpm_put_पूर्णांकerface_no_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

अटल अंतरभूत व्योम usb_mark_last_busy(काष्ठा usb_device *udev)
अणु
	pm_runसमय_mark_last_busy(&udev->dev);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक usb_enable_स्वतःsuspend(काष्ठा usb_device *udev)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_disable_स्वतःsuspend(काष्ठा usb_device *udev)
अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक usb_स्वतःpm_get_पूर्णांकerface(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_स्वतःpm_get_पूर्णांकerface_async(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु वापस 0; पूर्ण

अटल अंतरभूत व्योम usb_स्वतःpm_put_पूर्णांकerface(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु पूर्ण
अटल अंतरभूत व्योम usb_स्वतःpm_put_पूर्णांकerface_async(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु पूर्ण
अटल अंतरभूत व्योम usb_स्वतःpm_get_पूर्णांकerface_no_resume(
		काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु पूर्ण
अटल अंतरभूत व्योम usb_स्वतःpm_put_पूर्णांकerface_no_suspend(
		काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु पूर्ण
अटल अंतरभूत व्योम usb_mark_last_busy(काष्ठा usb_device *udev)
अणु पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक usb_disable_lpm(काष्ठा usb_device *udev);
बाह्य व्योम usb_enable_lpm(काष्ठा usb_device *udev);
/* Same as above, but these functions lock/unlock the bandwidth_mutex. */
बाह्य पूर्णांक usb_unlocked_disable_lpm(काष्ठा usb_device *udev);
बाह्य व्योम usb_unlocked_enable_lpm(काष्ठा usb_device *udev);

बाह्य पूर्णांक usb_disable_lपंचांग(काष्ठा usb_device *udev);
बाह्य व्योम usb_enable_lपंचांग(काष्ठा usb_device *udev);

अटल अंतरभूत bool usb_device_supports_lपंचांग(काष्ठा usb_device *udev)
अणु
	अगर (udev->speed < USB_SPEED_SUPER || !udev->bos || !udev->bos->ss_cap)
		वापस false;
	वापस udev->bos->ss_cap->bmAttributes & USB_LTM_SUPPORT;
पूर्ण

अटल अंतरभूत bool usb_device_no_sg_स्थिरraपूर्णांक(काष्ठा usb_device *udev)
अणु
	वापस udev && udev->bus && udev->bus->no_sg_स्थिरraपूर्णांक;
पूर्ण


/*-------------------------------------------------------------------------*/

/* क्रम drivers using iso endpoपूर्णांकs */
बाह्य पूर्णांक usb_get_current_frame_number(काष्ठा usb_device *usb_dev);

/* Sets up a group of bulk endpoपूर्णांकs to support multiple stream IDs. */
बाह्य पूर्णांक usb_alloc_streams(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps,
		अचिन्हित पूर्णांक num_streams, gfp_t mem_flags);

/* Reverts a group of bulk endpoपूर्णांकs back to not using stream IDs. */
बाह्य पूर्णांक usb_मुक्त_streams(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps,
		gfp_t mem_flags);

/* used these क्रम multi-पूर्णांकerface device registration */
बाह्य पूर्णांक usb_driver_claim_पूर्णांकerface(काष्ठा usb_driver *driver,
			काष्ठा usb_पूर्णांकerface *अगरace, व्योम *data);

/**
 * usb_पूर्णांकerface_claimed - वापसs true अगरf an पूर्णांकerface is claimed
 * @अगरace: the पूर्णांकerface being checked
 *
 * Return: %true (nonzero) अगरf the पूर्णांकerface is claimed, अन्यथा %false
 * (zero).
 *
 * Note:
 * Callers must own the driver model's usb bus पढ़ोlock.  So driver
 * probe() entries करोn't need extra locking, but other call contexts
 * may need to explicitly claim that lock.
 *
 */
अटल अंतरभूत पूर्णांक usb_पूर्णांकerface_claimed(काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	वापस (अगरace->dev.driver != शून्य);
पूर्ण

बाह्य व्योम usb_driver_release_पूर्णांकerface(काष्ठा usb_driver *driver,
			काष्ठा usb_पूर्णांकerface *अगरace);
स्थिर काष्ठा usb_device_id *usb_match_id(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
					 स्थिर काष्ठा usb_device_id *id);
बाह्य पूर्णांक usb_match_one_id(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			    स्थिर काष्ठा usb_device_id *id);

बाह्य पूर्णांक usb_क्रम_each_dev(व्योम *data, पूर्णांक (*fn)(काष्ठा usb_device *, व्योम *));
बाह्य काष्ठा usb_पूर्णांकerface *usb_find_पूर्णांकerface(काष्ठा usb_driver *drv,
		पूर्णांक minor);
बाह्य काष्ठा usb_पूर्णांकerface *usb_अगरnum_to_अगर(स्थिर काष्ठा usb_device *dev,
		अचिन्हित अगरnum);
बाह्य काष्ठा usb_host_पूर्णांकerface *usb_altnum_to_altsetting(
		स्थिर काष्ठा usb_पूर्णांकerface *पूर्णांकf, अचिन्हित पूर्णांक altnum);
बाह्य काष्ठा usb_host_पूर्णांकerface *usb_find_alt_setting(
		काष्ठा usb_host_config *config,
		अचिन्हित पूर्णांक अगरace_num,
		अचिन्हित पूर्णांक alt_num);

#अगर IS_REACHABLE(CONFIG_USB)
पूर्णांक usb_क्रम_each_port(व्योम *data, पूर्णांक (*fn)(काष्ठा device *, व्योम *));
#अन्यथा
अटल अंतरभूत पूर्णांक usb_क्रम_each_port(व्योम *data, पूर्णांक (*fn)(काष्ठा device *, व्योम *))
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* port claiming functions */
पूर्णांक usb_hub_claim_port(काष्ठा usb_device *hdev, अचिन्हित port1,
		काष्ठा usb_dev_state *owner);
पूर्णांक usb_hub_release_port(काष्ठा usb_device *hdev, अचिन्हित port1,
		काष्ठा usb_dev_state *owner);

/**
 * usb_make_path - वापसs stable device path in the usb tree
 * @dev: the device whose path is being स्थिरructed
 * @buf: where to put the string
 * @size: how big is "buf"?
 *
 * Return: Length of the string (> 0) or negative अगर size was too small.
 *
 * Note:
 * This identअगरier is पूर्णांकended to be "stable", reflecting physical paths in
 * hardware such as physical bus addresses क्रम host controllers or ports on
 * USB hubs.  That makes it stay the same until प्रणालीs are physically
 * reconfigured, by re-cabling a tree of USB devices or by moving USB host
 * controllers.  Adding and removing devices, including भव root hubs
 * in host controller driver modules, करोes not change these path identअगरiers;
 * neither करोes rebooting or re-क्रमागतerating.  These are more useful identअगरiers
 * than changeable ("unstable") ones like bus numbers or device addresses.
 *
 * With a partial exception क्रम devices connected to USB 2.0 root hubs, these
 * identअगरiers are also predictable.  So दीर्घ as the device tree isn't changed,
 * plugging any USB device पूर्णांकo a given hub port always gives it the same path.
 * Because of the use of "companion" controllers, devices connected to ports on
 * USB 2.0 root hubs (EHCI host controllers) will get one path ID अगर they are
 * high speed, and a dअगरferent one अगर they are full or low speed.
 */
अटल अंतरभूत पूर्णांक usb_make_path(काष्ठा usb_device *dev, अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक actual;
	actual = snम_लिखो(buf, size, "usb-%s-%s", dev->bus->bus_name,
			  dev->devpath);
	वापस (actual >= (पूर्णांक)size) ? -1 : actual;
पूर्ण

/*-------------------------------------------------------------------------*/

#घोषणा USB_DEVICE_ID_MATCH_DEVICE \
		(USB_DEVICE_ID_MATCH_VENDOR | USB_DEVICE_ID_MATCH_PRODUCT)
#घोषणा USB_DEVICE_ID_MATCH_DEV_RANGE \
		(USB_DEVICE_ID_MATCH_DEV_LO | USB_DEVICE_ID_MATCH_DEV_HI)
#घोषणा USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION \
		(USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_DEV_RANGE)
#घोषणा USB_DEVICE_ID_MATCH_DEV_INFO \
		(USB_DEVICE_ID_MATCH_DEV_CLASS | \
		USB_DEVICE_ID_MATCH_DEV_SUBCLASS | \
		USB_DEVICE_ID_MATCH_DEV_PROTOCOL)
#घोषणा USB_DEVICE_ID_MATCH_INT_INFO \
		(USB_DEVICE_ID_MATCH_INT_CLASS | \
		USB_DEVICE_ID_MATCH_INT_SUBCLASS | \
		USB_DEVICE_ID_MATCH_INT_PROTOCOL)

/**
 * USB_DEVICE - macro used to describe a specअगरic usb device
 * @vend: the 16 bit USB Venकरोr ID
 * @prod: the 16 bit USB Product ID
 *
 * This macro is used to create a काष्ठा usb_device_id that matches a
 * specअगरic device.
 */
#घोषणा USB_DEVICE(vend, prod) \
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE, \
	.idVenकरोr = (vend), \
	.idProduct = (prod)
/**
 * USB_DEVICE_VER - describe a specअगरic usb device with a version range
 * @vend: the 16 bit USB Venकरोr ID
 * @prod: the 16 bit USB Product ID
 * @lo: the bcdDevice_lo value
 * @hi: the bcdDevice_hi value
 *
 * This macro is used to create a काष्ठा usb_device_id that matches a
 * specअगरic device, with a version range.
 */
#घोषणा USB_DEVICE_VER(vend, prod, lo, hi) \
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION, \
	.idVenकरोr = (vend), \
	.idProduct = (prod), \
	.bcdDevice_lo = (lo), \
	.bcdDevice_hi = (hi)

/**
 * USB_DEVICE_INTERFACE_CLASS - describe a usb device with a specअगरic पूर्णांकerface class
 * @vend: the 16 bit USB Venकरोr ID
 * @prod: the 16 bit USB Product ID
 * @cl: bInterfaceClass value
 *
 * This macro is used to create a काष्ठा usb_device_id that matches a
 * specअगरic पूर्णांकerface class of devices.
 */
#घोषणा USB_DEVICE_INTERFACE_CLASS(vend, prod, cl) \
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE | \
		       USB_DEVICE_ID_MATCH_INT_CLASS, \
	.idVenकरोr = (vend), \
	.idProduct = (prod), \
	.bInterfaceClass = (cl)

/**
 * USB_DEVICE_INTERFACE_PROTOCOL - describe a usb device with a specअगरic पूर्णांकerface protocol
 * @vend: the 16 bit USB Venकरोr ID
 * @prod: the 16 bit USB Product ID
 * @pr: bInterfaceProtocol value
 *
 * This macro is used to create a काष्ठा usb_device_id that matches a
 * specअगरic पूर्णांकerface protocol of devices.
 */
#घोषणा USB_DEVICE_INTERFACE_PROTOCOL(vend, prod, pr) \
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE | \
		       USB_DEVICE_ID_MATCH_INT_PROTOCOL, \
	.idVenकरोr = (vend), \
	.idProduct = (prod), \
	.bInterfaceProtocol = (pr)

/**
 * USB_DEVICE_INTERFACE_NUMBER - describe a usb device with a specअगरic पूर्णांकerface number
 * @vend: the 16 bit USB Venकरोr ID
 * @prod: the 16 bit USB Product ID
 * @num: bInterfaceNumber value
 *
 * This macro is used to create a काष्ठा usb_device_id that matches a
 * specअगरic पूर्णांकerface number of devices.
 */
#घोषणा USB_DEVICE_INTERFACE_NUMBER(vend, prod, num) \
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE | \
		       USB_DEVICE_ID_MATCH_INT_NUMBER, \
	.idVenकरोr = (vend), \
	.idProduct = (prod), \
	.bInterfaceNumber = (num)

/**
 * USB_DEVICE_INFO - macro used to describe a class of usb devices
 * @cl: bDeviceClass value
 * @sc: bDeviceSubClass value
 * @pr: bDeviceProtocol value
 *
 * This macro is used to create a काष्ठा usb_device_id that matches a
 * specअगरic class of devices.
 */
#घोषणा USB_DEVICE_INFO(cl, sc, pr) \
	.match_flags = USB_DEVICE_ID_MATCH_DEV_INFO, \
	.bDeviceClass = (cl), \
	.bDeviceSubClass = (sc), \
	.bDeviceProtocol = (pr)

/**
 * USB_INTERFACE_INFO - macro used to describe a class of usb पूर्णांकerfaces
 * @cl: bInterfaceClass value
 * @sc: bInterfaceSubClass value
 * @pr: bInterfaceProtocol value
 *
 * This macro is used to create a काष्ठा usb_device_id that matches a
 * specअगरic class of पूर्णांकerfaces.
 */
#घोषणा USB_INTERFACE_INFO(cl, sc, pr) \
	.match_flags = USB_DEVICE_ID_MATCH_INT_INFO, \
	.bInterfaceClass = (cl), \
	.bInterfaceSubClass = (sc), \
	.bInterfaceProtocol = (pr)

/**
 * USB_DEVICE_AND_INTERFACE_INFO - describe a specअगरic usb device with a class of usb पूर्णांकerfaces
 * @vend: the 16 bit USB Venकरोr ID
 * @prod: the 16 bit USB Product ID
 * @cl: bInterfaceClass value
 * @sc: bInterfaceSubClass value
 * @pr: bInterfaceProtocol value
 *
 * This macro is used to create a काष्ठा usb_device_id that matches a
 * specअगरic device with a specअगरic class of पूर्णांकerfaces.
 *
 * This is especially useful when explicitly matching devices that have
 * venकरोr specअगरic bDeviceClass values, but standards-compliant पूर्णांकerfaces.
 */
#घोषणा USB_DEVICE_AND_INTERFACE_INFO(vend, prod, cl, sc, pr) \
	.match_flags = USB_DEVICE_ID_MATCH_INT_INFO \
		| USB_DEVICE_ID_MATCH_DEVICE, \
	.idVenकरोr = (vend), \
	.idProduct = (prod), \
	.bInterfaceClass = (cl), \
	.bInterfaceSubClass = (sc), \
	.bInterfaceProtocol = (pr)

/**
 * USB_VENDOR_AND_INTERFACE_INFO - describe a specअगरic usb venकरोr with a class of usb पूर्णांकerfaces
 * @vend: the 16 bit USB Venकरोr ID
 * @cl: bInterfaceClass value
 * @sc: bInterfaceSubClass value
 * @pr: bInterfaceProtocol value
 *
 * This macro is used to create a काष्ठा usb_device_id that matches a
 * specअगरic venकरोr with a specअगरic class of पूर्णांकerfaces.
 *
 * This is especially useful when explicitly matching devices that have
 * venकरोr specअगरic bDeviceClass values, but standards-compliant पूर्णांकerfaces.
 */
#घोषणा USB_VENDOR_AND_INTERFACE_INFO(vend, cl, sc, pr) \
	.match_flags = USB_DEVICE_ID_MATCH_INT_INFO \
		| USB_DEVICE_ID_MATCH_VENDOR, \
	.idVenकरोr = (vend), \
	.bInterfaceClass = (cl), \
	.bInterfaceSubClass = (sc), \
	.bInterfaceProtocol = (pr)

/* ----------------------------------------------------------------------- */

/* Stuff क्रम dynamic usb ids */
काष्ठा usb_dynids अणु
	spinlock_t lock;
	काष्ठा list_head list;
पूर्ण;

काष्ठा usb_dynid अणु
	काष्ठा list_head node;
	काष्ठा usb_device_id id;
पूर्ण;

बाह्य sमाप_प्रकार usb_store_new_id(काष्ठा usb_dynids *dynids,
				स्थिर काष्ठा usb_device_id *id_table,
				काष्ठा device_driver *driver,
				स्थिर अक्षर *buf, माप_प्रकार count);

बाह्य sमाप_प्रकार usb_show_dynids(काष्ठा usb_dynids *dynids, अक्षर *buf);

/**
 * काष्ठा usbdrv_wrap - wrapper क्रम driver-model काष्ठाure
 * @driver: The driver-model core driver काष्ठाure.
 * @क्रम_devices: Non-zero क्रम device drivers, 0 क्रम पूर्णांकerface drivers.
 */
काष्ठा usbdrv_wrap अणु
	काष्ठा device_driver driver;
	पूर्णांक क्रम_devices;
पूर्ण;

/**
 * काष्ठा usb_driver - identअगरies USB पूर्णांकerface driver to usbcore
 * @name: The driver name should be unique among USB drivers,
 *	and should normally be the same as the module name.
 * @probe: Called to see अगर the driver is willing to manage a particular
 *	पूर्णांकerface on a device.  If it is, probe वापसs zero and uses
 *	usb_set_पूर्णांकfdata() to associate driver-specअगरic data with the
 *	पूर्णांकerface.  It may also use usb_set_पूर्णांकerface() to specअगरy the
 *	appropriate altsetting.  If unwilling to manage the पूर्णांकerface,
 *	वापस -ENODEV, अगर genuine IO errors occurred, an appropriate
 *	negative त्रुटि_सं value.
 * @disconnect: Called when the पूर्णांकerface is no दीर्घer accessible, usually
 *	because its device has been (or is being) disconnected or the
 *	driver module is being unloaded.
 * @unlocked_ioctl: Used क्रम drivers that want to talk to userspace through
 *	the "usbfs" fileप्रणाली.  This lets devices provide ways to
 *	expose inक्रमmation to user space regardless of where they
 *	करो (or करोn't) show up otherwise in the fileप्रणाली.
 * @suspend: Called when the device is going to be suspended by the
 *	प्रणाली either from प्रणाली sleep or runसमय suspend context. The
 *	वापस value will be ignored in प्रणाली sleep context, so करो NOT
 *	try to जारी using the device अगर suspend fails in this हाल.
 *	Instead, let the resume or reset-resume routine recover from
 *	the failure.
 * @resume: Called when the device is being resumed by the प्रणाली.
 * @reset_resume: Called when the suspended device has been reset instead
 *	of being resumed.
 * @pre_reset: Called by usb_reset_device() when the device is about to be
 *	reset.  This routine must not वापस until the driver has no active
 *	URBs क्रम the device, and no more URBs may be submitted until the
 *	post_reset method is called.
 * @post_reset: Called by usb_reset_device() after the device
 *	has been reset
 * @id_table: USB drivers use ID table to support hotplugging.
 *	Export this with MODULE_DEVICE_TABLE(usb,...).  This must be set
 *	or your driver's probe function will never get called.
 * @dev_groups: Attributes attached to the device that will be created once it
 *	is bound to the driver.
 * @dynids: used पूर्णांकernally to hold the list of dynamically added device
 *	ids क्रम this driver.
 * @drvwrap: Driver-model core काष्ठाure wrapper.
 * @no_dynamic_id: अगर set to 1, the USB core will not allow dynamic ids to be
 *	added to this driver by preventing the sysfs file from being created.
 * @supports_स्वतःsuspend: अगर set to 0, the USB core will not allow स्वतःsuspend
 *	क्रम पूर्णांकerfaces bound to this driver.
 * @soft_unbind: अगर set to 1, the USB core will not समाप्त URBs and disable
 *	endpoपूर्णांकs beक्रमe calling the driver's disconnect method.
 * @disable_hub_initiated_lpm: अगर set to 1, the USB core will not allow hubs
 *	to initiate lower घातer link state transitions when an idle समयout
 *	occurs.  Device-initiated USB 3.0 link PM will still be allowed.
 *
 * USB पूर्णांकerface drivers must provide a name, probe() and disconnect()
 * methods, and an id_table.  Other driver fields are optional.
 *
 * The id_table is used in hotplugging.  It holds a set of descriptors,
 * and specialized data may be associated with each entry.  That table
 * is used by both user and kernel mode hotplugging support.
 *
 * The probe() and disconnect() methods are called in a context where
 * they can sleep, but they should aव्योम abusing the privilege.  Most
 * work to connect to a device should be करोne when the device is खोलोed,
 * and unकरोne at the last बंद.  The disconnect code needs to address
 * concurrency issues with respect to खोलो() and बंद() methods, as
 * well as क्रमcing all pending I/O requests to complete (by unlinking
 * them as necessary, and blocking until the unlinks complete).
 */
काष्ठा usb_driver अणु
	स्थिर अक्षर *name;

	पूर्णांक (*probe) (काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		      स्थिर काष्ठा usb_device_id *id);

	व्योम (*disconnect) (काष्ठा usb_पूर्णांकerface *पूर्णांकf);

	पूर्णांक (*unlocked_ioctl) (काष्ठा usb_पूर्णांकerface *पूर्णांकf, अचिन्हित पूर्णांक code,
			व्योम *buf);

	पूर्णांक (*suspend) (काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message);
	पूर्णांक (*resume) (काष्ठा usb_पूर्णांकerface *पूर्णांकf);
	पूर्णांक (*reset_resume)(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

	पूर्णांक (*pre_reset)(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
	पूर्णांक (*post_reset)(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

	स्थिर काष्ठा usb_device_id *id_table;
	स्थिर काष्ठा attribute_group **dev_groups;

	काष्ठा usb_dynids dynids;
	काष्ठा usbdrv_wrap drvwrap;
	अचिन्हित पूर्णांक no_dynamic_id:1;
	अचिन्हित पूर्णांक supports_स्वतःsuspend:1;
	अचिन्हित पूर्णांक disable_hub_initiated_lpm:1;
	अचिन्हित पूर्णांक soft_unbind:1;
पूर्ण;
#घोषणा	to_usb_driver(d) container_of(d, काष्ठा usb_driver, drvwrap.driver)

/**
 * काष्ठा usb_device_driver - identअगरies USB device driver to usbcore
 * @name: The driver name should be unique among USB drivers,
 *	and should normally be the same as the module name.
 * @match: If set, used क्रम better device/driver matching.
 * @probe: Called to see अगर the driver is willing to manage a particular
 *	device.  If it is, probe वापसs zero and uses dev_set_drvdata()
 *	to associate driver-specअगरic data with the device.  If unwilling
 *	to manage the device, वापस a negative त्रुटि_सं value.
 * @disconnect: Called when the device is no दीर्घer accessible, usually
 *	because it has been (or is being) disconnected or the driver's
 *	module is being unloaded.
 * @suspend: Called when the device is going to be suspended by the प्रणाली.
 * @resume: Called when the device is being resumed by the प्रणाली.
 * @dev_groups: Attributes attached to the device that will be created once it
 *	is bound to the driver.
 * @drvwrap: Driver-model core काष्ठाure wrapper.
 * @id_table: used with @match() to select better matching driver at
 * 	probe() समय.
 * @supports_स्वतःsuspend: अगर set to 0, the USB core will not allow स्वतःsuspend
 *	क्रम devices bound to this driver.
 * @generic_subclass: अगर set to 1, the generic USB driver's probe, disconnect,
 *	resume and suspend functions will be called in addition to the driver's
 *	own, so this part of the setup करोes not need to be replicated.
 *
 * USB drivers must provide all the fields listed above except drvwrap,
 * match, and id_table.
 */
काष्ठा usb_device_driver अणु
	स्थिर अक्षर *name;

	bool (*match) (काष्ठा usb_device *udev);
	पूर्णांक (*probe) (काष्ठा usb_device *udev);
	व्योम (*disconnect) (काष्ठा usb_device *udev);

	पूर्णांक (*suspend) (काष्ठा usb_device *udev, pm_message_t message);
	पूर्णांक (*resume) (काष्ठा usb_device *udev, pm_message_t message);
	स्थिर काष्ठा attribute_group **dev_groups;
	काष्ठा usbdrv_wrap drvwrap;
	स्थिर काष्ठा usb_device_id *id_table;
	अचिन्हित पूर्णांक supports_स्वतःsuspend:1;
	अचिन्हित पूर्णांक generic_subclass:1;
पूर्ण;
#घोषणा	to_usb_device_driver(d) container_of(d, काष्ठा usb_device_driver, \
		drvwrap.driver)

/**
 * काष्ठा usb_class_driver - identअगरies a USB driver that wants to use the USB major number
 * @name: the usb class device name क्रम this driver.  Will show up in sysfs.
 * @devnode: Callback to provide a naming hपूर्णांक क्रम a possible
 *	device node to create.
 * @fops: poपूर्णांकer to the काष्ठा file_operations of this driver.
 * @minor_base: the start of the minor range क्रम this driver.
 *
 * This काष्ठाure is used क्रम the usb_रेजिस्टर_dev() and
 * usb_deरेजिस्टर_dev() functions, to consolidate a number of the
 * parameters used क्रम them.
 */
काष्ठा usb_class_driver अणु
	अक्षर *name;
	अक्षर *(*devnode)(काष्ठा device *dev, umode_t *mode);
	स्थिर काष्ठा file_operations *fops;
	पूर्णांक minor_base;
पूर्ण;

/*
 * use these in module_init()/module_निकास()
 * and करोn't क्रमget MODULE_DEVICE_TABLE(usb, ...)
 */
बाह्य पूर्णांक usb_रेजिस्टर_driver(काष्ठा usb_driver *, काष्ठा module *,
			       स्थिर अक्षर *);

/* use a define to aव्योम include chaining to get THIS_MODULE & मित्रs */
#घोषणा usb_रेजिस्टर(driver) \
	usb_रेजिस्टर_driver(driver, THIS_MODULE, KBUILD_MODNAME)

बाह्य व्योम usb_deरेजिस्टर(काष्ठा usb_driver *);

/**
 * module_usb_driver() - Helper macro क्रम रेजिस्टरing a USB driver
 * @__usb_driver: usb_driver काष्ठा
 *
 * Helper macro क्रम USB drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_usb_driver(__usb_driver) \
	module_driver(__usb_driver, usb_रेजिस्टर, \
		       usb_deरेजिस्टर)

बाह्य पूर्णांक usb_रेजिस्टर_device_driver(काष्ठा usb_device_driver *,
			काष्ठा module *);
बाह्य व्योम usb_deरेजिस्टर_device_driver(काष्ठा usb_device_driver *);

बाह्य पूर्णांक usb_रेजिस्टर_dev(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			    काष्ठा usb_class_driver *class_driver);
बाह्य व्योम usb_deरेजिस्टर_dev(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			       काष्ठा usb_class_driver *class_driver);

बाह्य पूर्णांक usb_disabled(व्योम);

/* ----------------------------------------------------------------------- */

/*
 * URB support, क्रम asynchronous request completions
 */

/*
 * urb->transfer_flags:
 *
 * Note: URB_सूची_IN/OUT is स्वतःmatically set in usb_submit_urb().
 */
#घोषणा URB_SHORT_NOT_OK	0x0001	/* report लघु पढ़ोs as errors */
#घोषणा URB_ISO_ASAP		0x0002	/* iso-only; use the first unexpired
					 * slot in the schedule */
#घोषणा URB_NO_TRANSFER_DMA_MAP	0x0004	/* urb->transfer_dma valid on submit */
#घोषणा URB_ZERO_PACKET		0x0040	/* Finish bulk OUT with लघु packet */
#घोषणा URB_NO_INTERRUPT	0x0080	/* HINT: no non-error पूर्णांकerrupt
					 * needed */
#घोषणा URB_FREE_BUFFER		0x0100	/* Free transfer buffer with the URB */

/* The following flags are used पूर्णांकernally by usbcore and HCDs */
#घोषणा URB_सूची_IN		0x0200	/* Transfer from device to host */
#घोषणा URB_सूची_OUT		0
#घोषणा URB_सूची_MASK		URB_सूची_IN

#घोषणा URB_DMA_MAP_SINGLE	0x00010000	/* Non-scatter-gather mapping */
#घोषणा URB_DMA_MAP_PAGE	0x00020000	/* HCD-unsupported S-G */
#घोषणा URB_DMA_MAP_SG		0x00040000	/* HCD-supported S-G */
#घोषणा URB_MAP_LOCAL		0x00080000	/* HCD-local-memory mapping */
#घोषणा URB_SETUP_MAP_SINGLE	0x00100000	/* Setup packet DMA mapped */
#घोषणा URB_SETUP_MAP_LOCAL	0x00200000	/* HCD-local setup packet */
#घोषणा URB_DMA_SG_COMBINED	0x00400000	/* S-G entries were combined */
#घोषणा URB_ALIGNED_TEMP_BUFFER	0x00800000	/* Temp buffer was alloc'd */

काष्ठा usb_iso_packet_descriptor अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक length;		/* expected length */
	अचिन्हित पूर्णांक actual_length;
	पूर्णांक status;
पूर्ण;

काष्ठा urb;

काष्ठा usb_anchor अणु
	काष्ठा list_head urb_list;
	रुको_queue_head_t रुको;
	spinlock_t lock;
	atomic_t suspend_wakeups;
	अचिन्हित पूर्णांक poisoned:1;
पूर्ण;

अटल अंतरभूत व्योम init_usb_anchor(काष्ठा usb_anchor *anchor)
अणु
	स_रखो(anchor, 0, माप(*anchor));
	INIT_LIST_HEAD(&anchor->urb_list);
	init_रुकोqueue_head(&anchor->रुको);
	spin_lock_init(&anchor->lock);
पूर्ण

प्रकार व्योम (*usb_complete_t)(काष्ठा urb *);

/**
 * काष्ठा urb - USB Request Block
 * @urb_list: For use by current owner of the URB.
 * @anchor_list: membership in the list of an anchor
 * @anchor: to anchor URBs to a common mooring
 * @ep: Poपूर्णांकs to the endpoपूर्णांक's data काष्ठाure.  Will eventually
 *	replace @pipe.
 * @pipe: Holds endpoपूर्णांक number, direction, type, and more.
 *	Create these values with the eight macros available;
 *	usb_अणुsnd,rcvपूर्णTYPEpipe(dev,endpoपूर्णांक), where the TYPE is "ctrl"
 *	(control), "bulk", "int" (पूर्णांकerrupt), or "iso" (isochronous).
 *	For example usb_sndbulkpipe() or usb_rcvपूर्णांकpipe().  Endpoपूर्णांक
 *	numbers range from zero to fअगरteen.  Note that "in" endpoपूर्णांक two
 *	is a dअगरferent endpoपूर्णांक (and pipe) from "out" endpoपूर्णांक two.
 *	The current configuration controls the existence, type, and
 *	maximum packet size of any given endpoपूर्णांक.
 * @stream_id: the endpoपूर्णांक's stream ID क्रम bulk streams
 * @dev: Identअगरies the USB device to perक्रमm the request.
 * @status: This is पढ़ो in non-iso completion functions to get the
 *	status of the particular request.  ISO requests only use it
 *	to tell whether the URB was unlinked; detailed status क्रम
 *	each frame is in the fields of the iso_frame-desc.
 * @transfer_flags: A variety of flags may be used to affect how URB
 *	submission, unlinking, or operation are handled.  Dअगरferent
 *	kinds of URB can use dअगरferent flags.
 * @transfer_buffer:  This identअगरies the buffer to (or from) which the I/O
 *	request will be perक्रमmed unless URB_NO_TRANSFER_DMA_MAP is set
 *	(however, करो not leave garbage in transfer_buffer even then).
 *	This buffer must be suitable क्रम DMA; allocate it with
 *	kदो_स्मृति() or equivalent.  For transfers to "in" endpoपूर्णांकs, contents
 *	of this buffer will be modअगरied.  This buffer is used क्रम the data
 *	stage of control transfers.
 * @transfer_dma: When transfer_flags includes URB_NO_TRANSFER_DMA_MAP,
 *	the device driver is saying that it provided this DMA address,
 *	which the host controller driver should use in preference to the
 *	transfer_buffer.
 * @sg: scatter gather buffer list, the buffer size of each element in
 * 	the list (except the last) must be भागisible by the endpoपूर्णांक's
 * 	max packet size अगर no_sg_स्थिरraपूर्णांक isn't set in 'struct usb_bus'
 * @num_mapped_sgs: (पूर्णांकernal) number of mapped sg entries
 * @num_sgs: number of entries in the sg list
 * @transfer_buffer_length: How big is transfer_buffer.  The transfer may
 *	be broken up पूर्णांकo chunks according to the current maximum packet
 *	size क्रम the endpoपूर्णांक, which is a function of the configuration
 *	and is encoded in the pipe.  When the length is zero, neither
 *	transfer_buffer nor transfer_dma is used.
 * @actual_length: This is पढ़ो in non-iso completion functions, and
 *	it tells how many bytes (out of transfer_buffer_length) were
 *	transferred.  It will normally be the same as requested, unless
 *	either an error was reported or a लघु पढ़ो was perक्रमmed.
 *	The URB_SHORT_NOT_OK transfer flag may be used to make such
 *	लघु पढ़ोs be reported as errors.
 * @setup_packet: Only used क्रम control transfers, this poपूर्णांकs to eight bytes
 *	of setup data.  Control transfers always start by sending this data
 *	to the device.  Then transfer_buffer is पढ़ो or written, अगर needed.
 * @setup_dma: DMA poपूर्णांकer क्रम the setup packet.  The caller must not use
 *	this field; setup_packet must poपूर्णांक to a valid buffer.
 * @start_frame: Returns the initial frame क्रम isochronous transfers.
 * @number_of_packets: Lists the number of ISO transfer buffers.
 * @पूर्णांकerval: Specअगरies the polling पूर्णांकerval क्रम पूर्णांकerrupt or isochronous
 *	transfers.  The units are frames (milliseconds) क्रम full and low
 *	speed devices, and microframes (1/8 millisecond) क्रम highspeed
 *	and SuperSpeed devices.
 * @error_count: Returns the number of ISO transfers that reported errors.
 * @context: For use in completion functions.  This normally poपूर्णांकs to
 *	request-specअगरic driver context.
 * @complete: Completion handler. This URB is passed as the parameter to the
 *	completion function.  The completion function may then करो what
 *	it likes with the URB, including resubmitting or मुक्तing it.
 * @iso_frame_desc: Used to provide arrays of ISO transfer buffers and to
 *	collect the transfer status क्रम each buffer.
 *
 * This काष्ठाure identअगरies USB transfer requests.  URBs must be allocated by
 * calling usb_alloc_urb() and मुक्तd with a call to usb_मुक्त_urb().
 * Initialization may be करोne using various usb_fill_*_urb() functions.  URBs
 * are submitted using usb_submit_urb(), and pending requests may be canceled
 * using usb_unlink_urb() or usb_समाप्त_urb().
 *
 * Data Transfer Buffers:
 *
 * Normally drivers provide I/O buffers allocated with kदो_स्मृति() or otherwise
 * taken from the general page pool.  That is provided by transfer_buffer
 * (control requests also use setup_packet), and host controller drivers
 * perक्रमm a dma mapping (and unmapping) क्रम each buffer transferred.  Those
 * mapping operations can be expensive on some platक्रमms (perhaps using a dma
 * bounce buffer or talking to an IOMMU),
 * although they're cheap on commodity x86 and ppc hardware.
 *
 * Alternatively, drivers may pass the URB_NO_TRANSFER_DMA_MAP transfer flag,
 * which tells the host controller driver that no such mapping is needed क्रम
 * the transfer_buffer since
 * the device driver is DMA-aware.  For example, a device driver might
 * allocate a DMA buffer with usb_alloc_coherent() or call usb_buffer_map().
 * When this transfer flag is provided, host controller drivers will
 * attempt to use the dma address found in the transfer_dma
 * field rather than determining a dma address themselves.
 *
 * Note that transfer_buffer must still be set अगर the controller
 * करोes not support DMA (as indicated by hcd_uses_dma()) and when talking
 * to root hub. If you have to trasfer between highmem zone and the device
 * on such controller, create a bounce buffer or bail out with an error.
 * If transfer_buffer cannot be set (is in highmem) and the controller is DMA
 * capable, assign शून्य to it, so that usbmon knows not to use the value.
 * The setup_packet must always be set, so it cannot be located in highmem.
 *
 * Initialization:
 *
 * All URBs submitted must initialize the dev, pipe, transfer_flags (may be
 * zero), and complete fields.  All URBs must also initialize
 * transfer_buffer and transfer_buffer_length.  They may provide the
 * URB_SHORT_NOT_OK transfer flag, indicating that लघु पढ़ोs are
 * to be treated as errors; that flag is invalid क्रम ग_लिखो requests.
 *
 * Bulk URBs may
 * use the URB_ZERO_PACKET transfer flag, indicating that bulk OUT transfers
 * should always terminate with a लघु packet, even अगर it means adding an
 * extra zero length packet.
 *
 * Control URBs must provide a valid poपूर्णांकer in the setup_packet field.
 * Unlike the transfer_buffer, the setup_packet may not be mapped क्रम DMA
 * beक्रमehand.
 *
 * Interrupt URBs must provide an पूर्णांकerval, saying how often (in milliseconds
 * or, क्रम highspeed devices, 125 microsecond units)
 * to poll क्रम transfers.  After the URB has been submitted, the पूर्णांकerval
 * field reflects how the transfer was actually scheduled.
 * The polling पूर्णांकerval may be more frequent than requested.
 * For example, some controllers have a maximum पूर्णांकerval of 32 milliseconds,
 * जबतक others support पूर्णांकervals of up to 1024 milliseconds.
 * Isochronous URBs also have transfer पूर्णांकervals.  (Note that क्रम isochronous
 * endpoपूर्णांकs, as well as high speed पूर्णांकerrupt endpoपूर्णांकs, the encoding of
 * the transfer पूर्णांकerval in the endpoपूर्णांक descriptor is logarithmic.
 * Device drivers must convert that value to linear units themselves.)
 *
 * If an isochronous endpoपूर्णांक queue isn't alपढ़ोy running, the host
 * controller will schedule a new URB to start as soon as bandwidth
 * utilization allows.  If the queue is running then a new URB will be
 * scheduled to start in the first transfer slot following the end of the
 * preceding URB, अगर that slot has not alपढ़ोy expired.  If the slot has
 * expired (which can happen when IRQ delivery is delayed क्रम a दीर्घ समय),
 * the scheduling behavior depends on the URB_ISO_ASAP flag.  If the flag
 * is clear then the URB will be scheduled to start in the expired slot,
 * implying that some of its packets will not be transferred; अगर the flag
 * is set then the URB will be scheduled in the first unexpired slot,
 * अवरोधing the queue's synchronization.  Upon URB completion, the
 * start_frame field will be set to the (micro)frame number in which the
 * transfer was scheduled.  Ranges क्रम frame counter values are HC-specअगरic
 * and can go from as low as 256 to as high as 65536 frames.
 *
 * Isochronous URBs have a dअगरferent data transfer model, in part because
 * the quality of service is only "best effort".  Callers provide specially
 * allocated URBs, with number_of_packets worth of iso_frame_desc काष्ठाures
 * at the end.  Each such packet is an inभागidual ISO transfer.  Isochronous
 * URBs are normally queued, submitted by drivers to arrange that
 * transfers are at least द्विगुन buffered, and then explicitly resubmitted
 * in completion handlers, so
 * that data (such as audio or video) streams at as स्थिरant a rate as the
 * host controller scheduler can support.
 *
 * Completion Callbacks:
 *
 * The completion callback is made in_पूर्णांकerrupt(), and one of the first
 * things that a completion handler should करो is check the status field.
 * The status field is provided क्रम all URBs.  It is used to report
 * unlinked URBs, and status क्रम all non-ISO transfers.  It should not
 * be examined beक्रमe the URB is वापसed to the completion handler.
 *
 * The context field is normally used to link URBs back to the relevant
 * driver or request state.
 *
 * When the completion callback is invoked क्रम non-isochronous URBs, the
 * actual_length field tells how many bytes were transferred.  This field
 * is updated even when the URB terminated with an error or was unlinked.
 *
 * ISO transfer status is reported in the status and actual_length fields
 * of the iso_frame_desc array, and the number of errors is reported in
 * error_count.  Completion callbacks क्रम ISO transfers will normally
 * (re)submit URBs to ensure a स्थिरant transfer rate.
 *
 * Note that even fields marked "public" should not be touched by the driver
 * when the urb is owned by the hcd, that is, since the call to
 * usb_submit_urb() till the entry पूर्णांकo the completion routine.
 */
काष्ठा urb अणु
	/* निजी: usb core and host controller only fields in the urb */
	काष्ठा kref kref;		/* reference count of the URB */
	पूर्णांक unlinked;			/* unlink error code */
	व्योम *hcpriv;			/* निजी data क्रम host controller */
	atomic_t use_count;		/* concurrent submissions counter */
	atomic_t reject;		/* submissions will fail */

	/* खुला: करोcumented fields in the urb that can be used by drivers */
	काष्ठा list_head urb_list;	/* list head क्रम use by the urb's
					 * current owner */
	काष्ठा list_head anchor_list;	/* the URB may be anchored */
	काष्ठा usb_anchor *anchor;
	काष्ठा usb_device *dev;		/* (in) poपूर्णांकer to associated device */
	काष्ठा usb_host_endpoपूर्णांक *ep;	/* (पूर्णांकernal) poपूर्णांकer to endpoपूर्णांक */
	अचिन्हित पूर्णांक pipe;		/* (in) pipe inक्रमmation */
	अचिन्हित पूर्णांक stream_id;		/* (in) stream ID */
	पूर्णांक status;			/* (वापस) non-ISO status */
	अचिन्हित पूर्णांक transfer_flags;	/* (in) URB_SHORT_NOT_OK | ...*/
	व्योम *transfer_buffer;		/* (in) associated data buffer */
	dma_addr_t transfer_dma;	/* (in) dma addr क्रम transfer_buffer */
	काष्ठा scatterlist *sg;		/* (in) scatter gather buffer list */
	पूर्णांक num_mapped_sgs;		/* (पूर्णांकernal) mapped sg entries */
	पूर्णांक num_sgs;			/* (in) number of entries in the sg list */
	u32 transfer_buffer_length;	/* (in) data buffer length */
	u32 actual_length;		/* (वापस) actual transfer length */
	अचिन्हित अक्षर *setup_packet;	/* (in) setup packet (control only) */
	dma_addr_t setup_dma;		/* (in) dma addr क्रम setup_packet */
	पूर्णांक start_frame;		/* (modअगरy) start frame (ISO) */
	पूर्णांक number_of_packets;		/* (in) number of ISO packets */
	पूर्णांक पूर्णांकerval;			/* (modअगरy) transfer पूर्णांकerval
					 * (INT/ISO) */
	पूर्णांक error_count;		/* (वापस) number of ISO errors */
	व्योम *context;			/* (in) context क्रम completion */
	usb_complete_t complete;	/* (in) completion routine */
	काष्ठा usb_iso_packet_descriptor iso_frame_desc[];
					/* (in) ISO ONLY */
पूर्ण;

/* ----------------------------------------------------------------------- */

/**
 * usb_fill_control_urb - initializes a control urb
 * @urb: poपूर्णांकer to the urb to initialize.
 * @dev: poपूर्णांकer to the काष्ठा usb_device क्रम this urb.
 * @pipe: the endpoपूर्णांक pipe
 * @setup_packet: poपूर्णांकer to the setup_packet buffer
 * @transfer_buffer: poपूर्णांकer to the transfer buffer
 * @buffer_length: length of the transfer buffer
 * @complete_fn: poपूर्णांकer to the usb_complete_t function
 * @context: what to set the urb context to.
 *
 * Initializes a control urb with the proper inक्रमmation needed to submit
 * it to a device.
 */
अटल अंतरभूत व्योम usb_fill_control_urb(काष्ठा urb *urb,
					काष्ठा usb_device *dev,
					अचिन्हित पूर्णांक pipe,
					अचिन्हित अक्षर *setup_packet,
					व्योम *transfer_buffer,
					पूर्णांक buffer_length,
					usb_complete_t complete_fn,
					व्योम *context)
अणु
	urb->dev = dev;
	urb->pipe = pipe;
	urb->setup_packet = setup_packet;
	urb->transfer_buffer = transfer_buffer;
	urb->transfer_buffer_length = buffer_length;
	urb->complete = complete_fn;
	urb->context = context;
पूर्ण

/**
 * usb_fill_bulk_urb - macro to help initialize a bulk urb
 * @urb: poपूर्णांकer to the urb to initialize.
 * @dev: poपूर्णांकer to the काष्ठा usb_device क्रम this urb.
 * @pipe: the endpoपूर्णांक pipe
 * @transfer_buffer: poपूर्णांकer to the transfer buffer
 * @buffer_length: length of the transfer buffer
 * @complete_fn: poपूर्णांकer to the usb_complete_t function
 * @context: what to set the urb context to.
 *
 * Initializes a bulk urb with the proper inक्रमmation needed to submit it
 * to a device.
 */
अटल अंतरभूत व्योम usb_fill_bulk_urb(काष्ठा urb *urb,
				     काष्ठा usb_device *dev,
				     अचिन्हित पूर्णांक pipe,
				     व्योम *transfer_buffer,
				     पूर्णांक buffer_length,
				     usb_complete_t complete_fn,
				     व्योम *context)
अणु
	urb->dev = dev;
	urb->pipe = pipe;
	urb->transfer_buffer = transfer_buffer;
	urb->transfer_buffer_length = buffer_length;
	urb->complete = complete_fn;
	urb->context = context;
पूर्ण

/**
 * usb_fill_पूर्णांक_urb - macro to help initialize a पूर्णांकerrupt urb
 * @urb: poपूर्णांकer to the urb to initialize.
 * @dev: poपूर्णांकer to the काष्ठा usb_device क्रम this urb.
 * @pipe: the endpoपूर्णांक pipe
 * @transfer_buffer: poपूर्णांकer to the transfer buffer
 * @buffer_length: length of the transfer buffer
 * @complete_fn: poपूर्णांकer to the usb_complete_t function
 * @context: what to set the urb context to.
 * @पूर्णांकerval: what to set the urb पूर्णांकerval to, encoded like
 *	the endpoपूर्णांक descriptor's bInterval value.
 *
 * Initializes a पूर्णांकerrupt urb with the proper inक्रमmation needed to submit
 * it to a device.
 *
 * Note that High Speed and SuperSpeed(+) पूर्णांकerrupt endpoपूर्णांकs use a logarithmic
 * encoding of the endpoपूर्णांक पूर्णांकerval, and express polling पूर्णांकervals in
 * microframes (eight per millisecond) rather than in frames (one per
 * millisecond).
 *
 * Wireless USB also uses the logarithmic encoding, but specअगरies it in units of
 * 128us instead of 125us.  For Wireless USB devices, the पूर्णांकerval is passed
 * through to the host controller, rather than being translated पूर्णांकo microframe
 * units.
 */
अटल अंतरभूत व्योम usb_fill_पूर्णांक_urb(काष्ठा urb *urb,
				    काष्ठा usb_device *dev,
				    अचिन्हित पूर्णांक pipe,
				    व्योम *transfer_buffer,
				    पूर्णांक buffer_length,
				    usb_complete_t complete_fn,
				    व्योम *context,
				    पूर्णांक पूर्णांकerval)
अणु
	urb->dev = dev;
	urb->pipe = pipe;
	urb->transfer_buffer = transfer_buffer;
	urb->transfer_buffer_length = buffer_length;
	urb->complete = complete_fn;
	urb->context = context;

	अगर (dev->speed == USB_SPEED_HIGH || dev->speed >= USB_SPEED_SUPER) अणु
		/* make sure पूर्णांकerval is within allowed range */
		पूर्णांकerval = clamp(पूर्णांकerval, 1, 16);

		urb->पूर्णांकerval = 1 << (पूर्णांकerval - 1);
	पूर्ण अन्यथा अणु
		urb->पूर्णांकerval = पूर्णांकerval;
	पूर्ण

	urb->start_frame = -1;
पूर्ण

बाह्य व्योम usb_init_urb(काष्ठा urb *urb);
बाह्य काष्ठा urb *usb_alloc_urb(पूर्णांक iso_packets, gfp_t mem_flags);
बाह्य व्योम usb_मुक्त_urb(काष्ठा urb *urb);
#घोषणा usb_put_urb usb_मुक्त_urb
बाह्य काष्ठा urb *usb_get_urb(काष्ठा urb *urb);
बाह्य पूर्णांक usb_submit_urb(काष्ठा urb *urb, gfp_t mem_flags);
बाह्य पूर्णांक usb_unlink_urb(काष्ठा urb *urb);
बाह्य व्योम usb_समाप्त_urb(काष्ठा urb *urb);
बाह्य व्योम usb_poison_urb(काष्ठा urb *urb);
बाह्य व्योम usb_unpoison_urb(काष्ठा urb *urb);
बाह्य व्योम usb_block_urb(काष्ठा urb *urb);
बाह्य व्योम usb_समाप्त_anchored_urbs(काष्ठा usb_anchor *anchor);
बाह्य व्योम usb_poison_anchored_urbs(काष्ठा usb_anchor *anchor);
बाह्य व्योम usb_unpoison_anchored_urbs(काष्ठा usb_anchor *anchor);
बाह्य व्योम usb_unlink_anchored_urbs(काष्ठा usb_anchor *anchor);
बाह्य व्योम usb_anchor_suspend_wakeups(काष्ठा usb_anchor *anchor);
बाह्य व्योम usb_anchor_resume_wakeups(काष्ठा usb_anchor *anchor);
बाह्य व्योम usb_anchor_urb(काष्ठा urb *urb, काष्ठा usb_anchor *anchor);
बाह्य व्योम usb_unanchor_urb(काष्ठा urb *urb);
बाह्य पूर्णांक usb_रुको_anchor_empty_समयout(काष्ठा usb_anchor *anchor,
					 अचिन्हित पूर्णांक समयout);
बाह्य काष्ठा urb *usb_get_from_anchor(काष्ठा usb_anchor *anchor);
बाह्य व्योम usb_scuttle_anchored_urbs(काष्ठा usb_anchor *anchor);
बाह्य पूर्णांक usb_anchor_empty(काष्ठा usb_anchor *anchor);

#घोषणा usb_unblock_urb	usb_unpoison_urb

/**
 * usb_urb_dir_in - check अगर an URB describes an IN transfer
 * @urb: URB to be checked
 *
 * Return: 1 अगर @urb describes an IN transfer (device-to-host),
 * otherwise 0.
 */
अटल अंतरभूत पूर्णांक usb_urb_dir_in(काष्ठा urb *urb)
अणु
	वापस (urb->transfer_flags & URB_सूची_MASK) == URB_सूची_IN;
पूर्ण

/**
 * usb_urb_dir_out - check अगर an URB describes an OUT transfer
 * @urb: URB to be checked
 *
 * Return: 1 अगर @urb describes an OUT transfer (host-to-device),
 * otherwise 0.
 */
अटल अंतरभूत पूर्णांक usb_urb_dir_out(काष्ठा urb *urb)
अणु
	वापस (urb->transfer_flags & URB_सूची_MASK) == URB_सूची_OUT;
पूर्ण

पूर्णांक usb_pipe_type_check(काष्ठा usb_device *dev, अचिन्हित पूर्णांक pipe);
पूर्णांक usb_urb_ep_type_check(स्थिर काष्ठा urb *urb);

व्योम *usb_alloc_coherent(काष्ठा usb_device *dev, माप_प्रकार size,
	gfp_t mem_flags, dma_addr_t *dma);
व्योम usb_मुक्त_coherent(काष्ठा usb_device *dev, माप_प्रकार size,
	व्योम *addr, dma_addr_t dma);

#अगर 0
काष्ठा urb *usb_buffer_map(काष्ठा urb *urb);
व्योम usb_buffer_dmasync(काष्ठा urb *urb);
व्योम usb_buffer_unmap(काष्ठा urb *urb);
#पूर्ण_अगर

काष्ठा scatterlist;
पूर्णांक usb_buffer_map_sg(स्थिर काष्ठा usb_device *dev, पूर्णांक is_in,
		      काष्ठा scatterlist *sg, पूर्णांक nents);
#अगर 0
व्योम usb_buffer_dmasync_sg(स्थिर काष्ठा usb_device *dev, पूर्णांक is_in,
			   काष्ठा scatterlist *sg, पूर्णांक n_hw_ents);
#पूर्ण_अगर
व्योम usb_buffer_unmap_sg(स्थिर काष्ठा usb_device *dev, पूर्णांक is_in,
			 काष्ठा scatterlist *sg, पूर्णांक n_hw_ents);

/*-------------------------------------------------------------------*
 *                         SYNCHRONOUS CALL SUPPORT                  *
 *-------------------------------------------------------------------*/

बाह्य पूर्णांक usb_control_msg(काष्ठा usb_device *dev, अचिन्हित पूर्णांक pipe,
	__u8 request, __u8 requesttype, __u16 value, __u16 index,
	व्योम *data, __u16 size, पूर्णांक समयout);
बाह्य पूर्णांक usb_पूर्णांकerrupt_msg(काष्ठा usb_device *usb_dev, अचिन्हित पूर्णांक pipe,
	व्योम *data, पूर्णांक len, पूर्णांक *actual_length, पूर्णांक समयout);
बाह्य पूर्णांक usb_bulk_msg(काष्ठा usb_device *usb_dev, अचिन्हित पूर्णांक pipe,
	व्योम *data, पूर्णांक len, पूर्णांक *actual_length,
	पूर्णांक समयout);

/* wrappers around usb_control_msg() क्रम the most common standard requests */
पूर्णांक usb_control_msg_send(काष्ठा usb_device *dev, __u8 endpoपूर्णांक, __u8 request,
			 __u8 requesttype, __u16 value, __u16 index,
			 स्थिर व्योम *data, __u16 size, पूर्णांक समयout,
			 gfp_t memflags);
पूर्णांक usb_control_msg_recv(काष्ठा usb_device *dev, __u8 endpoपूर्णांक, __u8 request,
			 __u8 requesttype, __u16 value, __u16 index,
			 व्योम *data, __u16 size, पूर्णांक समयout,
			 gfp_t memflags);
बाह्य पूर्णांक usb_get_descriptor(काष्ठा usb_device *dev, अचिन्हित अक्षर desctype,
	अचिन्हित अक्षर descindex, व्योम *buf, पूर्णांक size);
बाह्य पूर्णांक usb_get_status(काष्ठा usb_device *dev,
	पूर्णांक recip, पूर्णांक type, पूर्णांक target, व्योम *data);

अटल अंतरभूत पूर्णांक usb_get_std_status(काष्ठा usb_device *dev,
	पूर्णांक recip, पूर्णांक target, व्योम *data)
अणु
	वापस usb_get_status(dev, recip, USB_STATUS_TYPE_STANDARD, target,
		data);
पूर्ण

अटल अंतरभूत पूर्णांक usb_get_pपंचांग_status(काष्ठा usb_device *dev, व्योम *data)
अणु
	वापस usb_get_status(dev, USB_RECIP_DEVICE, USB_STATUS_TYPE_PTM,
		0, data);
पूर्ण

बाह्य पूर्णांक usb_string(काष्ठा usb_device *dev, पूर्णांक index,
	अक्षर *buf, माप_प्रकार size);

/* wrappers that also update important state inside usbcore */
बाह्य पूर्णांक usb_clear_halt(काष्ठा usb_device *dev, पूर्णांक pipe);
बाह्य पूर्णांक usb_reset_configuration(काष्ठा usb_device *dev);
बाह्य पूर्णांक usb_set_पूर्णांकerface(काष्ठा usb_device *dev, पूर्णांक अगरnum, पूर्णांक alternate);
बाह्य व्योम usb_reset_endpoपूर्णांक(काष्ठा usb_device *dev, अचिन्हित पूर्णांक epaddr);

/* this request isn't really synchronous, but it beदीर्घs with the others */
बाह्य पूर्णांक usb_driver_set_configuration(काष्ठा usb_device *udev, पूर्णांक config);

/* choose and set configuration क्रम device */
बाह्य पूर्णांक usb_choose_configuration(काष्ठा usb_device *udev);
बाह्य पूर्णांक usb_set_configuration(काष्ठा usb_device *dev, पूर्णांक configuration);

/*
 * समयouts, in milliseconds, used क्रम sending/receiving control messages
 * they typically complete within a few frames (msec) after they're issued
 * USB identअगरies 5 second समयouts, maybe more in a few हालs, and a few
 * slow devices (like some MGE Ellipse UPSes) actually push that limit.
 */
#घोषणा USB_CTRL_GET_TIMEOUT	5000
#घोषणा USB_CTRL_SET_TIMEOUT	5000


/**
 * काष्ठा usb_sg_request - support क्रम scatter/gather I/O
 * @status: zero indicates success, अन्यथा negative त्रुटि_सं
 * @bytes: counts bytes transferred.
 *
 * These requests are initialized using usb_sg_init(), and then are used
 * as request handles passed to usb_sg_रुको() or usb_sg_cancel().  Most
 * members of the request object aren't क्रम driver access.
 *
 * The status and bytecount values are valid only after usb_sg_रुको()
 * वापसs.  If the status is zero, then the bytecount matches the total
 * from the request.
 *
 * After an error completion, drivers may need to clear a halt condition
 * on the endpoपूर्णांक.
 */
काष्ठा usb_sg_request अणु
	पूर्णांक			status;
	माप_प्रकार			bytes;

	/* निजी:
	 * members below are निजी to usbcore,
	 * and are not provided क्रम driver access!
	 */
	spinlock_t		lock;

	काष्ठा usb_device	*dev;
	पूर्णांक			pipe;

	पूर्णांक			entries;
	काष्ठा urb		**urbs;

	पूर्णांक			count;
	काष्ठा completion	complete;
पूर्ण;

पूर्णांक usb_sg_init(
	काष्ठा usb_sg_request	*io,
	काष्ठा usb_device	*dev,
	अचिन्हित		pipe,
	अचिन्हित		period,
	काष्ठा scatterlist	*sg,
	पूर्णांक			nents,
	माप_प्रकार			length,
	gfp_t			mem_flags
);
व्योम usb_sg_cancel(काष्ठा usb_sg_request *io);
व्योम usb_sg_रुको(काष्ठा usb_sg_request *io);


/* ----------------------------------------------------------------------- */

/*
 * For various legacy reasons, Linux has a small cookie that's paired with
 * a काष्ठा usb_device to identअगरy an endpoपूर्णांक queue.  Queue अक्षरacteristics
 * are defined by the endpoपूर्णांक's descriptor.  This cookie is called a "pipe",
 * an अचिन्हित पूर्णांक encoded as:
 *
 *  - direction:	bit 7		(0 = Host-to-Device [Out],
 *					 1 = Device-to-Host [In] ...
 *					like endpoपूर्णांक bEndpoपूर्णांकAddress)
 *  - device address:	bits 8-14       ... bit positions known to uhci-hcd
 *  - endpoपूर्णांक:		bits 15-18      ... bit positions known to uhci-hcd
 *  - pipe type:	bits 30-31	(00 = isochronous, 01 = पूर्णांकerrupt,
 *					 10 = control, 11 = bulk)
 *
 * Given the device address and endpoपूर्णांक descriptor, pipes are redundant.
 */

/* NOTE:  these are not the standard USB_ENDPOINT_XFER_* values!! */
/* (yet ... they're the values used by usbfs) */
#घोषणा PIPE_ISOCHRONOUS		0
#घोषणा PIPE_INTERRUPT			1
#घोषणा PIPE_CONTROL			2
#घोषणा PIPE_BULK			3

#घोषणा usb_pipein(pipe)	((pipe) & USB_सूची_IN)
#घोषणा usb_pipeout(pipe)	(!usb_pipein(pipe))

#घोषणा usb_pipedevice(pipe)	(((pipe) >> 8) & 0x7f)
#घोषणा usb_pipeendpoपूर्णांक(pipe)	(((pipe) >> 15) & 0xf)

#घोषणा usb_pipetype(pipe)	(((pipe) >> 30) & 3)
#घोषणा usb_pipeisoc(pipe)	(usb_pipetype((pipe)) == PIPE_ISOCHRONOUS)
#घोषणा usb_pipeपूर्णांक(pipe)	(usb_pipetype((pipe)) == PIPE_INTERRUPT)
#घोषणा usb_pipecontrol(pipe)	(usb_pipetype((pipe)) == PIPE_CONTROL)
#घोषणा usb_pipebulk(pipe)	(usb_pipetype((pipe)) == PIPE_BULK)

अटल अंतरभूत अचिन्हित पूर्णांक __create_pipe(काष्ठा usb_device *dev,
		अचिन्हित पूर्णांक endpoपूर्णांक)
अणु
	वापस (dev->devnum << 8) | (endpoपूर्णांक << 15);
पूर्ण

/* Create various pipes... */
#घोषणा usb_sndctrlpipe(dev, endpoपूर्णांक)	\
	((PIPE_CONTROL << 30) | __create_pipe(dev, endpoपूर्णांक))
#घोषणा usb_rcvctrlpipe(dev, endpoपूर्णांक)	\
	((PIPE_CONTROL << 30) | __create_pipe(dev, endpoपूर्णांक) | USB_सूची_IN)
#घोषणा usb_sndisocpipe(dev, endpoपूर्णांक)	\
	((PIPE_ISOCHRONOUS << 30) | __create_pipe(dev, endpoपूर्णांक))
#घोषणा usb_rcvisocpipe(dev, endpoपूर्णांक)	\
	((PIPE_ISOCHRONOUS << 30) | __create_pipe(dev, endpoपूर्णांक) | USB_सूची_IN)
#घोषणा usb_sndbulkpipe(dev, endpoपूर्णांक)	\
	((PIPE_BULK << 30) | __create_pipe(dev, endpoपूर्णांक))
#घोषणा usb_rcvbulkpipe(dev, endpoपूर्णांक)	\
	((PIPE_BULK << 30) | __create_pipe(dev, endpoपूर्णांक) | USB_सूची_IN)
#घोषणा usb_sndपूर्णांकpipe(dev, endpoपूर्णांक)	\
	((PIPE_INTERRUPT << 30) | __create_pipe(dev, endpoपूर्णांक))
#घोषणा usb_rcvपूर्णांकpipe(dev, endpoपूर्णांक)	\
	((PIPE_INTERRUPT << 30) | __create_pipe(dev, endpoपूर्णांक) | USB_सूची_IN)

अटल अंतरभूत काष्ठा usb_host_endpoपूर्णांक *
usb_pipe_endpoपूर्णांक(काष्ठा usb_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा usb_host_endpoपूर्णांक **eps;
	eps = usb_pipein(pipe) ? dev->ep_in : dev->ep_out;
	वापस eps[usb_pipeendpoपूर्णांक(pipe)];
पूर्ण

/*-------------------------------------------------------------------------*/

अटल अंतरभूत __u16
usb_maxpacket(काष्ठा usb_device *udev, पूर्णांक pipe, पूर्णांक is_out)
अणु
	काष्ठा usb_host_endpoपूर्णांक	*ep;
	अचिन्हित			epnum = usb_pipeendpoपूर्णांक(pipe);

	अगर (is_out) अणु
		WARN_ON(usb_pipein(pipe));
		ep = udev->ep_out[epnum];
	पूर्ण अन्यथा अणु
		WARN_ON(usb_pipeout(pipe));
		ep = udev->ep_in[epnum];
	पूर्ण
	अगर (!ep)
		वापस 0;

	/* NOTE:  only 0x07ff bits are क्रम packet size... */
	वापस usb_endpoपूर्णांक_maxp(&ep->desc);
पूर्ण

/* ----------------------------------------------------------------------- */

/* translate USB error codes to codes user space understands */
अटल अंतरभूत पूर्णांक usb_translate_errors(पूर्णांक error_code)
अणु
	चयन (error_code) अणु
	हाल 0:
	हाल -ENOMEM:
	हाल -ENODEV:
	हाल -EOPNOTSUPP:
		वापस error_code;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

/* Events from the usb core */
#घोषणा USB_DEVICE_ADD		0x0001
#घोषणा USB_DEVICE_REMOVE	0x0002
#घोषणा USB_BUS_ADD		0x0003
#घोषणा USB_BUS_REMOVE		0x0004
बाह्य व्योम usb_रेजिस्टर_notअगरy(काष्ठा notअगरier_block *nb);
बाह्य व्योम usb_unरेजिस्टर_notअगरy(काष्ठा notअगरier_block *nb);

/* debugfs stuff */
बाह्य काष्ठा dentry *usb_debug_root;

/* LED triggers */
क्रमागत usb_led_event अणु
	USB_LED_EVENT_HOST = 0,
	USB_LED_EVENT_GADGET = 1,
पूर्ण;

#अगर_घोषित CONFIG_USB_LED_TRIG
बाह्य व्योम usb_led_activity(क्रमागत usb_led_event ev);
#अन्यथा
अटल अंतरभूत व्योम usb_led_activity(क्रमागत usb_led_event ev) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर  /* __KERNEL__ */

#पूर्ण_अगर
