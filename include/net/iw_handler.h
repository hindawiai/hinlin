<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file define the new driver API क्रम Wireless Extensions
 *
 * Version :	8	16.3.07
 *
 * Authors :	Jean Tourrilhes - HPL - <jt@hpl.hp.com>
 * Copyright (c) 2001-2007 Jean Tourrilhes, All Rights Reserved.
 */

#अगर_अघोषित _IW_HANDLER_H
#घोषणा _IW_HANDLER_H

/************************** DOCUMENTATION **************************/
/*
 * Initial driver API (1996 -> onward) :
 * -----------------------------------
 * The initial API just sends the IOCTL request received from user space
 * to the driver (via the driver ioctl handler). The driver has to
 * handle all the rest...
 *
 * The initial API also defines a specअगरic handler in काष्ठा net_device
 * to handle wireless statistics.
 *
 * The initial APIs served us well and has proven a reasonably good design.
 * However, there is a few लघुcommings :
 *	o No events, everything is a request to the driver.
 *	o Large ioctl function in driver with gigantic चयन statement
 *	  (i.e. spaghetti code).
 *	o Driver has to mess up with copy_to/from_user, and in many हालs
 *	  करोes it unproperly. Common mistakes are :
 *		* buffer overflows (no checks or off by one checks)
 *		* call copy_to/from_user with irq disabled
 *	o The user space पूर्णांकerface is tied to ioctl because of the use
 *	  copy_to/from_user.
 *
 * New driver API (2002 -> onward) :
 * -------------------------------
 * The new driver API is just a bunch of standard functions (handlers),
 * each handling a specअगरic Wireless Extension. The driver just export
 * the list of handler it supports, and those will be called apropriately.
 *
 * I tried to keep the मुख्य advantage of the previous API (simplicity,
 * efficiency and light weight), and also I provide a good करोse of backward
 * compatibility (most काष्ठाures are the same, driver can use both API
 * simultaneously, ...).
 * Hopefully, I've also addressed the लघुcomming of the initial API.
 *
 * The advantage of the new API are :
 *	o Handling of Extensions in driver broken in small contained functions
 *	o Tighter checks of ioctl beक्रमe calling the driver
 *	o Flexible commit strategy (at least, the start of it)
 *	o Backward compatibility (can be mixed with old API)
 *	o Driver करोesn't have to worry about memory and user-space issues
 * The last poपूर्णांक is important क्रम the following reasons :
 *	o You are now able to call the new driver API from any API you
 *		want (including from within other parts of the kernel).
 *	o Common mistakes are aव्योमed (buffer overflow, user space copy
 *		with irq disabled and so on).
 *
 * The Drawback of the new API are :
 *	o bloat (especially kernel)
 *	o need to migrate existing drivers to new API
 * My initial testing shows that the new API adds around 3kB to the kernel
 * and save between 0 and 5kB from a typical driver.
 * Also, as all काष्ठाures and data types are unchanged, the migration is
 * quite straightक्रमward (but tedious).
 *
 * ---
 *
 * The new driver API is defined below in this file. User space should
 * not be aware of what's happening करोwn there...
 *
 * A new kernel wrapper is in अक्षरge of validating the IOCTLs and calling
 * the appropriate driver handler. This is implemented in :
 *	# net/core/wireless.c
 *
 * The driver export the list of handlers in :
 *	# include/linux/netdevice.h (one place)
 *
 * The new driver API is available क्रम WIRELESS_EXT >= 13.
 * Good luck with migration to the new API ;-)
 */

