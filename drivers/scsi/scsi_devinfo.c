<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/blkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_devinfo.h>

#समावेश "scsi_priv.h"


/*
 * scsi_dev_info_list: काष्ठाure to hold black/white listed devices.
 */
काष्ठा scsi_dev_info_list अणु
	काष्ठा list_head dev_info_list;
	अक्षर venकरोr[8];
	अक्षर model[16];
	blist_flags_t flags;
	अचिन्हित compatible; /* क्रम use with scsi_अटल_device_list entries */
पूर्ण;

काष्ठा scsi_dev_info_list_table अणु
	काष्ठा list_head node;	/* our node क्रम being on the master list */
	काष्ठा list_head scsi_dev_info_list; /* head of dev info list */
	स्थिर अक्षर *name;	/* name of list क्रम /proc (शून्य क्रम global) */
	पूर्णांक key;		/* unique numeric identअगरier */
पूर्ण;


अटल blist_flags_t scsi_शेष_dev_flags;
अटल LIST_HEAD(scsi_dev_info_list);
अटल अक्षर scsi_dev_flags[256];

/*
 * scsi_अटल_device_list: deprecated list of devices that require
 * settings that dअगरfer from the शेष, includes black-listed (broken)
 * devices. The entries here are added to the tail of scsi_dev_info_list
 * via scsi_dev_info_list_init.
 *
 * Do not add to this list, use the command line or proc पूर्णांकerface to add
 * to the scsi_dev_info_list. This table will eventually go away.
 */
अटल काष्ठा अणु
	अक्षर *venकरोr;
	अक्षर *model;
	अक्षर *revision;	/* revision known to be bad, unused */
	blist_flags_t flags;
