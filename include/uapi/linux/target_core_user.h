<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __TARGET_CORE_USER_H
#घोषणा __TARGET_CORE_USER_H

/* This header will be used by application too */

#समावेश <linux/types.h>
#समावेश <linux/uपन.स>

#घोषणा TCMU_VERSION "2.0"

/**
 * DOC: Ring Design
 * Ring Design
 * -----------
 *
 * The mmaped area is भागided पूर्णांकo three parts:
 * 1) The mailbox (काष्ठा tcmu_mailbox, below);
 * 2) The command ring;
 * 3) Everything beyond the command ring (data).
 *
 * The mailbox tells userspace the offset of the command ring from the
 * start of the shared memory region, and how big the command ring is.
 *
 * The kernel passes SCSI commands to userspace by putting a काष्ठा
 * tcmu_cmd_entry in the ring, updating mailbox->cmd_head, and poking
 * userspace via UIO's पूर्णांकerrupt mechanism.
 *
 * tcmu_cmd_entry contains a header. If the header type is PAD,
 * userspace should skip hdr->length bytes (mod cmdr_size) to find the
 * next cmd_entry.
 *
 * Otherwise, the entry will contain offsets पूर्णांकo the mmaped area that
 * contain the cdb and data buffers -- the latter accessible via the
 * iov array. iov addresses are also offsets पूर्णांकo the shared area.
 *
 * When userspace is completed handling the command, set
 * entry->rsp.scsi_status, fill in rsp.sense_buffer अगर appropriate,
 * and also set mailbox->cmd_tail equal to the old cmd_tail plus
 * hdr->length, mod cmdr_size. If cmd_tail करोesn't equal cmd_head, it
 * should process the next packet the same way, and so on.
 */

#घोषणा TCMU_MAILBOX_VERSION 2
#घोषणा ALIGN_SIZE 64 /* Should be enough क्रम most CPUs */
#घोषणा TCMU_MAILBOX_FLAG_CAP_OOOC (1 << 0) /* Out-of-order completions */
#घोषणा TCMU_MAILBOX_FLAG_CAP_READ_LEN (1 << 1) /* Read data length */
#घोषणा TCMU_MAILBOX_FLAG_CAP_TMR (1 << 2) /* TMR notअगरications */

काष्ठा tcmu_mailbox अणु
	__u16 version;
	__u16 flags;
	__u32 cmdr_off;
	__u32 cmdr_size;

	__u32 cmd_head;

	/* Updated by user. On its own cacheline */
	__u32 cmd_tail __attribute__((__aligned__(ALIGN_SIZE)));

पूर्ण __packed;

क्रमागत tcmu_opcode अणु
	TCMU_OP_PAD = 0,
	TCMU_OP_CMD,
	TCMU_OP_TMR,
पूर्ण;

/*
 * Only a few opcodes, and length is 8-byte aligned, so use low bits क्रम opcode.
 */
काष्ठा tcmu_cmd_entry_hdr अणु
	__u32 len_op;
	__u16 cmd_id;
	__u8 kflags;
#घोषणा TCMU_UFLAG_UNKNOWN_OP 0x1
#घोषणा TCMU_UFLAG_READ_LEN   0x2
	__u8 uflags;

पूर्ण __packed;

#घोषणा TCMU_OP_MASK 0x7

अटल अंतरभूत क्रमागत tcmu_opcode tcmu_hdr_get_op(__u32 len_op)
अणु
	वापस len_op & TCMU_OP_MASK;
पूर्ण

अटल अंतरभूत व्योम tcmu_hdr_set_op(__u32 *len_op, क्रमागत tcmu_opcode op)
अणु
	*len_op &= ~TCMU_OP_MASK;
	*len_op |= (op & TCMU_OP_MASK);
पूर्ण

अटल अंतरभूत __u32 tcmu_hdr_get_len(__u32 len_op)
अणु
	वापस len_op & ~TCMU_OP_MASK;
पूर्ण

अटल अंतरभूत व्योम tcmu_hdr_set_len(__u32 *len_op, __u32 len)
अणु
	*len_op &= TCMU_OP_MASK;
	*len_op |= len;
पूर्ण

/* Currently the same as SCSI_SENSE_BUFFERSIZE */
#घोषणा TCMU_SENSE_BUFFERSIZE 96

काष्ठा tcmu_cmd_entry अणु
	काष्ठा tcmu_cmd_entry_hdr hdr;

	जोड़ अणु
		काष्ठा अणु
			__u32 iov_cnt;
			__u32 iov_bidi_cnt;
			__u32 iov_dअगर_cnt;
			__u64 cdb_off;
			__u64 __pad1;
			__u64 __pad2;
			काष्ठा iovec iov[0];
		पूर्ण req;
		काष्ठा अणु
			__u8 scsi_status;
			__u8 __pad1;
			__u16 __pad2;
			__u32 पढ़ो_len;
			अक्षर sense_buffer[TCMU_SENSE_BUFFERSIZE];
		पूर्ण rsp;
	पूर्ण;

पूर्ण __packed;

काष्ठा tcmu_पंचांगr_entry अणु
	काष्ठा tcmu_cmd_entry_hdr hdr;

#घोषणा TCMU_TMR_UNKNOWN		0
#घोषणा TCMU_TMR_ABORT_TASK		1
#घोषणा TCMU_TMR_ABORT_TASK_SET		2
#घोषणा TCMU_TMR_CLEAR_ACA		3
#घोषणा TCMU_TMR_CLEAR_TASK_SET		4
#घोषणा TCMU_TMR_LUN_RESET		5
#घोषणा TCMU_TMR_TARGET_WARM_RESET	6
#घोषणा TCMU_TMR_TARGET_COLD_RESET	7
/* Pseuकरो reset due to received PR OUT */
#घोषणा TCMU_TMR_LUN_RESET_PRO		128
	__u8 पंचांगr_type;

	__u8 __pad1;
	__u16 __pad2;
	__u32 cmd_cnt;
	__u64 __pad3;
	__u64 __pad4;
	__u16 cmd_ids[0];
पूर्ण __packed;

#घोषणा TCMU_OP_ALIGN_SIZE माप(__u64)

क्रमागत tcmu_genl_cmd अणु
	TCMU_CMD_UNSPEC,
	TCMU_CMD_ADDED_DEVICE,
	TCMU_CMD_REMOVED_DEVICE,
	TCMU_CMD_RECONFIG_DEVICE,
	TCMU_CMD_ADDED_DEVICE_DONE,
	TCMU_CMD_REMOVED_DEVICE_DONE,
	TCMU_CMD_RECONFIG_DEVICE_DONE,
	TCMU_CMD_SET_FEATURES,
	__TCMU_CMD_MAX,
पूर्ण;
#घोषणा TCMU_CMD_MAX (__TCMU_CMD_MAX - 1)

क्रमागत tcmu_genl_attr अणु
	TCMU_ATTR_UNSPEC,
	TCMU_ATTR_DEVICE,
	TCMU_ATTR_MINOR,
	TCMU_ATTR_PAD,
	TCMU_ATTR_DEV_CFG,
	TCMU_ATTR_DEV_SIZE,
	TCMU_ATTR_WRITECACHE,
	TCMU_ATTR_CMD_STATUS,
	TCMU_ATTR_DEVICE_ID,
	TCMU_ATTR_SUPP_KERN_CMD_REPLY,
	__TCMU_ATTR_MAX,
पूर्ण;
#घोषणा TCMU_ATTR_MAX (__TCMU_ATTR_MAX - 1)

#पूर्ण_अगर
