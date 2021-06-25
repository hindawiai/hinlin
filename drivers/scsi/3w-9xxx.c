<शैली गुरु>
/*
   3w-9xxx.c -- 3ware 9000 Storage Controller device driver क्रम Linux.

   Written By: Adam Radक्रमd <aradक्रमd@gmail.com>
   Modअगरications By: Tom Couch

   Copyright (C) 2004-2009 Applied Micro Circuits Corporation.
   Copyright (C) 2010 LSI Corporation.

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

   Note: This version of the driver करोes not contain a bundled firmware
         image.

   History
   -------
   2.26.02.000 - Driver cleanup क्रम kernel submission.
   2.26.02.001 - Replace schedule_समयout() calls with msleep().
   2.26.02.002 - Add support क्रम PAE mode.
                 Add lun support.
                 Fix twa_हटाओ() to मुक्त irq handler/unरेजिस्टर_chrdev()
                 beक्रमe shutting करोwn card.
                 Change to new 'change_queue_depth' api.
                 Fix 'handled=1' ISR usage, हटाओ bogus IRQ check.
                 Remove un-needed eh_पात handler.
                 Add support क्रम embedded firmware error strings.
   2.26.02.003 - Correctly handle single sgl's with use_sg=1.
   2.26.02.004 - Add support क्रम 9550SX controllers.
   2.26.02.005 - Fix use_sg == 0 mapping on प्रणालीs with 4GB or higher.
   2.26.02.006 - Fix 9550SX pchip reset समयout.
                 Add big endian support.
   2.26.02.007 - Disable local पूर्णांकerrupts during kmap/unmap_atomic().
   2.26.02.008 - Free irq handler in __twa_shutकरोwn().
                 Serialize reset code.
                 Add support क्रम 9650SE controllers.
   2.26.02.009 - Fix dma mask setting to fallback to 32-bit अगर 64-bit fails.
   2.26.02.010 - Add support क्रम 9690SA controllers.
   2.26.02.011 - Increase max AENs drained to 256.
                 Add MSI support and "use_msi" module parameter.
                 Fix bug in twa_get_param() on 4GB+.
                 Use pci_resource_len() क्रम ioremap().
   2.26.02.012 - Add घातer management support.
   2.26.02.013 - Fix bug in twa_load_sgl().
   2.26.02.014 - Force 60 second समयout शेष.
*/

#समावेश <linux/module.h>
#समावेश <linux/reboot.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/समय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश "3w-9xxx.h"

/* Globals */
#घोषणा TW_DRIVER_VERSION "2.26.02.014"
अटल DEFINE_MUTEX(twa_chrdev_mutex);
अटल TW_Device_Extension *twa_device_extension_list[TW_MAX_SLOT];
अटल अचिन्हित पूर्णांक twa_device_extension_count;
अटल पूर्णांक twa_major = -1;
बाह्य काष्ठा समयzone sys_tz;

