<शैली गुरु>
/*
   3w-sas.c -- LSI 3ware SAS/SATA-RAID Controller device driver क्रम Linux.

   Written By: Adam Radक्रमd <aradक्रमd@gmail.com>

   Copyright (C) 2009 LSI Corporation.

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

   Controllers supported by this driver:

   LSI 3ware 9750 6Gb/s SAS/SATA-RAID

   Bugs/Comments/Suggestions should be mailed to:
   aradक्रमd@gmail.com

   History
   -------
   3.26.02.000 - Initial driver release.
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
#समावेश "3w-sas.h"

/* Globals */
#घोषणा TW_DRIVER_VERSION "3.26.02.000"
अटल DEFINE_MUTEX(twl_chrdev_mutex);
अटल TW_Device_Extension *twl_device_extension_list[TW_MAX_SLOT];
अटल अचिन्हित पूर्णांक twl_device_extension_count;
अटल पूर्णांक twl_major = -1;
बाह्य काष्ठा समयzone sys_tz;

/* Module parameters */
MODULE_AUTHOR ("LSI");
MODULE_DESCRIPTION ("LSI 3ware SAS/SATA-RAID Linux Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(TW_DRIVER_VERSION);

अटल पूर्णांक use_msi;
module_param(use_msi, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(use_msi, "Use Message Signaled Interrupts. Default: 0");

/* Function prototypes */
अटल पूर्णांक twl_reset_device_extension(TW_Device_Extension *tw_dev, पूर्णांक ioctl_reset);

/* Functions */

/* This function वापसs AENs through sysfs */
अटल sमाप_प्रकार twl_sysfs_aen_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				  काष्ठा bin_attribute *bin_attr,
				  अक्षर *outbuf, loff_t offset, माप_प्रकार count)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)shost->hostdata;
	अचिन्हित दीर्घ flags = 0;
	sमाप_प्रकार ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	spin_lock_irqsave(tw_dev->host->host_lock, flags);
	ret = memory_पढ़ो_from_buffer(outbuf, count, &offset, tw_dev->event_queue[0], माप(TW_Event) * TW_Q_LENGTH);
	spin_unlock_irqrestore(tw_dev->host->host_lock, flags);

	वापस ret;
पूर्ण /* End twl_sysfs_aen_पढ़ो() */

/* aen_पढ़ो sysfs attribute initializer */
अटल काष्ठा bin_attribute twl_sysfs_aen_पढ़ो_attr = अणु
	.attr = अणु
		.name = "3ware_aen_read",
		.mode = S_IRUSR,
	पूर्ण,
	.size = 0,
	.पढ़ो = twl_sysfs_aen_पढ़ो
पूर्ण;

/* This function वापसs driver compatibility info through sysfs */
अटल sमाप_प्रकार twl_sysfs_compat_info(काष्ठा file *filp, काष्ठा kobject *kobj,
				     काष्ठा bin_attribute *bin_attr,
				     अक्षर *outbuf, loff_t offset, माप_प्रकार count)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)shost->hostdata;
	अचिन्हित दीर्घ flags = 0;
	sमाप_प्रकार ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	spin_lock_irqsave(tw_dev->host->host_lock, flags);
	ret = memory_पढ़ो_from_buffer(outbuf, count, &offset, &tw_dev->tw_compat_info, माप(TW_Compatibility_Info));
	spin_unlock_irqrestore(tw_dev->host->host_lock, flags);

	वापस ret;
पूर्ण /* End twl_sysfs_compat_info() */

/* compat_info sysfs attribute initializer */
अटल काष्ठा bin_attribute twl_sysfs_compat_info_attr = अणु
	.attr = अणु
		.name = "3ware_compat_info",
		.mode = S_IRUSR,
	पूर्ण,
	.size = 0,
	.पढ़ो = twl_sysfs_compat_info
पूर्ण;

