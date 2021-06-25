<शैली गुरु>
/*
*
* tp3780i.c -- board driver क्रम 3780i on ThinkPads
*
*
* Written By: Mike Sullivan IBM Corporation
*
* Copyright (C) 1999 IBM Corporation
*
* This program is मुक्त software; you can redistribute it and/or modअगरy
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License क्रम more details.
*
* NO WARRANTY
* THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
* solely responsible क्रम determining the appropriateness of using and
* distributing the Program and assumes all risks associated with its
* exercise of rights under this Agreement, including but not limited to
* the risks and costs of program errors, damage to or loss of data,
* programs or equipment, and unavailability or पूर्णांकerruption of operations.
*
* DISCLAIMER OF LIABILITY
* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
* सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES
*
* You should have received a copy of the GNU General Public License
* aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*
* 10/23/2000 - Alpha Release
*	First release to the खुला
*/

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <यंत्र/पन.स>
#समावेश "smapi.h"
#समावेश "mwavedd.h"
#समावेश "tp3780i.h"
#समावेश "3780i.h"
#समावेश "mwavepub.h"

अटल अचिन्हित लघु s_ausThinkpadIrqToField[16] =
	अणु 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x0002, 0x0003, 0xFFFF, 0x0004,
	0xFFFF, 0xFFFF, 0x0005, 0x0006, 0xFFFF, 0xFFFF, 0xFFFF, 0x0007 पूर्ण;
अटल अचिन्हित लघु s_ausThinkpadDmaToField[8] =
	अणु 0x0001, 0x0002, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0003, 0x0004 पूर्ण;
अटल अचिन्हित लघु s_numIrqs = 16, s_numDmas = 8;


अटल व्योम EnableSRAM(THINKPAD_BD_DATA * pBDData)
अणु
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pBDData->rDspSettings;
	अचिन्हित लघु usDspBaseIO = pSettings->usDspBaseIO;
	DSP_GPIO_OUTPUT_DATA_15_8 rGpioOutputData;
	DSP_GPIO_DRIVER_ENABLE_15_8 rGpioDriverEnable;
	DSP_GPIO_MODE_15_8 rGpioMode;

	PRINTK_1(TRACE_TP3780I, "tp3780i::EnableSRAM, entry\n");

	MKWORD(rGpioMode) = ReadMsaCfg(DSP_GpioModeControl_15_8);
	rGpioMode.GpioMode10 = 0;
	WriteMsaCfg(DSP_GpioModeControl_15_8, MKWORD(rGpioMode));

	MKWORD(rGpioDriverEnable) = 0;
	rGpioDriverEnable.Enable10 = true;
	rGpioDriverEnable.Mask10 = true;
	WriteMsaCfg(DSP_GpioDriverEnable_15_8, MKWORD(rGpioDriverEnable));

	MKWORD(rGpioOutputData) = 0;
	rGpioOutputData.Latch10 = 0;
	rGpioOutputData.Mask10 = true;
	WriteMsaCfg(DSP_GpioOutputData_15_8, MKWORD(rGpioOutputData));

	PRINTK_1(TRACE_TP3780I, "tp3780i::EnableSRAM exit\n");
पूर्ण