/* Module parameters */
MODULE_AUTHOR ("LSI");
MODULE_DESCRIPTION ("3ware 9000 Storage Controller Linux Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(TW_DRIVER_VERSION);

अटल पूर्णांक use_msi = 0;
module_param(use_msi, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(use_msi, "Use Message Signaled Interrupts.  Default: 0");

/* Function prototypes */
अटल व्योम twa_aen_queue_event(TW_Device_Extension *tw_dev, TW_Command_Apache_Header *header);
अटल पूर्णांक twa_aen_पढ़ो_queue(TW_Device_Extension *tw_dev, पूर्णांक request_id);
अटल अक्षर *twa_aen_severity_lookup(अचिन्हित अक्षर severity_code);
अटल व्योम twa_aen_sync_समय(TW_Device_Extension *tw_dev, पूर्णांक request_id);
अटल दीर्घ twa_chrdev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
अटल पूर्णांक twa_chrdev_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक twa_fill_sense(TW_Device_Extension *tw_dev, पूर्णांक request_id, पूर्णांक copy_sense, पूर्णांक prपूर्णांक_host);
अटल व्योम twa_मुक्त_request_id(TW_Device_Extension *tw_dev,पूर्णांक request_id);
अटल व्योम twa_get_request_id(TW_Device_Extension *tw_dev, पूर्णांक *request_id);
अटल पूर्णांक twa_initconnection(TW_Device_Extension *tw_dev, पूर्णांक message_credits,
			      u32 set_features, अचिन्हित लघु current_fw_srl,
			      अचिन्हित लघु current_fw_arch_id,
			      अचिन्हित लघु current_fw_branch,
			      अचिन्हित लघु current_fw_build,
			      अचिन्हित लघु *fw_on_ctlr_srl,
			      अचिन्हित लघु *fw_on_ctlr_arch_id,
			      अचिन्हित लघु *fw_on_ctlr_branch,
			      अचिन्हित लघु *fw_on_ctlr_build,
			      u32 *init_connect_result);
अटल व्योम twa_load_sgl(TW_Device_Extension *tw_dev, TW_Command_Full *full_command_packet, पूर्णांक request_id, dma_addr_t dma_handle, पूर्णांक length);
अटल पूर्णांक twa_poll_response(TW_Device_Extension *tw_dev, पूर्णांक request_id, पूर्णांक seconds);
अटल पूर्णांक twa_poll_status_gone(TW_Device_Extension *tw_dev, u32 flag, पूर्णांक seconds);
अटल पूर्णांक twa_post_command_packet(TW_Device_Extension *tw_dev, पूर्णांक request_id, अक्षर पूर्णांकernal);
अटल पूर्णांक twa_reset_device_extension(TW_Device_Extension *tw_dev);
अटल पूर्णांक twa_reset_sequence(TW_Device_Extension *tw_dev, पूर्णांक soft_reset);
अटल पूर्णांक twa_scsiop_execute_scsi(TW_Device_Extension *tw_dev, पूर्णांक request_id,
				   अचिन्हित अक्षर *cdb, पूर्णांक use_sg,
				   TW_SG_Entry *sglistarg);
अटल व्योम twa_scsiop_execute_scsi_complete(TW_Device_Extension *tw_dev, पूर्णांक request_id);
अटल अक्षर *twa_string_lookup(twa_message_type *table, अचिन्हित पूर्णांक aen_code);

/* Functions */

/* Show some statistics about the card */
अटल sमाप_प्रकार twa_show_stats(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;
	अचिन्हित दीर्घ flags = 0;
	sमाप_प्रकार len;

	spin_lock_irqsave(tw_dev->host->host_lock, flags);
	len = snम_लिखो(buf, PAGE_SIZE, "3w-9xxx Driver version: %s\n"
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
पूर्ण /* End twa_show_stats() */

/* Create sysfs 'stats' entry */
अटल काष्ठा device_attribute twa_host_stats_attr = अणु
	.attr = अणु
		.name =		"stats",
		.mode =		S_IRUGO,
	पूर्ण,
	.show = twa_show_stats
पूर्ण;

/* Host attributes initializer */
अटल काष्ठा device_attribute *twa_host_attrs[] = अणु
	&twa_host_stats_attr,
	शून्य,
पूर्ण;

/* File operations काष्ठा क्रम अक्षरacter device */
अटल स्थिर काष्ठा file_operations twa_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= twa_chrdev_ioctl,
	.खोलो		= twa_chrdev_खोलो,
	.release	= शून्य,
	.llseek		= noop_llseek,
पूर्ण;

/*
 * The controllers use an अंतरभूत buffer instead of a mapped SGL क्रम small,
 * single entry buffers.  Note that we treat a zero-length transfer like
 * a mapped SGL.
 */
अटल bool twa_command_mapped(काष्ठा scsi_cmnd *cmd)
अणु
	वापस scsi_sg_count(cmd) != 1 ||
		scsi_bufflen(cmd) >= TW_MIN_SGL_LENGTH;
पूर्ण

/* This function will complete an aen request from the isr */
अटल पूर्णांक twa_aen_complete(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	TW_Command_Full *full_command_packet;
	TW_Command *command_packet;
	TW_Command_Apache_Header *header;
	अचिन्हित लघु aen;
	पूर्णांक retval = 1;

	header = (TW_Command_Apache_Header *)tw_dev->generic_buffer_virt[request_id];
	tw_dev->posted_request_count--;
	aen = le16_to_cpu(header->status_block.error);
	full_command_packet = tw_dev->command_packet_virt[request_id];
	command_packet = &full_command_packet->command.oldcommand;

	/* First check क्रम पूर्णांकernal completion of set param क्रम समय sync */
	अगर (TW_OP_OUT(command_packet->opcode__sgloffset) == TW_OP_SET_PARAM) अणु
		/* Keep पढ़ोing the queue in हाल there are more aen's */
		अगर (twa_aen_पढ़ो_queue(tw_dev, request_id))
			जाओ out2;
		अन्यथा अणु
			retval = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	चयन (aen) अणु
	हाल TW_AEN_QUEUE_EMPTY:
		/* Quit पढ़ोing the queue अगर this is the last one */
		अवरोध;
	हाल TW_AEN_SYNC_TIME_WITH_HOST:
		twa_aen_sync_समय(tw_dev, request_id);
		retval = 0;
		जाओ out;
	शेष:
		twa_aen_queue_event(tw_dev, header);

		/* If there are more aen's, keep पढ़ोing the queue */
		अगर (twa_aen_पढ़ो_queue(tw_dev, request_id))
			जाओ out2;
		अन्यथा अणु
			retval = 0;
			जाओ out;
		पूर्ण
	पूर्ण
	retval = 0;
out2:
	tw_dev->state[request_id] = TW_S_COMPLETED;
	twa_मुक्त_request_id(tw_dev, request_id);
	clear_bit(TW_IN_ATTENTION_LOOP, &tw_dev->flags);
out:
	वापस retval;
पूर्ण /* End twa_aen_complete() */

/* This function will drain aen queue */
अटल पूर्णांक twa_aen_drain_queue(TW_Device_Extension *tw_dev, पूर्णांक no_check_reset)
अणु
	पूर्णांक request_id = 0;
	अचिन्हित अक्षर cdb[TW_MAX_CDB_LEN];
	TW_SG_Entry sglist[1];
	पूर्णांक finished = 0, count = 0;
	TW_Command_Full *full_command_packet;
	TW_Command_Apache_Header *header;
	अचिन्हित लघु aen;
	पूर्णांक first_reset = 0, queue = 0, retval = 1;

	अगर (no_check_reset)
		first_reset = 0;
	अन्यथा
		first_reset = 1;

	full_command_packet = tw_dev->command_packet_virt[request_id];
	स_रखो(full_command_packet, 0, माप(TW_Command_Full));

	/* Initialize cdb */
	स_रखो(&cdb, 0, TW_MAX_CDB_LEN);
	cdb[0] = REQUEST_SENSE; /* opcode */
	cdb[4] = TW_ALLOCATION_LENGTH; /* allocation length */

	/* Initialize sglist */
	स_रखो(&sglist, 0, माप(TW_SG_Entry));
	sglist[0].length = TW_SECTOR_SIZE;
	sglist[0].address = tw_dev->generic_buffer_phys[request_id];

	अगर (sglist[0].address & TW_ALIGNMENT_9000_SGL) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1, "Found unaligned address during AEN drain");
		जाओ out;
	पूर्ण

	/* Mark पूर्णांकernal command */
	tw_dev->srb[request_id] = शून्य;

	करो अणु
		/* Send command to the board */
		अगर (twa_scsiop_execute_scsi(tw_dev, request_id, cdb, 1, sglist)) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x2, "Error posting request sense");
			जाओ out;
		पूर्ण

		/* Now poll क्रम completion */
		अगर (twa_poll_response(tw_dev, request_id, 30)) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x3, "No valid response while draining AEN queue");
			tw_dev->posted_request_count--;
			जाओ out;
		पूर्ण

		tw_dev->posted_request_count--;
		header = (TW_Command_Apache_Header *)tw_dev->generic_buffer_virt[request_id];
		aen = le16_to_cpu(header->status_block.error);
		queue = 0;
		count++;

		चयन (aen) अणु
		हाल TW_AEN_QUEUE_EMPTY:
			अगर (first_reset != 1)
				जाओ out;
			अन्यथा
				finished = 1;
			अवरोध;
		हाल TW_AEN_SOFT_RESET:
			अगर (first_reset == 0)
				first_reset = 1;
			अन्यथा
				queue = 1;
			अवरोध;
		हाल TW_AEN_SYNC_TIME_WITH_HOST:
			अवरोध;
		शेष:
			queue = 1;
		पूर्ण

		/* Now queue an event info */
		अगर (queue)
			twa_aen_queue_event(tw_dev, header);
	पूर्ण जबतक ((finished == 0) && (count < TW_MAX_AEN_DRAIN));

	अगर (count == TW_MAX_AEN_DRAIN)
		जाओ out;

	retval = 0;
out:
	tw_dev->state[request_id] = TW_S_INITIAL;
	वापस retval;
पूर्ण /* End twa_aen_drain_queue() */

/* This function will queue an event */
अटल व्योम twa_aen_queue_event(TW_Device_Extension *tw_dev, TW_Command_Apache_Header *header)
अणु
	u32 local_समय;
	TW_Event *event;
	अचिन्हित लघु aen;
	अक्षर host[16];
	अक्षर *error_str;

	tw_dev->aen_count++;

	/* Fill out event info */
	event = tw_dev->event_queue[tw_dev->error_index];

	/* Check क्रम clobber */
	host[0] = '\0';
	अगर (tw_dev->host) अणु
		प्र_लिखो(host, " scsi%d:", tw_dev->host->host_no);
		अगर (event->retrieved == TW_AEN_NOT_RETRIEVED)
			tw_dev->aen_clobber = 1;
	पूर्ण

	aen = le16_to_cpu(header->status_block.error);
	स_रखो(event, 0, माप(TW_Event));

	event->severity = TW_SEV_OUT(header->status_block.severity__reserved);
	/* event->समय_stamp_sec overflows in y2106 */
	local_समय = (u32)(kसमय_get_real_seconds() - (sys_tz.tz_minuteswest * 60));
	event->समय_stamp_sec = local_समय;
	event->aen_code = aen;
	event->retrieved = TW_AEN_NOT_RETRIEVED;
	event->sequence_id = tw_dev->error_sequence_id;
	tw_dev->error_sequence_id++;

	/* Check क्रम embedded error string */
	error_str = &(header->err_specअगरic_desc[म_माप(header->err_specअगरic_desc)+1]);

	header->err_specअगरic_desc[माप(header->err_specअगरic_desc) - 1] = '\0';
	event->parameter_len = म_माप(header->err_specअगरic_desc);
	स_नकल(event->parameter_data, header->err_specअगरic_desc, event->parameter_len + (error_str[0] == '\0' ? 0 : (1 + म_माप(error_str))));
	अगर (event->severity != TW_AEN_SEVERITY_DEBUG)
		prपूर्णांकk(KERN_WARNING "3w-9xxx:%s AEN: %s (0x%02X:0x%04X): %s:%s.\n",
		       host,
		       twa_aen_severity_lookup(TW_SEV_OUT(header->status_block.severity__reserved)),
		       TW_MESSAGE_SOURCE_CONTROLLER_EVENT, aen,
		       error_str[0] == '\0' ? twa_string_lookup(twa_aen_table, aen) : error_str,
		       header->err_specअगरic_desc);
	अन्यथा
		tw_dev->aen_count--;

	अगर ((tw_dev->error_index + 1) == TW_Q_LENGTH)
		tw_dev->event_queue_wrapped = 1;
	tw_dev->error_index = (tw_dev->error_index + 1 ) % TW_Q_LENGTH;
पूर्ण /* End twa_aen_queue_event() */

/* This function will पढ़ो the aen queue from the isr */
अटल पूर्णांक twa_aen_पढ़ो_queue(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	अचिन्हित अक्षर cdb[TW_MAX_CDB_LEN];
	TW_SG_Entry sglist[1];
	TW_Command_Full *full_command_packet;
	पूर्णांक retval = 1;

	full_command_packet = tw_dev->command_packet_virt[request_id];
	स_रखो(full_command_packet, 0, माप(TW_Command_Full));

	/* Initialize cdb */
	स_रखो(&cdb, 0, TW_MAX_CDB_LEN);
	cdb[0] = REQUEST_SENSE; /* opcode */
	cdb[4] = TW_ALLOCATION_LENGTH; /* allocation length */

	/* Initialize sglist */
	स_रखो(&sglist, 0, माप(TW_SG_Entry));
	sglist[0].length = TW_SECTOR_SIZE;
	sglist[0].address = tw_dev->generic_buffer_phys[request_id];

	/* Mark पूर्णांकernal command */
	tw_dev->srb[request_id] = शून्य;

	/* Now post the command packet */
	अगर (twa_scsiop_execute_scsi(tw_dev, request_id, cdb, 1, sglist)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x4, "Post failed while reading AEN queue");
		जाओ out;
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_aen_पढ़ो_queue() */

/* This function will look up an AEN severity string */
अटल अक्षर *twa_aen_severity_lookup(अचिन्हित अक्षर severity_code)
अणु
	अक्षर *retval = शून्य;

	अगर ((severity_code < (अचिन्हित अक्षर) TW_AEN_SEVERITY_ERROR) ||
	    (severity_code > (अचिन्हित अक्षर) TW_AEN_SEVERITY_DEBUG))
		जाओ out;

	retval = twa_aen_severity_table[severity_code];
out:
	वापस retval;
पूर्ण /* End twa_aen_severity_lookup() */

/* This function will sync firmware समय with the host समय */
अटल व्योम twa_aen_sync_समय(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	u32 schedulerसमय;
	TW_Command_Full *full_command_packet;
	TW_Command *command_packet;
	TW_Param_Apache *param;
	समय64_t local_समय;

	/* Fill out the command packet */
	full_command_packet = tw_dev->command_packet_virt[request_id];
	स_रखो(full_command_packet, 0, माप(TW_Command_Full));
	command_packet = &full_command_packet->command.oldcommand;
	command_packet->opcode__sgloffset = TW_OPSGL_IN(2, TW_OP_SET_PARAM);
	command_packet->request_id = request_id;
	command_packet->byte8_offset.param.sgl[0].address = TW_CPU_TO_SGL(tw_dev->generic_buffer_phys[request_id]);
	command_packet->byte8_offset.param.sgl[0].length = cpu_to_le32(TW_SECTOR_SIZE);
	command_packet->size = TW_COMMAND_SIZE;
	command_packet->byte6_offset.parameter_count = cpu_to_le16(1);

	/* Setup the param */
	param = (TW_Param_Apache *)tw_dev->generic_buffer_virt[request_id];
	स_रखो(param, 0, TW_SECTOR_SIZE);
	param->table_id = cpu_to_le16(TW_TIMEKEEP_TABLE | 0x8000); /* Controller समय keep table */
	param->parameter_id = cpu_to_le16(0x3); /* SchedulerTime */
	param->parameter_size_bytes = cpu_to_le16(4);

	/* Convert प्रणाली समय in UTC to local समय seconds since last
           Sunday 12:00AM */
	local_समय = (kसमय_get_real_seconds() - (sys_tz.tz_minuteswest * 60));
	भाग_u64_rem(local_समय - (3 * 86400), 604800, &schedulerसमय);
	schedulerसमय = cpu_to_le32(schedulerसमय % 604800);

	स_नकल(param->data, &schedulerसमय, माप(u32));

	/* Mark पूर्णांकernal command */
	tw_dev->srb[request_id] = शून्य;

	/* Now post the command */
	twa_post_command_packet(tw_dev, request_id, 1);
पूर्ण /* End twa_aen_sync_समय() */

/* This function will allocate memory and check अगर it is correctly aligned */
अटल पूर्णांक twa_allocate_memory(TW_Device_Extension *tw_dev, पूर्णांक size, पूर्णांक which)
अणु
	पूर्णांक i;
	dma_addr_t dma_handle;
	अचिन्हित दीर्घ *cpu_addr;
	पूर्णांक retval = 1;

	cpu_addr = dma_alloc_coherent(&tw_dev->tw_pci_dev->dev,
			size * TW_Q_LENGTH, &dma_handle, GFP_KERNEL);
	अगर (!cpu_addr) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x5, "Memory allocation failed");
		जाओ out;
	पूर्ण

	अगर ((अचिन्हित दीर्घ)cpu_addr % (TW_ALIGNMENT_9000)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x6, "Failed to allocate correctly aligned memory");
		dma_मुक्त_coherent(&tw_dev->tw_pci_dev->dev, size * TW_Q_LENGTH,
				cpu_addr, dma_handle);
		जाओ out;
	पूर्ण

	स_रखो(cpu_addr, 0, size*TW_Q_LENGTH);

	क्रम (i = 0; i < TW_Q_LENGTH; i++) अणु
		चयन(which) अणु
		हाल 0:
			tw_dev->command_packet_phys[i] = dma_handle+(i*size);
			tw_dev->command_packet_virt[i] = (TW_Command_Full *)((अचिन्हित अक्षर *)cpu_addr + (i*size));
			अवरोध;
		हाल 1:
			tw_dev->generic_buffer_phys[i] = dma_handle+(i*size);
			tw_dev->generic_buffer_virt[i] = (अचिन्हित दीर्घ *)((अचिन्हित अक्षर *)cpu_addr + (i*size));
			अवरोध;
		पूर्ण
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_allocate_memory() */

/* This function will check the status रेजिस्टर क्रम unexpected bits */
अटल पूर्णांक twa_check_bits(u32 status_reg_value)
अणु
	पूर्णांक retval = 1;

	अगर ((status_reg_value & TW_STATUS_EXPECTED_BITS) != TW_STATUS_EXPECTED_BITS)
		जाओ out;
	अगर ((status_reg_value & TW_STATUS_UNEXPECTED_BITS) != 0)
		जाओ out;

	retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_check_bits() */

/* This function will check the srl and decide अगर we are compatible  */
अटल पूर्णांक twa_check_srl(TW_Device_Extension *tw_dev, पूर्णांक *flashed)
अणु
	पूर्णांक retval = 1;
	अचिन्हित लघु fw_on_ctlr_srl = 0, fw_on_ctlr_arch_id = 0;
	अचिन्हित लघु fw_on_ctlr_branch = 0, fw_on_ctlr_build = 0;
	u32 init_connect_result = 0;

	अगर (twa_initconnection(tw_dev, TW_INIT_MESSAGE_CREDITS,
			       TW_EXTENDED_INIT_CONNECT, TW_CURRENT_DRIVER_SRL,
			       TW_9000_ARCH_ID, TW_CURRENT_DRIVER_BRANCH,
			       TW_CURRENT_DRIVER_BUILD, &fw_on_ctlr_srl,
			       &fw_on_ctlr_arch_id, &fw_on_ctlr_branch,
			       &fw_on_ctlr_build, &init_connect_result)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x7, "Initconnection failed while checking SRL");
		जाओ out;
	पूर्ण

	tw_dev->tw_compat_info.working_srl = fw_on_ctlr_srl;
	tw_dev->tw_compat_info.working_branch = fw_on_ctlr_branch;
	tw_dev->tw_compat_info.working_build = fw_on_ctlr_build;

	/* Try base mode compatibility */
	अगर (!(init_connect_result & TW_CTLR_FW_COMPATIBLE)) अणु
		अगर (twa_initconnection(tw_dev, TW_INIT_MESSAGE_CREDITS,
				       TW_EXTENDED_INIT_CONNECT,
				       TW_BASE_FW_SRL, TW_9000_ARCH_ID,
				       TW_BASE_FW_BRANCH, TW_BASE_FW_BUILD,
				       &fw_on_ctlr_srl, &fw_on_ctlr_arch_id,
				       &fw_on_ctlr_branch, &fw_on_ctlr_build,
				       &init_connect_result)) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0xa, "Initconnection (base mode) failed while checking SRL");
			जाओ out;
		पूर्ण
		अगर (!(init_connect_result & TW_CTLR_FW_COMPATIBLE)) अणु
			अगर (TW_CURRENT_DRIVER_SRL > fw_on_ctlr_srl) अणु
				TW_PRINTK(tw_dev->host, TW_DRIVER, 0x32, "Firmware and driver incompatibility: please upgrade firmware");
			पूर्ण अन्यथा अणु
				TW_PRINTK(tw_dev->host, TW_DRIVER, 0x33, "Firmware and driver incompatibility: please upgrade driver");
			पूर्ण
			जाओ out;
		पूर्ण
		tw_dev->tw_compat_info.working_srl = TW_BASE_FW_SRL;
		tw_dev->tw_compat_info.working_branch = TW_BASE_FW_BRANCH;
		tw_dev->tw_compat_info.working_build = TW_BASE_FW_BUILD;
	पूर्ण

	/* Load rest of compatibility काष्ठा */
	strlcpy(tw_dev->tw_compat_info.driver_version, TW_DRIVER_VERSION,
		माप(tw_dev->tw_compat_info.driver_version));
	tw_dev->tw_compat_info.driver_srl_high = TW_CURRENT_DRIVER_SRL;
	tw_dev->tw_compat_info.driver_branch_high = TW_CURRENT_DRIVER_BRANCH;
	tw_dev->tw_compat_info.driver_build_high = TW_CURRENT_DRIVER_BUILD;
	tw_dev->tw_compat_info.driver_srl_low = TW_BASE_FW_SRL;
	tw_dev->tw_compat_info.driver_branch_low = TW_BASE_FW_BRANCH;
	tw_dev->tw_compat_info.driver_build_low = TW_BASE_FW_BUILD;
	tw_dev->tw_compat_info.fw_on_ctlr_srl = fw_on_ctlr_srl;
	tw_dev->tw_compat_info.fw_on_ctlr_branch = fw_on_ctlr_branch;
	tw_dev->tw_compat_info.fw_on_ctlr_build = fw_on_ctlr_build;

	retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_check_srl() */

/* This function handles ioctl क्रम the अक्षरacter device */
अटल दीर्घ twa_chrdev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	दीर्घ समयout;
	अचिन्हित दीर्घ *cpu_addr, data_buffer_length_adjusted = 0, flags = 0;
	dma_addr_t dma_handle;
	पूर्णांक request_id = 0;
	अचिन्हित पूर्णांक sequence_id = 0;
	अचिन्हित अक्षर event_index, start_index;
	TW_Ioctl_Driver_Command driver_command;
	TW_Ioctl_Buf_Apache *tw_ioctl;
	TW_Lock *tw_lock;
	TW_Command_Full *full_command_packet;
	TW_Compatibility_Info *tw_compat_info;
	TW_Event *event;
	kसमय_प्रकार current_समय;
	TW_Device_Extension *tw_dev = twa_device_extension_list[iminor(inode)];
	पूर्णांक retval = TW_IOCTL_ERROR_OS_EFAULT;
	व्योम __user *argp = (व्योम __user *)arg;

	mutex_lock(&twa_chrdev_mutex);

	/* Only let one of these through at a समय */
	अगर (mutex_lock_पूर्णांकerruptible(&tw_dev->ioctl_lock)) अणु
		retval = TW_IOCTL_ERROR_OS_EINTR;
		जाओ out;
	पूर्ण

	/* First copy करोwn the driver command */
	अगर (copy_from_user(&driver_command, argp, माप(TW_Ioctl_Driver_Command)))
		जाओ out2;

	/* Check data buffer size */
	अगर (driver_command.buffer_length > TW_MAX_SECTORS * 2048) अणु
		retval = TW_IOCTL_ERROR_OS_EINVAL;
		जाओ out2;
	पूर्ण

	/* Hardware can only करो multiple of 512 byte transfers */
	data_buffer_length_adjusted = (driver_command.buffer_length + 511) & ~511;

	/* Now allocate ioctl buf memory */
	cpu_addr = dma_alloc_coherent(&tw_dev->tw_pci_dev->dev, data_buffer_length_adjusted+माप(TW_Ioctl_Buf_Apache) - 1, &dma_handle, GFP_KERNEL);
	अगर (!cpu_addr) अणु
		retval = TW_IOCTL_ERROR_OS_ENOMEM;
		जाओ out2;
	पूर्ण

	tw_ioctl = (TW_Ioctl_Buf_Apache *)cpu_addr;

	/* Now copy करोwn the entire ioctl */
	अगर (copy_from_user(tw_ioctl, argp, driver_command.buffer_length + माप(TW_Ioctl_Buf_Apache) - 1))
		जाओ out3;

	/* See which ioctl we are करोing */
	चयन (cmd) अणु
	हाल TW_IOCTL_FIRMWARE_PASS_THROUGH:
		spin_lock_irqsave(tw_dev->host->host_lock, flags);
		twa_get_request_id(tw_dev, &request_id);

		/* Flag पूर्णांकernal command */
		tw_dev->srb[request_id] = शून्य;

		/* Flag chrdev ioctl */
		tw_dev->chrdev_request_id = request_id;

		full_command_packet = &tw_ioctl->firmware_command;

		/* Load request id and sglist क्रम both command types */
		twa_load_sgl(tw_dev, full_command_packet, request_id, dma_handle, data_buffer_length_adjusted);

		स_नकल(tw_dev->command_packet_virt[request_id], &(tw_ioctl->firmware_command), माप(TW_Command_Full));

		/* Now post the command packet to the controller */
		twa_post_command_packet(tw_dev, request_id, 1);
		spin_unlock_irqrestore(tw_dev->host->host_lock, flags);

		समयout = TW_IOCTL_CHRDEV_TIMEOUT*HZ;

		/* Now रुको क्रम command to complete */
		समयout = रुको_event_समयout(tw_dev->ioctl_wqueue, tw_dev->chrdev_request_id == TW_IOCTL_CHRDEV_FREE, समयout);

		/* We समयd out, and didn't get an पूर्णांकerrupt */
		अगर (tw_dev->chrdev_request_id != TW_IOCTL_CHRDEV_FREE) अणु
			/* Now we need to reset the board */
			prपूर्णांकk(KERN_WARNING "3w-9xxx: scsi%d: WARNING: (0x%02X:0x%04X): Character ioctl (0x%x) timed out, resetting card.\n",
			       tw_dev->host->host_no, TW_DRIVER, 0x37,
			       cmd);
			retval = TW_IOCTL_ERROR_OS_EIO;
			twa_reset_device_extension(tw_dev);
			जाओ out3;
		पूर्ण

		/* Now copy in the command packet response */
		स_नकल(&(tw_ioctl->firmware_command), tw_dev->command_packet_virt[request_id], माप(TW_Command_Full));

		/* Now complete the io */
		spin_lock_irqsave(tw_dev->host->host_lock, flags);
		tw_dev->posted_request_count--;
		tw_dev->state[request_id] = TW_S_COMPLETED;
		twa_मुक्त_request_id(tw_dev, request_id);
		spin_unlock_irqrestore(tw_dev->host->host_lock, flags);
		अवरोध;
	हाल TW_IOCTL_GET_COMPATIBILITY_INFO:
		tw_ioctl->driver_command.status = 0;
		/* Copy compatibility काष्ठा पूर्णांकo ioctl data buffer */
		tw_compat_info = (TW_Compatibility_Info *)tw_ioctl->data_buffer;
		स_नकल(tw_compat_info, &tw_dev->tw_compat_info, माप(TW_Compatibility_Info));
		अवरोध;
	हाल TW_IOCTL_GET_LAST_EVENT:
		अगर (tw_dev->event_queue_wrapped) अणु
			अगर (tw_dev->aen_clobber) अणु
				tw_ioctl->driver_command.status = TW_IOCTL_ERROR_STATUS_AEN_CLOBBER;
				tw_dev->aen_clobber = 0;
			पूर्ण अन्यथा
				tw_ioctl->driver_command.status = 0;
		पूर्ण अन्यथा अणु
			अगर (!tw_dev->error_index) अणु
				tw_ioctl->driver_command.status = TW_IOCTL_ERROR_STATUS_NO_MORE_EVENTS;
				अवरोध;
			पूर्ण
			tw_ioctl->driver_command.status = 0;
		पूर्ण
		event_index = (tw_dev->error_index - 1 + TW_Q_LENGTH) % TW_Q_LENGTH;
		स_नकल(tw_ioctl->data_buffer, tw_dev->event_queue[event_index], माप(TW_Event));
		tw_dev->event_queue[event_index]->retrieved = TW_AEN_RETRIEVED;
		अवरोध;
	हाल TW_IOCTL_GET_FIRST_EVENT:
		अगर (tw_dev->event_queue_wrapped) अणु
			अगर (tw_dev->aen_clobber) अणु
				tw_ioctl->driver_command.status = TW_IOCTL_ERROR_STATUS_AEN_CLOBBER;
				tw_dev->aen_clobber = 0;
			पूर्ण अन्यथा
				tw_ioctl->driver_command.status = 0;
			event_index = tw_dev->error_index;
		पूर्ण अन्यथा अणु
			अगर (!tw_dev->error_index) अणु
				tw_ioctl->driver_command.status = TW_IOCTL_ERROR_STATUS_NO_MORE_EVENTS;
				अवरोध;
			पूर्ण
			tw_ioctl->driver_command.status = 0;
			event_index = 0;
		पूर्ण
		स_नकल(tw_ioctl->data_buffer, tw_dev->event_queue[event_index], माप(TW_Event));
		tw_dev->event_queue[event_index]->retrieved = TW_AEN_RETRIEVED;
		अवरोध;
	हाल TW_IOCTL_GET_NEXT_EVENT:
		event = (TW_Event *)tw_ioctl->data_buffer;
		sequence_id = event->sequence_id;
		tw_ioctl->driver_command.status = 0;

		अगर (tw_dev->event_queue_wrapped) अणु
			अगर (tw_dev->aen_clobber) अणु
				tw_ioctl->driver_command.status = TW_IOCTL_ERROR_STATUS_AEN_CLOBBER;
				tw_dev->aen_clobber = 0;
			पूर्ण
			start_index = tw_dev->error_index;
		पूर्ण अन्यथा अणु
			अगर (!tw_dev->error_index) अणु
				tw_ioctl->driver_command.status = TW_IOCTL_ERROR_STATUS_NO_MORE_EVENTS;
				अवरोध;
			पूर्ण
			start_index = 0;
		पूर्ण
		event_index = (start_index + sequence_id - tw_dev->event_queue[start_index]->sequence_id + 1) % TW_Q_LENGTH;

		अगर (!(tw_dev->event_queue[event_index]->sequence_id > sequence_id)) अणु
			अगर (tw_ioctl->driver_command.status == TW_IOCTL_ERROR_STATUS_AEN_CLOBBER)
				tw_dev->aen_clobber = 1;
			tw_ioctl->driver_command.status = TW_IOCTL_ERROR_STATUS_NO_MORE_EVENTS;
			अवरोध;
		पूर्ण
		स_नकल(tw_ioctl->data_buffer, tw_dev->event_queue[event_index], माप(TW_Event));
		tw_dev->event_queue[event_index]->retrieved = TW_AEN_RETRIEVED;
		अवरोध;
	हाल TW_IOCTL_GET_PREVIOUS_EVENT:
		event = (TW_Event *)tw_ioctl->data_buffer;
		sequence_id = event->sequence_id;
		tw_ioctl->driver_command.status = 0;

		अगर (tw_dev->event_queue_wrapped) अणु
			अगर (tw_dev->aen_clobber) अणु
				tw_ioctl->driver_command.status = TW_IOCTL_ERROR_STATUS_AEN_CLOBBER;
				tw_dev->aen_clobber = 0;
			पूर्ण
			start_index = tw_dev->error_index;
		पूर्ण अन्यथा अणु
			अगर (!tw_dev->error_index) अणु
				tw_ioctl->driver_command.status = TW_IOCTL_ERROR_STATUS_NO_MORE_EVENTS;
				अवरोध;
			पूर्ण
			start_index = 0;
		पूर्ण
		event_index = (start_index + sequence_id - tw_dev->event_queue[start_index]->sequence_id - 1) % TW_Q_LENGTH;

		अगर (!(tw_dev->event_queue[event_index]->sequence_id < sequence_id)) अणु
			अगर (tw_ioctl->driver_command.status == TW_IOCTL_ERROR_STATUS_AEN_CLOBBER)
				tw_dev->aen_clobber = 1;
			tw_ioctl->driver_command.status = TW_IOCTL_ERROR_STATUS_NO_MORE_EVENTS;
			अवरोध;
		पूर्ण
		स_नकल(tw_ioctl->data_buffer, tw_dev->event_queue[event_index], माप(TW_Event));
		tw_dev->event_queue[event_index]->retrieved = TW_AEN_RETRIEVED;
		अवरोध;
	हाल TW_IOCTL_GET_LOCK:
		tw_lock = (TW_Lock *)tw_ioctl->data_buffer;
		current_समय = kसमय_get();

		अगर ((tw_lock->क्रमce_flag == 1) || (tw_dev->ioctl_sem_lock == 0) ||
		    kसमय_after(current_समय, tw_dev->ioctl_समय)) अणु
			tw_dev->ioctl_sem_lock = 1;
			tw_dev->ioctl_समय = kसमय_add_ms(current_समय, tw_lock->समयout_msec);
			tw_ioctl->driver_command.status = 0;
			tw_lock->समय_reमुख्यing_msec = tw_lock->समयout_msec;
		पूर्ण अन्यथा अणु
			tw_ioctl->driver_command.status = TW_IOCTL_ERROR_STATUS_LOCKED;
			tw_lock->समय_reमुख्यing_msec = kसमय_ms_delta(tw_dev->ioctl_समय, current_समय);
		पूर्ण
		अवरोध;
	हाल TW_IOCTL_RELEASE_LOCK:
		अगर (tw_dev->ioctl_sem_lock == 1) अणु
			tw_dev->ioctl_sem_lock = 0;
			tw_ioctl->driver_command.status = 0;
		पूर्ण अन्यथा अणु
			tw_ioctl->driver_command.status = TW_IOCTL_ERROR_STATUS_NOT_LOCKED;
		पूर्ण
		अवरोध;
	शेष:
		retval = TW_IOCTL_ERROR_OS_ENOTTY;
		जाओ out3;
	पूर्ण

	/* Now copy the entire response to userspace */
	अगर (copy_to_user(argp, tw_ioctl, माप(TW_Ioctl_Buf_Apache) + driver_command.buffer_length - 1) == 0)
		retval = 0;
out3:
	/* Now मुक्त ioctl buf memory */
	dma_मुक्त_coherent(&tw_dev->tw_pci_dev->dev, data_buffer_length_adjusted+माप(TW_Ioctl_Buf_Apache) - 1, cpu_addr, dma_handle);
out2:
	mutex_unlock(&tw_dev->ioctl_lock);
out:
	mutex_unlock(&twa_chrdev_mutex);
	वापस retval;
पूर्ण /* End twa_chrdev_ioctl() */

/* This function handles खोलो क्रम the अक्षरacter device */
/* NOTE that this function will race with हटाओ. */
अटल पूर्णांक twa_chrdev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor_number;
	पूर्णांक retval = TW_IOCTL_ERROR_OS_ENODEV;

	अगर (!capable(CAP_SYS_ADMIN)) अणु
		retval = -EACCES;
		जाओ out;
	पूर्ण

	minor_number = iminor(inode);
	अगर (minor_number >= twa_device_extension_count)
		जाओ out;
	retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_chrdev_खोलो() */

/* This function will prपूर्णांक पढ़ोable messages from status रेजिस्टर errors */
अटल पूर्णांक twa_decode_bits(TW_Device_Extension *tw_dev, u32 status_reg_value)
अणु
	पूर्णांक retval = 1;

	/* Check क्रम various error conditions and handle them appropriately */
	अगर (status_reg_value & TW_STATUS_PCI_PARITY_ERROR) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0xc, "PCI Parity Error: clearing");
		ग_लिखोl(TW_CONTROL_CLEAR_PARITY_ERROR, TW_CONTROL_REG_ADDR(tw_dev));
	पूर्ण

	अगर (status_reg_value & TW_STATUS_PCI_ABORT) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0xd, "PCI Abort: clearing");
		ग_लिखोl(TW_CONTROL_CLEAR_PCI_ABORT, TW_CONTROL_REG_ADDR(tw_dev));
		pci_ग_लिखो_config_word(tw_dev->tw_pci_dev, PCI_STATUS, TW_PCI_CLEAR_PCI_ABORT);
	पूर्ण

	अगर (status_reg_value & TW_STATUS_QUEUE_ERROR) अणु
		अगर (((tw_dev->tw_pci_dev->device != PCI_DEVICE_ID_3WARE_9650SE) &&
		     (tw_dev->tw_pci_dev->device != PCI_DEVICE_ID_3WARE_9690SA)) ||
		    (!test_bit(TW_IN_RESET, &tw_dev->flags)))
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0xe, "Controller Queue Error: clearing");
		ग_लिखोl(TW_CONTROL_CLEAR_QUEUE_ERROR, TW_CONTROL_REG_ADDR(tw_dev));
	पूर्ण

	अगर (status_reg_value & TW_STATUS_MICROCONTROLLER_ERROR) अणु
		अगर (tw_dev->reset_prपूर्णांक == 0) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x10, "Microcontroller Error: clearing");
			tw_dev->reset_prपूर्णांक = 1;
		पूर्ण
		जाओ out;
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_decode_bits() */

