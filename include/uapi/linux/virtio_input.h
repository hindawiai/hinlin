<शैली गुरु>
#अगर_अघोषित _LINUX_VIRTIO_INPUT_H
#घोषणा _LINUX_VIRTIO_INPUT_H
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE. */

#समावेश <linux/types.h>

क्रमागत virtio_input_config_select अणु
	VIRTIO_INPUT_CFG_UNSET      = 0x00,
	VIRTIO_INPUT_CFG_ID_NAME    = 0x01,
	VIRTIO_INPUT_CFG_ID_SERIAL  = 0x02,
	VIRTIO_INPUT_CFG_ID_DEVIDS  = 0x03,
	VIRTIO_INPUT_CFG_PROP_BITS  = 0x10,
	VIRTIO_INPUT_CFG_EV_BITS    = 0x11,
	VIRTIO_INPUT_CFG_ABS_INFO   = 0x12,
पूर्ण;

काष्ठा virtio_input_असलinfo अणु
	__le32 min;
	__le32 max;
	__le32 fuzz;
	__le32 flat;
	__le32 res;
पूर्ण;

काष्ठा virtio_input_devids अणु
	__le16 bustype;
	__le16 venकरोr;
	__le16 product;
	__le16 version;
पूर्ण;

काष्ठा virtio_input_config अणु
	__u8    select;
	__u8    subsel;
	__u8    size;
	__u8    reserved[5];
	जोड़ अणु
		अक्षर string[128];
		__u8 biपंचांगap[128];
		काष्ठा virtio_input_असलinfo असल;
		काष्ठा virtio_input_devids ids;
	पूर्ण u;
पूर्ण;

काष्ठा virtio_input_event अणु
	__le16 type;
	__le16 code;
	__le32 value;
पूर्ण;

#पूर्ण_अगर /* _LINUX_VIRTIO_INPUT_H */
