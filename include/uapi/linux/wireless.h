<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file define a set of standard wireless extensions
 *
 * Version :	22	16.3.07
 *
 * Authors :	Jean Tourrilhes - HPL - <jt@hpl.hp.com>
 * Copyright (c) 1997-2007 Jean Tourrilhes, All Rights Reserved.
 */

#अगर_अघोषित _UAPI_LINUX_WIRELESS_H
#घोषणा _UAPI_LINUX_WIRELESS_H

/************************** DOCUMENTATION **************************/
/*
 * Initial APIs (1996 -> onward) :
 * -----------------------------
 * Basically, the wireless extensions are क्रम now a set of standard ioctl
 * call + /proc/net/wireless
 *
 * The entry /proc/net/wireless give statistics and inक्रमmation on the
 * driver.
 * This is better than having each driver having its entry because
 * its centralised and we may हटाओ the driver module safely.
 *
 * Ioctl are used to configure the driver and issue commands.  This is
 * better than command line options of insmod because we may want to
 * change dynamically (जबतक the driver is running) some parameters.
 *
 * The ioctl mechanimsm are copied from standard devices ioctl.
 * We have the list of command plus a काष्ठाure descibing the
 * data exchanged...
 * Note that to add these ioctl, I was obliged to modअगरy :
 *	# net/core/dev.c (two place + add include)
 *	# net/ipv4/af_inet.c (one place + add include)
 *
 * /proc/net/wireless is a copy of /proc/net/dev.
 * We have a काष्ठाure क्रम data passed from the driver to /proc/net/wireless
 * Too add this, I've modअगरied :
 *	# net/core/dev.c (two other places)
 *	# include/linux/netdevice.h (one place)
 *	# include/linux/proc_fs.h (one place)
 *
 * New driver API (2002 -> onward) :
 * -------------------------------
 * This file is only concerned with the user space API and common definitions.
 * The new driver API is defined and करोcumented in :
 *	# include/net/iw_handler.h
 *
 * Note as well that /proc/net/wireless implementation has now moved in :
 *	# net/core/wireless.c
 *
 * Wireless Events (2002 -> onward) :
 * --------------------------------
 * Events are defined at the end of this file, and implemented in :
 *	# net/core/wireless.c
 *
 * Other comments :
 * --------------
 * Do not add here things that are redundant with other mechanisms
 * (drivers init, अगरconfig, /proc/net/dev, ...) and with are not
 * wireless specअगरic.
 *
 * These wireless extensions are not magic : each driver has to provide
 * support क्रम them...
 *
 * IMPORTANT NOTE : As everything in the kernel, this is very much a
 * work in progress. Contact me अगर you have ideas of improvements...
 */

/***************************** INCLUDES *****************************/

#समावेश <linux/types.h>		/* क्रम __u* and __s* प्रकारs */
#समावेश <linux/socket.h>		/* क्रम "struct sockaddr" et al	*/
#समावेश <linux/अगर.h>			/* क्रम IFNAMSIZ and co... */

#अगर_घोषित __KERNEL__
#	include <linux/मानकघोष.स>	/* क्रम दुरत्व */
#अन्यथा
#	include <मानकघोष.स>		/* क्रम दुरत्व */
#पूर्ण_अगर

/***************************** VERSION *****************************/
/*
 * This स्थिरant is used to know the availability of the wireless
 * extensions and to know which version of wireless extensions it is
 * (there is some stuff that will be added in the future...)
 * I just plan to increment with each new version.
 */
#घोषणा WIRELESS_EXT	22

/*
 * Changes :
 *
 * V2 to V3
 * --------
 *	Alan Cox start some incompatibles changes. I've पूर्णांकegrated a bit more.
 *	- Encryption नामd to Encode to aव्योम US regulation problems
 *	- Frequency changed from भग्न to काष्ठा to aव्योम problems on old 386
 *
 * V3 to V4
 * --------
 *	- Add sensitivity
 *
 * V4 to V5
 * --------
 *	- Missing encoding definitions in range
 *	- Access poपूर्णांकs stuff
 *
 * V5 to V6
 * --------
 *	- 802.11 support (ESSID ioctls)
 *
 * V6 to V7
 * --------
 *	- define IW_ESSID_MAX_SIZE and IW_MAX_AP
 *
 * V7 to V8
 * --------
 *	- Changed my e-mail address
 *	- More 802.11 support (nickname, rate, rts, frag)
 *	- List index in frequencies
 *
 * V8 to V9
 * --------
 *	- Support क्रम 'mode of operation' (ad-hoc, managed...)
 *	- Support क्रम unicast and multicast घातer saving
 *	- Change encoding to support larger tokens (>64 bits)
 *	- Updated iw_params (disable, flags) and use it क्रम NWID
 *	- Extracted iw_poपूर्णांक from iwreq क्रम clarity
 *
 * V9 to V10
 * ---------
 *	- Add PM capability to range काष्ठाure
 *	- Add PM modअगरier : MAX/MIN/RELATIVE
 *	- Add encoding option : IW_ENCODE_NOKEY
 *	- Add TxPower ioctls (work like TxRate)
 *
 * V10 to V11
 * ----------
 *	- Add WE version in range (help backward/क्रमward compatibility)
 *	- Add retry ioctls (work like PM)
 *
 * V11 to V12
 * ----------
 *	- Add SIOCSIWSTATS to get /proc/net/wireless programatically
 *	- Add DEV PRIVATE IOCTL to aव्योम collisions in SIOCDEVPRIVATE space
 *	- Add new statistics (frag, retry, beacon)
 *	- Add average quality (क्रम user space calibration)
 *
 * V12 to V13
 * ----------
 *	- Document creation of new driver API.
 *	- Extract जोड़ iwreq_data from काष्ठा iwreq (क्रम new driver API).
 *	- Rename SIOCSIWNAME as SIOCSIWCOMMIT
 *
 * V13 to V14
 * ----------
 *	- Wireless Events support : define काष्ठा iw_event
 *	- Define additional specअगरic event numbers
 *	- Add "addr" and "param" fields in जोड़ iwreq_data
 *	- AP scanning stuff (SIOCSIWSCAN and मित्रs)
 *
 * V14 to V15
 * ----------
 *	- Add IW_PRIV_TYPE_ADDR क्रम काष्ठा sockaddr निजी arg
 *	- Make काष्ठा iw_freq चिन्हित (both m & e), add explicit padding
 *	- Add IWEVCUSTOM क्रम driver specअगरic event/scanning token
 *	- Add IW_MAX_GET_SPY क्रम driver वापसing a lot of addresses
 *	- Add IW_TXPOW_RANGE क्रम range of Tx Powers
 *	- Add IWEVREGISTERED & IWEVEXPIRED events क्रम Access Poपूर्णांकs
 *	- Add IW_MODE_MONITOR क्रम passive monitor
 *
 * V15 to V16
 * ----------
 *	- Increase the number of bitrates in iw_range to 32 (क्रम 802.11g)
 *	- Increase the number of frequencies in iw_range to 32 (क्रम 802.11b+a)
 *	- Reshuffle काष्ठा iw_range क्रम increases, add filler
 *	- Increase IW_MAX_AP to 64 क्रम driver वापसing a lot of addresses
 *	- Remove IW_MAX_GET_SPY because conflict with enhanced spy support
 *	- Add SIOCSIWTHRSPY/SIOCGIWTHRSPY and "struct iw_thrspy"
 *	- Add IW_ENCODE_TEMP and iw_range->encoding_login_index
 *
 * V16 to V17
 * ----------
 *	- Add flags to frequency -> स्वतः/fixed
 *	- Document (काष्ठा iw_quality *)->updated, add new flags (INVALID)
 *	- Wireless Event capability in काष्ठा iw_range
 *	- Add support क्रम relative TxPower (yick !)
 *
 * V17 to V18 (From Jouni Malinen <j@w1.fi>)
 * ----------
 *	- Add support क्रम WPA/WPA2
 *	- Add extended encoding configuration (SIOCSIWENCODEEXT and
 *	  SIOCGIWENCODEEXT)
 *	- Add SIOCSIWGENIE/SIOCGIWGENIE
 *	- Add SIOCSIWMLME
 *	- Add SIOCSIWPMKSA
 *	- Add काष्ठा iw_range bit field क्रम supported encoding capabilities
 *	- Add optional scan request parameters क्रम SIOCSIWSCAN
 *	- Add SIOCSIWAUTH/SIOCGIWAUTH क्रम setting authentication and WPA
 *	  related parameters (extensible up to 4096 parameter values)
 *	- Add wireless events: IWEVGENIE, IWEVMICHAELMICFAILURE,
 *	  IWEVASSOCREQIE, IWEVASSOCRESPIE, IWEVPMKIDCAND
 *
 * V18 to V19
 * ----------
 *	- Remove (काष्ठा iw_poपूर्णांक *)->poपूर्णांकer from events and streams
 *	- Remove header includes to help user space
 *	- Increase IW_ENCODING_TOKEN_MAX from 32 to 64
 *	- Add IW_QUAL_ALL_UPDATED and IW_QUAL_ALL_INVALID macros
 *	- Add explicit flag to tell stats are in dBm : IW_QUAL_DBM
 *	- Add IW_IOCTL_IDX() and IW_EVENT_IDX() macros
 *
 * V19 to V20
 * ----------
 *	- RtNetlink requests support (SET/GET)
 *
 * V20 to V21
 * ----------
 *	- Remove (काष्ठा net_device *)->get_wireless_stats()
 *	- Change length in ESSID and NICK to म_माप() instead of म_माप()+1
 *	- Add IW_RETRY_SHORT/IW_RETRY_LONG retry modअगरiers
 *	- Power/Retry relative values no दीर्घer * 100000
 *	- Add explicit flag to tell stats are in 802.11k RCPI : IW_QUAL_RCPI
 *
 * V21 to V22
 * ----------
 *	- Prevent leaking of kernel space in stream on 64 bits.
 */

