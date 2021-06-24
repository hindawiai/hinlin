<शैली गुरु>
/*
*
* mwavedd.c -- mwave device driver
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

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/major.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/device.h>
#समावेश <linux/serial.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/nospec.h>
#समावेश "smapi.h"
#समावेश "mwavedd.h"
#समावेश "3780i.h"
#समावेश "tp3780i.h"

MODULE_DESCRIPTION("3780i Advanced Communications Processor (Mwave) driver");
MODULE_AUTHOR("Mike Sullivan and Paul Schroeder");
MODULE_LICENSE("GPL");

/*
* These parameters support the setting of MWave resources. Note that no
* checks are made against other devices (ie. superio) क्रम conflicts.
* We'll depend on users using the tpctl utility to करो that क्रम now
*/
अटल DEFINE_MUTEX(mwave_mutex);
पूर्णांक mwave_debug = 0;
पूर्णांक mwave_3780i_irq = 0;
पूर्णांक mwave_3780i_io = 0;
पूर्णांक mwave_uart_irq = 0;
पूर्णांक mwave_uart_io = 0;
module_param(mwave_debug, पूर्णांक, 0);
module_param_hw(mwave_3780i_irq, पूर्णांक, irq, 0);
module_param_hw(mwave_3780i_io, पूर्णांक, ioport, 0);
module_param_hw(mwave_uart_irq, पूर्णांक, irq, 0);
module_param_hw(mwave_uart_io, पूर्णांक, ioport, 0);

अटल पूर्णांक mwave_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक mwave_बंद(काष्ठा inode *inode, काष्ठा file *file);
अटल दीर्घ mwave_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक iocmd,
							अचिन्हित दीर्घ ioarg);

MWAVE_DEVICE_DATA mwave_s_mdd;

अटल पूर्णांक mwave_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक retval = 0;

	PRINTK_3(TRACE_MWAVE,
		"mwavedd::mwave_open, entry inode %p file %p\n",
		 inode, file);
	PRINTK_2(TRACE_MWAVE,
		"mwavedd::mwave_open, exit return retval %x\n", retval);

	वापस retval;
पूर्ण

अटल पूर्णांक mwave_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक retval = 0;

	PRINTK_3(TRACE_MWAVE,
		"mwavedd::mwave_close, entry inode %p file %p\n",
		 inode,  file);

	PRINTK_2(TRACE_MWAVE, "mwavedd::mwave_close, exit retval %x\n",
		retval);

	वापस retval;
पूर्ण

अटल दीर्घ mwave_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक iocmd,
							अचिन्हित दीर्घ ioarg)
