<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Chassis LCD/LED driver क्रम HP-PARISC workstations
 *
 *      (c) Copyright 2000 Red Hat Software
 *      (c) Copyright 2000 Helge Deller <hdeller@redhat.com>
 *      (c) Copyright 2001-2009 Helge Deller <deller@gmx.de>
 *      (c) Copyright 2001 Ranकरोlph Chung <tausq@debian.org>
 *
 * TODO:
 *	- speed-up calculations with अंतरभूतd assembler
 *	- पूर्णांकerface to ग_लिखो to second row of LCD from /proc (अगर technically possible)
 *
 * Changes:
 *      - Audit copy_from_user in led_proc_ग_लिखो.
 *                                Daniele Bellucci <bellucda@tiscali.it>
 *	- Switch from using a tasklet to a work queue, so the led_LCD_driver
 *	  	can sleep.
 *	  			  David Pye <dmp@davidmpye.dyndns.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/मानकघोष.स>	/* क्रम दुरत्व() */
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/utsname.h>
#समावेश <linux/capability.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/reboot.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/rcupdate.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/param.h>		/* HZ */
#समावेश <यंत्र/led.h>
#समावेश <यंत्र/pdc.h>
#समावेश <linux/uaccess.h>

/* The control of the LEDs and LCDs on PARISC-machines have to be करोne 
   completely in software. The necessary calculations are करोne in a work queue
   task which is scheduled regularly, and since the calculations may consume a 
   relatively large amount of CPU समय, some of the calculations can be 
   turned off with the following variables (controlled via procfs) */

अटल पूर्णांक led_type __पढ़ो_mostly = -1;
अटल अचिन्हित अक्षर lastleds;	/* LED state from most recent update */
अटल अचिन्हित पूर्णांक led_heartbeat __पढ़ो_mostly = 1;
अटल अचिन्हित पूर्णांक led_diskio    __पढ़ो_mostly = 1;
अटल अचिन्हित पूर्णांक led_lanrxtx   __पढ़ो_mostly = 1;
अटल अक्षर lcd_text[32]          __पढ़ो_mostly;
अटल अक्षर lcd_text_शेष[32]  __पढ़ो_mostly;
अटल पूर्णांक  lcd_no_led_support    __पढ़ो_mostly = 0; /* KittyHawk करोesn't support LED on its LCD */


अटल काष्ठा workqueue_काष्ठा *led_wq;
अटल व्योम led_work_func(काष्ठा work_काष्ठा *);
अटल DECLARE_DELAYED_WORK(led_task, led_work_func);

#अगर 0
#घोषणा DPRINTK(x)	prपूर्णांकk x
#अन्यथा
#घोषणा DPRINTK(x)
#पूर्ण_अगर

काष्ठा lcd_block अणु
	अचिन्हित अक्षर command;	/* stores the command byte      */
	अचिन्हित अक्षर on;	/* value क्रम turning LED on     */
	अचिन्हित अक्षर off;	/* value क्रम turning LED off    */
पूर्ण;

/* Structure वापसed by PDC_RETURN_CHASSIS_INFO */
/* NOTE: we use अचिन्हित दीर्घ:16 two बार, since the following member 
   lcd_cmd_reg_addr needs to be 64bit aligned on 64bit PA2.0-machines */
काष्ठा pdc_chassis_lcd_info_ret_block अणु
	अचिन्हित दीर्घ model:16;		/* DISPLAY_MODEL_XXXX */
	अचिन्हित दीर्घ lcd_width:16;	/* width of the LCD in अक्षरs (DISPLAY_MODEL_LCD only) */
	अचिन्हित दीर्घ lcd_cmd_reg_addr;	/* ptr to LCD cmd-रेजिस्टर & data ptr क्रम LED */
	अचिन्हित दीर्घ lcd_data_reg_addr; /* ptr to LCD data-रेजिस्टर (LCD only) */
	अचिन्हित पूर्णांक min_cmd_delay;	/* delay in uS after cmd-ग_लिखो (LCD only) */
	अचिन्हित अक्षर reset_cmd1;	/* command #1 क्रम writing LCD string (LCD only) */
	अचिन्हित अक्षर reset_cmd2;	/* command #2 क्रम writing LCD string (LCD only) */
	अचिन्हित अक्षर act_enable;	/* 0 = no activity (LCD only) */
	काष्ठा lcd_block heartbeat;
	काष्ठा lcd_block disk_io;
	काष्ठा lcd_block lan_rcv;
	काष्ठा lcd_block lan_tx;
	अक्षर _pad;