पूर्ण scsi_अटल_device_list[] __initdata = अणु
	/*
	 * The following devices are known not to tolerate a lun != 0 scan
	 * क्रम one reason or another. Some will respond to all luns,
	 * others will lock up.
	 */
	अणु"Aashima", "IMAGERY 2400SP", "1.03", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"CHINON", "CD-ROM CDS-431", "H42", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"CHINON", "CD-ROM CDS-535", "Q14", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"DENON", "DRD-25X", "V", BLIST_NOLUNपूर्ण,			/* locks up */
	अणु"HITACHI", "DK312C", "CM81", BLIST_NOLUNपूर्ण,	/* responds to all lun */
	अणु"HITACHI", "DK314C", "CR21", BLIST_NOLUNपूर्ण,	/* responds to all lun */
	अणु"IBM", "2104-DU3", शून्य, BLIST_NOLUNपूर्ण,		/* locks up */
	अणु"IBM", "2104-TU3", शून्य, BLIST_NOLUNपूर्ण,		/* locks up */
	अणु"IMS", "CDD521/10", "2.06", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"MAXTOR", "XT-3280", "PR02", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"MAXTOR", "XT-4380S", "B3C", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"MAXTOR", "MXT-1240S", "I1.2", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"MAXTOR", "XT-4170S", "B5A", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"MAXTOR", "XT-8760S", "B7B", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"MEDIAVIS", "RENO CD-ROMX2A", "2.03", BLIST_NOLUNपूर्ण,	/* responds to all lun */
	अणु"MICROTEK", "ScanMakerIII", "2.30", BLIST_NOLUNपूर्ण,	/* responds to all lun */
	अणु"NEC", "CD-ROM DRIVE:841", "1.0", BLIST_NOLUNपूर्ण,/* locks up */
	अणु"PHILIPS", "PCA80SC", "V4-2", BLIST_NOLUNपूर्ण,	/* responds to all lun */
	अणु"RODIME", "RO3000S", "2.33", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"SUN", "SENA", शून्य, BLIST_NOLUNपूर्ण,		/* responds to all luns */
	/*
	 * The following causes a failed REQUEST SENSE on lun 1 क्रम
	 * aha152x controller, which causes SCSI code to reset bus.
	 */
	अणु"SANYO", "CRD-250S", "1.20", BLIST_NOLUNपूर्ण,
	/*
	 * The following causes a failed REQUEST SENSE on lun 1 क्रम
	 * aha152x controller, which causes SCSI code to reset bus.
	 */
	अणु"SEAGATE", "ST157N", "\004|j", BLIST_NOLUNपूर्ण,
	अणु"SEAGATE", "ST296", "921", BLIST_NOLUNपूर्ण,	/* responds to all lun */
	अणु"SEAGATE", "ST1581", "6538", BLIST_NOLUNपूर्ण,	/* responds to all lun */
	अणु"SONY", "CD-ROM CDU-541", "4.3d", BLIST_NOLUNपूर्ण,
	अणु"SONY", "CD-ROM CDU-55S", "1.0i", BLIST_NOLUNपूर्ण,
	अणु"SONY", "CD-ROM CDU-561", "1.7x", BLIST_NOLUNपूर्ण,
	अणु"SONY", "CD-ROM CDU-8012", शून्य, BLIST_NOLUNपूर्ण,
	अणु"SONY", "SDT-5000", "3.17", BLIST_SELECT_NO_ATNपूर्ण,
	अणु"TANDBERG", "TDC 3600", "U07", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"TEAC", "CD-R55S", "1.0H", BLIST_NOLUNपूर्ण,	/* locks up */
	/*
	 * The following causes a failed REQUEST SENSE on lun 1 क्रम
	 * seagate controller, which causes SCSI code to reset bus.
	 */
	अणु"TEAC", "CD-ROM", "1.06", BLIST_NOLUNपूर्ण,
	अणु"TEAC", "MT-2ST/45S2-27", "RV M", BLIST_NOLUNपूर्ण,	/* responds to all lun */
	/*
	 * The following causes a failed REQUEST SENSE on lun 1 क्रम
	 * seagate controller, which causes SCSI code to reset bus.
	 */
	अणु"HP", "C1750A", "3226", BLIST_NOLUNपूर्ण,		/* scanjet iic */
	अणु"HP", "C1790A", शून्य, BLIST_NOLUNपूर्ण,		/* scanjet iip */
	अणु"HP", "C2500A", शून्य, BLIST_NOLUNपूर्ण,		/* scanjet iicx */
	अणु"MEDIAVIS", "CDR-H93MV", "1.31", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"MICROTEK", "ScanMaker II", "5.61", BLIST_NOLUNपूर्ण,	/* responds to all lun */
	अणु"MITSUMI", "CD-R CR-2201CS", "6119", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"NEC", "D3856", "0009", BLIST_NOLUNपूर्ण,
	अणु"QUANTUM", "LPS525S", "3110", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"QUANTUM", "PD1225S", "3110", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"QUANTUM", "FIREBALL ST4.3S", "0F0C", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"RELISYS", "Scorpio", शून्य, BLIST_NOLUNपूर्ण,	/* responds to all lun */
	अणु"SANKYO", "CP525", "6.64", BLIST_NOLUNपूर्ण,	/* causes failed REQ SENSE, extra reset */
	अणु"TEXEL", "CD-ROM", "1.06", BLIST_NOLUN | BLIST_BORKENपूर्ण,
	अणु"transtec", "T5008", "0001", BLIST_NOREPORTLUN पूर्ण,
	अणु"YAMAHA", "CDR100", "1.00", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"YAMAHA", "CDR102", "1.00", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"YAMAHA", "CRW8424S", "1.0", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"YAMAHA", "CRW6416S", "1.0c", BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"", "Scanner", "1.80", BLIST_NOLUNपूर्ण,	/* responds to all lun */

	/*
	 * Other types of devices that have special flags.
	 * Note that all USB devices should have the BLIST_INQUIRY_36 flag.
	 */
	अणु"3PARdata", "VV", शून्य, BLIST_REPORTLUN2पूर्ण,
	अणु"ADAPTEC", "AACRAID", शून्य, BLIST_FORCELUNपूर्ण,
	अणु"ADAPTEC", "Adaptec 5400S", शून्य, BLIST_FORCELUNपूर्ण,
	अणु"AIX", "VDASD", शून्य, BLIST_TRY_VPD_PAGESपूर्ण,
	अणु"AFT PRO", "-IX CF", "0.0>", BLIST_FORCELUNपूर्ण,
	अणु"BELKIN", "USB 2 HS-CF", "1.95",  BLIST_FORCELUN | BLIST_INQUIRY_36पूर्ण,
	अणु"BROWNIE", "1200U3P", शून्य, BLIST_NOREPORTLUNपूर्ण,
	अणु"BROWNIE", "1600U3P", शून्य, BLIST_NOREPORTLUNपूर्ण,
	अणु"CANON", "IPUBJD", शून्य, BLIST_SPARSELUNपूर्ण,
	अणु"CBOX3", "USB Storage-SMC", "300A", BLIST_FORCELUN | BLIST_INQUIRY_36पूर्ण,
	अणु"CMD", "CRA-7280", शून्य, BLIST_SPARSELUNपूर्ण,	/* CMD RAID Controller */
	अणु"CNSI", "G7324", शून्य, BLIST_SPARSELUNपूर्ण,	/* Chaparral G7324 RAID */
	अणु"CNSi", "G8324", शून्य, BLIST_SPARSELUNपूर्ण,	/* Chaparral G8324 RAID */
	अणु"COMPAQ", "ARRAY CONTROLLER", शून्य, BLIST_SPARSELUN | BLIST_LARGELUN |
		BLIST_MAX_512 | BLIST_REPORTLUN2पूर्ण,	/* Compaq RA4x00 */
	अणु"COMPAQ", "LOGICAL VOLUME", शून्य, BLIST_FORCELUN | BLIST_MAX_512पूर्ण, /* Compaq RA4x00 */
	अणु"COMPAQ", "CR3500", शून्य, BLIST_FORCELUNपूर्ण,
	अणु"COMPAQ", "MSA1000", शून्य, BLIST_SPARSELUN | BLIST_NOSTARTONADDपूर्ण,
	अणु"COMPAQ", "MSA1000 VOLUME", शून्य, BLIST_SPARSELUN | BLIST_NOSTARTONADDपूर्ण,
	अणु"COMPAQ", "HSV110", शून्य, BLIST_REPORTLUN2 | BLIST_NOSTARTONADDपूर्ण,
	अणु"DDN", "SAN DataDirector", "*", BLIST_SPARSELUNपूर्ण,
	अणु"DEC", "HSG80", शून्य, BLIST_REPORTLUN2 | BLIST_NOSTARTONADDपूर्ण,
	अणु"DELL", "PV660F", शून्य, BLIST_SPARSELUNपूर्ण,
	अणु"DELL", "PV660F   PSEUDO", शून्य, BLIST_SPARSELUNपूर्ण,
	अणु"DELL", "PSEUDO DEVICE .", शून्य, BLIST_SPARSELUNपूर्ण,	/* Dell PV 530F */
	अणु"DELL", "PV530F", शून्य, BLIST_SPARSELUNपूर्ण,
	अणु"DELL", "PERCRAID", शून्य, BLIST_FORCELUNपूर्ण,
	अणु"DGC", "RAID", शून्य, BLIST_SPARSELUNपूर्ण,	/* EMC CLARiiON, storage on LUN 0 */
	अणु"DGC", "DISK", शून्य, BLIST_SPARSELUNपूर्ण,	/* EMC CLARiiON, no storage on LUN 0 */
	अणु"EMC",  "Invista", "*", BLIST_SPARSELUN | BLIST_LARGELUNपूर्ण,
	अणु"EMC", "SYMMETRIX", शून्य, BLIST_SPARSELUN | BLIST_LARGELUN |
	 BLIST_REPORTLUN2 | BLIST_RETRY_ITFपूर्ण,
	अणु"EMULEX", "MD21/S2     ESDI", शून्य, BLIST_SINGLELUNपूर्ण,
	अणु"easyRAID", "16P", शून्य, BLIST_NOREPORTLUNपूर्ण,
	अणु"easyRAID", "X6P", शून्य, BLIST_NOREPORTLUNपूर्ण,
	अणु"easyRAID", "F8", शून्य, BLIST_NOREPORTLUNपूर्ण,
	अणु"FSC", "CentricStor", "*", BLIST_SPARSELUN | BLIST_LARGELUNपूर्ण,
	अणु"FUJITSU", "ETERNUS_DXM", "*", BLIST_RETRY_ASC_C1पूर्ण,
	अणु"Generic", "USB SD Reader", "1.00", BLIST_FORCELUN | BLIST_INQUIRY_36पूर्ण,
	अणु"Generic", "USB Storage-SMC", शून्य, BLIST_FORCELUN | BLIST_INQUIRY_36पूर्ण, /* FW: 0180 and 0207 */
	अणु"HITACHI", "DF400", "*", BLIST_REPORTLUN2पूर्ण,
	अणु"HITACHI", "DF500", "*", BLIST_REPORTLUN2पूर्ण,
	अणु"HITACHI", "DISK-SUBSYSTEM", "*", BLIST_REPORTLUN2पूर्ण,
	अणु"HITACHI", "HUS1530", "*", BLIST_NO_DIFपूर्ण,
	अणु"HITACHI", "OPEN-", "*", BLIST_REPORTLUN2 | BLIST_TRY_VPD_PAGESपूर्ण,
	अणु"HP", "A6189A", शून्य, BLIST_SPARSELUN | BLIST_LARGELUNपूर्ण,	/* HP VA7400 */
	अणु"HP", "OPEN-", "*", BLIST_REPORTLUN2 | BLIST_TRY_VPD_PAGESपूर्ण, /* HP XP Arrays */
	अणु"HP", "NetRAID-4M", शून्य, BLIST_FORCELUNपूर्ण,
	अणु"HP", "HSV100", शून्य, BLIST_REPORTLUN2 | BLIST_NOSTARTONADDपूर्ण,
	अणु"HP", "C1557A", शून्य, BLIST_FORCELUNपूर्ण,
	अणु"HP", "C3323-300", "4269", BLIST_NOTQपूर्ण,
	अणु"HP", "C5713A", शून्य, BLIST_NOREPORTLUNपूर्ण,
	अणु"HP", "DISK-SUBSYSTEM", "*", BLIST_REPORTLUN2पूर्ण,
	अणु"HPE", "OPEN-", "*", BLIST_REPORTLUN2 | BLIST_TRY_VPD_PAGESपूर्ण,
	अणु"IBM", "AuSaV1S2", शून्य, BLIST_FORCELUNपूर्ण,
	अणु"IBM", "ProFibre 4000R", "*", BLIST_SPARSELUN | BLIST_LARGELUNपूर्ण,
	अणु"IBM", "2105", शून्य, BLIST_RETRY_HWERRORपूर्ण,
	अणु"iomega", "jaz 1GB", "J.86", BLIST_NOTQ | BLIST_NOLUNपूर्ण,
	अणु"IOMEGA", "ZIP", शून्य, BLIST_NOTQ | BLIST_NOLUNपूर्ण,
	अणु"IOMEGA", "Io20S         *F", शून्य, BLIST_KEYपूर्ण,
	अणु"INSITE", "Floptical   F*8I", शून्य, BLIST_KEYपूर्ण,
	अणु"INSITE", "I325VM", शून्य, BLIST_KEYपूर्ण,
	अणु"Intel", "Multi-Flex", शून्य, BLIST_NO_RSOCपूर्ण,
	अणु"iRiver", "iFP Mass Driver", शून्य, BLIST_NOT_LOCKABLE | BLIST_INQUIRY_36पूर्ण,
	अणु"LASOUND", "CDX7405", "3.10", BLIST_MAX5LUN | BLIST_SINGLELUNपूर्ण,
	अणु"Marvell", "Console", शून्य, BLIST_SKIP_VPD_PAGESपूर्ण,
	अणु"Marvell", "91xx Config", "1.01", BLIST_SKIP_VPD_PAGESपूर्ण,
	अणु"MATSHITA", "PD-1", शून्य, BLIST_FORCELUN | BLIST_SINGLELUNपूर्ण,
	अणु"MATSHITA", "DMC-LC5", शून्य, BLIST_NOT_LOCKABLE | BLIST_INQUIRY_36पूर्ण,
	अणु"MATSHITA", "DMC-LC40", शून्य, BLIST_NOT_LOCKABLE | BLIST_INQUIRY_36पूर्ण,
	अणु"Medion", "Flash XL  MMC/SD", "2.6D", BLIST_FORCELUNपूर्ण,
	अणु"MegaRAID", "LD", शून्य, BLIST_FORCELUNपूर्ण,
	अणु"MICROP", "4110", शून्य, BLIST_NOTQपूर्ण,
	अणु"MSFT", "Virtual HD", शून्य, BLIST_MAX_1024 | BLIST_NO_RSOCपूर्ण,
	अणु"MYLEX", "DACARMRB", "*", BLIST_REPORTLUN2पूर्ण,
	अणु"nCipher", "Fastness Crypto", शून्य, BLIST_FORCELUNपूर्ण,
	अणु"NAKAMICH", "MJ-4.8S", शून्य, BLIST_FORCELUN | BLIST_SINGLELUNपूर्ण,
	अणु"NAKAMICH", "MJ-5.16S", शून्य, BLIST_FORCELUN | BLIST_SINGLELUNपूर्ण,
	अणु"NEC", "PD-1 ODX654P", शून्य, BLIST_FORCELUN | BLIST_SINGLELUNपूर्ण,
	अणु"NEC", "iStorage", शून्य, BLIST_REPORTLUN2पूर्ण,
	अणु"NRC", "MBR-7", शून्य, BLIST_FORCELUN | BLIST_SINGLELUNपूर्ण,
	अणु"NRC", "MBR-7.4", शून्य, BLIST_FORCELUN | BLIST_SINGLELUNपूर्ण,
	अणु"PIONEER", "CD-ROM DRM-600", शून्य, BLIST_FORCELUN | BLIST_SINGLELUNपूर्ण,
	अणु"PIONEER", "CD-ROM DRM-602X", शून्य, BLIST_FORCELUN | BLIST_SINGLELUNपूर्ण,
	अणु"PIONEER", "CD-ROM DRM-604X", शून्य, BLIST_FORCELUN | BLIST_SINGLELUNपूर्ण,
	अणु"PIONEER", "CD-ROM DRM-624X", शून्य, BLIST_FORCELUN | BLIST_SINGLELUNपूर्ण,
	अणु"Promise", "VTrak E610f", शून्य, BLIST_SPARSELUN | BLIST_NO_RSOCपूर्ण,
	अणु"Promise", "", शून्य, BLIST_SPARSELUNपूर्ण,
	अणु"QEMU", "QEMU CD-ROM", शून्य, BLIST_SKIP_VPD_PAGESपूर्ण,
	अणु"QNAP", "iSCSI Storage", शून्य, BLIST_MAX_1024पूर्ण,
	अणु"SYNOLOGY", "iSCSI Storage", शून्य, BLIST_MAX_1024पूर्ण,
	अणु"QUANTUM", "XP34301", "1071", BLIST_NOTQपूर्ण,
	अणु"REGAL", "CDC-4X", शून्य, BLIST_MAX5LUN | BLIST_SINGLELUNपूर्ण,
	अणु"SanDisk", "ImageMate CF-SD1", शून्य, BLIST_FORCELUNपूर्ण,
	अणु"SEAGATE", "ST34555N", "0930", BLIST_NOTQपूर्ण,	/* Chokes on tagged INQUIRY */
	अणु"SEAGATE", "ST3390N", "9546", BLIST_NOTQपूर्ण,
	अणु"SEAGATE", "ST900MM0006", शून्य, BLIST_SKIP_VPD_PAGESपूर्ण,
	अणु"SGI", "RAID3", "*", BLIST_SPARSELUNपूर्ण,
	अणु"SGI", "RAID5", "*", BLIST_SPARSELUNपूर्ण,
	अणु"SGI", "TP9100", "*", BLIST_REPORTLUN2पूर्ण,
	अणु"SGI", "Universal Xport", "*", BLIST_NO_ULD_ATTACHपूर्ण,
	अणु"IBM", "Universal Xport", "*", BLIST_NO_ULD_ATTACHपूर्ण,
	अणु"SUN", "Universal Xport", "*", BLIST_NO_ULD_ATTACHपूर्ण,
	अणु"DELL", "Universal Xport", "*", BLIST_NO_ULD_ATTACHपूर्ण,
	अणु"STK", "Universal Xport", "*", BLIST_NO_ULD_ATTACHपूर्ण,
	अणु"NETAPP", "Universal Xport", "*", BLIST_NO_ULD_ATTACHपूर्ण,
	अणु"LSI", "Universal Xport", "*", BLIST_NO_ULD_ATTACHपूर्ण,
	अणु"ENGENIO", "Universal Xport", "*", BLIST_NO_ULD_ATTACHपूर्ण,
	अणु"LENOVO", "Universal Xport", "*", BLIST_NO_ULD_ATTACHपूर्ण,
	अणु"FUJITSU", "Universal Xport", "*", BLIST_NO_ULD_ATTACHपूर्ण,
	अणु"SanDisk", "Cruzer Blade", शून्य, BLIST_TRY_VPD_PAGES |
		BLIST_INQUIRY_36पूर्ण,
	अणु"SMSC", "USB 2 HS-CF", शून्य, BLIST_SPARSELUN | BLIST_INQUIRY_36पूर्ण,
	अणु"SONY", "CD-ROM CDU-8001", शून्य, BLIST_BORKENपूर्ण,
	अणु"SONY", "TSL", शून्य, BLIST_FORCELUNपूर्ण,		/* DDS3 & DDS4 स्वतःloaders */
	अणु"ST650211", "CF", शून्य, BLIST_RETRY_HWERRORपूर्ण,
	अणु"SUN", "T300", "*", BLIST_SPARSELUNपूर्ण,
	अणु"SUN", "T4", "*", BLIST_SPARSELUNपूर्ण,
	अणु"Tornado-", "F4", "*", BLIST_NOREPORTLUNपूर्ण,
	अणु"TOSHIBA", "CDROM", शून्य, BLIST_ISROMपूर्ण,
	अणु"TOSHIBA", "CD-ROM", शून्य, BLIST_ISROMपूर्ण,
	अणु"Traxdata", "CDR4120", शून्य, BLIST_NOLUNपूर्ण,	/* locks up */
	अणु"USB2.0", "SMARTMEDIA/XD", शून्य, BLIST_FORCELUN | BLIST_INQUIRY_36पूर्ण,
	अणु"WangDAT", "Model 2600", "01.7", BLIST_SELECT_NO_ATNपूर्ण,
	अणु"WangDAT", "Model 3200", "02.2", BLIST_SELECT_NO_ATNपूर्ण,
	अणु"WangDAT", "Model 1300", "02.4", BLIST_SELECT_NO_ATNपूर्ण,
	अणु"WDC WD25", "00JB-00FUA0", शून्य, BLIST_NOREPORTLUNपूर्ण,
	अणु"XYRATEX", "RS", "*", BLIST_SPARSELUN | BLIST_LARGELUNपूर्ण,
	अणु"Zzyzx", "RocketStor 500S", शून्य, BLIST_SPARSELUNपूर्ण,
	अणु"Zzyzx", "RocketStor 2000", शून्य, BLIST_SPARSELUNपूर्ण,
	अणु शून्य, शून्य, शून्य, 0 पूर्ण,
