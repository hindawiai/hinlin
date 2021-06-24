<शैली गुरु>
/*
*
* 3780i.h -- declarations क्रम 3780i.c
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

#अगर_अघोषित _LINUX_3780I_H
#घोषणा _LINUX_3780I_H

#समावेश <यंत्र/पन.स>

/* DSP I/O port offsets and definitions */
#घोषणा DSP_IsaSlaveControl        0x0000	/* ISA slave control रेजिस्टर */
#घोषणा DSP_IsaSlaveStatus         0x0001	/* ISA slave status रेजिस्टर */
#घोषणा DSP_ConfigAddress          0x0002	/* General config address रेजिस्टर */
#घोषणा DSP_ConfigData             0x0003	/* General config data रेजिस्टर */
#घोषणा DSP_HBridgeControl         0x0002	/* HBridge control रेजिस्टर */
#घोषणा DSP_MsaAddrLow             0x0004	/* MSP System Address, low word */
#घोषणा DSP_MsaAddrHigh            0x0006	/* MSP System Address, high word */
#घोषणा DSP_MsaDataDSISHigh        0x0008	/* MSA data रेजिस्टर: d-store word or high byte of i-store */
#घोषणा DSP_MsaDataISLow           0x000A	/* MSA data रेजिस्टर: low word of i-store */
#घोषणा DSP_ReadAndClear           0x000C	/* MSA पढ़ो and clear data रेजिस्टर */
#घोषणा DSP_Interrupt              0x000E	/* Interrupt रेजिस्टर (IPC source) */

प्रकार काष्ठा अणु
	अचिन्हित अक्षर ClockControl:1;	/* RW: Clock control: 0=normal, 1=stop 3780i घड़ीs */
	अचिन्हित अक्षर SoftReset:1;	/* RW: Soft reset 0=normal, 1=soft reset active */
	अचिन्हित अक्षर ConfigMode:1;	/* RW: Configuration mode, 0=normal, 1=config mode */
	अचिन्हित अक्षर Reserved:5;	/* 0: Reserved */
पूर्ण DSP_ISA_SLAVE_CONTROL;


प्रकार काष्ठा अणु
	अचिन्हित लघु EnableDspInt:1;	/* RW: Enable DSP to X86 ISA पूर्णांकerrupt 0=mask it, 1=enable it */
	अचिन्हित लघु MemAutoInc:1;	/* RW: Memory address स्वतः increment, 0=disable, 1=enable */
	अचिन्हित लघु IoAutoInc:1;	/* RW: I/O address स्वतः increment, 0=disable, 1=enable */
	अचिन्हित लघु DiagnosticMode:1;	/* RW: Disgnostic mode 0=nromal, 1=diagnostic mode */
	अचिन्हित लघु IsaPacingTimer:12;	/* R: ISA access pacing समयr: count of core cycles stolen */
पूर्ण DSP_HBRIDGE_CONTROL;


/* DSP रेजिस्टर indexes used with the configuration रेजिस्टर address (index) रेजिस्टर */
#घोषणा DSP_UartCfg1Index          0x0003	/* UART config रेजिस्टर 1 */
#घोषणा DSP_UartCfg2Index          0x0004	/* UART config रेजिस्टर 2 */
#घोषणा DSP_HBridgeCfg1Index       0x0007	/* HBridge config रेजिस्टर 1 */
#घोषणा DSP_HBridgeCfg2Index       0x0008	/* HBridge config रेजिस्टर 2 */
#घोषणा DSP_BusMasterCfg1Index     0x0009	/* ISA bus master config रेजिस्टर 1 */
#घोषणा DSP_BusMasterCfg2Index     0x000A	/* ISA bus master config रेजिस्टर 2 */
#घोषणा DSP_IsaProtCfgIndex        0x000F	/* ISA protocol control रेजिस्टर */
#घोषणा DSP_PowerMgCfgIndex        0x0010	/* Low poser suspend/resume enable */
#घोषणा DSP_HBusTimerCfgIndex      0x0011	/* HBUS समयr load value */