पूर्ण;


/* LCD_CMD and LCD_DATA क्रम KittyHawk machines */
#घोषणा KITTYHAWK_LCD_CMD  F_EXTEND(0xf0190000UL) /* 64bit-पढ़ोy */
#घोषणा KITTYHAWK_LCD_DATA (KITTYHAWK_LCD_CMD+1)

/* lcd_info is pre-initialized to the values needed to program KittyHawk LCD's 
 * HP seems to have used Sharp/Hitachi HD44780 LCDs most of the समय. */
अटल काष्ठा pdc_chassis_lcd_info_ret_block
lcd_info __attribute__((aligned(8))) __पढ़ो_mostly =
अणु
	.model =		DISPLAY_MODEL_LCD,
	.lcd_width =		16,
	.lcd_cmd_reg_addr =	KITTYHAWK_LCD_CMD,
	.lcd_data_reg_addr =	KITTYHAWK_LCD_DATA,
	.min_cmd_delay =	80,
	.reset_cmd1 =		0x80,
	.reset_cmd2 =		0xc0,
पूर्ण;


/* direct access to some of the lcd_info variables */
#घोषणा LCD_CMD_REG	lcd_info.lcd_cmd_reg_addr	 
#घोषणा LCD_DATA_REG	lcd_info.lcd_data_reg_addr	 
#घोषणा LED_DATA_REG	lcd_info.lcd_cmd_reg_addr	/* LASI & ASP only */

#घोषणा LED_HASLCD 1
#घोषणा LED_NOLCD  0

/* The workqueue must be created at init-समय */
अटल पूर्णांक start_task(व्योम) 
अणु	
	/* Display the शेष text now */
	अगर (led_type == LED_HASLCD) lcd_prपूर्णांक( lcd_text_शेष );

	/* KittyHawk has no LED support on its LCD */
	अगर (lcd_no_led_support) वापस 0;

	/* Create the work queue and queue the LED task */
	led_wq = create_singlethपढ़ो_workqueue("led_wq");	
	queue_delayed_work(led_wq, &led_task, 0);

	वापस 0;
पूर्ण

device_initcall(start_task);

/* ptr to LCD/LED-specअगरic function */
अटल व्योम (*led_func_ptr) (अचिन्हित अक्षर) __पढ़ो_mostly;

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक led_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	चयन ((दीर्घ)m->निजी)
	अणु
	हाल LED_NOLCD:
		seq_म_लिखो(m, "Heartbeat: %d\n", led_heartbeat);
		seq_म_लिखो(m, "Disk IO: %d\n", led_diskio);
		seq_म_लिखो(m, "LAN Rx/Tx: %d\n", led_lanrxtx);
		अवरोध;
	हाल LED_HASLCD:
		seq_म_लिखो(m, "%s\n", lcd_text);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक led_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, led_proc_show, PDE_DATA(inode));
पूर्ण


अटल sमाप_प्रकार led_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
	माप_प्रकार count, loff_t *pos)
अणु
	व्योम *data = PDE_DATA(file_inode(file));
	अक्षर *cur, lbuf[32];
	पूर्णांक d;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (count >= माप(lbuf))
		count = माप(lbuf)-1;

	अगर (copy_from_user(lbuf, buf, count))
		वापस -EFAULT;
	lbuf[count] = 0;

	cur = lbuf;

	चयन ((दीर्घ)data)
	अणु
	हाल LED_NOLCD:
		d = *cur++ - '0';
		अगर (d != 0 && d != 1) जाओ parse_error;
		led_heartbeat = d;

		अगर (*cur++ != ' ') जाओ parse_error;

		d = *cur++ - '0';
		अगर (d != 0 && d != 1) जाओ parse_error;
		led_diskio = d;

		अगर (*cur++ != ' ') जाओ parse_error;

		d = *cur++ - '0';
		अगर (d != 0 && d != 1) जाओ parse_error;
		led_lanrxtx = d;

		अवरोध;
	हाल LED_HASLCD:
		अगर (*cur && cur[म_माप(cur)-1] == '\n')
			cur[म_माप(cur)-1] = 0;
		अगर (*cur == 0) 
			cur = lcd_text_शेष;
		lcd_prपूर्णांक(cur);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	
	वापस count;