अटल irqवापस_t UartInterrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	PRINTK_3(TRACE_TP3780I,
		"tp3780i::UartInterrupt entry irq %x dev_id %p\n", irq, dev_id);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t DspInterrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	pMWAVE_DEVICE_DATA pDrvData = &mwave_s_mdd;
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pDrvData->rBDData.rDspSettings;
	अचिन्हित लघु usDspBaseIO = pSettings->usDspBaseIO;
	अचिन्हित लघु usIPCSource = 0, usIsolationMask, usPCNum;

	PRINTK_3(TRACE_TP3780I,
		"tp3780i::DspInterrupt entry irq %x dev_id %p\n", irq, dev_id);

	अगर (dsp3780I_GetIPCSource(usDspBaseIO, &usIPCSource) == 0) अणु
		PRINTK_2(TRACE_TP3780I,
			"tp3780i::DspInterrupt, return from dsp3780i_GetIPCSource, usIPCSource %x\n",
			usIPCSource);
		usIsolationMask = 1;
		क्रम (usPCNum = 1; usPCNum <= 16; usPCNum++) अणु
			अगर (usIPCSource & usIsolationMask) अणु
				usIPCSource &= ~usIsolationMask;
				PRINTK_3(TRACE_TP3780I,
					"tp3780i::DspInterrupt usPCNum %x usIPCSource %x\n",
					usPCNum, usIPCSource);
				अगर (pDrvData->IPCs[usPCNum - 1].usIntCount == 0) अणु
					pDrvData->IPCs[usPCNum - 1].usIntCount = 1;
				पूर्ण
				PRINTK_2(TRACE_TP3780I,
					"tp3780i::DspInterrupt usIntCount %x\n",
					pDrvData->IPCs[usPCNum - 1].usIntCount);
				अगर (pDrvData->IPCs[usPCNum - 1].bIsEnabled == true) अणु
					PRINTK_2(TRACE_TP3780I,
						"tp3780i::DspInterrupt, waking up usPCNum %x\n",
						usPCNum - 1);
					wake_up_पूर्णांकerruptible(&pDrvData->IPCs[usPCNum - 1].ipc_रुको_queue);
				पूर्ण अन्यथा अणु
					PRINTK_2(TRACE_TP3780I,
						"tp3780i::DspInterrupt, no one waiting for IPC %x\n",
						usPCNum - 1);
				पूर्ण
			पूर्ण
			अगर (usIPCSource == 0)
				अवरोध;
			/* try next IPC */
			usIsolationMask = usIsolationMask << 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		PRINTK_1(TRACE_TP3780I,
			"tp3780i::DspInterrupt, return false from dsp3780i_GetIPCSource\n");
	पूर्ण
	PRINTK_1(TRACE_TP3780I, "tp3780i::DspInterrupt exit\n");
	वापस IRQ_HANDLED;
पूर्ण


पूर्णांक tp3780I_InitializeBoardData(THINKPAD_BD_DATA * pBDData)
अणु
	पूर्णांक retval = 0;
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pBDData->rDspSettings;


	PRINTK_2(TRACE_TP3780I, "tp3780i::tp3780I_InitializeBoardData entry pBDData %p\n", pBDData);

	pBDData->bDSPEnabled = false;
	pSettings->bInterruptClaimed = false;

	retval = smapi_init();
	अगर (retval) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE "tp3780i::tp3780I_InitializeBoardData: Error: SMAPI is not available on this machine\n");
	पूर्ण अन्यथा अणु
		अगर (mwave_3780i_irq || mwave_3780i_io || mwave_uart_irq || mwave_uart_io) अणु
			retval = smapi_set_DSP_cfg();
		पूर्ण
	पूर्ण

	PRINTK_2(TRACE_TP3780I, "tp3780i::tp3780I_InitializeBoardData exit retval %x\n", retval);

	वापस retval;
पूर्ण

व्योम tp3780I_Cleanup(THINKPAD_BD_DATA *pBDData)
अणु
	PRINTK_2(TRACE_TP3780I,
		"tp3780i::tp3780I_Cleanup entry and exit pBDData %p\n", pBDData);
पूर्ण

पूर्णांक tp3780I_CalcResources(THINKPAD_BD_DATA * pBDData)
अणु
	SMAPI_DSP_SETTINGS rSmapiInfo;
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pBDData->rDspSettings;

	PRINTK_2(TRACE_TP3780I,
		"tp3780i::tp3780I_CalcResources entry pBDData %p\n", pBDData);

	अगर (smapi_query_DSP_cfg(&rSmapiInfo)) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE "tp3780i::tp3780I_CalcResources: Error: Could not query DSP config. Aborting.\n");
		वापस -EIO;
	पूर्ण

	/* Sanity check */
	अगर (
		( rSmapiInfo.usDspIRQ == 0 )
		|| ( rSmapiInfo.usDspBaseIO ==  0 )
		|| ( rSmapiInfo.usUartIRQ ==  0 )
		|| ( rSmapiInfo.usUartBaseIO ==  0 )
	) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE "tp3780i::tp3780I_CalcResources: Error: Illegal resource setting. Aborting.\n");
		वापस -EIO;
	पूर्ण

	pSettings->bDSPEnabled = (rSmapiInfo.bDSPEnabled && rSmapiInfo.bDSPPresent);
	pSettings->bModemEnabled = rSmapiInfo.bModemEnabled;
	pSettings->usDspIrq = rSmapiInfo.usDspIRQ;
	pSettings->usDspDma = rSmapiInfo.usDspDMA;
	pSettings->usDspBaseIO = rSmapiInfo.usDspBaseIO;
	pSettings->usUartIrq = rSmapiInfo.usUartIRQ;
	pSettings->usUartBaseIO = rSmapiInfo.usUartBaseIO;

	pSettings->uDStoreSize = TP_ABILITIES_DATA_SIZE;
	pSettings->uIStoreSize = TP_ABILITIES_INST_SIZE;
	pSettings->uIps = TP_ABILITIES_INTS_PER_SEC;

	अगर (pSettings->bDSPEnabled && pSettings->bModemEnabled && pSettings->usDspIrq == pSettings->usUartIrq) अणु
		pBDData->bShareDspIrq = pBDData->bShareUartIrq = 1;
	पूर्ण अन्यथा अणु
		pBDData->bShareDspIrq = pBDData->bShareUartIrq = 0;
	पूर्ण

	PRINTK_1(TRACE_TP3780I, "tp3780i::tp3780I_CalcResources exit\n");

	वापस 0;