अणु
	अचिन्हित पूर्णांक retval = 0;
	pMWAVE_DEVICE_DATA pDrvData = &mwave_s_mdd;
	व्योम __user *arg = (व्योम __user *)ioarg;

	PRINTK_4(TRACE_MWAVE,
		"mwavedd::mwave_ioctl, entry file %p cmd %x arg %x\n",
		file, iocmd, (पूर्णांक) ioarg);

	चयन (iocmd) अणु

		हाल IOCTL_MW_RESET:
			PRINTK_1(TRACE_MWAVE,
				"mwavedd::mwave_ioctl, IOCTL_MW_RESET"
				" calling tp3780I_ResetDSP\n");
			mutex_lock(&mwave_mutex);
			retval = tp3780I_ResetDSP(&pDrvData->rBDData);
			mutex_unlock(&mwave_mutex);
			PRINTK_2(TRACE_MWAVE,
				"mwavedd::mwave_ioctl, IOCTL_MW_RESET"
				" retval %x from tp3780I_ResetDSP\n",
				retval);
			अवरोध;
	
		हाल IOCTL_MW_RUN:
			PRINTK_1(TRACE_MWAVE,
				"mwavedd::mwave_ioctl, IOCTL_MW_RUN"
				" calling tp3780I_StartDSP\n");
			mutex_lock(&mwave_mutex);
			retval = tp3780I_StartDSP(&pDrvData->rBDData);
			mutex_unlock(&mwave_mutex);
			PRINTK_2(TRACE_MWAVE,
				"mwavedd::mwave_ioctl, IOCTL_MW_RUN"
				" retval %x from tp3780I_StartDSP\n",
				retval);
			अवरोध;
	
		हाल IOCTL_MW_DSP_ABILITIES: अणु
			MW_ABILITIES rAbilities;
	
			PRINTK_1(TRACE_MWAVE,
				"mwavedd::mwave_ioctl,"
				" IOCTL_MW_DSP_ABILITIES calling"
				" tp3780I_QueryAbilities\n");
			mutex_lock(&mwave_mutex);
			retval = tp3780I_QueryAbilities(&pDrvData->rBDData,
					&rAbilities);
			mutex_unlock(&mwave_mutex);
			PRINTK_2(TRACE_MWAVE,
				"mwavedd::mwave_ioctl, IOCTL_MW_DSP_ABILITIES"
				" retval %x from tp3780I_QueryAbilities\n",
				retval);
			अगर (retval == 0) अणु
				अगर( copy_to_user(arg, &rAbilities,
							माप(MW_ABILITIES)) )
					वापस -EFAULT;
			पूर्ण
			PRINTK_2(TRACE_MWAVE,
				"mwavedd::mwave_ioctl, IOCTL_MW_DSP_ABILITIES"
				" exit retval %x\n",
				retval);
		पूर्ण
			अवरोध;
	
		हाल IOCTL_MW_READ_DATA:
		हाल IOCTL_MW_READCLEAR_DATA: अणु
			MW_READWRITE rReadData;
			अचिन्हित लघु __user *pusBuffer = शून्य;
	
			अगर( copy_from_user(&rReadData, arg,
						माप(MW_READWRITE)) )
				वापस -EFAULT;
			pusBuffer = (अचिन्हित लघु __user *) (rReadData.pBuf);
	
			PRINTK_4(TRACE_MWAVE,
				"mwavedd::mwave_ioctl IOCTL_MW_READ_DATA,"
				" size %lx, ioarg %lx pusBuffer %p\n",
				rReadData.ulDataLength, ioarg, pusBuffer);
			mutex_lock(&mwave_mutex);
			retval = tp3780I_ReadWriteDspDStore(&pDrvData->rBDData,
					iocmd,
					pusBuffer,
					rReadData.ulDataLength,
					rReadData.usDspAddress);
			mutex_unlock(&mwave_mutex);
		पूर्ण
			अवरोध;
	
		हाल IOCTL_MW_READ_INST: अणु
			MW_READWRITE rReadData;
			अचिन्हित लघु __user *pusBuffer = शून्य;
	
			अगर( copy_from_user(&rReadData, arg,
						माप(MW_READWRITE)) )
				वापस -EFAULT;
			pusBuffer = (अचिन्हित लघु __user *) (rReadData.pBuf);
	
			PRINTK_4(TRACE_MWAVE,
				"mwavedd::mwave_ioctl IOCTL_MW_READ_INST,"
				" size %lx, ioarg %lx pusBuffer %p\n",
				rReadData.ulDataLength / 2, ioarg,
				pusBuffer);
			mutex_lock(&mwave_mutex);
			retval = tp3780I_ReadWriteDspDStore(&pDrvData->rBDData,
				iocmd, pusBuffer,
				rReadData.ulDataLength / 2,
				rReadData.usDspAddress);
			mutex_unlock(&mwave_mutex);
		पूर्ण
			अवरोध;
	
		हाल IOCTL_MW_WRITE_DATA: अणु
			MW_READWRITE rWriteData;
			अचिन्हित लघु __user *pusBuffer = शून्य;
	
			अगर( copy_from_user(&rWriteData, arg,
						माप(MW_READWRITE)) )
				वापस -EFAULT;
			pusBuffer = (अचिन्हित लघु __user *) (rWriteData.pBuf);
	
			PRINTK_4(TRACE_MWAVE,
				"mwavedd::mwave_ioctl IOCTL_MW_WRITE_DATA,"
				" size %lx, ioarg %lx pusBuffer %p\n",
				rWriteData.ulDataLength, ioarg,
				pusBuffer);
			mutex_lock(&mwave_mutex);
			retval = tp3780I_ReadWriteDspDStore(&pDrvData->rBDData,
					iocmd, pusBuffer,
					rWriteData.ulDataLength,
					rWriteData.usDspAddress);
			mutex_unlock(&mwave_mutex);
		पूर्ण
			अवरोध;
	
		हाल IOCTL_MW_WRITE_INST: अणु
			MW_READWRITE rWriteData;
			अचिन्हित लघु __user *pusBuffer = शून्य;
	
			अगर( copy_from_user(&rWriteData, arg,
						माप(MW_READWRITE)) )
				वापस -EFAULT;
			pusBuffer = (अचिन्हित लघु __user *)(rWriteData.pBuf);
	
			PRINTK_4(TRACE_MWAVE,
				"mwavedd::mwave_ioctl IOCTL_MW_WRITE_INST,"
				" size %lx, ioarg %lx pusBuffer %p\n",
				rWriteData.ulDataLength, ioarg,
				pusBuffer);
			mutex_lock(&mwave_mutex);
			retval = tp3780I_ReadWriteDspIStore(&pDrvData->rBDData,
					iocmd, pusBuffer,
					rWriteData.ulDataLength,
					rWriteData.usDspAddress);
			mutex_unlock(&mwave_mutex);
		पूर्ण
			अवरोध;
	
		हाल IOCTL_MW_REGISTER_IPC: अणु
			अचिन्हित पूर्णांक ipcnum = (अचिन्हित पूर्णांक) ioarg;
	
			अगर (ipcnum >= ARRAY_SIZE(pDrvData->IPCs)) अणु
				PRINTK_ERROR(KERN_ERR_MWAVE
						"mwavedd::mwave_ioctl:"
						" IOCTL_MW_REGISTER_IPC:"
						" Error: Invalid ipcnum %x\n",
						ipcnum);
				वापस -EINVAL;
			पूर्ण
			ipcnum = array_index_nospec(ipcnum,
						    ARRAY_SIZE(pDrvData->IPCs));
			PRINTK_3(TRACE_MWAVE,
				"mwavedd::mwave_ioctl IOCTL_MW_REGISTER_IPC"
				" ipcnum %x entry usIntCount %x\n",
				ipcnum,
				pDrvData->IPCs[ipcnum].usIntCount);

			mutex_lock(&mwave_mutex);
			pDrvData->IPCs[ipcnum].bIsHere = false;
			pDrvData->IPCs[ipcnum].bIsEnabled = true;
			mutex_unlock(&mwave_mutex);
	
			PRINTK_2(TRACE_MWAVE,
				"mwavedd::mwave_ioctl IOCTL_MW_REGISTER_IPC"
				" ipcnum %x exit\n",
				ipcnum);
		पूर्ण
			अवरोध;
	
		हाल IOCTL_MW_GET_IPC: अणु
			अचिन्हित पूर्णांक ipcnum = (अचिन्हित पूर्णांक) ioarg;
	
			अगर (ipcnum >= ARRAY_SIZE(pDrvData->IPCs)) अणु
				PRINTK_ERROR(KERN_ERR_MWAVE
						"mwavedd::mwave_ioctl:"
						" IOCTL_MW_GET_IPC: Error:"
						" Invalid ipcnum %x\n", ipcnum);
				वापस -EINVAL;
			पूर्ण
			ipcnum = array_index_nospec(ipcnum,
						    ARRAY_SIZE(pDrvData->IPCs));
			PRINTK_3(TRACE_MWAVE,
				"mwavedd::mwave_ioctl IOCTL_MW_GET_IPC"
				" ipcnum %x, usIntCount %x\n",
				ipcnum,
				pDrvData->IPCs[ipcnum].usIntCount);
	
			mutex_lock(&mwave_mutex);
			अगर (pDrvData->IPCs[ipcnum].bIsEnabled == true) अणु
				DECLARE_WAITQUEUE(रुको, current);

				PRINTK_2(TRACE_MWAVE,
					"mwavedd::mwave_ioctl, thread for"
					" ipc %x going to sleep\n",
					ipcnum);
				add_रुको_queue(&pDrvData->IPCs[ipcnum].ipc_रुको_queue, &रुको);
				pDrvData->IPCs[ipcnum].bIsHere = true;
				set_current_state(TASK_INTERRUPTIBLE);
				/* check whether an event was संकेतled by */
				/* the पूर्णांकerrupt handler जबतक we were gone */
				अगर (pDrvData->IPCs[ipcnum].usIntCount == 1) अणु	/* first पूर्णांक has occurred (race condition) */
					pDrvData->IPCs[ipcnum].usIntCount = 2;	/* first पूर्णांक has been handled */
					PRINTK_2(TRACE_MWAVE,
						"mwavedd::mwave_ioctl"
						" IOCTL_MW_GET_IPC ipcnum %x"
						" handling first int\n",
						ipcnum);
				पूर्ण अन्यथा अणु	/* either 1st पूर्णांक has not yet occurred, or we have alपढ़ोy handled the first पूर्णांक */
					schedule();
					अगर (pDrvData->IPCs[ipcnum].usIntCount == 1) अणु
						pDrvData->IPCs[ipcnum].usIntCount = 2;
					पूर्ण
					PRINTK_2(TRACE_MWAVE,
						"mwavedd::mwave_ioctl"
						" IOCTL_MW_GET_IPC ipcnum %x"
						" woke up and returning to"
						" application\n",
						ipcnum);
				पूर्ण
				pDrvData->IPCs[ipcnum].bIsHere = false;
				हटाओ_रुको_queue(&pDrvData->IPCs[ipcnum].ipc_रुको_queue, &रुको);
				set_current_state(TASK_RUNNING);
				PRINTK_2(TRACE_MWAVE,
					"mwavedd::mwave_ioctl IOCTL_MW_GET_IPC,"
					" returning thread for ipc %x"
					" processing\n",
					ipcnum);
			पूर्ण
			mutex_unlock(&mwave_mutex);
		पूर्ण
			अवरोध;
	
		हाल IOCTL_MW_UNREGISTER_IPC: अणु
			अचिन्हित पूर्णांक ipcnum = (अचिन्हित पूर्णांक) ioarg;
	
			PRINTK_2(TRACE_MWAVE,
				"mwavedd::mwave_ioctl IOCTL_MW_UNREGISTER_IPC"
				" ipcnum %x\n",
				ipcnum);
			अगर (ipcnum >= ARRAY_SIZE(pDrvData->IPCs)) अणु
				PRINTK_ERROR(KERN_ERR_MWAVE
						"mwavedd::mwave_ioctl:"
						" IOCTL_MW_UNREGISTER_IPC:"
						" Error: Invalid ipcnum %x\n",
						ipcnum);
				वापस -EINVAL;
			पूर्ण
			ipcnum = array_index_nospec(ipcnum,
						    ARRAY_SIZE(pDrvData->IPCs));
			mutex_lock(&mwave_mutex);
			अगर (pDrvData->IPCs[ipcnum].bIsEnabled == true) अणु
				pDrvData->IPCs[ipcnum].bIsEnabled = false;
				अगर (pDrvData->IPCs[ipcnum].bIsHere == true) अणु
					wake_up_पूर्णांकerruptible(&pDrvData->IPCs[ipcnum].ipc_रुको_queue);
				पूर्ण
			पूर्ण
			mutex_unlock(&mwave_mutex);
		पूर्ण
			अवरोध;
	
		शेष:
			वापस -ENOTTY;
	पूर्ण /* चयन */

	PRINTK_2(TRACE_MWAVE, "mwavedd::mwave_ioctl, exit retval %x\n", retval);

	वापस retval;
