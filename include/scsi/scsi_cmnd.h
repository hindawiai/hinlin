<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_SCSI_CMND_H
#घोषणा _SCSI_SCSI_CMND_H

#समावेश <linux/dma-mapping.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/t10-pi.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/scatterlist.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_request.h>

काष्ठा Scsi_Host;
काष्ठा scsi_driver;

/*
 * MAX_COMMAND_SIZE is:
 * The दीर्घest fixed-length SCSI CDB as per the SCSI standard.
 * fixed-length means: commands that their size can be determined
 * by their opcode and the CDB करोes not carry a length specअगरier, (unlike
 * the VARIABLE_LENGTH_CMD(0x7f) command). This is actually not exactly
 * true and the SCSI standard also defines extended commands and
 * venकरोr specअगरic commands that can be bigger than 16 bytes. The kernel
 * will support these using the same infraकाष्ठाure used क्रम VARLEN CDB's.
 * So in effect MAX_COMMAND_SIZE means the maximum size command scsi-ml
 * supports without specअगरying a cmd_len by ULD's
 */
#घोषणा MAX_COMMAND_SIZE 16
#अगर (MAX_COMMAND_SIZE > BLK_MAX_CDB)
# error MAX_COMMAND_SIZE can not be bigger than BLK_MAX_CDB
#पूर्ण_अगर

काष्ठा scsi_data_buffer अणु
	काष्ठा sg_table table;
	अचिन्हित length;
पूर्ण;

/* embedded in scsi_cmnd */
काष्ठा scsi_poपूर्णांकer अणु
	अक्षर *ptr;		/* data poपूर्णांकer */
	पूर्णांक this_residual;	/* left in this buffer */
	काष्ठा scatterlist *buffer;	/* which buffer */
	पूर्णांक buffers_residual;	/* how many buffers left */

        dma_addr_t dma_handle;

	अस्थिर पूर्णांक Status;
	अस्थिर पूर्णांक Message;
	अस्थिर पूर्णांक have_data_in;
	अस्थिर पूर्णांक sent_command;
	अस्थिर पूर्णांक phase;
पूर्ण;

/* क्रम scmd->flags */
#घोषणा SCMD_TAGGED		(1 << 0)
#घोषणा SCMD_INITIALIZED	(1 << 1)
#घोषणा SCMD_LAST		(1 << 2)
/* flags preserved across unprep / reprep */
#घोषणा SCMD_PRESERVED_FLAGS	(SCMD_INITIALIZED)

/* क्रम scmd->state */
#घोषणा SCMD_STATE_COMPLETE	0
#घोषणा SCMD_STATE_INFLIGHT	1

काष्ठा scsi_cmnd अणु
	काष्ठा scsi_request req;
	काष्ठा scsi_device *device;
	काष्ठा list_head eh_entry; /* entry क्रम the host eh_cmd_q */
	काष्ठा delayed_work पात_work;

	काष्ठा rcu_head rcu;

	पूर्णांक eh_eflags;		/* Used by error handlr */

	पूर्णांक budget_token;

	/*
	 * This is set to jअगरfies as it was when the command was first
	 * allocated.  It is used to समय how दीर्घ the command has
	 * been outstanding
	 */
	अचिन्हित दीर्घ jअगरfies_at_alloc;

	पूर्णांक retries;
	पूर्णांक allowed;

	अचिन्हित अक्षर prot_op;
	अचिन्हित अक्षर prot_type;
	अचिन्हित अक्षर prot_flags;

	अचिन्हित लघु cmd_len;
	क्रमागत dma_data_direction sc_data_direction;

	/* These elements define the operation we are about to perक्रमm */
	अचिन्हित अक्षर *cmnd;


	/* These elements define the operation we ultimately want to perक्रमm */
	काष्ठा scsi_data_buffer sdb;
	काष्ठा scsi_data_buffer *prot_sdb;

	अचिन्हित underflow;	/* Return error अगर less than
				   this amount is transferred */

	अचिन्हित transfersize;	/* How much we are guaranteed to
				   transfer with each SCSI transfer
				   (ie, between disconnect / 
				   reconnects.   Probably == sector
				   size */

	काष्ठा request *request;	/* The command we are
				   	   working on */

	अचिन्हित अक्षर *sense_buffer;
				/* obtained by REQUEST SENSE when
				 * CHECK CONDITION is received on original
				 * command (स्वतः-sense). Length must be
				 * SCSI_SENSE_BUFFERSIZE bytes. */

	/* Low-level करोne function - can be used by low-level driver to poपूर्णांक
	 *        to completion function.  Not used by mid/upper level code. */
	व्योम (*scsi_करोne) (काष्ठा scsi_cmnd *);

	/*
	 * The following fields can be written to by the host specअगरic code. 
	 * Everything अन्यथा should be left alone. 
	 */
	काष्ठा scsi_poपूर्णांकer SCp;	/* Scratchpad used by some host adapters */

	अचिन्हित अक्षर *host_scribble;	/* The host adapter is allowed to
					 * call scsi_दो_स्मृति and get some memory
					 * and hang it here.  The host adapter
					 * is also expected to call scsi_मुक्त
					 * to release this memory.  (The memory
					 * obtained by scsi_दो_स्मृति is guaranteed
					 * to be at an address < 16Mb). */

	पूर्णांक result;		/* Status code from lower level driver */
	पूर्णांक flags;		/* Command flags */
	अचिन्हित दीर्घ state;	/* Command completion state */

	अचिन्हित अक्षर tag;	/* SCSI-II queued command tag */
	अचिन्हित पूर्णांक extra_len;	/* length of alignment and padding */