/* ---------------------- THE IMPLEMENTATION ---------------------- */
/*
 * Some of the choice I've made are pretty controversials. Defining an
 * API is very much weighting compromises. This goes पूर्णांकo some of the
 * details and the thinking behind the implementation.
 *
 * Implementation goals :
 * --------------------
 * The implementation goals were as follow :
 *	o Obvious : you should not need a PhD to understand what's happening,
 *		the benefit is easier मुख्यtenance.
 *	o Flexible : it should accommodate a wide variety of driver
 *		implementations and be as flexible as the old API.
 *	o Lean : it should be efficient memory wise to minimise the impact
 *		on kernel footprपूर्णांक.
 *	o Transparent to user space : the large number of user space
 *		applications that use Wireless Extensions should not need
 *		any modअगरications.
 *
 * Array of functions versus Struct of functions
 * ---------------------------------------------
 * 1) Having an array of functions allow the kernel code to access the
 * handler in a single lookup, which is much more efficient (think hash
 * table here).
 * 2) The only drawback is that driver ग_लिखोr may put their handler in
 * the wrong slot. This is trivial to test (I set the frequency, the
 * bitrate changes). Once the handler is in the proper slot, it will be
 * there क्रमever, because the array is only extended at the end.
 * 3) Backward/क्रमward compatibility : adding new handler just require
 * extending the array, so you can put newer driver in older kernel
 * without having to patch the kernel code (and vice versa).
 *
 * All handler are of the same generic type
 * ----------------------------------------
 * That's a feature !!!
 * 1) Having a generic handler allow to have generic code, which is more
 * efficient. If each of the handler was inभागidually typed I would need
 * to add a big चयन in the kernel (== more bloat). This solution is
 * more scalable, adding new Wireless Extensions करोesn't add new code.
 * 2) You can use the same handler in dअगरferent slots of the array. For
 * hardware, it may be more efficient or logical to handle multiple
 * Wireless Extensions with a single function, and the API allow you to
 * करो that. (An example would be a single record on the card to control
 * both bitrate and frequency, the handler would पढ़ो the old record,
 * modअगरy it according to info->cmd and reग_लिखो it).
 *
 * Functions prototype uses जोड़ iwreq_data
 * -----------------------------------------
 * Some would have preferred functions defined this way :
 *	अटल पूर्णांक mydriver_ioctl_setrate(काष्ठा net_device *dev, 
 *					  दीर्घ rate, पूर्णांक स्वतः)
 * 1) The kernel code करोesn't "validate" the content of iwreq_data, and
 * can't करो it (dअगरferent hardware may have dअगरferent notion of what a
 * valid frequency is), so we करोn't pretend that we करो it.
 * 2) The above क्रमm is not extendable. If I want to add a flag (क्रम
 * example to distinguish setting max rate and basic rate), I would
 * अवरोध the prototype. Using iwreq_data is more flexible.
 * 3) Also, the above क्रमm is not generic (see above).
 * 4) I करोn't expect driver developper using the wrong field of the
 * जोड़ (Doh !), so अटल typechecking करोesn't add much value.
 * 5) Lastly, you can skip the जोड़ by करोing :
 *	अटल पूर्णांक mydriver_ioctl_setrate(काष्ठा net_device *dev,
 *					  काष्ठा iw_request_info *info,
 *					  काष्ठा iw_param *rrq,
 *					  अक्षर *extra)
 * And then adding the handler in the array like this :
 *        (iw_handler) mydriver_ioctl_setrate,             // SIOCSIWRATE
 *
 * Using functions and not a registry
 * ----------------------------------
 * Another implementation option would have been क्रम every instance to
 * define a registry (a काष्ठा containing all the Wireless Extensions)
 * and only have a function to commit the registry to the hardware.
 * 1) This approach can be emulated by the current code, but not
 * vice versa.
 * 2) Some drivers करोn't keep any configuration in the driver, क्रम them
 * adding such a registry would be a signअगरicant bloat.
 * 3) The code to translate from Wireless Extension to native क्रमmat is
 * needed anyway, so it would not reduce signअगरicantely the amount of code.
 * 4) The current approach only selectively translate Wireless Extensions
 * to native क्रमmat and only selectively set, whereas the registry approach
 * would require to translate all WE and set all parameters क्रम any single
 * change.
 * 5) For many Wireless Extensions, the GET operation वापस the current
 * dynamic value, not the value that was set.
 *
 * This header is <net/iw_handler.h>
 * ---------------------------------
 * 1) This header is kernel space only and should not be exported to
 * user space. Headers in "include/linux/" are exported, headers in
 * "include/net/" are not.
 *
 * Mixed 32/64 bit issues
 * ----------------------
 * The Wireless Extensions are deचिन्हित to be 64 bit clean, by using only
 * datatypes with explicit storage size.
 * There are some issues related to kernel and user space using dअगरferent
 * memory model, and in particular 64bit kernel with 32bit user space.
 * The problem is related to काष्ठा iw_poपूर्णांक, that contains a poपूर्णांकer
 * that *may* need to be translated.
 * This is quite messy. The new API करोesn't solve this problem (it can't),
 * but is a step in the right direction :
 * 1) Meta data about each ioctl is easily available, so we know what type
 * of translation is needed.
 * 2) The move of data between kernel and user space is only करोne in a single
 * place in the kernel, so adding specअगरic hooks in there is possible.
 * 3) In the दीर्घ term, it allows to move away from using ioctl as the
 * user space API.
 *
 * So many comments and so few code
 * --------------------------------
 * That's a feature. Comments won't bloat the resulting kernel binary.
 */