प्रकार काष्ठा अणु
	अचिन्हित अक्षर IrqActiveLow:1;	/* RW: IRQ active high or low: 0=high, 1=low */
	अचिन्हित अक्षर IrqPulse:1;	/* RW: IRQ pulse or level: 0=level, 1=pulse  */
	अचिन्हित अक्षर Irq:3;	/* RW: IRQ selection */
	अचिन्हित अक्षर BaseIO:2;	/* RW: Base I/O selection */
	अचिन्हित अक्षर Reserved:1;	/* 0: Reserved */
पूर्ण DSP_UART_CFG_1;

प्रकार काष्ठा अणु
	अचिन्हित अक्षर Enable:1;	/* RW: Enable I/O and IRQ: 0=false, 1=true */
	अचिन्हित अक्षर Reserved:7;	/* 0: Reserved */
पूर्ण DSP_UART_CFG_2;

प्रकार काष्ठा अणु
	अचिन्हित अक्षर IrqActiveLow:1;	/* RW: IRQ active high=0 or low=1 */
	अचिन्हित अक्षर IrqPulse:1;	/* RW: IRQ pulse=1 or level=0 */
	अचिन्हित अक्षर Irq:3;	/* RW: IRQ selection */
	अचिन्हित अक्षर AccessMode:1;	/* RW: 16-bit रेजिस्टर access method 0=byte, 1=word */
	अचिन्हित अक्षर Reserved:2;	/* 0: Reserved */
पूर्ण DSP_HBRIDGE_CFG_1;

प्रकार काष्ठा अणु
	अचिन्हित अक्षर Enable:1;	/* RW: enable I/O and IRQ: 0=false, 1=true */
	अचिन्हित अक्षर Reserved:7;	/* 0: Reserved */
पूर्ण DSP_HBRIDGE_CFG_2;


प्रकार काष्ठा अणु
	अचिन्हित अक्षर Dma:3;	/* RW: DMA channel selection */
	अचिन्हित अक्षर NumTransfers:2;	/* RW: Maximum # of transfers once being granted the ISA bus */
	अचिन्हित अक्षर ReRequest:2;	/* RW: Minimum delay between releasing the ISA bus and requesting it again */
	अचिन्हित अक्षर MEMCS16:1;	/* RW: ISA संकेत MEMCS16: 0=disabled, 1=enabled */
पूर्ण DSP_BUSMASTER_CFG_1;

प्रकार काष्ठा अणु
	अचिन्हित अक्षर IsaMemCmdWidth:2;	/* RW: ISA memory command width */
	अचिन्हित अक्षर Reserved:6;	/* 0: Reserved */
पूर्ण DSP_BUSMASTER_CFG_2;


प्रकार काष्ठा अणु
	अचिन्हित अक्षर GateIOCHRDY:1;	/* RW: Enable IOCHRDY gating: 0=false, 1=true */
	अचिन्हित अक्षर Reserved:7;	/* 0: Reserved */
पूर्ण DSP_ISA_PROT_CFG;

प्रकार काष्ठा अणु
	अचिन्हित अक्षर Enable:1;	/* RW: Enable low घातer suspend/resume 0=false, 1=true */
	अचिन्हित अक्षर Reserved:7;	/* 0: Reserved */
पूर्ण DSP_POWER_MGMT_CFG;

प्रकार काष्ठा अणु
	अचिन्हित अक्षर LoadValue:8;	/* RW: HBUS समयr load value */
पूर्ण DSP_HBUS_TIMER_CFG;



/* DSP रेजिस्टरs that exist in MSA I/O space */
#घोषणा DSP_ChipID                 0x80000000
#घोषणा DSP_MspBootDoमुख्य          0x80000580
#घोषणा DSP_LBusTimeoutDisable     0x80000580
#घोषणा DSP_ClockControl_1         0x8000058A
#घोषणा DSP_ClockControl_2         0x8000058C
#घोषणा DSP_ChipReset              0x80000588
#घोषणा DSP_GpioModeControl_15_8   0x80000082
#घोषणा DSP_GpioDriverEnable_15_8  0x80000076
#घोषणा DSP_GpioOutputData_15_8    0x80000072

