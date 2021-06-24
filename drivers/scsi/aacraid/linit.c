<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Adaptec AAC series RAID controller driver
 *	(c) Copyright 2001 Red Hat Inc.
 *
 * based on the old aacraid driver that is..
 * Adaptec aacraid device driver क्रम Linux.
 *
 * Copyright (c) 2000-2010 Adaptec, Inc.
 *               2010-2015 PMC-Sierra, Inc. (aacraid@pmc-sierra.com)
 *		 2016-2017 Microsemi Corp. (aacraid@microsemi.com)
 *
 * Module Name:
 *   linit.c
 *
 * Abstract: Linux Driver entry module क्रम Adaptec RAID Array Controller
 */


#समावेश <linux/compat.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/completion.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/aer.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/msकरोs_partition.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsicam.h>
#समावेश <scsi/scsi_eh.h>

#समावेश "aacraid.h"

#घोषणा AAC_DRIVER_VERSION		"1.2.1"
#अगर_अघोषित AAC_DRIVER_BRANCH
#घोषणा AAC_DRIVER_BRANCH		""
#पूर्ण_अगर
#घोषणा AAC_DRIVERNAME			"aacraid"

#अगर_घोषित AAC_DRIVER_BUILD
#घोषणा _str(x) #x
#घोषणा str(x) _str(x)
#घोषणा AAC_DRIVER_FULL_VERSION	AAC_DRIVER_VERSION "[" str(AAC_DRIVER_BUILD) "]" AAC_DRIVER_BRANCH
#अन्यथा
#घोषणा AAC_DRIVER_FULL_VERSION	AAC_DRIVER_VERSION AAC_DRIVER_BRANCH
#पूर्ण_अगर

MODULE_AUTHOR("Red Hat Inc and Adaptec");
MODULE_DESCRIPTION("Dell PERC2, 2/Si, 3/Si, 3/Di, "
		   "Adaptec Advanced Raid Products, "
		   "HP NetRAID-4M, IBM ServeRAID & ICP SCSI driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(AAC_DRIVER_FULL_VERSION);

अटल DEFINE_MUTEX(aac_mutex);
अटल LIST_HEAD(aac_devices);
अटल पूर्णांक aac_cfg_major = AAC_CHARDEV_UNREGISTERED;
अक्षर aac_driver_version[] = AAC_DRIVER_FULL_VERSION;

/*
 * Because of the way Linux names scsi devices, the order in this table has
 * become important.  Check क्रम on-board Raid first, add-in cards second.
 *
 * Note: The last field is used to index पूर्णांकo aac_drivers below.
 */
अटल स्थिर काष्ठा pci_device_id aac_pci_tbl[] = अणु
	अणु 0x1028, 0x0001, 0x1028, 0x0001, 0, 0, 0 पूर्ण, /* PERC 2/Si (Iguana/PERC2Si) */
	अणु 0x1028, 0x0002, 0x1028, 0x0002, 0, 0, 1 पूर्ण, /* PERC 3/Di (Opal/PERC3Di) */
	अणु 0x1028, 0x0003, 0x1028, 0x0003, 0, 0, 2 पूर्ण, /* PERC 3/Si (SlimFast/PERC3Si */
	अणु 0x1028, 0x0004, 0x1028, 0x00d0, 0, 0, 3 पूर्ण, /* PERC 3/Di (Iguana FlipChip/PERC3DiF */
	अणु 0x1028, 0x0002, 0x1028, 0x00d1, 0, 0, 4 पूर्ण, /* PERC 3/Di (Viper/PERC3DiV) */
	अणु 0x1028, 0x0002, 0x1028, 0x00d9, 0, 0, 5 पूर्ण, /* PERC 3/Di (Lexus/PERC3DiL) */
	अणु 0x1028, 0x000a, 0x1028, 0x0106, 0, 0, 6 पूर्ण, /* PERC 3/Di (Jaguar/PERC3DiJ) */
	अणु 0x1028, 0x000a, 0x1028, 0x011b, 0, 0, 7 पूर्ण, /* PERC 3/Di (Dagger/PERC3DiD) */
	अणु 0x1028, 0x000a, 0x1028, 0x0121, 0, 0, 8 पूर्ण, /* PERC 3/Di (Boxster/PERC3DiB) */
	अणु 0x9005, 0x0283, 0x9005, 0x0283, 0, 0, 9 पूर्ण, /* catapult */
	अणु 0x9005, 0x0284, 0x9005, 0x0284, 0, 0, 10 पूर्ण, /* tomcat */
	अणु 0x9005, 0x0285, 0x9005, 0x0286, 0, 0, 11 पूर्ण, /* Adaptec 2120S (Crusader) */
	अणु 0x9005, 0x0285, 0x9005, 0x0285, 0, 0, 12 पूर्ण, /* Adaptec 2200S (Vulcan) */
	अणु 0x9005, 0x0285, 0x9005, 0x0287, 0, 0, 13 पूर्ण, /* Adaptec 2200S (Vulcan-2m) */
	अणु 0x9005, 0x0285, 0x17aa, 0x0286, 0, 0, 14 पूर्ण, /* Legend S220 (Legend Crusader) */
	अणु 0x9005, 0x0285, 0x17aa, 0x0287, 0, 0, 15 पूर्ण, /* Legend S230 (Legend Vulcan) */

	अणु 0x9005, 0x0285, 0x9005, 0x0288, 0, 0, 16 पूर्ण, /* Adaptec 3230S (Harrier) */
	अणु 0x9005, 0x0285, 0x9005, 0x0289, 0, 0, 17 पूर्ण, /* Adaptec 3240S (Tornaकरो) */
	अणु 0x9005, 0x0285, 0x9005, 0x028a, 0, 0, 18 पूर्ण, /* ASR-2020ZCR SCSI PCI-X ZCR (Skyhawk) */
	अणु 0x9005, 0x0285, 0x9005, 0x028b, 0, 0, 19 पूर्ण, /* ASR-2025ZCR SCSI SO-DIMM PCI-X ZCR (Terminator) */
	अणु 0x9005, 0x0286, 0x9005, 0x028c, 0, 0, 20 पूर्ण, /* ASR-2230S + ASR-2230SLP PCI-X (Lancer) */
	अणु 0x9005, 0x0286, 0x9005, 0x028d, 0, 0, 21 पूर्ण, /* ASR-2130S (Lancer) */
	अणु 0x9005, 0x0286, 0x9005, 0x029b, 0, 0, 22 पूर्ण, /* AAR-2820SA (Intruder) */
	अणु 0x9005, 0x0286, 0x9005, 0x029c, 0, 0, 23 पूर्ण, /* AAR-2620SA (Intruder) */
	अणु 0x9005, 0x0286, 0x9005, 0x029d, 0, 0, 24 पूर्ण, /* AAR-2420SA (Intruder) */
	अणु 0x9005, 0x0286, 0x9005, 0x029e, 0, 0, 25 पूर्ण, /* ICP9024RO (Lancer) */
	अणु 0x9005, 0x0286, 0x9005, 0x029f, 0, 0, 26 पूर्ण, /* ICP9014RO (Lancer) */
	अणु 0x9005, 0x0286, 0x9005, 0x02a0, 0, 0, 27 पूर्ण, /* ICP9047MA (Lancer) */
	अणु 0x9005, 0x0286, 0x9005, 0x02a1, 0, 0, 28 पूर्ण, /* ICP9087MA (Lancer) */
	अणु 0x9005, 0x0286, 0x9005, 0x02a3, 0, 0, 29 पूर्ण, /* ICP5445AU (Hurricane44) */
	अणु 0x9005, 0x0285, 0x9005, 0x02a4, 0, 0, 30 पूर्ण, /* ICP9085LI (Marauder-X) */
	अणु 0x9005, 0x0285, 0x9005, 0x02a5, 0, 0, 31 पूर्ण, /* ICP5085BR (Marauder-E) */
	अणु 0x9005, 0x0286, 0x9005, 0x02a6, 0, 0, 32 पूर्ण, /* ICP9067MA (Intruder-6) */
	अणु 0x9005, 0x0287, 0x9005, 0x0800, 0, 0, 33 पूर्ण, /* Themisto Jupiter Platक्रमm */
	अणु 0x9005, 0x0200, 0x9005, 0x0200, 0, 0, 33 पूर्ण, /* Themisto Jupiter Platक्रमm */
	अणु 0x9005, 0x0286, 0x9005, 0x0800, 0, 0, 34 पूर्ण, /* Callisto Jupiter Platक्रमm */
	अणु 0x9005, 0x0285, 0x9005, 0x028e, 0, 0, 35 पूर्ण, /* ASR-2020SA SATA PCI-X ZCR (Skyhawk) */
	अणु 0x9005, 0x0285, 0x9005, 0x028f, 0, 0, 36 पूर्ण, /* ASR-2025SA SATA SO-DIMM PCI-X ZCR (Terminator) */
	अणु 0x9005, 0x0285, 0x9005, 0x0290, 0, 0, 37 पूर्ण, /* AAR-2410SA PCI SATA 4ch (Jaguar II) */
	अणु 0x9005, 0x0285, 0x1028, 0x0291, 0, 0, 38 पूर्ण, /* CERC SATA RAID 2 PCI SATA 6ch (DellCorsair) */
	अणु 0x9005, 0x0285, 0x9005, 0x0292, 0, 0, 39 पूर्ण, /* AAR-2810SA PCI SATA 8ch (Corsair-8) */
	अणु 0x9005, 0x0285, 0x9005, 0x0293, 0, 0, 40 पूर्ण, /* AAR-21610SA PCI SATA 16ch (Corsair-16) */
	अणु 0x9005, 0x0285, 0x9005, 0x0294, 0, 0, 41 पूर्ण, /* ESD SO-DIMM PCI-X SATA ZCR (Prowler) */
	अणु 0x9005, 0x0285, 0x103C, 0x3227, 0, 0, 42 पूर्ण, /* AAR-2610SA PCI SATA 6ch */
	अणु 0x9005, 0x0285, 0x9005, 0x0296, 0, 0, 43 पूर्ण, /* ASR-2240S (SabreExpress) */
	अणु 0x9005, 0x0285, 0x9005, 0x0297, 0, 0, 44 पूर्ण, /* ASR-4005 */
	अणु 0x9005, 0x0285, 0x1014, 0x02F2, 0, 0, 45 पूर्ण, /* IBM 8i (AvonPark) */
	अणु 0x9005, 0x0285, 0x1014, 0x0312, 0, 0, 45 पूर्ण, /* IBM 8i (AvonPark Lite) */
	अणु 0x9005, 0x0286, 0x1014, 0x9580, 0, 0, 46 पूर्ण, /* IBM 8k/8k-l8 (Aurora) */
	अणु 0x9005, 0x0286, 0x1014, 0x9540, 0, 0, 47 पूर्ण, /* IBM 8k/8k-l4 (Aurora Lite) */
	अणु 0x9005, 0x0285, 0x9005, 0x0298, 0, 0, 48 पूर्ण, /* ASR-4000 (BlackBird) */
	अणु 0x9005, 0x0285, 0x9005, 0x0299, 0, 0, 49 पूर्ण, /* ASR-4800SAS (Marauder-X) */
	अणु 0x9005, 0x0285, 0x9005, 0x029a, 0, 0, 50 पूर्ण, /* ASR-4805SAS (Marauder-E) */
	अणु 0x9005, 0x0286, 0x9005, 0x02a2, 0, 0, 51 पूर्ण, /* ASR-3800 (Hurricane44) */

	अणु 0x9005, 0x0285, 0x1028, 0x0287, 0, 0, 52 पूर्ण, /* Perc 320/DC*/
	अणु 0x1011, 0x0046, 0x9005, 0x0365, 0, 0, 53 पूर्ण, /* Adaptec 5400S (Mustang)*/
	अणु 0x1011, 0x0046, 0x9005, 0x0364, 0, 0, 54 पूर्ण, /* Adaptec 5400S (Mustang)*/
	अणु 0x1011, 0x0046, 0x9005, 0x1364, 0, 0, 55 पूर्ण, /* Dell PERC2/QC */
	अणु 0x1011, 0x0046, 0x103c, 0x10c2, 0, 0, 56 पूर्ण, /* HP NetRAID-4M */

	अणु 0x9005, 0x0285, 0x1028, PCI_ANY_ID, 0, 0, 57 पूर्ण, /* Dell Catchall */
	अणु 0x9005, 0x0285, 0x17aa, PCI_ANY_ID, 0, 0, 58 पूर्ण, /* Legend Catchall */
	अणु 0x9005, 0x0285, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 59 पूर्ण, /* Adaptec Catch All */
	अणु 0x9005, 0x0286, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 60 पूर्ण, /* Adaptec Rocket Catch All */
	अणु 0x9005, 0x0288, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 61 पूर्ण, /* Adaptec NEMER/ARK Catch All */
	अणु 0x9005, 0x028b, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 62 पूर्ण, /* Adaptec PMC Series 6 (Tupelo) */
	अणु 0x9005, 0x028c, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 63 पूर्ण, /* Adaptec PMC Series 7 (Denali) */
	अणु 0x9005, 0x028d, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 64 पूर्ण, /* Adaptec PMC Series 8 */
	अणु 0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, aac_pci_tbl);

