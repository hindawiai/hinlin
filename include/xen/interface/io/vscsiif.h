<शैली गुरु>
/******************************************************************************
 * vscsiअगर.h
 *
 * Based on the blkअगर.h code.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Copyright(c) FUJITSU Limited 2008.
 */

#अगर_अघोषित __XEN__PUBLIC_IO_SCSI_H__
#घोषणा __XEN__PUBLIC_IO_SCSI_H__

#समावेश "ring.h"
#समावेश "../grant_table.h"

/*
 * Feature and Parameter Negotiation
 * =================================
 * The two halves of a Xen pvSCSI driver utilize nodes within the XenStore to
 * communicate capabilities and to negotiate operating parameters.  This
 * section क्रमागतerates these nodes which reside in the respective front and
 * backend portions of the XenStore, following the XenBus convention.
 *
 * Any specअगरied शेष value is in effect अगर the corresponding XenBus node
 * is not present in the XenStore.
 *
 * XenStore nodes in sections marked "PRIVATE" are solely क्रम use by the
 * driver side whose XenBus tree contains them.
 *
 *****************************************************************************
 *                            Backend XenBus Nodes
 *****************************************************************************
 *
 *------------------ Backend Device Identअगरication (PRIVATE) ------------------
 *
 * p-devname
 *      Values:         string
 *
 *      A मुक्त string used to identअगरy the physical device (e.g. a disk name).
 *
 * p-dev
 *      Values:         string
 *
 *      A string specअगरying the backend device: either a 4-tuple "h:c:t:l"
 *      (host, controller, target, lun, all पूर्णांकegers), or a WWN (e.g.
 *      "naa.60014054ac780582").
 *
 * v-dev
 *      Values:         string
 *
 *      A string specअगरying the frontend device in क्रमm of a 4-tuple "h:c:t:l"
 *      (host, controller, target, lun, all पूर्णांकegers).
 *
 *--------------------------------- Features ---------------------------------
 *
 * feature-sg-grant
 *      Values:         अचिन्हित [VSCSIIF_SG_TABLESIZE...65535]
 *      Default Value:  0
 *
 *      Specअगरies the maximum number of scatter/gather elements in grant pages
 *      supported. If not set, the backend supports up to VSCSIIF_SG_TABLESIZE
 *      SG elements specअगरied directly in the request.
 *
 *****************************************************************************
 *                            Frontend XenBus Nodes
 *****************************************************************************
 *
 *----------------------- Request Transport Parameters -----------------------
 *
 * event-channel
 *      Values:         अचिन्हित
 *
 *      The identअगरier of the Xen event channel used to संकेत activity
 *      in the ring buffer.
 *
 * ring-ref
 *      Values:         अचिन्हित
 *
 *      The Xen grant reference granting permission क्रम the backend to map
 *      the sole page in a single page sized ring buffer.
 *
 * protocol
 *      Values:         string (XEN_IO_PROTO_ABI_*)
 *      Default Value:  XEN_IO_PROTO_ABI_NATIVE
 *
 *      The machine ABI rules governing the क्रमmat of all ring request and
 *      response काष्ठाures.
 */

/* Requests from the frontend to the backend */

/*
 * Request a SCSI operation specअगरied via a CDB in vscsiअगर_request.cmnd.
 * The target is specअगरied via channel, id and lun.
 *
 * The operation to be perक्रमmed is specअगरied via a CDB in cmnd[], the length
 * of the CDB is in cmd_len. sc_data_direction specअगरies the direction of data
 * (to the device, from the device, or none at all).
 *
 * If data is to be transferred to or from the device the buffer(s) in the
 * guest memory is/are specअगरied via one or multiple scsiअगर_request_segment
 * descriptors each specअगरying a memory page via a grant_ref_t, a offset पूर्णांकo
 * the page and the length of the area in that page. All scsiअगर_request_segment
 * areas concatenated क्रमm the resulting data buffer used by the operation.
 * If the number of scsiअगर_request_segment areas is not too large (less than
 * or equal VSCSIIF_SG_TABLESIZE) the areas can be specअगरied directly in the
 * seg[] array and the number of valid scsiअगर_request_segment elements is to be
 * set in nr_segments.
 *
 * If "feature-sg-grant" in the Xenstore is set it is possible to specअगरy more
 * than VSCSIIF_SG_TABLESIZE scsiअगर_request_segment elements via indirection.
 * The maximum number of allowed scsiअगर_request_segment elements is the value
 * of the "feature-sg-grant" entry from Xenstore. When using indirection the
 * seg[] array करोesn't contain specअगरications of the data buffers, but
 * references to scsiअगर_request_segment arrays, which in turn reference the
 * data buffers. While nr_segments holds the number of populated seg[] entries
 * (plus the set VSCSIIF_SG_GRANT bit), the number of scsiअगर_request_segment
 * elements referencing the target data buffers is calculated from the lengths
 * of the seg[] elements (the sum of all valid seg[].length भागided by the
 * size of one scsiअगर_request_segment काष्ठाure).
 */
