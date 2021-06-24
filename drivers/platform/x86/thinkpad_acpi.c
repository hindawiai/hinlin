<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  thinkpad_acpi.c - ThinkPad ACPI Extras
 *
 *  Copyright (C) 2004-2005 Borislav Deianov <borislav@users.sf.net>
 *  Copyright (C) 2006-2009 Henrique de Moraes Holschuh <hmh@hmh.eng.br>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा TPACPI_VERSION "0.26"
#घोषणा TPACPI_SYSFS_VERSION 0x030000

/*
 *  Changelog:
 *  2007-10-20		changelog trimmed करोwn
 *
 *  2007-03-27  0.14	नामd to thinkpad_acpi and moved to
 *  			drivers/misc.
 *
 *  2006-11-22	0.13	new मुख्यtainer
 *  			changelog now lives in git commit history, and will
 *  			not be updated further in-file.
 *
 *  2005-03-17	0.11	support क्रम 600e, 770x
 *			    thanks to Jamie Lentin <lentinj@dial.pipex.com>
 *
 *  2005-01-16	0.9	use MODULE_VERSION
 *			    thanks to Henrik Brix Andersen <brix@gentoo.org>
 *			fix parameter passing on module loading
 *			    thanks to Rusty Russell <rusty@rustcorp.com.au>
 *			    thanks to Jim Radक्रमd <radक्रमd@blackbean.org>
 *  2004-11-08	0.8	fix init error हाल, करोn't वापस from a macro
 *			    thanks to Chris Wright <chrisw@osdl.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/nvram.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/backlight.h>
#समावेश <linux/bitops.h>
#समावेश <linux/fb.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/input.h>
#समावेश <linux/leds.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/dmi.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/platक्रमm_profile.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>
#समावेश <linux/uaccess.h>
#समावेश <acpi/battery.h>
#समावेश <acpi/video.h>

/* ThinkPad CMOS commands */
#घोषणा TP_CMOS_VOLUME_DOWN	0
#घोषणा TP_CMOS_VOLUME_UP	1
#घोषणा TP_CMOS_VOLUME_MUTE	2
#घोषणा TP_CMOS_BRIGHTNESS_UP	4
#घोषणा TP_CMOS_BRIGHTNESS_DOWN	5
#घोषणा TP_CMOS_THINKLIGHT_ON	12
#घोषणा TP_CMOS_THINKLIGHT_OFF	13

/* NVRAM Addresses */
क्रमागत tp_nvram_addr अणु
	TP_NVRAM_ADDR_HK2		= 0x57,
	TP_NVRAM_ADDR_THINKLIGHT	= 0x58,
	TP_NVRAM_ADDR_VIDEO		= 0x59,
	TP_NVRAM_ADDR_BRIGHTNESS	= 0x5e,
	TP_NVRAM_ADDR_MIXER		= 0x60,
पूर्ण;

/* NVRAM bit masks */
क्रमागत अणु
	TP_NVRAM_MASK_HKT_THINKPAD	= 0x08,
	TP_NVRAM_MASK_HKT_ZOOM		= 0x20,
	TP_NVRAM_MASK_HKT_DISPLAY	= 0x40,
	TP_NVRAM_MASK_HKT_HIBERNATE	= 0x80,
	TP_NVRAM_MASK_THINKLIGHT	= 0x10,
	TP_NVRAM_MASK_HKT_DISPEXPND	= 0x30,
	TP_NVRAM_MASK_HKT_BRIGHTNESS	= 0x20,
	TP_NVRAM_MASK_LEVEL_BRIGHTNESS	= 0x0f,
	TP_NVRAM_POS_LEVEL_BRIGHTNESS	= 0,
	TP_NVRAM_MASK_MUTE		= 0x40,
	TP_NVRAM_MASK_HKT_VOLUME	= 0x80,
	TP_NVRAM_MASK_LEVEL_VOLUME	= 0x0f,
	TP_NVRAM_POS_LEVEL_VOLUME	= 0,
पूर्ण;

/* Misc NVRAM-related */
क्रमागत अणु
	TP_NVRAM_LEVEL_VOLUME_MAX = 14,
पूर्ण;

/* ACPI HIDs */
#घोषणा TPACPI_ACPI_IBM_HKEY_HID	"IBM0068"
#घोषणा TPACPI_ACPI_LENOVO_HKEY_HID	"LEN0068"
#घोषणा TPACPI_ACPI_LENOVO_HKEY_V2_HID	"LEN0268"
#घोषणा TPACPI_ACPI_EC_HID		"PNP0C09"

/* Input IDs */
#घोषणा TPACPI_HKEY_INPUT_PRODUCT	0x5054 /* "TP" */
#घोषणा TPACPI_HKEY_INPUT_VERSION	0x4101

/* ACPI \WGSV commands */
क्रमागत अणु
	TP_ACPI_WGSV_GET_STATE		= 0x01, /* Get state inक्रमmation */
	TP_ACPI_WGSV_PWR_ON_ON_RESUME	= 0x02, /* Resume WWAN घातered on */
	TP_ACPI_WGSV_PWR_OFF_ON_RESUME	= 0x03,	/* Resume WWAN घातered off */
	TP_ACPI_WGSV_SAVE_STATE		= 0x04, /* Save state क्रम S4/S5 */
पूर्ण;

/* TP_ACPI_WGSV_GET_STATE bits */
क्रमागत अणु
	TP_ACPI_WGSV_STATE_WWANEXIST	= 0x0001, /* WWAN hw available */
	TP_ACPI_WGSV_STATE_WWANPWR	= 0x0002, /* WWAN radio enabled */
	TP_ACPI_WGSV_STATE_WWANPWRRES	= 0x0004, /* WWAN state at resume */
	TP_ACPI_WGSV_STATE_WWANBIOSOFF	= 0x0008, /* WWAN disabled in BIOS */
	TP_ACPI_WGSV_STATE_BLTHEXIST	= 0x0001, /* BLTH hw available */
	TP_ACPI_WGSV_STATE_BLTHPWR	= 0x0002, /* BLTH radio enabled */
	TP_ACPI_WGSV_STATE_BLTHPWRRES	= 0x0004, /* BLTH state at resume */
	TP_ACPI_WGSV_STATE_BLTHBIOSOFF	= 0x0008, /* BLTH disabled in BIOS */
	TP_ACPI_WGSV_STATE_UWBEXIST	= 0x0010, /* UWB hw available */
	TP_ACPI_WGSV_STATE_UWBPWR	= 0x0020, /* UWB radio enabled */
पूर्ण;

/* HKEY events */
क्रमागत tpacpi_hkey_event_t अणु
	/* Hotkey-related */
	TP_HKEY_EV_HOTKEY_BASE		= 0x1001, /* first hotkey (FN+F1) */
	TP_HKEY_EV_BRGHT_UP		= 0x1010, /* Brightness up */
	TP_HKEY_EV_BRGHT_DOWN		= 0x1011, /* Brightness करोwn */
	TP_HKEY_EV_KBD_LIGHT		= 0x1012, /* Thinklight/kbd backlight */
	TP_HKEY_EV_VOL_UP		= 0x1015, /* Volume up or unmute */
	TP_HKEY_EV_VOL_DOWN		= 0x1016, /* Volume करोwn or unmute */
	TP_HKEY_EV_VOL_MUTE		= 0x1017, /* Mixer output mute */

	/* Reasons क्रम waking up from S3/S4 */
	TP_HKEY_EV_WKUP_S3_UNDOCK	= 0x2304, /* unकरोck requested, S3 */
	TP_HKEY_EV_WKUP_S4_UNDOCK	= 0x2404, /* unकरोck requested, S4 */
	TP_HKEY_EV_WKUP_S3_BAYEJ	= 0x2305, /* bay ejection req, S3 */
	TP_HKEY_EV_WKUP_S4_BAYEJ	= 0x2405, /* bay ejection req, S4 */
	TP_HKEY_EV_WKUP_S3_BATLOW	= 0x2313, /* battery empty, S3 */
	TP_HKEY_EV_WKUP_S4_BATLOW	= 0x2413, /* battery empty, S4 */

	/* Auto-sleep after eject request */
	TP_HKEY_EV_BAYEJ_ACK		= 0x3003, /* bay ejection complete */
	TP_HKEY_EV_UNDOCK_ACK		= 0x4003, /* unकरोck complete */

	/* Misc bay events */
	TP_HKEY_EV_OPTDRV_EJ		= 0x3006, /* opt. drive tray ejected */
	TP_HKEY_EV_HOTPLUG_DOCK		= 0x4010, /* करोcked पूर्णांकo hotplug करोck
						     or port replicator */
	TP_HKEY_EV_HOTPLUG_UNDOCK	= 0x4011, /* unकरोcked from hotplug
						     करोck or port replicator */
	/*
	 * Thinkpad X1 Tablet series devices emit 0x4012 and 0x4013
	 * when keyboard cover is attached, detached or folded onto the back
	 */
	TP_HKEY_EV_KBD_COVER_ATTACH	= 0x4012, /* keyboard cover attached */
	TP_HKEY_EV_KBD_COVER_DETACH	= 0x4013, /* keyboard cover detached or folded back */

	/* User-पूर्णांकerface events */
	TP_HKEY_EV_LID_CLOSE		= 0x5001, /* laptop lid बंदd */
	TP_HKEY_EV_LID_OPEN		= 0x5002, /* laptop lid खोलोed */
	TP_HKEY_EV_TABLET_TABLET	= 0x5009, /* tablet swivel up */
	TP_HKEY_EV_TABLET_NOTEBOOK	= 0x500a, /* tablet swivel करोwn */
	TP_HKEY_EV_TABLET_CHANGED	= 0x60c0, /* X1 Yoga (2016):
						   * enter/leave tablet mode
						   */
	TP_HKEY_EV_PEN_INSERTED		= 0x500b, /* tablet pen inserted */
	TP_HKEY_EV_PEN_REMOVED		= 0x500c, /* tablet pen हटाओd */
	TP_HKEY_EV_BRGHT_CHANGED	= 0x5010, /* backlight control event */

	/* Key-related user-पूर्णांकerface events */
	TP_HKEY_EV_KEY_NUMLOCK		= 0x6000, /* NumLock key pressed */
	TP_HKEY_EV_KEY_FN		= 0x6005, /* Fn key pressed? E420 */
	TP_HKEY_EV_KEY_FN_ESC           = 0x6060, /* Fn+Esc key pressed X240 */

	/* Thermal events */
	TP_HKEY_EV_ALARM_BAT_HOT	= 0x6011, /* battery too hot */
	TP_HKEY_EV_ALARM_BAT_XHOT	= 0x6012, /* battery critically hot */
	TP_HKEY_EV_ALARM_SENSOR_HOT	= 0x6021, /* sensor too hot */
	TP_HKEY_EV_ALARM_SENSOR_XHOT	= 0x6022, /* sensor critically hot */
	TP_HKEY_EV_THM_TABLE_CHANGED	= 0x6030, /* winकरोws; thermal table changed */
	TP_HKEY_EV_THM_CSM_COMPLETED    = 0x6032, /* winकरोws; thermal control set
						   * command completed. Related to
						   * AML DYTC */
	TP_HKEY_EV_THM_TRANSFM_CHANGED  = 0x60F0, /* winकरोws; thermal transक्रमmation
						   * changed. Related to AML GMTS */

	/* AC-related events */
	TP_HKEY_EV_AC_CHANGED		= 0x6040, /* AC status changed */

	/* Further user-पूर्णांकerface events */
	TP_HKEY_EV_PALM_DETECTED	= 0x60b0, /* palm hoveres keyboard */
	TP_HKEY_EV_PALM_UNDETECTED	= 0x60b1, /* palm हटाओd */

	/* Misc */
	TP_HKEY_EV_RFKILL_CHANGED	= 0x7000, /* rfसमाप्त चयन changed */
पूर्ण;

/****************************************************************************
 * Main driver
 */

#घोषणा TPACPI_NAME "thinkpad"
#घोषणा TPACPI_DESC "ThinkPad ACPI Extras"
#घोषणा TPACPI_खाता TPACPI_NAME "_acpi"
#घोषणा TPACPI_URL "http://ibm-acpi.sf.net/"
#घोषणा TPACPI_MAIL "ibm-acpi-devel@lists.sourceforge.net"

#घोषणा TPACPI_PROC_सूची "ibm"
#घोषणा TPACPI_ACPI_EVENT_PREFIX "ibm"
#घोषणा TPACPI_DRVR_NAME TPACPI_खाता
#घोषणा TPACPI_DRVR_SHORTNAME "tpacpi"
#घोषणा TPACPI_HWMON_DRVR_NAME TPACPI_NAME "_hwmon"

#घोषणा TPACPI_NVRAM_KTHREAD_NAME "ktpacpi_nvramd"
#घोषणा TPACPI_WORKQUEUE_NAME "ktpacpid"

#घोषणा TPACPI_MAX_ACPI_ARGS 3

/* Debugging prपूर्णांकk groups */
#घोषणा TPACPI_DBG_ALL		0xffff
#घोषणा TPACPI_DBG_DISCLOSETASK	0x8000
#घोषणा TPACPI_DBG_INIT		0x0001
#घोषणा TPACPI_DBG_EXIT		0x0002
#घोषणा TPACPI_DBG_RFKILL	0x0004
#घोषणा TPACPI_DBG_HKEY		0x0008
#घोषणा TPACPI_DBG_FAN		0x0010
#घोषणा TPACPI_DBG_BRGHT	0x0020
#घोषणा TPACPI_DBG_MIXER	0x0040

#घोषणा onoff(status, bit) ((status) & (1 << (bit)) ? "on" : "off")
#घोषणा enabled(status, bit) ((status) & (1 << (bit)) ? "enabled" : "disabled")
#घोषणा म_मापcmp(a, b) (म_भेदन((a), (b), म_माप(b)))


/****************************************************************************
 * Driver-wide काष्ठाs and misc. variables
 */

काष्ठा ibm_काष्ठा;

काष्ठा tp_acpi_drv_काष्ठा अणु
	स्थिर काष्ठा acpi_device_id *hid;
	काष्ठा acpi_driver *driver;

	व्योम (*notअगरy) (काष्ठा ibm_काष्ठा *, u32);
	acpi_handle *handle;
	u32 type;
	काष्ठा acpi_device *device;
पूर्ण;

काष्ठा ibm_काष्ठा अणु
	अक्षर *name;

	पूर्णांक (*पढ़ो) (काष्ठा seq_file *);
	पूर्णांक (*ग_लिखो) (अक्षर *);
	व्योम (*निकास) (व्योम);
	व्योम (*resume) (व्योम);
	व्योम (*suspend) (व्योम);
	व्योम (*shutकरोwn) (व्योम);

	काष्ठा list_head all_drivers;

	काष्ठा tp_acpi_drv_काष्ठा *acpi;

	काष्ठा अणु
		u8 acpi_driver_रेजिस्टरed:1;
		u8 acpi_notअगरy_installed:1;
		u8 proc_created:1;
		u8 init_called:1;
		u8 experimental:1;
	पूर्ण flags;
पूर्ण;

काष्ठा ibm_init_काष्ठा अणु
	अक्षर param[32];

	पूर्णांक (*init) (काष्ठा ibm_init_काष्ठा *);
	umode_t base_procfs_mode;
	काष्ठा ibm_काष्ठा *data;
पूर्ण;

अटल काष्ठा अणु
	u32 bluetooth:1;
	u32 hotkey:1;
	u32 hotkey_mask:1;
	u32 hotkey_wlsw:1;
	क्रमागत अणु
		TP_HOTKEY_TABLET_NONE = 0,
		TP_HOTKEY_TABLET_USES_MHKG,
		TP_HOTKEY_TABLET_USES_GMMS,
	पूर्ण hotkey_tablet;
	u32 kbdlight:1;
	u32 light:1;
	u32 light_status:1;
	u32 bright_acpimode:1;
	u32 bright_unkfw:1;
	u32 wan:1;
	u32 uwb:1;
	u32 fan_ctrl_status_undef:1;
	u32 second_fan:1;
	u32 second_fan_ctl:1;
	u32 beep_needs_two_args:1;
	u32 mixer_no_level_control:1;
	u32 battery_क्रमce_primary:1;
	u32 input_device_रेजिस्टरed:1;
	u32 platक्रमm_drv_रेजिस्टरed:1;
	u32 platक्रमm_drv_attrs_रेजिस्टरed:1;
	u32 sensors_pdrv_रेजिस्टरed:1;
	u32 sensors_pdrv_attrs_रेजिस्टरed:1;
	u32 sensors_pdev_attrs_रेजिस्टरed:1;
	u32 hotkey_poll_active:1;
	u32 has_adaptive_kbd:1;
पूर्ण tp_features;

अटल काष्ठा अणु
	u16 hotkey_mask_ff:1;
	u16 volume_ctrl_क्रमbidden:1;
पूर्ण tp_warned;

काष्ठा thinkpad_id_data अणु
	अचिन्हित पूर्णांक venकरोr;	/* ThinkPad venकरोr:
				 * PCI_VENDOR_ID_IBM/PCI_VENDOR_ID_LENOVO */

	अक्षर *bios_version_str;	/* Something like 1ZET51WW (1.03z) */
	अक्षर *ec_version_str;	/* Something like 1ZHT51WW-1.04a */

	u32 bios_model;		/* 1Y = 0x3159, 0 = unknown */
	u32 ec_model;
	u16 bios_release;	/* 1ZETK1WW = 0x4b31, 0 = unknown */
	u16 ec_release;

	अक्षर *model_str;	/* ThinkPad T43 */
	अक्षर *nummodel_str;	/* 9384A9C क्रम a 9384-A9C model */
पूर्ण;
अटल काष्ठा thinkpad_id_data thinkpad_id;

अटल क्रमागत अणु
	TPACPI_LIFE_INIT = 0,
	TPACPI_LIFE_RUNNING,
	TPACPI_LIFE_EXITING,
पूर्ण tpacpi_lअगरecycle;

अटल पूर्णांक experimental;
अटल u32 dbg_level;

अटल काष्ठा workqueue_काष्ठा *tpacpi_wq;

क्रमागत led_status_t अणु
	TPACPI_LED_OFF = 0,
	TPACPI_LED_ON,
	TPACPI_LED_BLINK,
पूर्ण;

/* tpacpi LED class */
काष्ठा tpacpi_led_classdev अणु
	काष्ठा led_classdev led_classdev;
	पूर्णांक led;
पूर्ण;

/* brightness level capabilities */
अटल अचिन्हित पूर्णांक bright_maxlvl;	/* 0 = unknown */

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
अटल पूर्णांक dbg_wlswemul;
अटल bool tpacpi_wlsw_emulstate;
अटल पूर्णांक dbg_bluetoothemul;
अटल bool tpacpi_bluetooth_emulstate;
अटल पूर्णांक dbg_wwanemul;
अटल bool tpacpi_wwan_emulstate;
अटल पूर्णांक dbg_uwbemul;
अटल bool tpacpi_uwb_emulstate;
#पूर्ण_अगर


/*************************************************************************
 *  Debugging helpers
 */

#घोषणा dbg_prपूर्णांकk(a_dbg_level, क्रमmat, arg...)				\
करो अणु									\
	अगर (dbg_level & (a_dbg_level))					\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " क्रमmat),		\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUG
#घोषणा vdbg_prपूर्णांकk dbg_prपूर्णांकk
अटल स्थिर अक्षर *str_supported(पूर्णांक is_supported);
#अन्यथा
अटल अंतरभूत स्थिर अक्षर *str_supported(पूर्णांक is_supported) अणु वापस ""; पूर्ण
#घोषणा vdbg_prपूर्णांकk(a_dbg_level, क्रमmat, arg...)	\
	करो अणु अगर (0) no_prपूर्णांकk(क्रमmat, ##arg); पूर्ण जबतक (0)
#पूर्ण_अगर

अटल व्योम tpacpi_log_usertask(स्थिर अक्षर * स्थिर what)
अणु
	prपूर्णांकk(KERN_DEBUG pr_fmt("%s: access by process with PID %d\n"),
	       what, task_tgid_vnr(current));
पूर्ण

#घोषणा tpacpi_disबंद_usertask(what, क्रमmat, arg...)			\
करो अणु									\
	अगर (unlikely((dbg_level & TPACPI_DBG_DISCLOSETASK) &&		\
		     (tpacpi_lअगरecycle == TPACPI_LIFE_RUNNING))) अणु	\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: PID %d: " क्रमmat),	\
		       what, task_tgid_vnr(current), ## arg);		\
	पूर्ण								\
पूर्ण जबतक (0)

/*
 * Quirk handling helpers
 *
 * ThinkPad IDs and versions seen in the field so far are
 * two or three अक्षरacters from the set [0-9A-Z], i.e. base 36.
 *
 * We use values well outside that range as specials.
 */

#घोषणा TPACPI_MATCH_ANY		0xffffffffU
#घोषणा TPACPI_MATCH_ANY_VERSION	0xffffU
#घोषणा TPACPI_MATCH_UNKNOWN		0U

/* TPID('1', 'Y') == 0x3159 */
#घोषणा TPID(__c1, __c2)	(((__c1) << 8) | (__c2))
#घोषणा TPID3(__c1, __c2, __c3)	(((__c1) << 16) | ((__c2) << 8) | (__c3))
#घोषणा TPVER TPID

#घोषणा TPACPI_Q_IBM(__id1, __id2, __quirk)	\
	अणु .venकरोr = PCI_VENDOR_ID_IBM,		\
	  .bios = TPID(__id1, __id2),		\
	  .ec = TPACPI_MATCH_ANY,		\
	  .quirks = (__quirk) पूर्ण

#घोषणा TPACPI_Q_LNV(__id1, __id2, __quirk)	\
	अणु .venकरोr = PCI_VENDOR_ID_LENOVO,	\
	  .bios = TPID(__id1, __id2),		\
	  .ec = TPACPI_MATCH_ANY,		\
	  .quirks = (__quirk) पूर्ण

#घोषणा TPACPI_Q_LNV3(__id1, __id2, __id3, __quirk) \
	अणु .venकरोr = PCI_VENDOR_ID_LENOVO,	\
	  .bios = TPID3(__id1, __id2, __id3),	\
	  .ec = TPACPI_MATCH_ANY,		\
	  .quirks = (__quirk) पूर्ण

#घोषणा TPACPI_QEC_IBM(__id1, __id2, __quirk)	\
	अणु .venकरोr = PCI_VENDOR_ID_IBM,		\
	  .bios = TPACPI_MATCH_ANY,		\
	  .ec = TPID(__id1, __id2),		\
	  .quirks = (__quirk) पूर्ण

#घोषणा TPACPI_QEC_LNV(__id1, __id2, __quirk)	\
	अणु .venकरोr = PCI_VENDOR_ID_LENOVO,	\
	  .bios = TPACPI_MATCH_ANY,		\
	  .ec = TPID(__id1, __id2),		\
	  .quirks = (__quirk) पूर्ण

काष्ठा tpacpi_quirk अणु
	अचिन्हित पूर्णांक venकरोr;
	u32 bios;
	u32 ec;
	अचिन्हित दीर्घ quirks;
पूर्ण;

/**
 * tpacpi_check_quirks() - search BIOS/EC version on a list
 * @qlist:		array of &काष्ठा tpacpi_quirk
 * @qlist_size:		number of elements in @qlist
 *
 * Iterates over a quirks list until one is found that matches the
 * ThinkPad's venकरोr, BIOS and EC model.
 *
 * Returns 0 अगर nothing matches, otherwise वापसs the quirks field of
 * the matching &काष्ठा tpacpi_quirk entry.
 *
 * The match criteria is: venकरोr, ec and bios much match.
 */
अटल अचिन्हित दीर्घ __init tpacpi_check_quirks(
			स्थिर काष्ठा tpacpi_quirk *qlist,
			अचिन्हित पूर्णांक qlist_size)
अणु
	जबतक (qlist_size) अणु
		अगर ((qlist->venकरोr == thinkpad_id.venकरोr ||
				qlist->venकरोr == TPACPI_MATCH_ANY) &&
		    (qlist->bios == thinkpad_id.bios_model ||
				qlist->bios == TPACPI_MATCH_ANY) &&
		    (qlist->ec == thinkpad_id.ec_model ||
				qlist->ec == TPACPI_MATCH_ANY))
			वापस qlist->quirks;

		qlist_size--;
		qlist++;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत bool __pure __init tpacpi_is_lenovo(व्योम)
अणु
	वापस thinkpad_id.venकरोr == PCI_VENDOR_ID_LENOVO;
पूर्ण

अटल अंतरभूत bool __pure __init tpacpi_is_ibm(व्योम)
अणु
	वापस thinkpad_id.venकरोr == PCI_VENDOR_ID_IBM;
पूर्ण

/****************************************************************************
 ****************************************************************************
 *
 * ACPI Helpers and device model
 *
 ****************************************************************************
 ****************************************************************************/

/*************************************************************************
 * ACPI basic handles
 */

अटल acpi_handle root_handle;
अटल acpi_handle ec_handle;

#घोषणा TPACPI_HANDLE(object, parent, paths...)			\
	अटल acpi_handle  object##_handle;			\
	अटल स्थिर acpi_handle * स्थिर object##_parent __initस्थिर =	\
						&parent##_handle; \
	अटल अक्षर *object##_paths[] __initdata = अणु paths पूर्ण

TPACPI_HANDLE(ecrd, ec, "ECRD");	/* 570 */
TPACPI_HANDLE(ecwr, ec, "ECWR");	/* 570 */

TPACPI_HANDLE(cmos, root, "\\UCMS",	/* R50, R50e, R50p, R51, */
					/* T4x, X31, X40 */
	   "\\CMOS",		/* A3x, G4x, R32, T23, T30, X22-24, X30 */
	   "\\CMS",		/* R40, R40e */
	   );			/* all others */

TPACPI_HANDLE(hkey, ec, "\\_SB.HKEY",	/* 600e/x, 770e, 770x */
	   "^HKEY",		/* R30, R31 */
	   "HKEY",		/* all others */
	   );			/* 570 */

/*************************************************************************
 * ACPI helpers
 */

अटल पूर्णांक acpi_evalf(acpi_handle handle,
		      पूर्णांक *res, अक्षर *method, अक्षर *fmt, ...)
अणु
	अक्षर *fmt0 = fmt;
	काष्ठा acpi_object_list params;
	जोड़ acpi_object in_objs[TPACPI_MAX_ACPI_ARGS];
	काष्ठा acpi_buffer result, *resultp;
	जोड़ acpi_object out_obj;
	acpi_status status;
	बहु_सूची ap;
	अक्षर res_type;
	पूर्णांक success;
	पूर्णांक quiet;

	अगर (!*fmt) अणु
		pr_err("acpi_evalf() called with empty format\n");
		वापस 0;
	पूर्ण

	अगर (*fmt == 'q') अणु
		quiet = 1;
		fmt++;
	पूर्ण अन्यथा
		quiet = 0;

	res_type = *(fmt++);

	params.count = 0;
	params.poपूर्णांकer = &in_objs[0];

	बहु_शुरू(ap, fmt);
	जबतक (*fmt) अणु
		अक्षर c = *(fmt++);
		चयन (c) अणु
		हाल 'd':	/* पूर्णांक */
			in_objs[params.count].पूर्णांकeger.value = बहु_तर्क(ap, पूर्णांक);
			in_objs[params.count++].type = ACPI_TYPE_INTEGER;
			अवरोध;
			/* add more types as needed */
		शेष:
			pr_err("acpi_evalf() called with invalid format character '%c'\n",
			       c);
			बहु_पूर्ण(ap);
			वापस 0;
		पूर्ण
	पूर्ण
	बहु_पूर्ण(ap);

	अगर (res_type != 'v') अणु
		result.length = माप(out_obj);
		result.poपूर्णांकer = &out_obj;
		resultp = &result;
	पूर्ण अन्यथा
		resultp = शून्य;

	status = acpi_evaluate_object(handle, method, &params, resultp);

	चयन (res_type) अणु
	हाल 'd':		/* पूर्णांक */
		success = (status == AE_OK &&
			   out_obj.type == ACPI_TYPE_INTEGER);
		अगर (success && res)
			*res = out_obj.पूर्णांकeger.value;
		अवरोध;
	हाल 'v':		/* व्योम */
		success = status == AE_OK;
		अवरोध;
		/* add more types as needed */
	शेष:
		pr_err("acpi_evalf() called with invalid format character '%c'\n",
		       res_type);
		वापस 0;
	पूर्ण

	अगर (!success && !quiet)
		pr_err("acpi_evalf(%s, %s, ...) failed: %s\n",
		       method, fmt0, acpi_क्रमmat_exception(status));

	वापस success;
पूर्ण

अटल पूर्णांक acpi_ec_पढ़ो(पूर्णांक i, u8 *p)
अणु
	पूर्णांक v;

	अगर (ecrd_handle) अणु
		अगर (!acpi_evalf(ecrd_handle, &v, शून्य, "dd", i))
			वापस 0;
		*p = v;
	पूर्ण अन्यथा अणु
		अगर (ec_पढ़ो(i, p) < 0)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक acpi_ec_ग_लिखो(पूर्णांक i, u8 v)
अणु
	अगर (ecwr_handle) अणु
		अगर (!acpi_evalf(ecwr_handle, शून्य, शून्य, "vdd", i, v))
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (ec_ग_लिखो(i, v) < 0)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक issue_thinkpad_cmos_command(पूर्णांक cmos_cmd)
अणु
	अगर (!cmos_handle)
		वापस -ENXIO;

	अगर (!acpi_evalf(cmos_handle, शून्य, शून्य, "vd", cmos_cmd))
		वापस -EIO;

	वापस 0;
पूर्ण

/*************************************************************************
 * ACPI device model
 */

#घोषणा TPACPI_ACPIHANDLE_INIT(object) \
	drv_acpi_handle_init(#object, &object##_handle, *object##_parent, \
		object##_paths, ARRAY_SIZE(object##_paths))

अटल व्योम __init drv_acpi_handle_init(स्थिर अक्षर *name,
			   acpi_handle *handle, स्थिर acpi_handle parent,
			   अक्षर **paths, स्थिर पूर्णांक num_paths)
अणु
	पूर्णांक i;
	acpi_status status;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "trying to locate ACPI handle for %s\n",
		name);

	क्रम (i = 0; i < num_paths; i++) अणु
		status = acpi_get_handle(parent, paths[i], handle);
		अगर (ACPI_SUCCESS(status)) अणु
			dbg_prपूर्णांकk(TPACPI_DBG_INIT,
				   "Found ACPI handle %s for %s\n",
				   paths[i], name);
			वापस;
		पूर्ण
	पूर्ण

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "ACPI handle for %s not found\n",
		    name);
	*handle = शून्य;
पूर्ण

अटल acpi_status __init tpacpi_acpi_handle_locate_callback(acpi_handle handle,
			u32 level, व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_device *dev;
	अगर (!म_भेद(context, "video")) अणु
		अगर (acpi_bus_get_device(handle, &dev))
			वापस AE_OK;
		अगर (म_भेद(ACPI_VIDEO_HID, acpi_device_hid(dev)))
			वापस AE_OK;
	पूर्ण

	*(acpi_handle *)वापस_value = handle;

	वापस AE_CTRL_TERMINATE;
पूर्ण

अटल व्योम __init tpacpi_acpi_handle_locate(स्थिर अक्षर *name,
		स्थिर अक्षर *hid,
		acpi_handle *handle)
अणु
	acpi_status status;
	acpi_handle device_found;

	BUG_ON(!name || !handle);
	vdbg_prपूर्णांकk(TPACPI_DBG_INIT,
			"trying to locate ACPI handle for %s, using HID %s\n",
			name, hid ? hid : "NULL");

	स_रखो(&device_found, 0, माप(device_found));
	status = acpi_get_devices(hid, tpacpi_acpi_handle_locate_callback,
				  (व्योम *)name, &device_found);

	*handle = शून्य;

	अगर (ACPI_SUCCESS(status)) अणु
		*handle = device_found;
		dbg_prपूर्णांकk(TPACPI_DBG_INIT,
			   "Found ACPI handle for %s\n", name);
	पूर्ण अन्यथा अणु
		vdbg_prपूर्णांकk(TPACPI_DBG_INIT,
			    "Could not locate an ACPI handle for %s: %s\n",
			    name, acpi_क्रमmat_exception(status));
	पूर्ण
पूर्ण

अटल व्योम dispatch_acpi_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	काष्ठा ibm_काष्ठा *ibm = data;

	अगर (tpacpi_lअगरecycle != TPACPI_LIFE_RUNNING)
		वापस;

	अगर (!ibm || !ibm->acpi || !ibm->acpi->notअगरy)
		वापस;

	ibm->acpi->notअगरy(ibm, event);
पूर्ण

अटल पूर्णांक __init setup_acpi_notअगरy(काष्ठा ibm_काष्ठा *ibm)
अणु
	acpi_status status;
	पूर्णांक rc;

	BUG_ON(!ibm->acpi);

	अगर (!*ibm->acpi->handle)
		वापस 0;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT,
		"setting up ACPI notify for %s\n", ibm->name);

	rc = acpi_bus_get_device(*ibm->acpi->handle, &ibm->acpi->device);
	अगर (rc < 0) अणु
		pr_err("acpi_bus_get_device(%s) failed: %d\n", ibm->name, rc);
		वापस -ENODEV;
	पूर्ण

	ibm->acpi->device->driver_data = ibm;
	प्र_लिखो(acpi_device_class(ibm->acpi->device), "%s/%s",
		TPACPI_ACPI_EVENT_PREFIX,
		ibm->name);

	status = acpi_install_notअगरy_handler(*ibm->acpi->handle,
			ibm->acpi->type, dispatch_acpi_notअगरy, ibm);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (status == AE_ALREADY_EXISTS) अणु
			pr_notice("another device driver is already handling %s events\n",
				  ibm->name);
		पूर्ण अन्यथा अणु
			pr_err("acpi_install_notify_handler(%s) failed: %s\n",
			       ibm->name, acpi_क्रमmat_exception(status));
		पूर्ण
		वापस -ENODEV;
	पूर्ण
	ibm->flags.acpi_notअगरy_installed = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __init tpacpi_device_add(काष्ठा acpi_device *device)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __init रेजिस्टर_tpacpi_subdriver(काष्ठा ibm_काष्ठा *ibm)
अणु
	पूर्णांक rc;

	dbg_prपूर्णांकk(TPACPI_DBG_INIT,
		"registering %s as an ACPI driver\n", ibm->name);

	BUG_ON(!ibm->acpi);

	ibm->acpi->driver = kzalloc(माप(काष्ठा acpi_driver), GFP_KERNEL);
	अगर (!ibm->acpi->driver) अणु
		pr_err("failed to allocate memory for ibm->acpi->driver\n");
		वापस -ENOMEM;
	पूर्ण

	प्र_लिखो(ibm->acpi->driver->name, "%s_%s", TPACPI_NAME, ibm->name);
	ibm->acpi->driver->ids = ibm->acpi->hid;

	ibm->acpi->driver->ops.add = &tpacpi_device_add;

	rc = acpi_bus_रेजिस्टर_driver(ibm->acpi->driver);
	अगर (rc < 0) अणु
		pr_err("acpi_bus_register_driver(%s) failed: %d\n",
		       ibm->name, rc);
		kमुक्त(ibm->acpi->driver);
		ibm->acpi->driver = शून्य;
	पूर्ण अन्यथा अगर (!rc)
		ibm->flags.acpi_driver_रेजिस्टरed = 1;

	वापस rc;
पूर्ण


/****************************************************************************
 ****************************************************************************
 *
 * Procfs Helpers
 *
 ****************************************************************************
 ****************************************************************************/

अटल पूर्णांक dispatch_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ibm_काष्ठा *ibm = m->निजी;

	अगर (!ibm || !ibm->पढ़ो)
		वापस -EINVAL;
	वापस ibm->पढ़ो(m);
पूर्ण

अटल पूर्णांक dispatch_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, dispatch_proc_show, PDE_DATA(inode));
पूर्ण

अटल sमाप_प्रकार dispatch_proc_ग_लिखो(काष्ठा file *file,
			स्थिर अक्षर __user *userbuf,
			माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा ibm_काष्ठा *ibm = PDE_DATA(file_inode(file));
	अक्षर *kernbuf;
	पूर्णांक ret;

	अगर (!ibm || !ibm->ग_लिखो)
		वापस -EINVAL;
	अगर (count > PAGE_SIZE - 1)
		वापस -EINVAL;

	kernbuf = kदो_स्मृति(count + 1, GFP_KERNEL);
	अगर (!kernbuf)
		वापस -ENOMEM;

	अगर (copy_from_user(kernbuf, userbuf, count)) अणु
		kमुक्त(kernbuf);
		वापस -EFAULT;
	पूर्ण

	kernbuf[count] = 0;
	ret = ibm->ग_लिखो(kernbuf);
	अगर (ret == 0)
		ret = count;

	kमुक्त(kernbuf);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा proc_ops dispatch_proc_ops = अणु
	.proc_खोलो	= dispatch_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= dispatch_proc_ग_लिखो,
पूर्ण;

/****************************************************************************
 ****************************************************************************
 *
 * Device model: input, hwmon and platक्रमm
 *
 ****************************************************************************
 ****************************************************************************/

अटल काष्ठा platक्रमm_device *tpacpi_pdev;
अटल काष्ठा platक्रमm_device *tpacpi_sensors_pdev;
अटल काष्ठा device *tpacpi_hwmon;
अटल काष्ठा input_dev *tpacpi_inputdev;
अटल काष्ठा mutex tpacpi_inputdev_send_mutex;
अटल LIST_HEAD(tpacpi_all_drivers);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tpacpi_suspend_handler(काष्ठा device *dev)
अणु
	काष्ठा ibm_काष्ठा *ibm, *iपंचांगp;

	list_क्रम_each_entry_safe(ibm, iपंचांगp,
				 &tpacpi_all_drivers,
				 all_drivers) अणु
		अगर (ibm->suspend)
			(ibm->suspend)();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tpacpi_resume_handler(काष्ठा device *dev)
अणु
	काष्ठा ibm_काष्ठा *ibm, *iपंचांगp;

	list_क्रम_each_entry_safe(ibm, iपंचांगp,
				 &tpacpi_all_drivers,
				 all_drivers) अणु
		अगर (ibm->resume)
			(ibm->resume)();
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tpacpi_pm,
			 tpacpi_suspend_handler, tpacpi_resume_handler);

अटल व्योम tpacpi_shutकरोwn_handler(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ibm_काष्ठा *ibm, *iपंचांगp;

	list_क्रम_each_entry_safe(ibm, iपंचांगp,
				 &tpacpi_all_drivers,
				 all_drivers) अणु
		अगर (ibm->shutकरोwn)
			(ibm->shutकरोwn)();
	पूर्ण
पूर्ण

अटल काष्ठा platक्रमm_driver tpacpi_pdriver = अणु
	.driver = अणु
		.name = TPACPI_DRVR_NAME,
		.pm = &tpacpi_pm,
	पूर्ण,
	.shutकरोwn = tpacpi_shutकरोwn_handler,
पूर्ण;

अटल काष्ठा platक्रमm_driver tpacpi_hwmon_pdriver = अणु
	.driver = अणु
		.name = TPACPI_HWMON_DRVR_NAME,
	पूर्ण,
पूर्ण;

/*************************************************************************
 * sysfs support helpers
 */

काष्ठा attribute_set अणु
	अचिन्हित पूर्णांक members, max_members;
	काष्ठा attribute_group group;
पूर्ण;

काष्ठा attribute_set_obj अणु
	काष्ठा attribute_set s;
	काष्ठा attribute *a;
पूर्ण __attribute__((packed));

अटल काष्ठा attribute_set *create_attr_set(अचिन्हित पूर्णांक max_members,
						स्थिर अक्षर *name)
अणु
	काष्ठा attribute_set_obj *sobj;

	अगर (max_members == 0)
		वापस शून्य;

	/* Allocates space क्रम implicit शून्य at the end too */
	sobj = kzalloc(माप(काष्ठा attribute_set_obj) +
		    max_members * माप(काष्ठा attribute *),
		    GFP_KERNEL);
	अगर (!sobj)
		वापस शून्य;
	sobj->s.max_members = max_members;
	sobj->s.group.attrs = &sobj->a;
	sobj->s.group.name = name;

	वापस &sobj->s;
पूर्ण

#घोषणा destroy_attr_set(_set) \
	kमुक्त(_set)

/* not multi-thपढ़ोed safe, use it in a single thपढ़ो per set */
अटल पूर्णांक add_to_attr_set(काष्ठा attribute_set *s, काष्ठा attribute *attr)
अणु
	अगर (!s || !attr)
		वापस -EINVAL;

	अगर (s->members >= s->max_members)
		वापस -ENOMEM;

	s->group.attrs[s->members] = attr;
	s->members++;

	वापस 0;
पूर्ण

अटल पूर्णांक add_many_to_attr_set(काष्ठा attribute_set *s,
			काष्ठा attribute **attr,
			अचिन्हित पूर्णांक count)
अणु
	पूर्णांक i, res;

	क्रम (i = 0; i < count; i++) अणु
		res = add_to_attr_set(s, attr[i]);
		अगर (res)
			वापस res;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम delete_attr_set(काष्ठा attribute_set *s, काष्ठा kobject *kobj)
अणु
	sysfs_हटाओ_group(kobj, &s->group);
	destroy_attr_set(s);
पूर्ण

#घोषणा रेजिस्टर_attr_set_with_sysfs(_attr_set, _kobj) \
	sysfs_create_group(_kobj, &_attr_set->group)

अटल पूर्णांक parse_म_से_अदीर्घ(स्थिर अक्षर *buf,
		अचिन्हित दीर्घ max, अचिन्हित दीर्घ *value)
अणु
	अक्षर *endp;

	*value = simple_म_से_अदीर्घ(skip_spaces(buf), &endp, 0);
	endp = skip_spaces(endp);
	अगर (*endp || *value > max)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम tpacpi_disable_brightness_delay(व्योम)
अणु
	अगर (acpi_evalf(hkey_handle, शून्य, "PWMS", "qvd", 0))
		pr_notice("ACPI backlight control delay disabled\n");
पूर्ण

अटल व्योम prपूर्णांकk_deprecated_attribute(स्थिर अक्षर * स्थिर what,
					स्थिर अक्षर * स्थिर details)
अणु
	tpacpi_log_usertask("deprecated sysfs attribute");
	pr_warn("WARNING: sysfs attribute %s is deprecated and will be removed. %s\n",
		what, details);
पूर्ण

/*************************************************************************
 * rfसमाप्त and radio control support helpers
 */

/*
 * ThinkPad-ACPI firmware handling model:
 *
 * WLSW (master wireless चयन) is event-driven, and is common to all
 * firmware-controlled radios.  It cannot be controlled, just monitored,
 * as expected.  It overrides all radio state in firmware
 *
 * The kernel, a masked-off hotkey, and WLSW can change the radio state
 * (TODO: verअगरy how WLSW पूर्णांकeracts with the वापसed radio state).
 *
 * The only समय there are shaकरोw radio state changes, is when
 * masked-off hotkeys are used.
 */

/*
 * Internal driver API क्रम radio state:
 *
 * पूर्णांक: < 0 = error, otherwise क्रमागत tpacpi_rfसमाप्त_state
 * bool: true means radio blocked (off)
 */
क्रमागत tpacpi_rfसमाप्त_state अणु
	TPACPI_RFK_RADIO_OFF = 0,
	TPACPI_RFK_RADIO_ON
पूर्ण;

/* rfसमाप्त चयनes */
क्रमागत tpacpi_rfk_id अणु
	TPACPI_RFK_BLUETOOTH_SW_ID = 0,
	TPACPI_RFK_WWAN_SW_ID,
	TPACPI_RFK_UWB_SW_ID,
	TPACPI_RFK_SW_MAX
पूर्ण;

अटल स्थिर अक्षर *tpacpi_rfसमाप्त_names[] = अणु
	[TPACPI_RFK_BLUETOOTH_SW_ID] = "bluetooth",
	[TPACPI_RFK_WWAN_SW_ID] = "wwan",
	[TPACPI_RFK_UWB_SW_ID] = "uwb",
	[TPACPI_RFK_SW_MAX] = शून्य
पूर्ण;

/* ThinkPad-ACPI rfसमाप्त subdriver */
काष्ठा tpacpi_rfk अणु
	काष्ठा rfसमाप्त *rfसमाप्त;
	क्रमागत tpacpi_rfk_id id;
	स्थिर काष्ठा tpacpi_rfk_ops *ops;
पूर्ण;

काष्ठा tpacpi_rfk_ops अणु
	/* firmware पूर्णांकerface */
	पूर्णांक (*get_status)(व्योम);
	पूर्णांक (*set_status)(स्थिर क्रमागत tpacpi_rfसमाप्त_state);
पूर्ण;

अटल काष्ठा tpacpi_rfk *tpacpi_rfसमाप्त_चयनes[TPACPI_RFK_SW_MAX];

/* Query FW and update rfसमाप्त sw state क्रम a given rfसमाप्त चयन */
अटल पूर्णांक tpacpi_rfk_update_swstate(स्थिर काष्ठा tpacpi_rfk *tp_rfk)
अणु
	पूर्णांक status;

	अगर (!tp_rfk)
		वापस -ENODEV;

	status = (tp_rfk->ops->get_status)();
	अगर (status < 0)
		वापस status;

	rfसमाप्त_set_sw_state(tp_rfk->rfसमाप्त,
			    (status == TPACPI_RFK_RADIO_OFF));

	वापस status;
पूर्ण

/* Query FW and update rfसमाप्त sw state क्रम all rfसमाप्त चयनes */
अटल व्योम tpacpi_rfk_update_swstate_all(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < TPACPI_RFK_SW_MAX; i++)
		tpacpi_rfk_update_swstate(tpacpi_rfसमाप्त_चयनes[i]);
पूर्ण

/*
 * Sync the HW-blocking state of all rfसमाप्त चयनes,
 * करो notice it causes the rfसमाप्त core to schedule uevents
 */
अटल व्योम tpacpi_rfk_update_hwblock_state(bool blocked)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा tpacpi_rfk *tp_rfk;

	क्रम (i = 0; i < TPACPI_RFK_SW_MAX; i++) अणु
		tp_rfk = tpacpi_rfसमाप्त_चयनes[i];
		अगर (tp_rfk) अणु
			अगर (rfसमाप्त_set_hw_state(tp_rfk->rfसमाप्त,
						blocked)) अणु
				/* ignore -- we track sw block */
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Call to get the WLSW state from the firmware */
अटल पूर्णांक hotkey_get_wlsw(व्योम);

/* Call to query WLSW state and update all rfसमाप्त चयनes */
अटल bool tpacpi_rfk_check_hwblock_state(व्योम)
अणु
	पूर्णांक res = hotkey_get_wlsw();
	पूर्णांक hw_blocked;

	/* When unknown or unsupported, we have to assume it is unblocked */
	अगर (res < 0)
		वापस false;

	hw_blocked = (res == TPACPI_RFK_RADIO_OFF);
	tpacpi_rfk_update_hwblock_state(hw_blocked);

	वापस hw_blocked;
पूर्ण

अटल पूर्णांक tpacpi_rfk_hook_set_block(व्योम *data, bool blocked)
अणु
	काष्ठा tpacpi_rfk *tp_rfk = data;
	पूर्णांक res;

	dbg_prपूर्णांकk(TPACPI_DBG_RFKILL,
		   "request to change radio state to %s\n",
		   blocked ? "blocked" : "unblocked");

	/* try to set radio state */
	res = (tp_rfk->ops->set_status)(blocked ?
				TPACPI_RFK_RADIO_OFF : TPACPI_RFK_RADIO_ON);

	/* and update the rfसमाप्त core with whatever the FW really did */
	tpacpi_rfk_update_swstate(tp_rfk);

	वापस (res < 0) ? res : 0;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops tpacpi_rfk_rfसमाप्त_ops = अणु
	.set_block = tpacpi_rfk_hook_set_block,
पूर्ण;

अटल पूर्णांक __init tpacpi_new_rfसमाप्त(स्थिर क्रमागत tpacpi_rfk_id id,
			स्थिर काष्ठा tpacpi_rfk_ops *tp_rfkops,
			स्थिर क्रमागत rfसमाप्त_type rfktype,
			स्थिर अक्षर *name,
			स्थिर bool set_शेष)
अणु
	काष्ठा tpacpi_rfk *atp_rfk;
	पूर्णांक res;
	bool sw_state = false;
	bool hw_state;
	पूर्णांक sw_status;

	BUG_ON(id >= TPACPI_RFK_SW_MAX || tpacpi_rfसमाप्त_चयनes[id]);

	atp_rfk = kzalloc(माप(काष्ठा tpacpi_rfk), GFP_KERNEL);
	अगर (atp_rfk)
		atp_rfk->rfसमाप्त = rfसमाप्त_alloc(name,
						&tpacpi_pdev->dev,
						rfktype,
						&tpacpi_rfk_rfसमाप्त_ops,
						atp_rfk);
	अगर (!atp_rfk || !atp_rfk->rfसमाप्त) अणु
		pr_err("failed to allocate memory for rfkill class\n");
		kमुक्त(atp_rfk);
		वापस -ENOMEM;
	पूर्ण

	atp_rfk->id = id;
	atp_rfk->ops = tp_rfkops;

	sw_status = (tp_rfkops->get_status)();
	अगर (sw_status < 0) अणु
		pr_err("failed to read initial state for %s, error %d\n",
		       name, sw_status);
	पूर्ण अन्यथा अणु
		sw_state = (sw_status == TPACPI_RFK_RADIO_OFF);
		अगर (set_शेष) अणु
			/* try to keep the initial state, since we ask the
			 * firmware to preserve it across S5 in NVRAM */
			rfसमाप्त_init_sw_state(atp_rfk->rfसमाप्त, sw_state);
		पूर्ण
	पूर्ण
	hw_state = tpacpi_rfk_check_hwblock_state();
	rfसमाप्त_set_hw_state(atp_rfk->rfसमाप्त, hw_state);

	res = rfसमाप्त_रेजिस्टर(atp_rfk->rfसमाप्त);
	अगर (res < 0) अणु
		pr_err("failed to register %s rfkill switch: %d\n", name, res);
		rfसमाप्त_destroy(atp_rfk->rfसमाप्त);
		kमुक्त(atp_rfk);
		वापस res;
	पूर्ण

	tpacpi_rfसमाप्त_चयनes[id] = atp_rfk;

	pr_info("rfkill switch %s: radio is %sblocked\n",
		name, (sw_state || hw_state) ? "" : "un");
	वापस 0;
पूर्ण

अटल व्योम tpacpi_destroy_rfसमाप्त(स्थिर क्रमागत tpacpi_rfk_id id)
अणु
	काष्ठा tpacpi_rfk *tp_rfk;

	BUG_ON(id >= TPACPI_RFK_SW_MAX);

	tp_rfk = tpacpi_rfसमाप्त_चयनes[id];
	अगर (tp_rfk) अणु
		rfसमाप्त_unरेजिस्टर(tp_rfk->rfसमाप्त);
		rfसमाप्त_destroy(tp_rfk->rfसमाप्त);
		tpacpi_rfसमाप्त_चयनes[id] = शून्य;
		kमुक्त(tp_rfk);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांकk_deprecated_rfसमाप्त_attribute(स्थिर अक्षर * स्थिर what)
अणु
	prपूर्णांकk_deprecated_attribute(what,
			"Please switch to generic rfkill before year 2010");
पूर्ण

/* sysfs <radio> enable ------------------------------------------------ */
अटल sमाप_प्रकार tpacpi_rfk_sysfs_enable_show(स्थिर क्रमागत tpacpi_rfk_id id,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	पूर्णांक status;

	prपूर्णांकk_deprecated_rfसमाप्त_attribute(attr->attr.name);

	/* This is in the ABI... */
	अगर (tpacpi_rfk_check_hwblock_state()) अणु
		status = TPACPI_RFK_RADIO_OFF;
	पूर्ण अन्यथा अणु
		status = tpacpi_rfk_update_swstate(tpacpi_rfसमाप्त_चयनes[id]);
		अगर (status < 0)
			वापस status;
	पूर्ण

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			(status == TPACPI_RFK_RADIO_ON) ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार tpacpi_rfk_sysfs_enable_store(स्थिर क्रमागत tpacpi_rfk_id id,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;
	पूर्णांक res;

	prपूर्णांकk_deprecated_rfसमाप्त_attribute(attr->attr.name);

	अगर (parse_म_से_अदीर्घ(buf, 1, &t))
		वापस -EINVAL;

	tpacpi_disबंद_usertask(attr->attr.name, "set to %ld\n", t);

	/* This is in the ABI... */
	अगर (tpacpi_rfk_check_hwblock_state() && !!t)
		वापस -EPERM;

	res = tpacpi_rfसमाप्त_चयनes[id]->ops->set_status((!!t) ?
				TPACPI_RFK_RADIO_ON : TPACPI_RFK_RADIO_OFF);
	tpacpi_rfk_update_swstate(tpacpi_rfसमाप्त_चयनes[id]);

	वापस (res < 0) ? res : count;
पूर्ण

/* procfs -------------------------------------------------------------- */
अटल पूर्णांक tpacpi_rfk_procfs_पढ़ो(स्थिर क्रमागत tpacpi_rfk_id id, काष्ठा seq_file *m)
अणु
	अगर (id >= TPACPI_RFK_SW_MAX)
		seq_म_लिखो(m, "status:\t\tnot supported\n");
	अन्यथा अणु
		पूर्णांक status;

		/* This is in the ABI... */
		अगर (tpacpi_rfk_check_hwblock_state()) अणु
			status = TPACPI_RFK_RADIO_OFF;
		पूर्ण अन्यथा अणु
			status = tpacpi_rfk_update_swstate(
						tpacpi_rfसमाप्त_चयनes[id]);
			अगर (status < 0)
				वापस status;
		पूर्ण

		seq_म_लिखो(m, "status:\t\t%s\n",
				(status == TPACPI_RFK_RADIO_ON) ?
					"enabled" : "disabled");
		seq_म_लिखो(m, "commands:\tenable, disable\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tpacpi_rfk_procfs_ग_लिखो(स्थिर क्रमागत tpacpi_rfk_id id, अक्षर *buf)
अणु
	अक्षर *cmd;
	पूर्णांक status = -1;
	पूर्णांक res = 0;

	अगर (id >= TPACPI_RFK_SW_MAX)
		वापस -ENODEV;

	जबतक ((cmd = strsep(&buf, ","))) अणु
		अगर (म_मापcmp(cmd, "enable") == 0)
			status = TPACPI_RFK_RADIO_ON;
		अन्यथा अगर (म_मापcmp(cmd, "disable") == 0)
			status = TPACPI_RFK_RADIO_OFF;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (status != -1) अणु
		tpacpi_disबंद_usertask("procfs", "attempt to %s %s\n",
				(status == TPACPI_RFK_RADIO_ON) ?
						"enable" : "disable",
				tpacpi_rfसमाप्त_names[id]);
		res = (tpacpi_rfसमाप्त_चयनes[id]->ops->set_status)(status);
		tpacpi_rfk_update_swstate(tpacpi_rfसमाप्त_चयनes[id]);
	पूर्ण

	वापस res;
पूर्ण

/*************************************************************************
 * thinkpad-acpi driver attributes
 */

/* पूर्णांकerface_version --------------------------------------------------- */
अटल sमाप_प्रकार पूर्णांकerface_version_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%08x\n", TPACPI_SYSFS_VERSION);
पूर्ण
अटल DRIVER_ATTR_RO(पूर्णांकerface_version);

/* debug_level --------------------------------------------------------- */
अटल sमाप_प्रकार debug_level_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%04x\n", dbg_level);
पूर्ण

अटल sमाप_प्रकार debug_level_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;

	अगर (parse_म_से_अदीर्घ(buf, 0xffff, &t))
		वापस -EINVAL;

	dbg_level = t;

	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(debug_level);

/* version ------------------------------------------------------------- */
अटल sमाप_प्रकार version_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s v%s\n",
			TPACPI_DESC, TPACPI_VERSION);
पूर्ण
अटल DRIVER_ATTR_RO(version);

/* --------------------------------------------------------------------- */

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES

/* wlsw_emulstate ------------------------------------------------------ */
अटल sमाप_प्रकार wlsw_emulstate_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", !!tpacpi_wlsw_emulstate);
पूर्ण

अटल sमाप_प्रकार wlsw_emulstate_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
				    माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;

	अगर (parse_म_से_अदीर्घ(buf, 1, &t))
		वापस -EINVAL;

	अगर (tpacpi_wlsw_emulstate != !!t) अणु
		tpacpi_wlsw_emulstate = !!t;
		tpacpi_rfk_update_hwblock_state(!t);	/* negative logic */
	पूर्ण

	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(wlsw_emulstate);

/* bluetooth_emulstate ------------------------------------------------- */
अटल sमाप_प्रकार bluetooth_emulstate_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", !!tpacpi_bluetooth_emulstate);
पूर्ण

अटल sमाप_प्रकार bluetooth_emulstate_store(काष्ठा device_driver *drv,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;

	अगर (parse_म_से_अदीर्घ(buf, 1, &t))
		वापस -EINVAL;

	tpacpi_bluetooth_emulstate = !!t;

	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(bluetooth_emulstate);

/* wwan_emulstate ------------------------------------------------- */
अटल sमाप_प्रकार wwan_emulstate_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", !!tpacpi_wwan_emulstate);
पूर्ण

अटल sमाप_प्रकार wwan_emulstate_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
				    माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;

	अगर (parse_म_से_अदीर्घ(buf, 1, &t))
		वापस -EINVAL;

	tpacpi_wwan_emulstate = !!t;

	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(wwan_emulstate);

/* uwb_emulstate ------------------------------------------------- */
अटल sमाप_प्रकार uwb_emulstate_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", !!tpacpi_uwb_emulstate);
पूर्ण

अटल sमाप_प्रकार uwb_emulstate_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
				   माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;

	अगर (parse_म_से_अदीर्घ(buf, 1, &t))
		वापस -EINVAL;

	tpacpi_uwb_emulstate = !!t;

	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(uwb_emulstate);
#पूर्ण_अगर

/* --------------------------------------------------------------------- */

अटल काष्ठा driver_attribute *tpacpi_driver_attributes[] = अणु
	&driver_attr_debug_level, &driver_attr_version,
	&driver_attr_पूर्णांकerface_version,
पूर्ण;

अटल पूर्णांक __init tpacpi_create_driver_attributes(काष्ठा device_driver *drv)
अणु
	पूर्णांक i, res;

	i = 0;
	res = 0;
	जबतक (!res && i < ARRAY_SIZE(tpacpi_driver_attributes)) अणु
		res = driver_create_file(drv, tpacpi_driver_attributes[i]);
		i++;
	पूर्ण

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	अगर (!res && dbg_wlswemul)
		res = driver_create_file(drv, &driver_attr_wlsw_emulstate);
	अगर (!res && dbg_bluetoothemul)
		res = driver_create_file(drv, &driver_attr_bluetooth_emulstate);
	अगर (!res && dbg_wwanemul)
		res = driver_create_file(drv, &driver_attr_wwan_emulstate);
	अगर (!res && dbg_uwbemul)
		res = driver_create_file(drv, &driver_attr_uwb_emulstate);
#पूर्ण_अगर

	वापस res;
पूर्ण

अटल व्योम tpacpi_हटाओ_driver_attributes(काष्ठा device_driver *drv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tpacpi_driver_attributes); i++)
		driver_हटाओ_file(drv, tpacpi_driver_attributes[i]);

#अगर_घोषित THINKPAD_ACPI_DEBUGFACILITIES
	driver_हटाओ_file(drv, &driver_attr_wlsw_emulstate);
	driver_हटाओ_file(drv, &driver_attr_bluetooth_emulstate);
	driver_हटाओ_file(drv, &driver_attr_wwan_emulstate);
	driver_हटाओ_file(drv, &driver_attr_uwb_emulstate);
#पूर्ण_अगर
पूर्ण

/*************************************************************************
 * Firmware Data
 */

/*
 * Table of recommended minimum BIOS versions
 *
 * Reasons क्रम listing:
 *    1. Stable BIOS, listed because the unknown amount of
 *       bugs and bad ACPI behaviour on older versions
 *
 *    2. BIOS or EC fw with known bugs that trigger on Linux
 *
 *    3. BIOS with known reduced functionality in older versions
 *
 *  We recommend the latest BIOS and EC version.
 *  We only support the latest BIOS and EC fw version as a rule.
 *
 *  Sources: IBM ThinkPad Public Web Documents (update changelogs),
 *  Inक्रमmation from users in ThinkWiki
 *
 *  WARNING: we use this table also to detect that the machine is
 *  a ThinkPad in some हालs, so करोn't हटाओ entries lightly.
 */

#घोषणा TPV_Q(__v, __id1, __id2, __bv1, __bv2)		\
	अणु .venकरोr	= (__v),			\
	  .bios		= TPID(__id1, __id2),		\
	  .ec		= TPACPI_MATCH_ANY,		\
	  .quirks	= TPACPI_MATCH_ANY_VERSION << 16 \
			  | TPVER(__bv1, __bv2) पूर्ण

#घोषणा TPV_Q_X(__v, __bid1, __bid2, __bv1, __bv2,	\
		__eid, __ev1, __ev2)			\
	अणु .venकरोr	= (__v),			\
	  .bios		= TPID(__bid1, __bid2),		\
	  .ec		= __eid,			\
	  .quirks	= TPVER(__ev1, __ev2) << 16	\
			  | TPVER(__bv1, __bv2) पूर्ण

#घोषणा TPV_QI0(__id1, __id2, __bv1, __bv2) \
	TPV_Q(PCI_VENDOR_ID_IBM, __id1, __id2, __bv1, __bv2)

/* Outdated IBM BIOSes often lack the EC id string */
#घोषणा TPV_QI1(__id1, __id2, __bv1, __bv2, __ev1, __ev2) \
	TPV_Q_X(PCI_VENDOR_ID_IBM, __id1, __id2, 	\
		__bv1, __bv2, TPID(__id1, __id2),	\
		__ev1, __ev2),				\
	TPV_Q_X(PCI_VENDOR_ID_IBM, __id1, __id2, 	\
		__bv1, __bv2, TPACPI_MATCH_UNKNOWN,	\
		__ev1, __ev2)

/* Outdated IBM BIOSes often lack the EC id string */
#घोषणा TPV_QI2(__bid1, __bid2, __bv1, __bv2,		\
		__eid1, __eid2, __ev1, __ev2) 		\
	TPV_Q_X(PCI_VENDOR_ID_IBM, __bid1, __bid2, 	\
		__bv1, __bv2, TPID(__eid1, __eid2),	\
		__ev1, __ev2),				\
	TPV_Q_X(PCI_VENDOR_ID_IBM, __bid1, __bid2, 	\
		__bv1, __bv2, TPACPI_MATCH_UNKNOWN,	\
		__ev1, __ev2)

#घोषणा TPV_QL0(__id1, __id2, __bv1, __bv2) \
	TPV_Q(PCI_VENDOR_ID_LENOVO, __id1, __id2, __bv1, __bv2)

#घोषणा TPV_QL1(__id1, __id2, __bv1, __bv2, __ev1, __ev2) \
	TPV_Q_X(PCI_VENDOR_ID_LENOVO, __id1, __id2, 	\
		__bv1, __bv2, TPID(__id1, __id2),	\
		__ev1, __ev2)

#घोषणा TPV_QL2(__bid1, __bid2, __bv1, __bv2,		\
		__eid1, __eid2, __ev1, __ev2) 		\
	TPV_Q_X(PCI_VENDOR_ID_LENOVO, __bid1, __bid2, 	\
		__bv1, __bv2, TPID(__eid1, __eid2),	\
		__ev1, __ev2)

अटल स्थिर काष्ठा tpacpi_quirk tpacpi_bios_version_qtable[] __initस्थिर = अणु
	/*  Numeric models ------------------ */
	/*      FW MODEL   BIOS VERS	      */
	TPV_QI0('I', 'M',  '6', '5'),		 /* 570 */
	TPV_QI0('I', 'U',  '2', '6'),		 /* 570E */
	TPV_QI0('I', 'B',  '5', '4'),		 /* 600 */
	TPV_QI0('I', 'H',  '4', '7'),		 /* 600E */
	TPV_QI0('I', 'N',  '3', '6'),		 /* 600E */
	TPV_QI0('I', 'T',  '5', '5'),		 /* 600X */
	TPV_QI0('I', 'D',  '4', '8'),		 /* 770, 770E, 770ED */
	TPV_QI0('I', 'I',  '4', '2'),		 /* 770X */
	TPV_QI0('I', 'O',  '2', '3'),		 /* 770Z */

	/* A-series ------------------------- */
	/*      FW MODEL   BIOS VERS  EC VERS */
	TPV_QI0('I', 'W',  '5', '9'),		 /* A20m */
	TPV_QI0('I', 'V',  '6', '9'),		 /* A20p */
	TPV_QI0('1', '0',  '2', '6'),		 /* A21e, A22e */
	TPV_QI0('K', 'U',  '3', '6'),		 /* A21e */
	TPV_QI0('K', 'X',  '3', '6'),		 /* A21m, A22m */
	TPV_QI0('K', 'Y',  '3', '8'),		 /* A21p, A22p */
	TPV_QI0('1', 'B',  '1', '7'),		 /* A22e */
	TPV_QI0('1', '3',  '2', '0'),		 /* A22m */
	TPV_QI0('1', 'E',  '7', '3'),		 /* A30/p (0) */
	TPV_QI1('1', 'G',  '4', '1',  '1', '7'), /* A31/p (0) */
	TPV_QI1('1', 'N',  '1', '6',  '0', '7'), /* A31/p (0) */

	/* G-series ------------------------- */
	/*      FW MODEL   BIOS VERS	      */
	TPV_QI0('1', 'T',  'A', '6'),		 /* G40 */
	TPV_QI0('1', 'X',  '5', '7'),		 /* G41 */

	/* R-series, T-series --------------- */
	/*      FW MODEL   BIOS VERS  EC VERS */
	TPV_QI0('1', 'C',  'F', '0'),		 /* R30 */
	TPV_QI0('1', 'F',  'F', '1'),		 /* R31 */
	TPV_QI0('1', 'M',  '9', '7'),		 /* R32 */
	TPV_QI0('1', 'O',  '6', '1'),		 /* R40 */
	TPV_QI0('1', 'P',  '6', '5'),		 /* R40 */
	TPV_QI0('1', 'S',  '7', '0'),		 /* R40e */
	TPV_QI1('1', 'R',  'D', 'R',  '7', '1'), /* R50/p, R51,
						    T40/p, T41/p, T42/p (1) */
	TPV_QI1('1', 'V',  '7', '1',  '2', '8'), /* R50e, R51 (1) */
	TPV_QI1('7', '8',  '7', '1',  '0', '6'), /* R51e (1) */
	TPV_QI1('7', '6',  '6', '9',  '1', '6'), /* R52 (1) */
	TPV_QI1('7', '0',  '6', '9',  '2', '8'), /* R52, T43 (1) */

	TPV_QI0('I', 'Y',  '6', '1'),		 /* T20 */
	TPV_QI0('K', 'Z',  '3', '4'),		 /* T21 */
	TPV_QI0('1', '6',  '3', '2'),		 /* T22 */
	TPV_QI1('1', 'A',  '6', '4',  '2', '3'), /* T23 (0) */
	TPV_QI1('1', 'I',  '7', '1',  '2', '0'), /* T30 (0) */
	TPV_QI1('1', 'Y',  '6', '5',  '2', '9'), /* T43/p (1) */

	TPV_QL1('7', '9',  'E', '3',  '5', '0'), /* T60/p */
	TPV_QL1('7', 'C',  'D', '2',  '2', '2'), /* R60, R60i */
	TPV_QL1('7', 'E',  'D', '0',  '1', '5'), /* R60e, R60i */

	/*      BIOS FW    BIOS VERS  EC FW     EC VERS */
	TPV_QI2('1', 'W',  '9', '0',  '1', 'V', '2', '8'), /* R50e (1) */
	TPV_QL2('7', 'I',  '3', '4',  '7', '9', '5', '0'), /* T60/p wide */

	/* X-series ------------------------- */
	/*      FW MODEL   BIOS VERS  EC VERS */
	TPV_QI0('I', 'Z',  '9', 'D'),		 /* X20, X21 */
	TPV_QI0('1', 'D',  '7', '0'),		 /* X22, X23, X24 */
	TPV_QI1('1', 'K',  '4', '8',  '1', '8'), /* X30 (0) */
	TPV_QI1('1', 'Q',  '9', '7',  '2', '3'), /* X31, X32 (0) */
	TPV_QI1('1', 'U',  'D', '3',  'B', '2'), /* X40 (0) */
	TPV_QI1('7', '4',  '6', '4',  '2', '7'), /* X41 (0) */
	TPV_QI1('7', '5',  '6', '0',  '2', '0'), /* X41t (0) */

	TPV_QL1('7', 'B',  'D', '7',  '4', '0'), /* X60/s */
	TPV_QL1('7', 'J',  '3', '0',  '1', '3'), /* X60t */

	/* (0) - older versions lack DMI EC fw string and functionality */
	/* (1) - older versions known to lack functionality */
पूर्ण;

#अघोषित TPV_QL1
#अघोषित TPV_QL0
#अघोषित TPV_QI2
#अघोषित TPV_QI1
#अघोषित TPV_QI0
#अघोषित TPV_Q_X
#अघोषित TPV_Q

अटल व्योम __init tpacpi_check_outdated_fw(व्योम)
अणु
	अचिन्हित दीर्घ fwvers;
	u16 ec_version, bios_version;

	fwvers = tpacpi_check_quirks(tpacpi_bios_version_qtable,
				ARRAY_SIZE(tpacpi_bios_version_qtable));

	अगर (!fwvers)
		वापस;

	bios_version = fwvers & 0xffffU;
	ec_version = (fwvers >> 16) & 0xffffU;

	/* note that unknown versions are set to 0x0000 and we use that */
	अगर ((bios_version > thinkpad_id.bios_release) ||
	    (ec_version > thinkpad_id.ec_release &&
				ec_version != TPACPI_MATCH_ANY_VERSION)) अणु
		/*
		 * The changelogs would let us track करोwn the exact
		 * reason, but it is just too much of a pain to track
		 * it.  We only list BIOSes that are either really
		 * broken, or really stable to begin with, so it is
		 * best अगर the user upgrades the firmware anyway.
		 */
		pr_warn("WARNING: Outdated ThinkPad BIOS/EC firmware\n");
		pr_warn("WARNING: This firmware may be missing critical bug fixes and/or important features\n");
	पूर्ण
पूर्ण

अटल bool __init tpacpi_is_fw_known(व्योम)
अणु
	वापस tpacpi_check_quirks(tpacpi_bios_version_qtable,
			ARRAY_SIZE(tpacpi_bios_version_qtable)) != 0;
पूर्ण

/****************************************************************************
 ****************************************************************************
 *
 * Subdrivers
 *
 ****************************************************************************
 ****************************************************************************/

/*************************************************************************
 * thinkpad-acpi metadata subdriver
 */

अटल पूर्णांक thinkpad_acpi_driver_पढ़ो(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "driver:\t\t%s\n", TPACPI_DESC);
	seq_म_लिखो(m, "version:\t%s\n", TPACPI_VERSION);
	वापस 0;
पूर्ण

अटल काष्ठा ibm_काष्ठा thinkpad_acpi_driver_data = अणु
	.name = "driver",
	.पढ़ो = thinkpad_acpi_driver_पढ़ो,
पूर्ण;

/*************************************************************************
 * Hotkey subdriver
 */

/*
 * ThinkPad firmware event model
 *
 * The ThinkPad firmware has two मुख्य event पूर्णांकerfaces: normal ACPI
 * notअगरications (which follow the ACPI standard), and a निजी event
 * पूर्णांकerface.
 *
 * The निजी event पूर्णांकerface also issues events क्रम the hotkeys.  As
 * the driver gained features, the event handling code ended up being
 * built around the hotkey subdriver.  This will need to be refactored
 * to a more क्रमmal event API eventually.
 *
 * Some "hotkeys" are actually supposed to be used as event reports,
 * such as "brightness has changed", "volume has changed", depending on
 * the ThinkPad model and how the firmware is operating.
 *
 * Unlike other classes, hotkey-class events have mask/unmask control on
 * non-ancient firmware.  However, how it behaves changes a lot with the
 * firmware model and version.
 */

क्रमागत अणु	/* hot key scan codes (derived from ACPI DSDT) */
	TP_ACPI_HOTKEYSCAN_FNF1		= 0,
	TP_ACPI_HOTKEYSCAN_FNF2,
	TP_ACPI_HOTKEYSCAN_FNF3,
	TP_ACPI_HOTKEYSCAN_FNF4,
	TP_ACPI_HOTKEYSCAN_FNF5,
	TP_ACPI_HOTKEYSCAN_FNF6,
	TP_ACPI_HOTKEYSCAN_FNF7,
	TP_ACPI_HOTKEYSCAN_FNF8,
	TP_ACPI_HOTKEYSCAN_FNF9,
	TP_ACPI_HOTKEYSCAN_FNF10,
	TP_ACPI_HOTKEYSCAN_FNF11,
	TP_ACPI_HOTKEYSCAN_FNF12,
	TP_ACPI_HOTKEYSCAN_FNBACKSPACE,
	TP_ACPI_HOTKEYSCAN_FNINSERT,
	TP_ACPI_HOTKEYSCAN_FNDELETE,
	TP_ACPI_HOTKEYSCAN_FNHOME,
	TP_ACPI_HOTKEYSCAN_FNEND,
	TP_ACPI_HOTKEYSCAN_FNPAGEUP,
	TP_ACPI_HOTKEYSCAN_FNPAGEDOWN,
	TP_ACPI_HOTKEYSCAN_FNSPACE,
	TP_ACPI_HOTKEYSCAN_VOLUMEUP,
	TP_ACPI_HOTKEYSCAN_VOLUMEDOWN,
	TP_ACPI_HOTKEYSCAN_MUTE,
	TP_ACPI_HOTKEYSCAN_THINKPAD,
	TP_ACPI_HOTKEYSCAN_UNK1,
	TP_ACPI_HOTKEYSCAN_UNK2,
	TP_ACPI_HOTKEYSCAN_UNK3,
	TP_ACPI_HOTKEYSCAN_UNK4,
	TP_ACPI_HOTKEYSCAN_UNK5,
	TP_ACPI_HOTKEYSCAN_UNK6,
	TP_ACPI_HOTKEYSCAN_UNK7,
	TP_ACPI_HOTKEYSCAN_UNK8,

	/* Adaptive keyboard keycodes */
	TP_ACPI_HOTKEYSCAN_ADAPTIVE_START,
	TP_ACPI_HOTKEYSCAN_MUTE2        = TP_ACPI_HOTKEYSCAN_ADAPTIVE_START,
	TP_ACPI_HOTKEYSCAN_BRIGHTNESS_ZERO,
	TP_ACPI_HOTKEYSCAN_CLIPPING_TOOL,
	TP_ACPI_HOTKEYSCAN_CLOUD,
	TP_ACPI_HOTKEYSCAN_UNK9,
	TP_ACPI_HOTKEYSCAN_VOICE,
	TP_ACPI_HOTKEYSCAN_UNK10,
	TP_ACPI_HOTKEYSCAN_GESTURES,
	TP_ACPI_HOTKEYSCAN_UNK11,
	TP_ACPI_HOTKEYSCAN_UNK12,
	TP_ACPI_HOTKEYSCAN_UNK13,
	TP_ACPI_HOTKEYSCAN_CONFIG,
	TP_ACPI_HOTKEYSCAN_NEW_TAB,
	TP_ACPI_HOTKEYSCAN_RELOAD,
	TP_ACPI_HOTKEYSCAN_BACK,
	TP_ACPI_HOTKEYSCAN_MIC_DOWN,
	TP_ACPI_HOTKEYSCAN_MIC_UP,
	TP_ACPI_HOTKEYSCAN_MIC_CANCELLATION,
	TP_ACPI_HOTKEYSCAN_CAMERA_MODE,
	TP_ACPI_HOTKEYSCAN_ROTATE_DISPLAY,

	/* Lenovo extended keymap, starting at 0x1300 */
	TP_ACPI_HOTKEYSCAN_EXTENDED_START,
	/* first new observed key (star, favorites) is 0x1311 */
	TP_ACPI_HOTKEYSCAN_STAR = 69,
	TP_ACPI_HOTKEYSCAN_CLIPPING_TOOL2,
	TP_ACPI_HOTKEYSCAN_CALCULATOR,
	TP_ACPI_HOTKEYSCAN_BLUETOOTH,
	TP_ACPI_HOTKEYSCAN_KEYBOARD,
	TP_ACPI_HOTKEYSCAN_FN_RIGHT_SHIFT, /* Used by "Lenovo Quick Clean" */
	TP_ACPI_HOTKEYSCAN_NOTIFICATION_CENTER,
	TP_ACPI_HOTKEYSCAN_PICKUP_PHONE,
	TP_ACPI_HOTKEYSCAN_HANGUP_PHONE,

	/* Hotkey keymap size */
	TPACPI_HOTKEY_MAP_LEN
पूर्ण;

क्रमागत अणु	/* Keys/events available through NVRAM polling */
	TPACPI_HKEY_NVRAM_KNOWN_MASK = 0x00fb88c0U,
	TPACPI_HKEY_NVRAM_GOOD_MASK  = 0x00fb8000U,
पूर्ण;

क्रमागत अणु	/* Positions of some of the keys in hotkey masks */
	TP_ACPI_HKEY_DISPSWTCH_MASK	= 1 << TP_ACPI_HOTKEYSCAN_FNF7,
	TP_ACPI_HKEY_DISPXPAND_MASK	= 1 << TP_ACPI_HOTKEYSCAN_FNF8,
	TP_ACPI_HKEY_HIBERNATE_MASK	= 1 << TP_ACPI_HOTKEYSCAN_FNF12,
	TP_ACPI_HKEY_BRGHTUP_MASK	= 1 << TP_ACPI_HOTKEYSCAN_FNHOME,
	TP_ACPI_HKEY_BRGHTDWN_MASK	= 1 << TP_ACPI_HOTKEYSCAN_FNEND,
	TP_ACPI_HKEY_KBD_LIGHT_MASK	= 1 << TP_ACPI_HOTKEYSCAN_FNPAGEUP,
	TP_ACPI_HKEY_ZOOM_MASK		= 1 << TP_ACPI_HOTKEYSCAN_FNSPACE,
	TP_ACPI_HKEY_VOLUP_MASK		= 1 << TP_ACPI_HOTKEYSCAN_VOLUMEUP,
	TP_ACPI_HKEY_VOLDWN_MASK	= 1 << TP_ACPI_HOTKEYSCAN_VOLUMEDOWN,
	TP_ACPI_HKEY_MUTE_MASK		= 1 << TP_ACPI_HOTKEYSCAN_MUTE,
	TP_ACPI_HKEY_THINKPAD_MASK	= 1 << TP_ACPI_HOTKEYSCAN_THINKPAD,
पूर्ण;

क्रमागत अणु	/* NVRAM to ACPI HKEY group map */
	TP_NVRAM_HKEY_GROUP_HK2		= TP_ACPI_HKEY_THINKPAD_MASK |
					  TP_ACPI_HKEY_ZOOM_MASK |
					  TP_ACPI_HKEY_DISPSWTCH_MASK |
					  TP_ACPI_HKEY_HIBERNATE_MASK,
	TP_NVRAM_HKEY_GROUP_BRIGHTNESS	= TP_ACPI_HKEY_BRGHTUP_MASK |
					  TP_ACPI_HKEY_BRGHTDWN_MASK,
	TP_NVRAM_HKEY_GROUP_VOLUME	= TP_ACPI_HKEY_VOLUP_MASK |
					  TP_ACPI_HKEY_VOLDWN_MASK |
					  TP_ACPI_HKEY_MUTE_MASK,
पूर्ण;

#अगर_घोषित CONFIG_THINKPAD_ACPI_HOTKEY_POLL
काष्ठा tp_nvram_state अणु
       u16 thinkpad_toggle:1;
       u16 zoom_toggle:1;
       u16 display_toggle:1;
       u16 thinklight_toggle:1;
       u16 hibernate_toggle:1;
       u16 displayexp_toggle:1;
       u16 display_state:1;
       u16 brightness_toggle:1;
       u16 volume_toggle:1;
       u16 mute:1;

       u8 brightness_level;
       u8 volume_level;
पूर्ण;

/* kthपढ़ो क्रम the hotkey poller */
अटल काष्ठा task_काष्ठा *tpacpi_hotkey_task;

/*
 * Acquire mutex to ग_लिखो poller control variables as an
 * atomic block.
 *
 * Increment hotkey_config_change when changing them अगर you
 * want the kthपढ़ो to क्रमget old state.
 *
 * See HOTKEY_CONFIG_CRITICAL_START/HOTKEY_CONFIG_CRITICAL_END
 */
अटल काष्ठा mutex hotkey_thपढ़ो_data_mutex;
अटल अचिन्हित पूर्णांक hotkey_config_change;

/*
 * hotkey poller control variables
 *
 * Must be atomic or पढ़ोers will also need to acquire mutex
 *
 * HOTKEY_CONFIG_CRITICAL_START/HOTKEY_CONFIG_CRITICAL_END
 * should be used only when the changes need to be taken as
 * a block, OR when one needs to क्रमce the kthपढ़ो to क्रमget
 * old state.
 */
अटल u32 hotkey_source_mask;		/* bit mask 0=ACPI,1=NVRAM */
अटल अचिन्हित पूर्णांक hotkey_poll_freq = 10; /* Hz */

#घोषणा HOTKEY_CONFIG_CRITICAL_START \
	करो अणु \
		mutex_lock(&hotkey_thपढ़ो_data_mutex); \
		hotkey_config_change++; \
	पूर्ण जबतक (0);
#घोषणा HOTKEY_CONFIG_CRITICAL_END \
	mutex_unlock(&hotkey_thपढ़ो_data_mutex);

#अन्यथा /* CONFIG_THINKPAD_ACPI_HOTKEY_POLL */

#घोषणा hotkey_source_mask 0U
#घोषणा HOTKEY_CONFIG_CRITICAL_START
#घोषणा HOTKEY_CONFIG_CRITICAL_END

#पूर्ण_अगर /* CONFIG_THINKPAD_ACPI_HOTKEY_POLL */

अटल काष्ठा mutex hotkey_mutex;

अटल क्रमागत अणु	/* Reasons क्रम waking up */
	TP_ACPI_WAKEUP_NONE = 0,	/* None or unknown */
	TP_ACPI_WAKEUP_BAYEJ,		/* Bay ejection request */
	TP_ACPI_WAKEUP_UNDOCK,		/* Unकरोck request */
पूर्ण hotkey_wakeup_reason;

अटल पूर्णांक hotkey_स्वतःsleep_ack;

अटल u32 hotkey_orig_mask;		/* events the BIOS had enabled */
अटल u32 hotkey_all_mask;		/* all events supported in fw */
अटल u32 hotkey_adaptive_all_mask;	/* all adaptive events supported in fw */
अटल u32 hotkey_reserved_mask;	/* events better left disabled */
अटल u32 hotkey_driver_mask;		/* events needed by the driver */
अटल u32 hotkey_user_mask;		/* events visible to userspace */
अटल u32 hotkey_acpi_mask;		/* events enabled in firmware */

अटल u16 *hotkey_keycode_map;

अटल काष्ठा attribute_set *hotkey_dev_attributes;

अटल व्योम tpacpi_driver_event(स्थिर अचिन्हित पूर्णांक hkey_event);
अटल व्योम hotkey_driver_event(स्थिर अचिन्हित पूर्णांक scancode);
अटल व्योम hotkey_poll_setup(स्थिर bool may_warn);

/* HKEY.MHKG() वापस bits */
#घोषणा TP_HOTKEY_TABLET_MASK (1 << 3)
क्रमागत अणु
	TP_ACPI_MULTI_MODE_INVALID	= 0,
	TP_ACPI_MULTI_MODE_UNKNOWN	= 1 << 0,
	TP_ACPI_MULTI_MODE_LAPTOP	= 1 << 1,
	TP_ACPI_MULTI_MODE_TABLET	= 1 << 2,
	TP_ACPI_MULTI_MODE_FLAT		= 1 << 3,
	TP_ACPI_MULTI_MODE_STAND	= 1 << 4,
	TP_ACPI_MULTI_MODE_TENT		= 1 << 5,
	TP_ACPI_MULTI_MODE_STAND_TENT	= 1 << 6,
पूर्ण;

क्रमागत अणु
	/* The following modes are considered tablet mode क्रम the purpose of
	 * reporting the status to userspace. i.e. in all these modes it makes
	 * sense to disable the laptop input devices such as touchpad and
	 * keyboard.
	 */
	TP_ACPI_MULTI_MODE_TABLET_LIKE	= TP_ACPI_MULTI_MODE_TABLET |
					  TP_ACPI_MULTI_MODE_STAND |
					  TP_ACPI_MULTI_MODE_TENT |
					  TP_ACPI_MULTI_MODE_STAND_TENT,
पूर्ण;

अटल पूर्णांक hotkey_get_wlsw(व्योम)
अणु
	पूर्णांक status;

	अगर (!tp_features.hotkey_wlsw)
		वापस -ENODEV;

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	अगर (dbg_wlswemul)
		वापस (tpacpi_wlsw_emulstate) ?
				TPACPI_RFK_RADIO_ON : TPACPI_RFK_RADIO_OFF;
#पूर्ण_अगर

	अगर (!acpi_evalf(hkey_handle, &status, "WLSW", "d"))
		वापस -EIO;

	वापस (status) ? TPACPI_RFK_RADIO_ON : TPACPI_RFK_RADIO_OFF;
पूर्ण

अटल पूर्णांक hotkey_gmms_get_tablet_mode(पूर्णांक s, पूर्णांक *has_tablet_mode)
अणु
	पूर्णांक type = (s >> 16) & 0xffff;
	पूर्णांक value = s & 0xffff;
	पूर्णांक mode = TP_ACPI_MULTI_MODE_INVALID;
	पूर्णांक valid_modes = 0;

	अगर (has_tablet_mode)
		*has_tablet_mode = 0;

	चयन (type) अणु
	हाल 1:
		valid_modes = TP_ACPI_MULTI_MODE_LAPTOP |
			      TP_ACPI_MULTI_MODE_TABLET |
			      TP_ACPI_MULTI_MODE_STAND_TENT;
		अवरोध;
	हाल 2:
		valid_modes = TP_ACPI_MULTI_MODE_LAPTOP |
			      TP_ACPI_MULTI_MODE_FLAT |
			      TP_ACPI_MULTI_MODE_TABLET |
			      TP_ACPI_MULTI_MODE_STAND |
			      TP_ACPI_MULTI_MODE_TENT;
		अवरोध;
	हाल 3:
		valid_modes = TP_ACPI_MULTI_MODE_LAPTOP |
			      TP_ACPI_MULTI_MODE_FLAT;
		अवरोध;
	हाल 4:
	हाल 5:
		/* In mode 4, FLAT is not specअगरied as a valid mode. However,
		 * it can be seen at least on the X1 Yoga 2nd Generation.
		 */
		valid_modes = TP_ACPI_MULTI_MODE_LAPTOP |
			      TP_ACPI_MULTI_MODE_FLAT |
			      TP_ACPI_MULTI_MODE_TABLET |
			      TP_ACPI_MULTI_MODE_STAND |
			      TP_ACPI_MULTI_MODE_TENT;
		अवरोध;
	शेष:
		pr_err("Unknown multi mode status type %d with value 0x%04X, please report this to %s\n",
		       type, value, TPACPI_MAIL);
		वापस 0;
	पूर्ण

	अगर (has_tablet_mode && (valid_modes & TP_ACPI_MULTI_MODE_TABLET_LIKE))
		*has_tablet_mode = 1;

	चयन (value) अणु
	हाल 1:
		mode = TP_ACPI_MULTI_MODE_LAPTOP;
		अवरोध;
	हाल 2:
		mode = TP_ACPI_MULTI_MODE_FLAT;
		अवरोध;
	हाल 3:
		mode = TP_ACPI_MULTI_MODE_TABLET;
		अवरोध;
	हाल 4:
		अगर (type == 1)
			mode = TP_ACPI_MULTI_MODE_STAND_TENT;
		अन्यथा
			mode = TP_ACPI_MULTI_MODE_STAND;
		अवरोध;
	हाल 5:
		mode = TP_ACPI_MULTI_MODE_TENT;
		अवरोध;
	शेष:
		अगर (type == 5 && value == 0xffff) अणु
			pr_warn("Multi mode status is undetected, assuming laptop\n");
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (!(mode & valid_modes)) अणु
		pr_err("Unknown/reserved multi mode value 0x%04X for type %d, please report this to %s\n",
		       value, type, TPACPI_MAIL);
		वापस 0;
	पूर्ण

	वापस !!(mode & TP_ACPI_MULTI_MODE_TABLET_LIKE);
पूर्ण

अटल पूर्णांक hotkey_get_tablet_mode(पूर्णांक *status)
अणु
	पूर्णांक s;

	चयन (tp_features.hotkey_tablet) अणु
	हाल TP_HOTKEY_TABLET_USES_MHKG:
		अगर (!acpi_evalf(hkey_handle, &s, "MHKG", "d"))
			वापस -EIO;

		*status = ((s & TP_HOTKEY_TABLET_MASK) != 0);
		अवरोध;
	हाल TP_HOTKEY_TABLET_USES_GMMS:
		अगर (!acpi_evalf(hkey_handle, &s, "GMMS", "dd", 0))
			वापस -EIO;

		*status = hotkey_gmms_get_tablet_mode(s, शून्य);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Reads current event mask from firmware, and updates
 * hotkey_acpi_mask accordingly.  Also resets any bits
 * from hotkey_user_mask that are unavailable to be
 * delivered (shaकरोw requirement of the userspace ABI).
 *
 * Call with hotkey_mutex held
 */
अटल पूर्णांक hotkey_mask_get(व्योम)
अणु
	अगर (tp_features.hotkey_mask) अणु
		u32 m = 0;

		अगर (!acpi_evalf(hkey_handle, &m, "DHKN", "d"))
			वापस -EIO;

		hotkey_acpi_mask = m;
	पूर्ण अन्यथा अणु
		/* no mask support करोesn't mean no event support... */
		hotkey_acpi_mask = hotkey_all_mask;
	पूर्ण

	/* sync userspace-visible mask */
	hotkey_user_mask &= (hotkey_acpi_mask | hotkey_source_mask);

	वापस 0;
पूर्ण

अटल व्योम hotkey_mask_warn_incomplete_mask(व्योम)
अणु
	/* log only what the user can fix... */
	स्थिर u32 wantedmask = hotkey_driver_mask &
		~(hotkey_acpi_mask | hotkey_source_mask) &
		(hotkey_all_mask | TPACPI_HKEY_NVRAM_KNOWN_MASK);

	अगर (wantedmask)
		pr_notice("required events 0x%08x not enabled!\n", wantedmask);
पूर्ण

/*
 * Set the firmware mask when supported
 *
 * Also calls hotkey_mask_get to update hotkey_acpi_mask.
 *
 * NOTE: करोes not set bits in hotkey_user_mask, but may reset them.
 *
 * Call with hotkey_mutex held
 */
अटल पूर्णांक hotkey_mask_set(u32 mask)
अणु
	पूर्णांक i;
	पूर्णांक rc = 0;

	स्थिर u32 fwmask = mask & ~hotkey_source_mask;

	अगर (tp_features.hotkey_mask) अणु
		क्रम (i = 0; i < 32; i++) अणु
			अगर (!acpi_evalf(hkey_handle,
					शून्य, "MHKM", "vdd", i + 1,
					!!(mask & (1 << i)))) अणु
				rc = -EIO;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * We *must* make an inconditional call to hotkey_mask_get to
	 * refresh hotkey_acpi_mask and update hotkey_user_mask
	 *
	 * Take the opportunity to also log when we cannot _enable_
	 * a given event.
	 */
	अगर (!hotkey_mask_get() && !rc && (fwmask & ~hotkey_acpi_mask)) अणु
		pr_notice("asked for hotkey mask 0x%08x, but firmware forced it to 0x%08x\n",
			  fwmask, hotkey_acpi_mask);
	पूर्ण

	अगर (tpacpi_lअगरecycle != TPACPI_LIFE_EXITING)
		hotkey_mask_warn_incomplete_mask();

	वापस rc;
पूर्ण

/*
 * Sets hotkey_user_mask and tries to set the firmware mask
 *
 * Call with hotkey_mutex held
 */
अटल पूर्णांक hotkey_user_mask_set(स्थिर u32 mask)
अणु
	पूर्णांक rc;

	/* Give people a chance to notice they are करोing something that
	 * is bound to go boom on their users sooner or later */
	अगर (!tp_warned.hotkey_mask_ff &&
	    (mask == 0xffff || mask == 0xffffff ||
	     mask == 0xffffffff)) अणु
		tp_warned.hotkey_mask_ff = 1;
		pr_notice("setting the hotkey mask to 0x%08x is likely not the best way to go about it\n",
			  mask);
		pr_notice("please consider using the driver defaults, and refer to up-to-date thinkpad-acpi documentation\n");
	पूर्ण

	/* Try to enable what the user asked क्रम, plus whatever we need.
	 * this syncs everything but won't enable bits in hotkey_user_mask */
	rc = hotkey_mask_set((mask | hotkey_driver_mask) & ~hotkey_source_mask);

	/* Enable the available bits in hotkey_user_mask */
	hotkey_user_mask = mask & (hotkey_acpi_mask | hotkey_source_mask);

	वापस rc;
पूर्ण

/*
 * Sets the driver hotkey mask.
 *
 * Can be called even अगर the hotkey subdriver is inactive
 */
अटल पूर्णांक tpacpi_hotkey_driver_mask_set(स्थिर u32 mask)
अणु
	पूर्णांक rc;

	/* Do the right thing अगर hotkey_init has not been called yet */
	अगर (!tp_features.hotkey) अणु
		hotkey_driver_mask = mask;
		वापस 0;
	पूर्ण

	mutex_lock(&hotkey_mutex);

	HOTKEY_CONFIG_CRITICAL_START
	hotkey_driver_mask = mask;
#अगर_घोषित CONFIG_THINKPAD_ACPI_HOTKEY_POLL
	hotkey_source_mask |= (mask & ~hotkey_all_mask);
#पूर्ण_अगर
	HOTKEY_CONFIG_CRITICAL_END

	rc = hotkey_mask_set((hotkey_acpi_mask | hotkey_driver_mask) &
							~hotkey_source_mask);
	hotkey_poll_setup(true);

	mutex_unlock(&hotkey_mutex);

	वापस rc;
पूर्ण

अटल पूर्णांक hotkey_status_get(पूर्णांक *status)
अणु
	अगर (!acpi_evalf(hkey_handle, status, "DHKC", "d"))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक hotkey_status_set(bool enable)
अणु
	अगर (!acpi_evalf(hkey_handle, शून्य, "MHKC", "vd", enable ? 1 : 0))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम tpacpi_input_send_tabletsw(व्योम)
अणु
	पूर्णांक state;

	अगर (tp_features.hotkey_tablet &&
	    !hotkey_get_tablet_mode(&state)) अणु
		mutex_lock(&tpacpi_inputdev_send_mutex);

		input_report_चयन(tpacpi_inputdev,
				    SW_TABLET_MODE, !!state);
		input_sync(tpacpi_inputdev);

		mutex_unlock(&tpacpi_inputdev_send_mutex);
	पूर्ण
पूर्ण

/* Do NOT call without validating scancode first */
अटल व्योम tpacpi_input_send_key(स्थिर अचिन्हित पूर्णांक scancode)
अणु
	स्थिर अचिन्हित पूर्णांक keycode = hotkey_keycode_map[scancode];

	अगर (keycode != KEY_RESERVED) अणु
		mutex_lock(&tpacpi_inputdev_send_mutex);

		input_event(tpacpi_inputdev, EV_MSC, MSC_SCAN, scancode);
		input_report_key(tpacpi_inputdev, keycode, 1);
		input_sync(tpacpi_inputdev);

		input_event(tpacpi_inputdev, EV_MSC, MSC_SCAN, scancode);
		input_report_key(tpacpi_inputdev, keycode, 0);
		input_sync(tpacpi_inputdev);

		mutex_unlock(&tpacpi_inputdev_send_mutex);
	पूर्ण
पूर्ण

/* Do NOT call without validating scancode first */
अटल व्योम tpacpi_input_send_key_masked(स्थिर अचिन्हित पूर्णांक scancode)
अणु
	hotkey_driver_event(scancode);
	अगर (hotkey_user_mask & (1 << scancode))
		tpacpi_input_send_key(scancode);
पूर्ण

#अगर_घोषित CONFIG_THINKPAD_ACPI_HOTKEY_POLL
अटल काष्ठा tp_acpi_drv_काष्ठा ibm_hotkey_acpidriver;

/* Do NOT call without validating scancode first */
अटल व्योम tpacpi_hotkey_send_key(अचिन्हित पूर्णांक scancode)
अणु
	tpacpi_input_send_key_masked(scancode);
पूर्ण

अटल व्योम hotkey_पढ़ो_nvram(काष्ठा tp_nvram_state *n, स्थिर u32 m)
अणु
	u8 d;

	अगर (m & TP_NVRAM_HKEY_GROUP_HK2) अणु
		d = nvram_पढ़ो_byte(TP_NVRAM_ADDR_HK2);
		n->thinkpad_toggle = !!(d & TP_NVRAM_MASK_HKT_THINKPAD);
		n->zoom_toggle = !!(d & TP_NVRAM_MASK_HKT_ZOOM);
		n->display_toggle = !!(d & TP_NVRAM_MASK_HKT_DISPLAY);
		n->hibernate_toggle = !!(d & TP_NVRAM_MASK_HKT_HIBERNATE);
	पूर्ण
	अगर (m & TP_ACPI_HKEY_KBD_LIGHT_MASK) अणु
		d = nvram_पढ़ो_byte(TP_NVRAM_ADDR_THINKLIGHT);
		n->thinklight_toggle = !!(d & TP_NVRAM_MASK_THINKLIGHT);
	पूर्ण
	अगर (m & TP_ACPI_HKEY_DISPXPAND_MASK) अणु
		d = nvram_पढ़ो_byte(TP_NVRAM_ADDR_VIDEO);
		n->displayexp_toggle =
				!!(d & TP_NVRAM_MASK_HKT_DISPEXPND);
	पूर्ण
	अगर (m & TP_NVRAM_HKEY_GROUP_BRIGHTNESS) अणु
		d = nvram_पढ़ो_byte(TP_NVRAM_ADDR_BRIGHTNESS);
		n->brightness_level = (d & TP_NVRAM_MASK_LEVEL_BRIGHTNESS)
				>> TP_NVRAM_POS_LEVEL_BRIGHTNESS;
		n->brightness_toggle =
				!!(d & TP_NVRAM_MASK_HKT_BRIGHTNESS);
	पूर्ण
	अगर (m & TP_NVRAM_HKEY_GROUP_VOLUME) अणु
		d = nvram_पढ़ो_byte(TP_NVRAM_ADDR_MIXER);
		n->volume_level = (d & TP_NVRAM_MASK_LEVEL_VOLUME)
				>> TP_NVRAM_POS_LEVEL_VOLUME;
		n->mute = !!(d & TP_NVRAM_MASK_MUTE);
		n->volume_toggle = !!(d & TP_NVRAM_MASK_HKT_VOLUME);
	पूर्ण
पूर्ण

#घोषणा TPACPI_COMPARE_KEY(__scancode, __member) \
करो अणु \
	अगर ((event_mask & (1 << __scancode)) && \
	    oldn->__member != newn->__member) \
		tpacpi_hotkey_send_key(__scancode); \
पूर्ण जबतक (0)

#घोषणा TPACPI_MAY_SEND_KEY(__scancode) \
करो अणु \
	अगर (event_mask & (1 << __scancode)) \
		tpacpi_hotkey_send_key(__scancode); \
पूर्ण जबतक (0)

अटल व्योम issue_volchange(स्थिर अचिन्हित पूर्णांक oldvol,
			    स्थिर अचिन्हित पूर्णांक newvol,
			    स्थिर u32 event_mask)
अणु
	अचिन्हित पूर्णांक i = oldvol;

	जबतक (i > newvol) अणु
		TPACPI_MAY_SEND_KEY(TP_ACPI_HOTKEYSCAN_VOLUMEDOWN);
		i--;
	पूर्ण
	जबतक (i < newvol) अणु
		TPACPI_MAY_SEND_KEY(TP_ACPI_HOTKEYSCAN_VOLUMEUP);
		i++;
	पूर्ण
पूर्ण

अटल व्योम issue_brightnesschange(स्थिर अचिन्हित पूर्णांक oldbrt,
				   स्थिर अचिन्हित पूर्णांक newbrt,
				   स्थिर u32 event_mask)
अणु
	अचिन्हित पूर्णांक i = oldbrt;

	जबतक (i > newbrt) अणु
		TPACPI_MAY_SEND_KEY(TP_ACPI_HOTKEYSCAN_FNEND);
		i--;
	पूर्ण
	जबतक (i < newbrt) अणु
		TPACPI_MAY_SEND_KEY(TP_ACPI_HOTKEYSCAN_FNHOME);
		i++;
	पूर्ण
पूर्ण

अटल व्योम hotkey_compare_and_issue_event(काष्ठा tp_nvram_state *oldn,
					   काष्ठा tp_nvram_state *newn,
					   स्थिर u32 event_mask)
अणु

	TPACPI_COMPARE_KEY(TP_ACPI_HOTKEYSCAN_THINKPAD, thinkpad_toggle);
	TPACPI_COMPARE_KEY(TP_ACPI_HOTKEYSCAN_FNSPACE, zoom_toggle);
	TPACPI_COMPARE_KEY(TP_ACPI_HOTKEYSCAN_FNF7, display_toggle);
	TPACPI_COMPARE_KEY(TP_ACPI_HOTKEYSCAN_FNF12, hibernate_toggle);

	TPACPI_COMPARE_KEY(TP_ACPI_HOTKEYSCAN_FNPAGEUP, thinklight_toggle);

	TPACPI_COMPARE_KEY(TP_ACPI_HOTKEYSCAN_FNF8, displayexp_toggle);

	/*
	 * Handle volume
	 *
	 * This code is supposed to duplicate the IBM firmware behaviour:
	 * - Pressing MUTE issues mute hotkey message, even when alपढ़ोy mute
	 * - Pressing Volume up/करोwn issues volume up/करोwn hotkey messages,
	 *   even when alपढ़ोy at maximum or minimum volume
	 * - The act of unmuting issues volume up/करोwn notअगरication,
	 *   depending which key was used to unmute
	 *
	 * We are स्थिरrained to what the NVRAM can tell us, which is not much
	 * and certainly not enough अगर more than one volume hotkey was pressed
	 * since the last poll cycle.
	 *
	 * Just to make our lअगरe पूर्णांकeresting, some newer Lenovo ThinkPads have
	 * bugs in the BIOS and may fail to update volume_toggle properly.
	 */
	अगर (newn->mute) अणु
		/* muted */
		अगर (!oldn->mute ||
		    oldn->volume_toggle != newn->volume_toggle ||
		    oldn->volume_level != newn->volume_level) अणु
			/* recently muted, or repeated mute keypress, or
			 * multiple presses ending in mute */
			issue_volchange(oldn->volume_level, newn->volume_level,
				event_mask);
			TPACPI_MAY_SEND_KEY(TP_ACPI_HOTKEYSCAN_MUTE);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* unmute */
		अगर (oldn->mute) अणु
			/* recently unmuted, issue 'unmute' keypress */
			TPACPI_MAY_SEND_KEY(TP_ACPI_HOTKEYSCAN_VOLUMEUP);
		पूर्ण
		अगर (oldn->volume_level != newn->volume_level) अणु
			issue_volchange(oldn->volume_level, newn->volume_level,
				event_mask);
		पूर्ण अन्यथा अगर (oldn->volume_toggle != newn->volume_toggle) अणु
			/* repeated vol up/करोwn keypress at end of scale ? */
			अगर (newn->volume_level == 0)
				TPACPI_MAY_SEND_KEY(TP_ACPI_HOTKEYSCAN_VOLUMEDOWN);
			अन्यथा अगर (newn->volume_level >= TP_NVRAM_LEVEL_VOLUME_MAX)
				TPACPI_MAY_SEND_KEY(TP_ACPI_HOTKEYSCAN_VOLUMEUP);
		पूर्ण
	पूर्ण

	/* handle brightness */
	अगर (oldn->brightness_level != newn->brightness_level) अणु
		issue_brightnesschange(oldn->brightness_level,
				       newn->brightness_level, event_mask);
	पूर्ण अन्यथा अगर (oldn->brightness_toggle != newn->brightness_toggle) अणु
		/* repeated key presses that didn't change state */
		अगर (newn->brightness_level == 0)
			TPACPI_MAY_SEND_KEY(TP_ACPI_HOTKEYSCAN_FNEND);
		अन्यथा अगर (newn->brightness_level >= bright_maxlvl
				&& !tp_features.bright_unkfw)
			TPACPI_MAY_SEND_KEY(TP_ACPI_HOTKEYSCAN_FNHOME);
	पूर्ण

#अघोषित TPACPI_COMPARE_KEY
#अघोषित TPACPI_MAY_SEND_KEY
पूर्ण

/*
 * Polling driver
 *
 * We track all events in hotkey_source_mask all the समय, since
 * most of them are edge-based.  We only issue those requested by
 * hotkey_user_mask or hotkey_driver_mask, though.
 */
अटल पूर्णांक hotkey_kthपढ़ो(व्योम *data)
अणु
	काष्ठा tp_nvram_state s[2] = अणु 0 पूर्ण;
	u32 poll_mask, event_mask;
	अचिन्हित पूर्णांक si, so;
	अचिन्हित दीर्घ t;
	अचिन्हित पूर्णांक change_detector;
	अचिन्हित पूर्णांक poll_freq;
	bool was_frozen;

	अगर (tpacpi_lअगरecycle == TPACPI_LIFE_EXITING)
		जाओ निकास;

	set_मुक्तzable();

	so = 0;
	si = 1;
	t = 0;

	/* Initial state क्रम compares */
	mutex_lock(&hotkey_thपढ़ो_data_mutex);
	change_detector = hotkey_config_change;
	poll_mask = hotkey_source_mask;
	event_mask = hotkey_source_mask &
			(hotkey_driver_mask | hotkey_user_mask);
	poll_freq = hotkey_poll_freq;
	mutex_unlock(&hotkey_thपढ़ो_data_mutex);
	hotkey_पढ़ो_nvram(&s[so], poll_mask);

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (t == 0) अणु
			अगर (likely(poll_freq))
				t = 1000/poll_freq;
			अन्यथा
				t = 100;	/* should never happen... */
		पूर्ण
		t = msleep_पूर्णांकerruptible(t);
		अगर (unlikely(kthपढ़ो_मुक्तzable_should_stop(&was_frozen)))
			अवरोध;

		अगर (t > 0 && !was_frozen)
			जारी;

		mutex_lock(&hotkey_thपढ़ो_data_mutex);
		अगर (was_frozen || hotkey_config_change != change_detector) अणु
			/* क्रमget old state on thaw or config change */
			si = so;
			t = 0;
			change_detector = hotkey_config_change;
		पूर्ण
		poll_mask = hotkey_source_mask;
		event_mask = hotkey_source_mask &
				(hotkey_driver_mask | hotkey_user_mask);
		poll_freq = hotkey_poll_freq;
		mutex_unlock(&hotkey_thपढ़ो_data_mutex);

		अगर (likely(poll_mask)) अणु
			hotkey_पढ़ो_nvram(&s[si], poll_mask);
			अगर (likely(si != so)) अणु
				hotkey_compare_and_issue_event(&s[so], &s[si],
								event_mask);
			पूर्ण
		पूर्ण

		so = si;
		si ^= 1;
	पूर्ण

निकास:
	वापस 0;
पूर्ण

/* call with hotkey_mutex held */
अटल व्योम hotkey_poll_stop_sync(व्योम)
अणु
	अगर (tpacpi_hotkey_task) अणु
		kthपढ़ो_stop(tpacpi_hotkey_task);
		tpacpi_hotkey_task = शून्य;
	पूर्ण
पूर्ण

/* call with hotkey_mutex held */
अटल व्योम hotkey_poll_setup(स्थिर bool may_warn)
अणु
	स्थिर u32 poll_driver_mask = hotkey_driver_mask & hotkey_source_mask;
	स्थिर u32 poll_user_mask = hotkey_user_mask & hotkey_source_mask;

	अगर (hotkey_poll_freq > 0 &&
	    (poll_driver_mask ||
	     (poll_user_mask && tpacpi_inputdev->users > 0))) अणु
		अगर (!tpacpi_hotkey_task) अणु
			tpacpi_hotkey_task = kthपढ़ो_run(hotkey_kthपढ़ो,
					शून्य, TPACPI_NVRAM_KTHREAD_NAME);
			अगर (IS_ERR(tpacpi_hotkey_task)) अणु
				tpacpi_hotkey_task = शून्य;
				pr_err("could not create kernel thread for hotkey polling\n");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		hotkey_poll_stop_sync();
		अगर (may_warn && (poll_driver_mask || poll_user_mask) &&
		    hotkey_poll_freq == 0) अणु
			pr_notice("hot keys 0x%08x and/or events 0x%08x require polling, which is currently disabled\n",
				  poll_user_mask, poll_driver_mask);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hotkey_poll_setup_safe(स्थिर bool may_warn)
अणु
	mutex_lock(&hotkey_mutex);
	hotkey_poll_setup(may_warn);
	mutex_unlock(&hotkey_mutex);
पूर्ण

/* call with hotkey_mutex held */
अटल व्योम hotkey_poll_set_freq(अचिन्हित पूर्णांक freq)
अणु
	अगर (!freq)
		hotkey_poll_stop_sync();

	hotkey_poll_freq = freq;
पूर्ण

#अन्यथा /* CONFIG_THINKPAD_ACPI_HOTKEY_POLL */

अटल व्योम hotkey_poll_setup(स्थिर bool __unused)
अणु
पूर्ण

अटल व्योम hotkey_poll_setup_safe(स्थिर bool __unused)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_THINKPAD_ACPI_HOTKEY_POLL */

अटल पूर्णांक hotkey_inputdev_खोलो(काष्ठा input_dev *dev)
अणु
	चयन (tpacpi_lअगरecycle) अणु
	हाल TPACPI_LIFE_INIT:
	हाल TPACPI_LIFE_RUNNING:
		hotkey_poll_setup_safe(false);
		वापस 0;
	हाल TPACPI_LIFE_EXITING:
		वापस -EBUSY;
	पूर्ण

	/* Should only happen अगर tpacpi_lअगरecycle is corrupt */
	BUG();
	वापस -EBUSY;
पूर्ण

अटल व्योम hotkey_inputdev_बंद(काष्ठा input_dev *dev)
अणु
	/* disable hotkey polling when possible */
	अगर (tpacpi_lअगरecycle != TPACPI_LIFE_EXITING &&
	    !(hotkey_source_mask & hotkey_driver_mask))
		hotkey_poll_setup_safe(false);
पूर्ण

/* sysfs hotkey enable ------------------------------------------------- */
अटल sमाप_प्रकार hotkey_enable_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक res, status;

	prपूर्णांकk_deprecated_attribute("hotkey_enable",
			"Hotkey reporting is always enabled");

	res = hotkey_status_get(&status);
	अगर (res)
		वापस res;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", status);
पूर्ण

अटल sमाप_प्रकार hotkey_enable_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;

	prपूर्णांकk_deprecated_attribute("hotkey_enable",
			"Hotkeys can be disabled through hotkey_mask");

	अगर (parse_म_से_अदीर्घ(buf, 1, &t))
		वापस -EINVAL;

	अगर (t == 0)
		वापस -EPERM;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(hotkey_enable);

/* sysfs hotkey mask --------------------------------------------------- */
अटल sमाप_प्रकार hotkey_mask_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%08x\n", hotkey_user_mask);
पूर्ण

अटल sमाप_प्रकार hotkey_mask_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;
	पूर्णांक res;

	अगर (parse_म_से_अदीर्घ(buf, 0xffffffffUL, &t))
		वापस -EINVAL;

	अगर (mutex_lock_समाप्तable(&hotkey_mutex))
		वापस -ERESTARTSYS;

	res = hotkey_user_mask_set(t);

#अगर_घोषित CONFIG_THINKPAD_ACPI_HOTKEY_POLL
	hotkey_poll_setup(true);
#पूर्ण_अगर

	mutex_unlock(&hotkey_mutex);

	tpacpi_disबंद_usertask("hotkey_mask", "set to 0x%08lx\n", t);

	वापस (res) ? res : count;
पूर्ण

अटल DEVICE_ATTR_RW(hotkey_mask);

/* sysfs hotkey bios_enabled ------------------------------------------- */
अटल sमाप_प्रकार hotkey_bios_enabled_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल DEVICE_ATTR_RO(hotkey_bios_enabled);

/* sysfs hotkey bios_mask ---------------------------------------------- */
अटल sमाप_प्रकार hotkey_bios_mask_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	prपूर्णांकk_deprecated_attribute("hotkey_bios_mask",
			"This attribute is useless.");
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%08x\n", hotkey_orig_mask);
पूर्ण

अटल DEVICE_ATTR_RO(hotkey_bios_mask);

/* sysfs hotkey all_mask ----------------------------------------------- */
अटल sमाप_प्रकार hotkey_all_mask_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%08x\n",
				hotkey_all_mask | hotkey_source_mask);
पूर्ण

अटल DEVICE_ATTR_RO(hotkey_all_mask);

/* sysfs hotkey all_mask ----------------------------------------------- */
अटल sमाप_प्रकार hotkey_adaptive_all_mask_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%08x\n",
			hotkey_adaptive_all_mask | hotkey_source_mask);
पूर्ण

अटल DEVICE_ATTR_RO(hotkey_adaptive_all_mask);

/* sysfs hotkey recommended_mask --------------------------------------- */
अटल sमाप_प्रकार hotkey_recommended_mask_show(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%08x\n",
			(hotkey_all_mask | hotkey_source_mask)
			& ~hotkey_reserved_mask);
पूर्ण

अटल DEVICE_ATTR_RO(hotkey_recommended_mask);

#अगर_घोषित CONFIG_THINKPAD_ACPI_HOTKEY_POLL

/* sysfs hotkey hotkey_source_mask ------------------------------------- */
अटल sमाप_प्रकार hotkey_source_mask_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%08x\n", hotkey_source_mask);
पूर्ण

अटल sमाप_प्रकार hotkey_source_mask_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;
	u32 r_ev;
	पूर्णांक rc;

	अगर (parse_म_से_अदीर्घ(buf, 0xffffffffUL, &t) ||
		((t & ~TPACPI_HKEY_NVRAM_KNOWN_MASK) != 0))
		वापस -EINVAL;

	अगर (mutex_lock_समाप्तable(&hotkey_mutex))
		वापस -ERESTARTSYS;

	HOTKEY_CONFIG_CRITICAL_START
	hotkey_source_mask = t;
	HOTKEY_CONFIG_CRITICAL_END

	rc = hotkey_mask_set((hotkey_user_mask | hotkey_driver_mask) &
			~hotkey_source_mask);
	hotkey_poll_setup(true);

	/* check अगर events needed by the driver got disabled */
	r_ev = hotkey_driver_mask & ~(hotkey_acpi_mask & hotkey_all_mask)
		& ~hotkey_source_mask & TPACPI_HKEY_NVRAM_KNOWN_MASK;

	mutex_unlock(&hotkey_mutex);

	अगर (rc < 0)
		pr_err("hotkey_source_mask: failed to update the firmware event mask!\n");

	अगर (r_ev)
		pr_notice("hotkey_source_mask: some important events were disabled: 0x%04x\n",
			  r_ev);

	tpacpi_disबंद_usertask("hotkey_source_mask", "set to 0x%08lx\n", t);

	वापस (rc < 0) ? rc : count;
पूर्ण

अटल DEVICE_ATTR_RW(hotkey_source_mask);

/* sysfs hotkey hotkey_poll_freq --------------------------------------- */
अटल sमाप_प्रकार hotkey_poll_freq_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", hotkey_poll_freq);
पूर्ण

अटल sमाप_प्रकार hotkey_poll_freq_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;

	अगर (parse_म_से_अदीर्घ(buf, 25, &t))
		वापस -EINVAL;

	अगर (mutex_lock_समाप्तable(&hotkey_mutex))
		वापस -ERESTARTSYS;

	hotkey_poll_set_freq(t);
	hotkey_poll_setup(true);

	mutex_unlock(&hotkey_mutex);

	tpacpi_disबंद_usertask("hotkey_poll_freq", "set to %lu\n", t);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(hotkey_poll_freq);

#पूर्ण_अगर /* CONFIG_THINKPAD_ACPI_HOTKEY_POLL */

/* sysfs hotkey radio_sw (pollable) ------------------------------------ */
अटल sमाप_प्रकार hotkey_radio_sw_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक res;
	res = hotkey_get_wlsw();
	अगर (res < 0)
		वापस res;

	/* Opportunistic update */
	tpacpi_rfk_update_hwblock_state((res == TPACPI_RFK_RADIO_OFF));

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			(res == TPACPI_RFK_RADIO_OFF) ? 0 : 1);
पूर्ण

अटल DEVICE_ATTR_RO(hotkey_radio_sw);

अटल व्योम hotkey_radio_sw_notअगरy_change(व्योम)
अणु
	अगर (tp_features.hotkey_wlsw)
		sysfs_notअगरy(&tpacpi_pdev->dev.kobj, शून्य,
			     "hotkey_radio_sw");
पूर्ण

/* sysfs hotkey tablet mode (pollable) --------------------------------- */
अटल sमाप_प्रकार hotkey_tablet_mode_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक res, s;
	res = hotkey_get_tablet_mode(&s);
	अगर (res < 0)
		वापस res;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", !!s);
पूर्ण

अटल DEVICE_ATTR_RO(hotkey_tablet_mode);

अटल व्योम hotkey_tablet_mode_notअगरy_change(व्योम)
अणु
	अगर (tp_features.hotkey_tablet)
		sysfs_notअगरy(&tpacpi_pdev->dev.kobj, शून्य,
			     "hotkey_tablet_mode");
पूर्ण

/* sysfs wakeup reason (pollable) -------------------------------------- */
अटल sमाप_प्रकार hotkey_wakeup_reason_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", hotkey_wakeup_reason);
पूर्ण

अटल DEVICE_ATTR(wakeup_reason, S_IRUGO, hotkey_wakeup_reason_show, शून्य);

अटल व्योम hotkey_wakeup_reason_notअगरy_change(व्योम)
अणु
	sysfs_notअगरy(&tpacpi_pdev->dev.kobj, शून्य,
		     "wakeup_reason");
पूर्ण

/* sysfs wakeup hotunplug_complete (pollable) -------------------------- */
अटल sमाप_प्रकार hotkey_wakeup_hotunplug_complete_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", hotkey_स्वतःsleep_ack);
पूर्ण

अटल DEVICE_ATTR(wakeup_hotunplug_complete, S_IRUGO,
		   hotkey_wakeup_hotunplug_complete_show, शून्य);

अटल व्योम hotkey_wakeup_hotunplug_complete_notअगरy_change(व्योम)
अणु
	sysfs_notअगरy(&tpacpi_pdev->dev.kobj, शून्य,
		     "wakeup_hotunplug_complete");
पूर्ण

/* sysfs adaptive kbd mode --------------------------------------------- */

अटल पूर्णांक adaptive_keyboard_get_mode(व्योम);
अटल पूर्णांक adaptive_keyboard_set_mode(पूर्णांक new_mode);

क्रमागत ADAPTIVE_KEY_MODE अणु
	HOME_MODE,
	WEB_BROWSER_MODE,
	WEB_CONFERENCE_MODE,
	FUNCTION_MODE,
	LAYFLAT_MODE
पूर्ण;

अटल sमाप_प्रकार adaptive_kbd_mode_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक current_mode;

	current_mode = adaptive_keyboard_get_mode();
	अगर (current_mode < 0)
		वापस current_mode;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", current_mode);
पूर्ण

अटल sमाप_प्रकार adaptive_kbd_mode_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;
	पूर्णांक res;

	अगर (parse_म_से_अदीर्घ(buf, LAYFLAT_MODE, &t))
		वापस -EINVAL;

	res = adaptive_keyboard_set_mode(t);
	वापस (res < 0) ? res : count;
पूर्ण

अटल DEVICE_ATTR_RW(adaptive_kbd_mode);

अटल काष्ठा attribute *adaptive_kbd_attributes[] = अणु
	&dev_attr_adaptive_kbd_mode.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adaptive_kbd_attr_group = अणु
	.attrs = adaptive_kbd_attributes,
पूर्ण;

/* --------------------------------------------------------------------- */

अटल काष्ठा attribute *hotkey_attributes[] __initdata = अणु
	&dev_attr_hotkey_enable.attr,
	&dev_attr_hotkey_bios_enabled.attr,
	&dev_attr_hotkey_bios_mask.attr,
	&dev_attr_wakeup_reason.attr,
	&dev_attr_wakeup_hotunplug_complete.attr,
	&dev_attr_hotkey_mask.attr,
	&dev_attr_hotkey_all_mask.attr,
	&dev_attr_hotkey_adaptive_all_mask.attr,
	&dev_attr_hotkey_recommended_mask.attr,
#अगर_घोषित CONFIG_THINKPAD_ACPI_HOTKEY_POLL
	&dev_attr_hotkey_source_mask.attr,
	&dev_attr_hotkey_poll_freq.attr,
#पूर्ण_अगर
पूर्ण;

/*
 * Sync both the hw and sw blocking state of all चयनes
 */
अटल व्योम tpacpi_send_radiosw_update(व्योम)
अणु
	पूर्णांक wlsw;

	/*
	 * We must sync all rfसमाप्त controllers *beक्रमe* issuing any
	 * rfसमाप्त input events, or we will race the rfसमाप्त core input
	 * handler.
	 *
	 * tpacpi_inputdev_send_mutex works as a synchronization poपूर्णांक
	 * क्रम the above.
	 *
	 * We optimize to aव्योम numerous calls to hotkey_get_wlsw.
	 */

	wlsw = hotkey_get_wlsw();

	/* Sync hw blocking state first अगर it is hw-blocked */
	अगर (wlsw == TPACPI_RFK_RADIO_OFF)
		tpacpi_rfk_update_hwblock_state(true);

	/* Sync sw blocking state */
	tpacpi_rfk_update_swstate_all();

	/* Sync hw blocking state last अगर it is hw-unblocked */
	अगर (wlsw == TPACPI_RFK_RADIO_ON)
		tpacpi_rfk_update_hwblock_state(false);

	/* Issue rfसमाप्त input event क्रम WLSW चयन */
	अगर (!(wlsw < 0)) अणु
		mutex_lock(&tpacpi_inputdev_send_mutex);

		input_report_चयन(tpacpi_inputdev,
				    SW_RFKILL_ALL, (wlsw > 0));
		input_sync(tpacpi_inputdev);

		mutex_unlock(&tpacpi_inputdev_send_mutex);
	पूर्ण

	/*
	 * this can be unconditional, as we will poll state again
	 * अगर userspace uses the notअगरy to पढ़ो data
	 */
	hotkey_radio_sw_notअगरy_change();
पूर्ण

अटल व्योम hotkey_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_THINKPAD_ACPI_HOTKEY_POLL
	mutex_lock(&hotkey_mutex);
	hotkey_poll_stop_sync();
	mutex_unlock(&hotkey_mutex);
#पूर्ण_अगर

	अगर (hotkey_dev_attributes)
		delete_attr_set(hotkey_dev_attributes, &tpacpi_pdev->dev.kobj);

	dbg_prपूर्णांकk(TPACPI_DBG_EXIT | TPACPI_DBG_HKEY,
		   "restoring original HKEY status and mask\n");
	/* yes, there is a bitwise or below, we want the
	 * functions to be called even अगर one of them fail */
	अगर (((tp_features.hotkey_mask &&
	      hotkey_mask_set(hotkey_orig_mask)) |
	     hotkey_status_set(false)) != 0)
		pr_err("failed to restore hot key mask to BIOS defaults\n");
पूर्ण

अटल व्योम __init hotkey_unmap(स्थिर अचिन्हित पूर्णांक scancode)
अणु
	अगर (hotkey_keycode_map[scancode] != KEY_RESERVED) अणु
		clear_bit(hotkey_keycode_map[scancode],
			  tpacpi_inputdev->keybit);
		hotkey_keycode_map[scancode] = KEY_RESERVED;
	पूर्ण
पूर्ण

/*
 * HKEY quirks:
 *   TPACPI_HK_Q_INIMASK:	Supports FN+F3,FN+F4,FN+F12
 */

#घोषणा	TPACPI_HK_Q_INIMASK	0x0001

अटल स्थिर काष्ठा tpacpi_quirk tpacpi_hotkey_qtable[] __initस्थिर = अणु
	TPACPI_Q_IBM('I', 'H', TPACPI_HK_Q_INIMASK), /* 600E */
	TPACPI_Q_IBM('I', 'N', TPACPI_HK_Q_INIMASK), /* 600E */
	TPACPI_Q_IBM('I', 'D', TPACPI_HK_Q_INIMASK), /* 770, 770E, 770ED */
	TPACPI_Q_IBM('I', 'W', TPACPI_HK_Q_INIMASK), /* A20m */
	TPACPI_Q_IBM('I', 'V', TPACPI_HK_Q_INIMASK), /* A20p */
	TPACPI_Q_IBM('1', '0', TPACPI_HK_Q_INIMASK), /* A21e, A22e */
	TPACPI_Q_IBM('K', 'U', TPACPI_HK_Q_INIMASK), /* A21e */
	TPACPI_Q_IBM('K', 'X', TPACPI_HK_Q_INIMASK), /* A21m, A22m */
	TPACPI_Q_IBM('K', 'Y', TPACPI_HK_Q_INIMASK), /* A21p, A22p */
	TPACPI_Q_IBM('1', 'B', TPACPI_HK_Q_INIMASK), /* A22e */
	TPACPI_Q_IBM('1', '3', TPACPI_HK_Q_INIMASK), /* A22m */
	TPACPI_Q_IBM('1', 'E', TPACPI_HK_Q_INIMASK), /* A30/p (0) */
	TPACPI_Q_IBM('1', 'C', TPACPI_HK_Q_INIMASK), /* R30 */
	TPACPI_Q_IBM('1', 'F', TPACPI_HK_Q_INIMASK), /* R31 */
	TPACPI_Q_IBM('I', 'Y', TPACPI_HK_Q_INIMASK), /* T20 */
	TPACPI_Q_IBM('K', 'Z', TPACPI_HK_Q_INIMASK), /* T21 */
	TPACPI_Q_IBM('1', '6', TPACPI_HK_Q_INIMASK), /* T22 */
	TPACPI_Q_IBM('I', 'Z', TPACPI_HK_Q_INIMASK), /* X20, X21 */
	TPACPI_Q_IBM('1', 'D', TPACPI_HK_Q_INIMASK), /* X22, X23, X24 */
पूर्ण;

प्रकार u16 tpacpi_keymap_entry_t;
प्रकार tpacpi_keymap_entry_t tpacpi_keymap_t[TPACPI_HOTKEY_MAP_LEN];

अटल पूर्णांक hotkey_init_tablet_mode(व्योम)
अणु
	पूर्णांक in_tablet_mode = 0, res;
	अक्षर *type = शून्य;

	अगर (acpi_evalf(hkey_handle, &res, "GMMS", "qdd", 0)) अणु
		पूर्णांक has_tablet_mode;

		in_tablet_mode = hotkey_gmms_get_tablet_mode(res,
							     &has_tablet_mode);
		/*
		 * The Yoga 11e series has 2 accelerometers described by a
		 * BOSC0200 ACPI node. This setup relies on a Winकरोws service
		 * which calls special ACPI methods on this node to report
		 * the laptop/tent/tablet mode to the EC. The bmc150 iio driver
		 * करोes not support this, so skip the hotkey on these models.
		 */
		अगर (has_tablet_mode && !acpi_dev_present("BOSC0200", "1", -1))
			tp_features.hotkey_tablet = TP_HOTKEY_TABLET_USES_GMMS;
		type = "GMMS";
	पूर्ण अन्यथा अगर (acpi_evalf(hkey_handle, &res, "MHKG", "qd")) अणु
		/* For X41t, X60t, X61t Tablets... */
		tp_features.hotkey_tablet = TP_HOTKEY_TABLET_USES_MHKG;
		in_tablet_mode = !!(res & TP_HOTKEY_TABLET_MASK);
		type = "MHKG";
	पूर्ण

	अगर (!tp_features.hotkey_tablet)
		वापस 0;

	pr_info("Tablet mode switch found (type: %s), currently in %s mode\n",
		type, in_tablet_mode ? "tablet" : "laptop");

	res = add_to_attr_set(hotkey_dev_attributes,
			      &dev_attr_hotkey_tablet_mode.attr);
	अगर (res)
		वापस -1;

	वापस in_tablet_mode;
पूर्ण

अटल पूर्णांक __init hotkey_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	/* Requirements क्रम changing the शेष keymaps:
	 *
	 * 1. Many of the keys are mapped to KEY_RESERVED क्रम very
	 *    good reasons.  Do not change them unless you have deep
	 *    knowledge on the IBM and Lenovo ThinkPad firmware क्रम
	 *    the various ThinkPad models.  The driver behaves
	 *    dअगरferently क्रम KEY_RESERVED: such keys have their
	 *    hot key mask *unset* in mask_recommended, and also
	 *    in the initial hot key mask programmed पूर्णांकo the
	 *    firmware at driver load समय, which means the firm-
	 *    ware may react very dअगरferently अगर you change them to
	 *    something अन्यथा;
	 *
	 * 2. You must be subscribed to the linux-thinkpad and
	 *    ibm-acpi-devel mailing lists, and you should पढ़ो the
	 *    list archives since 2007 अगर you want to change the
	 *    keymaps.  This requirement exists so that you will
	 *    know the past history of problems with the thinkpad-
	 *    acpi driver keymaps, and also that you will be
	 *    listening to any bug reports;
	 *
	 * 3. Do not send thinkpad-acpi specअगरic patches directly to
	 *    क्रम merging, *ever*.  Send them to the linux-acpi
	 *    mailinglist क्रम comments.  Merging is to be करोne only
	 *    through acpi-test and the ACPI मुख्यtainer.
	 *
	 * If the above is too much to ask, करोn't change the keymap.
	 * Ask the thinkpad-acpi मुख्यtainer to करो it, instead.
	 */

	क्रमागत keymap_index अणु
		TPACPI_KEYMAP_IBM_GENERIC = 0,
		TPACPI_KEYMAP_LENOVO_GENERIC,
	पूर्ण;

	अटल स्थिर tpacpi_keymap_t tpacpi_keymaps[] __initस्थिर = अणु
	/* Generic keymap क्रम IBM ThinkPads */
	[TPACPI_KEYMAP_IBM_GENERIC] = अणु
		/* Scan Codes 0x00 to 0x0B: ACPI HKEY FN+F1..F12 */
		KEY_FN_F1,	KEY_BATTERY,	KEY_COFFEE,	KEY_SLEEP,
		KEY_WLAN,	KEY_FN_F6, KEY_SWITCHVIDEOMODE, KEY_FN_F8,
		KEY_FN_F9,	KEY_FN_F10,	KEY_FN_F11,	KEY_SUSPEND,

		/* Scan codes 0x0C to 0x1F: Other ACPI HKEY hot keys */
		KEY_UNKNOWN,	/* 0x0C: FN+BACKSPACE */
		KEY_UNKNOWN,	/* 0x0D: FN+INSERT */
		KEY_UNKNOWN,	/* 0x0E: FN+DELETE */

		/* brightness: firmware always reacts to them */
		KEY_RESERVED,	/* 0x0F: FN+HOME (brightness up) */
		KEY_RESERVED,	/* 0x10: FN+END (brightness करोwn) */

		/* Thinklight: firmware always react to it */
		KEY_RESERVED,	/* 0x11: FN+PGUP (thinklight toggle) */

		KEY_UNKNOWN,	/* 0x12: FN+PGDOWN */
		KEY_ZOOM,	/* 0x13: FN+SPACE (zoom) */

		/* Volume: firmware always react to it and reprograms
		 * the built-in *extra* mixer.  Never map it to control
		 * another mixer by शेष. */
		KEY_RESERVED,	/* 0x14: VOLUME UP */
		KEY_RESERVED,	/* 0x15: VOLUME DOWN */
		KEY_RESERVED,	/* 0x16: MUTE */

		KEY_VENDOR,	/* 0x17: Thinkpad/AccessIBM/Lenovo */

		/* (assignments unknown, please report अगर found) */
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,

		/* No assignments, only used क्रम Adaptive keyboards. */
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,

		/* No assignment, used क्रम newer Lenovo models */
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN, KEY_UNKNOWN

		पूर्ण,

	/* Generic keymap क्रम Lenovo ThinkPads */
	[TPACPI_KEYMAP_LENOVO_GENERIC] = अणु
		/* Scan Codes 0x00 to 0x0B: ACPI HKEY FN+F1..F12 */
		KEY_FN_F1,	KEY_COFFEE,	KEY_BATTERY,	KEY_SLEEP,
		KEY_WLAN,	KEY_CAMERA, KEY_SWITCHVIDEOMODE, KEY_FN_F8,
		KEY_FN_F9,	KEY_FN_F10,	KEY_FN_F11,	KEY_SUSPEND,

		/* Scan codes 0x0C to 0x1F: Other ACPI HKEY hot keys */
		KEY_UNKNOWN,	/* 0x0C: FN+BACKSPACE */
		KEY_UNKNOWN,	/* 0x0D: FN+INSERT */
		KEY_UNKNOWN,	/* 0x0E: FN+DELETE */

		/* These should be enabled --only-- when ACPI video
		 * is disabled (i.e. in "vendor" mode), and are handled
		 * in a special way by the init code */
		KEY_BRIGHTNESSUP,	/* 0x0F: FN+HOME (brightness up) */
		KEY_BRIGHTNESSDOWN,	/* 0x10: FN+END (brightness करोwn) */

		KEY_RESERVED,	/* 0x11: FN+PGUP (thinklight toggle) */

		KEY_UNKNOWN,	/* 0x12: FN+PGDOWN */
		KEY_ZOOM,	/* 0x13: FN+SPACE (zoom) */

		/* Volume: z60/z61, T60 (BIOS version?): firmware always
		 * react to it and reprograms the built-in *extra* mixer.
		 * Never map it to control another mixer by शेष.
		 *
		 * T60?, T61, R60?, R61: firmware and EC tries to send
		 * these over the regular keyboard, so these are no-ops,
		 * but there are still weird bugs re. MUTE, so करो not
		 * change unless you get test reports from all Lenovo
		 * models.  May cause the BIOS to पूर्णांकerfere with the
		 * HDA mixer.
		 */
		KEY_RESERVED,	/* 0x14: VOLUME UP */
		KEY_RESERVED,	/* 0x15: VOLUME DOWN */
		KEY_RESERVED,	/* 0x16: MUTE */

		KEY_VENDOR,	/* 0x17: Thinkpad/AccessIBM/Lenovo */

		/* (assignments unknown, please report अगर found) */
		KEY_UNKNOWN, KEY_UNKNOWN,

		/*
		 * The mic mute button only sends 0x1a.  It करोes not
		 * स्वतःmatically mute the mic or change the mute light.
		 */
		KEY_MICMUTE,	/* 0x1a: Mic mute (since ?400 or so) */

		/* (assignments unknown, please report अगर found) */
		KEY_UNKNOWN,

		/* Extra keys in use since the X240 / T440 / T540 */
		KEY_CONFIG, KEY_SEARCH, KEY_SCALE, KEY_खाता,

		/*
		 * These are the adaptive keyboard keycodes क्रम Carbon X1 2014.
		 * The first item in this list is the Mute button which is
		 * emitted with 0x103 through
		 * adaptive_keyboard_hotkey_notअगरy_hotkey() when the sound
		 * symbol is held.
		 * We'll need to offset those by 0x20.
		 */
		KEY_RESERVED,        /* Mute held, 0x103 */
		KEY_BRIGHTNESS_MIN,  /* Backlight off */
		KEY_RESERVED,        /* Clipping tool */
		KEY_RESERVED,        /* Cloud */
		KEY_RESERVED,
		KEY_VOICECOMMAND,    /* Voice */
		KEY_RESERVED,
		KEY_RESERVED,        /* Gestures */
		KEY_RESERVED,
		KEY_RESERVED,
		KEY_RESERVED,
		KEY_CONFIG,          /* Settings */
		KEY_RESERVED,        /* New tab */
		KEY_REFRESH,         /* Reload */
		KEY_BACK,            /* Back */
		KEY_RESERVED,        /* Microphone करोwn */
		KEY_RESERVED,        /* Microphone up */
		KEY_RESERVED,        /* Microphone cancellation */
		KEY_RESERVED,        /* Camera mode */
		KEY_RESERVED,        /* Rotate display, 0x116 */

		/*
		 * These are found in 2017 models (e.g. T470s, X270).
		 * The lowest known value is 0x311, which according to
		 * the manual should launch a user defined favorite
		 * application.
		 *
		 * The offset क्रम these is TP_ACPI_HOTKEYSCAN_EXTENDED_START,
		 * corresponding to 0x34.
		 */

		/* (assignments unknown, please report अगर found) */
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,
		KEY_UNKNOWN,

		KEY_BOOKMARKS,			/* Favorite app, 0x311 */
		KEY_SELECTIVE_SCREENSHOT,	/* Clipping tool */
		KEY_CALC,			/* Calculator (above numpad, P52) */
		KEY_BLUETOOTH,			/* Bluetooth */
		KEY_KEYBOARD,			/* Keyboard, 0x315 */
		KEY_FN_RIGHT_SHIFT,		/* Fn + right Shअगरt */
		KEY_NOTIFICATION_CENTER,	/* Notअगरication Center */
		KEY_PICKUP_PHONE,		/* Answer incoming call */
		KEY_HANGUP_PHONE,		/* Decline incoming call */
		पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा tpacpi_quirk tpacpi_keymap_qtable[] __initस्थिर = अणु
		/* Generic maps (fallback) */
		अणु
		  .venकरोr = PCI_VENDOR_ID_IBM,
		  .bios = TPACPI_MATCH_ANY, .ec = TPACPI_MATCH_ANY,
		  .quirks = TPACPI_KEYMAP_IBM_GENERIC,
		पूर्ण,
		अणु
		  .venकरोr = PCI_VENDOR_ID_LENOVO,
		  .bios = TPACPI_MATCH_ANY, .ec = TPACPI_MATCH_ANY,
		  .quirks = TPACPI_KEYMAP_LENOVO_GENERIC,
		पूर्ण,
	पूर्ण;

#घोषणा TPACPI_HOTKEY_MAP_SIZE		माप(tpacpi_keymap_t)
#घोषणा TPACPI_HOTKEY_MAP_TYPESIZE	माप(tpacpi_keymap_entry_t)

	पूर्णांक res, i;
	पूर्णांक status;
	पूर्णांक hkeyv;
	bool radiosw_state  = false;
	bool tabletsw_state = false;

	अचिन्हित दीर्घ quirks;
	अचिन्हित दीर्घ keymap_id;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_HKEY,
			"initializing hotkey subdriver\n");

	BUG_ON(!tpacpi_inputdev);
	BUG_ON(tpacpi_inputdev->खोलो != शून्य ||
	       tpacpi_inputdev->बंद != शून्य);

	TPACPI_ACPIHANDLE_INIT(hkey);
	mutex_init(&hotkey_mutex);

#अगर_घोषित CONFIG_THINKPAD_ACPI_HOTKEY_POLL
	mutex_init(&hotkey_thपढ़ो_data_mutex);
#पूर्ण_अगर

	/* hotkey not supported on 570 */
	tp_features.hotkey = hkey_handle != शून्य;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_HKEY,
		"hotkeys are %s\n",
		str_supported(tp_features.hotkey));

	अगर (!tp_features.hotkey)
		वापस 1;

	quirks = tpacpi_check_quirks(tpacpi_hotkey_qtable,
				     ARRAY_SIZE(tpacpi_hotkey_qtable));

	tpacpi_disable_brightness_delay();

	/* MUST have enough space क्रम all attributes to be added to
	 * hotkey_dev_attributes */
	hotkey_dev_attributes = create_attr_set(
					ARRAY_SIZE(hotkey_attributes) + 2,
					शून्य);
	अगर (!hotkey_dev_attributes)
		वापस -ENOMEM;
	res = add_many_to_attr_set(hotkey_dev_attributes,
			hotkey_attributes,
			ARRAY_SIZE(hotkey_attributes));
	अगर (res)
		जाओ err_निकास;

	/* mask not supported on 600e/x, 770e, 770x, A21e, A2xm/p,
	   A30, R30, R31, T20-22, X20-21, X22-24.  Detected by checking
	   क्रम HKEY पूर्णांकerface version 0x100 */
	अगर (acpi_evalf(hkey_handle, &hkeyv, "MHKV", "qd")) अणु
		vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_HKEY,
			    "firmware HKEY interface version: 0x%x\n",
			    hkeyv);

		चयन (hkeyv >> 8) अणु
		हाल 1:
			/*
			 * MHKV 0x100 in A31, R40, R40e,
			 * T4x, X31, and later
			 */

			/* Paranoia check AND init hotkey_all_mask */
			अगर (!acpi_evalf(hkey_handle, &hotkey_all_mask,
					"MHKA", "qd")) अणु
				pr_err("missing MHKA handler, please report this to %s\n",
				       TPACPI_MAIL);
				/* Fallback: pre-init क्रम FN+F3,F4,F12 */
				hotkey_all_mask = 0x080cU;
			पूर्ण अन्यथा अणु
				tp_features.hotkey_mask = 1;
			पूर्ण
			अवरोध;

		हाल 2:
			/*
			 * MHKV 0x200 in X1, T460s, X260, T560, X1 Tablet (2016)
			 */

			/* Paranoia check AND init hotkey_all_mask */
			अगर (!acpi_evalf(hkey_handle, &hotkey_all_mask,
					"MHKA", "dd", 1)) अणु
				pr_err("missing MHKA handler, please report this to %s\n",
				       TPACPI_MAIL);
				/* Fallback: pre-init क्रम FN+F3,F4,F12 */
				hotkey_all_mask = 0x080cU;
			पूर्ण अन्यथा अणु
				tp_features.hotkey_mask = 1;
			पूर्ण

			/*
			 * Check अगर we have an adaptive keyboard, like on the
			 * Lenovo Carbon X1 2014 (2nd Gen).
			 */
			अगर (acpi_evalf(hkey_handle, &hotkey_adaptive_all_mask,
				       "MHKA", "dd", 2)) अणु
				अगर (hotkey_adaptive_all_mask != 0) अणु
					tp_features.has_adaptive_kbd = true;
					res = sysfs_create_group(
						&tpacpi_pdev->dev.kobj,
						&adaptive_kbd_attr_group);
					अगर (res)
						जाओ err_निकास;
				पूर्ण
			पूर्ण अन्यथा अणु
				tp_features.has_adaptive_kbd = false;
				hotkey_adaptive_all_mask = 0x0U;
			पूर्ण
			अवरोध;

		शेष:
			pr_err("unknown version of the HKEY interface: 0x%x\n",
			       hkeyv);
			pr_err("please report this to %s\n", TPACPI_MAIL);
			अवरोध;
		पूर्ण
	पूर्ण

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_HKEY,
		"hotkey masks are %s\n",
		str_supported(tp_features.hotkey_mask));

	/* Init hotkey_all_mask अगर not initialized yet */
	अगर (!tp_features.hotkey_mask && !hotkey_all_mask &&
	    (quirks & TPACPI_HK_Q_INIMASK))
		hotkey_all_mask = 0x080cU;  /* FN+F12, FN+F4, FN+F3 */

	/* Init hotkey_acpi_mask and hotkey_orig_mask */
	अगर (tp_features.hotkey_mask) अणु
		/* hotkey_source_mask *must* be zero क्रम
		 * the first hotkey_mask_get to वापस hotkey_orig_mask */
		res = hotkey_mask_get();
		अगर (res)
			जाओ err_निकास;

		hotkey_orig_mask = hotkey_acpi_mask;
	पूर्ण अन्यथा अणु
		hotkey_orig_mask = hotkey_all_mask;
		hotkey_acpi_mask = hotkey_all_mask;
	पूर्ण

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	अगर (dbg_wlswemul) अणु
		tp_features.hotkey_wlsw = 1;
		radiosw_state = !!tpacpi_wlsw_emulstate;
		pr_info("radio switch emulation enabled\n");
	पूर्ण अन्यथा
#पूर्ण_अगर
	/* Not all thinkpads have a hardware radio चयन */
	अगर (acpi_evalf(hkey_handle, &status, "WLSW", "qd")) अणु
		tp_features.hotkey_wlsw = 1;
		radiosw_state = !!status;
		pr_info("radio switch found; radios are %s\n",
			enabled(status, 0));
	पूर्ण
	अगर (tp_features.hotkey_wlsw)
		res = add_to_attr_set(hotkey_dev_attributes,
				&dev_attr_hotkey_radio_sw.attr);

	res = hotkey_init_tablet_mode();
	अगर (res < 0)
		जाओ err_निकास;

	tabletsw_state = res;

	res = रेजिस्टर_attr_set_with_sysfs(hotkey_dev_attributes,
					   &tpacpi_pdev->dev.kobj);
	अगर (res)
		जाओ err_निकास;

	/* Set up key map */
	keymap_id = tpacpi_check_quirks(tpacpi_keymap_qtable,
					ARRAY_SIZE(tpacpi_keymap_qtable));
	BUG_ON(keymap_id >= ARRAY_SIZE(tpacpi_keymaps));
	dbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_HKEY,
		   "using keymap number %lu\n", keymap_id);

	hotkey_keycode_map = kmemdup(&tpacpi_keymaps[keymap_id],
			TPACPI_HOTKEY_MAP_SIZE,	GFP_KERNEL);
	अगर (!hotkey_keycode_map) अणु
		pr_err("failed to allocate memory for key map\n");
		res = -ENOMEM;
		जाओ err_निकास;
	पूर्ण

	input_set_capability(tpacpi_inputdev, EV_MSC, MSC_SCAN);
	tpacpi_inputdev->keycodesize = TPACPI_HOTKEY_MAP_TYPESIZE;
	tpacpi_inputdev->keycodemax = TPACPI_HOTKEY_MAP_LEN;
	tpacpi_inputdev->keycode = hotkey_keycode_map;
	क्रम (i = 0; i < TPACPI_HOTKEY_MAP_LEN; i++) अणु
		अगर (hotkey_keycode_map[i] != KEY_RESERVED) अणु
			input_set_capability(tpacpi_inputdev, EV_KEY,
						hotkey_keycode_map[i]);
		पूर्ण अन्यथा अणु
			अगर (i < माप(hotkey_reserved_mask)*8)
				hotkey_reserved_mask |= 1 << i;
		पूर्ण
	पूर्ण

	अगर (tp_features.hotkey_wlsw) अणु
		input_set_capability(tpacpi_inputdev, EV_SW, SW_RFKILL_ALL);
		input_report_चयन(tpacpi_inputdev,
				    SW_RFKILL_ALL, radiosw_state);
	पूर्ण
	अगर (tp_features.hotkey_tablet) अणु
		input_set_capability(tpacpi_inputdev, EV_SW, SW_TABLET_MODE);
		input_report_चयन(tpacpi_inputdev,
				    SW_TABLET_MODE, tabletsw_state);
	पूर्ण

	/* Do not issue duplicate brightness change events to
	 * userspace. tpacpi_detect_brightness_capabilities() must have
	 * been called beक्रमe this poपूर्णांक  */
	अगर (acpi_video_get_backlight_type() != acpi_backlight_venकरोr) अणु
		pr_info("This ThinkPad has standard ACPI backlight brightness control, supported by the ACPI video driver\n");
		pr_notice("Disabling thinkpad-acpi brightness events by default...\n");

		/* Disable brightness up/करोwn on Lenovo thinkpads when
		 * ACPI is handling them, otherwise it is plain impossible
		 * क्रम userspace to करो something even remotely sane */
		hotkey_reserved_mask |=
			(1 << TP_ACPI_HOTKEYSCAN_FNHOME)
			| (1 << TP_ACPI_HOTKEYSCAN_FNEND);
		hotkey_unmap(TP_ACPI_HOTKEYSCAN_FNHOME);
		hotkey_unmap(TP_ACPI_HOTKEYSCAN_FNEND);
	पूर्ण

#अगर_घोषित CONFIG_THINKPAD_ACPI_HOTKEY_POLL
	hotkey_source_mask = TPACPI_HKEY_NVRAM_GOOD_MASK
				& ~hotkey_all_mask
				& ~hotkey_reserved_mask;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_HKEY,
		    "hotkey source mask 0x%08x, polling freq %u\n",
		    hotkey_source_mask, hotkey_poll_freq);
#पूर्ण_अगर

	dbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_HKEY,
			"enabling firmware HKEY event interface...\n");
	res = hotkey_status_set(true);
	अगर (res) अणु
		hotkey_निकास();
		वापस res;
	पूर्ण
	res = hotkey_mask_set(((hotkey_all_mask & ~hotkey_reserved_mask)
			       | hotkey_driver_mask)
			      & ~hotkey_source_mask);
	अगर (res < 0 && res != -ENXIO) अणु
		hotkey_निकास();
		वापस res;
	पूर्ण
	hotkey_user_mask = (hotkey_acpi_mask | hotkey_source_mask)
				& ~hotkey_reserved_mask;
	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_HKEY,
		"initial masks: user=0x%08x, fw=0x%08x, poll=0x%08x\n",
		hotkey_user_mask, hotkey_acpi_mask, hotkey_source_mask);

	tpacpi_inputdev->खोलो = &hotkey_inputdev_खोलो;
	tpacpi_inputdev->बंद = &hotkey_inputdev_बंद;

	hotkey_poll_setup_safe(true);

	वापस 0;

err_निकास:
	delete_attr_set(hotkey_dev_attributes, &tpacpi_pdev->dev.kobj);
	sysfs_हटाओ_group(&tpacpi_pdev->dev.kobj,
			&adaptive_kbd_attr_group);

	hotkey_dev_attributes = शून्य;

	वापस (res < 0) ? res : 1;
पूर्ण

/* Thinkpad X1 Carbon support 5 modes including Home mode, Web browser
 * mode, Web conference mode, Function mode and Lay-flat mode.
 * We support Home mode and Function mode currently.
 *
 * Will consider support rest of modes in future.
 *
 */
अटल स्थिर पूर्णांक adaptive_keyboard_modes[] = अणु
	HOME_MODE,
/*	WEB_BROWSER_MODE = 2,
	WEB_CONFERENCE_MODE = 3, */
	FUNCTION_MODE
पूर्ण;

#घोषणा DFR_CHANGE_ROW			0x101
#घोषणा DFR_SHOW_QUICKVIEW_ROW		0x102
#घोषणा FIRST_ADAPTIVE_KEY		0x103

/* press Fn key a जबतक second, it will चयन to Function Mode. Then
 * release Fn key, previous mode be restored.
 */
अटल bool adaptive_keyboard_mode_is_saved;
अटल पूर्णांक adaptive_keyboard_prev_mode;

अटल पूर्णांक adaptive_keyboard_get_mode(व्योम)
अणु
	पूर्णांक mode = 0;

	अगर (!acpi_evalf(hkey_handle, &mode, "GTRW", "dd", 0)) अणु
		pr_err("Cannot read adaptive keyboard mode\n");
		वापस -EIO;
	पूर्ण

	वापस mode;
पूर्ण

अटल पूर्णांक adaptive_keyboard_set_mode(पूर्णांक new_mode)
अणु
	अगर (new_mode < 0 ||
		new_mode > LAYFLAT_MODE)
		वापस -EINVAL;

	अगर (!acpi_evalf(hkey_handle, शून्य, "STRW", "vd", new_mode)) अणु
		pr_err("Cannot set adaptive keyboard mode\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adaptive_keyboard_get_next_mode(पूर्णांक mode)
अणु
	माप_प्रकार i;
	माप_प्रकार max_mode = ARRAY_SIZE(adaptive_keyboard_modes) - 1;

	क्रम (i = 0; i <= max_mode; i++) अणु
		अगर (adaptive_keyboard_modes[i] == mode)
			अवरोध;
	पूर्ण

	अगर (i >= max_mode)
		i = 0;
	अन्यथा
		i++;

	वापस adaptive_keyboard_modes[i];
पूर्ण

अटल bool adaptive_keyboard_hotkey_notअगरy_hotkey(अचिन्हित पूर्णांक scancode)
अणु
	पूर्णांक current_mode = 0;
	पूर्णांक new_mode = 0;
	पूर्णांक keycode;

	चयन (scancode) अणु
	हाल DFR_CHANGE_ROW:
		अगर (adaptive_keyboard_mode_is_saved) अणु
			new_mode = adaptive_keyboard_prev_mode;
			adaptive_keyboard_mode_is_saved = false;
		पूर्ण अन्यथा अणु
			current_mode = adaptive_keyboard_get_mode();
			अगर (current_mode < 0)
				वापस false;
			new_mode = adaptive_keyboard_get_next_mode(
					current_mode);
		पूर्ण

		अगर (adaptive_keyboard_set_mode(new_mode) < 0)
			वापस false;

		वापस true;

	हाल DFR_SHOW_QUICKVIEW_ROW:
		current_mode = adaptive_keyboard_get_mode();
		अगर (current_mode < 0)
			वापस false;

		adaptive_keyboard_prev_mode = current_mode;
		adaptive_keyboard_mode_is_saved = true;

		अगर (adaptive_keyboard_set_mode (FUNCTION_MODE) < 0)
			वापस false;
		वापस true;

	शेष:
		अगर (scancode < FIRST_ADAPTIVE_KEY ||
		    scancode >= FIRST_ADAPTIVE_KEY +
		    TP_ACPI_HOTKEYSCAN_EXTENDED_START -
		    TP_ACPI_HOTKEYSCAN_ADAPTIVE_START) अणु
			pr_info("Unhandled adaptive keyboard key: 0x%x\n",
				scancode);
			वापस false;
		पूर्ण
		keycode = hotkey_keycode_map[scancode - FIRST_ADAPTIVE_KEY +
					     TP_ACPI_HOTKEYSCAN_ADAPTIVE_START];
		अगर (keycode != KEY_RESERVED) अणु
			mutex_lock(&tpacpi_inputdev_send_mutex);

			input_report_key(tpacpi_inputdev, keycode, 1);
			input_sync(tpacpi_inputdev);

			input_report_key(tpacpi_inputdev, keycode, 0);
			input_sync(tpacpi_inputdev);

			mutex_unlock(&tpacpi_inputdev_send_mutex);
		पूर्ण
		वापस true;
	पूर्ण
पूर्ण

अटल bool hotkey_notअगरy_hotkey(स्थिर u32 hkey,
				 bool *send_acpi_ev,
				 bool *ignore_acpi_ev)
अणु
	/* 0x1000-0x1FFF: key presses */
	अचिन्हित पूर्णांक scancode = hkey & 0xfff;
	*send_acpi_ev = true;
	*ignore_acpi_ev = false;

	/*
	 * Original events are in the 0x10XX range, the adaptive keyboard
	 * found in 2014 X1 Carbon emits events are of 0x11XX. In 2017
	 * models, additional keys are emitted through 0x13XX.
	 */
	चयन ((hkey >> 8) & 0xf) अणु
	हाल 0:
		अगर (scancode > 0 &&
		    scancode <= TP_ACPI_HOTKEYSCAN_ADAPTIVE_START) अणु
			/* HKEY event 0x1001 is scancode 0x00 */
			scancode--;
			अगर (!(hotkey_source_mask & (1 << scancode))) अणु
				tpacpi_input_send_key_masked(scancode);
				*send_acpi_ev = false;
			पूर्ण अन्यथा अणु
				*ignore_acpi_ev = true;
			पूर्ण
			वापस true;
		पूर्ण
		अवरोध;

	हाल 1:
		वापस adaptive_keyboard_hotkey_notअगरy_hotkey(scancode);

	हाल 3:
		/* Extended keycodes start at 0x300 and our offset पूर्णांकo the map
		 * TP_ACPI_HOTKEYSCAN_EXTENDED_START. The calculated scancode
		 * will be positive, but might not be in the correct range.
		 */
		scancode -= (0x300 - TP_ACPI_HOTKEYSCAN_EXTENDED_START);
		अगर (scancode >= TP_ACPI_HOTKEYSCAN_EXTENDED_START &&
		    scancode < TPACPI_HOTKEY_MAP_LEN) अणु
			tpacpi_input_send_key(scancode);
			वापस true;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल bool hotkey_notअगरy_wakeup(स्थिर u32 hkey,
				 bool *send_acpi_ev,
				 bool *ignore_acpi_ev)
अणु
	/* 0x2000-0x2FFF: Wakeup reason */
	*send_acpi_ev = true;
	*ignore_acpi_ev = false;

	चयन (hkey) अणु
	हाल TP_HKEY_EV_WKUP_S3_UNDOCK: /* suspend, unकरोck */
	हाल TP_HKEY_EV_WKUP_S4_UNDOCK: /* hibernation, unकरोck */
		hotkey_wakeup_reason = TP_ACPI_WAKEUP_UNDOCK;
		*ignore_acpi_ev = true;
		अवरोध;

	हाल TP_HKEY_EV_WKUP_S3_BAYEJ: /* suspend, bay eject */
	हाल TP_HKEY_EV_WKUP_S4_BAYEJ: /* hibernation, bay eject */
		hotkey_wakeup_reason = TP_ACPI_WAKEUP_BAYEJ;
		*ignore_acpi_ev = true;
		अवरोध;

	हाल TP_HKEY_EV_WKUP_S3_BATLOW: /* Battery on critical low level/S3 */
	हाल TP_HKEY_EV_WKUP_S4_BATLOW: /* Battery on critical low level/S4 */
		pr_alert("EMERGENCY WAKEUP: battery almost empty\n");
		/* how to स्वतः-heal: */
		/* 2313: woke up from S3, go to S4/S5 */
		/* 2413: woke up from S4, go to S5 */
		अवरोध;

	शेष:
		वापस false;
	पूर्ण

	अगर (hotkey_wakeup_reason != TP_ACPI_WAKEUP_NONE) अणु
		pr_info("woke up due to a hot-unplug request...\n");
		hotkey_wakeup_reason_notअगरy_change();
	पूर्ण
	वापस true;
पूर्ण

अटल bool hotkey_notअगरy_करोckevent(स्थिर u32 hkey,
				 bool *send_acpi_ev,
				 bool *ignore_acpi_ev)
अणु
	/* 0x4000-0x4FFF: करोck-related events */
	*send_acpi_ev = true;
	*ignore_acpi_ev = false;

	चयन (hkey) अणु
	हाल TP_HKEY_EV_UNDOCK_ACK:
		/* ACPI unकरोck operation completed after wakeup */
		hotkey_स्वतःsleep_ack = 1;
		pr_info("undocked\n");
		hotkey_wakeup_hotunplug_complete_notअगरy_change();
		वापस true;

	हाल TP_HKEY_EV_HOTPLUG_DOCK: /* करोcked to port replicator */
		pr_info("docked into hotplug port replicator\n");
		वापस true;
	हाल TP_HKEY_EV_HOTPLUG_UNDOCK: /* unकरोcked from port replicator */
		pr_info("undocked from hotplug port replicator\n");
		वापस true;

	/*
	 * Deliberately ignore attaching and detaching the keybord cover to aव्योम
	 * duplicates from पूर्णांकel-vbtn, which alपढ़ोy emits SW_TABLET_MODE events
	 * to userspace.
	 *
	 * Please refer to the following thपढ़ो क्रम more inक्रमmation and a preliminary
	 * implementation using the GTOP ("Get Tablet OPtions") पूर्णांकerface that could be
	 * extended to other attachment options of the ThinkPad X1 Tablet series, such as
	 * the Pico cartridge करोck module:
	 * https://lore.kernel.org/platक्रमm-driver-x86/38cb8265-1e30-d547-9e12-b4ae290be737@a-kobel.de/
	 */
	हाल TP_HKEY_EV_KBD_COVER_ATTACH:
	हाल TP_HKEY_EV_KBD_COVER_DETACH:
		*send_acpi_ev = false;
		*ignore_acpi_ev = true;
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool hotkey_notअगरy_usrevent(स्थिर u32 hkey,
				 bool *send_acpi_ev,
				 bool *ignore_acpi_ev)
अणु
	/* 0x5000-0x5FFF: human पूर्णांकerface helpers */
	*send_acpi_ev = true;
	*ignore_acpi_ev = false;

	चयन (hkey) अणु
	हाल TP_HKEY_EV_PEN_INSERTED:  /* X61t: tablet pen inserted पूर्णांकo bay */
	हाल TP_HKEY_EV_PEN_REMOVED:   /* X61t: tablet pen हटाओd from bay */
		वापस true;

	हाल TP_HKEY_EV_TABLET_TABLET:   /* X41t-X61t: tablet mode */
	हाल TP_HKEY_EV_TABLET_NOTEBOOK: /* X41t-X61t: normal mode */
		tpacpi_input_send_tabletsw();
		hotkey_tablet_mode_notअगरy_change();
		*send_acpi_ev = false;
		वापस true;

	हाल TP_HKEY_EV_LID_CLOSE:	/* Lid बंदd */
	हाल TP_HKEY_EV_LID_OPEN:	/* Lid खोलोed */
	हाल TP_HKEY_EV_BRGHT_CHANGED:	/* brightness changed */
		/* करो not propagate these events */
		*ignore_acpi_ev = true;
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम thermal_dump_all_sensors(व्योम);
अटल व्योम palmsensor_refresh(व्योम);

अटल bool hotkey_notअगरy_6xxx(स्थिर u32 hkey,
				 bool *send_acpi_ev,
				 bool *ignore_acpi_ev)
अणु
	/* 0x6000-0x6FFF: thermal alarms/notices and keyboard events */
	*send_acpi_ev = true;
	*ignore_acpi_ev = false;

	चयन (hkey) अणु
	हाल TP_HKEY_EV_THM_TABLE_CHANGED:
		pr_debug("EC reports: Thermal Table has changed\n");
		/* recommended action: करो nothing, we करोn't have
		 * Lenovo ATM inक्रमmation */
		वापस true;
	हाल TP_HKEY_EV_THM_CSM_COMPLETED:
		pr_debug("EC reports: Thermal Control Command set completed (DYTC)\n");
		/* Thermal event - pass on to event handler */
		tpacpi_driver_event(hkey);
		वापस true;
	हाल TP_HKEY_EV_THM_TRANSFM_CHANGED:
		pr_debug("EC reports: Thermal Transformation changed (GMTS)\n");
		/* recommended action: करो nothing, we करोn't have
		 * Lenovo ATM inक्रमmation */
		वापस true;
	हाल TP_HKEY_EV_ALARM_BAT_HOT:
		pr_crit("THERMAL ALARM: battery is too hot!\n");
		/* recommended action: warn user through gui */
		अवरोध;
	हाल TP_HKEY_EV_ALARM_BAT_XHOT:
		pr_alert("THERMAL EMERGENCY: battery is extremely hot!\n");
		/* recommended action: immediate sleep/hibernate */
		अवरोध;
	हाल TP_HKEY_EV_ALARM_SENSOR_HOT:
		pr_crit("THERMAL ALARM: a sensor reports something is too hot!\n");
		/* recommended action: warn user through gui, that */
		/* some पूर्णांकernal component is too hot */
		अवरोध;
	हाल TP_HKEY_EV_ALARM_SENSOR_XHOT:
		pr_alert("THERMAL EMERGENCY: a sensor reports something is extremely hot!\n");
		/* recommended action: immediate sleep/hibernate */
		अवरोध;
	हाल TP_HKEY_EV_AC_CHANGED:
		/* X120e, X121e, X220, X220i, X220t, X230, T420, T420s, W520:
		 * AC status changed; can be triggered by plugging or
		 * unplugging AC adapter, करोcking or unकरोcking. */

		fallthrough;

	हाल TP_HKEY_EV_KEY_NUMLOCK:
	हाल TP_HKEY_EV_KEY_FN:
		/* key press events, we just ignore them as दीर्घ as the EC
		 * is still reporting them in the normal keyboard stream */
		*send_acpi_ev = false;
		*ignore_acpi_ev = true;
		वापस true;

	हाल TP_HKEY_EV_KEY_FN_ESC:
		/* Get the media key status to क्रमce the status LED to update */
		acpi_evalf(hkey_handle, शून्य, "GMKS", "v");
		*send_acpi_ev = false;
		*ignore_acpi_ev = true;
		वापस true;

	हाल TP_HKEY_EV_TABLET_CHANGED:
		tpacpi_input_send_tabletsw();
		hotkey_tablet_mode_notअगरy_change();
		*send_acpi_ev = false;
		वापस true;

	हाल TP_HKEY_EV_PALM_DETECTED:
	हाल TP_HKEY_EV_PALM_UNDETECTED:
		/* palm detected  - pass on to event handler */
		palmsensor_refresh();
		वापस true;

	शेष:
		/* report simply as unknown, no sensor dump */
		वापस false;
	पूर्ण

	thermal_dump_all_sensors();
	वापस true;
पूर्ण

अटल व्योम hotkey_notअगरy(काष्ठा ibm_काष्ठा *ibm, u32 event)
अणु
	u32 hkey;
	bool send_acpi_ev;
	bool ignore_acpi_ev;
	bool known_ev;

	अगर (event != 0x80) अणु
		pr_err("unknown HKEY notification event %d\n", event);
		/* क्रमward it to userspace, maybe it knows how to handle it */
		acpi_bus_generate_netlink_event(
					ibm->acpi->device->pnp.device_class,
					dev_name(&ibm->acpi->device->dev),
					event, 0);
		वापस;
	पूर्ण

	जबतक (1) अणु
		अगर (!acpi_evalf(hkey_handle, &hkey, "MHKP", "d")) अणु
			pr_err("failed to retrieve HKEY event\n");
			वापस;
		पूर्ण

		अगर (hkey == 0) अणु
			/* queue empty */
			वापस;
		पूर्ण

		send_acpi_ev = true;
		ignore_acpi_ev = false;

		चयन (hkey >> 12) अणु
		हाल 1:
			/* 0x1000-0x1FFF: key presses */
			known_ev = hotkey_notअगरy_hotkey(hkey, &send_acpi_ev,
						 &ignore_acpi_ev);
			अवरोध;
		हाल 2:
			/* 0x2000-0x2FFF: Wakeup reason */
			known_ev = hotkey_notअगरy_wakeup(hkey, &send_acpi_ev,
						 &ignore_acpi_ev);
			अवरोध;
		हाल 3:
			/* 0x3000-0x3FFF: bay-related wakeups */
			चयन (hkey) अणु
			हाल TP_HKEY_EV_BAYEJ_ACK:
				hotkey_स्वतःsleep_ack = 1;
				pr_info("bay ejected\n");
				hotkey_wakeup_hotunplug_complete_notअगरy_change();
				known_ev = true;
				अवरोध;
			हाल TP_HKEY_EV_OPTDRV_EJ:
				/* FIXME: kick libata अगर SATA link offline */
				known_ev = true;
				अवरोध;
			शेष:
				known_ev = false;
			पूर्ण
			अवरोध;
		हाल 4:
			/* 0x4000-0x4FFF: करोck-related events */
			known_ev = hotkey_notअगरy_करोckevent(hkey, &send_acpi_ev,
						&ignore_acpi_ev);
			अवरोध;
		हाल 5:
			/* 0x5000-0x5FFF: human पूर्णांकerface helpers */
			known_ev = hotkey_notअगरy_usrevent(hkey, &send_acpi_ev,
						 &ignore_acpi_ev);
			अवरोध;
		हाल 6:
			/* 0x6000-0x6FFF: thermal alarms/notices and
			 *                keyboard events */
			known_ev = hotkey_notअगरy_6xxx(hkey, &send_acpi_ev,
						 &ignore_acpi_ev);
			अवरोध;
		हाल 7:
			/* 0x7000-0x7FFF: misc */
			अगर (tp_features.hotkey_wlsw &&
					hkey == TP_HKEY_EV_RFKILL_CHANGED) अणु
				tpacpi_send_radiosw_update();
				send_acpi_ev = 0;
				known_ev = true;
				अवरोध;
			पूर्ण
			fallthrough;	/* to शेष */
		शेष:
			known_ev = false;
		पूर्ण
		अगर (!known_ev) अणु
			pr_notice("unhandled HKEY event 0x%04x\n", hkey);
			pr_notice("please report the conditions when this event happened to %s\n",
				  TPACPI_MAIL);
		पूर्ण

		/* netlink events */
		अगर (!ignore_acpi_ev && send_acpi_ev) अणु
			acpi_bus_generate_netlink_event(
					ibm->acpi->device->pnp.device_class,
					dev_name(&ibm->acpi->device->dev),
					event, hkey);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hotkey_suspend(व्योम)
अणु
	/* Do these on suspend, we get the events on early resume! */
	hotkey_wakeup_reason = TP_ACPI_WAKEUP_NONE;
	hotkey_स्वतःsleep_ack = 0;

	/* save previous mode of adaptive keyboard of X1 Carbon */
	अगर (tp_features.has_adaptive_kbd) अणु
		अगर (!acpi_evalf(hkey_handle, &adaptive_keyboard_prev_mode,
					"GTRW", "dd", 0)) अणु
			pr_err("Cannot read adaptive keyboard mode.\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hotkey_resume(व्योम)
अणु
	tpacpi_disable_brightness_delay();

	अगर (hotkey_status_set(true) < 0 ||
	    hotkey_mask_set(hotkey_acpi_mask) < 0)
		pr_err("error while attempting to reset the event firmware interface\n");

	tpacpi_send_radiosw_update();
	tpacpi_input_send_tabletsw();
	hotkey_tablet_mode_notअगरy_change();
	hotkey_wakeup_reason_notअगरy_change();
	hotkey_wakeup_hotunplug_complete_notअगरy_change();
	hotkey_poll_setup_safe(false);

	/* restore previous mode of adapive keyboard of X1 Carbon */
	अगर (tp_features.has_adaptive_kbd) अणु
		अगर (!acpi_evalf(hkey_handle, शून्य, "STRW", "vd",
					adaptive_keyboard_prev_mode)) अणु
			pr_err("Cannot set adaptive keyboard mode.\n");
		पूर्ण
	पूर्ण
पूर्ण

/* procfs -------------------------------------------------------------- */
अटल पूर्णांक hotkey_पढ़ो(काष्ठा seq_file *m)
अणु
	पूर्णांक res, status;

	अगर (!tp_features.hotkey) अणु
		seq_म_लिखो(m, "status:\t\tnot supported\n");
		वापस 0;
	पूर्ण

	अगर (mutex_lock_समाप्तable(&hotkey_mutex))
		वापस -ERESTARTSYS;
	res = hotkey_status_get(&status);
	अगर (!res)
		res = hotkey_mask_get();
	mutex_unlock(&hotkey_mutex);
	अगर (res)
		वापस res;

	seq_म_लिखो(m, "status:\t\t%s\n", enabled(status, 0));
	अगर (hotkey_all_mask) अणु
		seq_म_लिखो(m, "mask:\t\t0x%08x\n", hotkey_user_mask);
		seq_म_लिखो(m, "commands:\tenable, disable, reset, <mask>\n");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "mask:\t\tnot supported\n");
		seq_म_लिखो(m, "commands:\tenable, disable, reset\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hotkey_enabledisable_warn(bool enable)
अणु
	tpacpi_log_usertask("procfs hotkey enable/disable");
	अगर (!WARN((tpacpi_lअगरecycle == TPACPI_LIFE_RUNNING || !enable),
		  pr_fmt("hotkey enable/disable functionality has been removed from the driver.  Hotkeys are always enabled.\n")))
		pr_err("Please remove the hotkey=enable module parameter, it is deprecated.  Hotkeys are always enabled.\n");
पूर्ण

अटल पूर्णांक hotkey_ग_लिखो(अक्षर *buf)
अणु
	पूर्णांक res;
	u32 mask;
	अक्षर *cmd;

	अगर (!tp_features.hotkey)
		वापस -ENODEV;

	अगर (mutex_lock_समाप्तable(&hotkey_mutex))
		वापस -ERESTARTSYS;

	mask = hotkey_user_mask;

	res = 0;
	जबतक ((cmd = strsep(&buf, ","))) अणु
		अगर (म_मापcmp(cmd, "enable") == 0) अणु
			hotkey_enabledisable_warn(1);
		पूर्ण अन्यथा अगर (म_मापcmp(cmd, "disable") == 0) अणु
			hotkey_enabledisable_warn(0);
			res = -EPERM;
		पूर्ण अन्यथा अगर (म_मापcmp(cmd, "reset") == 0) अणु
			mask = (hotkey_all_mask | hotkey_source_mask)
				& ~hotkey_reserved_mask;
		पूर्ण अन्यथा अगर (माला_पूछो(cmd, "0x%x", &mask) == 1) अणु
			/* mask set */
		पूर्ण अन्यथा अगर (माला_पूछो(cmd, "%x", &mask) == 1) अणु
			/* mask set */
		पूर्ण अन्यथा अणु
			res = -EINVAL;
			जाओ errनिकास;
		पूर्ण
	पूर्ण

	अगर (!res) अणु
		tpacpi_disबंद_usertask("procfs hotkey",
			"set mask to 0x%08x\n", mask);
		res = hotkey_user_mask_set(mask);
	पूर्ण

errनिकास:
	mutex_unlock(&hotkey_mutex);
	वापस res;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id ibm_htk_device_ids[] = अणु
	अणुTPACPI_ACPI_IBM_HKEY_HID, 0पूर्ण,
	अणुTPACPI_ACPI_LENOVO_HKEY_HID, 0पूर्ण,
	अणुTPACPI_ACPI_LENOVO_HKEY_V2_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा tp_acpi_drv_काष्ठा ibm_hotkey_acpidriver = अणु
	.hid = ibm_htk_device_ids,
	.notअगरy = hotkey_notअगरy,
	.handle = &hkey_handle,
	.type = ACPI_DEVICE_NOTIFY,
पूर्ण;

अटल काष्ठा ibm_काष्ठा hotkey_driver_data = अणु
	.name = "hotkey",
	.पढ़ो = hotkey_पढ़ो,
	.ग_लिखो = hotkey_ग_लिखो,
	.निकास = hotkey_निकास,
	.resume = hotkey_resume,
	.suspend = hotkey_suspend,
	.acpi = &ibm_hotkey_acpidriver,
पूर्ण;

/*************************************************************************
 * Bluetooth subdriver
 */

क्रमागत अणु
	/* ACPI GBDC/SBDC bits */
	TP_ACPI_BLUETOOTH_HWPRESENT	= 0x01,	/* Bluetooth hw available */
	TP_ACPI_BLUETOOTH_RADIOSSW	= 0x02,	/* Bluetooth radio enabled */
	TP_ACPI_BLUETOOTH_RESUMECTRL	= 0x04,	/* Bluetooth state at resume:
						   0 = disable, 1 = enable */
पूर्ण;

क्रमागत अणु
	/* ACPI \BLTH commands */
	TP_ACPI_BLTH_GET_ULTRAPORT_ID	= 0x00, /* Get Ultraport BT ID */
	TP_ACPI_BLTH_GET_PWR_ON_RESUME	= 0x01, /* Get घातer-on-resume state */
	TP_ACPI_BLTH_PWR_ON_ON_RESUME	= 0x02, /* Resume घातered on */
	TP_ACPI_BLTH_PWR_OFF_ON_RESUME	= 0x03,	/* Resume घातered off */
	TP_ACPI_BLTH_SAVE_STATE		= 0x05, /* Save state क्रम S4/S5 */
पूर्ण;

#घोषणा TPACPI_RFK_BLUETOOTH_SW_NAME	"tpacpi_bluetooth_sw"

अटल पूर्णांक bluetooth_get_status(व्योम)
अणु
	पूर्णांक status;

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	अगर (dbg_bluetoothemul)
		वापस (tpacpi_bluetooth_emulstate) ?
		       TPACPI_RFK_RADIO_ON : TPACPI_RFK_RADIO_OFF;
#पूर्ण_अगर

	अगर (!acpi_evalf(hkey_handle, &status, "GBDC", "d"))
		वापस -EIO;

	वापस ((status & TP_ACPI_BLUETOOTH_RADIOSSW) != 0) ?
			TPACPI_RFK_RADIO_ON : TPACPI_RFK_RADIO_OFF;
पूर्ण

अटल पूर्णांक bluetooth_set_status(क्रमागत tpacpi_rfसमाप्त_state state)
अणु
	पूर्णांक status;

	vdbg_prपूर्णांकk(TPACPI_DBG_RFKILL,
		"will attempt to %s bluetooth\n",
		(state == TPACPI_RFK_RADIO_ON) ? "enable" : "disable");

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	अगर (dbg_bluetoothemul) अणु
		tpacpi_bluetooth_emulstate = (state == TPACPI_RFK_RADIO_ON);
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	अगर (state == TPACPI_RFK_RADIO_ON)
		status = TP_ACPI_BLUETOOTH_RADIOSSW
			  | TP_ACPI_BLUETOOTH_RESUMECTRL;
	अन्यथा
		status = 0;

	अगर (!acpi_evalf(hkey_handle, शून्य, "SBDC", "vd", status))
		वापस -EIO;

	वापस 0;
पूर्ण

/* sysfs bluetooth enable ---------------------------------------------- */
अटल sमाप_प्रकार bluetooth_enable_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	वापस tpacpi_rfk_sysfs_enable_show(TPACPI_RFK_BLUETOOTH_SW_ID,
			attr, buf);
पूर्ण

अटल sमाप_प्रकार bluetooth_enable_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस tpacpi_rfk_sysfs_enable_store(TPACPI_RFK_BLUETOOTH_SW_ID,
				attr, buf, count);
पूर्ण

अटल DEVICE_ATTR_RW(bluetooth_enable);

/* --------------------------------------------------------------------- */

अटल काष्ठा attribute *bluetooth_attributes[] = अणु
	&dev_attr_bluetooth_enable.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group bluetooth_attr_group = अणु
	.attrs = bluetooth_attributes,
पूर्ण;

अटल स्थिर काष्ठा tpacpi_rfk_ops bluetooth_tprfk_ops = अणु
	.get_status = bluetooth_get_status,
	.set_status = bluetooth_set_status,
पूर्ण;

अटल व्योम bluetooth_shutकरोwn(व्योम)
अणु
	/* Order firmware to save current state to NVRAM */
	अगर (!acpi_evalf(शून्य, शून्य, "\\BLTH", "vd",
			TP_ACPI_BLTH_SAVE_STATE))
		pr_notice("failed to save bluetooth state to NVRAM\n");
	अन्यथा
		vdbg_prपूर्णांकk(TPACPI_DBG_RFKILL,
			"bluetooth state saved to NVRAM\n");
पूर्ण

अटल व्योम bluetooth_निकास(व्योम)
अणु
	sysfs_हटाओ_group(&tpacpi_pdev->dev.kobj,
			&bluetooth_attr_group);

	tpacpi_destroy_rfसमाप्त(TPACPI_RFK_BLUETOOTH_SW_ID);

	bluetooth_shutकरोwn();
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id bt_fwbug_list[] __initस्थिर = अणु
	अणु
		.ident = "ThinkPad E485",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_BOARD_NAME, "20KU"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "ThinkPad E585",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_BOARD_NAME, "20KV"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "ThinkPad A285 - 20MW",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_BOARD_NAME, "20MW"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "ThinkPad A285 - 20MX",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_BOARD_NAME, "20MX"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "ThinkPad A485 - 20MU",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_BOARD_NAME, "20MU"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "ThinkPad A485 - 20MV",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_BOARD_NAME, "20MV"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pci_device_id fwbug_cards_ids[] __initस्थिर = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x24F3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x24FD) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2526) पूर्ण,
	अणुपूर्ण
पूर्ण;


अटल पूर्णांक __init have_bt_fwbug(व्योम)
अणु
	/*
	 * Some AMD based ThinkPads have a firmware bug that calling
	 * "GBDC" will cause bluetooth on Intel wireless cards blocked
	 */
	अगर (dmi_check_प्रणाली(bt_fwbug_list) && pci_dev_present(fwbug_cards_ids)) अणु
		vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_RFKILL,
			FW_BUG "disable bluetooth subdriver for Intel cards\n");
		वापस 1;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक __init bluetooth_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	पूर्णांक res;
	पूर्णांक status = 0;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_RFKILL,
			"initializing bluetooth subdriver\n");

	TPACPI_ACPIHANDLE_INIT(hkey);

	/* bluetooth not supported on 570, 600e/x, 770e, 770x, A21e, A2xm/p,
	   G4x, R30, R31, R40e, R50e, T20-22, X20-21 */
	tp_features.bluetooth = !have_bt_fwbug() && hkey_handle &&
	    acpi_evalf(hkey_handle, &status, "GBDC", "qd");

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_RFKILL,
		"bluetooth is %s, status 0x%02x\n",
		str_supported(tp_features.bluetooth),
		status);

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	अगर (dbg_bluetoothemul) अणु
		tp_features.bluetooth = 1;
		pr_info("bluetooth switch emulation enabled\n");
	पूर्ण अन्यथा
#पूर्ण_अगर
	अगर (tp_features.bluetooth &&
	    !(status & TP_ACPI_BLUETOOTH_HWPRESENT)) अणु
		/* no bluetooth hardware present in प्रणाली */
		tp_features.bluetooth = 0;
		dbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_RFKILL,
			   "bluetooth hardware not installed\n");
	पूर्ण

	अगर (!tp_features.bluetooth)
		वापस 1;

	res = tpacpi_new_rfसमाप्त(TPACPI_RFK_BLUETOOTH_SW_ID,
				&bluetooth_tprfk_ops,
				RFKILL_TYPE_BLUETOOTH,
				TPACPI_RFK_BLUETOOTH_SW_NAME,
				true);
	अगर (res)
		वापस res;

	res = sysfs_create_group(&tpacpi_pdev->dev.kobj,
				&bluetooth_attr_group);
	अगर (res) अणु
		tpacpi_destroy_rfसमाप्त(TPACPI_RFK_BLUETOOTH_SW_ID);
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

/* procfs -------------------------------------------------------------- */
अटल पूर्णांक bluetooth_पढ़ो(काष्ठा seq_file *m)
अणु
	वापस tpacpi_rfk_procfs_पढ़ो(TPACPI_RFK_BLUETOOTH_SW_ID, m);
पूर्ण

अटल पूर्णांक bluetooth_ग_लिखो(अक्षर *buf)
अणु
	वापस tpacpi_rfk_procfs_ग_लिखो(TPACPI_RFK_BLUETOOTH_SW_ID, buf);
पूर्ण

अटल काष्ठा ibm_काष्ठा bluetooth_driver_data = अणु
	.name = "bluetooth",
	.पढ़ो = bluetooth_पढ़ो,
	.ग_लिखो = bluetooth_ग_लिखो,
	.निकास = bluetooth_निकास,
	.shutकरोwn = bluetooth_shutकरोwn,
पूर्ण;

/*************************************************************************
 * Wan subdriver
 */

क्रमागत अणु
	/* ACPI GWAN/SWAN bits */
	TP_ACPI_WANCARD_HWPRESENT	= 0x01,	/* Wan hw available */
	TP_ACPI_WANCARD_RADIOSSW	= 0x02,	/* Wan radio enabled */
	TP_ACPI_WANCARD_RESUMECTRL	= 0x04,	/* Wan state at resume:
						   0 = disable, 1 = enable */
पूर्ण;

#घोषणा TPACPI_RFK_WWAN_SW_NAME		"tpacpi_wwan_sw"

अटल पूर्णांक wan_get_status(व्योम)
अणु
	पूर्णांक status;

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	अगर (dbg_wwanemul)
		वापस (tpacpi_wwan_emulstate) ?
		       TPACPI_RFK_RADIO_ON : TPACPI_RFK_RADIO_OFF;
#पूर्ण_अगर

	अगर (!acpi_evalf(hkey_handle, &status, "GWAN", "d"))
		वापस -EIO;

	वापस ((status & TP_ACPI_WANCARD_RADIOSSW) != 0) ?
			TPACPI_RFK_RADIO_ON : TPACPI_RFK_RADIO_OFF;
पूर्ण

अटल पूर्णांक wan_set_status(क्रमागत tpacpi_rfसमाप्त_state state)
अणु
	पूर्णांक status;

	vdbg_prपूर्णांकk(TPACPI_DBG_RFKILL,
		"will attempt to %s wwan\n",
		(state == TPACPI_RFK_RADIO_ON) ? "enable" : "disable");

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	अगर (dbg_wwanemul) अणु
		tpacpi_wwan_emulstate = (state == TPACPI_RFK_RADIO_ON);
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	अगर (state == TPACPI_RFK_RADIO_ON)
		status = TP_ACPI_WANCARD_RADIOSSW
			 | TP_ACPI_WANCARD_RESUMECTRL;
	अन्यथा
		status = 0;

	अगर (!acpi_evalf(hkey_handle, शून्य, "SWAN", "vd", status))
		वापस -EIO;

	वापस 0;
पूर्ण

/* sysfs wan enable ---------------------------------------------------- */
अटल sमाप_प्रकार wan_enable_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	वापस tpacpi_rfk_sysfs_enable_show(TPACPI_RFK_WWAN_SW_ID,
			attr, buf);
पूर्ण

अटल sमाप_प्रकार wan_enable_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस tpacpi_rfk_sysfs_enable_store(TPACPI_RFK_WWAN_SW_ID,
			attr, buf, count);
पूर्ण

अटल DEVICE_ATTR(wwan_enable, S_IWUSR | S_IRUGO,
		   wan_enable_show, wan_enable_store);

/* --------------------------------------------------------------------- */

अटल काष्ठा attribute *wan_attributes[] = अणु
	&dev_attr_wwan_enable.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group wan_attr_group = अणु
	.attrs = wan_attributes,
पूर्ण;

अटल स्थिर काष्ठा tpacpi_rfk_ops wan_tprfk_ops = अणु
	.get_status = wan_get_status,
	.set_status = wan_set_status,
पूर्ण;

अटल व्योम wan_shutकरोwn(व्योम)
अणु
	/* Order firmware to save current state to NVRAM */
	अगर (!acpi_evalf(शून्य, शून्य, "\\WGSV", "vd",
			TP_ACPI_WGSV_SAVE_STATE))
		pr_notice("failed to save WWAN state to NVRAM\n");
	अन्यथा
		vdbg_prपूर्णांकk(TPACPI_DBG_RFKILL,
			"WWAN state saved to NVRAM\n");
पूर्ण

अटल व्योम wan_निकास(व्योम)
अणु
	sysfs_हटाओ_group(&tpacpi_pdev->dev.kobj,
		&wan_attr_group);

	tpacpi_destroy_rfसमाप्त(TPACPI_RFK_WWAN_SW_ID);

	wan_shutकरोwn();
पूर्ण

अटल पूर्णांक __init wan_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	पूर्णांक res;
	पूर्णांक status = 0;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_RFKILL,
			"initializing wan subdriver\n");

	TPACPI_ACPIHANDLE_INIT(hkey);

	tp_features.wan = hkey_handle &&
	    acpi_evalf(hkey_handle, &status, "GWAN", "qd");

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_RFKILL,
		"wan is %s, status 0x%02x\n",
		str_supported(tp_features.wan),
		status);

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	अगर (dbg_wwanemul) अणु
		tp_features.wan = 1;
		pr_info("wwan switch emulation enabled\n");
	पूर्ण अन्यथा
#पूर्ण_अगर
	अगर (tp_features.wan &&
	    !(status & TP_ACPI_WANCARD_HWPRESENT)) अणु
		/* no wan hardware present in प्रणाली */
		tp_features.wan = 0;
		dbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_RFKILL,
			   "wan hardware not installed\n");
	पूर्ण

	अगर (!tp_features.wan)
		वापस 1;

	res = tpacpi_new_rfसमाप्त(TPACPI_RFK_WWAN_SW_ID,
				&wan_tprfk_ops,
				RFKILL_TYPE_WWAN,
				TPACPI_RFK_WWAN_SW_NAME,
				true);
	अगर (res)
		वापस res;

	res = sysfs_create_group(&tpacpi_pdev->dev.kobj,
				&wan_attr_group);

	अगर (res) अणु
		tpacpi_destroy_rfसमाप्त(TPACPI_RFK_WWAN_SW_ID);
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

/* procfs -------------------------------------------------------------- */
अटल पूर्णांक wan_पढ़ो(काष्ठा seq_file *m)
अणु
	वापस tpacpi_rfk_procfs_पढ़ो(TPACPI_RFK_WWAN_SW_ID, m);
पूर्ण

अटल पूर्णांक wan_ग_लिखो(अक्षर *buf)
अणु
	वापस tpacpi_rfk_procfs_ग_लिखो(TPACPI_RFK_WWAN_SW_ID, buf);
पूर्ण

अटल काष्ठा ibm_काष्ठा wan_driver_data = अणु
	.name = "wan",
	.पढ़ो = wan_पढ़ो,
	.ग_लिखो = wan_ग_लिखो,
	.निकास = wan_निकास,
	.shutकरोwn = wan_shutकरोwn,
पूर्ण;

/*************************************************************************
 * UWB subdriver
 */

क्रमागत अणु
	/* ACPI GUWB/SUWB bits */
	TP_ACPI_UWB_HWPRESENT	= 0x01,	/* UWB hw available */
	TP_ACPI_UWB_RADIOSSW	= 0x02,	/* UWB radio enabled */
पूर्ण;

#घोषणा TPACPI_RFK_UWB_SW_NAME	"tpacpi_uwb_sw"

अटल पूर्णांक uwb_get_status(व्योम)
अणु
	पूर्णांक status;

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	अगर (dbg_uwbemul)
		वापस (tpacpi_uwb_emulstate) ?
		       TPACPI_RFK_RADIO_ON : TPACPI_RFK_RADIO_OFF;
#पूर्ण_अगर

	अगर (!acpi_evalf(hkey_handle, &status, "GUWB", "d"))
		वापस -EIO;

	वापस ((status & TP_ACPI_UWB_RADIOSSW) != 0) ?
			TPACPI_RFK_RADIO_ON : TPACPI_RFK_RADIO_OFF;
पूर्ण

अटल पूर्णांक uwb_set_status(क्रमागत tpacpi_rfसमाप्त_state state)
अणु
	पूर्णांक status;

	vdbg_prपूर्णांकk(TPACPI_DBG_RFKILL,
		"will attempt to %s UWB\n",
		(state == TPACPI_RFK_RADIO_ON) ? "enable" : "disable");

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	अगर (dbg_uwbemul) अणु
		tpacpi_uwb_emulstate = (state == TPACPI_RFK_RADIO_ON);
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	अगर (state == TPACPI_RFK_RADIO_ON)
		status = TP_ACPI_UWB_RADIOSSW;
	अन्यथा
		status = 0;

	अगर (!acpi_evalf(hkey_handle, शून्य, "SUWB", "vd", status))
		वापस -EIO;

	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

अटल स्थिर काष्ठा tpacpi_rfk_ops uwb_tprfk_ops = अणु
	.get_status = uwb_get_status,
	.set_status = uwb_set_status,
पूर्ण;

अटल व्योम uwb_निकास(व्योम)
अणु
	tpacpi_destroy_rfसमाप्त(TPACPI_RFK_UWB_SW_ID);
पूर्ण

अटल पूर्णांक __init uwb_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	पूर्णांक res;
	पूर्णांक status = 0;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_RFKILL,
			"initializing uwb subdriver\n");

	TPACPI_ACPIHANDLE_INIT(hkey);

	tp_features.uwb = hkey_handle &&
	    acpi_evalf(hkey_handle, &status, "GUWB", "qd");

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_RFKILL,
		"uwb is %s, status 0x%02x\n",
		str_supported(tp_features.uwb),
		status);

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	अगर (dbg_uwbemul) अणु
		tp_features.uwb = 1;
		pr_info("uwb switch emulation enabled\n");
	पूर्ण अन्यथा
#पूर्ण_अगर
	अगर (tp_features.uwb &&
	    !(status & TP_ACPI_UWB_HWPRESENT)) अणु
		/* no uwb hardware present in प्रणाली */
		tp_features.uwb = 0;
		dbg_prपूर्णांकk(TPACPI_DBG_INIT,
			   "uwb hardware not installed\n");
	पूर्ण

	अगर (!tp_features.uwb)
		वापस 1;

	res = tpacpi_new_rfसमाप्त(TPACPI_RFK_UWB_SW_ID,
				&uwb_tprfk_ops,
				RFKILL_TYPE_UWB,
				TPACPI_RFK_UWB_SW_NAME,
				false);
	वापस res;
पूर्ण

अटल काष्ठा ibm_काष्ठा uwb_driver_data = अणु
	.name = "uwb",
	.निकास = uwb_निकास,
	.flags.experimental = 1,
पूर्ण;

/*************************************************************************
 * Video subdriver
 */

#अगर_घोषित CONFIG_THINKPAD_ACPI_VIDEO

क्रमागत video_access_mode अणु
	TPACPI_VIDEO_NONE = 0,
	TPACPI_VIDEO_570,	/* 570 */
	TPACPI_VIDEO_770,	/* 600e/x, 770e, 770x */
	TPACPI_VIDEO_NEW,	/* all others */
पूर्ण;

क्रमागत अणु	/* video status flags, based on VIDEO_570 */
	TP_ACPI_VIDEO_S_LCD = 0x01,	/* LCD output enabled */
	TP_ACPI_VIDEO_S_CRT = 0x02,	/* CRT output enabled */
	TP_ACPI_VIDEO_S_DVI = 0x08,	/* DVI output enabled */
पूर्ण;

क्रमागत अणु  /* TPACPI_VIDEO_570 स्थिरants */
	TP_ACPI_VIDEO_570_PHSCMD = 0x87,	/* unknown magic स्थिरant :( */
	TP_ACPI_VIDEO_570_PHSMASK = 0x03,	/* PHS bits that map to
						 * video_status_flags */
	TP_ACPI_VIDEO_570_PHS2CMD = 0x8b,	/* unknown magic स्थिरant :( */
	TP_ACPI_VIDEO_570_PHS2SET = 0x80,	/* unknown magic स्थिरant :( */
पूर्ण;

अटल क्रमागत video_access_mode video_supported;
अटल पूर्णांक video_orig_स्वतःsw;

अटल पूर्णांक video_स्वतःsw_get(व्योम);
अटल पूर्णांक video_स्वतःsw_set(पूर्णांक enable);

TPACPI_HANDLE(vid, root,
	      "\\_SB.PCI.AGP.VGA",	/* 570 */
	      "\\_SB.PCI0.AGP0.VID0",	/* 600e/x, 770x */
	      "\\_SB.PCI0.VID0",	/* 770e */
	      "\\_SB.PCI0.VID",		/* A21e, G4x, R50e, X30, X40 */
	      "\\_SB.PCI0.AGP.VGA",	/* X100e and a few others */
	      "\\_SB.PCI0.AGP.VID",	/* all others */
	);				/* R30, R31 */

TPACPI_HANDLE(vid2, root, "\\_SB.PCI0.AGPB.VID");	/* G41 */

अटल पूर्णांक __init video_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	पूर्णांक ivga;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "initializing video subdriver\n");

	TPACPI_ACPIHANDLE_INIT(vid);
	अगर (tpacpi_is_ibm())
		TPACPI_ACPIHANDLE_INIT(vid2);

	अगर (vid2_handle && acpi_evalf(शून्य, &ivga, "\\IVGA", "d") && ivga)
		/* G41, assume IVGA करोesn't change */
		vid_handle = vid2_handle;

	अगर (!vid_handle)
		/* video चयनing not supported on R30, R31 */
		video_supported = TPACPI_VIDEO_NONE;
	अन्यथा अगर (tpacpi_is_ibm() &&
		 acpi_evalf(vid_handle, &video_orig_स्वतःsw, "SWIT", "qd"))
		/* 570 */
		video_supported = TPACPI_VIDEO_570;
	अन्यथा अगर (tpacpi_is_ibm() &&
		 acpi_evalf(vid_handle, &video_orig_स्वतःsw, "^VADL", "qd"))
		/* 600e/x, 770e, 770x */
		video_supported = TPACPI_VIDEO_770;
	अन्यथा
		/* all others */
		video_supported = TPACPI_VIDEO_NEW;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "video is %s, mode %d\n",
		str_supported(video_supported != TPACPI_VIDEO_NONE),
		video_supported);

	वापस (video_supported != TPACPI_VIDEO_NONE) ? 0 : 1;
पूर्ण

अटल व्योम video_निकास(व्योम)
अणु
	dbg_prपूर्णांकk(TPACPI_DBG_EXIT,
		   "restoring original video autoswitch mode\n");
	अगर (video_स्वतःsw_set(video_orig_स्वतःsw))
		pr_err("error while trying to restore original video autoswitch mode\n");
पूर्ण

अटल पूर्णांक video_outमाला_दोw_get(व्योम)
अणु
	पूर्णांक status = 0;
	पूर्णांक i;

	चयन (video_supported) अणु
	हाल TPACPI_VIDEO_570:
		अगर (!acpi_evalf(शून्य, &i, "\\_SB.PHS", "dd",
				 TP_ACPI_VIDEO_570_PHSCMD))
			वापस -EIO;
		status = i & TP_ACPI_VIDEO_570_PHSMASK;
		अवरोध;
	हाल TPACPI_VIDEO_770:
		अगर (!acpi_evalf(शून्य, &i, "\\VCDL", "d"))
			वापस -EIO;
		अगर (i)
			status |= TP_ACPI_VIDEO_S_LCD;
		अगर (!acpi_evalf(शून्य, &i, "\\VCDC", "d"))
			वापस -EIO;
		अगर (i)
			status |= TP_ACPI_VIDEO_S_CRT;
		अवरोध;
	हाल TPACPI_VIDEO_NEW:
		अगर (!acpi_evalf(शून्य, शून्य, "\\VUPS", "vd", 1) ||
		    !acpi_evalf(शून्य, &i, "\\VCDC", "d"))
			वापस -EIO;
		अगर (i)
			status |= TP_ACPI_VIDEO_S_CRT;

		अगर (!acpi_evalf(शून्य, शून्य, "\\VUPS", "vd", 0) ||
		    !acpi_evalf(शून्य, &i, "\\VCDL", "d"))
			वापस -EIO;
		अगर (i)
			status |= TP_ACPI_VIDEO_S_LCD;
		अगर (!acpi_evalf(शून्य, &i, "\\VCDD", "d"))
			वापस -EIO;
		अगर (i)
			status |= TP_ACPI_VIDEO_S_DVI;
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक video_outमाला_दोw_set(पूर्णांक status)
अणु
	पूर्णांक स्वतःsw;
	पूर्णांक res = 0;

	चयन (video_supported) अणु
	हाल TPACPI_VIDEO_570:
		res = acpi_evalf(शून्य, शून्य,
				 "\\_SB.PHS2", "vdd",
				 TP_ACPI_VIDEO_570_PHS2CMD,
				 status | TP_ACPI_VIDEO_570_PHS2SET);
		अवरोध;
	हाल TPACPI_VIDEO_770:
		स्वतःsw = video_स्वतःsw_get();
		अगर (स्वतःsw < 0)
			वापस स्वतःsw;

		res = video_स्वतःsw_set(1);
		अगर (res)
			वापस res;
		res = acpi_evalf(vid_handle, शून्य,
				 "ASWT", "vdd", status * 0x100, 0);
		अगर (!स्वतःsw && video_स्वतःsw_set(स्वतःsw)) अणु
			pr_err("video auto-switch left enabled due to error\n");
			वापस -EIO;
		पूर्ण
		अवरोध;
	हाल TPACPI_VIDEO_NEW:
		res = acpi_evalf(शून्य, शून्य, "\\VUPS", "vd", 0x80) &&
		      acpi_evalf(शून्य, शून्य, "\\VSDS", "vdd", status, 1);
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस (res) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक video_स्वतःsw_get(व्योम)
अणु
	पूर्णांक स्वतःsw = 0;

	चयन (video_supported) अणु
	हाल TPACPI_VIDEO_570:
		अगर (!acpi_evalf(vid_handle, &स्वतःsw, "SWIT", "d"))
			वापस -EIO;
		अवरोध;
	हाल TPACPI_VIDEO_770:
	हाल TPACPI_VIDEO_NEW:
		अगर (!acpi_evalf(vid_handle, &स्वतःsw, "^VDEE", "d"))
			वापस -EIO;
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस स्वतःsw & 1;
पूर्ण

अटल पूर्णांक video_स्वतःsw_set(पूर्णांक enable)
अणु
	अगर (!acpi_evalf(vid_handle, शून्य, "_DOS", "vd", (enable) ? 1 : 0))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक video_outमाला_दोw_cycle(व्योम)
अणु
	पूर्णांक स्वतःsw = video_स्वतःsw_get();
	पूर्णांक res;

	अगर (स्वतःsw < 0)
		वापस स्वतःsw;

	चयन (video_supported) अणु
	हाल TPACPI_VIDEO_570:
		res = video_स्वतःsw_set(1);
		अगर (res)
			वापस res;
		res = acpi_evalf(ec_handle, शून्य, "_Q16", "v");
		अवरोध;
	हाल TPACPI_VIDEO_770:
	हाल TPACPI_VIDEO_NEW:
		res = video_स्वतःsw_set(1);
		अगर (res)
			वापस res;
		res = acpi_evalf(vid_handle, शून्य, "VSWT", "v");
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण
	अगर (!स्वतःsw && video_स्वतःsw_set(स्वतःsw)) अणु
		pr_err("video auto-switch left enabled due to error\n");
		वापस -EIO;
	पूर्ण

	वापस (res) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक video_expand_toggle(व्योम)
अणु
	चयन (video_supported) अणु
	हाल TPACPI_VIDEO_570:
		वापस acpi_evalf(ec_handle, शून्य, "_Q17", "v") ?
			0 : -EIO;
	हाल TPACPI_VIDEO_770:
		वापस acpi_evalf(vid_handle, शून्य, "VEXP", "v") ?
			0 : -EIO;
	हाल TPACPI_VIDEO_NEW:
		वापस acpi_evalf(शून्य, शून्य, "\\VEXP", "v") ?
			0 : -EIO;
	शेष:
		वापस -ENOSYS;
	पूर्ण
	/* not reached */
पूर्ण

अटल पूर्णांक video_पढ़ो(काष्ठा seq_file *m)
अणु
	पूर्णांक status, स्वतःsw;

	अगर (video_supported == TPACPI_VIDEO_NONE) अणु
		seq_म_लिखो(m, "status:\t\tnot supported\n");
		वापस 0;
	पूर्ण

	/* Even पढ़ोs can crash X.org, so... */
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	status = video_outमाला_दोw_get();
	अगर (status < 0)
		वापस status;

	स्वतःsw = video_स्वतःsw_get();
	अगर (स्वतःsw < 0)
		वापस स्वतःsw;

	seq_म_लिखो(m, "status:\t\tsupported\n");
	seq_म_लिखो(m, "lcd:\t\t%s\n", enabled(status, 0));
	seq_म_लिखो(m, "crt:\t\t%s\n", enabled(status, 1));
	अगर (video_supported == TPACPI_VIDEO_NEW)
		seq_म_लिखो(m, "dvi:\t\t%s\n", enabled(status, 3));
	seq_म_लिखो(m, "auto:\t\t%s\n", enabled(स्वतःsw, 0));
	seq_म_लिखो(m, "commands:\tlcd_enable, lcd_disable\n");
	seq_म_लिखो(m, "commands:\tcrt_enable, crt_disable\n");
	अगर (video_supported == TPACPI_VIDEO_NEW)
		seq_म_लिखो(m, "commands:\tdvi_enable, dvi_disable\n");
	seq_म_लिखो(m, "commands:\tauto_enable, auto_disable\n");
	seq_म_लिखो(m, "commands:\tvideo_switch, expand_toggle\n");

	वापस 0;
पूर्ण

अटल पूर्णांक video_ग_लिखो(अक्षर *buf)
अणु
	अक्षर *cmd;
	पूर्णांक enable, disable, status;
	पूर्णांक res;

	अगर (video_supported == TPACPI_VIDEO_NONE)
		वापस -ENODEV;

	/* Even पढ़ोs can crash X.org, let alone ग_लिखोs... */
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	enable = 0;
	disable = 0;

	जबतक ((cmd = strsep(&buf, ","))) अणु
		अगर (म_मापcmp(cmd, "lcd_enable") == 0) अणु
			enable |= TP_ACPI_VIDEO_S_LCD;
		पूर्ण अन्यथा अगर (म_मापcmp(cmd, "lcd_disable") == 0) अणु
			disable |= TP_ACPI_VIDEO_S_LCD;
		पूर्ण अन्यथा अगर (म_मापcmp(cmd, "crt_enable") == 0) अणु
			enable |= TP_ACPI_VIDEO_S_CRT;
		पूर्ण अन्यथा अगर (म_मापcmp(cmd, "crt_disable") == 0) अणु
			disable |= TP_ACPI_VIDEO_S_CRT;
		पूर्ण अन्यथा अगर (video_supported == TPACPI_VIDEO_NEW &&
			   म_मापcmp(cmd, "dvi_enable") == 0) अणु
			enable |= TP_ACPI_VIDEO_S_DVI;
		पूर्ण अन्यथा अगर (video_supported == TPACPI_VIDEO_NEW &&
			   म_मापcmp(cmd, "dvi_disable") == 0) अणु
			disable |= TP_ACPI_VIDEO_S_DVI;
		पूर्ण अन्यथा अगर (म_मापcmp(cmd, "auto_enable") == 0) अणु
			res = video_स्वतःsw_set(1);
			अगर (res)
				वापस res;
		पूर्ण अन्यथा अगर (म_मापcmp(cmd, "auto_disable") == 0) अणु
			res = video_स्वतःsw_set(0);
			अगर (res)
				वापस res;
		पूर्ण अन्यथा अगर (म_मापcmp(cmd, "video_switch") == 0) अणु
			res = video_outमाला_दोw_cycle();
			अगर (res)
				वापस res;
		पूर्ण अन्यथा अगर (म_मापcmp(cmd, "expand_toggle") == 0) अणु
			res = video_expand_toggle();
			अगर (res)
				वापस res;
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (enable || disable) अणु
		status = video_outमाला_दोw_get();
		अगर (status < 0)
			वापस status;
		res = video_outमाला_दोw_set((status & ~disable) | enable);
		अगर (res)
			वापस res;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ibm_काष्ठा video_driver_data = अणु
	.name = "video",
	.पढ़ो = video_पढ़ो,
	.ग_लिखो = video_ग_लिखो,
	.निकास = video_निकास,
पूर्ण;

#पूर्ण_अगर /* CONFIG_THINKPAD_ACPI_VIDEO */

/*************************************************************************
 * Keyboard backlight subdriver
 */

अटल क्रमागत led_brightness kbdlight_brightness;
अटल DEFINE_MUTEX(kbdlight_mutex);

अटल पूर्णांक kbdlight_set_level(पूर्णांक level)
अणु
	पूर्णांक ret = 0;

	अगर (!hkey_handle)
		वापस -ENXIO;

	mutex_lock(&kbdlight_mutex);

	अगर (!acpi_evalf(hkey_handle, शून्य, "MLCS", "dd", level))
		ret = -EIO;
	अन्यथा
		kbdlight_brightness = level;

	mutex_unlock(&kbdlight_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक kbdlight_get_level(व्योम)
अणु
	पूर्णांक status = 0;

	अगर (!hkey_handle)
		वापस -ENXIO;

	अगर (!acpi_evalf(hkey_handle, &status, "MLCG", "dd", 0))
		वापस -EIO;

	अगर (status < 0)
		वापस status;

	वापस status & 0x3;
पूर्ण

अटल bool kbdlight_is_supported(व्योम)
अणु
	पूर्णांक status = 0;

	अगर (!hkey_handle)
		वापस false;

	अगर (!acpi_has_method(hkey_handle, "MLCG")) अणु
		vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "kbdlight MLCG is unavailable\n");
		वापस false;
	पूर्ण

	अगर (!acpi_evalf(hkey_handle, &status, "MLCG", "qdd", 0)) अणु
		vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "kbdlight MLCG failed\n");
		वापस false;
	पूर्ण

	अगर (status < 0) अणु
		vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "kbdlight MLCG err: %d\n", status);
		वापस false;
	पूर्ण

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "kbdlight MLCG returned 0x%x\n", status);
	/*
	 * Guessed test क्रम keyboard backlight:
	 *
	 * Machines with backlight keyboard वापस:
	 *   b010100000010000000XX - ThinkPad X1 Carbon 3rd
	 *   b110100010010000000XX - ThinkPad x230
	 *   b010100000010000000XX - ThinkPad x240
	 *   b010100000010000000XX - ThinkPad W541
	 * (XX is current backlight level)
	 *
	 * Machines without backlight keyboard वापस:
	 *   b10100001000000000000 - ThinkPad x230
	 *   b10110001000000000000 - ThinkPad E430
	 *   b00000000000000000000 - ThinkPad E450
	 *
	 * Candidate BITs क्रम detection test (XOR):
	 *   b01000000001000000000
	 *              ^
	 */
	वापस status & BIT(9);
पूर्ण

अटल पूर्णांक kbdlight_sysfs_set(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness brightness)
अणु
	वापस kbdlight_set_level(brightness);
पूर्ण

अटल क्रमागत led_brightness kbdlight_sysfs_get(काष्ठा led_classdev *led_cdev)
अणु
	पूर्णांक level;

	level = kbdlight_get_level();
	अगर (level < 0)
		वापस 0;

	वापस level;
पूर्ण

अटल काष्ठा tpacpi_led_classdev tpacpi_led_kbdlight = अणु
	.led_classdev = अणु
		.name		= "tpacpi::kbd_backlight",
		.max_brightness	= 2,
		.flags		= LED_BRIGHT_HW_CHANGED,
		.brightness_set_blocking = &kbdlight_sysfs_set,
		.brightness_get	= &kbdlight_sysfs_get,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init kbdlight_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	पूर्णांक rc;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "initializing kbdlight subdriver\n");

	TPACPI_ACPIHANDLE_INIT(hkey);

	अगर (!kbdlight_is_supported()) अणु
		tp_features.kbdlight = 0;
		vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "kbdlight is unsupported\n");
		वापस 1;
	पूर्ण

	kbdlight_brightness = kbdlight_sysfs_get(शून्य);
	tp_features.kbdlight = 1;

	rc = led_classdev_रेजिस्टर(&tpacpi_pdev->dev,
				   &tpacpi_led_kbdlight.led_classdev);
	अगर (rc < 0) अणु
		tp_features.kbdlight = 0;
		वापस rc;
	पूर्ण

	tpacpi_hotkey_driver_mask_set(hotkey_driver_mask |
				      TP_ACPI_HKEY_KBD_LIGHT_MASK);
	वापस 0;
पूर्ण

अटल व्योम kbdlight_निकास(व्योम)
अणु
	led_classdev_unरेजिस्टर(&tpacpi_led_kbdlight.led_classdev);
पूर्ण

अटल पूर्णांक kbdlight_set_level_and_update(पूर्णांक level)
अणु
	पूर्णांक ret;
	काष्ठा led_classdev *led_cdev;

	ret = kbdlight_set_level(level);
	led_cdev = &tpacpi_led_kbdlight.led_classdev;

	अगर (ret == 0 && !(led_cdev->flags & LED_SUSPENDED))
		led_cdev->brightness = level;

	वापस ret;
पूर्ण

अटल पूर्णांक kbdlight_पढ़ो(काष्ठा seq_file *m)
अणु
	पूर्णांक level;

	अगर (!tp_features.kbdlight) अणु
		seq_म_लिखो(m, "status:\t\tnot supported\n");
	पूर्ण अन्यथा अणु
		level = kbdlight_get_level();
		अगर (level < 0)
			seq_म_लिखो(m, "status:\t\terror %d\n", level);
		अन्यथा
			seq_म_लिखो(m, "status:\t\t%d\n", level);
		seq_म_लिखो(m, "commands:\t0, 1, 2\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kbdlight_ग_लिखो(अक्षर *buf)
अणु
	अक्षर *cmd;
	पूर्णांक res, level = -EINVAL;

	अगर (!tp_features.kbdlight)
		वापस -ENODEV;

	जबतक ((cmd = strsep(&buf, ","))) अणु
		res = kstrtoपूर्णांक(cmd, 10, &level);
		अगर (res < 0)
			वापस res;
	पूर्ण

	अगर (level >= 3 || level < 0)
		वापस -EINVAL;

	वापस kbdlight_set_level_and_update(level);
पूर्ण

अटल व्योम kbdlight_suspend(व्योम)
अणु
	काष्ठा led_classdev *led_cdev;

	अगर (!tp_features.kbdlight)
		वापस;

	led_cdev = &tpacpi_led_kbdlight.led_classdev;
	led_update_brightness(led_cdev);
	led_classdev_suspend(led_cdev);
पूर्ण

अटल व्योम kbdlight_resume(व्योम)
अणु
	अगर (!tp_features.kbdlight)
		वापस;

	led_classdev_resume(&tpacpi_led_kbdlight.led_classdev);
पूर्ण

अटल काष्ठा ibm_काष्ठा kbdlight_driver_data = अणु
	.name = "kbdlight",
	.पढ़ो = kbdlight_पढ़ो,
	.ग_लिखो = kbdlight_ग_लिखो,
	.suspend = kbdlight_suspend,
	.resume = kbdlight_resume,
	.निकास = kbdlight_निकास,
पूर्ण;

/*************************************************************************
 * Light (thinklight) subdriver
 */

TPACPI_HANDLE(lght, root, "\\LGHT");	/* A21e, A2xm/p, T20-22, X20-21 */
TPACPI_HANDLE(ledb, ec, "LEDB");		/* G4x */

अटल पूर्णांक light_get_status(व्योम)
अणु
	पूर्णांक status = 0;

	अगर (tp_features.light_status) अणु
		अगर (!acpi_evalf(ec_handle, &status, "KBLT", "d"))
			वापस -EIO;
		वापस (!!status);
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक light_set_status(पूर्णांक status)
अणु
	पूर्णांक rc;

	अगर (tp_features.light) अणु
		अगर (cmos_handle) अणु
			rc = acpi_evalf(cmos_handle, शून्य, शून्य, "vd",
					(status) ?
						TP_CMOS_THINKLIGHT_ON :
						TP_CMOS_THINKLIGHT_OFF);
		पूर्ण अन्यथा अणु
			rc = acpi_evalf(lght_handle, शून्य, शून्य, "vd",
					(status) ? 1 : 0);
		पूर्ण
		वापस (rc) ? 0 : -EIO;
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक light_sysfs_set(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness brightness)
अणु
	वापस light_set_status((brightness != LED_OFF) ?
				TPACPI_LED_ON : TPACPI_LED_OFF);
पूर्ण

अटल क्रमागत led_brightness light_sysfs_get(काष्ठा led_classdev *led_cdev)
अणु
	वापस (light_get_status() == 1) ? LED_FULL : LED_OFF;
पूर्ण

अटल काष्ठा tpacpi_led_classdev tpacpi_led_thinklight = अणु
	.led_classdev = अणु
		.name		= "tpacpi::thinklight",
		.brightness_set_blocking = &light_sysfs_set,
		.brightness_get	= &light_sysfs_get,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init light_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	पूर्णांक rc;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "initializing light subdriver\n");

	अगर (tpacpi_is_ibm()) अणु
		TPACPI_ACPIHANDLE_INIT(ledb);
		TPACPI_ACPIHANDLE_INIT(lght);
	पूर्ण
	TPACPI_ACPIHANDLE_INIT(cmos);

	/* light not supported on 570, 600e/x, 770e, 770x, G4x, R30, R31 */
	tp_features.light = (cmos_handle || lght_handle) && !ledb_handle;

	अगर (tp_features.light)
		/* light status not supported on
		   570, 600e/x, 770e, 770x, G4x, R30, R31, R32, X20 */
		tp_features.light_status =
			acpi_evalf(ec_handle, शून्य, "KBLT", "qv");

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "light is %s, light status is %s\n",
		str_supported(tp_features.light),
		str_supported(tp_features.light_status));

	अगर (!tp_features.light)
		वापस 1;

	rc = led_classdev_रेजिस्टर(&tpacpi_pdev->dev,
				   &tpacpi_led_thinklight.led_classdev);

	अगर (rc < 0) अणु
		tp_features.light = 0;
		tp_features.light_status = 0;
	पूर्ण अन्यथा  अणु
		rc = 0;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम light_निकास(व्योम)
अणु
	led_classdev_unरेजिस्टर(&tpacpi_led_thinklight.led_classdev);
पूर्ण

अटल पूर्णांक light_पढ़ो(काष्ठा seq_file *m)
अणु
	पूर्णांक status;

	अगर (!tp_features.light) अणु
		seq_म_लिखो(m, "status:\t\tnot supported\n");
	पूर्ण अन्यथा अगर (!tp_features.light_status) अणु
		seq_म_लिखो(m, "status:\t\tunknown\n");
		seq_म_लिखो(m, "commands:\ton, off\n");
	पूर्ण अन्यथा अणु
		status = light_get_status();
		अगर (status < 0)
			वापस status;
		seq_म_लिखो(m, "status:\t\t%s\n", onoff(status, 0));
		seq_म_लिखो(m, "commands:\ton, off\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक light_ग_लिखो(अक्षर *buf)
अणु
	अक्षर *cmd;
	पूर्णांक newstatus = 0;

	अगर (!tp_features.light)
		वापस -ENODEV;

	जबतक ((cmd = strsep(&buf, ","))) अणु
		अगर (म_मापcmp(cmd, "on") == 0) अणु
			newstatus = 1;
		पूर्ण अन्यथा अगर (म_मापcmp(cmd, "off") == 0) अणु
			newstatus = 0;
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण

	वापस light_set_status(newstatus);
पूर्ण

अटल काष्ठा ibm_काष्ठा light_driver_data = अणु
	.name = "light",
	.पढ़ो = light_पढ़ो,
	.ग_लिखो = light_ग_लिखो,
	.निकास = light_निकास,
पूर्ण;

/*************************************************************************
 * CMOS subdriver
 */

/* sysfs cmos_command -------------------------------------------------- */
अटल sमाप_प्रकार cmos_command_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ cmos_cmd;
	पूर्णांक res;

	अगर (parse_म_से_अदीर्घ(buf, 21, &cmos_cmd))
		वापस -EINVAL;

	res = issue_thinkpad_cmos_command(cmos_cmd);
	वापस (res) ? res : count;
पूर्ण

अटल DEVICE_ATTR_WO(cmos_command);

/* --------------------------------------------------------------------- */

अटल पूर्णांक __init cmos_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	पूर्णांक res;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT,
		"initializing cmos commands subdriver\n");

	TPACPI_ACPIHANDLE_INIT(cmos);

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "cmos commands are %s\n",
		str_supported(cmos_handle != शून्य));

	res = device_create_file(&tpacpi_pdev->dev, &dev_attr_cmos_command);
	अगर (res)
		वापस res;

	वापस (cmos_handle) ? 0 : 1;
पूर्ण

अटल व्योम cmos_निकास(व्योम)
अणु
	device_हटाओ_file(&tpacpi_pdev->dev, &dev_attr_cmos_command);
पूर्ण

अटल पूर्णांक cmos_पढ़ो(काष्ठा seq_file *m)
अणु
	/* cmos not supported on 570, 600e/x, 770e, 770x, A21e, A2xm/p,
	   R30, R31, T20-22, X20-21 */
	अगर (!cmos_handle)
		seq_म_लिखो(m, "status:\t\tnot supported\n");
	अन्यथा अणु
		seq_म_लिखो(m, "status:\t\tsupported\n");
		seq_म_लिखो(m, "commands:\t<cmd> (<cmd> is 0-21)\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cmos_ग_लिखो(अक्षर *buf)
अणु
	अक्षर *cmd;
	पूर्णांक cmos_cmd, res;

	जबतक ((cmd = strsep(&buf, ","))) अणु
		अगर (माला_पूछो(cmd, "%u", &cmos_cmd) == 1 &&
		    cmos_cmd >= 0 && cmos_cmd <= 21) अणु
			/* cmos_cmd set */
		पूर्ण अन्यथा
			वापस -EINVAL;

		res = issue_thinkpad_cmos_command(cmos_cmd);
		अगर (res)
			वापस res;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ibm_काष्ठा cmos_driver_data = अणु
	.name = "cmos",
	.पढ़ो = cmos_पढ़ो,
	.ग_लिखो = cmos_ग_लिखो,
	.निकास = cmos_निकास,
पूर्ण;

/*************************************************************************
 * LED subdriver
 */

क्रमागत led_access_mode अणु
	TPACPI_LED_NONE = 0,
	TPACPI_LED_570,	/* 570 */
	TPACPI_LED_OLD,	/* 600e/x, 770e, 770x, A21e, A2xm/p, T20-22, X20-21 */
	TPACPI_LED_NEW,	/* all others */
पूर्ण;

क्रमागत अणु	/* For TPACPI_LED_OLD */
	TPACPI_LED_EC_HLCL = 0x0c,	/* EC reg to get led to घातer on */
	TPACPI_LED_EC_HLBL = 0x0d,	/* EC reg to blink a lit led */
	TPACPI_LED_EC_HLMS = 0x0e,	/* EC reg to select led to command */
पूर्ण;

अटल क्रमागत led_access_mode led_supported;

अटल acpi_handle led_handle;

#घोषणा TPACPI_LED_NUMLEDS 16
अटल काष्ठा tpacpi_led_classdev *tpacpi_leds;
अटल क्रमागत led_status_t tpacpi_led_state_cache[TPACPI_LED_NUMLEDS];
अटल स्थिर अक्षर * स्थिर tpacpi_led_names[TPACPI_LED_NUMLEDS] = अणु
	/* there's a limit of 19 अक्षरs + शून्य beक्रमe 2.6.26 */
	"tpacpi::power",
	"tpacpi:orange:batt",
	"tpacpi:green:batt",
	"tpacpi::dock_active",
	"tpacpi::bay_active",
	"tpacpi::dock_batt",
	"tpacpi::unknown_led",
	"tpacpi::standby",
	"tpacpi::dock_status1",
	"tpacpi::dock_status2",
	"tpacpi::unknown_led2",
	"tpacpi::unknown_led3",
	"tpacpi::thinkvantage",
पूर्ण;
#घोषणा TPACPI_SAFE_LEDS	0x1081U

अटल अंतरभूत bool tpacpi_is_led_restricted(स्थिर अचिन्हित पूर्णांक led)
अणु
#अगर_घोषित CONFIG_THINKPAD_ACPI_UNSAFE_LEDS
	वापस false;
#अन्यथा
	वापस (1U & (TPACPI_SAFE_LEDS >> led)) == 0;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक led_get_status(स्थिर अचिन्हित पूर्णांक led)
अणु
	पूर्णांक status;
	क्रमागत led_status_t led_s;

	चयन (led_supported) अणु
	हाल TPACPI_LED_570:
		अगर (!acpi_evalf(ec_handle,
				&status, "GLED", "dd", 1 << led))
			वापस -EIO;
		led_s = (status == 0) ?
				TPACPI_LED_OFF :
				((status == 1) ?
					TPACPI_LED_ON :
					TPACPI_LED_BLINK);
		tpacpi_led_state_cache[led] = led_s;
		वापस led_s;
	शेष:
		वापस -ENXIO;
	पूर्ण

	/* not reached */
पूर्ण

अटल पूर्णांक led_set_status(स्थिर अचिन्हित पूर्णांक led,
			  स्थिर क्रमागत led_status_t ledstatus)
अणु
	/* off, on, blink. Index is led_status_t */
	अटल स्थिर अचिन्हित पूर्णांक led_sled_arg1[] = अणु 0, 1, 3 पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक led_led_arg1[] = अणु 0, 0x80, 0xc0 पूर्ण;

	पूर्णांक rc = 0;

	चयन (led_supported) अणु
	हाल TPACPI_LED_570:
		/* 570 */
		अगर (unlikely(led > 7))
			वापस -EINVAL;
		अगर (unlikely(tpacpi_is_led_restricted(led)))
			वापस -EPERM;
		अगर (!acpi_evalf(led_handle, शून्य, शून्य, "vdd",
				(1 << led), led_sled_arg1[ledstatus]))
			वापस -EIO;
		अवरोध;
	हाल TPACPI_LED_OLD:
		/* 600e/x, 770e, 770x, A21e, A2xm/p, T20-22, X20 */
		अगर (unlikely(led > 7))
			वापस -EINVAL;
		अगर (unlikely(tpacpi_is_led_restricted(led)))
			वापस -EPERM;
		rc = ec_ग_लिखो(TPACPI_LED_EC_HLMS, (1 << led));
		अगर (rc >= 0)
			rc = ec_ग_लिखो(TPACPI_LED_EC_HLBL,
				      (ledstatus == TPACPI_LED_BLINK) << led);
		अगर (rc >= 0)
			rc = ec_ग_लिखो(TPACPI_LED_EC_HLCL,
				      (ledstatus != TPACPI_LED_OFF) << led);
		अवरोध;
	हाल TPACPI_LED_NEW:
		/* all others */
		अगर (unlikely(led >= TPACPI_LED_NUMLEDS))
			वापस -EINVAL;
		अगर (unlikely(tpacpi_is_led_restricted(led)))
			वापस -EPERM;
		अगर (!acpi_evalf(led_handle, शून्य, शून्य, "vdd",
				led, led_led_arg1[ledstatus]))
			वापस -EIO;
		अवरोध;
	शेष:
		वापस -ENXIO;
	पूर्ण

	अगर (!rc)
		tpacpi_led_state_cache[led] = ledstatus;

	वापस rc;
पूर्ण

अटल पूर्णांक led_sysfs_set(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness brightness)
अणु
	काष्ठा tpacpi_led_classdev *data = container_of(led_cdev,
			     काष्ठा tpacpi_led_classdev, led_classdev);
	क्रमागत led_status_t new_state;

	अगर (brightness == LED_OFF)
		new_state = TPACPI_LED_OFF;
	अन्यथा अगर (tpacpi_led_state_cache[data->led] != TPACPI_LED_BLINK)
		new_state = TPACPI_LED_ON;
	अन्यथा
		new_state = TPACPI_LED_BLINK;

	वापस led_set_status(data->led, new_state);
पूर्ण

अटल पूर्णांक led_sysfs_blink_set(काष्ठा led_classdev *led_cdev,
			अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा tpacpi_led_classdev *data = container_of(led_cdev,
			     काष्ठा tpacpi_led_classdev, led_classdev);

	/* Can we choose the flash rate? */
	अगर (*delay_on == 0 && *delay_off == 0) अणु
		/* yes. set them to the hardware blink rate (1 Hz) */
		*delay_on = 500; /* ms */
		*delay_off = 500; /* ms */
	पूर्ण अन्यथा अगर ((*delay_on != 500) || (*delay_off != 500))
		वापस -EINVAL;

	वापस led_set_status(data->led, TPACPI_LED_BLINK);
पूर्ण

अटल क्रमागत led_brightness led_sysfs_get(काष्ठा led_classdev *led_cdev)
अणु
	पूर्णांक rc;

	काष्ठा tpacpi_led_classdev *data = container_of(led_cdev,
			     काष्ठा tpacpi_led_classdev, led_classdev);

	rc = led_get_status(data->led);

	अगर (rc == TPACPI_LED_OFF || rc < 0)
		rc = LED_OFF;	/* no error handling in led class :( */
	अन्यथा
		rc = LED_FULL;

	वापस rc;
पूर्ण

अटल व्योम led_निकास(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < TPACPI_LED_NUMLEDS; i++)
		led_classdev_unरेजिस्टर(&tpacpi_leds[i].led_classdev);

	kमुक्त(tpacpi_leds);
पूर्ण

अटल पूर्णांक __init tpacpi_init_led(अचिन्हित पूर्णांक led)
अणु
	/* LEDs with no name करोn't get रेजिस्टरed */
	अगर (!tpacpi_led_names[led])
		वापस 0;

	tpacpi_leds[led].led_classdev.brightness_set_blocking = &led_sysfs_set;
	tpacpi_leds[led].led_classdev.blink_set = &led_sysfs_blink_set;
	अगर (led_supported == TPACPI_LED_570)
		tpacpi_leds[led].led_classdev.brightness_get = &led_sysfs_get;

	tpacpi_leds[led].led_classdev.name = tpacpi_led_names[led];
	tpacpi_leds[led].led = led;

	वापस led_classdev_रेजिस्टर(&tpacpi_pdev->dev, &tpacpi_leds[led].led_classdev);
पूर्ण

अटल स्थिर काष्ठा tpacpi_quirk led_useful_qtable[] __initस्थिर = अणु
	TPACPI_Q_IBM('1', 'E', 0x009f), /* A30 */
	TPACPI_Q_IBM('1', 'N', 0x009f), /* A31 */
	TPACPI_Q_IBM('1', 'G', 0x009f), /* A31 */

	TPACPI_Q_IBM('1', 'I', 0x0097), /* T30 */
	TPACPI_Q_IBM('1', 'R', 0x0097), /* T40, T41, T42, R50, R51 */
	TPACPI_Q_IBM('7', '0', 0x0097), /* T43, R52 */
	TPACPI_Q_IBM('1', 'Y', 0x0097), /* T43 */
	TPACPI_Q_IBM('1', 'W', 0x0097), /* R50e */
	TPACPI_Q_IBM('1', 'V', 0x0097), /* R51 */
	TPACPI_Q_IBM('7', '8', 0x0097), /* R51e */
	TPACPI_Q_IBM('7', '6', 0x0097), /* R52 */

	TPACPI_Q_IBM('1', 'K', 0x00bf), /* X30 */
	TPACPI_Q_IBM('1', 'Q', 0x00bf), /* X31, X32 */
	TPACPI_Q_IBM('1', 'U', 0x00bf), /* X40 */
	TPACPI_Q_IBM('7', '4', 0x00bf), /* X41 */
	TPACPI_Q_IBM('7', '5', 0x00bf), /* X41t */

	TPACPI_Q_IBM('7', '9', 0x1f97), /* T60 (1) */
	TPACPI_Q_IBM('7', '7', 0x1f97), /* Z60* (1) */
	TPACPI_Q_IBM('7', 'F', 0x1f97), /* Z61* (1) */
	TPACPI_Q_IBM('7', 'B', 0x1fb7), /* X60 (1) */

	/* (1) - may have excess leds enabled on MSB */

	/* Defaults (order matters, keep last, करोn't reorder!) */
	अणु /* Lenovo */
	  .venकरोr = PCI_VENDOR_ID_LENOVO,
	  .bios = TPACPI_MATCH_ANY, .ec = TPACPI_MATCH_ANY,
	  .quirks = 0x1fffU,
	पूर्ण,
	अणु /* IBM ThinkPads with no EC version string */
	  .venकरोr = PCI_VENDOR_ID_IBM,
	  .bios = TPACPI_MATCH_ANY, .ec = TPACPI_MATCH_UNKNOWN,
	  .quirks = 0x00ffU,
	पूर्ण,
	अणु /* IBM ThinkPads with EC version string */
	  .venकरोr = PCI_VENDOR_ID_IBM,
	  .bios = TPACPI_MATCH_ANY, .ec = TPACPI_MATCH_ANY,
	  .quirks = 0x00bfU,
	पूर्ण,
पूर्ण;

अटल क्रमागत led_access_mode __init led_init_detect_mode(व्योम)
अणु
	acpi_status status;

	अगर (tpacpi_is_ibm()) अणु
		/* 570 */
		status = acpi_get_handle(ec_handle, "SLED", &led_handle);
		अगर (ACPI_SUCCESS(status))
			वापस TPACPI_LED_570;

		/* 600e/x, 770e, 770x, A21e, A2xm/p, T20-22, X20-21 */
		status = acpi_get_handle(ec_handle, "SYSL", &led_handle);
		अगर (ACPI_SUCCESS(status))
			वापस TPACPI_LED_OLD;
	पूर्ण

	/* most others */
	status = acpi_get_handle(ec_handle, "LED", &led_handle);
	अगर (ACPI_SUCCESS(status))
		वापस TPACPI_LED_NEW;

	/* R30, R31, and unknown firmwares */
	led_handle = शून्य;
	वापस TPACPI_LED_NONE;
पूर्ण

अटल पूर्णांक __init led_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;
	अचिन्हित दीर्घ useful_leds;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "initializing LED subdriver\n");

	led_supported = led_init_detect_mode();

	अगर (led_supported != TPACPI_LED_NONE) अणु
		useful_leds = tpacpi_check_quirks(led_useful_qtable,
				ARRAY_SIZE(led_useful_qtable));

		अगर (!useful_leds) अणु
			led_handle = शून्य;
			led_supported = TPACPI_LED_NONE;
		पूर्ण
	पूर्ण

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "LED commands are %s, mode %d\n",
		str_supported(led_supported), led_supported);

	अगर (led_supported == TPACPI_LED_NONE)
		वापस 1;

	tpacpi_leds = kसुस्मृति(TPACPI_LED_NUMLEDS, माप(*tpacpi_leds),
			      GFP_KERNEL);
	अगर (!tpacpi_leds) अणु
		pr_err("Out of memory for LED data\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < TPACPI_LED_NUMLEDS; i++) अणु
		tpacpi_leds[i].led = -1;

		अगर (!tpacpi_is_led_restricted(i) && test_bit(i, &useful_leds)) अणु
			rc = tpacpi_init_led(i);
			अगर (rc < 0) अणु
				led_निकास();
				वापस rc;
			पूर्ण
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_THINKPAD_ACPI_UNSAFE_LEDS
	pr_notice("warning: userspace override of important firmware LEDs is enabled\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

#घोषणा str_led_status(s) \
	((s) == TPACPI_LED_OFF ? "off" : \
		((s) == TPACPI_LED_ON ? "on" : "blinking"))

अटल पूर्णांक led_पढ़ो(काष्ठा seq_file *m)
अणु
	अगर (!led_supported) अणु
		seq_म_लिखो(m, "status:\t\tnot supported\n");
		वापस 0;
	पूर्ण
	seq_म_लिखो(m, "status:\t\tsupported\n");

	अगर (led_supported == TPACPI_LED_570) अणु
		/* 570 */
		पूर्णांक i, status;
		क्रम (i = 0; i < 8; i++) अणु
			status = led_get_status(i);
			अगर (status < 0)
				वापस -EIO;
			seq_म_लिखो(m, "%d:\t\t%s\n",
				       i, str_led_status(status));
		पूर्ण
	पूर्ण

	seq_म_लिखो(m, "commands:\t<led> on, <led> off, <led> blink (<led> is 0-15)\n");

	वापस 0;
पूर्ण

अटल पूर्णांक led_ग_लिखो(अक्षर *buf)
अणु
	अक्षर *cmd;
	पूर्णांक led, rc;
	क्रमागत led_status_t s;

	अगर (!led_supported)
		वापस -ENODEV;

	जबतक ((cmd = strsep(&buf, ","))) अणु
		अगर (माला_पूछो(cmd, "%d", &led) != 1)
			वापस -EINVAL;

		अगर (led < 0 || led > (TPACPI_LED_NUMLEDS - 1))
			वापस -ENODEV;

		अगर (tpacpi_leds[led].led < 0)
			वापस -ENODEV;

		अगर (म_माला(cmd, "off")) अणु
			s = TPACPI_LED_OFF;
		पूर्ण अन्यथा अगर (म_माला(cmd, "on")) अणु
			s = TPACPI_LED_ON;
		पूर्ण अन्यथा अगर (म_माला(cmd, "blink")) अणु
			s = TPACPI_LED_BLINK;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण

		rc = led_set_status(led, s);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ibm_काष्ठा led_driver_data = अणु
	.name = "led",
	.पढ़ो = led_पढ़ो,
	.ग_लिखो = led_ग_लिखो,
	.निकास = led_निकास,
पूर्ण;

/*************************************************************************
 * Beep subdriver
 */

TPACPI_HANDLE(beep, ec, "BEEP");	/* all except R30, R31 */

#घोषणा TPACPI_BEEP_Q1 0x0001

अटल स्थिर काष्ठा tpacpi_quirk beep_quirk_table[] __initस्थिर = अणु
	TPACPI_Q_IBM('I', 'M', TPACPI_BEEP_Q1), /* 570 */
	TPACPI_Q_IBM('I', 'U', TPACPI_BEEP_Q1), /* 570E - unverअगरied */
पूर्ण;

अटल पूर्णांक __init beep_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	अचिन्हित दीर्घ quirks;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "initializing beep subdriver\n");

	TPACPI_ACPIHANDLE_INIT(beep);

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "beep is %s\n",
		str_supported(beep_handle != शून्य));

	quirks = tpacpi_check_quirks(beep_quirk_table,
				     ARRAY_SIZE(beep_quirk_table));

	tp_features.beep_needs_two_args = !!(quirks & TPACPI_BEEP_Q1);

	वापस (beep_handle) ? 0 : 1;
पूर्ण

अटल पूर्णांक beep_पढ़ो(काष्ठा seq_file *m)
अणु
	अगर (!beep_handle)
		seq_म_लिखो(m, "status:\t\tnot supported\n");
	अन्यथा अणु
		seq_म_लिखो(m, "status:\t\tsupported\n");
		seq_म_लिखो(m, "commands:\t<cmd> (<cmd> is 0-17)\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक beep_ग_लिखो(अक्षर *buf)
अणु
	अक्षर *cmd;
	पूर्णांक beep_cmd;

	अगर (!beep_handle)
		वापस -ENODEV;

	जबतक ((cmd = strsep(&buf, ","))) अणु
		अगर (माला_पूछो(cmd, "%u", &beep_cmd) == 1 &&
		    beep_cmd >= 0 && beep_cmd <= 17) अणु
			/* beep_cmd set */
		पूर्ण अन्यथा
			वापस -EINVAL;
		अगर (tp_features.beep_needs_two_args) अणु
			अगर (!acpi_evalf(beep_handle, शून्य, शून्य, "vdd",
					beep_cmd, 0))
				वापस -EIO;
		पूर्ण अन्यथा अणु
			अगर (!acpi_evalf(beep_handle, शून्य, शून्य, "vd",
					beep_cmd))
				वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ibm_काष्ठा beep_driver_data = अणु
	.name = "beep",
	.पढ़ो = beep_पढ़ो,
	.ग_लिखो = beep_ग_लिखो,
पूर्ण;

/*************************************************************************
 * Thermal subdriver
 */

क्रमागत thermal_access_mode अणु
	TPACPI_THERMAL_NONE = 0,	/* No thermal support */
	TPACPI_THERMAL_ACPI_TMP07,	/* Use ACPI TMP0-7 */
	TPACPI_THERMAL_ACPI_UPDT,	/* Use ACPI TMP0-7 with UPDT */
	TPACPI_THERMAL_TPEC_8,		/* Use ACPI EC regs, 8 sensors */
	TPACPI_THERMAL_TPEC_16,		/* Use ACPI EC regs, 16 sensors */
पूर्ण;

क्रमागत अणु /* TPACPI_THERMAL_TPEC_* */
	TP_EC_THERMAL_TMP0 = 0x78,	/* ACPI EC regs TMP 0..7 */
	TP_EC_THERMAL_TMP8 = 0xC0,	/* ACPI EC regs TMP 8..15 */
	TP_EC_FUNCREV      = 0xEF,      /* ACPI EC Functional revision */
	TP_EC_THERMAL_TMP_NA = -128,	/* ACPI EC sensor not available */

	TPACPI_THERMAL_SENSOR_NA = -128000, /* Sensor not available */
पूर्ण;


#घोषणा TPACPI_MAX_THERMAL_SENSORS 16	/* Max thermal sensors supported */
काष्ठा ibm_thermal_sensors_काष्ठा अणु
	s32 temp[TPACPI_MAX_THERMAL_SENSORS];
पूर्ण;

अटल क्रमागत thermal_access_mode thermal_पढ़ो_mode;
अटल स्थिर काष्ठा attribute_group *thermal_attr_group;
अटल bool thermal_use_labels;

/* idx is zero-based */
अटल पूर्णांक thermal_get_sensor(पूर्णांक idx, s32 *value)
अणु
	पूर्णांक t;
	s8 पंचांगp;
	अक्षर पंचांगpi[5];

	t = TP_EC_THERMAL_TMP0;

	चयन (thermal_पढ़ो_mode) अणु
#अगर TPACPI_MAX_THERMAL_SENSORS >= 16
	हाल TPACPI_THERMAL_TPEC_16:
		अगर (idx >= 8 && idx <= 15) अणु
			t = TP_EC_THERMAL_TMP8;
			idx -= 8;
		पूर्ण
#पूर्ण_अगर
		fallthrough;
	हाल TPACPI_THERMAL_TPEC_8:
		अगर (idx <= 7) अणु
			अगर (!acpi_ec_पढ़ो(t + idx, &पंचांगp))
				वापस -EIO;
			*value = पंचांगp * 1000;
			वापस 0;
		पूर्ण
		अवरोध;

	हाल TPACPI_THERMAL_ACPI_UPDT:
		अगर (idx <= 7) अणु
			snम_लिखो(पंचांगpi, माप(पंचांगpi), "TMP%c", '0' + idx);
			अगर (!acpi_evalf(ec_handle, शून्य, "UPDT", "v"))
				वापस -EIO;
			अगर (!acpi_evalf(ec_handle, &t, पंचांगpi, "d"))
				वापस -EIO;
			*value = (t - 2732) * 100;
			वापस 0;
		पूर्ण
		अवरोध;

	हाल TPACPI_THERMAL_ACPI_TMP07:
		अगर (idx <= 7) अणु
			snम_लिखो(पंचांगpi, माप(पंचांगpi), "TMP%c", '0' + idx);
			अगर (!acpi_evalf(ec_handle, &t, पंचांगpi, "d"))
				वापस -EIO;
			अगर (t > 127 || t < -127)
				t = TP_EC_THERMAL_TMP_NA;
			*value = t * 1000;
			वापस 0;
		पूर्ण
		अवरोध;

	हाल TPACPI_THERMAL_NONE:
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक thermal_get_sensors(काष्ठा ibm_thermal_sensors_काष्ठा *s)
अणु
	पूर्णांक res, i;
	पूर्णांक n;

	n = 8;
	i = 0;

	अगर (!s)
		वापस -EINVAL;

	अगर (thermal_पढ़ो_mode == TPACPI_THERMAL_TPEC_16)
		n = 16;

	क्रम (i = 0 ; i < n; i++) अणु
		res = thermal_get_sensor(i, &s->temp[i]);
		अगर (res)
			वापस res;
	पूर्ण

	वापस n;
पूर्ण

अटल व्योम thermal_dump_all_sensors(व्योम)
अणु
	पूर्णांक n, i;
	काष्ठा ibm_thermal_sensors_काष्ठा t;

	n = thermal_get_sensors(&t);
	अगर (n <= 0)
		वापस;

	pr_notice("temperatures (Celsius):");

	क्रम (i = 0; i < n; i++) अणु
		अगर (t.temp[i] != TPACPI_THERMAL_SENSOR_NA)
			pr_cont(" %d", (पूर्णांक)(t.temp[i] / 1000));
		अन्यथा
			pr_cont(" N/A");
	पूर्ण

	pr_cont("\n");
पूर्ण

/* sysfs temp##_input -------------------------------------------------- */

अटल sमाप_प्रकार thermal_temp_input_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr =
					to_sensor_dev_attr(attr);
	पूर्णांक idx = sensor_attr->index;
	s32 value;
	पूर्णांक res;

	res = thermal_get_sensor(idx, &value);
	अगर (res)
		वापस res;
	अगर (value == TPACPI_THERMAL_SENSOR_NA)
		वापस -ENXIO;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", value);
पूर्ण

#घोषणा THERMAL_SENSOR_ATTR_TEMP(_idxA, _idxB) \
	 SENSOR_ATTR(temp##_idxA##_input, S_IRUGO, \
		     thermal_temp_input_show, शून्य, _idxB)

अटल काष्ठा sensor_device_attribute sensor_dev_attr_thermal_temp_input[] = अणु
	THERMAL_SENSOR_ATTR_TEMP(1, 0),
	THERMAL_SENSOR_ATTR_TEMP(2, 1),
	THERMAL_SENSOR_ATTR_TEMP(3, 2),
	THERMAL_SENSOR_ATTR_TEMP(4, 3),
	THERMAL_SENSOR_ATTR_TEMP(5, 4),
	THERMAL_SENSOR_ATTR_TEMP(6, 5),
	THERMAL_SENSOR_ATTR_TEMP(7, 6),
	THERMAL_SENSOR_ATTR_TEMP(8, 7),
	THERMAL_SENSOR_ATTR_TEMP(9, 8),
	THERMAL_SENSOR_ATTR_TEMP(10, 9),
	THERMAL_SENSOR_ATTR_TEMP(11, 10),
	THERMAL_SENSOR_ATTR_TEMP(12, 11),
	THERMAL_SENSOR_ATTR_TEMP(13, 12),
	THERMAL_SENSOR_ATTR_TEMP(14, 13),
	THERMAL_SENSOR_ATTR_TEMP(15, 14),
	THERMAL_SENSOR_ATTR_TEMP(16, 15),
पूर्ण;

#घोषणा THERMAL_ATTRS(X) \
	&sensor_dev_attr_thermal_temp_input[X].dev_attr.attr

अटल काष्ठा attribute *thermal_temp_input_attr[] = अणु
	THERMAL_ATTRS(8),
	THERMAL_ATTRS(9),
	THERMAL_ATTRS(10),
	THERMAL_ATTRS(11),
	THERMAL_ATTRS(12),
	THERMAL_ATTRS(13),
	THERMAL_ATTRS(14),
	THERMAL_ATTRS(15),
	THERMAL_ATTRS(0),
	THERMAL_ATTRS(1),
	THERMAL_ATTRS(2),
	THERMAL_ATTRS(3),
	THERMAL_ATTRS(4),
	THERMAL_ATTRS(5),
	THERMAL_ATTRS(6),
	THERMAL_ATTRS(7),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group thermal_temp_input16_group = अणु
	.attrs = thermal_temp_input_attr
पूर्ण;

अटल स्थिर काष्ठा attribute_group thermal_temp_input8_group = अणु
	.attrs = &thermal_temp_input_attr[8]
पूर्ण;

#अघोषित THERMAL_SENSOR_ATTR_TEMP
#अघोषित THERMAL_ATTRS

अटल sमाप_प्रकार temp1_label_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "CPU\n");
पूर्ण
अटल DEVICE_ATTR_RO(temp1_label);

अटल sमाप_प्रकार temp2_label_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "GPU\n");
पूर्ण
अटल DEVICE_ATTR_RO(temp2_label);

अटल काष्ठा attribute *temp_label_attributes[] = अणु
	&dev_attr_temp1_label.attr,
	&dev_attr_temp2_label.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group temp_label_attr_group = अणु
	.attrs = temp_label_attributes,
पूर्ण;

/* --------------------------------------------------------------------- */

अटल पूर्णांक __init thermal_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	u8 t, ta1, ta2, ver = 0;
	पूर्णांक i;
	पूर्णांक acpi_पंचांगp7;
	पूर्णांक res;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "initializing thermal subdriver\n");

	acpi_पंचांगp7 = acpi_evalf(ec_handle, शून्य, "TMP7", "qv");

	अगर (thinkpad_id.ec_model) अणु
		/*
		 * Direct EC access mode: sensors at रेजिस्टरs
		 * 0x78-0x7F, 0xC0-0xC7.  Registers वापस 0x00 क्रम
		 * non-implemented, thermal sensors वापस 0x80 when
		 * not available
		 * The above rule is unक्रमtunately flawed. This has been seen with
		 * 0xC2 (घातer supply ID) causing thermal control problems.
		 * The EC version can be determined by offset 0xEF and at least क्रम
		 * version 3 the Lenovo firmware team confirmed that रेजिस्टरs 0xC0-0xC7
		 * are not thermal रेजिस्टरs.
		 */
		अगर (!acpi_ec_पढ़ो(TP_EC_FUNCREV, &ver))
			pr_warn("Thinkpad ACPI EC unable to access EC version\n");

		ta1 = ta2 = 0;
		क्रम (i = 0; i < 8; i++) अणु
			अगर (acpi_ec_पढ़ो(TP_EC_THERMAL_TMP0 + i, &t)) अणु
				ta1 |= t;
			पूर्ण अन्यथा अणु
				ta1 = 0;
				अवरोध;
			पूर्ण
			अगर (ver < 3) अणु
				अगर (acpi_ec_पढ़ो(TP_EC_THERMAL_TMP8 + i, &t)) अणु
					ta2 |= t;
				पूर्ण अन्यथा अणु
					ta1 = 0;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (ta1 == 0) अणु
			/* This is sheer paranoia, but we handle it anyway */
			अगर (acpi_पंचांगp7) अणु
				pr_err("ThinkPad ACPI EC access misbehaving, falling back to ACPI TMPx access mode\n");
				thermal_पढ़ो_mode = TPACPI_THERMAL_ACPI_TMP07;
			पूर्ण अन्यथा अणु
				pr_err("ThinkPad ACPI EC access misbehaving, disabling thermal sensors access\n");
				thermal_पढ़ो_mode = TPACPI_THERMAL_NONE;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (ver >= 3) अणु
				thermal_पढ़ो_mode = TPACPI_THERMAL_TPEC_8;
				thermal_use_labels = true;
			पूर्ण अन्यथा अणु
				thermal_पढ़ो_mode =
					(ta2 != 0) ?
					TPACPI_THERMAL_TPEC_16 : TPACPI_THERMAL_TPEC_8;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (acpi_पंचांगp7) अणु
		अगर (tpacpi_is_ibm() &&
		    acpi_evalf(ec_handle, शून्य, "UPDT", "qv")) अणु
			/* 600e/x, 770e, 770x */
			thermal_पढ़ो_mode = TPACPI_THERMAL_ACPI_UPDT;
		पूर्ण अन्यथा अणु
			/* IBM/LENOVO DSDT EC.TMPx access, max 8 sensors */
			thermal_पढ़ो_mode = TPACPI_THERMAL_ACPI_TMP07;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* temperatures not supported on 570, G4x, R30, R31, R32 */
		thermal_पढ़ो_mode = TPACPI_THERMAL_NONE;
	पूर्ण

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "thermal is %s, mode %d\n",
		str_supported(thermal_पढ़ो_mode != TPACPI_THERMAL_NONE),
		thermal_पढ़ो_mode);

	चयन (thermal_पढ़ो_mode) अणु
	हाल TPACPI_THERMAL_TPEC_16:
		thermal_attr_group = &thermal_temp_input16_group;
		अवरोध;
	हाल TPACPI_THERMAL_TPEC_8:
	हाल TPACPI_THERMAL_ACPI_TMP07:
	हाल TPACPI_THERMAL_ACPI_UPDT:
		thermal_attr_group = &thermal_temp_input8_group;
		अवरोध;
	हाल TPACPI_THERMAL_NONE:
	शेष:
		वापस 1;
	पूर्ण

	res = sysfs_create_group(&tpacpi_hwmon->kobj, thermal_attr_group);
	अगर (res)
		वापस res;

	अगर (thermal_use_labels) अणु
		res = sysfs_create_group(&tpacpi_hwmon->kobj, &temp_label_attr_group);
		अगर (res) अणु
			sysfs_हटाओ_group(&tpacpi_hwmon->kobj, thermal_attr_group);
			वापस res;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम thermal_निकास(व्योम)
अणु
	अगर (thermal_attr_group)
		sysfs_हटाओ_group(&tpacpi_hwmon->kobj, thermal_attr_group);

	अगर (thermal_use_labels)
		sysfs_हटाओ_group(&tpacpi_hwmon->kobj, &temp_label_attr_group);
पूर्ण

अटल पूर्णांक thermal_पढ़ो(काष्ठा seq_file *m)
अणु
	पूर्णांक n, i;
	काष्ठा ibm_thermal_sensors_काष्ठा t;

	n = thermal_get_sensors(&t);
	अगर (unlikely(n < 0))
		वापस n;

	seq_म_लिखो(m, "temperatures:\t");

	अगर (n > 0) अणु
		क्रम (i = 0; i < (n - 1); i++)
			seq_म_लिखो(m, "%d ", t.temp[i] / 1000);
		seq_म_लिखो(m, "%d\n", t.temp[i] / 1000);
	पूर्ण अन्यथा
		seq_म_लिखो(m, "not supported\n");

	वापस 0;
पूर्ण

अटल काष्ठा ibm_काष्ठा thermal_driver_data = अणु
	.name = "thermal",
	.पढ़ो = thermal_पढ़ो,
	.निकास = thermal_निकास,
पूर्ण;

/*************************************************************************
 * Backlight/brightness subdriver
 */

#घोषणा TPACPI_BACKLIGHT_DEV_NAME "thinkpad_screen"

/*
 * ThinkPads can पढ़ो brightness from two places: EC HBRV (0x31), or
 * CMOS NVRAM byte 0x5E, bits 0-3.
 *
 * EC HBRV (0x31) has the following layout
 *   Bit 7: unknown function
 *   Bit 6: unknown function
 *   Bit 5: Z: honour scale changes, NZ: ignore scale changes
 *   Bit 4: must be set to zero to aव्योम problems
 *   Bit 3-0: backlight brightness level
 *
 * brightness_get_raw वापसs status data in the HBRV layout
 *
 * WARNING: The X61 has been verअगरied to use HBRV क्रम something अन्यथा, so
 * this should be used _only_ on IBM ThinkPads, and maybe with some careful
 * testing on the very early *60 Lenovo models...
 */

क्रमागत अणु
	TP_EC_BACKLIGHT = 0x31,

	/* TP_EC_BACKLIGHT biपंचांगasks */
	TP_EC_BACKLIGHT_LVLMSK = 0x1F,
	TP_EC_BACKLIGHT_CMDMSK = 0xE0,
	TP_EC_BACKLIGHT_MAPSW = 0x20,
पूर्ण;

क्रमागत tpacpi_brightness_access_mode अणु
	TPACPI_BRGHT_MODE_AUTO = 0,	/* Not implemented yet */
	TPACPI_BRGHT_MODE_EC,		/* EC control */
	TPACPI_BRGHT_MODE_UCMS_STEP,	/* UCMS step-based control */
	TPACPI_BRGHT_MODE_ECNVRAM,	/* EC control w/ NVRAM store */
	TPACPI_BRGHT_MODE_MAX
पूर्ण;

अटल काष्ठा backlight_device *ibm_backlight_device;

अटल क्रमागत tpacpi_brightness_access_mode brightness_mode =
		TPACPI_BRGHT_MODE_MAX;

अटल अचिन्हित पूर्णांक brightness_enable = 2; /* 2 = स्वतः, 0 = no, 1 = yes */

अटल काष्ठा mutex brightness_mutex;

/* NVRAM brightness access,
 * call with brightness_mutex held! */
अटल अचिन्हित पूर्णांक tpacpi_brightness_nvram_get(व्योम)
अणु
	u8 lnvram;

	lnvram = (nvram_पढ़ो_byte(TP_NVRAM_ADDR_BRIGHTNESS)
		  & TP_NVRAM_MASK_LEVEL_BRIGHTNESS)
		  >> TP_NVRAM_POS_LEVEL_BRIGHTNESS;
	lnvram &= bright_maxlvl;

	वापस lnvram;
पूर्ण

अटल व्योम tpacpi_brightness_checkpoपूर्णांक_nvram(व्योम)
अणु
	u8 lec = 0;
	u8 b_nvram;

	अगर (brightness_mode != TPACPI_BRGHT_MODE_ECNVRAM)
		वापस;

	vdbg_prपूर्णांकk(TPACPI_DBG_BRGHT,
		"trying to checkpoint backlight level to NVRAM...\n");

	अगर (mutex_lock_समाप्तable(&brightness_mutex) < 0)
		वापस;

	अगर (unlikely(!acpi_ec_पढ़ो(TP_EC_BACKLIGHT, &lec)))
		जाओ unlock;
	lec &= TP_EC_BACKLIGHT_LVLMSK;
	b_nvram = nvram_पढ़ो_byte(TP_NVRAM_ADDR_BRIGHTNESS);

	अगर (lec != ((b_nvram & TP_NVRAM_MASK_LEVEL_BRIGHTNESS)
			     >> TP_NVRAM_POS_LEVEL_BRIGHTNESS)) अणु
		/* NVRAM needs update */
		b_nvram &= ~(TP_NVRAM_MASK_LEVEL_BRIGHTNESS <<
				TP_NVRAM_POS_LEVEL_BRIGHTNESS);
		b_nvram |= lec;
		nvram_ग_लिखो_byte(b_nvram, TP_NVRAM_ADDR_BRIGHTNESS);
		dbg_prपूर्णांकk(TPACPI_DBG_BRGHT,
			   "updated NVRAM backlight level to %u (0x%02x)\n",
			   (अचिन्हित पूर्णांक) lec, (अचिन्हित पूर्णांक) b_nvram);
	पूर्ण अन्यथा
		vdbg_prपूर्णांकk(TPACPI_DBG_BRGHT,
			   "NVRAM backlight level already is %u (0x%02x)\n",
			   (अचिन्हित पूर्णांक) lec, (अचिन्हित पूर्णांक) b_nvram);

unlock:
	mutex_unlock(&brightness_mutex);
पूर्ण


/* call with brightness_mutex held! */
अटल पूर्णांक tpacpi_brightness_get_raw(पूर्णांक *status)
अणु
	u8 lec = 0;

	चयन (brightness_mode) अणु
	हाल TPACPI_BRGHT_MODE_UCMS_STEP:
		*status = tpacpi_brightness_nvram_get();
		वापस 0;
	हाल TPACPI_BRGHT_MODE_EC:
	हाल TPACPI_BRGHT_MODE_ECNVRAM:
		अगर (unlikely(!acpi_ec_पढ़ो(TP_EC_BACKLIGHT, &lec)))
			वापस -EIO;
		*status = lec;
		वापस 0;
	शेष:
		वापस -ENXIO;
	पूर्ण
पूर्ण

/* call with brightness_mutex held! */
/* करो NOT call with illegal backlight level value */
अटल पूर्णांक tpacpi_brightness_set_ec(अचिन्हित पूर्णांक value)
अणु
	u8 lec = 0;

	अगर (unlikely(!acpi_ec_पढ़ो(TP_EC_BACKLIGHT, &lec)))
		वापस -EIO;

	अगर (unlikely(!acpi_ec_ग_लिखो(TP_EC_BACKLIGHT,
				(lec & TP_EC_BACKLIGHT_CMDMSK) |
				(value & TP_EC_BACKLIGHT_LVLMSK))))
		वापस -EIO;

	वापस 0;
पूर्ण

/* call with brightness_mutex held! */
अटल पूर्णांक tpacpi_brightness_set_ucmsstep(अचिन्हित पूर्णांक value)
अणु
	पूर्णांक cmos_cmd, inc;
	अचिन्हित पूर्णांक current_value, i;

	current_value = tpacpi_brightness_nvram_get();

	अगर (value == current_value)
		वापस 0;

	cmos_cmd = (value > current_value) ?
			TP_CMOS_BRIGHTNESS_UP :
			TP_CMOS_BRIGHTNESS_DOWN;
	inc = (value > current_value) ? 1 : -1;

	क्रम (i = current_value; i != value; i += inc)
		अगर (issue_thinkpad_cmos_command(cmos_cmd))
			वापस -EIO;

	वापस 0;
पूर्ण

/* May वापस EINTR which can always be mapped to ERESTARTSYS */
अटल पूर्णांक brightness_set(अचिन्हित पूर्णांक value)
अणु
	पूर्णांक res;

	अगर (value > bright_maxlvl)
		वापस -EINVAL;

	vdbg_prपूर्णांकk(TPACPI_DBG_BRGHT,
			"set backlight level to %d\n", value);

	res = mutex_lock_समाप्तable(&brightness_mutex);
	अगर (res < 0)
		वापस res;

	चयन (brightness_mode) अणु
	हाल TPACPI_BRGHT_MODE_EC:
	हाल TPACPI_BRGHT_MODE_ECNVRAM:
		res = tpacpi_brightness_set_ec(value);
		अवरोध;
	हाल TPACPI_BRGHT_MODE_UCMS_STEP:
		res = tpacpi_brightness_set_ucmsstep(value);
		अवरोध;
	शेष:
		res = -ENXIO;
	पूर्ण

	mutex_unlock(&brightness_mutex);
	वापस res;
पूर्ण

/* sysfs backlight class ----------------------------------------------- */

अटल पूर्णांक brightness_update_status(काष्ठा backlight_device *bd)
अणु
	अचिन्हित पूर्णांक level =
		(bd->props.fb_blank == FB_BLANK_UNBLANK &&
		 bd->props.घातer == FB_BLANK_UNBLANK) ?
				bd->props.brightness : 0;

	dbg_prपूर्णांकk(TPACPI_DBG_BRGHT,
			"backlight: attempt to set level to %d\n",
			level);

	/* it is the backlight class's job (caller) to handle
	 * EINTR and other errors properly */
	वापस brightness_set(level);
पूर्ण

अटल पूर्णांक brightness_get(काष्ठा backlight_device *bd)
अणु
	पूर्णांक status, res;

	res = mutex_lock_समाप्तable(&brightness_mutex);
	अगर (res < 0)
		वापस 0;

	res = tpacpi_brightness_get_raw(&status);

	mutex_unlock(&brightness_mutex);

	अगर (res < 0)
		वापस 0;

	वापस status & TP_EC_BACKLIGHT_LVLMSK;
पूर्ण

अटल व्योम tpacpi_brightness_notअगरy_change(व्योम)
अणु
	backlight_क्रमce_update(ibm_backlight_device,
			       BACKLIGHT_UPDATE_HOTKEY);
पूर्ण

अटल स्थिर काष्ठा backlight_ops ibm_backlight_data = अणु
	.get_brightness = brightness_get,
	.update_status  = brightness_update_status,
पूर्ण;

/* --------------------------------------------------------------------- */

/*
 * Call _BCL method of video device.  On some ThinkPads this will
 * चयन the firmware to the ACPI brightness control mode.
 */

अटल पूर्णांक __init tpacpi_query_bcl_levels(acpi_handle handle)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	काष्ठा acpi_device *device, *child;
	पूर्णांक rc;

	अगर (acpi_bus_get_device(handle, &device))
		वापस 0;

	rc = 0;
	list_क्रम_each_entry(child, &device->children, node) अणु
		acpi_status status = acpi_evaluate_object(child->handle, "_BCL",
							  शून्य, &buffer);
		अगर (ACPI_FAILURE(status)) अणु
			buffer.length = ACPI_ALLOCATE_BUFFER;
			जारी;
		पूर्ण

		obj = (जोड़ acpi_object *)buffer.poपूर्णांकer;
		अगर (!obj || (obj->type != ACPI_TYPE_PACKAGE)) अणु
			pr_err("Unknown _BCL data, please report this to %s\n",
				TPACPI_MAIL);
			rc = 0;
		पूर्ण अन्यथा अणु
			rc = obj->package.count;
		पूर्ण
		अवरोध;
	पूर्ण

	kमुक्त(buffer.poपूर्णांकer);
	वापस rc;
पूर्ण


/*
 * Returns 0 (no ACPI _BCL or _BCL invalid), or size of brightness map
 */
अटल अचिन्हित पूर्णांक __init tpacpi_check_std_acpi_brightness_support(व्योम)
अणु
	acpi_handle video_device;
	पूर्णांक bcl_levels = 0;

	tpacpi_acpi_handle_locate("video", शून्य, &video_device);
	अगर (video_device)
		bcl_levels = tpacpi_query_bcl_levels(video_device);

	tp_features.bright_acpimode = (bcl_levels > 0);

	वापस (bcl_levels > 2) ? (bcl_levels - 2) : 0;
पूर्ण

/*
 * These are only useful क्रम models that have only one possibility
 * of GPU.  If the BIOS model handles both ATI and Intel, करोn't use
 * these quirks.
 */
#घोषणा TPACPI_BRGHT_Q_NOEC	0x0001	/* Must NOT use EC HBRV */
#घोषणा TPACPI_BRGHT_Q_EC	0x0002  /* Should or must use EC HBRV */
#घोषणा TPACPI_BRGHT_Q_ASK	0x8000	/* Ask क्रम user report */

अटल स्थिर काष्ठा tpacpi_quirk brightness_quirk_table[] __initस्थिर = अणु
	/* Models with ATI GPUs known to require ECNVRAM mode */
	TPACPI_Q_IBM('1', 'Y', TPACPI_BRGHT_Q_EC),	/* T43/p ATI */

	/* Models with ATI GPUs that can use ECNVRAM */
	TPACPI_Q_IBM('1', 'R', TPACPI_BRGHT_Q_EC),	/* R50,51 T40-42 */
	TPACPI_Q_IBM('1', 'Q', TPACPI_BRGHT_Q_ASK|TPACPI_BRGHT_Q_EC),
	TPACPI_Q_IBM('7', '6', TPACPI_BRGHT_Q_EC),	/* R52 */
	TPACPI_Q_IBM('7', '8', TPACPI_BRGHT_Q_ASK|TPACPI_BRGHT_Q_EC),

	/* Models with Intel Extreme Graphics 2 */
	TPACPI_Q_IBM('1', 'U', TPACPI_BRGHT_Q_NOEC),	/* X40 */
	TPACPI_Q_IBM('1', 'V', TPACPI_BRGHT_Q_ASK|TPACPI_BRGHT_Q_EC),
	TPACPI_Q_IBM('1', 'W', TPACPI_BRGHT_Q_ASK|TPACPI_BRGHT_Q_EC),

	/* Models with Intel GMA900 */
	TPACPI_Q_IBM('7', '0', TPACPI_BRGHT_Q_NOEC),	/* T43, R52 */
	TPACPI_Q_IBM('7', '4', TPACPI_BRGHT_Q_NOEC),	/* X41 */
	TPACPI_Q_IBM('7', '5', TPACPI_BRGHT_Q_NOEC),	/* X41 Tablet */
पूर्ण;

/*
 * Returns < 0 क्रम error, otherwise sets tp_features.bright_*
 * and bright_maxlvl.
 */
अटल व्योम __init tpacpi_detect_brightness_capabilities(व्योम)
अणु
	अचिन्हित पूर्णांक b;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT,
		    "detecting firmware brightness interface capabilities\n");

	/* we could run a quirks check here (same table used by
	 * brightness_init) अगर needed */

	/*
	 * We always attempt to detect acpi support, so as to चयन
	 * Lenovo Vista BIOS to ACPI brightness mode even अगर we are not
	 * going to publish a backlight पूर्णांकerface
	 */
	b = tpacpi_check_std_acpi_brightness_support();
	चयन (b) अणु
	हाल 16:
		bright_maxlvl = 15;
		अवरोध;
	हाल 8:
	हाल 0:
		bright_maxlvl = 7;
		अवरोध;
	शेष:
		tp_features.bright_unkfw = 1;
		bright_maxlvl = b - 1;
	पूर्ण
	pr_debug("detected %u brightness levels\n", bright_maxlvl + 1);
पूर्ण

अटल पूर्णांक __init brightness_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	काष्ठा backlight_properties props;
	पूर्णांक b;
	अचिन्हित दीर्घ quirks;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "initializing brightness subdriver\n");

	mutex_init(&brightness_mutex);

	quirks = tpacpi_check_quirks(brightness_quirk_table,
				ARRAY_SIZE(brightness_quirk_table));

	/* tpacpi_detect_brightness_capabilities() must have run alपढ़ोy */

	/* अगर it is unknown, we करोn't handle it: it wouldn't be safe */
	अगर (tp_features.bright_unkfw)
		वापस 1;

	अगर (!brightness_enable) अणु
		dbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_BRGHT,
			   "brightness support disabled by module parameter\n");
		वापस 1;
	पूर्ण

	अगर (acpi_video_get_backlight_type() != acpi_backlight_venकरोr) अणु
		अगर (brightness_enable > 1) अणु
			pr_info("Standard ACPI backlight interface available, not loading native one\n");
			वापस 1;
		पूर्ण अन्यथा अगर (brightness_enable == 1) अणु
			pr_warn("Cannot enable backlight brightness support, ACPI is already handling it.  Refer to the acpi_backlight kernel parameter.\n");
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अगर (!tp_features.bright_acpimode) अणु
		pr_notice("ACPI backlight interface not available\n");
		वापस 1;
	पूर्ण

	pr_notice("ACPI native brightness control enabled\n");

	/*
	 * Check क्रम module parameter bogosity, note that we
	 * init brightness_mode to TPACPI_BRGHT_MODE_MAX in order to be
	 * able to detect "unspecified"
	 */
	अगर (brightness_mode > TPACPI_BRGHT_MODE_MAX)
		वापस -EINVAL;

	/* TPACPI_BRGHT_MODE_AUTO not implemented yet, just use शेष */
	अगर (brightness_mode == TPACPI_BRGHT_MODE_AUTO ||
	    brightness_mode == TPACPI_BRGHT_MODE_MAX) अणु
		अगर (quirks & TPACPI_BRGHT_Q_EC)
			brightness_mode = TPACPI_BRGHT_MODE_ECNVRAM;
		अन्यथा
			brightness_mode = TPACPI_BRGHT_MODE_UCMS_STEP;

		dbg_prपूर्णांकk(TPACPI_DBG_BRGHT,
			   "driver auto-selected brightness_mode=%d\n",
			   brightness_mode);
	पूर्ण

	/* Safety */
	अगर (!tpacpi_is_ibm() &&
	    (brightness_mode == TPACPI_BRGHT_MODE_ECNVRAM ||
	     brightness_mode == TPACPI_BRGHT_MODE_EC))
		वापस -EINVAL;

	अगर (tpacpi_brightness_get_raw(&b) < 0)
		वापस 1;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = bright_maxlvl;
	props.brightness = b & TP_EC_BACKLIGHT_LVLMSK;
	ibm_backlight_device = backlight_device_रेजिस्टर(TPACPI_BACKLIGHT_DEV_NAME,
							 शून्य, शून्य,
							 &ibm_backlight_data,
							 &props);
	अगर (IS_ERR(ibm_backlight_device)) अणु
		पूर्णांक rc = PTR_ERR(ibm_backlight_device);
		ibm_backlight_device = शून्य;
		pr_err("Could not register backlight device\n");
		वापस rc;
	पूर्ण
	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_BRGHT,
			"brightness is supported\n");

	अगर (quirks & TPACPI_BRGHT_Q_ASK) अणु
		pr_notice("brightness: will use unverified default: brightness_mode=%d\n",
			  brightness_mode);
		pr_notice("brightness: please report to %s whether it works well or not on your ThinkPad\n",
			  TPACPI_MAIL);
	पूर्ण

	/* Added by mistake in early 2007.  Probably useless, but it could
	 * be working around some unknown firmware problem where the value
	 * पढ़ो at startup करोesn't match the real hardware state... so leave
	 * it in place just in हाल */
	backlight_update_status(ibm_backlight_device);

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_BRGHT,
		    "brightness: registering brightness hotkeys as change notification\n");
	tpacpi_hotkey_driver_mask_set(hotkey_driver_mask
				| TP_ACPI_HKEY_BRGHTUP_MASK
				| TP_ACPI_HKEY_BRGHTDWN_MASK);
	वापस 0;
पूर्ण

अटल व्योम brightness_suspend(व्योम)
अणु
	tpacpi_brightness_checkpoपूर्णांक_nvram();
पूर्ण

अटल व्योम brightness_shutकरोwn(व्योम)
अणु
	tpacpi_brightness_checkpoपूर्णांक_nvram();
पूर्ण

अटल व्योम brightness_निकास(व्योम)
अणु
	अगर (ibm_backlight_device) अणु
		vdbg_prपूर्णांकk(TPACPI_DBG_EXIT | TPACPI_DBG_BRGHT,
			    "calling backlight_device_unregister()\n");
		backlight_device_unरेजिस्टर(ibm_backlight_device);
	पूर्ण

	tpacpi_brightness_checkpoपूर्णांक_nvram();
पूर्ण

अटल पूर्णांक brightness_पढ़ो(काष्ठा seq_file *m)
अणु
	पूर्णांक level;

	level = brightness_get(शून्य);
	अगर (level < 0) अणु
		seq_म_लिखो(m, "level:\t\tunreadable\n");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "level:\t\t%d\n", level);
		seq_म_लिखो(m, "commands:\tup, down\n");
		seq_म_लिखो(m, "commands:\tlevel <level> (<level> is 0-%d)\n",
			       bright_maxlvl);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक brightness_ग_लिखो(अक्षर *buf)
अणु
	पूर्णांक level;
	पूर्णांक rc;
	अक्षर *cmd;

	level = brightness_get(शून्य);
	अगर (level < 0)
		वापस level;

	जबतक ((cmd = strsep(&buf, ","))) अणु
		अगर (म_मापcmp(cmd, "up") == 0) अणु
			अगर (level < bright_maxlvl)
				level++;
		पूर्ण अन्यथा अगर (म_मापcmp(cmd, "down") == 0) अणु
			अगर (level > 0)
				level--;
		पूर्ण अन्यथा अगर (माला_पूछो(cmd, "level %d", &level) == 1 &&
			   level >= 0 && level <= bright_maxlvl) अणु
			/* new level set */
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण

	tpacpi_disबंद_usertask("procfs brightness",
			"set level to %d\n", level);

	/*
	 * Now we know what the final level should be, so we try to set it.
	 * Doing it this way makes the syscall restartable in हाल of EINTR
	 */
	rc = brightness_set(level);
	अगर (!rc && ibm_backlight_device)
		backlight_क्रमce_update(ibm_backlight_device,
					BACKLIGHT_UPDATE_SYSFS);
	वापस (rc == -EINTR) ? -ERESTARTSYS : rc;
पूर्ण

अटल काष्ठा ibm_काष्ठा brightness_driver_data = अणु
	.name = "brightness",
	.पढ़ो = brightness_पढ़ो,
	.ग_लिखो = brightness_ग_लिखो,
	.निकास = brightness_निकास,
	.suspend = brightness_suspend,
	.shutकरोwn = brightness_shutकरोwn,
पूर्ण;

/*************************************************************************
 * Volume subdriver
 */

/*
 * IBM ThinkPads have a simple volume controller with MUTE gating.
 * Very early Lenovo ThinkPads follow the IBM ThinkPad spec.
 *
 * Since the *61 series (and probably also the later *60 series), Lenovo
 * ThinkPads only implement the MUTE gate.
 *
 * EC रेजिस्टर 0x30
 *   Bit 6: MUTE (1 mutes sound)
 *   Bit 3-0: Volume
 *   Other bits should be zero as far as we know.
 *
 * This is also stored in CMOS NVRAM, byte 0x60, bit 6 (MUTE), and
 * bits 3-0 (volume).  Other bits in NVRAM may have other functions,
 * such as bit 7 which is used to detect repeated presses of MUTE,
 * and we leave them unchanged.
 *
 * On newer Lenovo ThinkPads, the EC can स्वतःmatically change the volume
 * in response to user input.  Unक्रमtunately, this rarely works well.
 * The laptop changes the state of its पूर्णांकernal MUTE gate and, on some
 * models, sends KEY_MUTE, causing any user code that responds to the
 * mute button to get confused.  The hardware MUTE gate is also
 * unnecessary, since user code can handle the mute button without
 * kernel or EC help.
 *
 * To aव्योम confusing userspace, we simply disable all EC-based mute
 * and volume controls when possible.
 */

#अगर_घोषित CONFIG_THINKPAD_ACPI_ALSA_SUPPORT

#घोषणा TPACPI_ALSA_DRVNAME  "ThinkPad EC"
#घोषणा TPACPI_ALSA_SHRTNAME "ThinkPad Console Audio Control"
#घोषणा TPACPI_ALSA_MIXERNAME TPACPI_ALSA_SHRTNAME

#अगर SNDRV_CARDS <= 32
#घोषणा DEFAULT_ALSA_IDX		~((1 << (SNDRV_CARDS - 3)) - 1)
#अन्यथा
#घोषणा DEFAULT_ALSA_IDX		~((1 << (32 - 3)) - 1)
#पूर्ण_अगर
अटल पूर्णांक alsa_index = DEFAULT_ALSA_IDX; /* last three slots */
अटल अक्षर *alsa_id = "ThinkPadEC";
अटल bool alsa_enable = SNDRV_DEFAULT_ENABLE1;

काष्ठा tpacpi_alsa_data अणु
	काष्ठा snd_card *card;
	काष्ठा snd_ctl_elem_id *ctl_mute_id;
	काष्ठा snd_ctl_elem_id *ctl_vol_id;
पूर्ण;

अटल काष्ठा snd_card *alsa_card;

क्रमागत अणु
	TP_EC_AUDIO = 0x30,

	/* TP_EC_AUDIO bits */
	TP_EC_AUDIO_MUTESW = 6,

	/* TP_EC_AUDIO biपंचांगasks */
	TP_EC_AUDIO_LVL_MSK = 0x0F,
	TP_EC_AUDIO_MUTESW_MSK = (1 << TP_EC_AUDIO_MUTESW),

	/* Maximum volume */
	TP_EC_VOLUME_MAX = 14,
पूर्ण;

क्रमागत tpacpi_volume_access_mode अणु
	TPACPI_VOL_MODE_AUTO = 0,	/* Not implemented yet */
	TPACPI_VOL_MODE_EC,		/* Pure EC control */
	TPACPI_VOL_MODE_UCMS_STEP,	/* UCMS step-based control: N/A */
	TPACPI_VOL_MODE_ECNVRAM,	/* EC control w/ NVRAM store */
	TPACPI_VOL_MODE_MAX
पूर्ण;

क्रमागत tpacpi_volume_capabilities अणु
	TPACPI_VOL_CAP_AUTO = 0,	/* Use white/blacklist */
	TPACPI_VOL_CAP_VOLMUTE,		/* Output vol and mute */
	TPACPI_VOL_CAP_MUTEONLY,	/* Output mute only */
	TPACPI_VOL_CAP_MAX
पूर्ण;

क्रमागत tpacpi_mute_btn_mode अणु
	TP_EC_MUTE_BTN_LATCH  = 0,	/* Mute mutes; up/करोwn unmutes */
	/* We करोn't know what mode 1 is. */
	TP_EC_MUTE_BTN_NONE   = 2,	/* Mute and up/करोwn are just keys */
	TP_EC_MUTE_BTN_TOGGLE = 3,	/* Mute toggles; up/करोwn unmutes */
पूर्ण;

अटल क्रमागत tpacpi_volume_access_mode volume_mode =
	TPACPI_VOL_MODE_MAX;

अटल क्रमागत tpacpi_volume_capabilities volume_capabilities;
अटल bool volume_control_allowed;
अटल bool software_mute_requested = true;
अटल bool software_mute_active;
अटल पूर्णांक software_mute_orig_mode;

/*
 * Used to syncronize ग_लिखोrs to TP_EC_AUDIO and
 * TP_NVRAM_ADDR_MIXER, as we need to करो पढ़ो-modअगरy-ग_लिखो
 */
अटल काष्ठा mutex volume_mutex;

अटल व्योम tpacpi_volume_checkpoपूर्णांक_nvram(व्योम)
अणु
	u8 lec = 0;
	u8 b_nvram;
	u8 ec_mask;

	अगर (volume_mode != TPACPI_VOL_MODE_ECNVRAM)
		वापस;
	अगर (!volume_control_allowed)
		वापस;
	अगर (software_mute_active)
		वापस;

	vdbg_prपूर्णांकk(TPACPI_DBG_MIXER,
		"trying to checkpoint mixer state to NVRAM...\n");

	अगर (tp_features.mixer_no_level_control)
		ec_mask = TP_EC_AUDIO_MUTESW_MSK;
	अन्यथा
		ec_mask = TP_EC_AUDIO_MUTESW_MSK | TP_EC_AUDIO_LVL_MSK;

	अगर (mutex_lock_समाप्तable(&volume_mutex) < 0)
		वापस;

	अगर (unlikely(!acpi_ec_पढ़ो(TP_EC_AUDIO, &lec)))
		जाओ unlock;
	lec &= ec_mask;
	b_nvram = nvram_पढ़ो_byte(TP_NVRAM_ADDR_MIXER);

	अगर (lec != (b_nvram & ec_mask)) अणु
		/* NVRAM needs update */
		b_nvram &= ~ec_mask;
		b_nvram |= lec;
		nvram_ग_लिखो_byte(b_nvram, TP_NVRAM_ADDR_MIXER);
		dbg_prपूर्णांकk(TPACPI_DBG_MIXER,
			   "updated NVRAM mixer status to 0x%02x (0x%02x)\n",
			   (अचिन्हित पूर्णांक) lec, (अचिन्हित पूर्णांक) b_nvram);
	पूर्ण अन्यथा अणु
		vdbg_prपूर्णांकk(TPACPI_DBG_MIXER,
			   "NVRAM mixer status already is 0x%02x (0x%02x)\n",
			   (अचिन्हित पूर्णांक) lec, (अचिन्हित पूर्णांक) b_nvram);
	पूर्ण

unlock:
	mutex_unlock(&volume_mutex);
पूर्ण

अटल पूर्णांक volume_get_status_ec(u8 *status)
अणु
	u8 s;

	अगर (!acpi_ec_पढ़ो(TP_EC_AUDIO, &s))
		वापस -EIO;

	*status = s;

	dbg_prपूर्णांकk(TPACPI_DBG_MIXER, "status 0x%02x\n", s);

	वापस 0;
पूर्ण

अटल पूर्णांक volume_get_status(u8 *status)
अणु
	वापस volume_get_status_ec(status);
पूर्ण

अटल पूर्णांक volume_set_status_ec(स्थिर u8 status)
अणु
	अगर (!acpi_ec_ग_लिखो(TP_EC_AUDIO, status))
		वापस -EIO;

	dbg_prपूर्णांकk(TPACPI_DBG_MIXER, "set EC mixer to 0x%02x\n", status);

	/*
	 * On X200s, and possibly on others, it can take a जबतक क्रम
	 * पढ़ोs to become correct.
	 */
	msleep(1);

	वापस 0;
पूर्ण

अटल पूर्णांक volume_set_status(स्थिर u8 status)
अणु
	वापस volume_set_status_ec(status);
पूर्ण

/* वापसs < 0 on error, 0 on no change, 1 on change */
अटल पूर्णांक __volume_set_mute_ec(स्थिर bool mute)
अणु
	पूर्णांक rc;
	u8 s, n;

	अगर (mutex_lock_समाप्तable(&volume_mutex) < 0)
		वापस -EINTR;

	rc = volume_get_status_ec(&s);
	अगर (rc)
		जाओ unlock;

	n = (mute) ? s | TP_EC_AUDIO_MUTESW_MSK :
		     s & ~TP_EC_AUDIO_MUTESW_MSK;

	अगर (n != s) अणु
		rc = volume_set_status_ec(n);
		अगर (!rc)
			rc = 1;
	पूर्ण

unlock:
	mutex_unlock(&volume_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक volume_alsa_set_mute(स्थिर bool mute)
अणु
	dbg_prपूर्णांकk(TPACPI_DBG_MIXER, "ALSA: trying to %smute\n",
		   (mute) ? "" : "un");
	वापस __volume_set_mute_ec(mute);
पूर्ण

अटल पूर्णांक volume_set_mute(स्थिर bool mute)
अणु
	पूर्णांक rc;

	dbg_prपूर्णांकk(TPACPI_DBG_MIXER, "trying to %smute\n",
		   (mute) ? "" : "un");

	rc = __volume_set_mute_ec(mute);
	वापस (rc < 0) ? rc : 0;
पूर्ण

/* वापसs < 0 on error, 0 on no change, 1 on change */
अटल पूर्णांक __volume_set_volume_ec(स्थिर u8 vol)
अणु
	पूर्णांक rc;
	u8 s, n;

	अगर (vol > TP_EC_VOLUME_MAX)
		वापस -EINVAL;

	अगर (mutex_lock_समाप्तable(&volume_mutex) < 0)
		वापस -EINTR;

	rc = volume_get_status_ec(&s);
	अगर (rc)
		जाओ unlock;

	n = (s & ~TP_EC_AUDIO_LVL_MSK) | vol;

	अगर (n != s) अणु
		rc = volume_set_status_ec(n);
		अगर (!rc)
			rc = 1;
	पूर्ण

unlock:
	mutex_unlock(&volume_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक volume_set_software_mute(bool startup)
अणु
	पूर्णांक result;

	अगर (!tpacpi_is_lenovo())
		वापस -ENODEV;

	अगर (startup) अणु
		अगर (!acpi_evalf(ec_handle, &software_mute_orig_mode,
				"HAUM", "qd"))
			वापस -EIO;

		dbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_MIXER,
			    "Initial HAUM setting was %d\n",
			    software_mute_orig_mode);
	पूर्ण

	अगर (!acpi_evalf(ec_handle, &result, "SAUM", "qdd",
			(पूर्णांक)TP_EC_MUTE_BTN_NONE))
		वापस -EIO;

	अगर (result != TP_EC_MUTE_BTN_NONE)
		pr_warn("Unexpected SAUM result %d\n",
			result);

	/*
	 * In software mute mode, the standard codec controls take
	 * precendence, so we unmute the ThinkPad HW चयन at
	 * startup.  Just on हाल there are SAUM-capable ThinkPads
	 * with level controls, set max HW volume as well.
	 */
	अगर (tp_features.mixer_no_level_control)
		result = volume_set_mute(false);
	अन्यथा
		result = volume_set_status(TP_EC_VOLUME_MAX);

	अगर (result != 0)
		pr_warn("Failed to unmute the HW mute switch\n");

	वापस 0;
पूर्ण

अटल व्योम volume_निकास_software_mute(व्योम)
अणु
	पूर्णांक r;

	अगर (!acpi_evalf(ec_handle, &r, "SAUM", "qdd", software_mute_orig_mode)
	    || r != software_mute_orig_mode)
		pr_warn("Failed to restore mute mode\n");
पूर्ण

अटल पूर्णांक volume_alsa_set_volume(स्थिर u8 vol)
अणु
	dbg_prपूर्णांकk(TPACPI_DBG_MIXER,
		   "ALSA: trying to set volume level to %hu\n", vol);
	वापस __volume_set_volume_ec(vol);
पूर्ण

अटल व्योम volume_alsa_notअगरy_change(व्योम)
अणु
	काष्ठा tpacpi_alsa_data *d;

	अगर (alsa_card && alsa_card->निजी_data) अणु
		d = alsa_card->निजी_data;
		अगर (d->ctl_mute_id)
			snd_ctl_notअगरy(alsa_card,
					SNDRV_CTL_EVENT_MASK_VALUE,
					d->ctl_mute_id);
		अगर (d->ctl_vol_id)
			snd_ctl_notअगरy(alsa_card,
					SNDRV_CTL_EVENT_MASK_VALUE,
					d->ctl_vol_id);
	पूर्ण
पूर्ण

अटल पूर्णांक volume_alsa_vol_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = TP_EC_VOLUME_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक volume_alsa_vol_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u8 s;
	पूर्णांक rc;

	rc = volume_get_status(&s);
	अगर (rc < 0)
		वापस rc;

	ucontrol->value.पूर्णांकeger.value[0] = s & TP_EC_AUDIO_LVL_MSK;
	वापस 0;
पूर्ण

अटल पूर्णांक volume_alsa_vol_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	tpacpi_disबंद_usertask("ALSA", "set volume to %ld\n",
				 ucontrol->value.पूर्णांकeger.value[0]);
	वापस volume_alsa_set_volume(ucontrol->value.पूर्णांकeger.value[0]);
पूर्ण

#घोषणा volume_alsa_mute_info snd_ctl_boolean_mono_info

अटल पूर्णांक volume_alsa_mute_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u8 s;
	पूर्णांक rc;

	rc = volume_get_status(&s);
	अगर (rc < 0)
		वापस rc;

	ucontrol->value.पूर्णांकeger.value[0] =
				(s & TP_EC_AUDIO_MUTESW_MSK) ? 0 : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक volume_alsa_mute_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	tpacpi_disबंद_usertask("ALSA", "%smute\n",
				 ucontrol->value.पूर्णांकeger.value[0] ?
					"un" : "");
	वापस volume_alsa_set_mute(!ucontrol->value.पूर्णांकeger.value[0]);
पूर्ण

अटल काष्ठा snd_kcontrol_new volume_alsa_control_vol __initdata = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Console Playback Volume",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READ,
	.info = volume_alsa_vol_info,
	.get = volume_alsa_vol_get,
पूर्ण;

अटल काष्ठा snd_kcontrol_new volume_alsa_control_mute __initdata = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Console Playback Switch",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READ,
	.info = volume_alsa_mute_info,
	.get = volume_alsa_mute_get,
पूर्ण;

अटल व्योम volume_suspend(व्योम)
अणु
	tpacpi_volume_checkpoपूर्णांक_nvram();
पूर्ण

अटल व्योम volume_resume(व्योम)
अणु
	अगर (software_mute_active) अणु
		अगर (volume_set_software_mute(false) < 0)
			pr_warn("Failed to restore software mute\n");
	पूर्ण अन्यथा अणु
		volume_alsa_notअगरy_change();
	पूर्ण
पूर्ण

अटल व्योम volume_shutकरोwn(व्योम)
अणु
	tpacpi_volume_checkpoपूर्णांक_nvram();
पूर्ण

अटल व्योम volume_निकास(व्योम)
अणु
	अगर (alsa_card) अणु
		snd_card_मुक्त(alsa_card);
		alsa_card = शून्य;
	पूर्ण

	tpacpi_volume_checkpoपूर्णांक_nvram();

	अगर (software_mute_active)
		volume_निकास_software_mute();
पूर्ण

अटल पूर्णांक __init volume_create_alsa_mixer(व्योम)
अणु
	काष्ठा snd_card *card;
	काष्ठा tpacpi_alsa_data *data;
	काष्ठा snd_kcontrol *ctl_vol;
	काष्ठा snd_kcontrol *ctl_mute;
	पूर्णांक rc;

	rc = snd_card_new(&tpacpi_pdev->dev,
			  alsa_index, alsa_id, THIS_MODULE,
			  माप(काष्ठा tpacpi_alsa_data), &card);
	अगर (rc < 0 || !card) अणु
		pr_err("Failed to create ALSA card structures: %d\n", rc);
		वापस 1;
	पूर्ण

	BUG_ON(!card->निजी_data);
	data = card->निजी_data;
	data->card = card;

	strlcpy(card->driver, TPACPI_ALSA_DRVNAME,
		माप(card->driver));
	strlcpy(card->लघुname, TPACPI_ALSA_SHRTNAME,
		माप(card->लघुname));
	snम_लिखो(card->mixername, माप(card->mixername), "ThinkPad EC %s",
		 (thinkpad_id.ec_version_str) ?
			thinkpad_id.ec_version_str : "(unknown)");
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s at EC reg 0x%02x, fw %s", card->लघुname, TP_EC_AUDIO,
		 (thinkpad_id.ec_version_str) ?
			thinkpad_id.ec_version_str : "unknown");

	अगर (volume_control_allowed) अणु
		volume_alsa_control_vol.put = volume_alsa_vol_put;
		volume_alsa_control_vol.access =
				SNDRV_CTL_ELEM_ACCESS_READWRITE;

		volume_alsa_control_mute.put = volume_alsa_mute_put;
		volume_alsa_control_mute.access =
				SNDRV_CTL_ELEM_ACCESS_READWRITE;
	पूर्ण

	अगर (!tp_features.mixer_no_level_control) अणु
		ctl_vol = snd_ctl_new1(&volume_alsa_control_vol, शून्य);
		rc = snd_ctl_add(card, ctl_vol);
		अगर (rc < 0) अणु
			pr_err("Failed to create ALSA volume control: %d\n",
			       rc);
			जाओ err_निकास;
		पूर्ण
		data->ctl_vol_id = &ctl_vol->id;
	पूर्ण

	ctl_mute = snd_ctl_new1(&volume_alsa_control_mute, शून्य);
	rc = snd_ctl_add(card, ctl_mute);
	अगर (rc < 0) अणु
		pr_err("Failed to create ALSA mute control: %d\n", rc);
		जाओ err_निकास;
	पूर्ण
	data->ctl_mute_id = &ctl_mute->id;

	rc = snd_card_रेजिस्टर(card);
	अगर (rc < 0) अणु
		pr_err("Failed to register ALSA card: %d\n", rc);
		जाओ err_निकास;
	पूर्ण

	alsa_card = card;
	वापस 0;

err_निकास:
	snd_card_मुक्त(card);
	वापस 1;
पूर्ण

#घोषणा TPACPI_VOL_Q_MUTEONLY	0x0001	/* Mute-only control available */
#घोषणा TPACPI_VOL_Q_LEVEL	0x0002  /* Volume control available */

अटल स्थिर काष्ठा tpacpi_quirk volume_quirk_table[] __initस्थिर = अणु
	/* Whitelist volume level on all IBM by शेष */
	अणु .venकरोr = PCI_VENDOR_ID_IBM,
	  .bios   = TPACPI_MATCH_ANY,
	  .ec     = TPACPI_MATCH_ANY,
	  .quirks = TPACPI_VOL_Q_LEVEL पूर्ण,

	/* Lenovo models with volume control (needs confirmation) */
	TPACPI_QEC_LNV('7', 'C', TPACPI_VOL_Q_LEVEL), /* R60/i */
	TPACPI_QEC_LNV('7', 'E', TPACPI_VOL_Q_LEVEL), /* R60e/i */
	TPACPI_QEC_LNV('7', '9', TPACPI_VOL_Q_LEVEL), /* T60/p */
	TPACPI_QEC_LNV('7', 'B', TPACPI_VOL_Q_LEVEL), /* X60/s */
	TPACPI_QEC_LNV('7', 'J', TPACPI_VOL_Q_LEVEL), /* X60t */
	TPACPI_QEC_LNV('7', '7', TPACPI_VOL_Q_LEVEL), /* Z60 */
	TPACPI_QEC_LNV('7', 'F', TPACPI_VOL_Q_LEVEL), /* Z61 */

	/* Whitelist mute-only on all Lenovo by शेष */
	अणु .venकरोr = PCI_VENDOR_ID_LENOVO,
	  .bios   = TPACPI_MATCH_ANY,
	  .ec	  = TPACPI_MATCH_ANY,
	  .quirks = TPACPI_VOL_Q_MUTEONLY पूर्ण
पूर्ण;

अटल पूर्णांक __init volume_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	अचिन्हित दीर्घ quirks;
	पूर्णांक rc;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT, "initializing volume subdriver\n");

	mutex_init(&volume_mutex);

	/*
	 * Check क्रम module parameter bogosity, note that we
	 * init volume_mode to TPACPI_VOL_MODE_MAX in order to be
	 * able to detect "unspecified"
	 */
	अगर (volume_mode > TPACPI_VOL_MODE_MAX)
		वापस -EINVAL;

	अगर (volume_mode == TPACPI_VOL_MODE_UCMS_STEP) अणु
		pr_err("UCMS step volume mode not implemented, please contact %s\n",
		       TPACPI_MAIL);
		वापस 1;
	पूर्ण

	अगर (volume_capabilities >= TPACPI_VOL_CAP_MAX)
		वापस -EINVAL;

	/*
	 * The ALSA mixer is our primary पूर्णांकerface.
	 * When disabled, करोn't install the subdriver at all
	 */
	अगर (!alsa_enable) अणु
		vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_MIXER,
			    "ALSA mixer disabled by parameter, not loading volume subdriver...\n");
		वापस 1;
	पूर्ण

	quirks = tpacpi_check_quirks(volume_quirk_table,
				     ARRAY_SIZE(volume_quirk_table));

	चयन (volume_capabilities) अणु
	हाल TPACPI_VOL_CAP_AUTO:
		अगर (quirks & TPACPI_VOL_Q_MUTEONLY)
			tp_features.mixer_no_level_control = 1;
		अन्यथा अगर (quirks & TPACPI_VOL_Q_LEVEL)
			tp_features.mixer_no_level_control = 0;
		अन्यथा
			वापस 1; /* no mixer */
		अवरोध;
	हाल TPACPI_VOL_CAP_VOLMUTE:
		tp_features.mixer_no_level_control = 0;
		अवरोध;
	हाल TPACPI_VOL_CAP_MUTEONLY:
		tp_features.mixer_no_level_control = 1;
		अवरोध;
	शेष:
		वापस 1;
	पूर्ण

	अगर (volume_capabilities != TPACPI_VOL_CAP_AUTO)
		dbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_MIXER,
				"using user-supplied volume_capabilities=%d\n",
				volume_capabilities);

	अगर (volume_mode == TPACPI_VOL_MODE_AUTO ||
	    volume_mode == TPACPI_VOL_MODE_MAX) अणु
		volume_mode = TPACPI_VOL_MODE_ECNVRAM;

		dbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_MIXER,
				"driver auto-selected volume_mode=%d\n",
				volume_mode);
	पूर्ण अन्यथा अणु
		dbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_MIXER,
				"using user-supplied volume_mode=%d\n",
				volume_mode);
	पूर्ण

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_MIXER,
			"mute is supported, volume control is %s\n",
			str_supported(!tp_features.mixer_no_level_control));

	अगर (software_mute_requested && volume_set_software_mute(true) == 0) अणु
		software_mute_active = true;
	पूर्ण अन्यथा अणु
		rc = volume_create_alsa_mixer();
		अगर (rc) अणु
			pr_err("Could not create the ALSA mixer interface\n");
			वापस rc;
		पूर्ण

		pr_info("Console audio control enabled, mode: %s\n",
			(volume_control_allowed) ?
				"override (read/write)" :
				"monitor (read only)");
	पूर्ण

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_MIXER,
		"registering volume hotkeys as change notification\n");
	tpacpi_hotkey_driver_mask_set(hotkey_driver_mask
			| TP_ACPI_HKEY_VOLUP_MASK
			| TP_ACPI_HKEY_VOLDWN_MASK
			| TP_ACPI_HKEY_MUTE_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक volume_पढ़ो(काष्ठा seq_file *m)
अणु
	u8 status;

	अगर (volume_get_status(&status) < 0) अणु
		seq_म_लिखो(m, "level:\t\tunreadable\n");
	पूर्ण अन्यथा अणु
		अगर (tp_features.mixer_no_level_control)
			seq_म_लिखो(m, "level:\t\tunsupported\n");
		अन्यथा
			seq_म_लिखो(m, "level:\t\t%d\n",
					status & TP_EC_AUDIO_LVL_MSK);

		seq_म_लिखो(m, "mute:\t\t%s\n",
				onoff(status, TP_EC_AUDIO_MUTESW));

		अगर (volume_control_allowed) अणु
			seq_म_लिखो(m, "commands:\tunmute, mute\n");
			अगर (!tp_features.mixer_no_level_control) अणु
				seq_म_लिखो(m, "commands:\tup, down\n");
				seq_म_लिखो(m, "commands:\tlevel <level> (<level> is 0-%d)\n",
					      TP_EC_VOLUME_MAX);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक volume_ग_लिखो(अक्षर *buf)
अणु
	u8 s;
	u8 new_level, new_mute;
	पूर्णांक l;
	अक्षर *cmd;
	पूर्णांक rc;

	/*
	 * We करो allow volume control at driver startup, so that the
	 * user can set initial state through the volume=... parameter hack.
	 */
	अगर (!volume_control_allowed && tpacpi_lअगरecycle != TPACPI_LIFE_INIT) अणु
		अगर (unlikely(!tp_warned.volume_ctrl_क्रमbidden)) अणु
			tp_warned.volume_ctrl_क्रमbidden = 1;
			pr_notice("Console audio control in monitor mode, changes are not allowed\n");
			pr_notice("Use the volume_control=1 module parameter to enable volume control\n");
		पूर्ण
		वापस -EPERM;
	पूर्ण

	rc = volume_get_status(&s);
	अगर (rc < 0)
		वापस rc;

	new_level = s & TP_EC_AUDIO_LVL_MSK;
	new_mute  = s & TP_EC_AUDIO_MUTESW_MSK;

	जबतक ((cmd = strsep(&buf, ","))) अणु
		अगर (!tp_features.mixer_no_level_control) अणु
			अगर (म_मापcmp(cmd, "up") == 0) अणु
				अगर (new_mute)
					new_mute = 0;
				अन्यथा अगर (new_level < TP_EC_VOLUME_MAX)
					new_level++;
				जारी;
			पूर्ण अन्यथा अगर (म_मापcmp(cmd, "down") == 0) अणु
				अगर (new_mute)
					new_mute = 0;
				अन्यथा अगर (new_level > 0)
					new_level--;
				जारी;
			पूर्ण अन्यथा अगर (माला_पूछो(cmd, "level %u", &l) == 1 &&
				   l >= 0 && l <= TP_EC_VOLUME_MAX) अणु
					new_level = l;
				जारी;
			पूर्ण
		पूर्ण
		अगर (म_मापcmp(cmd, "mute") == 0)
			new_mute = TP_EC_AUDIO_MUTESW_MSK;
		अन्यथा अगर (म_मापcmp(cmd, "unmute") == 0)
			new_mute = 0;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (tp_features.mixer_no_level_control) अणु
		tpacpi_disबंद_usertask("procfs volume", "%smute\n",
					new_mute ? "" : "un");
		rc = volume_set_mute(!!new_mute);
	पूर्ण अन्यथा अणु
		tpacpi_disबंद_usertask("procfs volume",
					"%smute and set level to %d\n",
					new_mute ? "" : "un", new_level);
		rc = volume_set_status(new_mute | new_level);
	पूर्ण
	volume_alsa_notअगरy_change();

	वापस (rc == -EINTR) ? -ERESTARTSYS : rc;
पूर्ण

अटल काष्ठा ibm_काष्ठा volume_driver_data = अणु
	.name = "volume",
	.पढ़ो = volume_पढ़ो,
	.ग_लिखो = volume_ग_लिखो,
	.निकास = volume_निकास,
	.suspend = volume_suspend,
	.resume = volume_resume,
	.shutकरोwn = volume_shutकरोwn,
पूर्ण;

#अन्यथा /* !CONFIG_THINKPAD_ACPI_ALSA_SUPPORT */

#घोषणा alsa_card शून्य

अटल अंतरभूत व्योम volume_alsa_notअगरy_change(व्योम)
अणु
पूर्ण

अटल पूर्णांक __init volume_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	pr_info("volume: disabled as there is no ALSA support in this kernel\n");

	वापस 1;
पूर्ण

अटल काष्ठा ibm_काष्ठा volume_driver_data = अणु
	.name = "volume",
पूर्ण;

#पूर्ण_अगर /* CONFIG_THINKPAD_ACPI_ALSA_SUPPORT */

/*************************************************************************
 * Fan subdriver
 */

/*
 * FAN ACCESS MODES
 *
 * TPACPI_FAN_RD_ACPI_GFAN:
 * 	ACPI GFAN method: वापसs fan level
 *
 * 	see TPACPI_FAN_WR_ACPI_SFAN
 * 	EC 0x2f (HFSP) not available अगर GFAN exists
 *
 * TPACPI_FAN_WR_ACPI_SFAN:
 * 	ACPI SFAN method: sets fan level, 0 (stop) to 7 (max)
 *
 * 	EC 0x2f (HFSP) might be available *क्रम पढ़ोing*, but करो not use
 * 	it क्रम writing.
 *
 * TPACPI_FAN_WR_TPEC:
 * 	ThinkPad EC रेजिस्टर 0x2f (HFSP): fan control loop mode
 * 	Supported on almost all ThinkPads
 *
 * 	Fan speed changes of any sort (including those caused by the
 * 	disengaged mode) are usually करोne slowly by the firmware as the
 * 	maximum amount of fan duty cycle change per second seems to be
 * 	limited.
 *
 * 	Reading is not available अगर GFAN exists.
 * 	Writing is not available अगर SFAN exists.
 *
 * 	Bits
 *	 7	स्वतःmatic mode engaged;
 *  		(शेष operation mode of the ThinkPad)
 * 		fan level is ignored in this mode.
 *	 6	full speed mode (takes precedence over bit 7);
 *		not available on all thinkpads.  May disable
 *		the tachometer जबतक the fan controller ramps up
 *		the speed (which can take up to a few *minutes*).
 *		Speeds up fan to 100% duty-cycle, which is far above
 *		the standard RPM levels.  It is not impossible that
 *		it could cause hardware damage.
 *	5-3	unused in some models.  Extra bits क्रम fan level
 *		in others, but still useless as all values above
 *		7 map to the same speed as level 7 in these models.
 *	2-0	fan level (0..7 usually)
 *			0x00 = stop
 * 			0x07 = max (set when temperatures critical)
 * 		Some ThinkPads may have other levels, see
 * 		TPACPI_FAN_WR_ACPI_FANS (X31/X40/X41)
 *
 *	FIRMWARE BUG: on some models, EC 0x2f might not be initialized at
 *	boot. Apparently the EC करोes not initialize it, so unless ACPI DSDT
 *	करोes so, its initial value is meaningless (0x07).
 *
 *	For firmware bugs, refer to:
 *	https://thinkwiki.org/wiki/Embedded_Controller_Firmware#Firmware_Issues
 *
 * 	----
 *
 *	ThinkPad EC रेजिस्टर 0x84 (LSB), 0x85 (MSB):
 *	Main fan tachometer पढ़ोing (in RPM)
 *
 *	This रेजिस्टर is present on all ThinkPads with a new-style EC, and
 *	it is known not to be present on the A21m/e, and T22, as there is
 *	something अन्यथा in offset 0x84 according to the ACPI DSDT.  Other
 *	ThinkPads from this same समय period (and earlier) probably lack the
 *	tachometer as well.
 *
 *	Unक्रमtunately a lot of ThinkPads with new-style ECs but whose firmware
 *	was never fixed by IBM to report the EC firmware version string
 *	probably support the tachometer (like the early X models), so
 *	detecting it is quite hard.  We need more data to know क्रम sure.
 *
 *	FIRMWARE BUG: always पढ़ो 0x84 first, otherwise incorrect पढ़ोings
 *	might result.
 *
 *	FIRMWARE BUG: may go stale जबतक the EC is चयनing to full speed
 *	mode.
 *
 *	For firmware bugs, refer to:
 *	https://thinkwiki.org/wiki/Embedded_Controller_Firmware#Firmware_Issues
 *
 *	----
 *
 *	ThinkPad EC रेजिस्टर 0x31 bit 0 (only on select models)
 *
 *	When bit 0 of EC रेजिस्टर 0x31 is zero, the tachometer रेजिस्टरs
 *	show the speed of the मुख्य fan.  When bit 0 of EC रेजिस्टर 0x31
 *	is one, the tachometer रेजिस्टरs show the speed of the auxiliary
 *	fan.
 *
 *	Fan control seems to affect both fans, regardless of the state
 *	of this bit.
 *
 *	So far, only the firmware क्रम the X60/X61 non-tablet versions
 *	seem to support this (firmware TP-7M).
 *
 * TPACPI_FAN_WR_ACPI_FANS:
 *	ThinkPad X31, X40, X41.  Not available in the X60.
 *
 *	FANS ACPI handle: takes three arguments: low speed, medium speed,
 *	high speed.  ACPI DSDT seems to map these three speeds to levels
 *	as follows: STOP LOW LOW MED MED HIGH HIGH HIGH HIGH
 *	(this map is stored on FAN0..FAN8 as "0,1,1,2,2,3,3,3,3")
 *
 * 	The speeds are stored on handles
 * 	(FANA:FAN9), (FANC:FANB), (FANE:FAND).
 *
 * 	There are three शेष speed sets, accessible as handles:
 * 	FS1L,FS1M,FS1H; FS2L,FS2M,FS2H; FS3L,FS3M,FS3H
 *
 * 	ACPI DSDT चयनes which set is in use depending on various
 * 	factors.
 *
 * 	TPACPI_FAN_WR_TPEC is also available and should be used to
 * 	command the fan.  The X31/X40/X41 seems to have 8 fan levels,
 * 	but the ACPI tables just mention level 7.
 */

क्रमागत अणु					/* Fan control स्थिरants */
	fan_status_offset = 0x2f,	/* EC रेजिस्टर 0x2f */
	fan_rpm_offset = 0x84,		/* EC रेजिस्टर 0x84: LSB, 0x85 MSB (RPM)
					 * 0x84 must be पढ़ो beक्रमe 0x85 */
	fan_select_offset = 0x31,	/* EC रेजिस्टर 0x31 (Firmware 7M)
					   bit 0 selects which fan is active */

	TP_EC_FAN_FULLSPEED = 0x40,	/* EC fan mode: full speed */
	TP_EC_FAN_AUTO	    = 0x80,	/* EC fan mode: स्वतः fan control */

	TPACPI_FAN_LAST_LEVEL = 0x100,	/* Use cached last-seen fan level */
पूर्ण;

क्रमागत fan_status_access_mode अणु
	TPACPI_FAN_NONE = 0,		/* No fan status or control */
	TPACPI_FAN_RD_ACPI_GFAN,	/* Use ACPI GFAN */
	TPACPI_FAN_RD_TPEC,		/* Use ACPI EC regs 0x2f, 0x84-0x85 */
पूर्ण;

क्रमागत fan_control_access_mode अणु
	TPACPI_FAN_WR_NONE = 0,		/* No fan control */
	TPACPI_FAN_WR_ACPI_SFAN,	/* Use ACPI SFAN */
	TPACPI_FAN_WR_TPEC,		/* Use ACPI EC reg 0x2f */
	TPACPI_FAN_WR_ACPI_FANS,	/* Use ACPI FANS and EC reg 0x2f */
पूर्ण;

क्रमागत fan_control_commands अणु
	TPACPI_FAN_CMD_SPEED 	= 0x0001,	/* speed command */
	TPACPI_FAN_CMD_LEVEL 	= 0x0002,	/* level command  */
	TPACPI_FAN_CMD_ENABLE	= 0x0004,	/* enable/disable cmd,
						 * and also watchकरोg cmd */
पूर्ण;

अटल bool fan_control_allowed;

अटल क्रमागत fan_status_access_mode fan_status_access_mode;
अटल क्रमागत fan_control_access_mode fan_control_access_mode;
अटल क्रमागत fan_control_commands fan_control_commands;

अटल u8 fan_control_initial_status;
अटल u8 fan_control_desired_level;
अटल u8 fan_control_resume_level;
अटल पूर्णांक fan_watchकरोg_maxपूर्णांकerval;

अटल काष्ठा mutex fan_mutex;

अटल व्योम fan_watchकरोg_fire(काष्ठा work_काष्ठा *ignored);
अटल DECLARE_DELAYED_WORK(fan_watchकरोg_task, fan_watchकरोg_fire);

TPACPI_HANDLE(fans, ec, "FANS");	/* X31, X40, X41 */
TPACPI_HANDLE(gfan, ec, "GFAN",	/* 570 */
	   "\\FSPD",		/* 600e/x, 770e, 770x */
	   );			/* all others */
TPACPI_HANDLE(sfan, ec, "SFAN",	/* 570 */
	   "JFNS",		/* 770x-JL */
	   );			/* all others */

/*
 * Unitialized HFSP quirk: ACPI DSDT and EC fail to initialize the
 * HFSP रेजिस्टर at boot, so it contains 0x07 but the Thinkpad could
 * be in स्वतः mode (0x80).
 *
 * This is corrected by any ग_लिखो to HFSP either by the driver, or
 * by the firmware.
 *
 * We assume 0x07 really means स्वतः mode जबतक this quirk is active,
 * as this is far more likely than the ThinkPad being in level 7,
 * which is only used by the firmware during thermal emergencies.
 *
 * Enable क्रम TP-1Y (T43), TP-78 (R51e), TP-76 (R52),
 * TP-70 (T43, R52), which are known to be buggy.
 */

अटल व्योम fan_quirk1_setup(व्योम)
अणु
	अगर (fan_control_initial_status == 0x07) अणु
		pr_notice("fan_init: initial fan status is unknown, assuming it is in auto mode\n");
		tp_features.fan_ctrl_status_undef = 1;
	पूर्ण
पूर्ण

अटल व्योम fan_quirk1_handle(u8 *fan_status)
अणु
	अगर (unlikely(tp_features.fan_ctrl_status_undef)) अणु
		अगर (*fan_status != fan_control_initial_status) अणु
			/* something changed the HFSP regisnter since
			 * driver init समय, so it is not undefined
			 * anymore */
			tp_features.fan_ctrl_status_undef = 0;
		पूर्ण अन्यथा अणु
			/* Return most likely status. In fact, it
			 * might be the only possible status */
			*fan_status = TP_EC_FAN_AUTO;
		पूर्ण
	पूर्ण
पूर्ण

/* Select मुख्य fan on X60/X61, NOOP on others */
अटल bool fan_select_fan1(व्योम)
अणु
	अगर (tp_features.second_fan) अणु
		u8 val;

		अगर (ec_पढ़ो(fan_select_offset, &val) < 0)
			वापस false;
		val &= 0xFEU;
		अगर (ec_ग_लिखो(fan_select_offset, val) < 0)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* Select secondary fan on X60/X61 */
अटल bool fan_select_fan2(व्योम)
अणु
	u8 val;

	अगर (!tp_features.second_fan)
		वापस false;

	अगर (ec_पढ़ो(fan_select_offset, &val) < 0)
		वापस false;
	val |= 0x01U;
	अगर (ec_ग_लिखो(fan_select_offset, val) < 0)
		वापस false;

	वापस true;
पूर्ण

/*
 * Call with fan_mutex held
 */
अटल व्योम fan_update_desired_level(u8 status)
अणु
	अगर ((status &
	     (TP_EC_FAN_AUTO | TP_EC_FAN_FULLSPEED)) == 0) अणु
		अगर (status > 7)
			fan_control_desired_level = 7;
		अन्यथा
			fan_control_desired_level = status;
	पूर्ण
पूर्ण

अटल पूर्णांक fan_get_status(u8 *status)
अणु
	u8 s;

	/* TODO:
	 * Add TPACPI_FAN_RD_ACPI_FANS ? */

	चयन (fan_status_access_mode) अणु
	हाल TPACPI_FAN_RD_ACPI_GFAN: अणु
		/* 570, 600e/x, 770e, 770x */
		पूर्णांक res;

		अगर (unlikely(!acpi_evalf(gfan_handle, &res, शून्य, "d")))
			वापस -EIO;

		अगर (likely(status))
			*status = res & 0x07;

		अवरोध;
	पूर्ण
	हाल TPACPI_FAN_RD_TPEC:
		/* all except 570, 600e/x, 770e, 770x */
		अगर (unlikely(!acpi_ec_पढ़ो(fan_status_offset, &s)))
			वापस -EIO;

		अगर (likely(status)) अणु
			*status = s;
			fan_quirk1_handle(status);
		पूर्ण

		अवरोध;

	शेष:
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fan_get_status_safe(u8 *status)
अणु
	पूर्णांक rc;
	u8 s;

	अगर (mutex_lock_समाप्तable(&fan_mutex))
		वापस -ERESTARTSYS;
	rc = fan_get_status(&s);
	अगर (!rc)
		fan_update_desired_level(s);
	mutex_unlock(&fan_mutex);

	अगर (rc)
		वापस rc;
	अगर (status)
		*status = s;

	वापस 0;
पूर्ण

अटल पूर्णांक fan_get_speed(अचिन्हित पूर्णांक *speed)
अणु
	u8 hi, lo;

	चयन (fan_status_access_mode) अणु
	हाल TPACPI_FAN_RD_TPEC:
		/* all except 570, 600e/x, 770e, 770x */
		अगर (unlikely(!fan_select_fan1()))
			वापस -EIO;
		अगर (unlikely(!acpi_ec_पढ़ो(fan_rpm_offset, &lo) ||
			     !acpi_ec_पढ़ो(fan_rpm_offset + 1, &hi)))
			वापस -EIO;

		अगर (likely(speed))
			*speed = (hi << 8) | lo;

		अवरोध;

	शेष:
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fan2_get_speed(अचिन्हित पूर्णांक *speed)
अणु
	u8 hi, lo;
	bool rc;

	चयन (fan_status_access_mode) अणु
	हाल TPACPI_FAN_RD_TPEC:
		/* all except 570, 600e/x, 770e, 770x */
		अगर (unlikely(!fan_select_fan2()))
			वापस -EIO;
		rc = !acpi_ec_पढ़ो(fan_rpm_offset, &lo) ||
			     !acpi_ec_पढ़ो(fan_rpm_offset + 1, &hi);
		fan_select_fan1(); /* play it safe */
		अगर (rc)
			वापस -EIO;

		अगर (likely(speed))
			*speed = (hi << 8) | lo;

		अवरोध;

	शेष:
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fan_set_level(पूर्णांक level)
अणु
	अगर (!fan_control_allowed)
		वापस -EPERM;

	चयन (fan_control_access_mode) अणु
	हाल TPACPI_FAN_WR_ACPI_SFAN:
		अगर ((level < 0) || (level > 7))
			वापस -EINVAL;

		अगर (tp_features.second_fan_ctl) अणु
			अगर (!fan_select_fan2() ||
			    !acpi_evalf(sfan_handle, शून्य, शून्य, "vd", level)) अणु
				pr_warn("Couldn't set 2nd fan level, disabling support\n");
				tp_features.second_fan_ctl = 0;
			पूर्ण
			fan_select_fan1();
		पूर्ण
		अगर (!acpi_evalf(sfan_handle, शून्य, शून्य, "vd", level))
			वापस -EIO;
		अवरोध;

	हाल TPACPI_FAN_WR_ACPI_FANS:
	हाल TPACPI_FAN_WR_TPEC:
		अगर (!(level & TP_EC_FAN_AUTO) &&
		    !(level & TP_EC_FAN_FULLSPEED) &&
		    ((level < 0) || (level > 7)))
			वापस -EINVAL;

		/* safety net should the EC not support AUTO
		 * or FULLSPEED mode bits and just ignore them */
		अगर (level & TP_EC_FAN_FULLSPEED)
			level |= 7;	/* safety min speed 7 */
		अन्यथा अगर (level & TP_EC_FAN_AUTO)
			level |= 4;	/* safety min speed 4 */

		अगर (tp_features.second_fan_ctl) अणु
			अगर (!fan_select_fan2() ||
			    !acpi_ec_ग_लिखो(fan_status_offset, level)) अणु
				pr_warn("Couldn't set 2nd fan level, disabling support\n");
				tp_features.second_fan_ctl = 0;
			पूर्ण
			fan_select_fan1();

		पूर्ण
		अगर (!acpi_ec_ग_लिखो(fan_status_offset, level))
			वापस -EIO;
		अन्यथा
			tp_features.fan_ctrl_status_undef = 0;
		अवरोध;

	शेष:
		वापस -ENXIO;
	पूर्ण

	vdbg_prपूर्णांकk(TPACPI_DBG_FAN,
		"fan control: set fan control register to 0x%02x\n", level);
	वापस 0;
पूर्ण

अटल पूर्णांक fan_set_level_safe(पूर्णांक level)
अणु
	पूर्णांक rc;

	अगर (!fan_control_allowed)
		वापस -EPERM;

	अगर (mutex_lock_समाप्तable(&fan_mutex))
		वापस -ERESTARTSYS;

	अगर (level == TPACPI_FAN_LAST_LEVEL)
		level = fan_control_desired_level;

	rc = fan_set_level(level);
	अगर (!rc)
		fan_update_desired_level(level);

	mutex_unlock(&fan_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक fan_set_enable(व्योम)
अणु
	u8 s;
	पूर्णांक rc;

	अगर (!fan_control_allowed)
		वापस -EPERM;

	अगर (mutex_lock_समाप्तable(&fan_mutex))
		वापस -ERESTARTSYS;

	चयन (fan_control_access_mode) अणु
	हाल TPACPI_FAN_WR_ACPI_FANS:
	हाल TPACPI_FAN_WR_TPEC:
		rc = fan_get_status(&s);
		अगर (rc < 0)
			अवरोध;

		/* Don't go out of emergency fan mode */
		अगर (s != 7) अणु
			s &= 0x07;
			s |= TP_EC_FAN_AUTO | 4; /* min fan speed 4 */
		पूर्ण

		अगर (!acpi_ec_ग_लिखो(fan_status_offset, s))
			rc = -EIO;
		अन्यथा अणु
			tp_features.fan_ctrl_status_undef = 0;
			rc = 0;
		पूर्ण
		अवरोध;

	हाल TPACPI_FAN_WR_ACPI_SFAN:
		rc = fan_get_status(&s);
		अगर (rc < 0)
			अवरोध;

		s &= 0x07;

		/* Set fan to at least level 4 */
		s |= 4;

		अगर (!acpi_evalf(sfan_handle, शून्य, शून्य, "vd", s))
			rc = -EIO;
		अन्यथा
			rc = 0;
		अवरोध;

	शेष:
		rc = -ENXIO;
	पूर्ण

	mutex_unlock(&fan_mutex);

	अगर (!rc)
		vdbg_prपूर्णांकk(TPACPI_DBG_FAN,
			"fan control: set fan control register to 0x%02x\n",
			s);
	वापस rc;
पूर्ण

अटल पूर्णांक fan_set_disable(व्योम)
अणु
	पूर्णांक rc;

	अगर (!fan_control_allowed)
		वापस -EPERM;

	अगर (mutex_lock_समाप्तable(&fan_mutex))
		वापस -ERESTARTSYS;

	rc = 0;
	चयन (fan_control_access_mode) अणु
	हाल TPACPI_FAN_WR_ACPI_FANS:
	हाल TPACPI_FAN_WR_TPEC:
		अगर (!acpi_ec_ग_लिखो(fan_status_offset, 0x00))
			rc = -EIO;
		अन्यथा अणु
			fan_control_desired_level = 0;
			tp_features.fan_ctrl_status_undef = 0;
		पूर्ण
		अवरोध;

	हाल TPACPI_FAN_WR_ACPI_SFAN:
		अगर (!acpi_evalf(sfan_handle, शून्य, शून्य, "vd", 0x00))
			rc = -EIO;
		अन्यथा
			fan_control_desired_level = 0;
		अवरोध;

	शेष:
		rc = -ENXIO;
	पूर्ण

	अगर (!rc)
		vdbg_prपूर्णांकk(TPACPI_DBG_FAN,
			"fan control: set fan control register to 0\n");

	mutex_unlock(&fan_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक fan_set_speed(पूर्णांक speed)
अणु
	पूर्णांक rc;

	अगर (!fan_control_allowed)
		वापस -EPERM;

	अगर (mutex_lock_समाप्तable(&fan_mutex))
		वापस -ERESTARTSYS;

	rc = 0;
	चयन (fan_control_access_mode) अणु
	हाल TPACPI_FAN_WR_ACPI_FANS:
		अगर (speed >= 0 && speed <= 65535) अणु
			अगर (!acpi_evalf(fans_handle, शून्य, शून्य, "vddd",
					speed, speed, speed))
				rc = -EIO;
		पूर्ण अन्यथा
			rc = -EINVAL;
		अवरोध;

	शेष:
		rc = -ENXIO;
	पूर्ण

	mutex_unlock(&fan_mutex);
	वापस rc;
पूर्ण

अटल व्योम fan_watchकरोg_reset(व्योम)
अणु
	अगर (fan_control_access_mode == TPACPI_FAN_WR_NONE)
		वापस;

	अगर (fan_watchकरोg_maxपूर्णांकerval > 0 &&
	    tpacpi_lअगरecycle != TPACPI_LIFE_EXITING)
		mod_delayed_work(tpacpi_wq, &fan_watchकरोg_task,
			msecs_to_jअगरfies(fan_watchकरोg_maxपूर्णांकerval * 1000));
	अन्यथा
		cancel_delayed_work(&fan_watchकरोg_task);
पूर्ण

अटल व्योम fan_watchकरोg_fire(काष्ठा work_काष्ठा *ignored)
अणु
	पूर्णांक rc;

	अगर (tpacpi_lअगरecycle != TPACPI_LIFE_RUNNING)
		वापस;

	pr_notice("fan watchdog: enabling fan\n");
	rc = fan_set_enable();
	अगर (rc < 0) अणु
		pr_err("fan watchdog: error %d while enabling fan, will try again later...\n",
		       rc);
		/* reschedule क्रम later */
		fan_watchकरोg_reset();
	पूर्ण
पूर्ण

/*
 * SYSFS fan layout: hwmon compatible (device)
 *
 * pwm*_enable:
 * 	0: "disengaged" mode
 * 	1: manual mode
 * 	2: native EC "auto" mode (recommended, hardware शेष)
 *
 * pwm*: set speed in manual mode, ignored otherwise.
 * 	0 is level 0; 255 is level 7. Intermediate poपूर्णांकs करोne with linear
 * 	पूर्णांकerpolation.
 *
 * fan*_input: tachometer पढ़ोing, RPM
 *
 *
 * SYSFS fan layout: extensions
 *
 * fan_watchकरोg (driver):
 * 	fan watchकरोg पूर्णांकerval in seconds, 0 disables (शेष), max 120
 */

/* sysfs fan pwm1_enable ----------------------------------------------- */
अटल sमाप_प्रकार fan_pwm1_enable_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	पूर्णांक res, mode;
	u8 status;

	res = fan_get_status_safe(&status);
	अगर (res)
		वापस res;

	अगर (status & TP_EC_FAN_FULLSPEED) अणु
		mode = 0;
	पूर्ण अन्यथा अगर (status & TP_EC_FAN_AUTO) अणु
		mode = 2;
	पूर्ण अन्यथा
		mode = 1;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", mode);
पूर्ण

अटल sमाप_प्रकार fan_pwm1_enable_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;
	पूर्णांक res, level;

	अगर (parse_म_से_अदीर्घ(buf, 2, &t))
		वापस -EINVAL;

	tpacpi_disबंद_usertask("hwmon pwm1_enable",
			"set fan mode to %lu\n", t);

	चयन (t) अणु
	हाल 0:
		level = TP_EC_FAN_FULLSPEED;
		अवरोध;
	हाल 1:
		level = TPACPI_FAN_LAST_LEVEL;
		अवरोध;
	हाल 2:
		level = TP_EC_FAN_AUTO;
		अवरोध;
	हाल 3:
		/* reserved क्रम software-controlled स्वतः mode */
		वापस -ENOSYS;
	शेष:
		वापस -EINVAL;
	पूर्ण

	res = fan_set_level_safe(level);
	अगर (res == -ENXIO)
		वापस -EINVAL;
	अन्यथा अगर (res < 0)
		वापस res;

	fan_watchकरोg_reset();

	वापस count;
पूर्ण

अटल DEVICE_ATTR(pwm1_enable, S_IWUSR | S_IRUGO,
		   fan_pwm1_enable_show, fan_pwm1_enable_store);

/* sysfs fan pwm1 ------------------------------------------------------ */
अटल sमाप_प्रकार fan_pwm1_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	पूर्णांक res;
	u8 status;

	res = fan_get_status_safe(&status);
	अगर (res)
		वापस res;

	अगर ((status &
	     (TP_EC_FAN_AUTO | TP_EC_FAN_FULLSPEED)) != 0)
		status = fan_control_desired_level;

	अगर (status > 7)
		status = 7;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", (status * 255) / 7);
पूर्ण

अटल sमाप_प्रकार fan_pwm1_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ s;
	पूर्णांक rc;
	u8 status, newlevel;

	अगर (parse_म_से_अदीर्घ(buf, 255, &s))
		वापस -EINVAL;

	tpacpi_disबंद_usertask("hwmon pwm1",
			"set fan speed to %lu\n", s);

	/* scale करोwn from 0-255 to 0-7 */
	newlevel = (s >> 5) & 0x07;

	अगर (mutex_lock_समाप्तable(&fan_mutex))
		वापस -ERESTARTSYS;

	rc = fan_get_status(&status);
	अगर (!rc && (status &
		    (TP_EC_FAN_AUTO | TP_EC_FAN_FULLSPEED)) == 0) अणु
		rc = fan_set_level(newlevel);
		अगर (rc == -ENXIO)
			rc = -EINVAL;
		अन्यथा अगर (!rc) अणु
			fan_update_desired_level(newlevel);
			fan_watchकरोg_reset();
		पूर्ण
	पूर्ण

	mutex_unlock(&fan_mutex);
	वापस (rc) ? rc : count;
पूर्ण

अटल DEVICE_ATTR(pwm1, S_IWUSR | S_IRUGO, fan_pwm1_show, fan_pwm1_store);

/* sysfs fan fan1_input ------------------------------------------------ */
अटल sमाप_प्रकार fan_fan1_input_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक res;
	अचिन्हित पूर्णांक speed;

	res = fan_get_speed(&speed);
	अगर (res < 0)
		वापस res;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", speed);
पूर्ण

अटल DEVICE_ATTR(fan1_input, S_IRUGO, fan_fan1_input_show, शून्य);

/* sysfs fan fan2_input ------------------------------------------------ */
अटल sमाप_प्रकार fan_fan2_input_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक res;
	अचिन्हित पूर्णांक speed;

	res = fan2_get_speed(&speed);
	अगर (res < 0)
		वापस res;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", speed);
पूर्ण

अटल DEVICE_ATTR(fan2_input, S_IRUGO, fan_fan2_input_show, शून्य);

/* sysfs fan fan_watchकरोg (hwmon driver) ------------------------------- */
अटल sमाप_प्रकार fan_watchकरोg_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", fan_watchकरोg_maxपूर्णांकerval);
पूर्ण

अटल sमाप_प्रकार fan_watchकरोg_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
				  माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;

	अगर (parse_म_से_अदीर्घ(buf, 120, &t))
		वापस -EINVAL;

	अगर (!fan_control_allowed)
		वापस -EPERM;

	fan_watchकरोg_maxपूर्णांकerval = t;
	fan_watchकरोg_reset();

	tpacpi_disबंद_usertask("fan_watchdog", "set to %lu\n", t);

	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(fan_watchकरोg);

/* --------------------------------------------------------------------- */
अटल काष्ठा attribute *fan_attributes[] = अणु
	&dev_attr_pwm1_enable.attr, &dev_attr_pwm1.attr,
	&dev_attr_fan1_input.attr,
	शून्य, /* क्रम fan2_input */
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group fan_attr_group = अणु
	.attrs = fan_attributes,
पूर्ण;

#घोषणा TPACPI_FAN_Q1	0x0001		/* Unitialized HFSP */
#घोषणा TPACPI_FAN_2FAN	0x0002		/* EC 0x31 bit 0 selects fan2 */
#घोषणा TPACPI_FAN_2CTL	0x0004		/* selects fan2 control */

अटल स्थिर काष्ठा tpacpi_quirk fan_quirk_table[] __initस्थिर = अणु
	TPACPI_QEC_IBM('1', 'Y', TPACPI_FAN_Q1),
	TPACPI_QEC_IBM('7', '8', TPACPI_FAN_Q1),
	TPACPI_QEC_IBM('7', '6', TPACPI_FAN_Q1),
	TPACPI_QEC_IBM('7', '0', TPACPI_FAN_Q1),
	TPACPI_QEC_LNV('7', 'M', TPACPI_FAN_2FAN),
	TPACPI_Q_LNV('N', '1', TPACPI_FAN_2FAN),
	TPACPI_Q_LNV3('N', '1', 'D', TPACPI_FAN_2CTL),	/* P70 */
	TPACPI_Q_LNV3('N', '1', 'E', TPACPI_FAN_2CTL),	/* P50 */
	TPACPI_Q_LNV3('N', '1', 'T', TPACPI_FAN_2CTL),	/* P71 */
	TPACPI_Q_LNV3('N', '1', 'U', TPACPI_FAN_2CTL),	/* P51 */
	TPACPI_Q_LNV3('N', '2', 'C', TPACPI_FAN_2CTL),	/* P52 / P72 */
	TPACPI_Q_LNV3('N', '2', 'N', TPACPI_FAN_2CTL),	/* P53 / P73 */
	TPACPI_Q_LNV3('N', '2', 'E', TPACPI_FAN_2CTL),	/* P1 / X1 Extreme (1st gen) */
	TPACPI_Q_LNV3('N', '2', 'O', TPACPI_FAN_2CTL),	/* P1 / X1 Extreme (2nd gen) */
	TPACPI_Q_LNV3('N', '2', 'V', TPACPI_FAN_2CTL),	/* P1 / X1 Extreme (3nd gen) */
	TPACPI_Q_LNV3('N', '3', '0', TPACPI_FAN_2CTL),	/* P15 (1st gen) / P15v (1st gen) */
	TPACPI_Q_LNV3('N', '3', '2', TPACPI_FAN_2CTL),	/* X1 Carbon (9th gen) */
पूर्ण;

अटल पूर्णांक __init fan_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ quirks;

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_FAN,
			"initializing fan subdriver\n");

	mutex_init(&fan_mutex);
	fan_status_access_mode = TPACPI_FAN_NONE;
	fan_control_access_mode = TPACPI_FAN_WR_NONE;
	fan_control_commands = 0;
	fan_watchकरोg_maxपूर्णांकerval = 0;
	tp_features.fan_ctrl_status_undef = 0;
	tp_features.second_fan = 0;
	tp_features.second_fan_ctl = 0;
	fan_control_desired_level = 7;

	अगर (tpacpi_is_ibm()) अणु
		TPACPI_ACPIHANDLE_INIT(fans);
		TPACPI_ACPIHANDLE_INIT(gfan);
		TPACPI_ACPIHANDLE_INIT(sfan);
	पूर्ण

	quirks = tpacpi_check_quirks(fan_quirk_table,
				     ARRAY_SIZE(fan_quirk_table));

	अगर (gfan_handle) अणु
		/* 570, 600e/x, 770e, 770x */
		fan_status_access_mode = TPACPI_FAN_RD_ACPI_GFAN;
	पूर्ण अन्यथा अणु
		/* all other ThinkPads: note that even old-style
		 * ThinkPad ECs supports the fan control रेजिस्टर */
		अगर (likely(acpi_ec_पढ़ो(fan_status_offset,
					&fan_control_initial_status))) अणु
			fan_status_access_mode = TPACPI_FAN_RD_TPEC;
			अगर (quirks & TPACPI_FAN_Q1)
				fan_quirk1_setup();
			अगर (quirks & TPACPI_FAN_2FAN) अणु
				tp_features.second_fan = 1;
				pr_info("secondary fan support enabled\n");
			पूर्ण
			अगर (quirks & TPACPI_FAN_2CTL) अणु
				tp_features.second_fan = 1;
				tp_features.second_fan_ctl = 1;
				pr_info("secondary fan control enabled\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			pr_err("ThinkPad ACPI EC access misbehaving, fan status and control unavailable\n");
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (sfan_handle) अणु
		/* 570, 770x-JL */
		fan_control_access_mode = TPACPI_FAN_WR_ACPI_SFAN;
		fan_control_commands |=
		    TPACPI_FAN_CMD_LEVEL | TPACPI_FAN_CMD_ENABLE;
	पूर्ण अन्यथा अणु
		अगर (!gfan_handle) अणु
			/* gfan without sfan means no fan control */
			/* all other models implement TP EC 0x2f control */

			अगर (fans_handle) अणु
				/* X31, X40, X41 */
				fan_control_access_mode =
				    TPACPI_FAN_WR_ACPI_FANS;
				fan_control_commands |=
				    TPACPI_FAN_CMD_SPEED |
				    TPACPI_FAN_CMD_LEVEL |
				    TPACPI_FAN_CMD_ENABLE;
			पूर्ण अन्यथा अणु
				fan_control_access_mode = TPACPI_FAN_WR_TPEC;
				fan_control_commands |=
				    TPACPI_FAN_CMD_LEVEL |
				    TPACPI_FAN_CMD_ENABLE;
			पूर्ण
		पूर्ण
	पूर्ण

	vdbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_FAN,
		"fan is %s, modes %d, %d\n",
		str_supported(fan_status_access_mode != TPACPI_FAN_NONE ||
		  fan_control_access_mode != TPACPI_FAN_WR_NONE),
		fan_status_access_mode, fan_control_access_mode);

	/* fan control master चयन */
	अगर (!fan_control_allowed) अणु
		fan_control_access_mode = TPACPI_FAN_WR_NONE;
		fan_control_commands = 0;
		dbg_prपूर्णांकk(TPACPI_DBG_INIT | TPACPI_DBG_FAN,
			   "fan control features disabled by parameter\n");
	पूर्ण

	/* update fan_control_desired_level */
	अगर (fan_status_access_mode != TPACPI_FAN_NONE)
		fan_get_status_safe(शून्य);

	अगर (fan_status_access_mode != TPACPI_FAN_NONE ||
	    fan_control_access_mode != TPACPI_FAN_WR_NONE) अणु
		अगर (tp_features.second_fan) अणु
			/* attach second fan tachometer */
			fan_attributes[ARRAY_SIZE(fan_attributes)-2] =
					&dev_attr_fan2_input.attr;
		पूर्ण
		rc = sysfs_create_group(&tpacpi_hwmon->kobj,
					 &fan_attr_group);
		अगर (rc < 0)
			वापस rc;

		rc = driver_create_file(&tpacpi_hwmon_pdriver.driver,
					&driver_attr_fan_watchकरोg);
		अगर (rc < 0) अणु
			sysfs_हटाओ_group(&tpacpi_hwmon->kobj,
					&fan_attr_group);
			वापस rc;
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा
		वापस 1;
पूर्ण

अटल व्योम fan_निकास(व्योम)
अणु
	vdbg_prपूर्णांकk(TPACPI_DBG_EXIT | TPACPI_DBG_FAN,
		    "cancelling any pending fan watchdog tasks\n");

	/* FIXME: can we really करो this unconditionally? */
	sysfs_हटाओ_group(&tpacpi_hwmon->kobj, &fan_attr_group);
	driver_हटाओ_file(&tpacpi_hwmon_pdriver.driver,
			   &driver_attr_fan_watchकरोg);

	cancel_delayed_work(&fan_watchकरोg_task);
	flush_workqueue(tpacpi_wq);
पूर्ण

अटल व्योम fan_suspend(व्योम)
अणु
	पूर्णांक rc;

	अगर (!fan_control_allowed)
		वापस;

	/* Store fan status in cache */
	fan_control_resume_level = 0;
	rc = fan_get_status_safe(&fan_control_resume_level);
	अगर (rc < 0)
		pr_notice("failed to read fan level for later restore during resume: %d\n",
			  rc);

	/* अगर it is undefined, करोn't attempt to restore it.
	 * KEEP THIS LAST */
	अगर (tp_features.fan_ctrl_status_undef)
		fan_control_resume_level = 0;
पूर्ण

अटल व्योम fan_resume(व्योम)
अणु
	u8 current_level = 7;
	bool करो_set = false;
	पूर्णांक rc;

	/* DSDT *always* updates status on resume */
	tp_features.fan_ctrl_status_undef = 0;

	अगर (!fan_control_allowed ||
	    !fan_control_resume_level ||
	    (fan_get_status_safe(&current_level) < 0))
		वापस;

	चयन (fan_control_access_mode) अणु
	हाल TPACPI_FAN_WR_ACPI_SFAN:
		/* never decrease fan level */
		करो_set = (fan_control_resume_level > current_level);
		अवरोध;
	हाल TPACPI_FAN_WR_ACPI_FANS:
	हाल TPACPI_FAN_WR_TPEC:
		/* never decrease fan level, scale is:
		 * TP_EC_FAN_FULLSPEED > 7 >= TP_EC_FAN_AUTO
		 *
		 * We expect the firmware to set either 7 or AUTO, but we
		 * handle FULLSPEED out of paranoia.
		 *
		 * So, we can safely only restore FULLSPEED or 7, anything
		 * अन्यथा could slow the fan.  Restoring AUTO is useless, at
		 * best that's exactly what the DSDT alपढ़ोy set (it is the
		 * slower it uses).
		 *
		 * Always keep in mind that the DSDT *will* have set the
		 * fans to what the venकरोr supposes is the best level.  We
		 * muck with it only to speed the fan up.
		 */
		अगर (fan_control_resume_level != 7 &&
		    !(fan_control_resume_level & TP_EC_FAN_FULLSPEED))
			वापस;
		अन्यथा
			करो_set = !(current_level & TP_EC_FAN_FULLSPEED) &&
				 (current_level != fan_control_resume_level);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	अगर (करो_set) अणु
		pr_notice("restoring fan level to 0x%02x\n",
			  fan_control_resume_level);
		rc = fan_set_level_safe(fan_control_resume_level);
		अगर (rc < 0)
			pr_notice("failed to restore fan level: %d\n", rc);
	पूर्ण
पूर्ण

अटल पूर्णांक fan_पढ़ो(काष्ठा seq_file *m)
अणु
	पूर्णांक rc;
	u8 status;
	अचिन्हित पूर्णांक speed = 0;

	चयन (fan_status_access_mode) अणु
	हाल TPACPI_FAN_RD_ACPI_GFAN:
		/* 570, 600e/x, 770e, 770x */
		rc = fan_get_status_safe(&status);
		अगर (rc < 0)
			वापस rc;

		seq_म_लिखो(m, "status:\t\t%s\n"
			       "level:\t\t%d\n",
			       (status != 0) ? "enabled" : "disabled", status);
		अवरोध;

	हाल TPACPI_FAN_RD_TPEC:
		/* all except 570, 600e/x, 770e, 770x */
		rc = fan_get_status_safe(&status);
		अगर (rc < 0)
			वापस rc;

		seq_म_लिखो(m, "status:\t\t%s\n",
			       (status != 0) ? "enabled" : "disabled");

		rc = fan_get_speed(&speed);
		अगर (rc < 0)
			वापस rc;

		seq_म_लिखो(m, "speed:\t\t%d\n", speed);

		अगर (status & TP_EC_FAN_FULLSPEED)
			/* Disengaged mode takes precedence */
			seq_म_लिखो(m, "level:\t\tdisengaged\n");
		अन्यथा अगर (status & TP_EC_FAN_AUTO)
			seq_म_लिखो(m, "level:\t\tauto\n");
		अन्यथा
			seq_म_लिखो(m, "level:\t\t%d\n", status);
		अवरोध;

	हाल TPACPI_FAN_NONE:
	शेष:
		seq_म_लिखो(m, "status:\t\tnot supported\n");
	पूर्ण

	अगर (fan_control_commands & TPACPI_FAN_CMD_LEVEL) अणु
		seq_म_लिखो(m, "commands:\tlevel <level>");

		चयन (fan_control_access_mode) अणु
		हाल TPACPI_FAN_WR_ACPI_SFAN:
			seq_म_लिखो(m, " (<level> is 0-7)\n");
			अवरोध;

		शेष:
			seq_म_लिखो(m, " (<level> is 0-7, auto, disengaged, full-speed)\n");
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (fan_control_commands & TPACPI_FAN_CMD_ENABLE)
		seq_म_लिखो(m, "commands:\tenable, disable\n"
			       "commands:\twatchdog <timeout> (<timeout> is 0 (off), 1-120 (seconds))\n");

	अगर (fan_control_commands & TPACPI_FAN_CMD_SPEED)
		seq_म_लिखो(m, "commands:\tspeed <speed> (<speed> is 0-65535)\n");

	वापस 0;
पूर्ण

अटल पूर्णांक fan_ग_लिखो_cmd_level(स्थिर अक्षर *cmd, पूर्णांक *rc)
अणु
	पूर्णांक level;

	अगर (म_मापcmp(cmd, "level auto") == 0)
		level = TP_EC_FAN_AUTO;
	अन्यथा अगर ((म_मापcmp(cmd, "level disengaged") == 0) |
			(म_मापcmp(cmd, "level full-speed") == 0))
		level = TP_EC_FAN_FULLSPEED;
	अन्यथा अगर (माला_पूछो(cmd, "level %d", &level) != 1)
		वापस 0;

	*rc = fan_set_level_safe(level);
	अगर (*rc == -ENXIO)
		pr_err("level command accepted for unsupported access mode %d\n",
		       fan_control_access_mode);
	अन्यथा अगर (!*rc)
		tpacpi_disबंद_usertask("procfs fan",
			"set level to %d\n", level);

	वापस 1;
पूर्ण

अटल पूर्णांक fan_ग_लिखो_cmd_enable(स्थिर अक्षर *cmd, पूर्णांक *rc)
अणु
	अगर (म_मापcmp(cmd, "enable") != 0)
		वापस 0;

	*rc = fan_set_enable();
	अगर (*rc == -ENXIO)
		pr_err("enable command accepted for unsupported access mode %d\n",
		       fan_control_access_mode);
	अन्यथा अगर (!*rc)
		tpacpi_disबंद_usertask("procfs fan", "enable\n");

	वापस 1;
पूर्ण

अटल पूर्णांक fan_ग_लिखो_cmd_disable(स्थिर अक्षर *cmd, पूर्णांक *rc)
अणु
	अगर (म_मापcmp(cmd, "disable") != 0)
		वापस 0;

	*rc = fan_set_disable();
	अगर (*rc == -ENXIO)
		pr_err("disable command accepted for unsupported access mode %d\n",
		       fan_control_access_mode);
	अन्यथा अगर (!*rc)
		tpacpi_disबंद_usertask("procfs fan", "disable\n");

	वापस 1;
पूर्ण

अटल पूर्णांक fan_ग_लिखो_cmd_speed(स्थिर अक्षर *cmd, पूर्णांक *rc)
अणु
	पूर्णांक speed;

	/* TODO:
	 * Support speed <low> <medium> <high> ? */

	अगर (माला_पूछो(cmd, "speed %d", &speed) != 1)
		वापस 0;

	*rc = fan_set_speed(speed);
	अगर (*rc == -ENXIO)
		pr_err("speed command accepted for unsupported access mode %d\n",
		       fan_control_access_mode);
	अन्यथा अगर (!*rc)
		tpacpi_disबंद_usertask("procfs fan",
			"set speed to %d\n", speed);

	वापस 1;
पूर्ण

अटल पूर्णांक fan_ग_लिखो_cmd_watchकरोg(स्थिर अक्षर *cmd, पूर्णांक *rc)
अणु
	पूर्णांक पूर्णांकerval;

	अगर (माला_पूछो(cmd, "watchdog %d", &पूर्णांकerval) != 1)
		वापस 0;

	अगर (पूर्णांकerval < 0 || पूर्णांकerval > 120)
		*rc = -EINVAL;
	अन्यथा अणु
		fan_watchकरोg_maxपूर्णांकerval = पूर्णांकerval;
		tpacpi_disबंद_usertask("procfs fan",
			"set watchdog timer to %d\n",
			पूर्णांकerval);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक fan_ग_लिखो(अक्षर *buf)
अणु
	अक्षर *cmd;
	पूर्णांक rc = 0;

	जबतक (!rc && (cmd = strsep(&buf, ","))) अणु
		अगर (!((fan_control_commands & TPACPI_FAN_CMD_LEVEL) &&
		      fan_ग_लिखो_cmd_level(cmd, &rc)) &&
		    !((fan_control_commands & TPACPI_FAN_CMD_ENABLE) &&
		      (fan_ग_लिखो_cmd_enable(cmd, &rc) ||
		       fan_ग_लिखो_cmd_disable(cmd, &rc) ||
		       fan_ग_लिखो_cmd_watchकरोg(cmd, &rc))) &&
		    !((fan_control_commands & TPACPI_FAN_CMD_SPEED) &&
		      fan_ग_लिखो_cmd_speed(cmd, &rc))
		    )
			rc = -EINVAL;
		अन्यथा अगर (!rc)
			fan_watchकरोg_reset();
	पूर्ण

	वापस rc;
पूर्ण

अटल काष्ठा ibm_काष्ठा fan_driver_data = अणु
	.name = "fan",
	.पढ़ो = fan_पढ़ो,
	.ग_लिखो = fan_ग_लिखो,
	.निकास = fan_निकास,
	.suspend = fan_suspend,
	.resume = fan_resume,
पूर्ण;

/*************************************************************************
 * Mute LED subdriver
 */

#घोषणा TPACPI_LED_MAX		2

काष्ठा tp_led_table अणु
	acpi_string name;
	पूर्णांक on_value;
	पूर्णांक off_value;
	पूर्णांक state;
पूर्ण;

अटल काष्ठा tp_led_table led_tables[TPACPI_LED_MAX] = अणु
	[LED_AUDIO_MUTE] = अणु
		.name = "SSMS",
		.on_value = 1,
		.off_value = 0,
	पूर्ण,
	[LED_AUDIO_MICMUTE] = अणु
		.name = "MMTS",
		.on_value = 2,
		.off_value = 0,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mute_led_on_off(काष्ठा tp_led_table *t, bool state)
अणु
	acpi_handle temp;
	पूर्णांक output;

	अगर (ACPI_FAILURE(acpi_get_handle(hkey_handle, t->name, &temp))) अणु
		pr_warn("Thinkpad ACPI has no %s interface.\n", t->name);
		वापस -EIO;
	पूर्ण

	अगर (!acpi_evalf(hkey_handle, &output, t->name, "dd",
			state ? t->on_value : t->off_value))
		वापस -EIO;

	t->state = state;
	वापस state;
पूर्ण

अटल पूर्णांक tpacpi_led_set(पूर्णांक whichled, bool on)
अणु
	काष्ठा tp_led_table *t;

	t = &led_tables[whichled];
	अगर (t->state < 0 || t->state == on)
		वापस t->state;
	वापस mute_led_on_off(t, on);
पूर्ण

अटल पूर्णांक tpacpi_led_mute_set(काष्ठा led_classdev *led_cdev,
			       क्रमागत led_brightness brightness)
अणु
	वापस tpacpi_led_set(LED_AUDIO_MUTE, brightness != LED_OFF);
पूर्ण

अटल पूर्णांक tpacpi_led_micmute_set(काष्ठा led_classdev *led_cdev,
				  क्रमागत led_brightness brightness)
अणु
	वापस tpacpi_led_set(LED_AUDIO_MICMUTE, brightness != LED_OFF);
पूर्ण

अटल काष्ठा led_classdev mute_led_cdev[TPACPI_LED_MAX] = अणु
	[LED_AUDIO_MUTE] = अणु
		.name		= "platform::mute",
		.max_brightness = 1,
		.brightness_set_blocking = tpacpi_led_mute_set,
		.शेष_trigger = "audio-mute",
	पूर्ण,
	[LED_AUDIO_MICMUTE] = अणु
		.name		= "platform::micmute",
		.max_brightness = 1,
		.brightness_set_blocking = tpacpi_led_micmute_set,
		.शेष_trigger = "audio-micmute",
	पूर्ण,
पूर्ण;

अटल पूर्णांक mute_led_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	acpi_handle temp;
	पूर्णांक i, err;

	क्रम (i = 0; i < TPACPI_LED_MAX; i++) अणु
		काष्ठा tp_led_table *t = &led_tables[i];
		अगर (ACPI_FAILURE(acpi_get_handle(hkey_handle, t->name, &temp))) अणु
			t->state = -ENODEV;
			जारी;
		पूर्ण

		mute_led_cdev[i].brightness = ledtrig_audio_get(i);
		err = led_classdev_रेजिस्टर(&tpacpi_pdev->dev, &mute_led_cdev[i]);
		अगर (err < 0) अणु
			जबतक (i--)
				led_classdev_unरेजिस्टर(&mute_led_cdev[i]);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mute_led_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TPACPI_LED_MAX; i++) अणु
		led_classdev_unरेजिस्टर(&mute_led_cdev[i]);
		tpacpi_led_set(i, false);
	पूर्ण
पूर्ण

अटल व्योम mute_led_resume(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TPACPI_LED_MAX; i++) अणु
		काष्ठा tp_led_table *t = &led_tables[i];
		अगर (t->state >= 0)
			mute_led_on_off(t, t->state);
	पूर्ण
पूर्ण

अटल काष्ठा ibm_काष्ठा mute_led_driver_data = अणु
	.name = "mute_led",
	.निकास = mute_led_निकास,
	.resume = mute_led_resume,
पूर्ण;

/*
 * Battery Wear Control Driver
 * Contact: Ognjen Galic <smclt30p@gmail.com>
 */

/* Metadata */

#घोषणा GET_START	"BCTG"
#घोषणा SET_START	"BCCS"
#घोषणा GET_STOP	"BCSG"
#घोषणा SET_STOP	"BCSS"

क्रमागत अणु
	BAT_ANY = 0,
	BAT_PRIMARY = 1,
	BAT_SECONDARY = 2
पूर्ण;

क्रमागत अणु
	/* Error condition bit */
	METHOD_ERR = BIT(31),
पूर्ण;

क्रमागत अणु
	/* This is used in the get/set helpers */
	THRESHOLD_START,
	THRESHOLD_STOP,
पूर्ण;

काष्ठा tpacpi_battery_data अणु
	पूर्णांक अक्षरge_start;
	पूर्णांक start_support;
	पूर्णांक अक्षरge_stop;
	पूर्णांक stop_support;
पूर्ण;

काष्ठा tpacpi_battery_driver_data अणु
	काष्ठा tpacpi_battery_data batteries[3];
	पूर्णांक inभागidual_addressing;
पूर्ण;

अटल काष्ठा tpacpi_battery_driver_data battery_info;

/* ACPI helpers/functions/probes */

/**
 * This evaluates a ACPI method call specअगरic to the battery
 * ACPI extension. The specअगरics are that an error is marked
 * in the 32rd bit of the response, so we just check that here.
 */
अटल acpi_status tpacpi_battery_acpi_eval(अक्षर *method, पूर्णांक *ret, पूर्णांक param)
अणु
	पूर्णांक response;

	अगर (!acpi_evalf(hkey_handle, &response, method, "dd", param)) अणु
		acpi_handle_err(hkey_handle, "%s: evaluate failed", method);
		वापस AE_ERROR;
	पूर्ण
	अगर (response & METHOD_ERR) अणु
		acpi_handle_err(hkey_handle,
				"%s evaluated but flagged as error", method);
		वापस AE_ERROR;
	पूर्ण
	*ret = response;
	वापस AE_OK;
पूर्ण

अटल पूर्णांक tpacpi_battery_get(पूर्णांक what, पूर्णांक battery, पूर्णांक *ret)
अणु
	चयन (what) अणु
	हाल THRESHOLD_START:
		अगर ACPI_FAILURE(tpacpi_battery_acpi_eval(GET_START, ret, battery))
			वापस -ENODEV;

		/* The value is in the low 8 bits of the response */
		*ret = *ret & 0xFF;
		वापस 0;
	हाल THRESHOLD_STOP:
		अगर ACPI_FAILURE(tpacpi_battery_acpi_eval(GET_STOP, ret, battery))
			वापस -ENODEV;
		/* Value is in lower 8 bits */
		*ret = *ret & 0xFF;
		/*
		 * On the stop value, अगर we वापस 0 that
		 * करोes not make any sense. 0 means Default, which
		 * means that अक्षरging stops at 100%, so we वापस
		 * that.
		 */
		अगर (*ret == 0)
			*ret = 100;
		वापस 0;
	शेष:
		pr_crit("wrong parameter: %d", what);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक tpacpi_battery_set(पूर्णांक what, पूर्णांक battery, पूर्णांक value)
अणु
	पूर्णांक param, ret;
	/* The first 8 bits are the value of the threshold */
	param = value;
	/* The battery ID is in bits 8-9, 2 bits */
	param |= battery << 8;

	चयन (what) अणु
	हाल THRESHOLD_START:
		अगर ACPI_FAILURE(tpacpi_battery_acpi_eval(SET_START, &ret, param)) अणु
			pr_err("failed to set charge threshold on battery %d",
					battery);
			वापस -ENODEV;
		पूर्ण
		वापस 0;
	हाल THRESHOLD_STOP:
		अगर ACPI_FAILURE(tpacpi_battery_acpi_eval(SET_STOP, &ret, param)) अणु
			pr_err("failed to set stop threshold: %d", battery);
			वापस -ENODEV;
		पूर्ण
		वापस 0;
	शेष:
		pr_crit("wrong parameter: %d", what);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक tpacpi_battery_probe(पूर्णांक battery)
अणु
	पूर्णांक ret = 0;

	स_रखो(&battery_info.batteries[battery], 0,
		माप(battery_info.batteries[battery]));

	/*
	 * 1) Get the current start threshold
	 * 2) Check क्रम support
	 * 3) Get the current stop threshold
	 * 4) Check क्रम support
	 */
	अगर (acpi_has_method(hkey_handle, GET_START)) अणु
		अगर ACPI_FAILURE(tpacpi_battery_acpi_eval(GET_START, &ret, battery)) अणु
			pr_err("Error probing battery %d\n", battery);
			वापस -ENODEV;
		पूर्ण
		/* Inभागidual addressing is in bit 9 */
		अगर (ret & BIT(9))
			battery_info.inभागidual_addressing = true;
		/* Support is marked in bit 8 */
		अगर (ret & BIT(8))
			battery_info.batteries[battery].start_support = 1;
		अन्यथा
			वापस -ENODEV;
		अगर (tpacpi_battery_get(THRESHOLD_START, battery,
			&battery_info.batteries[battery].अक्षरge_start)) अणु
			pr_err("Error probing battery %d\n", battery);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	अगर (acpi_has_method(hkey_handle, GET_STOP)) अणु
		अगर ACPI_FAILURE(tpacpi_battery_acpi_eval(GET_STOP, &ret, battery)) अणु
			pr_err("Error probing battery stop; %d\n", battery);
			वापस -ENODEV;
		पूर्ण
		/* Support is marked in bit 8 */
		अगर (ret & BIT(8))
			battery_info.batteries[battery].stop_support = 1;
		अन्यथा
			वापस -ENODEV;
		अगर (tpacpi_battery_get(THRESHOLD_STOP, battery,
			&battery_info.batteries[battery].अक्षरge_stop)) अणु
			pr_err("Error probing battery stop: %d\n", battery);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	pr_info("battery %d registered (start %d, stop %d)",
			battery,
			battery_info.batteries[battery].अक्षरge_start,
			battery_info.batteries[battery].अक्षरge_stop);

	वापस 0;
पूर्ण

/* General helper functions */

अटल पूर्णांक tpacpi_battery_get_id(स्थिर अक्षर *battery_name)
अणु

	अगर (म_भेद(battery_name, "BAT0") == 0 ||
	    tp_features.battery_क्रमce_primary)
		वापस BAT_PRIMARY;
	अगर (म_भेद(battery_name, "BAT1") == 0)
		वापस BAT_SECONDARY;
	/*
	 * If क्रम some reason the battery is not BAT0 nor is it
	 * BAT1, we will assume it's the शेष, first battery,
	 * AKA primary.
	 */
	pr_warn("unknown battery %s, assuming primary", battery_name);
	वापस BAT_PRIMARY;
पूर्ण

/* sysfs पूर्णांकerface */

अटल sमाप_प्रकार tpacpi_battery_store(पूर्णांक what,
				    काष्ठा device *dev,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा घातer_supply *supply = to_घातer_supply(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक battery, rval;
	/*
	 * Some प्रणालीs have support क्रम more than
	 * one battery. If that is the हाल,
	 * tpacpi_battery_probe marked that addressing
	 * them inभागidually is supported, so we करो that
	 * based on the device काष्ठा.
	 *
	 * On प्रणालीs that are not supported, we assume
	 * the primary as most of the ACPI calls fail
	 * with "Any Battery" as the parameter.
	 */
	अगर (battery_info.inभागidual_addressing)
		/* BAT_PRIMARY or BAT_SECONDARY */
		battery = tpacpi_battery_get_id(supply->desc->name);
	अन्यथा
		battery = BAT_PRIMARY;

	rval = kम_से_अदीर्घ(buf, 10, &value);
	अगर (rval)
		वापस rval;

	चयन (what) अणु
	हाल THRESHOLD_START:
		अगर (!battery_info.batteries[battery].start_support)
			वापस -ENODEV;
		/* valid values are [0, 99] */
		अगर (value > 99)
			वापस -EINVAL;
		अगर (value > battery_info.batteries[battery].अक्षरge_stop)
			वापस -EINVAL;
		अगर (tpacpi_battery_set(THRESHOLD_START, battery, value))
			वापस -ENODEV;
		battery_info.batteries[battery].अक्षरge_start = value;
		वापस count;

	हाल THRESHOLD_STOP:
		अगर (!battery_info.batteries[battery].stop_support)
			वापस -ENODEV;
		/* valid values are [1, 100] */
		अगर (value < 1 || value > 100)
			वापस -EINVAL;
		अगर (value < battery_info.batteries[battery].अक्षरge_start)
			वापस -EINVAL;
		battery_info.batteries[battery].अक्षरge_stop = value;
		/*
		 * When 100 is passed to stop, we need to flip
		 * it to 0 as that the EC understands that as
		 * "Default", which will अक्षरge to 100%
		 */
		अगर (value == 100)
			value = 0;
		अगर (tpacpi_battery_set(THRESHOLD_STOP, battery, value))
			वापस -EINVAL;
		वापस count;
	शेष:
		pr_crit("Wrong parameter: %d", what);
		वापस -EINVAL;
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार tpacpi_battery_show(पूर्णांक what,
				   काष्ठा device *dev,
				   अक्षर *buf)
अणु
	काष्ठा घातer_supply *supply = to_घातer_supply(dev);
	पूर्णांक ret, battery;
	/*
	 * Some प्रणालीs have support क्रम more than
	 * one battery. If that is the हाल,
	 * tpacpi_battery_probe marked that addressing
	 * them inभागidually is supported, so we;
	 * based on the device काष्ठा.
	 *
	 * On प्रणालीs that are not supported, we assume
	 * the primary as most of the ACPI calls fail
	 * with "Any Battery" as the parameter.
	 */
	अगर (battery_info.inभागidual_addressing)
		/* BAT_PRIMARY or BAT_SECONDARY */
		battery = tpacpi_battery_get_id(supply->desc->name);
	अन्यथा
		battery = BAT_PRIMARY;
	अगर (tpacpi_battery_get(what, battery, &ret))
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n", ret);
पूर्ण

अटल sमाप_प्रकार अक्षरge_control_start_threshold_show(काष्ठा device *device,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	वापस tpacpi_battery_show(THRESHOLD_START, device, buf);
पूर्ण

अटल sमाप_प्रकार अक्षरge_control_end_threshold_show(काष्ठा device *device,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	वापस tpacpi_battery_show(THRESHOLD_STOP, device, buf);
पूर्ण

अटल sमाप_प्रकार अक्षरge_control_start_threshold_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस tpacpi_battery_store(THRESHOLD_START, dev, buf, count);
पूर्ण

अटल sमाप_प्रकार अक्षरge_control_end_threshold_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस tpacpi_battery_store(THRESHOLD_STOP, dev, buf, count);
पूर्ण

अटल DEVICE_ATTR_RW(अक्षरge_control_start_threshold);
अटल DEVICE_ATTR_RW(अक्षरge_control_end_threshold);
अटल काष्ठा device_attribute dev_attr_अक्षरge_start_threshold = __ATTR(
	अक्षरge_start_threshold,
	0644,
	अक्षरge_control_start_threshold_show,
	अक्षरge_control_start_threshold_store
);
अटल काष्ठा device_attribute dev_attr_अक्षरge_stop_threshold = __ATTR(
	अक्षरge_stop_threshold,
	0644,
	अक्षरge_control_end_threshold_show,
	अक्षरge_control_end_threshold_store
);

अटल काष्ठा attribute *tpacpi_battery_attrs[] = अणु
	&dev_attr_अक्षरge_control_start_threshold.attr,
	&dev_attr_अक्षरge_control_end_threshold.attr,
	&dev_attr_अक्षरge_start_threshold.attr,
	&dev_attr_अक्षरge_stop_threshold.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(tpacpi_battery);

/* ACPI battery hooking */

अटल पूर्णांक tpacpi_battery_add(काष्ठा घातer_supply *battery)
अणु
	पूर्णांक batteryid = tpacpi_battery_get_id(battery->desc->name);

	अगर (tpacpi_battery_probe(batteryid))
		वापस -ENODEV;
	अगर (device_add_groups(&battery->dev, tpacpi_battery_groups))
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल पूर्णांक tpacpi_battery_हटाओ(काष्ठा घातer_supply *battery)
अणु
	device_हटाओ_groups(&battery->dev, tpacpi_battery_groups);
	वापस 0;
पूर्ण

अटल काष्ठा acpi_battery_hook battery_hook = अणु
	.add_battery = tpacpi_battery_add,
	.हटाओ_battery = tpacpi_battery_हटाओ,
	.name = "ThinkPad Battery Extension",
पूर्ण;

/* Subdriver init/निकास */

अटल स्थिर काष्ठा tpacpi_quirk battery_quirk_table[] __initस्थिर = अणु
	/*
	 * Inभागidual addressing is broken on models that expose the
	 * primary battery as BAT1.
	 */
	TPACPI_Q_LNV('J', '7', true),       /* B5400 */
	TPACPI_Q_LNV('J', 'I', true),       /* Thinkpad 11e */
	TPACPI_Q_LNV3('R', '0', 'B', true), /* Thinkpad 11e gen 3 */
	TPACPI_Q_LNV3('R', '0', 'C', true), /* Thinkpad 13 */
	TPACPI_Q_LNV3('R', '0', 'J', true), /* Thinkpad 13 gen 2 */
	TPACPI_Q_LNV3('R', '0', 'K', true), /* Thinkpad 11e gen 4 celeron BIOS */
पूर्ण;

अटल पूर्णांक __init tpacpi_battery_init(काष्ठा ibm_init_काष्ठा *ibm)
अणु
	स_रखो(&battery_info, 0, माप(battery_info));

	tp_features.battery_क्रमce_primary = tpacpi_check_quirks(
					battery_quirk_table,
					ARRAY_SIZE(battery_quirk_table));

	battery_hook_रेजिस्टर(&battery_hook);
	वापस 0;
पूर्ण

अटल व्योम tpacpi_battery_निकास(व्योम)
अणु
	battery_hook_unरेजिस्टर(&battery_hook);
पूर्ण

अटल काष्ठा ibm_काष्ठा battery_driver_data = अणु
	.name = "battery",
	.निकास = tpacpi_battery_निकास,
पूर्ण;

/*************************************************************************
 * LCD Shaकरोw subdriver, क्रम the Lenovo PrivacyGuard feature
 */

अटल पूर्णांक lcdshaकरोw_state;

अटल पूर्णांक lcdshaकरोw_on_off(bool state)
अणु
	acpi_handle set_shaकरोw_handle;
	पूर्णांक output;

	अगर (ACPI_FAILURE(acpi_get_handle(hkey_handle, "SSSS", &set_shaकरोw_handle))) अणु
		pr_warn("Thinkpad ACPI has no %s interface.\n", "SSSS");
		वापस -EIO;
	पूर्ण

	अगर (!acpi_evalf(set_shaकरोw_handle, &output, शून्य, "dd", (पूर्णांक)state))
		वापस -EIO;

	lcdshaकरोw_state = state;
	वापस 0;
पूर्ण

अटल पूर्णांक lcdshaकरोw_set(bool on)
अणु
	अगर (lcdshaकरोw_state < 0)
		वापस lcdshaकरोw_state;
	अगर (lcdshaकरोw_state == on)
		वापस 0;
	वापस lcdshaकरोw_on_off(on);
पूर्ण

अटल पूर्णांक tpacpi_lcdshaकरोw_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	acpi_handle get_shaकरोw_handle;
	पूर्णांक output;

	अगर (ACPI_FAILURE(acpi_get_handle(hkey_handle, "GSSS", &get_shaकरोw_handle))) अणु
		lcdshaकरोw_state = -ENODEV;
		वापस 0;
	पूर्ण

	अगर (!acpi_evalf(get_shaकरोw_handle, &output, शून्य, "dd", 0)) अणु
		lcdshaकरोw_state = -EIO;
		वापस -EIO;
	पूर्ण
	अगर (!(output & 0x10000)) अणु
		lcdshaकरोw_state = -ENODEV;
		वापस 0;
	पूर्ण
	lcdshaकरोw_state = output & 0x1;

	वापस 0;
पूर्ण

अटल व्योम lcdshaकरोw_resume(व्योम)
अणु
	अगर (lcdshaकरोw_state >= 0)
		lcdshaकरोw_on_off(lcdshaकरोw_state);
पूर्ण

अटल पूर्णांक lcdshaकरोw_पढ़ो(काष्ठा seq_file *m)
अणु
	अगर (lcdshaकरोw_state < 0) अणु
		seq_माला_दो(m, "status:\t\tnot supported\n");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "status:\t\t%d\n", lcdshaकरोw_state);
		seq_माला_दो(m, "commands:\t0, 1\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lcdshaकरोw_ग_लिखो(अक्षर *buf)
अणु
	अक्षर *cmd;
	पूर्णांक res, state = -EINVAL;

	अगर (lcdshaकरोw_state < 0)
		वापस -ENODEV;

	जबतक ((cmd = strsep(&buf, ","))) अणु
		res = kstrtoपूर्णांक(cmd, 10, &state);
		अगर (res < 0)
			वापस res;
	पूर्ण

	अगर (state >= 2 || state < 0)
		वापस -EINVAL;

	वापस lcdshaकरोw_set(state);
पूर्ण

अटल काष्ठा ibm_काष्ठा lcdshaकरोw_driver_data = अणु
	.name = "lcdshadow",
	.resume = lcdshaकरोw_resume,
	.पढ़ो = lcdshaकरोw_पढ़ो,
	.ग_लिखो = lcdshaकरोw_ग_लिखो,
पूर्ण;

/*************************************************************************
 * Thinkpad sensor पूर्णांकerfaces
 */

#घोषणा DYTC_CMD_QUERY        0 /* To get DYTC status - enable/revision */
#घोषणा DYTC_QUERY_ENABLE_BIT 8  /* Bit        8 - 0 = disabled, 1 = enabled */
#घोषणा DYTC_QUERY_SUBREV_BIT 16 /* Bits 16 - 27 - sub revision */
#घोषणा DYTC_QUERY_REV_BIT    28 /* Bits 28 - 31 - revision */

#घोषणा DYTC_CMD_GET          2 /* To get current IC function and mode */
#घोषणा DYTC_GET_LAPMODE_BIT 17 /* Set when in lapmode */

#घोषणा PALMSENSOR_PRESENT_BIT 0 /* Determine अगर psensor present */
#घोषणा PALMSENSOR_ON_BIT      1 /* psensor status */

अटल bool has_palmsensor;
अटल bool has_lapsensor;
अटल bool palm_state;
अटल bool lap_state;
अटल पूर्णांक dytc_version;

अटल पूर्णांक dytc_command(पूर्णांक command, पूर्णांक *output)
अणु
	acpi_handle dytc_handle;

	अगर (ACPI_FAILURE(acpi_get_handle(hkey_handle, "DYTC", &dytc_handle))) अणु
		/* Platक्रमm करोesn't support DYTC */
		वापस -ENODEV;
	पूर्ण
	अगर (!acpi_evalf(dytc_handle, output, शून्य, "dd", command))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक dytc_get_version(व्योम)
अणु
	पूर्णांक err, output;

	/* Check अगर we've been called beक्रमe - and just वापस cached value */
	अगर (dytc_version)
		वापस dytc_version;

	/* Otherwise query DYTC and extract version inक्रमmation */
	err = dytc_command(DYTC_CMD_QUERY, &output);
	/*
	 * If support isn't available (ENODEV) then don't वापस an error
	 * and करोn't create the sysfs group
	 */
	अगर (err == -ENODEV)
		वापस 0;
	/* For all other errors we can flag the failure */
	अगर (err)
		वापस err;

	/* Check DYTC is enabled and supports mode setting */
	अगर (output & BIT(DYTC_QUERY_ENABLE_BIT))
		dytc_version = (output >> DYTC_QUERY_REV_BIT) & 0xF;

	वापस 0;
पूर्ण

अटल पूर्णांक lapsensor_get(bool *present, bool *state)
अणु
	पूर्णांक output, err;

	*present = false;
	err = dytc_command(DYTC_CMD_GET, &output);
	अगर (err)
		वापस err;

	*present = true; /*If we get his far, we have lapmode support*/
	*state = output & BIT(DYTC_GET_LAPMODE_BIT) ? true : false;
	वापस 0;
पूर्ण

अटल पूर्णांक palmsensor_get(bool *present, bool *state)
अणु
	acpi_handle psensor_handle;
	पूर्णांक output;

	*present = false;
	अगर (ACPI_FAILURE(acpi_get_handle(hkey_handle, "GPSS", &psensor_handle)))
		वापस -ENODEV;
	अगर (!acpi_evalf(psensor_handle, &output, शून्य, "d"))
		वापस -EIO;

	*present = output & BIT(PALMSENSOR_PRESENT_BIT) ? true : false;
	*state = output & BIT(PALMSENSOR_ON_BIT) ? true : false;
	वापस 0;
पूर्ण

अटल व्योम lapsensor_refresh(व्योम)
अणु
	bool state;
	पूर्णांक err;

	अगर (has_lapsensor) अणु
		err = lapsensor_get(&has_lapsensor, &state);
		अगर (err)
			वापस;
		अगर (lap_state != state) अणु
			lap_state = state;
			sysfs_notअगरy(&tpacpi_pdev->dev.kobj, शून्य, "dytc_lapmode");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम palmsensor_refresh(व्योम)
अणु
	bool state;
	पूर्णांक err;

	अगर (has_palmsensor) अणु
		err = palmsensor_get(&has_palmsensor, &state);
		अगर (err)
			वापस;
		अगर (palm_state != state) अणु
			palm_state = state;
			sysfs_notअगरy(&tpacpi_pdev->dev.kobj, शून्य, "palmsensor");
		पूर्ण
	पूर्ण
पूर्ण

अटल sमाप_प्रकार dytc_lapmode_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	अगर (has_lapsensor)
		वापस sysfs_emit(buf, "%d\n", lap_state);
	वापस sysfs_emit(buf, "\n");
पूर्ण
अटल DEVICE_ATTR_RO(dytc_lapmode);

अटल sमाप_प्रकार palmsensor_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	अगर (has_palmsensor)
		वापस sysfs_emit(buf, "%d\n", palm_state);
	वापस sysfs_emit(buf, "\n");
पूर्ण
अटल DEVICE_ATTR_RO(palmsensor);

अटल पूर्णांक tpacpi_proxsensor_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	पूर्णांक palm_err, lap_err, err;

	palm_err = palmsensor_get(&has_palmsensor, &palm_state);
	lap_err = lapsensor_get(&has_lapsensor, &lap_state);
	/*
	 * If support isn't available (ENODEV) क्रम both devices then quit, but
	 * करोn't वापस an error.
	 */
	अगर ((palm_err == -ENODEV) && (lap_err == -ENODEV))
		वापस 0;
	/* Otherwise, अगर there was an error वापस it */
	अगर (palm_err && (palm_err != -ENODEV))
		वापस palm_err;
	अगर (lap_err && (lap_err != -ENODEV))
		वापस lap_err;

	अगर (has_palmsensor) अणु
		err = sysfs_create_file(&tpacpi_pdev->dev.kobj, &dev_attr_palmsensor.attr);
		अगर (err)
			वापस err;
	पूर्ण

	/* Check अगर we know the DYTC version, अगर we करोn't then get it */
	अगर (!dytc_version) अणु
		err = dytc_get_version();
		अगर (err)
			वापस err;
	पूर्ण
	/*
	 * Platक्रमms beक्रमe DYTC version 5 claim to have a lap sensor, but it करोesn't work, so we
	 * ignore them
	 */
	अगर (has_lapsensor && (dytc_version >= 5)) अणु
		err = sysfs_create_file(&tpacpi_pdev->dev.kobj, &dev_attr_dytc_lapmode.attr);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम proxsensor_निकास(व्योम)
अणु
	अगर (has_lapsensor)
		sysfs_हटाओ_file(&tpacpi_pdev->dev.kobj, &dev_attr_dytc_lapmode.attr);
	अगर (has_palmsensor)
		sysfs_हटाओ_file(&tpacpi_pdev->dev.kobj, &dev_attr_palmsensor.attr);
पूर्ण

अटल काष्ठा ibm_काष्ठा proxsensor_driver_data = अणु
	.name = "proximity-sensor",
	.निकास = proxsensor_निकास,
पूर्ण;

/*************************************************************************
 * DYTC Platक्रमm Profile पूर्णांकerface
 */

#घोषणा DYTC_CMD_SET          1 /* To enable/disable IC function mode */
#घोषणा DYTC_CMD_MMC_GET      8 /* To get current MMC function and mode */
#घोषणा DYTC_CMD_RESET    0x1ff /* To reset back to शेष */

#घोषणा DYTC_GET_FUNCTION_BIT 8  /* Bits  8-11 - function setting */
#घोषणा DYTC_GET_MODE_BIT     12 /* Bits 12-15 - mode setting */

#घोषणा DYTC_SET_FUNCTION_BIT 12 /* Bits 12-15 - function setting */
#घोषणा DYTC_SET_MODE_BIT     16 /* Bits 16-19 - mode setting */
#घोषणा DYTC_SET_VALID_BIT    20 /* Bit     20 - 1 = on, 0 = off */

#घोषणा DYTC_FUNCTION_STD     0  /* Function = 0, standard mode */
#घोषणा DYTC_FUNCTION_CQL     1  /* Function = 1, lap mode */
#घोषणा DYTC_FUNCTION_MMC     11 /* Function = 11, desk mode */

#घोषणा DYTC_MODE_PERFORM     2  /* High घातer mode aka perक्रमmance */
#घोषणा DYTC_MODE_LOWPOWER    3  /* Low घातer mode */
#घोषणा DYTC_MODE_BALANCE   0xF  /* Default mode aka balanced */
#घोषणा DYTC_MODE_MMC_BALANCE 0  /* Default mode from MMC_GET, aka balanced */

#घोषणा DYTC_ERR_MASK       0xF  /* Bits 0-3 in cmd result are the error result */
#घोषणा DYTC_ERR_SUCCESS      1  /* CMD completed successful */

#घोषणा DYTC_SET_COMMAND(function, mode, on) \
	(DYTC_CMD_SET | (function) << DYTC_SET_FUNCTION_BIT | \
	 (mode) << DYTC_SET_MODE_BIT | \
	 (on) << DYTC_SET_VALID_BIT)

#घोषणा DYTC_DISABLE_CQL DYTC_SET_COMMAND(DYTC_FUNCTION_CQL, DYTC_MODE_BALANCE, 0)

#घोषणा DYTC_ENABLE_CQL DYTC_SET_COMMAND(DYTC_FUNCTION_CQL, DYTC_MODE_BALANCE, 1)

अटल bool dytc_profile_available;
अटल क्रमागत platक्रमm_profile_option dytc_current_profile;
अटल atomic_t dytc_ignore_event = ATOMIC_INIT(0);
अटल DEFINE_MUTEX(dytc_mutex);
अटल bool dytc_mmc_get_available;

अटल पूर्णांक convert_dytc_to_profile(पूर्णांक dytcmode, क्रमागत platक्रमm_profile_option *profile)
अणु
	चयन (dytcmode) अणु
	हाल DYTC_MODE_LOWPOWER:
		*profile = PLATFORM_PROखाता_LOW_POWER;
		अवरोध;
	हाल DYTC_MODE_BALANCE:
	हाल DYTC_MODE_MMC_BALANCE:
		*profile =  PLATFORM_PROखाता_BALANCED;
		अवरोध;
	हाल DYTC_MODE_PERFORM:
		*profile =  PLATFORM_PROखाता_PERFORMANCE;
		अवरोध;
	शेष: /* Unknown mode */
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक convert_profile_to_dytc(क्रमागत platक्रमm_profile_option profile, पूर्णांक *perभ_शेषe)
अणु
	चयन (profile) अणु
	हाल PLATFORM_PROखाता_LOW_POWER:
		*perभ_शेषe = DYTC_MODE_LOWPOWER;
		अवरोध;
	हाल PLATFORM_PROखाता_BALANCED:
		*perभ_शेषe = DYTC_MODE_BALANCE;
		अवरोध;
	हाल PLATFORM_PROखाता_PERFORMANCE:
		*perभ_शेषe = DYTC_MODE_PERFORM;
		अवरोध;
	शेष: /* Unknown profile */
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * dytc_profile_get: Function to रेजिस्टर with platक्रमm_profile
 * handler. Returns current platक्रमm profile.
 */
अटल पूर्णांक dytc_profile_get(काष्ठा platक्रमm_profile_handler *pprof,
			    क्रमागत platक्रमm_profile_option *profile)
अणु
	*profile = dytc_current_profile;
	वापस 0;
पूर्ण

/*
 * Helper function - check अगर we are in CQL mode and अगर we are
 *  -  disable CQL,
 *  - run the command
 *  - enable CQL
 *  If not in CQL mode, just run the command
 */
अटल पूर्णांक dytc_cql_command(पूर्णांक command, पूर्णांक *output)
अणु
	पूर्णांक err, cmd_err, dummy;
	पूर्णांक cur_funcmode;

	/* Determine अगर we are in CQL mode. This alters the commands we करो */
	err = dytc_command(DYTC_CMD_GET, output);
	अगर (err)
		वापस err;

	cur_funcmode = (*output >> DYTC_GET_FUNCTION_BIT) & 0xF;
	/* Check अगर we're OK to वापस immediately */
	अगर ((command == DYTC_CMD_GET) && (cur_funcmode != DYTC_FUNCTION_CQL))
		वापस 0;

	अगर (cur_funcmode == DYTC_FUNCTION_CQL) अणु
		atomic_inc(&dytc_ignore_event);
		err = dytc_command(DYTC_DISABLE_CQL, &dummy);
		अगर (err)
			वापस err;
	पूर्ण

	cmd_err = dytc_command(command,	output);
	/* Check वापस condition after we've restored CQL state */

	अगर (cur_funcmode == DYTC_FUNCTION_CQL) अणु
		err = dytc_command(DYTC_ENABLE_CQL, &dummy);
		अगर (err)
			वापस err;
	पूर्ण
	वापस cmd_err;
पूर्ण

/*
 * dytc_profile_set: Function to रेजिस्टर with platक्रमm_profile
 * handler. Sets current platक्रमm profile.
 */
अटल पूर्णांक dytc_profile_set(काष्ठा platक्रमm_profile_handler *pprof,
			    क्रमागत platक्रमm_profile_option profile)
अणु
	पूर्णांक output;
	पूर्णांक err;

	अगर (!dytc_profile_available)
		वापस -ENODEV;

	err = mutex_lock_पूर्णांकerruptible(&dytc_mutex);
	अगर (err)
		वापस err;

	अगर (profile == PLATFORM_PROखाता_BALANCED) अणु
		/*
		 * To get back to balanced mode we need to issue a reset command.
		 * Note we still need to disable CQL mode beक्रमe hand and re-enable
		 * it afterwards, otherwise dytc_lapmode माला_लो reset to 0 and stays
		 * stuck at 0 क्रम aprox. 30 minutes.
		 */
		err = dytc_cql_command(DYTC_CMD_RESET, &output);
		अगर (err)
			जाओ unlock;
	पूर्ण अन्यथा अणु
		पूर्णांक perभ_शेषe;

		err = convert_profile_to_dytc(profile, &perभ_शेषe);
		अगर (err)
			जाओ unlock;

		/* Determine अगर we are in CQL mode. This alters the commands we करो */
		err = dytc_cql_command(DYTC_SET_COMMAND(DYTC_FUNCTION_MMC, perभ_शेषe, 1), &output);
		अगर (err)
			जाओ unlock;
	पूर्ण
	/* Success - update current profile */
	dytc_current_profile = profile;
unlock:
	mutex_unlock(&dytc_mutex);
	वापस err;
पूर्ण

अटल व्योम dytc_profile_refresh(व्योम)
अणु
	क्रमागत platक्रमm_profile_option profile;
	पूर्णांक output, err;
	पूर्णांक perभ_शेषe;

	mutex_lock(&dytc_mutex);
	अगर (dytc_mmc_get_available)
		err = dytc_command(DYTC_CMD_MMC_GET, &output);
	अन्यथा
		err = dytc_cql_command(DYTC_CMD_GET, &output);
	mutex_unlock(&dytc_mutex);
	अगर (err)
		वापस;

	perभ_शेषe = (output >> DYTC_GET_MODE_BIT) & 0xF;
	convert_dytc_to_profile(perभ_शेषe, &profile);
	अगर (profile != dytc_current_profile) अणु
		dytc_current_profile = profile;
		platक्रमm_profile_notअगरy();
	पूर्ण
पूर्ण

अटल काष्ठा platक्रमm_profile_handler dytc_profile = अणु
	.profile_get = dytc_profile_get,
	.profile_set = dytc_profile_set,
पूर्ण;

अटल पूर्णांक tpacpi_dytc_profile_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	पूर्णांक err, output;

	/* Setup supported modes */
	set_bit(PLATFORM_PROखाता_LOW_POWER, dytc_profile.choices);
	set_bit(PLATFORM_PROखाता_BALANCED, dytc_profile.choices);
	set_bit(PLATFORM_PROखाता_PERFORMANCE, dytc_profile.choices);

	dytc_profile_available = false;
	err = dytc_command(DYTC_CMD_QUERY, &output);
	/*
	 * If support isn't available (ENODEV) then don't वापस an error
	 * and करोn't create the sysfs group
	 */
	अगर (err == -ENODEV)
		वापस 0;
	/* For all other errors we can flag the failure */
	अगर (err)
		वापस err;

	/* Check अगर we know the DYTC version, अगर we करोn't then get it */
	अगर (!dytc_version) अणु
		err = dytc_get_version();
		अगर (err)
			वापस err;
	पूर्ण
	/* Check DYTC is enabled and supports mode setting */
	अगर (dytc_version >= 5) अणु
		dbg_prपूर्णांकk(TPACPI_DBG_INIT,
				"DYTC version %d: thermal mode available\n", dytc_version);
		/*
		 * Check अगर MMC_GET functionality available
		 * Version > 6 and वापस success from MMC_GET command
		 */
		dytc_mmc_get_available = false;
		अगर (dytc_version >= 6) अणु
			err = dytc_command(DYTC_CMD_MMC_GET, &output);
			अगर (!err && ((output & DYTC_ERR_MASK) == DYTC_ERR_SUCCESS))
				dytc_mmc_get_available = true;
		पूर्ण
		/* Create platक्रमm_profile काष्ठाure and रेजिस्टर */
		err = platक्रमm_profile_रेजिस्टर(&dytc_profile);
		/*
		 * If क्रम some reason platक्रमm_profiles aren't enabled
		 * करोn't quit terminally.
		 */
		अगर (err)
			वापस 0;

		dytc_profile_available = true;
		/* Ensure initial values are correct */
		dytc_profile_refresh();
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dytc_profile_निकास(व्योम)
अणु
	अगर (dytc_profile_available) अणु
		dytc_profile_available = false;
		platक्रमm_profile_हटाओ();
	पूर्ण
पूर्ण

अटल काष्ठा ibm_काष्ठा  dytc_profile_driver_data = अणु
	.name = "dytc-profile",
	.निकास = dytc_profile_निकास,
पूर्ण;

/*************************************************************************
 * Keyboard language पूर्णांकerface
 */

काष्ठा keyboard_lang_data अणु
	स्थिर अक्षर *lang_str;
	पूर्णांक lang_code;
पूर्ण;

अटल स्थिर काष्ठा keyboard_lang_data keyboard_lang_data[] = अणु
	अणु"be", 0x080cपूर्ण,
	अणु"cz", 0x0405पूर्ण,
	अणु"da", 0x0406पूर्ण,
	अणु"de", 0x0c07पूर्ण,
	अणु"en", 0x0000पूर्ण,
	अणु"es", 0x2c0aपूर्ण,
	अणु"et", 0x0425पूर्ण,
	अणु"fr", 0x040cपूर्ण,
	अणु"fr-ch", 0x100cपूर्ण,
	अणु"hu", 0x040eपूर्ण,
	अणु"it", 0x0410पूर्ण,
	अणु"jp", 0x0411पूर्ण,
	अणु"nl", 0x0413पूर्ण,
	अणु"nn", 0x0414पूर्ण,
	अणु"pl", 0x0415पूर्ण,
	अणु"pt", 0x0816पूर्ण,
	अणु"sl", 0x041bपूर्ण,
	अणु"sv", 0x081dपूर्ण,
	अणु"tr", 0x041fपूर्ण,
पूर्ण;

अटल पूर्णांक set_keyboard_lang_command(पूर्णांक command)
अणु
	acpi_handle sskl_handle;
	पूर्णांक output;

	अगर (ACPI_FAILURE(acpi_get_handle(hkey_handle, "SSKL", &sskl_handle))) अणु
		/* Platक्रमm करोesn't support SSKL */
		वापस -ENODEV;
	पूर्ण

	अगर (!acpi_evalf(sskl_handle, &output, शून्य, "dd", command))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक get_keyboard_lang(पूर्णांक *output)
अणु
	acpi_handle gskl_handle;
	पूर्णांक kbd_lang;

	अगर (ACPI_FAILURE(acpi_get_handle(hkey_handle, "GSKL", &gskl_handle))) अणु
		/* Platक्रमm करोesn't support GSKL */
		वापस -ENODEV;
	पूर्ण

	अगर (!acpi_evalf(gskl_handle, &kbd_lang, शून्य, "dd", 0x02000000))
		वापस -EIO;

	/*
	 * METHOD_ERR माला_लो वापसed on devices where there are no special (e.g. '=',
	 * '(' and ')') keys which use layout dependent key-press emulation.
	 */
	अगर (kbd_lang & METHOD_ERR)
		वापस -ENODEV;

	*output = kbd_lang;

	वापस 0;
पूर्ण

/* sysfs keyboard language entry */
अटल sमाप_प्रकार keyboard_lang_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	पूर्णांक output, err, i, len = 0;

	err = get_keyboard_lang(&output);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < ARRAY_SIZE(keyboard_lang_data); i++) अणु
		अगर (i)
			len += sysfs_emit_at(buf, len, "%s", " ");

		अगर (output == keyboard_lang_data[i].lang_code) अणु
			len += sysfs_emit_at(buf, len, "[%s]", keyboard_lang_data[i].lang_str);
		पूर्ण अन्यथा अणु
			len += sysfs_emit_at(buf, len, "%s", keyboard_lang_data[i].lang_str);
		पूर्ण
	पूर्ण
	len += sysfs_emit_at(buf, len, "\n");

	वापस len;
पूर्ण

अटल sमाप_प्रकार keyboard_lang_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err, i;
	bool lang_found = false;
	पूर्णांक lang_code = 0;

	क्रम (i = 0; i < ARRAY_SIZE(keyboard_lang_data); i++) अणु
		अगर (sysfs_streq(buf, keyboard_lang_data[i].lang_str)) अणु
			lang_code = keyboard_lang_data[i].lang_code;
			lang_found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (lang_found) अणु
		lang_code = lang_code | 1 << 24;

		/* Set language code */
		err = set_keyboard_lang_command(lang_code);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		dev_err(&tpacpi_pdev->dev, "Unknown Keyboard language. Ignoring\n");
		वापस -EINVAL;
	पूर्ण

	tpacpi_disबंद_usertask(attr->attr.name,
			"keyboard language is set to  %s\n", buf);

	sysfs_notअगरy(&tpacpi_pdev->dev.kobj, शून्य, "keyboard_lang");

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(keyboard_lang);

अटल काष्ठा attribute *kbdlang_attributes[] = अणु
	&dev_attr_keyboard_lang.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group kbdlang_attr_group = अणु
	.attrs = kbdlang_attributes,
पूर्ण;

अटल पूर्णांक tpacpi_kbdlang_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	पूर्णांक err, output;

	err = get_keyboard_lang(&output);
	/*
	 * If support isn't available (ENODEV) then don't वापस an error
	 * just करोn't create the sysfs group.
	 */
	अगर (err == -ENODEV)
		वापस 0;

	अगर (err)
		वापस err;

	/* Platक्रमm supports this feature - create the sysfs file */
	वापस sysfs_create_group(&tpacpi_pdev->dev.kobj, &kbdlang_attr_group);
पूर्ण

अटल व्योम kbdlang_निकास(व्योम)
अणु
	sysfs_हटाओ_group(&tpacpi_pdev->dev.kobj, &kbdlang_attr_group);
पूर्ण

अटल काष्ठा ibm_काष्ठा kbdlang_driver_data = अणु
	.name = "kbdlang",
	.निकास = kbdlang_निकास,
पूर्ण;

/*************************************************************************
 * DPRC(Dynamic Power Reduction Control) subdriver, क्रम the Lenovo WWAN
 * and WLAN feature.
 */
#घोषणा DPRC_GET_WWAN_ANTENNA_TYPE      0x40000
#घोषणा DPRC_WWAN_ANTENNA_TYPE_A_BIT    BIT(4)
#घोषणा DPRC_WWAN_ANTENNA_TYPE_B_BIT    BIT(8)
अटल bool has_antennatype;
अटल पूर्णांक wwan_antennatype;

अटल पूर्णांक dprc_command(पूर्णांक command, पूर्णांक *output)
अणु
	acpi_handle dprc_handle;

	अगर (ACPI_FAILURE(acpi_get_handle(hkey_handle, "DPRC", &dprc_handle))) अणु
		/* Platक्रमm करोesn't support DPRC */
		वापस -ENODEV;
	पूर्ण

	अगर (!acpi_evalf(dprc_handle, output, शून्य, "dd", command))
		वापस -EIO;

	/*
	 * METHOD_ERR माला_लो वापसed on devices where few commands are not supported
	 * क्रम example command to get WWAN Antenna type command is not supported on
	 * some devices.
	 */
	अगर (*output & METHOD_ERR)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक get_wwan_antenna(पूर्णांक *wwan_antennatype)
अणु
	पूर्णांक output, err;

	/* Get current Antenna type */
	err = dprc_command(DPRC_GET_WWAN_ANTENNA_TYPE, &output);
	अगर (err)
		वापस err;

	अगर (output & DPRC_WWAN_ANTENNA_TYPE_A_BIT)
		*wwan_antennatype = 1;
	अन्यथा अगर (output & DPRC_WWAN_ANTENNA_TYPE_B_BIT)
		*wwan_antennatype = 2;
	अन्यथा
		वापस -ENODEV;

	वापस 0;
पूर्ण

/* sysfs wwan antenna type entry */
अटल sमाप_प्रकार wwan_antenna_type_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	चयन (wwan_antennatype) अणु
	हाल 1:
		वापस sysfs_emit(buf, "type a\n");
	हाल 2:
		वापस sysfs_emit(buf, "type b\n");
	शेष:
		वापस -ENODATA;
	पूर्ण
पूर्ण
अटल DEVICE_ATTR_RO(wwan_antenna_type);

अटल पूर्णांक tpacpi_dprc_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	पूर्णांक wwanantenna_err, err;

	wwanantenna_err = get_wwan_antenna(&wwan_antennatype);
	/*
	 * If support isn't available (ENODEV) then quit, but don't
	 * वापस an error.
	 */
	अगर (wwanantenna_err == -ENODEV)
		वापस 0;

	/* अगर there was an error वापस it */
	अगर (wwanantenna_err && (wwanantenna_err != -ENODEV))
		वापस wwanantenna_err;
	अन्यथा अगर (!wwanantenna_err)
		has_antennatype = true;

	अगर (has_antennatype) अणु
		err = sysfs_create_file(&tpacpi_pdev->dev.kobj, &dev_attr_wwan_antenna_type.attr);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dprc_निकास(व्योम)
अणु
	अगर (has_antennatype)
		sysfs_हटाओ_file(&tpacpi_pdev->dev.kobj, &dev_attr_wwan_antenna_type.attr);
पूर्ण

अटल काष्ठा ibm_काष्ठा dprc_driver_data = अणु
	.name = "dprc",
	.निकास = dprc_निकास,
पूर्ण;

/****************************************************************************
 ****************************************************************************
 *
 * Infraकाष्ठाure
 *
 ****************************************************************************
 ****************************************************************************/

/*
 * HKEY event callout क्रम other subdrivers go here
 * (yes, it is ugly, but it is quick, safe, and माला_लो the job करोne
 */
अटल व्योम tpacpi_driver_event(स्थिर अचिन्हित पूर्णांक hkey_event)
अणु
	अगर (ibm_backlight_device) अणु
		चयन (hkey_event) अणु
		हाल TP_HKEY_EV_BRGHT_UP:
		हाल TP_HKEY_EV_BRGHT_DOWN:
			tpacpi_brightness_notअगरy_change();
		पूर्ण
	पूर्ण
	अगर (alsa_card) अणु
		चयन (hkey_event) अणु
		हाल TP_HKEY_EV_VOL_UP:
		हाल TP_HKEY_EV_VOL_DOWN:
		हाल TP_HKEY_EV_VOL_MUTE:
			volume_alsa_notअगरy_change();
		पूर्ण
	पूर्ण
	अगर (tp_features.kbdlight && hkey_event == TP_HKEY_EV_KBD_LIGHT) अणु
		क्रमागत led_brightness brightness;

		mutex_lock(&kbdlight_mutex);

		/*
		 * Check the brightness actually changed, setting the brightness
		 * through kbdlight_set_level() also triggers this event.
		 */
		brightness = kbdlight_sysfs_get(शून्य);
		अगर (kbdlight_brightness != brightness) अणु
			kbdlight_brightness = brightness;
			led_classdev_notअगरy_brightness_hw_changed(
				&tpacpi_led_kbdlight.led_classdev, brightness);
		पूर्ण

		mutex_unlock(&kbdlight_mutex);
	पूर्ण

	अगर (hkey_event == TP_HKEY_EV_THM_CSM_COMPLETED) अणु
		lapsensor_refresh();
		/* If we are alपढ़ोy accessing DYTC then skip dytc update */
		अगर (!atomic_add_unless(&dytc_ignore_event, -1, 0))
			dytc_profile_refresh();
	पूर्ण
पूर्ण

अटल व्योम hotkey_driver_event(स्थिर अचिन्हित पूर्णांक scancode)
अणु
	tpacpi_driver_event(TP_HKEY_EV_HOTKEY_BASE + scancode);
पूर्ण

/* --------------------------------------------------------------------- */

/* /proc support */
अटल काष्ठा proc_dir_entry *proc_dir;

/*
 * Module and infraकाष्ठाure proble, init and निकास handling
 */

अटल bool क्रमce_load;

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUG
अटल स्थिर अक्षर * __init str_supported(पूर्णांक is_supported)
अणु
	अटल अक्षर text_unsupported[] __initdata = "not supported";

	वापस (is_supported) ? &text_unsupported[4] : &text_unsupported[0];
पूर्ण
#पूर्ण_अगर /* CONFIG_THINKPAD_ACPI_DEBUG */

अटल व्योम ibm_निकास(काष्ठा ibm_काष्ठा *ibm)
अणु
	dbg_prपूर्णांकk(TPACPI_DBG_EXIT, "removing %s\n", ibm->name);

	list_del_init(&ibm->all_drivers);

	अगर (ibm->flags.acpi_notअगरy_installed) अणु
		dbg_prपूर्णांकk(TPACPI_DBG_EXIT,
			"%s: acpi_remove_notify_handler\n", ibm->name);
		BUG_ON(!ibm->acpi);
		acpi_हटाओ_notअगरy_handler(*ibm->acpi->handle,
					   ibm->acpi->type,
					   dispatch_acpi_notअगरy);
		ibm->flags.acpi_notअगरy_installed = 0;
	पूर्ण

	अगर (ibm->flags.proc_created) अणु
		dbg_prपूर्णांकk(TPACPI_DBG_EXIT,
			"%s: remove_proc_entry\n", ibm->name);
		हटाओ_proc_entry(ibm->name, proc_dir);
		ibm->flags.proc_created = 0;
	पूर्ण

	अगर (ibm->flags.acpi_driver_रेजिस्टरed) अणु
		dbg_prपूर्णांकk(TPACPI_DBG_EXIT,
			"%s: acpi_bus_unregister_driver\n", ibm->name);
		BUG_ON(!ibm->acpi);
		acpi_bus_unरेजिस्टर_driver(ibm->acpi->driver);
		kमुक्त(ibm->acpi->driver);
		ibm->acpi->driver = शून्य;
		ibm->flags.acpi_driver_रेजिस्टरed = 0;
	पूर्ण

	अगर (ibm->flags.init_called && ibm->निकास) अणु
		ibm->निकास();
		ibm->flags.init_called = 0;
	पूर्ण

	dbg_prपूर्णांकk(TPACPI_DBG_INIT, "finished removing %s\n", ibm->name);
पूर्ण

अटल पूर्णांक __init ibm_init(काष्ठा ibm_init_काष्ठा *iibm)
अणु
	पूर्णांक ret;
	काष्ठा ibm_काष्ठा *ibm = iibm->data;
	काष्ठा proc_dir_entry *entry;

	BUG_ON(ibm == शून्य);

	INIT_LIST_HEAD(&ibm->all_drivers);

	अगर (ibm->flags.experimental && !experimental)
		वापस 0;

	dbg_prपूर्णांकk(TPACPI_DBG_INIT,
		"probing for %s\n", ibm->name);

	अगर (iibm->init) अणु
		ret = iibm->init(iibm);
		अगर (ret > 0)
			वापस 0;	/* probe failed */
		अगर (ret)
			वापस ret;

		ibm->flags.init_called = 1;
	पूर्ण

	अगर (ibm->acpi) अणु
		अगर (ibm->acpi->hid) अणु
			ret = रेजिस्टर_tpacpi_subdriver(ibm);
			अगर (ret)
				जाओ err_out;
		पूर्ण

		अगर (ibm->acpi->notअगरy) अणु
			ret = setup_acpi_notअगरy(ibm);
			अगर (ret == -ENODEV) अणु
				pr_notice("disabling subdriver %s\n",
					  ibm->name);
				ret = 0;
				जाओ err_out;
			पूर्ण
			अगर (ret < 0)
				जाओ err_out;
		पूर्ण
	पूर्ण

	dbg_prपूर्णांकk(TPACPI_DBG_INIT,
		"%s installed\n", ibm->name);

	अगर (ibm->पढ़ो) अणु
		umode_t mode = iibm->base_procfs_mode;

		अगर (!mode)
			mode = S_IRUGO;
		अगर (ibm->ग_लिखो)
			mode |= S_IWUSR;
		entry = proc_create_data(ibm->name, mode, proc_dir,
					 &dispatch_proc_ops, ibm);
		अगर (!entry) अणु
			pr_err("unable to create proc entry %s\n", ibm->name);
			ret = -ENODEV;
			जाओ err_out;
		पूर्ण
		ibm->flags.proc_created = 1;
	पूर्ण

	list_add_tail(&ibm->all_drivers, &tpacpi_all_drivers);

	वापस 0;

err_out:
	dbg_prपूर्णांकk(TPACPI_DBG_INIT,
		"%s: at error exit path with result %d\n",
		ibm->name, ret);

	ibm_निकास(ibm);
	वापस (ret < 0) ? ret : 0;
पूर्ण

/* Probing */

अटल अक्षर __init tpacpi_parse_fw_id(स्थिर अक्षर * स्थिर s,
				      u32 *model, u16 *release)
अणु
	पूर्णांक i;

	अगर (!s || म_माप(s) < 8)
		जाओ invalid;

	क्रम (i = 0; i < 8; i++)
		अगर (!((s[i] >= '0' && s[i] <= '9') ||
		      (s[i] >= 'A' && s[i] <= 'Z')))
			जाओ invalid;

	/*
	 * Most models: xxyTkkWW (#.##c)
	 * Ancient 570/600 and -SL lacks (#.##c)
	 */
	अगर (s[3] == 'T' || s[3] == 'N') अणु
		*model = TPID(s[0], s[1]);
		*release = TPVER(s[4], s[5]);
		वापस s[2];

	/* New models: xxxyTkkW (#.##c); T550 and some others */
	पूर्ण अन्यथा अगर (s[4] == 'T' || s[4] == 'N') अणु
		*model = TPID3(s[0], s[1], s[2]);
		*release = TPVER(s[5], s[6]);
		वापस s[3];
	पूर्ण

invalid:
	वापस '\0';
पूर्ण

अटल व्योम find_new_ec_fwstr(स्थिर काष्ठा dmi_header *dm, व्योम *निजी)
अणु
	अक्षर *ec_fw_string = (अक्षर *) निजी;
	स्थिर अक्षर *dmi_data = (स्थिर अक्षर *)dm;
	/*
	 * ThinkPad Embedded Controller Program Table on newer models
	 *
	 * Offset |  Name                | Width  | Description
	 * ----------------------------------------------------
	 *  0x00  | Type                 | BYTE   | 0x8C
	 *  0x01  | Length               | BYTE   |
	 *  0x02  | Handle               | WORD   | Varies
	 *  0x04  | Signature            | BYTEx6 | ASCII क्रम "LENOVO"
	 *  0x0A  | OEM काष्ठा offset    | BYTE   | 0x0B
	 *  0x0B  | OEM काष्ठा number    | BYTE   | 0x07, क्रम this काष्ठाure
	 *  0x0C  | OEM काष्ठा revision  | BYTE   | 0x01, क्रम this क्रमmat
	 *  0x0D  | ECP version ID       | STR ID |
	 *  0x0E  | ECP release date     | STR ID |
	 */

	/* Return अगर data काष्ठाure not match */
	अगर (dm->type != 140 || dm->length < 0x0F ||
	स_भेद(dmi_data + 4, "LENOVO", 6) != 0 ||
	dmi_data[0x0A] != 0x0B || dmi_data[0x0B] != 0x07 ||
	dmi_data[0x0C] != 0x01)
		वापस;

	/* fwstr is the first 8byte string  */
	म_नकलन(ec_fw_string, dmi_data + 0x0F, 8);
पूर्ण

/* वापसs 0 - probe ok, or < 0 - probe error.
 * Probe ok करोesn't mean thinkpad found.
 * On error, kमुक्त() cleanup on tp->* is not perक्रमmed, caller must करो it */
अटल पूर्णांक __must_check __init get_thinkpad_model_data(
						काष्ठा thinkpad_id_data *tp)
अणु
	स्थिर काष्ठा dmi_device *dev = शून्य;
	अक्षर ec_fw_string[18] = अणु0पूर्ण;
	अक्षर स्थिर *s;
	अक्षर t;

	अगर (!tp)
		वापस -EINVAL;

	स_रखो(tp, 0, माप(*tp));

	अगर (dmi_name_in_venकरोrs("IBM"))
		tp->venकरोr = PCI_VENDOR_ID_IBM;
	अन्यथा अगर (dmi_name_in_venकरोrs("LENOVO"))
		tp->venकरोr = PCI_VENDOR_ID_LENOVO;
	अन्यथा
		वापस 0;

	s = dmi_get_प्रणाली_info(DMI_BIOS_VERSION);
	tp->bios_version_str = kstrdup(s, GFP_KERNEL);
	अगर (s && !tp->bios_version_str)
		वापस -ENOMEM;

	/* Really ancient ThinkPad 240X will fail this, which is fine */
	t = tpacpi_parse_fw_id(tp->bios_version_str,
			       &tp->bios_model, &tp->bios_release);
	अगर (t != 'E' && t != 'C')
		वापस 0;

	/*
	 * ThinkPad T23 or newer, A31 or newer, R50e or newer,
	 * X32 or newer, all Z series;  Some models must have an
	 * up-to-date BIOS or they will not be detected.
	 *
	 * See https://thinkwiki.org/wiki/List_of_DMI_IDs
	 */
	जबतक ((dev = dmi_find_device(DMI_DEV_TYPE_OEM_STRING, शून्य, dev))) अणु
		अगर (माला_पूछो(dev->name,
			   "IBM ThinkPad Embedded Controller -[%17c",
			   ec_fw_string) == 1) अणु
			ec_fw_string[माप(ec_fw_string) - 1] = 0;
			ec_fw_string[म_खोज(ec_fw_string, " ]")] = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Newer ThinkPads have dअगरferent EC program info table */
	अगर (!ec_fw_string[0])
		dmi_walk(find_new_ec_fwstr, &ec_fw_string);

	अगर (ec_fw_string[0]) अणु
		tp->ec_version_str = kstrdup(ec_fw_string, GFP_KERNEL);
		अगर (!tp->ec_version_str)
			वापस -ENOMEM;

		t = tpacpi_parse_fw_id(ec_fw_string,
			 &tp->ec_model, &tp->ec_release);
		अगर (t != 'H') अणु
			pr_notice("ThinkPad firmware release %s doesn't match the known patterns\n",
				  ec_fw_string);
			pr_notice("please report this to %s\n", TPACPI_MAIL);
		पूर्ण
	पूर्ण

	s = dmi_get_प्रणाली_info(DMI_PRODUCT_VERSION);
	अगर (s && !(strnहालcmp(s, "ThinkPad", 8) && strnहालcmp(s, "Lenovo", 6))) अणु
		tp->model_str = kstrdup(s, GFP_KERNEL);
		अगर (!tp->model_str)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		s = dmi_get_प्रणाली_info(DMI_BIOS_VENDOR);
		अगर (s && !(strnहालcmp(s, "Lenovo", 6))) अणु
			tp->model_str = kstrdup(s, GFP_KERNEL);
			अगर (!tp->model_str)
				वापस -ENOMEM;
		पूर्ण
	पूर्ण

	s = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);
	tp->nummodel_str = kstrdup(s, GFP_KERNEL);
	अगर (s && !tp->nummodel_str)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक __init probe_क्रम_thinkpad(व्योम)
अणु
	पूर्णांक is_thinkpad;

	अगर (acpi_disabled)
		वापस -ENODEV;

	/* It would be dangerous to run the driver in this हाल */
	अगर (!tpacpi_is_ibm() && !tpacpi_is_lenovo())
		वापस -ENODEV;

	/*
	 * Non-ancient models have better DMI tagging, but very old models
	 * करोn't.  tpacpi_is_fw_known() is a cheat to help in that हाल.
	 */
	is_thinkpad = (thinkpad_id.model_str != शून्य) ||
		      (thinkpad_id.ec_model != 0) ||
		      tpacpi_is_fw_known();

	/* The EC handler is required */
	tpacpi_acpi_handle_locate("ec", TPACPI_ACPI_EC_HID, &ec_handle);
	अगर (!ec_handle) अणु
		अगर (is_thinkpad)
			pr_err("Not yet supported ThinkPad detected!\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!is_thinkpad && !क्रमce_load)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम __init thinkpad_acpi_init_banner(व्योम)
अणु
	pr_info("%s v%s\n", TPACPI_DESC, TPACPI_VERSION);
	pr_info("%s\n", TPACPI_URL);

	pr_info("ThinkPad BIOS %s, EC %s\n",
		(thinkpad_id.bios_version_str) ?
			thinkpad_id.bios_version_str : "unknown",
		(thinkpad_id.ec_version_str) ?
			thinkpad_id.ec_version_str : "unknown");

	BUG_ON(!thinkpad_id.venकरोr);

	अगर (thinkpad_id.model_str)
		pr_info("%s %s, model %s\n",
			(thinkpad_id.venकरोr == PCI_VENDOR_ID_IBM) ?
				"IBM" : ((thinkpad_id.venकरोr ==
						PCI_VENDOR_ID_LENOVO) ?
					"Lenovo" : "Unknown vendor"),
			thinkpad_id.model_str,
			(thinkpad_id.nummodel_str) ?
				thinkpad_id.nummodel_str : "unknown");
पूर्ण

/* Module init, निकास, parameters */

अटल काष्ठा ibm_init_काष्ठा ibms_init[] __initdata = अणु
	अणु
		.data = &thinkpad_acpi_driver_data,
	पूर्ण,
	अणु
		.init = hotkey_init,
		.data = &hotkey_driver_data,
	पूर्ण,
	अणु
		.init = bluetooth_init,
		.data = &bluetooth_driver_data,
	पूर्ण,
	अणु
		.init = wan_init,
		.data = &wan_driver_data,
	पूर्ण,
	अणु
		.init = uwb_init,
		.data = &uwb_driver_data,
	पूर्ण,
#अगर_घोषित CONFIG_THINKPAD_ACPI_VIDEO
	अणु
		.init = video_init,
		.base_procfs_mode = S_IRUSR,
		.data = &video_driver_data,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.init = kbdlight_init,
		.data = &kbdlight_driver_data,
	पूर्ण,
	अणु
		.init = light_init,
		.data = &light_driver_data,
	पूर्ण,
	अणु
		.init = cmos_init,
		.data = &cmos_driver_data,
	पूर्ण,
	अणु
		.init = led_init,
		.data = &led_driver_data,
	पूर्ण,
	अणु
		.init = beep_init,
		.data = &beep_driver_data,
	पूर्ण,
	अणु
		.init = thermal_init,
		.data = &thermal_driver_data,
	पूर्ण,
	अणु
		.init = brightness_init,
		.data = &brightness_driver_data,
	पूर्ण,
	अणु
		.init = volume_init,
		.data = &volume_driver_data,
	पूर्ण,
	अणु
		.init = fan_init,
		.data = &fan_driver_data,
	पूर्ण,
	अणु
		.init = mute_led_init,
		.data = &mute_led_driver_data,
	पूर्ण,
	अणु
		.init = tpacpi_battery_init,
		.data = &battery_driver_data,
	पूर्ण,
	अणु
		.init = tpacpi_lcdshaकरोw_init,
		.data = &lcdshaकरोw_driver_data,
	पूर्ण,
	अणु
		.init = tpacpi_proxsensor_init,
		.data = &proxsensor_driver_data,
	पूर्ण,
	अणु
		.init = tpacpi_dytc_profile_init,
		.data = &dytc_profile_driver_data,
	पूर्ण,
	अणु
		.init = tpacpi_kbdlang_init,
		.data = &kbdlang_driver_data,
	पूर्ण,
	अणु
		.init = tpacpi_dprc_init,
		.data = &dprc_driver_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init set_ibm_param(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ibm_काष्ठा *ibm;

	अगर (!kp || !kp->name || !val)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(ibms_init); i++) अणु
		ibm = ibms_init[i].data;
		WARN_ON(ibm == शून्य);

		अगर (!ibm || !ibm->name)
			जारी;

		अगर (म_भेद(ibm->name, kp->name) == 0 && ibm->ग_लिखो) अणु
			अगर (म_माप(val) > माप(ibms_init[i].param) - 1)
				वापस -ENOSPC;
			म_नकल(ibms_init[i].param, val);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

module_param(experimental, पूर्णांक, 0444);
MODULE_PARM_DESC(experimental,
		 "Enables experimental features when non-zero");

module_param_named(debug, dbg_level, uपूर्णांक, 0);
MODULE_PARM_DESC(debug, "Sets debug level bit-mask");

module_param(क्रमce_load, bool, 0444);
MODULE_PARM_DESC(क्रमce_load,
		 "Attempts to load the driver even on a mis-identified ThinkPad when true");

module_param_named(fan_control, fan_control_allowed, bool, 0444);
MODULE_PARM_DESC(fan_control,
		 "Enables setting fan parameters features when true");

module_param_named(brightness_mode, brightness_mode, uपूर्णांक, 0444);
MODULE_PARM_DESC(brightness_mode,
		 "Selects brightness control strategy: 0=auto, 1=EC, 2=UCMS, 3=EC+NVRAM");

module_param(brightness_enable, uपूर्णांक, 0444);
MODULE_PARM_DESC(brightness_enable,
		 "Enables backlight control when 1, disables when 0");

#अगर_घोषित CONFIG_THINKPAD_ACPI_ALSA_SUPPORT
module_param_named(volume_mode, volume_mode, uपूर्णांक, 0444);
MODULE_PARM_DESC(volume_mode,
		 "Selects volume control strategy: 0=auto, 1=EC, 2=N/A, 3=EC+NVRAM");

module_param_named(volume_capabilities, volume_capabilities, uपूर्णांक, 0444);
MODULE_PARM_DESC(volume_capabilities,
		 "Selects the mixer capabilities: 0=auto, 1=volume and mute, 2=mute only");

module_param_named(volume_control, volume_control_allowed, bool, 0444);
MODULE_PARM_DESC(volume_control,
		 "Enables software override for the console audio control when true");

module_param_named(software_mute, software_mute_requested, bool, 0444);
MODULE_PARM_DESC(software_mute,
		 "Request full software mute control");

/* ALSA module API parameters */
module_param_named(index, alsa_index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "ALSA index for the ACPI EC Mixer");
module_param_named(id, alsa_id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ALSA id for the ACPI EC Mixer");
module_param_named(enable, alsa_enable, bool, 0444);
MODULE_PARM_DESC(enable, "Enable the ALSA interface for the ACPI EC Mixer");
#पूर्ण_अगर /* CONFIG_THINKPAD_ACPI_ALSA_SUPPORT */

/* The module parameter can't be read back, that's why 0 is used here */
#घोषणा TPACPI_PARAM(feature) \
	module_param_call(feature, set_ibm_param, शून्य, शून्य, 0); \
	MODULE_PARM_DESC(feature, "Simulates thinkpad-acpi procfs command at module load, see documentation")

TPACPI_PARAM(hotkey);
TPACPI_PARAM(bluetooth);
TPACPI_PARAM(video);
TPACPI_PARAM(light);
TPACPI_PARAM(cmos);
TPACPI_PARAM(led);
TPACPI_PARAM(beep);
TPACPI_PARAM(brightness);
TPACPI_PARAM(volume);
TPACPI_PARAM(fan);

#अगर_घोषित CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
module_param(dbg_wlswemul, uपूर्णांक, 0444);
MODULE_PARM_DESC(dbg_wlswemul, "Enables WLSW emulation");
module_param_named(wlsw_state, tpacpi_wlsw_emulstate, bool, 0);
MODULE_PARM_DESC(wlsw_state,
		 "Initial state of the emulated WLSW switch");

module_param(dbg_bluetoothemul, uपूर्णांक, 0444);
MODULE_PARM_DESC(dbg_bluetoothemul, "Enables bluetooth switch emulation");
module_param_named(bluetooth_state, tpacpi_bluetooth_emulstate, bool, 0);
MODULE_PARM_DESC(bluetooth_state,
		 "Initial state of the emulated bluetooth switch");

module_param(dbg_wwanemul, uपूर्णांक, 0444);
MODULE_PARM_DESC(dbg_wwanemul, "Enables WWAN switch emulation");
module_param_named(wwan_state, tpacpi_wwan_emulstate, bool, 0);
MODULE_PARM_DESC(wwan_state,
		 "Initial state of the emulated WWAN switch");

module_param(dbg_uwbemul, uपूर्णांक, 0444);
MODULE_PARM_DESC(dbg_uwbemul, "Enables UWB switch emulation");
module_param_named(uwb_state, tpacpi_uwb_emulstate, bool, 0);
MODULE_PARM_DESC(uwb_state,
		 "Initial state of the emulated UWB switch");
#पूर्ण_अगर

अटल व्योम thinkpad_acpi_module_निकास(व्योम)
अणु
	काष्ठा ibm_काष्ठा *ibm, *iपंचांगp;

	tpacpi_lअगरecycle = TPACPI_LIFE_EXITING;

	list_क्रम_each_entry_safe_reverse(ibm, iपंचांगp,
					 &tpacpi_all_drivers,
					 all_drivers) अणु
		ibm_निकास(ibm);
	पूर्ण

	dbg_prपूर्णांकk(TPACPI_DBG_INIT, "finished subdriver exit path...\n");

	अगर (tpacpi_inputdev) अणु
		अगर (tp_features.input_device_रेजिस्टरed)
			input_unरेजिस्टर_device(tpacpi_inputdev);
		अन्यथा
			input_मुक्त_device(tpacpi_inputdev);
		kमुक्त(hotkey_keycode_map);
	पूर्ण

	अगर (tpacpi_hwmon)
		hwmon_device_unरेजिस्टर(tpacpi_hwmon);

	अगर (tpacpi_sensors_pdev)
		platक्रमm_device_unरेजिस्टर(tpacpi_sensors_pdev);
	अगर (tpacpi_pdev)
		platक्रमm_device_unरेजिस्टर(tpacpi_pdev);

	अगर (tp_features.sensors_pdrv_attrs_रेजिस्टरed)
		tpacpi_हटाओ_driver_attributes(&tpacpi_hwmon_pdriver.driver);
	अगर (tp_features.platक्रमm_drv_attrs_रेजिस्टरed)
		tpacpi_हटाओ_driver_attributes(&tpacpi_pdriver.driver);

	अगर (tp_features.sensors_pdrv_रेजिस्टरed)
		platक्रमm_driver_unरेजिस्टर(&tpacpi_hwmon_pdriver);

	अगर (tp_features.platक्रमm_drv_रेजिस्टरed)
		platक्रमm_driver_unरेजिस्टर(&tpacpi_pdriver);

	अगर (proc_dir)
		हटाओ_proc_entry(TPACPI_PROC_सूची, acpi_root_dir);

	अगर (tpacpi_wq)
		destroy_workqueue(tpacpi_wq);

	kमुक्त(thinkpad_id.bios_version_str);
	kमुक्त(thinkpad_id.ec_version_str);
	kमुक्त(thinkpad_id.model_str);
	kमुक्त(thinkpad_id.nummodel_str);
पूर्ण


अटल पूर्णांक __init thinkpad_acpi_module_init(व्योम)
अणु
	पूर्णांक ret, i;

	tpacpi_lअगरecycle = TPACPI_LIFE_INIT;

	/* Driver-level probe */

	ret = get_thinkpad_model_data(&thinkpad_id);
	अगर (ret) अणु
		pr_err("unable to get DMI data: %d\n", ret);
		thinkpad_acpi_module_निकास();
		वापस ret;
	पूर्ण
	ret = probe_क्रम_thinkpad();
	अगर (ret) अणु
		thinkpad_acpi_module_निकास();
		वापस ret;
	पूर्ण

	/* Driver initialization */

	thinkpad_acpi_init_banner();
	tpacpi_check_outdated_fw();

	TPACPI_ACPIHANDLE_INIT(ecrd);
	TPACPI_ACPIHANDLE_INIT(ecwr);

	tpacpi_wq = create_singlethपढ़ो_workqueue(TPACPI_WORKQUEUE_NAME);
	अगर (!tpacpi_wq) अणु
		thinkpad_acpi_module_निकास();
		वापस -ENOMEM;
	पूर्ण

	proc_dir = proc_सूची_गढ़ो(TPACPI_PROC_सूची, acpi_root_dir);
	अगर (!proc_dir) अणु
		pr_err("unable to create proc dir " TPACPI_PROC_सूची "\n");
		thinkpad_acpi_module_निकास();
		वापस -ENODEV;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&tpacpi_pdriver);
	अगर (ret) अणु
		pr_err("unable to register main platform driver\n");
		thinkpad_acpi_module_निकास();
		वापस ret;
	पूर्ण
	tp_features.platक्रमm_drv_रेजिस्टरed = 1;

	ret = platक्रमm_driver_रेजिस्टर(&tpacpi_hwmon_pdriver);
	अगर (ret) अणु
		pr_err("unable to register hwmon platform driver\n");
		thinkpad_acpi_module_निकास();
		वापस ret;
	पूर्ण
	tp_features.sensors_pdrv_रेजिस्टरed = 1;

	ret = tpacpi_create_driver_attributes(&tpacpi_pdriver.driver);
	अगर (!ret) अणु
		tp_features.platक्रमm_drv_attrs_रेजिस्टरed = 1;
		ret = tpacpi_create_driver_attributes(
					&tpacpi_hwmon_pdriver.driver);
	पूर्ण
	अगर (ret) अणु
		pr_err("unable to create sysfs driver attributes\n");
		thinkpad_acpi_module_निकास();
		वापस ret;
	पूर्ण
	tp_features.sensors_pdrv_attrs_रेजिस्टरed = 1;


	/* Device initialization */
	tpacpi_pdev = platक्रमm_device_रेजिस्टर_simple(TPACPI_DRVR_NAME, -1,
							शून्य, 0);
	अगर (IS_ERR(tpacpi_pdev)) अणु
		ret = PTR_ERR(tpacpi_pdev);
		tpacpi_pdev = शून्य;
		pr_err("unable to register platform device\n");
		thinkpad_acpi_module_निकास();
		वापस ret;
	पूर्ण
	tpacpi_sensors_pdev = platक्रमm_device_रेजिस्टर_simple(
						TPACPI_HWMON_DRVR_NAME,
						-1, शून्य, 0);
	अगर (IS_ERR(tpacpi_sensors_pdev)) अणु
		ret = PTR_ERR(tpacpi_sensors_pdev);
		tpacpi_sensors_pdev = शून्य;
		pr_err("unable to register hwmon platform device\n");
		thinkpad_acpi_module_निकास();
		वापस ret;
	पूर्ण
	tp_features.sensors_pdev_attrs_रेजिस्टरed = 1;
	tpacpi_hwmon = hwmon_device_रेजिस्टर_with_groups(
		&tpacpi_sensors_pdev->dev, TPACPI_NAME, शून्य, शून्य);

	अगर (IS_ERR(tpacpi_hwmon)) अणु
		ret = PTR_ERR(tpacpi_hwmon);
		tpacpi_hwmon = शून्य;
		pr_err("unable to register hwmon device\n");
		thinkpad_acpi_module_निकास();
		वापस ret;
	पूर्ण
	mutex_init(&tpacpi_inputdev_send_mutex);
	tpacpi_inputdev = input_allocate_device();
	अगर (!tpacpi_inputdev) अणु
		thinkpad_acpi_module_निकास();
		वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		/* Prepare input device, but करोn't रेजिस्टर */
		tpacpi_inputdev->name = "ThinkPad Extra Buttons";
		tpacpi_inputdev->phys = TPACPI_DRVR_NAME "/input0";
		tpacpi_inputdev->id.bustype = BUS_HOST;
		tpacpi_inputdev->id.venकरोr = thinkpad_id.venकरोr;
		tpacpi_inputdev->id.product = TPACPI_HKEY_INPUT_PRODUCT;
		tpacpi_inputdev->id.version = TPACPI_HKEY_INPUT_VERSION;
		tpacpi_inputdev->dev.parent = &tpacpi_pdev->dev;
	पूर्ण

	/* Init subdriver dependencies */
	tpacpi_detect_brightness_capabilities();

	/* Init subdrivers */
	क्रम (i = 0; i < ARRAY_SIZE(ibms_init); i++) अणु
		ret = ibm_init(&ibms_init[i]);
		अगर (ret >= 0 && *ibms_init[i].param)
			ret = ibms_init[i].data->ग_लिखो(ibms_init[i].param);
		अगर (ret < 0) अणु
			thinkpad_acpi_module_निकास();
			वापस ret;
		पूर्ण
	पूर्ण

	tpacpi_lअगरecycle = TPACPI_LIFE_RUNNING;

	ret = input_रेजिस्टर_device(tpacpi_inputdev);
	अगर (ret < 0) अणु
		pr_err("unable to register input device\n");
		thinkpad_acpi_module_निकास();
		वापस ret;
	पूर्ण अन्यथा अणु
		tp_features.input_device_रेजिस्टरed = 1;
	पूर्ण

	वापस 0;
पूर्ण

MODULE_ALIAS(TPACPI_DRVR_SHORTNAME);

/*
 * This will स्वतःload the driver in almost every ThinkPad
 * in widespपढ़ो use.
 *
 * Only _VERY_ old models, like the 240, 240x and 570 lack
 * the HKEY event पूर्णांकerface.
 */
MODULE_DEVICE_TABLE(acpi, ibm_htk_device_ids);

/*
 * DMI matching क्रम module स्वतःloading
 *
 * See https://thinkwiki.org/wiki/List_of_DMI_IDs
 * See https://thinkwiki.org/wiki/BIOS_Upgrade_Downloads
 *
 * Only models listed in thinkwiki will be supported, so add yours
 * अगर it is not there yet.
 */
#घोषणा IBM_BIOS_MODULE_ALIAS(__type) \
	MODULE_ALIAS("dmi:bvnIBM:bvr" __type "ET??WW*")

/* Ancient thinkpad BIOSes have to be identअगरied by
 * BIOS type or model number, and there are far less
 * BIOS types than model numbers... */
IBM_BIOS_MODULE_ALIAS("I[MU]");		/* 570, 570e */

MODULE_AUTHOR("Borislav Deianov <borislav@users.sf.net>");
MODULE_AUTHOR("Henrique de Moraes Holschuh <hmh@hmh.eng.br>");
MODULE_DESCRIPTION(TPACPI_DESC);
MODULE_VERSION(TPACPI_VERSION);
MODULE_LICENSE("GPL");

module_init(thinkpad_acpi_module_init);
module_निकास(thinkpad_acpi_module_निकास);