पूर्ण;

अटल काष्ठा scsi_dev_info_list_table *scsi_devinfo_lookup_by_key(पूर्णांक key)
अणु
	काष्ठा scsi_dev_info_list_table *devinfo_table;
	पूर्णांक found = 0;

	list_क्रम_each_entry(devinfo_table, &scsi_dev_info_list, node)
		अगर (devinfo_table->key == key) अणु
			found = 1;
			अवरोध;
		पूर्ण
	अगर (!found)
		वापस ERR_PTR(-EINVAL);

	वापस devinfo_table;
पूर्ण

/*
 * scsi_म_नकल_devinfo: called from scsi_dev_info_list_add to copy पूर्णांकo
 * devinfo venकरोr and model strings.
 */
अटल व्योम scsi_म_नकल_devinfo(अक्षर *name, अक्षर *to, माप_प्रकार to_length,
				अक्षर *from, पूर्णांक compatible)
अणु
	माप_प्रकार from_length;

	from_length = म_माप(from);
	/* This zero-pads the destination */
	म_नकलन(to, from, to_length);
	अगर (from_length < to_length && !compatible) अणु
		/*
		 * space pad the string अगर it is लघु.
		 */
		स_रखो(&to[from_length], ' ', to_length - from_length);
	पूर्ण
	अगर (from_length > to_length)
		 prपूर्णांकk(KERN_WARNING "%s: %s string '%s' is too long\n",
			__func__, name, from);