/* This function will empty the response queue */
अटल पूर्णांक twa_empty_response_queue(TW_Device_Extension *tw_dev)
अणु
	u32 status_reg_value;
	पूर्णांक count = 0, retval = 1;

	status_reg_value = पढ़ोl(TW_STATUS_REG_ADDR(tw_dev));

	जबतक (((status_reg_value & TW_STATUS_RESPONSE_QUEUE_EMPTY) == 0) && (count < TW_MAX_RESPONSE_DRAIN)) अणु
		पढ़ोl(TW_RESPONSE_QUEUE_REG_ADDR(tw_dev));
		status_reg_value = पढ़ोl(TW_STATUS_REG_ADDR(tw_dev));
		count++;
	पूर्ण
	अगर (count == TW_MAX_RESPONSE_DRAIN)
		जाओ out;

	retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_empty_response_queue() */

/* This function will clear the pchip/response queue on 9550SX */
अटल पूर्णांक twa_empty_response_queue_large(TW_Device_Extension *tw_dev)
अणु
	u32 response_que_value = 0;
	अचिन्हित दीर्घ beक्रमe;
	पूर्णांक retval = 1;

	अगर (tw_dev->tw_pci_dev->device != PCI_DEVICE_ID_3WARE_9000) अणु
		beक्रमe = jअगरfies;
		जबतक ((response_que_value & TW_9550SX_DRAIN_COMPLETED) != TW_9550SX_DRAIN_COMPLETED) अणु
			response_que_value = पढ़ोl(TW_RESPONSE_QUEUE_REG_ADDR_LARGE(tw_dev));
			msleep(1);
			अगर (समय_after(jअगरfies, beक्रमe + HZ * 30))
				जाओ out;
		पूर्ण
		/* P-chip settle समय */
		msleep(500);
		retval = 0;
	पूर्ण अन्यथा
		retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_empty_response_queue_large() */