/***************************** INCLUDES *****************************/

#समावेश <linux/wireless.h>		/* IOCTL user space API */
#समावेश <linux/अगर_ether.h>

/***************************** VERSION *****************************/
/*
 * This स्थिरant is used to know which version of the driver API is
 * available. Hopefully, this will be pretty stable and no changes
 * will be needed...
 * I just plan to increment with each new version.
 */
#घोषणा IW_HANDLER_VERSION	8

/*
 * Changes :
 *
 * V2 to V3
 * --------
 *	- Move event definition in <linux/wireless.h>
 *	- Add Wireless Event support :
 *		o wireless_send_event() prototype
 *		o iwe_stream_add_event/poपूर्णांक() अंतरभूत functions
 * V3 to V4
 * --------
 *	- Reshuffle IW_HEADER_TYPE_XXX to map IW_PRIV_TYPE_XXX changes
 *
 * V4 to V5
 * --------
 *	- Add new spy support : काष्ठा iw_spy_data & prototypes
 *
 * V5 to V6
 * --------
 *	- Change the way we get to spy_data method क्रम added safety
 *	- Remove spy #अगर_घोषित, they are always on -> cleaner code
 *	- Add IW_DESCR_FLAG_NOMAX flag क्रम very large requests
 *	- Start migrating get_wireless_stats to काष्ठा iw_handler_def
 *
 * V6 to V7
 * --------
 *	- Add काष्ठा ieee80211_device poपूर्णांकer in काष्ठा iw_खुला_data
 *	- Remove (काष्ठा iw_poपूर्णांक *)->poपूर्णांकer from events and streams
 *	- Remove spy_offset from काष्ठा iw_handler_def
 *	- Add "check" version of event macros क्रम ieee802.11 stack
 *
 * V7 to V8
 * ----------
 *	- Prevent leaking of kernel space in stream on 64 bits.
 */

/**************************** CONSTANTS ****************************/

/* Enhanced spy support available */
#घोषणा IW_WIRELESS_SPY
#घोषणा IW_WIRELESS_THRSPY

/* Special error message क्रम the driver to indicate that we
 * should करो a commit after वापस from the iw_handler */
#घोषणा EIWCOMMIT	EINPROGRESS

/* Flags available in काष्ठा iw_request_info */
#घोषणा IW_REQUEST_FLAG_COMPAT	0x0001	/* Compat ioctl call */

/* Type of headers we know about (basically जोड़ iwreq_data) */
#घोषणा IW_HEADER_TYPE_शून्य	0	/* Not available */
#घोषणा IW_HEADER_TYPE_CHAR	2	/* अक्षर [IFNAMSIZ] */
#घोषणा IW_HEADER_TYPE_UINT	4	/* __u32 */
#घोषणा IW_HEADER_TYPE_FREQ	5	/* काष्ठा iw_freq */
#घोषणा IW_HEADER_TYPE_ADDR	6	/* काष्ठा sockaddr */
#घोषणा IW_HEADER_TYPE_POINT	8	/* काष्ठा iw_poपूर्णांक */
#घोषणा IW_HEADER_TYPE_PARAM	9	/* काष्ठा iw_param */
#घोषणा IW_HEADER_TYPE_QUAL	10	/* काष्ठा iw_quality */