पूर्ण

/**
 * scsi_dev_info_list_add - add one dev_info list entry.
 * @compatible: अगर true, null terminate लघु strings.  Otherwise space pad.
 * @venकरोr:	venकरोr string
 * @model:	model (product) string
 * @strflags:	पूर्णांकeger string
 * @flags:	अगर strflags शून्य, use this flag value
 *
 * Description:
 *	Create and add one dev_info entry क्रम @venकरोr, @model, @strflags or
 *	@flag. If @compatible, add to the tail of the list, करो not space
 *	pad, and set devinfo->compatible. The scsi_अटल_device_list entries
 *	are added with @compatible 1 and @clfags शून्य.
 *
 * Returns: 0 OK, -error on failure.
 **/
अटल पूर्णांक scsi_dev_info_list_add(पूर्णांक compatible, अक्षर *venकरोr, अक्षर *model,
			    अक्षर *strflags, blist_flags_t flags)
अणु
	वापस scsi_dev_info_list_add_keyed(compatible, venकरोr, model,
					    strflags, flags,
					    SCSI_DEVINFO_GLOBAL);
पूर्ण

/**
 * scsi_dev_info_list_add_keyed - add one dev_info list entry.
 * @compatible: अगर true, null terminate लघु strings.  Otherwise space pad.
 * @venकरोr:	venकरोr string
 * @model:	model (product) string
 * @strflags:	पूर्णांकeger string
 * @flags:	अगर strflags शून्य, use this flag value
 * @key:	specअगरy list to use
 *
 * Description:
 *	Create and add one dev_info entry क्रम @venकरोr, @model,
 *	@strflags or @flag in list specअगरied by @key. If @compatible,
 *	add to the tail of the list, करो not space pad, and set
 *	devinfo->compatible. The scsi_अटल_device_list entries are
 *	added with @compatible 1 and @clfags शून्य.
 *
 * Returns: 0 OK, -error on failure.
 **/