/*
 * dmb - For now we add the number of channels to this काष्ठाure.
 * In the future we should add a fib that reports the number of channels
 * क्रम the card.  At that समय we can हटाओ the channels from here
 */
अटल काष्ठा aac_driver_ident aac_drivers[] = अणु
	अणु aac_rx_init, "percraid", "DELL    ", "PERCRAID        ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* PERC 2/Si (Iguana/PERC2Si) */
	अणु aac_rx_init, "percraid", "DELL    ", "PERCRAID        ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* PERC 3/Di (Opal/PERC3Di) */
	अणु aac_rx_init, "percraid", "DELL    ", "PERCRAID        ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* PERC 3/Si (SlimFast/PERC3Si */
	अणु aac_rx_init, "percraid", "DELL    ", "PERCRAID        ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* PERC 3/Di (Iguana FlipChip/PERC3DiF */
	अणु aac_rx_init, "percraid", "DELL    ", "PERCRAID        ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* PERC 3/Di (Viper/PERC3DiV) */
	अणु aac_rx_init, "percraid", "DELL    ", "PERCRAID        ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* PERC 3/Di (Lexus/PERC3DiL) */
	अणु aac_rx_init, "percraid", "DELL    ", "PERCRAID        ", 1, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* PERC 3/Di (Jaguar/PERC3DiJ) */
	अणु aac_rx_init, "percraid", "DELL    ", "PERCRAID        ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* PERC 3/Di (Dagger/PERC3DiD) */
	अणु aac_rx_init, "percraid", "DELL    ", "PERCRAID        ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* PERC 3/Di (Boxster/PERC3DiB) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "catapult        ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* catapult */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "tomcat          ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* tomcat */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "Adaptec 2120S   ", 1, AAC_QUIRK_31BIT | AAC_QUIRK_34SG पूर्ण,		      /* Adaptec 2120S (Crusader) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "Adaptec 2200S   ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG पूर्ण,		      /* Adaptec 2200S (Vulcan) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "Adaptec 2200S   ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* Adaptec 2200S (Vulcan-2m) */
	अणु aac_rx_init, "aacraid",  "Legend  ", "Legend S220     ", 1, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* Legend S220 (Legend Crusader) */
	अणु aac_rx_init, "aacraid",  "Legend  ", "Legend S230     ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* Legend S230 (Legend Vulcan) */

	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "Adaptec 3230S   ", 2 पूर्ण, /* Adaptec 3230S (Harrier) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "Adaptec 3240S   ", 2 पूर्ण, /* Adaptec 3240S (Tornaकरो) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "ASR-2020ZCR     ", 2 पूर्ण, /* ASR-2020ZCR SCSI PCI-X ZCR (Skyhawk) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "ASR-2025ZCR     ", 2 पूर्ण, /* ASR-2025ZCR SCSI SO-DIMM PCI-X ZCR (Terminator) */
	अणु aac_rkt_init, "aacraid",  "ADAPTEC ", "ASR-2230S PCI-X ", 2 पूर्ण, /* ASR-2230S + ASR-2230SLP PCI-X (Lancer) */
	अणु aac_rkt_init, "aacraid",  "ADAPTEC ", "ASR-2130S PCI-X ", 1 पूर्ण, /* ASR-2130S (Lancer) */
	अणु aac_rkt_init, "aacraid",  "ADAPTEC ", "AAR-2820SA      ", 1 पूर्ण, /* AAR-2820SA (Intruder) */
	अणु aac_rkt_init, "aacraid",  "ADAPTEC ", "AAR-2620SA      ", 1 पूर्ण, /* AAR-2620SA (Intruder) */
	अणु aac_rkt_init, "aacraid",  "ADAPTEC ", "AAR-2420SA      ", 1 पूर्ण, /* AAR-2420SA (Intruder) */
	अणु aac_rkt_init, "aacraid",  "ICP     ", "ICP9024RO       ", 2 पूर्ण, /* ICP9024RO (Lancer) */
	अणु aac_rkt_init, "aacraid",  "ICP     ", "ICP9014RO       ", 1 पूर्ण, /* ICP9014RO (Lancer) */
	अणु aac_rkt_init, "aacraid",  "ICP     ", "ICP9047MA       ", 1 पूर्ण, /* ICP9047MA (Lancer) */
	अणु aac_rkt_init, "aacraid",  "ICP     ", "ICP9087MA       ", 1 पूर्ण, /* ICP9087MA (Lancer) */
	अणु aac_rkt_init, "aacraid",  "ICP     ", "ICP5445AU       ", 1 पूर्ण, /* ICP5445AU (Hurricane44) */
	अणु aac_rx_init, "aacraid",  "ICP     ", "ICP9085LI       ", 1 पूर्ण, /* ICP9085LI (Marauder-X) */
	अणु aac_rx_init, "aacraid",  "ICP     ", "ICP5085BR       ", 1 पूर्ण, /* ICP5085BR (Marauder-E) */
	अणु aac_rkt_init, "aacraid",  "ICP     ", "ICP9067MA       ", 1 पूर्ण, /* ICP9067MA (Intruder-6) */
	अणु शून्य        , "aacraid",  "ADAPTEC ", "Themisto        ", 0, AAC_QUIRK_SLAVE पूर्ण, /* Jupiter Platक्रमm */
	अणु aac_rkt_init, "aacraid",  "ADAPTEC ", "Callisto        ", 2, AAC_QUIRK_MASTER पूर्ण, /* Jupiter Platक्रमm */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "ASR-2020SA       ", 1 पूर्ण, /* ASR-2020SA SATA PCI-X ZCR (Skyhawk) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "ASR-2025SA       ", 1 पूर्ण, /* ASR-2025SA SATA SO-DIMM PCI-X ZCR (Terminator) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "AAR-2410SA SATA ", 1, AAC_QUIRK_17SG पूर्ण, /* AAR-2410SA PCI SATA 4ch (Jaguar II) */
	अणु aac_rx_init, "aacraid",  "DELL    ", "CERC SR2        ", 1, AAC_QUIRK_17SG पूर्ण, /* CERC SATA RAID 2 PCI SATA 6ch (DellCorsair) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "AAR-2810SA SATA ", 1, AAC_QUIRK_17SG पूर्ण, /* AAR-2810SA PCI SATA 8ch (Corsair-8) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "AAR-21610SA SATA", 1, AAC_QUIRK_17SG पूर्ण, /* AAR-21610SA PCI SATA 16ch (Corsair-16) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "ASR-2026ZCR     ", 1 पूर्ण, /* ESD SO-DIMM PCI-X SATA ZCR (Prowler) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "AAR-2610SA      ", 1 पूर्ण, /* SATA 6Ch (Bearcat) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "ASR-2240S       ", 1 पूर्ण, /* ASR-2240S (SabreExpress) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "ASR-4005        ", 1 पूर्ण, /* ASR-4005 */
	अणु aac_rx_init, "ServeRAID","IBM     ", "ServeRAID 8i    ", 1 पूर्ण, /* IBM 8i (AvonPark) */
	अणु aac_rkt_init, "ServeRAID","IBM     ", "ServeRAID 8k-l8 ", 1 पूर्ण, /* IBM 8k/8k-l8 (Aurora) */
	अणु aac_rkt_init, "ServeRAID","IBM     ", "ServeRAID 8k-l4 ", 1 पूर्ण, /* IBM 8k/8k-l4 (Aurora Lite) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "ASR-4000        ", 1 पूर्ण, /* ASR-4000 (BlackBird & AvonPark) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "ASR-4800SAS     ", 1 पूर्ण, /* ASR-4800SAS (Marauder-X) */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "ASR-4805SAS     ", 1 पूर्ण, /* ASR-4805SAS (Marauder-E) */
	अणु aac_rkt_init, "aacraid",  "ADAPTEC ", "ASR-3800        ", 1 पूर्ण, /* ASR-3800 (Hurricane44) */

	अणु aac_rx_init, "percraid", "DELL    ", "PERC 320/DC     ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG पूर्ण, /* Perc 320/DC*/
	अणु aac_sa_init, "aacraid",  "ADAPTEC ", "Adaptec 5400S   ", 4, AAC_QUIRK_34SG पूर्ण, /* Adaptec 5400S (Mustang)*/
	अणु aac_sa_init, "aacraid",  "ADAPTEC ", "AAC-364         ", 4, AAC_QUIRK_34SG पूर्ण, /* Adaptec 5400S (Mustang)*/
	अणु aac_sa_init, "percraid", "DELL    ", "PERCRAID        ", 4, AAC_QUIRK_34SG पूर्ण, /* Dell PERC2/QC */
	अणु aac_sa_init, "hpnraid",  "HP      ", "NetRAID         ", 4, AAC_QUIRK_34SG पूर्ण, /* HP NetRAID-4M */

	अणु aac_rx_init, "aacraid",  "DELL    ", "RAID            ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* Dell Catchall */
	अणु aac_rx_init, "aacraid",  "Legend  ", "RAID            ", 2, AAC_QUIRK_31BIT | AAC_QUIRK_34SG | AAC_QUIRK_SCSI_32 पूर्ण, /* Legend Catchall */
	अणु aac_rx_init, "aacraid",  "ADAPTEC ", "RAID            ", 2 पूर्ण, /* Adaptec Catch All */
	अणु aac_rkt_init, "aacraid", "ADAPTEC ", "RAID            ", 2 पूर्ण, /* Adaptec Rocket Catch All */
	अणु aac_nark_init, "aacraid", "ADAPTEC ", "RAID           ", 2 पूर्ण, /* Adaptec NEMER/ARK Catch All */
	अणु aac_src_init, "aacraid", "ADAPTEC ", "RAID            ", 2, AAC_QUIRK_SRC पूर्ण, /* Adaptec PMC Series 6 (Tupelo) */
	अणु aac_srcv_init, "aacraid", "ADAPTEC ", "RAID            ", 2, AAC_QUIRK_SRC पूर्ण, /* Adaptec PMC Series 7 (Denali) */
	अणु aac_srcv_init, "aacraid", "ADAPTEC ", "RAID            ", 2, AAC_QUIRK_SRC पूर्ण, /* Adaptec PMC Series 8 */