/**************************** CONSTANTS ****************************/

/* -------------------------- IOCTL LIST -------------------------- */

/* Wireless Identअगरication */
#घोषणा SIOCSIWCOMMIT	0x8B00		/* Commit pending changes to driver */
#घोषणा SIOCGIWNAME	0x8B01		/* get name == wireless protocol */
/* SIOCGIWNAME is used to verअगरy the presence of Wireless Extensions.
 * Common values : "IEEE 802.11-DS", "IEEE 802.11-FH", "IEEE 802.11b"...
 * Don't put the name of your driver there, it's useless. */

/* Basic operations */
#घोषणा SIOCSIWNWID	0x8B02		/* set network id (pre-802.11) */
#घोषणा SIOCGIWNWID	0x8B03		/* get network id (the cell) */
#घोषणा SIOCSIWFREQ	0x8B04		/* set channel/frequency (Hz) */
#घोषणा SIOCGIWFREQ	0x8B05		/* get channel/frequency (Hz) */
#घोषणा SIOCSIWMODE	0x8B06		/* set operation mode */
#घोषणा SIOCGIWMODE	0x8B07		/* get operation mode */
#घोषणा SIOCSIWSENS	0x8B08		/* set sensitivity (dBm) */
#घोषणा SIOCGIWSENS	0x8B09		/* get sensitivity (dBm) */

/* Inक्रमmative stuff */
#घोषणा SIOCSIWRANGE	0x8B0A		/* Unused */
#घोषणा SIOCGIWRANGE	0x8B0B		/* Get range of parameters */
#घोषणा SIOCSIWPRIV	0x8B0C		/* Unused */
#घोषणा SIOCGIWPRIV	0x8B0D		/* get निजी ioctl पूर्णांकerface info */
#घोषणा SIOCSIWSTATS	0x8B0E		/* Unused */
#घोषणा SIOCGIWSTATS	0x8B0F		/* Get /proc/net/wireless stats */
/* SIOCGIWSTATS is strictly used between user space and the kernel, and
 * is never passed to the driver (i.e. the driver will never see it). */

/* Spy support (statistics per MAC address - used क्रम Mobile IP support) */
#घोषणा SIOCSIWSPY	0x8B10		/* set spy addresses */
#घोषणा SIOCGIWSPY	0x8B11		/* get spy info (quality of link) */
#घोषणा SIOCSIWTHRSPY	0x8B12		/* set spy threshold (spy event) */
#घोषणा SIOCGIWTHRSPY	0x8B13		/* get spy threshold */

/* Access Poपूर्णांक manipulation */
#घोषणा SIOCSIWAP	0x8B14		/* set access poपूर्णांक MAC addresses */
#घोषणा SIOCGIWAP	0x8B15		/* get access poपूर्णांक MAC addresses */
#घोषणा SIOCGIWAPLIST	0x8B17		/* Deprecated in favor of scanning */
#घोषणा SIOCSIWSCAN	0x8B18		/* trigger scanning (list cells) */
#घोषणा SIOCGIWSCAN	0x8B19		/* get scanning results */

/* 802.11 specअगरic support */
#घोषणा SIOCSIWESSID	0x8B1A		/* set ESSID (network name) */
#घोषणा SIOCGIWESSID	0x8B1B		/* get ESSID */
#घोषणा SIOCSIWNICKN	0x8B1C		/* set node name/nickname */
#घोषणा SIOCGIWNICKN	0x8B1D		/* get node name/nickname */
/* As the ESSID and NICKN are strings up to 32 bytes दीर्घ, it करोesn't fit
 * within the 'iwreq' structure, so we need to use the 'data' member to
 * poपूर्णांक to a string in user space, like it is करोne क्रम RANGE... */

/* Other parameters useful in 802.11 and some other devices */
#घोषणा SIOCSIWRATE	0x8B20		/* set शेष bit rate (bps) */
#घोषणा SIOCGIWRATE	0x8B21		/* get शेष bit rate (bps) */
#घोषणा SIOCSIWRTS	0x8B22		/* set RTS/CTS threshold (bytes) */
#घोषणा SIOCGIWRTS	0x8B23		/* get RTS/CTS threshold (bytes) */
#घोषणा SIOCSIWFRAG	0x8B24		/* set fragmentation thr (bytes) */
#घोषणा SIOCGIWFRAG	0x8B25		/* get fragmentation thr (bytes) */
#घोषणा SIOCSIWTXPOW	0x8B26		/* set transmit घातer (dBm) */
#घोषणा SIOCGIWTXPOW	0x8B27		/* get transmit घातer (dBm) */
#घोषणा SIOCSIWRETRY	0x8B28		/* set retry limits and lअगरeसमय */
#घोषणा SIOCGIWRETRY	0x8B29		/* get retry limits and lअगरeसमय */