पूर्णांक scsi_dev_info_list_add_keyed(पूर्णांक compatible, अक्षर *venकरोr, अक्षर *model,
				 अक्षर *strflags, blist_flags_t flags,
				 क्रमागत scsi_devinfo_key key)
अणु
	काष्ठा scsi_dev_info_list *devinfo;
	काष्ठा scsi_dev_info_list_table *devinfo_table =
		scsi_devinfo_lookup_by_key(key);

	अगर (IS_ERR(devinfo_table))
		वापस PTR_ERR(devinfo_table);

	devinfo = kदो_स्मृति(माप(*devinfo), GFP_KERNEL);
	अगर (!devinfo) अणु
		prपूर्णांकk(KERN_ERR "%s: no memory\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	scsi_म_नकल_devinfo("vendor", devinfo->venकरोr, माप(devinfo->venकरोr),
			    venकरोr, compatible);
	scsi_म_नकल_devinfo("model", devinfo->model, माप(devinfo->model),
			    model, compatible);

	अगर (strflags) अणु
		अचिन्हित दीर्घ दीर्घ val;
		पूर्णांक ret = kम_से_अदीर्घl(strflags, 0, &val);

		अगर (ret != 0) अणु
			kमुक्त(devinfo);
			वापस ret;
		पूर्ण
		flags = (__क्रमce blist_flags_t)val;
	पूर्ण
	अगर (flags & __BLIST_UNUSED_MASK) अणु
		pr_err("scsi_devinfo (%s:%s): unsupported flags 0x%llx",
		       venकरोr, model, flags & __BLIST_UNUSED_MASK);
		kमुक्त(devinfo);
		वापस -EINVAL;
	पूर्ण
	devinfo->flags = flags;
	devinfo->compatible = compatible;

	अगर (compatible)
		list_add_tail(&devinfo->dev_info_list,
			      &devinfo_table->scsi_dev_info_list);
	अन्यथा
		list_add(&devinfo->dev_info_list,
			 &devinfo_table->scsi_dev_info_list);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(scsi_dev_info_list_add_keyed);

