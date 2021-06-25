<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
* cycx_cfm.h	Cyclom 2X WAN Link Driver.
*		Definitions क्रम the Cyclom 2X Firmware Module (CFM).
*
* Author:	Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
*
* Copyright:	(c) 1998-2003 Arnalकरो Carvalho de Melo
*
* Based on sdlasfm.h by Gene Kozin <74604.152@compuserve.com>
*
*		This program is मुक्त software; you can redistribute it and/or
*		modअगरy it under the terms of the GNU General Public License
*		as published by the Free Software Foundation; either version
*		2 of the License, or (at your option) any later version.
* ============================================================================
* 1998/08/08	acme		Initial version.
*/
#अगर_अघोषित	_CYCX_CFM_H
#घोषणा	_CYCX_CFM_H

/* Defines */

#घोषणा	CFM_VERSION	2
#घोषणा	CFM_SIGNATURE	"CFM - Cyclades CYCX Firmware Module"

/* min/max */
#घोषणा	CFM_IMAGE_SIZE	0x20000	/* max size of CYCX code image file */
#घोषणा	CFM_DESCR_LEN	256	/* max length of description string */
#घोषणा	CFM_MAX_CYCX	1	/* max number of compatible adapters */
#घोषणा	CFM_LOAD_BUFSZ	0x400	/* buffer size क्रम reset code (buffer_load) */

/* Firmware Commands */
#घोषणा GEN_POWER_ON	0x1280

#घोषणा GEN_SET_SEG	0x1401	/* boot segment setting. */
#घोषणा GEN_BOOT_DAT	0x1402	/* boot data. */
#घोषणा GEN_START	0x1403	/* board start. */
#घोषणा GEN_DEFPAR	0x1404	/* buffer length क्रम boot. */

/* Adapter Types */
#घोषणा CYCX_2X		2
/* क्रम now only the 2X is supported, no plans to support 8X or 16X */
#घोषणा CYCX_8X		8
#घोषणा CYCX_16X	16

#घोषणा	CFID_X25_2X	5200

/**
 *	काष्ठा cycx_fw_info - firmware module inक्रमmation.
 *	@codeid - firmware ID
 *	@version - firmware version number
 *	@adapter - compatible adapter types
 *	@memsize - minimum memory size
 *	@reserved - reserved
 *	@startoffs - entry poपूर्णांक offset
 *	@winoffs - dual-port memory winकरोw offset
 *	@codeoffs - code load offset
 *	@codesize - code size
 *	@dataoffs - configuration data load offset
 *	@datasize - configuration data size
 */
काष्ठा cycx_fw_info अणु
	अचिन्हित लघु	codeid;
	अचिन्हित लघु	version;
	अचिन्हित लघु	adapter[CFM_MAX_CYCX];
	अचिन्हित दीर्घ	memsize;
	अचिन्हित लघु	reserved[2];
	अचिन्हित लघु	startoffs;
	अचिन्हित लघु	winoffs;
	अचिन्हित लघु	codeoffs;
	अचिन्हित दीर्घ	codesize;
	अचिन्हित लघु	dataoffs;
	अचिन्हित दीर्घ	datasize;
पूर्ण;

/**
 *	काष्ठा cycx_firmware - CYCX firmware file काष्ठाure
 *	@signature - CFM file signature
 *	@version - file क्रमmat version
 *	@checksum - info + image
 *	@reserved - reserved
 *	@descr - description string
 *	@info - firmware module info
 *	@image - code image (variable size)
 */
काष्ठा cycx_firmware अणु
	अक्षर		    signature[80];
	अचिन्हित लघु	    version;
	अचिन्हित लघु	    checksum;
	अचिन्हित लघु	    reserved[6];
	अक्षर		    descr[CFM_DESCR_LEN];
	काष्ठा cycx_fw_info info;
	अचिन्हित अक्षर	    image[0];
पूर्ण;

काष्ठा cycx_fw_header अणु
	अचिन्हित दीर्घ  reset_size;
	अचिन्हित दीर्घ  data_size;
	अचिन्हित दीर्घ  code_size;
पूर्ण;
#पूर्ण_अगर	/* _CYCX_CFM_H */