पूर्ण;

/*
 * Return the driver निजी allocation behind the command.
 * Only works अगर cmd_size is set in the host ढाँचा.
 */
अटल अंतरभूत व्योम *scsi_cmd_priv(काष्ठा scsi_cmnd *cmd)
अणु
	वापस cmd + 1;
पूर्ण

/* make sure not to use it with passthrough commands */
अटल अंतरभूत काष्ठा scsi_driver *scsi_cmd_to_driver(काष्ठा scsi_cmnd *cmd)
अणु
	वापस *(काष्ठा scsi_driver **)cmd->request->rq_disk->निजी_data;
पूर्ण

बाह्य व्योम scsi_finish_command(काष्ठा scsi_cmnd *cmd);

बाह्य व्योम *scsi_kmap_atomic_sg(काष्ठा scatterlist *sg, पूर्णांक sg_count,
				 माप_प्रकार *offset, माप_प्रकार *len);
बाह्य व्योम scsi_kunmap_atomic_sg(व्योम *virt);

blk_status_t scsi_alloc_sgtables(काष्ठा scsi_cmnd *cmd);
व्योम scsi_मुक्त_sgtables(काष्ठा scsi_cmnd *cmd);

#अगर_घोषित CONFIG_SCSI_DMA
बाह्य पूर्णांक scsi_dma_map(काष्ठा scsi_cmnd *cmd);
बाह्य व्योम scsi_dma_unmap(काष्ठा scsi_cmnd *cmd);
#अन्यथा /* !CONFIG_SCSI_DMA */
अटल अंतरभूत पूर्णांक scsi_dma_map(काष्ठा scsi_cmnd *cmd) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम scsi_dma_unmap(काष्ठा scsi_cmnd *cmd) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_SCSI_DMA */

अटल अंतरभूत अचिन्हित scsi_sg_count(काष्ठा scsi_cmnd *cmd)
अणु
	वापस cmd->sdb.table.nents;
पूर्ण

अटल अंतरभूत काष्ठा scatterlist *scsi_sglist(काष्ठा scsi_cmnd *cmd)
अणु
	वापस cmd->sdb.table.sgl;
पूर्ण

अटल अंतरभूत अचिन्हित scsi_bufflen(काष्ठा scsi_cmnd *cmd)
अणु
	वापस cmd->sdb.length;
पूर्ण

अटल अंतरभूत व्योम scsi_set_resid(काष्ठा scsi_cmnd *cmd, अचिन्हित पूर्णांक resid)
अणु
	cmd->req.resid_len = resid;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक scsi_get_resid(काष्ठा scsi_cmnd *cmd)
अणु
	वापस cmd->req.resid_len;
पूर्ण

#घोषणा scsi_क्रम_each_sg(cmd, sg, nseg, __i)			\
	क्रम_each_sg(scsi_sglist(cmd), sg, nseg, __i)

अटल अंतरभूत पूर्णांक scsi_sg_copy_from_buffer(काष्ठा scsi_cmnd *cmd,
					   व्योम *buf, पूर्णांक buflen)
अणु
	वापस sg_copy_from_buffer(scsi_sglist(cmd), scsi_sg_count(cmd),
				   buf, buflen);
पूर्ण

अटल अंतरभूत पूर्णांक scsi_sg_copy_to_buffer(काष्ठा scsi_cmnd *cmd,
					 व्योम *buf, पूर्णांक buflen)
अणु
	वापस sg_copy_to_buffer(scsi_sglist(cmd), scsi_sg_count(cmd),
				 buf, buflen);
पूर्ण

/*
 * The operations below are hपूर्णांकs that tell the controller driver how
 * to handle I/Os with DIF or similar types of protection inक्रमmation.
 */
