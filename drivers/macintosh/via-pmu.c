<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Device driver क्रम the PMU in Apple PowerBooks and PowerMacs.
 *
 * The VIA (versatile पूर्णांकerface adapter) पूर्णांकerfaces to the PMU,
 * a 6805 microprocessor core whose primary function is to control
 * battery अक्षरging and प्रणाली घातer on the PowerBook 3400 and 2400.
 * The PMU also controls the ADB (Apple Desktop Bus) which connects
 * to the keyboard and mouse, as well as the non-अस्थिर RAM
 * and the RTC (real समय घड़ी) chip.
 *
 * Copyright (C) 1998 Paul Mackerras and Fabio Riccardi.
 * Copyright (C) 2001-2002 Benjamin Herrenschmidt
 * Copyright (C) 2006-2007 Johannes Berg
 *
 * THIS DRIVER IS BECOMING A TOTAL MESS !
 *  - Cleanup atomically disabling reply to PMU events after
 *    a sleep or a freq. चयन
 *
 */
#समावेश <मानकतर्क.स>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <linux/cuda.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/suspend.h>
#समावेश <linux/cpu.h>
#समावेश <linux/compat.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/irq.h>
#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/pmac_pfunc.h>
#समावेश <यंत्र/pmac_low_i2c.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/backlight.h>
#अन्यथा
#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/mac_via.h>
#पूर्ण_अगर

#समावेश "via-pmu-event.h"

/* Some compile options */
#अघोषित DEBUG_SLEEP

/* How many iterations between battery polls */
#घोषणा BATTERY_POLLING_COUNT	2

अटल DEFINE_MUTEX(pmu_info_proc_mutex);

/* VIA रेजिस्टरs - spaced 0x200 bytes apart */
#घोषणा RS		0x200		/* skip between रेजिस्टरs */
#घोषणा B		0		/* B-side data */
#घोषणा A		RS		/* A-side data */
#घोषणा सूचीB		(2*RS)		/* B-side direction (1=output) */
#घोषणा सूचीA		(3*RS)		/* A-side direction (1=output) */
#घोषणा T1CL		(4*RS)		/* Timer 1 ctr/latch (low 8 bits) */
#घोषणा T1CH		(5*RS)		/* Timer 1 counter (high 8 bits) */
#घोषणा T1LL		(6*RS)		/* Timer 1 latch (low 8 bits) */
#घोषणा T1LH		(7*RS)		/* Timer 1 latch (high 8 bits) */
#घोषणा T2CL		(8*RS)		/* Timer 2 ctr/latch (low 8 bits) */
#घोषणा T2CH		(9*RS)		/* Timer 2 counter (high 8 bits) */
#घोषणा SR		(10*RS)		/* Shअगरt रेजिस्टर */
#घोषणा ACR		(11*RS)		/* Auxiliary control रेजिस्टर */
#घोषणा PCR		(12*RS)		/* Peripheral control रेजिस्टर */
#घोषणा IFR		(13*RS)		/* Interrupt flag रेजिस्टर */
#घोषणा IER		(14*RS)		/* Interrupt enable रेजिस्टर */
#घोषणा ANH		(15*RS)		/* A-side data, no handshake */

/* Bits in B data रेजिस्टर: both active low */
#अगर_घोषित CONFIG_PPC_PMAC
#घोषणा TACK		0x08		/* Transfer acknowledge (input) */
#घोषणा TREQ		0x10		/* Transfer request (output) */
#अन्यथा
#घोषणा TACK		0x02
#घोषणा TREQ		0x04
#पूर्ण_अगर

/* Bits in ACR */
#घोषणा SR_CTRL		0x1c		/* Shअगरt रेजिस्टर control bits */
#घोषणा SR_EXT		0x0c		/* Shअगरt on बाह्यal घड़ी */
#घोषणा SR_OUT		0x10		/* Shअगरt out अगर 1 */

/* Bits in IFR and IER */
#घोषणा IER_SET		0x80		/* set bits in IER */
#घोषणा IER_CLR		0		/* clear bits in IER */
#घोषणा SR_INT		0x04		/* Shअगरt रेजिस्टर full/empty */
#घोषणा CB2_INT		0x08
#घोषणा CB1_INT		0x10		/* transition on CB1 input */

अटल अस्थिर क्रमागत pmu_state अणु
	uninitialized = 0,
	idle,
	sending,
	पूर्णांकack,
	पढ़ोing,
	पढ़ोing_पूर्णांकr,
	locked,
पूर्ण pmu_state;

अटल अस्थिर क्रमागत पूर्णांक_data_state अणु
	पूर्णांक_data_empty,
	पूर्णांक_data_fill,
	पूर्णांक_data_पढ़ोy,
	पूर्णांक_data_flush
पूर्ण पूर्णांक_data_state[2] = अणु पूर्णांक_data_empty, पूर्णांक_data_empty पूर्ण;

अटल काष्ठा adb_request *current_req;
अटल काष्ठा adb_request *last_req;
अटल काष्ठा adb_request *req_aरुकोing_reply;
अटल अचिन्हित अक्षर पूर्णांकerrupt_data[2][32];
अटल पूर्णांक पूर्णांकerrupt_data_len[2];
अटल पूर्णांक पूर्णांक_data_last;
अटल अचिन्हित अक्षर *reply_ptr;
अटल पूर्णांक data_index;
अटल पूर्णांक data_len;
अटल अस्थिर पूर्णांक adb_पूर्णांक_pending;
अटल अस्थिर पूर्णांक disable_poll;
अटल पूर्णांक pmu_kind = PMU_UNKNOWN;
अटल पूर्णांक pmu_fully_inited;
अटल पूर्णांक pmu_has_adb;
#अगर_घोषित CONFIG_PPC_PMAC
अटल अस्थिर अचिन्हित अक्षर __iomem *via1;
अटल अस्थिर अचिन्हित अक्षर __iomem *via2;
अटल काष्ठा device_node *vias;
अटल काष्ठा device_node *gpio_node;
#पूर्ण_अगर
अटल अचिन्हित अक्षर __iomem *gpio_reg;
अटल पूर्णांक gpio_irq = 0;
अटल पूर्णांक gpio_irq_enabled = -1;
अटल अस्थिर पूर्णांक pmu_suspended;
अटल spinlock_t pmu_lock;
अटल u8 pmu_पूर्णांकr_mask;
अटल पूर्णांक pmu_version;
अटल पूर्णांक drop_पूर्णांकerrupts;
#अगर defined(CONFIG_SUSPEND) && defined(CONFIG_PPC32)
अटल पूर्णांक option_lid_wakeup = 1;
#पूर्ण_अगर /* CONFIG_SUSPEND && CONFIG_PPC32 */
अटल अचिन्हित दीर्घ async_req_locks;

#घोषणा NUM_IRQ_STATS 13
अटल अचिन्हित पूर्णांक pmu_irq_stats[NUM_IRQ_STATS];

अटल काष्ठा proc_dir_entry *proc_pmu_root;
अटल काष्ठा proc_dir_entry *proc_pmu_info;
अटल काष्ठा proc_dir_entry *proc_pmu_irqstats;
अटल काष्ठा proc_dir_entry *proc_pmu_options;
अटल पूर्णांक option_server_mode;

पूर्णांक pmu_battery_count;
अटल पूर्णांक pmu_cur_battery;
अचिन्हित पूर्णांक pmu_घातer_flags = PMU_PWR_AC_PRESENT;
काष्ठा pmu_battery_info pmu_batteries[PMU_MAX_BATTERIES];
अटल पूर्णांक query_batt_समयr = BATTERY_POLLING_COUNT;
अटल काष्ठा adb_request batt_req;
अटल काष्ठा proc_dir_entry *proc_pmu_batt[PMU_MAX_BATTERIES];

पूर्णांक asleep;

#अगर_घोषित CONFIG_ADB
अटल पूर्णांक adb_dev_map;
अटल पूर्णांक pmu_adb_flags;

अटल पूर्णांक pmu_probe(व्योम);
अटल पूर्णांक pmu_init(व्योम);
अटल पूर्णांक pmu_send_request(काष्ठा adb_request *req, पूर्णांक sync);
अटल पूर्णांक pmu_adb_स्वतःpoll(पूर्णांक devs);
अटल पूर्णांक pmu_adb_reset_bus(व्योम);
#पूर्ण_अगर /* CONFIG_ADB */

अटल पूर्णांक init_pmu(व्योम);
अटल व्योम pmu_start(व्योम);
अटल irqवापस_t via_pmu_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg);
अटल irqवापस_t gpio1_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg);
अटल पूर्णांक pmu_info_proc_show(काष्ठा seq_file *m, व्योम *v);
अटल पूर्णांक pmu_irqstats_proc_show(काष्ठा seq_file *m, व्योम *v);
अटल पूर्णांक pmu_battery_proc_show(काष्ठा seq_file *m, व्योम *v);
अटल व्योम pmu_pass_पूर्णांकr(अचिन्हित अक्षर *data, पूर्णांक len);
अटल स्थिर काष्ठा proc_ops pmu_options_proc_ops;

#अगर_घोषित CONFIG_ADB
स्थिर काष्ठा adb_driver via_pmu_driver = अणु
	.name         = "PMU",
	.probe        = pmu_probe,
	.init         = pmu_init,
	.send_request = pmu_send_request,
	.स्वतःpoll     = pmu_adb_स्वतःpoll,
	.poll         = pmu_poll_adb,
	.reset_bus    = pmu_adb_reset_bus,
पूर्ण;
#पूर्ण_अगर /* CONFIG_ADB */

बाह्य व्योम low_sleep_handler(व्योम);
बाह्य व्योम enable_kernel_altivec(व्योम);
बाह्य व्योम enable_kernel_fp(व्योम);

#अगर_घोषित DEBUG_SLEEP
पूर्णांक pmu_polled_request(काष्ठा adb_request *req);
व्योम pmu_blink(पूर्णांक n);
#पूर्ण_अगर

/*
 * This table indicates क्रम each PMU opcode:
 * - the number of data bytes to be sent with the command, or -1
 *   अगर a length byte should be sent,
 * - the number of response bytes which the PMU will वापस, or
 *   -1 अगर it will send a length byte.
 */
अटल स्थिर s8 pmu_data_len[256][2] = अणु
/*	   0	   1	   2	   3	   4	   5	   6	   7  */
/*00*/	अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*08*/	अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,
/*10*/	अणु 1, 0पूर्ण,अणु 1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*18*/	अणु 0, 1पूर्ण,अणु 0, 1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु 0, 0पूर्ण,
/*20*/	अणु-1, 0पूर्ण,अणु 0, 0पूर्ण,अणु 2, 0पूर्ण,अणु 1, 0पूर्ण,अणु 1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*28*/	अणु 0,-1पूर्ण,अणु 0,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु 0,-1पूर्ण,
/*30*/	अणु 4, 0पूर्ण,अणु20, 0पूर्ण,अणु-1, 0पूर्ण,अणु 3, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*38*/	अणु 0, 4पूर्ण,अणु 0,20पूर्ण,अणु 2,-1पूर्ण,अणु 2, 1पूर्ण,अणु 3,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु 4, 0पूर्ण,
/*40*/	अणु 1, 0पूर्ण,अणु 1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*48*/	अणु 0, 1पूर्ण,अणु 0, 1पूर्ण,अणु-1,-1पूर्ण,अणु 1, 0पूर्ण,अणु 1, 0पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,
/*50*/	अणु 1, 0पूर्ण,अणु 0, 0पूर्ण,अणु 2, 0पूर्ण,अणु 2, 0पूर्ण,अणु-1, 0पूर्ण,अणु 1, 0पूर्ण,अणु 3, 0पूर्ण,अणु 1, 0पूर्ण,
/*58*/	अणु 0, 1पूर्ण,अणु 1, 0पूर्ण,अणु 0, 2पूर्ण,अणु 0, 2पूर्ण,अणु 0,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,
/*60*/	अणु 2, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*68*/	अणु 0, 3पूर्ण,अणु 0, 3पूर्ण,अणु 0, 2पूर्ण,अणु 0, 8पूर्ण,अणु 0,-1पूर्ण,अणु 0,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,
/*70*/	अणु 1, 0पूर्ण,अणु 1, 0पूर्ण,अणु 1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*78*/	अणु 0,-1पूर्ण,अणु 0,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु 5, 1पूर्ण,अणु 4, 1पूर्ण,अणु 4, 1पूर्ण,
/*80*/	अणु 4, 0पूर्ण,अणु-1, 0पूर्ण,अणु 0, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*88*/	अणु 0, 5पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,
/*90*/	अणु 1, 0पूर्ण,अणु 2, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*98*/	अणु 0, 1पूर्ण,अणु 0, 1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,
/*a0*/	अणु 2, 0पूर्ण,अणु 2, 0पूर्ण,अणु 2, 0पूर्ण,अणु 4, 0पूर्ण,अणु-1, 0पूर्ण,अणु 0, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*a8*/	अणु 1, 1पूर्ण,अणु 1, 0पूर्ण,अणु 3, 0पूर्ण,अणु 2, 0पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,
/*b0*/	अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*b8*/	अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,
/*c0*/	अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*c8*/	अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,
/*d0*/	अणु 0, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*d8*/	अणु 1, 1पूर्ण,अणु 1, 1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु 0, 1पूर्ण,अणु 0,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,
/*e0*/	अणु-1, 0पूर्ण,अणु 4, 0पूर्ण,अणु 0, 1पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु 4, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*e8*/	अणु 3,-1पूर्ण,अणु-1,-1पूर्ण,अणु 0, 1पूर्ण,अणु-1,-1पूर्ण,अणु 0,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु 0, 0पूर्ण,
/*f0*/	अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,अणु-1, 0पूर्ण,
/*f8*/	अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,अणु-1,-1पूर्ण,
पूर्ण;