/* Show some statistics about the card */
अटल sमाप_प्रकार twl_show_stats(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;
	अचिन्हित दीर्घ flags = 0;
	sमाप_प्रकार len;

	spin_lock_irqsave(tw_dev->host->host_lock, flags);
	len = snम_लिखो(buf, PAGE_SIZE, "3w-sas Driver version: %s\n"
		       "Current commands posted:   %4d\n"
		       "Max commands posted:       %4d\n"
		       "Last sgl length:           %4d\n"
		       "Max sgl length:            %4d\n"
		       "Last sector count:         %4d\n"
		       "Max sector count:          %4d\n"
		       "SCSI Host Resets:          %4d\n"
		       "AEN's:                     %4d\n",
		       TW_DRIVER_VERSION,
		       tw_dev->posted_request_count,
		       tw_dev->max_posted_request_count,
		       tw_dev->sgl_entries,
		       tw_dev->max_sgl_entries,
		       tw_dev->sector_count,
		       tw_dev->max_sector_count,
		       tw_dev->num_resets,
		       tw_dev->aen_count);
	spin_unlock_irqrestore(tw_dev->host->host_lock, flags);
	वापस len;
पूर्ण /* End twl_show_stats() */

/* stats sysfs attribute initializer */
अटल काष्ठा device_attribute twl_host_stats_attr = अणु
	.attr = अणु
		.name =		"3ware_stats",
		.mode =		S_IRUGO,
	पूर्ण,
	.show = twl_show_stats
पूर्ण;

/* Host attributes initializer */
अटल काष्ठा device_attribute *twl_host_attrs[] = अणु
	&twl_host_stats_attr,
	शून्य,
पूर्ण;

/* This function will look up an AEN severity string */
अटल अक्षर *twl_aen_severity_lookup(अचिन्हित अक्षर severity_code)
अणु
	अक्षर *retval = शून्य;

	अगर ((severity_code < (अचिन्हित अक्षर) TW_AEN_SEVERITY_ERROR) ||
	    (severity_code > (अचिन्हित अक्षर) TW_AEN_SEVERITY_DEBUG))
		जाओ out;

	retval = twl_aen_severity_table[severity_code];
out:
	वापस retval;
पूर्ण /* End twl_aen_severity_lookup() */

/* This function will queue an event */
अटल व्योम twl_aen_queue_event(TW_Device_Extension *tw_dev, TW_Command_Apache_Header *header)
अणु
	u32 local_समय;
	TW_Event *event;
	अचिन्हित लघु aen;
	अक्षर host[16];
	अक्षर *error_str;

	tw_dev->aen_count++;

	/* Fill out event info */
	event = tw_dev->event_queue[tw_dev->error_index];

	host[0] = '\0';
	अगर (tw_dev->host)
		प्र_लिखो(host, " scsi%d:", tw_dev->host->host_no);

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
	स_नकल(event->parameter_data, header->err_specअगरic_desc, event->parameter_len + 1 + म_माप(error_str));
	अगर (event->severity != TW_AEN_SEVERITY_DEBUG)
		prपूर्णांकk(KERN_WARNING "3w-sas:%s AEN: %s (0x%02X:0x%04X): %s:%s.\n",
		       host,
		       twl_aen_severity_lookup(TW_SEV_OUT(header->status_block.severity__reserved)),
		       TW_MESSAGE_SOURCE_CONTROLLER_EVENT, aen, error_str,
		       header->err_specअगरic_desc);
	अन्यथा
		tw_dev->aen_count--;

	tw_dev->error_index = (tw_dev->error_index + 1 ) % TW_Q_LENGTH;
पूर्ण /* End twl_aen_queue_event() */

/* This function will attempt to post a command packet to the board */
अटल पूर्णांक twl_post_command_packet(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	dma_addr_t command_que_value;

	command_que_value = tw_dev->command_packet_phys[request_id];
	command_que_value += TW_COMMAND_OFFSET;

	/* First ग_लिखो upper 4 bytes */
	ग_लिखोl((u32)((u64)command_que_value >> 32), TWL_HIBQPH_REG_ADDR(tw_dev));
	/* Then the lower 4 bytes */
	ग_लिखोl((u32)(command_que_value | TWL_PULL_MODE), TWL_HIBQPL_REG_ADDR(tw_dev));

	tw_dev->state[request_id] = TW_S_POSTED;
	tw_dev->posted_request_count++;
	अगर (tw_dev->posted_request_count > tw_dev->max_posted_request_count)
		tw_dev->max_posted_request_count = tw_dev->posted_request_count;

	वापस 0;
पूर्ण /* End twl_post_command_packet() */

/* This function hands scsi cdb's to the firmware */
अटल पूर्णांक twl_scsiop_execute_scsi(TW_Device_Extension *tw_dev, पूर्णांक request_id,
				   अचिन्हित अक्षर *cdb, पूर्णांक use_sg,
				   TW_SG_Entry_ISO *sglistarg)
अणु
	TW_Command_Full *full_command_packet;
	TW_Command_Apache *command_packet;
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
			sg_count = scsi_dma_map(srb);
			अगर (sg_count <= 0)
				जाओ out;

			scsi_क्रम_each_sg(srb, sg, sg_count, i) अणु
				command_packet->sg_list[i].address = TW_CPU_TO_SGL(sg_dma_address(sg));
				command_packet->sg_list[i].length = TW_CPU_TO_SGL(sg_dma_len(sg));
			पूर्ण
			command_packet->sgl_entries__lunh = cpu_to_le16(TW_REQ_LUN_IN((srb->device->lun >> 4), scsi_sg_count(tw_dev->srb[request_id])));
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Internal cdb post */
		क्रम (i = 0; i < use_sg; i++) अणु
			command_packet->sg_list[i].address = TW_CPU_TO_SGL(sglistarg[i].address);
			command_packet->sg_list[i].length = TW_CPU_TO_SGL(sglistarg[i].length);
		पूर्ण
		command_packet->sgl_entries__lunh = cpu_to_le16(TW_REQ_LUN_IN(0, use_sg));
	पूर्ण

	/* Update some stats */
	अगर (srb) अणु
		tw_dev->sector_count = scsi_bufflen(srb) / 512;
		अगर (tw_dev->sector_count > tw_dev->max_sector_count)
			tw_dev->max_sector_count = tw_dev->sector_count;
		tw_dev->sgl_entries = scsi_sg_count(srb);
		अगर (tw_dev->sgl_entries > tw_dev->max_sgl_entries)
			tw_dev->max_sgl_entries = tw_dev->sgl_entries;
	पूर्ण

	/* Now post the command to the board */
	retval = twl_post_command_packet(tw_dev, request_id);

out:
	वापस retval;
पूर्ण /* End twl_scsiop_execute_scsi() */

/* This function will पढ़ो the aen queue from the isr */
अटल पूर्णांक twl_aen_पढ़ो_queue(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	अचिन्हित अक्षर cdb[TW_MAX_CDB_LEN];
	TW_SG_Entry_ISO sglist[1];
	TW_Command_Full *full_command_packet;
	पूर्णांक retval = 1;

	full_command_packet = tw_dev->command_packet_virt[request_id];
	स_रखो(full_command_packet, 0, माप(TW_Command_Full));

	/* Initialize cdb */
	स_रखो(&cdb, 0, TW_MAX_CDB_LEN);
	cdb[0] = REQUEST_SENSE; /* opcode */
	cdb[4] = TW_ALLOCATION_LENGTH; /* allocation length */

	/* Initialize sglist */
	स_रखो(&sglist, 0, माप(TW_SG_Entry_ISO));
	sglist[0].length = TW_SECTOR_SIZE;
	sglist[0].address = tw_dev->generic_buffer_phys[request_id];

	/* Mark पूर्णांकernal command */
	tw_dev->srb[request_id] = शून्य;

	/* Now post the command packet */
	अगर (twl_scsiop_execute_scsi(tw_dev, request_id, cdb, 1, sglist)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x2, "Post failed while reading AEN queue");
		जाओ out;
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण /* End twl_aen_पढ़ो_queue() */

/* This function will sync firmware समय with the host समय */
अटल व्योम twl_aen_sync_समय(TW_Device_Extension *tw_dev, पूर्णांक request_id)
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
	command_packet->byte8_offset.param.sgl[0].length = TW_CPU_TO_SGL(TW_SECTOR_SIZE);
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
	schedulerसमय = cpu_to_le32(schedulerसमय);

	स_नकल(param->data, &schedulerसमय, माप(u32));

	/* Mark पूर्णांकernal command */
	tw_dev->srb[request_id] = शून्य;

	/* Now post the command */
	twl_post_command_packet(tw_dev, request_id);
पूर्ण /* End twl_aen_sync_समय() */

/* This function will assign an available request id */
अटल व्योम twl_get_request_id(TW_Device_Extension *tw_dev, पूर्णांक *request_id)
अणु
	*request_id = tw_dev->मुक्त_queue[tw_dev->मुक्त_head];
	tw_dev->मुक्त_head = (tw_dev->मुक्त_head + 1) % TW_Q_LENGTH;
	tw_dev->state[*request_id] = TW_S_STARTED;
पूर्ण /* End twl_get_request_id() */

/* This function will मुक्त a request id */
अटल व्योम twl_मुक्त_request_id(TW_Device_Extension *tw_dev, पूर्णांक request_id)
अणु
	tw_dev->मुक्त_queue[tw_dev->मुक्त_tail] = request_id;
	tw_dev->state[request_id] = TW_S_FINISHED;
	tw_dev->मुक्त_tail = (tw_dev->मुक्त_tail + 1) % TW_Q_LENGTH;
पूर्ण /* End twl_मुक्त_request_id() */

/* This function will complete an aen request from the isr */
अटल पूर्णांक twl_aen_complete(TW_Device_Extension *tw_dev, पूर्णांक request_id)
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
		अगर (twl_aen_पढ़ो_queue(tw_dev, request_id))
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
		twl_aen_sync_समय(tw_dev, request_id);
		retval = 0;
		जाओ out;
	शेष:
		twl_aen_queue_event(tw_dev, header);

		/* If there are more aen's, keep पढ़ोing the queue */
		अगर (twl_aen_पढ़ो_queue(tw_dev, request_id))
			जाओ out2;
		अन्यथा अणु
			retval = 0;
			जाओ out;
		पूर्ण
	पूर्ण
	retval = 0;
out2:
	tw_dev->state[request_id] = TW_S_COMPLETED;
	twl_मुक्त_request_id(tw_dev, request_id);
	clear_bit(TW_IN_ATTENTION_LOOP, &tw_dev->flags);
out:
	वापस retval;
पूर्ण /* End twl_aen_complete() */

/* This function will poll क्रम a response */
अटल पूर्णांक twl_poll_response(TW_Device_Extension *tw_dev, पूर्णांक request_id, पूर्णांक seconds)
अणु
	अचिन्हित दीर्घ beक्रमe;
	dma_addr_t mfa;
	u32 regh, regl;
	u32 response;
	पूर्णांक retval = 1;
	पूर्णांक found = 0;

	beक्रमe = jअगरfies;

	जबतक (!found) अणु
		अगर (माप(dma_addr_t) > 4) अणु
			regh = पढ़ोl(TWL_HOBQPH_REG_ADDR(tw_dev));
			regl = पढ़ोl(TWL_HOBQPL_REG_ADDR(tw_dev));
			mfa = ((u64)regh << 32) | regl;
		पूर्ण अन्यथा
			mfa = पढ़ोl(TWL_HOBQPL_REG_ADDR(tw_dev));

		response = (u32)mfa;

		अगर (TW_RESID_OUT(response) == request_id)
			found = 1;

		अगर (समय_after(jअगरfies, beक्रमe + HZ * seconds))
			जाओ out;

		msleep(50);
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण /* End twl_poll_response() */

/* This function will drain the aen queue */
अटल पूर्णांक twl_aen_drain_queue(TW_Device_Extension *tw_dev, पूर्णांक no_check_reset)
अणु
	पूर्णांक request_id = 0;
	अचिन्हित अक्षर cdb[TW_MAX_CDB_LEN];
	TW_SG_Entry_ISO sglist[1];
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
	स_रखो(&sglist, 0, माप(TW_SG_Entry_ISO));
	sglist[0].length = TW_SECTOR_SIZE;
	sglist[0].address = tw_dev->generic_buffer_phys[request_id];

	/* Mark पूर्णांकernal command */
	tw_dev->srb[request_id] = शून्य;

	करो अणु
		/* Send command to the board */
		अगर (twl_scsiop_execute_scsi(tw_dev, request_id, cdb, 1, sglist)) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x3, "Error posting request sense");
			जाओ out;
		पूर्ण

		/* Now poll क्रम completion */
		अगर (twl_poll_response(tw_dev, request_id, 30)) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x4, "No valid response while draining AEN queue");
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
			twl_aen_queue_event(tw_dev, header);
	पूर्ण जबतक ((finished == 0) && (count < TW_MAX_AEN_DRAIN));

	अगर (count == TW_MAX_AEN_DRAIN)
		जाओ out;

	retval = 0;
out:
	tw_dev->state[request_id] = TW_S_INITIAL;
	वापस retval;
पूर्ण /* End twl_aen_drain_queue() */

/* This function will allocate memory and check अगर it is correctly aligned */
अटल पूर्णांक twl_allocate_memory(TW_Device_Extension *tw_dev, पूर्णांक size, पूर्णांक which)
अणु
	पूर्णांक i;
	dma_addr_t dma_handle;
	अचिन्हित दीर्घ *cpu_addr;
	पूर्णांक retval = 1;

	cpu_addr = dma_alloc_coherent(&tw_dev->tw_pci_dev->dev,
				      size * TW_Q_LENGTH, &dma_handle,
				      GFP_KERNEL);
	अगर (!cpu_addr) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x5, "Memory allocation failed");
		जाओ out;
	पूर्ण

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
		हाल 2:
			tw_dev->sense_buffer_phys[i] = dma_handle+(i*size);
			tw_dev->sense_buffer_virt[i] = (TW_Command_Apache_Header *)((अचिन्हित अक्षर *)cpu_addr + (i*size));
			अवरोध;
		पूर्ण
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण /* End twl_allocate_memory() */