पूर्ण


पूर्णांक tp3780I_ClaimResources(THINKPAD_BD_DATA * pBDData)
अणु
	पूर्णांक retval = 0;
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pBDData->rDspSettings;
	काष्ठा resource *pres;

	PRINTK_2(TRACE_TP3780I,
		"tp3780i::tp3780I_ClaimResources entry pBDData %p\n", pBDData);

	pres = request_region(pSettings->usDspBaseIO, 16, "mwave_3780i");
	अगर ( pres == शून्य ) retval = -EIO;

	अगर (retval) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE "tp3780i::tp3780I_ClaimResources: Error: Could not claim I/O region starting at %x\n", pSettings->usDspBaseIO);
		retval = -EIO;
	पूर्ण

	PRINTK_2(TRACE_TP3780I, "tp3780i::tp3780I_ClaimResources exit retval %x\n", retval);

	वापस retval;
पूर्ण

पूर्णांक tp3780I_ReleaseResources(THINKPAD_BD_DATA * pBDData)
अणु
	पूर्णांक retval = 0;
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pBDData->rDspSettings;

	PRINTK_2(TRACE_TP3780I,
		"tp3780i::tp3780I_ReleaseResources entry pBDData %p\n", pBDData);

	release_region(pSettings->usDspBaseIO & (~3), 16);

	अगर (pSettings->bInterruptClaimed) अणु
		मुक्त_irq(pSettings->usDspIrq, शून्य);
		pSettings->bInterruptClaimed = false;
	पूर्ण

	PRINTK_2(TRACE_TP3780I,
		"tp3780i::tp3780I_ReleaseResources exit retval %x\n", retval);

	वापस retval;
पूर्ण