#घोषणा VSCSIIF_ACT_SCSI_CDB		1

/*
 * Request पात of a running operation क्रम the specअगरied target given by
 * channel, id, lun and the operation's rqid in ref_rqid.
 */
#घोषणा VSCSIIF_ACT_SCSI_ABORT		2

/*
 * Request a device reset of the specअगरied target (channel and id).
 */
#घोषणा VSCSIIF_ACT_SCSI_RESET		3

/*
 * Preset scatter/gather elements क्रम a following request. Deprecated.
 * Keeping the define only to aव्योम usage of the value "4" क्रम other actions.
 */
#घोषणा VSCSIIF_ACT_SCSI_SG_PRESET	4

/*
 * Maximum scatter/gather segments per request.
 *
 * Considering balance between allocating at least 16 "vscsiif_request"
 * काष्ठाures on one page (4096 bytes) and the number of scatter/gather
 * elements needed, we decided to use 26 as a magic number.
 *
 * If "feature-sg-grant" is set, more scatter/gather elements can be specअगरied
 * by placing them in one or more (up to VSCSIIF_SG_TABLESIZE) granted pages.
 * In this हाल the vscsiअगर_request seg elements करोn't contain references to
 * the user data, but to the SG elements referencing the user data.
 */
#घोषणा VSCSIIF_SG_TABLESIZE		26

/*
 * based on Linux kernel 2.6.18, still valid
 * Changing these values requires support of multiple protocols via the rings
 * as "old clients" will blindly use these values and the resulting काष्ठाure
 * sizes.
 */
#घोषणा VSCSIIF_MAX_COMMAND_SIZE	16
#घोषणा VSCSIIF_SENSE_BUFFERSIZE	96

काष्ठा scsiअगर_request_segment अणु
	grant_ref_t gref;
	uपूर्णांक16_t offset;
	uपूर्णांक16_t length;
पूर्ण;

#घोषणा VSCSIIF_SG_PER_PAGE (PAGE_SIZE / माप(काष्ठा scsiअगर_request_segment))

/* Size of one request is 252 bytes */
काष्ठा vscsiअगर_request अणु
	uपूर्णांक16_t rqid;		/* निजी guest value, echoed in resp  */
	uपूर्णांक8_t act;		/* command between backend and frontend */
	uपूर्णांक8_t cmd_len;	/* valid CDB bytes */

	uपूर्णांक8_t cmnd[VSCSIIF_MAX_COMMAND_SIZE];	/* the CDB */
	uपूर्णांक16_t समयout_per_command;	/* deprecated */
	uपूर्णांक16_t channel, id, lun;	/* (भव) device specअगरication */
	uपूर्णांक16_t ref_rqid;		/* command पात reference */
	uपूर्णांक8_t sc_data_direction;	/* क्रम DMA_TO_DEVICE(1)
					   DMA_FROM_DEVICE(2)
					   DMA_NONE(3) requests */
	uपूर्णांक8_t nr_segments;		/* Number of pieces of scatter-gather */
/*
 * flag in nr_segments: SG elements via grant page
 *
 * If VSCSIIF_SG_GRANT is set, the low 7 bits of nr_segments specअगरy the number
 * of grant pages containing SG elements. Usable अगर "feature-sg-grant" set.
 */
#घोषणा VSCSIIF_SG_GRANT	0x80

	काष्ठा scsiअगर_request_segment seg[VSCSIIF_SG_TABLESIZE];
	uपूर्णांक32_t reserved[3];
पूर्ण;

/* Size of one response is 252 bytes */
काष्ठा vscsiअगर_response अणु
	uपूर्णांक16_t rqid;		/* identअगरies request */
	uपूर्णांक8_t padding;
	uपूर्णांक8_t sense_len;
	uपूर्णांक8_t sense_buffer[VSCSIIF_SENSE_BUFFERSIZE];
	पूर्णांक32_t rslt;
	uपूर्णांक32_t residual_len;	/* request bufflen -
				   वापस the value from physical device */
	uपूर्णांक32_t reserved[36];
पूर्ण;

DEFINE_RING_TYPES(vscsiअगर, काष्ठा vscsiअगर_request, काष्ठा vscsiअगर_response);

#पूर्ण_अगर /*__XEN__PUBLIC_IO_SCSI_H__*/
