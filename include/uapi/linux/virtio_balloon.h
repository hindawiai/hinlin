<शैली गुरु>
#अगर_अघोषित _LINUX_VIRTIO_BALLOON_H
#घोषणा _LINUX_VIRTIO_BALLOON_H
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
#समावेश <linux/virtio_types.h>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>

/* The feature biपंचांगap क्रम virtio balloon */
#घोषणा VIRTIO_BALLOON_F_MUST_TELL_HOST	0 /* Tell beक्रमe reclaiming pages */
#घोषणा VIRTIO_BALLOON_F_STATS_VQ	1 /* Memory Stats virtqueue */
#घोषणा VIRTIO_BALLOON_F_DEFLATE_ON_OOM	2 /* Deflate balloon on OOM */
#घोषणा VIRTIO_BALLOON_F_FREE_PAGE_HINT	3 /* VQ to report मुक्त pages */
#घोषणा VIRTIO_BALLOON_F_PAGE_POISON	4 /* Guest is using page poisoning */
#घोषणा VIRTIO_BALLOON_F_REPORTING	5 /* Page reporting virtqueue */

/* Size of a PFN in the balloon पूर्णांकerface. */
#घोषणा VIRTIO_BALLOON_PFN_SHIFT 12

#घोषणा VIRTIO_BALLOON_CMD_ID_STOP	0
#घोषणा VIRTIO_BALLOON_CMD_ID_DONE	1
काष्ठा virtio_balloon_config अणु
	/* Number of pages host wants Guest to give up. */
	__le32 num_pages;
	/* Number of pages we've actually got in balloon. */
	__le32 actual;
	/*
	 * Free page hपूर्णांक command id, पढ़ोonly by guest.
	 * Was previously named मुक्त_page_report_cmd_id so we
	 * need to carry that name क्रम legacy support.
	 */
	जोड़ अणु
		__le32 मुक्त_page_hपूर्णांक_cmd_id;
		__le32 मुक्त_page_report_cmd_id;	/* deprecated */
	पूर्ण;
	/* Stores PAGE_POISON अगर page poisoning is in use */
	__le32 poison_val;
पूर्ण;

#घोषणा VIRTIO_BALLOON_S_SWAP_IN  0   /* Amount of memory swapped in */
#घोषणा VIRTIO_BALLOON_S_SWAP_OUT 1   /* Amount of memory swapped out */
#घोषणा VIRTIO_BALLOON_S_MAJFLT   2   /* Number of major faults */
#घोषणा VIRTIO_BALLOON_S_MINFLT   3   /* Number of minor faults */
#घोषणा VIRTIO_BALLOON_S_MEMFREE  4   /* Total amount of मुक्त memory */
#घोषणा VIRTIO_BALLOON_S_MEMTOT   5   /* Total amount of memory */
#घोषणा VIRTIO_BALLOON_S_AVAIL    6   /* Available memory as in /proc */
#घोषणा VIRTIO_BALLOON_S_CACHES   7   /* Disk caches */
#घोषणा VIRTIO_BALLOON_S_HTLB_PGALLOC  8  /* Hugetlb page allocations */
#घोषणा VIRTIO_BALLOON_S_HTLB_PGFAIL   9  /* Hugetlb page allocation failures */
#घोषणा VIRTIO_BALLOON_S_NR       10

#घोषणा VIRTIO_BALLOON_S_NAMES_WITH_PREFIX(VIRTIO_BALLOON_S_NAMES_prefix) अणु \
	VIRTIO_BALLOON_S_NAMES_prefix "swap-in", \
	VIRTIO_BALLOON_S_NAMES_prefix "swap-out", \
	VIRTIO_BALLOON_S_NAMES_prefix "major-faults", \
	VIRTIO_BALLOON_S_NAMES_prefix "minor-faults", \
	VIRTIO_BALLOON_S_NAMES_prefix "free-memory", \
	VIRTIO_BALLOON_S_NAMES_prefix "total-memory", \
	VIRTIO_BALLOON_S_NAMES_prefix "available-memory", \
	VIRTIO_BALLOON_S_NAMES_prefix "disk-caches", \
	VIRTIO_BALLOON_S_NAMES_prefix "hugetlb-allocations", \
	VIRTIO_BALLOON_S_NAMES_prefix "hugetlb-failures" \
पूर्ण

#घोषणा VIRTIO_BALLOON_S_NAMES VIRTIO_BALLOON_S_NAMES_WITH_PREFIX("")

/*
 * Memory statistics काष्ठाure.
 * Driver fills an array of these काष्ठाures and passes to device.
 *
 * NOTE: fields are laid out in a way that would make compiler add padding
 * between and after fields, so we have to use compiler-specअगरic attributes to
 * pack it, to disable this padding. This also often causes compiler to
 * generate suboptimal code.
 *
 * We मुख्यtain this statistics काष्ठाure क्रमmat क्रम backwards compatibility,
 * but करोn't follow this example.
 *
 * If implementing a similar काष्ठाure, करो something like the below instead:
 *     काष्ठा virtio_balloon_stat अणु
 *         __virtio16 tag;
 *         __u8 reserved[6];
 *         __virtio64 val;
 *     पूर्ण;
 *
 * In other words, add explicit reserved fields to align field and
 * काष्ठाure boundaries at field size, aव्योमing compiler padding
 * without the packed attribute.
 */
काष्ठा virtio_balloon_stat अणु
	__virtio16 tag;
	__virtio64 val;
पूर्ण __attribute__((packed));

#पूर्ण_अगर /* _LINUX_VIRTIO_BALLOON_H */