प्रकार काष्ठा अणु
	अचिन्हित लघु NMI:1;	/* RW: non maskable पूर्णांकerrupt */
	अचिन्हित लघु Halt:1;	/* RW: Halt MSP घड़ी */
	अचिन्हित लघु ResetCore:1;	/* RW: Reset MSP core पूर्णांकerface */
	अचिन्हित लघु Reserved:13;	/* 0: Reserved */
पूर्ण DSP_BOOT_DOMAIN;

प्रकार काष्ठा अणु
	अचिन्हित लघु DisableTimeout:1;	/* RW: Disable LBus समयout */
	अचिन्हित लघु Reserved:15;	/* 0: Reserved */
पूर्ण DSP_LBUS_TIMEOUT_DISABLE;

प्रकार काष्ठा अणु
	अचिन्हित लघु Memory:1;	/* RW: Reset memory पूर्णांकerface */
	अचिन्हित लघु SerialPort1:1;	/* RW: Reset serial port 1 पूर्णांकerface */
	अचिन्हित लघु SerialPort2:1;	/* RW: Reset serial port 2 पूर्णांकerface */
	अचिन्हित लघु SerialPort3:1;	/* RW: Reset serial port 3 पूर्णांकerface */
	अचिन्हित लघु Gpio:1;	/* RW: Reset GPIO पूर्णांकerface */
	अचिन्हित लघु Dma:1;	/* RW: Reset DMA पूर्णांकerface */
	अचिन्हित लघु SoundBlaster:1;	/* RW: Reset soundblaster पूर्णांकerface */
	अचिन्हित लघु Uart:1;	/* RW: Reset UART पूर्णांकerface */
	अचिन्हित लघु Midi:1;	/* RW: Reset MIDI पूर्णांकerface */
	अचिन्हित लघु IsaMaster:1;	/* RW: Reset ISA master पूर्णांकerface */
	अचिन्हित लघु Reserved:6;	/* 0: Reserved */
पूर्ण DSP_CHIP_RESET;

प्रकार काष्ठा अणु
	अचिन्हित लघु N_Divisor:6;	/* RW: (N) PLL output घड़ी भागisor */
	अचिन्हित लघु Reserved1:2;	/* 0: reserved */
	अचिन्हित लघु M_Multiplier:6;	/* RW: (M) PLL feedback घड़ी multiplier */
	अचिन्हित लघु Reserved2:2;	/* 0: reserved */
पूर्ण DSP_CLOCK_CONTROL_1;

प्रकार काष्ठा अणु
	अचिन्हित लघु PllBypass:1;	/* RW: PLL Bypass */
	अचिन्हित लघु Reserved:15;	/* 0: Reserved */
पूर्ण DSP_CLOCK_CONTROL_2;

प्रकार काष्ठा अणु
	अचिन्हित लघु Latch8:1;
	अचिन्हित लघु Latch9:1;
	अचिन्हित लघु Latch10:1;
	अचिन्हित लघु Latch11:1;
	अचिन्हित लघु Latch12:1;
	अचिन्हित लघु Latch13:1;
	अचिन्हित लघु Latch14:1;
	अचिन्हित लघु Latch15:1;
	अचिन्हित लघु Mask8:1;
	अचिन्हित लघु Mask9:1;
	अचिन्हित लघु Mask10:1;
	अचिन्हित लघु Mask11:1;
	अचिन्हित लघु Mask12:1;
	अचिन्हित लघु Mask13:1;
	अचिन्हित लघु Mask14:1;
	अचिन्हित लघु Mask15:1;
पूर्ण DSP_GPIO_OUTPUT_DATA_15_8;