/* This function will load the request id and various sgls क्रम ioctls */
अटल व्योम twl_load_sgl(TW_Device_Extension *tw_dev, TW_Command_Full *full_command_packet, पूर्णांक request_id, dma_addr_t dma_handle, पूर्णांक length)
अणु
	TW_Command *oldcommand;
	TW_Command_Apache *newcommand;
	TW_SG_Entry_ISO *sgl;
	अचिन्हित पूर्णांक pae = 0;

	अगर ((माप(दीर्घ) < 8) && (माप(dma_addr_t) > 4))
		pae = 1;

	अगर (TW_OP_OUT(full_command_packet->command.newcommand.opcode__reserved) == TW_OP_EXECUTE_SCSI) अणु
		newcommand = &full_command_packet->command.newcommand;
		newcommand->request_id__lunl =
			cpu_to_le16(TW_REQ_LUN_IN(TW_LUN_OUT(newcommand->request_id__lunl), request_id));
		अगर (length) अणु
			newcommand->sg_list[0].address = TW_CPU_TO_SGL(dma_handle + माप(TW_Ioctl_Buf_Apache) - 1);
			newcommand->sg_list[0].length = TW_CPU_TO_SGL(length);
		पूर्ण
		newcommand->sgl_entries__lunh =
			cpu_to_le16(TW_REQ_LUN_IN(TW_LUN_OUT(newcommand->sgl_entries__lunh), length ? 1 : 0));
	पूर्ण अन्यथा अणु
		oldcommand = &full_command_packet->command.oldcommand;
		oldcommand->request_id = request_id;

		अगर (TW_SGL_OUT(oldcommand->opcode__sgloffset)) अणु
			/* Load the sg list */
			sgl = (TW_SG_Entry_ISO *)((u32 *)oldcommand+oldcommand->size - (माप(TW_SG_Entry_ISO)/4) + pae + (माप(dma_addr_t) > 4 ? 1 : 0));
			sgl->address = TW_CPU_TO_SGL(dma_handle + माप(TW_Ioctl_Buf_Apache) - 1);
			sgl->length = TW_CPU_TO_SGL(length);
			oldcommand->size += pae;
			oldcommand->size += माप(dma_addr_t) > 4 ? 1 : 0;
		पूर्ण
	पूर्ण
पूर्ण /* End twl_load_sgl() */

/* This function handles ioctl क्रम the अक्षरacter device
   This पूर्णांकerface is used by smarपंचांगontools खोलो source software */
अटल दीर्घ twl_chrdev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ समयout;
	अचिन्हित दीर्घ *cpu_addr, data_buffer_length_adjusted = 0, flags = 0;
	dma_addr_t dma_handle;
	पूर्णांक request_id = 0;
	TW_Ioctl_Driver_Command driver_command;
	काष्ठा inode *inode = file_inode(file);
	TW_Ioctl_Buf_Apache *tw_ioctl;
	TW_Command_Full *full_command_packet;
	TW_Device_Extension *tw_dev = twl_device_extension_list[iminor(inode)];
	पूर्णांक retval = -EFAULT;
	व्योम __user *argp = (व्योम __user *)arg;

	mutex_lock(&twl_chrdev_mutex);

	/* Only let one of these through at a समय */
	अगर (mutex_lock_पूर्णांकerruptible(&tw_dev->ioctl_lock)) अणु
		retval = -EINTR;
		जाओ out;
	पूर्ण

	/* First copy करोwn the driver command */
	अगर (copy_from_user(&driver_command, argp, माप(TW_Ioctl_Driver_Command)))
		जाओ out2;

	/* Check data buffer size */
	अगर (driver_command.buffer_length > TW_MAX_SECTORS * 2048) अणु
		retval = -EINVAL;
		जाओ out2;
	पूर्ण

	/* Hardware can only करो multiple of 512 byte transfers */
	data_buffer_length_adjusted = (driver_command.buffer_length + 511) & ~511;

	/* Now allocate ioctl buf memory */
	cpu_addr = dma_alloc_coherent(&tw_dev->tw_pci_dev->dev, data_buffer_length_adjusted+माप(TW_Ioctl_Buf_Apache) - 1, &dma_handle, GFP_KERNEL);
	अगर (!cpu_addr) अणु
		retval = -ENOMEM;
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
		twl_get_request_id(tw_dev, &request_id);

		/* Flag पूर्णांकernal command */
		tw_dev->srb[request_id] = शून्य;

		/* Flag chrdev ioctl */
		tw_dev->chrdev_request_id = request_id;

		full_command_packet = (TW_Command_Full *)&tw_ioctl->firmware_command;

		/* Load request id and sglist क्रम both command types */
		twl_load_sgl(tw_dev, full_command_packet, request_id, dma_handle, data_buffer_length_adjusted);

		स_नकल(tw_dev->command_packet_virt[request_id], &(tw_ioctl->firmware_command), माप(TW_Command_Full));

		/* Now post the command packet to the controller */
		twl_post_command_packet(tw_dev, request_id);
		spin_unlock_irqrestore(tw_dev->host->host_lock, flags);

		समयout = TW_IOCTL_CHRDEV_TIMEOUT*HZ;

		/* Now रुको क्रम command to complete */
		समयout = रुको_event_समयout(tw_dev->ioctl_wqueue, tw_dev->chrdev_request_id == TW_IOCTL_CHRDEV_FREE, समयout);

		/* We समयd out, and didn't get an पूर्णांकerrupt */
		अगर (tw_dev->chrdev_request_id != TW_IOCTL_CHRDEV_FREE) अणु
			/* Now we need to reset the board */
			prपूर्णांकk(KERN_WARNING "3w-sas: scsi%d: WARNING: (0x%02X:0x%04X): Character ioctl (0x%x) timed out, resetting card.\n",
			       tw_dev->host->host_no, TW_DRIVER, 0x6,
			       cmd);
			retval = -EIO;
			twl_reset_device_extension(tw_dev, 1);
			जाओ out3;
		पूर्ण

		/* Now copy in the command packet response */
		स_नकल(&(tw_ioctl->firmware_command), tw_dev->command_packet_virt[request_id], माप(TW_Command_Full));

		/* Now complete the io */
		spin_lock_irqsave(tw_dev->host->host_lock, flags);
		tw_dev->posted_request_count--;
		tw_dev->state[request_id] = TW_S_COMPLETED;
		twl_मुक्त_request_id(tw_dev, request_id);
		spin_unlock_irqrestore(tw_dev->host->host_lock, flags);
		अवरोध;
	शेष:
		retval = -ENOTTY;
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
	mutex_unlock(&twl_chrdev_mutex);
	वापस retval;
