<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -*- linux-c -*-
 * APM BIOS driver क्रम Linux
 * Copyright 1994-2001 Stephen Rothwell (sfr@canb.auug.org.au)
 *
 * Initial development of this driver was funded by NEC Australia P/L
 *	and NEC Corporation
 *
 * October 1995, Rik Faith (faith@cs.unc.edu):
 *    Minor enhancements and updates (to the patch set) क्रम 1.3.x
 *    Documentation
 * January 1996, Rik Faith (faith@cs.unc.edu):
 *    Make /proc/apm easy to क्रमmat (bump driver version)
 * March 1996, Rik Faith (faith@cs.unc.edu):
 *    Prohibit APM BIOS calls unless apm_enabled.
 *    (Thanks to Ulrich Windl <Ulrich.Windl@rz.uni-regensburg.de>)
 * April 1996, Stephen Rothwell (sfr@canb.auug.org.au)
 *    Version 1.0 and 1.1
 * May 1996, Version 1.2
 * Feb 1998, Version 1.3
 * Feb 1998, Version 1.4
 * Aug 1998, Version 1.5
 * Sep 1998, Version 1.6
 * Nov 1998, Version 1.7
 * Jan 1999, Version 1.8
 * Jan 1999, Version 1.9
 * Oct 1999, Version 1.10
 * Nov 1999, Version 1.11
 * Jan 2000, Version 1.12
 * Feb 2000, Version 1.13
 * Nov 2000, Version 1.14
 * Oct 2001, Version 1.15
 * Jan 2002, Version 1.16
 * Oct 2002, Version 1.16ac
 *
 * History:
 *    0.6b: first version in official kernel, Linux 1.3.46
 *    0.7: changed /proc/apm क्रमmat, Linux 1.3.58
 *    0.8: fixed gcc 2.7.[12] compilation problems, Linux 1.3.59
 *    0.9: only call bios अगर bios is present, Linux 1.3.72
 *    1.0: use fixed device number, consolidate /proc/apm पूर्णांकo this file,
 *         Linux 1.3.85
 *    1.1: support user-space standby and suspend, घातer off after प्रणाली
 *         halted, Linux 1.3.98
 *    1.2: When resetting RTC after resume, take care so that the समय
 *         is only incorrect by 30-60mS (vs. 1S previously) (Gabor J. Toth
 *         <jtoth@princeton.edu>); improve पूर्णांकeraction between
 *         screen-blanking and gpm (Stephen Rothwell); Linux 1.99.4
 *    1.2a:Simple change to stop mysterious bug reports with SMP also added
 *	   levels to the prपूर्णांकk calls. APM is not defined क्रम SMP machines.
 *         The new replacement क्रम it is, but Linux करोesn't yet support this.
 *         Alan Cox Linux 2.1.55
 *    1.3: Set up a valid data descriptor 0x40 क्रम buggy BIOS's
 *    1.4: Upgraded to support APM 1.2. Integrated ThinkPad suspend patch by
 *         Dean Gaudet <dgaudet@arctic.org>.
 *         C. Scott Ananian <cananian@alumni.princeton.edu> Linux 2.1.87
 *    1.5: Fix segment रेजिस्टर reloading (in हाल of bad segments saved
 *         across BIOS call).
 *         Stephen Rothwell
 *    1.6: Cope with compiler/assembler dअगरferences.
 *         Only try to turn off the first display device.
 *         Fix OOPS at घातer off with no APM BIOS by Jan Echternach
 *                   <echter@inक्रमmatik.uni-rostock.de>
 *         Stephen Rothwell
 *    1.7: Modअगरy driver's cached copy of the disabled/disengaged flags
 *         to reflect current state of APM BIOS.
 *         Chris Rankin <rankinc@bellsouth.net>
 *         Reset पूर्णांकerrupt 0 समयr to 100Hz after suspend
 *         Chad Miller <cmiller@surfsouth.com>
 *         Add CONFIG_APM_IGNORE_SUSPEND_BOUNCE
 *         Riअक्षरd Gooch <rgooch@atnf.csiro.au>
 *         Allow boot समय disabling of APM
 *         Make boot messages far less verbose by शेष
 *         Make यंत्र safer
 *         Stephen Rothwell
 *    1.8: Add CONFIG_APM_RTC_IS_GMT
 *         Riअक्षरd Gooch <rgooch@atnf.csiro.au>
 *         change APM_NOINTS to CONFIG_APM_ALLOW_INTS
 *         हटाओ dependency on CONFIG_PROC_FS
 *         Stephen Rothwell
 *    1.9: Fix small typo.  <laslo@wodip.opole.pl>
 *         Try to cope with BIOS's that need to have all display
 *         devices blanked and not just the first one.
 *         Ross Paterson <ross@soi.city.ac.uk>
 *         Fix segment limit setting it has always been wrong as
 *         the segments needed to have byte granularity.
 *         Mark a few things __init.
 *         Add hack to allow घातer off of SMP प्रणालीs by popular request.
 *         Use CONFIG_SMP instead of __SMP__
 *         Ignore BOUNCES क्रम three seconds.
 *         Stephen Rothwell
 *   1.10: Fix क्रम Thinkpad वापस code.
 *         Merge 2.2 and 2.3 drivers.
 *         Remove APM dependencies in arch/i386/kernel/process.c
 *         Remove APM dependencies in drivers/अक्षर/sysrq.c
 *         Reset समय across standby.
 *         Allow more initialisation on SMP.
 *         Remove CONFIG_APM_POWER_OFF and make it boot समय
 *         configurable (शेष on).
 *         Make debug only a boot समय parameter (हटाओ APM_DEBUG).
 *         Try to blank all devices on any error.
 *   1.11: Remove APM dependencies in drivers/अक्षर/console.c
 *         Check nr_running to detect अगर we are idle (from
 *         Borislav Deianov <borislav@lix.polytechnique.fr>)
 *         Fix क्रम bioses that करोn't zero the top part of the
 *         entrypoपूर्णांक offset (Mario Sitta <sitta@al.unipmn.it>)
 *         (reported by Panos Katsaloulis <teras@ग_लिखोme.com>).
 *         Real mode घातer off patch (Walter Hofmann
 *         <Walter.Hofmann@physik.stud.uni-erlangen.de>).
 *   1.12: Remove CONFIG_SMP as the compiler will optimize
 *         the code away anyway (smp_num_cpus == 1 in UP)
 *         noted by Artur Skawina <skawina@geocities.com>.
 *         Make घातer off under SMP work again.
 *         Fix thinko with initial engaging of BIOS.
 *         Make sure घातer off only happens on CPU 0
 *         (Paul "Rusty" Russell <rusty@rustcorp.com.au>).
 *         Do error notअगरication to user mode अगर BIOS calls fail.
 *         Move entrypoपूर्णांक offset fix to ...boot/setup.S
 *         where it beदीर्घs (Cosmos <gis88564@cis.nctu.edu.tw>).
 *         Remove smp-घातer-off. SMP users must now specअगरy
 *         "apm=power-off" on the kernel command line. Suggested
 *         by Jim Avera <jima@hal.com>, modअगरied by Alan Cox
 *         <alan@lxorguk.ukuu.org.uk>.
 *         Register the /proc/apm entry even on SMP so that
 *         scripts that check क्रम it beक्रमe करोing घातer off
 *         work (Jim Avera <jima@hal.com>).
 *   1.13: Changes क्रम new pm_ पूर्णांकerfaces (Andy Henroid
 *         <andy_henroid@yahoo.com>).
 *         Modularize the code.
 *         Fix the Thinkpad (again) :-( (CONFIG_APM_IGNORE_MULTIPLE_SUSPENDS
 *         is now the way lअगरe works).
 *         Fix thinko in suspend() (wrong वापस).
 *         Notअगरy drivers on critical suspend.
 *         Make kapmd असलorb more idle समय (Pavel Machek <pavel@ucw.cz>
 *         modअगरied by sfr).
 *         Disable पूर्णांकerrupts जबतक we are suspended (Andy Henroid
 *         <andy_henroid@yahoo.com> fixed by sfr).
 *         Make घातer off work on SMP again (Tony Hoyle
 *         <पंचांगh@magenta-logic.com> and <zlatko@iskon.hr>) modअगरied by sfr.
 *         Remove CONFIG_APM_SUSPEND_BOUNCE.  The bounce ignore
 *         पूर्णांकerval is now configurable.
 *   1.14: Make connection version persist across module unload/load.
 *         Enable and engage घातer management earlier.
 *         Disengage घातer management on module unload.
 *         Changed to use the sysrq-रेजिस्टर hack क्रम रेजिस्टरing the
 *         घातer off function called by magic sysrq based upon discussions
 *         in irc://irc.खोलोprojects.net/#kernelnewbies
 *         (Crutcher Dunnavant <crutcher+kernel@datastacks.com>).
 *         Make CONFIG_APM_REAL_MODE_POWER_OFF run समय configurable.
 *         (Arjan van de Ven <arjanv@redhat.com>) modअगरied by sfr.
 *         Work around byte swap bug in one of the Vaio's BIOS's
 *         (Marc Boucher <marc@mbsi.ca>).
 *         Exposed the disable flag to dmi so that we can handle known
 *         broken APM (Alan Cox <alan@lxorguk.ukuu.org.uk>).
 *   1.14ac: If the BIOS says "I slowed the CPU down" then करोn't spin
 *         calling it - instead idle. (Alan Cox <alan@lxorguk.ukuu.org.uk>)
 *         If an APM idle fails log it and idle sensibly
 *   1.15: Don't queue events to clients who खोलो the device O_WRONLY.
 *         Don't expect replies from clients who खोलो the device O_RDONLY.
 *         (Idea from Thomas Hood)
 *         Minor रुकोqueue cleanups. (John Fremlin <chief@bandits.org>)
 *   1.16: Fix idle calling. (Andreas Steinmetz <ast@करोmdv.de> et al.)
 *         Notअगरy listeners of standby or suspend events beक्रमe notअगरying
 *         drivers. Return EBUSY to ioctl() अगर suspend is rejected.
 *         (Russell King <rmk@arm.linux.org.uk> and Thomas Hood)
 *         Ignore first resume after we generate our own resume event
 *         after a suspend (Thomas Hood)
 *         Daemonize now माला_लो rid of our controlling terminal (sfr).
 *         CONFIG_APM_CPU_IDLE now just affects the शेष value of
 *         idle_threshold (sfr).
 *         Change name of kernel apm daemon (as it no दीर्घer idles) (sfr).
 *   1.16ac: Fix up SMP support somewhat. You can now क्रमce SMP on and we
 *	   make _all_ APM calls on the CPU#0. Fix unsafe sign bug.
 *	   TODO: determine अगर its "boot CPU" or "CPU0" we want to lock to.
 *
 * APM 1.1 Reference:
 *
 *   Intel Corporation, Microsoft Corporation. Advanced Power Management
 *   (APM) BIOS Interface Specअगरication, Revision 1.1, September 1993.
 *   Intel Order Number 241704-001.  Microsoft Part Number 781-110-X01.
 *
 * [This करोcument is available मुक्त from Intel by calling 800.628.8686 (fax
 * 916.356.6100) or 800.548.4725; or from
 * http://www.microsoft.com/whdc/archive/amp_12.mspx  It is also
 * available from Microsoft by calling 206.882.8080.]
 *
 * APM 1.2 Reference:
 *   Intel Corporation, Microsoft Corporation. Advanced Power Management
 *   (APM) BIOS Interface Specअगरication, Revision 1.2, February 1996.
 *
 * [This करोcument is available from Microsoft at:
 *    http://www.microsoft.com/whdc/archive/amp_12.mspx]
 */

#घोषणा pr_fmt(fmt) "apm: " fmt

#समावेश <linux/module.h>

#समावेश <linux/poll.h>
#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/समयr.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/apm_मूलप्रण.स>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/pm.h>
#समावेश <linux/capability.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/smp.h>
#समावेश <linux/dmi.h>
#समावेश <linux/suspend.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/acpi.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/i8253.h>
#समावेश <linux/cpuidle.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/olpc.h>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/nospec-branch.h>

#अगर defined(CONFIG_APM_DISPLAY_BLANK) && defined(CONFIG_VT)
बाह्य पूर्णांक (*console_blank_hook)(पूर्णांक);
#पूर्ण_अगर

/*
 * The apm_bios device is one of the misc अक्षर devices.
 * This is its minor number.
 */
#घोषणा	APM_MINOR_DEV	134

/*
 * Various options can be changed at boot समय as follows:
 * (We allow underscores क्रम compatibility with the modules code)
 *	apm=on/off			enable/disable APM
 *	    [no-]allow[-_]पूर्णांकs		allow पूर्णांकerrupts during BIOS calls
 *	    [no-]broken[-_]psr		BIOS has a broken GetPowerStatus call
 *	    [no-]realmode[-_]घातer[-_]off	चयन to real mode beक्रमe
 *	    					घातering off
 *	    [no-]debug			log some debugging messages
 *	    [no-]घातer[-_]off		घातer off on shutकरोwn
 *	    [no-]smp			Use apm even on an SMP box
 *	    bounce[-_]पूर्णांकerval=<n>	number of ticks to ignore suspend
 *	    				bounces
 *          idle[-_]threshold=<n>       System idle percentage above which to
 *                                      make APM BIOS idle calls. Set it to
 *                                      100 to disable.
 *          idle[-_]period=<n>          Period (in 1/100s of a second) over
 *                                      which the idle percentage is
 *                                      calculated.
 */

/* KNOWN PROBLEM MACHINES:
 *
 * U: TI 4000M TravelMate: BIOS is *NOT* APM compliant
 *                         [Confirmed by TI representative]
 * ?: ACER 486DX4/75: uses dseg 0040, in violation of APM specअगरication
 *                    [Confirmed by BIOS disassembly]
 *                    [This may work now ...]
 * P: Toshiba 1950S: battery lअगरe inक्रमmation only माला_लो updated after resume
 * P: Midwest Micro Soundbook Elite DX2/66 monochrome: screen blanking
 * 	broken in BIOS [Reported by Garst R. Reese <reese@isn.net>]
 * ?: AcerNote-950: oops on पढ़ोing /proc/apm - workaround is a WIP
 * 	Neale Banks <neale@lowendale.com.au> December 2000
 *
 * Legend: U = unusable with APM patches
 *         P = partially usable with APM patches
 */

/*
 * Define as 1 to make the driver always call the APM BIOS busy
 * routine even अगर the घड़ी was not reported as slowed by the
 * idle routine.  Otherwise, define as 0.
 */
#घोषणा ALWAYS_CALL_BUSY   1

/*
 * Define to make the APM BIOS calls zero all data segment रेजिस्टरs (so
 * that an incorrect BIOS implementation will cause a kernel panic अगर it
 * tries to ग_लिखो to arbitrary memory).
 */
#घोषणा APM_ZERO_SEGS

#समावेश <यंत्र/apm.h>

/*
 * Define to re-initialize the पूर्णांकerrupt 0 समयr to 100 Hz after a suspend.
 * This patched by Chad Miller <cmiller@surfsouth.com>, original code by
 * David Chen <chen@ctpa04.mit.edu>
 */
#अघोषित INIT_TIMER_AFTER_SUSPEND

#अगर_घोषित INIT_TIMER_AFTER_SUSPEND
#समावेश <linux/समयx.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/delay.h>
#पूर्ण_अगर

/*
 * Need to poll the APM BIOS every second
 */
#घोषणा APM_CHECK_TIMEOUT	(HZ)

/*
 * Ignore suspend events क्रम this amount of समय after a resume
 */
#घोषणा DEFAULT_BOUNCE_INTERVAL	(3 * HZ)

/*
 * Maximum number of events stored
 */
#घोषणा APM_MAX_EVENTS		20

/*
 * The per-file APM data
 */
काष्ठा apm_user अणु
	पूर्णांक		magic;
	काष्ठा apm_user *next;
	अचिन्हित पूर्णांक	suser: 1;
	अचिन्हित पूर्णांक	ग_लिखोr: 1;
	अचिन्हित पूर्णांक	पढ़ोer: 1;
	अचिन्हित पूर्णांक	suspend_रुको: 1;
	पूर्णांक		suspend_result;
	पूर्णांक		suspends_pending;
	पूर्णांक		standbys_pending;
	पूर्णांक		suspends_पढ़ो;
	पूर्णांक		standbys_पढ़ो;
	पूर्णांक		event_head;
	पूर्णांक		event_tail;
	apm_event_t	events[APM_MAX_EVENTS];
पूर्ण;

/*
 * The magic number in apm_user
 */
#घोषणा APM_BIOS_MAGIC		0x4101

/*
 * idle percentage above which bios idle calls are करोne
 */
#अगर_घोषित CONFIG_APM_CPU_IDLE
#घोषणा DEFAULT_IDLE_THRESHOLD	95
#अन्यथा
#घोषणा DEFAULT_IDLE_THRESHOLD	100
#पूर्ण_अगर
#घोषणा DEFAULT_IDLE_PERIOD	(100 / 3)

अटल पूर्णांक apm_cpu_idle(काष्ठा cpuidle_device *dev,
			काष्ठा cpuidle_driver *drv, पूर्णांक index);

अटल काष्ठा cpuidle_driver apm_idle_driver = अणु
	.name = "apm_idle",
	.owner = THIS_MODULE,
	.states = अणु
		अणु /* entry 0 is क्रम polling */ पूर्ण,
		अणु /* entry 1 is क्रम APM idle */
			.name = "APM",
			.desc = "APM idle",
			.निकास_latency = 250,	/* WAG */
			.target_residency = 500,	/* WAG */
			.enter = &apm_cpu_idle
		पूर्ण,
	पूर्ण,
	.state_count = 2,
पूर्ण;

अटल काष्ठा cpuidle_device apm_cpuidle_device;

/*
 * Local variables
 */
__visible काष्ठा अणु
	अचिन्हित दीर्घ	offset;
	अचिन्हित लघु	segment;
पूर्ण apm_bios_entry;
अटल पूर्णांक घड़ी_slowed;
अटल पूर्णांक idle_threshold __पढ़ो_mostly = DEFAULT_IDLE_THRESHOLD;
अटल पूर्णांक idle_period __पढ़ो_mostly = DEFAULT_IDLE_PERIOD;
अटल पूर्णांक suspends_pending;
अटल पूर्णांक standbys_pending;
अटल पूर्णांक ignore_sys_suspend;
अटल पूर्णांक ignore_normal_resume;
अटल पूर्णांक bounce_पूर्णांकerval __पढ़ो_mostly = DEFAULT_BOUNCE_INTERVAL;

अटल bool debug __पढ़ो_mostly;
अटल bool smp __पढ़ो_mostly;
अटल पूर्णांक apm_disabled = -1;
#अगर_घोषित CONFIG_SMP
अटल bool घातer_off;
#अन्यथा
अटल bool घातer_off = 1;
#पूर्ण_अगर
अटल bool realmode_घातer_off;
#अगर_घोषित CONFIG_APM_ALLOW_INTS
अटल bool allow_पूर्णांकs = 1;
#अन्यथा
अटल bool allow_पूर्णांकs;
#पूर्ण_अगर
अटल bool broken_psr;

अटल DECLARE_WAIT_QUEUE_HEAD(apm_रुकोqueue);
अटल DECLARE_WAIT_QUEUE_HEAD(apm_suspend_रुकोqueue);
अटल काष्ठा apm_user *user_list;
अटल DEFINE_SPINLOCK(user_list_lock);
अटल DEFINE_MUTEX(apm_mutex);

/*
 * Set up a segment that references the real mode segment 0x40
 * that extends up to the end of page zero (that we have reserved).
 * This is क्रम buggy BIOS's that refer to (real mode) segment 0x40
 * even though they are called in रक्षित mode.
 */
अटल काष्ठा desc_काष्ठा bad_bios_desc = GDT_ENTRY_INIT(0x4092,
			(अचिन्हित दीर्घ)__va(0x400UL), PAGE_SIZE - 0x400 - 1);

अटल स्थिर अक्षर driver_version[] = "1.16ac";	/* no spaces */

अटल काष्ठा task_काष्ठा *kapmd_task;

/*
 *	APM event names taken from the APM 1.2 specअगरication. These are
 *	the message codes that the BIOS uses to tell us about events
 */
अटल स्थिर अक्षर * स्थिर apm_event_name[] = अणु
	"system standby",
	"system suspend",
	"normal resume",
	"critical resume",
	"low battery",
	"power status change",
	"update time",
	"critical suspend",
	"user standby",
	"user suspend",
	"system standby resume",
	"capabilities change"
पूर्ण;
#घोषणा NR_APM_EVENT_NAME ARRAY_SIZE(apm_event_name)

प्रकार काष्ठा lookup_t अणु
	पूर्णांक	key;
	अक्षर 	*msg;
पूर्ण lookup_t;

/*
 *	The BIOS वापसs a set of standard error codes in AX when the
 *	carry flag is set.
 */

अटल स्थिर lookup_t error_table[] = अणु
/* N/A	अणु APM_SUCCESS,		"Operation succeeded" पूर्ण, */
	अणु APM_DISABLED,		"Power management disabled" पूर्ण,
	अणु APM_CONNECTED,	"Real mode interface already connected" पूर्ण,
	अणु APM_NOT_CONNECTED,	"Interface not connected" पूर्ण,
	अणु APM_16_CONNECTED,	"16 bit interface already connected" पूर्ण,
/* N/A	अणु APM_16_UNSUPPORTED,	"16 bit interface not supported" पूर्ण, */
	अणु APM_32_CONNECTED,	"32 bit interface already connected" पूर्ण,
	अणु APM_32_UNSUPPORTED,	"32 bit interface not supported" पूर्ण,
	अणु APM_BAD_DEVICE,	"Unrecognized device ID" पूर्ण,
	अणु APM_BAD_PARAM,	"Parameter out of range" पूर्ण,
	अणु APM_NOT_ENGAGED,	"Interface not engaged" पूर्ण,
	अणु APM_BAD_FUNCTION,     "Function not supported" पूर्ण,
	अणु APM_RESUME_DISABLED,	"Resume timer disabled" पूर्ण,
	अणु APM_BAD_STATE,	"Unable to enter requested state" पूर्ण,
/* N/A	अणु APM_NO_EVENTS,	"No events pending" पूर्ण, */
	अणु APM_NO_ERROR,		"BIOS did not set a return code" पूर्ण,
	अणु APM_NOT_PRESENT,	"No APM present" पूर्ण
पूर्ण;
#घोषणा ERROR_COUNT	ARRAY_SIZE(error_table)

/**
 *	apm_error	-	display an APM error
 *	@str: inक्रमmation string
 *	@err: APM BIOS वापस code
 *
 *	Write a meaningful log entry to the kernel log in the event of
 *	an APM error.  Note that this also handles (negative) kernel errors.
 */

अटल व्योम apm_error(अक्षर *str, पूर्णांक err)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ERROR_COUNT; i++)
		अगर (error_table[i].key == err)
			अवरोध;
	अगर (i < ERROR_COUNT)
		pr_notice("%s: %s\n", str, error_table[i].msg);
	अन्यथा अगर (err < 0)
		pr_notice("%s: linux error code %i\n", str, err);
	अन्यथा
		pr_notice("%s: unknown error code %#2.2x\n",
		       str, err);
पूर्ण

/*
 * These are the actual BIOS calls.  Depending on APM_ZERO_SEGS and
 * apm_info.allow_पूर्णांकs, we are being really paranoid here!  Not only
 * are पूर्णांकerrupts disabled, but all the segment रेजिस्टरs (except SS)
 * are saved and zeroed this means that अगर the BIOS tries to reference
 * any data without explicitly loading the segment रेजिस्टरs, the kernel
 * will fault immediately rather than have some unक्रमeseen circumstances
 * क्रम the rest of the kernel.  And it will be very obvious!  :-) Doing
 * this depends on CS referring to the same physical memory as DS so that
 * DS can be zeroed beक्रमe the call. Unक्रमtunately, we can't करो anything
 * about the stack segment/poपूर्णांकer.  Also, we tell the compiler that
 * everything could change.
 *
 * Also, we KNOW that क्रम the non error हाल of apm_bios_call, there
 * is no useful data वापसed in the low order 8 bits of eax.
 */

अटल अंतरभूत अचिन्हित दीर्घ __apm_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	local_save_flags(flags);
	अगर (apm_info.allow_पूर्णांकs) अणु
		अगर (irqs_disabled_flags(flags))
			local_irq_enable();
	पूर्ण अन्यथा
		local_irq_disable();

	वापस flags;
पूर्ण

#घोषणा apm_irq_save(flags) \
	करो अणु flags = __apm_irq_save(); पूर्ण जबतक (0)

अटल अंतरभूत व्योम apm_irq_restore(अचिन्हित दीर्घ flags)
अणु
	अगर (irqs_disabled_flags(flags))
		local_irq_disable();
	अन्यथा अगर (irqs_disabled())
		local_irq_enable();
पूर्ण

#अगर_घोषित APM_ZERO_SEGS
#	define APM_DECL_SEGS \
		अचिन्हित पूर्णांक saved_fs; अचिन्हित पूर्णांक saved_gs;
#	define APM_DO_SAVE_SEGS \
		savesegment(fs, saved_fs); savesegment(gs, saved_gs)
#	define APM_DO_RESTORE_SEGS \
		loadsegment(fs, saved_fs); loadsegment(gs, saved_gs)
#अन्यथा
#	define APM_DECL_SEGS
#	define APM_DO_SAVE_SEGS
#	define APM_DO_RESTORE_SEGS
#पूर्ण_अगर

काष्ठा apm_bios_call अणु
	u32 func;
	/* In and out */
	u32 ebx;
	u32 ecx;
	/* Out only */
	u32 eax;
	u32 edx;
	u32 esi;

	/* Error: -ENOMEM, or bits 8-15 of eax */
	पूर्णांक err;
पूर्ण;

/**
 *	__apm_bios_call - Make an APM BIOS 32bit call
 *	@_call: poपूर्णांकer to काष्ठा apm_bios_call.
 *
 *	Make an APM call using the 32bit रक्षित mode पूर्णांकerface. The
 *	caller is responsible क्रम knowing अगर APM BIOS is configured and
 *	enabled. This call can disable पूर्णांकerrupts क्रम a दीर्घ period of
 *	समय on some laptops.  The वापस value is in AH and the carry
 *	flag is loaded पूर्णांकo AL.  If there is an error, then the error
 *	code is वापसed in AH (bits 8-15 of eax) and this function
 *	वापसs non-zero.
 *
 *	Note: this makes the call on the current CPU.
 */
अटल दीर्घ __apm_bios_call(व्योम *_call)
अणु
	APM_DECL_SEGS
	अचिन्हित दीर्घ		flags;
	पूर्णांक			cpu;
	काष्ठा desc_काष्ठा	save_desc_40;
	काष्ठा desc_काष्ठा	*gdt;
	काष्ठा apm_bios_call	*call = _call;

	cpu = get_cpu();
	BUG_ON(cpu != 0);
	gdt = get_cpu_gdt_rw(cpu);
	save_desc_40 = gdt[0x40 / 8];
	gdt[0x40 / 8] = bad_bios_desc;

	apm_irq_save(flags);
	firmware_restrict_branch_speculation_start();
	APM_DO_SAVE_SEGS;
	apm_bios_call_यंत्र(call->func, call->ebx, call->ecx,
			  &call->eax, &call->ebx, &call->ecx, &call->edx,
			  &call->esi);
	APM_DO_RESTORE_SEGS;
	firmware_restrict_branch_speculation_end();
	apm_irq_restore(flags);
	gdt[0x40 / 8] = save_desc_40;
	put_cpu();

	वापस call->eax & 0xff;
पूर्ण

/* Run __apm_bios_call or __apm_bios_call_simple on CPU 0 */
अटल पूर्णांक on_cpu0(दीर्घ (*fn)(व्योम *), काष्ठा apm_bios_call *call)
अणु
	पूर्णांक ret;

	/* Don't bother with work_on_cpu in the common case, so we don't
	 * have to worry about OOM or overhead. */
	अगर (get_cpu() == 0) अणु
		ret = fn(call);
		put_cpu();
	पूर्ण अन्यथा अणु
		put_cpu();
		ret = work_on_cpu(0, fn, call);
	पूर्ण

	/* work_on_cpu can fail with -ENOMEM */
	अगर (ret < 0)
		call->err = ret;
	अन्यथा
		call->err = (call->eax >> 8) & 0xff;

	वापस ret;
पूर्ण

/**
 *	apm_bios_call	-	Make an APM BIOS 32bit call (on CPU 0)
 *	@call: the apm_bios_call रेजिस्टरs.
 *
 *	If there is an error, it is वापसed in @call.err.
 */
अटल पूर्णांक apm_bios_call(काष्ठा apm_bios_call *call)
अणु
	वापस on_cpu0(__apm_bios_call, call);
पूर्ण

/**
 *	__apm_bios_call_simple - Make an APM BIOS 32bit call (on CPU 0)
 *	@_call: poपूर्णांकer to काष्ठा apm_bios_call.
 *
 *	Make a BIOS call that वापसs one value only, or just status.
 *	If there is an error, then the error code is वापसed in AH
 *	(bits 8-15 of eax) and this function वापसs non-zero (it can
 *	also वापस -ENOMEM). This is used क्रम simpler BIOS operations.
 *	This call may hold पूर्णांकerrupts off क्रम a दीर्घ समय on some laptops.
 *
 *	Note: this makes the call on the current CPU.
 */
अटल दीर्घ __apm_bios_call_simple(व्योम *_call)
अणु
	u8			error;
	APM_DECL_SEGS
	अचिन्हित दीर्घ		flags;
	पूर्णांक			cpu;
	काष्ठा desc_काष्ठा	save_desc_40;
	काष्ठा desc_काष्ठा	*gdt;
	काष्ठा apm_bios_call	*call = _call;

	cpu = get_cpu();
	BUG_ON(cpu != 0);
	gdt = get_cpu_gdt_rw(cpu);
	save_desc_40 = gdt[0x40 / 8];
	gdt[0x40 / 8] = bad_bios_desc;

	apm_irq_save(flags);
	firmware_restrict_branch_speculation_start();
	APM_DO_SAVE_SEGS;
	error = apm_bios_call_simple_यंत्र(call->func, call->ebx, call->ecx,
					 &call->eax);
	APM_DO_RESTORE_SEGS;
	firmware_restrict_branch_speculation_end();
	apm_irq_restore(flags);
	gdt[0x40 / 8] = save_desc_40;
	put_cpu();
	वापस error;
पूर्ण

/**
 *	apm_bios_call_simple	-	make a simple APM BIOS 32bit call
 *	@func: APM function to invoke
 *	@ebx_in: EBX रेजिस्टर value क्रम BIOS call
 *	@ecx_in: ECX रेजिस्टर value क्रम BIOS call
 *	@eax: EAX रेजिस्टर on वापस from the BIOS call
 *	@err: bits
 *
 *	Make a BIOS call that वापसs one value only, or just status.
 *	If there is an error, then the error code is वापसed in @err
 *	and this function वापसs non-zero. This is used क्रम simpler
 *	BIOS operations.  This call may hold पूर्णांकerrupts off क्रम a दीर्घ
 *	समय on some laptops.
 */
अटल पूर्णांक apm_bios_call_simple(u32 func, u32 ebx_in, u32 ecx_in, u32 *eax,
				पूर्णांक *err)
अणु
	काष्ठा apm_bios_call call;
	पूर्णांक ret;

	call.func = func;
	call.ebx = ebx_in;
	call.ecx = ecx_in;

	ret = on_cpu0(__apm_bios_call_simple, &call);
	*eax = call.eax;
	*err = call.err;
	वापस ret;
पूर्ण

/**
 *	apm_driver_version	-	APM driver version
 *	@val:	loaded with the APM version on वापस
 *
 *	Retrieve the APM version supported by the BIOS. This is only
 *	supported क्रम APM 1.1 or higher. An error indicates APM 1.0 is
 *	probably present.
 *
 *	On entry val should poपूर्णांक to a value indicating the APM driver
 *	version with the high byte being the major and the low byte the
 *	minor number both in BCD
 *
 *	On वापस it will hold the BIOS revision supported in the
 *	same क्रमmat.
 */

अटल पूर्णांक apm_driver_version(u_लघु *val)
अणु
	u32 eax;
	पूर्णांक err;

	अगर (apm_bios_call_simple(APM_FUNC_VERSION, 0, *val, &eax, &err))
		वापस err;
	*val = eax;
	वापस APM_SUCCESS;
पूर्ण

/**
 *	apm_get_event	-	get an APM event from the BIOS
 *	@event: poपूर्णांकer to the event
 *	@info: poपूर्णांक to the event inक्रमmation
 *
 *	The APM BIOS provides a polled inक्रमmation क्रम event
 *	reporting. The BIOS expects to be polled at least every second
 *	when events are pending. When a message is found the caller should
 *	poll until no more messages are present.  However, this causes
 *	problems on some laptops where a suspend event notअगरication is
 *	not cleared until it is acknowledged.
 *
 *	Additional inक्रमmation is वापसed in the info poपूर्णांकer, providing
 *	that APM 1.2 is in use. If no messages are pending the value 0x80
 *	is वापसed (No घातer management events pending).
 */
अटल पूर्णांक apm_get_event(apm_event_t *event, apm_eventinfo_t *info)
अणु
	काष्ठा apm_bios_call call;

	call.func = APM_FUNC_GET_EVENT;
	call.ebx = call.ecx = 0;

	अगर (apm_bios_call(&call))
		वापस call.err;

	*event = call.ebx;
	अगर (apm_info.connection_version < 0x0102)
		*info = ~0; /* indicate info not valid */
	अन्यथा
		*info = call.ecx;
	वापस APM_SUCCESS;
पूर्ण

/**
 *	set_घातer_state	-	set the घातer management state
 *	@what: which items to transition
 *	@state: state to transition to
 *
 *	Request an APM change of state क्रम one or more प्रणाली devices. The
 *	processor state must be transitioned last of all. what holds the
 *	class of device in the upper byte and the device number (0xFF क्रम
 *	all) क्रम the object to be transitioned.
 *
 *	The state holds the state to transition to, which may in fact
 *	be an acceptance of a BIOS requested state change.
 */

अटल पूर्णांक set_घातer_state(u_लघु what, u_लघु state)
अणु
	u32 eax;
	पूर्णांक err;

	अगर (apm_bios_call_simple(APM_FUNC_SET_STATE, what, state, &eax, &err))
		वापस err;
	वापस APM_SUCCESS;
पूर्ण

/**
 *	set_प्रणाली_घातer_state - set प्रणाली wide घातer state
 *	@state: which state to enter
 *
 *	Transition the entire प्रणाली पूर्णांकo a new APM घातer state.
 */

अटल पूर्णांक set_प्रणाली_घातer_state(u_लघु state)
अणु
	वापस set_घातer_state(APM_DEVICE_ALL, state);
पूर्ण

/**
 *	apm_करो_idle	-	perक्रमm घातer saving
 *
 *	This function notअगरies the BIOS that the processor is (in the view
 *	of the OS) idle. It वापसs -1 in the event that the BIOS refuses
 *	to handle the idle request. On a success the function वापसs 1
 *	अगर the BIOS did घड़ी slowing or 0 otherwise.
 */

अटल पूर्णांक apm_करो_idle(व्योम)
अणु
	u32 eax;
	u8 ret = 0;
	पूर्णांक idled = 0;
	पूर्णांक err = 0;

	अगर (!need_resched()) अणु
		idled = 1;
		ret = apm_bios_call_simple(APM_FUNC_IDLE, 0, 0, &eax, &err);
	पूर्ण

	अगर (!idled)
		वापस 0;

	अगर (ret) अणु
		अटल अचिन्हित दीर्घ t;

		/* This always fails on some SMP boards running UP kernels.
		 * Only report the failure the first 5 बार.
		 */
		अगर (++t < 5) अणु
			prपूर्णांकk(KERN_DEBUG "apm_do_idle failed (%d)\n", err);
			t = jअगरfies;
		पूर्ण
		वापस -1;
	पूर्ण
	घड़ी_slowed = (apm_info.bios.flags & APM_IDLE_SLOWS_CLOCK) != 0;
	वापस घड़ी_slowed;
पूर्ण

/**
 *	apm_करो_busy	-	inक्रमm the BIOS the CPU is busy
 *
 *	Request that the BIOS brings the CPU back to full perक्रमmance.
 */

अटल व्योम apm_करो_busy(व्योम)
अणु
	u32 dummy;
	पूर्णांक err;

	अगर (घड़ी_slowed || ALWAYS_CALL_BUSY) अणु
		(व्योम)apm_bios_call_simple(APM_FUNC_BUSY, 0, 0, &dummy, &err);
		घड़ी_slowed = 0;
	पूर्ण
पूर्ण

/*
 * If no process has really been पूर्णांकerested in
 * the CPU क्रम some समय, we want to call BIOS
 * घातer management - we probably want
 * to conserve घातer.
 */
#घोषणा IDLE_CALC_LIMIT	(HZ * 100)
#घोषणा IDLE_LEAKY_MAX	16

/**
 * apm_cpu_idle		-	cpu idling क्रम APM capable Linux
 *
 * This is the idling function the kernel executes when APM is available. It
 * tries to करो BIOS घातermanagement based on the average प्रणाली idle समय.
 * Furthermore it calls the प्रणाली शेष idle routine.
 */

अटल पूर्णांक apm_cpu_idle(काष्ठा cpuidle_device *dev,
	काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	अटल पूर्णांक use_apm_idle; /* = 0 */
	अटल अचिन्हित पूर्णांक last_jअगरfies; /* = 0 */
	अटल u64 last_sसमय; /* = 0 */
	u64 sसमय, uसमय;

	पूर्णांक apm_idle_करोne = 0;
	अचिन्हित पूर्णांक jअगरfies_since_last_check = jअगरfies - last_jअगरfies;
	अचिन्हित पूर्णांक bucket;

recalc:
	task_cpuसमय(current, &uसमय, &sसमय);
	अगर (jअगरfies_since_last_check > IDLE_CALC_LIMIT) अणु
		use_apm_idle = 0;
	पूर्ण अन्यथा अगर (jअगरfies_since_last_check > idle_period) अणु
		अचिन्हित पूर्णांक idle_percentage;

		idle_percentage = nsecs_to_jअगरfies(sसमय - last_sसमय);
		idle_percentage *= 100;
		idle_percentage /= jअगरfies_since_last_check;
		use_apm_idle = (idle_percentage > idle_threshold);
		अगर (apm_info.क्रमbid_idle)
			use_apm_idle = 0;
	पूर्ण

	last_jअगरfies = jअगरfies;
	last_sसमय = sसमय;

	bucket = IDLE_LEAKY_MAX;

	जबतक (!need_resched()) अणु
		अगर (use_apm_idle) अणु
			अचिन्हित पूर्णांक t;

			t = jअगरfies;
			चयन (apm_करो_idle()) अणु
			हाल 0:
				apm_idle_करोne = 1;
				अगर (t != jअगरfies) अणु
					अगर (bucket) अणु
						bucket = IDLE_LEAKY_MAX;
						जारी;
					पूर्ण
				पूर्ण अन्यथा अगर (bucket) अणु
					bucket--;
					जारी;
				पूर्ण
				अवरोध;
			हाल 1:
				apm_idle_करोne = 1;
				अवरोध;
			शेष: /* BIOS refused */
				अवरोध;
			पूर्ण
		पूर्ण
		शेष_idle();
		local_irq_disable();
		jअगरfies_since_last_check = jअगरfies - last_jअगरfies;
		अगर (jअगरfies_since_last_check > idle_period)
			जाओ recalc;
	पूर्ण

	अगर (apm_idle_करोne)
		apm_करो_busy();

	वापस index;
पूर्ण

/**
 *	apm_घातer_off	-	ask the BIOS to घातer off
 *
 *	Handle the घातer off sequence. This is the one piece of code we
 *	will execute even on SMP machines. In order to deal with BIOS
 *	bugs we support real mode APM BIOS घातer off calls. We also make
 *	the SMP call on CPU0 as some प्रणालीs will only honour this call
 *	on their first cpu.
 */

अटल व्योम apm_घातer_off(व्योम)
अणु
	/* Some bioses करोn't like being called from CPU != 0 */
	अगर (apm_info.realmode_घातer_off) अणु
		set_cpus_allowed_ptr(current, cpumask_of(0));
		machine_real_restart(MRR_APM);
	पूर्ण अन्यथा अणु
		(व्योम)set_प्रणाली_घातer_state(APM_STATE_OFF);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_APM_DO_ENABLE

/**
 *	apm_enable_घातer_management - enable BIOS APM घातer management
 *	@enable: enable yes/no
 *
 *	Enable or disable the APM BIOS घातer services.
 */

अटल पूर्णांक apm_enable_घातer_management(पूर्णांक enable)
अणु
	u32 eax;
	पूर्णांक err;

	अगर ((enable == 0) && (apm_info.bios.flags & APM_BIOS_DISENGAGED))
		वापस APM_NOT_ENGAGED;
	अगर (apm_bios_call_simple(APM_FUNC_ENABLE_PM, APM_DEVICE_BALL,
				 enable, &eax, &err))
		वापस err;
	अगर (enable)
		apm_info.bios.flags &= ~APM_BIOS_DISABLED;
	अन्यथा
		apm_info.bios.flags |= APM_BIOS_DISABLED;
	वापस APM_SUCCESS;
पूर्ण
#पूर्ण_अगर

/**
 *	apm_get_घातer_status	-	get current घातer state
 *	@status: वापसed status
 *	@bat: battery info
 *	@lअगरe: estimated lअगरe
 *
 *	Obtain the current घातer status from the APM BIOS. We वापस a
 *	status which gives the rough battery status, and current घातer
 *	source. The bat value वापसed give an estimate as a percentage
 *	of lअगरe and a status value क्रम the battery. The estimated lअगरe
 *	अगर reported is a lअगरeसमय in seconds/minutes at current घातer
 *	consumption.
 */

अटल पूर्णांक apm_get_घातer_status(u_लघु *status, u_लघु *bat, u_लघु *lअगरe)
अणु
	काष्ठा apm_bios_call call;

	call.func = APM_FUNC_GET_STATUS;
	call.ebx = APM_DEVICE_ALL;
	call.ecx = 0;

	अगर (apm_info.get_घातer_status_broken)
		वापस APM_32_UNSUPPORTED;
	अगर (apm_bios_call(&call)) अणु
		अगर (!call.err)
			वापस APM_NO_ERROR;
		वापस call.err;
	पूर्ण
	*status = call.ebx;
	*bat = call.ecx;
	अगर (apm_info.get_घातer_status_swabinminutes) अणु
		*lअगरe = swab16((u16)call.edx);
		*lअगरe |= 0x8000;
	पूर्ण अन्यथा
		*lअगरe = call.edx;
	वापस APM_SUCCESS;
पूर्ण

#अगर 0
अटल पूर्णांक apm_get_battery_status(u_लघु which, u_लघु *status,
				  u_लघु *bat, u_लघु *lअगरe, u_लघु *nbat)
अणु
	u32 eax;
	u32 ebx;
	u32 ecx;
	u32 edx;
	u32 esi;

	अगर (apm_info.connection_version < 0x0102) अणु
		/* pretend we only have one battery. */
		अगर (which != 1)
			वापस APM_BAD_DEVICE;
		*nbat = 1;
		वापस apm_get_घातer_status(status, bat, lअगरe);
	पूर्ण

	अगर (apm_bios_call(APM_FUNC_GET_STATUS, (0x8000 | (which)), 0, &eax,
			  &ebx, &ecx, &edx, &esi))
		वापस (eax >> 8) & 0xff;
	*status = ebx;
	*bat = ecx;
	*lअगरe = edx;
	*nbat = esi;
	वापस APM_SUCCESS;
पूर्ण
#पूर्ण_अगर

/**
 *	apm_engage_घातer_management	-	enable PM on a device
 *	@device: identity of device
 *	@enable: on/off
 *
 *	Activate or deactivate घातer management on either a specअगरic device
 *	or the entire प्रणाली (%APM_DEVICE_ALL).
 */

अटल पूर्णांक apm_engage_घातer_management(u_लघु device, पूर्णांक enable)
अणु
	u32 eax;
	पूर्णांक err;

	अगर ((enable == 0) && (device == APM_DEVICE_ALL)
	    && (apm_info.bios.flags & APM_BIOS_DISABLED))
		वापस APM_DISABLED;
	अगर (apm_bios_call_simple(APM_FUNC_ENGAGE_PM, device, enable,
				 &eax, &err))
		वापस err;
	अगर (device == APM_DEVICE_ALL) अणु
		अगर (enable)
			apm_info.bios.flags &= ~APM_BIOS_DISENGAGED;
		अन्यथा
			apm_info.bios.flags |= APM_BIOS_DISENGAGED;
	पूर्ण
	वापस APM_SUCCESS;
पूर्ण

#अगर defined(CONFIG_APM_DISPLAY_BLANK) && defined(CONFIG_VT)

/**
 *	apm_console_blank	-	blank the display
 *	@blank: on/off
 *
 *	Attempt to blank the console, firstly by blanking just video device
 *	zero, and अगर that fails (some BIOSes करोn't support it) then it blanks
 *	all video devices. Typically the BIOS will करो laptop backlight and
 *	monitor घातerकरोwn क्रम us.
 */

अटल पूर्णांक apm_console_blank(पूर्णांक blank)
अणु
	पूर्णांक error = APM_NOT_ENGAGED; /* silence gcc */
	पूर्णांक i;
	u_लघु state;
	अटल स्थिर u_लघु dev[3] = अणु 0x100, 0x1FF, 0x101 पूर्ण;

	state = blank ? APM_STATE_STANDBY : APM_STATE_READY;

	क्रम (i = 0; i < ARRAY_SIZE(dev); i++) अणु
		error = set_घातer_state(dev[i], state);

		अगर ((error == APM_SUCCESS) || (error == APM_NO_ERROR))
			वापस 1;

		अगर (error == APM_NOT_ENGAGED)
			अवरोध;
	पूर्ण

	अगर (error == APM_NOT_ENGAGED) अणु
		अटल पूर्णांक tried;
		पूर्णांक eng_error;
		अगर (tried++ == 0) अणु
			eng_error = apm_engage_घातer_management(APM_DEVICE_ALL, 1);
			अगर (eng_error) अणु
				apm_error("set display", error);
				apm_error("engage interface", eng_error);
				वापस 0;
			पूर्ण अन्यथा
				वापस apm_console_blank(blank);
		पूर्ण
	पूर्ण
	apm_error("set display", error);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक queue_empty(काष्ठा apm_user *as)
अणु
	वापस as->event_head == as->event_tail;
पूर्ण

अटल apm_event_t get_queued_event(काष्ठा apm_user *as)
अणु
	अगर (++as->event_tail >= APM_MAX_EVENTS)
		as->event_tail = 0;
	वापस as->events[as->event_tail];
पूर्ण

अटल व्योम queue_event(apm_event_t event, काष्ठा apm_user *sender)
अणु
	काष्ठा apm_user *as;

	spin_lock(&user_list_lock);
	अगर (user_list == शून्य)
		जाओ out;
	क्रम (as = user_list; as != शून्य; as = as->next) अणु
		अगर ((as == sender) || (!as->पढ़ोer))
			जारी;
		अगर (++as->event_head >= APM_MAX_EVENTS)
			as->event_head = 0;

		अगर (as->event_head == as->event_tail) अणु
			अटल पूर्णांक notअगरied;

			अगर (notअगरied++ == 0)
				pr_err("an event queue overflowed\n");
			अगर (++as->event_tail >= APM_MAX_EVENTS)
				as->event_tail = 0;
		पूर्ण
		as->events[as->event_head] = event;
		अगर (!as->suser || !as->ग_लिखोr)
			जारी;
		चयन (event) अणु
		हाल APM_SYS_SUSPEND:
		हाल APM_USER_SUSPEND:
			as->suspends_pending++;
			suspends_pending++;
			अवरोध;

		हाल APM_SYS_STANDBY:
		हाल APM_USER_STANDBY:
			as->standbys_pending++;
			standbys_pending++;
			अवरोध;
		पूर्ण
	पूर्ण
	wake_up_पूर्णांकerruptible(&apm_रुकोqueue);
out:
	spin_unlock(&user_list_lock);
पूर्ण

अटल व्योम reinit_समयr(व्योम)
अणु
#अगर_घोषित INIT_TIMER_AFTER_SUSPEND
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&i8253_lock, flags);
	/* set the घड़ी to HZ */
	outb_p(0x34, PIT_MODE);		/* binary, mode 2, LSB/MSB, ch 0 */
	udelay(10);
	outb_p(LATCH & 0xff, PIT_CH0);	/* LSB */
	udelay(10);
	outb_p(LATCH >> 8, PIT_CH0);	/* MSB */
	udelay(10);
	raw_spin_unlock_irqrestore(&i8253_lock, flags);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक suspend(पूर्णांक vetoable)
अणु
	पूर्णांक err;
	काष्ठा apm_user	*as;

	dpm_suspend_start(PMSG_SUSPEND);
	dpm_suspend_end(PMSG_SUSPEND);

	local_irq_disable();
	syscore_suspend();

	local_irq_enable();

	save_processor_state();
	err = set_प्रणाली_घातer_state(APM_STATE_SUSPEND);
	ignore_normal_resume = 1;
	restore_processor_state();

	local_irq_disable();
	reinit_समयr();

	अगर (err == APM_NO_ERROR)
		err = APM_SUCCESS;
	अगर (err != APM_SUCCESS)
		apm_error("suspend", err);
	err = (err == APM_SUCCESS) ? 0 : -EIO;

	syscore_resume();
	local_irq_enable();

	dpm_resume_start(PMSG_RESUME);
	dpm_resume_end(PMSG_RESUME);

	queue_event(APM_NORMAL_RESUME, शून्य);
	spin_lock(&user_list_lock);
	क्रम (as = user_list; as != शून्य; as = as->next) अणु
		as->suspend_रुको = 0;
		as->suspend_result = err;
	पूर्ण
	spin_unlock(&user_list_lock);
	wake_up_पूर्णांकerruptible(&apm_suspend_रुकोqueue);
	वापस err;
पूर्ण

अटल व्योम standby(व्योम)
अणु
	पूर्णांक err;

	dpm_suspend_end(PMSG_SUSPEND);

	local_irq_disable();
	syscore_suspend();
	local_irq_enable();

	err = set_प्रणाली_घातer_state(APM_STATE_STANDBY);
	अगर ((err != APM_SUCCESS) && (err != APM_NO_ERROR))
		apm_error("standby", err);

	local_irq_disable();
	syscore_resume();
	local_irq_enable();

	dpm_resume_start(PMSG_RESUME);
पूर्ण

अटल apm_event_t get_event(व्योम)
अणु
	पूर्णांक error;
	apm_event_t event = APM_NO_EVENTS; /* silence gcc */
	apm_eventinfo_t	info;

	अटल पूर्णांक notअगरied;

	/* we करोn't use the eventinfo */
	error = apm_get_event(&event, &info);
	अगर (error == APM_SUCCESS)
		वापस event;

	अगर ((error != APM_NO_EVENTS) && (notअगरied++ == 0))
		apm_error("get_event", error);

	वापस 0;
पूर्ण

अटल व्योम check_events(व्योम)
अणु
	apm_event_t event;
	अटल अचिन्हित दीर्घ last_resume;
	अटल पूर्णांक ignore_bounce;

	जबतक ((event = get_event()) != 0) अणु
		अगर (debug) अणु
			अगर (event <= NR_APM_EVENT_NAME)
				prपूर्णांकk(KERN_DEBUG "apm: received %s notify\n",
				       apm_event_name[event - 1]);
			अन्यथा
				prपूर्णांकk(KERN_DEBUG "apm: received unknown "
				       "event 0x%02x\n", event);
		पूर्ण
		अगर (ignore_bounce
		    && (समय_after(jअगरfies, last_resume + bounce_पूर्णांकerval)))
			ignore_bounce = 0;

		चयन (event) अणु
		हाल APM_SYS_STANDBY:
		हाल APM_USER_STANDBY:
			queue_event(event, शून्य);
			अगर (standbys_pending <= 0)
				standby();
			अवरोध;

		हाल APM_USER_SUSPEND:
#अगर_घोषित CONFIG_APM_IGNORE_USER_SUSPEND
			अगर (apm_info.connection_version > 0x100)
				set_प्रणाली_घातer_state(APM_STATE_REJECT);
			अवरोध;
#पूर्ण_अगर
		हाल APM_SYS_SUSPEND:
			अगर (ignore_bounce) अणु
				अगर (apm_info.connection_version > 0x100)
					set_प्रणाली_घातer_state(APM_STATE_REJECT);
				अवरोध;
			पूर्ण
			/*
			 * If we are alपढ़ोy processing a SUSPEND,
			 * then further SUSPEND events from the BIOS
			 * will be ignored.  We also वापस here to
			 * cope with the fact that the Thinkpads keep
			 * sending a SUSPEND event until something अन्यथा
			 * happens!
			 */
			अगर (ignore_sys_suspend)
				वापस;
			ignore_sys_suspend = 1;
			queue_event(event, शून्य);
			अगर (suspends_pending <= 0)
				(व्योम) suspend(1);
			अवरोध;

		हाल APM_NORMAL_RESUME:
		हाल APM_CRITICAL_RESUME:
		हाल APM_STANDBY_RESUME:
			ignore_sys_suspend = 0;
			last_resume = jअगरfies;
			ignore_bounce = 1;
			अगर ((event != APM_NORMAL_RESUME)
			    || (ignore_normal_resume == 0)) अणु
				dpm_resume_end(PMSG_RESUME);
				queue_event(event, शून्य);
			पूर्ण
			ignore_normal_resume = 0;
			अवरोध;

		हाल APM_CAPABILITY_CHANGE:
		हाल APM_LOW_BATTERY:
		हाल APM_POWER_STATUS_CHANGE:
			queue_event(event, शून्य);
			/* If needed, notअगरy drivers here */
			अवरोध;

		हाल APM_UPDATE_TIME:
			अवरोध;

		हाल APM_CRITICAL_SUSPEND:
			/*
			 * We are not allowed to reject a critical suspend.
			 */
			(व्योम)suspend(0);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम apm_event_handler(व्योम)
अणु
	अटल पूर्णांक pending_count = 4;
	पूर्णांक err;

	अगर ((standbys_pending > 0) || (suspends_pending > 0)) अणु
		अगर ((apm_info.connection_version > 0x100) &&
		    (pending_count-- <= 0)) अणु
			pending_count = 4;
			अगर (debug)
				prपूर्णांकk(KERN_DEBUG "apm: setting state busy\n");
			err = set_प्रणाली_घातer_state(APM_STATE_BUSY);
			अगर (err)
				apm_error("busy", err);
		पूर्ण
	पूर्ण अन्यथा
		pending_count = 4;
	check_events();
पूर्ण

/*
 * This is the APM thपढ़ो मुख्य loop.
 */

अटल व्योम apm_मुख्यloop(व्योम)
अणु
	DECLARE_WAITQUEUE(रुको, current);

	add_रुको_queue(&apm_रुकोqueue, &रुको);
	set_current_state(TASK_INTERRUPTIBLE);
	क्रम (;;) अणु
		schedule_समयout(APM_CHECK_TIMEOUT);
		अगर (kthपढ़ो_should_stop())
			अवरोध;
		/*
		 * Ok, check all events, check क्रम idle (and mark us sleeping
		 * so as not to count towards the load average)..
		 */
		set_current_state(TASK_INTERRUPTIBLE);
		apm_event_handler();
	पूर्ण
	हटाओ_रुको_queue(&apm_रुकोqueue, &रुको);
पूर्ण

अटल पूर्णांक check_apm_user(काष्ठा apm_user *as, स्थिर अक्षर *func)
अणु
	अगर (as == शून्य || as->magic != APM_BIOS_MAGIC) अणु
		pr_err("%s passed bad filp\n", func);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार करो_पढ़ो(काष्ठा file *fp, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा apm_user *as;
	पूर्णांक i;
	apm_event_t event;

	as = fp->निजी_data;
	अगर (check_apm_user(as, "read"))
		वापस -EIO;
	अगर ((पूर्णांक)count < माप(apm_event_t))
		वापस -EINVAL;
	अगर ((queue_empty(as)) && (fp->f_flags & O_NONBLOCK))
		वापस -EAGAIN;
	रुको_event_पूर्णांकerruptible(apm_रुकोqueue, !queue_empty(as));
	i = count;
	जबतक ((i >= माप(event)) && !queue_empty(as)) अणु
		event = get_queued_event(as);
		अगर (copy_to_user(buf, &event, माप(event))) अणु
			अगर (i < count)
				अवरोध;
			वापस -EFAULT;
		पूर्ण
		चयन (event) अणु
		हाल APM_SYS_SUSPEND:
		हाल APM_USER_SUSPEND:
			as->suspends_पढ़ो++;
			अवरोध;

		हाल APM_SYS_STANDBY:
		हाल APM_USER_STANDBY:
			as->standbys_पढ़ो++;
			अवरोध;
		पूर्ण
		buf += माप(event);
		i -= माप(event);
	पूर्ण
	अगर (i < count)
		वापस count - i;
	अगर (संकेत_pending(current))
		वापस -ERESTARTSYS;
	वापस 0;
पूर्ण

अटल __poll_t करो_poll(काष्ठा file *fp, poll_table *रुको)
अणु
	काष्ठा apm_user *as;

	as = fp->निजी_data;
	अगर (check_apm_user(as, "poll"))
		वापस 0;
	poll_रुको(fp, &apm_रुकोqueue, रुको);
	अगर (!queue_empty(as))
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

अटल दीर्घ करो_ioctl(काष्ठा file *filp, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	काष्ठा apm_user *as;
	पूर्णांक ret;

	as = filp->निजी_data;
	अगर (check_apm_user(as, "ioctl"))
		वापस -EIO;
	अगर (!as->suser || !as->ग_लिखोr)
		वापस -EPERM;
	चयन (cmd) अणु
	हाल APM_IOC_STANDBY:
		mutex_lock(&apm_mutex);
		अगर (as->standbys_पढ़ो > 0) अणु
			as->standbys_पढ़ो--;
			as->standbys_pending--;
			standbys_pending--;
		पूर्ण अन्यथा
			queue_event(APM_USER_STANDBY, as);
		अगर (standbys_pending <= 0)
			standby();
		mutex_unlock(&apm_mutex);
		अवरोध;
	हाल APM_IOC_SUSPEND:
		mutex_lock(&apm_mutex);
		अगर (as->suspends_पढ़ो > 0) अणु
			as->suspends_पढ़ो--;
			as->suspends_pending--;
			suspends_pending--;
		पूर्ण अन्यथा
			queue_event(APM_USER_SUSPEND, as);
		अगर (suspends_pending <= 0) अणु
			ret = suspend(1);
			mutex_unlock(&apm_mutex);
		पूर्ण अन्यथा अणु
			as->suspend_रुको = 1;
			mutex_unlock(&apm_mutex);
			रुको_event_पूर्णांकerruptible(apm_suspend_रुकोqueue,
					as->suspend_रुको == 0);
			ret = as->suspend_result;
		पूर्ण
		वापस ret;
	शेष:
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक करो_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा apm_user *as;

	as = filp->निजी_data;
	अगर (check_apm_user(as, "release"))
		वापस 0;
	filp->निजी_data = शून्य;
	अगर (as->standbys_pending > 0) अणु
		standbys_pending -= as->standbys_pending;
		अगर (standbys_pending <= 0)
			standby();
	पूर्ण
	अगर (as->suspends_pending > 0) अणु
		suspends_pending -= as->suspends_pending;
		अगर (suspends_pending <= 0)
			(व्योम) suspend(1);
	पूर्ण
	spin_lock(&user_list_lock);
	अगर (user_list == as)
		user_list = as->next;
	अन्यथा अणु
		काष्ठा apm_user *as1;

		क्रम (as1 = user_list;
		     (as1 != शून्य) && (as1->next != as);
		     as1 = as1->next)
			;
		अगर (as1 == शून्य)
			pr_err("filp not in user list\n");
		अन्यथा
			as1->next = as->next;
	पूर्ण
	spin_unlock(&user_list_lock);
	kमुक्त(as);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा apm_user *as;

	as = kदो_स्मृति(माप(*as), GFP_KERNEL);
	अगर (as == शून्य)
		वापस -ENOMEM;

	as->magic = APM_BIOS_MAGIC;
	as->event_tail = as->event_head = 0;
	as->suspends_pending = as->standbys_pending = 0;
	as->suspends_पढ़ो = as->standbys_पढ़ो = 0;
	/*
	 * XXX - this is a tiny bit broken, when we consider BSD
	 * process accounting. If the device is खोलोed by root, we
	 * instantly flag that we used superuser privs. Who knows,
	 * we might बंद the device immediately without करोing a
	 * privileged operation -- cevans
	 */
	as->suser = capable(CAP_SYS_ADMIN);
	as->ग_लिखोr = (filp->f_mode & FMODE_WRITE) == FMODE_WRITE;
	as->पढ़ोer = (filp->f_mode & FMODE_READ) == FMODE_READ;
	spin_lock(&user_list_lock);
	as->next = user_list;
	user_list = as;
	spin_unlock(&user_list_lock);
	filp->निजी_data = as;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक proc_apm_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित लघु	bx;
	अचिन्हित लघु	cx;
	अचिन्हित लघु	dx;
	पूर्णांक		error;
	अचिन्हित लघु  ac_line_status = 0xff;
	अचिन्हित लघु  battery_status = 0xff;
	अचिन्हित लघु  battery_flag   = 0xff;
	पूर्णांक		percentage     = -1;
	पूर्णांक             समय_units     = -1;
	अक्षर            *units         = "?";

	अगर ((num_online_cpus() == 1) &&
	    !(error = apm_get_घातer_status(&bx, &cx, &dx))) अणु
		ac_line_status = (bx >> 8) & 0xff;
		battery_status = bx & 0xff;
		अगर ((cx & 0xff) != 0xff)
			percentage = cx & 0xff;

		अगर (apm_info.connection_version > 0x100) अणु
			battery_flag = (cx >> 8) & 0xff;
			अगर (dx != 0xffff) अणु
				units = (dx & 0x8000) ? "min" : "sec";
				समय_units = dx & 0x7fff;
			पूर्ण
		पूर्ण
	पूर्ण
	/* Arguments, with symbols from linux/apm_मूलप्रण.स.  Inक्रमmation is
	   from the Get Power Status (0x0a) call unless otherwise noted.

	   0) Linux driver version (this will change अगर क्रमmat changes)
	   1) APM BIOS Version.  Usually 1.0, 1.1 or 1.2.
	   2) APM flags from APM Installation Check (0x00):
	      bit 0: APM_16_BIT_SUPPORT
	      bit 1: APM_32_BIT_SUPPORT
	      bit 2: APM_IDLE_SLOWS_CLOCK
	      bit 3: APM_BIOS_DISABLED
	      bit 4: APM_BIOS_DISENGAGED
	   3) AC line status
	      0x00: Off-line
	      0x01: On-line
	      0x02: On backup घातer (BIOS >= 1.1 only)
	      0xff: Unknown
	   4) Battery status
	      0x00: High
	      0x01: Low
	      0x02: Critical
	      0x03: Charging
	      0x04: Selected battery not present (BIOS >= 1.2 only)
	      0xff: Unknown
	   5) Battery flag
	      bit 0: High
	      bit 1: Low
	      bit 2: Critical
	      bit 3: Charging
	      bit 7: No प्रणाली battery
	      0xff: Unknown
	   6) Reमुख्यing battery lअगरe (percentage of अक्षरge):
	      0-100: valid
	      -1: Unknown
	   7) Reमुख्यing battery lअगरe (समय units):
	      Number of reमुख्यing minutes or seconds
	      -1: Unknown
	   8) min = minutes; sec = seconds */

	seq_म_लिखो(m, "%s %d.%d 0x%02x 0x%02x 0x%02x 0x%02x %d%% %d %s\n",
		   driver_version,
		   (apm_info.bios.version >> 8) & 0xff,
		   apm_info.bios.version & 0xff,
		   apm_info.bios.flags,
		   ac_line_status,
		   battery_status,
		   battery_flag,
		   percentage,
		   समय_units,
		   units);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक apm(व्योम *unused)
अणु
	अचिन्हित लघु	bx;
	अचिन्हित लघु	cx;
	अचिन्हित लघु	dx;
	पूर्णांक		error;
	अक्षर 		*घातer_stat;
	अक्षर 		*bat_stat;

	/* 2002/08/01 - WT
	 * This is to aव्योम अक्रमom crashes at boot समय during initialization
	 * on SMP प्रणालीs in हाल of "apm=power-off" mode. Seen on ASUS A7M266D.
	 * Some bioses करोn't like being called from CPU != 0.
	 * Method suggested by Ingo Molnar.
	 */
	set_cpus_allowed_ptr(current, cpumask_of(0));
	BUG_ON(smp_processor_id() != 0);

	अगर (apm_info.connection_version == 0) अणु
		apm_info.connection_version = apm_info.bios.version;
		अगर (apm_info.connection_version > 0x100) अणु
			/*
			 * We only support BIOSs up to version 1.2
			 */
			अगर (apm_info.connection_version > 0x0102)
				apm_info.connection_version = 0x0102;
			error = apm_driver_version(&apm_info.connection_version);
			अगर (error != APM_SUCCESS) अणु
				apm_error("driver version", error);
				/* Fall back to an APM 1.0 connection. */
				apm_info.connection_version = 0x100;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (debug)
		prपूर्णांकk(KERN_INFO "apm: Connection version %d.%d\n",
			(apm_info.connection_version >> 8) & 0xff,
			apm_info.connection_version & 0xff);

#अगर_घोषित CONFIG_APM_DO_ENABLE
	अगर (apm_info.bios.flags & APM_BIOS_DISABLED) अणु
		/*
		 * This call causes my NEC UltraLite Versa 33/C to hang अगर it
		 * is booted with PM disabled but not in the करोcking station.
		 * Unक्रमtunate ...
		 */
		error = apm_enable_घातer_management(1);
		अगर (error) अणु
			apm_error("enable power management", error);
			वापस -1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर ((apm_info.bios.flags & APM_BIOS_DISENGAGED)
	    && (apm_info.connection_version > 0x0100)) अणु
		error = apm_engage_घातer_management(APM_DEVICE_ALL, 1);
		अगर (error) अणु
			apm_error("engage power management", error);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (debug && (num_online_cpus() == 1 || smp)) अणु
		error = apm_get_घातer_status(&bx, &cx, &dx);
		अगर (error)
			prपूर्णांकk(KERN_INFO "apm: power status not available\n");
		अन्यथा अणु
			चयन ((bx >> 8) & 0xff) अणु
			हाल 0:
				घातer_stat = "off line";
				अवरोध;
			हाल 1:
				घातer_stat = "on line";
				अवरोध;
			हाल 2:
				घातer_stat = "on backup power";
				अवरोध;
			शेष:
				घातer_stat = "unknown";
				अवरोध;
			पूर्ण
			चयन (bx & 0xff) अणु
			हाल 0:
				bat_stat = "high";
				अवरोध;
			हाल 1:
				bat_stat = "low";
				अवरोध;
			हाल 2:
				bat_stat = "critical";
				अवरोध;
			हाल 3:
				bat_stat = "charging";
				अवरोध;
			शेष:
				bat_stat = "unknown";
				अवरोध;
			पूर्ण
			prपूर्णांकk(KERN_INFO
			       "apm: AC %s, battery status %s, battery life ",
			       घातer_stat, bat_stat);
			अगर ((cx & 0xff) == 0xff)
				prपूर्णांकk("unknown\n");
			अन्यथा
				prपूर्णांकk("%d%%\n", cx & 0xff);
			अगर (apm_info.connection_version > 0x100) अणु
				prपूर्णांकk(KERN_INFO
				       "apm: battery flag 0x%02x, battery life ",
				       (cx >> 8) & 0xff);
				अगर (dx == 0xffff)
					prपूर्णांकk("unknown\n");
				अन्यथा
					prपूर्णांकk("%d %s\n", dx & 0x7fff,
					       (dx & 0x8000) ?
					       "minutes" : "seconds");
			पूर्ण
		पूर्ण
	पूर्ण

	/* Install our घातer off handler.. */
	अगर (घातer_off)
		pm_घातer_off = apm_घातer_off;

	अगर (num_online_cpus() == 1 || smp) अणु
#अगर defined(CONFIG_APM_DISPLAY_BLANK) && defined(CONFIG_VT)
		console_blank_hook = apm_console_blank;
#पूर्ण_अगर
		apm_मुख्यloop();
#अगर defined(CONFIG_APM_DISPLAY_BLANK) && defined(CONFIG_VT)
		console_blank_hook = शून्य;
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक __init apm_setup(अक्षर *str)
अणु
	पूर्णांक invert;

	जबतक ((str != शून्य) && (*str != '\0')) अणु
		अगर (म_भेदन(str, "off", 3) == 0)
			apm_disabled = 1;
		अगर (म_भेदन(str, "on", 2) == 0)
			apm_disabled = 0;
		अगर ((म_भेदन(str, "bounce-interval=", 16) == 0) ||
		    (म_भेदन(str, "bounce_interval=", 16) == 0))
			bounce_पूर्णांकerval = simple_म_से_दीर्घ(str + 16, शून्य, 0);
		अगर ((म_भेदन(str, "idle-threshold=", 15) == 0) ||
		    (म_भेदन(str, "idle_threshold=", 15) == 0))
			idle_threshold = simple_म_से_दीर्घ(str + 15, शून्य, 0);
		अगर ((म_भेदन(str, "idle-period=", 12) == 0) ||
		    (म_भेदन(str, "idle_period=", 12) == 0))
			idle_period = simple_म_से_दीर्घ(str + 12, शून्य, 0);
		invert = (म_भेदन(str, "no-", 3) == 0) ||
			(म_भेदन(str, "no_", 3) == 0);
		अगर (invert)
			str += 3;
		अगर (म_भेदन(str, "debug", 5) == 0)
			debug = !invert;
		अगर ((म_भेदन(str, "power-off", 9) == 0) ||
		    (म_भेदन(str, "power_off", 9) == 0))
			घातer_off = !invert;
		अगर (म_भेदन(str, "smp", 3) == 0) अणु
			smp = !invert;
			idle_threshold = 100;
		पूर्ण
		अगर ((म_भेदन(str, "allow-ints", 10) == 0) ||
		    (म_भेदन(str, "allow_ints", 10) == 0))
			apm_info.allow_पूर्णांकs = !invert;
		अगर ((म_भेदन(str, "broken-psr", 10) == 0) ||
		    (म_भेदन(str, "broken_psr", 10) == 0))
			apm_info.get_घातer_status_broken = !invert;
		अगर ((म_भेदन(str, "realmode-power-off", 18) == 0) ||
		    (म_भेदन(str, "realmode_power_off", 18) == 0))
			apm_info.realmode_घातer_off = !invert;
		str = म_अक्षर(str, ',');
		अगर (str != शून्य)
			str += म_अखोज(str, ", \t");
	पूर्ण
	वापस 1;
पूर्ण

__setup("apm=", apm_setup);
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations apm_bios_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= करो_पढ़ो,
	.poll		= करो_poll,
	.unlocked_ioctl	= करो_ioctl,
	.खोलो		= करो_खोलो,
	.release	= करो_release,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice apm_device = अणु
	APM_MINOR_DEV,
	"apm_bios",
	&apm_bios_fops
पूर्ण;


/* Simple "print if true" callback */
अटल पूर्णांक __init prपूर्णांक_अगर_true(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	prपूर्णांकk("%s\n", d->ident);
	वापस 0;
पूर्ण

/*
 * Some Bioses enable the PS/2 mouse (touchpad) at resume, even अगर it was
 * disabled beक्रमe the suspend. Linux used to get terribly confused by that.
 */
अटल पूर्णांक __init broken_ps2_resume(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	prपूर्णांकk(KERN_INFO "%s machine detected. Mousepad Resume Bug "
	       "workaround hopefully not needed.\n", d->ident);
	वापस 0;
पूर्ण

/* Some bioses have a broken रक्षित mode घातeroff and need to use realmode */
अटल पूर्णांक __init set_realmode_घातer_off(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (apm_info.realmode_घातer_off == 0) अणु
		apm_info.realmode_घातer_off = 1;
		prपूर्णांकk(KERN_INFO "%s bios detected. "
		       "Using realmode poweroff only.\n", d->ident);
	पूर्ण
	वापस 0;
पूर्ण

/* Some laptops require पूर्णांकerrupts to be enabled during APM calls */
अटल पूर्णांक __init set_apm_पूर्णांकs(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (apm_info.allow_पूर्णांकs == 0) अणु
		apm_info.allow_पूर्णांकs = 1;
		prपूर्णांकk(KERN_INFO "%s machine detected. "
		       "Enabling interrupts during APM calls.\n", d->ident);
	पूर्ण
	वापस 0;
पूर्ण

/* Some APM bioses corrupt memory or just plain करो not work */
अटल पूर्णांक __init apm_is_horked(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (apm_info.disabled == 0) अणु
		apm_info.disabled = 1;
		prपूर्णांकk(KERN_INFO "%s machine detected. "
		       "Disabling APM.\n", d->ident);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init apm_is_horked_d850md(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (apm_info.disabled == 0) अणु
		apm_info.disabled = 1;
		prपूर्णांकk(KERN_INFO "%s machine detected. "
		       "Disabling APM.\n", d->ident);
		prपूर्णांकk(KERN_INFO "This bug is fixed in bios P15 which is available for\n");
		prपूर्णांकk(KERN_INFO "download from support.intel.com\n");
	पूर्ण
	वापस 0;
पूर्ण

/* Some APM bioses hang on APM idle calls */
अटल पूर्णांक __init apm_likes_to_melt(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (apm_info.क्रमbid_idle == 0) अणु
		apm_info.क्रमbid_idle = 1;
		prपूर्णांकk(KERN_INFO "%s machine detected. "
		       "Disabling APM idle calls.\n", d->ident);
	पूर्ण
	वापस 0;
पूर्ण

/*
 *  Check क्रम clue मुक्त BIOS implementations who use
 *  the following QA technique
 *
 *      [ Write BIOS Code ]<------
 *               |                ^
 *      < Does it Compile >----N--
 *               |Y               ^
 *	< Does it Boot Win98 >-N--
 *               |Y
 *           [Ship It]
 *
 *	Phoenix A04  08/24/2000 is known bad (Dell Inspiron 5000e)
 *	Phoenix A07  09/29/2000 is known good (Dell Inspiron 5000)
 */
अटल पूर्णांक __init broken_apm_घातer(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	apm_info.get_घातer_status_broken = 1;
	prपूर्णांकk(KERN_WARNING "BIOS strings suggest APM bugs, "
	       "disabling power status reporting.\n");
	वापस 0;
पूर्ण

/*
 * This bios swaps the APM minute reporting bytes over (Many sony laptops
 * have this problem).
 */
अटल पूर्णांक __init swab_apm_घातer_in_minutes(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	apm_info.get_घातer_status_swabinminutes = 1;
	prपूर्णांकk(KERN_WARNING "BIOS strings suggest APM reports battery life "
	       "in minutes and wrong byte order.\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id apm_dmi_table[] __initस्थिर = अणु
	अणु
		prपूर्णांक_अगर_true,
		KERN_WARNING "IBM T23 - BIOS 1.03b+ and controller firmware 1.02+ may be needed for Linux APM.",
		अणु	DMI_MATCH(DMI_SYS_VENDOR, "IBM"),
			DMI_MATCH(DMI_BIOS_VERSION, "1AET38WW (1.01b)"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on the C600 */
		broken_ps2_resume, "Dell Latitude C600",
		अणु	DMI_MATCH(DMI_SYS_VENDOR, "Dell"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude C600"), पूर्ण,
	पूर्ण,
	अणु	/* Allow पूर्णांकerrupts during suspend on Dell Latitude laptops*/
		set_apm_पूर्णांकs, "Dell Latitude",
		अणु	DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude C510"), पूर्ण
	पूर्ण,
	अणु	/* APM crashes */
		apm_is_horked, "Dell Inspiron 2500",
		अणु	DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 2500"),
			DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "A11"), पूर्ण,
	पूर्ण,
	अणु	/* Allow पूर्णांकerrupts during suspend on Dell Inspiron laptops*/
		set_apm_पूर्णांकs, "Dell Inspiron", अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 4000"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Inspiron 5000e */
		broken_apm_घातer, "Dell Inspiron 5000e",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "A04"),
			DMI_MATCH(DMI_BIOS_DATE, "08/24/2000"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Inspiron 2500 */
		broken_apm_घातer, "Dell Inspiron 2500",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "A12"),
			DMI_MATCH(DMI_BIOS_DATE, "02/04/2002"), पूर्ण,
	पूर्ण,
	अणु	/* APM crashes */
		apm_is_horked, "Dell Dimension 4100",
		अणु	DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "XPS-Z"),
			DMI_MATCH(DMI_BIOS_VENDOR, "Intel Corp."),
			DMI_MATCH(DMI_BIOS_VERSION, "A11"), पूर्ण,
	पूर्ण,
	अणु	/* Allow पूर्णांकerrupts during suspend on Compaq Laptops*/
		set_apm_पूर्णांकs, "Compaq 12XL125",
		अणु	DMI_MATCH(DMI_SYS_VENDOR, "Compaq"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Compaq PC"),
			DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "4.06"), पूर्ण,
	पूर्ण,
	अणु	/* Allow पूर्णांकerrupts during APM or the घड़ी goes slow */
		set_apm_पूर्णांकs, "ASUSTeK",
		अणु	DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "L8400K series Notebook PC"), पूर्ण,
	पूर्ण,
	अणु	/* APM blows on shutकरोwn */
		apm_is_horked, "ABIT KX7-333[R]",
		अणु	DMI_MATCH(DMI_BOARD_VENDOR, "ABIT"),
			DMI_MATCH(DMI_BOARD_NAME, "VT8367-8233A (KX7-333[R])"), पूर्ण,
	पूर्ण,
	अणु	/* APM crashes */
		apm_is_horked, "Trigem Delhi3",
		अणु	DMI_MATCH(DMI_SYS_VENDOR, "TriGem Computer, Inc"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Delhi3"), पूर्ण,
	पूर्ण,
	अणु	/* APM crashes */
		apm_is_horked, "Fujitsu-Siemens",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "hoenix/FUJITSU SIEMENS"),
			DMI_MATCH(DMI_BIOS_VERSION, "Version1.01"), पूर्ण,
	पूर्ण,
	अणु	/* APM crashes */
		apm_is_horked_d850md, "Intel D850MD",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Intel Corp."),
			DMI_MATCH(DMI_BIOS_VERSION, "MV85010A.86A.0016.P07.0201251536"), पूर्ण,
	पूर्ण,
	अणु	/* APM crashes */
		apm_is_horked, "Intel D810EMO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Intel Corp."),
			DMI_MATCH(DMI_BIOS_VERSION, "MO81010A.86A.0008.P04.0004170800"), पूर्ण,
	पूर्ण,
	अणु	/* APM crashes */
		apm_is_horked, "Dell XPS-Z",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Intel Corp."),
			DMI_MATCH(DMI_BIOS_VERSION, "A11"),
			DMI_MATCH(DMI_PRODUCT_NAME, "XPS-Z"), पूर्ण,
	पूर्ण,
	अणु	/* APM crashes */
		apm_is_horked, "Sharp PC-PJ/AX",
		अणु	DMI_MATCH(DMI_SYS_VENDOR, "SHARP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PC-PJ/AX"),
			DMI_MATCH(DMI_BIOS_VENDOR, "SystemSoft"),
			DMI_MATCH(DMI_BIOS_VERSION, "Version R2.08"), पूर्ण,
	पूर्ण,
	अणु	/* APM crashes */
		apm_is_horked, "Dell Inspiron 2500",
		अणु	DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 2500"),
			DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "A11"), पूर्ण,
	पूर्ण,
	अणु	/* APM idle hangs */
		apm_likes_to_melt, "Jabil AMD",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "American Megatrends Inc."),
			DMI_MATCH(DMI_BIOS_VERSION, "0AASNP06"), पूर्ण,
	पूर्ण,
	अणु	/* APM idle hangs */
		apm_likes_to_melt, "AMI Bios",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "American Megatrends Inc."),
			DMI_MATCH(DMI_BIOS_VERSION, "0AASNP05"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Sony Vaio PCG-N505X(DE) */
		swab_apm_घातer_in_minutes, "Sony VAIO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "R0206H"),
			DMI_MATCH(DMI_BIOS_DATE, "08/23/99"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Sony Vaio PCG-N505VX */
		swab_apm_घातer_in_minutes, "Sony VAIO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "W2K06H0"),
			DMI_MATCH(DMI_BIOS_DATE, "02/03/00"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Sony Vaio PCG-XG29 */
		swab_apm_घातer_in_minutes, "Sony VAIO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "R0117A0"),
			DMI_MATCH(DMI_BIOS_DATE, "04/25/00"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Sony Vaio PCG-Z600NE */
		swab_apm_घातer_in_minutes, "Sony VAIO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "R0121Z1"),
			DMI_MATCH(DMI_BIOS_DATE, "05/11/00"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Sony Vaio PCG-Z600NE */
		swab_apm_घातer_in_minutes, "Sony VAIO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "WME01Z1"),
			DMI_MATCH(DMI_BIOS_DATE, "08/11/00"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Sony Vaio PCG-Z600LEK(DE) */
		swab_apm_घातer_in_minutes, "Sony VAIO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "R0206Z3"),
			DMI_MATCH(DMI_BIOS_DATE, "12/25/00"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Sony Vaio PCG-Z505LS */
		swab_apm_घातer_in_minutes, "Sony VAIO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "R0203D0"),
			DMI_MATCH(DMI_BIOS_DATE, "05/12/00"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Sony Vaio PCG-Z505LS */
		swab_apm_घातer_in_minutes, "Sony VAIO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "R0203Z3"),
			DMI_MATCH(DMI_BIOS_DATE, "08/25/00"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Sony Vaio PCG-Z505LS (with updated BIOS) */
		swab_apm_घातer_in_minutes, "Sony VAIO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "R0209Z3"),
			DMI_MATCH(DMI_BIOS_DATE, "05/12/01"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Sony Vaio PCG-F104K */
		swab_apm_घातer_in_minutes, "Sony VAIO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "R0204K2"),
			DMI_MATCH(DMI_BIOS_DATE, "08/28/00"), पूर्ण,
	पूर्ण,

	अणु	/* Handle problems with APM on Sony Vaio PCG-C1VN/C1VE */
		swab_apm_घातer_in_minutes, "Sony VAIO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "R0208P1"),
			DMI_MATCH(DMI_BIOS_DATE, "11/09/00"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Sony Vaio PCG-C1VE */
		swab_apm_घातer_in_minutes, "Sony VAIO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "R0204P1"),
			DMI_MATCH(DMI_BIOS_DATE, "09/12/00"), पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with APM on Sony Vaio PCG-C1VE */
		swab_apm_घातer_in_minutes, "Sony VAIO",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "WXPO1Z3"),
			DMI_MATCH(DMI_BIOS_DATE, "10/26/01"), पूर्ण,
	पूर्ण,
	अणु	/* broken PM घातeroff bios */
		set_realmode_घातer_off, "Award Software v4.60 PGMA",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "Award Software International, Inc."),
			DMI_MATCH(DMI_BIOS_VERSION, "4.60 PGMA"),
			DMI_MATCH(DMI_BIOS_DATE, "134526184"), पूर्ण,
	पूर्ण,

	/* Generic per venकरोr APM settings  */

	अणु	/* Allow पूर्णांकerrupts during suspend on IBM laptops */
		set_apm_पूर्णांकs, "IBM",
		अणु	DMI_MATCH(DMI_SYS_VENDOR, "IBM"), पूर्ण,
	पूर्ण,

	अणु पूर्ण
पूर्ण;

/*
 * Just start the APM thपढ़ो. We करो NOT want to करो APM BIOS
 * calls from anything but the APM thपढ़ो, अगर क्रम no other reason
 * than the fact that we करोn't trust the APM BIOS. This way,
 * most common APM BIOS problems that lead to protection errors
 * etc will have at least some level of being contained...
 *
 * In लघु, अगर something bad happens, at least we have a choice
 * of just समाप्तing the apm thपढ़ो..
 */
अटल पूर्णांक __init apm_init(व्योम)
अणु
	काष्ठा desc_काष्ठा *gdt;
	पूर्णांक err;

	dmi_check_प्रणाली(apm_dmi_table);

	अगर (apm_info.bios.version == 0 || machine_is_olpc()) अणु
		prपूर्णांकk(KERN_INFO "apm: BIOS not found.\n");
		वापस -ENODEV;
	पूर्ण
	prपूर्णांकk(KERN_INFO
	       "apm: BIOS version %d.%d Flags 0x%02x (Driver version %s)\n",
	       ((apm_info.bios.version >> 8) & 0xff),
	       (apm_info.bios.version & 0xff),
	       apm_info.bios.flags,
	       driver_version);
	अगर ((apm_info.bios.flags & APM_32_BIT_SUPPORT) == 0) अणु
		prपूर्णांकk(KERN_INFO "apm: no 32 bit BIOS support\n");
		वापस -ENODEV;
	पूर्ण

	अगर (allow_पूर्णांकs)
		apm_info.allow_पूर्णांकs = 1;
	अगर (broken_psr)
		apm_info.get_घातer_status_broken = 1;
	अगर (realmode_घातer_off)
		apm_info.realmode_घातer_off = 1;
	/* User can override, but शेष is to trust DMI */
	अगर (apm_disabled != -1)
		apm_info.disabled = apm_disabled;

	/*
	 * Fix क्रम the Compaq Contura 3/25c which reports BIOS version 0.1
	 * but is reportedly a 1.0 BIOS.
	 */
	अगर (apm_info.bios.version == 0x001)
		apm_info.bios.version = 0x100;

	/* BIOS < 1.2 करोesn't set cseg_16_len */
	अगर (apm_info.bios.version < 0x102)
		apm_info.bios.cseg_16_len = 0; /* 64k */

	अगर (debug) अणु
		prपूर्णांकk(KERN_INFO "apm: entry %x:%x cseg16 %x dseg %x",
			apm_info.bios.cseg, apm_info.bios.offset,
			apm_info.bios.cseg_16, apm_info.bios.dseg);
		अगर (apm_info.bios.version > 0x100)
			prपूर्णांकk(" cseg len %x, dseg len %x",
				apm_info.bios.cseg_len,
				apm_info.bios.dseg_len);
		अगर (apm_info.bios.version > 0x101)
			prपूर्णांकk(" cseg16 len %x", apm_info.bios.cseg_16_len);
		prपूर्णांकk("\n");
	पूर्ण

	अगर (apm_info.disabled) अणु
		pr_notice("disabled on user request.\n");
		वापस -ENODEV;
	पूर्ण
	अगर ((num_online_cpus() > 1) && !घातer_off && !smp) अणु
		pr_notice("disabled - APM is not SMP safe.\n");
		apm_info.disabled = 1;
		वापस -ENODEV;
	पूर्ण
	अगर (!acpi_disabled) अणु
		pr_notice("overridden by ACPI.\n");
		apm_info.disabled = 1;
		वापस -ENODEV;
	पूर्ण

	/*
	 * Set up the दीर्घ jump entry poपूर्णांक to the APM BIOS, which is called
	 * from अंतरभूत assembly.
	 */
	apm_bios_entry.offset = apm_info.bios.offset;
	apm_bios_entry.segment = APM_CS;

	/*
	 * The APM 1.1 BIOS is supposed to provide limit inक्रमmation that it
	 * recognizes.  Many machines करो this correctly, but many others करो
	 * not restrict themselves to their claimed limit.  When this happens,
	 * they will cause a segmentation violation in the kernel at boot समय.
	 * Most BIOS's, however, will respect a 64k limit, so we use that.
	 *
	 * Note we only set APM segments on CPU zero, since we pin the APM
	 * code to that CPU.
	 */
	gdt = get_cpu_gdt_rw(0);
	set_desc_base(&gdt[APM_CS >> 3],
		 (अचिन्हित दीर्घ)__va((अचिन्हित दीर्घ)apm_info.bios.cseg << 4));
	set_desc_base(&gdt[APM_CS_16 >> 3],
		 (अचिन्हित दीर्घ)__va((अचिन्हित दीर्घ)apm_info.bios.cseg_16 << 4));
	set_desc_base(&gdt[APM_DS >> 3],
		 (अचिन्हित दीर्घ)__va((अचिन्हित दीर्घ)apm_info.bios.dseg << 4));

	proc_create_single("apm", 0, शून्य, proc_apm_show);

	kapmd_task = kthपढ़ो_create(apm, शून्य, "kapmd");
	अगर (IS_ERR(kapmd_task)) अणु
		pr_err("disabled - Unable to start kernel thread\n");
		err = PTR_ERR(kapmd_task);
		kapmd_task = शून्य;
		हटाओ_proc_entry("apm", शून्य);
		वापस err;
	पूर्ण
	wake_up_process(kapmd_task);

	अगर (num_online_cpus() > 1 && !smp) अणु
		prपूर्णांकk(KERN_NOTICE
		       "apm: disabled - APM is not SMP safe (power off active).\n");
		वापस 0;
	पूर्ण

	/*
	 * Note we करोn't actually care अगर the misc_device cannot be रेजिस्टरed.
	 * this driver can करो its job without it, even अगर userspace can't
	 * control it.  just log the error
	 */
	अगर (misc_रेजिस्टर(&apm_device))
		prपूर्णांकk(KERN_WARNING "apm: Could not register misc device.\n");

	अगर (HZ != 100)
		idle_period = (idle_period * HZ) / 100;
	अगर (idle_threshold < 100) अणु
		cpuidle_poll_state_init(&apm_idle_driver);
		अगर (!cpuidle_रेजिस्टर_driver(&apm_idle_driver))
			अगर (cpuidle_रेजिस्टर_device(&apm_cpuidle_device))
				cpuidle_unरेजिस्टर_driver(&apm_idle_driver);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास apm_निकास(व्योम)
अणु
	पूर्णांक error;

	cpuidle_unरेजिस्टर_device(&apm_cpuidle_device);
	cpuidle_unरेजिस्टर_driver(&apm_idle_driver);

	अगर (((apm_info.bios.flags & APM_BIOS_DISENGAGED) == 0)
	    && (apm_info.connection_version > 0x0100)) अणु
		error = apm_engage_घातer_management(APM_DEVICE_ALL, 0);
		अगर (error)
			apm_error("disengage power management", error);
	पूर्ण
	misc_deरेजिस्टर(&apm_device);
	हटाओ_proc_entry("apm", शून्य);
	अगर (घातer_off)
		pm_घातer_off = शून्य;
	अगर (kapmd_task) अणु
		kthपढ़ो_stop(kapmd_task);
		kapmd_task = शून्य;
	पूर्ण
पूर्ण

module_init(apm_init);
module_निकास(apm_निकास);

MODULE_AUTHOR("Stephen Rothwell");
MODULE_DESCRIPTION("Advanced Power Management");
MODULE_LICENSE("GPL");
module_param(debug, bool, 0644);
MODULE_PARM_DESC(debug, "Enable debug mode");
module_param(घातer_off, bool, 0444);
MODULE_PARM_DESC(घातer_off, "Enable power off");
module_param(bounce_पूर्णांकerval, पूर्णांक, 0444);
MODULE_PARM_DESC(bounce_पूर्णांकerval,
		"Set the number of ticks to ignore suspend bounces");
module_param(allow_पूर्णांकs, bool, 0444);
MODULE_PARM_DESC(allow_पूर्णांकs, "Allow interrupts during BIOS calls");
module_param(broken_psr, bool, 0444);
MODULE_PARM_DESC(broken_psr, "BIOS has a broken GetPowerStatus call");
module_param(realmode_घातer_off, bool, 0444);
MODULE_PARM_DESC(realmode_घातer_off,
		"Switch to real mode before powering off");
module_param(idle_threshold, पूर्णांक, 0444);
MODULE_PARM_DESC(idle_threshold,
	"System idle percentage above which to make APM BIOS idle calls");
module_param(idle_period, पूर्णांक, 0444);
MODULE_PARM_DESC(idle_period,
	"Period (in sec/100) over which to calculate the idle percentage");
module_param(smp, bool, 0444);
MODULE_PARM_DESC(smp,
	"Set this to enable APM use on an SMP platform. Use with caution on older systems");
MODULE_ALIAS_MISCDEV(APM_MINOR_DEV);
