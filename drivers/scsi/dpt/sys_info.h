<शैली गुरु>
/*	BSDI sys_info.h,v 1.6 1998/06/03 19:14:59 karels Exp	*/

/*
 * Copyright (c) 1996-1999 Distributed Processing Technology Corporation
 * All rights reserved.
 *
 * Redistribution and use in source क्रमm, with or without modअगरication, are
 * permitted provided that redistributions of source code must retain the
 * above copyright notice, this list of conditions and the following disclaimer.
 *
 * This software is provided `as is' by Distributed Processing Technology and
 * any express or implied warranties, including, but not limited to, the
 * implied warranties of merchantability and fitness क्रम a particular purpose,
 * are disclaimed. In no event shall Distributed Processing Technology be
 * liable क्रम any direct, indirect, incidental, special, exemplary or
 * consequential damages (including, but not limited to, procurement of
 * substitute goods or services; loss of use, data, or profits; or business
 * पूर्णांकerruptions) however caused and on any theory of liability, whether in
 * contract, strict liability, or tort (including negligence or otherwise)
 * arising in any way out of the use of this driver software, even अगर advised
 * of the possibility of such damage.
 *
 */

#अगर_अघोषित         __SYS_INFO_H
#घोषणा         __SYS_INFO_H

/*File - SYS_INFO.H
 ****************************************************************************
 *
 *Description:
 *
 *      This file contains काष्ठाure definitions क्रम the OS dependent
 *layer प्रणाली inक्रमmation buffers.
 *
 *Copyright Distributed Processing Technology, Corp.
 *        140 Candace Dr.
 *        Maitland, Fl. 32751   USA
 *        Phone: (407) 830-5522  Fax: (407) 260-5366
 *        All Rights Reserved
 *
 *Author:       Don Kemper
 *Date:         5/10/94
 *
 *Editors:
 *
 *Remarks:
 *
 *
 *****************************************************************************/


/*Include Files ------------------------------------------------------------- */

#समावेश        "osd_util.h"

#अगर_अघोषित NO_PACK
#अगर defined (_DPT_AIX)
#आशय options align=packed
#अन्यथा
#आशय pack(1)
#पूर्ण_अगर  /* aix */
#पूर्ण_अगर  // no unpack


/*काष्ठा - driveParam_S - start
 *===========================================================================
 *
 *Description:
 *
 *      This काष्ठाure defines the drive parameters seen during
 *booting.
 *
 *---------------------------------------------------------------------------*/

#अगर_घोषित  __cplusplus
   काष्ठा driveParam_S अणु
#अन्यथा
   प्रकार काष्ठा  अणु
#पूर्ण_अगर

   uSHORT       cylinders;      /* Up to 1024 */
   uCHAR        heads;          /* Up to 255 */
   uCHAR        sectors;        /* Up to 63 */

#अगर_घोषित  __cplusplus

//---------- Portability Additions ----------- in sp_sinfo.cpp
#अगर_घोषित DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#पूर्ण_अगर // DPT PORTABLE
//--------------------------------------------

   पूर्ण;
#अन्यथा
   पूर्ण driveParam_S;
#पूर्ण_अगर
/*driveParam_S - end */


/*काष्ठा - sysInfo_S - start
 *===========================================================================
 *
 *Description:
 *
 *      This काष्ठाure defines the command प्रणाली inक्रमmation that
 *should be वापसed by every OS dependent layer.
 *
 *---------------------------------------------------------------------------*/

/*flags - bit definitions */
#घोषणा SI_CMOS_Valid           0x0001
#घोषणा SI_NumDrivesValid       0x0002
#घोषणा SI_ProcessorValid       0x0004
#घोषणा SI_MemorySizeValid      0x0008
#घोषणा SI_DriveParamsValid     0x0010
#घोषणा SI_SmartROMverValid     0x0020
#घोषणा SI_OSversionValid       0x0040
#घोषणा SI_OSspecअगरicValid      0x0080  /* 1 अगर OS काष्ठाure वापसed */
#घोषणा SI_BusTypeValid         0x0100

#घोषणा SI_ALL_VALID            0x0FFF  /* All Std SysInfo is valid */
#घोषणा SI_NO_SmartROM          0x8000

