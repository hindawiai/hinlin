<शैली गुरु>
/*
*
* 3780i.c -- helper routines क्रम the 3780i DSP
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

#समावेश <linux/kernel.h>
#समावेश <linux/unistd.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/bitops.h>
#समावेश <linux/sched.h>	/* cond_resched() */

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/irq.h>
#समावेश "smapi.h"
#समावेश "mwavedd.h"
#समावेश "3780i.h"

अटल DEFINE_SPINLOCK(dsp_lock);

अटल व्योम PaceMsaAccess(अचिन्हित लघु usDspBaseIO)
अणु
	cond_resched();
	udelay(100);
	cond_resched();
पूर्ण

अचिन्हित लघु dsp3780I_ReadMsaCfg(अचिन्हित लघु usDspBaseIO,
                                   अचिन्हित दीर्घ ulMsaAddr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु val;

	PRINTK_3(TRACE_3780I,
		"3780i::dsp3780I_ReadMsaCfg entry usDspBaseIO %x ulMsaAddr %lx\n",
		usDspBaseIO, ulMsaAddr);

	spin_lock_irqsave(&dsp_lock, flags);
	OutWordDsp(DSP_MsaAddrLow, (अचिन्हित लघु) ulMsaAddr);
	OutWordDsp(DSP_MsaAddrHigh, (अचिन्हित लघु) (ulMsaAddr >> 16));
	val = InWordDsp(DSP_MsaDataDSISHigh);
	spin_unlock_irqrestore(&dsp_lock, flags);

	PRINTK_2(TRACE_3780I, "3780i::dsp3780I_ReadMsaCfg exit val %x\n", val);

	वापस val;
पूर्ण

व्योम dsp3780I_WriteMsaCfg(अचिन्हित लघु usDspBaseIO,
                          अचिन्हित दीर्घ ulMsaAddr, अचिन्हित लघु usValue)
अणु
	अचिन्हित दीर्घ flags;

	PRINTK_4(TRACE_3780I,
		"3780i::dsp3780i_WriteMsaCfg entry usDspBaseIO %x ulMsaAddr %lx usValue %x\n",
		usDspBaseIO, ulMsaAddr, usValue);

	spin_lock_irqsave(&dsp_lock, flags);
	OutWordDsp(DSP_MsaAddrLow, (अचिन्हित लघु) ulMsaAddr);
	OutWordDsp(DSP_MsaAddrHigh, (अचिन्हित लघु) (ulMsaAddr >> 16));
	OutWordDsp(DSP_MsaDataDSISHigh, usValue);
	spin_unlock_irqrestore(&dsp_lock, flags);
पूर्ण

अटल व्योम dsp3780I_WriteGenCfg(अचिन्हित लघु usDspBaseIO, अचिन्हित uIndex,
				 अचिन्हित अक्षर ucValue)
अणु
	DSP_ISA_SLAVE_CONTROL rSlaveControl;
	DSP_ISA_SLAVE_CONTROL rSlaveControl_Save;


	PRINTK_4(TRACE_3780I,
		"3780i::dsp3780i_WriteGenCfg entry usDspBaseIO %x uIndex %x ucValue %x\n",
		usDspBaseIO, uIndex, ucValue);

	MKBYTE(rSlaveControl) = InByteDsp(DSP_IsaSlaveControl);

	PRINTK_2(TRACE_3780I,
		"3780i::dsp3780i_WriteGenCfg rSlaveControl %x\n",
		MKBYTE(rSlaveControl));

	rSlaveControl_Save = rSlaveControl;
	rSlaveControl.ConfigMode = true;

	PRINTK_2(TRACE_3780I,
		"3780i::dsp3780i_WriteGenCfg entry rSlaveControl+ConfigMode %x\n",
		MKBYTE(rSlaveControl));

	OutByteDsp(DSP_IsaSlaveControl, MKBYTE(rSlaveControl));
	OutByteDsp(DSP_ConfigAddress, (अचिन्हित अक्षर) uIndex);
	OutByteDsp(DSP_ConfigData, ucValue);
	OutByteDsp(DSP_IsaSlaveControl, MKBYTE(rSlaveControl_Save));

	PRINTK_1(TRACE_3780I, "3780i::dsp3780i_WriteGenCfg exit\n");


पूर्ण

#अगर 0
अचिन्हित अक्षर dsp3780I_ReadGenCfg(अचिन्हित लघु usDspBaseIO,
                                  अचिन्हित uIndex)
अणु
	DSP_ISA_SLAVE_CONTROL rSlaveControl;
	DSP_ISA_SLAVE_CONTROL rSlaveControl_Save;
	अचिन्हित अक्षर ucValue;


	PRINTK_3(TRACE_3780I,
		"3780i::dsp3780i_ReadGenCfg entry usDspBaseIO %x uIndex %x\n",
		usDspBaseIO, uIndex);

	MKBYTE(rSlaveControl) = InByteDsp(DSP_IsaSlaveControl);
	rSlaveControl_Save = rSlaveControl;
	rSlaveControl.ConfigMode = true;
	OutByteDsp(DSP_IsaSlaveControl, MKBYTE(rSlaveControl));
	OutByteDsp(DSP_ConfigAddress, (अचिन्हित अक्षर) uIndex);
	ucValue = InByteDsp(DSP_ConfigData);
	OutByteDsp(DSP_IsaSlaveControl, MKBYTE(rSlaveControl_Save));

	PRINTK_2(TRACE_3780I,
		"3780i::dsp3780i_ReadGenCfg exit ucValue %x\n", ucValue);


	वापस ucValue;
पूर्ण
#पूर्ण_अगर  /*  0  */

पूर्णांक dsp3780I_EnableDSP(DSP_3780I_CONFIG_SETTINGS * pSettings,
                       अचिन्हित लघु *pIrqMap,
                       अचिन्हित लघु *pDmaMap)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु usDspBaseIO = pSettings->usDspBaseIO;
	पूर्णांक i;
	DSP_UART_CFG_1 rUartCfg1;
	DSP_UART_CFG_2 rUartCfg2;
	DSP_HBRIDGE_CFG_1 rHBridgeCfg1;
	DSP_HBRIDGE_CFG_2 rHBridgeCfg2;
	DSP_BUSMASTER_CFG_1 rBusmasterCfg1;
	DSP_BUSMASTER_CFG_2 rBusmasterCfg2;
	DSP_ISA_PROT_CFG rIsaProtCfg;
	DSP_POWER_MGMT_CFG rPowerMgmtCfg;
	DSP_HBUS_TIMER_CFG rHBusTimerCfg;
	DSP_LBUS_TIMEOUT_DISABLE rLBusTimeoutDisable;
	DSP_CHIP_RESET rChipReset;
	DSP_CLOCK_CONTROL_1 rClockControl1;
	DSP_CLOCK_CONTROL_2 rClockControl2;
	DSP_ISA_SLAVE_CONTROL rSlaveControl;
	DSP_HBRIDGE_CONTROL rHBridgeControl;
	अचिन्हित लघु ChipID = 0;
	अचिन्हित लघु tval;


	PRINTK_2(TRACE_3780I,
		"3780i::dsp3780I_EnableDSP entry pSettings->bDSPEnabled %x\n",
		pSettings->bDSPEnabled);


	अगर (!pSettings->bDSPEnabled) अणु
		PRINTK_ERROR( KERN_ERR "3780i::dsp3780I_EnableDSP: Error: DSP not enabled. Aborting.\n" );
		वापस -EIO;
	पूर्ण


	PRINTK_2(TRACE_3780I,
		"3780i::dsp3780i_EnableDSP entry pSettings->bModemEnabled %x\n",
		pSettings->bModemEnabled);

	अगर (pSettings->bModemEnabled) अणु
		rUartCfg1.Reserved = rUartCfg2.Reserved = 0;
		rUartCfg1.IrqActiveLow = pSettings->bUartIrqActiveLow;
		rUartCfg1.IrqPulse = pSettings->bUartIrqPulse;
		rUartCfg1.Irq =
			(अचिन्हित अक्षर) pIrqMap[pSettings->usUartIrq];
		चयन (pSettings->usUartBaseIO) अणु
		हाल 0x03F8:
			rUartCfg1.BaseIO = 0;
			अवरोध;
		हाल 0x02F8:
			rUartCfg1.BaseIO = 1;
			अवरोध;
		हाल 0x03E8:
			rUartCfg1.BaseIO = 2;
			अवरोध;
		हाल 0x02E8:
			rUartCfg1.BaseIO = 3;
			अवरोध;
		पूर्ण
		rUartCfg2.Enable = true;
	पूर्ण

	rHBridgeCfg1.Reserved = rHBridgeCfg2.Reserved = 0;
	rHBridgeCfg1.IrqActiveLow = pSettings->bDspIrqActiveLow;
	rHBridgeCfg1.IrqPulse = pSettings->bDspIrqPulse;
	rHBridgeCfg1.Irq = (अचिन्हित अक्षर) pIrqMap[pSettings->usDspIrq];
	rHBridgeCfg1.AccessMode = 1;
	rHBridgeCfg2.Enable = true;


	rBusmasterCfg2.Reserved = 0;
	rBusmasterCfg1.Dma = (अचिन्हित अक्षर) pDmaMap[pSettings->usDspDma];
	rBusmasterCfg1.NumTransfers =
		(अचिन्हित अक्षर) pSettings->usNumTransfers;
	rBusmasterCfg1.ReRequest = (अचिन्हित अक्षर) pSettings->usReRequest;
	rBusmasterCfg1.MEMCS16 = pSettings->bEnableMEMCS16;
	rBusmasterCfg2.IsaMemCmdWidth =
		(अचिन्हित अक्षर) pSettings->usIsaMemCmdWidth;


	rIsaProtCfg.Reserved = 0;
	rIsaProtCfg.GateIOCHRDY = pSettings->bGateIOCHRDY;

	rPowerMgmtCfg.Reserved = 0;
	rPowerMgmtCfg.Enable = pSettings->bEnablePwrMgmt;

	rHBusTimerCfg.LoadValue =
		(अचिन्हित अक्षर) pSettings->usHBusTimerLoadValue;

	rLBusTimeoutDisable.Reserved = 0;
	rLBusTimeoutDisable.DisableTimeout =
		pSettings->bDisableLBusTimeout;

	MKWORD(rChipReset) = ~pSettings->usChipletEnable;

	rClockControl1.Reserved1 = rClockControl1.Reserved2 = 0;
	rClockControl1.N_Divisor = pSettings->usN_Divisor;
	rClockControl1.M_Multiplier = pSettings->usM_Multiplier;

	rClockControl2.Reserved = 0;
	rClockControl2.PllBypass = pSettings->bPllBypass;

	/* Issue a soft reset to the chip */
	/* Note: Since we may be coming in with 3780i घड़ीs suspended, we must keep
	* soft-reset active क्रम 10ms.
	*/
	rSlaveControl.ClockControl = 0;
	rSlaveControl.SoftReset = true;
	rSlaveControl.ConfigMode = false;
	rSlaveControl.Reserved = 0;

	PRINTK_4(TRACE_3780I,
		"3780i::dsp3780i_EnableDSP usDspBaseIO %x index %x taddr %x\n",
		usDspBaseIO, DSP_IsaSlaveControl,
		usDspBaseIO + DSP_IsaSlaveControl);

	PRINTK_2(TRACE_3780I,
		"3780i::dsp3780i_EnableDSP rSlaveContrl %x\n",
		MKWORD(rSlaveControl));

	spin_lock_irqsave(&dsp_lock, flags);
	OutWordDsp(DSP_IsaSlaveControl, MKWORD(rSlaveControl));
	MKWORD(tval) = InWordDsp(DSP_IsaSlaveControl);

	PRINTK_2(TRACE_3780I,
		"3780i::dsp3780i_EnableDSP rSlaveControl 2 %x\n", tval);


	क्रम (i = 0; i < 11; i++)
		udelay(2000);

	rSlaveControl.SoftReset = false;
	OutWordDsp(DSP_IsaSlaveControl, MKWORD(rSlaveControl));

	MKWORD(tval) = InWordDsp(DSP_IsaSlaveControl);

	PRINTK_2(TRACE_3780I,
		"3780i::dsp3780i_EnableDSP rSlaveControl 3 %x\n", tval);


	/* Program our general configuration रेजिस्टरs */
	WriteGenCfg(DSP_HBridgeCfg1Index, MKBYTE(rHBridgeCfg1));
	WriteGenCfg(DSP_HBridgeCfg2Index, MKBYTE(rHBridgeCfg2));
	WriteGenCfg(DSP_BusMasterCfg1Index, MKBYTE(rBusmasterCfg1));
	WriteGenCfg(DSP_BusMasterCfg2Index, MKBYTE(rBusmasterCfg2));
	WriteGenCfg(DSP_IsaProtCfgIndex, MKBYTE(rIsaProtCfg));
	WriteGenCfg(DSP_PowerMgCfgIndex, MKBYTE(rPowerMgmtCfg));
	WriteGenCfg(DSP_HBusTimerCfgIndex, MKBYTE(rHBusTimerCfg));

	अगर (pSettings->bModemEnabled) अणु
		WriteGenCfg(DSP_UartCfg1Index, MKBYTE(rUartCfg1));
		WriteGenCfg(DSP_UartCfg2Index, MKBYTE(rUartCfg2));
	पूर्ण


	rHBridgeControl.EnableDspInt = false;
	rHBridgeControl.MemAutoInc = true;
	rHBridgeControl.IoAutoInc = false;
	rHBridgeControl.DiagnosticMode = false;

	PRINTK_3(TRACE_3780I,
		"3780i::dsp3780i_EnableDSP DSP_HBridgeControl %x rHBridgeControl %x\n",
		DSP_HBridgeControl, MKWORD(rHBridgeControl));

	OutWordDsp(DSP_HBridgeControl, MKWORD(rHBridgeControl));
	spin_unlock_irqrestore(&dsp_lock, flags);
	WriteMsaCfg(DSP_LBusTimeoutDisable, MKWORD(rLBusTimeoutDisable));
	WriteMsaCfg(DSP_ClockControl_1, MKWORD(rClockControl1));
	WriteMsaCfg(DSP_ClockControl_2, MKWORD(rClockControl2));
	WriteMsaCfg(DSP_ChipReset, MKWORD(rChipReset));

	ChipID = ReadMsaCfg(DSP_ChipID);

	PRINTK_2(TRACE_3780I,
		"3780i::dsp3780I_EnableDSP exiting bRC=true, ChipID %x\n",
		ChipID);

	वापस 0;
पूर्ण

पूर्णांक dsp3780I_DisableDSP(DSP_3780I_CONFIG_SETTINGS * pSettings)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु usDspBaseIO = pSettings->usDspBaseIO;
	DSP_ISA_SLAVE_CONTROL rSlaveControl;


	PRINTK_1(TRACE_3780I, "3780i::dsp3780i_DisableDSP entry\n");

	rSlaveControl.ClockControl = 0;
	rSlaveControl.SoftReset = true;
	rSlaveControl.ConfigMode = false;
	rSlaveControl.Reserved = 0;
	spin_lock_irqsave(&dsp_lock, flags);
	OutWordDsp(DSP_IsaSlaveControl, MKWORD(rSlaveControl));

	udelay(5);

	rSlaveControl.ClockControl = 1;
	OutWordDsp(DSP_IsaSlaveControl, MKWORD(rSlaveControl));
	spin_unlock_irqrestore(&dsp_lock, flags);

	udelay(5);


	PRINTK_1(TRACE_3780I, "3780i::dsp3780i_DisableDSP exit\n");

	वापस 0;
पूर्ण

पूर्णांक dsp3780I_Reset(DSP_3780I_CONFIG_SETTINGS * pSettings)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु usDspBaseIO = pSettings->usDspBaseIO;
	DSP_BOOT_DOMAIN rBootDoमुख्य;
	DSP_HBRIDGE_CONTROL rHBridgeControl;


	PRINTK_1(TRACE_3780I, "3780i::dsp3780i_Reset entry\n");

	spin_lock_irqsave(&dsp_lock, flags);
	/* Mask DSP to PC पूर्णांकerrupt */
	MKWORD(rHBridgeControl) = InWordDsp(DSP_HBridgeControl);

	PRINTK_2(TRACE_3780I, "3780i::dsp3780i_Reset rHBridgeControl %x\n",
		MKWORD(rHBridgeControl));

	rHBridgeControl.EnableDspInt = false;
	OutWordDsp(DSP_HBridgeControl, MKWORD(rHBridgeControl));
	spin_unlock_irqrestore(&dsp_lock, flags);

	/* Reset the core via the boot करोमुख्य रेजिस्टर */
	rBootDoमुख्य.ResetCore = true;
	rBootDoमुख्य.Halt = true;
	rBootDoमुख्य.NMI = true;
	rBootDoमुख्य.Reserved = 0;

	PRINTK_2(TRACE_3780I, "3780i::dsp3780i_Reset rBootDomain %x\n",
		MKWORD(rBootDoमुख्य));

	WriteMsaCfg(DSP_MspBootDoमुख्य, MKWORD(rBootDoमुख्य));

	/* Reset all the chiplets and then reactivate them */
	WriteMsaCfg(DSP_ChipReset, 0xFFFF);
	udelay(5);
	WriteMsaCfg(DSP_ChipReset,
			(अचिन्हित लघु) (~pSettings->usChipletEnable));


	PRINTK_1(TRACE_3780I, "3780i::dsp3780i_Reset exit bRC=0\n");

	वापस 0;
पूर्ण


पूर्णांक dsp3780I_Run(DSP_3780I_CONFIG_SETTINGS * pSettings)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु usDspBaseIO = pSettings->usDspBaseIO;
	DSP_BOOT_DOMAIN rBootDoमुख्य;
	DSP_HBRIDGE_CONTROL rHBridgeControl;


	PRINTK_1(TRACE_3780I, "3780i::dsp3780i_Run entry\n");


	/* Transition the core to a running state */
	rBootDoमुख्य.ResetCore = true;
	rBootDoमुख्य.Halt = false;
	rBootDoमुख्य.NMI = true;
	rBootDoमुख्य.Reserved = 0;
	WriteMsaCfg(DSP_MspBootDoमुख्य, MKWORD(rBootDoमुख्य));

	udelay(5);

	rBootDoमुख्य.ResetCore = false;
	WriteMsaCfg(DSP_MspBootDoमुख्य, MKWORD(rBootDoमुख्य));
	udelay(5);

	rBootDoमुख्य.NMI = false;
	WriteMsaCfg(DSP_MspBootDoमुख्य, MKWORD(rBootDoमुख्य));
	udelay(5);

	/* Enable DSP to PC पूर्णांकerrupt */
	spin_lock_irqsave(&dsp_lock, flags);
	MKWORD(rHBridgeControl) = InWordDsp(DSP_HBridgeControl);
	rHBridgeControl.EnableDspInt = true;

	PRINTK_2(TRACE_3780I, "3780i::dsp3780i_Run rHBridgeControl %x\n",
		MKWORD(rHBridgeControl));

	OutWordDsp(DSP_HBridgeControl, MKWORD(rHBridgeControl));
	spin_unlock_irqrestore(&dsp_lock, flags);


	PRINTK_1(TRACE_3780I, "3780i::dsp3780i_Run exit bRC=true\n");

	वापस 0;
पूर्ण


पूर्णांक dsp3780I_ReadDStore(अचिन्हित लघु usDspBaseIO, व्योम __user *pvBuffer,
                        अचिन्हित uCount, अचिन्हित दीर्घ ulDSPAddr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु __user *pusBuffer = pvBuffer;
	अचिन्हित लघु val;


	PRINTK_5(TRACE_3780I,
		"3780i::dsp3780I_ReadDStore entry usDspBaseIO %x, pusBuffer %p, uCount %x, ulDSPAddr %lx\n",
		usDspBaseIO, pusBuffer, uCount, ulDSPAddr);


	/* Set the initial MSA address. No adjusपंचांगents need to be made to data store addresses */
	spin_lock_irqsave(&dsp_lock, flags);
	OutWordDsp(DSP_MsaAddrLow, (अचिन्हित लघु) ulDSPAddr);
	OutWordDsp(DSP_MsaAddrHigh, (अचिन्हित लघु) (ulDSPAddr >> 16));
	spin_unlock_irqrestore(&dsp_lock, flags);

	/* Transfer the memory block */
	जबतक (uCount-- != 0) अणु
		spin_lock_irqsave(&dsp_lock, flags);
		val = InWordDsp(DSP_MsaDataDSISHigh);
		spin_unlock_irqrestore(&dsp_lock, flags);
		अगर(put_user(val, pusBuffer++))
			वापस -EFAULT;

		PRINTK_3(TRACE_3780I,
			"3780I::dsp3780I_ReadDStore uCount %x val %x\n",
			uCount, val);

		PaceMsaAccess(usDspBaseIO);
	पूर्ण


	PRINTK_1(TRACE_3780I,
		"3780I::dsp3780I_ReadDStore exit bRC=true\n");

	वापस 0;
पूर्ण

पूर्णांक dsp3780I_ReadAndClearDStore(अचिन्हित लघु usDspBaseIO,
                                व्योम __user *pvBuffer, अचिन्हित uCount,
                                अचिन्हित दीर्घ ulDSPAddr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु __user *pusBuffer = pvBuffer;
	अचिन्हित लघु val;


	PRINTK_5(TRACE_3780I,
		"3780i::dsp3780I_ReadAndDStore entry usDspBaseIO %x, pusBuffer %p, uCount %x, ulDSPAddr %lx\n",
		usDspBaseIO, pusBuffer, uCount, ulDSPAddr);


	/* Set the initial MSA address. No adjusपंचांगents need to be made to data store addresses */
	spin_lock_irqsave(&dsp_lock, flags);
	OutWordDsp(DSP_MsaAddrLow, (अचिन्हित लघु) ulDSPAddr);
	OutWordDsp(DSP_MsaAddrHigh, (अचिन्हित लघु) (ulDSPAddr >> 16));
	spin_unlock_irqrestore(&dsp_lock, flags);

	/* Transfer the memory block */
	जबतक (uCount-- != 0) अणु
		spin_lock_irqsave(&dsp_lock, flags);
		val = InWordDsp(DSP_ReadAndClear);
		spin_unlock_irqrestore(&dsp_lock, flags);
		अगर(put_user(val, pusBuffer++))
			वापस -EFAULT;

		PRINTK_3(TRACE_3780I,
			"3780I::dsp3780I_ReadAndCleanDStore uCount %x val %x\n",
			uCount, val);

		PaceMsaAccess(usDspBaseIO);
	पूर्ण


	PRINTK_1(TRACE_3780I,
		"3780I::dsp3780I_ReadAndClearDStore exit bRC=true\n");

	वापस 0;
पूर्ण


पूर्णांक dsp3780I_WriteDStore(अचिन्हित लघु usDspBaseIO, व्योम __user *pvBuffer,
                         अचिन्हित uCount, अचिन्हित दीर्घ ulDSPAddr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु __user *pusBuffer = pvBuffer;


	PRINTK_5(TRACE_3780I,
		"3780i::dsp3780D_WriteDStore entry usDspBaseIO %x, pusBuffer %p, uCount %x, ulDSPAddr %lx\n",
		usDspBaseIO, pusBuffer, uCount, ulDSPAddr);


	/* Set the initial MSA address. No adjusपंचांगents need to be made to data store addresses */
	spin_lock_irqsave(&dsp_lock, flags);
	OutWordDsp(DSP_MsaAddrLow, (अचिन्हित लघु) ulDSPAddr);
	OutWordDsp(DSP_MsaAddrHigh, (अचिन्हित लघु) (ulDSPAddr >> 16));
	spin_unlock_irqrestore(&dsp_lock, flags);

	/* Transfer the memory block */
	जबतक (uCount-- != 0) अणु
		अचिन्हित लघु val;
		अगर(get_user(val, pusBuffer++))
			वापस -EFAULT;
		spin_lock_irqsave(&dsp_lock, flags);
		OutWordDsp(DSP_MsaDataDSISHigh, val);
		spin_unlock_irqrestore(&dsp_lock, flags);

		PRINTK_3(TRACE_3780I,
			"3780I::dsp3780I_WriteDStore uCount %x val %x\n",
			uCount, val);

		PaceMsaAccess(usDspBaseIO);
	पूर्ण


	PRINTK_1(TRACE_3780I,
		"3780I::dsp3780D_WriteDStore exit bRC=true\n");

	वापस 0;
पूर्ण


पूर्णांक dsp3780I_ReadIStore(अचिन्हित लघु usDspBaseIO, व्योम __user *pvBuffer,
                        अचिन्हित uCount, अचिन्हित दीर्घ ulDSPAddr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु __user *pusBuffer = pvBuffer;

	PRINTK_5(TRACE_3780I,
		"3780i::dsp3780I_ReadIStore entry usDspBaseIO %x, pusBuffer %p, uCount %x, ulDSPAddr %lx\n",
		usDspBaseIO, pusBuffer, uCount, ulDSPAddr);

	/*
	* Set the initial MSA address. To convert from an inकाष्ठाion store
	* address to an MSA address
	* shअगरt the address two bits to the left and set bit 22
	*/
	ulDSPAddr = (ulDSPAddr << 2) | (1 << 22);
	spin_lock_irqsave(&dsp_lock, flags);
	OutWordDsp(DSP_MsaAddrLow, (अचिन्हित लघु) ulDSPAddr);
	OutWordDsp(DSP_MsaAddrHigh, (अचिन्हित लघु) (ulDSPAddr >> 16));
	spin_unlock_irqrestore(&dsp_lock, flags);

	/* Transfer the memory block */
	जबतक (uCount-- != 0) अणु
		अचिन्हित लघु val_lo, val_hi;
		spin_lock_irqsave(&dsp_lock, flags);
		val_lo = InWordDsp(DSP_MsaDataISLow);
		val_hi = InWordDsp(DSP_MsaDataDSISHigh);
		spin_unlock_irqrestore(&dsp_lock, flags);
		अगर(put_user(val_lo, pusBuffer++))
			वापस -EFAULT;
		अगर(put_user(val_hi, pusBuffer++))
			वापस -EFAULT;

		PRINTK_4(TRACE_3780I,
			"3780I::dsp3780I_ReadIStore uCount %x val_lo %x val_hi %x\n",
			uCount, val_lo, val_hi);

		PaceMsaAccess(usDspBaseIO);

	पूर्ण

	PRINTK_1(TRACE_3780I,
		"3780I::dsp3780I_ReadIStore exit bRC=true\n");

	वापस 0;
पूर्ण


पूर्णांक dsp3780I_WriteIStore(अचिन्हित लघु usDspBaseIO, व्योम __user *pvBuffer,
                         अचिन्हित uCount, अचिन्हित दीर्घ ulDSPAddr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु __user *pusBuffer = pvBuffer;

	PRINTK_5(TRACE_3780I,
		"3780i::dsp3780I_WriteIStore entry usDspBaseIO %x, pusBuffer %p, uCount %x, ulDSPAddr %lx\n",
		usDspBaseIO, pusBuffer, uCount, ulDSPAddr);


	/*
	* Set the initial MSA address. To convert from an inकाष्ठाion store
	* address to an MSA address
	* shअगरt the address two bits to the left and set bit 22
	*/
	ulDSPAddr = (ulDSPAddr << 2) | (1 << 22);
	spin_lock_irqsave(&dsp_lock, flags);
	OutWordDsp(DSP_MsaAddrLow, (अचिन्हित लघु) ulDSPAddr);
	OutWordDsp(DSP_MsaAddrHigh, (अचिन्हित लघु) (ulDSPAddr >> 16));
	spin_unlock_irqrestore(&dsp_lock, flags);

	/* Transfer the memory block */
	जबतक (uCount-- != 0) अणु
		अचिन्हित लघु val_lo, val_hi;
		अगर(get_user(val_lo, pusBuffer++))
			वापस -EFAULT;
		अगर(get_user(val_hi, pusBuffer++))
			वापस -EFAULT;
		spin_lock_irqsave(&dsp_lock, flags);
		OutWordDsp(DSP_MsaDataISLow, val_lo);
		OutWordDsp(DSP_MsaDataDSISHigh, val_hi);
		spin_unlock_irqrestore(&dsp_lock, flags);

		PRINTK_4(TRACE_3780I,
			"3780I::dsp3780I_WriteIStore uCount %x val_lo %x val_hi %x\n",
			uCount, val_lo, val_hi);

		PaceMsaAccess(usDspBaseIO);

	पूर्ण

	PRINTK_1(TRACE_3780I,
		"3780I::dsp3780I_WriteIStore exit bRC=true\n");

	वापस 0;
पूर्ण


पूर्णांक dsp3780I_GetIPCSource(अचिन्हित लघु usDspBaseIO,
                          अचिन्हित लघु *pusIPCSource)
अणु
	अचिन्हित दीर्घ flags;
	DSP_HBRIDGE_CONTROL rHBridgeControl;
	अचिन्हित लघु temp;


	PRINTK_3(TRACE_3780I,
		"3780i::dsp3780I_GetIPCSource entry usDspBaseIO %x pusIPCSource %p\n",
		usDspBaseIO, pusIPCSource);

	/*
	* Disable DSP to PC पूर्णांकerrupts, पढ़ो the पूर्णांकerrupt रेजिस्टर,
	* clear the pending IPC bits, and reenable DSP to PC पूर्णांकerrupts
	*/
	spin_lock_irqsave(&dsp_lock, flags);
	MKWORD(rHBridgeControl) = InWordDsp(DSP_HBridgeControl);
	rHBridgeControl.EnableDspInt = false;
	OutWordDsp(DSP_HBridgeControl, MKWORD(rHBridgeControl));

	*pusIPCSource = InWordDsp(DSP_Interrupt);
	temp = (अचिन्हित लघु) ~(*pusIPCSource);

	PRINTK_3(TRACE_3780I,
		"3780i::dsp3780I_GetIPCSource, usIPCSource %x ~ %x\n",
		*pusIPCSource, temp);

	OutWordDsp(DSP_Interrupt, (अचिन्हित लघु) ~(*pusIPCSource));

	rHBridgeControl.EnableDspInt = true;
	OutWordDsp(DSP_HBridgeControl, MKWORD(rHBridgeControl));
	spin_unlock_irqrestore(&dsp_lock, flags);


	PRINTK_2(TRACE_3780I,
		"3780i::dsp3780I_GetIPCSource exit usIPCSource %x\n",
		*pusIPCSource);

	वापस 0;
पूर्ण
