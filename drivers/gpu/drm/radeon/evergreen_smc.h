<शैली गुरु>
/*
 * Copyright 2011 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#अगर_अघोषित __EVERGREEN_SMC_H__
#घोषणा __EVERGREEN_SMC_H__

#समावेश "rv770_smc.h"

#आशय pack(push, 1)

#घोषणा SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE 16

काष्ठा SMC_Evergreen_MCRegisterAddress
अणु
    uपूर्णांक16_t s0;
    uपूर्णांक16_t s1;
पूर्ण;

प्रकार काष्ठा SMC_Evergreen_MCRegisterAddress SMC_Evergreen_MCRegisterAddress;


काष्ठा SMC_Evergreen_MCRegisterSet
अणु
    uपूर्णांक32_t value[SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

प्रकार काष्ठा SMC_Evergreen_MCRegisterSet SMC_Evergreen_MCRegisterSet;

काष्ठा SMC_Evergreen_MCRegisters
अणु
    uपूर्णांक8_t                             last;
    uपूर्णांक8_t                             reserved[3];
    SMC_Evergreen_MCRegisterAddress     address[SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE];
    SMC_Evergreen_MCRegisterSet         data[5];
पूर्ण;

प्रकार काष्ठा SMC_Evergreen_MCRegisters SMC_Evergreen_MCRegisters;

#घोषणा EVERGREEN_SMC_FIRMWARE_HEADER_LOCATION 0x100

#घोषणा EVERGREEN_SMC_FIRMWARE_HEADER_softRegisters   0x8
#घोषणा EVERGREEN_SMC_FIRMWARE_HEADER_stateTable      0xC
#घोषणा EVERGREEN_SMC_FIRMWARE_HEADER_mcRegisterTable 0x20


#आशय pack(pop)

#पूर्ण_अगर