पूर्ण;

/**
 *	aac_queuecommand	-	queue a SCSI command
 *	@shost:		Scsi host to queue command on
 *	@cmd:		SCSI command to queue
 *
 *	Queues a command क्रम execution by the associated Host Adapter.
 *
 *	TODO: unअगरy with aac_scsi_cmd().
 */

अटल पूर्णांक aac_queuecommand(काष्ठा Scsi_Host *shost,
			    काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक r = 0;
	cmd->SCp.phase = AAC_OWNER_LOWLEVEL;
	r = (aac_scsi_cmd(cmd) ? FAILED : 0);
	वापस r;
पूर्ण

/**
 *	aac_info		-	Returns the host adapter name
 *	@shost:		Scsi host to report on
 *
 *	Returns a अटल string describing the device in question
 */

अटल स्थिर अक्षर *aac_info(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा aac_dev *dev = (काष्ठा aac_dev *)shost->hostdata;
	वापस aac_drivers[dev->cardtype].name;
पूर्ण

/**
 *	aac_get_driver_ident
 *	@devtype: index पूर्णांकo lookup table
 *
 *	Returns a poपूर्णांकer to the entry in the driver lookup table.
 */

काष्ठा aac_driver_ident* aac_get_driver_ident(पूर्णांक devtype)
अणु
	वापस &aac_drivers[devtype];
पूर्ण

/**
 *	aac_biosparm	-	वापस BIOS parameters क्रम disk
 *	@sdev: The scsi device corresponding to the disk
 *	@bdev: the block device corresponding to the disk
 *	@capacity: the sector capacity of the disk
 *	@geom: geometry block to fill in
 *
 *	Return the Heads/Sectors/Cylinders BIOS Disk Parameters क्रम Disk.
 *	The शेष disk geometry is 64 heads, 32 sectors, and the appropriate
 *	number of cylinders so as not to exceed drive capacity.  In order क्रम
 *	disks equal to or larger than 1 GB to be addressable by the BIOS
 *	without exceeding the BIOS limitation of 1024 cylinders, Extended
 *	Translation should be enabled.   With Extended Translation enabled,
 *	drives between 1 GB inclusive and 2 GB exclusive are given a disk
 *	geometry of 128 heads and 32 sectors, and drives above 2 GB inclusive
 *	are given a disk geometry of 255 heads and 63 sectors.  However, अगर
 *	the BIOS detects that the Extended Translation setting करोes not match
 *	the geometry in the partition table, then the translation inferred
 *	from the partition table will be used by the BIOS, and a warning may
 *	be displayed.
 */

अटल पूर्णांक aac_biosparm(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
			sector_t capacity, पूर्णांक *geom)
अणु
	काष्ठा diskparm *param = (काष्ठा diskparm *)geom;
	अचिन्हित अक्षर *buf;

	dprपूर्णांकk((KERN_DEBUG "aac_biosparm.\n"));

	/*
	 *	Assuming extended translation is enabled - #REVISIT#
	 */
	अगर (capacity >= 2 * 1024 * 1024) अणु /* 1 GB in 512 byte sectors */
		अगर(capacity >= 4 * 1024 * 1024) अणु /* 2 GB in 512 byte sectors */
			param->heads = 255;
			param->sectors = 63;
		पूर्ण अन्यथा अणु
			param->heads = 128;
			param->sectors = 32;
		पूर्ण
	पूर्ण अन्यथा अणु
		param->heads = 64;
		param->sectors = 32;
	पूर्ण

	param->cylinders = cap_to_cyls(capacity, param->heads * param->sectors);

	/*
	 *	Read the first 1024 bytes from the disk device, अगर the boot
	 *	sector partition table is valid, search क्रम a partition table
	 *	entry whose end_head matches one of the standard geometry
	 *	translations ( 64/32, 128/32, 255/63 ).
	 */
	buf = scsi_bios_ptable(bdev);
	अगर (!buf)
		वापस 0;
	अगर (*(__le16 *)(buf + 0x40) == cpu_to_le16(MSDOS_LABEL_MAGIC)) अणु
		काष्ठा msकरोs_partition *first = (काष्ठा msकरोs_partition *)buf;
		काष्ठा msकरोs_partition *entry = first;
		पूर्णांक saved_cylinders = param->cylinders;
		पूर्णांक num;
		अचिन्हित अक्षर end_head, end_sec;

		क्रम(num = 0; num < 4; num++) अणु
			end_head = entry->end_head;
			end_sec = entry->end_sector & 0x3f;

			अगर(end_head == 63) अणु
				param->heads = 64;
				param->sectors = 32;
				अवरोध;
			पूर्ण अन्यथा अगर(end_head == 127) अणु
				param->heads = 128;
				param->sectors = 32;
				अवरोध;
			पूर्ण अन्यथा अगर(end_head == 254) अणु
				param->heads = 255;
				param->sectors = 63;
				अवरोध;
			पूर्ण
			entry++;
		पूर्ण

		अगर (num == 4) अणु
			end_head = first->end_head;
			end_sec = first->end_sector & 0x3f;
		पूर्ण

		param->cylinders = cap_to_cyls(capacity, param->heads * param->sectors);
		अगर (num < 4 && end_sec == param->sectors) अणु
			अगर (param->cylinders != saved_cylinders) अणु
				dprपूर्णांकk((KERN_DEBUG "Adopting geometry: heads=%d, sectors=%d from partition table %d.\n",
					param->heads, param->sectors, num));
			पूर्ण
		पूर्ण अन्यथा अगर (end_head > 0 || end_sec > 0) अणु
			dprपूर्णांकk((KERN_DEBUG "Strange geometry: heads=%d, sectors=%d in partition table %d.\n",
				end_head + 1, end_sec, num));
			dprपूर्णांकk((KERN_DEBUG "Using geometry: heads=%d, sectors=%d.\n",
					param->heads, param->sectors));
		पूर्ण
	पूर्ण
	kमुक्त(buf);
	वापस 0;
पूर्ण

/**
 *	aac_slave_configure		-	compute queue depths
 *	@sdev:	SCSI device we are considering
 *
 *	Selects queue depths क्रम each target device based on the host adapter's
 *	total capacity and the queue depth supported by the target device.
 *	A queue depth of one स्वतःmatically disables tagged queueing.
 */

अटल पूर्णांक aac_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा aac_dev *aac = (काष्ठा aac_dev *)sdev->host->hostdata;
	पूर्णांक chn, tid;
	अचिन्हित पूर्णांक depth = 0;
	अचिन्हित पूर्णांक set_समयout = 0;
	पूर्णांक समयout = 0;
	bool set_qd_dev_type = false;
	u8 devtype = 0;

	chn = aac_logical_to_phys(sdev_channel(sdev));
	tid = sdev_id(sdev);
	अगर (chn < AAC_MAX_BUSES && tid < AAC_MAX_TARGETS && aac->sa_firmware) अणु
		devtype = aac->hba_map[chn][tid].devtype;

		अगर (devtype == AAC_DEVTYPE_NATIVE_RAW) अणु
			depth = aac->hba_map[chn][tid].qd_limit;
			set_समयout = 1;
			जाओ common_config;
		पूर्ण
		अगर (devtype == AAC_DEVTYPE_ARC_RAW) अणु
			set_qd_dev_type = true;
			set_समयout = 1;
			जाओ common_config;
		पूर्ण
	पूर्ण

	अगर (aac->jbod && (sdev->type == TYPE_DISK))
		sdev->removable = 1;

	अगर (sdev->type == TYPE_DISK
	 && sdev_channel(sdev) != CONTAINER_CHANNEL
	 && (!aac->jbod || sdev->inq_periph_qual)
	 && (!aac->raid_scsi_mode || (sdev_channel(sdev) != 2))) अणु

		अगर (expose_physicals == 0)
			वापस -ENXIO;

		अगर (expose_physicals < 0)
			sdev->no_uld_attach = 1;
	पूर्ण

	अगर (sdev->tagged_supported
	 &&  sdev->type == TYPE_DISK
	 &&  (!aac->raid_scsi_mode || (sdev_channel(sdev) != 2))
	 && !sdev->no_uld_attach) अणु

		काष्ठा scsi_device * dev;
		काष्ठा Scsi_Host *host = sdev->host;
		अचिन्हित num_lsu = 0;
		अचिन्हित num_one = 0;
		अचिन्हित cid;

		set_समयout = 1;

		क्रम (cid = 0; cid < aac->maximum_num_containers; ++cid)
			अगर (aac->fsa_dev[cid].valid)
				++num_lsu;

		__shost_क्रम_each_device(dev, host) अणु
			अगर (dev->tagged_supported
			 && dev->type == TYPE_DISK
			 && (!aac->raid_scsi_mode || (sdev_channel(sdev) != 2))
			 && !dev->no_uld_attach) अणु
				अगर ((sdev_channel(dev) != CONTAINER_CHANNEL)
				 || !aac->fsa_dev[sdev_id(dev)].valid) अणु
					++num_lsu;
				पूर्ण
			पूर्ण अन्यथा अणु
				++num_one;
			पूर्ण
		पूर्ण

		अगर (num_lsu == 0)
			++num_lsu;

		depth = (host->can_queue - num_one) / num_lsu;

		अगर (sdev_channel(sdev) != NATIVE_CHANNEL)
			जाओ common_config;

		set_qd_dev_type = true;

	पूर्ण

common_config:

	/*
	 * Check अगर SATA drive
	 */
	अगर (set_qd_dev_type) अणु
		अगर (म_भेदन(sdev->venकरोr, "ATA", 3) == 0)
			depth = 32;
		अन्यथा
			depth = 64;
	पूर्ण

	/*
	 * Firmware has an inभागidual device recovery समय typically
	 * of 35 seconds, give us a margin. Thor devices can take दीर्घer in
	 * error recovery, hence dअगरferent value.
	 */
	अगर (set_समयout) अणु
		समयout = aac->sa_firmware ? AAC_SA_TIMEOUT : AAC_ARC_TIMEOUT;
		blk_queue_rq_समयout(sdev->request_queue, समयout * HZ);
	पूर्ण

	अगर (depth > 256)
		depth = 256;
	अन्यथा अगर (depth < 1)
		depth = 1;

	scsi_change_queue_depth(sdev, depth);

	sdev->tagged_supported = 1;

	वापस 0;
पूर्ण

/**
 *	aac_change_queue_depth		-	alter queue depths
 *	@sdev:	SCSI device we are considering
 *	@depth:	desired queue depth
 *
 *	Alters queue depths क्रम target device based on the host adapter's
 *	total capacity and the queue depth supported by the target device.
 */

अटल पूर्णांक aac_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक depth)
अणु
	काष्ठा aac_dev *aac = (काष्ठा aac_dev *)(sdev->host->hostdata);
	पूर्णांक chn, tid, is_native_device = 0;

	chn = aac_logical_to_phys(sdev_channel(sdev));
	tid = sdev_id(sdev);
	अगर (chn < AAC_MAX_BUSES && tid < AAC_MAX_TARGETS &&
		aac->hba_map[chn][tid].devtype == AAC_DEVTYPE_NATIVE_RAW)
		is_native_device = 1;

	अगर (sdev->tagged_supported && (sdev->type == TYPE_DISK) &&
	    (sdev_channel(sdev) == CONTAINER_CHANNEL)) अणु
		काष्ठा scsi_device * dev;
		काष्ठा Scsi_Host *host = sdev->host;
		अचिन्हित num = 0;

		__shost_क्रम_each_device(dev, host) अणु
			अगर (dev->tagged_supported && (dev->type == TYPE_DISK) &&
			    (sdev_channel(dev) == CONTAINER_CHANNEL))
				++num;
			++num;
		पूर्ण
		अगर (num >= host->can_queue)
			num = host->can_queue - 1;
		अगर (depth > (host->can_queue - num))
			depth = host->can_queue - num;
		अगर (depth > 256)
			depth = 256;
		अन्यथा अगर (depth < 2)
			depth = 2;
		वापस scsi_change_queue_depth(sdev, depth);
	पूर्ण अन्यथा अगर (is_native_device) अणु
		scsi_change_queue_depth(sdev, aac->hba_map[chn][tid].qd_limit);
	पूर्ण अन्यथा अणु
		scsi_change_queue_depth(sdev, 1);
	पूर्ण
	वापस sdev->queue_depth;
पूर्ण

अटल sमाप_प्रकार aac_show_raid_level(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा aac_dev *aac = (काष्ठा aac_dev *)(sdev->host->hostdata);
	अगर (sdev_channel(sdev) != CONTAINER_CHANNEL)
		वापस snम_लिखो(buf, PAGE_SIZE, sdev->no_uld_attach
		  ? "Hidden\n" :
		  ((aac->jbod && (sdev->type == TYPE_DISK)) ? "JBOD\n" : ""));
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n",
	  get_container_type(aac->fsa_dev[sdev_id(sdev)].type));
पूर्ण

अटल काष्ठा device_attribute aac_raid_level_attr = अणु
	.attr = अणु
		.name = "level",
		.mode = S_IRUGO,
	पूर्ण,
	.show = aac_show_raid_level
पूर्ण;

अटल sमाप_प्रकार aac_show_unique_id(काष्ठा device *dev,
	     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा aac_dev *aac = (काष्ठा aac_dev *)(sdev->host->hostdata);
	अचिन्हित अक्षर sn[16];

	स_रखो(sn, 0, माप(sn));

	अगर (sdev_channel(sdev) == CONTAINER_CHANNEL)
		स_नकल(sn, aac->fsa_dev[sdev_id(sdev)].identअगरier, माप(sn));

	वापस snम_लिखो(buf, 16 * 2 + 2,
		"%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
		sn[0], sn[1], sn[2], sn[3],
		sn[4], sn[5], sn[6], sn[7],
		sn[8], sn[9], sn[10], sn[11],
		sn[12], sn[13], sn[14], sn[15]);
पूर्ण

अटल काष्ठा device_attribute aac_unique_id_attr = अणु
	.attr = अणु
		.name = "unique_id",
		.mode = 0444,
	पूर्ण,
	.show = aac_show_unique_id
पूर्ण;



अटल काष्ठा device_attribute *aac_dev_attrs[] = अणु
	&aac_raid_level_attr,
	&aac_unique_id_attr,
	शून्य,
पूर्ण;

अटल पूर्णांक aac_ioctl(काष्ठा scsi_device *sdev, अचिन्हित पूर्णांक cmd,
		     व्योम __user *arg)
अणु
	पूर्णांक retval;
	काष्ठा aac_dev *dev = (काष्ठा aac_dev *)sdev->host->hostdata;
	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;
	retval = aac_adapter_check_health(dev);
	अगर (retval)
		वापस -EBUSY;
	वापस aac_करो_ioctl(dev, cmd, arg);
पूर्ण

काष्ठा fib_count_data अणु
	पूर्णांक mlcnt;
	पूर्णांक llcnt;
	पूर्णांक ehcnt;
	पूर्णांक fwcnt;
	पूर्णांक krlcnt;
पूर्ण;

अटल bool fib_count_iter(काष्ठा scsi_cmnd *scmnd, व्योम *data, bool reserved)
अणु
	काष्ठा fib_count_data *fib_count = data;

	चयन (scmnd->SCp.phase) अणु
	हाल AAC_OWNER_FIRMWARE:
		fib_count->fwcnt++;
		अवरोध;
	हाल AAC_OWNER_ERROR_HANDLER:
		fib_count->ehcnt++;
		अवरोध;
	हाल AAC_OWNER_LOWLEVEL:
		fib_count->llcnt++;
		अवरोध;
	हाल AAC_OWNER_MIDLEVEL:
		fib_count->mlcnt++;
		अवरोध;
	शेष:
		fib_count->krlcnt++;
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

/* Called during SCSI EH, so we करोn't need to block requests */
अटल पूर्णांक get_num_of_incomplete_fibs(काष्ठा aac_dev *aac)
अणु
	काष्ठा Scsi_Host *shost = aac->scsi_host_ptr;
	काष्ठा device *ctrl_dev;
	काष्ठा fib_count_data fcnt = अणु पूर्ण;

	scsi_host_busy_iter(shost, fib_count_iter, &fcnt);

	ctrl_dev = &aac->pdev->dev;

	dev_info(ctrl_dev, "outstanding cmd: midlevel-%d\n", fcnt.mlcnt);
	dev_info(ctrl_dev, "outstanding cmd: lowlevel-%d\n", fcnt.llcnt);
	dev_info(ctrl_dev, "outstanding cmd: error handler-%d\n", fcnt.ehcnt);
	dev_info(ctrl_dev, "outstanding cmd: firmware-%d\n", fcnt.fwcnt);
	dev_info(ctrl_dev, "outstanding cmd: kernel-%d\n", fcnt.krlcnt);

	वापस fcnt.mlcnt + fcnt.llcnt + fcnt.ehcnt + fcnt.fwcnt;
पूर्ण

अटल पूर्णांक aac_eh_पात(काष्ठा scsi_cmnd* cmd)
अणु
	काष्ठा scsi_device * dev = cmd->device;
	काष्ठा Scsi_Host * host = dev->host;
	काष्ठा aac_dev * aac = (काष्ठा aac_dev *)host->hostdata;
	पूर्णांक count, found;
	u32 bus, cid;
	पूर्णांक ret = FAILED;

	अगर (aac_adapter_check_health(aac))
		वापस ret;

	bus = aac_logical_to_phys(scmd_channel(cmd));
	cid = scmd_id(cmd);
	अगर (aac->hba_map[bus][cid].devtype == AAC_DEVTYPE_NATIVE_RAW) अणु
		काष्ठा fib *fib;
		काष्ठा aac_hba_पंचांग_req *पंचांगf;
		पूर्णांक status;
		u64 address;

		pr_err("%s: Host adapter abort request (%d,%d,%d,%d)\n",
		 AAC_DRIVERNAME,
		 host->host_no, sdev_channel(dev), sdev_id(dev), (पूर्णांक)dev->lun);

		found = 0;
		क्रम (count = 0; count < (host->can_queue + AAC_NUM_MGT_FIB); ++count) अणु
			fib = &aac->fibs[count];
			अगर (*(u8 *)fib->hw_fib_va != 0 &&
				(fib->flags & FIB_CONTEXT_FLAG_NATIVE_HBA) &&
				(fib->callback_data == cmd)) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!found)
			वापस ret;

		/* start a HBA_TMF_ABORT_TASK TMF request */
		fib = aac_fib_alloc(aac);
		अगर (!fib)
			वापस ret;

		पंचांगf = (काष्ठा aac_hba_पंचांग_req *)fib->hw_fib_va;
		स_रखो(पंचांगf, 0, माप(*पंचांगf));
		पंचांगf->पंचांगf = HBA_TMF_ABORT_TASK;
		पंचांगf->it_nexus = aac->hba_map[bus][cid].rmw_nexus;
		पंचांगf->lun[1] = cmd->device->lun;

		address = (u64)fib->hw_error_pa;
		पंचांगf->error_ptr_hi = cpu_to_le32((u32)(address >> 32));
		पंचांगf->error_ptr_lo = cpu_to_le32((u32)(address & 0xffffffff));
		पंचांगf->error_length = cpu_to_le32(FW_ERROR_BUFFER_SIZE);

		fib->hbacmd_size = माप(*पंचांगf);
		cmd->SCp.sent_command = 0;

		status = aac_hba_send(HBA_IU_TYPE_SCSI_TM_REQ, fib,
				  (fib_callback) aac_hba_callback,
				  (व्योम *) cmd);
		अगर (status != -EINPROGRESS) अणु
			aac_fib_complete(fib);
			aac_fib_मुक्त(fib);
			वापस ret;
		पूर्ण
		/* Wait up to 15 secs क्रम completion */
		क्रम (count = 0; count < 15; ++count) अणु
			अगर (cmd->SCp.sent_command) अणु
				ret = SUCCESS;
				अवरोध;
			पूर्ण
			msleep(1000);
		पूर्ण

		अगर (ret != SUCCESS)
			pr_err("%s: Host adapter abort request timed out\n",
			AAC_DRIVERNAME);
	पूर्ण अन्यथा अणु
		pr_err(
			"%s: Host adapter abort request.\n"
			"%s: Outstanding commands on (%d,%d,%d,%d):\n",
			AAC_DRIVERNAME, AAC_DRIVERNAME,
			host->host_no, sdev_channel(dev), sdev_id(dev),
			(पूर्णांक)dev->lun);
		चयन (cmd->cmnd[0]) अणु
		हाल SERVICE_ACTION_IN_16:
			अगर (!(aac->raw_io_पूर्णांकerface) ||
			    !(aac->raw_io_64) ||
			    ((cmd->cmnd[1] & 0x1f) != SAI_READ_CAPACITY_16))
				अवरोध;
			fallthrough;
		हाल INQUIRY:
		हाल READ_CAPACITY:
			/*
			 * Mark associated FIB to not complete,
			 * eh handler करोes this
			 */
			क्रम (count = 0;
				count < (host->can_queue + AAC_NUM_MGT_FIB);
				++count) अणु
				काष्ठा fib *fib = &aac->fibs[count];

				अगर (fib->hw_fib_va->header.XferState &&
				(fib->flags & FIB_CONTEXT_FLAG) &&
				(fib->callback_data == cmd)) अणु
					fib->flags |=
						FIB_CONTEXT_FLAG_TIMED_OUT;
					cmd->SCp.phase =
						AAC_OWNER_ERROR_HANDLER;
					ret = SUCCESS;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल TEST_UNIT_READY:
			/*
			 * Mark associated FIB to not complete,
			 * eh handler करोes this
			 */
			क्रम (count = 0;
				count < (host->can_queue + AAC_NUM_MGT_FIB);
				++count) अणु
				काष्ठा scsi_cmnd *command;
				काष्ठा fib *fib = &aac->fibs[count];

				command = fib->callback_data;

				अगर ((fib->hw_fib_va->header.XferState &
					cpu_to_le32
					(Async | NoResponseExpected)) &&
					(fib->flags & FIB_CONTEXT_FLAG) &&
					((command)) &&
					(command->device == cmd->device)) अणु
					fib->flags |=
						FIB_CONTEXT_FLAG_TIMED_OUT;
					command->SCp.phase =
						AAC_OWNER_ERROR_HANDLER;
					अगर (command == cmd)
						ret = SUCCESS;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल u8 aac_eh_पंचांगf_lun_reset_fib(काष्ठा aac_hba_map_info *info,
				   काष्ठा fib *fib, u64 पंचांगf_lun)
अणु
	काष्ठा aac_hba_पंचांग_req *पंचांगf;
	u64 address;

	/* start a HBA_TMF_LUN_RESET TMF request */
	पंचांगf = (काष्ठा aac_hba_पंचांग_req *)fib->hw_fib_va;
	स_रखो(पंचांगf, 0, माप(*पंचांगf));
	पंचांगf->पंचांगf = HBA_TMF_LUN_RESET;
	पंचांगf->it_nexus = info->rmw_nexus;
	पूर्णांक_to_scsilun(पंचांगf_lun, (काष्ठा scsi_lun *)पंचांगf->lun);

	address = (u64)fib->hw_error_pa;
	पंचांगf->error_ptr_hi = cpu_to_le32
		((u32)(address >> 32));
	पंचांगf->error_ptr_lo = cpu_to_le32
		((u32)(address & 0xffffffff));
	पंचांगf->error_length = cpu_to_le32(FW_ERROR_BUFFER_SIZE);
	fib->hbacmd_size = माप(*पंचांगf);

	वापस HBA_IU_TYPE_SCSI_TM_REQ;
पूर्ण

अटल u8 aac_eh_पंचांगf_hard_reset_fib(काष्ठा aac_hba_map_info *info,
				    काष्ठा fib *fib)
अणु
	काष्ठा aac_hba_reset_req *rst;
	u64 address;

	/* alपढ़ोy tried, start a hard reset now */
	rst = (काष्ठा aac_hba_reset_req *)fib->hw_fib_va;
	स_रखो(rst, 0, माप(*rst));
	rst->it_nexus = info->rmw_nexus;

	address = (u64)fib->hw_error_pa;
	rst->error_ptr_hi = cpu_to_le32((u32)(address >> 32));
	rst->error_ptr_lo = cpu_to_le32((u32)(address & 0xffffffff));
	rst->error_length = cpu_to_le32(FW_ERROR_BUFFER_SIZE);
	fib->hbacmd_size = माप(*rst);

       वापस HBA_IU_TYPE_SATA_REQ;
पूर्ण

अटल व्योम aac_पंचांगf_callback(व्योम *context, काष्ठा fib *fibptr)
अणु
	काष्ठा aac_hba_resp *err =
		&((काष्ठा aac_native_hba *)fibptr->hw_fib_va)->resp.err;
	काष्ठा aac_hba_map_info *info = context;
	पूर्णांक res;

	चयन (err->service_response) अणु
	हाल HBA_RESP_SVCRES_TMF_REJECTED:
		res = -1;
		अवरोध;
	हाल HBA_RESP_SVCRES_TMF_LUN_INVALID:
		res = 0;
		अवरोध;
	हाल HBA_RESP_SVCRES_TMF_COMPLETE:
	हाल HBA_RESP_SVCRES_TMF_SUCCEEDED:
		res = 0;
		अवरोध;
	शेष:
		res = -2;
		अवरोध;
	पूर्ण
	aac_fib_complete(fibptr);

	info->reset_state = res;
पूर्ण

/*
 *	aac_eh_dev_reset	- Device reset command handling
 *	@scsi_cmd:	SCSI command block causing the reset
 *
 */
अटल पूर्णांक aac_eh_dev_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_device * dev = cmd->device;
	काष्ठा Scsi_Host * host = dev->host;
	काष्ठा aac_dev * aac = (काष्ठा aac_dev *)host->hostdata;
	काष्ठा aac_hba_map_info *info;
	पूर्णांक count;
	u32 bus, cid;
	काष्ठा fib *fib;
	पूर्णांक ret = FAILED;
	पूर्णांक status;
	u8 command;

	bus = aac_logical_to_phys(scmd_channel(cmd));
	cid = scmd_id(cmd);

	अगर (bus >= AAC_MAX_BUSES || cid >= AAC_MAX_TARGETS)
		वापस FAILED;

	info = &aac->hba_map[bus][cid];

	अगर (!(info->devtype == AAC_DEVTYPE_NATIVE_RAW &&
	 !(info->reset_state > 0)))
		वापस FAILED;

	pr_err("%s: Host device reset request. SCSI hang ?\n",
	       AAC_DRIVERNAME);

	fib = aac_fib_alloc(aac);
	अगर (!fib)
		वापस ret;

	/* start a HBA_TMF_LUN_RESET TMF request */
	command = aac_eh_पंचांगf_lun_reset_fib(info, fib, dev->lun);

	info->reset_state = 1;

	status = aac_hba_send(command, fib,
			      (fib_callback) aac_पंचांगf_callback,
			      (व्योम *) info);
	अगर (status != -EINPROGRESS) अणु
		info->reset_state = 0;
		aac_fib_complete(fib);
		aac_fib_मुक्त(fib);
		वापस ret;
	पूर्ण
	/* Wait up to 15 seconds क्रम completion */
	क्रम (count = 0; count < 15; ++count) अणु
		अगर (info->reset_state == 0) अणु
			ret = info->reset_state == 0 ? SUCCESS : FAILED;
			अवरोध;
		पूर्ण
		msleep(1000);
	पूर्ण

	वापस ret;
पूर्ण

/*
 *	aac_eh_target_reset	- Target reset command handling
 *	@scsi_cmd:	SCSI command block causing the reset
 *
 */
अटल पूर्णांक aac_eh_target_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_device * dev = cmd->device;
	काष्ठा Scsi_Host * host = dev->host;
	काष्ठा aac_dev * aac = (काष्ठा aac_dev *)host->hostdata;
	काष्ठा aac_hba_map_info *info;
	पूर्णांक count;
	u32 bus, cid;
	पूर्णांक ret = FAILED;
	काष्ठा fib *fib;
	पूर्णांक status;
	u8 command;

	bus = aac_logical_to_phys(scmd_channel(cmd));
	cid = scmd_id(cmd);

	अगर (bus >= AAC_MAX_BUSES || cid >= AAC_MAX_TARGETS)
		वापस FAILED;

	info = &aac->hba_map[bus][cid];

	अगर (!(info->devtype == AAC_DEVTYPE_NATIVE_RAW &&
	 !(info->reset_state > 0)))
		वापस FAILED;

	pr_err("%s: Host target reset request. SCSI hang ?\n",
	       AAC_DRIVERNAME);

	fib = aac_fib_alloc(aac);
	अगर (!fib)
		वापस ret;


	/* alपढ़ोy tried, start a hard reset now */
	command = aac_eh_पंचांगf_hard_reset_fib(info, fib);

	info->reset_state = 2;

	status = aac_hba_send(command, fib,
			      (fib_callback) aac_पंचांगf_callback,
			      (व्योम *) info);

	अगर (status != -EINPROGRESS) अणु
		info->reset_state = 0;
		aac_fib_complete(fib);
		aac_fib_मुक्त(fib);
		वापस ret;
	पूर्ण

	/* Wait up to 15 seconds क्रम completion */
	क्रम (count = 0; count < 15; ++count) अणु
		अगर (info->reset_state <= 0) अणु
			ret = info->reset_state == 0 ? SUCCESS : FAILED;
			अवरोध;
		पूर्ण
		msleep(1000);
	पूर्ण

	वापस ret;
पूर्ण

/*
 *	aac_eh_bus_reset	- Bus reset command handling
 *	@scsi_cmd:	SCSI command block causing the reset
 *
 */
अटल पूर्णांक aac_eh_bus_reset(काष्ठा scsi_cmnd* cmd)
अणु
	काष्ठा scsi_device * dev = cmd->device;
	काष्ठा Scsi_Host * host = dev->host;
	काष्ठा aac_dev * aac = (काष्ठा aac_dev *)host->hostdata;
	पूर्णांक count;
	u32 cmd_bus;
	पूर्णांक status = 0;


	cmd_bus = aac_logical_to_phys(scmd_channel(cmd));
	/* Mark the assoc. FIB to not complete, eh handler करोes this */
	क्रम (count = 0; count < (host->can_queue + AAC_NUM_MGT_FIB); ++count) अणु
		काष्ठा fib *fib = &aac->fibs[count];

		अगर (fib->hw_fib_va->header.XferState &&
		    (fib->flags & FIB_CONTEXT_FLAG) &&
		    (fib->flags & FIB_CONTEXT_FLAG_SCSI_CMD)) अणु
			काष्ठा aac_hba_map_info *info;
			u32 bus, cid;

			cmd = (काष्ठा scsi_cmnd *)fib->callback_data;
			bus = aac_logical_to_phys(scmd_channel(cmd));
			अगर (bus != cmd_bus)
				जारी;
			cid = scmd_id(cmd);
			info = &aac->hba_map[bus][cid];
			अगर (bus >= AAC_MAX_BUSES || cid >= AAC_MAX_TARGETS ||
			    info->devtype != AAC_DEVTYPE_NATIVE_RAW) अणु
				fib->flags |= FIB_CONTEXT_FLAG_EH_RESET;
				cmd->SCp.phase = AAC_OWNER_ERROR_HANDLER;
			पूर्ण
		पूर्ण
	पूर्ण

	pr_err("%s: Host bus reset request. SCSI hang ?\n", AAC_DRIVERNAME);

	/*
	 * Check the health of the controller
	 */
	status = aac_adapter_check_health(aac);
	अगर (status)
		dev_err(&aac->pdev->dev, "Adapter health - %d\n", status);

	count = get_num_of_incomplete_fibs(aac);
	वापस (count == 0) ? SUCCESS : FAILED;
पूर्ण

/*
 *	aac_eh_host_reset	- Host reset command handling
 *	@scsi_cmd:	SCSI command block causing the reset
 *
 */
अटल पूर्णांक aac_eh_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_device * dev = cmd->device;
	काष्ठा Scsi_Host * host = dev->host;
	काष्ठा aac_dev * aac = (काष्ठा aac_dev *)host->hostdata;
	पूर्णांक ret = FAILED;
	__le32 supported_options2 = 0;
	bool is_mu_reset;
	bool is_ignore_reset;
	bool is_करोorbell_reset;

	/*
	 * Check अगर reset is supported by the firmware
	 */
	supported_options2 = aac->supplement_adapter_info.supported_options2;
	is_mu_reset = supported_options2 & AAC_OPTION_MU_RESET;
	is_करोorbell_reset = supported_options2 & AAC_OPTION_DOORBELL_RESET;
	is_ignore_reset = supported_options2 & AAC_OPTION_IGNORE_RESET;
	/*
	 * This adapter needs a blind reset, only करो so क्रम
	 * Adapters that support a रेजिस्टर, instead of a commanded,
	 * reset.
	 */
	अगर ((is_mu_reset || is_करोorbell_reset)
	 && aac_check_reset
	 && (aac_check_reset != -1 || !is_ignore_reset)) अणु
		/* Bypass रुको क्रम command quiesce */
		अगर (aac_reset_adapter(aac, 2, IOP_HWSOFT_RESET) == 0)
			ret = SUCCESS;
	पूर्ण
	/*
	 * Reset EH state
	 */
	अगर (ret == SUCCESS) अणु
		पूर्णांक bus, cid;
		काष्ठा aac_hba_map_info *info;

		क्रम (bus = 0; bus < AAC_MAX_BUSES; bus++) अणु
			क्रम (cid = 0; cid < AAC_MAX_TARGETS; cid++) अणु
				info = &aac->hba_map[bus][cid];
				अगर (info->devtype == AAC_DEVTYPE_NATIVE_RAW)
					info->reset_state = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 *	aac_cfg_खोलो		-	खोलो a configuration file
 *	@inode: inode being खोलोed
 *	@file: file handle attached
 *
 *	Called when the configuration device is खोलोed. Does the needed
 *	set up on the handle and then वापसs
 *
 *	Bugs: This needs extending to check a given adapter is present
 *	so we can support hot plugging, and to ref count adapters.
 */

अटल पूर्णांक aac_cfg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा aac_dev *aac;
	अचिन्हित minor_number = iminor(inode);
	पूर्णांक err = -ENODEV;

	mutex_lock(&aac_mutex);  /* BKL pushकरोwn: nothing अन्यथा protects this list */
	list_क्रम_each_entry(aac, &aac_devices, entry) अणु
		अगर (aac->id == minor_number) अणु
			file->निजी_data = aac;
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&aac_mutex);

	वापस err;
