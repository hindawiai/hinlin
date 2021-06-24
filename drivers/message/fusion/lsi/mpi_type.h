<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (c) 2000-2008 LSI Corporation.
 *
 *
 *           Name:  mpi_type.h
 *          Title:  MPI Basic type definitions
 *  Creation Date:  June 6, 2000
 *
 *    mpi_type.h Version:  01.05.02
 *
 *  Version History
 *  ---------------
 *
 *  Date      Version   Description
 *  --------  --------  ------------------------------------------------------
 *  05-08-00  00.10.01  Original release क्रम 0.10 spec dated 4/26/2000.
 *  06-06-00  01.00.01  Update version number क्रम 1.0 release.
 *  11-02-00  01.01.01  Original release क्रम post 1.0 work
 *  02-20-01  01.01.02  Added define and अगरdef क्रम MPI_POINTER.
 *  08-08-01  01.02.01  Original release क्रम v1.2 work.
 *  05-11-04  01.03.01  Original release क्रम MPI v1.3.
 *  08-19-04  01.05.01  Original release क्रम MPI v1.5.
 *  --------------------------------------------------------------------------
 */

#अगर_अघोषित MPI_TYPE_H
#घोषणा MPI_TYPE_H


/*******************************************************************************
 * Define MPI_POINTER अगर it hasn't alपढ़ोy been defined. By शेष MPI_POINTER
 * is defined to be a near poपूर्णांकer. MPI_POINTER can be defined as a far poपूर्णांकer
 * by defining MPI_POINTER as "far *" beक्रमe this header file is included.
 */
#अगर_अघोषित MPI_POINTER
#घोषणा MPI_POINTER     *
#पूर्ण_अगर


/*****************************************************************************
*
*               B a s i c    T y p e s
*
*****************************************************************************/

प्रकार चिन्हित   अक्षर   S8;
प्रकार अचिन्हित अक्षर   U8;
प्रकार चिन्हित   लघु  S16;
प्रकार अचिन्हित लघु  U16;


प्रकार पूर्णांक32_t   S32;
प्रकार u_पूर्णांक32_t U32;

प्रकार काष्ठा _S64
अणु
    U32          Low;
    S32          High;
पूर्ण S64;

प्रकार काष्ठा _U64
अणु
    U32          Low;
    U32          High;
पूर्ण U64;


/****************************************************************************/
/*  Poपूर्णांकers                                                                */
/****************************************************************************/

प्रकार S8      *PS8;
प्रकार U8      *PU8;
प्रकार S16     *PS16;
प्रकार U16     *PU16;
प्रकार S32     *PS32;
प्रकार U32     *PU32;
प्रकार S64     *PS64;
प्रकार U64     *PU64;


#पूर्ण_अगर