क्रमागत scsi_prot_operations अणु
	/* Normal I/O */
	SCSI_PROT_NORMAL = 0,

	/* OS-HBA: Protected, HBA-Target: Unरक्षित */
	SCSI_PROT_READ_INSERT,
	SCSI_PROT_WRITE_STRIP,

	/* OS-HBA: Unरक्षित, HBA-Target: Protected */
	SCSI_PROT_READ_STRIP,
	SCSI_PROT_WRITE_INSERT,

	/* OS-HBA: Protected, HBA-Target: Protected */
	SCSI_PROT_READ_PASS,
	SCSI_PROT_WRITE_PASS,
पूर्ण;

अटल अंतरभूत व्योम scsi_set_prot_op(काष्ठा scsi_cmnd *scmd, अचिन्हित अक्षर op)
अणु
	scmd->prot_op = op;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर scsi_get_prot_op(काष्ठा scsi_cmnd *scmd)
अणु
	वापस scmd->prot_op;
पूर्ण

क्रमागत scsi_prot_flags अणु
	SCSI_PROT_TRANSFER_PI		= 1 << 0,
	SCSI_PROT_GUARD_CHECK		= 1 << 1,
	SCSI_PROT_REF_CHECK		= 1 << 2,
	SCSI_PROT_REF_INCREMENT		= 1 << 3,
	SCSI_PROT_IP_CHECKSUM		= 1 << 4,
पूर्ण;

/*
 * The controller usually करोes not know anything about the target it
 * is communicating with.  However, when DIX is enabled the controller
 * must be know target type so it can verअगरy the protection
 * inक्रमmation passed aदीर्घ with the I/O.
 */
क्रमागत scsi_prot_target_type अणु
	SCSI_PROT_DIF_TYPE0 = 0,
	SCSI_PROT_DIF_TYPE1,
	SCSI_PROT_DIF_TYPE2,
	SCSI_PROT_DIF_TYPE3,
पूर्ण;

अटल अंतरभूत व्योम scsi_set_prot_type(काष्ठा scsi_cmnd *scmd, अचिन्हित अक्षर type)
अणु
	scmd->prot_type = type;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर scsi_get_prot_type(काष्ठा scsi_cmnd *scmd)
अणु
	वापस scmd->prot_type;
पूर्ण

अटल अंतरभूत sector_t scsi_get_lba(काष्ठा scsi_cmnd *scmd)
अणु
	वापस blk_rq_pos(scmd->request);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक scsi_prot_पूर्णांकerval(काष्ठा scsi_cmnd *scmd)
अणु
	वापस scmd->device->sector_size;
पूर्ण

अटल अंतरभूत अचिन्हित scsi_prot_sg_count(काष्ठा scsi_cmnd *cmd)
अणु
	वापस cmd->prot_sdb ? cmd->prot_sdb->table.nents : 0;
पूर्ण

अटल अंतरभूत काष्ठा scatterlist *scsi_prot_sglist(काष्ठा scsi_cmnd *cmd)
अणु
	वापस cmd->prot_sdb ? cmd->prot_sdb->table.sgl : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा scsi_data_buffer *scsi_prot(काष्ठा scsi_cmnd *cmd)
अणु
	वापस cmd->prot_sdb;
पूर्ण

#घोषणा scsi_क्रम_each_prot_sg(cmd, sg, nseg, __i)		\
	क्रम_each_sg(scsi_prot_sglist(cmd), sg, nseg, __i)

अटल अंतरभूत व्योम set_status_byte(काष्ठा scsi_cmnd *cmd, अक्षर status)
अणु
	cmd->result = (cmd->result & 0xffffff00) | status;
पूर्ण

अटल अंतरभूत व्योम set_msg_byte(काष्ठा scsi_cmnd *cmd, अक्षर status)
अणु
	cmd->result = (cmd->result & 0xffff00ff) | (status << 8);
पूर्ण

अटल अंतरभूत व्योम set_host_byte(काष्ठा scsi_cmnd *cmd, अक्षर status)
अणु
	cmd->result = (cmd->result & 0xff00ffff) | (status << 16);
पूर्ण

अटल अंतरभूत व्योम set_driver_byte(काष्ठा scsi_cmnd *cmd, अक्षर status)
अणु
	cmd->result = (cmd->result & 0x00ffffff) | (status << 24);
पूर्ण

अटल अंतरभूत अचिन्हित scsi_transfer_length(काष्ठा scsi_cmnd *scmd)
अणु
	अचिन्हित पूर्णांक xfer_len = scmd->sdb.length;
	अचिन्हित पूर्णांक prot_पूर्णांकerval = scsi_prot_पूर्णांकerval(scmd);

	अगर (scmd->prot_flags & SCSI_PROT_TRANSFER_PI)
		xfer_len += (xfer_len >> ilog2(prot_पूर्णांकerval)) * 8;

	वापस xfer_len;
पूर्ण

#पूर्ण_अगर /* _SCSI_SCSI_CMND_H */