पूर्ण /* End twl_chrdev_ioctl() */

/* This function handles खोलो क्रम the अक्षरacter device */
अटल पूर्णांक twl_chrdev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor_number;
	पूर्णांक retval = -ENODEV;

	अगर (!capable(CAP_SYS_ADMIN)) अणु
		retval = -EACCES;
		जाओ out;
	पूर्ण

	minor_number = iminor(inode);
	अगर (minor_number >= twl_device_extension_count)
		जाओ out;
	retval = 0;
out:
	वापस retval;
पूर्ण /* End twl_chrdev_खोलो() */

/* File operations काष्ठा क्रम अक्षरacter device */
अटल स्थिर काष्ठा file_operations twl_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= twl_chrdev_ioctl,
	.खोलो		= twl_chrdev_खोलो,
	.release	= शून्य,
	.llseek		= noop_llseek,
पूर्ण;

/* This function passes sense data from firmware to scsi layer */
अटल पूर्णांक twl_fill_sense(TW_Device_Extension *tw_dev, पूर्णांक i, पूर्णांक request_id, पूर्णांक copy_sense, पूर्णांक prपूर्णांक_host)
अणु
	TW_Command_Apache_Header *header;
	TW_Command_Full *full_command_packet;
	अचिन्हित लघु error;
	अक्षर *error_str;

	header = tw_dev->sense_buffer_virt[i];
	full_command_packet = tw_dev->command_packet_virt[request_id];

	/* Get embedded firmware error string */
	error_str = &(header->err_specअगरic_desc[म_माप(header->err_specअगरic_desc) + 1]);

	/* Don't prपूर्णांक error क्रम Logical unit not supported during rollcall */
	error = le16_to_cpu(header->status_block.error);
	अगर ((error != TW_ERROR_LOGICAL_UNIT_NOT_SUPPORTED) && (error != TW_ERROR_UNIT_OFFLINE) && (error != TW_ERROR_INVALID_FIELD_IN_CDB)) अणु
		अगर (prपूर्णांक_host)
			prपूर्णांकk(KERN_WARNING "3w-sas: scsi%d: ERROR: (0x%02X:0x%04X): %s:%s.\n",
			       tw_dev->host->host_no,
			       TW_MESSAGE_SOURCE_CONTROLLER_ERROR,
			       header->status_block.error,
			       error_str,
			       header->err_specअगरic_desc);
		अन्यथा
			prपूर्णांकk(KERN_WARNING "3w-sas: ERROR: (0x%02X:0x%04X): %s:%s.\n",
			       TW_MESSAGE_SOURCE_CONTROLLER_ERROR,
			       header->status_block.error,
			       error_str,
			       header->err_specअगरic_desc);
	पूर्ण

	अगर (copy_sense) अणु
		स_नकल(tw_dev->srb[request_id]->sense_buffer, header->sense_data, TW_SENSE_DATA_LENGTH);
		tw_dev->srb[request_id]->result = (full_command_packet->command.newcommand.status << 1);
		जाओ out;
	पूर्ण
out:
	वापस 1;
पूर्ण /* End twl_fill_sense() */

/* This function will मुक्त up device extension resources */
अटल व्योम twl_मुक्त_device_extension(TW_Device_Extension *tw_dev)
अणु
	अगर (tw_dev->command_packet_virt[0])
		dma_मुक्त_coherent(&tw_dev->tw_pci_dev->dev,
				    माप(TW_Command_Full)*TW_Q_LENGTH,
				    tw_dev->command_packet_virt[0],
				    tw_dev->command_packet_phys[0]);

	अगर (tw_dev->generic_buffer_virt[0])
		dma_मुक्त_coherent(&tw_dev->tw_pci_dev->dev,
				    TW_SECTOR_SIZE*TW_Q_LENGTH,
				    tw_dev->generic_buffer_virt[0],
				    tw_dev->generic_buffer_phys[0]);

	अगर (tw_dev->sense_buffer_virt[0])
		dma_मुक्त_coherent(&tw_dev->tw_pci_dev->dev,
				    माप(TW_Command_Apache_Header)*
				    TW_Q_LENGTH,
				    tw_dev->sense_buffer_virt[0],
				    tw_dev->sense_buffer_phys[0]);

	kमुक्त(tw_dev->event_queue[0]);
पूर्ण /* End twl_मुक्त_device_extension() */

/* This function will get parameter table entries from the firmware */
अटल व्योम *twl_get_param(TW_Device_Extension *tw_dev, पूर्णांक request_id, पूर्णांक table_id, पूर्णांक parameter_id, पूर्णांक parameter_size_bytes)
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
	command_packet->byte8_offset.param.sgl[0].length = TW_CPU_TO_SGL(TW_SECTOR_SIZE);

	/* Post the command packet to the board */
	twl_post_command_packet(tw_dev, request_id);

	/* Poll क्रम completion */
	अगर (twl_poll_response(tw_dev, request_id, 30))
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x7, "No valid response during get param")
	अन्यथा
		retval = (व्योम *)&(param->data[0]);

	tw_dev->posted_request_count--;
	tw_dev->state[request_id] = TW_S_INITIAL;

	वापस retval;
पूर्ण /* End twl_get_param() */

/* This function will send an initconnection command to controller */
अटल पूर्णांक twl_initconnection(TW_Device_Extension *tw_dev, पूर्णांक message_credits,
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
	twl_post_command_packet(tw_dev, request_id);

	/* Poll क्रम completion */
	अगर (twl_poll_response(tw_dev, request_id, 30)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x8, "No valid response during init connection");
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
पूर्ण /* End twl_initconnection() */

/* This function will initialize the fields of a device extension */
अटल पूर्णांक twl_initialize_device_extension(TW_Device_Extension *tw_dev)
अणु
	पूर्णांक i, retval = 1;

	/* Initialize command packet buffers */
	अगर (twl_allocate_memory(tw_dev, माप(TW_Command_Full), 0)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x9, "Command packet memory allocation failed");
		जाओ out;
	पूर्ण

	/* Initialize generic buffer */
	अगर (twl_allocate_memory(tw_dev, TW_SECTOR_SIZE, 1)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0xa, "Generic memory allocation failed");
		जाओ out;
	पूर्ण

	/* Allocate sense buffers */
	अगर (twl_allocate_memory(tw_dev, माप(TW_Command_Apache_Header), 2)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0xb, "Sense buffer allocation failed");
		जाओ out;
	पूर्ण

	/* Allocate event info space */
	tw_dev->event_queue[0] = kसुस्मृति(TW_Q_LENGTH, माप(TW_Event), GFP_KERNEL);
	अगर (!tw_dev->event_queue[0]) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0xc, "Event info memory allocation failed");
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < TW_Q_LENGTH; i++) अणु
		tw_dev->event_queue[i] = (TW_Event *)((अचिन्हित अक्षर *)tw_dev->event_queue[0] + (i * माप(TW_Event)));
		tw_dev->मुक्त_queue[i] = i;
		tw_dev->state[i] = TW_S_INITIAL;
	पूर्ण

	tw_dev->मुक्त_head = TW_Q_START;
	tw_dev->मुक्त_tail = TW_Q_START;
	tw_dev->error_sequence_id = 1;
	tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;

	mutex_init(&tw_dev->ioctl_lock);
	init_रुकोqueue_head(&tw_dev->ioctl_wqueue);

	retval = 0;