प्रकार काष्ठा अणु
	अचिन्हित लघु Enable8:1;
	अचिन्हित लघु Enable9:1;
	अचिन्हित लघु Enable10:1;
	अचिन्हित लघु Enable11:1;
	अचिन्हित लघु Enable12:1;
	अचिन्हित लघु Enable13:1;
	अचिन्हित लघु Enable14:1;
	अचिन्हित लघु Enable15:1;
	अचिन्हित लघु Mask8:1;
	अचिन्हित लघु Mask9:1;
	अचिन्हित लघु Mask10:1;
	अचिन्हित लघु Mask11:1;
	अचिन्हित लघु Mask12:1;
	अचिन्हित लघु Mask13:1;
	अचिन्हित लघु Mask14:1;
	अचिन्हित लघु Mask15:1;
पूर्ण DSP_GPIO_DRIVER_ENABLE_15_8;

प्रकार काष्ठा अणु
	अचिन्हित लघु GpioMode8:2;
	अचिन्हित लघु GpioMode9:2;
	अचिन्हित लघु GpioMode10:2;
	अचिन्हित लघु GpioMode11:2;
	अचिन्हित लघु GpioMode12:2;
	अचिन्हित लघु GpioMode13:2;
	अचिन्हित लघु GpioMode14:2;
	अचिन्हित लघु GpioMode15:2;
पूर्ण DSP_GPIO_MODE_15_8;

/* Component masks that are defined in dspmgr.h */
#घोषणा MW_ADC_MASK    0x0001
#घोषणा MW_AIC2_MASK   0x0006
#घोषणा MW_MIDI_MASK   0x0008
#घोषणा MW_CDDAC_MASK  0x8001
#घोषणा MW_AIC1_MASK   0xE006
#घोषणा MW_UART_MASK   0xE00A
#घोषणा MW_ACI_MASK    0xE00B

/*
* Definition of 3780i configuration काष्ठाure.  Unless otherwise stated,
* these values are provided as input to the 3780i support layer.  At present,
* the only values मुख्यtained by the 3780i support layer are the saved UART
* रेजिस्टरs.
*/
प्रकार काष्ठा _DSP_3780I_CONFIG_SETTINGS अणु

	/* Location of base configuration रेजिस्टर */
	अचिन्हित लघु usBaseConfigIO;

	/* Enables क्रम various DSP components */
	पूर्णांक bDSPEnabled;
	पूर्णांक bModemEnabled;
	पूर्णांक bInterruptClaimed;

	/* IRQ, DMA, and Base I/O addresses क्रम various DSP components */
	अचिन्हित लघु usDspIrq;
	अचिन्हित लघु usDspDma;
	अचिन्हित लघु usDspBaseIO;
	अचिन्हित लघु usUartIrq;
	अचिन्हित लघु usUartBaseIO;

	/* IRQ modes क्रम various DSP components */
	पूर्णांक bDspIrqActiveLow;
	पूर्णांक bUartIrqActiveLow;
	पूर्णांक bDspIrqPulse;
	पूर्णांक bUartIrqPulse;

	/* Card abilities */
	अचिन्हित uIps;
	अचिन्हित uDStoreSize;
	अचिन्हित uIStoreSize;
	अचिन्हित uDmaBandwidth;

	/* Adapter specअगरic 3780i settings */
	अचिन्हित लघु usNumTransfers;
	अचिन्हित लघु usReRequest;
	पूर्णांक bEnableMEMCS16;
	अचिन्हित लघु usIsaMemCmdWidth;
	पूर्णांक bGateIOCHRDY;
	पूर्णांक bEnablePwrMgmt;
	अचिन्हित लघु usHBusTimerLoadValue;
	पूर्णांक bDisableLBusTimeout;
	अचिन्हित लघु usN_Divisor;
	अचिन्हित लघु usM_Multiplier;
	पूर्णांक bPllBypass;
	अचिन्हित लघु usChipletEnable;	/* Used with the chip reset रेजिस्टर to enable specअगरic chiplets */

	/* Saved UART रेजिस्टरs. These are मुख्यtained by the 3780i support layer. */
	पूर्णांक bUartSaved;		/* True after a successful save of the UART रेजिस्टरs */
	अचिन्हित अक्षर ucIER;	/* Interrupt enable रेजिस्टर */
	अचिन्हित अक्षर ucFCR;	/* FIFO control रेजिस्टर */
	अचिन्हित अक्षर ucLCR;	/* Line control रेजिस्टर */
	अचिन्हित अक्षर ucMCR;	/* Modem control रेजिस्टर */
	अचिन्हित अक्षर ucSCR;	/* Scratch रेजिस्टर */
	अचिन्हित अक्षर ucDLL;	/* Divisor latch, low byte */
	अचिन्हित अक्षर ucDLM;	/* Divisor latch, high byte */
