<शैली गुरु>
/*
*
* mwavedd.h -- declarations क्रम mwave device driver
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

#अगर_अघोषित _LINUX_MWAVEDD_H
#घोषणा _LINUX_MWAVEDD_H
#समावेश "3780i.h"
#समावेश "tp3780i.h"
#समावेश "smapi.h"
#समावेश "mwavepub.h"
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/रुको.h>

बाह्य पूर्णांक mwave_debug;
बाह्य पूर्णांक mwave_3780i_irq;
बाह्य पूर्णांक mwave_3780i_io;
बाह्य पूर्णांक mwave_uart_irq;
बाह्य पूर्णांक mwave_uart_io;

#घोषणा PRINTK_ERROR prपूर्णांकk
#घोषणा KERN_ERR_MWAVE KERN_ERR "mwave: "

#घोषणा TRACE_MWAVE     0x0001
#घोषणा TRACE_SMAPI     0x0002
#घोषणा TRACE_3780I     0x0004
#घोषणा TRACE_TP3780I   0x0008

#अगर_घोषित MW_TRACE
#घोषणा PRINTK_1(f,s)                       \
  अगर (f & (mwave_debug)) अणु                  \
    prपूर्णांकk(s);                              \
  पूर्ण

#घोषणा PRINTK_2(f,s,v1)                    \
  अगर (f & (mwave_debug)) अणु                  \
    prपूर्णांकk(s,v1);                           \
  पूर्ण

#घोषणा PRINTK_3(f,s,v1,v2)                 \
  अगर (f & (mwave_debug)) अणु                  \
    prपूर्णांकk(s,v1,v2);                        \
  पूर्ण

#घोषणा PRINTK_4(f,s,v1,v2,v3)              \
  अगर (f & (mwave_debug)) अणु                  \
    prपूर्णांकk(s,v1,v2,v3);                     \
  पूर्ण

#घोषणा PRINTK_5(f,s,v1,v2,v3,v4)           \
  अगर (f & (mwave_debug)) अणु                  \
    prपूर्णांकk(s,v1,v2,v3,v4);                  \
  पूर्ण

#घोषणा PRINTK_6(f,s,v1,v2,v3,v4,v5)        \
  अगर (f & (mwave_debug)) अणु                  \
    prपूर्णांकk(s,v1,v2,v3,v4,v5);               \
  पूर्ण

#घोषणा PRINTK_7(f,s,v1,v2,v3,v4,v5,v6)     \
  अगर (f & (mwave_debug)) अणु                  \
    prपूर्णांकk(s,v1,v2,v3,v4,v5,v6);            \
  पूर्ण

#घोषणा PRINTK_8(f,s,v1,v2,v3,v4,v5,v6,v7)  \
  अगर (f & (mwave_debug)) अणु                  \
    prपूर्णांकk(s,v1,v2,v3,v4,v5,v6,v7);         \
  पूर्ण

#अन्यथा
#घोषणा PRINTK_1(f,s)
#घोषणा PRINTK_2(f,s,v1)
#घोषणा PRINTK_3(f,s,v1,v2)
#घोषणा PRINTK_4(f,s,v1,v2,v3)
#घोषणा PRINTK_5(f,s,v1,v2,v3,v4)
#घोषणा PRINTK_6(f,s,v1,v2,v3,v4,v5)
#घोषणा PRINTK_7(f,s,v1,v2,v3,v4,v5,v6)
#घोषणा PRINTK_8(f,s,v1,v2,v3,v4,v5,v6,v7)
#पूर्ण_अगर


प्रकार काष्ठा _MWAVE_IPC अणु
	अचिन्हित लघु usIntCount;	/* 0=none, 1=first, 2=greater than 1st */
	bool bIsEnabled;
	bool bIsHere;
	/* entry spin lock */
	रुको_queue_head_t ipc_रुको_queue;
पूर्ण MWAVE_IPC;

प्रकार काष्ठा _MWAVE_DEVICE_DATA अणु
	THINKPAD_BD_DATA rBDData;	/* board driver's data area */
	अचिन्हित दीर्घ ulIPCSource_ISR;	/* IPC source bits क्रम recently processed पूर्णांकr, set during ISR processing */
	अचिन्हित दीर्घ ulIPCSource_DPC;	/* IPC source bits क्रम recently processed पूर्णांकr, set during DPC processing */
	bool bBDInitialized;
	bool bResourcesClaimed;
	bool bDSPEnabled;
	bool bDSPReset;
	MWAVE_IPC IPCs[16];
	bool bMwaveDevRegistered;
	लघु sLine;
	पूर्णांक nr_रेजिस्टरed_attrs;
	पूर्णांक device_रेजिस्टरed;

पूर्ण MWAVE_DEVICE_DATA, *pMWAVE_DEVICE_DATA;

बाह्य MWAVE_DEVICE_DATA mwave_s_mdd;

#पूर्ण_अगर