out:
	वापस retval;
पूर्ण /* End twl_initialize_device_extension() */

/* This function will handle attention पूर्णांकerrupts */
अटल पूर्णांक twl_handle_attention_पूर्णांकerrupt(TW_Device_Extension *tw_dev)
अणु
	पूर्णांक retval = 1;
	u32 request_id, करोorbell;

	/* Read करोorbell status */
	करोorbell = पढ़ोl(TWL_HOBDB_REG_ADDR(tw_dev));

	/* Check क्रम controller errors */
	अगर (करोorbell & TWL_DOORBELL_CONTROLLER_ERROR) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0xd, "Microcontroller Error: clearing");
		जाओ out;
	पूर्ण

	/* Check अगर we need to perक्रमm an AEN drain */
	अगर (करोorbell & TWL_DOORBELL_ATTENTION_INTERRUPT) अणु
		अगर (!(test_and_set_bit(TW_IN_ATTENTION_LOOP, &tw_dev->flags))) अणु
			twl_get_request_id(tw_dev, &request_id);
			अगर (twl_aen_पढ़ो_queue(tw_dev, request_id)) अणु
				tw_dev->state[request_id] = TW_S_COMPLETED;
				twl_मुक्त_request_id(tw_dev, request_id);
				clear_bit(TW_IN_ATTENTION_LOOP, &tw_dev->flags);
			पूर्ण
		पूर्ण
	पूर्ण

	retval = 0;
out:
	/* Clear करोorbell पूर्णांकerrupt */
	TWL_CLEAR_DB_INTERRUPT(tw_dev);

	/* Make sure the clear was flushed by पढ़ोing it back */
	पढ़ोl(TWL_HOBDBC_REG_ADDR(tw_dev));

	वापस retval;
पूर्ण /* End twl_handle_attention_पूर्णांकerrupt() */

/* Interrupt service routine */
अटल irqवापस_t twl_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)dev_instance;
	पूर्णांक i, handled = 0, error = 0;
	dma_addr_t mfa = 0;
	u32 reg, regl, regh, response, request_id = 0;
	काष्ठा scsi_cmnd *cmd;
	TW_Command_Full *full_command_packet;

	spin_lock(tw_dev->host->host_lock);

	/* Read host पूर्णांकerrupt status */
	reg = पढ़ोl(TWL_HISTAT_REG_ADDR(tw_dev));

	/* Check अगर this is our पूर्णांकerrupt, otherwise bail */
	अगर (!(reg & TWL_HISTATUS_VALID_INTERRUPT))
		जाओ twl_पूर्णांकerrupt_bail;

	handled = 1;

	/* If we are resetting, bail */
	अगर (test_bit(TW_IN_RESET, &tw_dev->flags))
		जाओ twl_पूर्णांकerrupt_bail;

	/* Attention पूर्णांकerrupt */
	अगर (reg & TWL_HISTATUS_ATTENTION_INTERRUPT) अणु
		अगर (twl_handle_attention_पूर्णांकerrupt(tw_dev)) अणु
			TWL_MASK_INTERRUPTS(tw_dev);
			जाओ twl_पूर्णांकerrupt_bail;
		पूर्ण
	पूर्ण

	/* Response पूर्णांकerrupt */
	जबतक (reg & TWL_HISTATUS_RESPONSE_INTERRUPT) अणु
		अगर (माप(dma_addr_t) > 4) अणु
			regh = पढ़ोl(TWL_HOBQPH_REG_ADDR(tw_dev));
			regl = पढ़ोl(TWL_HOBQPL_REG_ADDR(tw_dev));
			mfa = ((u64)regh << 32) | regl;
		पूर्ण अन्यथा
			mfa = पढ़ोl(TWL_HOBQPL_REG_ADDR(tw_dev));

		error = 0;
		response = (u32)mfa;

		/* Check क्रम command packet error */
		अगर (!TW_NOTMFA_OUT(response)) अणु
			क्रम (i=0;i<TW_Q_LENGTH;i++) अणु
				अगर (tw_dev->sense_buffer_phys[i] == mfa) अणु
					request_id = le16_to_cpu(tw_dev->sense_buffer_virt[i]->header_desc.request_id);
					अगर (tw_dev->srb[request_id] != शून्य)
						error = twl_fill_sense(tw_dev, i, request_id, 1, 1);
					अन्यथा अणु
						/* Skip ioctl error prपूर्णांकs */
						अगर (request_id != tw_dev->chrdev_request_id)
							error = twl_fill_sense(tw_dev, i, request_id, 0, 1);
						अन्यथा
							स_नकल(tw_dev->command_packet_virt[request_id], tw_dev->sense_buffer_virt[i], माप(TW_Command_Apache_Header));
					पूर्ण

					/* Now re-post the sense buffer */
					ग_लिखोl((u32)((u64)tw_dev->sense_buffer_phys[i] >> 32), TWL_HOBQPH_REG_ADDR(tw_dev));
					ग_लिखोl((u32)tw_dev->sense_buffer_phys[i], TWL_HOBQPL_REG_ADDR(tw_dev));
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			request_id = TW_RESID_OUT(response);

		full_command_packet = tw_dev->command_packet_virt[request_id];

		/* Check क्रम correct state */
		अगर (tw_dev->state[request_id] != TW_S_POSTED) अणु
			अगर (tw_dev->srb[request_id] != शून्य) अणु
				TW_PRINTK(tw_dev->host, TW_DRIVER, 0xe, "Received a request id that wasn't posted");
				TWL_MASK_INTERRUPTS(tw_dev);
				जाओ twl_पूर्णांकerrupt_bail;
			पूर्ण
		पूर्ण

		/* Check क्रम पूर्णांकernal command completion */
		अगर (tw_dev->srb[request_id] == शून्य) अणु
			अगर (request_id != tw_dev->chrdev_request_id) अणु
				अगर (twl_aen_complete(tw_dev, request_id))
					TW_PRINTK(tw_dev->host, TW_DRIVER, 0xf, "Error completing AEN during attention interrupt");
			पूर्ण अन्यथा अणु
				tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;
				wake_up(&tw_dev->ioctl_wqueue);
			पूर्ण
		पूर्ण अन्यथा अणु
			cmd = tw_dev->srb[request_id];

			अगर (!error)
				cmd->result = (DID_OK << 16);

			/* Report residual bytes क्रम single sgl */
			अगर ((scsi_sg_count(cmd) <= 1) && (full_command_packet->command.newcommand.status == 0)) अणु
				अगर (full_command_packet->command.newcommand.sg_list[0].length < scsi_bufflen(tw_dev->srb[request_id]))
					scsi_set_resid(cmd, scsi_bufflen(cmd) - full_command_packet->command.newcommand.sg_list[0].length);
			पूर्ण

			/* Now complete the io */
			scsi_dma_unmap(cmd);
			cmd->scsi_करोne(cmd);
			tw_dev->state[request_id] = TW_S_COMPLETED;
			twl_मुक्त_request_id(tw_dev, request_id);
			tw_dev->posted_request_count--;
		पूर्ण

		/* Check क्रम another response पूर्णांकerrupt */
		reg = पढ़ोl(TWL_HISTAT_REG_ADDR(tw_dev));
	पूर्ण