पूर्ण DSP_3780I_CONFIG_SETTINGS;


/* 3780i support functions */
पूर्णांक dsp3780I_EnableDSP(DSP_3780I_CONFIG_SETTINGS * pSettings,
                       अचिन्हित लघु *pIrqMap,
                       अचिन्हित लघु *pDmaMap);
पूर्णांक dsp3780I_DisableDSP(DSP_3780I_CONFIG_SETTINGS * pSettings);
पूर्णांक dsp3780I_Reset(DSP_3780I_CONFIG_SETTINGS * pSettings);
पूर्णांक dsp3780I_Run(DSP_3780I_CONFIG_SETTINGS * pSettings);
पूर्णांक dsp3780I_ReadDStore(अचिन्हित लघु usDspBaseIO, व्योम __user *pvBuffer,
                        अचिन्हित uCount, अचिन्हित दीर्घ ulDSPAddr);
पूर्णांक dsp3780I_ReadAndClearDStore(अचिन्हित लघु usDspBaseIO,
                                व्योम __user *pvBuffer, अचिन्हित uCount,
                                अचिन्हित दीर्घ ulDSPAddr);
पूर्णांक dsp3780I_WriteDStore(अचिन्हित लघु usDspBaseIO, व्योम __user *pvBuffer,
                         अचिन्हित uCount, अचिन्हित दीर्घ ulDSPAddr);
पूर्णांक dsp3780I_ReadIStore(अचिन्हित लघु usDspBaseIO, व्योम __user *pvBuffer,
                        अचिन्हित uCount, अचिन्हित दीर्घ ulDSPAddr);
पूर्णांक dsp3780I_WriteIStore(अचिन्हित लघु usDspBaseIO, व्योम __user *pvBuffer,
                         अचिन्हित uCount, अचिन्हित दीर्घ ulDSPAddr);
अचिन्हित लघु dsp3780I_ReadMsaCfg(अचिन्हित लघु usDspBaseIO,
                                   अचिन्हित दीर्घ ulMsaAddr);
व्योम dsp3780I_WriteMsaCfg(अचिन्हित लघु usDspBaseIO,
                          अचिन्हित दीर्घ ulMsaAddr, अचिन्हित लघु usValue);
पूर्णांक dsp3780I_GetIPCSource(अचिन्हित लघु usDspBaseIO,
                          अचिन्हित लघु *pusIPCSource);

/* I/O port access macros */
#घोषणा MKWORD(var) (*((अचिन्हित लघु *)(&var)))
#घोषणा MKBYTE(var) (*((अचिन्हित अक्षर *)(&var)))

#घोषणा WriteMsaCfg(addr,value) dsp3780I_WriteMsaCfg(usDspBaseIO,addr,value)
#घोषणा ReadMsaCfg(addr) dsp3780I_ReadMsaCfg(usDspBaseIO,addr)
#घोषणा WriteGenCfg(index,value) dsp3780I_WriteGenCfg(usDspBaseIO,index,value)
#घोषणा ReadGenCfg(index) dsp3780I_ReadGenCfg(usDspBaseIO,index)

#घोषणा InWordDsp(index)          inw(usDspBaseIO+index)
#घोषणा InByteDsp(index)          inb(usDspBaseIO+index)
#घोषणा OutWordDsp(index,value)   outw(value,usDspBaseIO+index)
#घोषणा OutByteDsp(index,value)   outb(value,usDspBaseIO+index)

#पूर्ण_अगर
