<शैली गुरु>
#अगर_अघोषित _UAPI_LINUX_VIRTIO_RING_H
#घोषणा _UAPI_LINUX_VIRTIO_RING_H
/* An पूर्णांकerface क्रम efficient virtio implementation, currently क्रम use by KVM,
 * but hopefully others soon.  Do NOT change this since it will
 * अवरोध existing servers and clients.
 *
 * This header is BSD licensed so anyone can use the definitions to implement
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
 * SUCH DAMAGE.
 *
 * Copyright Rusty Russell IBM Corporation 2007. */
#अगर_अघोषित __KERNEL__
#समावेश <मानक_निवेशt.h>
#पूर्ण_अगर
#समावेश <linux/types.h>
#समावेश <linux/virtio_types.h>

/* This marks a buffer as continuing via the next field. */
#घोषणा VRING_DESC_F_NEXT	1
/* This marks a buffer as ग_लिखो-only (otherwise पढ़ो-only). */
#घोषणा VRING_DESC_F_WRITE	2
/* This means the buffer contains a list of buffer descriptors. */
#घोषणा VRING_DESC_F_INसूचीECT	4

/*
 * Mark a descriptor as available or used in packed ring.
 * Notice: they are defined as shअगरts instead of shअगरted values.
 */
#घोषणा VRING_PACKED_DESC_F_AVAIL	7
#घोषणा VRING_PACKED_DESC_F_USED	15

/* The Host uses this in used->flags to advise the Guest: करोn't kick me when
 * you add a buffer.  It's unreliable, so it's simply an optimization.  Guest
 * will still kick अगर it's out of buffers. */
#घोषणा VRING_USED_F_NO_NOTIFY	1
/* The Guest uses this in avail->flags to advise the Host: करोn't पूर्णांकerrupt me
 * when you consume a buffer.  It's unreliable, so it's simply an
 * optimization.  */
#घोषणा VRING_AVAIL_F_NO_INTERRUPT	1

/* Enable events in packed ring. */
#घोषणा VRING_PACKED_EVENT_FLAG_ENABLE	0x0
/* Disable events in packed ring. */
#घोषणा VRING_PACKED_EVENT_FLAG_DISABLE	0x1
/*
 * Enable events क्रम a specअगरic descriptor in packed ring.
 * (as specअगरied by Descriptor Ring Change Event Offset/Wrap Counter).
 * Only valid अगर VIRTIO_RING_F_EVENT_IDX has been negotiated.
 */
#घोषणा VRING_PACKED_EVENT_FLAG_DESC	0x2

/*
 * Wrap counter bit shअगरt in event suppression काष्ठाure
 * of packed ring.
 */
#घोषणा VRING_PACKED_EVENT_F_WRAP_CTR	15

/* We support indirect buffer descriptors */
#घोषणा VIRTIO_RING_F_INसूचीECT_DESC	28

/* The Guest publishes the used index क्रम which it expects an पूर्णांकerrupt
 * at the end of the avail ring. Host should ignore the avail->flags field. */
/* The Host publishes the avail index क्रम which it expects a kick
 * at the end of the used ring. Guest should ignore the used->flags field. */
#घोषणा VIRTIO_RING_F_EVENT_IDX		29

/* Alignment requirements क्रम vring elements.
 * When using pre-virtio 1.0 layout, these fall out naturally.
 */
#घोषणा VRING_AVAIL_ALIGN_SIZE 2
#घोषणा VRING_USED_ALIGN_SIZE 4
#घोषणा VRING_DESC_ALIGN_SIZE 16

/* Virtio ring descriptors: 16 bytes.  These can chain together via "next". */
काष्ठा vring_desc अणु
	/* Address (guest-physical). */
	__virtio64 addr;
	/* Length. */
	__virtio32 len;
	/* The flags as indicated above. */
	__virtio16 flags;
	/* We chain unused descriptors via this, too */
	__virtio16 next;
पूर्ण;

काष्ठा vring_avail अणु
	__virtio16 flags;
	__virtio16 idx;
	__virtio16 ring[];
पूर्ण;

/* u32 is used here क्रम ids क्रम padding reasons. */
काष्ठा vring_used_elem अणु
	/* Index of start of used descriptor chain. */
	__virtio32 id;
	/* Total length of the descriptor chain which was used (written to) */
	__virtio32 len;
पूर्ण;

प्रकार काष्ठा vring_used_elem __attribute__((aligned(VRING_USED_ALIGN_SIZE)))
	vring_used_elem_t;

काष्ठा vring_used अणु
	__virtio16 flags;
	__virtio16 idx;
	vring_used_elem_t ring[];
पूर्ण;