twl_पूर्णांकerrupt_bail:
	spin_unlock(tw_dev->host->host_lock);
	वापस IRQ_RETVAL(handled);
पूर्ण /* End twl_पूर्णांकerrupt() */

/* This function will poll क्रम a रेजिस्टर change */
अटल पूर्णांक twl_poll_रेजिस्टर(TW_Device_Extension *tw_dev, व्योम *reg, u32 value, u32 result, पूर्णांक seconds)
अणु
	अचिन्हित दीर्घ beक्रमe;
	पूर्णांक retval = 1;
	u32 reg_value;

	reg_value = पढ़ोl(reg);
	beक्रमe = jअगरfies;

	जबतक ((reg_value & value) != result) अणु
		reg_value = पढ़ोl(reg);
		अगर (समय_after(jअगरfies, beक्रमe + HZ * seconds))
			जाओ out;
		msleep(50);
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण /* End twl_poll_रेजिस्टर() */

/* This function will reset a controller */
अटल पूर्णांक twl_reset_sequence(TW_Device_Extension *tw_dev, पूर्णांक soft_reset)
अणु
	पूर्णांक retval = 1;
	पूर्णांक i = 0;
	u32 status = 0;
	अचिन्हित लघु fw_on_ctlr_srl = 0, fw_on_ctlr_arch_id = 0;
	अचिन्हित लघु fw_on_ctlr_branch = 0, fw_on_ctlr_build = 0;
	u32 init_connect_result = 0;
	पूर्णांक tries = 0;
	पूर्णांक करो_soft_reset = soft_reset;

	जबतक (tries < TW_MAX_RESET_TRIES) अणु
		/* Do a soft reset अगर one is needed */
		अगर (करो_soft_reset) अणु
			TWL_SOFT_RESET(tw_dev);

			/* Make sure controller is in a good state */
			अगर (twl_poll_रेजिस्टर(tw_dev, TWL_SCRPD3_REG_ADDR(tw_dev), TWL_CONTROLLER_READY, 0x0, 30)) अणु
				TW_PRINTK(tw_dev->host, TW_DRIVER, 0x10, "Controller never went non-ready during reset sequence");
				tries++;
				जारी;
			पूर्ण
			अगर (twl_poll_रेजिस्टर(tw_dev, TWL_SCRPD3_REG_ADDR(tw_dev), TWL_CONTROLLER_READY, TWL_CONTROLLER_READY, 60)) अणु
				TW_PRINTK(tw_dev->host, TW_DRIVER, 0x11, "Controller not ready during reset sequence");
				tries++;
				जारी;
			पूर्ण
		पूर्ण

		/* Initconnect */
		अगर (twl_initconnection(tw_dev, TW_INIT_MESSAGE_CREDITS,
				       TW_EXTENDED_INIT_CONNECT, TW_CURRENT_DRIVER_SRL,
				       TW_9750_ARCH_ID, TW_CURRENT_DRIVER_BRANCH,
				       TW_CURRENT_DRIVER_BUILD, &fw_on_ctlr_srl,
				       &fw_on_ctlr_arch_id, &fw_on_ctlr_branch,
				       &fw_on_ctlr_build, &init_connect_result)) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x12, "Initconnection failed while checking SRL");
			करो_soft_reset = 1;
			tries++;
			जारी;
		पूर्ण

		/* Load sense buffers */
		जबतक (i < TW_Q_LENGTH) अणु
			ग_लिखोl((u32)((u64)tw_dev->sense_buffer_phys[i] >> 32), TWL_HOBQPH_REG_ADDR(tw_dev));
			ग_लिखोl((u32)tw_dev->sense_buffer_phys[i], TWL_HOBQPL_REG_ADDR(tw_dev));

			/* Check status क्रम over-run after each ग_लिखो */
			status = पढ़ोl(TWL_STATUS_REG_ADDR(tw_dev));
			अगर (!(status & TWL_STATUS_OVERRUN_SUBMIT))
			    i++;
		पूर्ण

		/* Now check status */
		status = पढ़ोl(TWL_STATUS_REG_ADDR(tw_dev));
		अगर (status) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x13, "Bad controller status after loading sense buffers");
			करो_soft_reset = 1;
			tries++;
			जारी;
		पूर्ण

		/* Drain the AEN queue */
		अगर (twl_aen_drain_queue(tw_dev, soft_reset)) अणु
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x14, "AEN drain failed during reset sequence");
			करो_soft_reset = 1;
			tries++;
			जारी;
		पूर्ण

		/* Load rest of compatibility काष्ठा */
		म_नकलन(tw_dev->tw_compat_info.driver_version, TW_DRIVER_VERSION, म_माप(TW_DRIVER_VERSION));
		tw_dev->tw_compat_info.driver_srl_high = TW_CURRENT_DRIVER_SRL;
		tw_dev->tw_compat_info.driver_branch_high = TW_CURRENT_DRIVER_BRANCH;
		tw_dev->tw_compat_info.driver_build_high = TW_CURRENT_DRIVER_BUILD;
		tw_dev->tw_compat_info.driver_srl_low = TW_BASE_FW_SRL;
		tw_dev->tw_compat_info.driver_branch_low = TW_BASE_FW_BRANCH;
		tw_dev->tw_compat_info.driver_build_low = TW_BASE_FW_BUILD;
		tw_dev->tw_compat_info.fw_on_ctlr_srl = fw_on_ctlr_srl;
		tw_dev->tw_compat_info.fw_on_ctlr_branch = fw_on_ctlr_branch;
		tw_dev->tw_compat_info.fw_on_ctlr_build = fw_on_ctlr_build;

		/* If we got here, controller is in a good state */
		retval = 0;
		जाओ out;
	पूर्ण
out:
	वापस retval;
पूर्ण /* End twl_reset_sequence() */

/* This function will reset a device extension */
अटल पूर्णांक twl_reset_device_extension(TW_Device_Extension *tw_dev, पूर्णांक ioctl_reset)
अणु
	पूर्णांक i = 0, retval = 1;
	अचिन्हित दीर्घ flags = 0;

	/* Block SCSI requests जबतक we are resetting */
	अगर (ioctl_reset)
		scsi_block_requests(tw_dev->host);

	set_bit(TW_IN_RESET, &tw_dev->flags);
	TWL_MASK_INTERRUPTS(tw_dev);
	TWL_CLEAR_DB_INTERRUPT(tw_dev);

	spin_lock_irqsave(tw_dev->host->host_lock, flags);

	/* Abort all requests that are in progress */
	क्रम (i = 0; i < TW_Q_LENGTH; i++) अणु
		अगर ((tw_dev->state[i] != TW_S_FINISHED) &&
		    (tw_dev->state[i] != TW_S_INITIAL) &&
		    (tw_dev->state[i] != TW_S_COMPLETED)) अणु
			काष्ठा scsi_cmnd *cmd = tw_dev->srb[i];

			अगर (cmd) अणु
				cmd->result = (DID_RESET << 16);
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

	spin_unlock_irqrestore(tw_dev->host->host_lock, flags);

	अगर (twl_reset_sequence(tw_dev, 1))
		जाओ out;

	TWL_UNMASK_INTERRUPTS(tw_dev);

	clear_bit(TW_IN_RESET, &tw_dev->flags);
	tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;

	retval = 0;
out:
	अगर (ioctl_reset)
		scsi_unblock_requests(tw_dev->host);
	वापस retval;
पूर्ण /* End twl_reset_device_extension() */

/* This funciton वापसs unit geometry in cylinders/heads/sectors */
अटल पूर्णांक twl_scsi_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev, sector_t capacity, पूर्णांक geom[])
अणु
	पूर्णांक heads, sectors;

	अगर (capacity >= 0x200000) अणु
		heads = 255;
		sectors = 63;
	पूर्ण अन्यथा अणु
		heads = 64;
		sectors = 32;
	पूर्ण

	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = sector_भाग(capacity, heads * sectors); /* cylinders */

	वापस 0;