/* This function passes sense keys from firmware to scsi layer */
अटल पूर्णांक twa_fill_sense(TW_Device_Extension *tw_dev, पूर्णांक request_id, पूर्णांक copy_sense, पूर्णांक prपूर्णांक_host)
अणु
	TW_Command_Full *full_command_packet;
	अचिन्हित लघु error;
	पूर्णांक retval = 1;
	अक्षर *error_str;

	full_command_packet = tw_dev->command_packet_virt[request_id];

	/* Check क्रम embedded error string */
	error_str = &(full_command_packet->header.err_specअगरic_desc[म_माप(full_command_packet->header.err_specअगरic_desc) + 1]);

	/* Don't prपूर्णांक error क्रम Logical unit not supported during rollcall */
	error = le16_to_cpu(full_command_packet->header.status_block.error);
	अगर ((error != TW_ERROR_LOGICAL_UNIT_NOT_SUPPORTED) && (error != TW_ERROR_UNIT_OFFLINE)) अणु
		अगर (prपूर्णांक_host)
			prपूर्णांकk(KERN_WARNING "3w-9xxx: scsi%d: ERROR: (0x%02X:0x%04X): %s:%s.\n",
			       tw_dev->host->host_no,
			       TW_MESSAGE_SOURCE_CONTROLLER_ERROR,
			       full_command_packet->header.status_block.error,
			       error_str[0] == '\0' ?
			       twa_string_lookup(twa_error_table,
						 full_command_packet->header.status_block.error) : error_str,
			       full_command_packet->header.err_specअगरic_desc);
		अन्यथा
			prपूर्णांकk(KERN_WARNING "3w-9xxx: ERROR: (0x%02X:0x%04X): %s:%s.\n",
			       TW_MESSAGE_SOURCE_CONTROLLER_ERROR,
			       full_command_packet->header.status_block.error,
			       error_str[0] == '\0' ?
			       twa_string_lookup(twa_error_table,
						 full_command_packet->header.status_block.error) : error_str,
			       full_command_packet->header.err_specअगरic_desc);
	पूर्ण

	अगर (copy_sense) अणु
		स_नकल(tw_dev->srb[request_id]->sense_buffer, full_command_packet->header.sense_data, TW_SENSE_DATA_LENGTH);
		tw_dev->srb[request_id]->result = (full_command_packet->command.newcommand.status << 1);
		retval = TW_ISR_DONT_RESULT;
		जाओ out;
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_fill_sense() */

/* This function will मुक्त up device extension resources */
अटल व्योम twa_मुक्त_device_extension(TW_Device_Extension *tw_dev)
अणु
	अगर (tw_dev->command_packet_virt[0])
		dma_मुक्त_coherent(&tw_dev->tw_pci_dev->dev,
				माप(TW_Command_Full) * TW_Q_LENGTH,
				tw_dev->command_packet_virt[0],
				tw_dev->command_packet_phys[0]);

	अगर (tw_dev->generic_buffer_virt[0])
		dma_मुक्त_coherent(&tw_dev->tw_pci_dev->dev,
				TW_SECTOR_SIZE * TW_Q_LENGTH,
				tw_dev->generic_buffer_virt[0],
				tw_dev->generic_buffer_phys[0]);

	kमुक्त(tw_dev->event_queue[0]);
पूर्ण /* End twa_मुक्त_device_extension() */

/* This function will मुक्त a request id */
अटल व्योम twa_मुक्त_request_id(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	tw_dev->मुक्त_queue[tw_dev->मुक्त_tail] = request_id;
	tw_dev->state[request_id] = TW_S_FINISHED;
	tw_dev->मुक्त_tail = (tw_dev->मुक्त_tail + 1) % TW_Q_LENGTH;
पूर्ण /* End twa_मुक्त_request_id() */

/* This function will get parameter table entries from the firmware */
अटल व्योम *twa_get_param(TW_Device_Extension *tw_dev, पूर्णांक request_id, पूर्णांक table_id, पूर्णांक parameter_id, पूर्णांक parameter_size_bytes)
अणु
	TW_Command_Full *full_command_packet;
	TW_Command *command_packet;
	TW_Param_Apache *param;
	व्योम *retval = शून्य;

	/* Setup the command packet */
	full_command_packet = tw_dev->command_packet_virt[request_id];
	स_रखो(full_command_packet, 0, माप(TW_Command_Full));
	command_packet = &full_command_packet->command.oldcommand;

	command_packet->opcode__sgloffset = TW_OPSGL_IN(2, TW_OP_GET_PARAM);
	command_packet->size		  = TW_COMMAND_SIZE;
	command_packet->request_id	  = request_id;
	command_packet->byte6_offset.block_count = cpu_to_le16(1);

	/* Now setup the param */
	param = (TW_Param_Apache *)tw_dev->generic_buffer_virt[request_id];
	स_रखो(param, 0, TW_SECTOR_SIZE);
	param->table_id = cpu_to_le16(table_id | 0x8000);
	param->parameter_id = cpu_to_le16(parameter_id);
	param->parameter_size_bytes = cpu_to_le16(parameter_size_bytes);

	command_packet->byte8_offset.param.sgl[0].address = TW_CPU_TO_SGL(tw_dev->generic_buffer_phys[request_id]);
	command_packet->byte8_offset.param.sgl[0].length = cpu_to_le32(TW_SECTOR_SIZE);

	/* Post the command packet to the board */
	twa_post_command_packet(tw_dev, request_id, 1);

	/* Poll क्रम completion */
	अगर (twa_poll_response(tw_dev, request_id, 30))
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x13, "No valid response during get param")
	अन्यथा
		retval = (व्योम *)&(param->data[0]);

	tw_dev->posted_request_count--;
	tw_dev->state[request_id] = TW_S_INITIAL;

	वापस retval;
पूर्ण /* End twa_get_param() */

/* This function will assign an available request id */
अटल व्योम twa_get_request_id(TW_Device_Extension *tw_dev, पूर्णांक *request_id)
अणु
	*request_id = tw_dev->मुक्त_queue[tw_dev->मुक्त_head];
	tw_dev->मुक्त_head = (tw_dev->मुक्त_head + 1) % TW_Q_LENGTH;
	tw_dev->state[*request_id] = TW_S_STARTED;
पूर्ण /* End twa_get_request_id() */

