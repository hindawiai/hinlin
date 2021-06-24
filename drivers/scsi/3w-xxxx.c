<शैली गुरु>
/*
   3w-xxxx.c -- 3ware Storage Controller device driver क्रम Linux.

   Written By: Adam Radक्रमd <aradक्रमd@gmail.com>
   Modअगरications By: Joel Jacobson <linux@3ware.com>
                     Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
                     Brad Stअक्रम <linux@3ware.com>

   Copyright (C) 1999-2010 3ware Inc.

   Kernel compatibility By:	Andre Hedrick <andre@suse.com>
   Non-Copyright (C) 2000	Andre Hedrick <andre@suse.com>

   Further tiny build fixes and trivial hoovering    Alan Cox

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License क्रम more details.

   NO WARRANTY
   THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
   LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
   MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
   solely responsible क्रम determining the appropriateness of using and
   distributing the Program and assumes all risks associated with its
   exercise of rights under this Agreement, including but not limited to
   the risks and costs of program errors, damage to or loss of data,
   programs or equipment, and unavailability or पूर्णांकerruption of operations.

   DISCLAIMER OF LIABILITY
   NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
   सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
   TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
   USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
   HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES

   You should have received a copy of the GNU General Public License
   aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

   Bugs/Comments/Suggestions should be mailed to:

   aradक्रमd@gmail.com


   History
   -------
   0.1.000 -     Initial release.
   0.4.000 -     Added support क्रम Asynchronous Event Notअगरication through
                 ioctls क्रम 3DM.
   1.0.000 -     Added DPO & FUA bit support क्रम WRITE_10 & WRITE_6 cdb
                 to disable drive ग_लिखो-cache beक्रमe ग_लिखोs.
   1.1.000 -     Fixed perक्रमmance bug with DPO & FUA not existing क्रम WRITE_6.
   1.2.000 -     Added support क्रम clean shutकरोwn notअगरication/feature table.
   1.02.00.001 - Added support क्रम full command packet posts through ioctls
                 क्रम 3DM.
                 Bug fix so hot spare drives करोn't show up.
   1.02.00.002 - Fix bug with tw_setfeature() call that caused oops on some
                 प्रणालीs.
   08/21/00    - release previously allocated resources on failure at
                 tw_allocate_memory (acme)
   1.02.00.003 - Fix tw_पूर्णांकerrupt() to report error to scsi layer when
                 controller status is non-zero.
                 Added handling of request_sense opcode.
		 Fix possible null poपूर्णांकer dereference in
                 tw_reset_device_extension()
   1.02.00.004 - Add support क्रम device id of 3ware 7000 series controllers.
                 Make tw_setfeature() call with पूर्णांकerrupts disabled.
                 Register पूर्णांकerrupt handler beक्रमe enabling पूर्णांकerrupts.
                 Clear attention पूर्णांकerrupt beक्रमe draining aen queue.
   1.02.00.005 - Allocate bounce buffers and custom queue depth क्रम raid5 क्रम
                 6000 and 5000 series controllers.
                 Reduce polling mdelays causing problems on some प्रणालीs.
                 Fix use_sg = 1 calculation bug.
                 Check क्रम scsi_रेजिस्टर वापसing शून्य.
                 Add aen count to /proc/scsi/3w-xxxx.
                 Remove aen code unit masking in tw_aen_complete().
   1.02.00.006 - Remove unit from prपूर्णांकk in tw_scsi_eh_पात(), causing
                 possible oops.
                 Fix possible null poपूर्णांकer dereference in tw_scsi_queue()
                 अगर करोne function poपूर्णांकer was invalid.
   1.02.00.007 - Fix possible null poपूर्णांकer dereferences in tw_ioctl().
                 Remove check क्रम invalid करोne function poपूर्णांकer from
                 tw_scsi_queue().
   1.02.00.008 - Set max sectors per io to TW_MAX_SECTORS in tw_findcards().
                 Add tw_decode_error() क्रम prपूर्णांकing पढ़ोable error messages.
                 Prपूर्णांक some useful inक्रमmation on certain aen codes.
                 Add tw_decode_bits() क्रम पूर्णांकerpreting status रेजिस्टर output.
                 Make scsi_set_pci_device() क्रम kernels >= 2.4.4
                 Fix bug where aen's could be lost beक्रमe a reset.
                 Re-add spinlocks in tw_scsi_detect().
                 Fix possible null poपूर्णांकer dereference in tw_aen_drain_queue()
                 during initialization.
                 Clear pci parity errors during initialization and during io.
   1.02.00.009 - Remove redundant increment in tw_state_request_start().
                 Add ioctl support क्रम direct ATA command passthru.
                 Add entire aen code string list.
   1.02.00.010 - Cleanup queueing code, fix jbod thoughput.
                 Fix get_param क्रम specअगरic units.
   1.02.00.011 - Fix bug in tw_aen_complete() where aen's could be lost.
                 Fix tw_aen_drain_queue() to display useful info at init.
                 Set tw_host->max_id क्रम 12 port cards.
                 Add ioctl support क्रम raw command packet post from userspace
                 with sglist fragments (parameter and io).
   1.02.00.012 - Fix पढ़ो capacity to under report by 1 sector to fix get
                 last sector ioctl.
   1.02.00.013 - Fix bug where more AEN codes weren't coming out during
                 driver initialization.
                 Improved handling of PCI पातs.
   1.02.00.014 - Fix bug in tw_findcards() where AEN code could be lost.
                 Increase समयout in tw_aen_drain_queue() to 30 seconds.
   1.02.00.015 - Re-ग_लिखो raw command post with data ioctl method.
                 Remove raid5 bounce buffers क्रम raid5 क्रम 6XXX क्रम kernel 2.5
                 Add tw_map/unmap_scsi_sg/single_data() क्रम kernel 2.5
                 Replace io_request_lock with host_lock क्रम kernel 2.5
                 Set max_cmd_len to 16 क्रम 3dm क्रम kernel 2.5
   1.02.00.016 - Set host->max_sectors back up to 256.
   1.02.00.017 - Modअगरied pci parity error handling/clearing from config space
                 during initialization.
   1.02.00.018 - Better handling of request sense opcode and sense inक्रमmation
                 क्रम failed commands.  Add tw_decode_sense().
                 Replace all mdelay()'s with scsi_sleep().
   1.02.00.019 - Revert mdelay's and scsi_sleep's, this caused problems on
                 some SMP प्रणालीs.
   1.02.00.020 - Add pci_set_dma_mask(), reग_लिखो kदो_स्मृति()/virt_to_bus() to
                 pci_alloc/मुक्त_consistent().
                 Better alignment checking in tw_allocate_memory().
                 Cleanup tw_initialize_device_extension().
   1.02.00.021 - Bump cmd_per_lun in SHT to 255 क्रम better jbod perक्रमmance.
                 Improve handling of errors in tw_पूर्णांकerrupt().
                 Add handling/clearing of controller queue error.
                 Empty stale responses beक्रमe draining aen queue.
                 Fix tw_scsi_eh_पात() to not reset on every io पात.
                 Set can_queue in SHT to 255 to prevent hang from AEN.
   1.02.00.022 - Fix possible null poपूर्णांकer dereference in tw_scsi_release().
   1.02.00.023 - Fix bug in tw_aen_drain_queue() where unit # was always zero.
   1.02.00.024 - Add severity levels to AEN strings.
   1.02.00.025 - Fix command पूर्णांकerrupt spurious error messages.
                 Fix bug in raw command post with data ioctl method.
                 Fix bug where rollcall someबार failed with cable errors.
                 Prपूर्णांक unit # on all command समयouts.
   1.02.00.026 - Fix possible infinite retry bug with घातer glitch induced
                 drive समयouts.
                 Cleanup some AEN severity levels.
   1.02.00.027 - Add drive not supported AEN code क्रम SATA controllers.
                 Remove spurious unknown ioctl error message.
   1.02.00.028 - Fix bug where multiple controllers with no units were the
                 same card number.
                 Fix bug where cards were being shut करोwn more than once.
   1.02.00.029 - Add missing pci_मुक्त_consistent() in tw_allocate_memory().
                 Replace pci_map_single() with pci_map_page() क्रम highmem.
                 Check क्रम tw_setfeature() failure.
   1.02.00.030 - Make driver 64-bit clean.
   1.02.00.031 - Cleanup polling समयouts/routines in several places.
                 Add support क्रम mode sense opcode.
                 Add support क्रम cache mode page.
                 Add support क्रम synchronize cache opcode.
   1.02.00.032 - Fix small multicard rollcall bug.
                 Make driver stay loaded with no units क्रम hot add/swap.
                 Add support क्रम "twe" अक्षरacter device क्रम ioctls.
                 Clean up request_id queueing code.
                 Fix tw_scsi_queue() spinlocks.
   1.02.00.033 - Fix tw_aen_complete() to not queue 'queue empty' AEN's.
                 Initialize queues correctly when loading with no valid units.
   1.02.00.034 - Fix tw_decode_bits() to handle multiple errors.
                 Add support क्रम user configurable cmd_per_lun.
                 Add support क्रम sht->slave_configure().
   1.02.00.035 - Improve tw_allocate_memory() memory allocation.
                 Fix tw_chrdev_ioctl() to sleep correctly.
   1.02.00.036 - Increase अक्षरacter ioctl समयout to 60 seconds.
   1.02.00.037 - Fix tw_ioctl() to handle all non-data ATA passthru cmds
                 क्रम 'smartmontools' support.
   1.26.00.038 - Roll driver minor version to 26 to denote kernel 2.6.
                 Add support क्रम cmds_per_lun module parameter.
   1.26.00.039 - Fix bug in tw_chrdev_ioctl() polling code.
                 Fix data_buffer_length usage in tw_chrdev_ioctl().
                 Update contact inक्रमmation.
   1.26.02.000 - Convert driver to pci_driver क्रमmat.
   1.26.02.001 - Increase max ioctl buffer size to 512 sectors.
                 Make tw_scsi_queue() वापस 0 क्रम 'Unknown scsi opcode'.
                 Fix tw_हटाओ() to मुक्त irq handler/unरेजिस्टर_chrdev()
                 beक्रमe shutting करोwn card.
                 Change to new 'change_queue_depth' api.
                 Fix 'handled=1' ISR usage, हटाओ bogus IRQ check.
   1.26.02.002 - Free irq handler in __tw_shutकरोwn().
                 Turn on RCD bit क्रम caching mode page.
                 Serialize reset code.
   1.26.02.003 - Force 60 second समयout शेष.
*/

#समावेश <linux/module.h>
#समावेश <linux/reboot.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>
#समावेश <linux/समय.स>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_eh.h>
#समावेश "3w-xxxx.h"

/* Globals */
#घोषणा TW_DRIVER_VERSION "1.26.02.003"
अटल DEFINE_MUTEX(tw_mutex);
अटल TW_Device_Extension *tw_device_extension_list[TW_MAX_SLOT];
अटल पूर्णांक tw_device_extension_count = 0;
अटल पूर्णांक twe_major = -1;