अटल अक्षर *pbook_type[] = अणु
	"Unknown PowerBook",
	"PowerBook 2400/3400/3500(G3)",
	"PowerBook G3 Series",
	"1999 PowerBook G3",
	"Core99"
पूर्ण;

पूर्णांक __init find_via_pmu(व्योम)
अणु
#अगर_घोषित CONFIG_PPC_PMAC
	u64 taddr;
	स्थिर u32 *reg;

	अगर (pmu_state != uninitialized)
		वापस 1;
	vias = of_find_node_by_name(शून्य, "via-pmu");
	अगर (vias == शून्य)
		वापस 0;

	reg = of_get_property(vias, "reg", शून्य);
	अगर (reg == शून्य) अणु
		prपूर्णांकk(KERN_ERR "via-pmu: No \"reg\" property !\n");
		जाओ fail;
	पूर्ण
	taddr = of_translate_address(vias, reg);
	अगर (taddr == OF_BAD_ADDR) अणु
		prपूर्णांकk(KERN_ERR "via-pmu: Can't translate address !\n");
		जाओ fail;
	पूर्ण

	spin_lock_init(&pmu_lock);

	pmu_has_adb = 1;

	pmu_पूर्णांकr_mask =	PMU_INT_PCEJECT |
			PMU_INT_SNDBRT |
			PMU_INT_ADB |
			PMU_INT_TICK;
	
	अगर (of_node_name_eq(vias->parent, "ohare") ||
	    of_device_is_compatible(vias->parent, "ohare"))
		pmu_kind = PMU_OHARE_BASED;
	अन्यथा अगर (of_device_is_compatible(vias->parent, "paddington"))
		pmu_kind = PMU_PADDINGTON_BASED;
	अन्यथा अगर (of_device_is_compatible(vias->parent, "heathrow"))
		pmu_kind = PMU_HEATHROW_BASED;
	अन्यथा अगर (of_device_is_compatible(vias->parent, "Keylargo")
		 || of_device_is_compatible(vias->parent, "K2-Keylargo")) अणु
		काष्ठा device_node *gpiop;
		काष्ठा device_node *adbp;
		u64 gaddr = OF_BAD_ADDR;

		pmu_kind = PMU_KEYLARGO_BASED;
		adbp = of_find_node_by_type(शून्य, "adb");
		pmu_has_adb = (adbp != शून्य);
		of_node_put(adbp);
		pmu_पूर्णांकr_mask =	PMU_INT_PCEJECT |
				PMU_INT_SNDBRT |
				PMU_INT_ADB |
				PMU_INT_TICK |
				PMU_INT_ENVIRONMENT;
		
		gpiop = of_find_node_by_name(शून्य, "gpio");
		अगर (gpiop) अणु
			reg = of_get_property(gpiop, "reg", शून्य);
			अगर (reg)
				gaddr = of_translate_address(gpiop, reg);
			अगर (gaddr != OF_BAD_ADDR)
				gpio_reg = ioremap(gaddr, 0x10);
			of_node_put(gpiop);
		पूर्ण
		अगर (gpio_reg == शून्य) अणु
			prपूर्णांकk(KERN_ERR "via-pmu: Can't find GPIO reg !\n");
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा
		pmu_kind = PMU_UNKNOWN;

	via1 = via2 = ioremap(taddr, 0x2000);
	अगर (via1 == शून्य) अणु
		prपूर्णांकk(KERN_ERR "via-pmu: Can't map address !\n");
		जाओ fail_via_remap;
	पूर्ण
	
	out_8(&via1[IER], IER_CLR | 0x7f);	/* disable all पूर्णांकrs */
	out_8(&via1[IFR], 0x7f);			/* clear IFR */

	pmu_state = idle;

	अगर (!init_pmu())
		जाओ fail_init;

	sys_ctrler = SYS_CTRLER_PMU;
	
	वापस 1;

 fail_init:
	iounmap(via1);
	via1 = via2 = शून्य;
 fail_via_remap:
	iounmap(gpio_reg);
	gpio_reg = शून्य;
 fail:
	of_node_put(vias);
	vias = शून्य;
	pmu_state = uninitialized;
	वापस 0;
#अन्यथा
	अगर (macपूर्णांकosh_config->adb_type != MAC_ADB_PB2)
		वापस 0;

	pmu_kind = PMU_UNKNOWN;

	spin_lock_init(&pmu_lock);

	pmu_has_adb = 1;

	pmu_पूर्णांकr_mask =	PMU_INT_PCEJECT |
			PMU_INT_SNDBRT |
			PMU_INT_ADB |
			PMU_INT_TICK;

	pmu_state = idle;

	अगर (!init_pmu()) अणु
		pmu_state = uninitialized;
		वापस 0;
	पूर्ण

	वापस 1;
#पूर्ण_अगर /* !CONFIG_PPC_PMAC */
पूर्ण

#अगर_घोषित CONFIG_ADB
अटल पूर्णांक pmu_probe(व्योम)
अणु
	वापस pmu_state == uninitialized ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक pmu_init(व्योम)
अणु
	वापस pmu_state == uninitialized ? -ENODEV : 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ADB */

/*
 * We can't रुको until pmu_init माला_लो called, that happens too late.
 * It happens after IDE and SCSI initialization, which can take a few
 * seconds, and by that समय the PMU could have given up on us and
 * turned us off.
 * Thus this is called with arch_initcall rather than device_initcall.
 */
अटल पूर्णांक __init via_pmu_start(व्योम)
अणु
	अचिन्हित पूर्णांक __maybe_unused irq;

	अगर (pmu_state == uninitialized)
		वापस -ENODEV;

	batt_req.complete = 1;

#अगर_घोषित CONFIG_PPC_PMAC
	irq = irq_of_parse_and_map(vias, 0);
	अगर (!irq) अणु
		prपूर्णांकk(KERN_ERR "via-pmu: can't map interrupt\n");
		वापस -ENODEV;
	पूर्ण
	/* We set IRQF_NO_SUSPEND because we करोn't want the पूर्णांकerrupt
	 * to be disabled between the 2 passes of driver suspend, we
	 * control our own disabling क्रम that one
	 */
	अगर (request_irq(irq, via_pmu_पूर्णांकerrupt, IRQF_NO_SUSPEND,
			"VIA-PMU", (व्योम *)0)) अणु
		prपूर्णांकk(KERN_ERR "via-pmu: can't request irq %d\n", irq);
		वापस -ENODEV;
	पूर्ण

	अगर (pmu_kind == PMU_KEYLARGO_BASED) अणु
		gpio_node = of_find_node_by_name(शून्य, "extint-gpio1");
		अगर (gpio_node == शून्य)
			gpio_node = of_find_node_by_name(शून्य,
							 "pmu-interrupt");
		अगर (gpio_node)
			gpio_irq = irq_of_parse_and_map(gpio_node, 0);

		अगर (gpio_irq) अणु
			अगर (request_irq(gpio_irq, gpio1_पूर्णांकerrupt,
					IRQF_NO_SUSPEND, "GPIO1 ADB",
					(व्योम *)0))
				prपूर्णांकk(KERN_ERR "pmu: can't get irq %d"
				       " (GPIO1)\n", gpio_irq);
			अन्यथा
				gpio_irq_enabled = 1;
		पूर्ण
	पूर्ण

	/* Enable पूर्णांकerrupts */
	out_8(&via1[IER], IER_SET | SR_INT | CB1_INT);
#अन्यथा
	अगर (request_irq(IRQ_MAC_ADB_SR, via_pmu_पूर्णांकerrupt, IRQF_NO_SUSPEND,
			"VIA-PMU-SR", शून्य)) अणु
		pr_err("%s: couldn't get SR irq\n", __func__);
		वापस -ENODEV;
	पूर्ण
	अगर (request_irq(IRQ_MAC_ADB_CL, via_pmu_पूर्णांकerrupt, IRQF_NO_SUSPEND,
			"VIA-PMU-CL", शून्य)) अणु
		pr_err("%s: couldn't get CL irq\n", __func__);
		मुक्त_irq(IRQ_MAC_ADB_SR, शून्य);
		वापस -ENODEV;
	पूर्ण
#पूर्ण_अगर /* !CONFIG_PPC_PMAC */

	pmu_fully_inited = 1;

	/* Make sure PMU settle करोwn beक्रमe continuing. This is _very_ important
	 * since the IDE probe may shut पूर्णांकerrupts करोwn क्रम quite a bit of समय. If
	 * a PMU communication is pending जबतक this happens, the PMU may समयout
	 * Not that on Core99 machines, the PMU keeps sending us environement
	 * messages, we should find a way to either fix IDE or make it call
	 * pmu_suspend() beक्रमe masking पूर्णांकerrupts. This can also happens जबतक
	 * scolling with some fbdevs.
	 */
	करो अणु
		pmu_poll();
	पूर्ण जबतक (pmu_state != idle);

	वापस 0;
पूर्ण

arch_initcall(via_pmu_start);

/*
 * This has to be करोne after pci_init, which is a subsys_initcall.
 */
अटल पूर्णांक __init via_pmu_dev_init(व्योम)
अणु
	अगर (pmu_state == uninitialized)
		वापस -ENODEV;

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	/* Initialize backlight */
	pmu_backlight_init();
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC32
  	अगर (of_machine_is_compatible("AAPL,3400/2400") ||
  		of_machine_is_compatible("AAPL,3500")) अणु
		पूर्णांक mb = pmac_call_feature(PMAC_FTR_GET_MB_INFO,
			शून्य, PMAC_MB_INFO_MODEL, 0);
		pmu_battery_count = 1;
		अगर (mb == PMAC_TYPE_COMET)
			pmu_batteries[0].flags |= PMU_BATT_TYPE_COMET;
		अन्यथा
			pmu_batteries[0].flags |= PMU_BATT_TYPE_HOOPER;
	पूर्ण अन्यथा अगर (of_machine_is_compatible("AAPL,PowerBook1998") ||
		of_machine_is_compatible("PowerBook1,1")) अणु
		pmu_battery_count = 2;
		pmu_batteries[0].flags |= PMU_BATT_TYPE_SMART;
		pmu_batteries[1].flags |= PMU_BATT_TYPE_SMART;
	पूर्ण अन्यथा अणु
		काष्ठा device_node* prim =
			of_find_node_by_name(शून्य, "power-mgt");
		स्थिर u32 *prim_info = शून्य;
		अगर (prim)
			prim_info = of_get_property(prim, "prim-info", शून्य);
		अगर (prim_info) अणु
			/* Other stuffs here yet unknown */
			pmu_battery_count = (prim_info[6] >> 16) & 0xff;
			pmu_batteries[0].flags |= PMU_BATT_TYPE_SMART;
			अगर (pmu_battery_count > 1)
				pmu_batteries[1].flags |= PMU_BATT_TYPE_SMART;
		पूर्ण
		of_node_put(prim);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC32 */

	/* Create /proc/pmu */
	proc_pmu_root = proc_सूची_गढ़ो("pmu", शून्य);
	अगर (proc_pmu_root) अणु
		दीर्घ i;

		क्रम (i=0; i<pmu_battery_count; i++) अणु
			अक्षर title[16];
			प्र_लिखो(title, "battery_%ld", i);
			proc_pmu_batt[i] = proc_create_single_data(title, 0,
					proc_pmu_root, pmu_battery_proc_show,
					(व्योम *)i);
		पूर्ण

		proc_pmu_info = proc_create_single("info", 0, proc_pmu_root,
				pmu_info_proc_show);
		proc_pmu_irqstats = proc_create_single("interrupts", 0,
				proc_pmu_root, pmu_irqstats_proc_show);
		proc_pmu_options = proc_create("options", 0600, proc_pmu_root,
						&pmu_options_proc_ops);
	पूर्ण
	वापस 0;