/* Handling flags */
/* Most are not implemented. I just use them as a reminder of some
 * cool features we might need one day ;-) */
#घोषणा IW_DESCR_FLAG_NONE	0x0000	/* Obvious */
/* Wrapper level flags */
#घोषणा IW_DESCR_FLAG_DUMP	0x0001	/* Not part of the dump command */
#घोषणा IW_DESCR_FLAG_EVENT	0x0002	/* Generate an event on SET */
#घोषणा IW_DESCR_FLAG_RESTRICT	0x0004	/* GET : request is ROOT only */
				/* SET : Omit payload from generated iwevent */
#घोषणा IW_DESCR_FLAG_NOMAX	0x0008	/* GET : no limit on request size */
/* Driver level flags */
#घोषणा IW_DESCR_FLAG_WAIT	0x0100	/* Wait क्रम driver event */

/****************************** TYPES ******************************/

/* ----------------------- WIRELESS HANDLER ----------------------- */
/*
 * A wireless handler is just a standard function, that looks like the
 * ioctl handler.
 * We also define there how a handler list look like... As the Wireless
 * Extension space is quite dense, we use a simple array, which is faster
 * (that's the perfect hash table ;-).
 */

/*
 * Meta data about the request passed to the iw_handler.
 * Most handlers can safely ignore what's in there.
 * The 'cmd' field might come handy अगर you want to use the same handler
 * क्रम multiple command...
 * This काष्ठा is also my दीर्घ term insurance. I can add new fields here
 * without अवरोधing the prototype of iw_handler...
 */
काष्ठा iw_request_info अणु
	__u16		cmd;		/* Wireless Extension command */
	__u16		flags;		/* More to come ;-) */
पूर्ण;

काष्ठा net_device;

/*
 * This is how a function handling a Wireless Extension should look
 * like (both get and set, standard and निजी).
 */
प्रकार पूर्णांक (*iw_handler)(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra);

/*
 * This define all the handler that the driver export.
 * As you need only one per driver type, please use a अटल स्थिर
 * shared by all driver instances... Same क्रम the members...
 * This will be linked from net_device in <linux/netdevice.h>
 */
काष्ठा iw_handler_def अणु

	/* Array of handlers क्रम standard ioctls
	 * We will call dev->wireless_handlers->standard[ioctl - SIOCIWFIRST]
	 */
	स्थिर iw_handler *	standard;
	/* Number of handlers defined (more precisely, index of the
	 * last defined handler + 1) */
	__u16			num_standard;

#अगर_घोषित CONFIG_WEXT_PRIV
	__u16			num_निजी;
	/* Number of निजी arg description */
	__u16			num_निजी_args;
	/* Array of handlers क्रम निजी ioctls
	 * Will call dev->wireless_handlers->निजी[ioctl - SIOCIWFIRSTPRIV]
	 */
	स्थिर iw_handler *	निजी;

	/* Arguments of निजी handler. This one is just a list, so you
	 * can put it in any order you want and should not leave holes...
	 * We will स्वतःmatically export that to user space... */
	स्थिर काष्ठा iw_priv_args *	निजी_args;
#पूर्ण_अगर

	/* New location of get_wireless_stats, to de-bloat काष्ठा net_device.
	 * The old poपूर्णांकer in काष्ठा net_device will be gradually phased
	 * out, and drivers are encouraged to use this one... */
	काष्ठा iw_statistics*	(*get_wireless_stats)(काष्ठा net_device *dev);
पूर्ण;