parse_error:
	अगर ((दीर्घ)data == LED_NOLCD)
		prपूर्णांकk(KERN_CRIT "Parse error: expect \"n n n\" (n == 0 or 1) for heartbeat,\ndisk io and lan tx/rx indicators\n");
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा proc_ops led_proc_ops = अणु
	.proc_खोलो	= led_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= led_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक __init led_create_procfs(व्योम)
अणु
	काष्ठा proc_dir_entry *proc_pdc_root = शून्य;
	काष्ठा proc_dir_entry *ent;

	अगर (led_type == -1) वापस -1;

	proc_pdc_root = proc_सूची_गढ़ो("pdc", शून्य);
	अगर (!proc_pdc_root) वापस -1;

	अगर (!lcd_no_led_support)
	अणु
		ent = proc_create_data("led", S_IRUGO|S_IWUSR, proc_pdc_root,
					&led_proc_ops, (व्योम *)LED_NOLCD); /* LED */
		अगर (!ent) वापस -1;
	पूर्ण

	अगर (led_type == LED_HASLCD)
	अणु
		ent = proc_create_data("lcd", S_IRUGO|S_IWUSR, proc_pdc_root,
					&led_proc_ops, (व्योम *)LED_HASLCD); /* LCD */
		अगर (!ent) वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
   ** 
   ** led_ASP_driver()
   ** 
 */
#घोषणा	LED_DATA	0x01	/* data to shअगरt (0:on 1:off) */
#घोषणा	LED_STROBE	0x02	/* strobe to घड़ी data */
अटल व्योम led_ASP_driver(अचिन्हित अक्षर leds)
अणु
	पूर्णांक i;

	leds = ~leds;
	क्रम (i = 0; i < 8; i++) अणु
		अचिन्हित अक्षर value;
		value = (leds & 0x80) >> 7;
		gsc_ग_लिखोb( value,		 LED_DATA_REG );
		gsc_ग_लिखोb( value | LED_STROBE,	 LED_DATA_REG );
		leds <<= 1;
	पूर्ण
पूर्ण


/*
   ** 
   ** led_LASI_driver()
   ** 
 */
अटल व्योम led_LASI_driver(अचिन्हित अक्षर leds)
अणु
	leds = ~leds;
	gsc_ग_लिखोb( leds, LED_DATA_REG );
पूर्ण


/*
   ** 
   ** led_LCD_driver()
   **   
 */
अटल व्योम led_LCD_driver(अचिन्हित अक्षर leds)
अणु
	अटल पूर्णांक i;
	अटल अचिन्हित अक्षर mask[4] = अणु LED_HEARTBEAT, LED_DISK_IO,
		LED_LAN_RCV, LED_LAN_TX पूर्ण;
	
	अटल काष्ठा lcd_block * blockp[4] = अणु
		&lcd_info.heartbeat,
		&lcd_info.disk_io,
		&lcd_info.lan_rcv,
		&lcd_info.lan_tx
	पूर्ण;

	/* Convert min_cmd_delay to milliseconds */
	अचिन्हित पूर्णांक msec_cmd_delay = 1 + (lcd_info.min_cmd_delay / 1000);
	
	क्रम (i=0; i<4; ++i) 
	अणु
		अगर ((leds & mask[i]) != (lastleds & mask[i])) 
		अणु
			gsc_ग_लिखोb( blockp[i]->command, LCD_CMD_REG );
			msleep(msec_cmd_delay);
			
			gsc_ग_लिखोb( leds & mask[i] ? blockp[i]->on : 
					blockp[i]->off, LCD_DATA_REG );
			msleep(msec_cmd_delay);
		पूर्ण
	पूर्ण
पूर्ण


/*
   ** 
   ** led_get_net_activity()
   ** 
   ** calculate अगर there was TX- or RX-throughput on the network पूर्णांकerfaces
   ** (analog to dev_get_info() from net/core/dev.c)
   **   
 */