/*busType - definitions */
#घोषणा SI_ISA_BUS      0x00
#घोषणा SI_MCA_BUS      0x01
#घोषणा SI_EISA_BUS     0x02
#घोषणा SI_PCI_BUS      0x04

#अगर_घोषित  __cplusplus
   काष्ठा sysInfo_S अणु
#अन्यथा
   प्रकार काष्ठा  अणु
#पूर्ण_अगर

   uCHAR        drive0CMOS;             /* CMOS Drive 0 Type */
   uCHAR        drive1CMOS;             /* CMOS Drive 1 Type */
   uCHAR        numDrives;              /* 0040:0075 contents */
   uCHAR        processorFamily;        /* Same as DPTSIG's definition */
   uCHAR        processorType;          /* Same as DPTSIG's definition */
   uCHAR        smartROMMajorVersion;
   uCHAR        smartROMMinorVersion;   /* SmartROM version */
   uCHAR        smartROMRevision;
   uSHORT       flags;                  /* See bit definitions above */
   uSHORT       conventionalMemSize;    /* in KB */
   uINT         extendedMemSize;        /* in KB */
   uINT         osType;                 /* Same as DPTSIG's definition */
   uCHAR        osMajorVersion;
   uCHAR        osMinorVersion;         /* The OS version */
   uCHAR        osRevision;
#अगर_घोषित _SINIX_ADDON
   uCHAR        busType;                /* See defininitions above */
   uSHORT       osSubRevision;
   uCHAR        pad[2];                 /* For alignment */
#अन्यथा
   uCHAR        osSubRevision;
   uCHAR        busType;                /* See defininitions above */
   uCHAR        pad[3];                 /* For alignment */
#पूर्ण_अगर
   driveParam_S drives[16];             /* SmartROM Logical Drives */

#अगर_घोषित  __cplusplus

//---------- Portability Additions ----------- in sp_sinfo.cpp
#अगर_घोषित DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#पूर्ण_अगर // DPT PORTABLE
//--------------------------------------------

   पूर्ण;
#अन्यथा
   पूर्ण sysInfo_S;
#पूर्ण_अगर
/*sysInfo_S - end */


/*काष्ठा - DOS_Info_S - start
 *===========================================================================
 *
 *Description:
 *
 *      This काष्ठाure defines the प्रणाली inक्रमmation specअगरic to a
 *DOS workstation.
 *
 *---------------------------------------------------------------------------*/

/*flags - bit definitions */
#घोषणा DI_DOS_HIGH             0x01    /* DOS is loaded high */
#घोषणा DI_DPMI_VALID           0x02    /* DPMI version is valid */

#अगर_घोषित  __cplusplus
   काष्ठा DOS_Info_S अणु
#अन्यथा
   प्रकार काष्ठा अणु
#पूर्ण_अगर

   uCHAR        flags;          /* See bit definitions above */
   uSHORT       driverLocation; /* SmartROM BIOS address */
   uSHORT       DOS_version;
   uSHORT       DPMI_version;

#अगर_घोषित  __cplusplus

//---------- Portability Additions ----------- in sp_sinfo.cpp
#अगर_घोषित DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#पूर्ण_अगर // DPT PORTABLE
//--------------------------------------------

   पूर्ण;
#अन्यथा
   पूर्ण DOS_Info_S;
#पूर्ण_अगर
/*DOS_Info_S - end */


/*काष्ठा - Netware_Info_S - start
 *===========================================================================
 *
 *Description:
 *
 *      This काष्ठाure defines the प्रणाली inक्रमmation specअगरic to a
 *Netware machine.
 *
 *---------------------------------------------------------------------------*/

#अगर_घोषित  __cplusplus
   काष्ठा Netware_Info_S अणु
#अन्यथा
   प्रकार काष्ठा अणु
#पूर्ण_अगर

   uCHAR        driverName[13];         /* ie PM12NW31.DSK */
   uCHAR        serverName[48];
   uCHAR        netwareVersion;         /* The Netware OS version */
   uCHAR        netwareSubVersion;
   uCHAR        netwareRevision;
   uSHORT       maxConnections;         /* Probably  250 or 1000 */
   uSHORT       connectionsInUse;
   uSHORT       maxVolumes;
   uCHAR        unused;
   uCHAR        SFTlevel;
   uCHAR        TTSlevel;

   uCHAR        clibMajorVersion;       /* The CLIB.NLM version */
   uCHAR        clibMinorVersion;
   uCHAR        clibRevision;