पूर्ण

device_initcall(via_pmu_dev_init);

अटल पूर्णांक
init_pmu(व्योम)
अणु
	पूर्णांक समयout;
	काष्ठा adb_request req;

	/* Negate TREQ. Set TACK to input and TREQ to output. */
	out_8(&via2[B], in_8(&via2[B]) | TREQ);
	out_8(&via2[सूचीB], (in_8(&via2[सूचीB]) | TREQ) & ~TACK);

	pmu_request(&req, शून्य, 2, PMU_SET_INTR_MASK, pmu_पूर्णांकr_mask);
	समयout =  100000;
	जबतक (!req.complete) अणु
		अगर (--समयout < 0) अणु
			prपूर्णांकk(KERN_ERR "init_pmu: no response from PMU\n");
			वापस 0;
		पूर्ण
		udelay(10);
		pmu_poll();
	पूर्ण

	/* ack all pending पूर्णांकerrupts */
	समयout = 100000;
	पूर्णांकerrupt_data[0][0] = 1;
	जबतक (पूर्णांकerrupt_data[0][0] || pmu_state != idle) अणु
		अगर (--समयout < 0) अणु
			prपूर्णांकk(KERN_ERR "init_pmu: timed out acking intrs\n");
			वापस 0;
		पूर्ण
		अगर (pmu_state == idle)
			adb_पूर्णांक_pending = 1;
		via_pmu_पूर्णांकerrupt(0, शून्य);
		udelay(10);
	पूर्ण

	/* Tell PMU we are पढ़ोy.  */
	अगर (pmu_kind == PMU_KEYLARGO_BASED) अणु
		pmu_request(&req, शून्य, 2, PMU_SYSTEM_READY, 2);
		जबतक (!req.complete)
			pmu_poll();
	पूर्ण

	/* Read PMU version */
	pmu_request(&req, शून्य, 1, PMU_GET_VERSION);
	pmu_रुको_complete(&req);
	अगर (req.reply_len > 0)
		pmu_version = req.reply[0];
	
	/* Read server mode setting */
	अगर (pmu_kind == PMU_KEYLARGO_BASED) अणु
		pmu_request(&req, शून्य, 2, PMU_POWER_EVENTS,
			    PMU_PWR_GET_POWERUP_EVENTS);
		pmu_रुको_complete(&req);
		अगर (req.reply_len == 2) अणु
			अगर (req.reply[1] & PMU_PWR_WAKEUP_AC_INSERT)
				option_server_mode = 1;
			prपूर्णांकk(KERN_INFO "via-pmu: Server Mode is %s\n",
			       option_server_mode ? "enabled" : "disabled");
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_INFO "PMU driver v%d initialized for %s, firmware: %02x\n",
	       PMU_DRIVER_VERSION, pbook_type[pmu_kind], pmu_version);

	वापस 1;
पूर्ण

पूर्णांक
pmu_get_model(व्योम)
अणु
	वापस pmu_kind;
पूर्ण

अटल व्योम pmu_set_server_mode(पूर्णांक server_mode)
अणु
	काष्ठा adb_request req;

	अगर (pmu_kind != PMU_KEYLARGO_BASED)
		वापस;

	option_server_mode = server_mode;
	pmu_request(&req, शून्य, 2, PMU_POWER_EVENTS, PMU_PWR_GET_POWERUP_EVENTS);
	pmu_रुको_complete(&req);
	अगर (req.reply_len < 2)
		वापस;
	अगर (server_mode)
		pmu_request(&req, शून्य, 4, PMU_POWER_EVENTS,
			    PMU_PWR_SET_POWERUP_EVENTS,
			    req.reply[0], PMU_PWR_WAKEUP_AC_INSERT); 
	अन्यथा
		pmu_request(&req, शून्य, 4, PMU_POWER_EVENTS,
			    PMU_PWR_CLR_POWERUP_EVENTS,
			    req.reply[0], PMU_PWR_WAKEUP_AC_INSERT); 
	pmu_रुको_complete(&req);
पूर्ण

/* This new version of the code क्रम 2400/3400/3500 घातerbooks
 * is inspired from the implementation in gkrellm-pmu
 */
अटल व्योम
करोne_battery_state_ohare(काष्ठा adb_request* req)
अणु
#अगर_घोषित CONFIG_PPC_PMAC
	/* क्रमmat:
	 *  [0]    :  flags
	 *    0x01 :  AC indicator
	 *    0x02 :  अक्षरging
	 *    0x04 :  battery exist
	 *    0x08 :  
	 *    0x10 :  
	 *    0x20 :  full अक्षरged
	 *    0x40 :  pअक्षरge reset
	 *    0x80 :  battery exist
	 *
	 *  [1][2] :  battery voltage
	 *  [3]    :  CPU temperature
	 *  [4]    :  battery temperature
	 *  [5]    :  current
	 *  [6][7] :  pअक्षरge
	 *              --tkoba
	 */
	अचिन्हित पूर्णांक bat_flags = PMU_BATT_TYPE_HOOPER;
	दीर्घ pअक्षरge, अक्षरge, vb, vmax, lmax;
	दीर्घ vmax_अक्षरging, vmax_अक्षरged;
	दीर्घ amperage, voltage, समय, max;
	पूर्णांक mb = pmac_call_feature(PMAC_FTR_GET_MB_INFO,
			शून्य, PMAC_MB_INFO_MODEL, 0);

	अगर (req->reply[0] & 0x01)
		pmu_घातer_flags |= PMU_PWR_AC_PRESENT;
	अन्यथा
		pmu_घातer_flags &= ~PMU_PWR_AC_PRESENT;
	
	अगर (mb == PMAC_TYPE_COMET) अणु
		vmax_अक्षरged = 189;
		vmax_अक्षरging = 213;
		lmax = 6500;
	पूर्ण अन्यथा अणु
		vmax_अक्षरged = 330;
		vmax_अक्षरging = 330;
		lmax = 6500;
	पूर्ण
	vmax = vmax_अक्षरged;

	/* If battery installed */
	अगर (req->reply[0] & 0x04) अणु
		bat_flags |= PMU_BATT_PRESENT;
		अगर (req->reply[0] & 0x02)
			bat_flags |= PMU_BATT_CHARGING;
		vb = (req->reply[1] << 8) | req->reply[2];
		voltage = (vb * 265 + 72665) / 10;
		amperage = req->reply[5];
		अगर ((req->reply[0] & 0x01) == 0) अणु
			अगर (amperage > 200)
				vb += ((amperage - 200) * 15)/100;
		पूर्ण अन्यथा अगर (req->reply[0] & 0x02) अणु
			vb = (vb * 97) / 100;
			vmax = vmax_अक्षरging;
		पूर्ण
		अक्षरge = (100 * vb) / vmax;
		अगर (req->reply[0] & 0x40) अणु
			pअक्षरge = (req->reply[6] << 8) + req->reply[7];
			अगर (pअक्षरge > lmax)
				pअक्षरge = lmax;
			pअक्षरge *= 100;
			pअक्षरge = 100 - pअक्षरge / lmax;
			अगर (pअक्षरge < अक्षरge)
				अक्षरge = pअक्षरge;
		पूर्ण
		अगर (amperage > 0)
			समय = (अक्षरge * 16440) / amperage;
		अन्यथा
			समय = 0;
		max = 100;
		amperage = -amperage;
	पूर्ण अन्यथा
		अक्षरge = max = amperage = voltage = समय = 0;

	pmu_batteries[pmu_cur_battery].flags = bat_flags;
	pmu_batteries[pmu_cur_battery].अक्षरge = अक्षरge;
	pmu_batteries[pmu_cur_battery].max_अक्षरge = max;
	pmu_batteries[pmu_cur_battery].amperage = amperage;
	pmu_batteries[pmu_cur_battery].voltage = voltage;
	pmu_batteries[pmu_cur_battery].समय_reमुख्यing = समय;
#पूर्ण_अगर /* CONFIG_PPC_PMAC */

	clear_bit(0, &async_req_locks);
पूर्ण

अटल व्योम
करोne_battery_state_smart(काष्ठा adb_request* req)
अणु
	/* क्रमmat:
	 *  [0] : क्रमmat of this काष्ठाure (known: 3,4,5)
	 *  [1] : flags
	 *  
	 *  क्रमmat 3 & 4:
	 *  
	 *  [2] : अक्षरge
	 *  [3] : max अक्षरge
	 *  [4] : current
	 *  [5] : voltage
	 *  
	 *  क्रमmat 5:
	 *  
	 *  [2][3] : अक्षरge
	 *  [4][5] : max अक्षरge
	 *  [6][7] : current
	 *  [8][9] : voltage
	 */
	 
	अचिन्हित पूर्णांक bat_flags = PMU_BATT_TYPE_SMART;
	पूर्णांक amperage;
	अचिन्हित पूर्णांक capa, max, voltage;
	
	अगर (req->reply[1] & 0x01)
		pmu_घातer_flags |= PMU_PWR_AC_PRESENT;
	अन्यथा
		pmu_घातer_flags &= ~PMU_PWR_AC_PRESENT;


	capa = max = amperage = voltage = 0;
	
	अगर (req->reply[1] & 0x04) अणु
		bat_flags |= PMU_BATT_PRESENT;
		चयन(req->reply[0]) अणु
			हाल 3:
			हाल 4: capa = req->reply[2];
				max = req->reply[3];
				amperage = *((चिन्हित अक्षर *)&req->reply[4]);
				voltage = req->reply[5];
				अवरोध;
			हाल 5: capa = (req->reply[2] << 8) | req->reply[3];
				max = (req->reply[4] << 8) | req->reply[5];
				amperage = *((चिन्हित लघु *)&req->reply[6]);
				voltage = (req->reply[8] << 8) | req->reply[9];
				अवरोध;
			शेष:
				pr_warn("pmu.c: unrecognized battery info, "
					"len: %d, %4ph\n", req->reply_len,
							   req->reply);
				अवरोध;
		पूर्ण
	पूर्ण

	अगर ((req->reply[1] & 0x01) && (amperage > 0))
		bat_flags |= PMU_BATT_CHARGING;

	pmu_batteries[pmu_cur_battery].flags = bat_flags;
	pmu_batteries[pmu_cur_battery].अक्षरge = capa;
	pmu_batteries[pmu_cur_battery].max_अक्षरge = max;
	pmu_batteries[pmu_cur_battery].amperage = amperage;
	pmu_batteries[pmu_cur_battery].voltage = voltage;
	अगर (amperage) अणु
		अगर ((req->reply[1] & 0x01) && (amperage > 0))
			pmu_batteries[pmu_cur_battery].समय_reमुख्यing
				= ((max-capa) * 3600) / amperage;
		अन्यथा
			pmu_batteries[pmu_cur_battery].समय_reमुख्यing
				= (capa * 3600) / (-amperage);
	पूर्ण अन्यथा
		pmu_batteries[pmu_cur_battery].समय_reमुख्यing = 0;

	pmu_cur_battery = (pmu_cur_battery + 1) % pmu_battery_count;

	clear_bit(0, &async_req_locks);
पूर्ण

अटल व्योम
query_battery_state(व्योम)
अणु
	अगर (test_and_set_bit(0, &async_req_locks))
		वापस;
	अगर (pmu_kind == PMU_OHARE_BASED)
		pmu_request(&batt_req, करोne_battery_state_ohare,
			1, PMU_BATTERY_STATE);
	अन्यथा
		pmu_request(&batt_req, करोne_battery_state_smart,
			2, PMU_SMART_BATTERY_STATE, pmu_cur_battery+1);
पूर्ण

अटल पूर्णांक pmu_info_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "PMU driver version     : %d\n", PMU_DRIVER_VERSION);
	seq_म_लिखो(m, "PMU firmware version   : %02x\n", pmu_version);
	seq_म_लिखो(m, "AC Power               : %d\n",
		((pmu_घातer_flags & PMU_PWR_AC_PRESENT) != 0) || pmu_battery_count == 0);
	seq_म_लिखो(m, "Battery count          : %d\n", pmu_battery_count);

	वापस 0;
पूर्ण