/**
 * scsi_dev_info_list_find - find a matching dev_info list entry.
 * @venकरोr:	full venकरोr string
 * @model:	full model (product) string
 * @key:	specअगरy list to use
 *
 * Description:
 *	Finds the first dev_info entry matching @venकरोr, @model
 *	in list specअगरied by @key.
 *
 * Returns: poपूर्णांकer to matching entry, or ERR_PTR on failure.
 **/
अटल काष्ठा scsi_dev_info_list *scsi_dev_info_list_find(स्थिर अक्षर *venकरोr,
		स्थिर अक्षर *model, क्रमागत scsi_devinfo_key key)
अणु
	काष्ठा scsi_dev_info_list *devinfo;
	काष्ठा scsi_dev_info_list_table *devinfo_table =
		scsi_devinfo_lookup_by_key(key);
	माप_प्रकार vmax, mmax, mlen;
	स्थिर अक्षर *vskip, *mskip;

	अगर (IS_ERR(devinfo_table))
		वापस (काष्ठा scsi_dev_info_list *) devinfo_table;

	/* Prepare क्रम "compatible" matches */

	/*
	 * XXX why skip leading spaces? If an odd INQUIRY
	 * value, that should have been part of the
	 * scsi_अटल_device_list[] entry, such as "  FOO"
	 * rather than "FOO". Since this code is alपढ़ोy
	 * here, and we करोn't know what device it is
	 * trying to work with, leave it as-is.
	 */
	vmax = माप(devinfo->venकरोr);
	vskip = venकरोr;
	जबतक (vmax > 0 && *vskip == ' ') अणु
		vmax--;
		vskip++;
	पूर्ण
	/* Also skip trailing spaces */
	जबतक (vmax > 0 && vskip[vmax - 1] == ' ')
		--vmax;

	mmax = माप(devinfo->model);
	mskip = model;
	जबतक (mmax > 0 && *mskip == ' ') अणु
		mmax--;
		mskip++;
	पूर्ण
	जबतक (mmax > 0 && mskip[mmax - 1] == ' ')
		--mmax;

	list_क्रम_each_entry(devinfo, &devinfo_table->scsi_dev_info_list,
			    dev_info_list) अणु
		अगर (devinfo->compatible) अणु
			/*
			 * venकरोr strings must be an exact match
			 */
			अगर (vmax != strnlen(devinfo->venकरोr,
					    माप(devinfo->venकरोr)) ||
			    स_भेद(devinfo->venकरोr, vskip, vmax))
				जारी;

			/*
			 * @model specअगरies the full string, and
			 * must be larger or equal to devinfo->model
			 */
			mlen = strnlen(devinfo->model, माप(devinfo->model));
			अगर (mmax < mlen || स_भेद(devinfo->model, mskip, mlen))
				जारी;
			वापस devinfo;
		पूर्ण अन्यथा अणु
			अगर (!स_भेद(devinfo->venकरोr, venकरोr,
				    माप(devinfo->venकरोr)) &&
			    !स_भेद(devinfo->model, model,
				    माप(devinfo->model)))
				वापस devinfo;
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-ENOENT);
पूर्ण

/**
 * scsi_dev_info_list_del_keyed - हटाओ one dev_info list entry.
 * @venकरोr:	venकरोr string
 * @model:	model (product) string
 * @key:	specअगरy list to use
 *
 * Description:
 *	Remove and destroy one dev_info entry क्रम @venकरोr, @model
 *	in list specअगरied by @key.
 *
 * Returns: 0 OK, -error on failure.
 **/
पूर्णांक scsi_dev_info_list_del_keyed(अक्षर *venकरोr, अक्षर *model,
				 क्रमागत scsi_devinfo_key key)
अणु
	काष्ठा scsi_dev_info_list *found;

	found = scsi_dev_info_list_find(venकरोr, model, key);
	अगर (IS_ERR(found))
		वापस PTR_ERR(found);

	list_del(&found->dev_info_list);
	kमुक्त(found);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(scsi_dev_info_list_del_keyed);

/**
 * scsi_dev_info_list_add_str - parse dev_list and add to the scsi_dev_info_list.
 * @dev_list:	string of device flags to add
 *
 * Description:
 *	Parse dev_list, and add entries to the scsi_dev_info_list.
 *	dev_list is of the क्रमm "vendor:product:flag,vendor:product:flag".
 *	dev_list is modअगरied via strsep. Can be called क्रम command line
 *	addition, क्रम proc or mabye a sysfs पूर्णांकerface.
 *
 * Returns: 0 अगर OK, -error on failure.
 **/
अटल पूर्णांक scsi_dev_info_list_add_str(अक्षर *dev_list)
अणु
	अक्षर *venकरोr, *model, *strflags, *next;
	अक्षर *next_check;
	पूर्णांक res = 0;

	next = dev_list;
	अगर (next && next[0] == '"') अणु
		/*
		 * Ignore both the leading and trailing quote.
		 */
		next++;
		next_check = ",\"";
	पूर्ण अन्यथा अणु
		next_check = ",";
	पूर्ण

	/*
	 * For the leading and trailing '"' हाल, the क्रम loop comes
	 * through the last समय with venकरोr[0] == '\0'.
	 */
	क्रम (venकरोr = strsep(&next, ":"); venकरोr && (venकरोr[0] != '\0')
	     && (res == 0); venकरोr = strsep(&next, ":")) अणु
		strflags = शून्य;
		model = strsep(&next, ":");
		अगर (model)
			strflags = strsep(&next, next_check);
		अगर (!model || !strflags) अणु
			prपूर्णांकk(KERN_ERR "%s: bad dev info string '%s' '%s'"
			       " '%s'\n", __func__, venकरोr, model,
			       strflags);
			res = -EINVAL;
		पूर्ण अन्यथा
			res = scsi_dev_info_list_add(0 /* compatible */, venकरोr,
						     model, strflags, 0);
	पूर्ण
	वापस res;
पूर्ण