पूर्ण

/**
 *	aac_cfg_ioctl		-	AAC configuration request
 *	@file: file handle
 *	@cmd: ioctl command code
 *	@arg: argument
 *
 *	Handles a configuration ioctl. Currently this involves wrapping it
 *	up and feeding it पूर्णांकo the nasty winकरोwsalike glue layer.
 *
 *	Bugs: Needs locking against parallel ioctls lower करोwn
 *	Bugs: Needs to handle hot plugging
 */

अटल दीर्घ aac_cfg_ioctl(काष्ठा file *file,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा aac_dev *aac = (काष्ठा aac_dev *)file->निजी_data;

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	वापस aac_करो_ioctl(aac, cmd, (व्योम __user *)arg);
पूर्ण

अटल sमाप_प्रकार aac_show_model(काष्ठा device *device,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aac_dev *dev = (काष्ठा aac_dev*)class_to_shost(device)->hostdata;
	पूर्णांक len;

	अगर (dev->supplement_adapter_info.adapter_type_text[0]) अणु
		अक्षर *cp = dev->supplement_adapter_info.adapter_type_text;
		जबतक (*cp && *cp != ' ')
			++cp;
		जबतक (*cp == ' ')
			++cp;
		len = snम_लिखो(buf, PAGE_SIZE, "%s\n", cp);
	पूर्ण अन्यथा
		len = snम_लिखो(buf, PAGE_SIZE, "%s\n",
		  aac_drivers[dev->cardtype].model);
	वापस len;
पूर्ण

अटल sमाप_प्रकार aac_show_venकरोr(काष्ठा device *device,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aac_dev *dev = (काष्ठा aac_dev*)class_to_shost(device)->hostdata;
	काष्ठा aac_supplement_adapter_info *sup_adap_info;
	पूर्णांक len;

	sup_adap_info = &dev->supplement_adapter_info;
	अगर (sup_adap_info->adapter_type_text[0]) अणु
		अक्षर *cp = sup_adap_info->adapter_type_text;
		जबतक (*cp && *cp != ' ')
			++cp;
		len = snम_लिखो(buf, PAGE_SIZE, "%.*s\n",
			(पूर्णांक)(cp - (अक्षर *)sup_adap_info->adapter_type_text),
					sup_adap_info->adapter_type_text);
	पूर्ण अन्यथा
		len = snम_लिखो(buf, PAGE_SIZE, "%s\n",
			aac_drivers[dev->cardtype].vname);
	वापस len;
पूर्ण

अटल sमाप_प्रकार aac_show_flags(काष्ठा device *cdev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक len = 0;
	काष्ठा aac_dev *dev = (काष्ठा aac_dev*)class_to_shost(cdev)->hostdata;

	अगर (nblank(dprपूर्णांकk(x)))
		len = snम_लिखो(buf, PAGE_SIZE, "dprintk\n");
#अगर_घोषित AAC_DETAILED_STATUS_INFO
	len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			 "AAC_DETAILED_STATUS_INFO\n");
#पूर्ण_अगर
	अगर (dev->raw_io_पूर्णांकerface && dev->raw_io_64)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
				 "SAI_READ_CAPACITY_16\n");
	अगर (dev->jbod)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
				 "SUPPORTED_JBOD\n");
	अगर (dev->supplement_adapter_info.supported_options2 &
		AAC_OPTION_POWER_MANAGEMENT)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
				 "SUPPORTED_POWER_MANAGEMENT\n");
	अगर (dev->msi)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "PCI_HAS_MSI\n");
	वापस len;