/* This function will send an initconnection command to controller */
अटल पूर्णांक twa_initconnection(TW_Device_Extension *tw_dev, पूर्णांक message_credits,
			      u32 set_features, अचिन्हित लघु current_fw_srl,
			      अचिन्हित लघु current_fw_arch_id,
			      अचिन्हित लघु current_fw_branch,
			      अचिन्हित लघु current_fw_build,
			      अचिन्हित लघु *fw_on_ctlr_srl,
			      अचिन्हित लघु *fw_on_ctlr_arch_id,
			      अचिन्हित लघु *fw_on_ctlr_branch,
			      अचिन्हित लघु *fw_on_ctlr_build,
			      u32 *init_connect_result)
अणु
	TW_Command_Full *full_command_packet;
	TW_Initconnect *tw_initconnect;
	पूर्णांक request_id = 0, retval = 1;

	/* Initialize InitConnection command packet */
	full_command_packet = tw_dev->command_packet_virt[request_id];
	स_रखो(full_command_packet, 0, माप(TW_Command_Full));
	full_command_packet->header.header_desc.size_header = 128;

	tw_initconnect = (TW_Initconnect *)&full_command_packet->command.oldcommand;
	tw_initconnect->opcode__reserved = TW_OPRES_IN(0, TW_OP_INIT_CONNECTION);
	tw_initconnect->request_id = request_id;
	tw_initconnect->message_credits = cpu_to_le16(message_credits);
	tw_initconnect->features = set_features;

	/* Turn on 64-bit sgl support अगर we need to */
	tw_initconnect->features |= माप(dma_addr_t) > 4 ? 1 : 0;

	tw_initconnect->features = cpu_to_le32(tw_initconnect->features);

	अगर (set_features & TW_EXTENDED_INIT_CONNECT) अणु
		tw_initconnect->size = TW_INIT_COMMAND_PACKET_SIZE_EXTENDED;
		tw_initconnect->fw_srl = cpu_to_le16(current_fw_srl);
		tw_initconnect->fw_arch_id = cpu_to_le16(current_fw_arch_id);
		tw_initconnect->fw_branch = cpu_to_le16(current_fw_branch);
		tw_initconnect->fw_build = cpu_to_le16(current_fw_build);
	पूर्ण अन्यथा
		tw_initconnect->size = TW_INIT_COMMAND_PACKET_SIZE;

	/* Send command packet to the board */
	twa_post_command_packet(tw_dev, request_id, 1);

	/* Poll क्रम completion */
	अगर (twa_poll_response(tw_dev, request_id, 30)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x15, "No valid response during init connection");
	पूर्ण अन्यथा अणु
		अगर (set_features & TW_EXTENDED_INIT_CONNECT) अणु
			*fw_on_ctlr_srl = le16_to_cpu(tw_initconnect->fw_srl);
			*fw_on_ctlr_arch_id = le16_to_cpu(tw_initconnect->fw_arch_id);
			*fw_on_ctlr_branch = le16_to_cpu(tw_initconnect->fw_branch);
			*fw_on_ctlr_build = le16_to_cpu(tw_initconnect->fw_build);
			*init_connect_result = le32_to_cpu(tw_initconnect->result);
		पूर्ण
		retval = 0;
	पूर्ण

	tw_dev->posted_request_count--;
	tw_dev->state[request_id] = TW_S_INITIAL;

	वापस retval;
पूर्ण /* End twa_initconnection() */

/* This function will initialize the fields of a device extension */
अटल पूर्णांक twa_initialize_device_extension(TW_Device_Extension *tw_dev)
अणु
	पूर्णांक i, retval = 1;

	/* Initialize command packet buffers */
	अगर (twa_allocate_memory(tw_dev, माप(TW_Command_Full), 0)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x16, "Command packet memory allocation failed");
		जाओ out;
	पूर्ण

	/* Initialize generic buffer */
	अगर (twa_allocate_memory(tw_dev, TW_SECTOR_SIZE, 1)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x17, "Generic memory allocation failed");
		जाओ out;
	पूर्ण

	/* Allocate event info space */
	tw_dev->event_queue[0] = kसुस्मृति(TW_Q_LENGTH, माप(TW_Event), GFP_KERNEL);
	अगर (!tw_dev->event_queue[0]) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x18, "Event info memory allocation failed");
		जाओ out;
	पूर्ण


	क्रम (i = 0; i < TW_Q_LENGTH; i++) अणु
		tw_dev->event_queue[i] = (TW_Event *)((अचिन्हित अक्षर *)tw_dev->event_queue[0] + (i * माप(TW_Event)));
		tw_dev->मुक्त_queue[i] = i;
		tw_dev->state[i] = TW_S_INITIAL;
	पूर्ण

	tw_dev->pending_head = TW_Q_START;
	tw_dev->pending_tail = TW_Q_START;
	tw_dev->मुक्त_head = TW_Q_START;
	tw_dev->मुक्त_tail = TW_Q_START;
	tw_dev->error_sequence_id = 1;
	tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;

	mutex_init(&tw_dev->ioctl_lock);
	init_रुकोqueue_head(&tw_dev->ioctl_wqueue);

	retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_initialize_device_extension() */

/* This function is the पूर्णांकerrupt service routine */
अटल irqवापस_t twa_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	पूर्णांक request_id, error = 0;
	u32 status_reg_value;
	TW_Response_Queue response_que;
	TW_Command_Full *full_command_packet;
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)dev_instance;
	पूर्णांक handled = 0;

	/* Get the per adapter lock */
	spin_lock(tw_dev->host->host_lock);

	/* Read the रेजिस्टरs */
	status_reg_value = पढ़ोl(TW_STATUS_REG_ADDR(tw_dev));

	/* Check अगर this is our पूर्णांकerrupt, otherwise bail */
	अगर (!(status_reg_value & TW_STATUS_VALID_INTERRUPT))
		जाओ twa_पूर्णांकerrupt_bail;

	handled = 1;

	/* If we are resetting, bail */
	अगर (test_bit(TW_IN_RESET, &tw_dev->flags))
		जाओ twa_पूर्णांकerrupt_bail;

	/* Check controller क्रम errors */
	अगर (twa_check_bits(status_reg_value)) अणु
		अगर (twa_decode_bits(tw_dev, status_reg_value)) अणु
			TW_CLEAR_ALL_INTERRUPTS(tw_dev);
			जाओ twa_पूर्णांकerrupt_bail;
		पूर्ण
	पूर्ण

	/* Handle host पूर्णांकerrupt */
	अगर (status_reg_value & TW_STATUS_HOST_INTERRUPT)
		TW_CLEAR_HOST_INTERRUPT(tw_dev);

	/* Handle attention पूर्णांकerrupt */
	अगर (status_reg_value & TW_STATUS_ATTENTION_INTERRUPT) अणु
		TW_CLEAR_ATTENTION_INTERRUPT(tw_dev);
		अगर (!(test_and_set_bit(TW_IN_ATTENTION_LOOP, &tw_dev->flags))) अणु
			twa_get_request_id(tw_dev, &request_id);

			error = twa_aen_पढ़ो_queue(tw_dev, request_id);
			अगर (error) अणु
				tw_dev->state[request_id] = TW_S_COMPLETED;
				twa_मुक्त_request_id(tw_dev, request_id);
				clear_bit(TW_IN_ATTENTION_LOOP, &tw_dev->flags);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Handle command पूर्णांकerrupt */
	अगर (status_reg_value & TW_STATUS_COMMAND_INTERRUPT) अणु
		TW_MASK_COMMAND_INTERRUPT(tw_dev);
		/* Drain as many pending commands as we can */
		जबतक (tw_dev->pending_request_count > 0) अणु
			request_id = tw_dev->pending_queue[tw_dev->pending_head];
			अगर (tw_dev->state[request_id] != TW_S_PENDING) अणु
				TW_PRINTK(tw_dev->host, TW_DRIVER, 0x19, "Found request id that wasn't pending");
				TW_CLEAR_ALL_INTERRUPTS(tw_dev);
				जाओ twa_पूर्णांकerrupt_bail;
			पूर्ण
			अगर (twa_post_command_packet(tw_dev, request_id, 1)==0) अणु
				tw_dev->pending_head = (tw_dev->pending_head + 1) % TW_Q_LENGTH;
				tw_dev->pending_request_count--;
			पूर्ण अन्यथा अणु
				/* If we get here, we will जारी re-posting on the next command पूर्णांकerrupt */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Handle response पूर्णांकerrupt */
	अगर (status_reg_value & TW_STATUS_RESPONSE_INTERRUPT) अणु

		/* Drain the response queue from the board */
		जबतक ((status_reg_value & TW_STATUS_RESPONSE_QUEUE_EMPTY) == 0) अणु
			/* Complete the response */
			response_que.value = पढ़ोl(TW_RESPONSE_QUEUE_REG_ADDR(tw_dev));
			request_id = TW_RESID_OUT(response_que.response_id);
			full_command_packet = tw_dev->command_packet_virt[request_id];
			error = 0;
			/* Check क्रम command packet errors */
			अगर (full_command_packet->command.newcommand.status != 0) अणु
				अगर (tw_dev->srb[request_id] != शून्य) अणु
					error = twa_fill_sense(tw_dev, request_id, 1, 1);
				पूर्ण अन्यथा अणु
					/* Skip ioctl error prपूर्णांकs */
					अगर (request_id != tw_dev->chrdev_request_id) अणु
						error = twa_fill_sense(tw_dev, request_id, 0, 1);
					पूर्ण
				पूर्ण
			पूर्ण

			/* Check क्रम correct state */
			अगर (tw_dev->state[request_id] != TW_S_POSTED) अणु
				अगर (tw_dev->srb[request_id] != शून्य) अणु
					TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1a, "Received a request id that wasn't posted");
					TW_CLEAR_ALL_INTERRUPTS(tw_dev);
					जाओ twa_पूर्णांकerrupt_bail;
				पूर्ण
			पूर्ण

			/* Check क्रम पूर्णांकernal command completion */
			अगर (tw_dev->srb[request_id] == शून्य) अणु
				अगर (request_id != tw_dev->chrdev_request_id) अणु
					अगर (twa_aen_complete(tw_dev, request_id))
						TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1b, "Error completing AEN during attention interrupt");
				पूर्ण अन्यथा अणु
					tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;
					wake_up(&tw_dev->ioctl_wqueue);
				पूर्ण
			पूर्ण अन्यथा अणु
				काष्ठा scsi_cmnd *cmd;

				cmd = tw_dev->srb[request_id];

				twa_scsiop_execute_scsi_complete(tw_dev, request_id);
				/* If no error command was a success */
				अगर (error == 0) अणु
					cmd->result = (DID_OK << 16);
				पूर्ण

				/* If error, command failed */
				अगर (error == 1) अणु
					/* Ask क्रम a host reset */
					cmd->result = (DID_OK << 16) | (CHECK_CONDITION << 1);
				पूर्ण

				/* Report residual bytes क्रम single sgl */
				अगर ((scsi_sg_count(cmd) <= 1) && (full_command_packet->command.newcommand.status == 0)) अणु
					अगर (full_command_packet->command.newcommand.sg_list[0].length < scsi_bufflen(tw_dev->srb[request_id]))
						scsi_set_resid(cmd, scsi_bufflen(cmd) - full_command_packet->command.newcommand.sg_list[0].length);
				पूर्ण

				/* Now complete the io */
				अगर (twa_command_mapped(cmd))
					scsi_dma_unmap(cmd);
				cmd->scsi_करोne(cmd);
				tw_dev->state[request_id] = TW_S_COMPLETED;
				twa_मुक्त_request_id(tw_dev, request_id);
				tw_dev->posted_request_count--;
			पूर्ण

			/* Check क्रम valid status after each drain */
			status_reg_value = पढ़ोl(TW_STATUS_REG_ADDR(tw_dev));
			अगर (twa_check_bits(status_reg_value)) अणु
				अगर (twa_decode_bits(tw_dev, status_reg_value)) अणु
					TW_CLEAR_ALL_INTERRUPTS(tw_dev);
					जाओ twa_पूर्णांकerrupt_bail;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

twa_पूर्णांकerrupt_bail:
	spin_unlock(tw_dev->host->host_lock);
	वापस IRQ_RETVAL(handled);
पूर्ण /* End twa_पूर्णांकerrupt() */