पूर्ण /* End twl_scsi_biosparam() */

/* This is the new scsi eh reset function */
अटल पूर्णांक twl_scsi_eh_reset(काष्ठा scsi_cmnd *SCpnt)
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
	अगर (twl_reset_device_extension(tw_dev, 0)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x15, "Controller reset failed during scsi host reset");
		जाओ out;
	पूर्ण

	retval = SUCCESS;
out:
	mutex_unlock(&tw_dev->ioctl_lock);
	वापस retval;
पूर्ण /* End twl_scsi_eh_reset() */

/* This is the मुख्य scsi queue function to handle scsi opcodes */
अटल पूर्णांक twl_scsi_queue_lck(काष्ठा scsi_cmnd *SCpnt, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	पूर्णांक request_id, retval;
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)SCpnt->device->host->hostdata;

	/* If we are resetting due to समयd out ioctl, report as busy */
	अगर (test_bit(TW_IN_RESET, &tw_dev->flags)) अणु
		retval = SCSI_MLQUEUE_HOST_BUSY;
		जाओ out;
	पूर्ण

	/* Save करोne function पूर्णांकo scsi_cmnd काष्ठा */
	SCpnt->scsi_करोne = करोne;

	/* Get a मुक्त request id */
	twl_get_request_id(tw_dev, &request_id);

	/* Save the scsi command क्रम use by the ISR */
	tw_dev->srb[request_id] = SCpnt;

	retval = twl_scsiop_execute_scsi(tw_dev, request_id, शून्य, 0, शून्य);
	अगर (retval) अणु
		tw_dev->state[request_id] = TW_S_COMPLETED;
		twl_मुक्त_request_id(tw_dev, request_id);
		SCpnt->result = (DID_ERROR << 16);
		करोne(SCpnt);
		retval = 0;
	पूर्ण
out:
	वापस retval;
पूर्ण /* End twl_scsi_queue() */

अटल DEF_SCSI_QCMD(twl_scsi_queue)

/* This function tells the controller to shut करोwn */
अटल व्योम __twl_shutकरोwn(TW_Device_Extension *tw_dev)
अणु
	/* Disable पूर्णांकerrupts */
	TWL_MASK_INTERRUPTS(tw_dev);

	/* Free up the IRQ */
	मुक्त_irq(tw_dev->tw_pci_dev->irq, tw_dev);

	prपूर्णांकk(KERN_WARNING "3w-sas: Shutting down host %d.\n", tw_dev->host->host_no);

	/* Tell the card we are shutting करोwn */
	अगर (twl_initconnection(tw_dev, 1, 0, 0, 0, 0, 0, शून्य, शून्य, शून्य, शून्य, शून्य)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x16, "Connection shutdown failed");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "3w-sas: Shutdown complete.\n");
	पूर्ण

	/* Clear करोorbell पूर्णांकerrupt just beक्रमe निकास */
	TWL_CLEAR_DB_INTERRUPT(tw_dev);
पूर्ण /* End __twl_shutकरोwn() */

/* Wrapper क्रम __twl_shutकरोwn */
अटल व्योम twl_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	TW_Device_Extension *tw_dev;

	अगर (!host)
		वापस;

	tw_dev = (TW_Device_Extension *)host->hostdata;

	अगर (tw_dev->online)
		__twl_shutकरोwn(tw_dev);
पूर्ण /* End twl_shutकरोwn() */

/* This function configures unit settings when a unit is coming on-line */
अटल पूर्णांक twl_slave_configure(काष्ठा scsi_device *sdev)
अणु
	/* Force 60 second समयout */
	blk_queue_rq_समयout(sdev->request_queue, 60 * HZ);

	वापस 0;
पूर्ण /* End twl_slave_configure() */

/* scsi_host_ढाँचा initializer */
अटल काष्ठा scsi_host_ढाँचा driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "3w-sas",
	.queuecommand		= twl_scsi_queue,
	.eh_host_reset_handler	= twl_scsi_eh_reset,
	.bios_param		= twl_scsi_biosparam,
	.change_queue_depth	= scsi_change_queue_depth,
	.can_queue		= TW_Q_LENGTH-2,
	.slave_configure	= twl_slave_configure,
	.this_id		= -1,
	.sg_tablesize		= TW_LIBERATOR_MAX_SGL_LENGTH,
	.max_sectors		= TW_MAX_SECTORS,
	.cmd_per_lun		= TW_MAX_CMDS_PER_LUN,
	.shost_attrs		= twl_host_attrs,
	.emulated		= 1,
	.no_ग_लिखो_same		= 1,
पूर्ण;

/* This function will probe and initialize a card */
अटल पूर्णांक twl_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *dev_id)
अणु
	काष्ठा Scsi_Host *host = शून्य;
	TW_Device_Extension *tw_dev;
	पूर्णांक retval = -ENODEV;
	पूर्णांक *ptr_phycount, phycount=0;

	retval = pci_enable_device(pdev);
	अगर (retval) अणु
		TW_PRINTK(host, TW_DRIVER, 0x17, "Failed to enable pci device");
		जाओ out_disable_device;
	पूर्ण

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	retval = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (retval)
		retval = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (retval) अणु
		TW_PRINTK(host, TW_DRIVER, 0x18, "Failed to set dma mask");
		retval = -ENODEV;
		जाओ out_disable_device;
	पूर्ण

	host = scsi_host_alloc(&driver_ढाँचा, माप(TW_Device_Extension));
	अगर (!host) अणु
		TW_PRINTK(host, TW_DRIVER, 0x19, "Failed to allocate memory for device extension");
		retval = -ENOMEM;
		जाओ out_disable_device;
	पूर्ण
	tw_dev = shost_priv(host);

	/* Save values to device extension */
	tw_dev->host = host;
	tw_dev->tw_pci_dev = pdev;

	अगर (twl_initialize_device_extension(tw_dev)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1a, "Failed to initialize device extension");
		retval = -ENOMEM;
		जाओ out_मुक्त_device_extension;
	पूर्ण

	/* Request IO regions */
	retval = pci_request_regions(pdev, "3w-sas");
	अगर (retval) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1b, "Failed to get mem region");
		जाओ out_मुक्त_device_extension;
	पूर्ण

	/* Save base address, use region 1 */
	tw_dev->base_addr = pci_iomap(pdev, 1, 0);
	अगर (!tw_dev->base_addr) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1c, "Failed to ioremap");
		retval = -ENOMEM;
		जाओ out_release_mem_region;
	पूर्ण

	/* Disable पूर्णांकerrupts on the card */
	TWL_MASK_INTERRUPTS(tw_dev);

	/* Initialize the card */
	अगर (twl_reset_sequence(tw_dev, 0)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1d, "Controller reset failed during probe");
		retval = -ENOMEM;
		जाओ out_iounmap;
	पूर्ण

	/* Set host specअगरic parameters */
	host->max_id = TW_MAX_UNITS;
	host->max_cmd_len = TW_MAX_CDB_LEN;
	host->max_lun = TW_MAX_LUNS;
	host->max_channel = 0;

	/* Register the card with the kernel SCSI layer */
	retval = scsi_add_host(host, &pdev->dev);
	अगर (retval) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1e, "scsi add host failed");
		जाओ out_iounmap;
	पूर्ण

	pci_set_drvdata(pdev, host);

	prपूर्णांकk(KERN_WARNING "3w-sas: scsi%d: Found an LSI 3ware %s Controller at 0x%llx, IRQ: %d.\n",
	       host->host_no,
	       (अक्षर *)twl_get_param(tw_dev, 1, TW_VERSION_TABLE,
				     TW_PARAM_MODEL, TW_PARAM_MODEL_LENGTH),
	       (u64)pci_resource_start(pdev, 1), pdev->irq);

	ptr_phycount = twl_get_param(tw_dev, 2, TW_PARAM_PHY_SUMMARY_TABLE,
				     TW_PARAM_PHYCOUNT, TW_PARAM_PHYCOUNT_LENGTH);
	अगर (ptr_phycount)
		phycount = le32_to_cpu(*(पूर्णांक *)ptr_phycount);

	prपूर्णांकk(KERN_WARNING "3w-sas: scsi%d: Firmware %s, BIOS %s, Phys: %d.\n",
	       host->host_no,
	       (अक्षर *)twl_get_param(tw_dev, 1, TW_VERSION_TABLE,
				     TW_PARAM_FWVER, TW_PARAM_FWVER_LENGTH),
	       (अक्षर *)twl_get_param(tw_dev, 2, TW_VERSION_TABLE,
				     TW_PARAM_BIOSVER, TW_PARAM_BIOSVER_LENGTH),
	       phycount);

	/* Try to enable MSI */
	अगर (use_msi && !pci_enable_msi(pdev))
		set_bit(TW_USING_MSI, &tw_dev->flags);

	/* Now setup the पूर्णांकerrupt handler */
	retval = request_irq(pdev->irq, twl_पूर्णांकerrupt, IRQF_SHARED, "3w-sas", tw_dev);
	अगर (retval) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1f, "Error requesting IRQ");
		जाओ out_हटाओ_host;
	पूर्ण

	twl_device_extension_list[twl_device_extension_count] = tw_dev;
	twl_device_extension_count++;

	/* Re-enable पूर्णांकerrupts on the card */
	TWL_UNMASK_INTERRUPTS(tw_dev);

	/* Finally, scan the host */
	scsi_scan_host(host);

	/* Add sysfs binary files */
	अगर (sysfs_create_bin_file(&host->shost_dev.kobj, &twl_sysfs_aen_पढ़ो_attr))
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x20, "Failed to create sysfs binary file: 3ware_aen_read");
	अगर (sysfs_create_bin_file(&host->shost_dev.kobj, &twl_sysfs_compat_info_attr))
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x21, "Failed to create sysfs binary file: 3ware_compat_info");

	अगर (twl_major == -1) अणु
		अगर ((twl_major = रेजिस्टर_chrdev (0, "twl", &twl_fops)) < 0)
			TW_PRINTK(host, TW_DRIVER, 0x22, "Failed to register character device");
	पूर्ण
	tw_dev->online = 1;
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
	twl_मुक्त_device_extension(tw_dev);
	scsi_host_put(host);
