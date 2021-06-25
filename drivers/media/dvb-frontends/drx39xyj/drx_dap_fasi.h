<शैली गुरु>
/*
  Copyright (c), 2004-2005,2007-2010 Trident Microप्रणालीs, Inc.
  All rights reserved.

  Redistribution and use in source and binary क्रमms, with or without
  modअगरication, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  * Redistributions in binary क्रमm must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the करोcumentation
	and/or other materials provided with the distribution.
  * Neither the name of Trident Microप्रणालीs nor Hauppauge Computer Works
    nor the names of its contributors may be used to enकरोrse or promote
	products derived from this software without specअगरic prior written
	permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

/*******************************************************************************
* खाताNAME: $Id: drx_dap_fasi.h,v 1.5 2009/07/07 14:21:40 justin Exp $
*
* DESCRIPTION:
* Part of DRX driver.
* Data access protocol: Fast Access Sequential Interface (fasi)
* Fast access, because of लघु addressing क्रमmat (16 instead of 32 bits addr)
* Sequential, because of I2C.
*
* USAGE:
* Include.
*
* NOTES:
*
*
*******************************************************************************/

/*-------- compilation control चयनes --------------------------------------*/

#अगर_अघोषित __DRX_DAP_FASI_H__
#घोषणा __DRX_DAP_FASI_H__

/*-------- Required includes -------------------------------------------------*/

#समावेश "drx_driver.h"

/*-------- Defines, configuring the API --------------------------------------*/

/********************************************
* Allowed address क्रमmats
********************************************/

/*
* Comments about लघु/दीर्घ addressing क्रमmat:
*
* The DAP FASI offers दीर्घ address क्रमmat (4 bytes) and लघु address क्रमmat
* (2 bytes). The DAP can operate in 3 modes:
* (1) only लघु
* (2) only दीर्घ
* (3) both दीर्घ and लघु but लघु preferred and दीर्घ only when necessary
*
* These modes must be selected compile समय via compile चयनes.
* Compile चयन settings क्रम the dअगरferent modes:
* (1) DRXDAPFASI_LONG_ADDR_ALLOWED=0, DRXDAPFASI_SHORT_ADDR_ALLOWED=1
* (2) DRXDAPFASI_LONG_ADDR_ALLOWED=1, DRXDAPFASI_SHORT_ADDR_ALLOWED=0
* (3) DRXDAPFASI_LONG_ADDR_ALLOWED=1, DRXDAPFASI_SHORT_ADDR_ALLOWED=1
*
* The शेष setting will be (3) both दीर्घ and लघु.
* The शेष setting will need no compile चयनes.
* The शेष setting must be overridden अगर compile चयनes are alपढ़ोy
* defined.
*
*/

/* set शेष */
#अगर !defined(DRXDAPFASI_LONG_ADDR_ALLOWED)
#घोषणा  DRXDAPFASI_LONG_ADDR_ALLOWED 1
#पूर्ण_अगर

/* set शेष */
#अगर !defined(DRXDAPFASI_SHORT_ADDR_ALLOWED)
#घोषणा  DRXDAPFASI_SHORT_ADDR_ALLOWED 1
#पूर्ण_अगर

/* check */
#अगर ((DRXDAPFASI_LONG_ADDR_ALLOWED == 0) && \
      (DRXDAPFASI_SHORT_ADDR_ALLOWED == 0))
#त्रुटि  At least one of लघु- or दीर्घ-addressing क्रमmat must be allowed.
*;				/* illegal statement to क्रमce compiler error */
#पूर्ण_अगर

/********************************************
* Single/master multi master setting
********************************************/
/*
* Comments about SINGLE MASTER/MULTI MASTER  modes:
*
* Consider the two sides:1) the master and 2)the slave.
*
* Master:
* Single/multimaster operation set via DRXDAP_SINGLE_MASTER compile चयन
*  + single master mode means no use of repeated starts
*  + multi master mode means use of repeated starts
*  Default is single master.
*  Default can be overridden by setting the compile चयन DRXDAP_SINGLE_MASTER.
*
* Slave:
* Single/multi master selected via the flags in the FASI protocol.
*  + single master means remember memory address between i2c packets
*  + multimaster means flush memory address between i2c packets
*  Default is single master, DAP FASI changes multi-master setting silently
*  पूर्णांकo single master setting. This cannot be overridden.
*
*/
/* set शेष */
#अगर_अघोषित DRXDAP_SINGLE_MASTER
#घोषणा DRXDAP_SINGLE_MASTER 0
#पूर्ण_अगर