/* This function will load the request id and various sgls क्रम ioctls */
अटल व्योम twa_load_sgl(TW_Device_Extension *tw_dev, TW_Command_Full *full_command_packet, पूर्णांक request_id, dma_addr_t dma_handle, पूर्णांक length)
अणु
	TW_Command *oldcommand;
	TW_Command_Apache *newcommand;
	TW_SG_Entry *sgl;
	अचिन्हित पूर्णांक pae = 0;

	अगर ((माप(दीर्घ) < 8) && (माप(dma_addr_t) > 4))
		pae = 1;

	अगर (TW_OP_OUT(full_command_packet->command.newcommand.opcode__reserved) == TW_OP_EXECUTE_SCSI) अणु
		newcommand = &full_command_packet->command.newcommand;
		newcommand->request_id__lunl =
			cpu_to_le16(TW_REQ_LUN_IN(TW_LUN_OUT(newcommand->request_id__lunl), request_id));
		अगर (length) अणु
			newcommand->sg_list[0].address = TW_CPU_TO_SGL(dma_handle + माप(TW_Ioctl_Buf_Apache) - 1);
			newcommand->sg_list[0].length = cpu_to_le32(length);
		पूर्ण
		newcommand->sgl_entries__lunh =
			cpu_to_le16(TW_REQ_LUN_IN(TW_LUN_OUT(newcommand->sgl_entries__lunh), length ? 1 : 0));
	पूर्ण अन्यथा अणु
		oldcommand = &full_command_packet->command.oldcommand;
		oldcommand->request_id = request_id;

		अगर (TW_SGL_OUT(oldcommand->opcode__sgloffset)) अणु
			/* Load the sg list */
			अगर (tw_dev->tw_pci_dev->device == PCI_DEVICE_ID_3WARE_9690SA)
				sgl = (TW_SG_Entry *)((u32 *)oldcommand+oldcommand->size - (माप(TW_SG_Entry)/4) + pae);
			अन्यथा
				sgl = (TW_SG_Entry *)((u32 *)oldcommand+TW_SGL_OUT(oldcommand->opcode__sgloffset));
			sgl->address = TW_CPU_TO_SGL(dma_handle + माप(TW_Ioctl_Buf_Apache) - 1);
			sgl->length = cpu_to_le32(length);

			oldcommand->size += pae;
		पूर्ण
	पूर्ण
पूर्ण /* End twa_load_sgl() */

/* This function will poll क्रम a response पूर्णांकerrupt of a request */
अटल पूर्णांक twa_poll_response(TW_Device_Extension *tw_dev, पूर्णांक request_id, पूर्णांक seconds)
अणु
	पूर्णांक retval = 1, found = 0, response_request_id;
	TW_Response_Queue response_queue;
	TW_Command_Full *full_command_packet = tw_dev->command_packet_virt[request_id];

	अगर (twa_poll_status_gone(tw_dev, TW_STATUS_RESPONSE_QUEUE_EMPTY, seconds) == 0) अणु
		response_queue.value = पढ़ोl(TW_RESPONSE_QUEUE_REG_ADDR(tw_dev));
		response_request_id = TW_RESID_OUT(response_queue.response_id);
		अगर (request_id != response_request_id) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1e, "Found unexpected request id while polling for response");
			जाओ out;
		पूर्ण
		अगर (TW_OP_OUT(full_command_packet->command.newcommand.opcode__reserved) == TW_OP_EXECUTE_SCSI) अणु
			अगर (full_command_packet->command.newcommand.status != 0) अणु
				/* bad response */
				twa_fill_sense(tw_dev, request_id, 0, 0);
				जाओ out;
			पूर्ण
			found = 1;
		पूर्ण अन्यथा अणु
			अगर (full_command_packet->command.oldcommand.status != 0) अणु
				/* bad response */
				twa_fill_sense(tw_dev, request_id, 0, 0);
				जाओ out;
			पूर्ण
			found = 1;
		पूर्ण
	पूर्ण

	अगर (found)
		retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_poll_response() */

/* This function will poll the status रेजिस्टर क्रम a flag */
अटल पूर्णांक twa_poll_status(TW_Device_Extension *tw_dev, u32 flag, पूर्णांक seconds)
अणु
	u32 status_reg_value;
	अचिन्हित दीर्घ beक्रमe;
	पूर्णांक retval = 1;

	status_reg_value = पढ़ोl(TW_STATUS_REG_ADDR(tw_dev));
	beक्रमe = jअगरfies;

	अगर (twa_check_bits(status_reg_value))
		twa_decode_bits(tw_dev, status_reg_value);

	जबतक ((status_reg_value & flag) != flag) अणु
		status_reg_value = पढ़ोl(TW_STATUS_REG_ADDR(tw_dev));

		अगर (twa_check_bits(status_reg_value))
			twa_decode_bits(tw_dev, status_reg_value);

		अगर (समय_after(jअगरfies, beक्रमe + HZ * seconds))
			जाओ out;

		msleep(50);
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_poll_status() */

/* This function will poll the status रेजिस्टर क्रम disappearance of a flag */
अटल पूर्णांक twa_poll_status_gone(TW_Device_Extension *tw_dev, u32 flag, पूर्णांक seconds)
अणु
	u32 status_reg_value;
	अचिन्हित दीर्घ beक्रमe;
	पूर्णांक retval = 1;

	status_reg_value = पढ़ोl(TW_STATUS_REG_ADDR(tw_dev));
	beक्रमe = jअगरfies;

	अगर (twa_check_bits(status_reg_value))
		twa_decode_bits(tw_dev, status_reg_value);

	जबतक ((status_reg_value & flag) != 0) अणु
		status_reg_value = पढ़ोl(TW_STATUS_REG_ADDR(tw_dev));
		अगर (twa_check_bits(status_reg_value))
			twa_decode_bits(tw_dev, status_reg_value);

		अगर (समय_after(jअगरfies, beक्रमe + HZ * seconds))
			जाओ out;

		msleep(50);
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_poll_status_gone() */

/* This function will attempt to post a command packet to the board */
अटल पूर्णांक twa_post_command_packet(TW_Device_Extension *tw_dev, पूर्णांक request_id, अक्षर पूर्णांकernal)
अणु
	u32 status_reg_value;
	dma_addr_t command_que_value;
	पूर्णांक retval = 1;

	command_que_value = tw_dev->command_packet_phys[request_id];

	/* For 9650SE ग_लिखो low 4 bytes first */
	अगर ((tw_dev->tw_pci_dev->device == PCI_DEVICE_ID_3WARE_9650SE) ||
	    (tw_dev->tw_pci_dev->device == PCI_DEVICE_ID_3WARE_9690SA)) अणु
		command_que_value += TW_COMMAND_OFFSET;
		ग_लिखोl((u32)command_que_value, TW_COMMAND_QUEUE_REG_ADDR_LARGE(tw_dev));
	पूर्ण

	status_reg_value = पढ़ोl(TW_STATUS_REG_ADDR(tw_dev));

	अगर (twa_check_bits(status_reg_value))
		twa_decode_bits(tw_dev, status_reg_value);

	अगर (((tw_dev->pending_request_count > 0) && (tw_dev->state[request_id] != TW_S_PENDING)) || (status_reg_value & TW_STATUS_COMMAND_QUEUE_FULL)) अणु

		/* Only pend पूर्णांकernal driver commands */
		अगर (!पूर्णांकernal) अणु
			retval = SCSI_MLQUEUE_HOST_BUSY;
			जाओ out;
		पूर्ण

		/* Couldn't post the command packet, so we करो it later */
		अगर (tw_dev->state[request_id] != TW_S_PENDING) अणु
			tw_dev->state[request_id] = TW_S_PENDING;
			tw_dev->pending_request_count++;
			अगर (tw_dev->pending_request_count > tw_dev->max_pending_request_count) अणु
				tw_dev->max_pending_request_count = tw_dev->pending_request_count;
			पूर्ण
			tw_dev->pending_queue[tw_dev->pending_tail] = request_id;
			tw_dev->pending_tail = (tw_dev->pending_tail + 1) % TW_Q_LENGTH;
		पूर्ण
		TW_UNMASK_COMMAND_INTERRUPT(tw_dev);
		जाओ out;
	पूर्ण अन्यथा अणु
		अगर ((tw_dev->tw_pci_dev->device == PCI_DEVICE_ID_3WARE_9650SE) ||
		    (tw_dev->tw_pci_dev->device == PCI_DEVICE_ID_3WARE_9690SA)) अणु
			/* Now ग_लिखो upper 4 bytes */
			ग_लिखोl((u32)((u64)command_que_value >> 32), TW_COMMAND_QUEUE_REG_ADDR_LARGE(tw_dev) + 0x4);
		पूर्ण अन्यथा अणु
			अगर (माप(dma_addr_t) > 4) अणु
				command_que_value += TW_COMMAND_OFFSET;
				ग_लिखोl((u32)command_que_value, TW_COMMAND_QUEUE_REG_ADDR(tw_dev));
				ग_लिखोl((u32)((u64)command_que_value >> 32), TW_COMMAND_QUEUE_REG_ADDR(tw_dev) + 0x4);
			पूर्ण अन्यथा अणु
				ग_लिखोl(TW_COMMAND_OFFSET + command_que_value, TW_COMMAND_QUEUE_REG_ADDR(tw_dev));
			पूर्ण
		पूर्ण
		tw_dev->state[request_id] = TW_S_POSTED;
		tw_dev->posted_request_count++;
		अगर (tw_dev->posted_request_count > tw_dev->max_posted_request_count) अणु
			tw_dev->max_posted_request_count = tw_dev->posted_request_count;
		पूर्ण
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_post_command_packet() */

/* This function will reset a device extension */
अटल पूर्णांक twa_reset_device_extension(TW_Device_Extension *tw_dev)
अणु
	पूर्णांक i = 0;
	पूर्णांक retval = 1;
	अचिन्हित दीर्घ flags = 0;

	set_bit(TW_IN_RESET, &tw_dev->flags);
	TW_DISABLE_INTERRUPTS(tw_dev);
	TW_MASK_COMMAND_INTERRUPT(tw_dev);
	spin_lock_irqsave(tw_dev->host->host_lock, flags);

	/* Abort all requests that are in progress */
	क्रम (i = 0; i < TW_Q_LENGTH; i++) अणु
		अगर ((tw_dev->state[i] != TW_S_FINISHED) &&
		    (tw_dev->state[i] != TW_S_INITIAL) &&
		    (tw_dev->state[i] != TW_S_COMPLETED)) अणु
			अगर (tw_dev->srb[i]) अणु
				काष्ठा scsi_cmnd *cmd = tw_dev->srb[i];

				cmd->result = (DID_RESET << 16);
				अगर (twa_command_mapped(cmd))
					scsi_dma_unmap(cmd);
				cmd->scsi_करोne(cmd);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Reset queues and counts */
	क्रम (i = 0; i < TW_Q_LENGTH; i++) अणु
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

	अगर (twa_reset_sequence(tw_dev, 1))
		जाओ out;

	TW_ENABLE_AND_CLEAR_INTERRUPTS(tw_dev);
	clear_bit(TW_IN_RESET, &tw_dev->flags);
	tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;

	retval = 0;
out:
	वापस retval;
पूर्ण /* End twa_reset_device_extension() */

/* This function will reset a controller */
अटल पूर्णांक twa_reset_sequence(TW_Device_Extension *tw_dev, पूर्णांक soft_reset)
अणु
	पूर्णांक tries = 0, retval = 1, flashed = 0, करो_soft_reset = soft_reset;

	जबतक (tries < TW_MAX_RESET_TRIES) अणु
		अगर (करो_soft_reset) अणु
			TW_SOFT_RESET(tw_dev);
			/* Clear pchip/response queue on 9550SX */
			अगर (twa_empty_response_queue_large(tw_dev)) अणु
				TW_PRINTK(tw_dev->host, TW_DRIVER, 0x36, "Response queue (large) empty failed during reset sequence");
				करो_soft_reset = 1;
				tries++;
				जारी;
			पूर्ण
		पूर्ण

		/* Make sure controller is in a good state */
		अगर (twa_poll_status(tw_dev, TW_STATUS_MICROCONTROLLER_READY | (करो_soft_reset == 1 ? TW_STATUS_ATTENTION_INTERRUPT : 0), 60)) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1f, "Microcontroller not ready during reset sequence");
			करो_soft_reset = 1;
			tries++;
			जारी;
		पूर्ण

		/* Empty response queue */
		अगर (twa_empty_response_queue(tw_dev)) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x20, "Response queue empty failed during reset sequence");
			करो_soft_reset = 1;
			tries++;
			जारी;
		पूर्ण

		flashed = 0;

		/* Check क्रम compatibility/flash */
		अगर (twa_check_srl(tw_dev, &flashed)) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x21, "Compatibility check failed during reset sequence");
			करो_soft_reset = 1;
			tries++;
			जारी;
		पूर्ण अन्यथा अणु
			अगर (flashed) अणु
				tries++;
				जारी;
			पूर्ण
		पूर्ण

		/* Drain the AEN queue */
		अगर (twa_aen_drain_queue(tw_dev, soft_reset)) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x22, "AEN drain failed during reset sequence");
			करो_soft_reset = 1;
			tries++;
			जारी;
		पूर्ण

		/* If we got here, controller is in a good state */
		retval = 0;
		जाओ out;
	पूर्ण