/* Encoding stuff (scrambling, hardware security, WEP...) */
#घोषणा SIOCSIWENCODE	0x8B2A		/* set encoding token & mode */
#घोषणा SIOCGIWENCODE	0x8B2B		/* get encoding token & mode */
/* Power saving stuff (घातer management, unicast and multicast) */
#घोषणा SIOCSIWPOWER	0x8B2C		/* set Power Management settings */
#घोषणा SIOCGIWPOWER	0x8B2D		/* get Power Management settings */

/* WPA : Generic IEEE 802.11 inक्रमmatiom element (e.g., क्रम WPA/RSN/WMM).
 * This ioctl uses काष्ठा iw_poपूर्णांक and data buffer that includes IE id and len
 * fields. More than one IE may be included in the request. Setting the generic
 * IE to empty buffer (len=0) हटाओs the generic IE from the driver. Drivers
 * are allowed to generate their own WPA/RSN IEs, but in these हालs, drivers
 * are required to report the used IE as a wireless event, e.g., when
 * associating with an AP. */
#घोषणा SIOCSIWGENIE	0x8B30		/* set generic IE */
#घोषणा SIOCGIWGENIE	0x8B31		/* get generic IE */

/* WPA : IEEE 802.11 MLME requests */
#घोषणा SIOCSIWMLME	0x8B16		/* request MLME operation; uses
					 * काष्ठा iw_mlme */
/* WPA : Authentication mode parameters */
#घोषणा SIOCSIWAUTH	0x8B32		/* set authentication mode params */
#घोषणा SIOCGIWAUTH	0x8B33		/* get authentication mode params */

/* WPA : Extended version of encoding configuration */
#घोषणा SIOCSIWENCODEEXT 0x8B34		/* set encoding token & mode */
#घोषणा SIOCGIWENCODEEXT 0x8B35		/* get encoding token & mode */

/* WPA2 : PMKSA cache management */
#घोषणा SIOCSIWPMKSA	0x8B36		/* PMKSA cache operation */

/* -------------------- DEV PRIVATE IOCTL LIST -------------------- */

/* These 32 ioctl are wireless device निजी, क्रम 16 commands.
 * Each driver is मुक्त to use them क्रम whatever purpose it chooses,
 * however the driver *must* export the description of those ioctls
 * with SIOCGIWPRIV and *must* use arguments as defined below.
 * If you करोn't follow those rules, DaveM is going to hate you (reason :
 * it make mixed 32/64bit operation impossible).
 */
#घोषणा SIOCIWFIRSTPRIV	0x8BE0
#घोषणा SIOCIWLASTPRIV	0x8BFF
/* Previously, we were using SIOCDEVPRIVATE, but we now have our
 * separate range because of collisions with other tools such as
 * 'mii-tool'.
 * We now have 32 commands, so a bit more space ;-).
 * Also, all 'even' commands are only usable by root and don't वापस the
 * content of अगरr/iwr to user (but you are not obliged to use the set/get
 * convention, just use every other two command). More details in iwpriv.c.
 * And I repeat : you are not क्रमced to use them with iwpriv, but you
 * must be compliant with it.
 */

/* ------------------------- IOCTL STUFF ------------------------- */

/* The first and the last (range) */
#घोषणा SIOCIWFIRST	0x8B00
#घोषणा SIOCIWLAST	SIOCIWLASTPRIV		/* 0x8BFF */
#घोषणा IW_IOCTL_IDX(cmd)	((cmd) - SIOCIWFIRST)
#घोषणा IW_HANDLER(id, func)			\
	[IW_IOCTL_IDX(id)] = func

/* Odd : get (world access), even : set (root access) */
#घोषणा IW_IS_SET(cmd)	(!((cmd) & 0x1))
#घोषणा IW_IS_GET(cmd)	((cmd) & 0x1)

/* ----------------------- WIRELESS EVENTS ----------------------- */
/* Those are *NOT* ioctls, करो not issue request on them !!! */
/* Most events use the same identअगरier as ioctl requests */

#घोषणा IWEVTXDROP	0x8C00		/* Packet dropped to excessive retry */
#घोषणा IWEVQUAL	0x8C01		/* Quality part of statistics (scan) */
#घोषणा IWEVCUSTOM	0x8C02		/* Driver specअगरic ascii string */
#घोषणा IWEVREGISTERED	0x8C03		/* Discovered a new node (AP mode) */
#घोषणा IWEVEXPIRED	0x8C04		/* Expired a node (AP mode) */
#घोषणा IWEVGENIE	0x8C05		/* Generic IE (WPA, RSN, WMM, ..)
					 * (scan results); This includes id and
					 * length fields. One IWEVGENIE may
					 * contain more than one IE. Scan
					 * results may contain one or more
					 * IWEVGENIE events. */
#घोषणा IWEVMICHAELMICFAILURE 0x8C06	/* Michael MIC failure
					 * (काष्ठा iw_michaelmicfailure)
					 */
#घोषणा IWEVASSOCREQIE	0x8C07		/* IEs used in (Re)Association Request.
					 * The data includes id and length
					 * fields and may contain more than one
					 * IE. This event is required in
					 * Managed mode अगर the driver
					 * generates its own WPA/RSN IE. This
					 * should be sent just beक्रमe
					 * IWEVREGISTERED event क्रम the
					 * association. */
#घोषणा IWEVASSOCRESPIE	0x8C08		/* IEs used in (Re)Association
					 * Response. The data includes id and
					 * length fields and may contain more
					 * than one IE. This may be sent
					 * between IWEVASSOCREQIE and
					 * IWEVREGISTERED events क्रम the
					 * association. */
#घोषणा IWEVPMKIDCAND	0x8C09		/* PMKID candidate क्रम RSN
					 * pre-authentication
					 * (काष्ठा iw_pmkid_cand) */

#घोषणा IWEVFIRST	0x8C00
#घोषणा IW_EVENT_IDX(cmd)	((cmd) - IWEVFIRST)

/* ------------------------- PRIVATE INFO ------------------------- */
/*
 * The following is used with SIOCGIWPRIV. It allow a driver to define
 * the पूर्णांकerface (name, type of data) क्रम its निजी ioctl.
 * Privates ioctl are SIOCIWFIRSTPRIV -> SIOCIWLASTPRIV
 */

#घोषणा IW_PRIV_TYPE_MASK	0x7000	/* Type of arguments */
#घोषणा IW_PRIV_TYPE_NONE	0x0000
#घोषणा IW_PRIV_TYPE_BYTE	0x1000	/* Char as number */
#घोषणा IW_PRIV_TYPE_CHAR	0x2000	/* Char as अक्षरacter */
#घोषणा IW_PRIV_TYPE_INT	0x4000	/* 32 bits पूर्णांक */
#घोषणा IW_PRIV_TYPE_FLOAT	0x5000	/* काष्ठा iw_freq */
#घोषणा IW_PRIV_TYPE_ADDR	0x6000	/* काष्ठा sockaddr */

#घोषणा IW_PRIV_SIZE_FIXED	0x0800	/* Variable or fixed number of args */

#घोषणा IW_PRIV_SIZE_MASK	0x07FF	/* Max number of those args */

/*
 * Note : अगर the number of args is fixed and the size < 16 octets,
 * instead of passing a poपूर्णांकer we will put args in the iwreq काष्ठा...
 */

/* ----------------------- OTHER CONSTANTS ----------------------- */

/* Maximum frequencies in the range काष्ठा */
#घोषणा IW_MAX_FREQUENCIES	32
/* Note : अगर you have something like 80 frequencies,
 * करोn't increase this constant and don't fill the frequency list.
 * The user will be able to set by channel anyway... */