/* ---------------------- IOCTL DESCRIPTION ---------------------- */
/*
 * One of the मुख्य goal of the new पूर्णांकerface is to deal entirely with
 * user space/kernel space memory move.
 * For that, we need to know :
 *	o अगर iwreq is a poपूर्णांकer or contain the full data
 *	o what is the size of the data to copy
 *
 * For निजी IOCTLs, we use the same rules as used by iwpriv and
 * defined in काष्ठा iw_priv_args.
 *
 * For standard IOCTLs, things are quite dअगरferent and we need to
 * use the काष्ठाures below. Actually, this काष्ठा is also more
 * efficient, but that's another story...
 */

/*
 * Describe how a standard IOCTL looks like.
 */
काष्ठा iw_ioctl_description अणु
	__u8	header_type;		/* शून्य, iw_poपूर्णांक or other */
	__u8	token_type;		/* Future */
	__u16	token_size;		/* Granularity of payload */
	__u16	min_tokens;		/* Min acceptable token number */
	__u16	max_tokens;		/* Max acceptable token number */
	__u32	flags;			/* Special handling of the request */
पूर्ण;

/* Need to think of लघु header translation table. Later. */

/* --------------------- ENHANCED SPY SUPPORT --------------------- */
/*
 * In the old days, the driver was handling spy support all by itself.
 * Now, the driver can delegate this task to Wireless Extensions.
 * It needs to include this काष्ठा in its निजी part and use the
 * standard spy iw_handler.
 */

/*
 * Instance specअगरic spy data, i.e. addresses spied and quality क्रम them.
 */
काष्ठा iw_spy_data अणु
	/* --- Standard spy support --- */
	पूर्णांक			spy_number;
	u_अक्षर			spy_address[IW_MAX_SPY][ETH_ALEN];
	काष्ठा iw_quality	spy_stat[IW_MAX_SPY];
	/* --- Enhanced spy support (event) */
	काष्ठा iw_quality	spy_thr_low;	/* Low threshold */
	काष्ठा iw_quality	spy_thr_high;	/* High threshold */
	u_अक्षर			spy_thr_under[IW_MAX_SPY];
पूर्ण;

/* --------------------- DEVICE WIRELESS DATA --------------------- */
/*
 * This is all the wireless data specअगरic to a device instance that
 * is managed by the core of Wireless Extensions or the 802.11 layer.
 * We only keep poपूर्णांकer to those काष्ठाures, so that a driver is मुक्त
 * to share them between instances.
 * This काष्ठाure should be initialised beक्रमe रेजिस्टरing the device.
 * Access to this data follow the same rules as any other काष्ठा net_device
 * data (i.e. valid as दीर्घ as काष्ठा net_device exist, same locking rules).
 */
/* Forward declaration */
काष्ठा libipw_device;
/* The काष्ठा */
काष्ठा iw_खुला_data अणु
	/* Driver enhanced spy support */
	काष्ठा iw_spy_data *		spy_data;
	/* Legacy काष्ठाure managed by the ipw2x00-specअगरic IEEE 802.11 layer */
	काष्ठा libipw_device *		libipw;
पूर्ण;

/**************************** PROTOTYPES ****************************/
/*
 * Functions part of the Wireless Extensions (defined in net/core/wireless.c).
 * Those may be called only within the kernel.
 */

/* First : function strictly used inside the kernel */

/* Handle /proc/net/wireless, called in net/code/dev.c */
पूर्णांक dev_get_wireless_info(अक्षर *buffer, अक्षर **start, off_t offset, पूर्णांक length);

/* Second : functions that may be called by driver modules */

/* Send a single event to user space */
व्योम wireless_send_event(काष्ठा net_device *dev, अचिन्हित पूर्णांक cmd,
			 जोड़ iwreq_data *wrqu, स्थिर अक्षर *extra);
#अगर_घोषित CONFIG_WEXT_CORE
/* flush all previous wext events - अगर work is करोne from netdev notअगरiers */
व्योम wireless_nlevent_flush(व्योम);
#अन्यथा
अटल अंतरभूत व्योम wireless_nlevent_flush(व्योम) अणुपूर्ण
#पूर्ण_अगर

/* We may need a function to send a stream of events to user space.
 * More on that later... */