/* Module parameters */
MODULE_AUTHOR("LSI");
MODULE_DESCRIPTION("3ware Storage Controller Linux Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(TW_DRIVER_VERSION);

/* Function prototypes */
अटल पूर्णांक tw_reset_device_extension(TW_Device_Extension *tw_dev);

/* Functions */

/* This function will check the status रेजिस्टर क्रम unexpected bits */
अटल पूर्णांक tw_check_bits(u32 status_reg_value)
अणु
	अगर ((status_reg_value & TW_STATUS_EXPECTED_BITS) != TW_STATUS_EXPECTED_BITS) अणु
		dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_check_bits(): No expected bits (0x%x).\n", status_reg_value);
		वापस 1;
	पूर्ण
	अगर ((status_reg_value & TW_STATUS_UNEXPECTED_BITS) != 0) अणु
		dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_check_bits(): Found unexpected bits (0x%x).\n", status_reg_value);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण /* End tw_check_bits() */

/* This function will prपूर्णांक पढ़ोable messages from status रेजिस्टर errors */
अटल पूर्णांक tw_decode_bits(TW_Device_Extension *tw_dev, u32 status_reg_value, पूर्णांक prपूर्णांक_host)
अणु
	अक्षर host[16];

	dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_decode_bits()\n");

	अगर (prपूर्णांक_host)
		प्र_लिखो(host, " scsi%d:", tw_dev->host->host_no);
	अन्यथा
		host[0] = '\0';

	अगर (status_reg_value & TW_STATUS_PCI_PARITY_ERROR) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx:%s PCI Parity Error: clearing.\n", host);
		outl(TW_CONTROL_CLEAR_PARITY_ERROR, TW_CONTROL_REG_ADDR(tw_dev));
	पूर्ण

	अगर (status_reg_value & TW_STATUS_PCI_ABORT) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx:%s PCI Abort: clearing.\n", host);
		outl(TW_CONTROL_CLEAR_PCI_ABORT, TW_CONTROL_REG_ADDR(tw_dev));
		pci_ग_लिखो_config_word(tw_dev->tw_pci_dev, PCI_STATUS, TW_PCI_CLEAR_PCI_ABORT);
	पूर्ण

	अगर (status_reg_value & TW_STATUS_QUEUE_ERROR) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx:%s Controller Queue Error: clearing.\n", host);
		outl(TW_CONTROL_CLEAR_QUEUE_ERROR, TW_CONTROL_REG_ADDR(tw_dev));
	पूर्ण

	अगर (status_reg_value & TW_STATUS_SBUF_WRITE_ERROR) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx:%s SBUF Write Error: clearing.\n", host);
		outl(TW_CONTROL_CLEAR_SBUF_WRITE_ERROR, TW_CONTROL_REG_ADDR(tw_dev));
	पूर्ण

	अगर (status_reg_value & TW_STATUS_MICROCONTROLLER_ERROR) अणु
		अगर (tw_dev->reset_prपूर्णांक == 0) अणु
			prपूर्णांकk(KERN_WARNING "3w-xxxx:%s Microcontroller Error: clearing.\n", host);
			tw_dev->reset_prपूर्णांक = 1;
		पूर्ण
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण /* End tw_decode_bits() */

/* This function will poll the status रेजिस्टर क्रम a flag */
अटल पूर्णांक tw_poll_status(TW_Device_Extension *tw_dev, u32 flag, पूर्णांक seconds)
अणु
	u32 status_reg_value;
	अचिन्हित दीर्घ beक्रमe;
	पूर्णांक retval = 1;

	status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));
	beक्रमe = jअगरfies;

	अगर (tw_check_bits(status_reg_value))
		tw_decode_bits(tw_dev, status_reg_value, 0);

	जबतक ((status_reg_value & flag) != flag) अणु
		status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));

		अगर (tw_check_bits(status_reg_value))
			tw_decode_bits(tw_dev, status_reg_value, 0);

		अगर (समय_after(jअगरfies, beक्रमe + HZ * seconds))
			जाओ out;

		msleep(50);
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण /* End tw_poll_status() */

/* This function will poll the status रेजिस्टर क्रम disappearance of a flag */
अटल पूर्णांक tw_poll_status_gone(TW_Device_Extension *tw_dev, u32 flag, पूर्णांक seconds)
अणु
	u32 status_reg_value;
	अचिन्हित दीर्घ beक्रमe;
	पूर्णांक retval = 1;

	status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));
	beक्रमe = jअगरfies;

	अगर (tw_check_bits(status_reg_value))
		tw_decode_bits(tw_dev, status_reg_value, 0);

	जबतक ((status_reg_value & flag) != 0) अणु
		status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));

		अगर (tw_check_bits(status_reg_value))
			tw_decode_bits(tw_dev, status_reg_value, 0);

		अगर (समय_after(jअगरfies, beक्रमe + HZ * seconds))
			जाओ out;

		msleep(50);
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण /* End tw_poll_status_gone() */

/* This function will attempt to post a command packet to the board */
अटल पूर्णांक tw_post_command_packet(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	u32 status_reg_value;
	अचिन्हित दीर्घ command_que_value;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_post_command_packet()\n");
	command_que_value = tw_dev->command_packet_physical_address[request_id];
	status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));

	अगर (tw_check_bits(status_reg_value)) अणु
		dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_post_command_packet(): Unexpected bits.\n");
		tw_decode_bits(tw_dev, status_reg_value, 1);
	पूर्ण

	अगर ((status_reg_value & TW_STATUS_COMMAND_QUEUE_FULL) == 0) अणु
		/* We successfully posted the command packet */
		outl(command_que_value, TW_COMMAND_QUEUE_REG_ADDR(tw_dev));
		tw_dev->state[request_id] = TW_S_POSTED;
		tw_dev->posted_request_count++;
		अगर (tw_dev->posted_request_count > tw_dev->max_posted_request_count) अणु
			tw_dev->max_posted_request_count = tw_dev->posted_request_count;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Couldn't post the command packet, so we करो it in the isr */
		अगर (tw_dev->state[request_id] != TW_S_PENDING) अणु
			tw_dev->state[request_id] = TW_S_PENDING;
			tw_dev->pending_request_count++;
			अगर (tw_dev->pending_request_count > tw_dev->max_pending_request_count) अणु
				tw_dev->max_pending_request_count = tw_dev->pending_request_count;
			पूर्ण
			tw_dev->pending_queue[tw_dev->pending_tail] = request_id;
			अगर (tw_dev->pending_tail == TW_Q_LENGTH-1) अणु
				tw_dev->pending_tail = TW_Q_START;
			पूर्ण अन्यथा अणु
				tw_dev->pending_tail = tw_dev->pending_tail + 1;
			पूर्ण
		पूर्ण
		TW_UNMASK_COMMAND_INTERRUPT(tw_dev);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण /* End tw_post_command_packet() */

/* This function will वापस valid sense buffer inक्रमmation क्रम failed cmds */
अटल पूर्णांक tw_decode_sense(TW_Device_Extension *tw_dev, पूर्णांक request_id, पूर्णांक fill_sense)
अणु
	पूर्णांक i;
	TW_Command *command;

	dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_decode_sense()\n");
	command = (TW_Command *)tw_dev->command_packet_भव_address[request_id];

	prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Command failed: status = 0x%x, flags = 0x%x, unit #%d.\n", tw_dev->host->host_no, command->status, command->flags, TW_UNIT_OUT(command->unit__hostid));

	/* Attempt to वापस पूर्णांकelligent sense inक्रमmation */
	अगर (fill_sense) अणु
		अगर ((command->status == 0xc7) || (command->status == 0xcb)) अणु
			क्रम (i = 0; i < ARRAY_SIZE(tw_sense_table); i++) अणु
				अगर (command->flags == tw_sense_table[i][0]) अणु

					/* Valid bit and 'current errors' */
					tw_dev->srb[request_id]->sense_buffer[0] = (0x1 << 7 | 0x70);

					/* Sense key */
					tw_dev->srb[request_id]->sense_buffer[2] = tw_sense_table[i][1];

					/* Additional sense length */
					tw_dev->srb[request_id]->sense_buffer[7] = 0xa; /* 10 bytes */

					/* Additional sense code */
					tw_dev->srb[request_id]->sense_buffer[12] = tw_sense_table[i][2];

					/* Additional sense code qualअगरier */
					tw_dev->srb[request_id]->sense_buffer[13] = tw_sense_table[i][3];

					tw_dev->srb[request_id]->result = (DID_OK << 16) | (CHECK_CONDITION << 1);
					वापस TW_ISR_DONT_RESULT; /* Special हाल क्रम isr to not over-ग_लिखो result */
				पूर्ण
			पूर्ण
		पूर्ण

		/* If no table match, error so we get a reset */
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण /* End tw_decode_sense() */

/* This function will report controller error status */
अटल पूर्णांक tw_check_errors(TW_Device_Extension *tw_dev)
अणु
	u32 status_reg_value;

	status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));

	अगर (TW_STATUS_ERRORS(status_reg_value) || tw_check_bits(status_reg_value)) अणु
		tw_decode_bits(tw_dev, status_reg_value, 0);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण /* End tw_check_errors() */

/* This function will empty the response que */
अटल व्योम tw_empty_response_que(TW_Device_Extension *tw_dev)
अणु
	u32 status_reg_value;

	status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));

	जबतक ((status_reg_value & TW_STATUS_RESPONSE_QUEUE_EMPTY) == 0) अणु
		inl(TW_RESPONSE_QUEUE_REG_ADDR(tw_dev));
		status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));
	पूर्ण
पूर्ण /* End tw_empty_response_que() */