अटल __अंतरभूत__ पूर्णांक led_get_net_activity(व्योम)
अणु 
#अगर_अघोषित CONFIG_NET
	वापस 0;
#अन्यथा
	अटल u64 rx_total_last, tx_total_last;
	u64 rx_total, tx_total;
	काष्ठा net_device *dev;
	पूर्णांक retval;

	rx_total = tx_total = 0;
	
	/* we are running as a workqueue task, so we can use an RCU lookup */
	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, dev) अणु
	    स्थिर काष्ठा rtnl_link_stats64 *stats;
	    काष्ठा rtnl_link_stats64 temp;
	    काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);
	    अगर (!in_dev || !in_dev->अगरa_list)
		जारी;
	    अगर (ipv4_is_loopback(in_dev->अगरa_list->अगरa_local))
		जारी;
	    stats = dev_get_stats(dev, &temp);
	    rx_total += stats->rx_packets;
	    tx_total += stats->tx_packets;
	पूर्ण
	rcu_पढ़ो_unlock();

	retval = 0;

	अगर (rx_total != rx_total_last) अणु
		rx_total_last = rx_total;
		retval |= LED_LAN_RCV;
	पूर्ण

	अगर (tx_total != tx_total_last) अणु
		tx_total_last = tx_total;
		retval |= LED_LAN_TX;
	पूर्ण

	वापस retval;
#पूर्ण_अगर
पूर्ण


/*
   ** 
   ** led_get_diskio_activity()
   ** 
   ** calculate अगर there was disk-io in the प्रणाली
   **   
 */
अटल __अंतरभूत__ पूर्णांक led_get_diskio_activity(व्योम)
अणु	
	अटल अचिन्हित दीर्घ last_pgpgin, last_pgpgout;
	अचिन्हित दीर्घ events[NR_VM_EVENT_ITEMS];
	पूर्णांक changed;

	all_vm_events(events);

	/* Just use a very simple calculation here. Do not care about overflow,
	   since we only want to know अगर there was activity or not. */
	changed = (events[PGPGIN] != last_pgpgin) ||
		  (events[PGPGOUT] != last_pgpgout);
	last_pgpgin  = events[PGPGIN];
	last_pgpgout = events[PGPGOUT];

	वापस (changed ? LED_DISK_IO : 0);
पूर्ण



/*
   ** led_work_func()
   ** 
   ** manages when and which chassis LCD/LED माला_लो updated

    TODO:
    - display load average (older machines like 715/64 have 4 "free" LED's क्रम that)
    - optimizations
 */

#घोषणा HEARTBEAT_LEN (HZ*10/100)
#घोषणा HEARTBEAT_2ND_RANGE_START (HZ*28/100)
#घोषणा HEARTBEAT_2ND_RANGE_END   (HEARTBEAT_2ND_RANGE_START + HEARTBEAT_LEN)

#घोषणा LED_UPDATE_INTERVAL (1 + (HZ*19/1000))

अटल व्योम led_work_func (काष्ठा work_काष्ठा *unused)
अणु
	अटल अचिन्हित दीर्घ last_jअगरfies;
	अटल अचिन्हित दीर्घ count_HZ; /* counter in range 0..HZ */
	अचिन्हित अक्षर currentleds = 0; /* stores current value of the LEDs */

	/* निकास अगर not initialized */
	अगर (!led_func_ptr)
	    वापस;

	/* increment the heartbeat समयkeeper */
	count_HZ += jअगरfies - last_jअगरfies;
	last_jअगरfies = jअगरfies;
	अगर (count_HZ >= HZ)
	    count_HZ = 0;

	अगर (likely(led_heartbeat))
	अणु
		/* flash heartbeat-LED like a real heart
		 * (2 x लघु then a दीर्घ delay)
		 */
		अगर (count_HZ < HEARTBEAT_LEN || 
				(count_HZ >= HEARTBEAT_2ND_RANGE_START &&
				count_HZ < HEARTBEAT_2ND_RANGE_END)) 
			currentleds |= LED_HEARTBEAT;
	पूर्ण

	अगर (likely(led_lanrxtx))  currentleds |= led_get_net_activity();
	अगर (likely(led_diskio))   currentleds |= led_get_diskio_activity();

	/* blink LEDs अगर we got an Oops (HPMC) */
	अगर (unlikely(oops_in_progress)) अणु
		अगर (boot_cpu_data.cpu_type >= pcxl2) अणु
			/* newer machines करोn't have loadavg. LEDs, so we
			 * let all LEDs blink twice per second instead */
			currentleds = (count_HZ <= (HZ/2)) ? 0 : 0xff;
		पूर्ण अन्यथा अणु
			/* old machines: blink loadavg. LEDs twice per second */
			अगर (count_HZ <= (HZ/2))
				currentleds &= ~(LED4|LED5|LED6|LED7);
			अन्यथा
				currentleds |= (LED4|LED5|LED6|LED7);
		पूर्ण
	पूर्ण

	अगर (currentleds != lastleds)
	अणु
		led_func_ptr(currentleds);	/* Update the LCD/LEDs */
		lastleds = currentleds;
	पूर्ण

	queue_delayed_work(led_wq, &led_task, LED_UPDATE_INTERVAL);