/* Standard handler क्रम SIOCSIWSPY */
पूर्णांक iw_handler_set_spy(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *extra);
/* Standard handler क्रम SIOCGIWSPY */
पूर्णांक iw_handler_get_spy(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *extra);
/* Standard handler क्रम SIOCSIWTHRSPY */
पूर्णांक iw_handler_set_thrspy(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra);
/* Standard handler क्रम SIOCGIWTHRSPY */
पूर्णांक iw_handler_get_thrspy(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra);
/* Driver call to update spy records */
व्योम wireless_spy_update(काष्ठा net_device *dev, अचिन्हित अक्षर *address,
			 काष्ठा iw_quality *wstats);

/************************* INLINE FUNTIONS *************************/
/*
 * Function that are so simple that it's more efficient inlining them
 */

अटल अंतरभूत पूर्णांक iwe_stream_lcp_len(काष्ठा iw_request_info *info)
अणु
#अगर_घोषित CONFIG_COMPAT
	अगर (info->flags & IW_REQUEST_FLAG_COMPAT)
		वापस IW_EV_COMPAT_LCP_LEN;
#पूर्ण_अगर
	वापस IW_EV_LCP_LEN;
पूर्ण

अटल अंतरभूत पूर्णांक iwe_stream_poपूर्णांक_len(काष्ठा iw_request_info *info)
अणु
#अगर_घोषित CONFIG_COMPAT
	अगर (info->flags & IW_REQUEST_FLAG_COMPAT)
		वापस IW_EV_COMPAT_POINT_LEN;
#पूर्ण_अगर
	वापस IW_EV_POINT_LEN;
पूर्ण

अटल अंतरभूत पूर्णांक iwe_stream_event_len_adjust(काष्ठा iw_request_info *info,
					      पूर्णांक event_len)
अणु
#अगर_घोषित CONFIG_COMPAT
	अगर (info->flags & IW_REQUEST_FLAG_COMPAT) अणु
		event_len -= IW_EV_LCP_LEN;
		event_len += IW_EV_COMPAT_LCP_LEN;
	पूर्ण
#पूर्ण_अगर

	वापस event_len;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wrapper to add an Wireless Event to a stream of events.
 */
अक्षर *iwe_stream_add_event(काष्ठा iw_request_info *info, अक्षर *stream,
			   अक्षर *ends, काष्ठा iw_event *iwe, पूर्णांक event_len);

अटल अंतरभूत अक्षर *
iwe_stream_add_event_check(काष्ठा iw_request_info *info, अक्षर *stream,
			   अक्षर *ends, काष्ठा iw_event *iwe, पूर्णांक event_len)
अणु
	अक्षर *res = iwe_stream_add_event(info, stream, ends, iwe, event_len);

	अगर (res == stream)
		वापस ERR_PTR(-E2BIG);
	वापस res;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wrapper to add an लघु Wireless Event containing a poपूर्णांकer to a
 * stream of events.
 */
अक्षर *iwe_stream_add_poपूर्णांक(काष्ठा iw_request_info *info, अक्षर *stream,
			   अक्षर *ends, काष्ठा iw_event *iwe, अक्षर *extra);

अटल अंतरभूत अक्षर *
iwe_stream_add_poपूर्णांक_check(काष्ठा iw_request_info *info, अक्षर *stream,
			   अक्षर *ends, काष्ठा iw_event *iwe, अक्षर *extra)
अणु
	अक्षर *res = iwe_stream_add_poपूर्णांक(info, stream, ends, iwe, extra);

	अगर (res == stream)
		वापस ERR_PTR(-E2BIG);
	वापस res;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wrapper to add a value to a Wireless Event in a stream of events.
 * Be careful, this one is tricky to use properly :
 * At the first run, you need to have (value = event + IW_EV_LCP_LEN).
 */
अक्षर *iwe_stream_add_value(काष्ठा iw_request_info *info, अक्षर *event,
			   अक्षर *value, अक्षर *ends, काष्ठा iw_event *iwe,
			   पूर्णांक event_len);

#पूर्ण_अगर	/* _IW_HANDLER_H */