/**
 * scsi_get_device_flags - get device specअगरic flags from the dynamic
 *	device list.
 * @sdev:       &scsi_device to get flags क्रम
 * @venकरोr:	venकरोr name
 * @model:	model name
 *
 * Description:
 *     Search the global scsi_dev_info_list (specअगरied by list zero)
 *     क्रम an entry matching @venकरोr and @model, अगर found, वापस the
 *     matching flags value, अन्यथा वापस the host or global शेष
 *     settings.  Called during scan समय.
 **/
blist_flags_t scsi_get_device_flags(काष्ठा scsi_device *sdev,
				    स्थिर अचिन्हित अक्षर *venकरोr,
				    स्थिर अचिन्हित अक्षर *model)
अणु
	वापस scsi_get_device_flags_keyed(sdev, venकरोr, model,
					   SCSI_DEVINFO_GLOBAL);
पूर्ण


/**
 * scsi_get_device_flags_keyed - get device specअगरic flags from the dynamic device list
 * @sdev:       &scsi_device to get flags क्रम
 * @venकरोr:	venकरोr name
 * @model:	model name
 * @key:	list to look up
 *
 * Description:
 *     Search the scsi_dev_info_list specअगरied by @key क्रम an entry
 *     matching @venकरोr and @model, अगर found, वापस the matching
 *     flags value, अन्यथा वापस the host or global शेष settings.
 *     Called during scan समय.
 **/
blist_flags_t scsi_get_device_flags_keyed(काष्ठा scsi_device *sdev,
				स्थिर अचिन्हित अक्षर *venकरोr,
				स्थिर अचिन्हित अक्षर *model,
				क्रमागत scsi_devinfo_key key)
अणु
	काष्ठा scsi_dev_info_list *devinfo;

	devinfo = scsi_dev_info_list_find(venकरोr, model, key);
	अगर (!IS_ERR(devinfo))
		वापस devinfo->flags;

	/* key or device not found: वापस nothing */
	अगर (key != SCSI_DEVINFO_GLOBAL)
		वापस 0;

	/* except क्रम the global list, where we have an exception */
	अगर (sdev->sdev_bflags)
		वापस sdev->sdev_bflags;

	वापस scsi_शेष_dev_flags;
पूर्ण
EXPORT_SYMBOL(scsi_get_device_flags_keyed);

#अगर_घोषित CONFIG_SCSI_PROC_FS
काष्ठा द्विगुन_list अणु
	काष्ठा list_head *top;
	काष्ठा list_head *bottom;
पूर्ण;

अटल पूर्णांक devinfo_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा द्विगुन_list *dl = v;
	काष्ठा scsi_dev_info_list_table *devinfo_table =
		list_entry(dl->top, काष्ठा scsi_dev_info_list_table, node);
	काष्ठा scsi_dev_info_list *devinfo =
		list_entry(dl->bottom, काष्ठा scsi_dev_info_list,
			   dev_info_list);

	अगर (devinfo_table->scsi_dev_info_list.next == dl->bottom &&
	    devinfo_table->name)
		seq_म_लिखो(m, "[%s]:\n", devinfo_table->name);

	seq_म_लिखो(m, "'%.8s' '%.16s' 0x%llx\n",
		   devinfo->venकरोr, devinfo->model, devinfo->flags);
	वापस 0;
पूर्ण

अटल व्योम *devinfo_seq_start(काष्ठा seq_file *m, loff_t *ppos)
अणु
	काष्ठा द्विगुन_list *dl = kदो_स्मृति(माप(*dl), GFP_KERNEL);
	loff_t pos = *ppos;

	अगर (!dl)
		वापस शून्य;

	list_क्रम_each(dl->top, &scsi_dev_info_list) अणु
		काष्ठा scsi_dev_info_list_table *devinfo_table =
			list_entry(dl->top, काष्ठा scsi_dev_info_list_table,
				   node);
		list_क्रम_each(dl->bottom, &devinfo_table->scsi_dev_info_list)
			अगर (pos-- == 0)
				वापस dl;
	पूर्ण

	kमुक्त(dl);
	वापस शून्य;
पूर्ण

अटल व्योम *devinfo_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *ppos)
अणु
	काष्ठा द्विगुन_list *dl = v;
	काष्ठा scsi_dev_info_list_table *devinfo_table =
		list_entry(dl->top, काष्ठा scsi_dev_info_list_table, node);

	++*ppos;
	dl->bottom = dl->bottom->next;
	जबतक (&devinfo_table->scsi_dev_info_list == dl->bottom) अणु
		dl->top = dl->top->next;
		अगर (dl->top == &scsi_dev_info_list) अणु
			kमुक्त(dl);
			वापस शून्य;
		पूर्ण
		devinfo_table = list_entry(dl->top,
					   काष्ठा scsi_dev_info_list_table,
					   node);
		dl->bottom = devinfo_table->scsi_dev_info_list.next;
	पूर्ण

	वापस dl;
पूर्ण

अटल व्योम devinfo_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	kमुक्त(v);
पूर्ण

अटल स्थिर काष्ठा seq_operations scsi_devinfo_seq_ops = अणु
	.start	= devinfo_seq_start,
	.next	= devinfo_seq_next,
	.stop	= devinfo_seq_stop,
	.show	= devinfo_seq_show,
पूर्ण;

अटल पूर्णांक proc_scsi_devinfo_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &scsi_devinfo_seq_ops);
पूर्ण

/*
 * proc_scsi_dev_info_ग_लिखो - allow additions to scsi_dev_info_list via /proc.
 *
 * Description: Adds a black/white list entry क्रम venकरोr and model with an
 * पूर्णांकeger value of flag to the scsi device info list.
 * To use, echo "vendor:model:flag" > /proc/scsi/device_info
 */
अटल sमाप_प्रकार proc_scsi_devinfo_ग_लिखो(काष्ठा file *file,
				       स्थिर अक्षर __user *buf,
				       माप_प्रकार length, loff_t *ppos)