पूर्णांक tp3780I_EnableDSP(THINKPAD_BD_DATA * pBDData)
अणु
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pBDData->rDspSettings;
	bool bDSPPoweredUp = false, bInterruptAllocated = false;

	PRINTK_2(TRACE_TP3780I, "tp3780i::tp3780I_EnableDSP entry pBDData %p\n", pBDData);

	अगर (pBDData->bDSPEnabled) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE "tp3780i::tp3780I_EnableDSP: Error: DSP already enabled!\n");
		जाओ निकास_cleanup;
	पूर्ण

	अगर (!pSettings->bDSPEnabled) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE "tp3780::tp3780I_EnableDSP: Error: pSettings->bDSPEnabled not set\n");
		जाओ निकास_cleanup;
	पूर्ण

	अगर (
		(pSettings->usDspIrq >= s_numIrqs)
		|| (pSettings->usDspDma >= s_numDmas)
		|| (s_ausThinkpadIrqToField[pSettings->usDspIrq] == 0xFFFF)
		|| (s_ausThinkpadDmaToField[pSettings->usDspDma] == 0xFFFF)
	) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE "tp3780i::tp3780I_EnableDSP: Error: invalid irq %x\n", pSettings->usDspIrq);
		जाओ निकास_cleanup;
	पूर्ण

	अगर (
		((pSettings->usDspBaseIO & 0xF00F) != 0)
		|| (pSettings->usDspBaseIO & 0x0FF0) == 0
	) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE "tp3780i::tp3780I_EnableDSP: Error: Invalid DSP base I/O address %x\n", pSettings->usDspBaseIO);
		जाओ निकास_cleanup;
	पूर्ण

	अगर (pSettings->bModemEnabled) अणु
		अगर (
			pSettings->usUartIrq >= s_numIrqs
			|| s_ausThinkpadIrqToField[pSettings->usUartIrq] == 0xFFFF
		) अणु
			PRINTK_ERROR(KERN_ERR_MWAVE "tp3780i::tp3780I_EnableDSP: Error: Invalid UART IRQ %x\n", pSettings->usUartIrq);
			जाओ निकास_cleanup;
		पूर्ण
		चयन (pSettings->usUartBaseIO) अणु
			हाल 0x03F8:
			हाल 0x02F8:
			हाल 0x03E8:
			हाल 0x02E8:
				अवरोध;

			शेष:
				PRINTK_ERROR("tp3780i::tp3780I_EnableDSP: Error: Invalid UART base I/O address %x\n", pSettings->usUartBaseIO);
				जाओ निकास_cleanup;
		पूर्ण
	पूर्ण

	pSettings->bDspIrqActiveLow = pSettings->bDspIrqPulse = true;
	pSettings->bUartIrqActiveLow = pSettings->bUartIrqPulse = true;

	अगर (pBDData->bShareDspIrq) अणु
		pSettings->bDspIrqActiveLow = false;
	पूर्ण
	अगर (pBDData->bShareUartIrq) अणु
		pSettings->bUartIrqActiveLow = false;
	पूर्ण

	pSettings->usNumTransfers = TP_CFG_NumTransfers;
	pSettings->usReRequest = TP_CFG_RerequestTimer;
	pSettings->bEnableMEMCS16 = TP_CFG_MEMCS16;
	pSettings->usIsaMemCmdWidth = TP_CFG_IsaMemCmdWidth;
	pSettings->bGateIOCHRDY = TP_CFG_GateIOCHRDY;
	pSettings->bEnablePwrMgmt = TP_CFG_EnablePwrMgmt;
	pSettings->usHBusTimerLoadValue = TP_CFG_HBusTimerValue;
	pSettings->bDisableLBusTimeout = TP_CFG_DisableLBusTimeout;
	pSettings->usN_Divisor = TP_CFG_N_Divisor;
	pSettings->usM_Multiplier = TP_CFG_M_Multiplier;
	pSettings->bPllBypass = TP_CFG_PllBypass;
	pSettings->usChipletEnable = TP_CFG_ChipletEnable;

	अगर (request_irq(pSettings->usUartIrq, &UartInterrupt, 0, "mwave_uart", शून्य)) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE "tp3780i::tp3780I_EnableDSP: Error: Could not get UART IRQ %x\n", pSettings->usUartIrq);
		जाओ निकास_cleanup;
	पूर्ण अन्यथा अणु		/* no conflict just release */
		मुक्त_irq(pSettings->usUartIrq, शून्य);
	पूर्ण

	अगर (request_irq(pSettings->usDspIrq, &DspInterrupt, 0, "mwave_3780i", शून्य)) अणु
		PRINTK_ERROR("tp3780i::tp3780I_EnableDSP: Error: Could not get 3780i IRQ %x\n", pSettings->usDspIrq);
		जाओ निकास_cleanup;
	पूर्ण अन्यथा अणु
		PRINTK_3(TRACE_TP3780I,
			"tp3780i::tp3780I_EnableDSP, got interrupt %x bShareDspIrq %x\n",
			pSettings->usDspIrq, pBDData->bShareDspIrq);
		bInterruptAllocated = true;
		pSettings->bInterruptClaimed = true;
	पूर्ण

	smapi_set_DSP_घातer_state(false);
	अगर (smapi_set_DSP_घातer_state(true)) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE "tp3780i::tp3780I_EnableDSP: Error: smapi_set_DSP_power_state(true) failed\n");
		जाओ निकास_cleanup;
	पूर्ण अन्यथा अणु
		bDSPPoweredUp = true;
	पूर्ण

	अगर (dsp3780I_EnableDSP(pSettings, s_ausThinkpadIrqToField, s_ausThinkpadDmaToField)) अणु
		PRINTK_ERROR("tp3780i::tp3780I_EnableDSP: Error: dsp7880I_EnableDSP() failed\n");
		जाओ निकास_cleanup;
	पूर्ण

	EnableSRAM(pBDData);

	pBDData->bDSPEnabled = true;

	PRINTK_1(TRACE_TP3780I, "tp3780i::tp3780I_EnableDSP exit\n");

	वापस 0;