पूर्ण


अटल sमाप_प्रकार mwave_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
                          loff_t * ppos)
अणु
	PRINTK_5(TRACE_MWAVE,
		"mwavedd::mwave_read entry file %p, buf %p, count %zx ppos %p\n",
		file, buf, count, ppos);

	वापस -EINVAL;
पूर्ण


अटल sमाप_प्रकार mwave_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
                           माप_प्रकार count, loff_t * ppos)
अणु
	PRINTK_5(TRACE_MWAVE,
		"mwavedd::mwave_write entry file %p, buf %p,"
		" count %zx ppos %p\n",
		file, buf, count, ppos);

	वापस -EINVAL;
पूर्ण


अटल पूर्णांक रेजिस्टर_serial_portandirq(अचिन्हित पूर्णांक port, पूर्णांक irq)
अणु
	काष्ठा uart_8250_port uart;
	
	चयन ( port ) अणु
		हाल 0x3f8:
		हाल 0x2f8:
		हाल 0x3e8:
		हाल 0x2e8:
			/* OK */
			अवरोध;
		शेष:
			PRINTK_ERROR(KERN_ERR_MWAVE
					"mwavedd::register_serial_portandirq:"
					" Error: Illegal port %x\n", port );
			वापस -1;
	पूर्ण /* चयन */
	/* port is okay */

	चयन ( irq ) अणु
		हाल 3:
		हाल 4:
		हाल 5:
		हाल 7:
			/* OK */
			अवरोध;
		शेष:
			PRINTK_ERROR(KERN_ERR_MWAVE
					"mwavedd::register_serial_portandirq:"
					" Error: Illegal irq %x\n", irq );
			वापस -1;
	पूर्ण /* चयन */
	/* irq is okay */

	स_रखो(&uart, 0, माप(uart));
	
	uart.port.uartclk =  1843200;
	uart.port.iobase = port;
	uart.port.irq = irq;
	uart.port.iotype = UPIO_PORT;
	uart.port.flags =  UPF_SHARE_IRQ;
	वापस serial8250_रेजिस्टर_8250_port(&uart);