/* Maximum bit rates in the range काष्ठा */
#घोषणा IW_MAX_BITRATES		32

/* Maximum tx घातers in the range काष्ठा */
#घोषणा IW_MAX_TXPOWER		8
/* Note : अगर you more than 8 TXPowers, just set the max and min or
 * a few of them in the काष्ठा iw_range. */

/* Maximum of address that you may set with SPY */
#घोषणा IW_MAX_SPY		8

/* Maximum of address that you may get in the
   list of access poपूर्णांकs in range */
#घोषणा IW_MAX_AP		64

/* Maximum size of the ESSID and NICKN strings */
#घोषणा IW_ESSID_MAX_SIZE	32

/* Modes of operation */
#घोषणा IW_MODE_AUTO	0	/* Let the driver decides */
#घोषणा IW_MODE_ADHOC	1	/* Single cell network */
#घोषणा IW_MODE_INFRA	2	/* Multi cell network, roaming, ... */
#घोषणा IW_MODE_MASTER	3	/* Synchronisation master or Access Poपूर्णांक */
#घोषणा IW_MODE_REPEAT	4	/* Wireless Repeater (क्रमwarder) */
#घोषणा IW_MODE_SECOND	5	/* Secondary master/repeater (backup) */
#घोषणा IW_MODE_MONITOR	6	/* Passive monitor (listen only) */
#घोषणा IW_MODE_MESH	7	/* Mesh (IEEE 802.11s) network */

/* Statistics flags (biपंचांगask in updated) */
#घोषणा IW_QUAL_QUAL_UPDATED	0x01	/* Value was updated since last पढ़ो */
#घोषणा IW_QUAL_LEVEL_UPDATED	0x02
#घोषणा IW_QUAL_NOISE_UPDATED	0x04
#घोषणा IW_QUAL_ALL_UPDATED	0x07
#घोषणा IW_QUAL_DBM		0x08	/* Level + Noise are dBm */
#घोषणा IW_QUAL_QUAL_INVALID	0x10	/* Driver करोesn't provide value */
#घोषणा IW_QUAL_LEVEL_INVALID	0x20
#घोषणा IW_QUAL_NOISE_INVALID	0x40
#घोषणा IW_QUAL_RCPI		0x80	/* Level + Noise are 802.11k RCPI */
#घोषणा IW_QUAL_ALL_INVALID	0x70

/* Frequency flags */
#घोषणा IW_FREQ_AUTO		0x00	/* Let the driver decides */
#घोषणा IW_FREQ_FIXED		0x01	/* Force a specअगरic value */

/* Maximum number of size of encoding token available
 * they are listed in the range काष्ठाure */
#घोषणा IW_MAX_ENCODING_SIZES	8

/* Maximum size of the encoding token in bytes */
#घोषणा IW_ENCODING_TOKEN_MAX	64	/* 512 bits (क्रम now) */

/* Flags क्रम encoding (aदीर्घ with the token) */
#घोषणा IW_ENCODE_INDEX		0x00FF	/* Token index (अगर needed) */
#घोषणा IW_ENCODE_FLAGS		0xFF00	/* Flags defined below */
#घोषणा IW_ENCODE_MODE		0xF000	/* Modes defined below */
#घोषणा IW_ENCODE_DISABLED	0x8000	/* Encoding disabled */
#घोषणा IW_ENCODE_ENABLED	0x0000	/* Encoding enabled */
#घोषणा IW_ENCODE_RESTRICTED	0x4000	/* Refuse non-encoded packets */
#घोषणा IW_ENCODE_OPEN		0x2000	/* Accept non-encoded packets */
#घोषणा IW_ENCODE_NOKEY		0x0800  /* Key is ग_लिखो only, so not present */
#घोषणा IW_ENCODE_TEMP		0x0400  /* Temporary key */

/* Power management flags available (aदीर्घ with the value, अगर any) */
#घोषणा IW_POWER_ON		0x0000	/* No details... */
#घोषणा IW_POWER_TYPE		0xF000	/* Type of parameter */
#घोषणा IW_POWER_PERIOD		0x1000	/* Value is a period/duration of  */
#घोषणा IW_POWER_TIMEOUT	0x2000	/* Value is a समयout (to go asleep) */
#घोषणा IW_POWER_MODE		0x0F00	/* Power Management mode */
#घोषणा IW_POWER_UNICAST_R	0x0100	/* Receive only unicast messages */
#घोषणा IW_POWER_MULTICAST_R	0x0200	/* Receive only multicast messages */
#घोषणा IW_POWER_ALL_R		0x0300	/* Receive all messages though PM */
#घोषणा IW_POWER_FORCE_S	0x0400	/* Force PM procedure क्रम sending unicast */
#घोषणा IW_POWER_REPEATER	0x0800	/* Repeat broadcast messages in PM period */
#घोषणा IW_POWER_MODIFIER	0x000F	/* Modअगरy a parameter */
#घोषणा IW_POWER_MIN		0x0001	/* Value is a minimum  */
#घोषणा IW_POWER_MAX		0x0002	/* Value is a maximum */
#घोषणा IW_POWER_RELATIVE	0x0004	/* Value is not in seconds/ms/us */

/* Transmit Power flags available */
#घोषणा IW_TXPOW_TYPE		0x00FF	/* Type of value */
#घोषणा IW_TXPOW_DBM		0x0000	/* Value is in dBm */
#घोषणा IW_TXPOW_MWATT		0x0001	/* Value is in mW */
#घोषणा IW_TXPOW_RELATIVE	0x0002	/* Value is in arbitrary units */
#घोषणा IW_TXPOW_RANGE		0x1000	/* Range of value between min/max */

/* Retry limits and lअगरeसमय flags available */
#घोषणा IW_RETRY_ON		0x0000	/* No details... */
#घोषणा IW_RETRY_TYPE		0xF000	/* Type of parameter */
#घोषणा IW_RETRY_LIMIT		0x1000	/* Maximum number of retries*/
#घोषणा IW_RETRY_LIFETIME	0x2000	/* Maximum duration of retries in us */
#घोषणा IW_RETRY_MODIFIER	0x00FF	/* Modअगरy a parameter */
#घोषणा IW_RETRY_MIN		0x0001	/* Value is a minimum  */
#घोषणा IW_RETRY_MAX		0x0002	/* Value is a maximum */
#घोषणा IW_RETRY_RELATIVE	0x0004	/* Value is not in seconds/ms/us */
#घोषणा IW_RETRY_SHORT		0x0010	/* Value is क्रम लघु packets  */
#घोषणा IW_RETRY_LONG		0x0020	/* Value is क्रम दीर्घ packets */

/* Scanning request flags */
#घोषणा IW_SCAN_DEFAULT		0x0000	/* Default scan of the driver */
#घोषणा IW_SCAN_ALL_ESSID	0x0001	/* Scan all ESSIDs */
#घोषणा IW_SCAN_THIS_ESSID	0x0002	/* Scan only this ESSID */
#घोषणा IW_SCAN_ALL_FREQ	0x0004	/* Scan all Frequencies */
#घोषणा IW_SCAN_THIS_FREQ	0x0008	/* Scan only this Frequency */
#घोषणा IW_SCAN_ALL_MODE	0x0010	/* Scan all Modes */
#घोषणा IW_SCAN_THIS_MODE	0x0020	/* Scan only this Mode */
#घोषणा IW_SCAN_ALL_RATE	0x0040	/* Scan all Bit-Rates */
#घोषणा IW_SCAN_THIS_RATE	0x0080	/* Scan only this Bit-Rate */
/* काष्ठा iw_scan_req scan_type */
#घोषणा IW_SCAN_TYPE_ACTIVE 0
#घोषणा IW_SCAN_TYPE_PASSIVE 1
/* Maximum size of वापसed data */
#घोषणा IW_SCAN_MAX_DATA	4096	/* In bytes */

