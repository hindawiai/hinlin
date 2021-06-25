<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/***************************************************************************
                          dpti_ioctl.h  -  description
                             -------------------
    begin                : Thu Sep 7 2000
    copyright            : (C) 2001 by Adaptec

    See Documentation/scsi/dpti.rst क्रम history, notes, license info
    and credits
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *                                                                         *
 ***************************************************************************/

/***************************************************************************
 * This file is generated from  osd_unix.h                                 *
 * *************************************************************************/

#अगर_अघोषित _dpti_ioctl_h
#घोषणा _dpti_ioctl_h

// IOCTL पूर्णांकerface commands

#अगर_अघोषित _IOWR
# define _IOWR(x,y,z)	(((x)<<8)|y)
#पूर्ण_अगर
#अगर_अघोषित _IOW
# define _IOW(x,y,z)	(((x)<<8)|y)
#पूर्ण_अगर
#अगर_अघोषित _IOR
# define _IOR(x,y,z)	(((x)<<8)|y)
#पूर्ण_अगर
#अगर_अघोषित _IO
# define _IO(x,y)	(((x)<<8)|y)
#पूर्ण_अगर
/* EATA PassThrough Command	*/
#घोषणा EATAUSRCMD      _IOWR('D',65,EATA_CP)
/* Set Debug Level If Enabled	*/
#घोषणा DPT_DEBUG       _IOW('D',66,पूर्णांक)
/* Get Signature Structure	*/
#घोषणा DPT_SIGNATURE   _IOR('D',67,dpt_sig_S)
#अगर defined __bsdi__
#घोषणा DPT_SIGNATURE_PACKED   _IOR('D',67,dpt_sig_S_Packed)
#पूर्ण_अगर
/* Get Number Of DPT Adapters	*/
#घोषणा DPT_NUMCTRLS    _IOR('D',68,पूर्णांक)
/* Get Adapter Info Structure	*/
#घोषणा DPT_CTRLINFO    _IOR('D',69,CtrlInfo)
/* Get Statistics If Enabled	*/
#घोषणा DPT_STATINFO    _IO('D',70)
/* Clear Stats If Enabled	*/
#घोषणा DPT_CLRSTAT     _IO('D',71)
/* Get System Info Structure	*/
#घोषणा DPT_SYSINFO     _IOR('D',72,sysInfo_S)
/* Set Timeout Value		*/
#घोषणा DPT_TIMEOUT     _IO('D',73)
/* Get config Data  		*/
#घोषणा DPT_CONFIG      _IO('D',74)
/* Get Blink LED Code	        */
#घोषणा DPT_BLINKLED    _IOR('D',75,पूर्णांक)
/* Get Statistical inक्रमmation (अगर available) */
#घोषणा DPT_STATS_INFO        _IOR('D',80,STATS_DATA)
/* Clear the statistical inक्रमmation          */
#घोषणा DPT_STATS_CLEAR       _IO('D',81)
/* Get Perक्रमmance metrics */
#घोषणा DPT_PERF_INFO        _IOR('D',82,dpt_perf_t)
/* Send an I2O command */
#घोषणा I2OUSRCMD	_IO('D',76)
/* Inक्रमm driver to re-acquire LCT inक्रमmation */
#घोषणा I2ORESCANCMD	_IO('D',77)
/* Inक्रमm driver to reset adapter */
#घोषणा I2ORESETCMD	_IO('D',78)
/* See अगर the target is mounted */
#घोषणा DPT_TARGET_BUSY	_IOR('D',79, TARGET_BUSY_T)


  /* Structure Returned From Get Controller Info                             */

प्रकार काष्ठा अणु
	uCHAR    state;            /* Operational state               */
	uCHAR    id;               /* Host adapter SCSI id            */
	पूर्णांक      vect;             /* Interrupt vector number         */
	पूर्णांक      base;             /* Base I/O address                */
	पूर्णांक      njobs;            /* # of jobs sent to HA            */
	पूर्णांक      qdepth;           /* Controller queue depth.         */
	पूर्णांक      wakebase;         /* mpx wakeup base index.          */
	uINT     SGsize;           /* Scatter/Gather list size.       */
	अचिन्हित heads;            /* heads क्रम drives on cntlr.      */
	अचिन्हित sectors;          /* sectors क्रम drives on cntlr.    */
	uCHAR    करो_drive32;       /* Flag क्रम Above 16 MB Ability    */
	uCHAR    BusQuiet;         /* SCSI Bus Quiet Flag             */
	अक्षर     idPAL[4];         /* 4 Bytes Of The ID Pal           */
	uCHAR    primary;          /* 1 For Primary, 0 For Secondary  */
	uCHAR    eataVersion;      /* EATA Version                    */
	uINT     cpLength;         /* EATA Command Packet Length      */
	uINT     spLength;         /* EATA Status Packet Length       */
	uCHAR    drqNum;           /* DRQ Index (0,5,6,7)             */
	uCHAR    flag1;            /* EATA Flags 1 (Byte 9)           */
	uCHAR    flag2;            /* EATA Flags 2 (Byte 30)          */
पूर्ण CtrlInfo;

प्रकार काष्ठा अणु
	uSHORT length;		// Reमुख्यing length of this
	uSHORT drvrHBAnum;	// Relative HBA # used by the driver
	uINT baseAddr;		// Base I/O address
	uSHORT blinkState;	// Blink LED state (0=Not in blink LED)
	uCHAR pciBusNum;	// PCI Bus # (Optional)
	uCHAR pciDeviceNum;	// PCI Device # (Optional)
	uSHORT hbaFlags;	// Miscellaneous HBA flags
	uSHORT Interrupt;	// Interrupt set क्रम this device.
#   अगर (defined(_DPT_ARC))
	uINT baseLength;
	ADAPTER_OBJECT *AdapterObject;
	LARGE_INTEGER DmaLogicalAddress;
	PVOID DmaVirtualAddress;
	LARGE_INTEGER ReplyLogicalAddress;
	PVOID ReplyVirtualAddress;
#   अन्यथा
	uINT reserved1;		// Reserved क्रम future expansion
	uINT reserved2;		// Reserved क्रम future expansion
	uINT reserved3;		// Reserved क्रम future expansion
#   endअगर
पूर्ण drvrHBAinfo_S;

प्रकार काष्ठा TARGET_BUSY
अणु
  uLONG channel;
  uLONG id;
  uLONG lun;
  uLONG isBusy;
पूर्ण TARGET_BUSY_T;

#पूर्ण_अगर