निकास_cleanup:
	PRINTK_ERROR("tp3780i::tp3780I_EnableDSP: Cleaning up\n");
	अगर (bDSPPoweredUp)
		smapi_set_DSP_घातer_state(false);
	अगर (bInterruptAllocated) अणु
		मुक्त_irq(pSettings->usDspIrq, शून्य);
		pSettings->bInterruptClaimed = false;
	पूर्ण
	वापस -EIO;
पूर्ण


पूर्णांक tp3780I_DisableDSP(THINKPAD_BD_DATA * pBDData)
अणु
	पूर्णांक retval = 0;
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pBDData->rDspSettings;

	PRINTK_2(TRACE_TP3780I, "tp3780i::tp3780I_DisableDSP entry pBDData %p\n", pBDData);

	अगर (pBDData->bDSPEnabled) अणु
		dsp3780I_DisableDSP(&pBDData->rDspSettings);
		अगर (pSettings->bInterruptClaimed) अणु
			मुक्त_irq(pSettings->usDspIrq, शून्य);
			pSettings->bInterruptClaimed = false;
		पूर्ण
		smapi_set_DSP_घातer_state(false);
		pBDData->bDSPEnabled = false;
	पूर्ण

	PRINTK_2(TRACE_TP3780I, "tp3780i::tp3780I_DisableDSP exit retval %x\n", retval);

	वापस retval;
पूर्ण


पूर्णांक tp3780I_ResetDSP(THINKPAD_BD_DATA * pBDData)
अणु
	पूर्णांक retval = 0;
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pBDData->rDspSettings;

	PRINTK_2(TRACE_TP3780I, "tp3780i::tp3780I_ResetDSP entry pBDData %p\n",
		pBDData);

	अगर (dsp3780I_Reset(pSettings) == 0) अणु
		EnableSRAM(pBDData);
	पूर्ण अन्यथा अणु
		retval = -EIO;
	पूर्ण

	PRINTK_2(TRACE_TP3780I, "tp3780i::tp3780I_ResetDSP exit retval %x\n", retval);

	वापस retval;
पूर्ण


पूर्णांक tp3780I_StartDSP(THINKPAD_BD_DATA * pBDData)
अणु
	पूर्णांक retval = 0;
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pBDData->rDspSettings;

	PRINTK_2(TRACE_TP3780I, "tp3780i::tp3780I_StartDSP entry pBDData %p\n", pBDData);

	अगर (dsp3780I_Run(pSettings) == 0) अणु
		// @BUG @TBD EnableSRAM(pBDData);
	पूर्ण अन्यथा अणु
		retval = -EIO;
	पूर्ण

	PRINTK_2(TRACE_TP3780I, "tp3780i::tp3780I_StartDSP exit retval %x\n", retval);

	वापस retval;
पूर्ण


पूर्णांक tp3780I_QueryAbilities(THINKPAD_BD_DATA * pBDData, MW_ABILITIES * pAbilities)
अणु
	पूर्णांक retval = 0;

	PRINTK_2(TRACE_TP3780I,
		"tp3780i::tp3780I_QueryAbilities entry pBDData %p\n", pBDData);

	स_रखो(pAbilities, 0, माप(*pAbilities));
	/* fill out standard स्थिरant fields */
	pAbilities->instr_per_sec = pBDData->rDspSettings.uIps;
	pAbilities->data_size = pBDData->rDspSettings.uDStoreSize;
	pAbilities->inst_size = pBDData->rDspSettings.uIStoreSize;
	pAbilities->bus_dma_bw = pBDData->rDspSettings.uDmaBandwidth;

	/* fill out dynamically determined fields */
	pAbilities->component_list[0] = 0x00010000 | MW_ADC_MASK;
	pAbilities->component_list[1] = 0x00010000 | MW_ACI_MASK;
	pAbilities->component_list[2] = 0x00010000 | MW_AIC1_MASK;
	pAbilities->component_list[3] = 0x00010000 | MW_AIC2_MASK;
	pAbilities->component_list[4] = 0x00010000 | MW_CDDAC_MASK;
	pAbilities->component_list[5] = 0x00010000 | MW_MIDI_MASK;
	pAbilities->component_list[6] = 0x00010000 | MW_UART_MASK;
	pAbilities->component_count = 7;

	/* Fill out Mwave OS and BIOS task names */

	स_नकल(pAbilities->mwave_os_name, TP_ABILITIES_MWAVEOS_NAME,
		माप(TP_ABILITIES_MWAVEOS_NAME));
	स_नकल(pAbilities->bios_task_name, TP_ABILITIES_BIOSTASK_NAME,
		माप(TP_ABILITIES_BIOSTASK_NAME));

	PRINTK_1(TRACE_TP3780I,
		"tp3780i::tp3780I_QueryAbilities exit retval=SUCCESSFUL\n");

	वापस retval;
