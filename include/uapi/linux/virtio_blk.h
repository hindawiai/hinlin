<शैली गुरु>
#अगर_अघोषित _LINUX_VIRTIO_BLK_H
#घोषणा _LINUX_VIRTIO_BLK_H
/* This header is BSD licensed so anyone can use the definitions to implement
 * compatible drivers/servers.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of IBM nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE. */
#समावेश <linux/types.h>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_types.h>

/* Feature bits */
#घोषणा VIRTIO_BLK_F_SIZE_MAX	1	/* Indicates maximum segment size */
#घोषणा VIRTIO_BLK_F_SEG_MAX	2	/* Indicates maximum # of segments */
#घोषणा VIRTIO_BLK_F_GEOMETRY	4	/* Legacy geometry available  */
#घोषणा VIRTIO_BLK_F_RO		5	/* Disk is पढ़ो-only */
#घोषणा VIRTIO_BLK_F_BLK_SIZE	6	/* Block size of disk is available*/
#घोषणा VIRTIO_BLK_F_TOPOLOGY	10	/* Topology inक्रमmation is available */
#घोषणा VIRTIO_BLK_F_MQ		12	/* support more than one vq */
#घोषणा VIRTIO_BLK_F_DISCARD	13	/* DISCARD is supported */
#घोषणा VIRTIO_BLK_F_WRITE_ZEROES	14	/* WRITE ZEROES is supported */

/* Legacy feature bits */
#अगर_अघोषित VIRTIO_BLK_NO_LEGACY
#घोषणा VIRTIO_BLK_F_BARRIER	0	/* Does host support barriers? */
#घोषणा VIRTIO_BLK_F_SCSI	7	/* Supports scsi command passthru */
#घोषणा VIRTIO_BLK_F_FLUSH	9	/* Flush command supported */
#घोषणा VIRTIO_BLK_F_CONFIG_WCE	11	/* Writeback mode available in config */
#अगर_अघोषित __KERNEL__
/* Old (deprecated) name क्रम VIRTIO_BLK_F_FLUSH. */
#घोषणा VIRTIO_BLK_F_WCE VIRTIO_BLK_F_FLUSH
#पूर्ण_अगर
#पूर्ण_अगर /* !VIRTIO_BLK_NO_LEGACY */

#घोषणा VIRTIO_BLK_ID_BYTES	20	/* ID string length */

काष्ठा virtio_blk_config अणु
	/* The capacity (in 512-byte sectors). */
	__virtio64 capacity;
	/* The maximum segment size (अगर VIRTIO_BLK_F_SIZE_MAX) */
	__virtio32 size_max;
	/* The maximum number of segments (अगर VIRTIO_BLK_F_SEG_MAX) */
	__virtio32 seg_max;
	/* geometry of the device (अगर VIRTIO_BLK_F_GEOMETRY) */
	काष्ठा virtio_blk_geometry अणु
		__virtio16 cylinders;
		__u8 heads;
		__u8 sectors;
	पूर्ण geometry;

	/* block size of device (अगर VIRTIO_BLK_F_BLK_SIZE) */
	__virtio32 blk_size;

	/* the next 4 entries are guarded by VIRTIO_BLK_F_TOPOLOGY  */
	/* exponent क्रम physical block per logical block. */
	__u8 physical_block_exp;
	/* alignment offset in logical blocks. */
	__u8 alignment_offset;
	/* minimum I/O size without perक्रमmance penalty in logical blocks. */
	__virtio16 min_io_size;
	/* optimal sustained I/O size in logical blocks. */
	__virtio32 opt_io_size;

	/* ग_लिखोback mode (अगर VIRTIO_BLK_F_CONFIG_WCE) */
	__u8 wce;
	__u8 unused;

	/* number of vqs, only available when VIRTIO_BLK_F_MQ is set */
	__virtio16 num_queues;

	/* the next 3 entries are guarded by VIRTIO_BLK_F_DISCARD */
	/*
	 * The maximum discard sectors (in 512-byte sectors) क्रम
	 * one segment.
	 */
	__virtio32 max_discard_sectors;
	/*
	 * The maximum number of discard segments in a
	 * discard command.
	 */
	__virtio32 max_discard_seg;
	/* Discard commands must be aligned to this number of sectors. */
	__virtio32 discard_sector_alignment;

	/* the next 3 entries are guarded by VIRTIO_BLK_F_WRITE_ZEROES */
	/*
	 * The maximum number of ग_लिखो zeroes sectors (in 512-byte sectors) in
	 * one segment.
	 */
	__virtio32 max_ग_लिखो_zeroes_sectors;
	/*
	 * The maximum number of segments in a ग_लिखो zeroes
	 * command.
	 */
	__virtio32 max_ग_लिखो_zeroes_seg;
	/*
	 * Set अगर a VIRTIO_BLK_T_WRITE_ZEROES request may result in the
	 * deallocation of one or more of the sectors.
	 */
	__u8 ग_लिखो_zeroes_may_unmap;

	__u8 unused1[3];