out_disable_device:
	pci_disable_device(pdev);

	वापस retval;
पूर्ण /* End twl_probe() */

/* This function is called to हटाओ a device */
अटल व्योम twl_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	TW_Device_Extension *tw_dev;

	अगर (!host)
		वापस;

	tw_dev = (TW_Device_Extension *)host->hostdata;

	अगर (!tw_dev->online)
		वापस;

	/* Remove sysfs binary files */
	sysfs_हटाओ_bin_file(&host->shost_dev.kobj, &twl_sysfs_aen_पढ़ो_attr);
	sysfs_हटाओ_bin_file(&host->shost_dev.kobj, &twl_sysfs_compat_info_attr);

	scsi_हटाओ_host(tw_dev->host);

	/* Unरेजिस्टर अक्षरacter device */
	अगर (twl_major >= 0) अणु
		unरेजिस्टर_chrdev(twl_major, "twl");
		twl_major = -1;
	पूर्ण

	/* Shutकरोwn the card */
	__twl_shutकरोwn(tw_dev);

	/* Disable MSI अगर enabled */
	अगर (test_bit(TW_USING_MSI, &tw_dev->flags))
		pci_disable_msi(pdev);

	/* Free IO remapping */
	iounmap(tw_dev->base_addr);

	/* Free up the mem region */
	pci_release_regions(pdev);

	/* Free up device extension resources */
	twl_मुक्त_device_extension(tw_dev);

	scsi_host_put(tw_dev->host);
	pci_disable_device(pdev);
	twl_device_extension_count--;
पूर्ण /* End twl_हटाओ() */

/* This function is called on PCI suspend */
अटल पूर्णांक __maybe_unused twl_suspend(काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *host = dev_get_drvdata(dev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;

	prपूर्णांकk(KERN_WARNING "3w-sas: Suspending host %d.\n", tw_dev->host->host_no);
	/* Disable पूर्णांकerrupts */
	TWL_MASK_INTERRUPTS(tw_dev);

	मुक्त_irq(tw_dev->tw_pci_dev->irq, tw_dev);

	/* Tell the card we are shutting करोwn */
	अगर (twl_initconnection(tw_dev, 1, 0, 0, 0, 0, 0, शून्य, शून्य, शून्य, शून्य, शून्य)) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x23, "Connection shutdown failed during suspend");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "3w-sas: Suspend complete.\n");
	पूर्ण

	/* Clear करोorbell पूर्णांकerrupt */
	TWL_CLEAR_DB_INTERRUPT(tw_dev);

	वापस 0;
पूर्ण /* End twl_suspend() */

/* This function is called on PCI resume */
अटल पूर्णांक __maybe_unused twl_resume(काष्ठा device *dev)
अणु
	पूर्णांक retval = 0;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;

	prपूर्णांकk(KERN_WARNING "3w-sas: Resuming host %d.\n", tw_dev->host->host_no);
	pci_try_set_mwi(pdev);

	retval = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (retval)
		retval = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (retval) अणु
		TW_PRINTK(host, TW_DRIVER, 0x25, "Failed to set dma mask during resume");
		retval = -ENODEV;
		जाओ out_disable_device;
	पूर्ण

	/* Initialize the card */
	अगर (twl_reset_sequence(tw_dev, 0)) अणु
		retval = -ENODEV;
		जाओ out_disable_device;
	पूर्ण

	/* Now setup the पूर्णांकerrupt handler */
	retval = request_irq(pdev->irq, twl_पूर्णांकerrupt, IRQF_SHARED, "3w-sas", tw_dev);
	अगर (retval) अणु
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x26, "Error requesting IRQ during resume");
		retval = -ENODEV;
		जाओ out_disable_device;
	पूर्ण

	/* Now enable MSI अगर enabled */
	अगर (test_bit(TW_USING_MSI, &tw_dev->flags))
		pci_enable_msi(pdev);

	/* Re-enable पूर्णांकerrupts on the card */
	TWL_UNMASK_INTERRUPTS(tw_dev);

	prपूर्णांकk(KERN_WARNING "3w-sas: Resume complete.\n");
	वापस 0;

out_disable_device:
	scsi_हटाओ_host(host);

	वापस retval;
पूर्ण /* End twl_resume() */

/* PCI Devices supported by this driver */
अटल काष्ठा pci_device_id twl_pci_tbl[] = अणु
	अणु PCI_VDEVICE(3WARE, PCI_DEVICE_ID_3WARE_9750) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, twl_pci_tbl);

अटल SIMPLE_DEV_PM_OPS(twl_pm_ops, twl_suspend, twl_resume);

/* pci_driver initializer */
अटल काष्ठा pci_driver twl_driver = अणु
	.name		= "3w-sas",
	.id_table	= twl_pci_tbl,
	.probe		= twl_probe,
	.हटाओ		= twl_हटाओ,
	.driver.pm	= &twl_pm_ops,
	.shutकरोwn	= twl_shutकरोwn
पूर्ण;

/* This function is called on driver initialization */
अटल पूर्णांक __init twl_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "LSI 3ware SAS/SATA-RAID Controller device driver for Linux v%s.\n", TW_DRIVER_VERSION);

	वापस pci_रेजिस्टर_driver(&twl_driver);
पूर्ण /* End twl_init() */

/* This function is called on driver निकास */
अटल व्योम __निकास twl_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&twl_driver);
पूर्ण /* End twl_निकास() */

module_init(twl_init);
module_निकास(twl_निकास);