पूर्ण


अटल स्थिर काष्ठा file_operations mwave_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= mwave_पढ़ो,
	.ग_लिखो		= mwave_ग_लिखो,
	.unlocked_ioctl	= mwave_ioctl,
	.खोलो		= mwave_खोलो,
	.release	= mwave_बंद,
	.llseek		= शेष_llseek,
पूर्ण;


अटल काष्ठा miscdevice mwave_misc_dev = अणु MWAVE_MINOR, "mwave", &mwave_fops पूर्ण;

#अगर 0 /* totally b0rked */
/*
 * sysfs support <paulsch@us.ibm.com>
 */

काष्ठा device mwave_device;

/* Prevent code redundancy, create a macro क्रम mwave_show_* functions. */
#घोषणा mwave_show_function(attr_name, क्रमmat_string, field)		\
अटल sमाप_प्रकार mwave_show_##attr_name(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	DSP_3780I_CONFIG_SETTINGS *pSettings =				\
		&mwave_s_mdd.rBDData.rDspSettings;			\
        वापस प्र_लिखो(buf, क्रमmat_string, pSettings->field);		\
पूर्ण

/* All of our attributes are पढ़ो attributes. */
#घोषणा mwave_dev_rd_attr(attr_name, क्रमmat_string, field)		\
	mwave_show_function(attr_name, क्रमmat_string, field)		\