out:
	वापस retval;
पूर्ण /* End twa_reset_sequence() */

/* This funciton वापसs unit geometry in cylinders/heads/sectors */
अटल पूर्णांक twa_scsi_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev, sector_t capacity, पूर्णांक geom[])
अणु
	पूर्णांक heads, sectors, cylinders;

	अगर (capacity >= 0x200000) अणु
		heads = 255;
		sectors = 63;
		cylinders = sector_भाग(capacity, heads * sectors);
	पूर्ण अन्यथा अणु
		heads = 64;
		sectors = 32;
		cylinders = sector_भाग(capacity, heads * sectors);
	पूर्ण

	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = cylinders;

	वापस 0;
पूर्ण /* End twa_scsi_biosparam() */

/* This is the new scsi eh reset function */
अटल पूर्णांक twa_scsi_eh_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	TW_Device_Extension *tw_dev = शून्य;
	पूर्णांक retval = FAILED;

	tw_dev = (TW_Device_Extension *)SCpnt->device->host->hostdata;

	tw_dev->num_resets++;

	sdev_prपूर्णांकk(KERN_WARNING, SCpnt->device,
		"WARNING: (0x%02X:0x%04X): Command (0x%x) timed out, resetting card.\n",
		TW_DRIVER, 0x2c, SCpnt->cmnd[0]);

	/* Make sure we are not issuing an ioctl or resetting from ioctl */
	mutex_lock(&tw_dev->ioctl_lock);

	/* Now reset the card and some of the device extension data */
	अगर (twa_reset_device_extension(tw_dev)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x2b, "Controller reset failed during scsi host reset");
		जाओ out;
	पूर्ण

	retval = SUCCESS;
out:
	mutex_unlock(&tw_dev->ioctl_lock);
	वापस retval;
पूर्ण /* End twa_scsi_eh_reset() */

/* This is the मुख्य scsi queue function to handle scsi opcodes */
अटल पूर्णांक twa_scsi_queue_lck(काष्ठा scsi_cmnd *SCpnt, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	पूर्णांक request_id, retval;
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)SCpnt->device->host->hostdata;

	/* If we are resetting due to समयd out ioctl, report as busy */
	अगर (test_bit(TW_IN_RESET, &tw_dev->flags)) अणु
		retval = SCSI_MLQUEUE_HOST_BUSY;
		जाओ out;
	पूर्ण

	/* Check अगर this FW supports luns */
	अगर ((SCpnt->device->lun != 0) && (tw_dev->tw_compat_info.working_srl < TW_FW_SRL_LUNS_SUPPORTED)) अणु
		SCpnt->result = (DID_BAD_TARGET << 16);
		करोne(SCpnt);
		retval = 0;
		जाओ out;
	पूर्ण

	/* Save करोne function पूर्णांकo scsi_cmnd काष्ठा */
	SCpnt->scsi_करोne = करोne;

	/* Get a मुक्त request id */
	twa_get_request_id(tw_dev, &request_id);

	/* Save the scsi command क्रम use by the ISR */
	tw_dev->srb[request_id] = SCpnt;

	retval = twa_scsiop_execute_scsi(tw_dev, request_id, शून्य, 0, शून्य);
	चयन (retval) अणु
	हाल SCSI_MLQUEUE_HOST_BUSY:
		अगर (twa_command_mapped(SCpnt))
			scsi_dma_unmap(SCpnt);
		twa_मुक्त_request_id(tw_dev, request_id);
		अवरोध;
	हाल 1:
		SCpnt->result = (DID_ERROR << 16);
		अगर (twa_command_mapped(SCpnt))
			scsi_dma_unmap(SCpnt);
		करोne(SCpnt);
		tw_dev->state[request_id] = TW_S_COMPLETED;
		twa_मुक्त_request_id(tw_dev, request_id);
		retval = 0;
	पूर्ण
out:
	वापस retval;
पूर्ण /* End twa_scsi_queue() */

अटल DEF_SCSI_QCMD(twa_scsi_queue)

/* This function hands scsi cdb's to the firmware */
अटल पूर्णांक twa_scsiop_execute_scsi(TW_Device_Extension *tw_dev, पूर्णांक request_id,
				   अचिन्हित अक्षर *cdb, पूर्णांक use_sg,
				   TW_SG_Entry *sglistarg)
अणु
	TW_Command_Full *full_command_packet;
	TW_Command_Apache *command_packet;
	u32 num_sectors = 0x0;
	पूर्णांक i, sg_count;
	काष्ठा scsi_cmnd *srb = शून्य;
	काष्ठा scatterlist *sg;
	पूर्णांक retval = 1;

	अगर (tw_dev->srb[request_id])
		srb = tw_dev->srb[request_id];

	/* Initialize command packet */
	full_command_packet = tw_dev->command_packet_virt[request_id];
	full_command_packet->header.header_desc.size_header = 128;
	full_command_packet->header.status_block.error = 0;
	full_command_packet->header.status_block.severity__reserved = 0;

	command_packet = &full_command_packet->command.newcommand;
	command_packet->status = 0;
	command_packet->opcode__reserved = TW_OPRES_IN(0, TW_OP_EXECUTE_SCSI);

	/* We क्रमced 16 byte cdb use earlier */
	अगर (!cdb)
		स_नकल(command_packet->cdb, srb->cmnd, TW_MAX_CDB_LEN);
	अन्यथा
		स_नकल(command_packet->cdb, cdb, TW_MAX_CDB_LEN);

	अगर (srb) अणु
		command_packet->unit = srb->device->id;
		command_packet->request_id__lunl =
			cpu_to_le16(TW_REQ_LUN_IN(srb->device->lun, request_id));
	पूर्ण अन्यथा अणु
		command_packet->request_id__lunl =
			cpu_to_le16(TW_REQ_LUN_IN(0, request_id));
		command_packet->unit = 0;
	पूर्ण

	command_packet->sgl_offset = 16;

	अगर (!sglistarg) अणु
		/* Map sglist from scsi layer to cmd packet */

		अगर (scsi_sg_count(srb)) अणु
			अगर (!twa_command_mapped(srb)) अणु
				अगर (srb->sc_data_direction == DMA_TO_DEVICE ||
				    srb->sc_data_direction == DMA_BIसूचीECTIONAL)
					scsi_sg_copy_to_buffer(srb,
							       tw_dev->generic_buffer_virt[request_id],
							       TW_SECTOR_SIZE);
				command_packet->sg_list[0].address = TW_CPU_TO_SGL(tw_dev->generic_buffer_phys[request_id]);
				command_packet->sg_list[0].length = cpu_to_le32(TW_MIN_SGL_LENGTH);
			पूर्ण अन्यथा अणु
				sg_count = scsi_dma_map(srb);
				अगर (sg_count < 0)
					जाओ out;

				scsi_क्रम_each_sg(srb, sg, sg_count, i) अणु
					command_packet->sg_list[i].address = TW_CPU_TO_SGL(sg_dma_address(sg));
					command_packet->sg_list[i].length = cpu_to_le32(sg_dma_len(sg));
					अगर (command_packet->sg_list[i].address & TW_CPU_TO_SGL(TW_ALIGNMENT_9000_SGL)) अणु
						TW_PRINTK(tw_dev->host, TW_DRIVER, 0x2e, "Found unaligned sgl address during execute scsi");
						जाओ out;
					पूर्ण
				पूर्ण
			पूर्ण
			command_packet->sgl_entries__lunh = cpu_to_le16(TW_REQ_LUN_IN((srb->device->lun >> 4), scsi_sg_count(tw_dev->srb[request_id])));
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Internal cdb post */
		क्रम (i = 0; i < use_sg; i++) अणु
			command_packet->sg_list[i].address = TW_CPU_TO_SGL(sglistarg[i].address);
			command_packet->sg_list[i].length = cpu_to_le32(sglistarg[i].length);
			अगर (command_packet->sg_list[i].address & TW_CPU_TO_SGL(TW_ALIGNMENT_9000_SGL)) अणु
				TW_PRINTK(tw_dev->host, TW_DRIVER, 0x2f, "Found unaligned sgl address during internal post");
				जाओ out;
			पूर्ण
		पूर्ण
		command_packet->sgl_entries__lunh = cpu_to_le16(TW_REQ_LUN_IN(0, use_sg));
	पूर्ण

	अगर (srb) अणु
		अगर (srb->cmnd[0] == READ_6 || srb->cmnd[0] == WRITE_6)
			num_sectors = (u32)srb->cmnd[4];

		अगर (srb->cmnd[0] == READ_10 || srb->cmnd[0] == WRITE_10)
			num_sectors = (u32)srb->cmnd[8] | ((u32)srb->cmnd[7] << 8);
	पूर्ण

	/* Update sector statistic */
	tw_dev->sector_count = num_sectors;
	अगर (tw_dev->sector_count > tw_dev->max_sector_count)
		tw_dev->max_sector_count = tw_dev->sector_count;

	/* Update SG statistics */
	अगर (srb) अणु
		tw_dev->sgl_entries = scsi_sg_count(tw_dev->srb[request_id]);
		अगर (tw_dev->sgl_entries > tw_dev->max_sgl_entries)
			tw_dev->max_sgl_entries = tw_dev->sgl_entries;
	पूर्ण

	/* Now post the command to the board */
	अगर (srb) अणु
		retval = twa_post_command_packet(tw_dev, request_id, 0);
	पूर्ण अन्यथा अणु
		twa_post_command_packet(tw_dev, request_id, 1);
		retval = 0;
	पूर्ण
out:
	वापस retval;
पूर्ण /* End twa_scsiop_execute_scsi() */

/* This function completes an execute scsi operation */
अटल व्योम twa_scsiop_execute_scsi_complete(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	काष्ठा scsi_cmnd *cmd = tw_dev->srb[request_id];

	अगर (!twa_command_mapped(cmd) &&
	    (cmd->sc_data_direction == DMA_FROM_DEVICE ||
	     cmd->sc_data_direction == DMA_BIसूचीECTIONAL)) अणु
		अगर (scsi_sg_count(cmd) == 1) अणु
			व्योम *buf = tw_dev->generic_buffer_virt[request_id];

			scsi_sg_copy_from_buffer(cmd, buf, TW_SECTOR_SIZE);
		पूर्ण
	पूर्ण
पूर्ण /* End twa_scsiop_execute_scsi_complete() */

/* This function tells the controller to shut करोwn */
अटल व्योम __twa_shutकरोwn(TW_Device_Extension *tw_dev)
अणु
	/* Disable पूर्णांकerrupts */
	TW_DISABLE_INTERRUPTS(tw_dev);

	/* Free up the IRQ */
	मुक्त_irq(tw_dev->tw_pci_dev->irq, tw_dev);

	prपूर्णांकk(KERN_WARNING "3w-9xxx: Shutting down host %d.\n", tw_dev->host->host_no);

	/* Tell the card we are shutting करोwn */
	अगर (twa_initconnection(tw_dev, 1, 0, 0, 0, 0, 0, शून्य, शून्य, शून्य, शून्य, शून्य)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x31, "Connection shutdown failed");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "3w-9xxx: Shutdown complete.\n");
	पूर्ण

	/* Clear all पूर्णांकerrupts just beक्रमe निकास */
	TW_CLEAR_ALL_INTERRUPTS(tw_dev);
पूर्ण /* End __twa_shutकरोwn() */

/* Wrapper क्रम __twa_shutकरोwn */
अटल व्योम twa_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;

	__twa_shutकरोwn(tw_dev);
पूर्ण /* End twa_shutकरोwn() */

/* This function will look up a string */
अटल अक्षर *twa_string_lookup(twa_message_type *table, अचिन्हित पूर्णांक code)
अणु
	पूर्णांक index;

	क्रम (index = 0; ((code != table[index].code) &&
		      (table[index].text != (अक्षर *)0)); index++);
	वापस(table[index].text);