पूर्ण

/*
   ** led_halt()
   ** 
   ** called by the reboot notअगरier chain at shutकरोwn and stops all
   ** LED/LCD activities.
   ** 
 */

अटल पूर्णांक led_halt(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);

अटल काष्ठा notअगरier_block led_notअगरier = अणु
	.notअगरier_call = led_halt,
पूर्ण;
अटल पूर्णांक notअगरier_disabled = 0;

अटल पूर्णांक led_halt(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *buf) 
अणु
	अक्षर *txt;

	अगर (notअगरier_disabled)
		वापस NOTIFY_OK;

	notअगरier_disabled = 1;
	चयन (event) अणु
	हाल SYS_RESTART:	txt = "SYSTEM RESTART";
				अवरोध;
	हाल SYS_HALT:		txt = "SYSTEM HALT";
				अवरोध;
	हाल SYS_POWER_OFF:	txt = "SYSTEM POWER OFF";
				अवरोध;
	शेष:		वापस NOTIFY_DONE;
	पूर्ण
	
	/* Cancel the work item and delete the queue */
	अगर (led_wq) अणु
		cancel_delayed_work_sync(&led_task);
		destroy_workqueue(led_wq);
		led_wq = शून्य;
	पूर्ण
 
	अगर (lcd_info.model == DISPLAY_MODEL_LCD)
		lcd_prपूर्णांक(txt);
	अन्यथा
		अगर (led_func_ptr)
			led_func_ptr(0xff); /* turn all LEDs ON */
	
	वापस NOTIFY_OK;
पूर्ण

/*
   ** रेजिस्टर_led_driver()
   ** 
   ** रेजिस्टरs an बाह्यal LED or LCD क्रम usage by this driver.
   ** currently only LCD-, LASI- and ASP-style LCD/LED's are supported.
   ** 
 */

पूर्णांक __init रेजिस्टर_led_driver(पूर्णांक model, अचिन्हित दीर्घ cmd_reg, अचिन्हित दीर्घ data_reg)
अणु
	अटल पूर्णांक initialized;
	
	अगर (initialized || !data_reg)
		वापस 1;
	
	lcd_info.model = model;		/* store the values */
	LCD_CMD_REG = (cmd_reg == LED_CMD_REG_NONE) ? 0 : cmd_reg;

	चयन (lcd_info.model) अणु
	हाल DISPLAY_MODEL_LCD:
		LCD_DATA_REG = data_reg;
		prपूर्णांकk(KERN_INFO "LCD display at %lx,%lx registered\n", 
			LCD_CMD_REG , LCD_DATA_REG);
		led_func_ptr = led_LCD_driver;
		led_type = LED_HASLCD;
		अवरोध;

	हाल DISPLAY_MODEL_LASI:
		/* Skip to रेजिस्टर LED in QEMU */
		अगर (running_on_qemu)
			वापस 1;
		LED_DATA_REG = data_reg;
		led_func_ptr = led_LASI_driver;
		prपूर्णांकk(KERN_INFO "LED display at %lx registered\n", LED_DATA_REG);
		led_type = LED_NOLCD;
		अवरोध;

	हाल DISPLAY_MODEL_OLD_ASP:
		LED_DATA_REG = data_reg;
		led_func_ptr = led_ASP_driver;
		prपूर्णांकk(KERN_INFO "LED (ASP-style) display at %lx registered\n", 
		    LED_DATA_REG);
		led_type = LED_NOLCD;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "%s: Wrong LCD/LED model %d !\n",
		       __func__, lcd_info.model);
		वापस 1;
	पूर्ण
	
	/* mark the LCD/LED driver now as initialized and 
	 * रेजिस्टर to the reboot notअगरier chain */
	initialized++;
	रेजिस्टर_reboot_notअगरier(&led_notअगरier);

	/* Ensure the work is queued */
	अगर (led_wq) अणु
		queue_delayed_work(led_wq, &led_task, 0);
	पूर्ण

	वापस 0;
