<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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

#अगर_अघोषित SMU8_H
#घोषणा SMU8_H

#आशय pack(push, 1)

#घोषणा ENABLE_DEBUG_FEATURES

काष्ठा SMU8_Firmware_Header अणु
	uपूर्णांक32_t Version;
	uपूर्णांक32_t ImageSize;
	uपूर्णांक32_t CodeSize;
	uपूर्णांक32_t HeaderSize;
	uपूर्णांक32_t EntryPoपूर्णांक;
	uपूर्णांक32_t Rtos;
	uपूर्णांक32_t UcodeLoadStatus;
	uपूर्णांक32_t DpmTable;
	uपूर्णांक32_t FanTable;
	uपूर्णांक32_t PmFuseTable;
	uपूर्णांक32_t Globals;
	uपूर्णांक32_t Reserved[20];
	uपूर्णांक32_t Signature;
पूर्ण;

काष्ठा SMU8_MulसमयdiaPowerLogData अणु
	uपूर्णांक32_t avgTotalPower;
	uपूर्णांक32_t avgGpuPower;
	uपूर्णांक32_t avgUvdPower;
	uपूर्णांक32_t avgVcePower;

	uपूर्णांक32_t avgSclk;
	uपूर्णांक32_t avgDclk;
	uपूर्णांक32_t avgVclk;
	uपूर्णांक32_t avgEclk;

	uपूर्णांक32_t startTimeHi;
	uपूर्णांक32_t startTimeLo;

	uपूर्णांक32_t endTimeHi;
	uपूर्णांक32_t endTimeLo;
पूर्ण;

#घोषणा SMU8_FIRMWARE_HEADER_LOCATION 0x1FF80
#घोषणा SMU8_UNBCSR_START_ADDR 0xC0100000

#घोषणा SMN_MP1_SRAM_START_ADDR 0x10000000

#आशय pack(pop)

#पूर्ण_अगर