पूर्ण

पूर्णांक tp3780I_ReadWriteDspDStore(THINKPAD_BD_DATA * pBDData, अचिन्हित पूर्णांक uOpcode,
                               व्योम __user *pvBuffer, अचिन्हित पूर्णांक uCount,
                               अचिन्हित दीर्घ ulDSPAddr)
अणु
	पूर्णांक retval = 0;
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pBDData->rDspSettings;
	अचिन्हित लघु usDspBaseIO = pSettings->usDspBaseIO;
	bool bRC = 0;

	PRINTK_6(TRACE_TP3780I,
		"tp3780i::tp3780I_ReadWriteDspDStore entry pBDData %p, uOpcode %x, pvBuffer %p, uCount %x, ulDSPAddr %lx\n",
		pBDData, uOpcode, pvBuffer, uCount, ulDSPAddr);

	अगर (pBDData->bDSPEnabled) अणु
		चयन (uOpcode) अणु
		हाल IOCTL_MW_READ_DATA:
			bRC = dsp3780I_ReadDStore(usDspBaseIO, pvBuffer, uCount, ulDSPAddr);
			अवरोध;

		हाल IOCTL_MW_READCLEAR_DATA:
			bRC = dsp3780I_ReadAndClearDStore(usDspBaseIO, pvBuffer, uCount, ulDSPAddr);
			अवरोध;

		हाल IOCTL_MW_WRITE_DATA:
			bRC = dsp3780I_WriteDStore(usDspBaseIO, pvBuffer, uCount, ulDSPAddr);
			अवरोध;
		पूर्ण
	पूर्ण

	retval = (bRC) ? -EIO : 0;
	PRINTK_2(TRACE_TP3780I, "tp3780i::tp3780I_ReadWriteDspDStore exit retval %x\n", retval);

	वापस retval;
पूर्ण


पूर्णांक tp3780I_ReadWriteDspIStore(THINKPAD_BD_DATA * pBDData, अचिन्हित पूर्णांक uOpcode,
                               व्योम __user *pvBuffer, अचिन्हित पूर्णांक uCount,
                               अचिन्हित दीर्घ ulDSPAddr)
अणु
	पूर्णांक retval = 0;
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pBDData->rDspSettings;
	अचिन्हित लघु usDspBaseIO = pSettings->usDspBaseIO;
	bool bRC = 0;

	PRINTK_6(TRACE_TP3780I,
		"tp3780i::tp3780I_ReadWriteDspIStore entry pBDData %p, uOpcode %x, pvBuffer %p, uCount %x, ulDSPAddr %lx\n",
		pBDData, uOpcode, pvBuffer, uCount, ulDSPAddr);

	अगर (pBDData->bDSPEnabled) अणु
		चयन (uOpcode) अणु
		हाल IOCTL_MW_READ_INST:
			bRC = dsp3780I_ReadIStore(usDspBaseIO, pvBuffer, uCount, ulDSPAddr);
			अवरोध;

		हाल IOCTL_MW_WRITE_INST:
			bRC = dsp3780I_WriteIStore(usDspBaseIO, pvBuffer, uCount, ulDSPAddr);
			अवरोध;
		पूर्ण
	पूर्ण

	retval = (bRC) ? -EIO : 0;

	PRINTK_2(TRACE_TP3780I,
		"tp3780i::tp3780I_ReadWriteDspIStore exit retval %x\n", retval);

	वापस retval;
पूर्ण

