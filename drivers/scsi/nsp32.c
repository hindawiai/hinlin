<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NinjaSCSI-32Bi Cardbus, NinjaSCSI-32UDE PCI/CardBus SCSI driver
 * Copyright (C) 2001, 2002, 2003
 *      YOKOTA Hiroshi <yokota@netlab.is.tsukuba.ac.jp>
 *      GOTO Masanori <जाओm@debian.or.jp>, <जाओm@debian.org>
 *
 * Revision History:
 *   1.0: Initial Release.
 *   1.1: Add /proc SDTR status.
 *        Remove obsolete error handler nsp32_reset.
 *        Some clean up.
 *   1.2: PowerPC (big endian) support.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/ioport.h>
#समावेश <linux/major.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_ioctl.h>

#समावेश "nsp32.h"


/***********************************************************************
 * Module parameters
 */
अटल पूर्णांक       trans_mode = 0;	/* शेष: BIOS */
module_param     (trans_mode, पूर्णांक, 0);
MODULE_PARM_DESC(trans_mode, "transfer mode (0: BIOS(default) 1: Async 2: Ultra20M");
#घोषणा ASYNC_MODE    1
#घोषणा ULTRA20M_MODE 2

अटल bool      स्वतः_param = 0;	/* शेष: ON */
module_param     (स्वतः_param, bool, 0);
MODULE_PARM_DESC(स्वतः_param, "AutoParameter mode (0: ON(default) 1: OFF)");

अटल bool      disc_priv  = 1;	/* शेष: OFF */
module_param     (disc_priv, bool, 0);
MODULE_PARM_DESC(disc_priv,  "disconnection privilege mode (0: ON 1: OFF(default))");

MODULE_AUTHOR("YOKOTA Hiroshi <yokota@netlab.is.tsukuba.ac.jp>, GOTO Masanori <gotom@debian.or.jp>");
MODULE_DESCRIPTION("Workbit NinjaSCSI-32Bi/UDE CardBus/PCI SCSI host bus adapter module");
MODULE_LICENSE("GPL");

अटल स्थिर अक्षर *nsp32_release_version = "1.2";


/****************************************************************************
 * Supported hardware
 */
अटल काष्ठा pci_device_id nsp32_pci_table[] = अणु
	अणु
		.venकरोr      = PCI_VENDOR_ID_IODATA,
		.device      = PCI_DEVICE_ID_NINJASCSI_32BI_CBSC_II,
		.subvenकरोr   = PCI_ANY_ID,
		.subdevice   = PCI_ANY_ID,
		.driver_data = MODEL_IODATA,
	पूर्ण,
	अणु
		.venकरोr      = PCI_VENDOR_ID_WORKBIT,
		.device      = PCI_DEVICE_ID_NINJASCSI_32BI_KME,
		.subvenकरोr   = PCI_ANY_ID,
		.subdevice   = PCI_ANY_ID,
		.driver_data = MODEL_KME,
	पूर्ण,
	अणु
		.venकरोr      = PCI_VENDOR_ID_WORKBIT,
		.device      = PCI_DEVICE_ID_NINJASCSI_32BI_WBT,
		.subvenकरोr   = PCI_ANY_ID,
		.subdevice   = PCI_ANY_ID,
		.driver_data = MODEL_WORKBIT,
	पूर्ण,
	अणु
		.venकरोr      = PCI_VENDOR_ID_WORKBIT,
		.device      = PCI_DEVICE_ID_WORKBIT_STANDARD,
		.subvenकरोr   = PCI_ANY_ID,
		.subdevice   = PCI_ANY_ID,
		.driver_data = MODEL_PCI_WORKBIT,
	पूर्ण,
	अणु
		.venकरोr      = PCI_VENDOR_ID_WORKBIT,
		.device      = PCI_DEVICE_ID_NINJASCSI_32BI_LOGITEC,
		.subvenकरोr   = PCI_ANY_ID,
		.subdevice   = PCI_ANY_ID,
		.driver_data = MODEL_LOGITEC,
	पूर्ण,
	अणु
		.venकरोr      = PCI_VENDOR_ID_WORKBIT,
		.device      = PCI_DEVICE_ID_NINJASCSI_32BIB_LOGITEC,
		.subvenकरोr   = PCI_ANY_ID,
		.subdevice   = PCI_ANY_ID,
		.driver_data = MODEL_PCI_LOGITEC,
	पूर्ण,
	अणु
		.venकरोr      = PCI_VENDOR_ID_WORKBIT,
		.device      = PCI_DEVICE_ID_NINJASCSI_32UDE_MELCO,
		.subvenकरोr   = PCI_ANY_ID,
		.subdevice   = PCI_ANY_ID,
		.driver_data = MODEL_PCI_MELCO,
	पूर्ण,
	अणु
		.venकरोr      = PCI_VENDOR_ID_WORKBIT,
		.device      = PCI_DEVICE_ID_NINJASCSI_32UDE_MELCO_II,
		.subvenकरोr   = PCI_ANY_ID,
		.subdevice   = PCI_ANY_ID,
		.driver_data = MODEL_PCI_MELCO,
	पूर्ण,
	अणु0,0,पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, nsp32_pci_table);

अटल nsp32_hw_data nsp32_data_base;  /* probe <-> detect glue */


/*
 * Period/AckWidth speed conversion table
 *
 * Note: This period/ackwidth speed table must be in descending order.
 */
अटल nsp32_sync_table nsp32_sync_table_40M[] = अणु
     /* अणुPNo, AW,   SP,   EP, SREQ smplपूर्ण  Speed(MB/s) Period AckWidth */
	अणु0x1,  0, 0x0c, 0x0c, SMPL_40Mपूर्ण,  /*  20.0 :  50ns,  25ns */
	अणु0x2,  0, 0x0d, 0x18, SMPL_40Mपूर्ण,  /*  13.3 :  75ns,  25ns */
	अणु0x3,  1, 0x19, 0x19, SMPL_40Mपूर्ण,  /*  10.0 : 100ns,  50ns */
	अणु0x4,  1, 0x1a, 0x1f, SMPL_20Mपूर्ण,  /*   8.0 : 125ns,  50ns */
	अणु0x5,  2, 0x20, 0x25, SMPL_20Mपूर्ण,  /*   6.7 : 150ns,  75ns */
	अणु0x6,  2, 0x26, 0x31, SMPL_20Mपूर्ण,  /*   5.7 : 175ns,  75ns */
	अणु0x7,  3, 0x32, 0x32, SMPL_20Mपूर्ण,  /*   5.0 : 200ns, 100ns */
	अणु0x8,  3, 0x33, 0x38, SMPL_10Mपूर्ण,  /*   4.4 : 225ns, 100ns */
	अणु0x9,  3, 0x39, 0x3e, SMPL_10Mपूर्ण,  /*   4.0 : 250ns, 100ns */
पूर्ण;

अटल nsp32_sync_table nsp32_sync_table_20M[] = अणु
	अणु0x1,  0, 0x19, 0x19, SMPL_40Mपूर्ण,  /* 10.0 : 100ns,  50ns */
	अणु0x2,  0, 0x1a, 0x25, SMPL_20Mपूर्ण,  /*  6.7 : 150ns,  50ns */
	अणु0x3,  1, 0x26, 0x32, SMPL_20Mपूर्ण,  /*  5.0 : 200ns, 100ns */
	अणु0x4,  1, 0x33, 0x3e, SMPL_10Mपूर्ण,  /*  4.0 : 250ns, 100ns */
	अणु0x5,  2, 0x3f, 0x4b, SMPL_10Mपूर्ण,  /*  3.3 : 300ns, 150ns */
	अणु0x6,  2, 0x4c, 0x57, SMPL_10Mपूर्ण,  /*  2.8 : 350ns, 150ns */
	अणु0x7,  3, 0x58, 0x64, SMPL_10Mपूर्ण,  /*  2.5 : 400ns, 200ns */
	अणु0x8,  3, 0x65, 0x70, SMPL_10Mपूर्ण,  /*  2.2 : 450ns, 200ns */
	अणु0x9,  3, 0x71, 0x7d, SMPL_10Mपूर्ण,  /*  2.0 : 500ns, 200ns */
पूर्ण;

अटल nsp32_sync_table nsp32_sync_table_pci[] = अणु
	अणु0x1,  0, 0x0c, 0x0f, SMPL_40Mपूर्ण,  /* 16.6 :  60ns,  30ns */
	अणु0x2,  0, 0x10, 0x16, SMPL_40Mपूर्ण,  /* 11.1 :  90ns,  30ns */
	अणु0x3,  1, 0x17, 0x1e, SMPL_20Mपूर्ण,  /*  8.3 : 120ns,  60ns */
	अणु0x4,  1, 0x1f, 0x25, SMPL_20Mपूर्ण,  /*  6.7 : 150ns,  60ns */
	अणु0x5,  2, 0x26, 0x2d, SMPL_20Mपूर्ण,  /*  5.6 : 180ns,  90ns */
	अणु0x6,  2, 0x2e, 0x34, SMPL_10Mपूर्ण,  /*  4.8 : 210ns,  90ns */
	अणु0x7,  3, 0x35, 0x3c, SMPL_10Mपूर्ण,  /*  4.2 : 240ns, 120ns */
	अणु0x8,  3, 0x3d, 0x43, SMPL_10Mपूर्ण,  /*  3.7 : 270ns, 120ns */
	अणु0x9,  3, 0x44, 0x4b, SMPL_10Mपूर्ण,  /*  3.3 : 300ns, 120ns */
पूर्ण;

/*
 * function declaration
 */