/* Scan capability flags - in (काष्ठा iw_range *)->scan_capa */
#घोषणा IW_SCAN_CAPA_NONE		0x00
#घोषणा IW_SCAN_CAPA_ESSID		0x01
#घोषणा IW_SCAN_CAPA_BSSID		0x02
#घोषणा IW_SCAN_CAPA_CHANNEL	0x04
#घोषणा IW_SCAN_CAPA_MODE		0x08
#घोषणा IW_SCAN_CAPA_RATE		0x10
#घोषणा IW_SCAN_CAPA_TYPE		0x20
#घोषणा IW_SCAN_CAPA_TIME		0x40

/* Max number of अक्षर in custom event - use multiple of them अगर needed */
#घोषणा IW_CUSTOM_MAX		256	/* In bytes */

/* Generic inक्रमmation element */
#घोषणा IW_GENERIC_IE_MAX	1024

/* MLME requests (SIOCSIWMLME / काष्ठा iw_mlme) */
#घोषणा IW_MLME_DEAUTH		0
#घोषणा IW_MLME_DISASSOC	1
#घोषणा IW_MLME_AUTH		2
#घोषणा IW_MLME_ASSOC		3

/* SIOCSIWAUTH/SIOCGIWAUTH काष्ठा iw_param flags */
#घोषणा IW_AUTH_INDEX		0x0FFF
#घोषणा IW_AUTH_FLAGS		0xF000
/* SIOCSIWAUTH/SIOCGIWAUTH parameters (0 .. 4095)
 * (IW_AUTH_INDEX mask in काष्ठा iw_param flags; this is the index of the
 * parameter that is being set/get to; value will be पढ़ो/written to
 * काष्ठा iw_param value field) */
#घोषणा IW_AUTH_WPA_VERSION		0
#घोषणा IW_AUTH_CIPHER_PAIRWISE		1
#घोषणा IW_AUTH_CIPHER_GROUP		2
#घोषणा IW_AUTH_KEY_MGMT		3
#घोषणा IW_AUTH_TKIP_COUNTERMEASURES	4
#घोषणा IW_AUTH_DROP_UNENCRYPTED	5
#घोषणा IW_AUTH_80211_AUTH_ALG		6
#घोषणा IW_AUTH_WPA_ENABLED		7
#घोषणा IW_AUTH_RX_UNENCRYPTED_EAPOL	8
#घोषणा IW_AUTH_ROAMING_CONTROL		9
#घोषणा IW_AUTH_PRIVACY_INVOKED		10
#घोषणा IW_AUTH_CIPHER_GROUP_MGMT	11
#घोषणा IW_AUTH_MFP			12

/* IW_AUTH_WPA_VERSION values (bit field) */
#घोषणा IW_AUTH_WPA_VERSION_DISABLED	0x00000001
#घोषणा IW_AUTH_WPA_VERSION_WPA		0x00000002
#घोषणा IW_AUTH_WPA_VERSION_WPA2	0x00000004

/* IW_AUTH_PAIRWISE_CIPHER, IW_AUTH_GROUP_CIPHER, and IW_AUTH_CIPHER_GROUP_MGMT
 * values (bit field) */
#घोषणा IW_AUTH_CIPHER_NONE	0x00000001
#घोषणा IW_AUTH_CIPHER_WEP40	0x00000002
#घोषणा IW_AUTH_CIPHER_TKIP	0x00000004
#घोषणा IW_AUTH_CIPHER_CCMP	0x00000008
#घोषणा IW_AUTH_CIPHER_WEP104	0x00000010
#घोषणा IW_AUTH_CIPHER_AES_CMAC	0x00000020

/* IW_AUTH_KEY_MGMT values (bit field) */
#घोषणा IW_AUTH_KEY_MGMT_802_1X	1
#घोषणा IW_AUTH_KEY_MGMT_PSK	2

/* IW_AUTH_80211_AUTH_ALG values (bit field) */
#घोषणा IW_AUTH_ALG_OPEN_SYSTEM	0x00000001
#घोषणा IW_AUTH_ALG_SHARED_KEY	0x00000002
#घोषणा IW_AUTH_ALG_LEAP	0x00000004

/* IW_AUTH_ROAMING_CONTROL values */
#घोषणा IW_AUTH_ROAMING_ENABLE	0	/* driver/firmware based roaming */
#घोषणा IW_AUTH_ROAMING_DISABLE	1	/* user space program used क्रम roaming
					 * control */

/* IW_AUTH_MFP (management frame protection) values */
#घोषणा IW_AUTH_MFP_DISABLED	0	/* MFP disabled */
#घोषणा IW_AUTH_MFP_OPTIONAL	1	/* MFP optional */
#घोषणा IW_AUTH_MFP_REQUIRED	2	/* MFP required */

/* SIOCSIWENCODEEXT definitions */
#घोषणा IW_ENCODE_SEQ_MAX_SIZE	8
/* काष्ठा iw_encode_ext ->alg */
#घोषणा IW_ENCODE_ALG_NONE	0
#घोषणा IW_ENCODE_ALG_WEP	1
#घोषणा IW_ENCODE_ALG_TKIP	2
#घोषणा IW_ENCODE_ALG_CCMP	3
#घोषणा IW_ENCODE_ALG_PMK	4
#घोषणा IW_ENCODE_ALG_AES_CMAC	5
/* काष्ठा iw_encode_ext ->ext_flags */
#घोषणा IW_ENCODE_EXT_TX_SEQ_VALID	0x00000001
#घोषणा IW_ENCODE_EXT_RX_SEQ_VALID	0x00000002
#घोषणा IW_ENCODE_EXT_GROUP_KEY		0x00000004
#घोषणा IW_ENCODE_EXT_SET_TX_KEY	0x00000008

/* IWEVMICHAELMICFAILURE : काष्ठा iw_michaelmicfailure ->flags */
#घोषणा IW_MICFAILURE_KEY_ID	0x00000003 /* Key ID 0..3 */
#घोषणा IW_MICFAILURE_GROUP	0x00000004
#घोषणा IW_MICFAILURE_PAIRWISE	0x00000008
#घोषणा IW_MICFAILURE_STAKEY	0x00000010
#घोषणा IW_MICFAILURE_COUNT	0x00000060 /* 1 or 2 (0 = count not supported)
					    */

/* Bit field values क्रम enc_capa in काष्ठा iw_range */
#घोषणा IW_ENC_CAPA_WPA		0x00000001
#घोषणा IW_ENC_CAPA_WPA2	0x00000002
#घोषणा IW_ENC_CAPA_CIPHER_TKIP	0x00000004
#घोषणा IW_ENC_CAPA_CIPHER_CCMP	0x00000008
#घोषणा IW_ENC_CAPA_4WAY_HANDSHAKE	0x00000010

/* Event capability macros - in (काष्ठा iw_range *)->event_capa
 * Because we have more than 32 possible events, we use an array of
 * 32 bit biपंचांगasks. Note : 32 bits = 0x20 = 2^5. */