अणु
	अक्षर *buffer;
	sमाप_प्रकार err = length;

	अगर (!buf || length>PAGE_SIZE)
		वापस -EINVAL;
	अगर (!(buffer = (अक्षर *) __get_मुक्त_page(GFP_KERNEL)))
		वापस -ENOMEM;
	अगर (copy_from_user(buffer, buf, length)) अणु
		err =-EFAULT;
		जाओ out;
	पूर्ण

	अगर (length < PAGE_SIZE)
		buffer[length] = '\0';
	अन्यथा अगर (buffer[PAGE_SIZE-1]) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	scsi_dev_info_list_add_str(buffer);

out:
	मुक्त_page((अचिन्हित दीर्घ)buffer);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा proc_ops scsi_devinfo_proc_ops = अणु
	.proc_खोलो	= proc_scsi_devinfo_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= proc_scsi_devinfo_ग_लिखो,
	.proc_lseek	= seq_lseek,
	.proc_release	= seq_release,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SCSI_PROC_FS */

module_param_string(dev_flags, scsi_dev_flags, माप(scsi_dev_flags), 0);
MODULE_PARM_DESC(dev_flags,
	 "Given scsi_dev_flags=vendor:model:flags[,v:m:f] add black/white"
	 " list entries for vendor and model with an integer value of flags"
	 " to the scsi device info list");

module_param_named(शेष_dev_flags, scsi_शेष_dev_flags, ulदीर्घ, 0644);
MODULE_PARM_DESC(शेष_dev_flags,
		 "scsi default device flag uint64_t value");

/**
 * scsi_निकास_devinfo - हटाओ /proc/scsi/device_info & the scsi_dev_info_list
 **/
व्योम scsi_निकास_devinfo(व्योम)
अणु
#अगर_घोषित CONFIG_SCSI_PROC_FS
	हटाओ_proc_entry("scsi/device_info", शून्य);
#पूर्ण_अगर

	scsi_dev_info_हटाओ_list(SCSI_DEVINFO_GLOBAL);
पूर्ण

/**
 * scsi_dev_info_add_list - add a new devinfo list
 * @key:	key of the list to add
 * @name:	Name of the list to add (क्रम /proc/scsi/device_info)
 *
 * Adds the requested list, वापसs zero on success, -EEXIST अगर the
 * key is alपढ़ोy रेजिस्टरed to a list, or other error on failure.
 */
पूर्णांक scsi_dev_info_add_list(क्रमागत scsi_devinfo_key key, स्थिर अक्षर *name)
अणु
	काष्ठा scsi_dev_info_list_table *devinfo_table =
		scsi_devinfo_lookup_by_key(key);

	अगर (!IS_ERR(devinfo_table))
		/* list alपढ़ोy exists */
		वापस -EEXIST;

	devinfo_table = kदो_स्मृति(माप(*devinfo_table), GFP_KERNEL);

	अगर (!devinfo_table)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&devinfo_table->node);
	INIT_LIST_HEAD(&devinfo_table->scsi_dev_info_list);
	devinfo_table->name = name;
	devinfo_table->key = key;
	list_add_tail(&devinfo_table->node, &scsi_dev_info_list);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(scsi_dev_info_add_list);

/**
 * scsi_dev_info_हटाओ_list - destroy an added devinfo list
 * @key: key of the list to destroy
 *
 * Iterates over the entire list first, मुक्तing all the values, then
 * मुक्तs the list itself.  Returns 0 on success or -EINVAL अगर the key
 * can't be found.
 */
पूर्णांक scsi_dev_info_हटाओ_list(क्रमागत scsi_devinfo_key key)
अणु
	काष्ठा list_head *lh, *lh_next;
	काष्ठा scsi_dev_info_list_table *devinfo_table =
		scsi_devinfo_lookup_by_key(key);

	अगर (IS_ERR(devinfo_table))
		/* no such list */
		वापस -EINVAL;

	/* हटाओ from the master list */
	list_del(&devinfo_table->node);

	list_क्रम_each_safe(lh, lh_next, &devinfo_table->scsi_dev_info_list) अणु
		काष्ठा scsi_dev_info_list *devinfo;

		devinfo = list_entry(lh, काष्ठा scsi_dev_info_list,
				     dev_info_list);
		kमुक्त(devinfo);
	पूर्ण
	kमुक्त(devinfo_table);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(scsi_dev_info_हटाओ_list);

/**
 * scsi_init_devinfo - set up the dynamic device list.
 *
 * Description:
 *	Add command line entries from scsi_dev_flags, then add
 *	scsi_अटल_device_list entries to the scsi device info list.
 */
पूर्णांक __init scsi_init_devinfo(व्योम)
अणु
#अगर_घोषित CONFIG_SCSI_PROC_FS
	काष्ठा proc_dir_entry *p;
#पूर्ण_अगर
	पूर्णांक error, i;

	error = scsi_dev_info_add_list(SCSI_DEVINFO_GLOBAL, शून्य);
	अगर (error)
		वापस error;

	error = scsi_dev_info_list_add_str(scsi_dev_flags);
	अगर (error)
		जाओ out;

	क्रम (i = 0; scsi_अटल_device_list[i].venकरोr; i++) अणु
		error = scsi_dev_info_list_add(1 /* compatibile */,
				scsi_अटल_device_list[i].venकरोr,
				scsi_अटल_device_list[i].model,
				शून्य,
				scsi_अटल_device_list[i].flags);
		अगर (error)
			जाओ out;
	पूर्ण

#अगर_घोषित CONFIG_SCSI_PROC_FS
	p = proc_create("scsi/device_info", 0, शून्य, &scsi_devinfo_proc_ops);
	अगर (!p) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण
#पूर्ण_अगर /* CONFIG_SCSI_PROC_FS */

 out:
	अगर (error)
		scsi_निकास_devinfo();
	वापस error;
पूर्ण