अटल DEVICE_ATTR(attr_name, S_IRUGO, mwave_show_##attr_name, शून्य)

mwave_dev_rd_attr (3780i_dma, "%i\n", usDspDma);
mwave_dev_rd_attr (3780i_irq, "%i\n", usDspIrq);
mwave_dev_rd_attr (3780i_io, "%#.4x\n", usDspBaseIO);
mwave_dev_rd_attr (uart_irq, "%i\n", usUartIrq);
mwave_dev_rd_attr (uart_io, "%#.4x\n", usUartBaseIO);

अटल काष्ठा device_attribute * स्थिर mwave_dev_attrs[] = अणु
	&dev_attr_3780i_dma,
	&dev_attr_3780i_irq,
	&dev_attr_3780i_io,
	&dev_attr_uart_irq,
	&dev_attr_uart_io,
पूर्ण;
#पूर्ण_अगर

/*
* mwave_init is called on module load
*
* mwave_निकास is called on module unload
* mwave_निकास is also used to clean up after an पातed mwave_init
*/
अटल व्योम mwave_निकास(व्योम)
अणु
	pMWAVE_DEVICE_DATA pDrvData = &mwave_s_mdd;

	PRINTK_1(TRACE_MWAVE, "mwavedd::mwave_exit entry\n");

#अगर 0
	क्रम (i = 0; i < pDrvData->nr_रेजिस्टरed_attrs; i++)
		device_हटाओ_file(&mwave_device, mwave_dev_attrs[i]);
	pDrvData->nr_रेजिस्टरed_attrs = 0;

	अगर (pDrvData->device_रेजिस्टरed) अणु
		device_unरेजिस्टर(&mwave_device);
		pDrvData->device_रेजिस्टरed = false;
	पूर्ण
#पूर्ण_अगर

	अगर ( pDrvData->sLine >= 0 ) अणु
		serial8250_unरेजिस्टर_port(pDrvData->sLine);
	पूर्ण
	अगर (pDrvData->bMwaveDevRegistered) अणु
		misc_deरेजिस्टर(&mwave_misc_dev);
	पूर्ण
	अगर (pDrvData->bDSPEnabled) अणु
		tp3780I_DisableDSP(&pDrvData->rBDData);
	पूर्ण
	अगर (pDrvData->bResourcesClaimed) अणु
		tp3780I_ReleaseResources(&pDrvData->rBDData);
	पूर्ण
	अगर (pDrvData->bBDInitialized) अणु
		tp3780I_Cleanup(&pDrvData->rBDData);
	पूर्ण

	PRINTK_1(TRACE_MWAVE, "mwavedd::mwave_exit exit\n");
पूर्ण

module_निकास(mwave_निकास);

अटल पूर्णांक __init mwave_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक retval = 0;
	pMWAVE_DEVICE_DATA pDrvData = &mwave_s_mdd;

	PRINTK_1(TRACE_MWAVE, "mwavedd::mwave_init entry\n");

	स_रखो(&mwave_s_mdd, 0, माप(MWAVE_DEVICE_DATA));

	pDrvData->bBDInitialized = false;
	pDrvData->bResourcesClaimed = false;
	pDrvData->bDSPEnabled = false;
	pDrvData->bDSPReset = false;
	pDrvData->bMwaveDevRegistered = false;
	pDrvData->sLine = -1;

	क्रम (i = 0; i < ARRAY_SIZE(pDrvData->IPCs); i++) अणु
		pDrvData->IPCs[i].bIsEnabled = false;
		pDrvData->IPCs[i].bIsHere = false;
		pDrvData->IPCs[i].usIntCount = 0;	/* no पूर्णांकs received yet */
		init_रुकोqueue_head(&pDrvData->IPCs[i].ipc_रुको_queue);
	पूर्ण

	retval = tp3780I_InitializeBoardData(&pDrvData->rBDData);
	PRINTK_2(TRACE_MWAVE,
		"mwavedd::mwave_init, return from tp3780I_InitializeBoardData"
		" retval %x\n",
		retval);
	अगर (retval) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE
				"mwavedd::mwave_init: Error:"
				" Failed to initialize board data\n");
		जाओ cleanup_error;
	पूर्ण
	pDrvData->bBDInitialized = true;

	retval = tp3780I_CalcResources(&pDrvData->rBDData);
	PRINTK_2(TRACE_MWAVE,
		"mwavedd::mwave_init, return from tp3780I_CalcResources"
		" retval %x\n",
		retval);
	अगर (retval) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE
				"mwavedd:mwave_init: Error:"
				" Failed to calculate resources\n");
		जाओ cleanup_error;
	पूर्ण

	retval = tp3780I_ClaimResources(&pDrvData->rBDData);
	PRINTK_2(TRACE_MWAVE,
		"mwavedd::mwave_init, return from tp3780I_ClaimResources"
		" retval %x\n",
		retval);
	अगर (retval) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE
				"mwavedd:mwave_init: Error:"
				" Failed to claim resources\n");
		जाओ cleanup_error;
	पूर्ण
	pDrvData->bResourcesClaimed = true;

	retval = tp3780I_EnableDSP(&pDrvData->rBDData);
	PRINTK_2(TRACE_MWAVE,
		"mwavedd::mwave_init, return from tp3780I_EnableDSP"
		" retval %x\n",
		retval);
	अगर (retval) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE
				"mwavedd:mwave_init: Error:"
				" Failed to enable DSP\n");
		जाओ cleanup_error;
	पूर्ण
	pDrvData->bDSPEnabled = true;

	अगर (misc_रेजिस्टर(&mwave_misc_dev) < 0) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE
				"mwavedd:mwave_init: Error:"
				" Failed to register misc device\n");
		जाओ cleanup_error;
	पूर्ण
	pDrvData->bMwaveDevRegistered = true;

	pDrvData->sLine = रेजिस्टर_serial_portandirq(
		pDrvData->rBDData.rDspSettings.usUartBaseIO,
		pDrvData->rBDData.rDspSettings.usUartIrq
	);
	अगर (pDrvData->sLine < 0) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE
				"mwavedd:mwave_init: Error:"
				" Failed to register serial driver\n");
		जाओ cleanup_error;
	पूर्ण
	/* uart is रेजिस्टरed */

#अगर 0
	/* sysfs */
	स_रखो(&mwave_device, 0, माप (काष्ठा device));
	dev_set_name(&mwave_device, "mwave");

	अगर (device_रेजिस्टर(&mwave_device))
		जाओ cleanup_error;
	pDrvData->device_रेजिस्टरed = true;
	क्रम (i = 0; i < ARRAY_SIZE(mwave_dev_attrs); i++) अणु
		अगर(device_create_file(&mwave_device, mwave_dev_attrs[i])) अणु
			PRINTK_ERROR(KERN_ERR_MWAVE
					"mwavedd:mwave_init: Error:"
					" Failed to create sysfs file %s\n",
					mwave_dev_attrs[i]->attr.name);
			जाओ cleanup_error;
		पूर्ण
		pDrvData->nr_रेजिस्टरed_attrs++;
	पूर्ण
#पूर्ण_अगर

	/* SUCCESS! */
	वापस 0;

cleanup_error:
	PRINTK_ERROR(KERN_ERR_MWAVE
			"mwavedd::mwave_init: Error:"
			" Failed to initialize\n");
	mwave_निकास(); /* clean up */

	वापस -EIO;
पूर्ण

module_init(mwave_init);