पूर्ण

/*
   ** रेजिस्टर_led_regions()
   ** 
   ** रेजिस्टर_led_regions() रेजिस्टरs the LCD/LED regions क्रम /procfs.
   ** At bootup - where the initialisation of the LCD/LED normally happens - 
   ** not all पूर्णांकernal काष्ठाures of request_region() are properly set up,
   ** so that we delay the led-registration until after busdevices_init() 
   ** has been executed.
   **
 */

व्योम __init रेजिस्टर_led_regions(व्योम)
अणु
	चयन (lcd_info.model) अणु
	हाल DISPLAY_MODEL_LCD:
		request_mem_region((अचिन्हित दीर्घ)LCD_CMD_REG,  1, "lcd_cmd");
		request_mem_region((अचिन्हित दीर्घ)LCD_DATA_REG, 1, "lcd_data");
		अवरोध;
	हाल DISPLAY_MODEL_LASI:
	हाल DISPLAY_MODEL_OLD_ASP:
		request_mem_region((अचिन्हित दीर्घ)LED_DATA_REG, 1, "led_data");
		अवरोध;
	पूर्ण
पूर्ण


/*
   ** 
   ** lcd_prपूर्णांक()
   ** 
   ** Displays the given string on the LCD-Display of newer machines.
   ** lcd_prपूर्णांक() disables/enables the समयr-based led work queue to
   ** aव्योम a race condition जबतक writing the CMD/DATA रेजिस्टर pair.
   **
 */
पूर्णांक lcd_prपूर्णांक( स्थिर अक्षर *str )
अणु
	पूर्णांक i;

	अगर (!led_func_ptr || lcd_info.model != DISPLAY_MODEL_LCD)
	    वापस 0;
	
	/* temporarily disable the led work task */
	अगर (led_wq)
		cancel_delayed_work_sync(&led_task);

	/* copy display string to buffer क्रम procfs */
	strlcpy(lcd_text, str, माप(lcd_text));

	/* Set LCD Cursor to 1st अक्षरacter */
	gsc_ग_लिखोb(lcd_info.reset_cmd1, LCD_CMD_REG);
	udelay(lcd_info.min_cmd_delay);

	/* Prपूर्णांक the string */
	क्रम (i=0; i < lcd_info.lcd_width; i++) अणु
	    अगर (str && *str)
		gsc_ग_लिखोb(*str++, LCD_DATA_REG);
	    अन्यथा
		gsc_ग_लिखोb(' ', LCD_DATA_REG);
	    udelay(lcd_info.min_cmd_delay);
	पूर्ण
	
	/* re-queue the work */
	अगर (led_wq) अणु
		queue_delayed_work(led_wq, &led_task, 0);
	पूर्ण

	वापस lcd_info.lcd_width;
पूर्ण

/*
   ** led_init()
   ** 
   ** led_init() is called very early in the bootup-process from setup.c 
   ** and asks the PDC क्रम an usable chassis LCD or LED.
   ** If the PDC करोesn't वापस any info, then the LED
   ** is detected by lasi.c or asp.c and रेजिस्टरed with the
   ** above functions lasi_led_init() or asp_led_init().
   ** KittyHawk machines have often a buggy PDC, so that
   ** we explicitly check क्रम those machines here.
 */