/* module entry poपूर्णांक */
अटल पूर्णांक         nsp32_probe (काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम        nsp32_हटाओ(काष्ठा pci_dev *);
अटल पूर्णांक  __init init_nsp32  (व्योम);
अटल व्योम __निकास निकास_nsp32  (व्योम);

/* काष्ठा काष्ठा scsi_host_ढाँचा */
अटल पूर्णांक         nsp32_show_info   (काष्ठा seq_file *, काष्ठा Scsi_Host *);

अटल पूर्णांक         nsp32_detect      (काष्ठा pci_dev *pdev);
अटल पूर्णांक         nsp32_queuecommand(काष्ठा Scsi_Host *, काष्ठा scsi_cmnd *);
अटल स्थिर अक्षर *nsp32_info        (काष्ठा Scsi_Host *);
अटल पूर्णांक         nsp32_release     (काष्ठा Scsi_Host *);

/* SCSI error handler */
अटल पूर्णांक         nsp32_eh_पात     (काष्ठा scsi_cmnd *);
अटल पूर्णांक         nsp32_eh_host_reset(काष्ठा scsi_cmnd *);

/* generate SCSI message */
अटल व्योम nsp32_build_identअगरy(काष्ठा scsi_cmnd *);
अटल व्योम nsp32_build_nop     (काष्ठा scsi_cmnd *);
अटल व्योम nsp32_build_reject  (काष्ठा scsi_cmnd *);
अटल व्योम nsp32_build_sdtr    (काष्ठा scsi_cmnd *, अचिन्हित अक्षर, अचिन्हित अक्षर);

/* SCSI message handler */
अटल पूर्णांक  nsp32_busमुक्त_occur(काष्ठा scsi_cmnd *, अचिन्हित लघु);
अटल व्योम nsp32_msgout_occur (काष्ठा scsi_cmnd *);
अटल व्योम nsp32_msgin_occur  (काष्ठा scsi_cmnd *, अचिन्हित दीर्घ, अचिन्हित लघु);

अटल पूर्णांक  nsp32_setup_sg_table    (काष्ठा scsi_cmnd *);
अटल पूर्णांक  nsp32_selection_स्वतःpara(काष्ठा scsi_cmnd *);
अटल पूर्णांक  nsp32_selection_स्वतःscsi(काष्ठा scsi_cmnd *);
अटल व्योम nsp32_scsi_करोne         (काष्ठा scsi_cmnd *);
अटल पूर्णांक  nsp32_arbitration       (काष्ठा scsi_cmnd *, अचिन्हित पूर्णांक);
अटल पूर्णांक  nsp32_reselection       (काष्ठा scsi_cmnd *, अचिन्हित अक्षर);
अटल व्योम nsp32_adjust_busमुक्त    (काष्ठा scsi_cmnd *, अचिन्हित पूर्णांक);
अटल व्योम nsp32_restart_स्वतःscsi  (काष्ठा scsi_cmnd *, अचिन्हित लघु);

/* SCSI SDTR */
अटल व्योम nsp32_analyze_sdtr       (काष्ठा scsi_cmnd *);
अटल पूर्णांक  nsp32_search_period_entry(nsp32_hw_data *, nsp32_target *, अचिन्हित अक्षर);
अटल व्योम nsp32_set_async          (nsp32_hw_data *, nsp32_target *);
अटल व्योम nsp32_set_max_sync       (nsp32_hw_data *, nsp32_target *, अचिन्हित अक्षर *, अचिन्हित अक्षर *);
अटल व्योम nsp32_set_sync_entry     (nsp32_hw_data *, nsp32_target *, पूर्णांक, अचिन्हित अक्षर);

/* SCSI bus status handler */
अटल व्योम nsp32_रुको_req    (nsp32_hw_data *, पूर्णांक);
अटल व्योम nsp32_रुको_sack   (nsp32_hw_data *, पूर्णांक);
अटल व्योम nsp32_sack_निश्चित (nsp32_hw_data *);
अटल व्योम nsp32_sack_negate (nsp32_hw_data *);
अटल व्योम nsp32_करो_bus_reset(nsp32_hw_data *);

/* hardware पूर्णांकerrupt handler */
अटल irqवापस_t करो_nsp32_isr(पूर्णांक, व्योम *);

/* initialize hardware */
अटल पूर्णांक  nsp32hw_init(nsp32_hw_data *);

/* EEPROM handler */
अटल        पूर्णांक  nsp32_getprom_param (nsp32_hw_data *);
अटल        पूर्णांक  nsp32_getprom_at24  (nsp32_hw_data *);
अटल        पूर्णांक  nsp32_getprom_c16   (nsp32_hw_data *);
अटल        व्योम nsp32_prom_start    (nsp32_hw_data *);
अटल        व्योम nsp32_prom_stop     (nsp32_hw_data *);
अटल        पूर्णांक  nsp32_prom_पढ़ो     (nsp32_hw_data *, पूर्णांक);
अटल        पूर्णांक  nsp32_prom_पढ़ो_bit (nsp32_hw_data *);
अटल        व्योम nsp32_prom_ग_लिखो_bit(nsp32_hw_data *, पूर्णांक);
अटल        व्योम nsp32_prom_set      (nsp32_hw_data *, पूर्णांक, पूर्णांक);
अटल        पूर्णांक  nsp32_prom_get      (nsp32_hw_data *, पूर्णांक);

/* debug/warning/info message */
अटल व्योम nsp32_message (स्थिर अक्षर *, पूर्णांक, अक्षर *, अक्षर *, ...);
#अगर_घोषित NSP32_DEBUG
अटल व्योम nsp32_dmessage(स्थिर अक्षर *, पूर्णांक, पूर्णांक,    अक्षर *, ...);
#पूर्ण_अगर

/*
 * max_sectors is currently limited up to 128.
 */
अटल काष्ठा scsi_host_ढाँचा nsp32_ढाँचा = अणु
	.proc_name			= "nsp32",
	.name				= "Workbit NinjaSCSI-32Bi/UDE",
	.show_info			= nsp32_show_info,
	.info				= nsp32_info,
	.queuecommand			= nsp32_queuecommand,
	.can_queue			= 1,
	.sg_tablesize			= NSP32_SG_SIZE,
	.max_sectors			= 128,
	.this_id			= NSP32_HOST_SCSIID,
	.dma_boundary			= PAGE_SIZE - 1,
	.eh_पात_handler		= nsp32_eh_पात,
	.eh_host_reset_handler		= nsp32_eh_host_reset,
/*	.highmem_io			= 1, */
पूर्ण;

#समावेश "nsp32_io.h"

/***********************************************************************
 * debug, error prपूर्णांक
 */
#अगर_अघोषित NSP32_DEBUG
# define NSP32_DEBUG_MASK	      0x000000
# define nsp32_msg(type, args...)     nsp32_message ("", 0, (type), args)
# define nsp32_dbg(mask, args...)     /* */
#अन्यथा
# define NSP32_DEBUG_MASK	      0xffffff
# define nsp32_msg(type, args...) \
	nsp32_message (__func__, __LINE__, (type), args)
# define nsp32_dbg(mask, args...) \
	nsp32_dmessage(__func__, __LINE__, (mask), args)
#पूर्ण_अगर

#घोषणा NSP32_DEBUG_QUEUECOMMAND	BIT(0)
#घोषणा NSP32_DEBUG_REGISTER		BIT(1)
#घोषणा NSP32_DEBUG_AUTOSCSI		BIT(2)
#घोषणा NSP32_DEBUG_INTR		BIT(3)
#घोषणा NSP32_DEBUG_SGLIST		BIT(4)
#घोषणा NSP32_DEBUG_BUSFREE		BIT(5)
#घोषणा NSP32_DEBUG_CDB_CONTENTS	BIT(6)
#घोषणा NSP32_DEBUG_RESELECTION		BIT(7)
#घोषणा NSP32_DEBUG_MSGINOCCUR		BIT(8)
#घोषणा NSP32_DEBUG_EEPROM		BIT(9)
#घोषणा NSP32_DEBUG_MSGOUTOCCUR		BIT(10)
#घोषणा NSP32_DEBUG_BUSRESET		BIT(11)
#घोषणा NSP32_DEBUG_RESTART		BIT(12)
#घोषणा NSP32_DEBUG_SYNC		BIT(13)
#घोषणा NSP32_DEBUG_WAIT		BIT(14)
#घोषणा NSP32_DEBUG_TARGETFLAG		BIT(15)
#घोषणा NSP32_DEBUG_PROC		BIT(16)
#घोषणा NSP32_DEBUG_INIT		BIT(17)
#घोषणा NSP32_SPECIAL_PRINT_REGISTER	BIT(20)

#घोषणा NSP32_DEBUG_BUF_LEN		100

__म_लिखो(4, 5)
अटल व्योम nsp32_message(स्थिर अक्षर *func, पूर्णांक line, अक्षर *type, अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर buf[NSP32_DEBUG_BUF_LEN];

	बहु_शुरू(args, fmt);
	vsnम_लिखो(buf, माप(buf), fmt, args);
	बहु_पूर्ण(args);

#अगर_अघोषित NSP32_DEBUG
	prपूर्णांकk("%snsp32: %s\n", type, buf);
#अन्यथा
	prपूर्णांकk("%snsp32: %s (%d): %s\n", type, func, line, buf);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित NSP32_DEBUG
अटल व्योम nsp32_dmessage(स्थिर अक्षर *func, पूर्णांक line, पूर्णांक mask, अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर buf[NSP32_DEBUG_BUF_LEN];

	बहु_शुरू(args, fmt);
	vsnम_लिखो(buf, माप(buf), fmt, args);
	बहु_पूर्ण(args);

	अगर (mask & NSP32_DEBUG_MASK) अणु
		prपूर्णांकk("nsp32-debug: 0x%x %s (%d): %s\n", mask, func, line, buf);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित NSP32_DEBUG
# include "nsp32_debug.c"
#अन्यथा
# define show_command(arg)   /* */
# define show_busphase(arg)  /* */
# define show_स्वतःphase(arg) /* */
#पूर्ण_अगर

/*
 * IDENTIFY Message
 */
अटल व्योम nsp32_build_identअगरy(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	पूर्णांक pos             = data->msgout_len;
	पूर्णांक mode            = FALSE;

	/* XXX: Auto DiscPriv detection is progressing... */
	अगर (disc_priv == 0) अणु
		/* mode = TRUE; */
	पूर्ण

	data->msgoutbuf[pos] = IDENTIFY(mode, SCpnt->device->lun); pos++;

	data->msgout_len = pos;
पूर्ण

/*
 * SDTR Message Routine
 */
अटल व्योम nsp32_build_sdtr(काष्ठा scsi_cmnd    *SCpnt,
			     अचिन्हित अक्षर period,
			     अचिन्हित अक्षर offset)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	पूर्णांक pos             = data->msgout_len;

	data->msgoutbuf[pos] = EXTENDED_MESSAGE;  pos++;
	data->msgoutbuf[pos] = EXTENDED_SDTR_LEN; pos++;
	data->msgoutbuf[pos] = EXTENDED_SDTR;     pos++;
	data->msgoutbuf[pos] = period;            pos++;
	data->msgoutbuf[pos] = offset;            pos++;

	data->msgout_len = pos;
पूर्ण

/*
 * No Operation Message
 */
अटल व्योम nsp32_build_nop(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	पूर्णांक            pos  = data->msgout_len;

	अगर (pos != 0) अणु
		nsp32_msg(KERN_WARNING,
			  "Some messages are already contained!");
		वापस;
	पूर्ण

	data->msgoutbuf[pos] = NOP; pos++;
	data->msgout_len = pos;
पूर्ण

/*
 * Reject Message
 */
अटल व्योम nsp32_build_reject(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	पूर्णांक            pos  = data->msgout_len;

	data->msgoutbuf[pos] = MESSAGE_REJECT; pos++;
	data->msgout_len = pos;
पूर्ण
	
/*
 * समयr
 */
#अगर 0
अटल व्योम nsp32_start_समयr(काष्ठा scsi_cmnd *SCpnt, पूर्णांक समय)
अणु
	अचिन्हित पूर्णांक base = SCpnt->host->io_port;

	nsp32_dbg(NSP32_DEBUG_INTR, "timer=%d", समय);

	अगर (समय & (~TIMER_CNT_MASK)) अणु
		nsp32_dbg(NSP32_DEBUG_INTR, "timer set overflow");
	पूर्ण

	nsp32_ग_लिखो2(base, TIMER_SET, समय & TIMER_CNT_MASK);
पूर्ण
#पूर्ण_अगर


/*
 * set SCSI command and other parameter to asic, and start selection phase
 */
अटल पूर्णांक nsp32_selection_स्वतःpara(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp32_hw_data  *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	अचिन्हित पूर्णांक	base    = SCpnt->device->host->io_port;
	अचिन्हित पूर्णांक	host_id = SCpnt->device->host->this_id;
	अचिन्हित अक्षर	target  = scmd_id(SCpnt);
	nsp32_स्वतःparam *param  = data->स्वतःparam;
	अचिन्हित अक्षर	phase;
	पूर्णांक		i, ret;
	अचिन्हित पूर्णांक	msgout;
	u16_le	        s;

	nsp32_dbg(NSP32_DEBUG_AUTOSCSI, "in");

	/*
	 * check bus मुक्त
	 */
	phase = nsp32_पढ़ो1(base, SCSI_BUS_MONITOR);
	अगर (phase != BUSMON_BUS_FREE) अणु
		nsp32_msg(KERN_WARNING, "bus busy");
		show_busphase(phase & BUSMON_PHASE_MASK);
		SCpnt->result = DID_BUS_BUSY << 16;
		वापस FALSE;
	पूर्ण

	/*
	 * message out
	 *
	 * Note: If the range of msgout_len is 1 - 3, fill scsi_msgout.
	 *       over 3 messages needs another routine.
	 */
	अगर (data->msgout_len == 0) अणु
		nsp32_msg(KERN_ERR, "SCSI MsgOut without any message!");
		SCpnt->result = DID_ERROR << 16;
		वापस FALSE;
	पूर्ण अन्यथा अगर (data->msgout_len > 0 && data->msgout_len <= 3) अणु
		msgout = 0;
		क्रम (i = 0; i < data->msgout_len; i++) अणु
			/*
			 * the sending order of the message is:
			 *  MCNT 3: MSG#0 -> MSG#1 -> MSG#2
			 *  MCNT 2:          MSG#1 -> MSG#2
			 *  MCNT 1:                   MSG#2    
			 */
			msgout >>= 8;
			msgout |= ((अचिन्हित पूर्णांक)(data->msgoutbuf[i]) << 24);
		पूर्ण
		msgout |= MV_VALID;	/* MV valid */
		msgout |= (अचिन्हित पूर्णांक)data->msgout_len; /* len */
	पूर्ण अन्यथा अणु
		/* data->msgout_len > 3 */
		msgout = 0;
	पूर्ण

	// nsp_dbg(NSP32_DEBUG_AUTOSCSI, "sel time out=0x%x\n", nsp32_पढ़ो2(base, SEL_TIME_OUT));
	// nsp32_ग_लिखो2(base, SEL_TIME_OUT,   SEL_TIMEOUT_TIME);

	/*
	 * setup asic parameter
	 */
	स_रखो(param, 0, माप(nsp32_स्वतःparam));

	/* cdb */
	क्रम (i = 0; i < SCpnt->cmd_len; i++) अणु
		param->cdb[4 * i] = SCpnt->cmnd[i];
	पूर्ण

	/* outgoing messages */
	param->msgout = cpu_to_le32(msgout);

	/* syncreg, ackwidth, target id, SREQ sampling rate */
	param->syncreg    = data->cur_target->syncreg;
	param->ackwidth   = data->cur_target->ackwidth;
	param->target_id  = BIT(host_id) | BIT(target);
	param->sample_reg = data->cur_target->sample_reg;

	// nsp32_dbg(NSP32_DEBUG_AUTOSCSI, "sample rate=0x%x\n", data->cur_target->sample_reg);

	/* command control */
	param->command_control = cpu_to_le16(CLEAR_CDB_FIFO_POINTER |
					     AUTOSCSI_START         |
					     AUTO_MSGIN_00_OR_04    |
					     AUTO_MSGIN_02          |
					     AUTO_ATN               );


	/* transfer control */
	s = 0;
	चयन (data->trans_method) अणु
	हाल NSP32_TRANSFER_BUSMASTER:
		s |= BM_START;
		अवरोध;
	हाल NSP32_TRANSFER_MMIO:
		s |= CB_MMIO_MODE;
		अवरोध;
	हाल NSP32_TRANSFER_PIO:
		s |= CB_IO_MODE;
		अवरोध;
	शेष:
		nsp32_msg(KERN_ERR, "unknown trans_method");
		अवरोध;
	पूर्ण
	/*
	 * OR-ed BLIEND_MODE, FIFO पूर्णांकr is decreased, instead of PCI bus रुकोs.
	 * For bus master transfer, it's taken off.
	 */
	s |= (TRANSFER_GO | ALL_COUNTER_CLR);
	param->transfer_control = cpu_to_le16(s);

	/* sg table addr */
	param->sgt_poपूर्णांकer = cpu_to_le32(data->cur_lunt->sglun_paddr);

	/*
	 * transfer parameter to ASIC
	 */
	nsp32_ग_लिखो4(base, SGT_ADR,         data->स्वतः_paddr);
	nsp32_ग_लिखो2(base, COMMAND_CONTROL, CLEAR_CDB_FIFO_POINTER |
		                            AUTO_PARAMETER         );

	/*
	 * Check arbitration
	 */
	ret = nsp32_arbitration(SCpnt, base);

	वापस ret;
पूर्ण


/*
 * Selection with AUTO SCSI (without AUTO PARAMETER)
 */
अटल पूर्णांक nsp32_selection_स्वतःscsi(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp32_hw_data  *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	अचिन्हित पूर्णांक	base    = SCpnt->device->host->io_port;
	अचिन्हित पूर्णांक	host_id = SCpnt->device->host->this_id;
	अचिन्हित अक्षर	target  = scmd_id(SCpnt);
	अचिन्हित अक्षर	phase;
	पूर्णांक		status;
	अचिन्हित लघु	command	= 0;
	अचिन्हित पूर्णांक	msgout  = 0;
	पूर्णांक		i;

	nsp32_dbg(NSP32_DEBUG_AUTOSCSI, "in");

	/*
	 * IRQ disable
	 */
	nsp32_ग_लिखो2(base, IRQ_CONTROL, IRQ_CONTROL_ALL_IRQ_MASK);

	/*
	 * check bus line
	 */
	phase = nsp32_पढ़ो1(base, SCSI_BUS_MONITOR);
	अगर ((phase & BUSMON_BSY) || (phase & BUSMON_SEL)) अणु
		nsp32_msg(KERN_WARNING, "bus busy");
		SCpnt->result = DID_BUS_BUSY << 16;
		status = 1;
		जाओ out;
        पूर्ण

	/*
	 * clear execph
	 */
	nsp32_पढ़ो2(base, SCSI_EXECUTE_PHASE);

	/*
	 * clear FIFO counter to set CDBs
	 */
	nsp32_ग_लिखो2(base, COMMAND_CONTROL, CLEAR_CDB_FIFO_POINTER);

	/*
	 * set CDB0 - CDB15
	 */
	क्रम (i = 0; i < SCpnt->cmd_len; i++) अणु
		nsp32_ग_लिखो1(base, COMMAND_DATA, SCpnt->cmnd[i]);
        पूर्ण
	nsp32_dbg(NSP32_DEBUG_CDB_CONTENTS, "CDB[0]=[0x%x]", SCpnt->cmnd[0]);

	/*
	 * set SCSIOUT LATCH(initiator)/TARGET(target) (OR-ed) ID
	 */
	nsp32_ग_लिखो1(base, SCSI_OUT_LATCH_TARGET_ID, BIT(host_id) | BIT(target));

	/*
	 * set SCSI MSGOUT REG
	 *
	 * Note: If the range of msgout_len is 1 - 3, fill scsi_msgout.
	 *       over 3 messages needs another routine.
	 */
	अगर (data->msgout_len == 0) अणु
		nsp32_msg(KERN_ERR, "SCSI MsgOut without any message!");
		SCpnt->result = DID_ERROR << 16;
		status = 1;
		जाओ out;
	पूर्ण अन्यथा अगर (data->msgout_len > 0 && data->msgout_len <= 3) अणु
		msgout = 0;
		क्रम (i = 0; i < data->msgout_len; i++) अणु
			/*
			 * the sending order of the message is:
			 *  MCNT 3: MSG#0 -> MSG#1 -> MSG#2
			 *  MCNT 2:          MSG#1 -> MSG#2
			 *  MCNT 1:                   MSG#2    
			 */
			msgout >>= 8;
			msgout |= ((अचिन्हित पूर्णांक)(data->msgoutbuf[i]) << 24);
		पूर्ण
		msgout |= MV_VALID;	/* MV valid */
		msgout |= (अचिन्हित पूर्णांक)data->msgout_len; /* len */
		nsp32_ग_लिखो4(base, SCSI_MSG_OUT, msgout);
	पूर्ण अन्यथा अणु
		/* data->msgout_len > 3 */
		nsp32_ग_लिखो4(base, SCSI_MSG_OUT, 0);
	पूर्ण

	/*
	 * set selection समयout(= 250ms)
	 */
	nsp32_ग_लिखो2(base, SEL_TIME_OUT,   SEL_TIMEOUT_TIME);

	/*
	 * set SREQ hazard समाप्तer sampling rate
	 * 
	 * TODO: sample_rate (BASE+0F) is 0 when पूर्णांकernal घड़ी = 40MHz.
	 *      check other पूर्णांकernal घड़ी!
	 */
	nsp32_ग_लिखो1(base, SREQ_SMPL_RATE, data->cur_target->sample_reg);

	/*
	 * clear Arbit
	 */
	nsp32_ग_लिखो1(base, SET_ARBIT,      ARBIT_CLEAR);

	/*
	 * set SYNCREG
	 * Don't set BM_START_ADR beक्रमe setting this रेजिस्टर.
	 */
	nsp32_ग_लिखो1(base, SYNC_REG,  data->cur_target->syncreg);

	/*
	 * set ACKWIDTH
	 */
	nsp32_ग_लिखो1(base, ACK_WIDTH, data->cur_target->ackwidth);

	nsp32_dbg(NSP32_DEBUG_AUTOSCSI,
		  "syncreg=0x%x, ackwidth=0x%x, sgtpaddr=0x%x, id=0x%x",
		  nsp32_पढ़ो1(base, SYNC_REG), nsp32_पढ़ो1(base, ACK_WIDTH),
		  nsp32_पढ़ो4(base, SGT_ADR), nsp32_पढ़ो1(base, SCSI_OUT_LATCH_TARGET_ID));
	nsp32_dbg(NSP32_DEBUG_AUTOSCSI, "msgout_len=%d, msgout=0x%x",
		  data->msgout_len, msgout);

	/*
	 * set SGT ADDR (physical address)
	 */
	nsp32_ग_लिखो4(base, SGT_ADR, data->cur_lunt->sglun_paddr);

	/*
	 * set TRANSFER CONTROL REG
	 */
	command = 0;
	command |= (TRANSFER_GO | ALL_COUNTER_CLR);
	अगर (data->trans_method & NSP32_TRANSFER_BUSMASTER) अणु
		अगर (scsi_bufflen(SCpnt) > 0) अणु
			command |= BM_START;
		पूर्ण
	पूर्ण अन्यथा अगर (data->trans_method & NSP32_TRANSFER_MMIO) अणु
		command |= CB_MMIO_MODE;
	पूर्ण अन्यथा अगर (data->trans_method & NSP32_TRANSFER_PIO) अणु
		command |= CB_IO_MODE;
	पूर्ण
	nsp32_ग_लिखो2(base, TRANSFER_CONTROL, command);

	/*
	 * start AUTO SCSI, kick off arbitration
	 */
	command = (CLEAR_CDB_FIFO_POINTER |
		   AUTOSCSI_START         |
		   AUTO_MSGIN_00_OR_04    |
		   AUTO_MSGIN_02          |
		   AUTO_ATN                );
	nsp32_ग_लिखो2(base, COMMAND_CONTROL, command);

	/*
	 * Check arbitration
	 */
	status = nsp32_arbitration(SCpnt, base);

 out:
	/*
	 * IRQ enable
	 */
	nsp32_ग_लिखो2(base, IRQ_CONTROL, 0);

	वापस status;
पूर्ण


/*
 * Arbitration Status Check
 *	
 * Note: Arbitration counter is रुकोed during ARBIT_GO is not lअगरting.
 *	 Using udelay(1) consumes CPU समय and प्रणाली समय, but 
 *	 arbitration delay समय is defined minimal 2.4us in SCSI
 *	 specअगरication, thus udelay works as coarse grained रुको समयr.
 */
अटल पूर्णांक nsp32_arbitration(काष्ठा scsi_cmnd *SCpnt, अचिन्हित पूर्णांक base)
अणु
	अचिन्हित अक्षर arbit;
	पूर्णांक	      status = TRUE;
	पूर्णांक	      समय   = 0;

	करो अणु
		arbit = nsp32_पढ़ो1(base, ARBIT_STATUS);
		समय++;
	पूर्ण जबतक ((arbit & (ARBIT_WIN | ARBIT_FAIL)) == 0 &&
		 (समय <= ARBIT_TIMEOUT_TIME));

	nsp32_dbg(NSP32_DEBUG_AUTOSCSI,
		  "arbit: 0x%x, delay time: %d", arbit, समय);

	अगर (arbit & ARBIT_WIN) अणु
		/* Arbitration succeeded */
		SCpnt->result = DID_OK << 16;
		nsp32_index_ग_लिखो1(base, EXT_PORT, LED_ON); /* PCI LED on */
	पूर्ण अन्यथा अगर (arbit & ARBIT_FAIL) अणु
		/* Arbitration failed */
		SCpnt->result = DID_BUS_BUSY << 16;
		status = FALSE;
	पूर्ण अन्यथा अणु
		/*
		 * unknown error or ARBIT_GO समयout,
		 * something lock up! guess no connection.
		 */
		nsp32_dbg(NSP32_DEBUG_AUTOSCSI, "arbit timeout");
		SCpnt->result = DID_NO_CONNECT << 16;
		status = FALSE;
        पूर्ण

	/*
	 * clear Arbit
	 */
	nsp32_ग_लिखो1(base, SET_ARBIT, ARBIT_CLEAR);

	वापस status;
पूर्ण


/*
 * reselection
 *
 * Note: This reselection routine is called from msgin_occur,
 *	 reselection target id&lun must be alपढ़ोy set.
 *	 SCSI-2 says IDENTIFY implies RESTORE_POINTER operation.
 */
अटल पूर्णांक nsp32_reselection(काष्ठा scsi_cmnd *SCpnt, अचिन्हित अक्षर newlun)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	अचिन्हित पूर्णांक   host_id = SCpnt->device->host->this_id;
	अचिन्हित पूर्णांक   base    = SCpnt->device->host->io_port;
	अचिन्हित अक्षर  पंचांगpid, newid;

	nsp32_dbg(NSP32_DEBUG_RESELECTION, "enter");

	/*
	 * calculate reselected SCSI ID
	 */
	पंचांगpid = nsp32_पढ़ो1(base, RESELECT_ID);
	पंचांगpid &= (~BIT(host_id));
	newid = 0;
	जबतक (पंचांगpid) अणु
		अगर (पंचांगpid & 1) अणु
			अवरोध;
		पूर्ण
		पंचांगpid >>= 1;
		newid++;
	पूर्ण

	/*
	 * If reselected New ID:LUN is not existed
	 * or current nexus is not existed, unexpected
	 * reselection is occurred. Send reject message.
	 */
	अगर (newid >= ARRAY_SIZE(data->lunt) || newlun >= ARRAY_SIZE(data->lunt[0])) अणु
		nsp32_msg(KERN_WARNING, "unknown id/lun");
		वापस FALSE;
	पूर्ण अन्यथा अगर(data->lunt[newid][newlun].SCpnt == शून्य) अणु
		nsp32_msg(KERN_WARNING, "no SCSI command is processing");
		वापस FALSE;
	पूर्ण

	data->cur_id    = newid;
	data->cur_lun   = newlun;
	data->cur_target = &(data->target[newid]);
	data->cur_lunt   = &(data->lunt[newid][newlun]);

	/* reset SACK/SavedACK counter (or ALL clear?) */
	nsp32_ग_लिखो4(base, CLR_COUNTER, CLRCOUNTER_ALLMASK);

	वापस TRUE;
पूर्ण


/*
 * nsp32_setup_sg_table - build scatter gather list क्रम transfer data
 *			    with bus master.
 *
 * Note: NinjaSCSI-32Bi/UDE bus master can not transfer over 64KB at a समय.
 */
अटल पूर्णांक nsp32_setup_sg_table(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	काष्ठा scatterlist *sg;
	nsp32_sgtable *sgt = data->cur_lunt->sglun->sgt;
	पूर्णांक num, i;
	u32_le l;

	अगर (sgt == शून्य) अणु
		nsp32_dbg(NSP32_DEBUG_SGLIST, "SGT == null");
		वापस FALSE;
	पूर्ण

	num = scsi_dma_map(SCpnt);
	अगर (!num)
		वापस TRUE;
	अन्यथा अगर (num < 0)
		वापस FALSE;
	अन्यथा अणु
		scsi_क्रम_each_sg(SCpnt, sg, num, i) अणु
			/*
			 * Build nsp32_sglist, substitute sg dma addresses.
			 */
			sgt[i].addr = cpu_to_le32(sg_dma_address(sg));
			sgt[i].len  = cpu_to_le32(sg_dma_len(sg));

			अगर (le32_to_cpu(sgt[i].len) > 0x10000) अणु
				nsp32_msg(KERN_ERR,
					"can't transfer over 64KB at a time, size=0x%x", le32_to_cpu(sgt[i].len));
				वापस FALSE;
			पूर्ण
			nsp32_dbg(NSP32_DEBUG_SGLIST,
				  "num 0x%x : addr 0x%lx len 0x%lx",
				  i,
				  le32_to_cpu(sgt[i].addr),
				  le32_to_cpu(sgt[i].len ));
		पूर्ण

		/* set end mark */
		l = le32_to_cpu(sgt[num-1].len);
		sgt[num-1].len = cpu_to_le32(l | SGTEND);
	पूर्ण

	वापस TRUE;
पूर्ण

अटल पूर्णांक nsp32_queuecommand_lck(काष्ठा scsi_cmnd *SCpnt, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	nsp32_target *target;
	nsp32_lunt   *cur_lunt;
	पूर्णांक ret;

	nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND,
		  "enter. target: 0x%x LUN: 0x%llx cmnd: 0x%x cmndlen: 0x%x "
		  "use_sg: 0x%x reqbuf: 0x%lx reqlen: 0x%x",
		  SCpnt->device->id, SCpnt->device->lun, SCpnt->cmnd[0], SCpnt->cmd_len,
		  scsi_sg_count(SCpnt), scsi_sglist(SCpnt), scsi_bufflen(SCpnt));

	अगर (data->CurrentSC != शून्य) अणु
		nsp32_msg(KERN_ERR, "Currentsc != NULL. Cancel this command request");
		data->CurrentSC = शून्य;
		SCpnt->result   = DID_NO_CONNECT << 16;
		करोne(SCpnt);
		वापस 0;
	पूर्ण

	/* check target ID is not same as this initiator ID */
	अगर (scmd_id(SCpnt) == SCpnt->device->host->this_id) अणु
		nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND, "target==host???");
		SCpnt->result = DID_BAD_TARGET << 16;
		करोne(SCpnt);
		वापस 0;
	पूर्ण

	/* check target LUN is allowable value */
	अगर (SCpnt->device->lun >= MAX_LUN) अणु
		nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND, "no more lun");
		SCpnt->result = DID_BAD_TARGET << 16;
		करोne(SCpnt);
		वापस 0;
	पूर्ण

	show_command(SCpnt);

	SCpnt->scsi_करोne     = करोne;
	data->CurrentSC      = SCpnt;
	SCpnt->SCp.Status    = SAM_STAT_CHECK_CONDITION;
	SCpnt->SCp.Message   = 0;
	scsi_set_resid(SCpnt, scsi_bufflen(SCpnt));

	SCpnt->SCp.ptr		    = (अक्षर *)scsi_sglist(SCpnt);
	SCpnt->SCp.this_residual    = scsi_bufflen(SCpnt);
	SCpnt->SCp.buffer	    = शून्य;
	SCpnt->SCp.buffers_residual = 0;

	/* initialize data */
	data->msgout_len	= 0;
	data->msgin_len		= 0;
	cur_lunt		= &(data->lunt[SCpnt->device->id][SCpnt->device->lun]);
	cur_lunt->SCpnt		= SCpnt;
	cur_lunt->save_datp	= 0;
	cur_lunt->msgin03	= FALSE;
	data->cur_lunt		= cur_lunt;
	data->cur_id		= SCpnt->device->id;
	data->cur_lun		= SCpnt->device->lun;

	ret = nsp32_setup_sg_table(SCpnt);
	अगर (ret == FALSE) अणु
		nsp32_msg(KERN_ERR, "SGT fail");
		SCpnt->result = DID_ERROR << 16;
		nsp32_scsi_करोne(SCpnt);
		वापस 0;
	पूर्ण

	/* Build IDENTIFY */
	nsp32_build_identअगरy(SCpnt);

	/* 
	 * If target is the first समय to transfer after the reset
	 * (target करोn't have SDTR_DONE and SDTR_INITIATOR), sync
	 * message SDTR is needed to करो synchronous transfer.
	 */
	target = &data->target[scmd_id(SCpnt)];
	data->cur_target = target;

	अगर (!(target->sync_flag & (SDTR_DONE | SDTR_INITIATOR | SDTR_TARGET))) अणु
		अचिन्हित अक्षर period, offset;

		अगर (trans_mode != ASYNC_MODE) अणु
			nsp32_set_max_sync(data, target, &period, &offset);
			nsp32_build_sdtr(SCpnt, period, offset);
			target->sync_flag |= SDTR_INITIATOR;
		पूर्ण अन्यथा अणु
			nsp32_set_async(data, target);
			target->sync_flag |= SDTR_DONE;
		पूर्ण

		nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND,
			  "SDTR: entry: %d start_period: 0x%x offset: 0x%x\n",
			  target->limit_entry, period, offset);
	पूर्ण अन्यथा अगर (target->sync_flag & SDTR_INITIATOR) अणु
		/*
		 * It was negotiating SDTR with target, sending from the
		 * initiator, but there are no chance to हटाओ this flag.
		 * Set async because we करोn't get proper negotiation.
		 */
		nsp32_set_async(data, target);
		target->sync_flag &= ~SDTR_INITIATOR;
		target->sync_flag |= SDTR_DONE;

		nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND,
			  "SDTR_INITIATOR: fall back to async");
	पूर्ण अन्यथा अगर (target->sync_flag & SDTR_TARGET) अणु
		/*
		 * It was negotiating SDTR with target, sending from target,
		 * but there are no chance to हटाओ this flag.  Set async
		 * because we करोn't get proper negotiation.
		 */
		nsp32_set_async(data, target);
		target->sync_flag &= ~SDTR_TARGET;
		target->sync_flag |= SDTR_DONE;

		nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND,
			  "Unknown SDTR from target is reached, fall back to async.");
	पूर्ण

	nsp32_dbg(NSP32_DEBUG_TARGETFLAG,
		  "target: %d sync_flag: 0x%x syncreg: 0x%x ackwidth: 0x%x",
		  SCpnt->device->id, target->sync_flag, target->syncreg,
		  target->ackwidth);

	/* Selection */
	अगर (स्वतः_param == 0) अणु
		ret = nsp32_selection_स्वतःpara(SCpnt);
	पूर्ण अन्यथा अणु
		ret = nsp32_selection_स्वतःscsi(SCpnt);
	पूर्ण

	अगर (ret != TRUE) अणु
		nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND, "selection fail");
		nsp32_scsi_करोne(SCpnt);
	पूर्ण

	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(nsp32_queuecommand)

/* initialize asic */
अटल पूर्णांक nsp32hw_init(nsp32_hw_data *data)
अणु
	अचिन्हित पूर्णांक   base = data->BaseAddress;
	अचिन्हित लघु irq_stat;
	अचिन्हित दीर्घ  lc_reg;
	अचिन्हित अक्षर  घातer;

	lc_reg = nsp32_index_पढ़ो4(base, CFG_LATE_CACHE);
	अगर ((lc_reg & 0xff00) == 0) अणु
		lc_reg |= (0x20 << 8);
		nsp32_index_ग_लिखो2(base, CFG_LATE_CACHE, lc_reg & 0xffff);
	पूर्ण

	nsp32_ग_लिखो2(base, IRQ_CONTROL,        IRQ_CONTROL_ALL_IRQ_MASK);
	nsp32_ग_लिखो2(base, TRANSFER_CONTROL,   0);
	nsp32_ग_लिखो4(base, BM_CNT,             0);
	nsp32_ग_लिखो2(base, SCSI_EXECUTE_PHASE, 0);

	करो अणु
		irq_stat = nsp32_पढ़ो2(base, IRQ_STATUS);
		nsp32_dbg(NSP32_DEBUG_INIT, "irq_stat 0x%x", irq_stat);
	पूर्ण जबतक (irq_stat & IRQSTATUS_ANY_IRQ);

	/*
	 * Fill FIFO_FULL_SHLD, FIFO_EMPTY_SHLD. Below parameter is
	 *  designated by specअगरication.
	 */
	अगर ((data->trans_method & NSP32_TRANSFER_PIO) ||
	    (data->trans_method & NSP32_TRANSFER_MMIO)) अणु
		nsp32_index_ग_लिखो1(base, FIFO_FULL_SHLD_COUNT,  0x40);
		nsp32_index_ग_लिखो1(base, FIFO_EMPTY_SHLD_COUNT, 0x40);
	पूर्ण अन्यथा अगर (data->trans_method & NSP32_TRANSFER_BUSMASTER) अणु
		nsp32_index_ग_लिखो1(base, FIFO_FULL_SHLD_COUNT,  0x10);
		nsp32_index_ग_लिखो1(base, FIFO_EMPTY_SHLD_COUNT, 0x60);
	पूर्ण अन्यथा अणु
		nsp32_dbg(NSP32_DEBUG_INIT, "unknown transfer mode");
	पूर्ण

	nsp32_dbg(NSP32_DEBUG_INIT, "full 0x%x emp 0x%x",
		  nsp32_index_पढ़ो1(base, FIFO_FULL_SHLD_COUNT),
		  nsp32_index_पढ़ो1(base, FIFO_EMPTY_SHLD_COUNT));

	nsp32_index_ग_लिखो1(base, CLOCK_DIV, data->घड़ी);
	nsp32_index_ग_लिखो1(base, BM_CYCLE,  MEMRD_CMD1 | SGT_AUTO_PARA_MEMED_CMD);
	nsp32_ग_लिखो1(base, PARITY_CONTROL, 0);	/* parity check is disable */

	/*
	 * initialize MISC_WRRD रेजिस्टर
	 * 
	 * Note: Designated parameters is obeyed as following:
	 *	MISC_SCSI_सूचीECTION_DETECTOR_SELECT: It must be set.
	 *	MISC_MASTER_TERMINATION_SELECT:      It must be set.
	 *	MISC_BMREQ_NEGATE_TIMING_SEL:	     It should be set.
	 *	MISC_AUTOSEL_TIMING_SEL:	     It should be set.
	 *	MISC_BMSTOP_CHANGE2_NONDATA_PHASE:   It should be set.
	 *	MISC_DELAYED_BMSTART:		     It's selected क्रम safety.
	 *
	 * Note: If MISC_BMSTOP_CHANGE2_NONDATA_PHASE is set, then
	 *	we have to set TRANSFERCONTROL_BM_START as 0 and set
	 *	appropriate value beक्रमe restarting bus master transfer.
	 */
	nsp32_index_ग_लिखो2(base, MISC_WR,
			   (SCSI_सूचीECTION_DETECTOR_SELECT |
			    DELAYED_BMSTART                |
			    MASTER_TERMINATION_SELECT      |
			    BMREQ_NEGATE_TIMING_SEL        |
			    AUTOSEL_TIMING_SEL             |
			    BMSTOP_CHANGE2_NONDATA_PHASE));

	nsp32_index_ग_लिखो1(base, TERM_PWR_CONTROL, 0);
	घातer = nsp32_index_पढ़ो1(base, TERM_PWR_CONTROL);
	अगर (!(घातer & SENSE)) अणु
		nsp32_msg(KERN_INFO, "term power on");
		nsp32_index_ग_लिखो1(base, TERM_PWR_CONTROL, BPWR);
	पूर्ण

	nsp32_ग_लिखो2(base, TIMER_SET, TIMER_STOP);
	nsp32_ग_लिखो2(base, TIMER_SET, TIMER_STOP); /* Required 2 बार */

	nsp32_ग_लिखो1(base, SYNC_REG,     0);
	nsp32_ग_लिखो1(base, ACK_WIDTH,    0);
	nsp32_ग_लिखो2(base, SEL_TIME_OUT, SEL_TIMEOUT_TIME);

	/*
	 * enable to select designated IRQ (except क्रम
	 * IRQSELECT_SERR, IRQSELECT_PERR, IRQSELECT_BMCNTERR)
	 */
	nsp32_index_ग_लिखो2(base, IRQ_SELECT, IRQSELECT_TIMER_IRQ         |
			                     IRQSELECT_SCSIRESET_IRQ     |
			                     IRQSELECT_FIFO_SHLD_IRQ     |
			                     IRQSELECT_RESELECT_IRQ      |
			                     IRQSELECT_PHASE_CHANGE_IRQ  |
			                     IRQSELECT_AUTO_SCSI_SEQ_IRQ |
			                  //   IRQSELECT_BMCNTERR_IRQ      |
			                     IRQSELECT_TARGET_ABORT_IRQ  |
			                     IRQSELECT_MASTER_ABORT_IRQ );
	nsp32_ग_लिखो2(base, IRQ_CONTROL, 0);

	/* PCI LED off */
	nsp32_index_ग_लिखो1(base, EXT_PORT_DDR, LED_OFF);
	nsp32_index_ग_लिखो1(base, EXT_PORT,     LED_OFF);

	वापस TRUE;
पूर्ण


/* पूर्णांकerrupt routine */
अटल irqवापस_t करो_nsp32_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	nsp32_hw_data *data = dev_id;
	अचिन्हित पूर्णांक base = data->BaseAddress;
	काष्ठा scsi_cmnd *SCpnt = data->CurrentSC;
	अचिन्हित लघु स्वतः_stat, irq_stat, trans_stat;
	अचिन्हित अक्षर busmon, busphase;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	पूर्णांक handled = 0;
	काष्ठा Scsi_Host *host = data->Host;

	spin_lock_irqsave(host->host_lock, flags);

	/*
	 * IRQ check, then enable IRQ mask
	 */
	irq_stat = nsp32_पढ़ो2(base, IRQ_STATUS);
	nsp32_dbg(NSP32_DEBUG_INTR, 
		  "enter IRQ: %d, IRQstatus: 0x%x", irq, irq_stat);
	/* is this पूर्णांकerrupt comes from Ninja asic? */
	अगर ((irq_stat & IRQSTATUS_ANY_IRQ) == 0) अणु
		nsp32_dbg(NSP32_DEBUG_INTR, "shared interrupt: irq other 0x%x", irq_stat);
		जाओ out2;
	पूर्ण
	handled = 1;
	nsp32_ग_लिखो2(base, IRQ_CONTROL, IRQ_CONTROL_ALL_IRQ_MASK);

	busmon = nsp32_पढ़ो1(base, SCSI_BUS_MONITOR);
	busphase = busmon & BUSMON_PHASE_MASK;

	trans_stat = nsp32_पढ़ो2(base, TRANSFER_STATUS);
	अगर ((irq_stat == 0xffff) && (trans_stat == 0xffff)) अणु
		nsp32_msg(KERN_INFO, "card disconnect");
		अगर (data->CurrentSC != शून्य) अणु
			nsp32_msg(KERN_INFO, "clean up current SCSI command");
			SCpnt->result = DID_BAD_TARGET << 16;
			nsp32_scsi_करोne(SCpnt);
		पूर्ण
		जाओ out;
	पूर्ण

	/* Timer IRQ */
	अगर (irq_stat & IRQSTATUS_TIMER_IRQ) अणु
		nsp32_dbg(NSP32_DEBUG_INTR, "timer stop");
		nsp32_ग_लिखो2(base, TIMER_SET, TIMER_STOP);
		जाओ out;
	पूर्ण

	/* SCSI reset */
	अगर (irq_stat & IRQSTATUS_SCSIRESET_IRQ) अणु
		nsp32_msg(KERN_INFO, "detected someone do bus reset");
		nsp32_करो_bus_reset(data);
		अगर (SCpnt != शून्य) अणु
			SCpnt->result = DID_RESET << 16;
			nsp32_scsi_करोne(SCpnt);
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (SCpnt == शून्य) अणु
		nsp32_msg(KERN_WARNING, "SCpnt==NULL this can't be happened");
		nsp32_msg(KERN_WARNING, "irq_stat=0x%x trans_stat=0x%x", irq_stat, trans_stat);
		जाओ out;
	पूर्ण

	/*
	 * AutoSCSI Interrupt.
	 * Note: This पूर्णांकerrupt is occurred when AutoSCSI is finished.  Then
	 * check SCSIEXECUTEPHASE, and करो appropriate action.  Each phases are
	 * recorded when AutoSCSI sequencer has been processed.
	 */
	अगर(irq_stat & IRQSTATUS_AUTOSCSI_IRQ) अणु
		/* getting SCSI executed phase */
		स्वतः_stat = nsp32_पढ़ो2(base, SCSI_EXECUTE_PHASE);
		nsp32_ग_लिखो2(base, SCSI_EXECUTE_PHASE, 0);

		/* Selection Timeout, go busमुक्त phase. */
		अगर (स्वतः_stat & SELECTION_TIMEOUT) अणु
			nsp32_dbg(NSP32_DEBUG_INTR,
				  "selection timeout occurred");

			SCpnt->result = DID_TIME_OUT << 16;
			nsp32_scsi_करोne(SCpnt);
			जाओ out;
		पूर्ण

		अगर (स्वतः_stat & MSGOUT_PHASE) अणु
			/*
			 * MsgOut phase was processed.
			 * If MSG_IN_OCCUER is not set, then MsgOut phase is
			 * completed. Thus, msgout_len must reset.  Otherwise,
			 * nothing to करो here. If MSG_OUT_OCCUER is occurred,
			 * then we will encounter the condition and check.
			 */
			अगर (!(स्वतः_stat & MSG_IN_OCCUER) &&
			     (data->msgout_len <= 3)) अणु
				/*
				 * !MSG_IN_OCCUER && msgout_len <=3
				 *   ---> AutoSCSI with MSGOUTreg is processed.
				 */
				data->msgout_len = 0;
			पूर्ण

			nsp32_dbg(NSP32_DEBUG_INTR, "MsgOut phase processed");
		पूर्ण

		अगर ((स्वतः_stat & DATA_IN_PHASE) &&
		    (scsi_get_resid(SCpnt) > 0) &&
		    ((nsp32_पढ़ो2(base, FIFO_REST_CNT) & FIFO_REST_MASK) != 0)) अणु
			prपूर्णांकk( "auto+fifo\n");
			//nsp32_pio_पढ़ो(SCpnt);
		पूर्ण

		अगर (स्वतः_stat & (DATA_IN_PHASE | DATA_OUT_PHASE)) अणु
			/* DATA_IN_PHASE/DATA_OUT_PHASE was processed. */
			nsp32_dbg(NSP32_DEBUG_INTR,
				  "Data in/out phase processed");

			/* पढ़ो BMCNT, SGT poपूर्णांकer addr */
			nsp32_dbg(NSP32_DEBUG_INTR, "BMCNT=0x%lx", 
				    nsp32_पढ़ो4(base, BM_CNT));
			nsp32_dbg(NSP32_DEBUG_INTR, "addr=0x%lx", 
				    nsp32_पढ़ो4(base, SGT_ADR));
			nsp32_dbg(NSP32_DEBUG_INTR, "SACK=0x%lx", 
				    nsp32_पढ़ो4(base, SACK_CNT));
			nsp32_dbg(NSP32_DEBUG_INTR, "SSACK=0x%lx", 
				    nsp32_पढ़ो4(base, SAVED_SACK_CNT));

			scsi_set_resid(SCpnt, 0); /* all data transferred! */
		पूर्ण

		/*
		 * MsgIn Occur
		 */
		अगर (स्वतः_stat & MSG_IN_OCCUER) अणु
			nsp32_msgin_occur(SCpnt, irq_stat, स्वतः_stat);
		पूर्ण

		/*
		 * MsgOut Occur
		 */
		अगर (स्वतः_stat & MSG_OUT_OCCUER) अणु
			nsp32_msgout_occur(SCpnt);
		पूर्ण

		/*
		 * Bus Free Occur
		 */
		अगर (स्वतः_stat & BUS_FREE_OCCUER) अणु
			ret = nsp32_busमुक्त_occur(SCpnt, स्वतः_stat);
			अगर (ret == TRUE) अणु
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (स्वतः_stat & STATUS_PHASE) अणु
			/*
			 * Read CSB and substitute CSB क्रम SCpnt->result
			 * to save status phase stutas byte.
			 * scsi error handler checks host_byte (DID_*:
			 * low level driver to indicate status), then checks 
			 * status_byte (SCSI status byte).
			 */
			SCpnt->result =	(पूर्णांक)nsp32_पढ़ो1(base, SCSI_CSB_IN);
		पूर्ण

		अगर (स्वतः_stat & ILLEGAL_PHASE) अणु
			/* Illegal phase is detected. SACK is not back. */
			nsp32_msg(KERN_WARNING, 
				  "AUTO SCSI ILLEGAL PHASE OCCUR!!!!");

			/* TODO: currently we करोn't have any action... bus reset? */

			/*
			 * To send back SACK, निश्चित, रुको, and negate.
			 */
			nsp32_sack_निश्चित(data);
			nsp32_रुको_req(data, NEGATE);
			nsp32_sack_negate(data);

		पूर्ण

		अगर (स्वतः_stat & COMMAND_PHASE) अणु
			/* nothing to करो */
			nsp32_dbg(NSP32_DEBUG_INTR, "Command phase processed");
		पूर्ण

		अगर (स्वतः_stat & AUTOSCSI_BUSY) अणु
			/* AutoSCSI is running */
		पूर्ण

		show_स्वतःphase(स्वतः_stat);
	पूर्ण

	/* FIFO_SHLD_IRQ */
	अगर (irq_stat & IRQSTATUS_FIFO_SHLD_IRQ) अणु
		nsp32_dbg(NSP32_DEBUG_INTR, "FIFO IRQ");

		चयन(busphase) अणु
		हाल BUSPHASE_DATA_OUT:
			nsp32_dbg(NSP32_DEBUG_INTR, "fifo/write");

			//nsp32_pio_ग_लिखो(SCpnt);

			अवरोध;

		हाल BUSPHASE_DATA_IN:
			nsp32_dbg(NSP32_DEBUG_INTR, "fifo/read");

			//nsp32_pio_पढ़ो(SCpnt);

			अवरोध;

		हाल BUSPHASE_STATUS:
			nsp32_dbg(NSP32_DEBUG_INTR, "fifo/status");

			SCpnt->SCp.Status = nsp32_पढ़ो1(base, SCSI_CSB_IN);

			अवरोध;
		शेष:
			nsp32_dbg(NSP32_DEBUG_INTR, "fifo/other phase");
			nsp32_dbg(NSP32_DEBUG_INTR, "irq_stat=0x%x trans_stat=0x%x", irq_stat, trans_stat);
			show_busphase(busphase);
			अवरोध;
		पूर्ण

		जाओ out;
	पूर्ण

	/* Phase Change IRQ */
	अगर (irq_stat & IRQSTATUS_PHASE_CHANGE_IRQ) अणु
		nsp32_dbg(NSP32_DEBUG_INTR, "phase change IRQ");

		चयन(busphase) अणु
		हाल BUSPHASE_MESSAGE_IN:
			nsp32_dbg(NSP32_DEBUG_INTR, "phase chg/msg in");
			nsp32_msgin_occur(SCpnt, irq_stat, 0);
			अवरोध;
		शेष:
			nsp32_msg(KERN_WARNING, "phase chg/other phase?");
			nsp32_msg(KERN_WARNING, "irq_stat=0x%x trans_stat=0x%x\n",
				  irq_stat, trans_stat);
			show_busphase(busphase);
			अवरोध;
		पूर्ण
		जाओ out;
	पूर्ण

	/* PCI_IRQ */
	अगर (irq_stat & IRQSTATUS_PCI_IRQ) अणु
		nsp32_dbg(NSP32_DEBUG_INTR, "PCI IRQ occurred");
		/* Do nothing */
	पूर्ण

	/* BMCNTERR_IRQ */
	अगर (irq_stat & IRQSTATUS_BMCNTERR_IRQ) अणु
		nsp32_msg(KERN_ERR, "Received unexpected BMCNTERR IRQ! ");
		/*
		 * TODO: To be implemented improving bus master
		 * transfer reliability when BMCNTERR is occurred in
		 * AutoSCSI phase described in specअगरication.
		 */
	पूर्ण

#अगर 0
	nsp32_dbg(NSP32_DEBUG_INTR,
		  "irq_stat=0x%x trans_stat=0x%x", irq_stat, trans_stat);
	show_busphase(busphase);
#पूर्ण_अगर

 out:
	/* disable IRQ mask */
	nsp32_ग_लिखो2(base, IRQ_CONTROL, 0);

 out2:
	spin_unlock_irqrestore(host->host_lock, flags);

	nsp32_dbg(NSP32_DEBUG_INTR, "exit");

	वापस IRQ_RETVAL(handled);
पूर्ण


अटल पूर्णांक nsp32_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	अचिन्हित दीर्घ     flags;
	nsp32_hw_data    *data;
	पूर्णांक               hostno;
	अचिन्हित पूर्णांक      base;
	अचिन्हित अक्षर     mode_reg;
	पूर्णांक               id, speed;
	दीर्घ              model;

	hostno = host->host_no;
	data = (nsp32_hw_data *)host->hostdata;
	base = host->io_port;

	seq_माला_दो(m, "NinjaSCSI-32 status\n\n");
	seq_म_लिखो(m, "Driver version:        %s, $Revision: 1.33 $\n", nsp32_release_version);
	seq_म_लिखो(m, "SCSI host No.:         %d\n",		hostno);
	seq_म_लिखो(m, "IRQ:                   %d\n",		host->irq);
	seq_म_लिखो(m, "IO:                    0x%lx-0x%lx\n", host->io_port, host->io_port + host->n_io_port - 1);
	seq_म_लिखो(m, "MMIO(virtual address): 0x%lx-0x%lx\n",	host->base, host->base + data->MmioLength - 1);
	seq_म_लिखो(m, "sg_tablesize:          %d\n",		host->sg_tablesize);
	seq_म_लिखो(m, "Chip revision:         0x%x\n",		(nsp32_पढ़ो2(base, INDEX_REG) >> 8) & 0xff);

	mode_reg = nsp32_index_पढ़ो1(base, CHIP_MODE);
	model    = data->pci_devid->driver_data;

#अगर_घोषित CONFIG_PM
	seq_म_लिखो(m, "Power Management:      %s\n",          (mode_reg & OPTF) ? "yes" : "no");
#पूर्ण_अगर
	seq_म_लिखो(m, "OEM:                   %ld, %s\n",     (mode_reg & (OEM0|OEM1)), nsp32_model[model]);

	spin_lock_irqsave(&(data->Lock), flags);
	seq_म_लिखो(m, "CurrentSC:             0x%p\n\n",      data->CurrentSC);
	spin_unlock_irqrestore(&(data->Lock), flags);


	seq_माला_दो(m, "SDTR status\n");
	क्रम (id = 0; id < ARRAY_SIZE(data->target); id++) अणु

		seq_म_लिखो(m, "id %d: ", id);

		अगर (id == host->this_id) अणु
			seq_माला_दो(m, "----- NinjaSCSI-32 host adapter\n");
			जारी;
		पूर्ण

		अगर (data->target[id].sync_flag == SDTR_DONE) अणु
			अगर (data->target[id].period == 0            &&
			    data->target[id].offset == ASYNC_OFFSET ) अणु
				seq_माला_दो(m, "async");
			पूर्ण अन्यथा अणु
				seq_माला_दो(m, " sync");
			पूर्ण
		पूर्ण अन्यथा अणु
			seq_माला_दो(m, " none");
		पूर्ण

		अगर (data->target[id].period != 0) अणु

			speed = 1000000 / (data->target[id].period * 4);

			seq_म_लिखो(m, " transfer %d.%dMB/s, offset %d",
				speed / 1000,
				speed % 1000,
				data->target[id].offset
				);
		पूर्ण
		seq_अ_दो(m, '\n');
	पूर्ण
	वापस 0;
पूर्ण



/*
 * Reset parameters and call scsi_करोne क्रम data->cur_lunt.
 * Be careful setting SCpnt->result = DID_* beक्रमe calling this function.
 */
अटल व्योम nsp32_scsi_करोne(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	अचिन्हित पूर्णांक   base = SCpnt->device->host->io_port;

	scsi_dma_unmap(SCpnt);

	/*
	 * clear TRANSFERCONTROL_BM_START
	 */
	nsp32_ग_लिखो2(base, TRANSFER_CONTROL, 0);
	nsp32_ग_लिखो4(base, BM_CNT,           0);

	/*
	 * call scsi_करोne
	 */
	(*SCpnt->scsi_करोne)(SCpnt);

	/*
	 * reset parameters
	 */
	data->cur_lunt->SCpnt = शून्य;
	data->cur_lunt        = शून्य;
	data->cur_target      = शून्य;
	data->CurrentSC      = शून्य;
पूर्ण


/*
 * Bus Free Occur
 *
 * Current Phase is BUSFREE. AutoSCSI is स्वतःmatically execute BUSFREE phase
 * with ACK reply when below condition is matched:
 *	MsgIn 00: Command Complete.
 *	MsgIn 02: Save Data Poपूर्णांकer.
 *	MsgIn 04: Disconnect.
 * In other हाल, unexpected BUSFREE is detected.
 */
अटल पूर्णांक nsp32_busमुक्त_occur(काष्ठा scsi_cmnd *SCpnt, अचिन्हित लघु execph)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	अचिन्हित पूर्णांक base   = SCpnt->device->host->io_port;

	nsp32_dbg(NSP32_DEBUG_BUSFREE, "enter execph=0x%x", execph);
	show_स्वतःphase(execph);

	nsp32_ग_लिखो4(base, BM_CNT,           0);
	nsp32_ग_लिखो2(base, TRANSFER_CONTROL, 0);

	/*
	 * MsgIn 02: Save Data Poपूर्णांकer
	 *
	 * VALID:
	 *   Save Data Poपूर्णांकer is received. Adjust poपूर्णांकer.
	 *   
	 * NO-VALID:
	 *   SCSI-3 says अगर Save Data Poपूर्णांकer is not received, then we restart
	 *   processing and we can't adjust any SCSI data poपूर्णांकer in next data
	 *   phase.
	 */
	अगर (execph & MSGIN_02_VALID) अणु
		nsp32_dbg(NSP32_DEBUG_BUSFREE, "MsgIn02_Valid");

		/*
		 * Check sack_cnt/saved_sack_cnt, then adjust sg table अगर
		 * needed.
		 */
		अगर (!(execph & MSGIN_00_VALID) && 
		    ((execph & DATA_IN_PHASE) || (execph & DATA_OUT_PHASE))) अणु
			अचिन्हित पूर्णांक sacklen, s_sacklen;

			/*
			 * Read SACK count and SAVEDSACK count, then compare.
			 */
			sacklen   = nsp32_पढ़ो4(base, SACK_CNT      );
			s_sacklen = nsp32_पढ़ो4(base, SAVED_SACK_CNT);

			/*
			 * If SAVEDSACKCNT == 0, it means SavedDataPoपूर्णांकer is
			 * come after data transferring.
			 */
			अगर (s_sacklen > 0) अणु
				/*
				 * Comparing between sack and savedsack to
				 * check the condition of AutoMsgIn03.
				 *
				 * If they are same, set msgin03 == TRUE,
				 * COMMANDCONTROL_AUTO_MSGIN_03 is enabled at
				 * reselection.  On the other hand, अगर they
				 * aren't same, set msgin03 == FALSE, and
				 * COMMANDCONTROL_AUTO_MSGIN_03 is disabled at
				 * reselection.
				 */
				अगर (sacklen != s_sacklen) अणु
					data->cur_lunt->msgin03 = FALSE;
				पूर्ण अन्यथा अणु
					data->cur_lunt->msgin03 = TRUE;
				पूर्ण

				nsp32_adjust_busमुक्त(SCpnt, s_sacklen);
			पूर्ण
		पूर्ण

		/* This value has not substitude with valid value yet... */
		//data->cur_lunt->save_datp = data->cur_datp;
	पूर्ण अन्यथा अणु
		/*
		 * no processing.
		 */
	पूर्ण
	
	अगर (execph & MSGIN_03_VALID) अणु
		/* MsgIn03 was valid to be processed. No need processing. */
	पूर्ण

	/*
	 * target SDTR check
	 */
	अगर (data->cur_target->sync_flag & SDTR_INITIATOR) अणु
		/*
		 * SDTR negotiation pulled by the initiator has not
		 * finished yet. Fall back to ASYNC mode.
		 */
		nsp32_set_async(data, data->cur_target);
		data->cur_target->sync_flag &= ~SDTR_INITIATOR;
		data->cur_target->sync_flag |= SDTR_DONE;
	पूर्ण अन्यथा अगर (data->cur_target->sync_flag & SDTR_TARGET) अणु
		/*
		 * SDTR negotiation pulled by the target has been
		 * negotiating.
		 */
		अगर (execph & (MSGIN_00_VALID | MSGIN_04_VALID)) अणु
			/* 
			 * If valid message is received, then
			 * negotiation is succeeded.
			 */
		पूर्ण अन्यथा अणु
			/*
			 * On the contrary, अगर unexpected bus मुक्त is
			 * occurred, then negotiation is failed. Fall
			 * back to ASYNC mode.
			 */
			nsp32_set_async(data, data->cur_target);
		पूर्ण
		data->cur_target->sync_flag &= ~SDTR_TARGET;
		data->cur_target->sync_flag |= SDTR_DONE;
	पूर्ण

	/*
	 * It is always ensured by SCSI standard that initiator
	 * चयनes पूर्णांकo Bus Free Phase after
	 * receiving message 00 (Command Complete), 04 (Disconnect).
	 * It's the reason that processing here is valid.
	 */
	अगर (execph & MSGIN_00_VALID) अणु
		/* MsgIn 00: Command Complete */
		nsp32_dbg(NSP32_DEBUG_BUSFREE, "command complete");

		SCpnt->SCp.Status  = nsp32_पढ़ो1(base, SCSI_CSB_IN);
		SCpnt->SCp.Message = 0;
		nsp32_dbg(NSP32_DEBUG_BUSFREE, 
			  "normal end stat=0x%x resid=0x%x\n",
			  SCpnt->SCp.Status, scsi_get_resid(SCpnt));
		SCpnt->result = (DID_OK             << 16) |
			        (SCpnt->SCp.Message <<  8) |
			        (SCpnt->SCp.Status  <<  0);
		nsp32_scsi_करोne(SCpnt);
		/* All operation is करोne */
		वापस TRUE;
	पूर्ण अन्यथा अगर (execph & MSGIN_04_VALID) अणु
		/* MsgIn 04: Disconnect */
		SCpnt->SCp.Status  = nsp32_पढ़ो1(base, SCSI_CSB_IN);
		SCpnt->SCp.Message = 4;
		
		nsp32_dbg(NSP32_DEBUG_BUSFREE, "disconnect");
		वापस TRUE;
	पूर्ण अन्यथा अणु
		/* Unexpected bus मुक्त */
		nsp32_msg(KERN_WARNING, "unexpected bus free occurred");

		/* DID_ERROR? */
		//SCpnt->result   = (DID_OK << 16) | (SCpnt->SCp.Message << 8) | (SCpnt->SCp.Status << 0);
		SCpnt->result = DID_ERROR << 16;
		nsp32_scsi_करोne(SCpnt);
		वापस TRUE;
	पूर्ण
	वापस FALSE;
पूर्ण


/*
 * nsp32_adjust_busमुक्त - adjusting SG table
 *
 * Note: This driver adjust the SG table using SCSI ACK
 *       counter instead of BMCNT counter!
 */
अटल व्योम nsp32_adjust_busमुक्त(काष्ठा scsi_cmnd *SCpnt, अचिन्हित पूर्णांक s_sacklen)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	पूर्णांक                   old_entry = data->cur_entry;
	पूर्णांक                   new_entry;
	पूर्णांक                   sg_num = data->cur_lunt->sg_num;
	nsp32_sgtable *sgt    = data->cur_lunt->sglun->sgt;
	अचिन्हित पूर्णांक          restlen, sentlen;
	u32_le                len, addr;

	nsp32_dbg(NSP32_DEBUG_SGLIST, "old resid=0x%x", scsi_get_resid(SCpnt));

	/* adjust saved SACK count with 4 byte start address boundary */
	s_sacklen -= le32_to_cpu(sgt[old_entry].addr) & 3;

	/*
	 * calculate new_entry from sack count and each sgt[].len 
	 * calculate the byte which is पूर्णांकent to send
	 */
	sentlen = 0;
	क्रम (new_entry = old_entry; new_entry < sg_num; new_entry++) अणु
		sentlen += (le32_to_cpu(sgt[new_entry].len) & ~SGTEND);
		अगर (sentlen > s_sacklen) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	/* all sgt is processed */
	अगर (new_entry == sg_num) अणु
		जाओ last;
	पूर्ण

	अगर (sentlen == s_sacklen) अणु
		/* XXX: confirm it's ok or not */
		/* In this हाल, it's ok because we are at 
		   the head element of the sg. restlen is correctly calculated. */
	पूर्ण

	/* calculate the rest length क्रम transferring */
	restlen = sentlen - s_sacklen;

	/* update adjusting current SG table entry */
	len  = le32_to_cpu(sgt[new_entry].len);
	addr = le32_to_cpu(sgt[new_entry].addr);
	addr += (len - restlen);
	sgt[new_entry].addr = cpu_to_le32(addr);
	sgt[new_entry].len  = cpu_to_le32(restlen);

	/* set cur_entry with new_entry */
	data->cur_entry = new_entry;
 
	वापस;

 last:
	अगर (scsi_get_resid(SCpnt) < sentlen) अणु
		nsp32_msg(KERN_ERR, "resid underflow");
	पूर्ण

	scsi_set_resid(SCpnt, scsi_get_resid(SCpnt) - sentlen);
	nsp32_dbg(NSP32_DEBUG_SGLIST, "new resid=0x%x", scsi_get_resid(SCpnt));

	/* update hostdata and lun */

	वापस;
पूर्ण


/*
 * It's called MsgOut phase occur.
 * NinjaSCSI-32Bi/UDE स्वतःmatically processes up to 3 messages in
 * message out phase. It, however, has more than 3 messages,
 * HBA creates the पूर्णांकerrupt and we have to process by hand.
 */
अटल व्योम nsp32_msgout_occur(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	अचिन्हित पूर्णांक base   = SCpnt->device->host->io_port;
	पूर्णांक i;
	
	nsp32_dbg(NSP32_DEBUG_MSGOUTOCCUR,
		  "enter: msgout_len: 0x%x", data->msgout_len);

	/*
	 * If MsgOut phase is occurred without having any
	 * message, then No_Operation is sent (SCSI-2).
	 */
	अगर (data->msgout_len == 0) अणु
		nsp32_build_nop(SCpnt);
	पूर्ण

	/*
	 * send messages
	 */
	क्रम (i = 0; i < data->msgout_len; i++) अणु
		nsp32_dbg(NSP32_DEBUG_MSGOUTOCCUR,
			  "%d : 0x%x", i, data->msgoutbuf[i]);

		/*
		 * Check REQ is निश्चितed.
		 */
		nsp32_रुको_req(data, ASSERT);

		अगर (i == (data->msgout_len - 1)) अणु
			/*
			 * If the last message, set the AutoSCSI restart
			 * beक्रमe send back the ack message. AutoSCSI
			 * restart स्वतःmatically negate ATN संकेत.
			 */
			//command = (AUTO_MSGIN_00_OR_04 | AUTO_MSGIN_02);
			//nsp32_restart_स्वतःscsi(SCpnt, command);
			nsp32_ग_लिखो2(base, COMMAND_CONTROL,
					 (CLEAR_CDB_FIFO_POINTER |
					  AUTO_COMMAND_PHASE     |
					  AUTOSCSI_RESTART       |
					  AUTO_MSGIN_00_OR_04    |
					  AUTO_MSGIN_02          ));
		पूर्ण
		/*
		 * Write data with SACK, then रुको sack is
		 * स्वतःmatically negated.
		 */
		nsp32_ग_लिखो1(base, SCSI_DATA_WITH_ACK, data->msgoutbuf[i]);
		nsp32_रुको_sack(data, NEGATE);

		nsp32_dbg(NSP32_DEBUG_MSGOUTOCCUR, "bus: 0x%x\n",
			  nsp32_पढ़ो1(base, SCSI_BUS_MONITOR));
	पूर्ण

	data->msgout_len = 0;

	nsp32_dbg(NSP32_DEBUG_MSGOUTOCCUR, "exit");
पूर्ण

/*
 * Restart AutoSCSI
 *
 * Note: Restarting AutoSCSI needs set:
 *		SYNC_REG, ACK_WIDTH, SGT_ADR, TRANSFER_CONTROL
 */
अटल व्योम nsp32_restart_स्वतःscsi(काष्ठा scsi_cmnd *SCpnt, अचिन्हित लघु command)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	अचिन्हित पूर्णांक   base = data->BaseAddress;
	अचिन्हित लघु transfer = 0;

	nsp32_dbg(NSP32_DEBUG_RESTART, "enter");

	अगर (data->cur_target == शून्य || data->cur_lunt == शून्य) अणु
		nsp32_msg(KERN_ERR, "Target or Lun is invalid");
	पूर्ण

	/*
	 * set SYNC_REG
	 * Don't set BM_START_ADR beक्रमe setting this रेजिस्टर.
	 */
	nsp32_ग_लिखो1(base, SYNC_REG, data->cur_target->syncreg);

	/*
	 * set ACKWIDTH
	 */
	nsp32_ग_लिखो1(base, ACK_WIDTH, data->cur_target->ackwidth);

	/*
	 * set SREQ hazard समाप्तer sampling rate
	 */
	nsp32_ग_लिखो1(base, SREQ_SMPL_RATE, data->cur_target->sample_reg);

	/*
	 * set SGT ADDR (physical address)
	 */
	nsp32_ग_लिखो4(base, SGT_ADR, data->cur_lunt->sglun_paddr);

	/*
	 * set TRANSFER CONTROL REG
	 */
	transfer = 0;
	transfer |= (TRANSFER_GO | ALL_COUNTER_CLR);
	अगर (data->trans_method & NSP32_TRANSFER_BUSMASTER) अणु
		अगर (scsi_bufflen(SCpnt) > 0) अणु
			transfer |= BM_START;
		पूर्ण
	पूर्ण अन्यथा अगर (data->trans_method & NSP32_TRANSFER_MMIO) अणु
		transfer |= CB_MMIO_MODE;
	पूर्ण अन्यथा अगर (data->trans_method & NSP32_TRANSFER_PIO) अणु
		transfer |= CB_IO_MODE;
	पूर्ण
	nsp32_ग_लिखो2(base, TRANSFER_CONTROL, transfer);

	/*
	 * restart AutoSCSI
	 *
	 * TODO: COMMANDCONTROL_AUTO_COMMAND_PHASE is needed ?
	 */
	command |= (CLEAR_CDB_FIFO_POINTER |
		    AUTO_COMMAND_PHASE     |
		    AUTOSCSI_RESTART       );
	nsp32_ग_लिखो2(base, COMMAND_CONTROL, command);

	nsp32_dbg(NSP32_DEBUG_RESTART, "exit");
पूर्ण


/*
 * cannot run स्वतःmatically message in occur
 */
अटल व्योम nsp32_msgin_occur(काष्ठा scsi_cmnd     *SCpnt,
			      अचिन्हित दीर्घ  irq_status,
			      अचिन्हित लघु execph)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	अचिन्हित पूर्णांक   base = SCpnt->device->host->io_port;
	अचिन्हित अक्षर  msg;
	अचिन्हित अक्षर  msgtype;
	अचिन्हित अक्षर  newlun;
	अचिन्हित लघु command  = 0;
	पूर्णांक            msgclear = TRUE;
	दीर्घ           new_sgtp;
	पूर्णांक            ret;

	/*
	 * पढ़ो first message
	 *    Use SCSIDATA_W_ACK instead of SCSIDATAIN, because the procedure
	 *    of Message-In have to be processed beक्रमe sending back SCSI ACK.
	 */
	msg = nsp32_पढ़ो1(base, SCSI_DATA_IN);
	data->msginbuf[(अचिन्हित अक्षर)data->msgin_len] = msg;
	msgtype = data->msginbuf[0];
	nsp32_dbg(NSP32_DEBUG_MSGINOCCUR,
		  "enter: msglen: 0x%x msgin: 0x%x msgtype: 0x%x",
		  data->msgin_len, msg, msgtype);

	/*
	 * TODO: We need checking whether bus phase is message in?
	 */

	/*
	 * निश्चित SCSI ACK
	 */
	nsp32_sack_निश्चित(data);

	/*
	 * processing IDENTIFY
	 */
	अगर (msgtype & 0x80) अणु
		अगर (!(irq_status & IRQSTATUS_RESELECT_OCCUER)) अणु
			/* Invalid (non reselect) phase */
			जाओ reject;
		पूर्ण

		newlun = msgtype & 0x1f; /* TODO: SPI-3 compliant? */
		ret = nsp32_reselection(SCpnt, newlun);
		अगर (ret == TRUE) अणु
			जाओ restart;
		पूर्ण अन्यथा अणु
			जाओ reject;
		पूर्ण
	पूर्ण
	
	/*
	 * processing messages except क्रम IDENTIFY
	 *
	 * TODO: Messages are all SCSI-2 terminology. SCSI-3 compliance is TODO.
	 */
	चयन (msgtype) अणु
	/*
	 * 1-byte message
	 */
	हाल COMMAND_COMPLETE:
	हाल DISCONNECT:
		/*
		 * These messages should not be occurred.
		 * They should be processed on AutoSCSI sequencer.
		 */
		nsp32_msg(KERN_WARNING, 
			   "unexpected message of AutoSCSI MsgIn: 0x%x", msg);
		अवरोध;
		
	हाल RESTORE_POINTERS:
		/*
		 * AutoMsgIn03 is disabled, and HBA माला_लो this message.
		 */

		अगर ((execph & DATA_IN_PHASE) || (execph & DATA_OUT_PHASE)) अणु
			अचिन्हित पूर्णांक s_sacklen;

			s_sacklen = nsp32_पढ़ो4(base, SAVED_SACK_CNT);
			अगर ((execph & MSGIN_02_VALID) && (s_sacklen > 0)) अणु
				nsp32_adjust_busमुक्त(SCpnt, s_sacklen);
			पूर्ण अन्यथा अणु
				/* No need to reग_लिखो SGT */
			पूर्ण
		पूर्ण
		data->cur_lunt->msgin03 = FALSE;

		/* Update with the new value */

		/* reset SACK/SavedACK counter (or ALL clear?) */
		nsp32_ग_लिखो4(base, CLR_COUNTER, CLRCOUNTER_ALLMASK);

		/*
		 * set new sg poपूर्णांकer
		 */
		new_sgtp = data->cur_lunt->sglun_paddr + 
			(data->cur_lunt->cur_entry * माप(nsp32_sgtable));
		nsp32_ग_लिखो4(base, SGT_ADR, new_sgtp);

		अवरोध;

	हाल SAVE_POINTERS:
		/*
		 * These messages should not be occurred.
		 * They should be processed on AutoSCSI sequencer.
		 */
		nsp32_msg (KERN_WARNING, 
			   "unexpected message of AutoSCSI MsgIn: SAVE_POINTERS");
		
		अवरोध;
		
	हाल MESSAGE_REJECT:
		/* If previous message_out is sending SDTR, and get 
		   message_reject from target, SDTR negotiation is failed */
		अगर (data->cur_target->sync_flag &
				(SDTR_INITIATOR | SDTR_TARGET)) अणु
			/*
			 * Current target is negotiating SDTR, but it's
			 * failed.  Fall back to async transfer mode, and set
			 * SDTR_DONE.
			 */
			nsp32_set_async(data, data->cur_target);
			data->cur_target->sync_flag &= ~SDTR_INITIATOR;
			data->cur_target->sync_flag |= SDTR_DONE;

		पूर्ण
		अवरोध;

	हाल LINKED_CMD_COMPLETE:
	हाल LINKED_FLG_CMD_COMPLETE:
		/* queue tag is not supported currently */
		nsp32_msg (KERN_WARNING, 
			   "unsupported message: 0x%x", msgtype);
		अवरोध;

	हाल INITIATE_RECOVERY:
		/* staring ECA (Extended Contingent Allegiance) state. */
		/* This message is declined in SPI2 or later. */

		जाओ reject;

	/*
	 * 2-byte message
	 */
	हाल SIMPLE_QUEUE_TAG:
	हाल 0x23:
		/*
		 * 0x23: Ignore_Wide_Residue is not declared in scsi.h.
		 * No support is needed.
		 */
		अगर (data->msgin_len >= 1) अणु
			जाओ reject;
		पूर्ण

		/* current position is 1-byte of 2 byte */
		msgclear = FALSE;

		अवरोध;

	/*
	 * extended message
	 */
	हाल EXTENDED_MESSAGE:
		अगर (data->msgin_len < 1) अणु
			/*
			 * Current position करोes not reach 2-byte
			 * (2-byte is extended message length).
			 */
			msgclear = FALSE;
			अवरोध;
		पूर्ण

		अगर ((data->msginbuf[1] + 1) > data->msgin_len) अणु
			/*
			 * Current extended message has msginbuf[1] + 2
			 * (msgin_len starts counting from 0, so buf[1] + 1).
			 * If current message position is not finished,
			 * जारी receiving message.
			 */
			msgclear = FALSE;
			अवरोध;
		पूर्ण

		/*
		 * Reach here means regular length of each type of 
		 * extended messages.
		 */
		चयन (data->msginbuf[2]) अणु
		हाल EXTENDED_MODIFY_DATA_POINTER:
			/* TODO */
			जाओ reject; /* not implemented yet */
			अवरोध;

		हाल EXTENDED_SDTR:
			/*
			 * Exchange this message between initiator and target.
			 */
			अगर (data->msgin_len != EXTENDED_SDTR_LEN + 1) अणु
				/*
				 * received inappropriate message.
				 */
				जाओ reject;
				अवरोध;
			पूर्ण

			nsp32_analyze_sdtr(SCpnt);

			अवरोध;

		हाल EXTENDED_EXTENDED_IDENTIFY:
			/* SCSI-I only, not supported. */
			जाओ reject; /* not implemented yet */

			अवरोध;

		हाल EXTENDED_WDTR:
			जाओ reject; /* not implemented yet */

			अवरोध;
			
		शेष:
			जाओ reject;
		पूर्ण
		अवरोध;
		
	शेष:
		जाओ reject;
	पूर्ण

 restart:
	अगर (msgclear == TRUE) अणु
		data->msgin_len = 0;

		/*
		 * If restarting AutoSCSI, but there are some message to out
		 * (msgout_len > 0), set AutoATN, and set SCSIMSGOUT as 0
		 * (MV_VALID = 0). When commandcontrol is written with
		 * AutoSCSI restart, at the same समय MsgOutOccur should be
		 * happened (however, such situation is really possible...?).
		 */
		अगर (data->msgout_len > 0) अणु	
			nsp32_ग_लिखो4(base, SCSI_MSG_OUT, 0);
			command |= AUTO_ATN;
		पूर्ण

		/*
		 * restart AutoSCSI
		 * If it's failed, COMMANDCONTROL_AUTO_COMMAND_PHASE is needed.
		 */
		command |= (AUTO_MSGIN_00_OR_04 | AUTO_MSGIN_02);

		/*
		 * If current msgin03 is TRUE, then flag on.
		 */
		अगर (data->cur_lunt->msgin03 == TRUE) अणु
			command |= AUTO_MSGIN_03;
		पूर्ण
		data->cur_lunt->msgin03 = FALSE;
	पूर्ण अन्यथा अणु
		data->msgin_len++;
	पूर्ण

	/*
	 * restart AutoSCSI
	 */
	nsp32_restart_स्वतःscsi(SCpnt, command);

	/*
	 * रुको SCSI REQ negate क्रम REQ-ACK handshake
	 */
	nsp32_रुको_req(data, NEGATE);

	/*
	 * negate SCSI ACK
	 */
	nsp32_sack_negate(data);

	nsp32_dbg(NSP32_DEBUG_MSGINOCCUR, "exit");

	वापस;

 reject:
	nsp32_msg(KERN_WARNING, 
		  "invalid or unsupported MessageIn, rejected. "
		  "current msg: 0x%x (len: 0x%x), processing msg: 0x%x",
		  msg, data->msgin_len, msgtype);
	nsp32_build_reject(SCpnt);
	data->msgin_len = 0;

	जाओ restart;
पूर्ण

/*
 * 
 */
अटल व्योम nsp32_analyze_sdtr(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp32_hw_data   *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	nsp32_target     *target     = data->cur_target;
	अचिन्हित अक्षर     get_period = data->msginbuf[3];
	अचिन्हित अक्षर     get_offset = data->msginbuf[4];
	पूर्णांक               entry;

	nsp32_dbg(NSP32_DEBUG_MSGINOCCUR, "enter");

	/*
	 * If this inititor sent the SDTR message, then target responds SDTR,
	 * initiator SYNCREG, ACKWIDTH from SDTR parameter.
	 * Messages are not appropriate, then send back reject message.
	 * If initiator did not send the SDTR, but target sends SDTR, 
	 * initiator calculator the appropriate parameter and send back SDTR.
	 */	
	अगर (target->sync_flag & SDTR_INITIATOR) अणु
		/*
		 * Initiator sent SDTR, the target responds and
		 * send back negotiation SDTR.
		 */
		nsp32_dbg(NSP32_DEBUG_MSGINOCCUR, "target responds SDTR");
	
		target->sync_flag &= ~SDTR_INITIATOR;
		target->sync_flag |= SDTR_DONE;

		/*
		 * offset:
		 */
		अगर (get_offset > SYNC_OFFSET) अणु
			/*
			 * Negotiation is failed, the target send back
			 * unexpected offset value.
			 */
			जाओ reject;
		पूर्ण
		
		अगर (get_offset == ASYNC_OFFSET) अणु
			/*
			 * Negotiation is succeeded, the target want
			 * to fall back पूर्णांकo asynchronous transfer mode.
			 */
			जाओ async;
		पूर्ण

		/*
		 * period:
		 *    Check whether sync period is too लघु. If too लघु,
		 *    fall back to async mode. If it's ok, then investigate
		 *    the received sync period. If sync period is acceptable
		 *    between sync table start_period and end_period, then
		 *    set this I_T nexus as sent offset and period.
		 *    If it's not acceptable, send back reject and fall back
		 *    to async mode.
		 */
		अगर (get_period < data->synct[0].period_num) अणु
			/*
			 * Negotiation is failed, the target send back
			 * unexpected period value.
			 */
			जाओ reject;
		पूर्ण

		entry = nsp32_search_period_entry(data, target, get_period);

		अगर (entry < 0) अणु
			/*
			 * Target want to use दीर्घ period which is not 
			 * acceptable NinjaSCSI-32Bi/UDE.
			 */
			जाओ reject;
		पूर्ण

		/*
		 * Set new sync table and offset in this I_T nexus.
		 */
		nsp32_set_sync_entry(data, target, entry, get_offset);
	पूर्ण अन्यथा अणु
		/* Target send SDTR to initiator. */
		nsp32_dbg(NSP32_DEBUG_MSGINOCCUR, "target send SDTR");
	
		target->sync_flag |= SDTR_INITIATOR;

		/* offset: */
		अगर (get_offset > SYNC_OFFSET) अणु
			/* send back as SYNC_OFFSET */
			get_offset = SYNC_OFFSET;
		पूर्ण

		/* period: */
		अगर (get_period < data->synct[0].period_num) अणु
			get_period = data->synct[0].period_num;
		पूर्ण

		entry = nsp32_search_period_entry(data, target, get_period);

		अगर (get_offset == ASYNC_OFFSET || entry < 0) अणु
			nsp32_set_async(data, target);
			nsp32_build_sdtr(SCpnt, 0, ASYNC_OFFSET);
		पूर्ण अन्यथा अणु
			nsp32_set_sync_entry(data, target, entry, get_offset);
			nsp32_build_sdtr(SCpnt, get_period, get_offset);
		पूर्ण
	पूर्ण

	target->period = get_period;
	nsp32_dbg(NSP32_DEBUG_MSGINOCCUR, "exit");
	वापस;

 reject:
	/*
	 * If the current message is unacceptable, send back to the target
	 * with reject message.
	 */
	nsp32_build_reject(SCpnt);

 async:
	nsp32_set_async(data, target);	/* set as ASYNC transfer mode */

	target->period = 0;
	nsp32_dbg(NSP32_DEBUG_MSGINOCCUR, "exit: set async");
	वापस;
पूर्ण


/*
 * Search config entry number matched in sync_table from given
 * target and speed period value. If failed to search, वापस negative value.
 */
अटल पूर्णांक nsp32_search_period_entry(nsp32_hw_data *data,
				     nsp32_target  *target,
				     अचिन्हित अक्षर  period)
अणु
	पूर्णांक i;

	अगर (target->limit_entry >= data->syncnum) अणु
		nsp32_msg(KERN_ERR, "limit_entry exceeds syncnum!");
		target->limit_entry = 0;
	पूर्ण

	क्रम (i = target->limit_entry; i < data->syncnum; i++) अणु
		अगर (period >= data->synct[i].start_period &&
		    period <= data->synct[i].end_period) अणु
				अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Check given period value is over the sync_table value.
	 * If so, वापस max value.
	 */
	अगर (i == data->syncnum) अणु
		i = -1;
	पूर्ण

	वापस i;
पूर्ण


/*
 * target <-> initiator use ASYNC transfer
 */
अटल व्योम nsp32_set_async(nsp32_hw_data *data, nsp32_target *target)
अणु
	अचिन्हित अक्षर period = data->synct[target->limit_entry].period_num;

	target->offset     = ASYNC_OFFSET;
	target->period     = 0;
	target->syncreg    = TO_SYNCREG(period, ASYNC_OFFSET);
	target->ackwidth   = 0;
	target->sample_reg = 0;

	nsp32_dbg(NSP32_DEBUG_SYNC, "set async");
पूर्ण


/*
 * target <-> initiator use maximum SYNC transfer
 */
अटल व्योम nsp32_set_max_sync(nsp32_hw_data *data,
			       nsp32_target  *target,
			       अचिन्हित अक्षर *period,
			       अचिन्हित अक्षर *offset)
अणु
	अचिन्हित अक्षर period_num, ackwidth;

	period_num = data->synct[target->limit_entry].period_num;
	*period    = data->synct[target->limit_entry].start_period;
	ackwidth   = data->synct[target->limit_entry].ackwidth;
	*offset    = SYNC_OFFSET;

	target->syncreg    = TO_SYNCREG(period_num, *offset);
	target->ackwidth   = ackwidth;
	target->offset     = *offset;
	target->sample_reg = 0;       /* disable SREQ sampling */
पूर्ण


/*
 * target <-> initiator use entry number speed
 */
अटल व्योम nsp32_set_sync_entry(nsp32_hw_data *data,
				 nsp32_target  *target,
				 पूर्णांक            entry,
				 अचिन्हित अक्षर  offset)
अणु
	अचिन्हित अक्षर period, ackwidth, sample_rate;

	period      = data->synct[entry].period_num;
	ackwidth    = data->synct[entry].ackwidth;
	sample_rate = data->synct[entry].sample_rate;

	target->syncreg    = TO_SYNCREG(period, offset);
	target->ackwidth   = ackwidth;
	target->offset     = offset;
	target->sample_reg = sample_rate | SAMPLING_ENABLE;

	nsp32_dbg(NSP32_DEBUG_SYNC, "set sync");
पूर्ण


/*
 * It रुकोs until SCSI REQ becomes निश्चितion or negation state.
 *
 * Note: If nsp32_msgin_occur is called, we निश्चितs SCSI ACK. Then
 *     connected target responds SCSI REQ negation.  We have to रुको
 *     SCSI REQ becomes negation in order to negate SCSI ACK संकेत क्रम
 *     REQ-ACK handshake.
 */
अटल व्योम nsp32_रुको_req(nsp32_hw_data *data, पूर्णांक state)
अणु
	अचिन्हित पूर्णांक  base      = data->BaseAddress;
	पूर्णांक           रुको_समय = 0;
	अचिन्हित अक्षर bus, req_bit;

	अगर (!((state == ASSERT) || (state == NEGATE))) अणु
		nsp32_msg(KERN_ERR, "unknown state designation");
	पूर्ण
	/* REQ is BIT(5) */
	req_bit = (state == ASSERT ? BUSMON_REQ : 0);

	करो अणु
		bus = nsp32_पढ़ो1(base, SCSI_BUS_MONITOR);
		अगर ((bus & BUSMON_REQ) == req_bit) अणु
			nsp32_dbg(NSP32_DEBUG_WAIT, 
				  "wait_time: %d", रुको_समय);
			वापस;
		पूर्ण
		udelay(1);
		रुको_समय++;
	पूर्ण जबतक (रुको_समय < REQSACK_TIMEOUT_TIME);

	nsp32_msg(KERN_WARNING, "wait REQ timeout, req_bit: 0x%x", req_bit);
पूर्ण

/*
 * It रुकोs until SCSI SACK becomes निश्चितion or negation state.
 */
अटल व्योम nsp32_रुको_sack(nsp32_hw_data *data, पूर्णांक state)
अणु
	अचिन्हित पूर्णांक  base      = data->BaseAddress;
	पूर्णांक           रुको_समय = 0;
	अचिन्हित अक्षर bus, ack_bit;

	अगर (!((state == ASSERT) || (state == NEGATE))) अणु
		nsp32_msg(KERN_ERR, "unknown state designation");
	पूर्ण
	/* ACK is BIT(4) */
	ack_bit = (state == ASSERT ? BUSMON_ACK : 0);

	करो अणु
		bus = nsp32_पढ़ो1(base, SCSI_BUS_MONITOR);
		अगर ((bus & BUSMON_ACK) == ack_bit) अणु
			nsp32_dbg(NSP32_DEBUG_WAIT,
				  "wait_time: %d", रुको_समय);
			वापस;
		पूर्ण
		udelay(1);
		रुको_समय++;
	पूर्ण जबतक (रुको_समय < REQSACK_TIMEOUT_TIME);

	nsp32_msg(KERN_WARNING, "wait SACK timeout, ack_bit: 0x%x", ack_bit);
पूर्ण

/*
 * निश्चित SCSI ACK
 *
 * Note: SCSI ACK निश्चितion needs with ACKENB=1, AUTOसूचीECTION=1.
 */
अटल व्योम nsp32_sack_निश्चित(nsp32_hw_data *data)
अणु
	अचिन्हित पूर्णांक  base = data->BaseAddress;
	अचिन्हित अक्षर busctrl;

	busctrl  = nsp32_पढ़ो1(base, SCSI_BUS_CONTROL);
	busctrl	|= (BUSCTL_ACK | AUTOसूचीECTION | ACKENB);
	nsp32_ग_लिखो1(base, SCSI_BUS_CONTROL, busctrl);
पूर्ण

/*
 * negate SCSI ACK
 */
अटल व्योम nsp32_sack_negate(nsp32_hw_data *data)
अणु
	अचिन्हित पूर्णांक  base = data->BaseAddress;
	अचिन्हित अक्षर busctrl;

	busctrl  = nsp32_पढ़ो1(base, SCSI_BUS_CONTROL);
	busctrl	&= ~BUSCTL_ACK;
	nsp32_ग_लिखो1(base, SCSI_BUS_CONTROL, busctrl);
पूर्ण



/*
 * Note: n_io_port is defined as 0x7f because I/O रेजिस्टर port is
 *	 asचिन्हित as:
 *	0x800-0x8ff: memory mapped I/O port
 *	0x900-0xbff: (map same 0x800-0x8ff I/O port image repeatedly)
 *	0xc00-0xfff: CardBus status रेजिस्टरs
 */
अटल पूर्णांक nsp32_detect(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host;	/* रेजिस्टरed host काष्ठाure */
	काष्ठा resource  *res;
	nsp32_hw_data    *data;
	पूर्णांक               ret;
	पूर्णांक               i, j;

	nsp32_dbg(NSP32_DEBUG_REGISTER, "enter");

	/*
	 * रेजिस्टर this HBA as SCSI device
	 */
	host = scsi_host_alloc(&nsp32_ढाँचा, माप(nsp32_hw_data));
	अगर (host == शून्य) अणु
		nsp32_msg (KERN_ERR, "failed to scsi register");
		जाओ err;
	पूर्ण

	/*
	 * set nsp32_hw_data
	 */
	data = (nsp32_hw_data *)host->hostdata;

	स_नकल(data, &nsp32_data_base, माप(nsp32_hw_data));

	host->irq       = data->IrqNumber;
	host->io_port   = data->BaseAddress;
	host->unique_id = data->BaseAddress;
	host->n_io_port	= data->NumAddress;
	host->base      = (अचिन्हित दीर्घ)data->MmioAddress;

	data->Host      = host;
	spin_lock_init(&(data->Lock));

	data->cur_lunt   = शून्य;
	data->cur_target = शून्य;

	/*
	 * Bus master transfer mode is supported currently.
	 */
	data->trans_method = NSP32_TRANSFER_BUSMASTER;

	/*
	 * Set घड़ी भाग, CLOCK_4 (HBA has own बाह्यal घड़ी, and
	 * भागiding * 100ns/4).
	 * Currently CLOCK_4 has only tested, not क्रम CLOCK_2/PCICLK yet.
	 */
	data->घड़ी = CLOCK_4;

	/*
	 * Select appropriate nsp32_sync_table and set I_CLOCKDIV.
	 */
	चयन (data->घड़ी) अणु
	हाल CLOCK_4:
		/* If data->घड़ी is CLOCK_4, then select 40M sync table. */
		data->synct   = nsp32_sync_table_40M;
		data->syncnum = ARRAY_SIZE(nsp32_sync_table_40M);
		अवरोध;
	हाल CLOCK_2:
		/* If data->घड़ी is CLOCK_2, then select 20M sync table. */
		data->synct   = nsp32_sync_table_20M;
		data->syncnum = ARRAY_SIZE(nsp32_sync_table_20M);
		अवरोध;
	हाल PCICLK:
		/* If data->घड़ी is PCICLK, then select pci sync table. */
		data->synct   = nsp32_sync_table_pci;
		data->syncnum = ARRAY_SIZE(nsp32_sync_table_pci);
		अवरोध;
	शेष:
		nsp32_msg(KERN_WARNING,
			  "Invalid clock div is selected, set CLOCK_4.");
		/* Use शेष value CLOCK_4 */
		data->घड़ी   = CLOCK_4;
		data->synct   = nsp32_sync_table_40M;
		data->syncnum = ARRAY_SIZE(nsp32_sync_table_40M);
	पूर्ण

	/*
	 * setup nsp32_lunt
	 */

	/*
	 * setup DMA 
	 */
	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32)) != 0) अणु
		nsp32_msg (KERN_ERR, "failed to set PCI DMA mask");
		जाओ scsi_unरेजिस्टर;
	पूर्ण

	/*
	 * allocate स्वतःparam DMA resource.
	 */
	data->स्वतःparam = dma_alloc_coherent(&pdev->dev,
			माप(nsp32_स्वतःparam), &(data->स्वतः_paddr),
			GFP_KERNEL);
	अगर (data->स्वतःparam == शून्य) अणु
		nsp32_msg(KERN_ERR, "failed to allocate DMA memory");
		जाओ scsi_unरेजिस्टर;
	पूर्ण

	/*
	 * allocate scatter-gather DMA resource.
	 */
	data->sg_list = dma_alloc_coherent(&pdev->dev, NSP32_SG_TABLE_SIZE,
			&data->sg_paddr, GFP_KERNEL);
	अगर (data->sg_list == शून्य) अणु
		nsp32_msg(KERN_ERR, "failed to allocate DMA memory");
		जाओ मुक्त_स्वतःparam;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data->lunt); i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(data->lunt[0]); j++) अणु
			पूर्णांक offset = i * ARRAY_SIZE(data->lunt[0]) + j;
			nsp32_lunt पंचांगp = अणु
				.SCpnt       = शून्य,
				.save_datp   = 0,
				.msgin03     = FALSE,
				.sg_num      = 0,
				.cur_entry   = 0,
				.sglun       = &(data->sg_list[offset]),
				.sglun_paddr = data->sg_paddr + (offset * माप(nsp32_sglun)),
			पूर्ण;

			data->lunt[i][j] = पंचांगp;
		पूर्ण
	पूर्ण

	/*
	 * setup target
	 */
	क्रम (i = 0; i < ARRAY_SIZE(data->target); i++) अणु
		nsp32_target *target = &(data->target[i]);

		target->limit_entry  = 0;
		target->sync_flag    = 0;
		nsp32_set_async(data, target);
	पूर्ण

	/*
	 * EEPROM check
	 */
	ret = nsp32_getprom_param(data);
	अगर (ret == FALSE) अणु
		data->reसमय_रखो = 3;	/* शेष 3 */
	पूर्ण

	/*
	 * setup HBA
	 */
	nsp32hw_init(data);

	snम_लिखो(data->info_str, माप(data->info_str),
		 "NinjaSCSI-32Bi/UDE: irq %d, io 0x%lx+0x%x",
		 host->irq, host->io_port, host->n_io_port);

	/*
	 * SCSI bus reset
	 *
	 * Note: It's important to reset SCSI bus in initialization phase.
	 *     NinjaSCSI-32Bi/UDE HBA EEPROM seems to exchange SDTR when
	 *     प्रणाली is coming up, so SCSI devices connected to HBA is set as
	 *     un-asynchronous mode.  It brings the merit that this HBA is
	 *     पढ़ोy to start synchronous transfer without any preparation,
	 *     but we are dअगरficult to control transfer speed.  In addition,
	 *     it prevents device transfer speed from effecting EEPROM start-up
	 *     SDTR.  NinjaSCSI-32Bi/UDE has the feature अगर EEPROM is set as
	 *     Auto Mode, then FAST-10M is selected when SCSI devices are
	 *     connected same or more than 4 devices.  It should be aव्योमed
	 *     depending on this specअगरication. Thus, resetting the SCSI bus
	 *     restores all connected SCSI devices to asynchronous mode, then
	 *     this driver set SDTR safely later, and we can control all SCSI
	 *     device transfer mode.
	 */
	nsp32_करो_bus_reset(data);

	ret = request_irq(host->irq, करो_nsp32_isr, IRQF_SHARED, "nsp32", data);
	अगर (ret < 0) अणु
		nsp32_msg(KERN_ERR, "Unable to allocate IRQ for NinjaSCSI32 "
			  "SCSI PCI controller. Interrupt: %d", host->irq);
		जाओ मुक्त_sg_list;
	पूर्ण

        /*
         * PCI IO रेजिस्टर
         */
	res = request_region(host->io_port, host->n_io_port, "nsp32");
	अगर (res == शून्य) अणु
		nsp32_msg(KERN_ERR, 
			  "I/O region 0x%x+0x%x is already used",
			  data->BaseAddress, data->NumAddress);
		जाओ मुक्त_irq;
        पूर्ण

	ret = scsi_add_host(host, &pdev->dev);
	अगर (ret) अणु
		nsp32_msg(KERN_ERR, "failed to add scsi host");
		जाओ मुक्त_region;
	पूर्ण
	scsi_scan_host(host);
	pci_set_drvdata(pdev, host);
	वापस 0;

 मुक्त_region:
	release_region(host->io_port, host->n_io_port);

 मुक्त_irq:
	मुक्त_irq(host->irq, data);

 मुक्त_sg_list:
	dma_मुक्त_coherent(&pdev->dev, NSP32_SG_TABLE_SIZE,
			    data->sg_list, data->sg_paddr);

 मुक्त_स्वतःparam:
	dma_मुक्त_coherent(&pdev->dev, माप(nsp32_स्वतःparam),
			    data->स्वतःparam, data->स्वतः_paddr);
	
 scsi_unरेजिस्टर:
	scsi_host_put(host);

 err:
	वापस 1;
पूर्ण

अटल पूर्णांक nsp32_release(काष्ठा Scsi_Host *host)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)host->hostdata;

	अगर (data->स्वतःparam) अणु
		dma_मुक्त_coherent(&data->Pci->dev, माप(nsp32_स्वतःparam),
				    data->स्वतःparam, data->स्वतः_paddr);
	पूर्ण

	अगर (data->sg_list) अणु
		dma_मुक्त_coherent(&data->Pci->dev, NSP32_SG_TABLE_SIZE,
				    data->sg_list, data->sg_paddr);
	पूर्ण

	अगर (host->irq) अणु
		मुक्त_irq(host->irq, data);
	पूर्ण

	अगर (host->io_port && host->n_io_port) अणु
		release_region(host->io_port, host->n_io_port);
	पूर्ण

	अगर (data->MmioAddress) अणु
		iounmap(data->MmioAddress);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *nsp32_info(काष्ठा Scsi_Host *shpnt)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)shpnt->hostdata;

	वापस data->info_str;