#घोषणा IW_EVENT_CAPA_BASE(cmd)		((cmd >= SIOCIWFIRSTPRIV) ? \
					 (cmd - SIOCIWFIRSTPRIV + 0x60) : \
					 (cmd - SIOCIWFIRST))
#घोषणा IW_EVENT_CAPA_INDEX(cmd)	(IW_EVENT_CAPA_BASE(cmd) >> 5)
#घोषणा IW_EVENT_CAPA_MASK(cmd)		(1 << (IW_EVENT_CAPA_BASE(cmd) & 0x1F))
/* Event capability स्थिरants - event स्वतःgenerated by the kernel
 * This list is valid क्रम most 802.11 devices, customise as needed... */
#घोषणा IW_EVENT_CAPA_K_0	(IW_EVENT_CAPA_MASK(0x8B04) | \
				 IW_EVENT_CAPA_MASK(0x8B06) | \
				 IW_EVENT_CAPA_MASK(0x8B1A))
#घोषणा IW_EVENT_CAPA_K_1	(IW_EVENT_CAPA_MASK(0x8B2A))
/* "Easy" macro to set events in iw_range (less efficient) */
#घोषणा IW_EVENT_CAPA_SET(event_capa, cmd) (event_capa[IW_EVENT_CAPA_INDEX(cmd)] |= IW_EVENT_CAPA_MASK(cmd))
#घोषणा IW_EVENT_CAPA_SET_KERNEL(event_capa) अणुevent_capa[0] |= IW_EVENT_CAPA_K_0; event_capa[1] |= IW_EVENT_CAPA_K_1; पूर्ण


/****************************** TYPES ******************************/

/* --------------------------- SUBTYPES --------------------------- */
/*
 *	Generic क्रमmat क्रम most parameters that fit in an पूर्णांक
 */
काष्ठा iw_param अणु
  __s32		value;		/* The value of the parameter itself */
  __u8		fixed;		/* Hardware should not use स्वतः select */
  __u8		disabled;	/* Disable the feature */
  __u16		flags;		/* Various specअगरc flags (अगर any) */
पूर्ण;

/*
 *	For all data larger than 16 octets, we need to use a
 *	poपूर्णांकer to memory allocated in user space.
 */
काष्ठा iw_poपूर्णांक अणु
  व्योम __user	*poपूर्णांकer;	/* Poपूर्णांकer to the data  (in user space) */
  __u16		length;		/* number of fields or size in bytes */
  __u16		flags;		/* Optional params */
पूर्ण;


/*
 *	A frequency
 *	For numbers lower than 10^9, we encode the number in 'm' and
 *	set 'e' to 0
 *	For number greater than 10^9, we भागide it by the lowest घातer
 *	of 10 to get 'm' lower than 10^9, with 'm'= f / (10^'e')...
 *	The घातer of 10 is in 'e', the result of the division is in 'm'.
 */
काष्ठा iw_freq अणु
	__s32		m;		/* Mantissa */
	__s16		e;		/* Exponent */
	__u8		i;		/* List index (when in range काष्ठा) */
	__u8		flags;		/* Flags (fixed/स्वतः) */
पूर्ण;

/*
 *	Quality of the link
 */
काष्ठा iw_quality अणु
	__u8		qual;		/* link quality (%retries, SNR,
					   %missed beacons or better...) */
	__u8		level;		/* संकेत level (dBm) */
	__u8		noise;		/* noise level (dBm) */
	__u8		updated;	/* Flags to know अगर updated */
पूर्ण;

/*
 *	Packet discarded in the wireless adapter due to
 *	"wireless" specअगरic problems...
 *	Note : the list of counter and statistics in net_device_stats
 *	is alपढ़ोy pretty exhaustive, and you should use that first.
 *	This is only additional stats...
 */
काष्ठा iw_discarded अणु
	__u32		nwid;		/* Rx : Wrong nwid/essid */
	__u32		code;		/* Rx : Unable to code/decode (WEP) */
	__u32		fragment;	/* Rx : Can't perक्रमm MAC reassembly */
	__u32		retries;	/* Tx : Max MAC retries num reached */
	__u32		misc;		/* Others हालs */
पूर्ण;

/*
 *	Packet/Time period missed in the wireless adapter due to
 *	"wireless" specअगरic problems...
 */
काष्ठा iw_missed अणु
	__u32		beacon;		/* Missed beacons/superframe */
पूर्ण;

/*
 *	Quality range (क्रम spy threshold)
 */
काष्ठा iw_thrspy अणु
	काष्ठा sockaddr		addr;		/* Source address (hw/mac) */
	काष्ठा iw_quality	qual;		/* Quality of the link */
	काष्ठा iw_quality	low;		/* Low threshold */
	काष्ठा iw_quality	high;		/* High threshold */
पूर्ण;

/*
 *	Optional data क्रम scan request
 *
 *	Note: these optional parameters are controlling parameters क्रम the
 *	scanning behavior, these करो not apply to getting scan results
 *	(SIOCGIWSCAN). Drivers are expected to keep a local BSS table and
 *	provide a merged results with all BSSes even अगर the previous scan
 *	request limited scanning to a subset, e.g., by specअगरying an SSID.
 *	Especially, scan results are required to include an entry क्रम the
 *	current BSS अगर the driver is in Managed mode and associated with an AP.
 */
काष्ठा iw_scan_req अणु
	__u8		scan_type; /* IW_SCAN_TYPE_अणुACTIVE,PASSIVEपूर्ण */
	__u8		essid_len;
	__u8		num_channels; /* num entries in channel_list;
				       * 0 = scan all allowed channels */
	__u8		flags; /* reserved as padding; use zero, this may
				* be used in the future क्रम adding flags
				* to request dअगरferent scan behavior */
	काष्ठा sockaddr	bssid; /* ff:ff:ff:ff:ff:ff क्रम broadcast BSSID or
				* inभागidual address of a specअगरic BSS */

	/*
	 * Use this ESSID अगर IW_SCAN_THIS_ESSID flag is used instead of using
	 * the current ESSID. This allows scan requests क्रम specअगरic ESSID
	 * without having to change the current ESSID and potentially अवरोधing
	 * the current association.
	 */
	__u8		essid[IW_ESSID_MAX_SIZE];

	/*
	 * Optional parameters क्रम changing the शेष scanning behavior.
	 * These are based on the MLME-SCAN.request from IEEE Std 802.11.
	 * TU is 1.024 ms. If these are set to 0, driver is expected to use
	 * reasonable शेष values. min_channel_समय defines the समय that
	 * will be used to रुको क्रम the first reply on each channel. If no
	 * replies are received, next channel will be scanned after this. If
	 * replies are received, total समय रुकोed on the channel is defined by
	 * max_channel_समय.
	 */
	__u32		min_channel_समय; /* in TU */
	__u32		max_channel_समय; /* in TU */

	काष्ठा iw_freq	channel_list[IW_MAX_FREQUENCIES];
पूर्ण;

/* ------------------------- WPA SUPPORT ------------------------- */