पूर्ण

अटल sमाप_प्रकार aac_show_kernel_version(काष्ठा device *device,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा aac_dev *dev = (काष्ठा aac_dev*)class_to_shost(device)->hostdata;
	पूर्णांक len, पंचांगp;

	पंचांगp = le32_to_cpu(dev->adapter_info.kernelrev);
	len = snम_लिखो(buf, PAGE_SIZE, "%d.%d-%d[%d]\n",
	  पंचांगp >> 24, (पंचांगp >> 16) & 0xff, पंचांगp & 0xff,
	  le32_to_cpu(dev->adapter_info.kernelbuild));
	वापस len;
पूर्ण

अटल sमाप_प्रकार aac_show_monitor_version(काष्ठा device *device,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा aac_dev *dev = (काष्ठा aac_dev*)class_to_shost(device)->hostdata;
	पूर्णांक len, पंचांगp;

	पंचांगp = le32_to_cpu(dev->adapter_info.monitorrev);
	len = snम_लिखो(buf, PAGE_SIZE, "%d.%d-%d[%d]\n",
	  पंचांगp >> 24, (पंचांगp >> 16) & 0xff, पंचांगp & 0xff,
	  le32_to_cpu(dev->adapter_info.monitorbuild));
	वापस len;
पूर्ण

अटल sमाप_प्रकार aac_show_bios_version(काष्ठा device *device,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा aac_dev *dev = (काष्ठा aac_dev*)class_to_shost(device)->hostdata;
	पूर्णांक len, पंचांगp;

	पंचांगp = le32_to_cpu(dev->adapter_info.biosrev);
	len = snम_लिखो(buf, PAGE_SIZE, "%d.%d-%d[%d]\n",
	  पंचांगp >> 24, (पंचांगp >> 16) & 0xff, पंचांगp & 0xff,
	  le32_to_cpu(dev->adapter_info.biosbuild));
	वापस len;
पूर्ण

अटल sमाप_प्रकार aac_show_driver_version(काष्ठा device *device,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", aac_driver_version);
पूर्ण

अटल sमाप_प्रकार aac_show_serial_number(काष्ठा device *device,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aac_dev *dev = (काष्ठा aac_dev*)class_to_shost(device)->hostdata;
	पूर्णांक len = 0;

	अगर (le32_to_cpu(dev->adapter_info.serial[0]) != 0xBAD0)
		len = snम_लिखो(buf, 16, "%06X\n",
		  le32_to_cpu(dev->adapter_info.serial[0]));
	अगर (len &&
	  !स_भेद(&dev->supplement_adapter_info.mfg_pcba_serial_no[
	    माप(dev->supplement_adapter_info.mfg_pcba_serial_no)-len],
	  buf, len-1))
		len = snम_लिखो(buf, 16, "%.*s\n",
		  (पूर्णांक)माप(dev->supplement_adapter_info.mfg_pcba_serial_no),
		  dev->supplement_adapter_info.mfg_pcba_serial_no);

	वापस min(len, 16);
पूर्ण

अटल sमाप_प्रकार aac_show_max_channel(काष्ठा device *device,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
	  class_to_shost(device)->max_channel);
पूर्ण

अटल sमाप_प्रकार aac_show_max_id(काष्ठा device *device,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
	  class_to_shost(device)->max_id);
पूर्ण

अटल sमाप_प्रकार aac_store_reset_adapter(काष्ठा device *device,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक retval = -EACCES;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस retval;

	retval = aac_reset_adapter(shost_priv(class_to_shost(device)),
					buf[0] == '!', IOP_HWSOFT_RESET);
	अगर (retval >= 0)
		retval = count;

	वापस retval;
पूर्ण

अटल sमाप_प्रकार aac_show_reset_adapter(काष्ठा device *device,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा aac_dev *dev = (काष्ठा aac_dev*)class_to_shost(device)->hostdata;
	पूर्णांक len, पंचांगp;

	पंचांगp = aac_adapter_check_health(dev);
	अगर ((पंचांगp == 0) && dev->in_reset)
		पंचांगp = -EBUSY;
	len = snम_लिखो(buf, PAGE_SIZE, "0x%x\n", पंचांगp);
	वापस len;
पूर्ण

अटल काष्ठा device_attribute aac_model = अणु
	.attr = अणु
		.name = "model",
		.mode = S_IRUGO,
	पूर्ण,
	.show = aac_show_model,
पूर्ण;
अटल काष्ठा device_attribute aac_venकरोr = अणु
	.attr = अणु
		.name = "vendor",
		.mode = S_IRUGO,
	पूर्ण,
	.show = aac_show_venकरोr,
पूर्ण;
अटल काष्ठा device_attribute aac_flags = अणु
	.attr = अणु
		.name = "flags",
		.mode = S_IRUGO,
	पूर्ण,
	.show = aac_show_flags,
पूर्ण;
अटल काष्ठा device_attribute aac_kernel_version = अणु
	.attr = अणु
		.name = "hba_kernel_version",
		.mode = S_IRUGO,
	पूर्ण,
	.show = aac_show_kernel_version,
पूर्ण;
अटल काष्ठा device_attribute aac_monitor_version = अणु
	.attr = अणु
		.name = "hba_monitor_version",
		.mode = S_IRUGO,
	पूर्ण,
	.show = aac_show_monitor_version,
पूर्ण;
अटल काष्ठा device_attribute aac_bios_version = अणु
	.attr = अणु
		.name = "hba_bios_version",
		.mode = S_IRUGO,
	पूर्ण,
	.show = aac_show_bios_version,
पूर्ण;
अटल काष्ठा device_attribute aac_lld_version = अणु
	.attr = अणु
		.name = "driver_version",
		.mode = 0444,
	पूर्ण,
	.show = aac_show_driver_version,
पूर्ण;
अटल काष्ठा device_attribute aac_serial_number = अणु
	.attr = अणु
		.name = "serial_number",
		.mode = S_IRUGO,
	पूर्ण,
	.show = aac_show_serial_number,
पूर्ण;
अटल काष्ठा device_attribute aac_max_channel = अणु
	.attr = अणु
		.name = "max_channel",
		.mode = S_IRUGO,
	पूर्ण,
	.show = aac_show_max_channel,
पूर्ण;
अटल काष्ठा device_attribute aac_max_id = अणु
	.attr = अणु
		.name = "max_id",
		.mode = S_IRUGO,
	पूर्ण,
	.show = aac_show_max_id,
पूर्ण;
अटल काष्ठा device_attribute aac_reset = अणु
	.attr = अणु
		.name = "reset_host",
		.mode = S_IWUSR|S_IRUGO,
	पूर्ण,
	.store = aac_store_reset_adapter,
	.show = aac_show_reset_adapter,
पूर्ण;

अटल काष्ठा device_attribute *aac_attrs[] = अणु
	&aac_model,
	&aac_venकरोr,
	&aac_flags,
	&aac_kernel_version,
	&aac_monitor_version,
	&aac_bios_version,
	&aac_lld_version,
	&aac_serial_number,
	&aac_max_channel,
	&aac_max_id,
	&aac_reset,
	शून्य
पूर्ण;

sमाप_प्रकार aac_get_serial_number(काष्ठा device *device, अक्षर *buf)
अणु
	वापस aac_show_serial_number(device, &aac_serial_number, buf);
पूर्ण

अटल स्थिर काष्ठा file_operations aac_cfg_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= aac_cfg_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl   = aac_cfg_ioctl,
#पूर्ण_अगर
	.खोलो		= aac_cfg_खोलो,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा aac_driver_ढाँचा = अणु
	.module				= THIS_MODULE,
	.name				= "AAC",
	.proc_name			= AAC_DRIVERNAME,
	.info				= aac_info,
	.ioctl				= aac_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl			= aac_ioctl,
#पूर्ण_अगर
	.queuecommand			= aac_queuecommand,
	.bios_param			= aac_biosparm,
	.shost_attrs			= aac_attrs,
	.slave_configure		= aac_slave_configure,
	.change_queue_depth		= aac_change_queue_depth,
	.sdev_attrs			= aac_dev_attrs,
	.eh_पात_handler		= aac_eh_पात,
	.eh_device_reset_handler	= aac_eh_dev_reset,
	.eh_target_reset_handler	= aac_eh_target_reset,
	.eh_bus_reset_handler		= aac_eh_bus_reset,
	.eh_host_reset_handler		= aac_eh_host_reset,
	.can_queue			= AAC_NUM_IO_FIB,
	.this_id			= MAXIMUM_NUM_CONTAINERS,
	.sg_tablesize			= 16,
	.max_sectors			= 128,
#अगर (AAC_NUM_IO_FIB > 256)
	.cmd_per_lun			= 256,
#अन्यथा
	.cmd_per_lun			= AAC_NUM_IO_FIB,
#पूर्ण_अगर
	.emulated			= 1,
	.no_ग_लिखो_same			= 1,
पूर्ण;

अटल व्योम __aac_shutकरोwn(काष्ठा aac_dev * aac)
अणु
	पूर्णांक i;

	mutex_lock(&aac->ioctl_mutex);
	aac->adapter_shutकरोwn = 1;
	mutex_unlock(&aac->ioctl_mutex);

	अगर (aac->aअगर_thपढ़ो) अणु
		पूर्णांक i;
		/* Clear out events first */
		क्रम (i = 0; i < (aac->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB); i++) अणु
			काष्ठा fib *fib = &aac->fibs[i];
			अगर (!(fib->hw_fib_va->header.XferState & cpu_to_le32(NoResponseExpected | Async)) &&
			    (fib->hw_fib_va->header.XferState & cpu_to_le32(ResponseExpected)))
				complete(&fib->event_रुको);
		पूर्ण
		kthपढ़ो_stop(aac->thपढ़ो);
		aac->thपढ़ो = शून्य;
	पूर्ण

	aac_send_shutकरोwn(aac);

	aac_adapter_disable_पूर्णांक(aac);

	अगर (aac_is_src(aac)) अणु
		अगर (aac->max_msix > 1) अणु
			क्रम (i = 0; i < aac->max_msix; i++) अणु
				मुक्त_irq(pci_irq_vector(aac->pdev, i),
					 &(aac->aac_msix[i]));
			पूर्ण
		पूर्ण अन्यथा अणु
			मुक्त_irq(aac->pdev->irq,
				 &(aac->aac_msix[0]));
		पूर्ण
	पूर्ण अन्यथा अणु
		मुक्त_irq(aac->pdev->irq, aac);
	पूर्ण
	अगर (aac->msi)
		pci_disable_msi(aac->pdev);
	अन्यथा अगर (aac->max_msix > 1)
		pci_disable_msix(aac->pdev);
पूर्ण
अटल व्योम aac_init_अक्षर(व्योम)
अणु
	aac_cfg_major = रेजिस्टर_chrdev(0, "aac", &aac_cfg_fops);
	अगर (aac_cfg_major < 0) अणु
		pr_err("aacraid: unable to register \"aac\" device.\n");
	पूर्ण
पूर्ण

व्योम aac_reinit_aअगर(काष्ठा aac_dev *aac, अचिन्हित पूर्णांक index)
अणु
	/*
	 * Firmware may send a AIF messages very early and the Driver may have
	 * ignored as it is not fully पढ़ोy to process the messages. Send
	 * AIF to firmware so that अगर there are any unprocessed events they
	 * can be processed now.
	 */
	अगर (aac_drivers[index].quirks & AAC_QUIRK_SRC)
		aac_पूर्णांकr_normal(aac, 0, 2, 0, शून्य);

पूर्ण

अटल पूर्णांक aac_probe_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अचिन्हित index = id->driver_data;
	काष्ठा Scsi_Host *shost;
	काष्ठा aac_dev *aac;
	काष्ठा list_head *insert = &aac_devices;
	पूर्णांक error;
	पूर्णांक unique_id = 0;
	u64 dmamask;
	पूर्णांक mask_bits = 0;
	बाह्य पूर्णांक aac_sync_mode;

	/*
	 * Only series 7 needs freset.
	 */
	अगर (pdev->device == PMC_DEVICE_S7)
		pdev->needs_freset = 1;

	list_क्रम_each_entry(aac, &aac_devices, entry) अणु
		अगर (aac->id > unique_id)
			अवरोध;
		insert = &aac->entry;
		unique_id++;
	पूर्ण

	pci_disable_link_state(pdev, PCIE_LINK_STATE_L0S | PCIE_LINK_STATE_L1 |
			       PCIE_LINK_STATE_CLKPM);

	error = pci_enable_device(pdev);
	अगर (error)
		जाओ out;

	अगर (!(aac_drivers[index].quirks & AAC_QUIRK_SRC)) अणु
		error = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (error) अणु
			dev_err(&pdev->dev, "PCI 32 BIT dma mask set failed");
			जाओ out_disable_pdev;
		पूर्ण
	पूर्ण

	/*
	 * If the quirk31 bit is set, the adapter needs adapter
	 * to driver communication memory to be allocated below 2gig
	 */
	अगर (aac_drivers[index].quirks & AAC_QUIRK_31BIT) अणु
		dmamask = DMA_BIT_MASK(31);
		mask_bits = 31;
	पूर्ण अन्यथा अणु
		dmamask = DMA_BIT_MASK(32);
		mask_bits = 32;
	पूर्ण

	error = dma_set_coherent_mask(&pdev->dev, dmamask);
	अगर (error) अणु
		dev_err(&pdev->dev, "PCI %d B consistent dma mask set failed\n"
				, mask_bits);
		जाओ out_disable_pdev;
	पूर्ण

	pci_set_master(pdev);

	shost = scsi_host_alloc(&aac_driver_ढाँचा, माप(काष्ठा aac_dev));
	अगर (!shost) अणु
		error = -ENOMEM;
		जाओ out_disable_pdev;
	पूर्ण

	shost->irq = pdev->irq;
	shost->unique_id = unique_id;
	shost->max_cmd_len = 16;

	अगर (aac_cfg_major == AAC_CHARDEV_NEEDS_REINIT)
		aac_init_अक्षर();

	aac = (काष्ठा aac_dev *)shost->hostdata;
	aac->base_start = pci_resource_start(pdev, 0);
	aac->scsi_host_ptr = shost;
	aac->pdev = pdev;
	aac->name = aac_driver_ढाँचा.name;
	aac->id = shost->unique_id;
	aac->cardtype = index;
	INIT_LIST_HEAD(&aac->entry);

	अगर (aac_reset_devices || reset_devices)
		aac->init_reset = true;

	aac->fibs = kसुस्मृति(shost->can_queue + AAC_NUM_MGT_FIB,
			    माप(काष्ठा fib),
			    GFP_KERNEL);
	अगर (!aac->fibs) अणु
		error = -ENOMEM;
		जाओ out_मुक्त_host;
	पूर्ण

	spin_lock_init(&aac->fib_lock);

	mutex_init(&aac->ioctl_mutex);
	mutex_init(&aac->scan_mutex);

	INIT_DELAYED_WORK(&aac->safw_rescan_work, aac_safw_rescan_worker);
	INIT_DELAYED_WORK(&aac->src_reinit_aअगर_worker,
				aac_src_reinit_aअगर_worker);
	/*
	 *	Map in the रेजिस्टरs from the adapter.
	 */
	aac->base_size = AAC_MIN_FOOTPRINT_SIZE;
	अगर ((*aac_drivers[index].init)(aac)) अणु
		error = -ENODEV;
		जाओ out_unmap;
	पूर्ण

	अगर (aac->sync_mode) अणु
		अगर (aac_sync_mode)
			prपूर्णांकk(KERN_INFO "%s%d: Sync. mode enforced "
				"by driver parameter. This will cause "
				"a significant performance decrease!\n",
				aac->name,
				aac->id);
		अन्यथा
			prपूर्णांकk(KERN_INFO "%s%d: Async. mode not supported "
				"by current driver, sync. mode enforced."
				"\nPlease update driver to get full performance.\n",
				aac->name,
				aac->id);
	पूर्ण

	/*
	 *	Start any kernel thपढ़ोs needed
	 */
	aac->thपढ़ो = kthपढ़ो_run(aac_command_thपढ़ो, aac, AAC_DRIVERNAME);
	अगर (IS_ERR(aac->thपढ़ो)) अणु
		prपूर्णांकk(KERN_ERR "aacraid: Unable to create command thread.\n");
		error = PTR_ERR(aac->thपढ़ो);
		aac->thपढ़ो = शून्य;
		जाओ out_deinit;
	पूर्ण

	aac->maximum_num_channels = aac_drivers[index].channels;
	error = aac_get_adapter_info(aac);
	अगर (error < 0)
		जाओ out_deinit;

	/*
	 * Lets override negotiations and drop the maximum SG limit to 34
	 */
	अगर ((aac_drivers[index].quirks & AAC_QUIRK_34SG) &&
			(shost->sg_tablesize > 34)) अणु
		shost->sg_tablesize = 34;
		shost->max_sectors = (shost->sg_tablesize * 8) + 112;
	पूर्ण

	अगर ((aac_drivers[index].quirks & AAC_QUIRK_17SG) &&
			(shost->sg_tablesize > 17)) अणु
		shost->sg_tablesize = 17;
		shost->max_sectors = (shost->sg_tablesize * 8) + 112;
	पूर्ण

	अगर (aac->adapter_info.options & AAC_OPT_NEW_COMM)
		shost->max_segment_size = shost->max_sectors << 9;
	अन्यथा
		shost->max_segment_size = 65536;

	/*
	 * Firmware म_लिखो works only with older firmware.
	 */
	अगर (aac_drivers[index].quirks & AAC_QUIRK_34SG)
		aac->म_लिखो_enabled = 1;
	अन्यथा
		aac->म_लिखो_enabled = 0;

	/*
	 * max channel will be the physical channels plus 1 भव channel
	 * all containers are on the भव channel 0 (CONTAINER_CHANNEL)
	 * physical channels are address by their actual physical number+1
	 */
	अगर (aac->nondasd_support || expose_physicals || aac->jbod)
		shost->max_channel = aac->maximum_num_channels;
	अन्यथा
		shost->max_channel = 0;

	aac_get_config_status(aac, 0);
	aac_get_containers(aac);
	list_add(&aac->entry, insert);

	shost->max_id = aac->maximum_num_containers;
	अगर (shost->max_id < aac->maximum_num_physicals)
		shost->max_id = aac->maximum_num_physicals;
	अगर (shost->max_id < MAXIMUM_NUM_CONTAINERS)
		shost->max_id = MAXIMUM_NUM_CONTAINERS;
	अन्यथा
		shost->this_id = shost->max_id;

	अगर (!aac->sa_firmware && aac_drivers[index].quirks & AAC_QUIRK_SRC)
		aac_पूर्णांकr_normal(aac, 0, 2, 0, शून्य);

	/*
	 * dmb - we may need to move the setting of these parms somewhere अन्यथा once
	 * we get a fib that can report the actual numbers
	 */
	shost->max_lun = AAC_MAX_LUN;

	pci_set_drvdata(pdev, shost);

	error = scsi_add_host(shost, &pdev->dev);
	अगर (error)
		जाओ out_deinit;

	aac_scan_host(aac);

	pci_enable_pcie_error_reporting(pdev);
	pci_save_state(pdev);

	वापस 0;

 out_deinit:
	__aac_shutकरोwn(aac);
 out_unmap:
	aac_fib_map_मुक्त(aac);
	अगर (aac->comm_addr)
		dma_मुक्त_coherent(&aac->pdev->dev, aac->comm_size,
				  aac->comm_addr, aac->comm_phys);
	kमुक्त(aac->queues);
	aac_adapter_ioremap(aac, 0);
	kमुक्त(aac->fibs);
	kमुक्त(aac->fsa_dev);
 out_मुक्त_host:
	scsi_host_put(shost);
 out_disable_pdev:
	pci_disable_device(pdev);
 out:
	वापस error;
पूर्ण

अटल व्योम aac_release_resources(काष्ठा aac_dev *aac)
अणु
	aac_adapter_disable_पूर्णांक(aac);
	aac_मुक्त_irq(aac);
पूर्ण

अटल पूर्णांक aac_acquire_resources(काष्ठा aac_dev *dev)
अणु
	अचिन्हित दीर्घ status;
	/*
	 *	First clear out all पूर्णांकerrupts.  Then enable the one's that we
	 *	can handle.
	 */
	जबतक (!((status = src_पढ़ोl(dev, MUnit.OMR)) & KERNEL_UP_AND_RUNNING)
		|| status == 0xffffffff)
			msleep(20);

	aac_adapter_disable_पूर्णांक(dev);
	aac_adapter_enable_पूर्णांक(dev);


	अगर (aac_is_src(dev))
		aac_define_पूर्णांक_mode(dev);

	अगर (dev->msi_enabled)
		aac_src_access_devreg(dev, AAC_ENABLE_MSIX);

	अगर (aac_acquire_irq(dev))
		जाओ error_iounmap;

	aac_adapter_enable_पूर्णांक(dev);

	/*max msix may change  after EEH
	 * Re-assign vectors to fibs
	 */
	aac_fib_vector_assign(dev);

	अगर (!dev->sync_mode) अणु
		/* After EEH recovery or suspend resume, max_msix count
		 * may change, thereक्रमe updating in init as well.
		 */
		dev->init->r7.no_of_msix_vectors = cpu_to_le32(dev->max_msix);
		aac_adapter_start(dev);
	पूर्ण
	वापस 0;

error_iounmap:
	वापस -1;

पूर्ण

अटल पूर्णांक __maybe_unused aac_suspend(काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost = dev_get_drvdata(dev);
	काष्ठा aac_dev *aac = (काष्ठा aac_dev *)shost->hostdata;

	scsi_host_block(shost);
	aac_cancel_rescan_worker(aac);
	aac_send_shutकरोwn(aac);

	aac_release_resources(aac);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused aac_resume(काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost = dev_get_drvdata(dev);
	काष्ठा aac_dev *aac = (काष्ठा aac_dev *)shost->hostdata;

	अगर (aac_acquire_resources(aac))
		जाओ fail_device;
	/*
	* reset this flag to unblock ioctl() as it was set at
	* aac_send_shutकरोwn() to block ioctls from upperlayer
	*/
	aac->adapter_shutकरोwn = 0;
	scsi_host_unblock(shost, SDEV_RUNNING);

	वापस 0;

fail_device:
	prपूर्णांकk(KERN_INFO "%s%d: resume failed.\n", aac->name, aac->id);
	scsi_host_put(shost);
	वापस -ENODEV;
पूर्ण

अटल व्योम aac_shutकरोwn(काष्ठा pci_dev *dev)
अणु
	काष्ठा Scsi_Host *shost = pci_get_drvdata(dev);

	scsi_host_block(shost);
	__aac_shutकरोwn((काष्ठा aac_dev *)shost->hostdata);
पूर्ण

अटल व्योम aac_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost = pci_get_drvdata(pdev);
	काष्ठा aac_dev *aac = (काष्ठा aac_dev *)shost->hostdata;

	aac_cancel_rescan_worker(aac);
	scsi_हटाओ_host(shost);

	__aac_shutकरोwn(aac);
	aac_fib_map_मुक्त(aac);
	dma_मुक्त_coherent(&aac->pdev->dev, aac->comm_size, aac->comm_addr,
			  aac->comm_phys);
	kमुक्त(aac->queues);

	aac_adapter_ioremap(aac, 0);

	kमुक्त(aac->fibs);
	kमुक्त(aac->fsa_dev);

	list_del(&aac->entry);
	scsi_host_put(shost);
	pci_disable_device(pdev);
	अगर (list_empty(&aac_devices)) अणु
		unरेजिस्टर_chrdev(aac_cfg_major, "aac");
		aac_cfg_major = AAC_CHARDEV_NEEDS_REINIT;
	पूर्ण
पूर्ण

अटल pci_ers_result_t aac_pci_error_detected(काष्ठा pci_dev *pdev,
					pci_channel_state_t error)
अणु
	काष्ठा Scsi_Host *shost = pci_get_drvdata(pdev);
	काष्ठा aac_dev *aac = shost_priv(shost);

	dev_err(&pdev->dev, "aacraid: PCI error detected %x\n", error);

	चयन (error) अणु
	हाल pci_channel_io_normal:
		वापस PCI_ERS_RESULT_CAN_RECOVER;
	हाल pci_channel_io_frozen:
		aac->handle_pci_error = 1;

		scsi_host_block(shost);
		aac_cancel_rescan_worker(aac);
		scsi_host_complete_all_commands(shost, DID_NO_CONNECT);
		aac_release_resources(aac);

		pci_disable_pcie_error_reporting(pdev);
		aac_adapter_ioremap(aac, 0);

		वापस PCI_ERS_RESULT_NEED_RESET;
	हाल pci_channel_io_perm_failure:
		aac->handle_pci_error = 1;

		scsi_host_complete_all_commands(shost, DID_NO_CONNECT);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t aac_pci_mmio_enabled(काष्ठा pci_dev *pdev)
अणु
	dev_err(&pdev->dev, "aacraid: PCI error - mmio enabled\n");
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t aac_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	dev_err(&pdev->dev, "aacraid: PCI error - slot reset\n");
	pci_restore_state(pdev);
	अगर (pci_enable_device(pdev)) अणु
		dev_warn(&pdev->dev,
			"aacraid: failed to enable slave\n");
		जाओ fail_device;
	पूर्ण

	pci_set_master(pdev);

	अगर (pci_enable_device_mem(pdev)) अणु
		dev_err(&pdev->dev, "pci_enable_device_mem failed\n");
		जाओ fail_device;
	पूर्ण

	वापस PCI_ERS_RESULT_RECOVERED;

fail_device:
	dev_err(&pdev->dev, "aacraid: PCI error - slot reset failed\n");
	वापस PCI_ERS_RESULT_DISCONNECT;
पूर्ण


अटल व्योम aac_pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost = pci_get_drvdata(pdev);
	काष्ठा aac_dev *aac = (काष्ठा aac_dev *)shost_priv(shost);

	अगर (aac_adapter_ioremap(aac, aac->base_size)) अणु

		dev_err(&pdev->dev, "aacraid: ioremap failed\n");
		/* remap failed, go back ... */
		aac->comm_पूर्णांकerface = AAC_COMM_PRODUCER;
		अगर (aac_adapter_ioremap(aac, AAC_MIN_FOOTPRINT_SIZE)) अणु
			dev_warn(&pdev->dev,
				"aacraid: unable to map adapter.\n");

			वापस;
		पूर्ण
	पूर्ण

	msleep(10000);

	aac_acquire_resources(aac);

	/*
	 * reset this flag to unblock ioctl() as it was set
	 * at aac_send_shutकरोwn() to block ioctls from upperlayer
	 */
	aac->adapter_shutकरोwn = 0;
	aac->handle_pci_error = 0;

	scsi_host_unblock(shost, SDEV_RUNNING);
	aac_scan_host(aac);
	pci_save_state(pdev);

	dev_err(&pdev->dev, "aacraid: PCI error - resume\n");
पूर्ण

अटल काष्ठा pci_error_handlers aac_pci_err_handler = अणु
	.error_detected		= aac_pci_error_detected,
	.mmio_enabled		= aac_pci_mmio_enabled,
	.slot_reset		= aac_pci_slot_reset,
	.resume			= aac_pci_resume,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(aac_pm_ops, aac_suspend, aac_resume);

अटल काष्ठा pci_driver aac_pci_driver = अणु
	.name		= AAC_DRIVERNAME,
	.id_table	= aac_pci_tbl,
	.probe		= aac_probe_one,
	.हटाओ		= aac_हटाओ_one,
	.driver.pm      = &aac_pm_ops,
	.shutकरोwn	= aac_shutकरोwn,
	.err_handler    = &aac_pci_err_handler,
पूर्ण;

अटल पूर्णांक __init aac_init(व्योम)
अणु
	पूर्णांक error;

	prपूर्णांकk(KERN_INFO "Adaptec %s driver %s\n",
	  AAC_DRIVERNAME, aac_driver_version);

	error = pci_रेजिस्टर_driver(&aac_pci_driver);
	अगर (error < 0)
		वापस error;

	aac_init_अक्षर();


	वापस 0;
पूर्ण

अटल व्योम __निकास aac_निकास(व्योम)
अणु
	अगर (aac_cfg_major > -1)
		unरेजिस्टर_chrdev(aac_cfg_major, "aac");
	pci_unरेजिस्टर_driver(&aac_pci_driver);
पूर्ण

module_init(aac_init);
module_निकास(aac_निकास);
