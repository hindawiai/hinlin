<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/************************************************************************
 *
 *	io_edgeport.h	Edgeport Linux Interface definitions
 *
 *	Copyright (C) 2000 Inside Out Networks, Inc.
 *
 ************************************************************************/

#अगर !defined(_IO_EDGEPORT_H_)
#घोषणा	_IO_EDGEPORT_H_

#घोषणा MAX_RS232_PORTS		8	/* Max # of RS-232 ports per device */

/* प्रकारs that the insideout headers need */
#अगर_अघोषित LOW8
	#घोषणा LOW8(a)		((अचिन्हित अक्षर)(a & 0xff))
#पूर्ण_अगर
#अगर_अघोषित HIGH8
	#घोषणा HIGH8(a)	((अचिन्हित अक्षर)((a & 0xff00) >> 8))
#पूर्ण_अगर

#समावेश "io_usbvend.h"

/*
 *	Product inक्रमmation पढ़ो from the Edgeport
 */
काष्ठा edgeport_product_info अणु
	__u16	ProductId;			/* Product Identअगरier */
	__u8	NumPorts;			/* Number of ports on edgeport */
	__u8	ProdInfoVer;			/* What version of काष्ठाure is this? */

	__u32	IsServer        :1;		/* Set अगर Server */
	__u32	IsRS232         :1;		/* Set अगर RS-232 ports exist */
	__u32	IsRS422         :1;		/* Set अगर RS-422 ports exist */
	__u32	IsRS485         :1;		/* Set अगर RS-485 ports exist */
	__u32	IsReserved      :28;		/* Reserved क्रम later expansion */

	__u8	RomSize;			/* Size of ROM/E2PROM in K */
	__u8	RamSize;			/* Size of बाह्यal RAM in K */
	__u8	CpuRev;				/* CPU revision level (chg only अगर s/w visible) */
	__u8	BoardRev;			/* PCB revision level (chg only अगर s/w visible) */

	__u8	BootMajorVersion;		/* Boot Firmware version: xx. */
	__u8	BootMinorVersion;		/*			  yy. */
	__le16	BootBuildNumber;		/*			  zzzz (LE क्रमmat) */

	__u8	FirmwareMajorVersion;		/* Operational Firmware version:xx. */
	__u8	FirmwareMinorVersion;		/*				yy. */
	__le16	FirmwareBuildNumber;		/*				zzzz (LE क्रमmat) */

	__u8	ManufactureDescDate[3];		/* MM/DD/YY when descriptor ढाँचा was compiled */
	__u8	HardwareType;

	__u8	iDownloadFile;			/* What to करोwnload to EPiC device */
	__u8	EpicVer;			/* What version of EPiC spec this device supports */

	काष्ठा edge_compatibility_bits Epic;
पूर्ण;

#पूर्ण_अगर