/*
 *	Extended data काष्ठाure क्रम get/set encoding (this is used with
 *	SIOCSIWENCODEEXT/SIOCGIWENCODEEXT. काष्ठा iw_poपूर्णांक and IW_ENCODE_*
 *	flags are used in the same way as with SIOCSIWENCODE/SIOCGIWENCODE and
 *	only the data contents changes (key data -> this काष्ठाure, including
 *	key data).
 *
 *	If the new key is the first group key, it will be set as the शेष
 *	TX key. Otherwise, शेष TX key index is only changed अगर
 *	IW_ENCODE_EXT_SET_TX_KEY flag is set.
 *
 *	Key will be changed with SIOCSIWENCODEEXT in all हालs except क्रम
 *	special "change TX key index" operation which is indicated by setting
 *	key_len = 0 and ext_flags |= IW_ENCODE_EXT_SET_TX_KEY.
 *
 *	tx_seq/rx_seq are only used when respective
 *	IW_ENCODE_EXT_अणुTX,RXपूर्ण_SEQ_VALID flag is set in ext_flags. Normal
 *	TKIP/CCMP operation is to set RX seq with SIOCSIWENCODEEXT and start
 *	TX seq from zero whenever key is changed. SIOCGIWENCODEEXT is normally
 *	used only by an Authenticator (AP or an IBSS station) to get the
 *	current TX sequence number. Using TX_SEQ_VALID क्रम SIOCSIWENCODEEXT and
 *	RX_SEQ_VALID क्रम SIOCGIWENCODEEXT are optional, but can be useful क्रम
 *	debugging/testing.
 */
काष्ठा iw_encode_ext अणु
	__u32		ext_flags; /* IW_ENCODE_EXT_* */
	__u8		tx_seq[IW_ENCODE_SEQ_MAX_SIZE]; /* LSB first */
	__u8		rx_seq[IW_ENCODE_SEQ_MAX_SIZE]; /* LSB first */
	काष्ठा sockaddr	addr; /* ff:ff:ff:ff:ff:ff क्रम broadcast/multicast
			       * (group) keys or unicast address क्रम
			       * inभागidual keys */
	__u16		alg; /* IW_ENCODE_ALG_* */
	__u16		key_len;
	__u8		key[0];
पूर्ण;

/* SIOCSIWMLME data */
काष्ठा iw_mlme अणु
	__u16		cmd; /* IW_MLME_* */
	__u16		reason_code;
	काष्ठा sockaddr	addr;
पूर्ण;

/* SIOCSIWPMKSA data */
#घोषणा IW_PMKSA_ADD		1
#घोषणा IW_PMKSA_REMOVE		2
#घोषणा IW_PMKSA_FLUSH		3

#घोषणा IW_PMKID_LEN	16

काष्ठा iw_pmksa अणु
	__u32		cmd; /* IW_PMKSA_* */
	काष्ठा sockaddr	bssid;
	__u8		pmkid[IW_PMKID_LEN];
पूर्ण;

/* IWEVMICHAELMICFAILURE data */
काष्ठा iw_michaelmicfailure अणु
	__u32		flags;
	काष्ठा sockaddr	src_addr;
	__u8		tsc[IW_ENCODE_SEQ_MAX_SIZE]; /* LSB first */
पूर्ण;

/* IWEVPMKIDCAND data */
#घोषणा IW_PMKID_CAND_PREAUTH	0x00000001 /* RNS pre-authentication enabled */
काष्ठा iw_pmkid_cand अणु
	__u32		flags; /* IW_PMKID_CAND_* */
	__u32		index; /* the smaller the index, the higher the
				* priority */
	काष्ठा sockaddr	bssid;
पूर्ण;

/* ------------------------ WIRELESS STATS ------------------------ */
/*
 * Wireless statistics (used क्रम /proc/net/wireless)
 */
काष्ठा iw_statistics अणु
	__u16		status;		/* Status
					 * - device dependent क्रम now */

	काष्ठा iw_quality	qual;		/* Quality of the link
						 * (instant/mean/max) */
	काष्ठा iw_discarded	discard;	/* Packet discarded counts */
	काष्ठा iw_missed	miss;		/* Packet missed counts */
पूर्ण;

/* ------------------------ IOCTL REQUEST ------------------------ */
/*
 * This काष्ठाure defines the payload of an ioctl, and is used
 * below.
 *
 * Note that this काष्ठाure should fit on the memory footprपूर्णांक
 * of iwreq (which is the same as अगरreq), which mean a max size of
 * 16 octets = 128 bits. Warning, poपूर्णांकers might be 64 bits wide...
 * You should check this when increasing the काष्ठाures defined
 * above in this file...
 */
जोड़ iwreq_data अणु
	/* Config - generic */
	अक्षर		name[IFNAMSIZ];
	/* Name : used to verअगरy the presence of  wireless extensions.
	 * Name of the protocol/provider... */

	काष्ठा iw_poपूर्णांक	essid;		/* Extended network name */
	काष्ठा iw_param	nwid;		/* network id (or करोमुख्य - the cell) */
	काष्ठा iw_freq	freq;		/* frequency or channel :
					 * 0-1000 = channel
					 * > 1000 = frequency in Hz */

	काष्ठा iw_param	sens;		/* संकेत level threshold */
	काष्ठा iw_param	bitrate;	/* शेष bit rate */
	काष्ठा iw_param	txघातer;	/* शेष transmit घातer */
	काष्ठा iw_param	rts;		/* RTS threshold */
	काष्ठा iw_param	frag;		/* Fragmentation threshold */
	__u32		mode;		/* Operation mode */
	काष्ठा iw_param	retry;		/* Retry limits & lअगरeसमय */

	काष्ठा iw_poपूर्णांक	encoding;	/* Encoding stuff : tokens */
	काष्ठा iw_param	घातer;		/* PM duration/समयout */
	काष्ठा iw_quality qual;		/* Quality part of statistics */

	काष्ठा sockaddr	ap_addr;	/* Access poपूर्णांक address */
	काष्ठा sockaddr	addr;		/* Destination address (hw/mac) */

	काष्ठा iw_param	param;		/* Other small parameters */
	काष्ठा iw_poपूर्णांक	data;		/* Other large parameters */
पूर्ण;

/*
 * The काष्ठाure to exchange data क्रम ioctl.
 * This काष्ठाure is the same as 'struct ifreq', but (re)defined क्रम
 * convenience...
 * Do I need to remind you about काष्ठाure size (32 octets) ?
 */
काष्ठा iwreq अणु
	जोड़
	अणु
		अक्षर	अगरrn_name[IFNAMSIZ];	/* अगर name, e.g. "eth0" */
	पूर्ण अगरr_अगरrn;

	/* Data part (defined just above) */
	जोड़ iwreq_data	u;
पूर्ण;

/* -------------------------- IOCTL DATA -------------------------- */
/*
 *	For those ioctl which want to exchange mode data that what could
 *	fit in the above काष्ठाure...
 */

/*
 *	Range of parameters
 */