पूर्णांक __init led_init(व्योम)
अणु
	काष्ठा pdc_chassis_info chassis_info;
	पूर्णांक ret;

	snम_लिखो(lcd_text_शेष, माप(lcd_text_शेष),
		"Linux %s", init_utsname()->release);

	/* Work around the buggy PDC of KittyHawk-machines */
	चयन (CPU_HVERSION) अणु
	हाल 0x580:		/* KittyHawk DC2-100 (K100) */
	हाल 0x581:		/* KittyHawk DC3-120 (K210) */
	हाल 0x582:		/* KittyHawk DC3 100 (K400) */
	हाल 0x583:		/* KittyHawk DC3 120 (K410) */
	हाल 0x58B:		/* KittyHawk DC2 100 (K200) */
		prपूर्णांकk(KERN_INFO "%s: KittyHawk-Machine (hversion 0x%x) found, "
				"LED detection skipped.\n", __खाता__, CPU_HVERSION);
		lcd_no_led_support = 1;
		जाओ found;	/* use the preinitialized values of lcd_info */
	पूर्ण

	/* initialize the काष्ठा, so that we can check क्रम valid वापस values */
	lcd_info.model = DISPLAY_MODEL_NONE;
	chassis_info.actcnt = chassis_info.maxcnt = 0;

	ret = pdc_chassis_info(&chassis_info, &lcd_info, माप(lcd_info));
	अगर (ret == PDC_OK) अणु
		DPRINTK((KERN_INFO "%s: chassis info: model=%d (%s), "
			 "lcd_width=%d, cmd_delay=%u,\n"
			 "%s: sizecnt=%d, actcnt=%ld, maxcnt=%ld\n",
		         __खाता__, lcd_info.model,
			 (lcd_info.model==DISPLAY_MODEL_LCD) ? "LCD" :
			  (lcd_info.model==DISPLAY_MODEL_LASI) ? "LED" : "unknown",
			 lcd_info.lcd_width, lcd_info.min_cmd_delay,
			 __खाता__, माप(lcd_info), 
			 chassis_info.actcnt, chassis_info.maxcnt));
		DPRINTK((KERN_INFO "%s: cmd=%p, data=%p, reset1=%x, reset2=%x, act_enable=%d\n",
			__खाता__, lcd_info.lcd_cmd_reg_addr, 
			lcd_info.lcd_data_reg_addr, lcd_info.reset_cmd1,  
			lcd_info.reset_cmd2, lcd_info.act_enable ));
	
		/* check the results. Some machines have a buggy PDC */
		अगर (chassis_info.actcnt <= 0 || chassis_info.actcnt != chassis_info.maxcnt)
			जाओ not_found;

		चयन (lcd_info.model) अणु
		हाल DISPLAY_MODEL_LCD:		/* LCD display */
			अगर (chassis_info.actcnt < 
				दुरत्व(काष्ठा pdc_chassis_lcd_info_ret_block, _pad)-1)
				जाओ not_found;
			अगर (!lcd_info.act_enable) अणु
				DPRINTK((KERN_INFO "PDC prohibited usage of the LCD.\n"));
				जाओ not_found;
			पूर्ण
			अवरोध;

		हाल DISPLAY_MODEL_NONE:	/* no LED or LCD available */
			prपूर्णांकk(KERN_INFO "PDC reported no LCD or LED.\n");
			जाओ not_found;

		हाल DISPLAY_MODEL_LASI:	/* Lasi style 8 bit LED display */
			अगर (chassis_info.actcnt != 8 && chassis_info.actcnt != 32)
				जाओ not_found;
			अवरोध;

		शेष:
			prपूर्णांकk(KERN_WARNING "PDC reported unknown LCD/LED model %d\n",
			       lcd_info.model);
			जाओ not_found;
		पूर्ण /* चयन() */

found:
		/* रेजिस्टर the LCD/LED driver */
		रेजिस्टर_led_driver(lcd_info.model, LCD_CMD_REG, LCD_DATA_REG);
		वापस 0;

	पूर्ण अन्यथा अणु /* अगर() */
		DPRINTK((KERN_INFO "pdc_chassis_info call failed with retval = %d\n", ret));
	पूर्ण

not_found:
	lcd_info.model = DISPLAY_MODEL_NONE;
	वापस 1;
पूर्ण

अटल व्योम __निकास led_निकास(व्योम)
अणु
	unरेजिस्टर_reboot_notअगरier(&led_notअगरier);
	वापस;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
module_init(led_create_procfs)
#पूर्ण_अगर
