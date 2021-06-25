<शैली गुरु>
/*
*
* mwavepub.h -- PUBLIC declarations क्रम the mwave driver
*               and applications using it
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

#अगर_अघोषित _LINUX_MWAVEPUB_H
#घोषणा _LINUX_MWAVEPUB_H

#समावेश <linux/miscdevice.h>


प्रकार काष्ठा _MW_ABILITIES अणु
	अचिन्हित दीर्घ instr_per_sec;
	अचिन्हित दीर्घ data_size;
	अचिन्हित दीर्घ inst_size;
	अचिन्हित दीर्घ bus_dma_bw;
	अचिन्हित लघु uart_enable;
	लघु component_count;
	अचिन्हित दीर्घ component_list[7];
	अक्षर mwave_os_name[16];
	अक्षर bios_task_name[16];
पूर्ण MW_ABILITIES, *pMW_ABILITIES;


प्रकार काष्ठा _MW_READWRITE अणु
	अचिन्हित लघु usDspAddress;	/* The dsp address */
	अचिन्हित दीर्घ ulDataLength;	/* The size in bytes of the data or user buffer */
	व्योम __user *pBuf;		/* Input:variable sized buffer */
पूर्ण MW_READWRITE, *pMW_READWRITE;

#घोषणा IOCTL_MW_RESET           _IO(MWAVE_MINOR,1)
#घोषणा IOCTL_MW_RUN             _IO(MWAVE_MINOR,2)
#घोषणा IOCTL_MW_DSP_ABILITIES   _IOR(MWAVE_MINOR,3,MW_ABILITIES)
#घोषणा IOCTL_MW_READ_DATA       _IOR(MWAVE_MINOR,4,MW_READWRITE)
#घोषणा IOCTL_MW_READCLEAR_DATA  _IOR(MWAVE_MINOR,5,MW_READWRITE)
#घोषणा IOCTL_MW_READ_INST       _IOR(MWAVE_MINOR,6,MW_READWRITE)
#घोषणा IOCTL_MW_WRITE_DATA      _IOW(MWAVE_MINOR,7,MW_READWRITE)
#घोषणा IOCTL_MW_WRITE_INST      _IOW(MWAVE_MINOR,8,MW_READWRITE)
#घोषणा IOCTL_MW_REGISTER_IPC    _IOW(MWAVE_MINOR,9,पूर्णांक)
#घोषणा IOCTL_MW_UNREGISTER_IPC  _IOW(MWAVE_MINOR,10,पूर्णांक)
#घोषणा IOCTL_MW_GET_IPC         _IOW(MWAVE_MINOR,11,पूर्णांक)
#घोषणा IOCTL_MW_TRACE           _IOR(MWAVE_MINOR,12,MW_READWRITE)


#पूर्ण_अगर
