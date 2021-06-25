<शैली गुरु>
 /*
  * PMC-Sierra SPC 8001 SAS/SATA based host adapters driver
  *
  * Copyright (c) 2008-2009 USI Co., Ltd.
  * All rights reserved.
  *
  * Redistribution and use in source and binary क्रमms, with or without
  * modअगरication, are permitted provided that the following conditions
  * are met:
  * 1. Redistributions of source code must retain the above copyright
  *    notice, this list of conditions, and the following disclaimer,
  *    without modअगरication.
  * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
  *    substantially similar to the "NO WARRANTY" disclaimer below
  *    ("Disclaimer") and any redistribution must be conditioned upon
  *    including a substantially similar Disclaimer requirement क्रम further
  *    binary redistribution.
  * 3. Neither the names of the above-listed copyright holders nor the names
  *    of any contributors may be used to enकरोrse or promote products derived
  *    from this software without specअगरic prior written permission.
  *
  * Alternatively, this software may be distributed under the terms of the
  * GNU General Public License ("GPL") version 2 as published by the Free
  * Software Foundation.
  *
  * NO WARRANTY
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
  * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
  * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  * POSSIBILITY OF SUCH DAMAGES.
  *
  */

#अगर_अघोषित PM8001_CTL_H_INCLUDED
#घोषणा PM8001_CTL_H_INCLUDED

#घोषणा IOCTL_BUF_SIZE		4096
#घोषणा HEADER_LEN			28
#घोषणा SIZE_OFFSET			16

#घोषणा BIOSOFFSET			56
#घोषणा BIOS_OFFSET_LIMIT		61

#घोषणा FLASH_OK                        0x000000
#घोषणा FAIL_OPEN_BIOS_खाता             0x000100
#घोषणा FAIL_खाता_SIZE                  0x000a00
#घोषणा FAIL_PARAMETERS                 0x000b00
#घोषणा FAIL_OUT_MEMORY                 0x000c00
#घोषणा FLASH_IN_PROGRESS               0x001000

#घोषणा IB_OB_READ_TIMES                256
#घोषणा SYSFS_OFFSET                    1024
#घोषणा PM80XX_IB_OB_QUEUE_SIZE         (32 * 1024)
#घोषणा PM8001_IB_OB_QUEUE_SIZE         (16 * 1024)

अटल अंतरभूत u32 pm8001_ctl_aap1_memmap(u8 *ptr, पूर्णांक idx, पूर्णांक off)
अणु
	वापस *(u32 *)(ptr + idx * 32 + off);
पूर्ण
#पूर्ण_अगर /* PM8001_CTL_H_INCLUDED */