/*
 * The ring element addresses are passed between components with dअगरferent
 * alignments assumptions. Thus, we might need to decrease the compiler-selected
 * alignment, and so must use a प्रकार to make sure the aligned attribute
 * actually takes hold:
 *
 * https://gcc.gnu.org/onlineकरोcs//gcc/Common-Type-Attributes.hपंचांगl#Common-Type-Attributes
 *
 * When used on a काष्ठा, or काष्ठा member, the aligned attribute can only
 * increase the alignment; in order to decrease it, the packed attribute must
 * be specअगरied as well. When used as part of a प्रकार, the aligned attribute
 * can both increase and decrease alignment, and specअगरying the packed
 * attribute generates a warning.
 */
प्रकार काष्ठा vring_desc __attribute__((aligned(VRING_DESC_ALIGN_SIZE)))
	vring_desc_t;
प्रकार काष्ठा vring_avail __attribute__((aligned(VRING_AVAIL_ALIGN_SIZE)))
	vring_avail_t;
प्रकार काष्ठा vring_used __attribute__((aligned(VRING_USED_ALIGN_SIZE)))
	vring_used_t;

काष्ठा vring अणु
	अचिन्हित पूर्णांक num;

	vring_desc_t *desc;

	vring_avail_t *avail;

	vring_used_t *used;
पूर्ण;

#अगर_अघोषित VIRTIO_RING_NO_LEGACY

/* The standard layout क्रम the ring is a continuous chunk of memory which looks
 * like this.  We assume num is a घातer of 2.
 *
 * काष्ठा vring
 * अणु
 *	// The actual descriptors (16 bytes each)
 *	काष्ठा vring_desc desc[num];
 *
 *	// A ring of available descriptor heads with मुक्त-running index.
 *	__virtio16 avail_flags;
 *	__virtio16 avail_idx;
 *	__virtio16 available[num];
 *	__virtio16 used_event_idx;
 *
 *	// Padding to the next align boundary.
 *	अक्षर pad[];
 *
 *	// A ring of used descriptor heads with मुक्त-running index.
 *	__virtio16 used_flags;
 *	__virtio16 used_idx;
 *	काष्ठा vring_used_elem used[num];
 *	__virtio16 avail_event_idx;
 * पूर्ण;
 */
/* We publish the used event index at the end of the available ring, and vice
 * versa. They are at the end क्रम backwards compatibility. */
#घोषणा vring_used_event(vr) ((vr)->avail->ring[(vr)->num])
#घोषणा vring_avail_event(vr) (*(__virtio16 *)&(vr)->used->ring[(vr)->num])

अटल अंतरभूत व्योम vring_init(काष्ठा vring *vr, अचिन्हित पूर्णांक num, व्योम *p,
			      अचिन्हित दीर्घ align)
अणु
	vr->num = num;
	vr->desc = p;
	vr->avail = (काष्ठा vring_avail *)((अक्षर *)p + num * माप(काष्ठा vring_desc));
	vr->used = (व्योम *)(((uपूर्णांकptr_t)&vr->avail->ring[num] + माप(__virtio16)
		+ align-1) & ~(align - 1));
पूर्ण

अटल अंतरभूत अचिन्हित vring_size(अचिन्हित पूर्णांक num, अचिन्हित दीर्घ align)
अणु
	वापस ((माप(काष्ठा vring_desc) * num + माप(__virtio16) * (3 + num)
		 + align - 1) & ~(align - 1))
		+ माप(__virtio16) * 3 + माप(काष्ठा vring_used_elem) * num;
पूर्ण

#पूर्ण_अगर /* VIRTIO_RING_NO_LEGACY */

/* The following is used with USED_EVENT_IDX and AVAIL_EVENT_IDX */
/* Assuming a given event_idx value from the other side, अगर
 * we have just incremented index from old to new_idx,
 * should we trigger an event? */
अटल अंतरभूत पूर्णांक vring_need_event(__u16 event_idx, __u16 new_idx, __u16 old)
अणु
	/* Note: Xen has similar logic क्रम notअगरication hold-off
	 * in include/xen/पूर्णांकerface/io/ring.h with req_event and req_prod
	 * corresponding to event_idx + 1 and new_idx respectively.
	 * Note also that req_event and req_prod in Xen start at 1,
	 * event indexes in virtio start at 0. */
	वापस (__u16)(new_idx - event_idx - 1) < (__u16)(new_idx - old);
पूर्ण

काष्ठा vring_packed_desc_event अणु
	/* Descriptor Ring Change Event Offset/Wrap Counter. */
	__le16 off_wrap;
	/* Descriptor Ring Change Event Flags. */
	__le16 flags;
पूर्ण;

काष्ठा vring_packed_desc अणु
	/* Buffer Address. */
	__le64 addr;
	/* Buffer Length. */
	__le32 len;
	/* Buffer ID. */
	__le16 id;
	/* The flags depending on descriptor type. */
	__le16 flags;
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_VIRTIO_RING_H */
