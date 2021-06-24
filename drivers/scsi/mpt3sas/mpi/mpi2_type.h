<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright 2000-2014 Avago Technologies.  All rights reserved.
 *
 *
 *           Name:  mpi2_type.h
 *          Title:  MPI basic type definitions
 *  Creation Date:  August 16, 2006
 *
 *    mpi2_type.h Version:  02.00.01
 *
 *  Version History
 *  ---------------
 *
 *  Date      Version   Description
 *  --------  --------  ------------------------------------------------------
 *  04-30-07  02.00.00  Corresponds to Fusion-MPT MPI Specअगरication Rev A.
 *  11-18-14  02.00.01  Updated copyright inक्रमmation.
 *  --------------------------------------------------------------------------
 */

#अगर_अघोषित MPI2_TYPE_H
#घोषणा MPI2_TYPE_H

/*******************************************************************************
 * Define * अगर it hasn't alपढ़ोy been defined. By शेष
 * * is defined to be a near poपूर्णांकer. MPI2_POINTER can be defined as
 * a far poपूर्णांकer by defining * as "far *" beक्रमe this header file is
 * included.
 */

/* the basic types may have alपढ़ोy been included by mpi_type.h */
#अगर_अघोषित MPI_TYPE_H
/*****************************************************************************
*
*               Basic Types
*
*****************************************************************************/

प्रकार u8 U8;
प्रकार __le16 U16;
प्रकार __le32 U32;
प्रकार __le64 U64 __attribute__ ((aligned(4)));

/*****************************************************************************
*
*               Poपूर्णांकer Types
*
*****************************************************************************/

प्रकार U8 *PU8;
प्रकार U16 *PU16;
प्रकार U32 *PU32;
प्रकार U64 *PU64;

#पूर्ण_अगर

#पूर्ण_अगर