काष्ठा iw_range अणु
	/* Inक्रमmative stuff (to choose between dअगरferent पूर्णांकerface) */
	__u32		throughput;	/* To give an idea... */
	/* In theory this value should be the maximum benchmarked
	 * TCP/IP throughput, because with most of these devices the
	 * bit rate is meaningless (overhead an co) to estimate how
	 * fast the connection will go and pick the fastest one.
	 * I suggest people to play with Netperf or any benchmark...
	 */

	/* NWID (or करोमुख्य id) */
	__u32		min_nwid;	/* Minimal NWID we are able to set */
	__u32		max_nwid;	/* Maximal NWID we are able to set */

	/* Old Frequency (backward compat - moved lower ) */
	__u16		old_num_channels;
	__u8		old_num_frequency;

	/* Scan capabilities */
	__u8		scan_capa; 	/* IW_SCAN_CAPA_* bit field */

	/* Wireless event capability biपंचांगasks */
	__u32		event_capa[6];

	/* संकेत level threshold range */
	__s32		sensitivity;

	/* Quality of link & SNR stuff */
	/* Quality range (link, level, noise)
	 * If the quality is असलolute, it will be in the range [0 ; max_qual],
	 * अगर the quality is dBm, it will be in the range [max_qual ; 0].
	 * Don't क्रमget that we use 8 bit arithmetics... */
	काष्ठा iw_quality	max_qual;	/* Quality of the link */
	/* This should contain the average/typical values of the quality
	 * indicator. This should be the threshold between a "good" and
	 * a "bad" link (example : monitor going from green to orange).
	 * Currently, user space apps like quality monitors करोn't have any
	 * way to calibrate the measurement. With this, they can split
	 * the range between 0 and max_qual in dअगरferent quality level
	 * (using a geometric subभागision centered on the average).
	 * I expect that people करोing the user space apps will feedback
	 * us on which value we need to put in each driver... */
	काष्ठा iw_quality	avg_qual;	/* Quality of the link */

	/* Rates */
	__u8		num_bitrates;	/* Number of entries in the list */
	__s32		bitrate[IW_MAX_BITRATES];	/* list, in bps */

	/* RTS threshold */
	__s32		min_rts;	/* Minimal RTS threshold */
	__s32		max_rts;	/* Maximal RTS threshold */

	/* Frag threshold */
	__s32		min_frag;	/* Minimal frag threshold */
	__s32		max_frag;	/* Maximal frag threshold */

	/* Power Management duration & समयout */
	__s32		min_pmp;	/* Minimal PM period */
	__s32		max_pmp;	/* Maximal PM period */
	__s32		min_pmt;	/* Minimal PM समयout */
	__s32		max_pmt;	/* Maximal PM समयout */
	__u16		pmp_flags;	/* How to decode max/min PM period */
	__u16		pmt_flags;	/* How to decode max/min PM समयout */
	__u16		pm_capa;	/* What PM options are supported */

	/* Encoder stuff */
	__u16	encoding_size[IW_MAX_ENCODING_SIZES];	/* Dअगरferent token sizes */
	__u8	num_encoding_sizes;	/* Number of entry in the list */
	__u8	max_encoding_tokens;	/* Max number of tokens */
	/* For drivers that need a "login/passwd" क्रमm */
	__u8	encoding_login_index;	/* token index क्रम login token */

	/* Transmit घातer */
	__u16		txघातer_capa;	/* What options are supported */
	__u8		num_txघातer;	/* Number of entries in the list */
	__s32		txघातer[IW_MAX_TXPOWER];	/* list, in bps */

	/* Wireless Extension version info */
	__u8		we_version_compiled;	/* Must be WIRELESS_EXT */
	__u8		we_version_source;	/* Last update of source */

	/* Retry limits and lअगरeसमय */
	__u16		retry_capa;	/* What retry options are supported */
	__u16		retry_flags;	/* How to decode max/min retry limit */
	__u16		r_समय_flags;	/* How to decode max/min retry lअगरe */
	__s32		min_retry;	/* Minimal number of retries */
	__s32		max_retry;	/* Maximal number of retries */
	__s32		min_r_समय;	/* Minimal retry lअगरeसमय */
	__s32		max_r_समय;	/* Maximal retry lअगरeसमय */

	/* Frequency */
	__u16		num_channels;	/* Number of channels [0; num - 1] */
	__u8		num_frequency;	/* Number of entry in the list */
	काष्ठा iw_freq	freq[IW_MAX_FREQUENCIES];	/* list */
	/* Note : this frequency list करोesn't need to fit channel numbers,
	 * because each entry contain its channel index */

	__u32		enc_capa;	/* IW_ENC_CAPA_* bit field */
पूर्ण;

/*
 * Private ioctl पूर्णांकerface inक्रमmation
 */

काष्ठा iw_priv_args अणु
	__u32		cmd;		/* Number of the ioctl to issue */
	__u16		set_args;	/* Type and number of args */
	__u16		get_args;	/* Type and number of args */
	अक्षर		name[IFNAMSIZ];	/* Name of the extension */
पूर्ण;

/* ----------------------- WIRELESS EVENTS ----------------------- */
/*
 * Wireless events are carried through the rtnetlink socket to user
 * space. They are encapsulated in the IFLA_WIRELESS field of
 * a RTM_NEWLINK message.
 */

/*
 * A Wireless Event. Contains basically the same data as the ioctl...
 */
काष्ठा iw_event अणु
	__u16		len;			/* Real length of this stuff */
	__u16		cmd;			/* Wireless IOCTL */
	जोड़ iwreq_data	u;		/* IOCTL fixed payload */
पूर्ण;

/* Size of the Event prefix (including padding and alignement junk) */
#घोषणा IW_EV_LCP_LEN	(माप(काष्ठा iw_event) - माप(जोड़ iwreq_data))
/* Size of the various events */
#घोषणा IW_EV_CHAR_LEN	(IW_EV_LCP_LEN + IFNAMSIZ)
#घोषणा IW_EV_UINT_LEN	(IW_EV_LCP_LEN + माप(__u32))
#घोषणा IW_EV_FREQ_LEN	(IW_EV_LCP_LEN + माप(काष्ठा iw_freq))
#घोषणा IW_EV_PARAM_LEN	(IW_EV_LCP_LEN + माप(काष्ठा iw_param))
#घोषणा IW_EV_ADDR_LEN	(IW_EV_LCP_LEN + माप(काष्ठा sockaddr))
#घोषणा IW_EV_QUAL_LEN	(IW_EV_LCP_LEN + माप(काष्ठा iw_quality))

/* iw_poपूर्णांक events are special. First, the payload (extra data) come at
 * the end of the event, so they are bigger than IW_EV_POINT_LEN. Second,
 * we omit the poपूर्णांकer, so start at an offset. */
#घोषणा IW_EV_POINT_OFF दुरत्व(काष्ठा iw_poपूर्णांक, length)
#घोषणा IW_EV_POINT_LEN	(IW_EV_LCP_LEN + माप(काष्ठा iw_poपूर्णांक) - \
			 IW_EV_POINT_OFF)


/* Size of the Event prefix when packed in stream */
#घोषणा IW_EV_LCP_PK_LEN	(4)
/* Size of the various events when packed in stream */
#घोषणा IW_EV_CHAR_PK_LEN	(IW_EV_LCP_PK_LEN + IFNAMSIZ)
#घोषणा IW_EV_UINT_PK_LEN	(IW_EV_LCP_PK_LEN + माप(__u32))
#घोषणा IW_EV_FREQ_PK_LEN	(IW_EV_LCP_PK_LEN + माप(काष्ठा iw_freq))
#घोषणा IW_EV_PARAM_PK_LEN	(IW_EV_LCP_PK_LEN + माप(काष्ठा iw_param))
#घोषणा IW_EV_ADDR_PK_LEN	(IW_EV_LCP_PK_LEN + माप(काष्ठा sockaddr))
#घोषणा IW_EV_QUAL_PK_LEN	(IW_EV_LCP_PK_LEN + माप(काष्ठा iw_quality))
#घोषणा IW_EV_POINT_PK_LEN	(IW_EV_LCP_PK_LEN + 4)

#पूर्ण_अगर /* _UAPI_LINUX_WIRELESS_H */