अटल पूर्णांक pmu_irqstats_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;
	अटल स्थिर अक्षर *irq_names[NUM_IRQ_STATS] = अणु
		"Unknown interrupt (type 0)",
		"Unknown interrupt (type 1)",
		"PC-Card eject button",
		"Sound/Brightness button",
		"ADB message",
		"Battery state change",
		"Environment interrupt",
		"Tick timer",
		"Ghost interrupt (zero len)",
		"Empty interrupt (empty mask)",
		"Max irqs in a row",
		"Total CB1 triggered events",
		"Total GPIO1 triggered events",
        पूर्ण;

	क्रम (i = 0; i < NUM_IRQ_STATS; i++) अणु
		seq_म_लिखो(m, " %2u: %10u (%s)\n",
			     i, pmu_irq_stats[i], irq_names[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pmu_battery_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	दीर्घ batnum = (दीर्घ)m->निजी;
	
	seq_अ_दो(m, '\n');
	seq_म_लिखो(m, "flags      : %08x\n", pmu_batteries[batnum].flags);
	seq_म_लिखो(m, "charge     : %d\n", pmu_batteries[batnum].अक्षरge);
	seq_म_लिखो(m, "max_charge : %d\n", pmu_batteries[batnum].max_अक्षरge);
	seq_म_लिखो(m, "current    : %d\n", pmu_batteries[batnum].amperage);
	seq_म_लिखो(m, "voltage    : %d\n", pmu_batteries[batnum].voltage);
	seq_म_लिखो(m, "time rem.  : %d\n", pmu_batteries[batnum].समय_reमुख्यing);
	वापस 0;
पूर्ण

अटल पूर्णांक pmu_options_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
#अगर defined(CONFIG_SUSPEND) && defined(CONFIG_PPC32)
	अगर (pmu_kind == PMU_KEYLARGO_BASED &&
	    pmac_call_feature(PMAC_FTR_SLEEP_STATE,शून्य,0,-1) >= 0)
		seq_म_लिखो(m, "lid_wakeup=%d\n", option_lid_wakeup);
#पूर्ण_अगर
	अगर (pmu_kind == PMU_KEYLARGO_BASED)
		seq_म_लिखो(m, "server_mode=%d\n", option_server_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक pmu_options_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, pmu_options_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार pmu_options_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	अक्षर पंचांगp[33];
	अक्षर *label, *val;
	माप_प्रकार fcount = count;
	
	अगर (!count)
		वापस -EINVAL;
	अगर (count > 32)
		count = 32;
	अगर (copy_from_user(पंचांगp, buffer, count))
		वापस -EFAULT;
	पंचांगp[count] = 0;

	label = पंचांगp;
	जबतक(*label == ' ')
		label++;
	val = label;
	जबतक(*val && (*val != '=')) अणु
		अगर (*val == ' ')
			*val = 0;
		val++;
	पूर्ण
	अगर ((*val) == 0)
		वापस -EINVAL;
	*(val++) = 0;
	जबतक(*val == ' ')
		val++;
#अगर defined(CONFIG_SUSPEND) && defined(CONFIG_PPC32)
	अगर (pmu_kind == PMU_KEYLARGO_BASED &&
	    pmac_call_feature(PMAC_FTR_SLEEP_STATE,शून्य,0,-1) >= 0)
		अगर (!म_भेद(label, "lid_wakeup"))
			option_lid_wakeup = ((*val) == '1');
#पूर्ण_अगर
	अगर (pmu_kind == PMU_KEYLARGO_BASED && !म_भेद(label, "server_mode")) अणु
		पूर्णांक new_value;
		new_value = ((*val) == '1');
		अगर (new_value != option_server_mode)
			pmu_set_server_mode(new_value);
	पूर्ण
	वापस fcount;
पूर्ण

अटल स्थिर काष्ठा proc_ops pmu_options_proc_ops = अणु
	.proc_खोलो	= pmu_options_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= pmu_options_proc_ग_लिखो,
पूर्ण;

#अगर_घोषित CONFIG_ADB
/* Send an ADB command */
अटल पूर्णांक pmu_send_request(काष्ठा adb_request *req, पूर्णांक sync)
अणु
	पूर्णांक i, ret;

	अगर (pmu_state == uninitialized || !pmu_fully_inited) अणु
		req->complete = 1;
		वापस -ENXIO;
	पूर्ण

	ret = -EINVAL;

	चयन (req->data[0]) अणु
	हाल PMU_PACKET:
		क्रम (i = 0; i < req->nbytes - 1; ++i)
			req->data[i] = req->data[i+1];
		--req->nbytes;
		अगर (pmu_data_len[req->data[0]][1] != 0) अणु
			req->reply[0] = ADB_RET_OK;
			req->reply_len = 1;
		पूर्ण अन्यथा
			req->reply_len = 0;
		ret = pmu_queue_request(req);
		अवरोध;
	हाल CUDA_PACKET:
		चयन (req->data[1]) अणु
		हाल CUDA_GET_TIME:
			अगर (req->nbytes != 2)
				अवरोध;
			req->data[0] = PMU_READ_RTC;
			req->nbytes = 1;
			req->reply_len = 3;
			req->reply[0] = CUDA_PACKET;
			req->reply[1] = 0;
			req->reply[2] = CUDA_GET_TIME;
			ret = pmu_queue_request(req);
			अवरोध;
		हाल CUDA_SET_TIME:
			अगर (req->nbytes != 6)
				अवरोध;
			req->data[0] = PMU_SET_RTC;
			req->nbytes = 5;
			क्रम (i = 1; i <= 4; ++i)
				req->data[i] = req->data[i+1];
			req->reply_len = 3;
			req->reply[0] = CUDA_PACKET;
			req->reply[1] = 0;
			req->reply[2] = CUDA_SET_TIME;
			ret = pmu_queue_request(req);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ADB_PACKET:
	    	अगर (!pmu_has_adb)
    			वापस -ENXIO;
		क्रम (i = req->nbytes - 1; i > 1; --i)
			req->data[i+2] = req->data[i];
		req->data[3] = req->nbytes - 2;
		req->data[2] = pmu_adb_flags;
		/*req->data[1] = req->data[1];*/
		req->data[0] = PMU_ADB_CMD;
		req->nbytes += 2;
		req->reply_expected = 1;
		req->reply_len = 0;
		ret = pmu_queue_request(req);
		अवरोध;
	पूर्ण
	अगर (ret) अणु
		req->complete = 1;
		वापस ret;
	पूर्ण

	अगर (sync)
		जबतक (!req->complete)
			pmu_poll();

	वापस 0;
पूर्ण

/* Enable/disable स्वतःpolling */
अटल पूर्णांक __pmu_adb_स्वतःpoll(पूर्णांक devs)
अणु
	काष्ठा adb_request req;

	अगर (devs) अणु
		pmu_request(&req, शून्य, 5, PMU_ADB_CMD, 0, 0x86,
			    adb_dev_map >> 8, adb_dev_map);
		pmu_adb_flags = 2;
	पूर्ण अन्यथा अणु
		pmu_request(&req, शून्य, 1, PMU_ADB_POLL_OFF);
		pmu_adb_flags = 0;
	पूर्ण
	जबतक (!req.complete)
		pmu_poll();
	वापस 0;
पूर्ण

अटल पूर्णांक pmu_adb_स्वतःpoll(पूर्णांक devs)
अणु
	अगर (pmu_state == uninitialized || !pmu_fully_inited || !pmu_has_adb)
		वापस -ENXIO;

	adb_dev_map = devs;
	वापस __pmu_adb_स्वतःpoll(devs);
पूर्ण

/* Reset the ADB bus */
अटल पूर्णांक pmu_adb_reset_bus(व्योम)
अणु
	काष्ठा adb_request req;
	पूर्णांक save_स्वतःpoll = adb_dev_map;

	अगर (pmu_state == uninitialized || !pmu_fully_inited || !pmu_has_adb)
		वापस -ENXIO;

	/* anyone got a better idea?? */
	__pmu_adb_स्वतःpoll(0);

	req.nbytes = 4;
	req.करोne = शून्य;
	req.data[0] = PMU_ADB_CMD;
	req.data[1] = ADB_BUSRESET;
	req.data[2] = 0;
	req.data[3] = 0;
	req.data[4] = 0;
	req.reply_len = 0;
	req.reply_expected = 1;
	अगर (pmu_queue_request(&req) != 0) अणु
		prपूर्णांकk(KERN_ERR "pmu_adb_reset_bus: pmu_queue_request failed\n");
		वापस -EIO;
	पूर्ण
	pmu_रुको_complete(&req);

	अगर (save_स्वतःpoll != 0)
		__pmu_adb_स्वतःpoll(save_स्वतःpoll);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ADB */

/* Conकाष्ठा and send a pmu request */
पूर्णांक
pmu_request(काष्ठा adb_request *req, व्योम (*करोne)(काष्ठा adb_request *),
	    पूर्णांक nbytes, ...)
अणु
	बहु_सूची list;
	पूर्णांक i;

	अगर (pmu_state == uninitialized)
		वापस -ENXIO;

	अगर (nbytes < 0 || nbytes > 32) अणु
		prपूर्णांकk(KERN_ERR "pmu_request: bad nbytes (%d)\n", nbytes);
		req->complete = 1;
		वापस -EINVAL;
	पूर्ण
	req->nbytes = nbytes;
	req->करोne = करोne;
	बहु_शुरू(list, nbytes);
	क्रम (i = 0; i < nbytes; ++i)
		req->data[i] = बहु_तर्क(list, पूर्णांक);
	बहु_पूर्ण(list);
	req->reply_len = 0;
	req->reply_expected = 0;
	वापस pmu_queue_request(req);
पूर्ण

पूर्णांक
pmu_queue_request(काष्ठा adb_request *req)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक nsend;

	अगर (pmu_state == uninitialized) अणु
		req->complete = 1;
		वापस -ENXIO;
	पूर्ण
	अगर (req->nbytes <= 0) अणु
		req->complete = 1;
		वापस 0;
	पूर्ण
	nsend = pmu_data_len[req->data[0]][0];
	अगर (nsend >= 0 && req->nbytes != nsend + 1) अणु
		req->complete = 1;
		वापस -EINVAL;
	पूर्ण

	req->next = शून्य;
	req->sent = 0;
	req->complete = 0;

	spin_lock_irqsave(&pmu_lock, flags);
	अगर (current_req) अणु
		last_req->next = req;
		last_req = req;
	पूर्ण अन्यथा अणु
		current_req = req;
		last_req = req;
		अगर (pmu_state == idle)
			pmu_start();
	पूर्ण
	spin_unlock_irqrestore(&pmu_lock, flags);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
रुको_क्रम_ack(व्योम)
अणु
	/* Sightly increased the delay, I had one occurrence of the message
	 * reported
	 */
	पूर्णांक समयout = 4000;
	जबतक ((in_8(&via2[B]) & TACK) == 0) अणु
		अगर (--समयout < 0) अणु
			prपूर्णांकk(KERN_ERR "PMU not responding (!ack)\n");
			वापस;
		पूर्ण
		udelay(10);
	पूर्ण
पूर्ण

/* New PMU seems to be very sensitive to those timings, so we make sure
 * PCI is flushed immediately */
अटल अंतरभूत व्योम
send_byte(पूर्णांक x)
अणु
	out_8(&via1[ACR], in_8(&via1[ACR]) | SR_OUT | SR_EXT);
	out_8(&via1[SR], x);
	out_8(&via2[B], in_8(&via2[B]) & ~TREQ);	/* निश्चित TREQ */
	(व्योम)in_8(&via2[B]);
पूर्ण

अटल अंतरभूत व्योम
recv_byte(व्योम)
अणु
	out_8(&via1[ACR], (in_8(&via1[ACR]) & ~SR_OUT) | SR_EXT);
	in_8(&via1[SR]);		/* resets SR */
	out_8(&via2[B], in_8(&via2[B]) & ~TREQ);
	(व्योम)in_8(&via2[B]);
पूर्ण

अटल अंतरभूत व्योम
pmu_करोne(काष्ठा adb_request *req)
अणु
	व्योम (*करोne)(काष्ठा adb_request *) = req->करोne;
	mb();
	req->complete = 1;
    	/* Here, we assume that अगर the request has a करोne member, the
    	 * काष्ठा request will survive to setting req->complete to 1
    	 */
	अगर (करोne)
		(*करोne)(req);
पूर्ण

अटल व्योम
pmu_start(व्योम)
अणु
	काष्ठा adb_request *req;

	/* निश्चित pmu_state == idle */
	/* get the packet to send */
	req = current_req;
	अगर (!req || pmu_state != idle
	    || (/*req->reply_expected && */req_aरुकोing_reply))
		वापस;

	pmu_state = sending;
	data_index = 1;
	data_len = pmu_data_len[req->data[0]][0];

	/* Sounds safer to make sure ACK is high beक्रमe writing. This helped
	 * समाप्त a problem with ADB and some iBooks
	 */
	रुको_क्रम_ack();
	/* set the shअगरt रेजिस्टर to shअगरt out and send a byte */
	send_byte(req->data[0]);
पूर्ण

व्योम
pmu_poll(व्योम)
अणु
	अगर (pmu_state == uninitialized)
		वापस;
	अगर (disable_poll)
		वापस;
	via_pmu_पूर्णांकerrupt(0, शून्य);
पूर्ण

व्योम
pmu_poll_adb(व्योम)
अणु
	अगर (pmu_state == uninitialized)
		वापस;
	अगर (disable_poll)
		वापस;
	/* Kicks ADB पढ़ो when PMU is suspended */
	adb_पूर्णांक_pending = 1;
	करो अणु
		via_pmu_पूर्णांकerrupt(0, शून्य);
	पूर्ण जबतक (pmu_suspended && (adb_पूर्णांक_pending || pmu_state != idle
		|| req_aरुकोing_reply));
पूर्ण

व्योम
pmu_रुको_complete(काष्ठा adb_request *req)
अणु
	अगर (pmu_state == uninitialized)
		वापस;
	जबतक((pmu_state != idle && pmu_state != locked) || !req->complete)
		via_pmu_पूर्णांकerrupt(0, शून्य);
पूर्ण

/* This function loops until the PMU is idle and prevents it from
 * anwsering to ADB पूर्णांकerrupts. pmu_request can still be called.
 * This is करोne to aव्योम spurrious shutकरोwns when we know we'll have
 * पूर्णांकerrupts चयनed off क्रम a दीर्घ समय
 */
व्योम
pmu_suspend(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	अगर (pmu_state == uninitialized)
		वापस;
	
	spin_lock_irqsave(&pmu_lock, flags);
	pmu_suspended++;
	अगर (pmu_suspended > 1) अणु
		spin_unlock_irqrestore(&pmu_lock, flags);
		वापस;
	पूर्ण

	करो अणु
		spin_unlock_irqrestore(&pmu_lock, flags);
		अगर (req_aरुकोing_reply)
			adb_पूर्णांक_pending = 1;
		via_pmu_पूर्णांकerrupt(0, शून्य);
		spin_lock_irqsave(&pmu_lock, flags);
		अगर (!adb_पूर्णांक_pending && pmu_state == idle && !req_aरुकोing_reply) अणु
			अगर (gpio_irq >= 0)
				disable_irq_nosync(gpio_irq);
			out_8(&via1[IER], CB1_INT | IER_CLR);
			spin_unlock_irqrestore(&pmu_lock, flags);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);
पूर्ण

व्योम
pmu_resume(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	अगर (pmu_state == uninitialized || pmu_suspended < 1)
		वापस;

	spin_lock_irqsave(&pmu_lock, flags);
	pmu_suspended--;
	अगर (pmu_suspended > 0) अणु
		spin_unlock_irqrestore(&pmu_lock, flags);
		वापस;
	पूर्ण
	adb_पूर्णांक_pending = 1;
	अगर (gpio_irq >= 0)
		enable_irq(gpio_irq);
	out_8(&via1[IER], CB1_INT | IER_SET);
	spin_unlock_irqrestore(&pmu_lock, flags);
	pmu_poll();
पूर्ण

/* Interrupt data could be the result data from an ADB cmd */
अटल व्योम
pmu_handle_data(अचिन्हित अक्षर *data, पूर्णांक len)
अणु
	अचिन्हित अक्षर पूर्णांकs;
	पूर्णांक idx;
	पूर्णांक i = 0;

	asleep = 0;
	अगर (drop_पूर्णांकerrupts || len < 1) अणु
		adb_पूर्णांक_pending = 0;
		pmu_irq_stats[8]++;
		वापस;
	पूर्ण

	/* Get PMU पूर्णांकerrupt mask */
	पूर्णांकs = data[0];

	/* Record zero पूर्णांकerrupts क्रम stats */
	अगर (पूर्णांकs == 0)
		pmu_irq_stats[9]++;

	/* Hack to deal with ADB स्वतःpoll flag */
	अगर (पूर्णांकs & PMU_INT_ADB)
		पूर्णांकs &= ~(PMU_INT_ADB_AUTO | PMU_INT_AUTO_SRQ_POLL);

next:
	अगर (पूर्णांकs == 0) अणु
		अगर (i > pmu_irq_stats[10])
			pmu_irq_stats[10] = i;
		वापस;
	पूर्ण
	i++;

	idx = ffs(पूर्णांकs) - 1;
	पूर्णांकs &= ~BIT(idx);

	pmu_irq_stats[idx]++;

	/* Note: क्रम some reason, we get an पूर्णांकerrupt with len=1,
	 * data[0]==0 after each normal ADB पूर्णांकerrupt, at least
	 * on the Pismo. Still investigating...  --BenH
	 */
	चयन (BIT(idx)) अणु
	हाल PMU_INT_ADB:
		अगर ((data[0] & PMU_INT_ADB_AUTO) == 0) अणु
			काष्ठा adb_request *req = req_aरुकोing_reply;
			अगर (!req) अणु
				prपूर्णांकk(KERN_ERR "PMU: extra ADB reply\n");
				वापस;
			पूर्ण
			req_aरुकोing_reply = शून्य;
			अगर (len <= 2)
				req->reply_len = 0;
			अन्यथा अणु
				स_नकल(req->reply, data + 1, len - 1);
				req->reply_len = len - 1;
			पूर्ण
			pmu_करोne(req);
		पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_XMON
			अगर (len == 4 && data[1] == 0x2c) अणु
				बाह्य पूर्णांक xmon_wants_key, xmon_adb_keycode;
				अगर (xmon_wants_key) अणु
					xmon_adb_keycode = data[2];
					वापस;
				पूर्ण
			पूर्ण
#पूर्ण_अगर /* CONFIG_XMON */
#अगर_घोषित CONFIG_ADB
			/*
			 * XXX On the [23]400 the PMU gives us an up
			 * event क्रम keycodes 0x74 or 0x75 when the PC
			 * card eject buttons are released, so we
			 * ignore those events.
			 */
			अगर (!(pmu_kind == PMU_OHARE_BASED && len == 4
			      && data[1] == 0x2c && data[3] == 0xff
			      && (data[2] & ~1) == 0xf4))
				adb_input(data+1, len-1, 1);
#पूर्ण_अगर /* CONFIG_ADB */		
		पूर्ण
		अवरोध;

	/* Sound/brightness button pressed */
	हाल PMU_INT_SNDBRT:
#अगर_घोषित CONFIG_PMAC_BACKLIGHT
		अगर (len == 3)
			pmac_backlight_set_legacy_brightness_pmu(data[1] >> 4);
#पूर्ण_अगर
		अवरोध;

	/* Tick पूर्णांकerrupt */
	हाल PMU_INT_TICK:
		/* Environment or tick पूर्णांकerrupt, query batteries */
		अगर (pmu_battery_count) अणु
			अगर ((--query_batt_समयr) == 0) अणु
				query_battery_state();
				query_batt_समयr = BATTERY_POLLING_COUNT;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल PMU_INT_ENVIRONMENT:
		अगर (pmu_battery_count)
			query_battery_state();
		pmu_pass_पूर्णांकr(data, len);
		/* len == 6 is probably a bad check. But how करो I
		 * know what PMU versions send what events here? */
		अगर (len == 6) अणु
			via_pmu_event(PMU_EVT_POWER, !!(data[1]&8));
			via_pmu_event(PMU_EVT_LID, data[1]&1);
		पूर्ण
		अवरोध;

	शेष:
	       pmu_pass_पूर्णांकr(data, len);
	पूर्ण
	जाओ next;
पूर्ण

अटल काष्ठा adb_request*
pmu_sr_पूर्णांकr(व्योम)
अणु
	काष्ठा adb_request *req;
	पूर्णांक bite = 0;

	अगर (in_8(&via2[B]) & TREQ) अणु
		prपूर्णांकk(KERN_ERR "PMU: spurious SR intr (%x)\n", in_8(&via2[B]));
		वापस शून्य;
	पूर्ण
	/* The ack may not yet be low when we get the पूर्णांकerrupt */
	जबतक ((in_8(&via2[B]) & TACK) != 0)
			;

	/* अगर पढ़ोing grab the byte, and reset the पूर्णांकerrupt */
	अगर (pmu_state == पढ़ोing || pmu_state == पढ़ोing_पूर्णांकr)
		bite = in_8(&via1[SR]);

	/* reset TREQ and रुको क्रम TACK to go high */
	out_8(&via2[B], in_8(&via2[B]) | TREQ);
	रुको_क्रम_ack();

	चयन (pmu_state) अणु
	हाल sending:
		req = current_req;
		अगर (data_len < 0) अणु
			data_len = req->nbytes - 1;
			send_byte(data_len);
			अवरोध;
		पूर्ण
		अगर (data_index <= data_len) अणु
			send_byte(req->data[data_index++]);
			अवरोध;
		पूर्ण
		req->sent = 1;
		data_len = pmu_data_len[req->data[0]][1];
		अगर (data_len == 0) अणु
			pmu_state = idle;
			current_req = req->next;
			अगर (req->reply_expected)
				req_aरुकोing_reply = req;
			अन्यथा
				वापस req;
		पूर्ण अन्यथा अणु
			pmu_state = पढ़ोing;
			data_index = 0;
			reply_ptr = req->reply + req->reply_len;
			recv_byte();
		पूर्ण
		अवरोध;

	हाल पूर्णांकack:
		data_index = 0;
		data_len = -1;
		pmu_state = पढ़ोing_पूर्णांकr;
		reply_ptr = पूर्णांकerrupt_data[पूर्णांक_data_last];
		recv_byte();
		अगर (gpio_irq >= 0 && !gpio_irq_enabled) अणु
			enable_irq(gpio_irq);
			gpio_irq_enabled = 1;
		पूर्ण
		अवरोध;

	हाल पढ़ोing:
	हाल पढ़ोing_पूर्णांकr:
		अगर (data_len == -1) अणु
			data_len = bite;
			अगर (bite > 32)
				prपूर्णांकk(KERN_ERR "PMU: bad reply len %d\n", bite);
		पूर्ण अन्यथा अगर (data_index < 32) अणु
			reply_ptr[data_index++] = bite;
		पूर्ण
		अगर (data_index < data_len) अणु
			recv_byte();
			अवरोध;
		पूर्ण

		अगर (pmu_state == पढ़ोing_पूर्णांकr) अणु
			pmu_state = idle;
			पूर्णांक_data_state[पूर्णांक_data_last] = पूर्णांक_data_पढ़ोy;
			पूर्णांकerrupt_data_len[पूर्णांक_data_last] = data_len;
		पूर्ण अन्यथा अणु
			req = current_req;
			/* 
			 * For PMU sleep and freq change requests, we lock the
			 * PMU until it's explicitly unlocked. This aव्योमs any
			 * spurrious event polling getting in
			 */
			current_req = req->next;
			req->reply_len += data_index;
			अगर (req->data[0] == PMU_SLEEP || req->data[0] == PMU_CPU_SPEED)
				pmu_state = locked;
			अन्यथा
				pmu_state = idle;
			वापस req;
		पूर्ण
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "via_pmu_interrupt: unknown state %d?\n",
		       pmu_state);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल irqवापस_t
via_pmu_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक पूर्णांकr;
	पूर्णांक nloop = 0;
	पूर्णांक पूर्णांक_data = -1;
	काष्ठा adb_request *req = शून्य;
	पूर्णांक handled = 0;

	/* This is a bit brutal, we can probably करो better */
	spin_lock_irqsave(&pmu_lock, flags);
	++disable_poll;
	
	क्रम (;;) अणु
		/* On 68k Macs, VIA पूर्णांकerrupts are dispatched inभागidually.
		 * Unless we are polling, the relevant IRQ flag has alपढ़ोy
		 * been cleared.
		 */
		पूर्णांकr = 0;
		अगर (IS_ENABLED(CONFIG_PPC_PMAC) || !irq) अणु
			पूर्णांकr = in_8(&via1[IFR]) & (SR_INT | CB1_INT);
			out_8(&via1[IFR], पूर्णांकr);
		पूर्ण
#अगर_अघोषित CONFIG_PPC_PMAC
		चयन (irq) अणु
		हाल IRQ_MAC_ADB_CL:
			पूर्णांकr = CB1_INT;
			अवरोध;
		हाल IRQ_MAC_ADB_SR:
			पूर्णांकr = SR_INT;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		अगर (पूर्णांकr == 0)
			अवरोध;
		handled = 1;
		अगर (++nloop > 1000) अणु
			prपूर्णांकk(KERN_DEBUG "PMU: stuck in intr loop, "
			       "intr=%x, ier=%x pmu_state=%d\n",
			       पूर्णांकr, in_8(&via1[IER]), pmu_state);
			अवरोध;
		पूर्ण
		अगर (पूर्णांकr & CB1_INT) अणु
			adb_पूर्णांक_pending = 1;
			pmu_irq_stats[11]++;
		पूर्ण
		अगर (पूर्णांकr & SR_INT) अणु
			req = pmu_sr_पूर्णांकr();
			अगर (req)
				अवरोध;
		पूर्ण
#अगर_अघोषित CONFIG_PPC_PMAC
		अवरोध;
#पूर्ण_अगर
	पूर्ण

recheck:
	अगर (pmu_state == idle) अणु
		अगर (adb_पूर्णांक_pending) अणु
			अगर (पूर्णांक_data_state[0] == पूर्णांक_data_empty)
				पूर्णांक_data_last = 0;
			अन्यथा अगर (पूर्णांक_data_state[1] == पूर्णांक_data_empty)
				पूर्णांक_data_last = 1;
			अन्यथा
				जाओ no_मुक्त_slot;
			pmu_state = पूर्णांकack;
			पूर्णांक_data_state[पूर्णांक_data_last] = पूर्णांक_data_fill;
			/* Sounds safer to make sure ACK is high beक्रमe writing.
			 * This helped समाप्त a problem with ADB and some iBooks
			 */
			रुको_क्रम_ack();
			send_byte(PMU_INT_ACK);
			adb_पूर्णांक_pending = 0;
		पूर्ण अन्यथा अगर (current_req)
			pmu_start();
	पूर्ण
no_मुक्त_slot:			
	/* Mark the oldest buffer क्रम flushing */
	अगर (पूर्णांक_data_state[!पूर्णांक_data_last] == पूर्णांक_data_पढ़ोy) अणु
		पूर्णांक_data_state[!पूर्णांक_data_last] = पूर्णांक_data_flush;
		पूर्णांक_data = !पूर्णांक_data_last;
	पूर्ण अन्यथा अगर (पूर्णांक_data_state[पूर्णांक_data_last] == पूर्णांक_data_पढ़ोy) अणु
		पूर्णांक_data_state[पूर्णांक_data_last] = पूर्णांक_data_flush;
		पूर्णांक_data = पूर्णांक_data_last;
	पूर्ण
	--disable_poll;
	spin_unlock_irqrestore(&pmu_lock, flags);

	/* Deal with completed PMU requests outside of the lock */
	अगर (req) अणु
		pmu_करोne(req);
		req = शून्य;
	पूर्ण
		
	/* Deal with पूर्णांकerrupt datas outside of the lock */
	अगर (पूर्णांक_data >= 0) अणु
		pmu_handle_data(पूर्णांकerrupt_data[पूर्णांक_data], पूर्णांकerrupt_data_len[पूर्णांक_data]);
		spin_lock_irqsave(&pmu_lock, flags);
		++disable_poll;
		पूर्णांक_data_state[पूर्णांक_data] = पूर्णांक_data_empty;
		पूर्णांक_data = -1;
		जाओ recheck;
	पूर्ण

	वापस IRQ_RETVAL(handled);
पूर्ण

व्योम
pmu_unlock(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pmu_lock, flags);
	अगर (pmu_state == locked)
		pmu_state = idle;
	adb_पूर्णांक_pending = 1;
	spin_unlock_irqrestore(&pmu_lock, flags);
पूर्ण


अटल __maybe_unused irqवापस_t
gpio1_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
	अचिन्हित दीर्घ flags;

	अगर ((in_8(gpio_reg + 0x9) & 0x02) == 0) अणु
		spin_lock_irqsave(&pmu_lock, flags);
		अगर (gpio_irq_enabled > 0) अणु
			disable_irq_nosync(gpio_irq);
			gpio_irq_enabled = 0;
		पूर्ण
		pmu_irq_stats[12]++;
		adb_पूर्णांक_pending = 1;
		spin_unlock_irqrestore(&pmu_lock, flags);
		via_pmu_पूर्णांकerrupt(0, शून्य);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

व्योम
pmu_enable_irled(पूर्णांक on)
अणु
	काष्ठा adb_request req;

	अगर (pmu_state == uninitialized)
		वापस ;
	अगर (pmu_kind == PMU_KEYLARGO_BASED)
		वापस ;

	pmu_request(&req, शून्य, 2, PMU_POWER_CTRL, PMU_POW_IRLED |
	    (on ? PMU_POW_ON : PMU_POW_OFF));
	pmu_रुको_complete(&req);
पूर्ण

/* Offset between Unix समय (1970-based) and Mac समय (1904-based) */
#घोषणा RTC_OFFSET	2082844800

समय64_t pmu_get_समय(व्योम)
अणु
	काष्ठा adb_request req;
	u32 now;

	अगर (pmu_request(&req, शून्य, 1, PMU_READ_RTC) < 0)
		वापस 0;
	pmu_रुको_complete(&req);
	अगर (req.reply_len != 4)
		pr_err("%s: got %d byte reply\n", __func__, req.reply_len);
	now = (req.reply[0] << 24) + (req.reply[1] << 16) +
	      (req.reply[2] << 8) + req.reply[3];
	वापस (समय64_t)now - RTC_OFFSET;
पूर्ण

पूर्णांक pmu_set_rtc_समय(काष्ठा rtc_समय *पंचांग)
अणु
	u32 now;
	काष्ठा adb_request req;

	now = lower_32_bits(rtc_पंचांग_to_समय64(पंचांग) + RTC_OFFSET);
	अगर (pmu_request(&req, शून्य, 5, PMU_SET_RTC,
	                now >> 24, now >> 16, now >> 8, now) < 0)
		वापस -ENXIO;
	pmu_रुको_complete(&req);
	अगर (req.reply_len != 0)
		pr_err("%s: got %d byte reply\n", __func__, req.reply_len);
	वापस 0;
पूर्ण

व्योम
pmu_restart(व्योम)
अणु
	काष्ठा adb_request req;

	अगर (pmu_state == uninitialized)
		वापस;

	local_irq_disable();

	drop_पूर्णांकerrupts = 1;
	
	अगर (pmu_kind != PMU_KEYLARGO_BASED) अणु
		pmu_request(&req, शून्य, 2, PMU_SET_INTR_MASK, PMU_INT_ADB |
						PMU_INT_TICK );
		जबतक(!req.complete)
			pmu_poll();
	पूर्ण

	pmu_request(&req, शून्य, 1, PMU_RESET);
	pmu_रुको_complete(&req);
	क्रम (;;)
		;
पूर्ण

व्योम
pmu_shutकरोwn(व्योम)
अणु
	काष्ठा adb_request req;

	अगर (pmu_state == uninitialized)
		वापस;

	local_irq_disable();

	drop_पूर्णांकerrupts = 1;

	अगर (pmu_kind != PMU_KEYLARGO_BASED) अणु
		pmu_request(&req, शून्य, 2, PMU_SET_INTR_MASK, PMU_INT_ADB |
						PMU_INT_TICK );
		pmu_रुको_complete(&req);
	पूर्ण अन्यथा अणु
		/* Disable server mode on shutकरोwn or we'll just
		 * wake up again
		 */
		pmu_set_server_mode(0);
	पूर्ण

	pmu_request(&req, शून्य, 5, PMU_SHUTDOWN,
		    'M', 'A', 'T', 'T');
	pmu_रुको_complete(&req);
	क्रम (;;)
		;
पूर्ण

पूर्णांक
pmu_present(व्योम)
अणु
	वापस pmu_state != uninitialized;
पूर्ण

#अगर defined(CONFIG_SUSPEND) && defined(CONFIG_PPC32)
/*
 * Put the घातerbook to sleep.
 */
 
अटल u32 save_via[8];
अटल पूर्णांक __fake_sleep;

अटल व्योम
save_via_state(व्योम)
अणु
	save_via[0] = in_8(&via1[ANH]);
	save_via[1] = in_8(&via1[सूचीA]);
	save_via[2] = in_8(&via1[B]);
	save_via[3] = in_8(&via1[सूचीB]);
	save_via[4] = in_8(&via1[PCR]);
	save_via[5] = in_8(&via1[ACR]);
	save_via[6] = in_8(&via1[T1CL]);
	save_via[7] = in_8(&via1[T1CH]);
पूर्ण
अटल व्योम
restore_via_state(व्योम)
अणु
	out_8(&via1[ANH],  save_via[0]);
	out_8(&via1[सूचीA], save_via[1]);
	out_8(&via1[B],    save_via[2]);
	out_8(&via1[सूचीB], save_via[3]);
	out_8(&via1[PCR],  save_via[4]);
	out_8(&via1[ACR],  save_via[5]);
	out_8(&via1[T1CL], save_via[6]);
	out_8(&via1[T1CH], save_via[7]);
	out_8(&via1[IER], IER_CLR | 0x7f);	/* disable all पूर्णांकrs */
	out_8(&via1[IFR], 0x7f);			/* clear IFR */
	out_8(&via1[IER], IER_SET | SR_INT | CB1_INT);
पूर्ण

#घोषणा	GRACKLE_PM	(1<<7)
#घोषणा GRACKLE_DOZE	(1<<5)
#घोषणा	GRACKLE_NAP	(1<<4)
#घोषणा	GRACKLE_SLEEP	(1<<3)

अटल पूर्णांक घातerbook_sleep_grackle(व्योम)
अणु
	अचिन्हित दीर्घ save_l2cr;
	अचिन्हित लघु pmcr1;
	काष्ठा adb_request req;
	काष्ठा pci_dev *grackle;

	grackle = pci_get_करोमुख्य_bus_and_slot(0, 0, 0);
	अगर (!grackle)
		वापस -ENODEV;

	/* Turn off various things. Darwin करोes some retry tests here... */
	pmu_request(&req, शून्य, 2, PMU_POWER_CTRL0, PMU_POW0_OFF|PMU_POW0_HARD_DRIVE);
	pmu_रुको_complete(&req);
	pmu_request(&req, शून्य, 2, PMU_POWER_CTRL,
		PMU_POW_OFF|PMU_POW_BACKLIGHT|PMU_POW_IRLED|PMU_POW_MEDIABAY);
	pmu_रुको_complete(&req);

	/* For 750, save backside cache setting and disable it */
	save_l2cr = _get_L2CR();	/* (वापसs -1 अगर not available) */

	अगर (!__fake_sleep) अणु
		/* Ask the PMU to put us to sleep */
		pmu_request(&req, शून्य, 5, PMU_SLEEP, 'M', 'A', 'T', 'T');
		pmu_रुको_complete(&req);
	पूर्ण

	/* The VIA is supposed not to be restored correctly*/
	save_via_state();
	/* We shut करोwn some HW */
	pmac_call_feature(PMAC_FTR_SLEEP_STATE,शून्य,0,1);

	pci_पढ़ो_config_word(grackle, 0x70, &pmcr1);
	/* Apparently, MacOS uses NAP mode क्रम Grackle ??? */
	pmcr1 &= ~(GRACKLE_DOZE|GRACKLE_SLEEP); 
	pmcr1 |= GRACKLE_PM|GRACKLE_NAP;
	pci_ग_लिखो_config_word(grackle, 0x70, pmcr1);

	/* Call low-level ASM sleep handler */
	अगर (__fake_sleep)
		mdelay(5000);
	अन्यथा
		low_sleep_handler();

	/* We're awake again, stop grackle PM */
	pci_पढ़ो_config_word(grackle, 0x70, &pmcr1);
	pmcr1 &= ~(GRACKLE_PM|GRACKLE_DOZE|GRACKLE_SLEEP|GRACKLE_NAP); 
	pci_ग_लिखो_config_word(grackle, 0x70, pmcr1);

	pci_dev_put(grackle);

	/* Make sure the PMU is idle */
	pmac_call_feature(PMAC_FTR_SLEEP_STATE,शून्य,0,0);
	restore_via_state();
	
	/* Restore L2 cache */
	अगर (save_l2cr != 0xffffffff && (save_l2cr & L2CR_L2E) != 0)
 		_set_L2CR(save_l2cr);
	
	/* Restore userland MMU context */
	चयन_mmu_context(शून्य, current->active_mm, शून्य);

	/* Power things up */
	pmu_unlock();
	pmu_request(&req, शून्य, 2, PMU_SET_INTR_MASK, pmu_पूर्णांकr_mask);
	pmu_रुको_complete(&req);
	pmu_request(&req, शून्य, 2, PMU_POWER_CTRL0,
			PMU_POW0_ON|PMU_POW0_HARD_DRIVE);
	pmu_रुको_complete(&req);
	pmu_request(&req, शून्य, 2, PMU_POWER_CTRL,
			PMU_POW_ON|PMU_POW_BACKLIGHT|PMU_POW_CHARGER|PMU_POW_IRLED|PMU_POW_MEDIABAY);
	pmu_रुको_complete(&req);

	वापस 0;
पूर्ण

अटल पूर्णांक
घातerbook_sleep_Core99(व्योम)
अणु
	अचिन्हित दीर्घ save_l2cr;
	अचिन्हित दीर्घ save_l3cr;
	काष्ठा adb_request req;
	
	अगर (pmac_call_feature(PMAC_FTR_SLEEP_STATE,शून्य,0,-1) < 0) अणु
		prपूर्णांकk(KERN_ERR "Sleep mode not supported on this machine\n");
		वापस -ENOSYS;
	पूर्ण

	अगर (num_online_cpus() > 1 || cpu_is_offline(0))
		वापस -EAGAIN;

	/* Stop environment and ADB पूर्णांकerrupts */
	pmu_request(&req, शून्य, 2, PMU_SET_INTR_MASK, 0);
	pmu_रुको_complete(&req);

	/* Tell PMU what events will wake us up */
	pmu_request(&req, शून्य, 4, PMU_POWER_EVENTS, PMU_PWR_CLR_WAKEUP_EVENTS,
		0xff, 0xff);
	pmu_रुको_complete(&req);
	pmu_request(&req, शून्य, 4, PMU_POWER_EVENTS, PMU_PWR_SET_WAKEUP_EVENTS,
		0, PMU_PWR_WAKEUP_KEY |
		(option_lid_wakeup ? PMU_PWR_WAKEUP_LID_OPEN : 0));
	pmu_रुको_complete(&req);

	/* Save the state of the L2 and L3 caches */
	save_l3cr = _get_L3CR();	/* (वापसs -1 अगर not available) */
	save_l2cr = _get_L2CR();	/* (वापसs -1 अगर not available) */

	अगर (!__fake_sleep) अणु
		/* Ask the PMU to put us to sleep */
		pmu_request(&req, शून्य, 5, PMU_SLEEP, 'M', 'A', 'T', 'T');
		pmu_रुको_complete(&req);
	पूर्ण

	/* The VIA is supposed not to be restored correctly*/
	save_via_state();

	/* Shut करोwn various ASICs. There's a chance that we can no दीर्घer
	 * talk to the PMU after this, so I moved it to _after_ sending the
	 * sleep command to it. Still need to be checked.
	 */
	pmac_call_feature(PMAC_FTR_SLEEP_STATE, शून्य, 0, 1);

	/* Call low-level ASM sleep handler */
	अगर (__fake_sleep)
		mdelay(5000);
	अन्यथा
		low_sleep_handler();

	/* Restore Apple core ASICs state */
	pmac_call_feature(PMAC_FTR_SLEEP_STATE, शून्य, 0, 0);

	/* Restore VIA */
	restore_via_state();

	/* tweak LPJ beक्रमe cpufreq is there */
	loops_per_jअगरfy *= 2;

	/* Restore video */
	pmac_call_early_video_resume();

	/* Restore L2 cache */
	अगर (save_l2cr != 0xffffffff && (save_l2cr & L2CR_L2E) != 0)
 		_set_L2CR(save_l2cr);
	/* Restore L3 cache */
	अगर (save_l3cr != 0xffffffff && (save_l3cr & L3CR_L3E) != 0)
 		_set_L3CR(save_l3cr);
	
	/* Restore userland MMU context */
	चयन_mmu_context(शून्य, current->active_mm, शून्य);

	/* Tell PMU we are पढ़ोy */
	pmu_unlock();
	pmu_request(&req, शून्य, 2, PMU_SYSTEM_READY, 2);
	pmu_रुको_complete(&req);
	pmu_request(&req, शून्य, 2, PMU_SET_INTR_MASK, pmu_पूर्णांकr_mask);
	pmu_रुको_complete(&req);

	/* Restore LPJ, cpufreq will adjust the cpu frequency */
	loops_per_jअगरfy /= 2;

	वापस 0;
पूर्ण

#घोषणा PB3400_MEM_CTRL		0xf8000000
#घोषणा PB3400_MEM_CTRL_SLEEP	0x70

अटल व्योम __iomem *pb3400_mem_ctrl;

अटल व्योम घातerbook_sleep_init_3400(व्योम)
अणु
	/* map in the memory controller रेजिस्टरs */
	pb3400_mem_ctrl = ioremap(PB3400_MEM_CTRL, 0x100);
	अगर (pb3400_mem_ctrl == शून्य)
		prपूर्णांकk(KERN_WARNING "ioremap failed: sleep won't be possible");
पूर्ण

अटल पूर्णांक घातerbook_sleep_3400(व्योम)
अणु
	पूर्णांक i, x;
	अचिन्हित पूर्णांक hid0;
	अचिन्हित दीर्घ msr;
	काष्ठा adb_request sleep_req;
	अचिन्हित पूर्णांक __iomem *mem_ctrl_sleep;

	अगर (pb3400_mem_ctrl == शून्य)
		वापस -ENOMEM;
	mem_ctrl_sleep = pb3400_mem_ctrl + PB3400_MEM_CTRL_SLEEP;

	/* Set the memory controller to keep the memory refreshed
	   जबतक we're asleep */
	क्रम (i = 0x403f; i >= 0x4000; --i) अणु
		out_be32(mem_ctrl_sleep, i);
		करो अणु
			x = (in_be32(mem_ctrl_sleep) >> 16) & 0x3ff;
		पूर्ण जबतक (x == 0);
		अगर (x >= 0x100)
			अवरोध;
	पूर्ण

	/* Ask the PMU to put us to sleep */
	pmu_request(&sleep_req, शून्य, 5, PMU_SLEEP, 'M', 'A', 'T', 'T');
	pmu_रुको_complete(&sleep_req);
	pmu_unlock();

	pmac_call_feature(PMAC_FTR_SLEEP_STATE, शून्य, 0, 1);

	asleep = 1;

	/* Put the CPU पूर्णांकo sleep mode */
	hid0 = mfspr(SPRN_HID0);
	hid0 = (hid0 & ~(HID0_NAP | HID0_DOZE)) | HID0_SLEEP;
	mtspr(SPRN_HID0, hid0);
	local_irq_enable();
	msr = mfmsr() | MSR_POW;
	जबतक (asleep) अणु
		mb();
		mपंचांगsr(msr);
		isync();
	पूर्ण
	local_irq_disable();

	/* OK, we're awake again, start restoring things */
	out_be32(mem_ctrl_sleep, 0x3f);
	pmac_call_feature(PMAC_FTR_SLEEP_STATE, शून्य, 0, 0);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_SUSPEND && CONFIG_PPC32 */

/*
 * Support क्रम /dev/pmu device
 */
#घोषणा RB_SIZE		0x10
काष्ठा pmu_निजी अणु
	काष्ठा list_head list;
	पूर्णांक	rb_get;
	पूर्णांक	rb_put;
	काष्ठा rb_entry अणु
		अचिन्हित लघु len;
		अचिन्हित अक्षर data[16];
	पूर्ण	rb_buf[RB_SIZE];
	रुको_queue_head_t रुको;
	spinlock_t lock;
#अगर defined(CONFIG_INPUT_ADBHID) && defined(CONFIG_PMAC_BACKLIGHT)
	पूर्णांक	backlight_locker;
#पूर्ण_अगर
पूर्ण;

अटल LIST_HEAD(all_pmu_pvt);
अटल DEFINE_SPINLOCK(all_pvt_lock);

अटल व्योम
pmu_pass_पूर्णांकr(अचिन्हित अक्षर *data, पूर्णांक len)
अणु
	काष्ठा pmu_निजी *pp;
	काष्ठा list_head *list;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (len > माप(pp->rb_buf[0].data))
		len = माप(pp->rb_buf[0].data);
	spin_lock_irqsave(&all_pvt_lock, flags);
	क्रम (list = &all_pmu_pvt; (list = list->next) != &all_pmu_pvt; ) अणु
		pp = list_entry(list, काष्ठा pmu_निजी, list);
		spin_lock(&pp->lock);
		i = pp->rb_put + 1;
		अगर (i >= RB_SIZE)
			i = 0;
		अगर (i != pp->rb_get) अणु
			काष्ठा rb_entry *rp = &pp->rb_buf[pp->rb_put];
			rp->len = len;
			स_नकल(rp->data, data, len);
			pp->rb_put = i;
			wake_up_पूर्णांकerruptible(&pp->रुको);
		पूर्ण
		spin_unlock(&pp->lock);
	पूर्ण
	spin_unlock_irqrestore(&all_pvt_lock, flags);
पूर्ण

अटल पूर्णांक
pmu_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा pmu_निजी *pp;
	अचिन्हित दीर्घ flags;

	pp = kदो_स्मृति(माप(काष्ठा pmu_निजी), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;
	pp->rb_get = pp->rb_put = 0;
	spin_lock_init(&pp->lock);
	init_रुकोqueue_head(&pp->रुको);
	mutex_lock(&pmu_info_proc_mutex);
	spin_lock_irqsave(&all_pvt_lock, flags);
#अगर defined(CONFIG_INPUT_ADBHID) && defined(CONFIG_PMAC_BACKLIGHT)
	pp->backlight_locker = 0;
#पूर्ण_अगर
	list_add(&pp->list, &all_pmu_pvt);
	spin_unlock_irqrestore(&all_pvt_lock, flags);
	file->निजी_data = pp;
	mutex_unlock(&pmu_info_proc_mutex);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार 
pmu_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा pmu_निजी *pp = file->निजी_data;
	DECLARE_WAITQUEUE(रुको, current);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (count < 1 || !pp)
		वापस -EINVAL;

	spin_lock_irqsave(&pp->lock, flags);
	add_रुको_queue(&pp->रुको, &रुको);
	set_current_state(TASK_INTERRUPTIBLE);

	क्रम (;;) अणु
		ret = -EAGAIN;
		अगर (pp->rb_get != pp->rb_put) अणु
			पूर्णांक i = pp->rb_get;
			काष्ठा rb_entry *rp = &pp->rb_buf[i];
			ret = rp->len;
			spin_unlock_irqrestore(&pp->lock, flags);
			अगर (ret > count)
				ret = count;
			अगर (ret > 0 && copy_to_user(buf, rp->data, ret))
				ret = -EFAULT;
			अगर (++i >= RB_SIZE)
				i = 0;
			spin_lock_irqsave(&pp->lock, flags);
			pp->rb_get = i;
		पूर्ण
		अगर (ret >= 0)
			अवरोध;
		अगर (file->f_flags & O_NONBLOCK)
			अवरोध;
		ret = -ERESTARTSYS;
		अगर (संकेत_pending(current))
			अवरोध;
		spin_unlock_irqrestore(&pp->lock, flags);
		schedule();
		spin_lock_irqsave(&pp->lock, flags);
	पूर्ण
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&pp->रुको, &रुको);
	spin_unlock_irqrestore(&pp->lock, flags);
	
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
pmu_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	वापस 0;
पूर्ण

अटल __poll_t
pmu_fpoll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा pmu_निजी *pp = filp->निजी_data;
	__poll_t mask = 0;
	अचिन्हित दीर्घ flags;
	
	अगर (!pp)
		वापस 0;
	poll_रुको(filp, &pp->रुको, रुको);
	spin_lock_irqsave(&pp->lock, flags);
	अगर (pp->rb_get != pp->rb_put)
		mask |= EPOLLIN;
	spin_unlock_irqrestore(&pp->lock, flags);
	वापस mask;
पूर्ण

अटल पूर्णांक
pmu_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा pmu_निजी *pp = file->निजी_data;
	अचिन्हित दीर्घ flags;

	अगर (pp) अणु
		file->निजी_data = शून्य;
		spin_lock_irqsave(&all_pvt_lock, flags);
		list_del(&pp->list);
		spin_unlock_irqrestore(&all_pvt_lock, flags);

#अगर defined(CONFIG_INPUT_ADBHID) && defined(CONFIG_PMAC_BACKLIGHT)
		अगर (pp->backlight_locker)
			pmac_backlight_enable();
#पूर्ण_अगर

		kमुक्त(pp);
	पूर्ण
	वापस 0;
पूर्ण

#अगर defined(CONFIG_SUSPEND) && defined(CONFIG_PPC32)
अटल व्योम pmac_suspend_disable_irqs(व्योम)
अणु
	/* Call platक्रमm functions marked "on sleep" */
	pmac_pfunc_i2c_suspend();
	pmac_pfunc_base_suspend();
पूर्ण

अटल पूर्णांक घातerbook_sleep(suspend_state_t state)
अणु
	पूर्णांक error = 0;

	/* Wait क्रम completion of async requests */
	जबतक (!batt_req.complete)
		pmu_poll();

	/* Giveup the lazy FPU & vec so we करोn't have to back them
	 * up from the low level code
	 */
	enable_kernel_fp();

#अगर_घोषित CONFIG_ALTIVEC
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		enable_kernel_altivec();
#पूर्ण_अगर /* CONFIG_ALTIVEC */

	चयन (pmu_kind) अणु
	हाल PMU_OHARE_BASED:
		error = घातerbook_sleep_3400();
		अवरोध;
	हाल PMU_HEATHROW_BASED:
	हाल PMU_PADDINGTON_BASED:
		error = घातerbook_sleep_grackle();
		अवरोध;
	हाल PMU_KEYLARGO_BASED:
		error = घातerbook_sleep_Core99();
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	अगर (error)
		वापस error;

	mdelay(100);

	वापस 0;
पूर्ण

अटल व्योम pmac_suspend_enable_irqs(व्योम)
अणु
	/* Force a poll of ADB पूर्णांकerrupts */
	adb_पूर्णांक_pending = 1;
	via_pmu_पूर्णांकerrupt(0, शून्य);

	mdelay(10);

	/* Call platक्रमm functions marked "on wake" */
	pmac_pfunc_base_resume();
	pmac_pfunc_i2c_resume();
पूर्ण

अटल पूर्णांक pmu_sleep_valid(suspend_state_t state)
अणु
	वापस state == PM_SUSPEND_MEM
		&& (pmac_call_feature(PMAC_FTR_SLEEP_STATE, शून्य, 0, -1) >= 0);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops pmu_pm_ops = अणु
	.enter = घातerbook_sleep,
	.valid = pmu_sleep_valid,
पूर्ण;

अटल पूर्णांक रेजिस्टर_pmu_pm_ops(व्योम)
अणु
	अगर (pmu_kind == PMU_OHARE_BASED)
		घातerbook_sleep_init_3400();
	ppc_md.suspend_disable_irqs = pmac_suspend_disable_irqs;
	ppc_md.suspend_enable_irqs = pmac_suspend_enable_irqs;
	suspend_set_ops(&pmu_pm_ops);

	वापस 0;
पूर्ण

device_initcall(रेजिस्टर_pmu_pm_ops);
#पूर्ण_अगर

अटल पूर्णांक pmu_ioctl(काष्ठा file *filp,
		     u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	__u32 __user *argp = (__u32 __user *)arg;
	पूर्णांक error = -EINVAL;

	चयन (cmd) अणु
#अगर_घोषित CONFIG_PPC_PMAC
	हाल PMU_IOC_SLEEP:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EACCES;
		वापस pm_suspend(PM_SUSPEND_MEM);
	हाल PMU_IOC_CAN_SLEEP:
		अगर (pmac_call_feature(PMAC_FTR_SLEEP_STATE, शून्य, 0, -1) < 0)
			वापस put_user(0, argp);
		अन्यथा
			वापस put_user(1, argp);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PMAC_BACKLIGHT_LEGACY
	/* Compatibility ioctl's क्रम backlight */
	हाल PMU_IOC_GET_BACKLIGHT:
	अणु
		पूर्णांक brightness;

		brightness = pmac_backlight_get_legacy_brightness();
		अगर (brightness < 0)
			वापस brightness;
		अन्यथा
			वापस put_user(brightness, argp);

	पूर्ण
	हाल PMU_IOC_SET_BACKLIGHT:
	अणु
		पूर्णांक brightness;

		error = get_user(brightness, argp);
		अगर (error)
			वापस error;

		वापस pmac_backlight_set_legacy_brightness(brightness);
	पूर्ण
#अगर_घोषित CONFIG_INPUT_ADBHID
	हाल PMU_IOC_GRAB_BACKLIGHT: अणु
		काष्ठा pmu_निजी *pp = filp->निजी_data;

		अगर (pp->backlight_locker)
			वापस 0;

		pp->backlight_locker = 1;
		pmac_backlight_disable();

		वापस 0;
	पूर्ण
#पूर्ण_अगर /* CONFIG_INPUT_ADBHID */
#पूर्ण_अगर /* CONFIG_PMAC_BACKLIGHT_LEGACY */

	हाल PMU_IOC_GET_MODEL:
	    	वापस put_user(pmu_kind, argp);
	हाल PMU_IOC_HAS_ADB:
		वापस put_user(pmu_has_adb, argp);
	पूर्ण
	वापस error;
पूर्ण

अटल दीर्घ pmu_unlocked_ioctl(काष्ठा file *filp,
			       u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	पूर्णांक ret;

	mutex_lock(&pmu_info_proc_mutex);
	ret = pmu_ioctl(filp, cmd, arg);
	mutex_unlock(&pmu_info_proc_mutex);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
#घोषणा PMU_IOC_GET_BACKLIGHT32	_IOR('B', 1, compat_माप_प्रकार)
#घोषणा PMU_IOC_SET_BACKLIGHT32	_IOW('B', 2, compat_माप_प्रकार)
#घोषणा PMU_IOC_GET_MODEL32	_IOR('B', 3, compat_माप_प्रकार)
#घोषणा PMU_IOC_HAS_ADB32	_IOR('B', 4, compat_माप_प्रकार)
#घोषणा PMU_IOC_CAN_SLEEP32	_IOR('B', 5, compat_माप_प्रकार)
#घोषणा PMU_IOC_GRAB_BACKLIGHT32 _IOR('B', 6, compat_माप_प्रकार)

अटल दीर्घ compat_pmu_ioctl (काष्ठा file *filp, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल PMU_IOC_SLEEP:
		अवरोध;
	हाल PMU_IOC_GET_BACKLIGHT32:
		cmd = PMU_IOC_GET_BACKLIGHT;
		अवरोध;
	हाल PMU_IOC_SET_BACKLIGHT32:
		cmd = PMU_IOC_SET_BACKLIGHT;
		अवरोध;
	हाल PMU_IOC_GET_MODEL32:
		cmd = PMU_IOC_GET_MODEL;
		अवरोध;
	हाल PMU_IOC_HAS_ADB32:
		cmd = PMU_IOC_HAS_ADB;
		अवरोध;
	हाल PMU_IOC_CAN_SLEEP32:
		cmd = PMU_IOC_CAN_SLEEP;
		अवरोध;
	हाल PMU_IOC_GRAB_BACKLIGHT32:
		cmd = PMU_IOC_GRAB_BACKLIGHT;
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस pmu_unlocked_ioctl(filp, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations pmu_device_fops = अणु
	.पढ़ो		= pmu_पढ़ो,
	.ग_लिखो		= pmu_ग_लिखो,
	.poll		= pmu_fpoll,
	.unlocked_ioctl	= pmu_unlocked_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= compat_pmu_ioctl,
#पूर्ण_अगर
	.खोलो		= pmu_खोलो,
	.release	= pmu_release,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice pmu_device = अणु
	PMU_MINOR, "pmu", &pmu_device_fops
पूर्ण;

अटल पूर्णांक pmu_device_init(व्योम)
अणु
	अगर (pmu_state == uninitialized)
		वापस 0;
	अगर (misc_रेजिस्टर(&pmu_device) < 0)
		prपूर्णांकk(KERN_ERR "via-pmu: cannot register misc device.\n");
	वापस 0;
पूर्ण
device_initcall(pmu_device_init);


#अगर_घोषित DEBUG_SLEEP
अटल अंतरभूत व्योम 
polled_handshake(व्योम)
अणु
	via2[B] &= ~TREQ; eieio();
	जबतक ((via2[B] & TACK) != 0)
		;
	via2[B] |= TREQ; eieio();
	जबतक ((via2[B] & TACK) == 0)
		;
पूर्ण

अटल अंतरभूत व्योम 
polled_send_byte(पूर्णांक x)
अणु
	via1[ACR] |= SR_OUT | SR_EXT; eieio();
	via1[SR] = x; eieio();
	polled_handshake();
पूर्ण

अटल अंतरभूत पूर्णांक
polled_recv_byte(व्योम)
अणु
	पूर्णांक x;

	via1[ACR] = (via1[ACR] & ~SR_OUT) | SR_EXT; eieio();
	x = via1[SR]; eieio();
	polled_handshake();
	x = via1[SR]; eieio();
	वापस x;
पूर्ण

पूर्णांक
pmu_polled_request(काष्ठा adb_request *req)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, l, c;

	req->complete = 1;
	c = req->data[0];
	l = pmu_data_len[c][0];
	अगर (l >= 0 && req->nbytes != l + 1)
		वापस -EINVAL;

	local_irq_save(flags);
	जबतक (pmu_state != idle)
		pmu_poll();

	जबतक ((via2[B] & TACK) == 0)
		;
	polled_send_byte(c);
	अगर (l < 0) अणु
		l = req->nbytes - 1;
		polled_send_byte(l);
	पूर्ण
	क्रम (i = 1; i <= l; ++i)
		polled_send_byte(req->data[i]);

	l = pmu_data_len[c][1];
	अगर (l < 0)
		l = polled_recv_byte();
	क्रम (i = 0; i < l; ++i)
		req->reply[i + req->reply_len] = polled_recv_byte();

	अगर (req->करोne)
		(*req->करोne)(req);

	local_irq_restore(flags);
	वापस 0;
पूर्ण

/* N.B. This करोesn't work on the 3400 */
व्योम pmu_blink(पूर्णांक n)
अणु
	काष्ठा adb_request req;

	स_रखो(&req, 0, माप(req));

	क्रम (; n > 0; --n) अणु
		req.nbytes = 4;
		req.करोne = शून्य;
		req.data[0] = 0xee;
		req.data[1] = 4;
		req.data[2] = 0;
		req.data[3] = 1;
		req.reply[0] = ADB_RET_OK;
		req.reply_len = 1;
		req.reply_expected = 0;
		pmu_polled_request(&req);
		mdelay(50);
		req.nbytes = 4;
		req.करोne = शून्य;
		req.data[0] = 0xee;
		req.data[1] = 4;
		req.data[2] = 0;
		req.data[3] = 0;
		req.reply[0] = ADB_RET_OK;
		req.reply_len = 1;
		req.reply_expected = 0;
		pmu_polled_request(&req);
		mdelay(50);
	पूर्ण
	mdelay(50);
पूर्ण
#पूर्ण_अगर /* DEBUG_SLEEP */

#अगर defined(CONFIG_SUSPEND) && defined(CONFIG_PPC32)
पूर्णांक pmu_sys_suspended;

अटल पूर्णांक pmu_syscore_suspend(व्योम)
अणु
	/* Suspend PMU event पूर्णांकerrupts */
	pmu_suspend();
	pmu_sys_suspended = 1;

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	/* Tell backlight code not to muck around with the chip anymore */
	pmu_backlight_set_sleep(1);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम pmu_syscore_resume(व्योम)
अणु
	काष्ठा adb_request req;

	अगर (!pmu_sys_suspended)
		वापस;

	/* Tell PMU we are पढ़ोy */
	pmu_request(&req, शून्य, 2, PMU_SYSTEM_READY, 2);
	pmu_रुको_complete(&req);

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	/* Tell backlight code it can use the chip again */
	pmu_backlight_set_sleep(0);
#पूर्ण_अगर
	/* Resume PMU event पूर्णांकerrupts */
	pmu_resume();
	pmu_sys_suspended = 0;
पूर्ण

अटल काष्ठा syscore_ops pmu_syscore_ops = अणु
	.suspend = pmu_syscore_suspend,
	.resume = pmu_syscore_resume,
पूर्ण;

अटल पूर्णांक pmu_syscore_रेजिस्टर(व्योम)
अणु
	रेजिस्टर_syscore_ops(&pmu_syscore_ops);

	वापस 0;
पूर्ण
subsys_initcall(pmu_syscore_रेजिस्टर);
#पूर्ण_अगर /* CONFIG_SUSPEND && CONFIG_PPC32 */

EXPORT_SYMBOL(pmu_request);
EXPORT_SYMBOL(pmu_queue_request);
EXPORT_SYMBOL(pmu_poll);
EXPORT_SYMBOL(pmu_poll_adb);
EXPORT_SYMBOL(pmu_रुको_complete);
EXPORT_SYMBOL(pmu_suspend);
EXPORT_SYMBOL(pmu_resume);
EXPORT_SYMBOL(pmu_unlock);
#अगर defined(CONFIG_PPC32)
EXPORT_SYMBOL(pmu_enable_irled);
EXPORT_SYMBOL(pmu_battery_count);
EXPORT_SYMBOL(pmu_batteries);
EXPORT_SYMBOL(pmu_घातer_flags);
#पूर्ण_अगर /* CONFIG_SUSPEND && CONFIG_PPC32 */