पूर्ण /* End twa_string_lookup() */

/* This function माला_लो called when a disk is coming on-line */
अटल पूर्णांक twa_slave_configure(काष्ठा scsi_device *sdev)
अणु
	/* Force 60 second समयout */
	blk_queue_rq_समयout(sdev->request_queue, 60 * HZ);

	वापस 0;
पूर्ण /* End twa_slave_configure() */

/* scsi_host_ढाँचा initializer */
अटल काष्ठा scsi_host_ढाँचा driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "3ware 9000 Storage Controller",
	.queuecommand		= twa_scsi_queue,
	.eh_host_reset_handler	= twa_scsi_eh_reset,
	.bios_param		= twa_scsi_biosparam,
	.change_queue_depth	= scsi_change_queue_depth,
	.can_queue		= TW_Q_LENGTH-2,
	.slave_configure	= twa_slave_configure,
	.this_id		= -1,
	.sg_tablesize		= TW_APACHE_MAX_SGL_LENGTH,
	.max_sectors		= TW_MAX_SECTORS,
	.cmd_per_lun		= TW_MAX_CMDS_PER_LUN,
	.shost_attrs		= twa_host_attrs,
	.emulated		= 1,
	.no_ग_लिखो_same		= 1,
पूर्ण;

/* This function will probe and initialize a card */
अटल पूर्णांक twa_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *dev_id)
अणु
	काष्ठा Scsi_Host *host = शून्य;
	TW_Device_Extension *tw_dev;
	अचिन्हित दीर्घ mem_addr, mem_len;
	पूर्णांक retval;

	retval = pci_enable_device(pdev);
	अगर (retval) अणु
		TW_PRINTK(host, TW_DRIVER, 0x34, "Failed to enable pci device");
		जाओ out_disable_device;
	पूर्ण

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	retval = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (retval)
		retval = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (retval) अणु
		TW_PRINTK(host, TW_DRIVER, 0x23, "Failed to set dma mask");
		retval = -ENODEV;
		जाओ out_disable_device;
	पूर्ण

	host = scsi_host_alloc(&driver_ढाँचा, माप(TW_Device_Extension));
	अगर (!host) अणु
		TW_PRINTK(host, TW_DRIVER, 0x24, "Failed to allocate memory for device extension");
		retval = -ENOMEM;
		जाओ out_disable_device;
	पूर्ण
	tw_dev = (TW_Device_Extension *)host->hostdata;

	/* Save values to device extension */
	tw_dev->host = host;
	tw_dev->tw_pci_dev = pdev;

	अगर (twa_initialize_device_extension(tw_dev)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x25, "Failed to initialize device extension");
		retval = -ENOMEM;
		जाओ out_मुक्त_device_extension;
	पूर्ण

	/* Request IO regions */
	retval = pci_request_regions(pdev, "3w-9xxx");
	अगर (retval) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x26, "Failed to get mem region");
		जाओ out_मुक्त_device_extension;
	पूर्ण

	अगर (pdev->device == PCI_DEVICE_ID_3WARE_9000) अणु
		mem_addr = pci_resource_start(pdev, 1);
		mem_len = pci_resource_len(pdev, 1);
	पूर्ण अन्यथा अणु
		mem_addr = pci_resource_start(pdev, 2);
		mem_len = pci_resource_len(pdev, 2);
	पूर्ण

	/* Save base address */
	tw_dev->base_addr = ioremap(mem_addr, mem_len);
	अगर (!tw_dev->base_addr) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x35, "Failed to ioremap");
		retval = -ENOMEM;
		जाओ out_release_mem_region;
	पूर्ण

	/* Disable पूर्णांकerrupts on the card */
	TW_DISABLE_INTERRUPTS(tw_dev);

	/* Initialize the card */
	अगर (twa_reset_sequence(tw_dev, 0)) अणु
		retval = -ENOMEM;
		जाओ out_iounmap;
	पूर्ण

	/* Set host specअगरic parameters */
	अगर ((pdev->device == PCI_DEVICE_ID_3WARE_9650SE) ||
	    (pdev->device == PCI_DEVICE_ID_3WARE_9690SA))
		host->max_id = TW_MAX_UNITS_9650SE;
	अन्यथा
		host->max_id = TW_MAX_UNITS;

	host->max_cmd_len = TW_MAX_CDB_LEN;

	/* Channels aren't supported by adapter */
	host->max_lun = TW_MAX_LUNS(tw_dev->tw_compat_info.working_srl);
	host->max_channel = 0;

	/* Register the card with the kernel SCSI layer */
	retval = scsi_add_host(host, &pdev->dev);
	अगर (retval) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x27, "scsi add host failed");
		जाओ out_iounmap;
	पूर्ण

	pci_set_drvdata(pdev, host);

	prपूर्णांकk(KERN_WARNING "3w-9xxx: scsi%d: Found a 3ware 9000 Storage Controller at 0x%lx, IRQ: %d.\n",
	       host->host_no, mem_addr, pdev->irq);
	prपूर्णांकk(KERN_WARNING "3w-9xxx: scsi%d: Firmware %s, BIOS %s, Ports: %d.\n",
	       host->host_no,
	       (अक्षर *)twa_get_param(tw_dev, 0, TW_VERSION_TABLE,
				     TW_PARAM_FWVER, TW_PARAM_FWVER_LENGTH),
	       (अक्षर *)twa_get_param(tw_dev, 1, TW_VERSION_TABLE,
				     TW_PARAM_BIOSVER, TW_PARAM_BIOSVER_LENGTH),
	       le32_to_cpu(*(पूर्णांक *)twa_get_param(tw_dev, 2, TW_INFORMATION_TABLE,
				     TW_PARAM_PORTCOUNT, TW_PARAM_PORTCOUNT_LENGTH)));

	/* Try to enable MSI */
	अगर (use_msi && (pdev->device != PCI_DEVICE_ID_3WARE_9000) &&
	    !pci_enable_msi(pdev))
		set_bit(TW_USING_MSI, &tw_dev->flags);

	/* Now setup the पूर्णांकerrupt handler */
	retval = request_irq(pdev->irq, twa_पूर्णांकerrupt, IRQF_SHARED, "3w-9xxx", tw_dev);
	अगर (retval) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x30, "Error requesting IRQ");
		जाओ out_हटाओ_host;
	पूर्ण

	twa_device_extension_list[twa_device_extension_count] = tw_dev;
	twa_device_extension_count++;

	/* Re-enable पूर्णांकerrupts on the card */
	TW_ENABLE_AND_CLEAR_INTERRUPTS(tw_dev);

	/* Finally, scan the host */
	scsi_scan_host(host);

	अगर (twa_major == -1) अणु
		अगर ((twa_major = रेजिस्टर_chrdev (0, "twa", &twa_fops)) < 0)
			TW_PRINTK(host, TW_DRIVER, 0x29, "Failed to register character device");
	पूर्ण
	वापस 0;

out_हटाओ_host:
	अगर (test_bit(TW_USING_MSI, &tw_dev->flags))
		pci_disable_msi(pdev);
	scsi_हटाओ_host(host);
out_iounmap:
	iounmap(tw_dev->base_addr);
out_release_mem_region:
	pci_release_regions(pdev);
out_मुक्त_device_extension:
	twa_मुक्त_device_extension(tw_dev);
	scsi_host_put(host);
out_disable_device:
	pci_disable_device(pdev);

	वापस retval;
पूर्ण /* End twa_probe() */

/* This function is called to हटाओ a device */
अटल व्योम twa_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;

	scsi_हटाओ_host(tw_dev->host);

	/* Unरेजिस्टर अक्षरacter device */
	अगर (twa_major >= 0) अणु
		unरेजिस्टर_chrdev(twa_major, "twa");
		twa_major = -1;
	पूर्ण

	/* Shutकरोwn the card */
	__twa_shutकरोwn(tw_dev);

	/* Disable MSI अगर enabled */
	अगर (test_bit(TW_USING_MSI, &tw_dev->flags))
		pci_disable_msi(pdev);

	/* Free IO remapping */
	iounmap(tw_dev->base_addr);

	/* Free up the mem region */
	pci_release_regions(pdev);

	/* Free up device extension resources */
	twa_मुक्त_device_extension(tw_dev);

	scsi_host_put(tw_dev->host);
	pci_disable_device(pdev);
	twa_device_extension_count--;
पूर्ण /* End twa_हटाओ() */

/* This function is called on PCI suspend */
अटल पूर्णांक __maybe_unused twa_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;

	prपूर्णांकk(KERN_WARNING "3w-9xxx: Suspending host %d.\n", tw_dev->host->host_no);

	TW_DISABLE_INTERRUPTS(tw_dev);
	मुक्त_irq(tw_dev->tw_pci_dev->irq, tw_dev);

	अगर (test_bit(TW_USING_MSI, &tw_dev->flags))
		pci_disable_msi(pdev);

	/* Tell the card we are shutting करोwn */
	अगर (twa_initconnection(tw_dev, 1, 0, 0, 0, 0, 0, शून्य, शून्य, शून्य, शून्य, शून्य)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x38, "Connection shutdown failed during suspend");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "3w-9xxx: Suspend complete.\n");
	पूर्ण
	TW_CLEAR_ALL_INTERRUPTS(tw_dev);

	वापस 0;
पूर्ण /* End twa_suspend() */

/* This function is called on PCI resume */
अटल पूर्णांक __maybe_unused twa_resume(काष्ठा device *dev)
अणु
	पूर्णांक retval = 0;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;

	prपूर्णांकk(KERN_WARNING "3w-9xxx: Resuming host %d.\n", tw_dev->host->host_no);

	pci_try_set_mwi(pdev);

	retval = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (retval)
		retval = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (retval) अणु
		TW_PRINTK(host, TW_DRIVER, 0x40, "Failed to set dma mask during resume");
		retval = -ENODEV;
		जाओ out_disable_device;
	पूर्ण

	/* Initialize the card */
	अगर (twa_reset_sequence(tw_dev, 0)) अणु
		retval = -ENODEV;
		जाओ out_disable_device;
	पूर्ण

	/* Now setup the पूर्णांकerrupt handler */
	retval = request_irq(pdev->irq, twa_पूर्णांकerrupt, IRQF_SHARED, "3w-9xxx", tw_dev);
	अगर (retval) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x42, "Error requesting IRQ during resume");
		retval = -ENODEV;
		जाओ out_disable_device;
	पूर्ण

	/* Now enable MSI अगर enabled */
	अगर (test_bit(TW_USING_MSI, &tw_dev->flags))
		pci_enable_msi(pdev);

	/* Re-enable पूर्णांकerrupts on the card */
	TW_ENABLE_AND_CLEAR_INTERRUPTS(tw_dev);

	prपूर्णांकk(KERN_WARNING "3w-9xxx: Resume complete.\n");
	वापस 0;

out_disable_device:
	scsi_हटाओ_host(host);

	वापस retval;
पूर्ण /* End twa_resume() */

/* PCI Devices supported by this driver */
अटल काष्ठा pci_device_id twa_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_3WARE, PCI_DEVICE_ID_3WARE_9000,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु PCI_VENDOR_ID_3WARE, PCI_DEVICE_ID_3WARE_9550SX,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु PCI_VENDOR_ID_3WARE, PCI_DEVICE_ID_3WARE_9650SE,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु PCI_VENDOR_ID_3WARE, PCI_DEVICE_ID_3WARE_9690SA,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, twa_pci_tbl);

अटल SIMPLE_DEV_PM_OPS(twa_pm_ops, twa_suspend, twa_resume);

/* pci_driver initializer */
अटल काष्ठा pci_driver twa_driver = अणु
	.name		= "3w-9xxx",
	.id_table	= twa_pci_tbl,
	.probe		= twa_probe,
	.हटाओ		= twa_हटाओ,
	.driver.pm	= &twa_pm_ops,
	.shutकरोwn	= twa_shutकरोwn
पूर्ण;

/* This function is called on driver initialization */
अटल पूर्णांक __init twa_init(व्योम)
अणु
	prपूर्णांकk(KERN_WARNING "3ware 9000 Storage Controller device driver for Linux v%s.\n", TW_DRIVER_VERSION);

	वापस pci_रेजिस्टर_driver(&twa_driver);
पूर्ण /* End twa_init() */

/* This function is called on driver निकास */
अटल व्योम __निकास twa_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&twa_driver);
पूर्ण /* End twa_निकास() */

module_init(twa_init);
module_निकास(twa_निकास);