/********************************************
* Chunk/mode checking
********************************************/
/*
* Comments about DRXDAP_MAX_WCHUNKSIZE in single or multi master mode and
* in combination with लघु and दीर्घ addressing क्रमmat. All text below
* assumes दीर्घ addressing क्रमmat. The table also includes inक्रमmation
* क्रम लघु ADDRessing क्रमmat.
*
* In single master mode, data can be written by sending the रेजिस्टर address
* first, then two or four bytes of data in the next packet.
* Because the device address plus a रेजिस्टर address equals five bytes,
* the minimum chunk size must be five.
* If ten-bit I2C device addresses are used, the minimum chunk size must be six,
* because the I2C device address will then occupy two bytes when writing.
*
* Data in single master mode is transferred as follows:
* <S> <devW>  a0  a1  a2  a3  <P>
* <S> <devW>  d0  d1 [d2  d3] <P>
* ..
* or
* ..
* <S> <devW>  a0  a1  a2  a3  <P>
* <S> <devR> --- <P>
*
* In multi-master mode, the data must immediately follow the address (an I2C
* stop resets the पूर्णांकernal address), and hence the minimum chunk size is
* 1 <I2C address> + 4 (रेजिस्टर address) + 2 (data to send) = 7 bytes (8 अगर
* 10-bit I2C device addresses are used).
*
* The 7-bit or 10-bit i2c address parameters is a runसमय parameter.
* The other parameters can be limited via compile समय चयनes.
*
*-------------------------------------------------------------------------------
*
*  Minimum chunk size table (in bytes):
*
*       +----------------+----------------+
*       | 7b i2c addr    | 10b i2c addr   |
*       +----------------+----------------+
*       | single | multi | single | multi |
* ------+--------+-------+--------+-------+
* लघु | 3      | 5     | 4      | 6     |
* दीर्घ  | 5      | 7     | 6      | 8     |
* ------+--------+-------+--------+-------+
*
*/

/* set शेष */
#अगर !defined(DRXDAP_MAX_WCHUNKSIZE)
#घोषणा  DRXDAP_MAX_WCHUNKSIZE 254
#पूर्ण_अगर

/* check */
#अगर ((DRXDAPFASI_LONG_ADDR_ALLOWED == 0) && (DRXDAPFASI_SHORT_ADDR_ALLOWED == 1))
#अगर DRXDAP_SINGLE_MASTER
#घोषणा  DRXDAP_MAX_WCHUNKSIZE_MIN 3
#अन्यथा
#घोषणा  DRXDAP_MAX_WCHUNKSIZE_MIN 5
#पूर्ण_अगर
#अन्यथा
#अगर DRXDAP_SINGLE_MASTER
#घोषणा  DRXDAP_MAX_WCHUNKSIZE_MIN 5
#अन्यथा
#घोषणा  DRXDAP_MAX_WCHUNKSIZE_MIN 7
#पूर्ण_अगर
#पूर्ण_अगर

#अगर  DRXDAP_MAX_WCHUNKSIZE <  DRXDAP_MAX_WCHUNKSIZE_MIN
#अगर ((DRXDAPFASI_LONG_ADDR_ALLOWED == 0) && (DRXDAPFASI_SHORT_ADDR_ALLOWED == 1))
#अगर DRXDAP_SINGLE_MASTER
#त्रुटि  DRXDAP_MAX_WCHUNKSIZE must be at least 3 in single master mode
*;				/* illegal statement to क्रमce compiler error */
#अन्यथा
#त्रुटि  DRXDAP_MAX_WCHUNKSIZE must be at least 5 in multi master mode
*;				/* illegal statement to क्रमce compiler error */
#पूर्ण_अगर
#अन्यथा
#अगर DRXDAP_SINGLE_MASTER
#त्रुटि  DRXDAP_MAX_WCHUNKSIZE must be at least 5 in single master mode
*;				/* illegal statement to क्रमce compiler error */
#अन्यथा
#त्रुटि  DRXDAP_MAX_WCHUNKSIZE must be at least 7 in multi master mode
*;				/* illegal statement to क्रमce compiler error */
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर

/* set शेष */
#अगर !defined(DRXDAP_MAX_RCHUNKSIZE)
#घोषणा  DRXDAP_MAX_RCHUNKSIZE 254
#पूर्ण_अगर

/* check */
#अगर  DRXDAP_MAX_RCHUNKSIZE < 2
#त्रुटि  DRXDAP_MAX_RCHUNKSIZE must be at least 2
*;				/* illegal statement to क्रमce compiler error */
#पूर्ण_अगर

/* check */
#अगर  DRXDAP_MAX_RCHUNKSIZE & 1
#त्रुटि  DRXDAP_MAX_RCHUNKSIZE must be even
*;				/* illegal statement to क्रमce compiler error */
#पूर्ण_अगर

/*-------- Public API functions ----------------------------------------------*/

बाह्य काष्ठा drx_access_func drx_dap_fasi_funct_g;

#घोषणा DRXDAP_FASI_RMW           0x10000000
#घोषणा DRXDAP_FASI_BROADCAST     0x20000000
#घोषणा DRXDAP_FASI_CLEARCRC      0x80000000
#घोषणा DRXDAP_FASI_SINGLE_MASTER 0xC0000000
#घोषणा DRXDAP_FASI_MULTI_MASTER  0x40000000
#घोषणा DRXDAP_FASI_SMM_SWITCH    0x40000000	/* single/multi master चयन */
#घोषणा DRXDAP_FASI_MODEFLAGS     0xC0000000
#घोषणा DRXDAP_FASI_FLAGS         0xF0000000

#घोषणा DRXDAP_FASI_ADDR2BLOCK(addr)  (((addr)>>22)&0x3F)
#घोषणा DRXDAP_FASI_ADDR2BANK(addr)   (((addr)>>16)&0x3F)
#घोषणा DRXDAP_FASI_ADDR2OFFSET(addr) ((addr)&0x7FFF)

#घोषणा DRXDAP_FASI_SHORT_FORMAT(addr)     (((addr) & 0xFC30FF80) == 0)
#घोषणा DRXDAP_FASI_LONG_FORMAT(addr)      (((addr) & 0xFC30FF80) != 0)
#घोषणा DRXDAP_FASI_OFFSET_TOO_LARGE(addr) (((addr) & 0x00008000) != 0)

#पूर्ण_अगर				/* __DRX_DAP_FASI_H__ */