/* This function will मुक्त a request_id */
अटल व्योम tw_state_request_finish(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	tw_dev->मुक्त_queue[tw_dev->मुक्त_tail] = request_id;
	tw_dev->state[request_id] = TW_S_FINISHED;
	tw_dev->मुक्त_tail = (tw_dev->मुक्त_tail + 1) % TW_Q_LENGTH;
पूर्ण /* End tw_state_request_finish() */

/* This function will assign an available request_id */
अटल व्योम tw_state_request_start(TW_Device_Extension *tw_dev, पूर्णांक *request_id)
अणु
	*request_id = tw_dev->मुक्त_queue[tw_dev->मुक्त_head];
	tw_dev->मुक्त_head = (tw_dev->मुक्त_head + 1) % TW_Q_LENGTH;
	tw_dev->state[*request_id] = TW_S_STARTED;
पूर्ण /* End tw_state_request_start() */

/* Show some statistics about the card */
अटल sमाप_प्रकार tw_show_stats(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;
	अचिन्हित दीर्घ flags = 0;
	sमाप_प्रकार len;

	spin_lock_irqsave(tw_dev->host->host_lock, flags);
	len = snम_लिखो(buf, PAGE_SIZE, "3w-xxxx Driver version: %s\n"
		       "Current commands posted:   %4d\n"
		       "Max commands posted:       %4d\n"
		       "Current pending commands:  %4d\n"
		       "Max pending commands:      %4d\n"
		       "Last sgl length:           %4d\n"
		       "Max sgl length:            %4d\n"
		       "Last sector count:         %4d\n"
		       "Max sector count:          %4d\n"
		       "SCSI Host Resets:          %4d\n"
		       "AEN's:                     %4d\n", 
		       TW_DRIVER_VERSION,
		       tw_dev->posted_request_count,
		       tw_dev->max_posted_request_count,
		       tw_dev->pending_request_count,
		       tw_dev->max_pending_request_count,
		       tw_dev->sgl_entries,
		       tw_dev->max_sgl_entries,
		       tw_dev->sector_count,
		       tw_dev->max_sector_count,
		       tw_dev->num_resets,
		       tw_dev->aen_count);
	spin_unlock_irqrestore(tw_dev->host->host_lock, flags);
	वापस len;
पूर्ण /* End tw_show_stats() */

/* Create sysfs 'stats' entry */
अटल काष्ठा device_attribute tw_host_stats_attr = अणु
	.attr = अणु
		.name =		"stats",
		.mode =		S_IRUGO,
	पूर्ण,
	.show = tw_show_stats
पूर्ण;

/* Host attributes initializer */
अटल काष्ठा device_attribute *tw_host_attrs[] = अणु
	&tw_host_stats_attr,
	शून्य,
पूर्ण;

/* This function will पढ़ो the aen queue from the isr */
अटल पूर्णांक tw_aen_पढ़ो_queue(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	TW_Command *command_packet;
	TW_Param *param;
	अचिन्हित दीर्घ command_que_value;
	u32 status_reg_value;
	अचिन्हित दीर्घ param_value = 0;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_aen_read_queue()\n");

	status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));
	अगर (tw_check_bits(status_reg_value)) अणु
		dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_read_queue(): Unexpected bits.\n");
		tw_decode_bits(tw_dev, status_reg_value, 1);
		वापस 1;
	पूर्ण
	अगर (tw_dev->command_packet_भव_address[request_id] == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_read_queue(): Bad command packet virtual address.\n");
		वापस 1;
	पूर्ण
	command_packet = (TW_Command *)tw_dev->command_packet_भव_address[request_id];
	स_रखो(command_packet, 0, माप(TW_Sector));
	command_packet->opcode__sgloffset = TW_OPSGL_IN(2, TW_OP_GET_PARAM);
	command_packet->size = 4;
	command_packet->request_id = request_id;
	command_packet->status = 0;
	command_packet->flags = 0;
	command_packet->byte6.parameter_count = 1;
	command_que_value = tw_dev->command_packet_physical_address[request_id];
	अगर (command_que_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_read_queue(): Bad command packet physical address.\n");
		वापस 1;
	पूर्ण
	/* Now setup the param */
	अगर (tw_dev->alignment_भव_address[request_id] == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_read_queue(): Bad alignment virtual address.\n");
		वापस 1;
	पूर्ण
	param = (TW_Param *)tw_dev->alignment_भव_address[request_id];
	स_रखो(param, 0, माप(TW_Sector));
	param->table_id = 0x401; /* AEN table */
	param->parameter_id = 2; /* Unit code */
	param->parameter_size_bytes = 2;
	param_value = tw_dev->alignment_physical_address[request_id];
	अगर (param_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_read_queue(): Bad alignment physical address.\n");
		वापस 1;
	पूर्ण
	command_packet->byte8.param.sgl[0].address = param_value;
	command_packet->byte8.param.sgl[0].length = माप(TW_Sector);

	/* Now post the command packet */
	अगर ((status_reg_value & TW_STATUS_COMMAND_QUEUE_FULL) == 0) अणु
		dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_read_queue(): Post succeeded.\n");
		tw_dev->srb[request_id] = शून्य; /* Flag पूर्णांकernal command */
		tw_dev->state[request_id] = TW_S_POSTED;
		outl(command_que_value, TW_COMMAND_QUEUE_REG_ADDR(tw_dev));
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_read_queue(): Post failed, will retry.\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण /* End tw_aen_पढ़ो_queue() */

/* This function will complete an aen request from the isr */
अटल पूर्णांक tw_aen_complete(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	TW_Param *param;
	अचिन्हित लघु aen;
	पूर्णांक error = 0, table_max = 0;

	dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_complete()\n");
	अगर (tw_dev->alignment_भव_address[request_id] == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_complete(): Bad alignment virtual address.\n");
		वापस 1;
	पूर्ण
	param = (TW_Param *)tw_dev->alignment_भव_address[request_id];
	aen = *(अचिन्हित लघु *)(param->data);
	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_aen_complete(): Queue'd code 0x%x\n", aen);

	/* Prपूर्णांक some useful info when certain aen codes come out */
	अगर (aen == 0x0ff) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: AEN: INFO: AEN queue overflow.\n", tw_dev->host->host_no);
	पूर्ण अन्यथा अणु
		table_max = ARRAY_SIZE(tw_aen_string);
		अगर ((aen & 0x0ff) < table_max) अणु
			अगर ((tw_aen_string[aen & 0xff][म_माप(tw_aen_string[aen & 0xff])-1]) == '#') अणु
				prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: AEN: %s%d.\n", tw_dev->host->host_no, tw_aen_string[aen & 0xff], aen >> 8);
			पूर्ण अन्यथा अणु
				अगर (aen != 0x0)
					prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: AEN: %s.\n", tw_dev->host->host_no, tw_aen_string[aen & 0xff]);
			पूर्ण
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Received AEN %d.\n", tw_dev->host->host_no, aen);
		पूर्ण
	पूर्ण
	अगर (aen != TW_AEN_QUEUE_EMPTY) अणु
		tw_dev->aen_count++;

		/* Now queue the code */
		tw_dev->aen_queue[tw_dev->aen_tail] = aen;
		अगर (tw_dev->aen_tail == TW_Q_LENGTH - 1) अणु
			tw_dev->aen_tail = TW_Q_START;
		पूर्ण अन्यथा अणु
			tw_dev->aen_tail = tw_dev->aen_tail + 1;
		पूर्ण
		अगर (tw_dev->aen_head == tw_dev->aen_tail) अणु
			अगर (tw_dev->aen_head == TW_Q_LENGTH - 1) अणु
				tw_dev->aen_head = TW_Q_START;
			पूर्ण अन्यथा अणु
				tw_dev->aen_head = tw_dev->aen_head + 1;
			पूर्ण
		पूर्ण

		error = tw_aen_पढ़ो_queue(tw_dev, request_id);
		अगर (error) अणु
			prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Error completing AEN.\n", tw_dev->host->host_no);
			tw_dev->state[request_id] = TW_S_COMPLETED;
			tw_state_request_finish(tw_dev, request_id);
		पूर्ण
	पूर्ण अन्यथा अणु
		tw_dev->state[request_id] = TW_S_COMPLETED;
		tw_state_request_finish(tw_dev, request_id);
	पूर्ण

	वापस 0;
पूर्ण /* End tw_aen_complete() */

/* This function will drain the aen queue after a soft reset */
अटल पूर्णांक tw_aen_drain_queue(TW_Device_Extension *tw_dev)
अणु
	TW_Command *command_packet;
	TW_Param *param;
	पूर्णांक request_id = 0;
	अचिन्हित दीर्घ command_que_value;
	अचिन्हित दीर्घ param_value;
	TW_Response_Queue response_queue;
	अचिन्हित लघु aen;
	अचिन्हित लघु aen_code;
	पूर्णांक finished = 0;
	पूर्णांक first_reset = 0;
	पूर्णांक queue = 0;
	पूर्णांक found = 0, table_max = 0;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_aen_drain_queue()\n");

	अगर (tw_poll_status(tw_dev, TW_STATUS_ATTENTION_INTERRUPT | TW_STATUS_MICROCONTROLLER_READY, 30)) अणु
		dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_drain_queue(): No attention interrupt for card %d.\n", tw_device_extension_count);
		वापस 1;
	पूर्ण
	TW_CLEAR_ATTENTION_INTERRUPT(tw_dev);

	/* Empty response queue */
	tw_empty_response_que(tw_dev);

	/* Initialize command packet */
	अगर (tw_dev->command_packet_भव_address[request_id] == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_drain_queue(): Bad command packet virtual address.\n");
		वापस 1;
	पूर्ण
	command_packet = (TW_Command *)tw_dev->command_packet_भव_address[request_id];
	स_रखो(command_packet, 0, माप(TW_Sector));
	command_packet->opcode__sgloffset = TW_OPSGL_IN(2, TW_OP_GET_PARAM);
	command_packet->size = 4;
	command_packet->request_id = request_id;
	command_packet->status = 0;
	command_packet->flags = 0;
	command_packet->byte6.parameter_count = 1;
	command_que_value = tw_dev->command_packet_physical_address[request_id];
	अगर (command_que_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_drain_queue(): Bad command packet physical address.\n");
		वापस 1;
	पूर्ण

	/* Now setup the param */
	अगर (tw_dev->alignment_भव_address[request_id] == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_drain_queue(): Bad alignment virtual address.\n");
		वापस 1;
	पूर्ण
	param = (TW_Param *)tw_dev->alignment_भव_address[request_id];
	स_रखो(param, 0, माप(TW_Sector));
	param->table_id = 0x401; /* AEN table */
	param->parameter_id = 2; /* Unit code */
	param->parameter_size_bytes = 2;
	param_value = tw_dev->alignment_physical_address[request_id];
	अगर (param_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_drain_queue(): Bad alignment physical address.\n");
		वापस 1;
	पूर्ण
	command_packet->byte8.param.sgl[0].address = param_value;
	command_packet->byte8.param.sgl[0].length = माप(TW_Sector);

	/* Now drain the controller's aen queue */
	करो अणु
		/* Post command packet */
		outl(command_que_value, TW_COMMAND_QUEUE_REG_ADDR(tw_dev));

		/* Now poll क्रम completion */
		अगर (tw_poll_status_gone(tw_dev, TW_STATUS_RESPONSE_QUEUE_EMPTY, 30) == 0) अणु
			response_queue.value = inl(TW_RESPONSE_QUEUE_REG_ADDR(tw_dev));
			request_id = TW_RESID_OUT(response_queue.response_id);

			अगर (request_id != 0) अणु
				/* Unexpected request id */
				prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_drain_queue(): Unexpected request id.\n");
				वापस 1;
			पूर्ण

			अगर (command_packet->status != 0) अणु
				अगर (command_packet->flags != TW_AEN_TABLE_UNDEFINED) अणु
					/* Bad response */
					tw_decode_sense(tw_dev, request_id, 0);
					वापस 1;
				पूर्ण अन्यथा अणु
					/* We know this is a 3w-1x00, and करोesn't support aen's */
					वापस 0;
				पूर्ण
			पूर्ण

			/* Now check the aen */
			aen = *(अचिन्हित लघु *)(param->data);
			aen_code = (aen & 0x0ff);
			queue = 0;
			चयन (aen_code) अणु
				हाल TW_AEN_QUEUE_EMPTY:
					dprपूर्णांकk(KERN_WARNING "3w-xxxx: AEN: %s.\n", tw_aen_string[aen & 0xff]);
					अगर (first_reset != 1) अणु
						वापस 1;
					पूर्ण अन्यथा अणु
						finished = 1;
					पूर्ण
					अवरोध;
				हाल TW_AEN_SOFT_RESET:
					अगर (first_reset == 0) अणु
						first_reset = 1;
					पूर्ण अन्यथा अणु
						prपूर्णांकk(KERN_WARNING "3w-xxxx: AEN: %s.\n", tw_aen_string[aen & 0xff]);
						tw_dev->aen_count++;
						queue = 1;
					पूर्ण
					अवरोध;
				शेष:
					अगर (aen == 0x0ff) अणु
						prपूर्णांकk(KERN_WARNING "3w-xxxx: AEN: INFO: AEN queue overflow.\n");
					पूर्ण अन्यथा अणु
						table_max = ARRAY_SIZE(tw_aen_string);
						अगर ((aen & 0x0ff) < table_max) अणु
							अगर ((tw_aen_string[aen & 0xff][म_माप(tw_aen_string[aen & 0xff])-1]) == '#') अणु
								prपूर्णांकk(KERN_WARNING "3w-xxxx: AEN: %s%d.\n", tw_aen_string[aen & 0xff], aen >> 8);
							पूर्ण अन्यथा अणु
								prपूर्णांकk(KERN_WARNING "3w-xxxx: AEN: %s.\n", tw_aen_string[aen & 0xff]);
							पूर्ण
						पूर्ण अन्यथा
							prपूर्णांकk(KERN_WARNING "3w-xxxx: Received AEN %d.\n", aen);
					पूर्ण
					tw_dev->aen_count++;
					queue = 1;
			पूर्ण

			/* Now put the aen on the aen_queue */
			अगर (queue == 1) अणु
				tw_dev->aen_queue[tw_dev->aen_tail] = aen;
				अगर (tw_dev->aen_tail == TW_Q_LENGTH - 1) अणु
					tw_dev->aen_tail = TW_Q_START;
				पूर्ण अन्यथा अणु
					tw_dev->aen_tail = tw_dev->aen_tail + 1;
				पूर्ण
				अगर (tw_dev->aen_head == tw_dev->aen_tail) अणु
					अगर (tw_dev->aen_head == TW_Q_LENGTH - 1) अणु
						tw_dev->aen_head = TW_Q_START;
					पूर्ण अन्यथा अणु
						tw_dev->aen_head = tw_dev->aen_head + 1;
					पूर्ण
				पूर्ण
			पूर्ण
			found = 1;
		पूर्ण
		अगर (found == 0) अणु
			prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_aen_drain_queue(): Response never received.\n");
			वापस 1;
		पूर्ण
	पूर्ण जबतक (finished == 0);

	वापस 0;
पूर्ण /* End tw_aen_drain_queue() */

/* This function will allocate memory */
अटल पूर्णांक tw_allocate_memory(TW_Device_Extension *tw_dev, पूर्णांक size, पूर्णांक which)
अणु
	पूर्णांक i;
	dma_addr_t dma_handle;
	अचिन्हित दीर्घ *cpu_addr = शून्य;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_allocate_memory()\n");

	cpu_addr = dma_alloc_coherent(&tw_dev->tw_pci_dev->dev,
			size * TW_Q_LENGTH, &dma_handle, GFP_KERNEL);
	अगर (cpu_addr == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: dma_alloc_coherent() failed.\n");
		वापस 1;
	पूर्ण

	अगर ((अचिन्हित दीर्घ)cpu_addr % (tw_dev->tw_pci_dev->device == TW_DEVICE_ID ? TW_ALIGNMENT_6000 : TW_ALIGNMENT_7000)) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: Couldn't allocate correctly aligned memory.\n");
		dma_मुक्त_coherent(&tw_dev->tw_pci_dev->dev, size * TW_Q_LENGTH,
				cpu_addr, dma_handle);
		वापस 1;
	पूर्ण

	स_रखो(cpu_addr, 0, size*TW_Q_LENGTH);

	क्रम (i=0;i<TW_Q_LENGTH;i++) अणु
		चयन(which) अणु
		हाल 0:
			tw_dev->command_packet_physical_address[i] = dma_handle+(i*size);
			tw_dev->command_packet_भव_address[i] = (अचिन्हित दीर्घ *)((अचिन्हित अक्षर *)cpu_addr + (i*size));
			अवरोध;
		हाल 1:
			tw_dev->alignment_physical_address[i] = dma_handle+(i*size);
			tw_dev->alignment_भव_address[i] = (अचिन्हित दीर्घ *)((अचिन्हित अक्षर *)cpu_addr + (i*size));
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_allocate_memory(): case slip in tw_allocate_memory()\n");
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण /* End tw_allocate_memory() */

/* This function handles ioctl क्रम the अक्षरacter device */
अटल दीर्घ tw_chrdev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक request_id;
	dma_addr_t dma_handle;
	अचिन्हित लघु tw_aen_code;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक data_buffer_length = 0;
	अचिन्हित दीर्घ data_buffer_length_adjusted = 0;
	काष्ठा inode *inode = file_inode(file);
	अचिन्हित दीर्घ *cpu_addr;
	दीर्घ समयout;
	TW_New_Ioctl *tw_ioctl;
	TW_Passthru *passthru;
	TW_Device_Extension *tw_dev = tw_device_extension_list[iminor(inode)];
	पूर्णांक retval = -EFAULT;
	व्योम __user *argp = (व्योम __user *)arg;

	dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_chrdev_ioctl()\n");

	mutex_lock(&tw_mutex);
	/* Only let one of these through at a समय */
	अगर (mutex_lock_पूर्णांकerruptible(&tw_dev->ioctl_lock)) अणु
		mutex_unlock(&tw_mutex);
		वापस -EINTR;
	पूर्ण

	/* First copy करोwn the buffer length */
	अगर (copy_from_user(&data_buffer_length, argp, माप(अचिन्हित पूर्णांक)))
		जाओ out;

	/* Check size */
	अगर (data_buffer_length > TW_MAX_IOCTL_SECTORS * 512) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	/* Hardware can only करो multiple of 512 byte transfers */
	data_buffer_length_adjusted = (data_buffer_length + 511) & ~511;

	/* Now allocate ioctl buf memory */
	cpu_addr = dma_alloc_coherent(&tw_dev->tw_pci_dev->dev, data_buffer_length_adjusted+माप(TW_New_Ioctl) - 1, &dma_handle, GFP_KERNEL);
	अगर (cpu_addr == शून्य) अणु
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	tw_ioctl = (TW_New_Ioctl *)cpu_addr;

	/* Now copy करोwn the entire ioctl */
	अगर (copy_from_user(tw_ioctl, argp, data_buffer_length + माप(TW_New_Ioctl) - 1))
		जाओ out2;

	passthru = (TW_Passthru *)&tw_ioctl->firmware_command;

	/* See which ioctl we are करोing */
	चयन (cmd) अणु
		हाल TW_OP_NOP:
			dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_chrdev_ioctl(): caught TW_OP_NOP.\n");
			अवरोध;
		हाल TW_OP_AEN_LISTEN:
			dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_chrdev_ioctl(): caught TW_AEN_LISTEN.\n");
			स_रखो(tw_ioctl->data_buffer, 0, data_buffer_length);

			spin_lock_irqsave(tw_dev->host->host_lock, flags);
			अगर (tw_dev->aen_head == tw_dev->aen_tail) अणु
				tw_aen_code = TW_AEN_QUEUE_EMPTY;
			पूर्ण अन्यथा अणु
				tw_aen_code = tw_dev->aen_queue[tw_dev->aen_head];
				अगर (tw_dev->aen_head == TW_Q_LENGTH - 1) अणु
					tw_dev->aen_head = TW_Q_START;
				पूर्ण अन्यथा अणु
					tw_dev->aen_head = tw_dev->aen_head + 1;
				पूर्ण
			पूर्ण
			spin_unlock_irqrestore(tw_dev->host->host_lock, flags);
			स_नकल(tw_ioctl->data_buffer, &tw_aen_code, माप(tw_aen_code));
			अवरोध;
		हाल TW_CMD_PACKET_WITH_DATA:
			dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_chrdev_ioctl(): caught TW_CMD_PACKET_WITH_DATA.\n");
			spin_lock_irqsave(tw_dev->host->host_lock, flags);

			tw_state_request_start(tw_dev, &request_id);

			/* Flag पूर्णांकernal command */
			tw_dev->srb[request_id] = शून्य;

			/* Flag chrdev ioctl */
			tw_dev->chrdev_request_id = request_id;

			tw_ioctl->firmware_command.request_id = request_id;

			/* Load the sg list */
			चयन (TW_SGL_OUT(tw_ioctl->firmware_command.opcode__sgloffset)) अणु
			हाल 2:
				tw_ioctl->firmware_command.byte8.param.sgl[0].address = dma_handle + माप(TW_New_Ioctl) - 1;
				tw_ioctl->firmware_command.byte8.param.sgl[0].length = data_buffer_length_adjusted;
				अवरोध;
			हाल 3:
				tw_ioctl->firmware_command.byte8.io.sgl[0].address = dma_handle + माप(TW_New_Ioctl) - 1;
				tw_ioctl->firmware_command.byte8.io.sgl[0].length = data_buffer_length_adjusted;
				अवरोध;
			हाल 5:
				passthru->sg_list[0].address = dma_handle + माप(TW_New_Ioctl) - 1;
				passthru->sg_list[0].length = data_buffer_length_adjusted;
				अवरोध;
			पूर्ण

			स_नकल(tw_dev->command_packet_भव_address[request_id], &(tw_ioctl->firmware_command), माप(TW_Command));

			/* Now post the command packet to the controller */
			tw_post_command_packet(tw_dev, request_id);
			spin_unlock_irqrestore(tw_dev->host->host_lock, flags);

			समयout = TW_IOCTL_CHRDEV_TIMEOUT*HZ;

			/* Now रुको क्रम the command to complete */
			समयout = रुको_event_समयout(tw_dev->ioctl_wqueue, tw_dev->chrdev_request_id == TW_IOCTL_CHRDEV_FREE, समयout);

			/* We समयd out, and didn't get an पूर्णांकerrupt */
			अगर (tw_dev->chrdev_request_id != TW_IOCTL_CHRDEV_FREE) अणु
				/* Now we need to reset the board */
				prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Character ioctl (0x%x) timed out, resetting card.\n", tw_dev->host->host_no, cmd);
				retval = -EIO;
				अगर (tw_reset_device_extension(tw_dev)) अणु
					prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_chrdev_ioctl(): Reset failed for card %d.\n", tw_dev->host->host_no);
				पूर्ण
				जाओ out2;
			पूर्ण

			/* Now copy in the command packet response */
			स_नकल(&(tw_ioctl->firmware_command), tw_dev->command_packet_भव_address[request_id], माप(TW_Command));

			/* Now complete the io */
			spin_lock_irqsave(tw_dev->host->host_lock, flags);
			tw_dev->posted_request_count--;
			tw_dev->state[request_id] = TW_S_COMPLETED;
			tw_state_request_finish(tw_dev, request_id);
			spin_unlock_irqrestore(tw_dev->host->host_lock, flags);
			अवरोध;
		शेष:
			retval = -ENOTTY;
			जाओ out2;
	पूर्ण

	/* Now copy the response to userspace */
	अगर (copy_to_user(argp, tw_ioctl, माप(TW_New_Ioctl) + data_buffer_length - 1))
		जाओ out2;
	retval = 0;
out2:
	/* Now मुक्त ioctl buf memory */
	dma_मुक्त_coherent(&tw_dev->tw_pci_dev->dev, data_buffer_length_adjusted+माप(TW_New_Ioctl) - 1, cpu_addr, dma_handle);
out:
	mutex_unlock(&tw_dev->ioctl_lock);
	mutex_unlock(&tw_mutex);
	वापस retval;
पूर्ण /* End tw_chrdev_ioctl() */

/* This function handles खोलो क्रम the अक्षरacter device */
/* NOTE that this function races with हटाओ. */
अटल पूर्णांक tw_chrdev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor_number;

	dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_ioctl_open()\n");

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	minor_number = iminor(inode);
	अगर (minor_number >= tw_device_extension_count)
		वापस -ENODEV;

	वापस 0;
पूर्ण /* End tw_chrdev_खोलो() */

/* File operations काष्ठा क्रम अक्षरacter device */
अटल स्थिर काष्ठा file_operations tw_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= tw_chrdev_ioctl,
	.compat_ioctl   = compat_ptr_ioctl,
	.खोलो		= tw_chrdev_खोलो,
	.release	= शून्य,
	.llseek		= noop_llseek,
पूर्ण;

/* This function will मुक्त up device extension resources */
अटल व्योम tw_मुक्त_device_extension(TW_Device_Extension *tw_dev)
अणु
	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_free_device_extension()\n");

	/* Free command packet and generic buffer memory */
	अगर (tw_dev->command_packet_भव_address[0])
		dma_मुक्त_coherent(&tw_dev->tw_pci_dev->dev,
				माप(TW_Command) * TW_Q_LENGTH,
				tw_dev->command_packet_भव_address[0],
				tw_dev->command_packet_physical_address[0]);

	अगर (tw_dev->alignment_भव_address[0])
		dma_मुक्त_coherent(&tw_dev->tw_pci_dev->dev,
				माप(TW_Sector) * TW_Q_LENGTH,
				tw_dev->alignment_भव_address[0],
				tw_dev->alignment_physical_address[0]);
पूर्ण /* End tw_मुक्त_device_extension() */

/* This function will send an initconnection command to controller */
अटल पूर्णांक tw_initconnection(TW_Device_Extension *tw_dev, पूर्णांक message_credits)
अणु
	अचिन्हित दीर्घ command_que_value;
	TW_Command  *command_packet;
	TW_Response_Queue response_queue;
	पूर्णांक request_id = 0;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_initconnection()\n");

	/* Initialize InitConnection command packet */
	अगर (tw_dev->command_packet_भव_address[request_id] == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_initconnection(): Bad command packet virtual address.\n");
		वापस 1;
	पूर्ण

	command_packet = (TW_Command *)tw_dev->command_packet_भव_address[request_id];
	स_रखो(command_packet, 0, माप(TW_Sector));
	command_packet->opcode__sgloffset = TW_OPSGL_IN(0, TW_OP_INIT_CONNECTION);
	command_packet->size = TW_INIT_COMMAND_PACKET_SIZE;
	command_packet->request_id = request_id;
	command_packet->status = 0x0;
	command_packet->flags = 0x0;
	command_packet->byte6.message_credits = message_credits; 
	command_packet->byte8.init_connection.response_queue_poपूर्णांकer = 0x0;
	command_que_value = tw_dev->command_packet_physical_address[request_id];

	अगर (command_que_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_initconnection(): Bad command packet physical address.\n");
		वापस 1;
	पूर्ण

	/* Send command packet to the board */
	outl(command_que_value, TW_COMMAND_QUEUE_REG_ADDR(tw_dev));

	/* Poll क्रम completion */
	अगर (tw_poll_status_gone(tw_dev, TW_STATUS_RESPONSE_QUEUE_EMPTY, 30) == 0) अणु
		response_queue.value = inl(TW_RESPONSE_QUEUE_REG_ADDR(tw_dev));
		request_id = TW_RESID_OUT(response_queue.response_id);

		अगर (request_id != 0) अणु
			/* unexpected request id */
			prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_initconnection(): Unexpected request id.\n");
			वापस 1;
		पूर्ण
		अगर (command_packet->status != 0) अणु
			/* bad response */
			tw_decode_sense(tw_dev, request_id, 0);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण /* End tw_initconnection() */

/* Set a value in the features table */
अटल पूर्णांक tw_setfeature(TW_Device_Extension *tw_dev, पूर्णांक parm, पूर्णांक param_size,
			 अचिन्हित अक्षर *val)
अणु
	TW_Param *param;
	TW_Command  *command_packet;
	TW_Response_Queue response_queue;
	पूर्णांक request_id = 0;
	अचिन्हित दीर्घ command_que_value;
	अचिन्हित दीर्घ param_value;

	/* Initialize SetParam command packet */
	अगर (tw_dev->command_packet_भव_address[request_id] == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_setfeature(): Bad command packet virtual address.\n");
		वापस 1;
	पूर्ण
	command_packet = (TW_Command *)tw_dev->command_packet_भव_address[request_id];
	स_रखो(command_packet, 0, माप(TW_Sector));
	param = (TW_Param *)tw_dev->alignment_भव_address[request_id];

	command_packet->opcode__sgloffset = TW_OPSGL_IN(2, TW_OP_SET_PARAM);
	param->table_id = 0x404;  /* Features table */
	param->parameter_id = parm;
	param->parameter_size_bytes = param_size;
	स_नकल(param->data, val, param_size);

	param_value = tw_dev->alignment_physical_address[request_id];
	अगर (param_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_setfeature(): Bad alignment physical address.\n");
		tw_dev->state[request_id] = TW_S_COMPLETED;
		tw_state_request_finish(tw_dev, request_id);
		tw_dev->srb[request_id]->result = (DID_OK << 16);
		tw_dev->srb[request_id]->scsi_करोne(tw_dev->srb[request_id]);
	पूर्ण
	command_packet->byte8.param.sgl[0].address = param_value;
	command_packet->byte8.param.sgl[0].length = माप(TW_Sector);

	command_packet->size = 4;
	command_packet->request_id = request_id;
	command_packet->byte6.parameter_count = 1;

	command_que_value = tw_dev->command_packet_physical_address[request_id];
	अगर (command_que_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_setfeature(): Bad command packet physical address.\n");
		वापस 1;
	पूर्ण

	/* Send command packet to the board */
	outl(command_que_value, TW_COMMAND_QUEUE_REG_ADDR(tw_dev));

	/* Poll क्रम completion */
	अगर (tw_poll_status_gone(tw_dev, TW_STATUS_RESPONSE_QUEUE_EMPTY, 30) == 0) अणु
		response_queue.value = inl(TW_RESPONSE_QUEUE_REG_ADDR(tw_dev));
		request_id = TW_RESID_OUT(response_queue.response_id);

		अगर (request_id != 0) अणु
			/* unexpected request id */
			prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_setfeature(): Unexpected request id.\n");
			वापस 1;
		पूर्ण
		अगर (command_packet->status != 0) अणु
			/* bad response */
			tw_decode_sense(tw_dev, request_id, 0);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण /* End tw_setfeature() */

/* This function will reset a controller */
अटल पूर्णांक tw_reset_sequence(TW_Device_Extension *tw_dev)
अणु
	पूर्णांक error = 0;
	पूर्णांक tries = 0;
	अचिन्हित अक्षर c = 1;

	/* Reset the board */
	जबतक (tries < TW_MAX_RESET_TRIES) अणु
		TW_SOFT_RESET(tw_dev);

		error = tw_aen_drain_queue(tw_dev);
		अगर (error) अणु
			prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: AEN drain failed, retrying.\n", tw_dev->host->host_no);
			tries++;
			जारी;
		पूर्ण

		/* Check क्रम controller errors */
		अगर (tw_check_errors(tw_dev)) अणु
			prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Controller errors found, retrying.\n", tw_dev->host->host_no);
			tries++;
			जारी;
		पूर्ण

		/* Now the controller is in a good state */
		अवरोध;
	पूर्ण

	अगर (tries >= TW_MAX_RESET_TRIES) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Controller errors, card not responding, check all cabling.\n", tw_dev->host->host_no);
		वापस 1;
	पूर्ण

	error = tw_initconnection(tw_dev, TW_INIT_MESSAGE_CREDITS);
	अगर (error) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Connection initialization failed.\n", tw_dev->host->host_no);
		वापस 1;
	पूर्ण

	error = tw_setfeature(tw_dev, 2, 1, &c);
	अगर (error) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: Unable to set features for card, probable old firmware or card.\n");
	पूर्ण

	वापस 0;
पूर्ण /* End tw_reset_sequence() */

/* This function will initialize the fields of a device extension */
अटल पूर्णांक tw_initialize_device_extension(TW_Device_Extension *tw_dev)
अणु
	पूर्णांक i, error=0;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_initialize_device_extension()\n");

	/* Initialize command packet buffers */
	error = tw_allocate_memory(tw_dev, माप(TW_Command), 0);
	अगर (error) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: Command packet memory allocation failed.\n");
		वापस 1;
	पूर्ण

	/* Initialize generic buffer */
	error = tw_allocate_memory(tw_dev, माप(TW_Sector), 1);
	अगर (error) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: Generic memory allocation failed.\n");
		वापस 1;
	पूर्ण

	क्रम (i=0;i<TW_Q_LENGTH;i++) अणु
		tw_dev->मुक्त_queue[i] = i;
		tw_dev->state[i] = TW_S_INITIAL;
	पूर्ण

	tw_dev->pending_head = TW_Q_START;
	tw_dev->pending_tail = TW_Q_START;
	tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;

	mutex_init(&tw_dev->ioctl_lock);
	init_रुकोqueue_head(&tw_dev->ioctl_wqueue);

	वापस 0;
पूर्ण /* End tw_initialize_device_extension() */

/* This function will reset a device extension */
अटल पूर्णांक tw_reset_device_extension(TW_Device_Extension *tw_dev)
अणु
	पूर्णांक i = 0;
	काष्ठा scsi_cmnd *srb;
	अचिन्हित दीर्घ flags = 0;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_reset_device_extension()\n");

	set_bit(TW_IN_RESET, &tw_dev->flags);
	TW_DISABLE_INTERRUPTS(tw_dev);
	TW_MASK_COMMAND_INTERRUPT(tw_dev);
	spin_lock_irqsave(tw_dev->host->host_lock, flags);

	/* Abort all requests that are in progress */
	क्रम (i=0;i<TW_Q_LENGTH;i++) अणु
		अगर ((tw_dev->state[i] != TW_S_FINISHED) &&
		    (tw_dev->state[i] != TW_S_INITIAL) &&
		    (tw_dev->state[i] != TW_S_COMPLETED)) अणु
			srb = tw_dev->srb[i];
			अगर (srb != शून्य) अणु
				srb->result = (DID_RESET << 16);
				scsi_dma_unmap(srb);
				srb->scsi_करोne(srb);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Reset queues and counts */
	क्रम (i=0;i<TW_Q_LENGTH;i++) अणु
		tw_dev->मुक्त_queue[i] = i;
		tw_dev->state[i] = TW_S_INITIAL;
	पूर्ण
	tw_dev->मुक्त_head = TW_Q_START;
	tw_dev->मुक्त_tail = TW_Q_START;
	tw_dev->posted_request_count = 0;
	tw_dev->pending_request_count = 0;
	tw_dev->pending_head = TW_Q_START;
	tw_dev->pending_tail = TW_Q_START;
	tw_dev->reset_prपूर्णांक = 0;

	spin_unlock_irqrestore(tw_dev->host->host_lock, flags);

	अगर (tw_reset_sequence(tw_dev)) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Reset sequence failed.\n", tw_dev->host->host_no);
		वापस 1;
	पूर्ण

	TW_ENABLE_AND_CLEAR_INTERRUPTS(tw_dev);
	clear_bit(TW_IN_RESET, &tw_dev->flags);
	tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;

	वापस 0;
पूर्ण /* End tw_reset_device_extension() */

/* This funciton वापसs unit geometry in cylinders/heads/sectors */
अटल पूर्णांक tw_scsi_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
			     sector_t capacity, पूर्णांक geom[])
अणु
	पूर्णांक heads, sectors, cylinders;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsi_biosparam()\n");

	heads = 64;
	sectors = 32;
	cylinders = sector_भाग(capacity, heads * sectors);

	अगर (capacity >= 0x200000) अणु
		heads = 255;
		sectors = 63;
		cylinders = sector_भाग(capacity, heads * sectors);
	पूर्ण

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsi_biosparam(): heads = %d, sectors = %d, cylinders = %d\n", heads, sectors, cylinders);
	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = cylinders;

	वापस 0;
पूर्ण /* End tw_scsi_biosparam() */

/* This is the new scsi eh reset function */
अटल पूर्णांक tw_scsi_eh_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	TW_Device_Extension *tw_dev=शून्य;
	पूर्णांक retval = FAILED;

	tw_dev = (TW_Device_Extension *)SCpnt->device->host->hostdata;

	tw_dev->num_resets++;

	sdev_prपूर्णांकk(KERN_WARNING, SCpnt->device,
		"WARNING: Command (0x%x) timed out, resetting card.\n",
		SCpnt->cmnd[0]);

	/* Make sure we are not issuing an ioctl or resetting from ioctl */
	mutex_lock(&tw_dev->ioctl_lock);

	/* Now reset the card and some of the device extension data */
	अगर (tw_reset_device_extension(tw_dev)) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Reset failed.\n", tw_dev->host->host_no);
		जाओ out;
	पूर्ण

	retval = SUCCESS;
out:
	mutex_unlock(&tw_dev->ioctl_lock);
	वापस retval;
पूर्ण /* End tw_scsi_eh_reset() */

/* This function handles scsi inquiry commands */
अटल पूर्णांक tw_scsiop_inquiry(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	TW_Param *param;
	TW_Command *command_packet;
	अचिन्हित दीर्घ command_que_value;
	अचिन्हित दीर्घ param_value;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_inquiry()\n");

	/* Initialize command packet */
	command_packet = (TW_Command *)tw_dev->command_packet_भव_address[request_id];
	अगर (command_packet == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_inquiry(): Bad command packet virtual address.\n");
		वापस 1;
	पूर्ण
	स_रखो(command_packet, 0, माप(TW_Sector));
	command_packet->opcode__sgloffset = TW_OPSGL_IN(2, TW_OP_GET_PARAM);
	command_packet->size = 4;
	command_packet->request_id = request_id;
	command_packet->status = 0;
	command_packet->flags = 0;
	command_packet->byte6.parameter_count = 1;

	/* Now setup the param */
	अगर (tw_dev->alignment_भव_address[request_id] == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_inquiry(): Bad alignment virtual address.\n");
		वापस 1;
	पूर्ण
	param = (TW_Param *)tw_dev->alignment_भव_address[request_id];
	स_रखो(param, 0, माप(TW_Sector));
	param->table_id = 3;	 /* unit summary table */
	param->parameter_id = 3; /* unitsstatus parameter */
	param->parameter_size_bytes = TW_MAX_UNITS;
	param_value = tw_dev->alignment_physical_address[request_id];
	अगर (param_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_inquiry(): Bad alignment physical address.\n");
		वापस 1;
	पूर्ण

	command_packet->byte8.param.sgl[0].address = param_value;
	command_packet->byte8.param.sgl[0].length = माप(TW_Sector);
	command_que_value = tw_dev->command_packet_physical_address[request_id];
	अगर (command_que_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_inquiry(): Bad command packet physical address.\n");
		वापस 1;
	पूर्ण

	/* Now try to post the command packet */
	tw_post_command_packet(tw_dev, request_id);

	वापस 0;
पूर्ण /* End tw_scsiop_inquiry() */

अटल व्योम tw_transfer_पूर्णांकernal(TW_Device_Extension *tw_dev, पूर्णांक request_id,
				 व्योम *data, अचिन्हित पूर्णांक len)
अणु
	scsi_sg_copy_from_buffer(tw_dev->srb[request_id], data, len);
पूर्ण

/* This function is called by the isr to complete an inquiry command */
अटल पूर्णांक tw_scsiop_inquiry_complete(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	अचिन्हित अक्षर *is_unit_present;
	अचिन्हित अक्षर request_buffer[36];
	TW_Param *param;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_inquiry_complete()\n");

	स_रखो(request_buffer, 0, माप(request_buffer));
	request_buffer[0] = TYPE_DISK; /* Peripheral device type */
	request_buffer[1] = 0;	       /* Device type modअगरier */
	request_buffer[2] = 0;	       /* No ansi/iso compliance */
	request_buffer[4] = 31;	       /* Additional length */
	स_नकल(&request_buffer[8], "3ware   ", 8);	 /* Venकरोr ID */
	प्र_लिखो(&request_buffer[16], "Logical Disk %-2d ", tw_dev->srb[request_id]->device->id);
	स_नकल(&request_buffer[32], TW_DRIVER_VERSION, 3);
	tw_transfer_पूर्णांकernal(tw_dev, request_id, request_buffer,
			     माप(request_buffer));

	param = (TW_Param *)tw_dev->alignment_भव_address[request_id];
	अगर (param == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_inquiry_complete(): Bad alignment virtual address.\n");
		वापस 1;
	पूर्ण
	is_unit_present = &(param->data[0]);

	अगर (is_unit_present[tw_dev->srb[request_id]->device->id] & TW_UNIT_ONLINE) अणु
		tw_dev->is_unit_present[tw_dev->srb[request_id]->device->id] = 1;
	पूर्ण अन्यथा अणु
		tw_dev->is_unit_present[tw_dev->srb[request_id]->device->id] = 0;
		tw_dev->srb[request_id]->result = (DID_BAD_TARGET << 16);
		वापस TW_ISR_DONT_RESULT;
	पूर्ण

	वापस 0;
पूर्ण /* End tw_scsiop_inquiry_complete() */

/* This function handles scsi mode_sense commands */
अटल पूर्णांक tw_scsiop_mode_sense(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	TW_Param *param;
	TW_Command *command_packet;
	अचिन्हित दीर्घ command_que_value;
	अचिन्हित दीर्घ param_value;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_mode_sense()\n");

	/* Only page control = 0, page code = 0x8 (cache page) supported */
	अगर (tw_dev->srb[request_id]->cmnd[2] != 0x8) अणु
		tw_dev->state[request_id] = TW_S_COMPLETED;
		tw_state_request_finish(tw_dev, request_id);
		tw_dev->srb[request_id]->result = (DID_OK << 16);
		tw_dev->srb[request_id]->scsi_करोne(tw_dev->srb[request_id]);
		वापस 0;
	पूर्ण

	/* Now पढ़ो firmware cache setting क्रम this unit */
	command_packet = (TW_Command *)tw_dev->command_packet_भव_address[request_id];
	अगर (command_packet == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_mode_sense(): Bad command packet virtual address.\n");
		वापस 1;
	पूर्ण

	/* Setup the command packet */
	स_रखो(command_packet, 0, माप(TW_Sector));
	command_packet->opcode__sgloffset = TW_OPSGL_IN(2, TW_OP_GET_PARAM);
	command_packet->size = 4;
	command_packet->request_id = request_id;
	command_packet->status = 0;
	command_packet->flags = 0;
	command_packet->byte6.parameter_count = 1;

	/* Setup the param */
	अगर (tw_dev->alignment_भव_address[request_id] == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_mode_sense(): Bad alignment virtual address.\n");
		वापस 1;
	पूर्ण

	param = (TW_Param *)tw_dev->alignment_भव_address[request_id];
	स_रखो(param, 0, माप(TW_Sector));
	param->table_id = TW_UNIT_INFORMATION_TABLE_BASE + tw_dev->srb[request_id]->device->id;
	param->parameter_id = 7; /* unit flags */
	param->parameter_size_bytes = 1;
	param_value = tw_dev->alignment_physical_address[request_id];
	अगर (param_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_mode_sense(): Bad alignment physical address.\n");
		वापस 1;
	पूर्ण

	command_packet->byte8.param.sgl[0].address = param_value;
	command_packet->byte8.param.sgl[0].length = माप(TW_Sector);
	command_que_value = tw_dev->command_packet_physical_address[request_id];
	अगर (command_que_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_mode_sense(): Bad command packet physical address.\n");
		वापस 1;
	पूर्ण

	/* Now try to post the command packet */
	tw_post_command_packet(tw_dev, request_id);

	वापस 0;
पूर्ण /* End tw_scsiop_mode_sense() */

/* This function is called by the isr to complete a mode sense command */
अटल पूर्णांक tw_scsiop_mode_sense_complete(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	TW_Param *param;
	अचिन्हित अक्षर *flags;
	अचिन्हित अक्षर request_buffer[8];

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_mode_sense_complete()\n");

	param = (TW_Param *)tw_dev->alignment_भव_address[request_id];
	अगर (param == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_mode_sense_complete(): Bad alignment virtual address.\n");
		वापस 1;
	पूर्ण
	flags = (अक्षर *)&(param->data[0]);
	स_रखो(request_buffer, 0, माप(request_buffer));

	request_buffer[0] = 0xf;	/* mode data length */
	request_buffer[1] = 0;		/* शेष medium type */
	request_buffer[2] = 0x10;	/* dpo/fua support on */
	request_buffer[3] = 0;		/* no block descriptors */
	request_buffer[4] = 0x8;	/* caching page */
	request_buffer[5] = 0xa;	/* page length */
	अगर (*flags & 0x1)
		request_buffer[6] = 0x5;	/* WCE on, RCD on */
	अन्यथा
		request_buffer[6] = 0x1;	/* WCE off, RCD on */
	tw_transfer_पूर्णांकernal(tw_dev, request_id, request_buffer,
			     माप(request_buffer));

	वापस 0;
पूर्ण /* End tw_scsiop_mode_sense_complete() */

/* This function handles scsi पढ़ो_capacity commands */
अटल पूर्णांक tw_scsiop_पढ़ो_capacity(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	TW_Param *param;
	TW_Command *command_packet;
	अचिन्हित दीर्घ command_que_value;
	अचिन्हित दीर्घ param_value;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_read_capacity()\n");

	/* Initialize command packet */
	command_packet = (TW_Command *)tw_dev->command_packet_भव_address[request_id];

	अगर (command_packet == शून्य) अणु
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_read_capacity(): Bad command packet virtual address.\n");
		वापस 1;
	पूर्ण
	स_रखो(command_packet, 0, माप(TW_Sector));
	command_packet->opcode__sgloffset = TW_OPSGL_IN(2, TW_OP_GET_PARAM);
	command_packet->size = 4;
	command_packet->request_id = request_id;
	command_packet->unit__hostid = TW_UNITHOST_IN(0, tw_dev->srb[request_id]->device->id);
	command_packet->status = 0;
	command_packet->flags = 0;
	command_packet->byte6.block_count = 1;

	/* Now setup the param */
	अगर (tw_dev->alignment_भव_address[request_id] == शून्य) अणु
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_read_capacity(): Bad alignment virtual address.\n");
		वापस 1;
	पूर्ण
	param = (TW_Param *)tw_dev->alignment_भव_address[request_id];
	स_रखो(param, 0, माप(TW_Sector));
	param->table_id = TW_UNIT_INFORMATION_TABLE_BASE +
		tw_dev->srb[request_id]->device->id;
	param->parameter_id = 4;	/* unitcapacity parameter */
	param->parameter_size_bytes = 4;
	param_value = tw_dev->alignment_physical_address[request_id];
	अगर (param_value == 0) अणु
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_read_capacity(): Bad alignment physical address.\n");
		वापस 1;
	पूर्ण

	command_packet->byte8.param.sgl[0].address = param_value;
	command_packet->byte8.param.sgl[0].length = माप(TW_Sector);
	command_que_value = tw_dev->command_packet_physical_address[request_id];
	अगर (command_que_value == 0) अणु
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_read_capacity(): Bad command packet physical address.\n");
		वापस 1;
	पूर्ण

	/* Now try to post the command to the board */
	tw_post_command_packet(tw_dev, request_id);

	वापस 0;
पूर्ण /* End tw_scsiop_पढ़ो_capacity() */

/* This function is called by the isr to complete a पढ़ोcapacity command */
अटल पूर्णांक tw_scsiop_पढ़ो_capacity_complete(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	अचिन्हित अक्षर *param_data;
	u32 capacity;
	अक्षर buff[8];
	TW_Param *param;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_read_capacity_complete()\n");

	स_रखो(buff, 0, माप(buff));
	param = (TW_Param *)tw_dev->alignment_भव_address[request_id];
	अगर (param == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_read_capacity_complete(): Bad alignment virtual address.\n");
		वापस 1;
	पूर्ण
	param_data = &(param->data[0]);

	capacity = (param_data[3] << 24) | (param_data[2] << 16) |
		   (param_data[1] << 8) | param_data[0];

	/* Subtract one sector to fix get last sector ioctl */
	capacity -= 1;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_read_capacity_complete(): Capacity = 0x%x.\n", capacity);

	/* Number of LBA's */
	buff[0] = (capacity >> 24);
	buff[1] = (capacity >> 16) & 0xff;
	buff[2] = (capacity >> 8) & 0xff;
	buff[3] = capacity & 0xff;

	/* Block size in bytes (512) */
	buff[4] = (TW_BLOCK_SIZE >> 24);
	buff[5] = (TW_BLOCK_SIZE >> 16) & 0xff;
	buff[6] = (TW_BLOCK_SIZE >> 8) & 0xff;
	buff[7] = TW_BLOCK_SIZE & 0xff;

	tw_transfer_पूर्णांकernal(tw_dev, request_id, buff, माप(buff));

	वापस 0;
पूर्ण /* End tw_scsiop_पढ़ो_capacity_complete() */

/* This function handles scsi पढ़ो or ग_लिखो commands */
अटल पूर्णांक tw_scsiop_पढ़ो_ग_लिखो(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	TW_Command *command_packet;
	अचिन्हित दीर्घ command_que_value;
	u32 lba = 0x0, num_sectors = 0x0;
	पूर्णांक i, use_sg;
	काष्ठा scsi_cmnd *srb;
	काष्ठा scatterlist *sglist, *sg;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_read_write()\n");

	srb = tw_dev->srb[request_id];

	sglist = scsi_sglist(srb);
	अगर (!sglist) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_read_write(): Request buffer NULL.\n");
		वापस 1;
	पूर्ण

	/* Initialize command packet */
	command_packet = (TW_Command *)tw_dev->command_packet_भव_address[request_id];
	अगर (command_packet == शून्य) अणु
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_read_write(): Bad command packet virtual address.\n");
		वापस 1;
	पूर्ण

	अगर (srb->cmnd[0] == READ_6 || srb->cmnd[0] == READ_10) अणु
		command_packet->opcode__sgloffset = TW_OPSGL_IN(3, TW_OP_READ);
	पूर्ण अन्यथा अणु
		command_packet->opcode__sgloffset = TW_OPSGL_IN(3, TW_OP_WRITE);
	पूर्ण

	command_packet->size = 3;
	command_packet->request_id = request_id;
	command_packet->unit__hostid = TW_UNITHOST_IN(0, srb->device->id);
	command_packet->status = 0;
	command_packet->flags = 0;

	अगर (srb->cmnd[0] == WRITE_10) अणु
		अगर ((srb->cmnd[1] & 0x8) || (srb->cmnd[1] & 0x10))
			command_packet->flags = 1;
	पूर्ण

	अगर (srb->cmnd[0] == READ_6 || srb->cmnd[0] == WRITE_6) अणु
		lba = ((u32)srb->cmnd[1] << 16) | ((u32)srb->cmnd[2] << 8) | (u32)srb->cmnd[3];
		num_sectors = (u32)srb->cmnd[4];
	पूर्ण अन्यथा अणु
		lba = ((u32)srb->cmnd[2] << 24) | ((u32)srb->cmnd[3] << 16) | ((u32)srb->cmnd[4] << 8) | (u32)srb->cmnd[5];
		num_sectors = (u32)srb->cmnd[8] | ((u32)srb->cmnd[7] << 8);
	पूर्ण

	/* Update sector statistic */
	tw_dev->sector_count = num_sectors;
	अगर (tw_dev->sector_count > tw_dev->max_sector_count)
		tw_dev->max_sector_count = tw_dev->sector_count;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_read_write(): lba = 0x%x num_sectors = 0x%x\n", lba, num_sectors);
	command_packet->byte8.io.lba = lba;
	command_packet->byte6.block_count = num_sectors;

	use_sg = scsi_dma_map(srb);
	अगर (use_sg <= 0)
		वापस 1;

	scsi_क्रम_each_sg(tw_dev->srb[request_id], sg, use_sg, i) अणु
		command_packet->byte8.io.sgl[i].address = sg_dma_address(sg);
		command_packet->byte8.io.sgl[i].length = sg_dma_len(sg);
		command_packet->size+=2;
	पूर्ण

	/* Update SG statistics */
	tw_dev->sgl_entries = scsi_sg_count(tw_dev->srb[request_id]);
	अगर (tw_dev->sgl_entries > tw_dev->max_sgl_entries)
		tw_dev->max_sgl_entries = tw_dev->sgl_entries;

	command_que_value = tw_dev->command_packet_physical_address[request_id];
	अगर (command_que_value == 0) अणु
		dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_read_write(): Bad command packet physical address.\n");
		वापस 1;
	पूर्ण

	/* Now try to post the command to the board */
	tw_post_command_packet(tw_dev, request_id);

	वापस 0;
पूर्ण /* End tw_scsiop_पढ़ो_ग_लिखो() */

/* This function will handle the request sense scsi command */
अटल पूर्णांक tw_scsiop_request_sense(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	अक्षर request_buffer[18];

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_request_sense()\n");

	स_रखो(request_buffer, 0, माप(request_buffer));
	request_buffer[0] = 0x70; /* Immediate fixed क्रमmat */
	request_buffer[7] = 10;	/* minimum size per SPC: 18 bytes */
	/* leave all other fields zero, giving effectively NO_SENSE वापस */
	tw_transfer_पूर्णांकernal(tw_dev, request_id, request_buffer,
			     माप(request_buffer));

	tw_dev->state[request_id] = TW_S_COMPLETED;
	tw_state_request_finish(tw_dev, request_id);

	/* If we got a request_sense, we probably want a reset, वापस error */
	tw_dev->srb[request_id]->result = (DID_ERROR << 16);
	tw_dev->srb[request_id]->scsi_करोne(tw_dev->srb[request_id]);

	वापस 0;
पूर्ण /* End tw_scsiop_request_sense() */

/* This function will handle synchronize cache scsi command */
अटल पूर्णांक tw_scsiop_synchronize_cache(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	TW_Command *command_packet;
	अचिन्हित दीर्घ command_que_value;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_synchronize_cache()\n");

	/* Send firmware flush command क्रम this unit */
	command_packet = (TW_Command *)tw_dev->command_packet_भव_address[request_id];
	अगर (command_packet == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_synchronize_cache(): Bad command packet virtual address.\n");
		वापस 1;
	पूर्ण

	/* Setup the command packet */
	स_रखो(command_packet, 0, माप(TW_Sector));
	command_packet->opcode__sgloffset = TW_OPSGL_IN(0, TW_OP_FLUSH_CACHE);
	command_packet->size = 2;
	command_packet->request_id = request_id;
	command_packet->unit__hostid = TW_UNITHOST_IN(0, tw_dev->srb[request_id]->device->id);
	command_packet->status = 0;
	command_packet->flags = 0;
	command_packet->byte6.parameter_count = 1;
	command_que_value = tw_dev->command_packet_physical_address[request_id];
	अगर (command_que_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_synchronize_cache(): Bad command packet physical address.\n");
		वापस 1;
	पूर्ण

	/* Now try to post the command packet */
	tw_post_command_packet(tw_dev, request_id);

	वापस 0;
पूर्ण /* End tw_scsiop_synchronize_cache() */

/* This function will handle test unit पढ़ोy scsi command */
अटल पूर्णांक tw_scsiop_test_unit_पढ़ोy(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	TW_Param *param;
	TW_Command *command_packet;
	अचिन्हित दीर्घ command_que_value;
	अचिन्हित दीर्घ param_value;

	dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsiop_test_unit_ready()\n");

	/* Initialize command packet */
	command_packet = (TW_Command *)tw_dev->command_packet_भव_address[request_id];
	अगर (command_packet == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_test_unit_ready(): Bad command packet virtual address.\n");
		वापस 1;
	पूर्ण
	स_रखो(command_packet, 0, माप(TW_Sector));
	command_packet->opcode__sgloffset = TW_OPSGL_IN(2, TW_OP_GET_PARAM);
	command_packet->size = 4;
	command_packet->request_id = request_id;
	command_packet->status = 0;
	command_packet->flags = 0;
	command_packet->byte6.parameter_count = 1;

	/* Now setup the param */
	अगर (tw_dev->alignment_भव_address[request_id] == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_test_unit_ready(): Bad alignment virtual address.\n");
		वापस 1;
	पूर्ण
	param = (TW_Param *)tw_dev->alignment_भव_address[request_id];
	स_रखो(param, 0, माप(TW_Sector));
	param->table_id = 3;	 /* unit summary table */
	param->parameter_id = 3; /* unitsstatus parameter */
	param->parameter_size_bytes = TW_MAX_UNITS;
	param_value = tw_dev->alignment_physical_address[request_id];
	अगर (param_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_test_unit_ready(): Bad alignment physical address.\n");
		वापस 1;
	पूर्ण

	command_packet->byte8.param.sgl[0].address = param_value;
	command_packet->byte8.param.sgl[0].length = माप(TW_Sector);
	command_que_value = tw_dev->command_packet_physical_address[request_id];
	अगर (command_que_value == 0) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_test_unit_ready(): Bad command packet physical address.\n");
		वापस 1;
	पूर्ण

	/* Now try to post the command packet */
	tw_post_command_packet(tw_dev, request_id);

	वापस 0;
पूर्ण /* End tw_scsiop_test_unit_पढ़ोy() */

/* This function is called by the isr to complete a testunitपढ़ोy command */
अटल पूर्णांक tw_scsiop_test_unit_पढ़ोy_complete(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	अचिन्हित अक्षर *is_unit_present;
	TW_Param *param;

	dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_test_unit_ready_complete()\n");

	param = (TW_Param *)tw_dev->alignment_भव_address[request_id];
	अगर (param == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: tw_scsiop_test_unit_ready_complete(): Bad alignment virtual address.\n");
		वापस 1;
	पूर्ण
	is_unit_present = &(param->data[0]);

	अगर (is_unit_present[tw_dev->srb[request_id]->device->id] & TW_UNIT_ONLINE) अणु
		tw_dev->is_unit_present[tw_dev->srb[request_id]->device->id] = 1;
	पूर्ण अन्यथा अणु
		tw_dev->is_unit_present[tw_dev->srb[request_id]->device->id] = 0;
		tw_dev->srb[request_id]->result = (DID_BAD_TARGET << 16);
		वापस TW_ISR_DONT_RESULT;
	पूर्ण

	वापस 0;
पूर्ण /* End tw_scsiop_test_unit_पढ़ोy_complete() */

/* This is the मुख्य scsi queue function to handle scsi opcodes */
अटल पूर्णांक tw_scsi_queue_lck(काष्ठा scsi_cmnd *SCpnt, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	अचिन्हित अक्षर *command = SCpnt->cmnd;
	पूर्णांक request_id = 0;
	पूर्णांक retval = 1;
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)SCpnt->device->host->hostdata;

	/* If we are resetting due to समयd out ioctl, report as busy */
	अगर (test_bit(TW_IN_RESET, &tw_dev->flags))
		वापस SCSI_MLQUEUE_HOST_BUSY;

	/* Save करोne function पूर्णांकo काष्ठा scsi_cmnd */
	SCpnt->scsi_करोne = करोne;

	/* Queue the command and get a request id */
	tw_state_request_start(tw_dev, &request_id);

	/* Save the scsi command क्रम use by the ISR */
	tw_dev->srb[request_id] = SCpnt;

	चयन (*command) अणु
	हाल READ_10:
	हाल READ_6:
	हाल WRITE_10:
	हाल WRITE_6:
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsi_queue(): caught READ/WRITE.\n");
		retval = tw_scsiop_पढ़ो_ग_लिखो(tw_dev, request_id);
		अवरोध;
	हाल TEST_UNIT_READY:
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsi_queue(): caught TEST_UNIT_READY.\n");
		retval = tw_scsiop_test_unit_पढ़ोy(tw_dev, request_id);
		अवरोध;
	हाल INQUIRY:
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsi_queue(): caught INQUIRY.\n");
		retval = tw_scsiop_inquiry(tw_dev, request_id);
		अवरोध;
	हाल READ_CAPACITY:
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsi_queue(): caught READ_CAPACITY.\n");
		retval = tw_scsiop_पढ़ो_capacity(tw_dev, request_id);
		अवरोध;
	हाल REQUEST_SENSE:
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsi_queue(): caught REQUEST_SENSE.\n");
		retval = tw_scsiop_request_sense(tw_dev, request_id);
		अवरोध;
	हाल MODE_SENSE:
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsi_queue(): caught MODE_SENSE.\n");
		retval = tw_scsiop_mode_sense(tw_dev, request_id);
		अवरोध;
	हाल SYNCHRONIZE_CACHE:
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_scsi_queue(): caught SYNCHRONIZE_CACHE.\n");
		retval = tw_scsiop_synchronize_cache(tw_dev, request_id);
		अवरोध;
	हाल TW_IOCTL:
		prपूर्णांकk(KERN_WARNING "3w-xxxx: SCSI_IOCTL_SEND_COMMAND deprecated, please update your 3ware tools.\n");
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_NOTICE "3w-xxxx: scsi%d: Unknown scsi opcode: 0x%x\n", tw_dev->host->host_no, *command);
		tw_dev->state[request_id] = TW_S_COMPLETED;
		tw_state_request_finish(tw_dev, request_id);
		scsi_build_sense_buffer(1, SCpnt->sense_buffer, ILLEGAL_REQUEST, 0x20, 0);
		करोne(SCpnt);
		retval = 0;
	पूर्ण
	अगर (retval) अणु
		tw_dev->state[request_id] = TW_S_COMPLETED;
		tw_state_request_finish(tw_dev, request_id);
		SCpnt->result = (DID_ERROR << 16);
		करोne(SCpnt);
		retval = 0;
	पूर्ण
	वापस retval;
पूर्ण /* End tw_scsi_queue() */

अटल DEF_SCSI_QCMD(tw_scsi_queue)

/* This function is the पूर्णांकerrupt service routine */
अटल irqवापस_t tw_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	पूर्णांक request_id;
	u32 status_reg_value;
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)dev_instance;
	TW_Response_Queue response_que;
	पूर्णांक error = 0, retval = 0;
	TW_Command *command_packet;
	पूर्णांक handled = 0;

	/* Get the host lock क्रम io completions */
	spin_lock(tw_dev->host->host_lock);

	/* Read the रेजिस्टरs */
	status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));

	/* Check अगर this is our पूर्णांकerrupt, otherwise bail */
	अगर (!(status_reg_value & TW_STATUS_VALID_INTERRUPT))
		जाओ tw_पूर्णांकerrupt_bail;

	handled = 1;

	/* If we are resetting, bail */
	अगर (test_bit(TW_IN_RESET, &tw_dev->flags))
		जाओ tw_पूर्णांकerrupt_bail;

	/* Check controller क्रम errors */
	अगर (tw_check_bits(status_reg_value)) अणु
		dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_interrupt(): Unexpected bits.\n");
		अगर (tw_decode_bits(tw_dev, status_reg_value, 1)) अणु
			TW_CLEAR_ALL_INTERRUPTS(tw_dev);
			जाओ tw_पूर्णांकerrupt_bail;
		पूर्ण
	पूर्ण

	/* Handle host पूर्णांकerrupt */
	अगर (status_reg_value & TW_STATUS_HOST_INTERRUPT) अणु
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_interrupt(): Received host interrupt.\n");
		TW_CLEAR_HOST_INTERRUPT(tw_dev);
	पूर्ण

	/* Handle attention पूर्णांकerrupt */
	अगर (status_reg_value & TW_STATUS_ATTENTION_INTERRUPT) अणु
		dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_interrupt(): Received attention interrupt.\n");
		TW_CLEAR_ATTENTION_INTERRUPT(tw_dev);
		tw_state_request_start(tw_dev, &request_id);
		error = tw_aen_पढ़ो_queue(tw_dev, request_id);
		अगर (error) अणु
			prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Error reading aen queue.\n", tw_dev->host->host_no);
			tw_dev->state[request_id] = TW_S_COMPLETED;
			tw_state_request_finish(tw_dev, request_id);
		पूर्ण
	पूर्ण

	/* Handle command पूर्णांकerrupt */
	अगर (status_reg_value & TW_STATUS_COMMAND_INTERRUPT) अणु
		/* Drain as many pending commands as we can */
		जबतक (tw_dev->pending_request_count > 0) अणु
			request_id = tw_dev->pending_queue[tw_dev->pending_head];
			अगर (tw_dev->state[request_id] != TW_S_PENDING) अणु
				prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Found request id that wasn't pending.\n", tw_dev->host->host_no);
				अवरोध;
			पूर्ण
			अगर (tw_post_command_packet(tw_dev, request_id)==0) अणु
				अगर (tw_dev->pending_head == TW_Q_LENGTH-1) अणु
					tw_dev->pending_head = TW_Q_START;
				पूर्ण अन्यथा अणु
					tw_dev->pending_head = tw_dev->pending_head + 1;
				पूर्ण
				tw_dev->pending_request_count--;
			पूर्ण अन्यथा अणु
				/* If we get here, we will जारी re-posting on the next command पूर्णांकerrupt */
				अवरोध;
			पूर्ण
		पूर्ण
		/* If there are no more pending requests, we mask command पूर्णांकerrupt */
		अगर (tw_dev->pending_request_count == 0)
			TW_MASK_COMMAND_INTERRUPT(tw_dev);
	पूर्ण

	/* Handle response पूर्णांकerrupt */
	अगर (status_reg_value & TW_STATUS_RESPONSE_INTERRUPT) अणु
		/* Drain the response queue from the board */
		जबतक ((status_reg_value & TW_STATUS_RESPONSE_QUEUE_EMPTY) == 0) अणु
			/* Read response queue रेजिस्टर */
			response_que.value = inl(TW_RESPONSE_QUEUE_REG_ADDR(tw_dev));
			request_id = TW_RESID_OUT(response_que.response_id);
			command_packet = (TW_Command *)tw_dev->command_packet_भव_address[request_id];
			error = 0;

			/* Check क्रम bad response */
			अगर (command_packet->status != 0) अणु
				/* If पूर्णांकernal command, करोn't error, don't fill sense */
				अगर (tw_dev->srb[request_id] == शून्य) अणु
					tw_decode_sense(tw_dev, request_id, 0);
				पूर्ण अन्यथा अणु
					error = tw_decode_sense(tw_dev, request_id, 1);
				पूर्ण
			पूर्ण

			/* Check क्रम correct state */
			अगर (tw_dev->state[request_id] != TW_S_POSTED) अणु
				अगर (tw_dev->srb[request_id] != शून्य) अणु
					prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Received a request id that wasn't posted.\n", tw_dev->host->host_no);
					error = 1;
				पूर्ण
			पूर्ण

			dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_interrupt(): Response queue request id: %d.\n", request_id);

			/* Check क्रम पूर्णांकernal command completion */
			अगर (tw_dev->srb[request_id] == शून्य) अणु
				dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_interrupt(): Found internally posted command.\n");
				/* Check क्रम chrdev ioctl completion */
				अगर (request_id != tw_dev->chrdev_request_id) अणु
					retval = tw_aen_complete(tw_dev, request_id);
					अगर (retval) अणु
						prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Error completing aen.\n", tw_dev->host->host_no);
					पूर्ण
				पूर्ण अन्यथा अणु
					tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;
					wake_up(&tw_dev->ioctl_wqueue);
				पूर्ण
			पूर्ण अन्यथा अणु
				चयन (tw_dev->srb[request_id]->cmnd[0]) अणु
				हाल READ_10:
				हाल READ_6:
					dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_interrupt(): caught READ_10/READ_6\n");
					अवरोध;
				हाल WRITE_10:
				हाल WRITE_6:
					dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_interrupt(): caught WRITE_10/WRITE_6\n");
					अवरोध;
				हाल TEST_UNIT_READY:
					dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_interrupt(): caught TEST_UNIT_READY\n");
					error = tw_scsiop_test_unit_पढ़ोy_complete(tw_dev, request_id);
					अवरोध;
				हाल INQUIRY:
					dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_interrupt(): caught INQUIRY\n");
					error = tw_scsiop_inquiry_complete(tw_dev, request_id);
					अवरोध;
				हाल READ_CAPACITY:
					dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_interrupt(): caught READ_CAPACITY\n");
					error = tw_scsiop_पढ़ो_capacity_complete(tw_dev, request_id);
					अवरोध;
				हाल MODE_SENSE:
					dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_interrupt(): caught MODE_SENSE\n");
					error = tw_scsiop_mode_sense_complete(tw_dev, request_id);
					अवरोध;
				हाल SYNCHRONIZE_CACHE:
					dprपूर्णांकk(KERN_NOTICE "3w-xxxx: tw_interrupt(): caught SYNCHRONIZE_CACHE\n");
					अवरोध;
				शेष:
					prपूर्णांकk(KERN_WARNING "3w-xxxx: case slip in tw_interrupt()\n");
					error = 1;
				पूर्ण

				/* If no error command was a success */
				अगर (error == 0) अणु
					tw_dev->srb[request_id]->result = (DID_OK << 16);
				पूर्ण

				/* If error, command failed */
				अगर (error == 1) अणु
					/* Ask क्रम a host reset */
					tw_dev->srb[request_id]->result = (DID_OK << 16) | (CHECK_CONDITION << 1);
				पूर्ण

				/* Now complete the io */
				अगर ((error != TW_ISR_DONT_COMPLETE)) अणु
					scsi_dma_unmap(tw_dev->srb[request_id]);
					tw_dev->srb[request_id]->scsi_करोne(tw_dev->srb[request_id]);
					tw_dev->state[request_id] = TW_S_COMPLETED;
					tw_state_request_finish(tw_dev, request_id);
					tw_dev->posted_request_count--;
				पूर्ण
			पूर्ण

			/* Check क्रम valid status after each drain */
			status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));
			अगर (tw_check_bits(status_reg_value)) अणु
				dprपूर्णांकk(KERN_WARNING "3w-xxxx: tw_interrupt(): Unexpected bits.\n");
				अगर (tw_decode_bits(tw_dev, status_reg_value, 1)) अणु
					TW_CLEAR_ALL_INTERRUPTS(tw_dev);
					जाओ tw_पूर्णांकerrupt_bail;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

tw_पूर्णांकerrupt_bail:
	spin_unlock(tw_dev->host->host_lock);
	वापस IRQ_RETVAL(handled);
पूर्ण /* End tw_पूर्णांकerrupt() */

/* This function tells the controller to shut करोwn */
अटल व्योम __tw_shutकरोwn(TW_Device_Extension *tw_dev)
अणु
	/* Disable पूर्णांकerrupts */
	TW_DISABLE_INTERRUPTS(tw_dev);

	/* Free up the IRQ */
	मुक्त_irq(tw_dev->tw_pci_dev->irq, tw_dev);

	prपूर्णांकk(KERN_WARNING "3w-xxxx: Shutting down host %d.\n", tw_dev->host->host_no);

	/* Tell the card we are shutting करोwn */
	अगर (tw_initconnection(tw_dev, 1)) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: Connection shutdown failed.\n");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: Shutdown complete.\n");
	पूर्ण

	/* Clear all पूर्णांकerrupts just beक्रमe निकास */
	TW_ENABLE_AND_CLEAR_INTERRUPTS(tw_dev);
पूर्ण /* End __tw_shutकरोwn() */

/* Wrapper क्रम __tw_shutकरोwn */
अटल व्योम tw_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;

	__tw_shutकरोwn(tw_dev);
पूर्ण /* End tw_shutकरोwn() */

/* This function माला_लो called when a disk is coming online */
अटल पूर्णांक tw_slave_configure(काष्ठा scsi_device *sdev)
अणु
	/* Force 60 second समयout */
	blk_queue_rq_समयout(sdev->request_queue, 60 * HZ);

	वापस 0;
पूर्ण /* End tw_slave_configure() */

अटल काष्ठा scsi_host_ढाँचा driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "3ware Storage Controller",
	.queuecommand		= tw_scsi_queue,
	.eh_host_reset_handler	= tw_scsi_eh_reset,
	.bios_param		= tw_scsi_biosparam,
	.change_queue_depth	= scsi_change_queue_depth,
	.can_queue		= TW_Q_LENGTH-2,
	.slave_configure	= tw_slave_configure,
	.this_id		= -1,
	.sg_tablesize		= TW_MAX_SGL_LENGTH,
	.max_sectors		= TW_MAX_SECTORS,
	.cmd_per_lun		= TW_MAX_CMDS_PER_LUN,
	.shost_attrs		= tw_host_attrs,
	.emulated		= 1,
	.no_ग_लिखो_same		= 1,
पूर्ण;

/* This function will probe and initialize a card */
अटल पूर्णांक tw_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *dev_id)
अणु
	काष्ठा Scsi_Host *host = शून्य;
	TW_Device_Extension *tw_dev;
	पूर्णांक retval = -ENODEV;

	retval = pci_enable_device(pdev);
	अगर (retval) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: Failed to enable pci device.");
		जाओ out_disable_device;
	पूर्ण

	pci_set_master(pdev);

	retval = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (retval) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: Failed to set dma mask.");
		जाओ out_disable_device;
	पूर्ण

	host = scsi_host_alloc(&driver_ढाँचा, माप(TW_Device_Extension));
	अगर (!host) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: Failed to allocate memory for device extension.");
		retval = -ENOMEM;
		जाओ out_disable_device;
	पूर्ण
	tw_dev = (TW_Device_Extension *)host->hostdata;

	/* Save values to device extension */
	tw_dev->host = host;
	tw_dev->tw_pci_dev = pdev;

	अगर (tw_initialize_device_extension(tw_dev)) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: Failed to initialize device extension.");
		retval = -ENOMEM;
		जाओ out_मुक्त_device_extension;
	पूर्ण

	/* Request IO regions */
	retval = pci_request_regions(pdev, "3w-xxxx");
	अगर (retval) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: Failed to get mem region.");
		जाओ out_मुक्त_device_extension;
	पूर्ण

	/* Save base address */
	tw_dev->base_addr = pci_resource_start(pdev, 0);
	अगर (!tw_dev->base_addr) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: Failed to get io address.");
		retval = -ENOMEM;
		जाओ out_release_mem_region;
	पूर्ण

	/* Disable पूर्णांकerrupts on the card */
	TW_DISABLE_INTERRUPTS(tw_dev);

	/* Initialize the card */
	अगर (tw_reset_sequence(tw_dev))
		जाओ out_release_mem_region;

	/* Set host specअगरic parameters */
	host->max_id = TW_MAX_UNITS;
	host->max_cmd_len = TW_MAX_CDB_LEN;

	/* Luns and channels aren't supported by adapter */
	host->max_lun = 0;
	host->max_channel = 0;

	/* Register the card with the kernel SCSI layer */
	retval = scsi_add_host(host, &pdev->dev);
	अगर (retval) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi add host failed");
		जाओ out_release_mem_region;
	पूर्ण

	pci_set_drvdata(pdev, host);

	prपूर्णांकk(KERN_WARNING "3w-xxxx: scsi%d: Found a 3ware Storage Controller at 0x%x, IRQ: %d.\n", host->host_no, tw_dev->base_addr, pdev->irq);

	/* Now setup the पूर्णांकerrupt handler */
	retval = request_irq(pdev->irq, tw_पूर्णांकerrupt, IRQF_SHARED, "3w-xxxx", tw_dev);
	अगर (retval) अणु
		prपूर्णांकk(KERN_WARNING "3w-xxxx: Error requesting IRQ.");
		जाओ out_हटाओ_host;
	पूर्ण

	tw_device_extension_list[tw_device_extension_count] = tw_dev;
	tw_device_extension_count++;

	/* Re-enable पूर्णांकerrupts on the card */
	TW_ENABLE_AND_CLEAR_INTERRUPTS(tw_dev);

	/* Finally, scan the host */
	scsi_scan_host(host);

	अगर (twe_major == -1) अणु
		अगर ((twe_major = रेजिस्टर_chrdev (0, "twe", &tw_fops)) < 0)
			prपूर्णांकk(KERN_WARNING "3w-xxxx: Failed to register character device.");
	पूर्ण
	वापस 0;

out_हटाओ_host:
	scsi_हटाओ_host(host);
out_release_mem_region:
	pci_release_regions(pdev);
out_मुक्त_device_extension:
	tw_मुक्त_device_extension(tw_dev);
	scsi_host_put(host);
out_disable_device:
	pci_disable_device(pdev);

	वापस retval;
पूर्ण /* End tw_probe() */

/* This function is called to हटाओ a device */
अटल व्योम tw_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;

	scsi_हटाओ_host(tw_dev->host);

	/* Unरेजिस्टर अक्षरacter device */
	अगर (twe_major >= 0) अणु
		unरेजिस्टर_chrdev(twe_major, "twe");
		twe_major = -1;
	पूर्ण

	/* Shutकरोwn the card */
	__tw_shutकरोwn(tw_dev);

	/* Free up the mem region */
	pci_release_regions(pdev);

	/* Free up device extension resources */
	tw_मुक्त_device_extension(tw_dev);

	scsi_host_put(tw_dev->host);
	pci_disable_device(pdev);
	tw_device_extension_count--;
पूर्ण /* End tw_हटाओ() */

/* PCI Devices supported by this driver */
अटल काष्ठा pci_device_id tw_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_3WARE, PCI_DEVICE_ID_3WARE_1000,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु PCI_VENDOR_ID_3WARE, PCI_DEVICE_ID_3WARE_7000,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, tw_pci_tbl);

/* pci_driver initializer */
अटल काष्ठा pci_driver tw_driver = अणु
	.name		= "3w-xxxx",
	.id_table	= tw_pci_tbl,
	.probe		= tw_probe,
	.हटाओ		= tw_हटाओ,
	.shutकरोwn	= tw_shutकरोwn,
पूर्ण;

/* This function is called on driver initialization */
अटल पूर्णांक __init tw_init(व्योम)
अणु
	prपूर्णांकk(KERN_WARNING "3ware Storage Controller device driver for Linux v%s.\n", TW_DRIVER_VERSION);

	वापस pci_रेजिस्टर_driver(&tw_driver);
पूर्ण /* End tw_init() */

/* This function is called on driver निकास */
अटल व्योम __निकास tw_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&tw_driver);
पूर्ण /* End tw_निकास() */

module_init(tw_init);
module_निकास(tw_निकास);