पूर्ण


/****************************************************************************
 * error handler
 */
अटल पूर्णांक nsp32_eh_पात(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	अचिन्हित पूर्णांक   base = SCpnt->device->host->io_port;

	nsp32_msg(KERN_WARNING, "abort");

	अगर (data->cur_lunt->SCpnt == शून्य) अणु
		nsp32_dbg(NSP32_DEBUG_BUSRESET, "abort failed");
		वापस FAILED;
	पूर्ण

	अगर (data->cur_target->sync_flag & (SDTR_INITIATOR | SDTR_TARGET)) अणु
		/* reset SDTR negotiation */
		data->cur_target->sync_flag = 0;
		nsp32_set_async(data, data->cur_target);
	पूर्ण

	nsp32_ग_लिखो2(base, TRANSFER_CONTROL, 0);
	nsp32_ग_लिखो2(base, BM_CNT,           0);

	SCpnt->result = DID_ABORT << 16;
	nsp32_scsi_करोne(SCpnt);

	nsp32_dbg(NSP32_DEBUG_BUSRESET, "abort success");
	वापस SUCCESS;
पूर्ण

अटल व्योम nsp32_करो_bus_reset(nsp32_hw_data *data)
अणु
	अचिन्हित पूर्णांक   base = data->BaseAddress;
	पूर्णांक i;
	अचिन्हित लघु __maybe_unused पूर्णांकrdat;

	nsp32_dbg(NSP32_DEBUG_BUSRESET, "in");

	/*
	 * stop all transfer
	 * clear TRANSFERCONTROL_BM_START
	 * clear counter
	 */
	nsp32_ग_लिखो2(base, TRANSFER_CONTROL, 0);
	nsp32_ग_लिखो4(base, BM_CNT,           0);
	nsp32_ग_लिखो4(base, CLR_COUNTER,      CLRCOUNTER_ALLMASK);

	/*
	 * fall back to asynchronous transfer mode
	 * initialize SDTR negotiation flag
	 */
	क्रम (i = 0; i < ARRAY_SIZE(data->target); i++) अणु
		nsp32_target *target = &data->target[i];

		target->sync_flag = 0;
		nsp32_set_async(data, target);
	पूर्ण

	/*
	 * reset SCSI bus
	 */
	nsp32_ग_लिखो1(base, SCSI_BUS_CONTROL, BUSCTL_RST);
	mdelay(RESET_HOLD_TIME / 1000);
	nsp32_ग_लिखो1(base, SCSI_BUS_CONTROL, 0);
	क्रम(i = 0; i < 5; i++) अणु
		पूर्णांकrdat = nsp32_पढ़ो2(base, IRQ_STATUS); /* dummy पढ़ो */
		nsp32_dbg(NSP32_DEBUG_BUSRESET, "irq:1: 0x%x", पूर्णांकrdat);
        पूर्ण

	data->CurrentSC = शून्य;
पूर्ण

अटल पूर्णांक nsp32_eh_host_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	काष्ठा Scsi_Host *host = SCpnt->device->host;
	अचिन्हित पूर्णांक      base = SCpnt->device->host->io_port;
	nsp32_hw_data    *data = (nsp32_hw_data *)host->hostdata;

	nsp32_msg(KERN_INFO, "Host Reset");	
	nsp32_dbg(NSP32_DEBUG_BUSRESET, "SCpnt=0x%x", SCpnt);

	spin_lock_irq(SCpnt->device->host->host_lock);

	nsp32hw_init(data);
	nsp32_ग_लिखो2(base, IRQ_CONTROL, IRQ_CONTROL_ALL_IRQ_MASK);
	nsp32_करो_bus_reset(data);
	nsp32_ग_लिखो2(base, IRQ_CONTROL, 0);

	spin_unlock_irq(SCpnt->device->host->host_lock);
	वापस SUCCESS;	/* Host reset is succeeded at any समय. */
पूर्ण


/**************************************************************************
 * EEPROM handler
 */

/*
 * getting EEPROM parameter
 */
अटल पूर्णांक nsp32_getprom_param(nsp32_hw_data *data)
अणु
	पूर्णांक venकरोr = data->pci_devid->venकरोr;
	पूर्णांक device = data->pci_devid->device;
	पूर्णांक ret, i;
	पूर्णांक __maybe_unused val;

	/*
	 * EEPROM checking.
	 */
	ret = nsp32_prom_पढ़ो(data, 0x7e);
	अगर (ret != 0x55) अणु
		nsp32_msg(KERN_INFO, "No EEPROM detected: 0x%x", ret);
		वापस FALSE;
	पूर्ण
	ret = nsp32_prom_पढ़ो(data, 0x7f);
	अगर (ret != 0xaa) अणु
		nsp32_msg(KERN_INFO, "Invalid number: 0x%x", ret);
		वापस FALSE;
	पूर्ण

	/*
	 * check EEPROM type
	 */
	अगर (venकरोr == PCI_VENDOR_ID_WORKBIT &&
	    device == PCI_DEVICE_ID_WORKBIT_STANDARD) अणु
		ret = nsp32_getprom_c16(data);
	पूर्ण अन्यथा अगर (venकरोr == PCI_VENDOR_ID_WORKBIT &&
		   device == PCI_DEVICE_ID_NINJASCSI_32BIB_LOGITEC) अणु
		ret = nsp32_getprom_at24(data);
	पूर्ण अन्यथा अगर (venकरोr == PCI_VENDOR_ID_WORKBIT &&
		   device == PCI_DEVICE_ID_NINJASCSI_32UDE_MELCO ) अणु
		ret = nsp32_getprom_at24(data);
	पूर्ण अन्यथा अणु
		nsp32_msg(KERN_WARNING, "Unknown EEPROM");
		ret = FALSE;
	पूर्ण

	/* क्रम debug : SPROM data full checking */
	क्रम (i = 0; i <= 0x1f; i++) अणु
		val = nsp32_prom_पढ़ो(data, i);
		nsp32_dbg(NSP32_DEBUG_EEPROM,
			  "rom address 0x%x : 0x%x", i, val);
	पूर्ण

	वापस ret;
पूर्ण


/*
 * AT24C01A (Logitec: LHA-600S), AT24C02 (Melco Buffalo: IFC-USLP) data map:
 *
 *   ROMADDR
 *   0x00 - 0x06 :  Device Synchronous Transfer Period (SCSI ID 0 - 6) 
 *			Value 0x0: ASYNC, 0x0c: Ultra-20M, 0x19: Fast-10M
 *   0x07        :  HBA Synchronous Transfer Period
 *			Value 0: AutoSync, 1: Manual Setting
 *   0x08 - 0x0f :  Not Used? (0x0)
 *   0x10        :  Bus Termination
 * 			Value 0: Auto[ON], 1: ON, 2: OFF
 *   0x11        :  Not Used? (0)
 *   0x12        :  Bus Reset Delay Time (0x03)
 *   0x13        :  Bootable CD Support
 *			Value 0: Disable, 1: Enable
 *   0x14        :  Device Scan
 *			Bit   7  6  5  4  3  2  1  0
 *			      |  <----------------->
 * 			      |    SCSI ID: Value 0: Skip, 1: YES
 *			      |->  Value 0: ALL scan,  Value 1: Manual
 *   0x15 - 0x1b :  Not Used? (0)
 *   0x1c        :  Constant? (0x01) (घड़ी भाग?)
 *   0x1d - 0x7c :  Not Used (0xff)
 *   0x7d	 :  Not Used? (0xff)
 *   0x7e        :  Constant (0x55), Validity signature
 *   0x7f        :  Constant (0xaa), Validity signature
 */
अटल पूर्णांक nsp32_getprom_at24(nsp32_hw_data *data)
अणु
	पूर्णांक           ret, i;
	पूर्णांक           स्वतः_sync;
	nsp32_target *target;
	पूर्णांक           entry;

	/*
	 * Reset समय which is designated by EEPROM.
	 *
	 * TODO: Not used yet.
	 */
	data->reसमय_रखो = nsp32_prom_पढ़ो(data, 0x12);

	/*
	 * HBA Synchronous Transfer Period
	 *
	 * Note: स्वतः_sync = 0: स्वतः, 1: manual.  Ninja SCSI HBA spec says
	 *	that अगर स्वतः_sync is 0 (स्वतः), and connected SCSI devices are
	 *	same or lower than 3, then transfer speed is set as ULTRA-20M.
	 *	On the contrary अगर connected SCSI devices are same or higher
	 *	than 4, then transfer speed is set as FAST-10M.
	 *
	 *	I अवरोध this rule. The number of connected SCSI devices are
	 *	only ignored. If स्वतः_sync is 0 (स्वतः), then transfer speed is
	 *	क्रमced as ULTRA-20M.
	 */
	ret = nsp32_prom_पढ़ो(data, 0x07);
	चयन (ret) अणु
	हाल 0:
		स्वतः_sync = TRUE;
		अवरोध;
	हाल 1:
		स्वतः_sync = FALSE;
		अवरोध;
	शेष:
		nsp32_msg(KERN_WARNING,
			  "Unsupported Auto Sync mode. Fall back to manual mode.");
		स्वतः_sync = TRUE;
	पूर्ण

	अगर (trans_mode == ULTRA20M_MODE) अणु
		स्वतः_sync = TRUE;
	पूर्ण

	/*
	 * each device Synchronous Transfer Period
	 */
	क्रम (i = 0; i < NSP32_HOST_SCSIID; i++) अणु
		target = &data->target[i];
		अगर (स्वतः_sync == TRUE) अणु
			target->limit_entry = 0;   /* set as ULTRA20M */
		पूर्ण अन्यथा अणु
			ret   = nsp32_prom_पढ़ो(data, i);
			entry = nsp32_search_period_entry(data, target, ret);
			अगर (entry < 0) अणु
				/* search failed... set maximum speed */
				entry = 0;
			पूर्ण
			target->limit_entry = entry;
		पूर्ण
	पूर्ण

	वापस TRUE;
पूर्ण


/*
 * C16 110 (I-O Data: SC-NBD) data map:
 *
 *   ROMADDR
 *   0x00 - 0x06 :  Device Synchronous Transfer Period (SCSI ID 0 - 6) 
 *			Value 0x0: 20MB/S, 0x1: 10MB/S, 0x2: 5MB/S, 0x3: ASYNC
 *   0x07        :  0 (HBA Synchronous Transfer Period: Auto Sync)
 *   0x08 - 0x0f :  Not Used? (0x0)
 *   0x10        :  Transfer Mode
 *			Value 0: PIO, 1: Busmater
 *   0x11        :  Bus Reset Delay Time (0x00-0x20)
 *   0x12        :  Bus Termination
 * 			Value 0: Disable, 1: Enable
 *   0x13 - 0x19 :  Disconnection
 *			Value 0: Disable, 1: Enable
 *   0x1a - 0x7c :  Not Used? (0)
 *   0x7d	 :  Not Used? (0xf8)
 *   0x7e        :  Constant (0x55), Validity signature
 *   0x7f        :  Constant (0xaa), Validity signature
 */
अटल पूर्णांक nsp32_getprom_c16(nsp32_hw_data *data)
अणु
	पूर्णांक           ret, i;
	nsp32_target *target;
	पूर्णांक           entry, val;

	/*
	 * Reset समय which is designated by EEPROM.
	 *
	 * TODO: Not used yet.
	 */
	data->reसमय_रखो = nsp32_prom_पढ़ो(data, 0x11);

	/*
	 * each device Synchronous Transfer Period
	 */
	क्रम (i = 0; i < NSP32_HOST_SCSIID; i++) अणु
		target = &data->target[i];
		ret = nsp32_prom_पढ़ो(data, i);
		चयन (ret) अणु
		हाल 0:		/* 20MB/s */
			val = 0x0c;
			अवरोध;
		हाल 1:		/* 10MB/s */
			val = 0x19;
			अवरोध;
		हाल 2:		/* 5MB/s */
			val = 0x32;
			अवरोध;
		हाल 3:		/* ASYNC */
			val = 0x00;
			अवरोध;
		शेष:	/* शेष 20MB/s */
			val = 0x0c;
			अवरोध;
		पूर्ण
		entry = nsp32_search_period_entry(data, target, val);
		अगर (entry < 0 || trans_mode == ULTRA20M_MODE) अणु
			/* search failed... set maximum speed */
			entry = 0;
		पूर्ण
		target->limit_entry = entry;
	पूर्ण

	वापस TRUE;
पूर्ण


/*
 * Aपंचांगel AT24C01A (drived in 5V) serial EEPROM routines
 */
अटल पूर्णांक nsp32_prom_पढ़ो(nsp32_hw_data *data, पूर्णांक romaddr)
अणु
	पूर्णांक i, val;

	/* start condition */
	nsp32_prom_start(data);

	/* device address */
	nsp32_prom_ग_लिखो_bit(data, 1);	/* 1 */
	nsp32_prom_ग_लिखो_bit(data, 0);	/* 0 */
	nsp32_prom_ग_लिखो_bit(data, 1);	/* 1 */
	nsp32_prom_ग_लिखो_bit(data, 0);	/* 0 */
	nsp32_prom_ग_लिखो_bit(data, 0);	/* A2: 0 (GND) */
	nsp32_prom_ग_लिखो_bit(data, 0);	/* A1: 0 (GND) */
	nsp32_prom_ग_लिखो_bit(data, 0);	/* A0: 0 (GND) */

	/* R/W: W क्रम dummy ग_लिखो */
	nsp32_prom_ग_लिखो_bit(data, 0);

	/* ack */
	nsp32_prom_ग_लिखो_bit(data, 0);

	/* word address */
	क्रम (i = 7; i >= 0; i--) अणु
		nsp32_prom_ग_लिखो_bit(data, ((romaddr >> i) & 1));
	पूर्ण

	/* ack */
	nsp32_prom_ग_लिखो_bit(data, 0);

	/* start condition */
	nsp32_prom_start(data);

	/* device address */
	nsp32_prom_ग_लिखो_bit(data, 1);	/* 1 */
	nsp32_prom_ग_लिखो_bit(data, 0);	/* 0 */
	nsp32_prom_ग_लिखो_bit(data, 1);	/* 1 */
	nsp32_prom_ग_लिखो_bit(data, 0);	/* 0 */
	nsp32_prom_ग_लिखो_bit(data, 0);	/* A2: 0 (GND) */
	nsp32_prom_ग_लिखो_bit(data, 0);	/* A1: 0 (GND) */
	nsp32_prom_ग_लिखो_bit(data, 0);	/* A0: 0 (GND) */

	/* R/W: R */
	nsp32_prom_ग_लिखो_bit(data, 1);

	/* ack */
	nsp32_prom_ग_लिखो_bit(data, 0);

	/* data... */
	val = 0;
	क्रम (i = 7; i >= 0; i--) अणु
		val += (nsp32_prom_पढ़ो_bit(data) << i);
	पूर्ण
	
	/* no ack */
	nsp32_prom_ग_लिखो_bit(data, 1);

	/* stop condition */
	nsp32_prom_stop(data);

	वापस val;
पूर्ण

अटल व्योम nsp32_prom_set(nsp32_hw_data *data, पूर्णांक bit, पूर्णांक val)
अणु
	पूर्णांक base = data->BaseAddress;
	पूर्णांक पंचांगp;

	पंचांगp = nsp32_index_पढ़ो1(base, SERIAL_ROM_CTL);

	अगर (val == 0) अणु
		पंचांगp &= ~bit;
	पूर्ण अन्यथा अणु
		पंचांगp |=  bit;
	पूर्ण

	nsp32_index_ग_लिखो1(base, SERIAL_ROM_CTL, पंचांगp);

	udelay(10);
पूर्ण

अटल पूर्णांक nsp32_prom_get(nsp32_hw_data *data, पूर्णांक bit)
अणु
	पूर्णांक base = data->BaseAddress;
	पूर्णांक पंचांगp, ret;

	अगर (bit != SDA) अणु
		nsp32_msg(KERN_ERR, "return value is not appropriate");
		वापस 0;
	पूर्ण


	पंचांगp = nsp32_index_पढ़ो1(base, SERIAL_ROM_CTL) & bit;

	अगर (पंचांगp == 0) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = 1;
	पूर्ण

	udelay(10);

	वापस ret;
पूर्ण

अटल व्योम nsp32_prom_start (nsp32_hw_data *data)
अणु
	/* start condition */
	nsp32_prom_set(data, SCL, 1);
	nsp32_prom_set(data, SDA, 1);
	nsp32_prom_set(data, ENA, 1);	/* output mode */
	nsp32_prom_set(data, SDA, 0);	/* keeping SCL=1 and transiting
					 * SDA 1->0 is start condition */
	nsp32_prom_set(data, SCL, 0);
पूर्ण

अटल व्योम nsp32_prom_stop (nsp32_hw_data *data)
अणु
	/* stop condition */
	nsp32_prom_set(data, SCL, 1);
	nsp32_prom_set(data, SDA, 0);
	nsp32_prom_set(data, ENA, 1);	/* output mode */
	nsp32_prom_set(data, SDA, 1);
	nsp32_prom_set(data, SCL, 0);
पूर्ण

अटल व्योम nsp32_prom_ग_लिखो_bit(nsp32_hw_data *data, पूर्णांक val)
अणु
	/* ग_लिखो */
	nsp32_prom_set(data, SDA, val);
	nsp32_prom_set(data, SCL, 1  );
	nsp32_prom_set(data, SCL, 0  );
पूर्ण

अटल पूर्णांक nsp32_prom_पढ़ो_bit(nsp32_hw_data *data)
अणु
	पूर्णांक val;

	/* पढ़ो */
	nsp32_prom_set(data, ENA, 0);	/* input mode */
	nsp32_prom_set(data, SCL, 1);

	val = nsp32_prom_get(data, SDA);

	nsp32_prom_set(data, SCL, 0);
	nsp32_prom_set(data, ENA, 1);	/* output mode */

	वापस val;
पूर्ण


/**************************************************************************
 * Power Management
 */
#अगर_घोषित CONFIG_PM

/* Device suspended */
अटल पूर्णांक nsp32_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);

	nsp32_msg(KERN_INFO, "pci-suspend: pdev=0x%p, state.event=%x, slot=%s, host=0x%p",
		  pdev, state.event, pci_name(pdev), host);

	pci_save_state     (pdev);
	pci_disable_device (pdev);
	pci_set_घातer_state(pdev, pci_choose_state(pdev, state));

	वापस 0;