#अगर_घोषित  __cplusplus

//---------- Portability Additions ----------- in sp_sinfo.cpp
#अगर_घोषित DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#पूर्ण_अगर // DPT PORTABLE
//--------------------------------------------

   पूर्ण;
#अन्यथा
   पूर्ण Netware_Info_S;
#पूर्ण_अगर
/*Netware_Info_S - end */


/*काष्ठा - OS2_Info_S - start
 *===========================================================================
 *
 *Description:
 *
 *      This काष्ठाure defines the प्रणाली inक्रमmation specअगरic to an
 *OS/2 machine.
 *
 *---------------------------------------------------------------------------*/

#अगर_घोषित  __cplusplus
   काष्ठा OS2_Info_S अणु
#अन्यथा
   प्रकार काष्ठा अणु
#पूर्ण_अगर

   uCHAR        something;

#अगर_घोषित  __cplusplus

//---------- Portability Additions ----------- in sp_sinfo.cpp
#अगर_घोषित DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#पूर्ण_अगर // DPT PORTABLE
//--------------------------------------------

   पूर्ण;
#अन्यथा
   पूर्ण OS2_Info_S;
#पूर्ण_अगर
/*OS2_Info_S - end */


/*काष्ठा - WinNT_Info_S - start
 *===========================================================================
 *
 *Description:
 *
 *      This काष्ठाure defines the प्रणाली inक्रमmation specअगरic to a
 *Winकरोws NT machine.
 *
 *---------------------------------------------------------------------------*/

#अगर_घोषित  __cplusplus
   काष्ठा WinNT_Info_S अणु
#अन्यथा
   प्रकार काष्ठा अणु
#पूर्ण_अगर

   uCHAR        something;

#अगर_घोषित  __cplusplus

//---------- Portability Additions ----------- in sp_sinfo.cpp
#अगर_घोषित DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#पूर्ण_अगर // DPT PORTABLE
//--------------------------------------------

   पूर्ण;
#अन्यथा
   पूर्ण WinNT_Info_S;
#पूर्ण_अगर
/*WinNT_Info_S - end */


/*काष्ठा - SCO_Info_S - start
 *===========================================================================
 *
 *Description:
 *
 *      This काष्ठाure defines the प्रणाली inक्रमmation specअगरic to an
 *SCO UNIX machine.
 *
 *---------------------------------------------------------------------------*/

#अगर_घोषित  __cplusplus
   काष्ठा SCO_Info_S अणु
#अन्यथा
   प्रकार काष्ठा अणु
#पूर्ण_अगर

   uCHAR        something;

#अगर_घोषित  __cplusplus

//---------- Portability Additions ----------- in sp_sinfo.cpp
#अगर_घोषित DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#पूर्ण_अगर // DPT PORTABLE
//--------------------------------------------

   पूर्ण;
#अन्यथा
   पूर्ण SCO_Info_S;
#पूर्ण_अगर
/*SCO_Info_S - end */


/*काष्ठा - USL_Info_S - start
 *===========================================================================
 *
 *Description:
 *
 *      This काष्ठाure defines the प्रणाली inक्रमmation specअगरic to a
 *USL UNIX machine.
 *
 *---------------------------------------------------------------------------*/

#अगर_घोषित  __cplusplus
   काष्ठा USL_Info_S अणु
#अन्यथा
   प्रकार काष्ठा अणु
#पूर्ण_अगर

   uCHAR        something;

#अगर_घोषित  __cplusplus

//---------- Portability Additions ----------- in sp_sinfo.cpp
#अगर_घोषित DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#पूर्ण_अगर // DPT PORTABLE
//--------------------------------------------

   पूर्ण;
#अन्यथा
   पूर्ण USL_Info_S;
#पूर्ण_अगर
/*USL_Info_S - end */


  /* Restore शेष काष्ठाure packing */
#अगर_अघोषित NO_UNPACK
#अगर defined (_DPT_AIX)
#आशय options align=reset
#या_अगर defined (UNPACK_FOUR)
#आशय pack(4)
#अन्यथा
#आशय pack()
#पूर्ण_अगर  /* aix */
#पूर्ण_अगर  // no unpack

#पूर्ण_अगर  // __SYS_INFO_H

