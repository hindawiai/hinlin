<शैली गुरु>
/*
*
* tp3780i.h -- declarations क्रम tp3780i.c
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

#अगर_अघोषित _LINUX_TP3780I_H
#घोषणा _LINUX_TP3780I_H

#समावेश <यंत्र/पन.स>
#समावेश "mwavepub.h"


/* DSP abilities स्थिरants क्रम 3780i based Thinkpads */
#घोषणा TP_ABILITIES_INTS_PER_SEC       39160800
#घोषणा TP_ABILITIES_DATA_SIZE          32768
#घोषणा TP_ABILITIES_INST_SIZE          32768
#घोषणा TP_ABILITIES_MWAVEOS_NAME       "mwaveos0700.dsp"
#घोषणा TP_ABILITIES_BIOSTASK_NAME      "mwbio701.dsp"


/* DSP configuration values क्रम 3780i based Thinkpads */
#घोषणा TP_CFG_NumTransfers     3	/* 16 transfers */
#घोषणा TP_CFG_RerequestTimer   1	/* 2 usec */
#घोषणा TP_CFG_MEMCS16          0	/* Disabled, 16-bit memory assumed */
#घोषणा TP_CFG_IsaMemCmdWidth   3	/* 295 nsec (16-bit) */
#घोषणा TP_CFG_GateIOCHRDY      0	/* No IOCHRDY gating */
#घोषणा TP_CFG_EnablePwrMgmt    1	/* Enable low poser suspend/resume */
#घोषणा TP_CFG_HBusTimerValue 255	/* HBus समयr load value */
#घोषणा TP_CFG_DisableLBusTimeout 0	/* Enable LBus समयout */
#घोषणा TP_CFG_N_Divisor       32	/* Clock = 39.1608 Mhz */
#घोषणा TP_CFG_M_Multiplier    37	/* " */
#घोषणा TP_CFG_PllBypass        0	/* करोn't bypass */
#घोषणा TP_CFG_ChipletEnable 0xFFFF	/* Enable all chiplets */

प्रकार काष्ठा अणु
	पूर्णांक bDSPEnabled;
	पूर्णांक bShareDspIrq;
	पूर्णांक bShareUartIrq;
	DSP_3780I_CONFIG_SETTINGS rDspSettings;
पूर्ण THINKPAD_BD_DATA;

पूर्णांक tp3780I_InitializeBoardData(THINKPAD_BD_DATA * pBDData);
पूर्णांक tp3780I_CalcResources(THINKPAD_BD_DATA * pBDData);
पूर्णांक tp3780I_ClaimResources(THINKPAD_BD_DATA * pBDData);
पूर्णांक tp3780I_ReleaseResources(THINKPAD_BD_DATA * pBDData);
पूर्णांक tp3780I_EnableDSP(THINKPAD_BD_DATA * pBDData);
पूर्णांक tp3780I_DisableDSP(THINKPAD_BD_DATA * pBDData);
पूर्णांक tp3780I_ResetDSP(THINKPAD_BD_DATA * pBDData);
पूर्णांक tp3780I_StartDSP(THINKPAD_BD_DATA * pBDData);
पूर्णांक tp3780I_QueryAbilities(THINKPAD_BD_DATA * pBDData, MW_ABILITIES * pAbilities);
व्योम tp3780I_Cleanup(THINKPAD_BD_DATA *pBDData);
पूर्णांक tp3780I_ReadWriteDspDStore(THINKPAD_BD_DATA * pBDData, अचिन्हित पूर्णांक uOpcode,
                               व्योम __user *pvBuffer, अचिन्हित पूर्णांक uCount,
                               अचिन्हित दीर्घ ulDSPAddr);
पूर्णांक tp3780I_ReadWriteDspIStore(THINKPAD_BD_DATA * pBDData, अचिन्हित पूर्णांक uOpcode,
                               व्योम __user *pvBuffer, अचिन्हित पूर्णांक uCount,
                               अचिन्हित दीर्घ ulDSPAddr);


#पूर्ण_अगर