पूर्ण __attribute__((packed));

/*
 * Command types
 *
 * Usage is a bit tricky as some bits are used as flags and some are not.
 *
 * Rules:
 *   VIRTIO_BLK_T_OUT may be combined with VIRTIO_BLK_T_SCSI_CMD or
 *   VIRTIO_BLK_T_BARRIER.  VIRTIO_BLK_T_FLUSH is a command of its own
 *   and may not be combined with any of the other flags.
 */

/* These two define direction. */
#घोषणा VIRTIO_BLK_T_IN		0
#घोषणा VIRTIO_BLK_T_OUT	1

#अगर_अघोषित VIRTIO_BLK_NO_LEGACY
/* This bit says it's a scsi command, not an actual पढ़ो or ग_लिखो. */
#घोषणा VIRTIO_BLK_T_SCSI_CMD	2
#पूर्ण_अगर /* VIRTIO_BLK_NO_LEGACY */

/* Cache flush command */
#घोषणा VIRTIO_BLK_T_FLUSH	4

/* Get device ID command */
#घोषणा VIRTIO_BLK_T_GET_ID    8

/* Discard command */
#घोषणा VIRTIO_BLK_T_DISCARD	11

/* Write zeroes command */
#घोषणा VIRTIO_BLK_T_WRITE_ZEROES	13

#अगर_अघोषित VIRTIO_BLK_NO_LEGACY
/* Barrier beक्रमe this op. */
#घोषणा VIRTIO_BLK_T_BARRIER	0x80000000
#पूर्ण_अगर /* !VIRTIO_BLK_NO_LEGACY */

/*
 * This comes first in the पढ़ो scatter-gather list.
 * For legacy virtio, अगर VIRTIO_F_ANY_LAYOUT is not negotiated,
 * this is the first element of the पढ़ो scatter-gather list.
 */
काष्ठा virtio_blk_outhdr अणु
	/* VIRTIO_BLK_T* */
	__virtio32 type;
	/* io priority. */
	__virtio32 ioprio;
	/* Sector (ie. 512 byte offset) */
	__virtio64 sector;
पूर्ण;

/* Unmap this range (only valid क्रम ग_लिखो zeroes command) */
#घोषणा VIRTIO_BLK_WRITE_ZEROES_FLAG_UNMAP	0x00000001

/* Discard/ग_लिखो zeroes range क्रम each request. */
काष्ठा virtio_blk_discard_ग_लिखो_zeroes अणु
	/* discard/ग_लिखो zeroes start sector */
	__le64 sector;
	/* number of discard/ग_लिखो zeroes sectors */
	__le32 num_sectors;
	/* flags क्रम this range */
	__le32 flags;
पूर्ण;

#अगर_अघोषित VIRTIO_BLK_NO_LEGACY
काष्ठा virtio_scsi_inhdr अणु
	__virtio32 errors;
	__virtio32 data_len;
	__virtio32 sense_len;
	__virtio32 residual;
पूर्ण;
#पूर्ण_अगर /* !VIRTIO_BLK_NO_LEGACY */

/* And this is the final byte of the ग_लिखो scatter-gather list. */
#घोषणा VIRTIO_BLK_S_OK		0
#घोषणा VIRTIO_BLK_S_IOERR	1
#घोषणा VIRTIO_BLK_S_UNSUPP	2
#पूर्ण_अगर /* _LINUX_VIRTIO_BLK_H */