पूर्ण

/* Device woken up */
अटल पूर्णांक nsp32_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	nsp32_hw_data    *data = (nsp32_hw_data *)host->hostdata;
	अचिन्हित लघु    reg;

	nsp32_msg(KERN_INFO, "pci-resume: pdev=0x%p, slot=%s, host=0x%p", pdev, pci_name(pdev), host);

	pci_set_घातer_state(pdev, PCI_D0);
	pci_enable_wake    (pdev, PCI_D0, 0);
	pci_restore_state  (pdev);

	reg = nsp32_पढ़ो2(data->BaseAddress, INDEX_REG);

	nsp32_msg(KERN_INFO, "io=0x%x reg=0x%x", data->BaseAddress, reg);

	अगर (reg == 0xffff) अणु
		nsp32_msg(KERN_INFO, "missing device. abort resume.");
		वापस 0;
	पूर्ण

	nsp32hw_init      (data);
	nsp32_करो_bus_reset(data);

	nsp32_msg(KERN_INFO, "resume success");

	वापस 0;
पूर्ण

#पूर्ण_अगर

/************************************************************************
 * PCI/Cardbus probe/हटाओ routine
 */
अटल पूर्णांक nsp32_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक ret;
	nsp32_hw_data *data = &nsp32_data_base;

	nsp32_dbg(NSP32_DEBUG_REGISTER, "enter");

        ret = pci_enable_device(pdev);
	अगर (ret) अणु
		nsp32_msg(KERN_ERR, "failed to enable pci device");
		वापस ret;
	पूर्ण

	data->Pci         = pdev;
	data->pci_devid   = id;
	data->IrqNumber   = pdev->irq;
	data->BaseAddress = pci_resource_start(pdev, 0);
	data->NumAddress  = pci_resource_len  (pdev, 0);
	data->MmioAddress = pci_ioremap_bar(pdev, 1);
	data->MmioLength  = pci_resource_len  (pdev, 1);

	pci_set_master(pdev);

	ret = nsp32_detect(pdev);

	nsp32_msg(KERN_INFO, "irq: %i mmio: %p+0x%lx slot: %s model: %s",
		  pdev->irq,
		  data->MmioAddress, data->MmioLength,
		  pci_name(pdev),
		  nsp32_model[id->driver_data]);

	nsp32_dbg(NSP32_DEBUG_REGISTER, "exit %d", ret);

	वापस ret;
पूर्ण

अटल व्योम nsp32_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);

	nsp32_dbg(NSP32_DEBUG_REGISTER, "enter");

        scsi_हटाओ_host(host);

	nsp32_release(host);

	scsi_host_put(host);
पूर्ण

अटल काष्ठा pci_driver nsp32_driver = अणु
	.name		= "nsp32",
	.id_table	= nsp32_pci_table,
	.probe		= nsp32_probe,
	.हटाओ		= nsp32_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= nsp32_suspend, 
	.resume		= nsp32_resume, 
#पूर्ण_अगर
पूर्ण;

/*********************************************************************
 * Moule entry poपूर्णांक
 */
अटल पूर्णांक __init init_nsp32(व्योम) अणु
	nsp32_msg(KERN_INFO, "loading...");
	वापस pci_रेजिस्टर_driver(&nsp32_driver);
पूर्ण

अटल व्योम __निकास निकास_nsp32(व्योम) अणु
	nsp32_msg(KERN_INFO, "unloading...");
	pci_unरेजिस्टर_driver(&nsp32_driver);
पूर्ण

module_init(init_nsp32);
module_निकास(निकास_nsp32);

/* end */
